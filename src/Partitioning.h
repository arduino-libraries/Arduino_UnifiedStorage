
#include "Arduino.h"
#include "Types.h"
#include "Arduino_POSIXStorage.h"
#include <vector>

constexpr int mbrBlockSize = 4096;
constexpr int mbrPartitionType = 0x0B;
constexpr char * mountPointName = "mountPoint";
constexpr int maximumMBRPartitions = 4;
constexpr int emptyPartitionType = 0x00;
constexpr uint8_t mbrMagicNumbers[] = {0x55, 0xAA};


struct Partition {
    int size;
    FileSystems fileSystemType;
};

struct __attribute__((packed)) mbrEntry {
    uint8_t status;
    uint8_t chsStart[3];
    uint8_t type;
    uint8_t chsStop[3];
    uint32_t lbaOffset;
    uint32_t lbaSize;
};

struct __attribute__((packed)) mbrTable {
    mbrEntry entries[4];
    uint8_t signature[2];
};


class Partitioning{
    public:
        /**
         * This method erases the first block (4096 bytes) of the BlockDevice to delete any already existing MBR partition table
         * @param The BlockDevice on which the MBR sector is situated.
         * @returns True upon success, False on failure
        */
        static bool eraseMBRSector(BlockDeviceType * blockDevice);

        /**
         * This method partitions the BlockDevice according to the partitioning schemme given by the vector of Partition structs
         * @param blockDevice - the BlockDevice which we would like to partition.
         * @param partitions - a vector of Partition structs that represents the partitioning scheme 
         * @returns True upon success, False on failure
        */
        static bool partitionDrive(BlockDeviceType * blockDevice, std::vector<Partition> partitions);

        /**
         * This method reads and unpacks the MBR partition information and returns a list of partitions it can find on the drive
         * @param  blockDevice on which the MBR sector is situated.
         * @returns std::vector of Partition containing size and filesystem information about each partition
        */
        static std::vector<Partition> readPartitions(BlockDeviceType * blockDevice);
    private:
        static bool isPartitionSchemeValid(BlockDeviceType * blockDevice, std::vector<Partition> partitions);
        static bool formatPartition(BlockDeviceType * blockDevice, int partitionNumber, FileSystems fileSystemType);
        static bool createAndFormatPartitions(BlockDeviceType * blockDevice, std::vector<Partition> partitions);
       
};
