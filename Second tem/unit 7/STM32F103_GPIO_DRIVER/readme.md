# STM32F103x6 GPIO Driver

## Overview

The STM32F103x6 GPIO driver is a software module that provides an interface to control and configure General-Purpose Input/Output (GPIO) pins on the STM32F103x6 microcontroller series. This driver simplifies the interaction with GPIO pins, making it easier to use them in your embedded applications.

## Key Features

- **Initialization and Configuration**: The driver allows you to initialize and configure GPIO pins quickly. You can specify the port, pin number, pin mode, speed, and pull-up/pull-down settings.

- **Pin Modes**: It supports various pin modes, including input, output, alternate function (for peripherals like UART or SPI), and analog mode.

- **Pin Speed Control**: You can set the speed of the GPIO pin (Low, Medium, or High) as per your application's requirements.

- **Pull-Up and Pull-Down Resistors**: The driver provides options to enable or disable pull-up and pull-down resistors on GPIO pins.

- **Pin State Control**: You can easily set the state of an output pin as High or Low and read the current state of an input pin.

- **Interrupt Handling**: The driver offers interrupt handling capabilities for GPIO pins, allowing you to generate interrupts based on pin events (e.g., rising edge, falling edge).

- **Support for Multiple STM32F103x6 Variants**: The driver is designed to work with various microcontroller variants within the STM32F103x6 series.

## Getting Started

To use this GPIO driver, follow these basic steps:

1. Clone or download the driver repository to your development environment.

2. Include the `gpio_driver.h` header file in your project.

3. Initialize and configure the GPIO pins using the provided functions.

4. Build and flash your project to the STM32F103x6 microcontroller.

For detailed usage instructions and examples, refer to  the code comments in the `gpio_driver.c` and `gpio_driver.h` files.


## Author

The driver was authored by [Ali AboOuf](https://github.com/yourusername). If you have any questions or suggestions, you can contact the author at [your.email@example.com](mailto:your.email@example.com).

This GPIO driver simplifies GPIO handling in your STM32F103x6 projects, making it easier to interface with external components and peripherals.

Remember to replace [Your Name](https://github.com/yourusername) and [your.email@example.com](mailto:your.email@example.com) with your actual information.
