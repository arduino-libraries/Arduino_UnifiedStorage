#define ARDUINO_UNIFIED_STORAGE_DEBUG
#include <Arduino_UnifiedStorage.h>

#if defined(HAS_USB)
USBStorage usb = USBStorage();
#endif

#if defined(HAS_SD)
SDStorage sd = SDStorage();
#endif

#if defined(HAS_QSPI)
InternalStorage internal = InternalStorage();
#endif

void runRepeatedMountTest(Arduino_UnifiedStorage * storage, String storageType, int n = 10){
  debugPrint("Running repeated mount test for " + storageType); 

  for(size_t i=0;i<n;i++){
    int mountResult = storage->begin();

    debugPrint("Mounting drive"); 
    if(mountResult != 1) {
      debugPrint("Mounting drive failed: " + String(getErrno()));
    } else {
      debugPrint("Successfully mounted"); 
    }

    Folder root = storage->getRootFolder();
    UFile file = root.createFile("file.txt", FileMode::WRITE);
    file.write("writing stuff to the file");
    file.changeMode(FileMode::READ);
    debugPrint(file.readAsString()); 
    file.close();
    file.remove();

    int umountResult = storage->unmount();
    if(!umountResult) {
      debugPrint("Unmounting drive failed: " + String(getErrno())); 
    } else {
      debugPrint("Successfully unmounted"); 
    }
  }
}


void setup(){
    #if defined(ARDUINO_PORTENTA_C33) || defined(ARDUINO_PORTENTA_H7_M7)
        Serial.begin(115200);
        while(!Serial);
    #elif defined(ARDUINO_OPTA)
        beginRS485(115200);
    #endif 
    
    #if defined(HAS_QSPI)
    debugPrint("RUNNING FORMAT AND REPEATED MOUNT - QSPI Storage"); 
    debugPrint("Formatting QSPI drive as LittleFS: " + String(internal.format(FS_LITTLEFS))); 
    runRepeatedMountTest(&internal, "QSPI");
    debugPrint("Formatting QSPI drive as FAT32: " + String(internal.format(FS_FAT))); 
    runRepeatedMountTest(&internal, "QSPI");
    debugPrint("Formatting SD drive as LittleFS again: " + String(internal.format(FS_LITTLEFS))); 
    runRepeatedMountTest(&internal, "QSPI");
    debugPrint("Formatting SD drive as FAT32 again: " + String(internal.format(FS_FAT))); 
    runRepeatedMountTest(&internal, "QSPI");
    #endif 

    // format storage as FAT32
    #if defined(HAS_USB)
    debugPrint("RUNNING FORMAT AND REPEATED MOUNT - USB"); 
    debugPrint("Formatting USB drive as LittleFS: " + String(usb.format(FS_FAT))); 
    debugPrint("" + String(errno));
    runRepeatedMountTest(&usb, "USB");
    debugPrint("Formatting USB drive as FAT32: " + String(usb.format(FS_FAT)));  
    runRepeatedMountTest(&usb, "USB");
        
    debugPrint("Formatting USB drive as LittleFS again: " + String(usb.format(FS_LITTLEFS))); 
    runRepeatedMountTest(&usb, "USB");
    debugPrint("Formatting USB drive as FAT32 again: " + String(usb.format(FS_FAT))); 
    runRepeatedMountTest(&usb, "USB"); 
    #endif 



    #if defined(HAS_SD)
    debugPrint("RUNNING FORMAT AND REPEATED MOUNT - SD Card");
    debugPrint("Formatting SD drive as LittleFS: " + String(sd.format(FS_LITTLEFS)));
    runRepeatedMountTest(&sd, "SD");
    debugPrint("Formatting SD drive as FAT32: " + String(sd.format(FS_FAT)));
    runRepeatedMountTest(&sd, "SD");
    debugPrint("Formatting SD drive as LittleFS again: " + String(sd.format(FS_LITTLEFS)));
    runRepeatedMountTest(&sd, "SD");
    debugPrint("Formatting SD drive as FAT32 again: " + String(sd.format(FS_FAT)));
    runRepeatedMountTest(&sd, "SD");
    #endif 




}

void loop(){

}