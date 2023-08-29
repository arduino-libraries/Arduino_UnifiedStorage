#include <Arduino_UnifiedStorage.h>

#define HAS_USB 
#define HAS_SD 
#define HAS_QSPI 

#if defined(HAS_USB)
USBStorage * usb = new USBStorage();
#endif

#if defined(HAS_SD)
SDStorage * sd = new SDStorage();
#endif

#if defined(HAS_QSPI)
InternalStorage * qspi = new InternalStorage(2, "user", FS_FAT);
#endif


void test(String opperation, Arduino_UnifiedStorage* sourceStorage, Arduino_UnifiedStorage* destinationStorage, const char* storageTypeA, const char* storageTypeB) {
    Serial.println("----------------------------------------------------------");
    Serial.println("Running test for " + opperation + " from " + String(storageTypeA) + " to " + String(storageTypeB) + "\n");

    int mountSource = sourceStorage -> begin();
    int mountDest =  destinationStorage->begin();

    Serial.println("Mount " + String(storageTypeA) + ": " + mountSource);
    Serial.println("Mount " + String(storageTypeB) + ": " + mountDest);

    if(mountSource && mountDest){
   
        String fileName = "/test_" + String(millis()) + ".txt";
        // Create a file in the source storage
        UFile fileToMove = sourceStorage->getRootFolder().createFile(fileName, FileMode::WRITE);
        fileToMove.write(reinterpret_cast<const uint8_t*>("Test data"), 9);
        fileToMove.close();

        int opperationResult = -1;
        if (opperation == "move") {
            opperationResult = fileToMove.moveTo(destinationStorage->getRootFolder(), true);
        } else if(opperation == "copy"){
            opperationResult = fileToMove.copyTo(destinationStorage->getRootFolder(), true);
        }

        if (opperationResult) {
            Serial.println(opperation + " from " + String(storageTypeA) + " to " + String(storageTypeB) + " successful");

            // Delete the moved file from the destination storage
            UFile movedFile;
            movedFile.open(destinationStorage->getRootFolder().getPathString() + fileName, FileMode::READ);
            if (movedFile.remove()) {
            Serial.println("File deletion from " + String(storageTypeB) + " successful");
            } else {
            Serial.println("File deletion from " + String(storageTypeB) + " failed");
            Serial.println(getErrno());
            }
        } else {
            Serial.println(opperation + " from " + String(storageTypeA) + " to " + String(storageTypeB) + " failed");
            Serial.println(getErrno());
        }

        Serial.println();
        int unmountSource = sourceStorage->unmount();
        Serial.println("Unmount " + String(storageTypeA) + ": " + unmountSource);

        int unmountDest = destinationStorage->unmount();
        Serial.println("Unmount " + String(storageTypeB) + ": " + unmountDest);

        delay(1000);
    }  else {
        Serial.println("cannot execute test, fs not mounted");
    }
}


void sd_and_usb(){
    Serial.println("Formatting both USB and SD to FAT");
    usb->formatFAT();
    sd->formatFAT();

    test("move", usb, sd, "USB FAT", "SD FAT");
    test("copy", usb, sd, "USB FAT", "SD FAT");
    
    test("move", sd, usb, "SD FAT", "USB FAT");
    test("copy", sd, usb, "SD FAT", "USB FAT");

    Serial.println("Formatting USB to LittleFS");
    usb->formatLittleFS();
    test("move", usb, sd, "USB LittleFS", "SD FAT ");
    test("copy", usb, sd, "USB LittleFS", "SD FAT ");

    test("move", sd, usb, "SD FAT", "USB LittleFS");
    test("copy", sd, usb, "SD FAT", "USB LittleFS");

    Serial.println("Formatting SD to LittleFS");
    sd->formatLittleFS();
    test("move", sd, usb, "SD LittleFS", "USB LittleFS");
    test("copy", sd, usb, "SD LittleFS", "USB LittleFS");

    test("move", usb, sd, "USB LittleFS", "SD LittleFS");
    test("copy", usb, sd, "USB LittleFS", "SD LittleFS");

    Serial.println("Formatting USB to FAT");
    usb->formatFAT();
    test("move", usb, sd, "USB FAT", "SD LittleFS");
    test("copy", usb, sd, "USB FAT", "SD LittleFS");

    test("move", sd, usb, "SD LittleFS", "USB FAT");
    test("copy", sd, usb, "SD LittleFS", "USB FAT");



}

