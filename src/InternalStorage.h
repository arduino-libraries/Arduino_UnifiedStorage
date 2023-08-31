

#ifndef InternalStorage_H
#define InternalStorage_H

#include "Arduino_UnifiedStorage.h"




class InternalStorage : public Arduino_UnifiedStorage {


    public:
        InternalStorage();
        // Override begin() method for SD card initialization
        InternalStorage(int partition, const char * name, FileSystems fs);

        int begin() override;

        int begin(FileSystems fs) override;

        int unmount() override;

        Folder getRootFolder() override;

        void setQSPIPartition(int partition);

        void setQSPIPartitionName(const char * name);

        int formatFAT();

        int formatLittleFS();

        
        #if defined(ARDUINO_PORTENTA_C33)
            BlockDevice * getBlockDevice();
        #elif defined(ARDUINO_PORTENTA_H7_M7)  ||  defined(ARDUINO_OPTA)
            mbed::BlockDevice  * getBlockDevice();
        #endif


    private:
        #if defined(ARDUINO_PORTENTA_C33)
        BlockDevice * blockDevice;
        MBRBlockDevice * userData;
        FileSystem * userDataFileSystem;
        #elif defined(ARDUINO_PORTENTA_H7_M7)  ||  defined(ARDUINO_OPTA)
        mbed::BlockDevice * blockDevice;
        mbed::MBRBlockDevice * userData;
        mbed::FileSystem * userDataFileSystem;
        #endif

        int partitionNumber = 2;
        char * partitionName = "user";
        FileSystems fs = FS_FAT;
};

#endif