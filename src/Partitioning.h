
#ifndef PARTITIONING_H
#define PARTITIONING_H

#include "Arduino.h"
#include "Types.h"
#include "Arduino_POSIXStorage.h"
#include <vector>


constexpr int mbrBlockSize = 4096;
constexpr int mbrPartitionType = 0x0B;
constexpr const char * mountPointName = "mountPoint";
constexpr int maximumMBRPartitions = 4;
constexpr int emptyPartitionType = 0x00;
constexpr uint8_t mbrMagicNumbers[] = {0x55, 0xAA};


struct Partition {
    int size;
    FileSystems fileSystemType;
};

struct __attribute__((packed)) mbrEntry {
    uint8_t status;
    /**
     * @brief The starting CHS (Cylinder-Head-Sector) address of the partition.
     */
    uint8_t chsStart[3];
    uint8_t type;
    /**
     * @brief The ending CHS (Cylinder-Head-Sector) address of the partition.
     */
    uint8_t chsStop[3];
    
    /**
     * @brief The logical block address offset of the partition.
     */
    uint32_t lbaOffset;
    /**
     * @brief The size of each Logical Block Address (LBA) in bytes.
     */
    uint32_t lbaSize;
};

struct __attribute__((packed)) mbrTable {
    mbrEntry entries[4];
    uint8_t signature[2];
};


class Partitioning{
    public:
        /**
         * Erases the first block (4096 bytes) of the BlockDevice to delete any already existing MBR partition table
         * @param The BlockDevice on which the MBR sector is situated.
         * @returns True upon success, False on failure
        */
        static bool eraseMBRSector(BlockDeviceType * blockDevice);

        /**
         * Partitions the BlockDevice according to the partitioning schemme given by the vector of Partition structs
         * @param blockDevice - the BlockDevice which we would like to partition.
         * @param partitions - a vector of Partition structs that represents the partitioning scheme 
         * @returns True upon success, False on failure
        */
        static bool partitionDrive(BlockDeviceType * blockDevice, std::vector<Partition> partitions);

        /**
         * Reads and unpacks the MBR partition information and returns a list of partitions it can find on the drive
         * @param  blockDevice on which the MBR sector is situated.
         * @returns std::vector of Partition containing size and filesystem information about each partition
        */
        static std::vector<Partition> readPartitions(BlockDeviceType * blockDevice);
    private:
        /**
         * Checks if the given partition scheme is valid for the specified block device.
         * It does that by checking if the sum of the partition sizes is equal to the size of the block device and
         * by ensuring that there are a maximum of 4 partitions.
         *
         * @param blockDevice The block device to check the partition scheme against.
         * @param partitions The partition scheme to check for validity.
         * @return True if the partition scheme is valid for the block device, false otherwise.
         */
        static bool isPartitionSchemeValid(BlockDeviceType * blockDevice, std::vector<Partition> partitions);
        
        
        /**
         * Formats the specified partition of the given block device with the specified file system type.
         *
         * @param blockDevice The block device to format the partition on.
         * @param partitionNumber The number of the partition to format.
         * @param fileSystemType The file system type to format the partition with.
         * @return True if the partition was formatted successfully, false otherwise.
         */
        static bool formatPartition(BlockDeviceType * blockDevice, int partitionNumber, FileSystems fileSystemType);
        
        /**
         * Creates and formats partitions on the specified block device.
         * The partitioning splits the block device into partitions of the specified sizes and formats them with the specified file system types.
         *
         * @param blockDevice Pointer to the block device to partition and format.
         * @param partitions Vector of Partition objects representing the partitions to create and format.
         * @return True if all partitions were successfully created and formatted, false otherwise.
         */
        static bool createAndFormatPartitions(BlockDeviceType * blockDevice, std::vector<Partition> partitions);
       
};

#endif