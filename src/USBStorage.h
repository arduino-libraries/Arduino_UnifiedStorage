#include "Arduino_UnifiedStorage.h"

#ifndef USBStorage_H
#define USBStorage_H

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

        void disconnect();


    private:
        void usbCallback();
        bool connected = false;
        bool available = false;
        bool hasChanged = false;
        bool isIdentical = false;
        unsigned long previousMillis; 
        int interval = 500;
};

#endif