# Digital Design Projects

This repository contains digital design projects focused on FPGA-based implementations. The projects include the design of a DSP slice for Spartan-6 FPGAs and an SPI Slave module connected to a Single Port RAM.

## Table of Contents

- [Project 1: DSP48A1 Design](#project-1-dsp48a1-design)
  - [Overview](#overview)
  - [Architecture](#architecture)
  - [Features](#features)
  - [Implementation](#implementation)

- [Project 2: SPI Slave with Single Port RAM](#project-2-spi-slave-with-single-port-ram)
  - [Overview](#overview-1)
  - [Architecture](#architecture-1)
  - [Features](#features-1)
  - [Implementation](#implementation-1)

## Project 1: DSP48A1 Design

### Overview

The first project involves the design of a DSP48A1 slice, a key component used in Spartan-6 FPGAs. The DSP48A1 is a versatile digital signal processing slice used for arithmetic operations, including multiplication, addition, and accumulation.

### Architecture

The DSP48A1 slice is designed to perform the following operations:

- **Multiplication:** Multiplies two 18-bit input operands.
- **Addition:** Adds the product of the multiplication to an accumulator.
- **Shifting:** Supports bitwise shifting operations.
- **Pipelining:** Includes optional pipeline stages for higher clock frequencies.

### Features

- Fully parameterizable design to support different operand widths.
- Support for various arithmetic operations with selectable modes.
- Pipelined architecture for high-speed operation.
- Compatible with Spartan-6 FPGA resources.

### Implementation

To implement the DSP48A1 slice:

1. Clone the repository.
2. Navigate to the `dsp48a1_design` directory.
3. Use an FPGA design tool (e.g., Xilinx ISE or Vivado) to synthesize and simulate the design.

    ```sh
    # Example command for synthesis
    ise dsp48a1.xise
    ```

## Project 2: SPI Slave with Single Port RAM

### Overview

The second project focuses on designing an SPI Slave module that interfaces with a Single Port RAM. The SPI Slave allows for communication with an external master device, enabling data storage and retrieval from the RAM.

### Architecture

The architecture of the SPI Slave with Single Port RAM includes the following components:

- **SPI Interface:** Handles the SPI communication protocol, including data reception and transmission.
- **RAM Controller:** Manages the read and write operations to the Single Port RAM.
- **Control Logic:** Coordinates between the SPI interface and the RAM, ensuring correct data flow and timing.

### Features

- Supports standard SPI modes (0, 1, 2, 3).
- Configurable RAM size and address width.
- Efficient data transfer between SPI and RAM.
- Minimal resource usage, optimized for FPGA implementation.

### Implementation

To implement the SPI Slave with Single Port RAM:

1. Clone the repository.
2. Navigate to the `spi_slave_ram_design` directory.
3. Use an FPGA design tool (e.g., Xilinx ISE or Vivado) to synthesize and simulate the design.

    ```sh
    # Example command for synthesis
    ise spi_slave_ram.xise
    ```
