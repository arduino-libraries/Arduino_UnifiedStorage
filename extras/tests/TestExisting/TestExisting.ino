
#define ARDUINO_UNIFIED_STORAGE_DEBUG

#include <Arduino_UnifiedStorage.h>


InternalStorage internalStorage;

void setup() {
    /* UNCOMMENT THIS PART IF YOU WANT TO ENABLE FORMATTING*/


    #if defined(HAS_SERIAL)
        Serial.begin(115200);
        while(!Serial);
    #elif defined(HAS_RS485)
        beginRS485(115200);
    #endif 

    // toggle this to enable debugging output
    Arduino_UnifiedStorage::debuggingModeEnabled = false;

    internalStorage.begin();

    Folder root = internalStorage.getRootFolder();

    // Test copyTo
    Arduino_UnifiedStorage::testPrint("Testing copyTo...");
    Folder sourceFolder2 =  root.createSubfolder("source_folder");
    Arduino_UnifiedStorage::testPrint("Folder 1 created");

    Arduino_UnifiedStorage::testPrint("Trying to create a folder on top of an existing one... without overwrite");
    Folder sourceFolder3 =  root.createSubfolder("source_folder");
   
    
    Arduino_UnifiedStorage::testPrint("Trying to create a folder on top of an existing one... with overwrite");
    Folder sourceFolder4 =  root.createSubfolder("source_folder", true);

    Folder destinationFolder2 = root.createSubfolder("destination_folder");
    Arduino_UnifiedStorage::testPrint("Folder 2 created");


    bool copyResult = sourceFolder2.copyTo(destinationFolder2, true); // Overwrite if exists
    if (copyResult) {
        Arduino_UnifiedStorage::testPrint("Copy successful");
    } else {
        Arduino_UnifiedStorage::testPrint("Copy failed");
    }

    // Test moveTo
    Folder sourceFolder =  root.createSubfolder("source");
    Folder destinationFolder = root.createSubfolder("destination");

    Arduino_UnifiedStorage::testPrint("Testing moveTo... ");
    bool moveResult = sourceFolder.moveTo(destinationFolder, true); // Overwrite if exists
    if (moveResult) {
        Arduino_UnifiedStorage::testPrint("Move successful");
    } else {
        Arduino_UnifiedStorage::testPrint("Move failed");
    }

    Folder someFolder = root.createSubfolder("lets_put_files_here");
    UFile someFile = someFolder.createFile("somefile.txt", FileMode::WRITE);

    Folder someOtherFolder = root.createSubfolder("lets_put_files_here");
    UFile someOtherFile = someFolder.createFile("somefile.txt",  FileMode::WRITE);

    bool success = someFile.copyTo(someOtherFolder);
    Arduino_UnifiedStorage::testPrint("trying to copy file without overwrite: " + String(success));

    success = someFile.copyTo(someOtherFolder,true);
    Arduino_UnifiedStorage::testPrint("trying to copy file with overwrite: " + String(success));

}

void loop() {
    // Nothing to do here
}
