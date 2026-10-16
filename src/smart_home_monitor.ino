/*
 * Smart Home Gas/Water Monitor — educational reference firmware
 *
 * Assumed hardware: classic ESP32 DevKit, 5 V MQ-2 module with AO output,
 * normally-open float switch, LED, and an active buzzer driven by an NPN
 * transistor. This is generated example code, not verified against your build.
 *
 * SAFETY: This prototype is not a certified gas alarm. Never rely on it for
 * life safety or property protection. Use a certified gas detector. Do not
 * release flammable gas to test the sensor.
 */

#include <Arduino.h>

constexpr uint8_t PIN_GAS_ADC = 34;       // ADC1 input on classic ESP32.
constexpr uint8_t PIN_WATER_SWITCH = 27; // Switch closes to GND at alert level.
constexpr uint8_t PIN_ALARM_LED = 18;
constexpr uint8_t PIN_BUZZER_DRIVER = 19;

// PLACEHOLDER ONLY: tune using the exact sensor module and a controlled setup.
// This is a raw ADC value, not a calibrated gas concentration in ppm.
constexpr int GAS_THRESHOLD_RAW = 2200;
constexpr uint8_t GAS_SAMPLES = 24;
constexpr uint32_t REPORT_INTERVAL_MS = 1000;

uint32_t lastReportMs = 0;

int readGasAverage() {
  uint32_t total = 0;
  for (uint8_t i = 0; i < GAS_SAMPLES; ++i) {
    total += analogRead(PIN_GAS_ADC);
    delay(5);
  }
  return static_cast<int>(total / GAS_SAMPLES);
}

void setup() {
  Serial.begin(115200);

  pinMode(PIN_WATER_SWITCH, INPUT_PULLUP);
  pinMode(PIN_ALARM_LED, OUTPUT);
  pinMode(PIN_BUZZER_DRIVER, OUTPUT);

  digitalWrite(PIN_ALARM_LED, LOW);
  digitalWrite(PIN_BUZZER_DRIVER, LOW);

  analogReadResolution(12);
  analogSetPinAttenuation(PIN_GAS_ADC, ADC_11db);

  Serial.println("Smart Home Monitor reference firmware");
  Serial.println("MQ-2 output is qualitative raw ADC only; calibrate threshold.");
  Serial.println("Water switch should close to GND at the selected alert level.");
}

void loop() {
  const int gasRaw = readGasAverage();
  const bool gasAlarm = gasRaw >= GAS_THRESHOLD_RAW;
  const bool waterAlarm = digitalRead(PIN_WATER_SWITCH) == LOW;
  const bool alarm = gasAlarm || waterAlarm;

  digitalWrite(PIN_ALARM_LED, alarm ? HIGH : LOW);
  digitalWrite(PIN_BUZZER_DRIVER, alarm ? HIGH : LOW);

  if (millis() - lastReportMs >= REPORT_INTERVAL_MS) {
    lastReportMs = millis();
    Serial.printf(
      "MQ-2 raw=%d threshold=%d gas=%s water=%s alarm=%s\n",
      gasRaw,
      GAS_THRESHOLD_RAW,
      gasAlarm ? "ALERT" : "clear",
      waterAlarm ? "ALERT" : "clear",
      alarm ? "ON" : "off"
    );
  }
}
