
#include "Arduino.h"
#include "Types.h"
#include "Arduino_POSIXStorage.h"
#include <vector>

struct Partition {
    int size;
    FileSystems fs;
};

class Partitioning{
    public:
        static bool eraseMBRSector(BlockDeviceType * bd);
        static bool partitionDrive(BlockDeviceType * bd, std::vector<Partition> partitions);
    private:
        static bool isPartitionSchemeValid(BlockDeviceType * bd, std::vector<Partition> partitions);
        static bool formatPartition(BlockDeviceType * bd, int partitionNumber, FileSystems fs);
        static bool createAndFormatPartitions(BlockDeviceType * bd, std::vector<Partition> partitions);
       
};
