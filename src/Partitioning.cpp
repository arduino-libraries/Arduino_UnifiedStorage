
#include <Partitioning.h>

 bool Partitioning::eraseMBRSector(BlockDeviceType * bd)
{
    #define MBR_BLOCK_SIZE 4096
    unsigned char buffer[MBR_BLOCK_SIZE];
    memset(buffer, 0xFF, sizeof(buffer));

    if(bd-> program(buffer, 0, sizeof(buffer)) == 0){
        if(bd -> erase(0, MBR_BLOCK_SIZE) == 0){
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

 bool Partitioning::isPartitionSchemeValid(BlockDeviceType * bd, std::vector<Partition> partitions){
    size_t driveSize = bd -> size() / 1024;
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

 bool Partitioning::formatPartition(BlockDeviceType * bd, int partitionNumber, FileSystems fs){
    #define DEFAULT_FS_LABEL "label"
    MBRBlockDeviceType * thisPartition;
    thisPartition = new MBRBlockDeviceType(bd, partitionNumber);
    if(thisPartition != NULL){
        FileSystemType *  thisFileSystem;

        if (fs == FS_FAT){
            thisFileSystem = new FATFileSystemType(DEFAULT_FS_LABEL);
        } else if (fs == FS_LITTLEFS){
            thisFileSystem = new LittleFileSystemType(DEFAULT_FS_LABEL);
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

 bool Partitioning::createAndFormatPartitions(BlockDeviceType * bd, std::vector<Partition> partitions){
       
    bool success = false;
    int lastPartitionEnd = 0;

    for (size_t i = 1; i < partitions.size() + 1; ++i) {
        int thisPartitionEnd = (partitions[i - 1].size * 1024) + lastPartitionEnd;

        if(MBRBlockDeviceType::partition(bd, i , 0x0B, lastPartitionEnd, thisPartitionEnd) == 0){
            success = formatPartition(bd, i, partitions[i - 1].fs);
        } else {
            success = false;
        }

        lastPartitionEnd = thisPartitionEnd;
    }

    return success;
}

 bool Partitioning::partitionDrive(BlockDeviceType * bd, std::vector<Partition> partitions){
    bd -> init();

    if(isPartitionSchemeValid(bd, partitions)){
        if(eraseMBRSector(bd)){
            if(createAndFormatPartitions(bd, partitions)){
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
   