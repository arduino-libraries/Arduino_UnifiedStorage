#include <Arduino.h>
#include "Arduino_UnifiedStorage.h"

#define HAS_USB 1
#define HAS_SD  1
#define HAS_QSPI 1

#ifdef HAS_USB
USBStorage usb = USBStorage();
#endif

#ifdef HAS_SD
SDStorage sd = SDStorage();
#endif

#ifdef HAS_QSPI 
InternalStorage internal = InternalStorage(2, "user", FS_LITTLEFS);
#endif 

void testMoveAndDelete(Arduino_UnifiedStorage* sourceStorage, Arduino_UnifiedStorage* destinationStorage, const char* storageTypeA, const char* storageTypeB) {



String fileName = "/test_" + String(millis()) + ".txt";
  // Create a file in the source storage
  UFile fileToMove = sourceStorage->getRootFolder().createFile(fileName, FileMode::WRITE);
  fileToMove.write(reinterpret_cast<const uint8_t*>("Test data"), 9);
  fileToMove.close();

  // Move the file to the destination storage
  if (fileToMove.moveTo(destinationStorage->getRootFolder())) {
    Serial.println("Moving from " + String(storageTypeA) + " to " + String(storageTypeB) + " successful");

    // Delete the moved file from the destination storage
    UFile movedFile;
    movedFile.open(destinationStorage->getRootFolder().getPathString() + fileName, FileMode::READ);
    if (movedFile.remove()) {
      Serial.println("File deletion from " + String(storageTypeB) + " successful");
    } else {
      Serial.println("File deletion from " + String(storageTypeB) + " failed");
      Serial.println(getErrno());
    }
  } else {
    Serial.println("Moving from " + String(storageTypeA) + " to " + String(storageTypeB) + " failed");
    Serial.println(getErrno());
  }

  Serial.println();
}


void testCopyAndDelete(Arduino_UnifiedStorage* sourceStorage, Arduino_UnifiedStorage* destinationStorage, const char* storageTypeA, const char* storageTypeB) {



String fileName = "/test_" + String(millis()) + ".txt";
  // Create a file in the source storage
  UFile fileToMove = sourceStorage->getRootFolder().createFile(fileName, FileMode::WRITE);
  fileToMove.write(reinterpret_cast<const uint8_t*>("Test data"), 9);
  fileToMove.close();

  // Move the file to the destination storage
  if (fileToMove.copyTo(destinationStorage->getRootFolder())) {
    Serial.println("Copying from " + String(storageTypeA) + " to " + String(storageTypeB) + " successful");

    // Delete the moved file from the destination storage
    UFile movedFile;
    movedFile.open(destinationStorage->getRootFolder().getPathString() + fileName, FileMode::READ);
    if (movedFile.remove()) {
      Serial.println("File deletion from " + String(storageTypeB) + " successful");
    } else {
      Serial.println("File deletion from " + String(storageTypeB) + " failed");
      Serial.println(getErrno());
    }
  } else {
    Serial.println("Moving from " + String(storageTypeA) + " to " + String(storageTypeB) + " failed");
    Serial.println(getErrno());
  }

fileToMove.remove();
  Serial.println();

}

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

void runRepeatedMountTest(Arduino_UnifiedStorage * storage, String storageType, int n = 10){
  Serial.println("Running repeated mount test for " + storageType);

  for(size_t i=0;i<n;i++){
    int mountResult = storage->begin();

    Serial.println("Mounting drive");
    if(mountResult != 1) {
      Serial.println(mountResult);
      Serial.println(getErrno());
    }

    Folder root = storage->getRootFolder();
    UFile file = root.createFile("file.txt", FileMode::WRITE);
    file.write("writing stuff to the file");
    file.changeMode(FileMode::READ);
    Serial.println(file.readAsString());
    file.close();
    file.remove();

    int umountResult = storage->unmount();
    if(!umountResult) {
      Serial.println("Unmounting drive");
      Serial.println(umountResult);
      Serial.println(getErrno());
    } else {
      Serial.println("Succesfully unmounted");
    }
  }
}

