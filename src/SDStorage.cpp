#include "SDStorage.h"



#if defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_C33)

SDStorage::SDStorage(){

}

int SDStorage::begin(){
  return mount(DEV_SDCARD, this->fileSystem, MNT_DEFAULT) == 0;
}

int SDStorage::begin(FileSystems fs){
  this -> fileSystem = fs;
  this -> begin();
}

int SDStorage::unmount(){
  return umount(DEV_SDCARD) == 0;
}

Folder SDStorage::getRootFolder(){
    return Folder("/sdcard");
}

int SDStorage::format(FileSystems fs){
    if(fs == FS_FAT){
        this -> begin();
        this -> unmount();
        this -> fileSystem = FS_FAT;
        return mkfs(DEV_SDCARD, FS_FAT);
    } else if (fs == FS_LITTLEFS) {
        this -> begin();
        this -> unmount();
        this -> fileSystem = FS_LITTLEFS;
        return mkfs(DEV_SDCARD, FS_LITTLEFS);
    }

}


#endif