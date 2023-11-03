

#ifndef SDStorage_H
#define SDStorage_H

#include "Arduino_UnifiedStorage.h"

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
         * @return true if successful, false if failed.
         */
        bool begin() override ;

        /**
         * Initializes the SD card storage with the specified file system.
         * 
         * @param fs The desired file system (FS_FAT or FS_LITTLEFS).
         * @return true if successful, false if failed.
         */
        bool begin(FileSystems fs) override;

        /**
         * Unmounts the SD card storage.
         * 
         * @return true if successful, false if failed.
         */
        bool unmount() override;

        /**
         * Retrieves the root folder of the SD card storage.
         * 
         * @return The root folder as a Folder object.
         */
        Folder getRootFolder() override;

        /**
         * Formats the SD card storage with the selected file system.
         * 
         * @return true if successful, false if failed.
         */
        bool format(FileSystems fs) override;
        
    private:
        FileSystems fileSystemType = FS_FAT;
};

#endif
