#include "Arduino_UnifiedStorage.h"

InternalStorage::InternalStorage(){
    std::vector<Partition> partitionsAvailable = Partitioning::readPartitions(QSPIFBlockDeviceType::get_default_instance());
    if(partitionsAvailable.size() == 0){

        //Arduino_UnifiedStorage::debugPrint("[InternalStorage][INFO] No partitions found, restoring default partitions");
        restoreDefaultPartitions();
    } else {
        int lastPartitionNumber = partitionsAvailable.size();
        FileSystems lastPartitionFileSystem = partitionsAvailable.back().fileSystemType;
        //Arduino_UnifiedStorage::debugPrint("[InternalStorage][INFO] Found " + String(lastPartitionNumber) + " partitions, using last partition as internal storage");

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
    return Partitioning::partitionDrive(QSPIFBlockDeviceType::get_default_instance(), partitions);
}

bool InternalStorage::partition(){
    return Partitioning::partitionDrive(QSPIFBlockDeviceType::get_default_instance(), {{QSPI_STORAGE_SIZE, FS_LITTLEFS}});
}

bool InternalStorage::restoreDefaultPartitions(){
    return Partitioning::partitionDrive(QSPIFBlockDeviceType::get_default_instance(), {
        {1024, FS_FAT}, // 1 MB for certificates
        {5120, FS_FAT}, // 5 MB for OTA firmware updates
        {8192, FS_LITTLEFS} // 8 MB for user data
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
            Arduino_UnifiedStorage::debugPrint("[InternalStorage][begin][INFO] Mounting partition " + String(this->partitionNumber) + " as FAT");
        } else {
            this -> fileSystem = new LittleFileSystemType(this->partitionName);
            Arduino_UnifiedStorage::debugPrint("[InternalStorage][begin][INFO] Mounting partition " + String(this->partitionNumber) + " as LittleFS");
        }

        int err = this -> fileSystem -> mount(mbrBlockDevice);
        if(err!=0){
            Arduino_UnifiedStorage::debugPrint("[InternalStorage][ERROR] Could not mount partition " + String(this->partitionNumber) + " as " + prettyPrintFileSystemType(this->fileSystemType) + ", error code: " + String(errno));
        }
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
            int err = this -> fileSystem -> reformat(this-> mbrBlockDevice);
            if(err != 0){
                Arduino_UnifiedStorage::debugPrint("[InternalStorage][format][ERROR] Error formatting partition " + String(this->partitionNumber) + " as FAT: " + String(errno));
            } 
            return err == 0;
    } if (fs == FS_LITTLEFS) {
            this -> fileSystem =  new LittleFileSystemType(this->partitionName);
            int err = this -> fileSystem -> reformat(this-> mbrBlockDevice);
            if(err != 0){
                Arduino_UnifiedStorage::debugPrint("[InternalStorage][format][ERROR] Error formatting partition " + String(this->partitionNumber) + " as LittleFS: " + String(errno));
            }
            return err  == 0;
    }

    return false;
}

BlockDeviceType * InternalStorage::getBlockDevice(){
    return this -> blockDevice;
}
