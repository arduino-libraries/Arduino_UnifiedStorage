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
InternalStorage qspi = InternalStorage();
#endif


void test(String operation, Arduino_UnifiedStorage* sourceStorage, Arduino_UnifiedStorage* destinationStorage, const char* storageTypeA, const char* storageTypeB) {
    printToSerialOrRS485("----------------------------------------------------------");
    printToSerialOrRS485("Running test for " + operation + " from " + String(storageTypeA) + " to " + String(storageTypeB) + "\n");

    int mountSource = sourceStorage -> begin();
    int mountDest =  destinationStorage->begin();

    printToSerialOrRS485("Mount " + String(storageTypeA) + ": " + mountSource); printToSerialOrRS485("\n");
    printToSerialOrRS485("Mount " + String(storageTypeB) + ": " + mountDest); printToSerialOrRS485("\n");

    if(mountSource && mountDest){
   
        String fileName = "test_" + String(millis()) + ".txt";
        // Create a file in the source storage
        UFile fileToMove = sourceStorage->getRootFolder().createFile(fileName, FileMode::WRITE);
        fileToMove.write(reinterpret_cast<const uint8_t*>("Test data"), 9);
        fileToMove.close();

        int opperationResult = -1;
        if (operation == "move") {
            opperationResult = fileToMove.moveTo(destinationStorage->getRootFolder(), true);
            fileToMove.close();
            fileToMove.remove();
        } else if(operation == "copy"){
            opperationResult = fileToMove.copyTo(destinationStorage->getRootFolder(), true);
            fileToMove.close();
            fileToMove.remove();
        }

        if (opperationResult) {
            printToSerialOrRS485(operation + " from " + String(storageTypeA) + " to " + String(storageTypeB) + " successful \n");
        }

        int unmountSource = sourceStorage->unmount();
        int unmountDest = destinationStorage->unmount();

        delay(1000);
        
    }  else {
        printToSerialOrRS485("cannot execute test, fs not mounted \n");
    }
}


#if defined(HAS_USB) && defined(HAS_SD)
void sd_and_usb(){
    printToSerialOrRS485("TESTING SD AND USB \n\n\n\n");

    printToSerialOrRS485("-----------------------------"); printToSerialOrRS485("\n");
    printToSerialOrRS485("Formatting USB to FAT: " +  String(usb.format(FS_FAT)));printToSerialOrRS485("\n");
    printToSerialOrRS485("Formatting SD to FAT: "  + String(sd.format(FS_FAT)));printToSerialOrRS485("\n");
    printToSerialOrRS485("-----------------------------");printToSerialOrRS485("\n");


    test("move", &usb, &sd, "USB FAT", "SD FAT");
    test("copy", &usb, &sd, "USB FAT", "SD FAT");
    
    test("move", &sd, &usb, "SD FAT", "USB FAT");
    test("copy", &sd, &usb, "SD FAT", "USB FAT");

    printToSerialOrRS485("-----------------------------");printToSerialOrRS485("\n");
    printToSerialOrRS485("Formatting USB to LittleFS:" + String(usb.format(FS_LITTLEFS)));printToSerialOrRS485("\n");
    printToSerialOrRS485("-----------------------------");printToSerialOrRS485("\n");

    test("move", &usb, &sd, "USB LittleFS", "SD FAT ");
    test("copy", &usb, &sd, "USB LittleFS", "SD FAT ");

    test("move", &sd, &usb, "SD FAT", "USB LittleFS");
    test("copy", &sd, &usb, "SD FAT", "USB LittleFS");

    printToSerialOrRS485("-----------------------------");printToSerialOrRS485("\n");
    printToSerialOrRS485("Formatting SD to LittleFS: "+ String(sd.format(FS_LITTLEFS)));printToSerialOrRS485("\n");
    printToSerialOrRS485("-----------------------------");printToSerialOrRS485("\n");

    test("move", &sd, &usb, "SD LittleFS", "USB LittleFS");
    test("copy", &sd, &usb, "SD LittleFS", "USB LittleFS");

    test("move", &usb, &sd, "USB LittleFS", "SD LittleFS");
    test("copy", &usb, &sd, "USB LittleFS", "SD LittleFS");

    printToSerialOrRS485("-----------------------------");printToSerialOrRS485("\n");
    printToSerialOrRS485("Formatting USB to FAT: " + String(usb.format(FS_FAT)));printToSerialOrRS485("\n");
    printToSerialOrRS485("-----------------------------");printToSerialOrRS485("\n");

    test("move", &usb, &sd, "USB FAT", "SD LittleFS");
    test("copy", &usb, &sd, "USB FAT", "SD LittleFS");

    test("move", &sd, &usb, "SD LittleFS", "USB FAT");
    test("copy", &sd, &usb, "SD LittleFS", "USB FAT");
}
#endif


