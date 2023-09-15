# STM32F103 I2C and EEPROM Driver

![Screenshot (102)](https://github.com/aliabooof/embedded_System_Online_Diploma/assets/62174374/99e114b3-f661-41f4-bf21-f551bbf75bb0)

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)

This repository contains an STM32F103 I2C (Inter-Integrated Circuit) and EEPROM driver implementation. The driver provides an interface for communicating with EEPROM (Electrically Erasable Programmable Read-Only Memory) devices over the I2C bus. It simplifies the configuration and usage of I2C communication for your STM32F103-based projects.

## Features

- Initialization and configuration of the I2C peripheral.
- Reading and writing data to EEPROM devices.
- Support for various EEPROM models and sizes.
- Easily configurable I2C bus speed and other settings.

## Hardware Requirements

To use this I2C and EEPROM driver, you'll need the following hardware components:

- STM32F103 microcontroller board (e.g., [STM32F103C8T6](https://www.st.com/en/microcontrollers-microprocessors/stm32f103.html)).
- EEPROM device compatible with the I2C protocol (e.g., 24CXX series).

## Software Requirements

Ensure you have the following software tools and libraries installed:

- [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) (or your preferred STM32 development environment).
- STM32 HAL library.
- Keil, IAR, or another IDE if you prefer a different development environment.
- Git (optional, for cloning the repository).


```c

uint8_t dataToWrite = 0xAA;
EEPROM_WriteByte(0x0010, dataToWrite); // Example: Write a byte to EEPROM address 0x0010
uint8_t dataRead = EEPROM_ReadByte(0x0010); // Example: Read a byte from EEPROM address 0x0010
```
Customize your application to handle EEPROM data as needed.


