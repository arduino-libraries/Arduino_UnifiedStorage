#include "SDStorage.h"

#if defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_C33)

SDStorage::SDStorage(){
}

bool SDStorage::begin(){
    int err = mount(DEV_SDCARD, this->fileSystemType, MNT_DEFAULT);
    if(err != 0){
        Arduino_UnifiedStorage::debugPrint("[SDCard][begin][ERROR] Error mounting SD card: " + String(errno));
        return false;
    } else {
        Arduino_UnifiedStorage::debugPrint("[SDCard][begin][INFO] SD card mounted successfully");
    }

    return err == 0;
}

bool SDStorage::begin(FileSystems fs){
  this -> fileSystemType = fs;
  return this -> begin();
}

bool SDStorage::unmount(){
    int err = umount(DEV_SDCARD);
    if(err != 0){
        Arduino_UnifiedStorage::debugPrint("[SDCard][unmount][ERROR] Error unmounting SD card: " + String(errno));
    }
    return err == 0;
}

Folder SDStorage::getRootFolder(){
    return Folder("/sdcard");
}

bool SDStorage::format(FileSystems fs){
    int err = 0;
    Arduino_UnifiedStorage::debugPrint("[SDCard][format][INFO] Mounting SD drive");
    this->begin();
    Arduino_UnifiedStorage::debugPrint("[SDCard][format][INFO] Unmounting SD drive");
    this->unmount();
    this->fileSystemType = fs;
    err = mkfs(DEV_SDCARD, fs);
    if(err != 0){
        Arduino_UnifiedStorage::debugPrint("[SDCard][format][ERROR] Error formatting SD card: " + String(errno));
    } else {
        Arduino_UnifiedStorage::debugPrint("[SDCard][format][INFO] SD card formatted successfully");
    }
    return err == 0;
}

#endif