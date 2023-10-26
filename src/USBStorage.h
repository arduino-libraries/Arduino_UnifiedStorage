

#ifndef USBStorage_H
#define USBStorage_H

#include "Arduino_UnifiedStorage.h"
/**
 * Represents a USB storage using the Arduino Unified Storage library.
 */
class USBStorage : public Arduino_UnifiedStorage {
public:

    /**
     * Default constructor for the USBStorage class.
     */
    USBStorage();

    /**
     * Initializes the USB storage.
     * 
     * @return true if successful, false if failed.
     */
    bool begin() override;

    /**
     * Initializes the USB storage with the specified file system.
     * 
     * @param fs The desired file system (FS_FAT or FS_LITTLEFS).
     * @return true if successful, false if failed.
     */
    bool begin(FileSystems fs) override;

    /**
     * Unmounts the USB storage.
     * 
     * @return true if successful, false if failed.
     */
    bool unmount() override;

    /**
     * Retrieves the root folder of the USB storage.
     * 
     * @return The root folder as a Folder object.
     */
    Folder getRootFolder() override;

    /**
     * Formats the USB storage with the selected file system.
     * 
     * @return true if successful, false if failed.
     */
    bool format(FileSystems fs) override;

    /**
     * Checks if the USB storage is mounted.
     * 
     * @return true if mounted, false otherwise.
     */
    bool isMounted();

    void onConnect(void (* const callbackFunction)());

    void removeOnConnectCallback();

    void onDisconnect(void (* const callbackFunction)());

    void removeOnDisconnectCallback();


private:
    FileSystems fileSystem = FS_FAT;
    bool mounted = false;
    unsigned long previousMillis; 
    unsigned int interval = 500; // document what this does too, make it constexp (mountRetryInterval)
};

#endif
