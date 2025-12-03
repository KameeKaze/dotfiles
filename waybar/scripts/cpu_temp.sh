#!/bin/bash

# Get CPU usage (average of all cores)
cpu=$(grep 'cpu ' /proc/stat | awk '{usage=($2+$4)*100/($2+$4+$5)} END {printf "%.0f", usage}')

# Get temperature in °C (from hwmon)
temp=$(cat /sys/class/hwmon/hwmon1/temp1_input)
temp=$((temp / 1000))

# Print combined output
echo " ${cpu}% |  ${temp}°C"
