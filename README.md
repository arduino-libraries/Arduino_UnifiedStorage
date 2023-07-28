# Unified Storage Library

The UnifiedStorage library provides a unified interface to access different types of storage, including internal storage, SD cards, and USB mass storage devices. It simplifies the handling of files and directories across multiple storage mediums on Portenta, Opta, and some Nicla boards.


## Examples
* **examples/basic** - this example is concerned with reading/writing and seeking
* **examples/advanced** - this example is concerned with more advanced features like creating folders, traversing folder sturctures and moving/copying from one storage medium to another
* **examples/opta_logger** - this is more of a real life usecase, where this library is used on an Arduino Opta to log sensor data to a file on the internal storage and check if a USB Mass Storage deviece is inserted. If it is detected it will backup the information on the internal storage, only copying the bytes that are new since the last update.

## Instructions
1. Download and install this library 
2. Check compatibility with your platform
3. Make sure your drives are FAT32 formatted (for now, LittleFS support will be added later)
4. To use internal storage, you need to make sure it is partitioned and formatted correctly 
    * You can do that by flashing the `QSPIFormat` example that can be found in the `STM32H747_System` folder (For Portenta H7/Opta/Giga) or in the `Storage` folder for Portenta C33
    * Open the serial monitor and select answer with "Y" when this appears "Do you want to use partition scheme 1? Y/[n]"
    * Reboot the board


## Features
* Access files and directories on internal storage, SD cards, and USB mass storage devices.
* Read and write data to files.
* Create, remove, and rename files and directories.
* Copy and move files and directories.
* List files and subfolders in a directory.
* Manipulate folders from one storage medium to another. 

## Compatibility

This library is compatible with STM32 and Renesas based Arduino boards. The availability of storage mediums depends on the hardware interfaces.

* Portenta Machine Control: USB and Internal QSPI Flash
* Portenta H7 + Portenta Breakout: USB, SD, and QSPI
* Portenta H7 + Vision Shield: SD and QSPI
* Arduino Giga R1: USB and QSPI
* Arduino Opta: USB and QSPI
* Portenta C33 + Portenta Breakout: USB, SD, and QSPI
* Portenta C33 + Vision Shield: SD and QSPI
