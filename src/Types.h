#ifndef TYPES_H
#define TYPES_H

#include "Boards.h"

enum FileMode { READ, WRITE, APPEND };

#if defined(USES_RENESAS_CORE)
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

#elif defined(USES_MBED_CORE)
    #include "QSPIFBlockDevice.h"
    #include "MBRBlockDevice.h"
    #include "LittleFileSystem.h"
    #include "FATFileSystem.h"

    typedef QSPIFBlockDevice QSPIFBlockDeviceType;
    typedef mbed::MBRBlockDevice MBRBlockDeviceType;
    typedef mbed::BlockDevice BlockDeviceType;
    typedef mbed::FATFileSystem FATFileSystemType;
    typedef mbed::LittleFileSystem LittleFileSystemType;
    typedef mbed::FileSystem FileSystemType;
#endif 

#endif  // TYPES_H