#include "Arduino_UnifiedStorage.h"

InternalStorage::InternalStorage(){

    #if defined(ARDUINO_PORTENTA_C33)
        this -> setQSPIPartition(2);
    #elif defined(ARDUINO_PORTENTA_H7_M7)
        this -> setQSPIPartition(3);
    #endif

    this -> setQSPIPartitionName("user");
}

InternalStorage::InternalStorage(int partition, const char * name, FileSystems fs){
    this -> setQSPIPartition(partition);
    this -> setQSPIPartitionName(name);
    this -> fs = fs;
}

int InternalStorage::begin(FileSystems fs){
  this -> fs = fs;
  this -> begin();
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
            
            if(this -> userDataFileSystem != nullptr){
                delete(this -> userDataFileSystem);
            } 
            this -> userDataFileSystem = new mbed::FATFileSystem(this->partitionName);
        } else {

            if(this -> userDataFileSystem != nullptr){
                delete(this -> userDataFileSystem);
            } 

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
    return Folder(String("/" + String(this->partitionName)).c_str());
}

void InternalStorage::setQSPIPartition(int partition){
    this -> partitionNumber = partition;
}

void InternalStorage::setQSPIPartitionName(const char * name){
    this -> partitionName = (char *)name;
}

int InternalStorage::format(FileSystems fs){
    this -> begin();
    this -> unmount();
    this -> fs = fs;


    if(fs == FS_FAT){
        #if defined(ARDUINO_PORTENTA_C33)
            this -> userDataFileSystem = new FATFileSystem(this->partitionName);
            return this -> userDataFileSystem -> reformat(this-> userData);
        #elif defined(ARDUINO_PORTENTA_H7_M7) ||  defined(ARDUINO_OPTA) 
            this -> userDataFileSystem =  new mbed::FATFileSystem(this->partitionName);
            return this -> userDataFileSystem -> reformat(this-> userData);
        #endif
    } if (fs == FS_LITTLEFS) {
        #if defined(ARDUINO_PORTENTA_C33)
            this -> userDataFileSystem = new LittleFileSystem(this->partitionName);
            return this -> userDataFileSystem -> reformat(this-> userData);
        #elif defined(ARDUINO_PORTENTA_H7_M7) ||  defined(ARDUINO_OPTA) 
            this -> userDataFileSystem =  new mbed::LittleFileSystem(this->partitionName);
            return this -> userDataFileSystem -> reformat(this-> userData);
        #endif
    }
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