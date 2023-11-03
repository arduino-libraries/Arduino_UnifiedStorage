
#define ARDUINO_UNIFIED_STORAGE_DEBUG

#include <Arduino_UnifiedStorage.h>


InternalStorage internalStorage = InternalStorage();

void setup() {
    /* UNCOMMENT THIS PART IF YOU WANT TO ENABLE FORMATTING*/


    #if defined(ARDUINO_PORTENTA_C33) || defined(ARDUINO_PORTENTA_H7_M7)
        Serial.begin(115200);
        while(!Serial);
    #elif defined(ARDUINO_OPTA)
        beginRS485(115200);
    #endif 



    internalStorage.begin();
   

    Folder root = internalStorage.getRootFolder();


    // Test copyTo
    Arduino_UnifiedStorage::debugPrint("Testing copyTo...");
    Folder sourceFolder2 =  root.createSubfolder("source_folder");
    Arduino_UnifiedStorage::debugPrint("Folder 1 created");

    Arduino_UnifiedStorage::debugPrint("Trying to create a folder on top of an existing one... without overwrite");
    Folder sourceFolder3 =  root.createSubfolder("source_folder");
   
    
    Arduino_UnifiedStorage::debugPrint("Trying to create a folder on top of an existing one... with overwrite");
    Folder sourceFolder4 =  root.createSubfolder("source_folder", true);



    Folder destinationFolder2 = root.createSubfolder("destination_folder");
    Arduino_UnifiedStorage::debugPrint("Folder 2 created");



    bool copyResult = sourceFolder2.copyTo(destinationFolder2, true); // Overwrite if exists
    if (copyResult) {
        Arduino_UnifiedStorage::debugPrint("Copy successful");
    } else {
        Arduino_UnifiedStorage::debugPrint("Copy failed");
    }


    // Test moveTo
    Folder sourceFolder =  root.createSubfolder("source");
    Folder destinationFolder = root.createSubfolder("destination");

    Arduino_UnifiedStorage::debugPrint("Testing moveTo... ");
    bool moveResult = sourceFolder.moveTo(destinationFolder, true); // Overwrite if exists
    if (moveResult) {
        Arduino_UnifiedStorage::debugPrint("Move successful");
    } else {
        Arduino_UnifiedStorage::debugPrint("Move failed");
    }


    Folder someFolder = root.createSubfolder("lets_put_files_here");
    UFile someFile = someFolder.createFile("somefile.txt", FileMode::WRITE);



    Folder someOtherFolder = root.createSubfolder("lets_put_files_here");
    UFile someOtherFile = someFolder.createFile("somefile.txt",  FileMode::WRITE);


    bool success = someFile.copyTo(someOtherFolder);
    Arduino_UnifiedStorage::debugPrint("trying to copy file without overwrite: " + String(success));

    success = someFile.copyTo(someOtherFolder,true);
    Arduino_UnifiedStorage::debugPrint("trying to copy file with overwrite: " + String(success));

}

void loop() {
    // Nothing to do here
}
