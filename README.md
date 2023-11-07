# 💾 Unified Storage Library 

[![Check Arduino](https://github.com/arduino-libraries/Arduino_UnifiedStorage/actions/workflows/check-arduino.yml/badge.svg)](https://github.com/arduino-libraries/Arduino_UnifiedStorage/actions/workflows/check-arduino.yml) [![Compile Examples](https://github.com/arduino-libraries/Arduino_UnifiedStorage/actions/workflows/compile-examples.yml/badge.svg)](https://github.com/arduino-libraries/Arduino_UnifiedStorage/actions/workflows/compile-examples.yml) [![Spell Check](https://github.com/arduino-libraries/Arduino_UnifiedStorage/actions/workflows/spell-check.yml/badge.svg)](https://github.com/arduino-libraries/Arduino_UnifiedStorage/actions/workflows/spell-check.yml) [![Sync Labels](https://github.com/arduino-libraries/Arduino_UnifiedStorage/actions/workflows/sync-labels.yml/badge.svg)](https://github.com/arduino-libraries/Arduino_UnifiedStorage/actions/workflows/sync-labels.yml)

The Arduino_UnifiedStorage library provides a unified interface to access different types of storage, including internal storage, SD cards, and USB mass storage devices. It simplifies the handling of files and directories across multiple storage mediums on Portenta, Opta, and some Nicla boards.

## Examples

* [**examples/SimpleStorageWriteRead**](https://github.com/arduino-libraries/Arduino_UnifiedStorage/blob/main/examples/SimpleStorageWriteRead/SimpleStorageWriteRead.ino) - Write/read simple data from SD, USB and internal storage

* [**examples/AdvancedUSBInternalOperations**](https://github.com/arduino-libraries/Arduino_UnifiedStorage/blob/main/examples/AdvancedUSBInternalOperations/AdvancedUSBInternalOperations.ino) - Navigate file structure and demonstrate file operations between USB and internal storage

* [**examples/BackupInternalPartitions**](https://github.com/arduino-libraries/Arduino_UnifiedStorage/blob/main/examples/BackupInternalPartitions/BackupInternalPartitions.ino) - Back up all partitions on the internal storage to a USB Mass Storage device.

* [**examples/Logger**](https://github.com/arduino-libraries/Arduino_UnifiedStorage/blob/main/examples/Logger/Logger.ino) - This example demonstrates how you can log sensor data into its internal storage and detect the insertion of a USB drive. When a USB drive is connected, it selectively transfers only the new data to the USB mass storage device. Even if you remove the USB drive, the device continues to log data in its internal storage. This capability is particularly valuable for accumulating training data required for embedded machine learning applications.
 
* [**examples/InternalStoragePartitioning**](https://github.com/arduino-libraries/Arduino_UnifiedStorage/blob/main/examples/InternalStoragePartitioning/InternalStoragePartitioning.ino) - Demonstrates how you can use the Arduino_UnifiedStorage library to create and read partitions on the Internal QSPI Storage. 
 
## 👀 Instructions

1. Download and install this library
2. Check compatibility with your platform
3. Check out the examples or read read the documentation [here](./docs).

## ✨ Features

* Access files and directories on internal storage, SD cards, and USB mass storage devices.
* Read and write data to files.
* Create, remove, and rename files and directories.
* Copy and move files and directories.
* List files and subfolders in a directory.
* Manipulate files and folders from one storage medium to another
* Format partitions and drives (FAT and LittleFS)
* Create and modify partitions on the internal storage
* Register callbacks whenever a USB Mass Storage device has been inserted or removed
* Get verbose output of every action the library performs for seamless debugging

## Compatibility

This library has been tested with the following STM32 and Renesas based Arduino boards. The availability of storage mediums depends on the hardware interfaces:

* **Portenta Machine Control**: USB and Internal QSPI Flash
* **Portenta H7 + Portenta Breakout**: USB, SD, and QSPI
* **Portenta H7 + Vision Shield**: SD and QSPI
* **Portenta C33 + Portenta Breakout**: USB, SD, and QSPI
* **Portenta C33 + Vision Shield**: SD and QSPI
* **Opta**: Internal QSPI Flash and USB


The library allows you to connect a USB drives in a couple of different ways:

* **Use the USB-C port on the board**: Ensure Serial functionality is not in use on the same port to prevent conflicts.
* **Connect to the USB-A port**: Located on the Portenta Breakout
* **Use a USB Hub**: Note that while our some USB Hubs are supported, we cannot ensure compatibility with all USB Hubs. Especially for when used together with advanced features like Ethernet or HDMI, such as certain USB-C hubs.

**Note:** Due to the extremely large selection of USB Mass Storage devices on the market, we cannot guarantee compatibility with your USB thumb drive. However, we had great results with drives from reputable brands such as Kingston, SanDisk, Samsung, etc.

**Note:** Due to an unforeseen compatibility issue on the Portenta Breakout Board, inserting a USB drive on the USB-A port of the breakout board may occasionally cause a reboot on Portenta C33 boards. You can work around this issue by connecting your USB Mass Storage device through a USB hub. Please note that the USB Callback functionality on the Portenta C33 boards might also be affected by this issue.

This limitation only affects Portenta C33 boards.

## 📖 Documentation

For more information about this library please read the documentation [here](./docs).
