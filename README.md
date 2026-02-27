## 📋 Table of Contents

-  [Overview](#-overview)
-  [Features](#-features)
-  [Hardware Requirements](#-hardware-requirements)
-  [Wiring Diagram](#-wiring-diagram)
-  [How It Works](#-how-it-works)
-  [Software Architecture](#-software-architecture)
-  [Installation](#-installation)
-  [Usage](#-usage)
- [Code Structure](#-code-structure)
- [Calibration](#-calibration)
- [Troubleshooting](#-troubleshooting)
- [Testing](#-testing)
- [Contributing](#-contributing)
- [License](#-license)
- [Acknowledgments](#-acknowledgments)


## Overview
This project implements a real-time digital thermometer using an ATmega328P microcontroller to read temperature data from an LM35 analog temperature sensor and display it on a 4-digit multiplexed 7-segment display. The system utilizes SPI communication protocol with 74HC595 shift registers to efficiently drive the display using only 3 GPIO pins, demonstrating resource-efficient embedded system design principles.

## Features
- Real-time Temperature Display - Updates every 100ms
- Wide Measurement Range - 0°C to 99°C
- High Accuracy - ±1°C precision using LM35 sensor
- Flicker-Free Display - 500Hz multiplexing refresh rate
- Low Pin Count - Only 3 GPIO pins for display control
 - Common Cathode Support - Compatible with standard 7-segment displays

 ### Technical Features
- SPI Communication - Hardware SPI for fast data transfer (125kHz)
- Daisy-Chained Shift Registers - Two 74HC595 ICs for 16-bit output
- 10-bit ADC - 1024-level resolution for temperature sensing
- Modular Code Structure - Separate SPI, ADC, and display modules
- Current Protection - 220Ω resistors on all segment lines
- AVCC Filtering - 100nF capacitor for stable ADC reference
### Advanced Features
- Software Calibration - Adjustable offset and scaling
- Debug Mode - Raw ADC value display option
- Configurable Update Rate - Adjustable refresh frequency
-Scalable Design - Easy to extend to more digits or displays

## Hardware Requirements

## Wiring Diagram
                              ┌─────────────────┐
                              │   ATmega328P    │
                              │                 │
         ┌─────────────┐      │  PB5 ──┐ 17     │
         │   LM35      │      │  PB3 ──┼─ 15     │
    5V ──┤ Pin 1 (VCC) │      │  PB2 ──┼─ 14     │
         │ Pin 2 (OUT) ├──────┤  PC0 ──┼─ 23     │
    GND ─┤ Pin 3 (GND) │      │        │         │
         └─────────────┘      │  AVCC ── 20     │
                              │  AREF ─┼─ 21     │
                              └────────┼─────────┘
                                       │
                    ┌──────────────────┼──────────────────┐
                    │                  │                  │
               ┌────▼────┐        ┌───▼────┐       ┌────▼────┐
               │  74HC595 │        │74HC595 │       │ 7-Segment│
               │   (U2)   │        │  (U3)  │       │ Display  │
               │  Digits  │        │Segments│       │          │
               │          │        │        │       │          │
    PB2 ───────┤ ST_CP 12 │        │ST_CP 12│       │A B C D E │
    PB5 ───────┤ SH_CP 11 │        │SH_CP 11│       │F G DP    │
    PB3 ───────┤ DS   14  │        │DS   14 │       │          │
               │          │ Q7' 9 ─┴───→ DS 14      │COM1 COM2 │
         Q0 15─┤          │        │        │       │COM3 COM4 │
         Q1  1─┤          │        │Q0   15─┼───────┤A         │
         Q2  7─┤          │        │Q1    1─┼───────┤B         │
         Q3  4─┤          │        │Q2    7─┼───────┤C         │
         Q4  5─┤          │        │Q3    4─┼───────┤D         │
         Q5  6─┤          │        │Q4    5─┼───────┤E         │
         Q6  9─┤          │        │Q5    6─┼───────┤F         │
         Q7 10─┤          │        │Q6    9─┼───────┤G         │
               │     8 GND│        │Q7   10─┼───────┤DP        │
               │    16 VCC│        │   8 GND│       │          │
               └──────────┘        └───┬────┘       └──────────┘
                    │                  │
                   GND                GND
