#! /bin/bash

kermit kermit_config.cfg -s start_fw.sh
kermit kermit_config.cfg -s stop_fw.sh
kermit kermit_config.cfg -s rc.local /etc/rc.local


kermit kermit_config.cfg -s ../Debug/WildhornAV_CM4.elf /lib/firmware/rproc-m4-fw

kermit kermit_config.cfg -f

cp ../Debug/WildhornAV_CM4.elf ./WildhornAV_CM4_prev
