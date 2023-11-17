
#define ARDUINO_UNIFIED_STORAGE_DEBUG
#include <Arduino_UnifiedStorage.h>

#if defined(HAS_USB)
USBStorage usb = USBStorage();
#endif

#if defined(HAS_SD)
SDStorage sd = SDStorage();
#endif

#if defined(HAS_QSPI)
InternalStorage internal = InternalStorage();
#endif



bool testFolderCreation(Folder root) {
  Folder subfolder = root.createSubfolder("test_folder");
  if (subfolder.exists()) {
    Arduino_UnifiedStorage::testPrint("\n--- Test creating folder using root.createSubfolder ---");
    Arduino_UnifiedStorage::testPrint("Test creating folder using root.createSubfolder - Success");
    subfolder.remove();
    return true;
  } else {
    Arduino_UnifiedStorage::testPrint("Test creating folder using root.createSubfolder - Failed. Error: " + String(getErrno()));
    return false;
  }
}

bool testFolderRenaming(Folder root) {
  Folder sourceFolder = root.createSubfolder("source_folder");
  if (sourceFolder.exists()) {
    Arduino_UnifiedStorage::testPrint("\n--- Test renaming folder ---");
    Arduino_UnifiedStorage::testPrint("Source folder name: " + String(sourceFolder.getPathAsString()));
    if (sourceFolder.rename("renamed_folder")) {
      Arduino_UnifiedStorage::testPrint("Folder renamed to: " + String(sourceFolder.getPathAsString()));
      sourceFolder.remove();
      return true;
    } else {
      Arduino_UnifiedStorage::testPrint("Folder renaming failed. Error: " + String(getErrno()));
      return false;
    }
  } else {
    Arduino_UnifiedStorage::testPrint("Test folder renaming - Failed. Error: " + String(getErrno()));
    return false;
  }
}

bool testCopyingFolder(Folder root) {
  Folder sourceFolder = root.createSubfolder("folder1");
  Folder copyDestination = root.createSubfolder("copy_destination");

  if (sourceFolder.exists()) {
    Arduino_UnifiedStorage::testPrint("\n--- Test copying a folder ---");
    Arduino_UnifiedStorage::testPrint("Source folder name: " + String(sourceFolder.getPathAsString()));
    Arduino_UnifiedStorage::testPrint("Destination folder name: " + String(copyDestination.getPathAsString()));

   

    if (sourceFolder.copyTo(copyDestination, true)) {
      Arduino_UnifiedStorage::testPrint("Folder copied successfully!");
      sourceFolder.remove();
      copyDestination.remove();
      return true;
    } else {
      Arduino_UnifiedStorage::testPrint("Folder copying failed. Error: " + String(getErrno()));
      sourceFolder.remove();
      return false;
    }
  } else {
    Arduino_UnifiedStorage::testPrint("Test copying a folder - Failed to create source folder. Error: " + String(getErrno()));
    return false;
  }
}

bool testMovingFolder(Folder root) {


  Folder sourceFolderMove = root.createSubfolder("source_folder_move");
  Folder moveDestination = root.createSubfolder("move_destination");

  if (sourceFolderMove.exists()) {
    Arduino_UnifiedStorage::testPrint("\n--- Test moving a folder ---");
    Arduino_UnifiedStorage::testPrint("Source folder name: " + String(sourceFolderMove.getPathAsString()));
    Arduino_UnifiedStorage::testPrint("Destination folder name: " + String(moveDestination.getPathAsString()));
    if (sourceFolderMove.moveTo(moveDestination)) {
      Arduino_UnifiedStorage::testPrint("Folder moved successfully!");
      sourceFolderMove.remove();
      moveDestination.remove();
      return true;
    } else {
      Arduino_UnifiedStorage::testPrint("Folder moving failed. Error: " + String(getErrno()));
      return false;
    }
  } else {
    Arduino_UnifiedStorage::testPrint("Test moving a folder - Failed to create source folder. Error: " + String(getErrno()));
    return false;
  }


}



void runTests(Arduino_UnifiedStorage * storage, String storageType) {
    if (storage->begin()) {
        Folder root = storage->getRootFolder();
        Arduino_UnifiedStorage::testPrint("========= Folder Tests =========");

        testFolderCreation(root);
        testFolderRenaming(root);
        testCopyingFolder(root);
        testMovingFolder(root);

        storage->unmount();
        Arduino_UnifiedStorage::testPrint("");
    }
}

void setup(){
    #if defined(HAS_SERIAL)
        Serial.begin(115200);
        while(!Serial);
    #elif defined(HAS_RS485)
        beginRS485(115200);
    #endif 


    // toggle this to enable debugging output
    Arduino_UnifiedStorage::debuggingModeEnabled = false;

    #if defined(HAS_QSPI)
        runTests(&internal, "QSPI");
    #endif 

    #if defined(HAS_USB)
        runTests(&usb, "USB");
    #endif 

    #if defined(HAS_SD)
        runTests(&sd, "SD");
    #endif 

}

void loop(){

}