void setup() {
    Serial.begin(9600);
    while (!Serial); 




    Serial.println("Formatting all attached drives...");
    Serial.println("Formatting USB drive: " + String(usb.formatLittleFS()));
    Serial.println("Formatting SD drive: " + String(sd.formatFAT()));
    Serial.println("Formatting Internal drive: " + String(internal.formatLittleFS()));

 
    
    runRepeatedMountTest(&usb, "USB");
    runRepeatedMountTest(&sd, "SD");
    runRepeatedMountTest(&internal, "QSPI");



    runTests(&usb, "USB Storage");
    runTests(&internal, "Internal Storage (QSPI)");
    runTests(&sd, "SD Storage");


    delay(1000);



    usb.begin();
    sd.begin();
    internal.begin();

    testMoveAndDelete(&sd, &internal, "SD", "Internal");
    testMoveAndDelete(&internal, &sd, "Internal", "SD");
    testMoveAndDelete(&usb, &sd, "USB", "SD");
    testMoveAndDelete(&sd, &usb, "SD", "USB");
    testMoveAndDelete(&usb, &internal, "USB", "Internal");
    testMoveAndDelete(&internal, &usb, "Internal", "USB");


    testCopyAndDelete(&sd, &internal, "SD", "Internal");
    testCopyAndDelete(&internal, &sd, "Internal", "SD");
    testCopyAndDelete(&usb, &sd, "USB", "SD");
    testCopyAndDelete(&sd, &usb, "SD", "USB");
    testCopyAndDelete(&usb, &internal, "USB", "Internal");
    testCopyAndDelete(&internal, &usb, "Internal", "USB");

    usb.unmount();
    sd.unmount();
    internal.unmount();

}

void loop() {
}

void clearData(Folder root){

  for(UFile f : root.getFiles()){
      f.remove();
    }

  for(Folder d: root.getFolders()){
      d.remove(); 
  }

}



void runTests(Arduino_UnifiedStorage * storage, String storageType) {

 

  if (storage->begin()) {

    
    Folder root = storage->getRootFolder();
   // clearData(root);
  
    Serial.println("=== Testing " + storageType + " ===");
    
    Serial.println("========= UFile Tests =========");

    testFileCreationWithOpen(root);
    testFileCreationWithCreate(root);
    testWritingCharBuffer(root);
    testWritingWithString(root);
    testAppending(root);
    testReadingAll(root);
    testSeeking(root);
    testAvailableData(root);
    testCopyingFile(root);
    testMovingFile(root);

    Serial.println("========= FS Contents after UFile Tests =========");
    printFolderContents(root);
    Serial.println("=============================\n");

    Serial.println("========= Folder Tests =========");

    testFolderCreation(root);
    testFolderRenaming(root);
    testCopyingFolder(root);
    testMovingFolder(root);

    Serial.println("========= FS Contents after Folder Tests =========");
    printFolderContents(root);
    Serial.println("=============================\n");
   storage->unmount();

  } else {
    Serial.println(storageType + " not initialized!");
  }

}

bool testFileCreationWithOpen(Folder root) {
  UFile file = UFile();
  String path = root.getPathString() + "/test_open.txt";
  Serial.println(path);
  if (file.open(path, FileMode::WRITE)) {
    Serial.println("\n--- Test creating file using file.open ---");
    Serial.println("Test creating file using file.open - Success");
    file.close();
    file.remove();
    return true;
  } else {
    Serial.println("Test creating file using file.open - Failed. Error: " + String(getErrno()));
    return false;
  }

}

