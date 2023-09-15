# STM32F103 SPI Driver

![spi](https://github.com/aliabooof/embedded_System_Online_Diploma/assets/62174374/3bc8ab5a-f020-409a-a069-c78f2bbf2a34)


## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Getting Started](#getting-started)
- [Usage](#usage)

## Introduction

This repository contains an STM32F103 SPI (Serial Peripheral Interface) driver implementation. The SPI driver provides an interface to communicate with SPI peripherals on the STM32F103 microcontroller. This driver simplifies the configuration and usage of SPI communication for your STM32F103-based projects.

## Features

- Initialization and configuration of SPI peripherals.
- Transmitting and receiving data using SPI communication.
- Support for various SPI modes (e.g., SPI Mode 0, Mode 1, Mode 2, Mode 3).
- Easily configurable baud rate, data frame format, and other settings.

## Hardware Requirements

To use this SPI driver, you'll need the following hardware components:

- STM32F103 microcontroller board 
- SPI-enabled peripheral devices (e.g., sensors, displays, memory) for communication.

## Software Requirements

Ensure you have the following software tools and libraries installed:

- [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) (or your preferred STM32 development environment).
- STM32 HAL library.
- Keil, IAR, or another IDE if you prefer a different development environment.
- Git (optional, for cloning the repository).


Connect the SPI-enabled peripheral devices to the appropriate SPI pins on your STM32 board.

Run your project and verify the SPI communication.

## Usage
check the main.c file under Src folder
