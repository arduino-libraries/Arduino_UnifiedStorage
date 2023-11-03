

#ifndef USBStorage_H
#define USBStorage_H

#include "Arduino_UnifiedStorage.h"
/**
 * USBStorage class provides an interface to access USB storage devices.
 * It inherits from the Arduino_UnifiedStorage class and implements its pure virtual functions.
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

    /**
     * Sets the callback function to be called when a USB connection is established.
     *
     * @param callbackFunction A pointer to the function to be called when a USB connection is established.
     */
    void onConnect(void (* const callbackFunction)());

    /**
     * @brief Removes the callback function that is executed when the USB storage device is connected.
     * 
     */
    void removeOnConnectCallback();

    /**
     * @brief Sets a callback function to be called when the USB storage device is disconnected.
     * 
     * @param callbackFunction A pointer to the function to be called when the USB storage device is disconnected.
     */
    void onDisconnect(void (* const callbackFunction)());

    /**
     * @brief Removes the callback function that is called when the USB storage device is disconnected.
     * 
     */
    void removeOnDisconnectCallback();


private:
    FileSystems fileSystemType = FS_FAT;
    bool mounted = false;
    unsigned long previousMillis; 
    unsigned int interval = 500; // document what this does too, make it constexp (mountRetryInterval)
};

#endif
