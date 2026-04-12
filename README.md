# 🐍 RebelRescue

> Cable-actuated disaster rescue snake robot — built at hackathon

RebelRescue is a snake-shaped reconnaissance robot that slithers through rubble, tight gaps, and hazardous zones that are too dangerous for human entry. It detects smoke, flame, temperature, and humidity in real time, streams live video via a Logitech camera, and is controlled via WASD keys over Serial — all from a laptop.

---

## Demo

| What you see | What it means |
|---|---|
| Snake moves forward | W key sent over Serial |
| `*** GAS DETECTED ***` in Serial Monitor | MQ-2 threshold crossed |
| `*** FLAME DETECTED ***` in Serial Monitor | Flame sensor triggered |
| Live camera feed | Logitech camera plugged into operator laptop |

---

## Hardware

| Component | Role |
|---|---|
| Arduino Uno Q | Main brain — sensor reads, Serial comms, logic |
| ESP32 | Servo motor controller — cable actuation |
| SG90 Servo × 2 | Drive snake joint motion |
| MQ-2 Gas Sensor | Smoke / gas detection |
| Flame Sensor | Flame detection |
| DHT22 / HTU21D | Temperature & humidity at robot tip |
| Logitech Camera | Live first-person video feed |
| 3D Printed Body | Modular PLA snake segments |

---

## Wiring (Arduino Uno Q)

| Pin | Connected to |
|---|---|
| Pin 9 | Servo 1 signal |
| Pin 10 | Servo 2 signal |
| Pin 7 | Ultrasonic TRIG |
| Pin 8 | Ultrasonic ECHO |
| Pin 4 | Flame sensor DO |
| Pin 2 | Mic / sound DO |
| A0 | Gas sensor AO |
| A1 | Flame sensor AO |
| 5V | Sensor VCC |
| GND | Common ground |

> ⚠️ Power servos from an **external 5V supply** — not from the board's 5V pin. Connect all GNDs together.

---

## Software Setup

### Requirements

- [Arduino IDE 2.x](https://www.arduino.cc/en/software)
- Arduino Uno Q board package (install via Boards Manager)
- [ADB (Android Debug Bridge)](https://developer.android.com/tools/releases/platform-tools) — required to flash the Uno Q

### Libraries

Install via `Sketch → Include Library → Manage Libraries`:

```
Servo         (built-in)
NewPing       by Tim Eckel
ArduinoJson   by Benoit Blanchon
```

### Flashing

The Arduino Uno Q flashes over **ADB, not USB-Serial**.

1. Install ADB and add it to your system PATH
2. Connect Uno Q via USB-C
3. Run `adb devices` — confirm your board is listed
4. Select `Arduino UNO Q` as board and the ADB device as port in Arduino IDE
5. Upload normally

---

## Controls

Send single characters over Serial Monitor (9600 baud):

| Key | Action |
|---|---|
| `W` | Forward |
| `S` | Backward |
| `A` | Turn left |
| `D` | Turn right |
| `X` | Stop |

---

## Sensor Outputs

Serial Monitor prints live readings every 500ms:

```
Gas level: 312 / 1023  |  Status: Safe
Flame: 0  |  Status: No flame
Distance: 24.3 cm
```

When thresholds are crossed:

```
Gas level: 647 / 1023  |  Status: *** GAS DETECTED ***
Flame: 1  |  Status: *** FLAME DETECTED ***
```

> ⚠️ MQ-2 gas sensor needs **30–60 seconds warmup** after power-on before readings are reliable. Plan for this in your demo startup.

---

## Project Structure

```
rebelrescue/
├── firmware/
│   ├── uno_q_main/
│   │   └── uno_q_main.ino      # Main sketch — sensors + Serial control
│   └── esp32_servos/
│       └── esp32_servos.ino    # ESP32 sketch — servo gait control
├── hardware/
│   └── pinout.md               # Full pin mapping reference
├── models/
│   └── snake_segment.stl       # 3D printable body segment
└── README.md
```

---

## Architecture

```
Operator Laptop
    │
    ├── Serial (USB-C) ──────► Arduino Uno Q
    │                               │
    │                               ├── MQ-2 Gas Sensor  (A0)
    │                               ├── Flame Sensor     (Pin 4)
    │                               ├── DHT22 Temp/Hum   (Pin 5)
    │                               └── Serial TX ──────► ESP32
    │                                                       │
    │                                                  Servo 1 (Pin 9)
    │                                                  Servo 2 (Pin 10)
    │
    └── USB ─────────────────► Logitech Camera (live video)
```

---

## Team

Built at the **MakeNJIT 2026 Hardware Hackathon**

---

## What's Next

- Browser-based dashboard with live sensor gauges
- Ultrasonic obstacle avoidance (semi-autonomous mode)
- More body segments for deeper reach
- Two-way audio (mic + speaker)
- Waterproofing for flood scenarios
- Hazard heatmap from fused sensor + movement data

---

## License

MIT
