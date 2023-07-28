#include "SDStorage.h"



#if defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_C33)

SDStorage::SDStorage(){

}

int SDStorage::begin(){
  return mount(DEV_SDCARD, FS_FAT, MNT_DEFAULT) == 0;
}

int SDStorage::unmount(){
  return umount(DEV_SDCARD) == 0;
}

Folder SDStorage::getRootFolder(){
    return Folder("/sdcard");
}

int SDStorage::format(){
    return mkfs(DEV_SDCARD, FS_FAT);
}

#endif