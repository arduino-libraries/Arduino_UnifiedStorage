#include "USBStorage.h"

#if defined(ARDUINO_PORTENTA_H7_M7)
    #include <Arduino_USBHostMbed5.h>
#endif

#define MAX_TRIES 10

bool USBStorage::usb_available = false;

USBStorage::USBStorage(){
 #if defined(ARDUINO_PORTENTA_C33)
         register_hotplug_callback(DEV_USB,  [](){
            usb_available = !usb_available;

        });
#endif
}


int USBStorage::begin(FileSystems fs){
  this -> fs = fs;
  this -> begin();
}

int USBStorage::begin(){

 

    int attempts = 0;
    int err = mount(DEV_USB, this->fs, MNT_DEFAULT);

    while (0 != err && attempts < MAX_TRIES) {
        attempts +=1;
        err = mount(DEV_USB, this->fs, MNT_DEFAULT);
        delay(1000);
    }

    if(err == 0){
        this -> connected = true;
    } else {
        this -> connected = false;
    }

    return err == 0;
}


int USBStorage::unmount(){
  auto unmountResult = umount(DEV_USB);
    

  if(unmountResult == 0){
      this -> connected = false;
  } else {
  }

  return unmountResult == 0;
}

Folder USBStorage::getRootFolder(){
    return Folder("/usb");
}


bool USBStorage::isAvailable(){
    return usb_available;
}

bool USBStorage::isConnected(){
    return this -> connected;
}

void USBStorage::checkConnection(){
    #if defined(ARDUINO_PORTENTA_H7_M7)
    USBHost * host;
    USBDeviceConnected * dev;
    unsigned long currentMillis = millis();
    boolean found = false;

    if (currentMillis - previousMillis >= interval) {
        this -> previousMillis = currentMillis;

            host = USBHost::getHostInst();

        
                    if ((dev = host->getDevice(0)) != NULL) {
                         usb_available = true;
                           found = true;
                        } else {
                             usb_available = false;
                        }
    }
        
                
         

    #endif
}



int USBStorage::formatFAT(){
    this -> begin();
    this -> unmount();
    this -> fs = FS_FAT;
    return mkfs(DEV_USB, FS_FAT);
}

int USBStorage::formatLittleFS(){
    this -> begin();
    this -> unmount();
    this -> fs = FS_LITTLEFS;
    return mkfs(DEV_USB, FS_LITTLEFS);
}
