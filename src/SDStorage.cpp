#include "SDStorage.h"

#if defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_C33)

SDStorage::SDStorage(){
}

bool SDStorage::begin(){
  return mount(DEV_SDCARD, this->fileSystem, MNT_DEFAULT) == 0;
}

bool SDStorage::begin(FileSystems fs){
  this -> fileSystem = fs;
  return this -> begin();
}

bool SDStorage::unmount(){
    return umount(DEV_SDCARD) == 0;
}

Folder SDStorage::getRootFolder(){
    return Folder("/sdcard");
}

bool SDStorage::format(FileSystems fs){
    int err = 0;
    if(fs == FS_FAT){
        this -> begin();
        this -> unmount();
        this -> fileSystem = FS_FAT;
        err = mkfs(DEV_SDCARD, FS_FAT);
    } else if (fs == FS_LITTLEFS) {
        this -> begin();
        this -> unmount();
        this -> fileSystem = FS_LITTLEFS;
        err =  mkfs(DEV_SDCARD, FS_LITTLEFS);
    }

    return err == 0;
}

#endif