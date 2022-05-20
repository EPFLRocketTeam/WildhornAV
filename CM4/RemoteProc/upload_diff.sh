#! /bin/bash

diff -a ../Debug/WildhornAV_CM4.elf  ./WildhornAV_CM4_prev > upload.patch

bzip2 -f upload.patch

scp upload.patch.bz2 root@192.168.7.1:~/

ssh root@192.168.7.1 "sh install_diff.sh"

cp ../Debug/WildhornAV_CM4.elf ./WildhornAV_CM4_prev
