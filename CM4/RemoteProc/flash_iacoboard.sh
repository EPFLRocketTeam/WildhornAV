#! /bin/bash

# HOSTBOARD FIRMWARE UPDATING SCRIPT
# uses ssh if available
# otherwise uses ckermit



REMOTE_SSH=$( ifconfig | grep 192.168.7. )

SSH_TARGET="root@192.168.7.1"

KERMIT_CONFIG=kermit_config.cfg


if [[ $1 == "kermit" ]]; then
	REMOTE_SSH=
fi



# local stuff

LAST_FIRMWARE_HASH=$( sha256sum WildhornAV_CM4.elf | awk '{print $1}' )

echo "last firmware hash [local]: "$LAST_FIRMWARE_HASH






if [[ -z "$REMOTE_SSH" ]]; then 
	# use ckermit
	echo "using CKERMIT"
	REMOTE_FIRMWARE_HASH=$( kermit kermit_config.cfg -C "remote host sha256sum WildhornAV_CM4.elf, exit" | awk '{print $1}')
	echo "last firmware hash [remote]: "$REMOTE_FIRMWARE_HASH
	if [[ $LAST_FIRMWARE_HASH == $REMOTE_FIRMWARE_HASH ]] ; then
		echo "firmware match, delta update possible"

		diff -au --to-file=../Debug/WildhornAV_CM4.elf WildhornAV_CM4.elf > update.patch
		echo "delta created"

		DATA_CHECK=$( cat  update.patch )
		if [ -z "$DATA_CHECK" ]; then
			echo "no changes detected, exit"
			exit 0
		fi

		bzip2 -f update.patch
		echo "delta compressed"

		kermit $KERMIT_CONFIG -s update.patch.bz2 ~/ 
		echo "delta uploaded"

		kermit $KERMIT_CONFIG -C "remote host bunzip2 -f update.patch.bz2, exit"
		echo "delta uncompressed"

		kermit $KERMIT_CONFIG -C "remote host python3 patcher.py, exit"
		echo "delta applied"

		kermit $KERMIT_CONFIG -C "remote host cp WildhornAV_CM4.elf /lib/firmware/rproc-m4-fw, exit"
		echo "firmware installed"

	else
		echo "firmware mismatch, full refresh required"

		kermit $KERMIT_CONFIG -s patch.py ~/
		kermit $KERMIT_CONFIG -s patcher.py ~/
		kermit $KERMIT_CONFIG -s start_fw.sh ~/
		kermit $KERMIT_CONFIG -s stop_fw.sh ~/
		kermit $KERMIT_CONFIG -s rc.local /etc/rc.local
		kermit $KERMIT_CONFIG -C " remote host chmod +x /etc/rc.local, exit"
		echo "tools sent"

		cp  ../Debug/WildhornAV_CM4.elf WildhornAV_CM4.elf
		bzip2 -f WildhornAV_CM4.elf
		echo "firmware compressed"

		kermit $KERMIT_CONFIG -s WildhornAV_CM4.elf.bz2 ~/
		echo "firmware sent"

		kermit $KERMIT_CONFIG -C "remote host bunzip2 -f  WildhornAV_CM4.elf.bz2, exit"
		echo "firmware uncompressed"

		kermit $KERMIT_CONFIG -C "remote host cp WildhornAV_CM4.elf /lib/firmware/rproc-m4-fw, exit"
		echo "firmware installed"	

	fi

else
	# use ssh
	echo "using SSH"

	REMOTE_FIRMWARE_HASH=$( ssh $SSH_TARGET "sha256sum WildhornAV_CM4.elf" | awk '{print $1}' )
	echo "last firmware hash [remote]: "$REMOTE_FIRMWARE_HASH

	if [[ $LAST_FIRMWARE_HASH == $REMOTE_FIRMWARE_HASH ]] ; then #use delta update
		echo "firmware match, delta update possible"

		diff -au --to-file=../Debug/WildhornAV_CM4.elf WildhornAV_CM4.elf > update.patch
		echo "delta created"

		DATA_CHECK=$( cat  update.patch )
		if [ -z "$DATA_CHECK" ]; then
			echo "no changes detected, exit"
			exit 0
		fi

		bzip2 -f update.patch
		echo "delta compressed"

		scp update.patch.bz2 $SSH_TARGET:~/ 
		echo "delta uploaded"

		ssh $SSH_TARGET "bunzip2 -f update.patch.bz2"
		echo "delta uncompressed"

		ssh $SSH_TARGET "python3 patcher.py"
		echo "delta applied"

		ssh $SSH_TARGET "cp WildhornAV_CM4.elf /lib/firmware/rproc-m4-fw"
		echo "firmware installed"

	else
		echo "firmware mismatch, full refresh required"

		scp patch.py $SSH_TARGET:~/
		scp patcher.py $SSH_TARGET:~/
		scp start_fw.sh $SSH_TARGET:~/
		scp stop_fw.sh $SSH_TARGET:~/
		scp rc.local $SSH_TARGET:/etc/rc.local
		ssh $SSH_TARGET "chmod +x /etc/rc.local"
		echo "tools sent"

		cp  ../Debug/WildhornAV_CM4.elf WildhornAV_CM4.elf
		bzip2 -f WildhornAV_CM4.elf
		echo "firmware compressed"

		scp WildhornAV_CM4.elf.bz2 $SSH_TARGET:~/
		echo "firmware sent"

		ssh $SSH_TARGET "bunzip2 -f  WildhornAV_CM4.elf.bz2"
		echo "firmware uncompressed"

		ssh $SSH_TARGET "cp WildhornAV_CM4.elf /lib/firmware/rproc-m4-fw"
		echo "firmware installed"	

	fi

	REMOTE_HASH_CHECK=$( ssh $SSH_TARGET "sha256sum /lib/firmware/rproc-m4-fw" | awk '{print $1}' )
	echo "remote installed firmware hash: "$REMOTE_HASH_CHECK

	LOCAL_HASH_CHECK=$( sha256sum ../Debug/WildhornAV_CM4.elf | awk '{print $1}' )
	echo "local latest firmware hash: "$LOCAL_HASH_CHECK

	if [[ $REMOTE_HASH_CHECK == $LOCAL_HASH_CHECK ]]; then
		echo "match, success!"
	else
		echo "error, install unsucessul"
		exit 1 
	fi

fi


echo "updating local cache"
cp ../Debug/WildhornAV_CM4.elf WildhornAV_CM4.elf 
echo "local cache updated"
echo "terminating, reset hostboard"

