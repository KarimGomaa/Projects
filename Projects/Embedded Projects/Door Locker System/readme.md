# Door Locker Security System

This repository contains the implementation of a Door Locker Security System designed to unlock a door using a password. The system is built using the ATmega32 microcontroller and includes various peripheral drivers for handling inputs, outputs, and communication.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [System Architecture](#system-architecture)
- [Drivers](#drivers)
- [Hardware](#hardware)
- [Implementation Details](#implementation-details)
- [How to Use](#how-to-use)
- [License](#license)
- [Contact](#contact)

## Overview

The Door Locker Security System is a microcontroller-based application that allows a user to unlock a door by entering a correct password. The system ensures secure access control by verifying the entered password against a stored one in EEPROM and provides feedback through an LCD display and a buzzer.

## Features

- **Password Protection:** The door can only be unlocked by entering the correct password.
- **User Interface:** Keypad for password input and LCD for displaying system messages.
- **Security Alert:** Buzzer activates if the wrong password is entered multiple times.
- **Persistent Storage:** EEPROM is used to store the password, ensuring it remains even after power loss.
- **Motor Control:** DC-Motor is used to physically unlock the door when the correct password is entered.

## System Architecture

The system is built around the ATmega32 microcontroller and includes the following components:

- **Keypad:** For user input (password entry).
- **LCD Display:** For displaying prompts, errors, and status messages.
- **DC Motor:** Controls the locking mechanism of the door.
- **Buzzer:** Alerts the user in case of incorrect password entries.
- **EEPROM:** Stores the password securely.
- **Communication Interfaces:** UART and I2C for serial communication.

## Drivers

The project includes the following drivers:

- **GPIO (General Purpose Input/Output):** Manages the I/O pins of the microcontroller.
- **Keypad Driver:** Interfaces with the keypad for capturing user input.
- **LCD Driver:** Controls the LCD for displaying messages.
- **Timer Driver:** Provides timing functionalities for various system operations.
- **UART Driver:** Handles serial communication.
- **I2C Driver:** Manages communication with the EEPROM.
- **EEPROM Driver:** For reading and writing the password in non-volatile memory.
- **Buzzer Driver:** Controls the buzzer for sound alerts.
- **DC-Motor Driver:** Operates the motor to unlock the door.

## Hardware

The system is implemented using the ATmega32 microcontroller, interfacing with various peripherals as described above. The hardware setup includes:

- **ATmega32 Microcontroller**
- **4x4 Keypad**
- **16x2 LCD Display**
- **DC Motor**
- **Buzzer**
- **External EEPROM (via I2C)**
- **Power Supply**
- **Connecting Wires and Breadboard or PCB**

## Implementation Details

### Password Management

- The system prompts the user to enter a password using the keypad.
- The entered password is compared with the stored password in EEPROM.
- If the password matches, the DC motor unlocks the door, and a confirmation message is displayed on the LCD.
- If the password is incorrect, the system gives the user multiple attempts before activating the buzzer for a security alert.

### Motor Control

- The DC motor is controlled by the microcontroller to physically unlock or lock the door.
- The motor operates for a specific duration controlled by a timer to ensure the door is properly unlocked.

### Communication

- **UART** is used for potential debugging or communication with other systems.
- **I2C** is utilized to interface with the EEPROM for storing and retrieving the password.

## How to Use

1. Clone the repository to your local environment.
2. Connect the hardware components according to the circuit diagram provided.
3. Configure the microcontroller and peripherals using the provided drivers.
4. Compile and upload the firmware to the ATmega32 microcontroller.
5. Use the keypad to enter the password and unlock the door.

    ```sh
    # Example command for compiling
    avr-gcc -mmcu=atmega32 -o door_locker.elf door_locker.c
    avrdude -c usbasp -p m32 -U flash:w:door_locker.elf
    ```

