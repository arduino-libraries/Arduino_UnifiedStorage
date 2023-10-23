#include "Arduino_UnifiedStorage.h"

InternalStorage::InternalStorage(){
    this -> setQSPIPartitionName("user");
}


InternalStorage::InternalStorage(int partition, const char * name, FileSystems fs){
    this -> setQSPIPartition(partition);
    this -> setQSPIPartitionName(name);
    this -> fileSystem = fs;
}

bool InternalStorage::begin(FileSystems fs){
  this -> fileSystem = fs;
  return this -> begin();
}

bool InternalStorage::partition(std::vector<Partition> partitions){
    Partitioning::partitionDrive(QSPIFBlockDeviceType::get_default_instance(), partitions);
}



bool InternalStorage::begin(){
        this -> blockDevice = BlockDeviceType::get_default_instance();
        this -> userData = new MBRBlockDeviceType(this->blockDevice, this->partitionNumber);

        if(this -> fileSystem == FS_FAT){
            this -> userDataFileSystem = new FATFileSystemType(this->partitionName);
        } else {
            this -> userDataFileSystem = new LittleFileSystemType(this->partitionName);
        }

        int err = this -> userDataFileSystem -> mount(userData);
        return err == 0;
}

bool InternalStorage::unmount(){
    int err = this -> userDataFileSystem -> unmount();
    return err == 0;
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

bool InternalStorage::format(FileSystems fs){
    this -> begin();
    this -> unmount();
    this -> fileSystem = fs;

    if(fs == FS_FAT){
            this -> userDataFileSystem = new FATFileSystemType(this->partitionName);
            return this -> userDataFileSystem -> reformat(this-> userData)  == 0;
    } if (fs == FS_LITTLEFS) {
            this -> userDataFileSystem =  new LittleFileSystemType(this->partitionName);
            return this -> userDataFileSystem -> reformat(this-> userData)  == 0;
    }

    return false;
}


BlockDeviceType * InternalStorage::getBlockDevice(){
    return this -> blockDevice;
}