#include <Arduino_UnifiedStorage.h>

InternalStorage internalStorage = InternalStorage(2, "user", FS_LITTLEFS);


void setup() {
    /* UNCOMMENT THIS PART IF YOU WANT TO ENABLE FORMATTING*/



    Serial.begin(9600);
    delay(1000); // Give time to open the Serial Monitor
    while(!Serial);



    internalStorage.formatLittleFS();
        internalStorage.begin();
   

    Folder root = internalStorage.getRootFolder();
    Serial.println(root.getPathString());

    // Test copyTo
    Serial.println("Testing copyTo...");
    Folder sourceFolder2 =  root.createSubfolder("source_folder");
    Serial.println("Folder 1 created");

    Serial.println("Trying to create a folder on top of an existing one... without overwrite");
    Folder sourceFolder3 =  root.createSubfolder("source_folder");
    
    Serial.println("Trying to create a folder on top of an existing one... with overwrite");
    Folder sourceFolder4 =  root.createSubfolder("source_folder", true);

    Folder destinationFolder2 = root.createSubfolder("destination_folder");
    Serial.println("Folder 2 created");

    Serial.println(sourceFolder2.getPathString());
    Serial.println(destinationFolder2.getPathString());

        Serial.println();
            Serial.println();


    bool copyResult = sourceFolder2.copyTo(destinationFolder2, true); // Overwrite if exists
    if (copyResult) {
        Serial.println("Copy successful");
    } else {
        Serial.println("Copy failed");
    }
    Serial.println();




    // Test moveTo
    Folder sourceFolder =  root.createSubfolder("source");
    Folder destinationFolder = root.createSubfolder("destination");


    Serial.println();
        Serial.println();
    Serial.println("Testing moveTo...");
    bool moveResult = sourceFolder.moveTo(destinationFolder, true); // Overwrite if exists
    if (moveResult) {
        Serial.println("Move successful");
    } else {
        Serial.println("Move failed");
    }


    Folder someFolder = root.createSubfolder("lets_put_files_here");
    UFile someFile = someFolder.createFile("somefile.txt", FileMode::WRITE);



    Folder someOtherFolder = root.createSubfolder("lets_put_files_here");
    UFile someOtherFile = someFolder.createFile("somefile.txt",  FileMode::WRITE);


    bool success = someFile.copyTo(someOtherFolder);
    Serial.println("trying to copy file without overwrite");
    Serial.println(success);

    success = someFile.copyTo(someOtherFolder,true);
    Serial.println("trying to copy file with overwrite");
    Serial.println(success);



}

void loop() {
    // Nothing to do here
}
