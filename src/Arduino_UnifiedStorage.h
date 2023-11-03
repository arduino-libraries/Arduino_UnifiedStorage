#ifndef UnifiedStorage_H
#define UnifiedStorage_H


#include "Arduino.h"
#include "Arduino_POSIXStorage.h"
#include "Boards.h"


#include "Types.h"
#include "Partitioning.h"

#include "Folder.h"
#include "UFile.h"



/**
 * Abstract class representing the common features of the supported storage methods 
 */
class Arduino_UnifiedStorage {
    public:
        /**
         * Initializes the storage.
         * 
         * @return true if successful, false if failed.
         */
        virtual bool begin() = 0;

        /**
          * Initializes the  storage with the specified file system.
          * @param fs The desired file system (FS_FAT or FS_LITTLEFS).
          * @return true if successful, false if failed.
          */
        virtual bool begin(FileSystems fs) = 0;

        /**
         * Unmounts the storage.
         * @return true if successful, false if failed.
         */
        virtual bool unmount() = 0;

        /**
         * Retrieves the root folder of the storage.
         * @return The root folder as a Folder object.
         */
        virtual Folder getRootFolder() = 0;

        /**
         * Formats the storage with the selected file system.
         * @return true if successful, false if failed.
         */
        virtual bool format(FileSystems fs) = 0;


        static bool debuggingModeEnabled;

        static void debugPrint(String message);

        static void testPrint(String message);

};

    #if defined(HAS_USB)
        #include "USBStorage.h"
    #endif

    #if defined(HAS_SD)
        #include "SDStorage.h"
    #endif

    #if defined(HAS_QSPI)
        #include "InternalStorage.h"
    #endif

#endif
