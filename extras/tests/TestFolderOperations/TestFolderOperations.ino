#include <Arduino_UnifiedStorage.h>

#define HAS_USB 
#define HAS_SD 
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
      Serial.print("  ");
    }
    Serial.print("[D] ");
    Serial.println(subdir.getPath());
    printFolderContents(subdir, indentation + 1);
  }

  // Print files
  for (UFile file : files) {
    for (int i = 0; i < indentation; i++) {
      Serial.print("  ");
    }
    Serial.print("[F] ");
    Serial.println(file.getPath());
  }
}


bool testFolderCreation(Folder root) {
  Folder subfolder = root.createSubfolder("test_folder");
  if (subfolder.exists()) {
    Serial.println("\n--- Test creating folder using root.createSubfolder ---");
    Serial.println("Test creating folder using root.createSubfolder - Success");
    subfolder.remove();
    return true;
  } else {
    Serial.println("Test creating folder using root.createSubfolder - Failed. Error: " + String(getErrno()));
    return false;
  }
}

bool testFolderRenaming(Folder root) {
  Folder sourceFolder = root.createSubfolder("source_folder");
  if (sourceFolder.exists()) {
    Serial.println("\n--- Test renaming folder ---");
    Serial.println("Source folder name: " + String(sourceFolder.getPathString()));
    if (sourceFolder.rename("renamed_folder")) {
      Serial.println("Folder renamed to: " + String(sourceFolder.getPathString()));
      sourceFolder.remove();
      return true;
    } else {
      Serial.println("Folder renaming failed. Error: " + String(getErrno()));
      return false;
    }
  } else {
    Serial.println("Test folder renaming - Failed. Error: " + String(getErrno()));
    return false;
  }
}

bool testCopyingFolder(Folder root) {
  Folder sourceFolder = root.createSubfolder("folder1");
  Folder copyDestination = root.createSubfolder("copy_destination");

  if (sourceFolder.exists()) {
    Serial.println("\n--- Test copying a folder ---");
    Serial.println("Source folder name: " + String(sourceFolder.getPathString()));
    Serial.println("Destination folder name: " + String(copyDestination.getPathString()));

   

    if (sourceFolder.copyTo(copyDestination, true)) {
      Serial.println("Folder copied successfully!");
      sourceFolder.remove();
      copyDestination.remove();
      return true;
    } else {
      Serial.println("Folder copying failed. Error: " + String(getErrno()));
      sourceFolder.remove();
      return false;
    }
  } else {
    Serial.println("Test copying a folder - Failed to create source folder. Error: " + String(getErrno()));
    return false;
  }
}

bool testMovingFolder(Folder root) {


  Folder sourceFolderMove = root.createSubfolder("source_folder_move");
  Folder moveDestination = root.createSubfolder("move_destination");

  if (sourceFolderMove.exists()) {
    Serial.println("\n--- Test moving a folder ---");
    Serial.println("Source folder name: " + String(sourceFolderMove.getPathString()));
    Serial.println("Destination folder name: " + String(moveDestination.getPathString()));
    if (sourceFolderMove.moveTo(moveDestination)) {
      Serial.println("Folder moved successfully!");
      sourceFolderMove.remove();
      moveDestination.remove();
      return true;
    } else {
      Serial.println("Folder moving failed. Error: " + String(getErrno()));
      return false;
    }
  } else {
    Serial.println("Test moving a folder - Failed to create source folder. Error: " + String(getErrno()));
    return false;
  }


}



void runTests(Arduino_UnifiedStorage * storage, String storageType) {
    if (storage->begin()) {
        Folder root = storage->getRootFolder();


        Serial.println("========= Folder Tests =========");

        testFolderCreation(root);
        testFolderRenaming(root);
        testCopyingFolder(root);
        testMovingFolder(root);

        Serial.println("========= FS Contents after Folder Tests =========");
        printFolderContents(root);
        storage->unmount();
        Serial.println();
    }
}

void setup(){
    Serial.begin(115200);
    while(!Serial);
    
    #if defined(HAS_USB)
        runTests(&usb, "USB");
    #endif 

    #if defined(HAS_QSPI)
        runTests(&internal, "QSPI");
    #endif 

    #if defined(HAS_SD)
        runTests(&sd, "SD");
    #endif 

}

void loop(){

}