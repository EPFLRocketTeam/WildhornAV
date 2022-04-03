# WildhornAV
This repository holds all of the source code for the Wildhorn Avionics

## Overview
This code is meant to be executed on an stm32mp157dab based custom hostboard. These hostboards are developped inhouse at EPFL Rocket team. The stm32mp157 series of microprocessors feature a dualcore cortex A7 optimized for linux and a cortex M4 coprocessor optimized for real time operating systems. 


## Organization
The project is organized around two subdirectories CA7 and CM4. These contain the code for each processor subsystem as their names indicate.

### CA7
The CA7 subdir contains the device tree overlays for our hostboard as well as the user code which will be running in the linux environement.

### CM4
The CM4 subdir contains all the code which will be running on the coprocessor. The autogenerated code from stm32cubeMX is located in the CM4/core/ folder. The code developped by the avionics team is located inside the CM4/ert/ folder. This folder is itself separated into subfolder for the different parts of the software.

## Features
* ![img](https://img.shields.io/badge/Feature-Done-success) Compilation scripts [Olivér, Maxime, Yohann, Alex]
* ![img](https://img.shields.io/badge/Feature-Done-success) Linux boot [Iacopo, Olivér]
* ![img](https://img.shields.io/badge/Feature-Done-success) Coprocessor launch [Iacopo]
* ![img](https://img.shields.io/badge/Feature-Done-success) Blinking led [Iacopo]
* ![img](https://img.shields.io/badge/Feature-Progress-important) Generic device driver [Iacopo] 
* ![img](https://img.shields.io/badge/Feature-Progress-important) Coprocessor communication [Iacopo]
* ![img](https://img.shields.io/badge/Feature-Progress-important) Multiboard communication [Olivér]
* ![img](https://img.shields.io/badge/Feature-Unstarted-critical) Barometer device [unassigned]
* ![img](https://img.shields.io/badge/Feature-Unstarted-critical) Accelerometer device [unassigned]
* ![img](https://img.shields.io/badge/Feature-Unstarted-critical) Gyroscope device [unassigned]
* ![img](https://img.shields.io/badge/Feature-Unstarted-critical) GNSS device [unassigned]
* ![img](https://img.shields.io/badge/Feature-Progress-important) Radio device [Charlotte]
* ![img](https://img.shields.io/badge/Feature-Unstarted-critical) Recovery device [unassigned]
* ![img](https://img.shields.io/badge/Feature-Unstarted-critical) I2C interface [unassigned]
* ![img](https://img.shields.io/badge/Feature-Unstarted-critical) SPI interface [unassigned]
* ![img](https://img.shields.io/badge/Feature-Progress-important) UART interface [Iacopo]
* ![img](https://img.shields.io/badge/Feature-Unstarted-critical) State machine [unassigned]
* ![img](https://img.shields.io/badge/Feature-Unstarted-critical) State estimation [Yohann]

## Contributors

* Alex Schulster
* Yohann Paulus
* Maxime Chantemargue
* Oliver Facklam
* Iacopo Sprenger

