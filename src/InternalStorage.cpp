#include "Arduino_UnifiedStorage.h"

InternalStorage::InternalStorage(){
    this -> fs = FS_FAT;
    this -> setQSPIPartition(2);
    this -> setQSPIPartitionName("user");
}

InternalStorage::InternalStorage(int partition, const char * name, uint8_t fs){
    this -> setQSPIPartition(partition);
    this -> setQSPIPartitionName(name);
    this -> fs = fs;
}


int InternalStorage::begin(){
    #if defined(ARDUINO_PORTENTA_C33)
        this -> blockDevice = BlockDevice::get_default_instance();
        this -> userData = new MBRBlockDevice(this->blockDevice, this->partitionNumber);
        if(this -> fs == FS_FAT){
            this -> userDataFileSystem = new FATFileSystem(this->partitionName);
        } else {
            this -> userDataFileSystem = new LittleFileSystem(this->partitionName);
        }
        int err = this -> userDataFileSystem -> mount(userData);
        if(err == 0) return 1;
    #elif defined(ARDUINO_PORTENTA_H7_M7) ||  defined(ARDUINO_OPTA) 
        this -> blockDevice = QSPIFBlockDevice::get_default_instance();
        this -> userData = new mbed::MBRBlockDevice(this->blockDevice, this->partitionNumber);
        if(this -> fs == FS_FAT){
            this -> userDataFileSystem = new mbed::FATFileSystem(this->partitionName);
        } else {
            this -> userDataFileSystem = new mbed::LittleFileSystem(this->partitionName);
        }
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

int InternalStorage::formatFAT(){
    this -> begin();
    this -> unmount();
    this -> fs = FS_FAT;
    #if defined(ARDUINO_PORTENTA_C33)
        this -> userDataFileSystem = new FATFileSystem(this->partitionName);
        return this -> userDataFileSystem -> reformat(this-> userData);
    #elif defined(ARDUINO_PORTENTA_H7_M7) ||  defined(ARDUINO_OPTA) 
        this -> userDataFileSystem =  new mbed::FATFileSystem(this->partitionName);
        return this -> userDataFileSystem -> reformat(this-> userData);
    #endif
}

int InternalStorage::formatLittleFS(){
    this -> begin();
    this -> unmount();
    this -> fs = FS_LITTLEFS;
    #if defined(ARDUINO_PORTENTA_C33)
        this -> userDataFileSystem = new LittleFileSystem(this->partitionName);
        return this -> userDataFileSystem -> reformat(this-> userData);
    #elif defined(ARDUINO_PORTENTA_H7_M7) ||  defined(ARDUINO_OPTA) 
        this -> userDataFileSystem =  new mbed::LittleFileSystem(this->partitionName);
        return this -> userDataFileSystem -> reformat(this-> userData);
    #endif
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