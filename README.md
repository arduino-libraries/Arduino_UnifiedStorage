# Unified Storage Library

The Arduino_UnifiedStorage library provides a unified interface to access different types of storage, including internal storage, SD cards, and USB mass storage devices. It simplifies the handling of files and directories across multiple storage mediums on Portenta, Opta, and some Nicla boards.


## Examples
* [**examples/SimpleStorageWriteRead**](https://github.com/arduino-libraries/Arduino_UnifiedStorage/blob/main/examples/SimpleStorageWriteRead/SimpleStorageWriteRead.ino) - this example is concerned with reading/writing and seeking
* [**examples/AdvancedUSBInternalOperations**](https://github.com/arduino-libraries/Arduino_UnifiedStorage/blob/main/examples/AdvancedUSBInternalOperations/AdvancedUSBInternalOperations.ino) - this example is concerned with more advanced features like creating folders, traversing folder sturctures and moving/copying from one storage medium to another
* [**examples/PortentaH7Logger**](https://github.com/arduino-libraries/Arduino_UnifiedStorage/blob/main/examples/PortentaH7Logger/PortentaH7Logger.ino) - this is more of a real life usecase, where this library is used to log sensor data to a file on the internal storage and check if a USB Mass Storage deviece is inserted. If it is detected it will backup the information on the internal storage, only copying the bytes that are new since the last update.
* [**examples/BackupInternalPartitions**](https://github.com/arduino-libraries/Arduino_UnifiedStorage/blob/main/examples/BackupInternalPartitions/BackupInternalPartitions.ino) - Another real life usecase, where this library is used to back-up all partitions on the internal storage to a USB Mass Storage device.

## Instructions
1. Download and install this library 
2. Check compatibility with your platform
3. To use internal storage, you need to make sure it is partitioned and formatted correctly:

### Formatting the Portenta H7 Internal Storage
* Flash the `QSPIFormat` example that can be found in the `STM32H747_System` folder (For Portenta H7/Opta/Giga)
* Open the serial monitor and select answer with "n" when this appears "Do you want to use partition scheme 1? Y/[n]"
* The sketch will warn you that the content of the QSPI flash will be erased. Answer with "Y".
* When asked if you'd like to use LittleFS on the data parition, select "n". Most of the examples assume that the drive is formatted as FAT. You can use the library to format to LittleFS later. 
* Reboot the board
 
### Formatting the Portenta C33 Internal Storage
*  Flash the `QSPIFormat` example that can be found in the `Storage` folder for Portenta C33.
*  Open the Serial Monitor. The sketch will warn you that the content of the QSPI flash will be erased. Answer with "Y".
*  When asked if you'd like to use LittleFS on the data parition, select "n". Most of the examples assume that the drive is formatted as FAT. You can use the library to format to LittleFS later. 
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
This library is compatible with STM32 and Renesas based Arduino boards. The availability of storage mediums depends on the hardware interfaces:
* Portenta Machine Control: USB and Internal QSPI Flash
* Portenta H7 + Portenta Breakout: USB, SD, and QSPI
* Portenta H7 + Vision Shield: SD and QSPI
* Portenta C33 + Portenta Breakout: USB, SD, and QSPI
* Portenta C33 + Vision Shield: SD and QSPI
