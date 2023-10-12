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
  printToSerialOrRS485("Running repeated mount test for " + storageType); printToSerialOrRS485("\n");

  for(size_t i=0;i<n;i++){
    int mountResult = storage->begin();

    printToSerialOrRS485("Mounting drive"); printToSerialOrRS485("\n");
    if(mountResult != 1) {
      printToSerialOrRS485(mountResult);
      printToSerialOrRS485(getErrno());
      printToSerialOrRS485("\n");
    }

    Folder root = storage->getRootFolder();
    UFile file = root.createFile("file.txt", FileMode::WRITE);
    file.write("writing stuff to the file");
    file.changeMode(FileMode::READ);
    printToSerialOrRS485(file.readAsString()); printToSerialOrRS485("\n");
    file.close();
    file.remove();

    int umountResult = storage->unmount();
    if(!umountResult) {
      printToSerialOrRS485("Unmounting drive"); printToSerialOrRS485("\n");
      printToSerialOrRS485(umountResult);
      printToSerialOrRS485(getErrno());
    } else {
      printToSerialOrRS485("Successfully unmounted"); printToSerialOrRS485("\n");
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
    printToSerialOrRS485("RUNNING FORMAT AND REPEATED MOUNT - QSPI Storage \n"); printToSerialOrRS485("\n");
    printToSerialOrRS485("Formatting QSPI drive as LittleFS: " + String(internal.format(FS_LITTLEFS))); printToSerialOrRS485("\n");
    runRepeatedMountTest(&internal, "QSPI");
    printToSerialOrRS485("Formatting QSPI drive as FAT32: " + String(internal.format(FS_FAT))); printToSerialOrRS485("\n");
    runRepeatedMountTest(&internal, "QSPI");
    printToSerialOrRS485("Formatting SD drive as LittleFS again: " + String(internal.format(FS_LITTLEFS))); printToSerialOrRS485("\n");
    runRepeatedMountTest(&internal, "QSPI");
    printToSerialOrRS485("Formatting SD drive as FAT32 again: " + String(internal.format(FS_FAT))); printToSerialOrRS485("\n");
    runRepeatedMountTest(&internal, "QSPI");
    #endif 

    // format storage as FAT32
    #if defined(HAS_USB)
    printToSerialOrRS485("RUNNING FORMAT AND REPEATED MOUNT - USB \n"); printToSerialOrRS485("\n");
    printToSerialOrRS485("Formatting USB drive as LittleFS: " + String(usb.format(FS_FAT))); printToSerialOrRS485("\n");
    printToSerialOrRS485("" + String(errno));
    runRepeatedMountTest(&usb, "USB");
    printToSerialOrRS485("Formatting USB drive as FAT32: " + String(usb.format(FS_FAT)));  printToSerialOrRS485("\n");
    runRepeatedMountTest(&usb, "USB");
        
    printToSerialOrRS485("Formatting USB drive as LittleFS again: " + String(usb.format(FS_LITTLEFS))); printToSerialOrRS485("\n");
    runRepeatedMountTest(&usb, "USB");
    printToSerialOrRS485("Formatting USB drive as FAT32 again: " + String(usb.format(FS_FAT))); printToSerialOrRS485("\n");
    runRepeatedMountTest(&usb, "USB"); printToSerialOrRS485("\n");
    #endif 



    #if defined(HAS_SD)
    printToSerialOrRS485("RUNNING FORMAT AND REPEATED MOUNT - SD Card \n");
    printToSerialOrRS485("Formatting SD drive as LittleFS: " + String(sd.format(FS_LITTLEFS)));
    runRepeatedMountTest(&&sd, "SD");
    printToSerialOrRS485("Formatting SD drive as FAT32: " + String(sd.format(FS_FAT)));
    runRepeatedMountTest(&&sd, "SD");
    printToSerialOrRS485("Formatting SD drive as LittleFS again: " + String(sd.format(FS_LITTLEFS)));
    runRepeatedMountTest(&&sd, "SD");
    printToSerialOrRS485("Formatting SD drive as FAT32 again: " + String(sd.format(FS_FAT)));
    runRepeatedMountTest(&&sd, "SD");
    #endif 




}

void loop(){

}