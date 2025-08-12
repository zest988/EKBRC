#!/bin/sh

# Turn on Bluetooth
bluetoothctl power on

# Start scanning
bluetoothctl scan on &
SCAN_PID=$!
sleep 10  # Scan for 10 seconds

# Stop scanning
kill $SCAN_PID

# Look for the device named "KOReader-Remote"
DEVICE=$(bluetoothctl devices | grep "KOReader-Remote" | awk '{print $2}')

if [ -n "$DEVICE" ]; then
    # Pair and connect
    bluetoothctl pair "$DEVICE"
    bluetoothctl trust "$DEVICE"
    bluetoothctl connect "$DEVICE"
    echo "Successfully connected to $DEVICE"
else
    echo "KOReader-Remote not found"
fi
