# Verification Projects

This repository contains verification projects focused on developing verification environments for hardware modules. The projects utilize SystemVerilog and UVM (Universal Verification Methodology) to verify the functionality and performance of a FIFO module and an SPI-Slave connected to a Dual-Port RAM.

## Table of Contents

- [Project 1: FIFO Verification](#project-1-fifo-verification)
  - [Overview](#overview)
  - [Testbench Architecture](#testbench-architecture)
  - [Features](#features)
  - [Simulation](#simulation)

- [Project 2: SPI-Slave with Dual-Port RAM Verification](#project-2-spi-slave-with-dual-port-ram-verification)
  - [Overview](#overview-1)
  - [UVM Environment](#uvm-environment)
  - [Features](#features-1)
  - [Simulation](#simulation-1)

## Project 1: FIFO Verification

### Overview

The first project focuses on verifying a FIFO (First-In-First-Out) module. The goal is to ensure the FIFO behaves correctly under various conditions, such as data overflow, underflow, and normal operation.

### Testbench Architecture

The testbench for the FIFO module is developed using SystemVerilog. It is class-based and consists of the following components:

- **Stimulus Generator:** Generates input data for the FIFO.
- **Monitor:** Observes the output of the FIFO and compares it with the expected results.
- **Scoreboard:** Tracks the correctness of the FIFO's output.
- **Checker:** Ensures that the FIFO's operations (push and pop) adhere to the expected timing and behavior.

### Features

- Verification of FIFO's functionality in different scenarios.
- Testing under conditions like overflow and underflow.
- Coverage analysis to ensure all possible states and transitions are tested.

### Simulation

To run the simulation, follow these steps:

1. Clone the repository.
2. Navigate to the `fifo_verification` directory.
3. Use a SystemVerilog-compatible simulator to run the testbench.

    ```sh
    # Example command
    vcs -sverilog -full64 fifo_tb.sv -o fifo_simv
    ./fifo_simv
    ```

## Project 2: SPI-Slave with Dual-Port RAM Verification

### Overview

The second project involves verifying an SPI-Slave module connected to a Dual-Port RAM. The verification environment is developed using the Universal Verification Methodology (UVM).

### UVM Environment

The UVM environment is designed to verify the SPI-Slave module's interaction with the Dual-Port RAM. The environment includes:

- **UVM Agent:** Handles the generation of SPI transactions and monitors the responses.
- **UVM Monitor:** Observes the behavior of the SPI-Slave and the Dual-Port RAM, collecting relevant data.
- **UVM Scoreboard:** Compares the observed results with the expected behavior.
- **UVM Driver:** Drives the SPI interface with various test sequences.

### Features

- Comprehensive verification of the SPI-Slave's behavior in various scenarios.
- Testing of data transfer between SPI-Slave and Dual-Port RAM.
- Functional coverage and assertion-based checks.
