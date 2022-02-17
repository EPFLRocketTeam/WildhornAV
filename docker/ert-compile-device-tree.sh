#!/bin/bash

############## GENERAL HELPERS ################

usage() {
	echo "Usage: ert-compile-device-tree <path/to/CA7>"
	echo ""
	echo "    Example: ert-compile-device-tree ./CA7"
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
	
	TMP_FILES=("$ABS_ROOT"/tf-a*)
	TFA_DIR=$(basename "${TMP_FILES[0]}")
	
	TMP_FILES=("$ABS_ROOT"/u-boot*)
	UBOOT_DIR=$(basename "${TMP_FILES[0]}")
}

############# LINUX COMPILATION ##############

compile_linux() {
	echo ""
	echo "Compiling linux device tree"
	echo ""
	pushd "$ABS_ROOT/$LINUX_DIR/"

	# remove old folders
	rm -rf src/ build/
	# extract source & switch to to
	tar xfJ linux*.tar.xz --one-top-level=src --strip-components 1
	pushd src
	# patch source
	for p in `ls -1 ../*.patch`; do patch -p1 < $p; done
	
	# copy the device tree source (from MX)
	cp -r "$ABS_ROOT/DeviceTree/$PROJECT_NAME/kernel"/* arch/arm/boot/dts/
	
	# configure linux compilation
	mkdir -p ../build
	make O="$PWD/../build" multi_v7_defconfig fragment*.config
	for f in `ls -1 ../fragment*.config`; do scripts/kconfig/merge_config.sh -m -r -O $PWD/../build $PWD/../build/.config $f; done
	yes '' | make oldconfig O="$PWD/../build"
	
	# do compilation
	make "$1".dtb LOADADDR=0xC2000040 O="$PWD/../build"
	
	popd
	popd
	echo ""
	echo "Done compiling linux device tree"
	echo ""
}

############# TFA COMPILATION ##############

compile_tfa() {
	echo ""
	echo "Compiling TF-A"
	echo ""
	pushd "$ABS_ROOT/$TFA_DIR/"

	# remove old folders
	rm -rf src/ build/
	# extract source & switch to to
	tar xfz tf-a*.tar.gz --one-top-level=src --strip-components 1
	pushd src
	# patch source
	for p in `ls -1 ../*.patch`; do patch -p1 < $p; done
	
	# copy the device tree source (from MX)
	cp -r "$ABS_ROOT/DeviceTree/$PROJECT_NAME/tf-a"/* fdts/
	
	# configure linux compilation
	export FIP_DEPLOYDIR_ROOT="$ABS_ROOT/FIP_artifacts"
	
	# do compilation
	make -f ../Makefile.sdk TF_A_DEVICETREE=$1 FIP_CONFIG=" trusted" FIP_BL32_CONF="tfa," TF_A_CONFIG="trusted emmc sdcard usb" DEPLOYDIR=$FIP_DEPLOYDIR_ROOT/arm-trusted-firmware stm32
	
	popd
	popd
	echo ""
	echo "Done compiling TF-A"
	echo ""
}

############# UBOOT COMPILATION ##############

compile_uboot() {
	echo ""
	echo "Compiling U-boot"
	echo ""
	pushd "$ABS_ROOT/$UBOOT_DIR/"

	# remove old folders
	rm -rf src/ build/
	# extract source & switch to to
	tar xfz u-boot*.tar.gz --one-top-level=src --strip-components 1
	pushd src
	# patch source
	for p in `ls -1 ../*.patch`; do patch -p1 < $p; done
	
	# copy the device tree source (from MX)
	cp -r "$ABS_ROOT/DeviceTree/$PROJECT_NAME/u-boot"/* arch/arm/dts/
	
	# configure linux compilation
	export FIP_DEPLOYDIR_ROOT="$ABS_ROOT/FIP_artifacts"
	
	# do compilation
	make -f ../Makefile.sdk DEVICE_TREE=$1 DEPLOYDIR=$FIP_DEPLOYDIR_ROOT/u-boot FIP_CONFIG=" trusted" FIP_BL32_CONF="tfa," all
	
	popd
	popd
	echo ""
	echo "Done compiling U-boot"
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
	echo "Project name: $PROJECT_NAME"
	echo "Linux folder: $LINUX_DIR"
	echo "TF-A folder: $TFA_DIR"
	echo "U-boot folder: $UBOOT_DIR"
	echo "Device tree name: $DEVICE_TREE_NAME"
	echo ""
	
	# ask for confirmation
	read -p "Is this configuration correct?" -n 1 -r CONFIRM
	echo ""
	if [[ $CONFIRM =~ ^[Yy]$ ]]
	then
		pushd "$ABS_ROOT"
		
		#remove old stuff
		rm -rf FIP_artifacts/
		
		#do the compilation
		compile_linux $DEVICE_TREE_NAME
		compile_tfa $DEVICE_TREE_NAME
		compile_uboot $DEVICE_TREE_NAME
		
		popd
	fi
fi



