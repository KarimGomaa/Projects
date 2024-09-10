# 🖥️ Process Monitor Script

## 📑 Table of Contents

- [📝 Description](#-description)
- [🚀 Usage](#-usage)
- [🔍 Script Overview](#-script-overview)
- [🧪 Example](#-example)
- [🛠️ Configuration](#-configuration)
- [⚙️ Functions](#-functions)
- [🎥 Testing Video](#-testing-video)
- [🎉 Conclusion](#-conclusion)

## 📝 Description

`process_monitor.sh` is a versatile Bash script designed for monitoring and managing system processes. It provides functionalities for listing processes, checking system statistics, real-time monitoring, and more. Users can interact with the script to view process information, kill processes, and receive alerts for high resource usage.

## 🚀 Usage

To use this script, follow these steps:

1. Open your terminal.
2. Navigate to the directory containing `process_monitor.sh`.
3. Make sure the script has executable permissions:
    ```bash
    chmod +x process_monitor.sh
    ```
4. Run the script:
    ```bash
    ./process_monitor.sh
    ```

## 🔍 Script Overview

The script performs several key tasks:

- **List Processes**: Displays all running processes with CPU and memory usage.
- **Process Information**: Provides detailed information about a specific process.
- **Kill a Process**: Terminates a process based on its PID.
- **System Stats**: Shows system statistics including total processes, memory usage, and CPU load.
- **Real-time Monitoring**: Continuously lists processes and updates at a specified interval. Press 'q' to quit.
- **Search and Filter Processes**: Allows searching for processes by name or user.
- **Check Resource Usage Alerts**: Monitors processes for high CPU and memory usage based on predefined thresholds.

## 🧪 Example

To start the script and use its features, simply run:

```bash
./process_monitor.sh
```

You will be presented with a menu to choose various options for process monitoring and management.

## 🛠️ Configuration
The script sources configuration settings from process_monitor.conf. If the file is not found, default values are used:

- `UPDATE_INTERVAL`: Interval for real-time monitoring (default: 5 seconds)
- `CPU_ALERT_THRESHOLD`: CPU usage alert threshold (default: 90%)
- `MEMORY_ALERT_THRESHOLD`: Memory usage alert threshold (default: 80%)


## ⚙️ Functions
The script includes the following functions:

- `list_processes()`: Lists all running processes.
- `process_info()`: Provides detailed information about a specified PID.
- `kill_process()`: Terminates a process based on its PID.
- `system_stats()`: Displays system-wide process statistics.
- `real_time_monitor()`: Continuously monitors processes in real-time.
- `search_processes()`: Searches for processes matching specified criteria.
- `check_alerts()`: Checks for processes exceeding CPU and memory usage thresholds.

## 📹 Testing Video

You can view the testing video [here](https://drive.google.com/file/d/1K7l0YvltT9PKJz9T9iHi4V2dK5Yrs6Qh/view?usp=sharing).


## 🎉 Conclusion
process_monitor.sh is a powerful tool for managing and monitoring system processes. It offers an interactive mode for ease of use and real-time monitoring capabilities to keep track of system performance. For any suggestions or improvements, feel free to contribute!
