#include "USBStorage.h"

#if defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_OPTA)
    #include <Arduino_USBHostMbed5.h>
#endif

// The maximum number of attempts to mount the USB drive
constexpr auto MAX_MOUNT_ATTEMPTS = 10;


USBStorage::USBStorage(){
}

bool USBStorage::begin(FileSystems fs){
  this -> fileSystem = fs;
  return this -> begin();
}

void USBStorage::registerHotplugCallback(void (* const callbackFunction)()){
    register_hotplug_callback(DEV_USB, callbackFunction);
}

void USBStorage::deregisterHotplugCallback(){
    deregister_hotplug_callback(DEV_USB);
}

void USBStorage::registerUnplugCallback(void (* const callbackFunction)()){
    register_unplug_callback(DEV_USB, callbackFunction);
}

void USBStorage::deregisterUnplugCallback(){
    deregister_unplug_callback(DEV_USB);
}


bool USBStorage::begin(){
    int attempts = 0;
    int err = mount(DEV_USB, this->fileSystem, MNT_DEFAULT);

    while (0 != err && attempts < MAX_MOUNT_ATTEMPTS) {
        attempts +=1;
        err = mount(DEV_USB, this->fileSystem, MNT_DEFAULT);
        delay(1000);
    }

    if(err == 0){
        this -> mounted = true;
    } else {
        this -> mounted = false;
    }

    return err == 0;


}

bool USBStorage::unmount(){
  auto unmountResult = umount(DEV_USB);
    

  if(unmountResult == 0){
      this -> mounted = false;
  }

    return unmountResult == 0;
}

Folder USBStorage::getRootFolder(){
    return Folder("/usb");
}


bool USBStorage::isMounted(){
    return this -> mounted;
}

bool  USBStorage::format(FileSystems fs){
    
    if(fs == FS_FAT){
        this -> begin();
        this -> unmount();
        this -> fileSystem = FS_FAT;
        return mkfs(DEV_USB, FS_FAT) == 0;
    } else if(FS_LITTLEFS) {
        this -> begin();
        this -> unmount();
        this -> fileSystem = FS_LITTLEFS;
        return mkfs(DEV_USB, FS_LITTLEFS) == 0;
    }

}

