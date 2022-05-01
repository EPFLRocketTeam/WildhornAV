#! /bin/sh


scp start_fw.sh root@192.168.7.1:~/
scp stop_fw.sh root@192.168.7.1:~/
scp install_diff.sh root@192.168.7.1:~/
scp rc.local root@192.168.7.1:/etc/
ssh root@192.168.7.1 "sh stop_fw.sh && cd /etc && chmod +x rc.local && cd - && exit"
scp ../Debug/WildhornAV_CM4.elf root@192.168.7.1:~/

ssh root@192.168.7.1 "cp ./WildhornAV_CM4.elf /lib/firmware/rproc-m4-fw"

ssh root@192.168.7.1 "sh stop_fw.sh && sh start_fw.sh && exit"

cp ../Debug/WildhornAV_CM4.elf ./WildhornAV_CM4_prev
