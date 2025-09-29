/*
-----------------------------
Title: LUX_Reader_calibrated
-----------------------------
Purpose: LUX_Reader_Calibrated
Hardware notes: ESP8266
Compiler: VSC 
Author: XLab42
Versions:
	1.0: 
Callibration function: Y(x) = 4.0043 e^(1.2885 x)
*/

// ------------------------------ libraries:
#include <Arduino.h>

// ------------------------------ constants & variables:
const float Vcc     = 3.3;      // NodeMCU ADC range (0–3.3 V)
const int   ADC_MAX = 1023;     // 10-bit ADC on ESP8266

// ------------------------------ functions:
float adcToVoltage(int adc) {
  return Vcc * (float)adc / (float)ADC_MAX;
}

// ------------------------------ setup:
void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("LDR lux meter using exponential calibration...");
}

// ------------------------------ loop:
void loop() {
  // Simple averaging for smoother reading
  const int N = 16;
  long sum = 0;
  for (int i = 0; i < N; i++) {
    sum += analogRead(A0);
    delay(5);
  }
  int adc = sum / N;

  float Vout = adcToVoltage(adc);
  // Guard against invalid values
  Vout = constrain(Vout, 0.0, Vcc);

  // Use calibrated exponential equation
  float lux = 4.0043 * exp(1.2885 * Vout);

  Serial.print("ADC: "); Serial.print(adc);
  Serial.print("  Vout: "); Serial.print(Vout, 3);
  Serial.print(" V  Lux: "); Serial.println(lux, 2);

  delay(1000);
}
