#!/bin/bash

############## GENERAL HELPERS ################

usage() {
	echo "Usage: ert-create-flash-image <path/to/CA7>"
	echo ""
	echo "    Example: ert-create-flash-image ./CA7"
	exit 1
}

detect_folders() {
	REL_ROOT=$1
	ABS_ROOT=$(realpath "$REL_ROOT")
	
	TMP_FILES=("$ABS_ROOT/DeviceTree"/*)
	PROJECT_NAME=$(basename "${TMP_FILES[0]}")
	
	TMP_FILES=("$ABS_ROOT/DeviceTree/$PROJECT_NAME/kernel"/*)
	DEVICE_TREE_NAME=$(basename "${TMP_FILES[0]}" .dts)
	
	TMP_FILES=("$ABS_ROOT"/linux*)
	LINUX_DIR=$(basename "${TMP_FILES[0]}")
	
	TMP_FILES=("$ABS_ROOT"/images*)
	IMAGES_DIR=$(basename "${TMP_FILES[0]}")
}

############# BOOTFS MODIFICATION ##############

edit_bootfs() {
	echo ""
	echo "Modifying linux boot fs"
	echo ""
	
	# mount bootfs image
	mkdir -p /mnt/bootfs_tmp
	mount -o loop "$ABS_ROOT/$IMAGES_DIR/st-image-bootfs-openstlinux-weston-stm32mp1.ext4" /mnt/bootfs_tmp
	
	# copy device tree blob
	cp "$ABS_ROOT/$LINUX_DIR/build/arch/arm/boot/dts/$1.dtb" /mnt/bootfs_tmp

	# edit extlinux.conf
	pushd /mnt/bootfs_tmp
	rm -rf *extlinux*
	mkdir -p extlinux/
	
	echo "MENU TITLE Select the boot mode" 		 > extlinux/extlinux.conf
	echo "MENU BACKGROUND ../splash.bmp" 		>> extlinux/extlinux.conf
	echo "TIMEOUT 5" 				>> extlinux/extlinux.conf
	echo "DEFAULT $1" 				>> extlinux/extlinux.conf
	echo "LABEL $1" 				>> extlinux/extlinux.conf
	echo "        KERNEL /uImage" 			>> extlinux/extlinux.conf
	echo "        FDT /$1.dtb" 			>> extlinux/extlinux.conf
	echo "        APPEND root=PARTUUID=e91c4e10-16e6-4c0e-bd0e-77becf4a3582 rootwait rw console=ttySTM0,115200" >> extlinux/extlinux.conf
	
	popd
	
	#unmount bootfs image
	umount /mnt/bootfs_tmp
	sync
	rm -r /mnt/bootfs_tmp
	
	echo ""
	echo "Done modifying linux boot fs"
	echo ""
}

############# FLASH IMAGE CREATION ##############

create_image() {
	echo ""
	echo "Creating flash image"
	echo ""
	pushd "$ABS_ROOT/deploy-flash/"

	# create flashlayout tsv file
	echo "#Opt	Id	Name	Type	IP	Offset	Binary" > flashlayout_sdcard.tsv
	echo "-	0x01	fsbl1-boot	Binary	none	0x0	../FIP_artifacts/arm-trusted-firmware/tf-a-$1-usb.stm32" 	>> flashlayout_sdcard.tsv
	echo "-	0x03	fip-boot	Binary	none	0x0	../FIP_artifacts/fip/fip-$1-trusted.bin" 			>> flashlayout_sdcard.tsv
	echo "P	0x04	fsbl1	Binary	mmc0	0x00004400	../FIP_artifacts/arm-trusted-firmware/tf-a-$1-sdcard.stm32" 	>> flashlayout_sdcard.tsv
	echo "P	0x05	fsbl2	Binary	mmc0	0x00044400	../FIP_artifacts/arm-trusted-firmware/tf-a-$1-sdcard.stm32"	>> flashlayout_sdcard.tsv
	echo "PD	0x06	fip	Binary	mmc0	0x00084400	../FIP_artifacts/fip/fip-$1-trusted.bin" 		>> flashlayout_sdcard.tsv
	echo "P	0x10	boot	System	mmc0	0x00484400	../$IMAGES_DIR/st-image-bootfs-openstlinux-weston-stm32mp1.ext4" >> flashlayout_sdcard.tsv
	echo "P	0x11	vendorfs	FileSystem	mmc0	0x04484400	../$IMAGES_DIR/st-image-vendorfs-openstlinux-weston-stm32mp1.ext4" >> flashlayout_sdcard.tsv
	echo "P	0x12	rootfs	FileSystem	mmc0	0x05484400	../$IMAGES_DIR/st-image-weston-openstlinux-weston-stm32mp1.ext4" >> flashlayout_sdcard.tsv
	
	# create the flash image
	create_sdcard_from_flashlayout flashlayout_sdcard.tsv
	
	popd
	echo ""
	echo "Done creating flash image"
	echo ""
}

########### MAIN ################
if [ $# -ne 1 ];
then
	echo "[ERROR]: bad number of parameters"
	echo ""
	usage
else
	# find all necessary files
	detect_folders $1
	echo ""
	echo "CA7 root folder: $ABS_ROOT"
	echo "Linux folder: $LINUX_DIR"
	echo "Filesystem images folder: $IMAGES_DIR"
	echo "Device tree name: $DEVICE_TREE_NAME"
	echo ""
	
	# ask for confirmation
	read -p "Is this configuration correct?" -n 1 -r CONFIRM
	echo ""
	if [[ $CONFIRM =~ ^[Yy]$ ]]
	then
		pushd "$ABS_ROOT"
		
		#create deployment folder
		mkdir -p deploy-flash/
		
		#create flash image
		edit_bootfs $DEVICE_TREE_NAME
		create_image $DEVICE_TREE_NAME
		
		popd
	fi
fi



