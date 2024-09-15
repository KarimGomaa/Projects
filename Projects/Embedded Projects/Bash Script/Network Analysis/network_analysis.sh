#!/bin/bash

##################################################################################################### 
# 
# Auther: Karim Gomaa
#
# File Nmae: network_analysis.sh
#
# Description: Bash Script to Analysis Network and print useful informations about it
#
#####################################################################################################


######################################## Checking Files #############################################
# Check if the pcap file is provided as an argument
if [ -z "$1" ]; then
  echo "Usage: $0 <path_to_pcap_file>"
  exit 1
fi

# Input: Path to the Wireshark pcap file
pcap_file=$1

# Check if tshark is installed
if ! command -v tshark &> /dev/null; then
  echo "tshark could not be found, please install it."
  exit 1
fi
#####################################################################################################


######################################### Analyze Functions ############################################

# Function to extract information from the pcap file
analyze_traffic() {
  echo "Analyzing network traffic from $pcap_file..."

  # Total number of packets
  total_packets=$(tshark -r "$pcap_file" | wc -l)

  # Number of HTTP packets
  http_packets=$(tshark -r "$pcap_file" -Y http | wc -l)

  # Number of HTTPS (TLS) packets
  https_packets=$(tshark -r "$pcap_file" -Y tls | wc -l)

  # Extract top 5 source IP addresses
  top_source_ips=$(tshark -r "$pcap_file" -T fields -e ip.src | sort | uniq -c | sort -nr | head -n 5)

  # Extract top 5 destination IP addresses
  top_dest_ips=$(tshark -r "$pcap_file" -T fields -e ip.dst | sort | uniq -c | sort -nr | head -n 5)

  # Output analysis summary
  echo "----- Network Traffic Analysis Report -----"
  echo "1. Total Packets: $total_packets"
  echo "2. Protocols:"
  echo "  - HTTP: $http_packets packets"
  echo "  - HTTPS/TLS: $https_packets packets"
  echo ""
  echo "3. Top 5 Source IP Addresses:"
  echo "$top_source_ips"
  echo ""
  echo "4. Top 5 Destination IP Addresses:"
  echo "$top_dest_ips"
  echo ""
  echo "----- End of Report -----"
}

#####################################################################################################


# Start analyze_traffic $1 contain a path to a directory
analyze_traffic