#if defined(HAS_QSPI) && defined(HAS_SD)
void qspi_and_sd() {
    printToSerialOrRS485("TESTING QSPI AND SD \n\n\n\n");
    printToSerialOrRS485("-----------------------------");
    printToSerialOrRS485("Formatting QSPI to FAT: " + String(qspi.format(FS_FAT)));
    printToSerialOrRS485("Formatting SD to FAT: " +  String(sd.format(FS_FAT)));
    printToSerialOrRS485("-----------------------------");

    test("move", &qspi, &sd, "QSPI FAT", "SD FAT");
    test("copy", &qspi, &sd, "QSPI FAT", "SD FAT");
    
    test("move", &sd, &qspi, "SD FAT", "QSPI FAT");
    test("copy", &sd, &qspi, "SD FAT", "QSPI FAT");

    printToSerialOrRS485("-----------------------------");
    printToSerialOrRS485("Formatting QSPI to LittleFS:" + String(qspi.format(FS_LITTLEFS)));
    printToSerialOrRS485("-----------------------------");

    test("move", &qspi, &sd, "QSPI LittleFS", "SD FAT");
    test("copy", &qspi, &sd, "QSPI LittleFS", "SD FAT");

    test("move", &sd, &qspi, "SD FAT", "QSPI LittleFS");
    test("copy", &sd, &qspi, "SD FAT", "QSPI LittleFS");

    printToSerialOrRS485("-----------------------------");
    printToSerialOrRS485("Formatting SD to LittleFS: "+ String(sd.format(FS_LITTLEFS)));
    printToSerialOrRS485("-----------------------------");

    test("move", &qspi, &sd, "QSPI LittleFS", "SD LittleFS");
    test("copy", &qspi, &sd, "QSPI LittleFS", "SD LittleFS");

    test("move", &sd, &qspi, "SD LittleFS", "QSPI LittleFS");
    test("copy", &sd, &qspi, "SD LittleFS", "QSPI LittleFS");

    printToSerialOrRS485("-----------------------------");
    printToSerialOrRS485("Formatting QSPI to FAT: " + String(qspi.format(FS_FAT)));
    printToSerialOrRS485("-----------------------------");
    
    test("move", &sd, &qspi, "SD LittleFS", "QSPI FAT");
    test("copy", &sd, &qspi, "SD LittleFS", "QSPI FAT");

    test("move", &qspi, &sd, "QSPI FAT", "SD LittleFS");
    test("copy", &qspi, &sd, "QSPI FAT", "SD LittleFS");
}
#endif

