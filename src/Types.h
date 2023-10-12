#if defined(ARDUINO_PORTENTA_C33)
    #include "BlockDevice.h"
    #include "MBRBlockDevice.h"
    #include "LittleFileSystem.h"
    #include "FATFileSystem.h"

    typedef BlockDevice QSPIFBlockDeviceType;
    typedef MBRBlockDevice MBRBlockDeviceType;
    typedef BlockDevice BlockDeviceType;
    typedef FATFileSystem FATFileSystemType;
    typedef LittleFileSystem LittleFileSystemType;
    typedef FileSystem FileSystemType;

#elif defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_OPTA)
    #include "QSPIFBlockDevice.h"
    #include "MBRBlockDevice.h"
    #include "FATFileSystem.h"

    typedef QSPIFBlockDevice QSPIFBlockDeviceType;
    typedef mbed::MBRBlockDevice MBRBlockDeviceType;
    typedef mbed::BlockDevice BlockDeviceType;
    typedef mbed::FATFileSystem FATFileSystemType;
    typedef mbed::LittleFileSystem LittleFileSystemType;
    typedef mbed::FileSystem FileSystemType;

#endif 
