#define ARDUINO_UNIFIED_STORAGE_DEBUG

#include <Arduino_UnifiedStorage.h>
#include "Boards.h"
#include "Utils.h"



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
    debugPrint("\n--- Test creating folder using root.createSubfolder ---");
    debugPrint("Test creating folder using root.createSubfolder - Success");
    subfolder.remove();
    return true;
  } else {
    debugPrint("Test creating folder using root.createSubfolder - Failed. Error: " + String(getErrno()));
    return false;
  }
}

bool testFolderRenaming(Folder root) {
  Folder sourceFolder = root.createSubfolder("source_folder");
  if (sourceFolder.exists()) {
    debugPrint("\n--- Test renaming folder ---");
    debugPrint("Source folder name: " + String(sourceFolder.getPathAsString()));
    if (sourceFolder.rename("renamed_folder")) {
      debugPrint("Folder renamed to: " + String(sourceFolder.getPathAsString()));
      sourceFolder.remove();
      return true;
    } else {
      debugPrint("Folder renaming failed. Error: " + String(getErrno()));
      return false;
    }
  } else {
    debugPrint("Test folder renaming - Failed. Error: " + String(getErrno()));
    return false;
  }
}

bool testCopyingFolder(Folder root) {
  Folder sourceFolder = root.createSubfolder("folder1");
  Folder copyDestination = root.createSubfolder("copy_destination");

  if (sourceFolder.exists()) {
    debugPrint("\n--- Test copying a folder ---");
    debugPrint("Source folder name: " + String(sourceFolder.getPathAsString()));
    debugPrint("Destination folder name: " + String(copyDestination.getPathAsString()));

   

    if (sourceFolder.copyTo(copyDestination, true)) {
      debugPrint("Folder copied successfully!");
      sourceFolder.remove();
      copyDestination.remove();
      return true;
    } else {
      debugPrint("Folder copying failed. Error: " + String(getErrno()));
      sourceFolder.remove();
      return false;
    }
  } else {
    debugPrint("Test copying a folder - Failed to create source folder. Error: " + String(getErrno()));
    return false;
  }
}

bool testMovingFolder(Folder root) {


  Folder sourceFolderMove = root.createSubfolder("source_folder_move");
  Folder moveDestination = root.createSubfolder("move_destination");

  if (sourceFolderMove.exists()) {
    debugPrint("\n--- Test moving a folder ---");
    debugPrint("Source folder name: " + String(sourceFolderMove.getPathAsString()));
    debugPrint("Destination folder name: " + String(moveDestination.getPathAsString()));
    if (sourceFolderMove.moveTo(moveDestination)) {
      debugPrint("Folder moved successfully!");
      sourceFolderMove.remove();
      moveDestination.remove();
      return true;
    } else {
      debugPrint("Folder moving failed. Error: " + String(getErrno()));
      return false;
    }
  } else {
    debugPrint("Test moving a folder - Failed to create source folder. Error: " + String(getErrno()));
    return false;
  }


}



void runTests(Arduino_UnifiedStorage * storage, String storageType) {
    if (storage->begin()) {
        Folder root = storage->getRootFolder();


        debugPrint("========= Folder Tests =========");

        testFolderCreation(root);
        testFolderRenaming(root);
        testCopyingFolder(root);
        testMovingFolder(root);

        storage->unmount();
        debugPrint("");
    }
}

void setup(){
    #if defined(ARDUINO_PORTENTA_C33) || defined(ARDUINO_PORTENTA_H7_M7)
        Serial.begin(115200);
        while(!Serial);
    #elif defined(ARDUINO_OPTA)
        beginRS485(115200);
    #endif 

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