#!/bin/sh

# bash script to launch the firmware

# for now, fixed firmware location and name 

FW_NAME=rproc-m4-fw
FW_LOCATION=/lib/firmware

echo -n $FW_LOCATION > /sys/module/firmware_class/parameters/path

echo -n $FW_NAME > /sys/class/remoteproc/remoteproc0/firmware

echo -n start > /sys/class/remoteproc/remoteproc0/state








