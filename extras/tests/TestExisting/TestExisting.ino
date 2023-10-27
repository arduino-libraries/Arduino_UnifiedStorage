
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
    debugPrint("Testing copyTo...");
    Folder sourceFolder2 =  root.createSubfolder("source_folder");
    debugPrint("Folder 1 created");

    debugPrint("Trying to create a folder on top of an existing one... without overwrite");
    Folder sourceFolder3 =  root.createSubfolder("source_folder");
   
    
    debugPrint("Trying to create a folder on top of an existing one... with overwrite");
    Folder sourceFolder4 =  root.createSubfolder("source_folder", true);



    Folder destinationFolder2 = root.createSubfolder("destination_folder");
    debugPrint("Folder 2 created");



    bool copyResult = sourceFolder2.copyTo(destinationFolder2, true); // Overwrite if exists
    if (copyResult) {
        debugPrint("Copy successful");
    } else {
        debugPrint("Copy failed");
    }


    // Test moveTo
    Folder sourceFolder =  root.createSubfolder("source");
    Folder destinationFolder = root.createSubfolder("destination");

    debugPrint("Testing moveTo... ");
    bool moveResult = sourceFolder.moveTo(destinationFolder, true); // Overwrite if exists
    if (moveResult) {
        debugPrint("Move successful");
    } else {
        debugPrint("Move failed");
    }


    Folder someFolder = root.createSubfolder("lets_put_files_here");
    UFile someFile = someFolder.createFile("somefile.txt", FileMode::WRITE);



    Folder someOtherFolder = root.createSubfolder("lets_put_files_here");
    UFile someOtherFile = someFolder.createFile("somefile.txt",  FileMode::WRITE);


    bool success = someFile.copyTo(someOtherFolder);
    debugPrint("trying to copy file without overwrite: " + String(success));

    success = someFile.copyTo(someOtherFolder,true);
    debugPrint("trying to copy file with overwrite: " + String(success));

}

void loop() {
    // Nothing to do here
}
