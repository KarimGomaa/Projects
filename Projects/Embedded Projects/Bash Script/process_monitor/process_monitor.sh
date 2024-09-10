#!/usr/bin/bash

##################################################################################################### 
# 
# Auther: Karim Gomaa
#
# File Nmae: process_monitor.sh
#
# Description: Bash Script to List Processes information , System Stats , Check Resource Usage Alerts,
#              Search and Filter Processes , Real-time Monitoring.
#              and use varies options like (Process information, Kill) in an interactive mode
#
#####################################################################################################


######################################## Sourcing Files #############################################

# Source configuration file
CONFIG_FILE="process_monitor.conf"
if [[ -f $CONFIG_FILE ]]; then
    source $CONFIG_FILE
else
    echo "Configuration file not found! Using default values."
    UPDATE_INTERVAL=5
    CPU_ALERT_THRESHOLD=90
    MEMORY_ALERT_THRESHOLD=80
fi

#####################################################################################################


############################################ Functions ##############################################

# Function to list running processes
list_processes() {
    echo "Listing all running processes:"
    # List processes and filter out those with 0.0 CPU usage using awk
    ps -eo pid,comm,%cpu,%mem --sort=-%cpu | awk '$3 > 0.0'
}

# Function to get detailed process information
process_info() {
    read -p "Enter Process ID (PID): " pid
    ps -p $pid -o pid,ppid,user,%cpu,%mem,etime,comm
}

# Function to kill a process
kill_process() {
    read -p "Enter Process ID (PID) to kill: " pid

    # Check if the PID exists and get the process name, remove header with "comm="
    process_name=$(ps -p $pid -o comm=)
    
    if [ -z "$process_name" ]; then
        echo "Error: Process with PID $pid not found."
        return 1  # Exit the function if PID is invalid
    fi

    # Kill the process
    if kill -9 $pid; then
        echo "Process $pid ($process_name) terminated."
    else
        echo "Failed to kill process $pid."
        return 1  # Exit with error if killing fails
    fi

    # to log process termination activities with username, process name, and pid
    log_file="process_monitor.log"

    # Log the username, process name, and PID
    echo "User $(whoami) terminated process: $process_name (pid: $pid)" >> $log_file
}


# Function to display system process statistics
system_stats() {
    echo "System Process Statistics:"
    echo "Total Processes: $(ps aux | wc -l)"
    echo "Memory Usage:"
    free -h
    echo "CPU Load:"
    uptime
}

# Function for real-time monitoring with 'q' to exit
real_time_monitor() {
    while true; do
        clear
        list_processes
        
        # Wait for user input with a timeout
        echo "Press 'q' to quit."

        # -t $UPDATE_INTERVAL to wait for the UPDATE_INTERVAL in the configuration file then continue
        # -n to read only one char
        read -t $UPDATE_INTERVAL -n 1 input
        
        # If the user presses 'q', break the loop and exit
        if [[ $input == "q" ]]; then
            echo "Exiting real-time monitoring..."
            break
        fi
    done
}

# Function to search and filter processes
search_processes() {
    read -p "Enter search criteria (name/user): " search
    ps -eo pid,comm,user,%cpu,%mem --sort=-%cpu | grep -i $search
}

check_alerts() {
    # ps command lists all processes with their PID, command name, CPU usage, and memory usage, sorted by CPU usage.
    # awk is used to compare each process's CPU and memory usage against the defined thresholds.
    ps -eo pid,comm,%cpu,%mem --sort=-%cpu | awk -v cpu_thresh=$CPU_ALERT_THRESHOLD -v mem_thresh=$MEMORY_ALERT_THRESHOLD '
    {
        # $3 refers to the %CPU usage (third column in the ps output).
        # If the %CPU of a process exceeds the predefined CPU_ALERT_THRESHOLD, trigger a CPU usage alert.
        if ($3 > cpu_thresh) {
            # Prints an alert message indicating that the process is using too much CPU.
            # $2 refers to the command name, $1 refers to the PID, and $3 refers to the %CPU usage.
            print "ALERT: Process " $2 " (PID: " $1 ") is using too much CPU: " $3 "%."
        }

        # $4 refers to the %Memory usage (fourth column in the ps output).
        # If the %Memory usage of a process exceeds the predefined MEMORY_ALERT_THRESHOLD, trigger a memory usage alert.
        if ($4 > mem_thresh) {
            # Prints an alert message indicating that the process is using too much memory.
            # $2 refers to the command name, $1 refers to the PID, and $4 refers to the %Memory usage.
            print "ALERT: Process " $2 " (PID: " $1 ") is using too much memory: " $4 "%."
        }
    }'
}

#####################################################################################################


######################################### Main Functions ############################################

# main with Interactive mode
main() {
    while true; do
        echo "Process Monitor Menu:"
        echo "1. List Processes"
        echo "2. Process Information"
        echo "3. Kill a Process"
        echo "4. System Stats"
        echo "5. Real-time Monitoring"
        echo "6. Search and Filter Processes"
        echo "7. Check Resource Usage Alerts"
        echo "8. Exit"
        read -p "Choose an option: " option

        case $option in
            1) list_processes ;;
            2) process_info ;;
            3) kill_process ;;
            4) system_stats ;;
            5) real_time_monitor ;;
            6) search_processes ;;
            7) check_alerts ;;
            8) exit 0 ;;
            *) echo "Invalid option, please try again." ;;
        esac # End the case block

    done
}

#####################################################################################################


# Start main
main