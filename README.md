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

## featurse
- Real-time Temperature Display - Updates every 100ms
- Wide Measurement Range - 0°C to 99°C
- High Accuracy - ±1°C precision using LM35 sensor
- Flicker-Free Display - 500Hz multiplexing refresh rate
- Low Pin Count - Only 3 GPIO pins for display control
 - Common Cathode Support - Compatible with standard 7-segment displays
