# WildhornAV
This repository holds all of the source code for the Wildhorn Avionics

## Overview
This code is meant to be executed on an stm32mp157dab based custom hostboard. These hostboards are developped inhouse at EPFL Rocket team. The stm32mp157 series of microprocessors feature a dualcore cortex A7 optimized for linux and a cortex M4 coprocessor optimized for real time operating systems. 


## Organization
The project is organized around two subdirectories CA7 and CM4. These contain the code for each processor subsystem as their names indicate.

### CA7
The CA7 subdir contains the device tree overlays for our hostboard as well as the user code which will be running in the linux environement.

### CM4
The CM4 subdir contains all the code which will be running on the coprocessor.

## Features
* Linux boot  ![img](https://img.shields.io/badge/Feature-Done-success)
* Coprocessor launch ![img](https://img.shields.io/badge/Feature-Done-success)
* Blinking led ![img](https://img.shields.io/badge/Feature-Done-success)
* Generic device driver ![img](https://img.shields.io/badge/Feature-Progress-important)
* Multiboard communication ![img](https://img.shields.io/badge/Feature-Progress-important)
* Sensor interfaces ![img](https://img.shields.io/badge/Feature-Unstarted-critical)

## Contributors

* Alex Schulster
* Yohan Paulus
* Maxime Chantemargue
* Oliver Facklam
* Iacopo Sprenger


