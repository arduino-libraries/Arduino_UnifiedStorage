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




    internalStorage.format(FS_LITTLEFS);
    internalStorage.begin();
   c

    Folder root = internalStorage.getRootFolder();


    // Test copyTo
    printToSerialOrRS485("Testing copyTo... \n");
    Folder sourceFolder2 =  root.createSubfolder("source_folder");
    printToSerialOrRS485("Folder 1 created \n");

    printToSerialOrRS485("Trying to create a folder on top of an existing one... without overwrite \n");
    Folder sourceFolder3 =  root.createSubfolder("source_folder");
    
    printToSerialOrRS485("Trying to create a folder on top of an existing one... with overwrite \n");
    Folder sourceFolder4 =  root.createSubfolder("source_folder", true);

    Folder destinationFolder2 = root.createSubfolder("destination_folder");
    printToSerialOrRS485("Folder 2 created \n");



    bool copyResult = sourceFolder2.copyTo(destinationFolder2, true); // Overwrite if exists
    if (copyResult) {
        printToSerialOrRS485("Copy successful \n");
    } else {
        printToSerialOrRS485("Copy failed \n");
    }




    // Test moveTo
    Folder sourceFolder =  root.createSubfolder("source");
    Folder destinationFolder = root.createSubfolder("destination");

    printToSerialOrRS485("Testing moveTo...  \n");
    bool moveResult = sourceFolder.moveTo(destinationFolder, true); // Overwrite if exists
    if (moveResult) {
        printToSerialOrRS485("Move successful \n");
    } else {
        printToSerialOrRS485("Move failed \n");
    }


    Folder someFolder = root.createSubfolder("lets_put_files_here");
    UFile someFile = someFolder.createFile("somefile.txt", FileMode::WRITE);



    Folder someOtherFolder = root.createSubfolder("lets_put_files_here");
    UFile someOtherFile = someFolder.createFile("somefile.txt",  FileMode::WRITE);


    bool success = someFile.copyTo(someOtherFolder);
    printToSerialOrRS485("trying to copy file without overwrite: %d\n", success);

    success = someFile.copyTo(someOtherFolder,true);
    printToSerialOrRS485("trying to copy file with overwrite: %d \n", success);

}

void loop() {
    // Nothing to do here
}
