# Unified Storage Library

[![Check Arduino](https://github.com/arduino-libraries/Arduino_UnifiedStorage/actions/workflows/check-arduino.yml/badge.svg)](https://github.com/arduino-libraries/Arduino_UnifiedStorage/actions/workflows/check-arduino.yml) [![Compile Examples](https://github.com/arduino-libraries/Arduino_UnifiedStorage/actions/workflows/compile-examples.yml/badge.svg)](https://github.com/arduino-libraries/Arduino_UnifiedStorage/actions/workflows/compile-examples.yml) [![Spell Check](https://github.com/arduino-libraries/Arduino_UnifiedStorage/actions/workflows/spell-check.yml/badge.svg)](https://github.com/arduino-libraries/Arduino_UnifiedStorage/actions/workflows/spell-check.yml) [![Sync Labels](https://github.com/arduino-libraries/Arduino_UnifiedStorage/actions/workflows/sync-labels.yml/badge.svg)](https://github.com/arduino-libraries/Arduino_UnifiedStorage/actions/workflows/sync-labels.yml)

The Arduino_UnifiedStorage library provides a unified interface to access different types of storage, including internal storage, SD cards, and USB mass storage devices. It simplifies the handling of files and directories across multiple storage mediums on Portenta, Opta, and some Nicla boards.


## Examples
* [**examples/SimpleStorageWriteRead**](https://github.com/arduino-libraries/Arduino_UnifiedStorage/blob/main/examples/SimpleStorageWriteRead/SimpleStorageWriteRead.ino) - Write/read simple data from SD, USB and internal storage
* [**examples/AdvancedUSBInternalOperations**](https://github.com/arduino-libraries/Arduino_UnifiedStorage/blob/main/examples/AdvancedUSBInternalOperations/AdvancedUSBInternalOperations.ino) - Navigate file structure and demonstrate file operations between USB and internal storage
* [**examples/BackupInternalPartitions**](https://github.com/arduino-libraries/Arduino_UnifiedStorage/blob/main/examples/BackupInternalPartitions/BackupInternalPartitions.ino) - Back up all partitions on the internal storage to a USB Mass Storage device.

## Instructions
1. Download and install this library 
2. Check compatibility with your platform
3. To use internal storage, you need to make sure it is partitioned and formatted correctly:

### Formatting the Portenta H7 / Portenta Machine Control / Opta Internal Storage
* Flash the `QSPIFormat` example that can be found in the `STM32H747_System` folder
* Open the serial monitor and select answer with "n" when this appears "Do you want to use partition scheme 1? Y/[n]"
* The sketch will warn you that the content of the QSPI flash will be erased. Answer with "Y".
* When asked if you'd like to use LittleFS on the data partition, select "n". Most of the examples assume that the drive is formatted as FAT. You can use the library to format to LittleFS later. 
* Reboot the board
 
### Formatting the Portenta C33 Internal Storage
*  Flash the `QSPIFormat` example that can be found in the `Storage` folder for Portenta C33.
*  Open the Serial Monitor. The sketch will warn you that the content of the QSPI flash will be erased. Answer with "Y".
*  When asked if you'd like to use LittleFS on the data partition, select "n". Most of the examples assume that the drive is formatted as FAT. You can use the library to format to LittleFS later. 
*  Reboot the board

## Features
* Access files and directories on internal storage, SD cards, and USB mass storage devices.
* Read and write data to files.
* Create, remove, and rename files and directories.
* Copy and move files and directories.
* List files and subfolders in a directory.
* Manipulate files and folders from one storage medium to another
* Format partitions and drives (FAT and LittleFS)

## Compatibility
This library has been tested with the following STM32 and Renesas based Arduino boards. The availability of storage mediums depends on the hardware interfaces:
* Portenta Machine Control: USB and Internal QSPI Flash
* Portenta H7 + Portenta Breakout: USB, SD, and QSPI
* Portenta H7 + Vision Shield: SD and QSPI
* Portenta C33 + Portenta Breakout: USB, SD, and QSPI
* Portenta C33 + Vision Shield: SD and QSPI
* Opta: Internal QSPI Flash and USB


Note: Due to an unforeseen compatibility issue on the Portenta Breakout Board, inserting a USB drive on the USB-A port of the breakout board may occasionally cause a reboot on Portenta C33 boards. You can work around this issue by connecting your USB Mass Storage device through a USB hub. This limitation only affects Portenta C33 boards.