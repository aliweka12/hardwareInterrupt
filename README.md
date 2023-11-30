# STM32F4xx GPIO and Clock Management

This project provides a C++ implementation for managing system clock configuration, LED operations, and external interrupts on STM32F4xx series microcontrollers. It showcases object-oriented principles in embedded programming by encapsulating functionalities in classes.

## Features

- **Clock Management**: Configures the system clock with appropriate PLL settings and power configurations.
- **LED Management**: Manages LED operations including initialization and state toggling.
- **Interrupt Management**: Sets up and handles external interrupts on a GPIO pin.

## Prerequisites

To use this project, you'll need:
- STM32F4xx HAL Libraries.
- An STM32F4xx series microcontroller.
- A compatible development environment, such as STM32CubeIDE.

## Project Structure

- `ClockManager`: A class responsible for configuring the system clock.
- `IndicatorLED`: A class for managing LED operations.
- `InterruptManager`: A class for configuring and handling external interrupts (EXTI).

## Usage

1. **Initialization**: The `main` function initializes the HAL library, system clock, LED, and external interrupt handler.
2. **Clock Configuration**: The `ClockManager` class configures the system clock.
3. **LED Control**: Use the `IndicatorLED` class to initialize and control the LED state.
4. **Interrupt Handling**: The `InterruptManager` class sets up and manages external interrupts.

