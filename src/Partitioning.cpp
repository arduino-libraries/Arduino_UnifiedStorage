
#include <Partitioning.h>

bool Partitioning::eraseMBRSector(BlockDeviceType * blockDevice)
{
    unsigned char buffer[mbrBlockSize];
    memset(buffer, 0xFF, sizeof(buffer));

    if(blockDevice-> program(buffer, 0, sizeof(buffer)) == 0){
        if(blockDevice -> erase(0, mbrBlockSize) == 0){
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

    if(totalSize <= driveSize && partitions.size() <= maximumMBRPartitions){
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
       
    bool success = true; // initialize to true
    int lastPartitionEnd = 0;

    for (size_t i = 1; i < partitions.size() + 1; ++i) {
        auto currentPartition = partitions[i - 1];
        int thisPartitionEnd = (currentPartition.size * 1024) + lastPartitionEnd;

        if(MBRBlockDeviceType::partition(blockDevice, i, mbrPartitionType, lastPartitionEnd, thisPartitionEnd) == 0){
            success &= formatPartition(blockDevice, i, currentPartition.fileSystemType); // use bitwise AND to check if all partitions are successful
        } else {
            success = false;
        }

        lastPartitionEnd = thisPartitionEnd;
    }

    return success;
}

bool Partitioning::partitionDrive(BlockDeviceType * blockDevice, std::vector<Partition> partitions){
    blockDevice -> init();

    if(!isPartitionSchemeValid(blockDevice, partitions)){
        return false;
    }

    if(!eraseMBRSector(blockDevice)){
        return false;
    }

    if(!createAndFormatPartitions(blockDevice, partitions)){
        return false;
    }

    return true;
}

std::vector<Partition> Partitioning::readPartitions(BlockDeviceType * blockDevice){
    std::vector<Partition> partitions;
    
    auto returnCode = blockDevice->init();
    if (returnCode) {
        debugPrint("ERROR! Unable to read the Block Device.");
        return partitions;
    }

    auto buffer_size = std::max<uint32_t>(blockDevice->get_program_size(), sizeof(mbrTable));

    if (buffer_size % blockDevice->get_program_size() != 0) {
        buffer_size += blockDevice->get_program_size() - (buffer_size % blockDevice->get_program_size());
    }

    auto buffer = new uint8_t[buffer_size];

    returnCode = blockDevice->read(buffer, 512 - buffer_size, buffer_size);
    if (returnCode) {
        debugPrint("ERROR! Unable to read the Master Boot Record");

        delete[] buffer;
        return partitions;
    }


    auto table_start_offset = buffer_size - sizeof(mbrTable);
    auto table = reinterpret_cast<mbrTable*>(&buffer[table_start_offset]);
    
    if (table->signature[0] != mbrMagicNumbers[0] || table->signature[1] != mbrMagicNumbers[1]) {
 
        debugPrint("MBR Not Found");
        debugPrint("Flash Memory doesn't have partitions.");
        delete[] buffer;
        return partitions;
    }

    auto part { 1u };
    int partitionIndex = 0;
    for (auto const& entry : table->entries) {
        partitionIndex ++;
        Partition partition;

        /*This code calculates the size of a partition in kilobytes.
        It takes the Logical Block Address (LBA) size of the partition, 
        multiplies it by 4096 (the size of a block in bytes),
        and then shifts the result 10 bits to the right to convert it to kilobytes. 
        */
       partition.size = (entry.lbaSize * 4096) >> 10;

        if (entry.type == emptyPartitionType) {
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
