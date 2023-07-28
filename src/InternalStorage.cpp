#include "UnifiedStorage.h"

InternalStorage::InternalStorage(){
    #if defined(ARDUINO_PORTENTA_C33)
        this -> blockDevice = BlockDevice::get_default_instance();
        this -> userData = new MBRBlockDevice(this->blockDevice, 2);
        this -> userDataFileSystem = new FATFileSystem(this->partitionName);
    #elif defined(ARDUINO_PORTENTA_H7_M7) ||  defined(ARDUINO_OPTA) 
        this -> blockDevice = QSPIFBlockDevice::get_default_instance();
        this -> userData = new mbed::MBRBlockDevice(this->blockDevice, this->partitionNumber);
        this -> userDataFileSystem =  new mbed::FATFileSystem(this->partitionName);
    #endif
}

int InternalStorage::begin(){
    #if defined(ARDUINO_PORTENTA_C33)
        int err = this -> userDataFileSystem -> mount(userData);
        if(err == 0) return 1;
    #elif defined(ARDUINO_PORTENTA_H7_M7) ||  defined(ARDUINO_OPTA) 
        int err = this -> userDataFileSystem -> mount(this -> userData);
        if(err == 0) return 1;
    #endif
}

int InternalStorage::unmount(){
     int err = this -> userDataFileSystem -> unmount();
     if(err == 0) return 1;
}

Folder InternalStorage::getRootFolder(){
 return Folder("/user");
}


void InternalStorage::setQSPIPartition(int partition){
    this -> partitionNumber = partition;
}

void InternalStorage::setQSPIPartitionName(const char * name){
    this -> partitionName = (char *)name;
}

int InternalStorage::format(){
    return this -> userDataFileSystem -> reformat(this -> userData);

}

#if defined(ARDUINO_PORTENTA_C33)
BlockDevice * InternalStorage::getBlockDevice(){
    return this -> blockDevice;
}
#endif


#if defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_OPTA) 
              mbed::BlockDevice *  InternalStorage::getBlockDevice(){
                return this -> blockDevice;
              }
 
#endif