bool testFileCreationWithCreate(Folder root) {
  Serial.println("\n--- Test creating file using root.createFile ---");
  UFile file = root.createFile("test_create.txt", FileMode::WRITE);
  if (file.exists()) {
    Serial.println("Test creating file using root.createFile - Success");
    file.close();
    file.remove();
    return true;
  } else {
    Serial.println("Test creating file using root.createFile - Failed. Error: " + String(getErrno()));
    return false;
  }
}

bool testWritingCharBuffer(Folder root) {
  UFile file = root.createFile("test_write.txt", FileMode::WRITE);
  if (file.exists()) {
    Serial.println("\n--- Test writing char * buffer ---");
    size_t bytesWritten = file.write(reinterpret_cast<const uint8_t*>("Hello, World!"), 13);
    Serial.println("Bytes written to file: " + String(bytesWritten));
    file.close();
    file.remove();
    return bytesWritten == 13;
  } else {
    Serial.println("Test writing char * buffer - Failed. Error: " + String(getErrno()));
    return false;
  }
}

bool testWritingWithString(Folder root) {
  UFile file = root.createFile("test_write_string.txt", FileMode::WRITE);
  if (file.exists()) {
    Serial.println("\n--- Test writing String ---");
    String data = " This is a test with String data.";
    size_t bytesWritten = file.write(data);
    Serial.println("Bytes written to file (with String): " + String(bytesWritten));
    file.close();
    file.remove();
    return true;

  } else {
    Serial.println("Test writing with String data type - Failed. Error: " + String(getErrno()));
    return false;
  }
  
}

bool testAppending(Folder root) {
  UFile file = root.createFile("test_append.txt", FileMode::WRITE);
  if (file.exists()) {
    Serial.println("\n--- Test appending ---");
    String data = " Appending some more data.";
    size_t bytesWritten = file.write(reinterpret_cast<const uint8_t*>(data.c_str()), data.length());
    Serial.println("Bytes written to file (appending): " + String(bytesWritten));
    file.close();
    file.remove();
    return true;
  } else {
    Serial.println("Test appending to the file - Failed. Error: " + String(getErrno()));
    return false;
  }
}

bool testReadingAll(Folder root) {
  UFile file = root.createFile("test_read.txt", FileMode::WRITE);
  if (file.exists()) {
    file.write(reinterpret_cast<const uint8_t*>("Hello, World!"), 13);
    file.close();

    if (file.open(root.getPathString() + "/test_read.txt", FileMode::READ)) {
      char buffer[file.available()];
      size_t bytesRead = file.read(reinterpret_cast<uint8_t*>(buffer), sizeof(buffer));
      buffer[bytesRead] = '\0'; // Null-terminate the string
      Serial.println("\n--- Test reading everything from the file ---");
      Serial.println("Read from file (test_read.txt): " + String(buffer));
      Serial.println("error at print? cplm ");
      file.close();

      file.remove();

      return true;
    } else {
      Serial.println("Test reading everything from the file - Failed. Error: " + String(getErrno()));
      return false;
    }
  } else {
    Serial.println("Test reading everything from the file - Failed to create file. Error: " + String(getErrno()));
    return false;
  
  }

  return false;
}

bool testSeeking(Folder root) {

  UFile file = root.createFile("test_seek.txt", FileMode::WRITE);
  if (file.exists()) {
    file.write(reinterpret_cast<const uint8_t*>("Hello, World!"), 13);
    file.close();
 

    if (file.open(root.getPathString() + "/test_seek.txt", FileMode::READ)) {
      Serial.println("\n--- Test seeking file ---");
      file.seek(7);
      char buffer[20];
      size_t bytesRead = file.read(reinterpret_cast<uint8_t*>(buffer), sizeof(buffer));
      buffer[bytesRead] = '\0'; // Null-terminate the string
      Serial.println("Read after seeking: " + String(buffer));
      file.close();
      file.remove();
      return true;
    } else {
      Serial.println("Test seeking in the file - Failed. Error: " + String(getErrno()));
      return false;
    }
  } else {
    Serial.println("Test seeking in the file - Failed to create file. Error: " + String(getErrno()));
    return false;
  }
  
}

