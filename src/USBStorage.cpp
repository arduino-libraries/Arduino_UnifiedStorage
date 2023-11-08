#include "USBStorage.h"
#include "Arduino_POSIXStorage.h"

// The maximum number of attempts to mount the USB drive
constexpr auto MAX_MOUNT_ATTEMPTS = 10;

USBStorage::USBStorage(){
}

bool USBStorage::begin(FileSystems fs){
  this -> fileSystemType = fs;
  return this -> begin();
}

void USBStorage::onConnect(void (* const callbackFunction)()){
    register_hotplug_callback(DEV_USB, callbackFunction);
}

void USBStorage::removeOnConnectCallback(){
    deregister_hotplug_callback(DEV_USB);
}

void USBStorage::onDisconnect(void (* const callbackFunction)()){
    register_unplug_callback(DEV_USB, callbackFunction);
}

void USBStorage::removeOnDisconnectCallback(){
    deregister_unplug_callback(DEV_USB);
}

bool USBStorage::begin(){
    int attempts = 0;
    int err = mount(DEV_USB, this->fileSystemType, MNT_DEFAULT);
    if(err != 0){
        Arduino_UnifiedStorage::debugPrint("[USBStorage][begin][ERROR] Error mounting USB drive: " + String(errno));
    } else {
        Arduino_UnifiedStorage::debugPrint("[USBStorage][begin][INFO] USB drive mounted successfully");
    }

    while (0 != err && attempts < MAX_MOUNT_ATTEMPTS) {
        attempts +=1;
        err = mount(DEV_USB, this->fileSystemType, MNT_DEFAULT);
        if(err != 0){
            Arduino_UnifiedStorage::debugPrint("[USBStorage][mount][ERROR] Error mounting USB drive: " + String(errno));
            Arduino_UnifiedStorage::debugPrint("[USBStorage][mount][INFO] Attempt " + String(attempts) + " of " + String(MAX_MOUNT_ATTEMPTS) + " to mount USB drive");
        } else {
            Arduino_UnifiedStorage::debugPrint("[USBStorage][mount][INFO] USB drive mounted successfully");
        }
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
        Arduino_UnifiedStorage::debugPrint("[USBStorage][unmount][INFO] USB drive unmounted successfully");
        this -> mounted = false;
    } else {
        Arduino_UnifiedStorage::debugPrint("[USBStorage][unmount][ERROR] Error unmounting USB drive: " + String(errno));
    }

    return unmountResult == 0;
}

Folder USBStorage::getRootFolder(){
    return Folder("/usb");
}

bool USBStorage::isMounted(){
    return this->mounted;
}

bool USBStorage::format(FileSystems fs){
    int err = 0;
    Arduino_UnifiedStorage::debugPrint("[USBStorage][format][INFO] Mounting USB drive");
    this->begin();
    Arduino_UnifiedStorage::debugPrint("[USBStorage][format][INFO] Unmounting USB drive");
    this->unmount();
    this->fileSystemType = fs;
    err = mkfs(DEV_USB, fs);
    if(err != 0){
        Arduino_UnifiedStorage::debugPrint("[USBStorage][format][ERROR] Error formatting USB drive: " + String(errno));
    } else {
        Arduino_UnifiedStorage::debugPrint("[USBStorage][format][INFO] USB card formatted successfully");
    }
    return err == 0;
}
