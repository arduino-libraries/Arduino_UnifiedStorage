#include "Arduino_UnifiedStorage.h"

#ifndef USBStorage_H
#define USBStorage_H



static bool usb_available = false;

class USBStorage : public Arduino_UnifiedStorage {
    public:
        USBStorage();
        // Override begin() method for SD card initialization
        int begin() override;

        int unmount() override;

        Folder getRootFolder() override;

        int format() override;

        bool isConnected();
        
        bool isAvailable();

        void checkConnection();



    private:


        bool connected = false;
   
        unsigned long previousMillis; 
        int interval = 500;
};

#endif