#if defined(HAS_QSPI) && defined(HAS_USB)
void qspi_and_usb() {

    printToSerialOrRS485("TESTING QSPI AND USB \n\n\n\n");
    printToSerialOrRS485("-----------------------------");printToSerialOrRS485("\n");
    qspi.begin();
    qspi.unmount();
    usb.begin();
    usb.unmount();
  
    printToSerialOrRS485("Formatting USB to FAT: " +  String(usb.format(FS_FAT)));printToSerialOrRS485("now formatting qspi");
    delay(1000);
    printToSerialOrRS485("Formatting QSPI to FAT: " + String(qspi.format(FS_FAT)));printToSerialOrRS485("\n");
    printToSerialOrRS485("-----------------------------");printToSerialOrRS485("\n");

    test("move", &qspi, &usb, "QSPI FAT", "USB FAT");
    test("copy", &qspi, &usb, "QSPI FAT", "USB FAT");
    
    test("move", &usb, &qspi, "USB FAT", "QSPI FAT");
    test("copy", &usb, &qspi, "USB FAT", "QSPI FAT");

    printToSerialOrRS485("-----------------------------");printToSerialOrRS485("\n");
    printToSerialOrRS485("Formatting QSPI to LittleFS:" + String(qspi.format(FS_LITTLEFS)));printToSerialOrRS485("\n");
    printToSerialOrRS485("-----------------------------");printToSerialOrRS485("\n");

    test("move", &qspi, &usb, "QSPI LittleFS", "USB FAT");
    test("copy", &qspi, &usb, "QSPI LittleFS", "USB FAT");

    test("move", &usb, &qspi, "USB FAT", "QSPI LittleFS");
    test("copy", &usb, &qspi, "USB FAT", "QSPI LittleFS");

    printToSerialOrRS485("-----------------------------");printToSerialOrRS485("\n");
    printToSerialOrRS485("Formatting USB to LittleFS: "+ String(usb.format(FS_LITTLEFS)));printToSerialOrRS485("\n");
    printToSerialOrRS485("-----------------------------");printToSerialOrRS485("\n");

    test("move", &qspi, &usb, "QSPI LittleFS", "USB LittleFS");
    test("copy", &qspi, &usb, "QSPI LittleFS", "USB LittleFS");


    test("move", &usb, &qspi, "USB LittleFS", "QSPI LittleFS");
    test("copy", &usb, &qspi, "USB LittleFS", "QSPI LittleFS");

    printToSerialOrRS485("-----------------------------");printToSerialOrRS485("\n");
    printToSerialOrRS485("Formatting QSPI to FAT:" + String(qspi.format(FS_FAT)));printToSerialOrRS485("\n");
    printToSerialOrRS485("-----------------------------");printToSerialOrRS485("\n");

    test("move", &usb, &qspi, "USB LittleFS", "QSPI FAT");
    test("copy", &usb, &qspi, "USB LittleFS", "QSPI FAT");

    test("move", &qspi, &usb, "QSPI FAT", "USB LittleFS");
    test("copy", &qspi, &usb, "QSPI FAT", "USB LittleFS");

}
#endif

void setup(){
    #if defined(ARDUINO_PORTENTA_C33) || defined(ARDUINO_PORTENTA_H7_M7)
        Serial.begin(115200);
        while(!Serial);
    #elif defined(ARDUINO_OPTA)
        beginRS485(115200);
    #endif 

    #if defined(HAS_USB) && defined(HAS_SD) && defined(HAS_QSPI)
        qspi_and_usb();
        sd_and_usb();
        qspi_and_sd();
        printToSerialOrRS485("Tests finished, formatting all partitions back to FAT:");
        printToSerialOrRS485("\t * Formatting QSPI to FAT: " + String(qspi.format(FS_FAT)));
        printToSerialOrRS485("\t * Formatting SD to FAT: " + String(sd.format(FS_FAT)));
        printToSerialOrRS485("\t * Formatting USB to FAT: " + String(usb.format(FS_FAT)));
    #elif defined(HAS_USB) && defined(HAS_SD)
        sd_and_usb();
        printToSerialOrRS485("\t * Formatting SD to FAT:" + String(sd.format(FS_FAT)));
        printToSerialOrRS485("\t * Formatting USB to FAT:" + String(usb.format(FS_FAT)));
    #elif defined(HAS_USB) && defined(HAS_QSPI)
        qspi_and_usb();
        printToSerialOrRS485("Tests finished, formatting all partitions back to FAT:");printToSerialOrRS485("\n");
        printToSerialOrRS485("\t * Formatting QSPI to FAT:" + String(qspi.format(FS_FAT)));printToSerialOrRS485("\n");
        printToSerialOrRS485("\t * Formatting USB to FAT:" + String(usb.format(FS_FAT)));printToSerialOrRS485("\n");
    #elif defined(HAS_SD) && defined(HAS_QSPI)
        qspi_and_sd();
        printToSerialOrRS485("Tests finished, formatting all partitions back to FAT:");
        printToSerialOrRS485("\t * Formatting QSPI to FAT:" + String(qspi.format(FS_FAT)));
        printToSerialOrRS485("\t * Formatting SD to FAT:" + String(sd.format(FS_FAT)));
    #elif defined(HAS_USB)
        printToSerialOrRS485("Cannot perform tests if only one storage type is selected");
    #elif defined(HAS_SD)
        printToSerialOrRS485("Cannot perform tests if only one storage type is selected");
    #elif defined(HAS_QSPI)
        printToSerialOrRS485("Cannot perform tests if only one storage type is selected");
    #else
        printToSerialOrRS485("Cannot perform tests if no storage type is selected");
    #endif

}

void loop(){

}