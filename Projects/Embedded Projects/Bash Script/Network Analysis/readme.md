# 🖥️ Network Traffic Analysis Bash Script

This project automates network traffic analysis using a Bash script. The script analyzes `.pcap` files captured by **Wireshark** or **tcpdump** and generates a summary report with relevant statistics like total packets, protocols, and top IP addresses.

## 📑 Table of Contents

- [📜 Prerequisites](#-prerequisites)
- [🛠️ How to Create a `.pcap` File](#️-how-to-create-a-pcap-file)
- [📝 How to Run the Bash Script](#-how-to-run-the-bash-script)
- [📊 Sample Output](#-sample-output)


## 📜 Prerequisites

Before running the script, ensure you have the following:

- Wireshark or tcpdump installed.
    
   - **Install Wireshark** On Ubuntu/Debian:
     ```bash
     sudo apt install wireshark
     ```

   - **Install tcpdump** On Ubuntu/Debian:
     ```bash
     sudo apt install tcpdump
     ```    
- tshark is installed.
    
     - **Install tshark** On Ubuntu/Debian:
        ```bash
        sudo apt install tshark
        ``` 

- Sudo privileges to capture network traffic.
    - Make sure you have the right permissions to capture network traffic (e.g., run Wireshark/tcpdump with     `sudo`).


## 🛠️ How to Create a `.pcap` File

You can capture network traffic using either **Wireshark** or **tcpdump**. Below are the instructions for both methods:

### 🦈 Wireshark Method

1. **Capture Traffic**:
   - Open Wireshark.
   - Select the appropriate network interface (e.g., `eth0`, `wlan0`).
   - Click the **Start Capturing Packets** button.

2. **Stop the Capture**:
   - Once you've captured enough data, click the **Stop Capture** button (red square).

3. **Save the Capture**:
   - Go to **File > Save As**, and save the file as `network_traffic.pcap`.

##

### 🧰 tcpdump Method

1. **Capture Traffic**:
   Run the following command to capture network traffic on a specific interface:
   ```bash
   sudo tcpdump -i <interface> -w network_traffic.pcap

Replace `<interface>` with the appropriate network interface, e.g., `eth0` for Ethernet or `wlan0` for Wi-Fi.

3. Stop the Capture: Press `Ctrl + C` to stop capturing once you have enough data.


## 📝 How to Run the Bash Script
1. Make the script executable:
```bash
chmod +x analyze_traffic.sh
```
2. Run the script: Provide the `.pcap` file path as an argument:
```bash
./analyze_traffic.sh network_traffic.pcap
```

## 📊 Sample Output
```bash
----- Network Traffic Analysis Report -----
1. Total Packets: 1000
2. Protocols:
  - HTTP: 600 packets
  - HTTPS/TLS: 400 packets

3. Top 5 Source IP Addresses:
  - 192.168.1.1: 300 packets
  - 192.168.1.2: 200 packets

4. Top 5 Destination IP Addresses:
  - 10.0.0.1: 400 packets
  - 10.0.0.2: 300 packets

----- End of Report -----
```

##

Thank you for using our Network analysis application! If you have any questions or suggestions, please feel free to contribute or contact us.

Happy Coding!
