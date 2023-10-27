#define ARDUINO_UNIFIED_STORAGE_DEBUG

#include <Arduino_UnifiedStorage.h>



void test(String operation, Arduino_UnifiedStorage* sourceStorage, Arduino_UnifiedStorage* destinationStorage, const char* storageTypeA, const char* storageTypeB) {
    debugPrint("Testing " + operation + " from " + String(storageTypeA) + " to " + String(storageTypeB));
    sourceStorage->ls();
    destinationStorage->ls();
    debugPrint("Result: " + String(sourceStorage->move(destinationStorage, "/test.txt", "/test.txt")));
    sourceStorage->ls();
    destinationStorage->ls();
    delay(1000);
}

#if defined(HAS_USB) && defined(HAS_SD)
void sd_and_usb(){
    debugPrint("TESTING SD AND USB \n\n");

    debugPrint("-----------------------------"); 
    debugPrint("Formatting USB to FAT: " +  String(usb.format(FS_FAT)));
    delay(1000);
    debugPrint("Formatting SD to FAT: "  + String(sd.format(FS_FAT)));
    delay(1000);
    debugPrint("-----------------------------");


    test("move", &usb, &sd, "USB FAT", "SD FAT");
    delay(1000);
    test("copy", &usb, &sd, "USB FAT", "SD FAT");
    delay(1000);
    
    test("move", &sd, &usb, "SD FAT", "USB FAT");
    delay(1000);
    test("copy", &sd, &usb, "SD FAT", "USB FAT");
    delay(1000);

    debugPrint("-----------------------------");
    debugPrint("Formatting USB to LittleFS:" + String(usb.format(FS_LITTLEFS)));
    delay(1000);
    debugPrint("-----------------------------");

    test("move", &usb, &sd, "USB LittleFS", "SD FAT ");
    delay(1000);
    test("copy", &usb, &sd, "USB LittleFS", "SD FAT ");
    delay(1000);

    test("move", &sd, &usb, "SD FAT", "USB LittleFS");
    delay(1000);
    test("copy", &sd, &usb, "SD FAT", "USB LittleFS");
    delay(1000);

    debugPrint("-----------------------------");
    debugPrint("Formatting SD to LittleFS: "+ String(sd.format(FS_LITTLEFS)));
    delay(1000);
    debugPrint("-----------------------------");

    test("move", &sd, &usb, "SD LittleFS", "USB LittleFS");
    delay(1000);
    test("copy", &sd, &usb, "SD LittleFS", "USB LittleFS");
    delay(1000);

    test("move", &usb, &sd, "USB LittleFS", "SD LittleFS");
    delay(1000);
    test("copy", &usb, &sd, "USB LittleFS", "SD LittleFS");
    delay(1000);

    debugPrint("-----------------------------");
    debugPrint("Formatting USB to FAT: " + String(usb.format(FS_FAT)));
    delay(1000);
    debugPrint("-----------------------------");

    test("move", &usb, &sd, "USB FAT", "SD LittleFS");
    delay(1000);
    test("copy", &usb, &sd, "USB FAT", "SD LittleFS");
    delay(1000);

    test("move", &sd, &usb, "SD LittleFS", "USB FAT");
    delay(1000);
    test("copy", &sd, &usb, "SD LittleFS", "USB FAT");
    delay(1000);
}
#endif

#if defined(HAS_QSPI) && defined(HAS_SD)
void qspi_and_sd() {
    debugPrint("TESTING QSPI AND SD \n\n");
    debugPrint("-----------------------------");
    debugPrint("Formatting QSPI to FAT: " + String(qspi.format(FS_FAT)));
    delay(1000);
    debugPrint("Formatting SD to FAT: " +  String(sd.format(FS_FAT)));
    delay(1000);
    debugPrint("-----------------------------");

    test("move", &qspi, &sd, "QSPI FAT", "SD FAT");
    delay(1000);
    test("copy", &qspi, &sd, "QSPI FAT", "SD FAT");
    delay(1000);
    
    test("move", &sd, &qspi, "SD FAT", "QSPI FAT");
    delay(1000);
    test("copy", &sd, &qspi, "SD FAT", "QSPI FAT");
    delay(1000);

    debugPrint("-----------------------------");
    debugPrint("Formatting QSPI to LittleFS:" + String(qspi.format(FS_LITTLEFS)));
    delay(1000);
    debugPrint("-----------------------------");

    test("move", &qspi, &sd, "QSPI LittleFS", "SD FAT");
    delay(1000);
    test("copy", &qspi, &sd, "QSPI LittleFS", "SD FAT");
    delay(1000);

    test("move", &sd, &qspi, "SD FAT", "QSPI LittleFS");
    delay(1000);
    test("copy", &sd, &qspi, "SD FAT", "QSPI LittleFS");
    delay(1000);

    debugPrint("-----------------------------");
    debugPrint("Formatting SD to LittleFS: "+ String(sd.format(FS_LITTLEFS)));
    delay(1000);
    debugPrint("-----------------------------");

    test("move", &qspi, &sd, "QSPI LittleFS", "SD LittleFS");
    delay(1000);
    test("copy", &qspi, &sd, "QSPI LittleFS", "SD LittleFS");
    delay(1000);

    test("move", &sd, &qspi, "SD LittleFS", "QSPI LittleFS");
    delay(1000);
    test("copy", &sd, &qspi, "SD LittleFS", "QSPI LittleFS");
    delay(1000);

    debugPrint("-----------------------------");
    debugPrint("Formatting QSPI to FAT: " + String(qspi.format(FS_FAT)));
    delay(1000);
    debugPrint("-----------------------------");
    
    test("move", &sd, &qspi, "SD LittleFS", "QSPI FAT");
    delay(1000);
    test("copy", &sd, &qspi, "SD LittleFS", "QSPI FAT");
    delay(1000);

    test("move", &qspi, &sd, "QSPI FAT", "SD LittleFS");
    delay(1000);
    test("copy", &qspi, &sd, "QSPI FAT", "SD LittleFS");
    delay(1000);
}
#endif

