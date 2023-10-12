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
      printToSerialOrRS485("  ");
    }
    printToSerialOrRS485("[D] ");
    printToSerialOrRS485(subdir.getPath());
    printFolderContents(subdir, indentation + 1);
  }

  // Print files
  for (UFile file : files) {
    for (int i = 0; i < indentation; i++) {
      printToSerialOrRS485("  ");
    }
    printToSerialOrRS485("[F] ");
    printToSerialOrRS485(file.getPath());
  }
}


bool testFolderCreation(Folder root) {
  Folder subfolder = root.createSubfolder("test_folder");
  if (subfolder.exists()) {
    printToSerialOrRS485("\n--- Test creating folder using root.createSubfolder ---");
    printToSerialOrRS485("Test creating folder using root.createSubfolder - Success");
    subfolder.remove();
    return true;
  } else {
    printToSerialOrRS485("Test creating folder using root.createSubfolder - Failed. Error: " + String(getErrno()));
    return false;
  }
}

bool testFolderRenaming(Folder root) {
  Folder sourceFolder = root.createSubfolder("source_folder");
  if (sourceFolder.exists()) {
    printToSerialOrRS485("\n--- Test renaming folder ---");
    printToSerialOrRS485("Source folder name: " + String(sourceFolder.getPathAsString()));
    if (sourceFolder.rename("renamed_folder")) {
      printToSerialOrRS485("Folder renamed to: " + String(sourceFolder.getPathAsString()));
      sourceFolder.remove();
      return true;
    } else {
      printToSerialOrRS485("Folder renaming failed. Error: " + String(getErrno()));
      return false;
    }
  } else {
    printToSerialOrRS485("Test folder renaming - Failed. Error: " + String(getErrno()));
    return false;
  }
}

bool testCopyingFolder(Folder root) {
  Folder sourceFolder = root.createSubfolder("folder1");
  Folder copyDestination = root.createSubfolder("copy_destination");

  if (sourceFolder.exists()) {
    printToSerialOrRS485("\n--- Test copying a folder ---");
    printToSerialOrRS485("Source folder name: " + String(sourceFolder.getPathAsString()));
    printToSerialOrRS485("Destination folder name: " + String(copyDestination.getPathAsString()));

   

    if (sourceFolder.copyTo(copyDestination, true)) {
      printToSerialOrRS485("Folder copied successfully!");
      sourceFolder.remove();
      copyDestination.remove();
      return true;
    } else {
      printToSerialOrRS485("Folder copying failed. Error: " + String(getErrno()));
      sourceFolder.remove();
      return false;
    }
  } else {
    printToSerialOrRS485("Test copying a folder - Failed to create source folder. Error: " + String(getErrno()));
    return false;
  }
}

bool testMovingFolder(Folder root) {


  Folder sourceFolderMove = root.createSubfolder("source_folder_move");
  Folder moveDestination = root.createSubfolder("move_destination");

  if (sourceFolderMove.exists()) {
    printToSerialOrRS485("\n--- Test moving a folder ---");
    printToSerialOrRS485("Source folder name: " + String(sourceFolderMove.getPathAsString()));
    printToSerialOrRS485("Destination folder name: " + String(moveDestination.getPathAsString()));
    if (sourceFolderMove.moveTo(moveDestination)) {
      printToSerialOrRS485("Folder moved successfully!");
      sourceFolderMove.remove();
      moveDestination.remove();
      return true;
    } else {
      printToSerialOrRS485("Folder moving failed. Error: " + String(getErrno()));
      return false;
    }
  } else {
    printToSerialOrRS485("Test moving a folder - Failed to create source folder. Error: " + String(getErrno()));
    return false;
  }


}



void runTests(Arduino_UnifiedStorage * storage, String storageType) {
    if (storage->begin()) {
        Folder root = storage->getRootFolder();


        printToSerialOrRS485("========= Folder Tests =========");

        testFolderCreation(root);
        testFolderRenaming(root);
        testCopyingFolder(root);
        testMovingFolder(root);

        printToSerialOrRS485("========= FS Contents after Folder Tests =========");
        printFolderContents(root);
        storage->unmount();
        printToSerialOrRS485("");
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