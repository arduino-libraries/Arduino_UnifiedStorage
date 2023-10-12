
#ifndef UnifiedStorage_H
#define UnifiedStorage_H

#define HAS_SD defined(ARDUINO_PORTENTA_C33) || defined(ARDUINO_PORTENTA_H7_M7) 
#define HAS_USB defined(ARDUINO_PORTENTA_C33) || defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_OPTA) 
#define HAS_QSPI defined(ARDUINO_PORTENTA_C33) || defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_OPTA) || defined(ARDUINO_NICLA_VISION)

#define USES_RENESAS_CORE defined(ARDUINO_PORTENTA_C33)
#define USES_MBED_CORE  defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_OPTA) || defined(ARDUINO_NICLA_VISION)


#include "Arduino.h"
#include "Arduino_POSIXStorage.h"
#include <vector>
#include "Types.h"
#include "Utils.h"
#include "Folder.h"
#include "UFile.h"




#if defined(HAS_USB)
    #include "USBStorage.h"
#endif

#if defined(HAS_SD)
    #include "SDStorage.h"
#endif

#if defined(HAS_QSPI)
    #include "InternalStorage.h"
#endif



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

};





#endif

