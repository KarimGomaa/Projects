# RTOS Project 🚀

Welcome to the RTOS Project! This project demonstrates the implementation of a Real-Time Operating System (RTOS) using FreeRTOS. It involves creating tasks, semaphores, and timers to manage communication between sender and receiver tasks.

## Table of Contents 📚

- [📝 Overview](#overview)
- [✨ Features](#features)
- [🚀 Getting Started](#getting-started)
- [📂 Code Structure](#code-structure)
- [🔧 Functions](#functions)
- [🛠 Tasks](#tasks)
- [⏲️ Callback Functions](#callback-functions)
- [🚀 Main Function](#main-function)
- [🧠 Memory Management](#memory-management)
- [🙏 Acknowledgements](#acknowledgements)

## 📝 Overview

This RTOS project demonstrates task management and inter-task communication using semaphores and queues. The main components include sender tasks that generate messages at random intervals and a receiver task that processes these messages.

## ✨ Features

- **Task Management:** Sender and receiver tasks with different priorities.
- **Semaphore Usage:** Synchronization between tasks.
- **Timer Management:** Dynamic timer periods for sender tasks.
- **Queue Communication:** Task-to-task message passing.
- **Statistics Reporting:** Periodic reporting of task performance and statistics.

## 🚀 Getting Started

To get started with this project, clone the repository and follow the setup instructions. Ensure you have FreeRTOS installed and properly configured.

```bash
git clone https://github.com/KarimGomaa/Projects
cd <project-directory>
# Follow the specific build instructions for your environment
```
## 📂 Code Structure

- `main.c`: Contains the main function and initialization code.
- `tasks.c`: Defines the tasks (Sender1, Sender2, Sender3, and Receiver).
- `timers.c`: Manages timer callbacks.
- `semaphores.c`: Handles semaphore operations.
- `queues.c`: Contains queue-related operations and initializations.

## 🔧 Functions

### `TicksRandomValue()`

Generates a random value in ticks within a specified range.

### `mainReset()`

Initializes the global counters and queue, and resets the array index.

### `Reset()`

Resets the counters and queue, prints statistics, and manages timer destruction.

## 🛠 Tasks️

### `Sender1Task(void *pvParameters)`

A sender task that generates messages and sends them to the queue.

### `Sender2Task(void *pvParameters)`

Another sender task similar to `Sender1Task` but with its own semaphore.

### `Sender3Task(void *pvParameters)`

Third sender task with its own semaphore and message handling.

### `ReceiverTask(void *pvParameters)`

Receives messages from the queue and updates the counters.

## ⏲️ Callback Functions

### `sender1TimerCallback(TimerHandle_t xTimer)`

Updates the timer period and releases the semaphore for `Sender1Task`.

### `sender2TimerCallback(TimerHandle_t xTimer)`

Updates the timer period and releases the semaphore for `Sender2Task`.

### `sender3TimerCallback(TimerHandle_t xTimer)`

Updates the timer period and releases the semaphore for `Sender3Task`.

### `receiverTimerCallback(TimerHandle_t xTimer)`

Releases the semaphore for `ReceiverTask` and triggers a reset if the maximum number of received messages is reached.

## 🚀 Main Function

The `main()` function initializes the system, creates tasks, semaphores, and timers, and starts the RTOS scheduler.

```c
int main(void)
{
    // Initialization code here...
}
```

## 🧠 Memory Management

### `vApplicationMallocFailedHook()`
Handles memory allocation failures in FreeRTOS.

### `vApplicationStackOverflowHook()`
Handles stack overflow detection.

### `vApplicationIdleHook()`
Reports free stack space during idle task execution.

### `vApplicationGetIdleTaskMemory()`
Provides memory for the Idle task.

### `vApplicationGetTimerTaskMemory()`

Provides memory for the Timer task.


## 🙏 Acknowledgements

- **FreeRTOS:** For providing the real-time operating system kernel.
- **Community Contributions:** Special thanks to contributors and the FreeRTOS community for valuable resources and support.
- **Documentation:** References from FreeRTOS documentation and related materials.

##

Thank you for checking out the RTOS Project! If you have any questions or need further assistance, feel free to open an issue or contact the project maintainer. Happy coding! 🎉
