FROM ubuntu:focal

# install dependencies
ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Zurich

RUN apt-get update
RUN apt-get install -y gawk wget git-core diffstat unzip texinfo gcc-multilib build-essential chrpath socat cpio python3 python3-pip python3-pexpect xz-utils debianutils iputils-ping python3-git python3-jinja2 libegl1-mesa libsdl1.2-dev pylint3 pylint xterm
RUN apt-get install -y make xsltproc docbook-utils fop dblatex xmlto kmod
RUN apt-get install -y libncurses5 libncurses5-dev libncursesw5-dev libssl-dev linux-headers-generic u-boot-tools device-tree-compiler bison flex g++ libyaml-dev libmpc-dev libgmp-dev
RUN apt-get install -y coreutils bsdmainutils sed curl bc lrzsz corkscrew cvs nfs-common nfs-kernel-server libarchive-zip-perl dos2unix texi2html libxml2-utils

# install the SDK
ADD st-image-*-toolchain-*.sh ./sdk_installer.sh
RUN chmod +x sdk_installer.sh
RUN mkdir sdk
RUN ./sdk_installer.sh -d sdk
RUN rm sdk_installer.sh

RUN echo "source /sdk/environment-setup-cortexa7t2hf-neon-vfpv4-ostl-linux-gnueabi" >> /root/.bashrc

# add custom scripts
RUN mkdir ert-scripts

ADD create_sdcard_from_flashlayout.sh ./ert-scripts
RUN ln -s /ert-scripts/create_sdcard_from_flashlayout.sh /bin/create_sdcard_from_flashlayout

ADD ert-compile-device-tree.sh ./ert-scripts
RUN ln -s /ert-scripts/ert-compile-device-tree.sh /bin/ert-compile-device-tree

ADD ert-create-flash-image.sh ./ert-scripts
RUN ln -s /ert-scripts/ert-create-flash-image.sh /bin/ert-create-flash-image


