
#include <Partitioning.h>

 bool Partitioning::eraseMBRSector(BlockDeviceType * blockDevice)
{
    unsigned char buffer[MBRBlockSize];
    memset(buffer, 0xFF, sizeof(buffer));

    if(blockDevice-> program(buffer, 0, sizeof(buffer)) == 0){
        if(blockDevice -> erase(0, MBRBlockSize) == 0){
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

 bool Partitioning::isPartitionSchemeValid(BlockDeviceType * blockDevice, std::vector<Partition> partitions){
    size_t driveSize = blockDevice -> size() / 1024; // 
    int totalSize = 0;

    for (size_t i = 1; i < partitions.size() + 1; ++i) {
        Partition thisPartition = partitions[i - 1];
        totalSize += thisPartition.size;
    }

    if(totalSize <= driveSize && partitions.size() <= 4){
        return true;
    } else {
        return false;
    }
}

 bool Partitioning::formatPartition(BlockDeviceType * blockDevice, int partitionNumber, FileSystems fileSystemType){
    MBRBlockDeviceType * thisPartition;
    thisPartition = new MBRBlockDeviceType(blockDevice, partitionNumber);
    if(thisPartition != NULL){

        FileSystemType *  thisFileSystem;

        if (fileSystemType == FS_FAT){
            thisFileSystem = new FATFileSystemType(mountPointName);
        } else if (fileSystemType == FS_LITTLEFS){
            thisFileSystem = new LittleFileSystemType(mountPointName);
        }

        if(thisFileSystem->reformat(thisPartition) == 0){
            delete(thisFileSystem);
            delete(thisPartition);
            return true;
        } else {
            return false;
        }
    } else {
         return false;
    }
}

 bool Partitioning::createAndFormatPartitions(BlockDeviceType * blockDevice, std::vector<Partition> partitions){
       
    bool success = false;
    int lastPartitionEnd = 0;

    for (size_t i = 1; i < partitions.size() + 1; ++i) {
        int thisPartitionEnd = (partitions[i - 1].size * 1024) + lastPartitionEnd;

        if(MBRBlockDeviceType::partition(blockDevice, i, MBRPartitionType, lastPartitionEnd, thisPartitionEnd) == 0){
            success = formatPartition(blockDevice, i, partitions[i - 1].fileSystemType);
        } else {
            success = false;
        }

        lastPartitionEnd = thisPartitionEnd;
    }

    return success;
}

 bool Partitioning::partitionDrive(BlockDeviceType * blockDevice, std::vector<Partition> partitions){
    blockDevice -> init();

    if(isPartitionSchemeValid(blockDevice, partitions)){
        if(eraseMBRSector(blockDevice)){
            if(createAndFormatPartitions(blockDevice, partitions)){
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
}

std::vector<Partition> Partitioning::readPartitions(BlockDeviceType * blockDevice){
    std::vector<Partition> partitions;
    
    auto ret = blockDevice->init();
    if (ret) {
        Serial.println("ERROR! Unable to read the Block Device.");
        return partitions;
    }

    auto buffer_size = std::max<uint32_t>(blockDevice->get_program_size(), sizeof(mbrTable));

    if (buffer_size % blockDevice->get_program_size() != 0) {
        buffer_size += blockDevice->get_program_size() - (buffer_size % blockDevice->get_program_size());
    }

    auto buffer = new uint8_t[buffer_size];

    ret = blockDevice->read(buffer, 512 - buffer_size, buffer_size);
    if (ret) {
        Serial.println("ERROR! Unable to read the Master Boot Record");

        delete[] buffer;
        return partitions;
    }

    auto table_start_offset = buffer_size - sizeof(mbrTable);
    auto table = reinterpret_cast<mbrTable*>(&buffer[table_start_offset]);

    if (table->signature[0] != 0x55 || table->signature[1] != 0xAA) {
        Serial.println("MBR Not Found");
        Serial.println("Flash Memory doesn't have partitions.");
        delete[] buffer;
        return partitions;
    }

    auto part { 1u };
    int partitionIndex = 0;
    for (auto const& entry : table->entries) {
        partitionIndex ++;
        Partition partition;
        partition.size = (entry.lbaSize * 4096) >> 10;

        if (entry.type == 0x00) {
            // Skip empty partitions
            continue;
        }


        MBRBlockDeviceType * mbrBlocKDevice = new MBRBlockDeviceType(blockDevice, partitionIndex);
        FATFileSystemType  * fatProbeFileSystem =  new FATFileSystemType("probing");
        LittleFileSystemType * littleFsProbeFilesystem =  new LittleFileSystemType("probing");
    
        if(fatProbeFileSystem -> mount(mbrBlocKDevice) == 0){
            fatProbeFileSystem -> unmount();
            partition.fileSystemType = FS_FAT;
            partitions.push_back(partition);
            
        } else if (littleFsProbeFilesystem -> mount(mbrBlocKDevice) == 0){
            littleFsProbeFilesystem -> unmount();
            partition.fileSystemType = FS_LITTLEFS;
            partitions.push_back(partition);
        }

 
    }

    delete[] buffer;
    return partitions;
}
