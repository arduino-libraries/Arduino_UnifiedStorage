#include "Arduino_UnifiedStorage.h"

InternalStorage::InternalStorage(){
    std::vector<Partition> partitionsAvailable = Partitioning::readPartitions(QSPIFBlockDeviceType::get_default_instance());
    if(partitionsAvailable.size() == 0){
        restoreDefaultPartitions();
    } else {
        int lastPartitionNumber = partitionsAvailable.size();
        FileSystems lastPartitionFileSystem = partitionsAvailable.back().fileSystemType;

        this -> partitionNumber = lastPartitionNumber;
        this -> fileSystemType = lastPartitionFileSystem;
        this -> partitionName = (char *)"internal"; 
    }
}


InternalStorage::InternalStorage(int partition, const char * name, FileSystems fileSystemType){
    this -> partitionNumber = partition;
    this -> partitionName = (char *)name;
    this -> fileSystemType = fileSystemType;
}

bool InternalStorage::begin(FileSystems fileSystemType){
  this -> fileSystemType = fileSystemType;
  return this -> begin();
}

bool InternalStorage::partition(std::vector<Partition> partitions){
    Partitioning::partitionDrive(QSPIFBlockDeviceType::get_default_instance(), partitions);
}

bool InternalStorage::partition(){
    Partitioning::partitionDrive(QSPIFBlockDeviceType::get_default_instance(), {{QSPI_STORAGE_SIZE, FS_LITTLEFS}});
}


bool InternalStorage::restoreDefaultPartitions(){
    Partitioning::partitionDrive(QSPIFBlockDeviceType::get_default_instance(), {
        {1024, FS_FAT},
        {5120, FS_FAT},
        {8192, FS_LITTLEFS}
    });
}

std::vector<Partition> InternalStorage::readPartitions(){
    return Partitioning::readPartitions(QSPIFBlockDeviceType::get_default_instance());
}

bool InternalStorage::begin(){
 
        this -> blockDevice = BlockDeviceType::get_default_instance();
        this -> mbrBlockDevice = new MBRBlockDeviceType(this->blockDevice, this->partitionNumber);

        if(this -> fileSystemType == FS_FAT){
            this -> fileSystem = new FATFileSystemType(this->partitionName);
        } else {
            this -> fileSystem = new LittleFileSystemType(this->partitionName);
        }

        int err = this -> fileSystem -> mount(mbrBlockDevice);
        return err == 0;
}

bool InternalStorage::unmount(){
    int err = this -> fileSystem -> unmount();
    return err == 0;
}

Folder InternalStorage::getRootFolder(){
    return Folder(String("/" + String(this->partitionName)).c_str());
}

bool InternalStorage::format(FileSystems fs){
    this -> begin();
    this -> unmount();
    this -> fileSystemType = fs;

    if(fs == FS_FAT){
            this -> fileSystem = new FATFileSystemType(this->partitionName);
            return this -> fileSystem -> reformat(this-> mbrBlockDevice)  == 0;
    } if (fs == FS_LITTLEFS) {
            this -> fileSystem =  new LittleFileSystemType(this->partitionName);
            return this -> fileSystem -> reformat(this-> mbrBlockDevice)  == 0;
    }

    return false;
}


BlockDeviceType * InternalStorage::getBlockDevice(){
    return this -> blockDevice;
}