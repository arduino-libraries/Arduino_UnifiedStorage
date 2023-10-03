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
   

    Folder root = internalStorage.getRootFolder();


    // Test copyTo
    printFormatted("Testing copyTo... \n");
    Folder sourceFolder2 =  root.createSubfolder("source_folder");
    printFormatted("Folder 1 created \n");

    printFormatted("Trying to create a folder on top of an existing one... without overwrite \n");
    Folder sourceFolder3 =  root.createSubfolder("source_folder");
    
    printFormatted("Trying to create a folder on top of an existing one... with overwrite \n");
    Folder sourceFolder4 =  root.createSubfolder("source_folder", true);

    Folder destinationFolder2 = root.createSubfolder("destination_folder");
    printFormatted("Folder 2 created \n");



    bool copyResult = sourceFolder2.copyTo(destinationFolder2, true); // Overwrite if exists
    if (copyResult) {
        printFormatted("Copy successful \n");
    } else {
        printFormatted("Copy failed \n");
    }




    // Test moveTo
    Folder sourceFolder =  root.createSubfolder("source");
    Folder destinationFolder = root.createSubfolder("destination");

    printFormatted("Testing moveTo...  \n");
    bool moveResult = sourceFolder.moveTo(destinationFolder, true); // Overwrite if exists
    if (moveResult) {
        printFormatted("Move successful \n");
    } else {
        printFormatted("Move failed \n");
    }


    Folder someFolder = root.createSubfolder("lets_put_files_here");
    UFile someFile = someFolder.createFile("somefile.txt", FileMode::WRITE);



    Folder someOtherFolder = root.createSubfolder("lets_put_files_here");
    UFile someOtherFile = someFolder.createFile("somefile.txt",  FileMode::WRITE);


    bool success = someFile.copyTo(someOtherFolder);
    printFormatted("trying to copy file without overwrite: %d\n", success);

    success = someFile.copyTo(someOtherFolder,true);
    printFormatted("trying to copy file with overwrite: %d \n", success);

}

void loop() {
    // Nothing to do here
}
