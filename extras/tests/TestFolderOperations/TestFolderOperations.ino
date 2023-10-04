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

void printFolderContents(Folder dir, int indentation = 0) {
  std::vector<Folder> directories = dir.getFolders();
  std::vector<UFile>files = dir.getFiles();

  // Print directories
  for (Folder subdir : directories) {
    for (int i = 0; i < indentation; i++) {
      printFormatted("  ");
    }
    printFormatted("[D] ");
    printFormatted(subdir.getPath());
    printFolderContents(subdir, indentation + 1);
  }

  // Print files
  for (UFile file : files) {
    for (int i = 0; i < indentation; i++) {
      printFormatted("  ");
    }
    printFormatted("[F] ");
    printFormatted(file.getPath());
  }
}


bool testFolderCreation(Folder root) {
  Folder subfolder = root.createSubfolder("test_folder");
  if (subfolder.exists()) {
    printFormatted("\n--- Test creating folder using root.createSubfolder ---");
    printFormatted("Test creating folder using root.createSubfolder - Success");
    subfolder.remove();
    return true;
  } else {
    printFormatted("Test creating folder using root.createSubfolder - Failed. Error: " + String(getErrno()));
    return false;
  }
}

bool testFolderRenaming(Folder root) {
  Folder sourceFolder = root.createSubfolder("source_folder");
  if (sourceFolder.exists()) {
    printFormatted("\n--- Test renaming folder ---");
    printFormatted("Source folder name: " + String(sourceFolder.getPathAsString()));
    if (sourceFolder.rename("renamed_folder")) {
      printFormatted("Folder renamed to: " + String(sourceFolder.getPathAsString()));
      sourceFolder.remove();
      return true;
    } else {
      printFormatted("Folder renaming failed. Error: " + String(getErrno()));
      return false;
    }
  } else {
    printFormatted("Test folder renaming - Failed. Error: " + String(getErrno()));
    return false;
  }
}

bool testCopyingFolder(Folder root) {
  Folder sourceFolder = root.createSubfolder("folder1");
  Folder copyDestination = root.createSubfolder("copy_destination");

  if (sourceFolder.exists()) {
    printFormatted("\n--- Test copying a folder ---");
    printFormatted("Source folder name: " + String(sourceFolder.getPathAsString()));
    printFormatted("Destination folder name: " + String(copyDestination.getPathAsString()));

   

    if (sourceFolder.copyTo(copyDestination, true)) {
      printFormatted("Folder copied successfully!");
      sourceFolder.remove();
      copyDestination.remove();
      return true;
    } else {
      printFormatted("Folder copying failed. Error: " + String(getErrno()));
      sourceFolder.remove();
      return false;
    }
  } else {
    printFormatted("Test copying a folder - Failed to create source folder. Error: " + String(getErrno()));
    return false;
  }
}

bool testMovingFolder(Folder root) {


  Folder sourceFolderMove = root.createSubfolder("source_folder_move");
  Folder moveDestination = root.createSubfolder("move_destination");

  if (sourceFolderMove.exists()) {
    printFormatted("\n--- Test moving a folder ---");
    printFormatted("Source folder name: " + String(sourceFolderMove.getPathAsString()));
    printFormatted("Destination folder name: " + String(moveDestination.getPathAsString()));
    if (sourceFolderMove.moveTo(moveDestination)) {
      printFormatted("Folder moved successfully!");
      sourceFolderMove.remove();
      moveDestination.remove();
      return true;
    } else {
      printFormatted("Folder moving failed. Error: " + String(getErrno()));
      return false;
    }
  } else {
    printFormatted("Test moving a folder - Failed to create source folder. Error: " + String(getErrno()));
    return false;
  }


}



void runTests(Arduino_UnifiedStorage * storage, String storageType) {
    if (storage->begin()) {
        Folder root = storage->getRootFolder();


        printFormatted("========= Folder Tests =========");

        testFolderCreation(root);
        testFolderRenaming(root);
        testCopyingFolder(root);
        testMovingFolder(root);

        printFormatted("========= FS Contents after Folder Tests =========");
        printFolderContents(root);
        storage->unmount();
        printFormatted("");
    }
}

void setup(){
    #if defined(ARDUINO_PORTENTA_C33) || defined(ARDUINO_PORTENTA_H7_M7)
        Serial.begin(115200);
        while(!Serial);
    #elif defined(ARDUINO_OPTA)
        beginRS485(115200);
    #endif 

    
    #if defined(HAS_USB)
        runTests(&usb, "USB");
    #endif 

    #if defined(HAS_QSPI)
        runTests(&internal, "QSPI");
    #endif 

    #if defined(HAS_SD)
        runTests(&&sd, "SD");
    #endif 

}

void loop(){

}