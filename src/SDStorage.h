

#ifndef SDStorage_H
#define SDStorage_H

#include "Arduino_UnifiedStorage.h"

#if defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_C33) || !defined(ARDUINO_OPTA)

class SDStorage: public Arduino_UnifiedStorage  {
    public:
        SDStorage();
        // Override begin() method for SD card initialization
        int begin() override ;

        int begin(FileSystems fs) override;

        int unmount() override;

        Folder getRootFolder() override;

        int formatFAT() override;

        int formatLittleFS() override;
    private:
        FileSystems fs = FS_FAT;
        
};

#endif

#endif