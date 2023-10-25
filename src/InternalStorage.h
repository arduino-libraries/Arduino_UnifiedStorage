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

    static std::vector<Partition> readPartitions();

    static bool partition(); 

    static bool restoreDefaultPartitions();

    private:
        BlockDeviceType * blockDevice;
        MBRBlockDeviceType * mbrBlockDevice;
        FileSystemType * fileSystem;
        int partitionNumber;
        char * partitionName;        
        FileSystems fileSystemType;

};


#endif