#include <Arduino_UnifiedStorage.h>

#define HAS_USB 
#define HAS_SD 
#define HAS_QSPI 

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
  Serial.println("Running repeated mount test for " + storageType);

  for(size_t i=0;i<n;i++){
    int mountResult = storage->begin();

    Serial.println("Mounting drive");
    if(mountResult != 1) {
      Serial.println(mountResult);
      Serial.println(getErrno());
    }

    Folder root = storage->getRootFolder();
    UFile file = root.createFile("file.txt", FileMode::WRITE);
    file.write("writing stuff to the file");
    file.changeMode(FileMode::READ);
    Serial.println(file.readAsString());
    file.close();
    file.remove();

    int umountResult = storage->unmount();
    if(!umountResult) {
      Serial.println("Unmounting drive");
      Serial.println(umountResult);
      Serial.println(getErrno());
    } else {
      Serial.println("Successfully unmounted");
    }
  }
}


void setup(){
    Serial.begin(115200);
    while(!Serial);
    
    // format storage as FAT32
    #if defined(HAS_USB)
    Serial.println("RUNNING FORMAT AND REPEATED MOUNT - USB \n");
    Serial.println("Formatting USB drive as LittleFS: " + String(usb.format(FS_LITTLEFS)));
    runRepeatedMountTest(&usb, "USB");
    Serial.println("Formatting USB drive as FAT32: " + String(usb.format(FS_FAT)));
    runRepeatedMountTest(&usb, "USB");
        
    Serial.println("Formatting USB drive as LittleFS again: " + String(usb.format(FS_LITTLEFS)));
    runRepeatedMountTest(&usb, "USB");
    Serial.println("Formatting USB drive as FAT32 again: " + String(usb.format(FS_FAT)));
    runRepeatedMountTest(&usb, "USB");
    #endif 



    #if defined(HAS_SD)
    Serial.println("RUNNING FORMAT AND REPEATED MOUNT - SD Card \n");
    Serial.println("Formatting SD drive as LittleFS: " + String(sd.format(FS_LITTLEFS)));
    runRepeatedMountTest(&sd, "SD");
    Serial.println("Formatting SD drive as FAT32: " + String(sd.format(FS_FAT)));
    runRepeatedMountTest(&sd, "SD");
    Serial.println("Formatting SD drive as LittleFS again: " + String(sd.format(FS_LITTLEFS)));
    runRepeatedMountTest(&sd, "SD");
    Serial.println("Formatting SD drive as FAT32 again: " + String(sd.format(FS_FAT)));
    runRepeatedMountTest(&sd, "SD");
    #endif 


    #if defined(HAS_QSPI)
    Serial.println("RUNNING FORMAT AND REPEATED MOUNT - QSPI Storage \n");
    Serial.println("Formatting QSPI drive as LittleFS: " + String(internal.format(FS_LITTLEFS)));
    runRepeatedMountTest(&internal, "QSPI");
    Serial.println("Formatting QSPI drive as FAT32: " + String(internal.format(FS_FAT)));
    runRepeatedMountTest(&internal, "QSPI");
    Serial.println("Formatting SD drive as LittleFS again: " + String(internal.format(FS_LITTLEFS)));
    runRepeatedMountTest(&internal, "QSPI");
    Serial.println("Formatting SD drive as FAT32 again: " + String(internal.format(FS_FAT)));
    runRepeatedMountTest(&internal, "QSPI");
    #endif 

}

void loop(){

}