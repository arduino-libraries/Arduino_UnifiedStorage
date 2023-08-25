#include "USBStorage.h"

#if defined(ARDUINO_PORTENTA_H7_M7)
    #include <Arduino_USBHostMbed5.h>
#endif

#define MAX_TRIES 10

USBStorage::USBStorage(){
 #if defined(ARDUINO_PORTENTA_C33)
         register_hotplug_callback(DEV_USB,  [](){
            available = !available;

        });
#endif
}

int USBStorage::begin(){

 

    int attempts = 0;
    int err = mount(DEV_USB, FS_FAT, MNT_DEFAULT);

    while (0 != err && attempts < MAX_TRIES) {
        attempts +=1;
        err = mount(DEV_USB, FS_FAT, MNT_DEFAULT);
        Serial.println(errno);
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
    return available;
}

bool USBStorage::isConnected(){
    return this -> connected;
}


/*


void USBStorage::checkConnection(){
    #if defined(ARDUINO_PORTENTA_H7_M7)
    USBHost * host;
    USBDeviceConnected * dev;
    unsigned long currentMillis = millis();
    boolean found = false;

    if (currentMillis - previousMillis >= interval) {
        this -> previousMillis = currentMillis;
            host = USBHost::getHostInst();
            if(host->getDevice(0) != NULL){
                this->available = true;
            } else {
                this->available = false;
            }
    }
    #endif
}
*/


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
                         available = true;

                        uint8_t ceva =  dev->getNbIntf();
                           found = true;
                        } else {
                             available = false;
                        }
    }
        
                
         

    #endif
}

int USBStorage::format(){
    return mkfs(DEV_USB, FS_FAT);
}