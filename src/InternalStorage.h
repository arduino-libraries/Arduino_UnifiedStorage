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
     * Constructs an InternalStorage object with default settings.
     * If no partitions are available, it restores the default partitioning scheme (See restoreDefaultPartitions() for more info).
     * If partitions are available, it sets the partition number, file system type, and partition name based on the last partition available.
     * When using the default partitioning scheme the last partition would be the user partition. 
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

    /**
     * Partitions the internal storage according to the partitioning scheme given in the `partitions` parameter erasing the existing partitions
     * @param partitions - vector of structs of type Partition that represents the partitioning scheme
     * @return true if successful, false if failed.
     */
    static bool partition(std::vector<Partition> partitions);


    /**
     * Creates one partition spanning over the whole size of the internal storage drive erasing the existing partitions.
     * @return true if successful, false if failed.
     */
    static bool partition(); 

    /**
     * Restores the default partitioning scheme (1MB FAT32 for Certificates, 5MB FAT32 for OTA, 8MB user storage) to the internal storage drive erasing the existing partitions.
     * @return true if successful, false if failed.
     */
    static bool restoreDefaultPartitions();

    /**
     * Reads the partitioning scheme from the MBR sector of the internal storage drive and returns a vector of structs of type Partition that represents the partitioning scheme
     * @return vector of structs of type Partition 
    */
    static std::vector<Partition> readPartitions();

    private:
        BlockDeviceType * blockDevice;
        MBRBlockDeviceType * mbrBlockDevice;
        FileSystemType * fileSystem;
        int partitionNumber;
        char * partitionName;        
        FileSystems fileSystemType;

};


#endif