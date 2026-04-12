// ============================================================
//  Fire & Gas Detection System
//  Components: MQ Gas Sensor, KY-026 Flame Sensor, Buzzer
//  Board: Arduino Uno Q
//  IDE: Arduino IDE 2.3.8
//  Output: Tools → Serial Monitor (set to 115200 baud)
// ============================================================

#include <Arduino_RouterBridge.h>  // Required for Monitor output on Uno Q

// --- Pin Definitions ---
const int MQ_PIN      = A0;  // MQ sensor AO  → Arduino A0
const int FLAME_PIN   = A1;  // KY-026 AO     → Arduino A1
const int BUZZER_PIN  = 8;   // Buzzer + leg  → Arduino D8

// --- Thresholds (adjust after seeing your baseline readings) ---
const int MQ_THRESHOLD    = 1000;  // Gas alarm above this value
const int FLAME_THRESHOLD = 500;  // Flame alarm below this value

// --- Timing ---
const unsigned long PRINT_INTERVAL = 500;  // Print every 500ms
unsigned long lastPrint = 0;

void setup() {
  Monitor.begin();  // Start Monitor output (shows in IDE Serial Monitor)
  delay(2000);      // Wait for monitor to connect

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  Monitor.println("==============================================");
  Monitor.println("  Fire & Gas Detection System - Ready");
  Monitor.println("  Board: Arduino Uno Q");
  Monitor.println("==============================================");
  Monitor.println("  MQ Threshold   : " + String(MQ_THRESHOLD));
  Monitor.println("  Flame Threshold: " + String(FLAME_THRESHOLD));
  Monitor.println("----------------------------------------------");
  Monitor.println("MQ [value] (status) | Flame [value] (status) | Alarm");
  Monitor.println("----------------------------------------------");
}

void loop() {
  // --- Read sensors ---
  int mqValue    = analogRead(MQ_PIN);
  int flameValue = analogRead(FLAME_PIN);

  // --- Evaluate thresholds ---
  bool gasDetected   = (mqValue   >= MQ_THRESHOLD);
  bool flameDetected = (flameValue <= FLAME_THRESHOLD);
  bool alarmActive   = gasDetected || flameDetected;

  // --- Drive buzzer ---
  digitalWrite(BUZZER_PIN, alarmActive ? HIGH : LOW);

  // --- Print output every 500ms ---
  unsigned long now = millis();
  if (now - lastPrint >= PRINT_INTERVAL) {
    lastPrint = now;

    Monitor.print("MQ: ");
    Monitor.print(mqValue);
    Monitor.print(" (");
    Monitor.print(gasDetected ? "GAS DETECTED!" : "Clear");
    Monitor.print(")  |  ");

    Monitor.print("Flame: ");
    Monitor.print(flameValue);
    Monitor.print(" (");
    Monitor.print(flameDetected ? "FLAME DETECTED!" : "No flame");
    Monitor.print(")  |  ");

    Monitor.print("Alarm: ");
    Monitor.println(alarmActive ? "*** ON ***" : "off");
  }
}