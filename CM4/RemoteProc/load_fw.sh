#! /bin/sh


scp start_fw.sh root@192.168.7.1:~/
scp stop_fw.sh root@192.168.7.1:~/

scp ../Debug/WildhornAV_CM4.elf root@192.168.7.1:~/

ssh root@192.168.7.1 "sh stop_fw.sh; sh start_fw.sh; exit"
