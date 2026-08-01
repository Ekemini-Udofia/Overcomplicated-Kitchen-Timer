# Arduino Nano Kitchen Timer

A lightweight kitchen timer built on the Arduino framework for the ATmega168PA. Features custom timing via potentiometer, button controls, SSD1306 OLED UI, and watchdog recovery.

## Hardware Components
* Microcontroller: Arduino Nano (ATmega168PA)
* Display: SSD1306 128x64 I2C OLED
* Input: 1x Potentiometer (time setting), 2x Push Buttons (Start/Pause, Reset)
* Output: Piezo Buzzer
* Reliability: Internal Watchdog Timer (WDT) enabled for system crash recovery

## Dependencies
* Arduino Framework
* `U8g2` library (by Oliver Kraus)

## Default Pinout
* SSD1306 OLED: A4 (SDA), A5 (SCL)
* Potentiometer: A0
* Start/Pause Button: D2 (INT0)
* Reset Button: D3 (INT1)
* Buzzer: D8

## Setup
1. Clone the repository and open in PlatformIO or Arduino IDE.
2. Install the `U8g2` library.
3. Select board target `Arduino Nano` with processor `ATmega168` or `ATmega168P`.
4. Compile and flash to board.