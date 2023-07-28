

#ifndef SDStorage_H
#define SDStorage_H

#include "UnifiedStorage.h"

#if defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_C33) || !defined(ARDUINO_OPTA)

class SDStorage: public UnifiedStorage  {
    public:
        SDStorage();
        // Override begin() method for SD card initialization
        int begin() override ;

        int unmount() override;

        Folder getRootFolder() override;

        int format() override;
};

#endif

#endif