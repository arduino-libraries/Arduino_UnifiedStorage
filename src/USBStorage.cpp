#include "USBStorage.h"

#if defined(ARDUINO_PORTENTA_H7_M7)
    #include <Arduino_USBHostMbed5.h>
#endif

#define MAX_TRIES 10

USBStorage::USBStorage(){

}

void USBStorage::usbCallback(){
    /*
    if(this-> available){
        this -> available = false;
    } else {
        this -> available = true; 
    }
    */
}

int USBStorage::begin(){

    #if defined(ARDUINO_PORTENTA_C33)
        register_hotplug_callback(DEV_USB, this->usbCallback);
    #endif

    int attempts = 0;
    int err = mount(DEV_USB, FS_FAT, MNT_DEFAULT);

    while (0 != err && attempts < MAX_TRIES) {
        attempts +=1;
        err = mount(DEV_USB, FS_FAT, MNT_DEFAULT);
        Serial.println(errno);
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
    return this -> available;
}

bool USBStorage::isConnected(){
    return this -> connected;
}

void USBStorage::disconnect(){


    USBHost * host;
    USBDeviceConnected * dev;
     host = USBHost::getHostInst();
     host -> getDevice(0) -> disconnect();

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
                         this->available = true;

                        uint8_t ceva =  dev->getNbIntf();
                        /*
                
                        Serial.println(dev->getName(ceva));
                        Serial.println(dev->getVid());
                        Serial.println(dev->getPid());
                        Serial.println(dev->getClass());
                        Serial.println(dev->getSubClass());
                 */
                           found = true;
                        } else {
                             this->available = false;
                        }
    }
        
                
         

    #endif
}

int USBStorage::format(){
    return mkfs(DEV_USB, FS_FAT);
}