#include <Arduino_UnifiedStorage.h>

#if !defined(ARDUINO_OPTA)
#define HAS_SD 
#endif

#define HAS_USB 
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
  printFormatted("Running repeated mount test for " + storageType);

  for(size_t i=0;i<n;i++){
    int mountResult = storage->begin();

    printFormatted("Mounting drive");
    if(mountResult != 1) {
      printFormatted(mountResult);
      printFormatted(getErrno());
    }

    Folder root = storage->getRootFolder();
    UFile file = root.createFile("file.txt", FileMode::WRITE);
    file.write("writing stuff to the file");
    file.changeMode(FileMode::READ);
    printFormatted(file.readAsString());
    file.close();
    file.remove();

    int umountResult = storage->unmount();
    if(!umountResult) {
      printFormatted("Unmounting drive");
      printFormatted(umountResult);
      printFormatted(getErrno());
    } else {
      printFormatted("Successfully unmounted");
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
    printFormatted("RUNNING FORMAT AND REPEATED MOUNT - QSPI Storage \n");
    printFormatted("Formatting QSPI drive as LittleFS: " + String(internal.format(FS_LITTLEFS)));
    runRepeatedMountTest(&internal, "QSPI");
    printFormatted("Formatting QSPI drive as FAT32: " + String(internal.format(FS_FAT)));
    runRepeatedMountTest(&internal, "QSPI");
    printFormatted("Formatting SD drive as LittleFS again: " + String(internal.format(FS_LITTLEFS)));
    runRepeatedMountTest(&internal, "QSPI");
    printFormatted("Formatting SD drive as FAT32 again: " + String(internal.format(FS_FAT)));
    runRepeatedMountTest(&internal, "QSPI");
    #endif 

    // format storage as FAT32
    #if defined(HAS_USB)
    printFormatted("RUNNING FORMAT AND REPEATED MOUNT - USB \n");
    printFormatted("Formatting USB drive as LittleFS: " + String(usb.format(FS_FAT)));
    printFormatted("" + String(errno));
    runRepeatedMountTest(&usb, "USB");
    printFormatted("Formatting USB drive as FAT32: " + String(usb.format(FS_FAT)));
    runRepeatedMountTest(&usb, "USB");
        
    printFormatted("Formatting USB drive as LittleFS again: " + String(usb.format(FS_LITTLEFS)));
    runRepeatedMountTest(&usb, "USB");
    printFormatted("Formatting USB drive as FAT32 again: " + String(usb.format(FS_FAT)));
    runRepeatedMountTest(&usb, "USB");
    #endif 



    #if defined(HAS_SD)
    printFormatted("RUNNING FORMAT AND REPEATED MOUNT - SD Card \n");
    printFormatted("Formatting SD drive as LittleFS: " + String(sd.format(FS_LITTLEFS)));
    runRepeatedMountTest(&sd, "SD");
    printFormatted("Formatting SD drive as FAT32: " + String(sd.format(FS_FAT)));
    runRepeatedMountTest(&sd, "SD");
    printFormatted("Formatting SD drive as LittleFS again: " + String(sd.format(FS_LITTLEFS)));
    runRepeatedMountTest(&sd, "SD");
    printFormatted("Formatting SD drive as FAT32 again: " + String(sd.format(FS_FAT)));
    runRepeatedMountTest(&sd, "SD");
    #endif 




}

void loop(){

}