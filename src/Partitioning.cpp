#include <Partitioning.h>
#include "Utils.h"
#include "Arduino_UnifiedStorage.h"

bool Partitioning::eraseMBRSector(BlockDeviceType * blockDevice)
{
    unsigned char buffer[mbrBlockSize];
    memset(buffer, 0xFF, sizeof(buffer));

    if(blockDevice-> program(buffer, 0, sizeof(buffer)) == 0){
        Arduino_UnifiedStorage::debugPrint("[Partitioning][eraseMBRSector][INFO] MBR Sector Erased");
        if(blockDevice -> erase(0, mbrBlockSize) == 0){
            Arduino_UnifiedStorage::debugPrint("[Partitioning][eraseMBRSector][INFO] MBR Sector Erased");
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
    size_t totalSize = 0;

    for (size_t i = 1; i < partitions.size() + 1; ++i) {
        Partition thisPartition = partitions[i - 1];

        if(thisPartition.size < 0 && (thisPartition.size & (thisPartition.size - 1)) != 0){
            return false;
        }
        totalSize += thisPartition.size;
    }

    if(totalSize <= driveSize && partitions.size() <= maximumMBRPartitions){
        Arduino_UnifiedStorage::debugPrint("[Partitioning][isPartitioningSchemeValid][INFO] Partitioning Scheme is Valid");
        return true;
    } else {
        Arduino_UnifiedStorage::debugPrint("[Partitioning][isPartitioningSchemeValid][INFO] Partitioning Scheme is Invalid");
        return false;
    }
}

bool Partitioning::formatPartition(BlockDeviceType * blockDevice, int partitionNumber, FileSystems fileSystemType){
    Arduino_UnifiedStorage::debugPrint("[Partitioning][formatPartition][INFO] Formatting partition " + String(partitionNumber));
    MBRBlockDeviceType * thisPartition;
    thisPartition = new MBRBlockDeviceType(blockDevice, partitionNumber);
    if(thisPartition != NULL){

        FileSystemType *  thisFileSystem = NULL;

        if (fileSystemType == FS_FAT){
            thisFileSystem = new FATFileSystemType(mountPointName);
        } else if (fileSystemType == FS_LITTLEFS){
            thisFileSystem = new LittleFileSystemType(mountPointName);
        }

        if(thisFileSystem->reformat(thisPartition) == 0){
            Arduino_UnifiedStorage::debugPrint("[Partitioning][formatPartition][INFO] Partition " + String(partitionNumber) + " formatted successfully");
            delete(thisFileSystem);
            delete(thisPartition);
            return true;
        } else {
            Arduino_UnifiedStorage::debugPrint("[Partitioning][formatPartition][ERROR] Failed to format partition " + String(partitionNumber));
            return false;
        }
    } else {
         Arduino_UnifiedStorage::debugPrint("[Partitioning][formatPartition][ERROR] Failed to create MBRBlockDeviceType for partition " + String(partitionNumber));
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
            Arduino_UnifiedStorage::debugPrint("[Partitioning][INFO] Partition " + String(i) + " created");
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
        blockDevice -> deinit();
        return false;
    }

    if(!eraseMBRSector(blockDevice)){
        blockDevice -> deinit();
        return false;
    }

    if(!createAndFormatPartitions(blockDevice, partitions)){
        blockDevice -> deinit();
        return false;
    }

    blockDevice -> deinit();
    return true;
}

std::vector<Partition> Partitioning::readPartitions(BlockDeviceType * blockDevice){
    std::vector<Partition> partitions;
    
    auto returnCode = blockDevice->init();
    if (returnCode) {
        Arduino_UnifiedStorage::debugPrint("[Partitioning][readPartitions][ERROR] Unable to read the Block Device.");
        return partitions;
    }

    auto buffer_size = std::max<uint32_t>(blockDevice->get_program_size(), sizeof(mbrTable));

    if (buffer_size % blockDevice->get_program_size() != 0) {
        buffer_size += blockDevice->get_program_size() - (buffer_size % blockDevice->get_program_size());
    }

    auto buffer = new uint8_t[buffer_size];

    returnCode = blockDevice->read(buffer, 512 - buffer_size, buffer_size);
    if (returnCode) {
        Arduino_UnifiedStorage::debugPrint("[Partitioning][readPartitions][ERROR] Unable to read the Master Boot Record");

        delete[] buffer;
        return partitions;
    }

    auto table_start_offset = buffer_size - sizeof(mbrTable);
    auto table = reinterpret_cast<mbrTable*>(&buffer[table_start_offset]);
    
    if (table->signature[0] != mbrMagicNumbers[0] || table->signature[1] != mbrMagicNumbers[1]) {
 
        Arduino_UnifiedStorage::debugPrint("[Partitioning][readPartitions][INFO] MBR Not Found - Flash Memory doesn't have partitions.");
        delete[] buffer;
        return partitions;
    }

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

        if (entry.type == emptyPartitionType || partition.size == 0) {
            // Skip empty partitions
            Arduino_UnifiedStorage::debugPrint("[Partitioning][readPartitions][INFO] Partition " + String(partitionIndex) + " is empty, skipping");
            continue;
        }

        MBRBlockDeviceType * mbrBlocKDevice = new MBRBlockDeviceType(blockDevice, partitionIndex);
        FATFileSystemType  * fatProbeFileSystem =  new FATFileSystemType("probing");
        LittleFileSystemType * littleFsProbeFilesystem =  new LittleFileSystemType("probing");
    
        if(fatProbeFileSystem -> mount(mbrBlocKDevice) == 0){
            Arduino_UnifiedStorage::debugPrint("[Partitioning][readPartitions][INFO] Partition " + String(partitionIndex) + " is formatted with FAT file system");
            fatProbeFileSystem -> unmount();
            partition.fileSystemType = FS_FAT;
            partitions.push_back(partition);
            
        } else if (littleFsProbeFilesystem -> mount(mbrBlocKDevice) == 0){
            Arduino_UnifiedStorage::debugPrint("[Partitioning][readPartitions][INFO] Partition " + String(partitionIndex) + " is formatted with LittleFS file system");
            littleFsProbeFilesystem -> unmount();
            partition.fileSystemType = FS_LITTLEFS;
            partitions.push_back(partition);
        } else {
            Arduino_UnifiedStorage::debugPrint("[Partitioning][readPartitions][INFO] Partition " + String(partitionIndex) + " is not formatted with a recognized file system");
        }
 
    }

    delete[] buffer;
    return partitions;
}
