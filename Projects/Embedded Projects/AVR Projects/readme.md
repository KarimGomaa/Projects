# Embedded Systems Projects

This repository contains several embedded systems projects developed using the ATmega32 microcontroller. Each project involves different sensors, drivers, and output displays to accomplish specific tasks such as measuring soil moisture, controlling fan speed, measuring distance, and implementing a stopwatch.

## Table of Contents

- [Project 1: Distance Measuring System](#project-2-distance-measuring-system)
  - [Overview](#overview-1)
  - [Features](#features-1)
  - [System Architecture](#system-architecture-1)
  - [Drivers](#drivers-1)
  - [Hardware](#hardware-1)
  - [Implementation Details](#implementation-details-1)
  - [How to Use](#how-to-use-1)

- [Project 2: Soil Moisture System](#project-1-soil-moisture-system)
  - [Overview](#overview)
  - [Features](#features)
  - [System Architecture](#system-architecture)
  - [Drivers](#drivers)
  - [Hardware](#hardware)
  - [Implementation Details](#implementation-details)
  - [How to Use](#how-to-use)

- [Project 3: Fan Speed Controller with Temperature](#project-3-fan-speed-controller-with-temperature)
  - [Overview](#overview-2)
  - [Features](#features-2)
  - [System Architecture](#system-architecture-2)
  - [Drivers](#drivers-2)
  - [Hardware](#hardware-2)
  - [Implementation Details](#implementation-details-2)
  - [How to Use](#how-to-use-2)

- [Project 4: Stopwatch](#project-4-stopwatch)
  - [Overview](#overview-3)
  - [Features](#features-3)
  - [System Architecture](#system-architecture-3)
  - [Drivers](#drivers-3)
  - [Hardware](#hardware-3)
  - [Implementation Details](#implementation-details-3)
  - [How to Use](#how-to-use-3)

## Project 1: Distance Measuring System

### Overview

The Distance Measuring System measures the distance of an object using an ultrasonic sensor and displays the result on an LCD.

### Features

- **Distance Measurement:** Accurate measurement of distance using an ultrasonic sensor.
- **User Interface:** LCD display for showing the distance.

### System Architecture

- **Ultrasonic Sensor:** Measures the distance to an object by sending out sound waves and timing the echo.
- **LCD Display:** Shows the distance in centimeters or inches.
- **Microcontroller:** ATmega32 processes the sensor data and controls the display.

### Drivers

- **GPIO (General Purpose Input/Output)**
- **ICU (Input Capture Unit)**
- **Ultrasonic Sensor Driver**
- **LCD Driver**

### Hardware

- **ATmega32 Microcontroller**
- **Ultrasonic Sensor**
- **16x2 LCD Display**
- **Power Supply**

### Implementation Details

The system uses the ICU to time the echo received by the ultrasonic sensor, calculates the distance, and displays it on the LCD.

### How to Use

1. Clone the repository.
2. Connect the hardware components as per the schematic.
3. Compile and upload the code to the ATmega32 microcontroller.
4. Measure distances and view them on the LCD.

## Project 2: Soil Moisture System

### Overview

The Soil Moisture System is designed to measure the moisture level in the soil and display the reading on an LCD. The project was developed collaboratively by a group of seven members.

### Features

- **Moisture Measurement:** Real-time measurement of soil moisture using a sensor.
- **User Interface:** LCD display for showing the moisture level.
- **Collaboration:** Developed as part of a team effort.

### System Architecture

- **Soil Moisture Sensor:** Detects the moisture content in the soil.
- **LCD Display:** Shows the moisture level to the user.
- **Microcontroller:** ATmega32 is used to process the sensor data and control the display.

### Drivers

- **GPIO (General Purpose Input/Output)**
- **ICU (Input Capture Unit)**
- **Soil Moisture Sensor Driver**
- **LCD Driver**

### Hardware

- **ATmega32 Microcontroller**
- **Soil Moisture Sensor**
- **16x2 LCD Display**
- **Power Supply**

### Implementation Details

The system reads the analog signal from the soil moisture sensor, processes it, and displays the moisture level on the LCD. The ICU is used to capture sensor data accurately.

### How to Use

1. Clone the repository.
2. Connect the hardware components as per the schematic.
3. Compile and upload the code to the ATmega32 microcontroller.
4. Monitor the soil moisture on the LCD.



## Project 3: Fan Speed Controller with Temperature

### Overview

The Fan Speed Controller adjusts the speed of a fan based on the temperature measured by an LM35 sensor.

### Features

- **Temperature-Based Control:** Fan speed varies according to the temperature.
- **User Interface:** LCD display for showing the temperature and fan speed.

### System Architecture

- **LM35 Temperature Sensor:** Measures the ambient temperature.
- **DC Motor:** Represents the fan whose speed is controlled.
- **LCD Display:** Shows temperature and fan speed.
- **Microcontroller:** ATmega32 processes the temperature data and controls the motor speed using PWM.

### Drivers

- **GPIO (General Purpose Input/Output)**
- **ADC (Analog-to-Digital Converter)**
- **PWM (Pulse Width Modulation)**
- **LM35 Sensor Driver**
- **LCD Driver**
- **DC-Motor Driver**

### Hardware

- **ATmega32 Microcontroller**
- **LM35 Temperature Sensor**
- **DC Motor**
- **16x2 LCD Display**
- **Power Supply**

### Implementation Details

The system reads the temperature from the LM35 sensor using ADC, adjusts the PWM signal to control the fan speed, and displays the data on the LCD.

### How to Use

1. Clone the repository.
2. Connect the hardware components as per the schematic.
3. Compile and upload the code to the ATmega32 microcontroller.
4. Observe the fan speed adjusting based on the temperature.

## Project 4: Stopwatch

### Overview

The Stopwatch system measures and displays elapsed time on 7-segment displays.

### Features

- **Time Measurement:** Stopwatch functionality with start, stop, and reset features.
- **Display:** Elapsed time shown on 7-segment displays.

### System Architecture

- **7-Segment Display:** Displays the elapsed time.
- **External Interrupts:** Used to start, stop, and reset the stopwatch.
- **Microcontroller:** ATmega32 handles time counting and display control.

### Drivers

- **GPIO (General Purpose Input/Output)**
- **Timer Driver**
- **External Interrupts Driver**
- **7-Segment Display Driver**

### Hardware

- **ATmega32 Microcontroller**
- **7-Segment Displays**
- **Push Buttons for Start/Stop/Reset**
- **Power Supply**

### Implementation Details

The system uses a timer to measure time intervals and updates the 7-segment display. External interrupts handle the start, stop, and reset functions.

### How to Use

1. Clone the repository.
2. Connect the hardware components as per the schematic.
3. Compile and upload the code to the ATmega32 microcontroller.
4. Control the stopwatch using the push buttons and view the time on the 7-segment displays.
