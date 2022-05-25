#! /bin/sh


scp start_fw.sh root@192.168.7.1:~/
scp stop_fw.sh root@192.168.7.1:~/
scp rc.local root@192.168.7.1:/etc/
ssh root@192.168.7.1 "sh stop_fw.sh && cd /etc && chmod +x rc.local && cd - && exit"
scp ../Debug/WildhornAV_CM4.elf root@192.168.7.1:/lib/firmware/rproc-m4-fw

ssh root@192.168.7.1 "sh stop_fw.sh && sh start_fw.sh && exit"