#if defined(HAS_QSPI) && defined(HAS_USB)
void qspi_and_usb() {

    debugPrint("TESTING QSPI AND USB \n\n");
    debugPrint("-----------------------------");
    qspi.begin();
    qspi.unmount();
    usb.begin();
    usb.unmount();
  
    debugPrint("Formatting USB to FAT: " +  String(usb.format(FS_FAT)));debugPrint("now formatting qspi");
    delay(1000);
    debugPrint("Formatting QSPI to FAT: " + String(qspi.format(FS_FAT)));
    debugPrint("-----------------------------");

    test("move", &qspi, &usb, "QSPI FAT", "USB FAT");
    delay(1000);
    test("copy", &qspi, &usb, "QSPI FAT", "USB FAT");
    delay(1000);
    
    test("move", &usb, &qspi, "USB FAT", "QSPI FAT");
    delay(1000);
    test("copy", &usb, &qspi, "USB FAT", "QSPI FAT");
    delay(1000);

    debugPrint("-----------------------------");
    debugPrint("Formatting QSPI to LittleFS:" + String(qspi.format(FS_LITTLEFS)));
    delay(1000);
    debugPrint("-----------------------------");

    test("move", &qspi, &usb, "QSPI LittleFS", "USB FAT");
    delay(1000);
    test("copy", &qspi, &usb, "QSPI LittleFS", "USB FAT");
    delay(1000);

    test("move", &usb, &qspi, "USB FAT", "QSPI LittleFS");
    delay(1000);
    test("copy", &usb, &qspi, "USB FAT", "QSPI LittleFS");
    delay(1000);

    debugPrint("-----------------------------");
    debugPrint("Formatting USB to LittleFS: "+ String(usb.format(FS_LITTLEFS)));
    delay(1000);
    debugPrint("-----------------------------");

    test("move", &qspi, &usb, "QSPI LittleFS", "USB LittleFS");
    delay(1000);
    test("copy", &qspi, &usb, "QSPI LittleFS", "USB LittleFS");
    delay(1000);

    test("move", &usb, &qspi, "USB LittleFS", "QSPI LittleFS");
    delay(1000);
    test("copy", &usb, &qspi, "USB LittleFS", "QSPI LittleFS");
    delay(1000);

    debugPrint("-----------------------------");
    debugPrint("Formatting QSPI to FAT:" + String(qspi.format(FS_FAT)));
    delay(1000);
    debugPrint("-----------------------------");

    test("move", &usb, &qspi, "USB LittleFS", "QSPI FAT");
    delay(1000);
    test("copy", &usb, &qspi, "USB LittleFS", "QSPI FAT");
    delay(1000);

    test("move", &qspi, &usb, "QSPI FAT", "USB LittleFS");
    delay(1000);
    test("copy", &qspi, &usb, "QSPI FAT", "USB LittleFS");
    delay(1000);
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
        debugPrint("Tests finished, formatting all partitions back to FAT:");
        debugPrint("\t * Formatting QSPI to FAT: " + String(qspi.format(FS_FAT)));
        debugPrint("\t * Formatting SD to FAT: " + String(sd.format(FS_FAT)));
        debugPrint("\t * Formatting USB to FAT: " + String(usb.format(FS_FAT)));
    #elif defined(HAS_USB) && defined(HAS_SD)
        sd_and_usb();
        debugPrint("\t * Formatting SD to FAT:" + String(sd.format(FS_FAT)));
        debugPrint("\t * Formatting USB to FAT:" + String(usb.format(FS_FAT)));
    #elif defined(HAS_USB) && defined(HAS_QSPI)
        qspi_and_usb();
        debugPrint("Tests finished, formatting all partitions back to FAT:");
        debugPrint("\t * Formatting QSPI to FAT:" + String(qspi.format(FS_FAT)));
        debugPrint("\t * Formatting USB to FAT:" + String(usb.format(FS_FAT)));
    #elif defined(HAS_SD) && defined(HAS_QSPI)
        qspi_and_sd();
        debugPrint("Tests finished, formatting all partitions back to FAT:");
        debugPrint("\t * Formatting QSPI to FAT:" + String(qspi.format(FS_FAT)));
        debugPrint("\t * Formatting SD to FAT:" + String(sd.format(FS_FAT)));
    #elif defined(HAS_USB)
        debugPrint("Cannot perform tests if only one storage type is selected");
    #elif defined(HAS_SD)
        debugPrint("Cannot perform tests if only one storage type is selected");
    #elif defined(HAS_QSPI)
        debugPrint("Cannot perform tests if only one storage type is selected");
    #else
        debugPrint("Cannot perform tests if no storage type is selected");
    #endif

}

void loop(){

}