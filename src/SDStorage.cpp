#include "SDStorage.h"



#if defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_C33)

SDStorage::SDStorage(){

}

int SDStorage::begin(){
  return mount(DEV_SDCARD, this->fs, MNT_DEFAULT) == 0;
}

int SDStorage::begin(FileSystems fs){
  this -> fs = fs;
  this -> begin();
}

int SDStorage::unmount(){
  return umount(DEV_SDCARD) == 0;
}

Folder SDStorage::getRootFolder(){
    return Folder("/sdcard");
}

int SDStorage::formatFAT(){
    this -> begin();
    this -> unmount();
    this -> fs = FS_FAT;
    return mkfs(DEV_SDCARD, FS_FAT);
}

int SDStorage::formatLittleFS(){
    this -> begin();
    this -> unmount();
    this -> fs = FS_LITTLEFS;
    return mkfs(DEV_SDCARD, FS_LITTLEFS);
}


#endif