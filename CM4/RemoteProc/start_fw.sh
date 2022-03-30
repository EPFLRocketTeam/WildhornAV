#!/bin/sh

# bash script to launch the firmware

# for now, fixed firmware location and name 

FW_NAME=WildhornAV_CM4.elf
FW_LOCATION=$(eval pwd)

echo -n $FW_LOCATION > /sys/module/firmware_class/parameters/path

echo -n $FW_NAME > /sys/class/remoteproc/remoteproc0/firmware

echo -n start > /sys/class/remoteproc/remoteproc0/state








