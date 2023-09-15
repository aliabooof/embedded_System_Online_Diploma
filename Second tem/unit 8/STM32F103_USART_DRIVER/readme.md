# STM32F103 USART Driver

## The polling method :

![usart_polling](https://github.com/aliabooof/embedded_System_Online_Diploma/assets/62174374/810779a8-890d-401c-9f16-a754c7f5196b)

## The interrupt method :

![usart_intr](https://github.com/aliabooof/embedded_System_Online_Diploma/assets/62174374/f95a72d2-fda3-4a34-aef5-e5bda02da89e)

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Contributing](#contributing)


## Introduction

This repository contains an STM32F103 USART (Universal Synchronous/Asynchronous Receiver Transmitter) driver implementation. The USART driver provides an interface to communicate with USART peripherals on the STM32F103 microcontroller. This driver simplifies the configuration and usage of USART communication for your STM32F103-based projects.

## Features

- Initialization and configuration of USART peripherals.
- Transmitting and receiving data using USART communication.
- Support for both polling and interrupt-driven communication modes.
- Easily configurable baud rate, data frame format, and other settings.

## Hardware Requirements

To use this USART driver, you'll need the following hardware components:

- STM32F103 microcontroller board 
- USART-enabled peripheral devices (e.g., sensors, modules) for communication.

## Software Requirements

Ensure you have the following software tools and libraries installed:

- [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) (or your preferred STM32 development environment).
- STM32 HAL library.
- Keil, IAR, or another IDE if you prefer a different development environment.
- Git (optional, for cloning the repository).

## Getting Started

Follow these steps to get started with the USART driver:

1. Clone this repository to your local machine (if you haven't already):

2. Open your STM32 development environment and create a new project or integrate the driver into an existing one.

3. Configure the USART settings in your project (baud rate, data frame format, etc.) as needed.

4. Include the usart_driver.h header in your project and use the provided functions to initialize, transmit, and receive data over USART.

5. Build and flash your project to the STM32F103 board.

6. Connect the USART-enabled peripheral devices to the appropriate USART pins on your STM32 board.

5. Run your project and verify the USART communication.

## Usage
To use the USART driver, follow these steps:

Include the usart_driver.h header in your source file:

```c
void ALI_UART_IRQ_Callback(void){
	MCAL_USART_recive_data(USART1, &ch,disable);
	MCAL_USART_send_data(USART1, &ch, enable);
}

int main(void){

	//Initializing Peripherals
	clock_init();
	USART_config_t config;

	config.baud_rate = USART_BAUD_RATE_115200;
	config.hwFlCt = USART_HWFLCT_NONE;
	config.IRQ_enable = USART_IRQ_ENABLE_RXNEIE;
	config.p_IRQ_callback = ALI_UART_IRQ_Callback;
	config.parity = USART_PARITY_NONE;
	config.data_lenght = USART_DATA_LENGHT_8B;
	config.stop_bits = USART_STOP_BITS_1;
	config.USART_mode = USART_MODE_TX_RX;

	MCAL_USART_init(USART1, &config);
	MCAL_USART_set_pins(USART1);

	while(1){

		/*
		//polling
		MCAL_USART_recive_data(USART1, &ch, enable);
		MCAL_USART_send_data(USART1, &ch, enable);
		 */
	}
}
```
## Contributing
Contributions to this USART driver project are welcome! If you'd like to contribute, please follow these guidelines:

- Fork the repository.
- Create a new branch for your feature or bug fix.
- Make your changes and test them thoroughly.
- Create a pull request with a clear description of your changes.
