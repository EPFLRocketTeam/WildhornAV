#!bin/bash

bunzip2 -f upload.patch.bz2

patch WildhornAV_CM4.elf upload.patch

cp WildhornAV_CM4.elf /lib/firmware/rproc-m4-fw

sh stop_fw.sh

sh start_fw.sh