bool testAvailableData(Folder root) {
  UFile file = root.createFile("test_available.txt", FileMode::WRITE);
  if (file.exists()) {
    file.write(reinterpret_cast<const uint8_t*>("Hello, World!"), 13);
    file.close();

    if (file.open(root.getPathString() + "/test_available.txt", FileMode::READ)) {
      Serial.println("\n--- Test available data ---");
      int availableBytes = file.available();
      Serial.println("Available bytes in file (test_available.txt): " + String(availableBytes));
      file.close();
      file.remove();
      return true;
    } else {
      Serial.println("Test checking available data in the file - Failed. Error: " + String(getErrno()));
      return false;
    }
  } else {
    Serial.println("Test checking available data in the file - Failed to create file. Error: " + String(getErrno()));
    return false;
  }

  return false;
}

bool testCopyingFile(Folder root) {
    // Test copying a file
  UFile sourceFile = root.createFile("test_source_copy.txt", FileMode::WRITE);
  if (sourceFile.exists()) {
    sourceFile.write(reinterpret_cast<const uint8_t*>("Hello, World!"), 13);
    sourceFile.close();

    Folder destinationFolder = root.createSubfolder("test_folder_copy");

    if (destinationFolder.exists()) {
        Serial.println("\n--- Test copying a file ---");
        Serial.println("Source file name: " + String(sourceFile.getPathString()));
        
        if (sourceFile.copyTo(destinationFolder)) {
          Serial.println("File copied successfully!");
          sourceFile.close();
          sourceFile.remove();
          destinationFolder.remove();
          return true;
        } else {
          Serial.println("File copying failed. Error: " + String(getErrno()));
          return false;
        }
      } else {
        Serial.println("Test copying a file - Failed. Error: " + String(getErrno()));
        return false;
      }

    } else {
      Serial.println("Test copying a file - Failed to create destination folder. Error: " + String(getErrno()));
      return false;
    }
}

bool testMovingFile(Folder root) {
  UFile sourceFileMove = root.createFile("test_source_move.txt", FileMode::WRITE);
  if (sourceFileMove.exists()) {
    sourceFileMove.write(reinterpret_cast<const uint8_t*>("Hello, World!"), 13);
    sourceFileMove.close();

    Folder destinationFolder = root.createSubfolder("test_folder_move");
    if (destinationFolder.exists()) {
      UFile movedFile = sourceFileMove;
      if (movedFile.exists()) {
        Serial.println("\n--- Test moving a file ---");
        Serial.println("Source file name: " + String(sourceFileMove.getPathString()));
        Serial.println("Destination file name: " + String(destinationFolder.getPathString()) + "/test_source_move.txt");
        if (sourceFileMove.moveTo(destinationFolder)) {
          Serial.println("File moved successfully!");
          sourceFileMove.close();
          movedFile.close();
          movedFile.remove();
          destinationFolder.remove();
          sourceFileMove.remove();
          return true;
        } else {
          Serial.println("File moving failed. Error: " + String(getErrno()));
          return false;
        }
      } else {
        Serial.println("Test moving a file - Failed. Error: " + String(getErrno()));
        return false;
      }
    } else {
      Serial.println("Test moving a file - Failed to create destination folder. Error: " + String(getErrno()));
      return false;
    }
  } else {
    Serial.println("Test moving a file - Failed. Error: " + String(getErrno()));
    return false;
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
  copyDestination.createSubfolder("folder1");

  if (sourceFolder.exists()) {
    Serial.println("\n--- Test copying a folder ---");
    Serial.println("Source folder name: " + String(sourceFolder.getPathString()));
    Serial.println("Destination folder name: " + String(copyDestination.getPathString()));

   

    if (sourceFolder.copyTo(copyDestination, false)) {
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

