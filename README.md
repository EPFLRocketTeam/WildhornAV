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
* ![img](https://img.shields.io/badge/Feature-Done-success) Generic device driver [Iacopo] 
* ![img](https://img.shields.io/badge/Feature-Working-yellow) Coprocessor communication [Iacopo]
* ![img](https://img.shields.io/badge/Feature-Progress-important) Multiboard communication [Olivér]
* ![img](https://img.shields.io/badge/Feature-Progress-important) Barometer device [Johanna, Iacopo]
* ![img](https://img.shields.io/badge/Feature-Progress-important) Accelerometer device [Johanna, Iacopo]
* ![img](https://img.shields.io/badge/Feature-Progress-important) Gyroscope device [Johanna, Iacopo]
* ![img](https://img.shields.io/badge/Feature-Progress-important) GNSS device [Charlotte]
* ![img](https://img.shields.io/badge/Feature-Progress-important) Radio device [Martin, Charlotte]
* ![img](https://img.shields.io/badge/Feature-Unstarted-critical) Recovery device [unassigned]
* ![img](https://img.shields.io/badge/Feature-Done-success) I2C interface [Iacopo]
* ![img](https://img.shields.io/badge/Feature-Unstarted-critical) SPI interface [unassigned]
* ![img](https://img.shields.io/badge/Feature-Done-success) UART interface [Iacopo]
* ![img](https://img.shields.io/badge/Feature-Progress-important) State machine [Iacopo]
* ![img](https://img.shields.io/badge/Feature-Unstarted-critical) State estimation [Yohann]
* ![img](https://img.shields.io/badge/Feature-Unstarted-critical) Feedback logging app [unassigned]
* ![img](https://img.shields.io/badge/Feature-Unstarted-critical) OD Sync and logging app [unassigned]
* ![img](https://img.shields.io/badge/Feature-Unstarted-critical) Data handling app [unassigned]
* ![img](https://img.shields.io/badge/Feature-Unstarted-critical) Command handling app [unassigned]


## Contributors

* Alex Schulster
* Yohann Paulus
* Maxime Chantemargue
* Oliver Facklam
* Iacopo Sprenger

