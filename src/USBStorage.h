#include "Arduino_UnifiedStorage.h"

#ifndef USBStorage_H
#define USBStorage_H

/**
 * Represents USB storage using the Arduino Unified Storage library.
 */
static bool usb_available = false;

class USBStorage : public Arduino_UnifiedStorage {
public:

    /**
     * Default constructor for the USBStorage class.
     */
    USBStorage();

    /**
     * Initializes the USB storage.
     * 
     * @return 1 if successful, 0 if failed.
     */
    int begin() override;

    /**
     * Initializes the USB storage with the specified file system.
     * 
     * @param fs The desired file system (FS_FAT or FS_LITTLEFS).
     * @return 1 if successful, 0 if failed.
     */
    int begin(FileSystems fs) override;

    /**
     * Unmounts the USB storage.
     * 
     * @return 1 if successful, 0 if failed.
     */
    int unmount() override;

    /**
     * Retrieves the root folder of the USB storage.
     * 
     * @return The root folder as a Folder object.
     */
    Folder getRootFolder() override;

    /**
     * Formats the USB storage with the FAT file system.
     * 
     * @return 1 if successful, 0 if failed.
     */
    int formatFAT() override;

    /**
     * Formats the USB storage with the LittleFS file system.
     * 
     * @return 1 if successful, 0 if failed.
     */
    int formatLittleFS() override;

    /**
     * Checks if the USB storage is connected.
     * 
     * @return true if connected, false otherwise.
     */
    bool isConnected();

    /**
     * Checks if the USB storage is available.
     * 
     * @return true if available, false otherwise.
     */
    bool isAvailable();

    /**
     * Checks the USB storage connection status.
     */
    void checkConnection();

private:
    FileSystems fs = FS_FAT;
    bool connected = false;
    unsigned long previousMillis; 
    int interval = 500;
};

#endif