void qspi_and_sd() {
    Serial.println("Formatting both QSPI and SD to FAT");
    qspi->formatFAT();
    sd->formatFAT();

    test("move", qspi, sd, "QSPI FAT", "SD FAT");
    test("copy", qspi, sd, "QSPI FAT", "SD FAT");
    
    test("move", sd, qspi, "SD FAT", "QSPI FAT");
    test("copy", sd, qspi, "SD FAT", "QSPI FAT");

    Serial.println("Formatting QSPI to LittleFS");
    qspi->formatLittleFS();
    test("move", qspi, sd, "QSPI LittleFS", "SD FAT");
    test("copy", qspi, sd, "QSPI LittleFS", "SD FAT");

    test("move", sd, qspi, "SD FAT", "QSPI LittleFS");
    test("copy", sd, qspi, "SD FAT", "QSPI LittleFS");

    Serial.println("Formatting SD to LittleFS");
    sd->formatLittleFS();
    test("move", qspi, sd, "QSPI LittleFS", "SD LittleFS");
    test("copy", qspi, sd, "QSPI LittleFS", "SD LittleFS");

    test("move", sd, qspi, "SD LittleFS", "QSPI LittleFS");
    test("copy", sd, qspi, "SD LittleFS", "QSPI LittleFS");

    Serial.println("Formatting QSPI to FAT");
    qspi->formatFAT();
    
    test("move", sd, qspi, "SD LittleFS", "QSPI FAT");
    test("copy", sd, qspi, "SD LittleFS", "QSPI FAT");

    test("move", qspi, sd, "QSPI FAT", "SD LittleFS");
    test("copy", qspi, sd, "QSPI FAT", "SD LittleFS");
}


void qspi_and_usb() {
    Serial.println("Formatting both QSPI and USB to FAT");
    qspi->formatFAT();
    usb->formatFAT();

    test("move", qspi, usb, "QSPI FAT", "USB FAT");
    test("copy", qspi, usb, "QSPI FAT", "USB FAT");
    
    test("move", usb, qspi, "USB FAT", "QSPI FAT");
    test("copy", usb, qspi, "USB FAT", "QSPI FAT");

    Serial.println("Formatting QSPI to LittleFS");
    qspi->formatLittleFS();
    test("move", qspi, usb, "QSPI LittleFS", "USB FAT");
    test("copy", qspi, usb, "QSPI LittleFS", "USB FAT");

    test("move", usb, qspi, "USB FAT", "QSPI LittleFS");
    test("copy", usb, qspi, "USB FAT", "QSPI LittleFS");

    Serial.println("Formatting USB to LittleFS");
    usb->formatLittleFS();

    test("move", qspi, usb, "QSPI LittleFS", "USB LittleFS");
    test("copy", qspi, usb, "QSPI LittleFS", "USB LittleFS");


    test("move", usb, qspi, "USB LittleFS", "QSPI LittleFS");
    test("copy", usb, qspi, "USB LittleFS", "QSPI LittleFS");

    qspi->formatFAT();
    test("move", usb, qspi, "USB LittleFS", "QSPI FAT");
    test("copy", usb, qspi, "USB LittleFS", "QSPI FAT");

    test("move", qspi, usb, "QSPI FAT", "USB LittleFS");
    test("copy", qspi, usb, "QSPI FAT", "USB LittleFS");

}


void setup(){
    Serial.begin(115200);
    while(!Serial);

    #if defined(HAS_USB) && defined(HAS_SD) && defined(HAS_QSPI)
        qspi_and_usb();
        qspi_and_sd();
        sd_and_usb();
    #elif defined(HAS_USB) && defined(HAS_SD)
        sd_and_usb();
    #elif defined(HAS_USB) && defined(HAS_QSPI)
        qspi_and_usb();
    #elif defined(HAS_SD) && defined(HAS_QSPI)
        qspi_and_sd();
    #elif defined(HAS_USB)
        Serial.println("Cannot perform tests if only one storage type is selected");
    #elif defined(HAS_SD)
        Serial.println("Cannot perform tests if only one storage type is selected");
    #elif defined(HAS_QSPI)
        Serial.println("Cannot perform tests if only one storage type is selected");
    #else
        Serial.println("Cannot perform tests if no storage type is selected");
    #endif

}

void loop(){

}