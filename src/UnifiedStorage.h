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

class UnifiedStorage {
    public:
        virtual int begin() = 0;

        virtual int unmount() = 0;

        virtual Folder getRootFolder() = 0;

        virtual int format() = 0;
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

