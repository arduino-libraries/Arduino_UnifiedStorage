#ifndef InternalStorage_H
#define InternalStorage_H

#include "Arduino_UnifiedStorage.h"
#include "Types.h"


/**
 * Represents internal storage using the Arduino Unified Storage library.
 */
class InternalStorage : public Arduino_UnifiedStorage {
public:
    /**
     * Default constructor for the InternalStorage class.
     */
    InternalStorage();

    /**
     * Constructs an InternalStorage object with the specified partition, name, and file system.
     * 
     * @param partition The partition number.
     * @param name The name of the partition.
     * @param fs The desired file system (FS_FAT or FS_LITTLEFS).
     */
    InternalStorage(int partition, const char *name, FileSystems fs);

    /**
     * Initializes the internal storage.
     * 
     * @return true if successful, false if failed.
     */
    bool begin() override;

    /**
     * Initializes the internal storage with the specified file system.
     * 
     * @param fs The desired file system (FS_FAT or FS_LITTLEFS).
     * @return true if successful, false if failed.
     */
    bool begin(FileSystems fs) override;

    /**
     * Unmounts the internal storage.
     * 
     * @return true if successful, false if failed.
     */
    bool unmount() override;

    /**
     * Retrieves the root folder of the internal storage.
     * 
     * @return The root folder as a Folder object.
     */
    Folder getRootFolder() override;

    /**
     * Sets the QSPI partition number.
     * 
     * @param partition The partition number.
     */
    void setQSPIPartition(int partition);

    /**
     * Sets the QSPI partition name.
     * 
     * @param name The name of the partition.
     */
    void setQSPIPartitionName(const char *name);

    /**
     * Formats the internal storage with the selected file system.
     * 
     * @return true if successful, false if failed.
     */
    bool format(FileSystems fs) override;


    /**
     * Retrieves the block device associated with the internal storage.
     * 
     * @return The block device as a BlockDevice object.
     */

    BlockDeviceType *getBlockDevice();

    static bool partition(std::vector<Partition> partitions);
    // partition() -> one Partition
    // restoreDefaultPartitions();


    private:
        BlockDeviceType * blockDevice;
        MBRBlockDeviceType * userData;
        FileSystemType * userDataFileSystem;
        int partitionNumber = 2;

        char * partitionName ;        
        FileSystems fileSystem;
        bool entireDrive = false;
};


#endif