## 📋 Table of Contents

-  [Overview](#-overview)
-  [Features](#-features)
-  [Hardware Requirements](#-hardware-requirements)
-  [Wiring Diagram](#-wiring-diagram)
-  [How It Works](#-how-it-works)
-  [Usage](#-usage)
- [Code Structure](#-code-structure)
- [Troubleshooting](#-troubleshooting)
- [Summary](#-summary)


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

| Component           | Quantity | Part Number | Description                          |
|---------------------|----------|-------------|--------------------------------------|
| Microcontroller     | 1        | ATmega328P  | 8-bit AVR MCU, 32KB Flash            |
| Temperature Sensor  | 1        | LM35        | Precision IC Temperature Sensor       |
| Shift Registers     | 2        | 74HC595     | 8-bit Serial-In/Parallel-Out         |
| 7-Segment Display   | 1        | 5641AS      | 4-Digit Common Cathode                |
| Resistors           | 8        | 220Ω 1/4W   | Current limiting for segments         |
| Breadboard          | 1        | -           | Solderless prototyping board          |
| Jumper Wires        | ~20      | -           | Male-to-male dupont wires             |
| Power Supply        | 1        | 5V DC       | Regulated 5V power source             |

## wiring diagram
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
### How it works 

Here's the table in markdown format, ready to be copied and pasted:

| Step | Component   | Action               | Data/Value                 |
|------|-------------|----------------------|----------------------------|
| 1    | LM35        | Senses temperature   | 25°C → 0.25V               |
| 2    | ATmega ADC  | Converts analog to digital | 0.25V → ADC=51          |
| 3    | ATmega CPU  | Calculates temperature | 51 → 25°C                 |
| 4    | ATmega CPU  | Extracts digits       | 25 → d3=2, d4=5            |
| 5    | SPI         | Sends segment pattern | 0x5B (for '2')             |
| 6    | SPI         | Sends digit select    | 0x04 (Digit 3)             |
| 7    | 74HC595     | Latches data          | U3=Segments, U2=Digit      |
| 8    | Display     | Lights up segments    | Shows "2" on Digit 3       |
| 9    | Loop        | Repeats for all digits | Refreshes at 500Hz        |


## Usage
### 1.Hardware Setup

- Connect the LM35 temperature sensor:

- Pin 1 → 5V

- Pin 2 → A0 (ADC0)

- Pin 3 → GND

- Connect the two 74HC595 shift registers:

- DS → MOSI (D11)

- SH_CP → SCK (D13)

- ST_CP → Latch (D10 or configured pin)

- OE → GND

- MR → 5V

- Q7’ of first register → DS of second register

 Connect the 4-digit 7-segment display:

- Segment pins → First 74HC595 outputs

- Digit control pins → Second 74HC595 outputs

- Ensure correct configuration for Common Cathode

Make sure all components share a common ground.

### 2. Upload the Firmware

- Open the project in your AVR development environment.

- Select the correct microcontroller (ATmega328P).

- Compile the code.

- Upload the generated .hex file to the Arduino Uno.
  
### 3. Running the System

- Power the board via USB or external 5V supply.

- The display will automatically begin showing the ambient temperature in Celsius.

- The temperature updates continuously in real-time.

- Touching the LM35 sensor will increase the displayed temperature due to body heat.

  ### Expected Output

At room temperature (~25–35°C), the display should show:

```
0027
0032
0035
```
## Code Structure 
### 1. SPI Configuration

Responsible for initializing and handling communication with the two 74HC595 shift registers.
```c
void SPI_init(void);
void SPI_send(uint8_t data);
void send_16bit(uint8_t digit, uint8_t segment);
```
- Configures ATmega328P as SPI Master

- Sends segment and digit data serially

- Controls latch pin for parallel output update

 ### 2. ADC Configuration

Handles analog-to-digital conversion for the LM35 sensor.
```c
void ADC_init(void);
unsigned int ADC_read(void);
unsigned int read_temperature(void);
```
- Uses AVCC (5V) as reference

- Prescaler set to 128 for stable ADC clock

- Converts raw ADC value to temperature in Celsius

  Conversion formula:
```
  Temperature (°C) = (ADC_value × 500) / 1023
```
### Display Control

Manages digit extraction and multiplexing.
```c
void display_number(unsigned int number);
```
- Splits temperature into thousands, hundreds, tens, and units

- Sends segment patterns using lookup table

- Refreshes digits using multiplexing technique

### 4. Segment Lookup Table

Defines segment patterns for Common Cathode 7-segment display.
```c
unsigned char seg_code[10];
```
Maps digits 0–9 to corresponding segment byte values.

### 5. Main Application Loop
 ```c
 void main(void);
 ```
Workflow:

#### 1.Initialize SPI

#### 2.Initialize ADC

#### 3.Continuously:

   - Read temperature

   - Refresh display multiple times for stability

## Troubleshooting

- If the display shows 0500 → Check LM35 wiring (likely reversed).

- If it shows very low values ```(0002, 0003) →``` Check sensor power and ground.

- If display flickers → Verify multiplex timing and wiring of digit control lines.

- If nothing appears → Check SPI connections and latch pin.

## Summary
Summary

This project demonstrates the design and implementation of a real-time digital temperature monitoring system using an ATmega328P microcontroller and an LM35 temperature sensor.The measured analog temperature signal is converted using the internal ADC and displayed on a 4-digit 7-segment display driven through two 74HC595 shift registers via SPI communication.The system efficiently reduces microcontroller I/O usage by leveraging serial-to-parallel conversion and multiplexing techniques, making it both hardware-efficient and scalable.

Through this project, key embedded systems concepts were applied, including:

- Analog-to-Digital Conversion (ADC)

- SPI Communication Protocol

- Shift Register Cascading

- Multiplexed Display Control

- Embedded C Programming

- Real Hardware Debugging and Signal Validation

The final implementation was successfully tested on an Arduino Uno platform, producing stable and accurate real-time temperature readings.
