

#ifndef SDStorage_H
#define SDStorage_H

#include "Arduino_UnifiedStorage.h"

#if defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_C33) || !defined(ARDUINO_OPTA)

/**
 * Represents an SD card storage using the Arduino Unified Storage library.
 */
class SDStorage: public Arduino_UnifiedStorage  {
    public:
        /**
        * Default constructor for the SDStorage class.
        */
        SDStorage();

        /**
        * Initializes the SD card storage.
        * 
        * @return 1 if successful, 0 if failed.
        */
        int begin() override ;

        /**
         * Initializes the SD card storage with the specified file system.
         * 
         * @param fs The desired file system (FS_FAT or FS_LITTLEFS).
         * @return 1 if successful, 0 if failed.
        */
        int begin(FileSystems fs) override;

        /**
         * Unmounts the SD card storage.
         * 
         * @return 1 if successful, 0 if failed.
        */
        int unmount() override;

        /**
         * Retrieves the root folder of the SD card storage.
         * 
         * @return The root folder as a Folder object.
        */
        Folder getRootFolder() override;

        /**
         * Formats the SD card storage with the FAT file system.
         * 
         * @return 1 if successful, 0 if failed.
         */
        int formatFAT() override;
        
        /**
         * Formats the SD card storage with the LittleFS file system.
         * 
         * @return 1 if successful, 0 if failed.
        */

        int formatLittleFS() override;
    private:
        FileSystems fs = FS_FAT;
        
};

#endif

#endif