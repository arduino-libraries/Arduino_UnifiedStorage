#ifndef UnifiedStorage_H
#define UnifiedStorage_H


#include "Folder.h"
#include "UFile.h"


#if defined(ARDUINO_PORTENTA_C33)
#include "Types.h"
#include "Arduino.h"
#include "Arduino_POSIXStorage.h"
#endif



    #if defined(ARDUINO_PORTENTA_C33)
        #include "QSPIFlashBlockDevice.h"
        #include <BlockDevice.h>
        #include <MBRBlockDevice.h>
        #include "FATFileSystem.h"
    #elif defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_OPTA)
        #include "QSPIFBlockDevice.h"
        #include "MBRBlockDevice.h"
        #include "FATFileSystem.h"
    #endif 


/**
 * Abstract class representing the common features of the supported storage methods 
 */
class Arduino_UnifiedStorage {
    public:
        /**
         * Initializes the storage.
         * 
         * @return 1 if successful, 0 if failed.
         */
        virtual int begin() = 0;

        /**
          * Initializes the  storage with the specified file system.
          * @param fs The desired file system (FS_FAT or FS_LITTLEFS).
          * @return 1 if successful, 0 if failed.
          */
        virtual int begin(FileSystems fs) = 0;

        /**
         * Unmounts the storage.
         * @return 1 if successful, 0 if failed.
         */
        virtual int unmount() = 0;

        /**
         * Retrieves the root folder of the storage.
         * @return The root folder as a Folder object.
         */
        virtual Folder getRootFolder() = 0;

        /**
         * Formats the storage with the selected file system.
         * @return 1 if successful, 0 if failed.
         */
        virtual int format(FileSystems fs) = 0;

};


#if defined(ARDUINO_PORTENTA_C33) || defined(ARDUINO_PORTENTA_H7_M7)
    #include "USBStorage.h"
    #include "SDStorage.h"
    #include "InternalStorage.h"
#elif defined(ARDUINO_OPTA)
    #include "USBStorage.h"
    #include "InternalStorage.h"
#endif


#endif

