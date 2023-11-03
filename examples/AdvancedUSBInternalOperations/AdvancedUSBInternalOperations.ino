/*
    AdvancedUSBInternalOperations

    Demonstrates advanced usage of the "Arduino_UnifiedStorage" library with USB & internal storage, including file operations.
    Creates, copies, and moves files between storage types, and prints folder contents.

    In the setup function, the code initializes serial communication, mounts both USB & internal storage and 
    reformats the internal storage for a clean file system. Then, it creates a root directory in the internal storage
    and creates a subdirectory with a file inside it containing the string "Hello World!".

    Then, it copies the file from internal storage to USB storage and moves the subdirectory from internal storage to USB storage.

    After the file operations, the code prints the contents of both the USB storage and the internal storage. 
    It recursively prints the directories (marked as "[D]") and files (marked as "[F]") using the "printFolderContents" function.
    
    Created 28th July 2023
    By Cristian Dragomir

    Modified 24th August 2023
    By Ali Jahangiri

    https://github.com/arduino-libraries/Arduino_UnifiedStorage/blob/main/examples/SimpleStorageWriteRead/SimpleStorageWriteRead.ino

*/
#include "Arduino_UnifiedStorage.h"

// Two instances are made for the USB and internal storage respectively
USBStorage usbStorage;
InternalStorage internalStorage;


// Helper function to prints the contents of a folder, including subdirectories (marked as "[D]") and files (marked as "[F]").
void printFolderContents(Folder dir, int indentation = 0) {
  std::vector<Folder> directories = dir.getFolders();
  std::vector<UFile> files = dir.getFiles();

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



void setup() {
  Serial.begin(115200);
  while (!Serial);

  // toggle this to enable debugging output
  Arduino_UnifiedStorage::debuggingModeEnabled = false;

  usbStorage = USBStorage();
  internalStorage = InternalStorage();

  // Mount the USB storage
  if(usbStorage.begin()){
    Serial.println("USB storage mounted.");
  } else {
    Serial.println(errno);
  }

  if(internalStorage.begin()){
      Serial.println("Internal storage mounted.");
  } else {
     Serial.println(errno);
  }

  // Create a root directory in the internal storage
  Folder root = internalStorage.getRootFolder();

  // Create a subdirectory and a file (file.txt) inside the root directory
  Folder subdir = root.createSubfolder("subdir");
  UFile file = root.createFile("file.txt", FileMode::WRITE);

  // Write "Hello World!" inside file.txt
  file.write("Hello, world!");
  file.close();

  // Copy the file from internal storage to USB storage
  bool success = file.copyTo(usbStorage.getRootFolder(), true);
  if (success) {
    Serial.println("File copied successfully from internal storage to USB storage.");
  } else {
    Serial.println("Failed to copy file from internal storage to USB storage.");
    Serial.println(getErrno());
  }

  // Move the subdirectory from internal storage to USB storage
  success = subdir.moveTo(usbStorage.getRootFolder(), true);
  if (success) {
    Serial.println("Subdirectory moved successfully from internal storage to USB storage.");
  } else {
    Serial.println("Failed to move subdirectory from internal storage to USB storage.");
    Serial.println(getErrno());
  }

  // Print contents of the USB storage
  //Serial.println("USB storage contents:");
  //printFolderContents(usbStorage.getRootFolder());

  // Print contents of the internal storage
  Serial.println("Internal storage contents:");
  printFolderContents(internalStorage.getRootFolder());
}

void loop() {
  // Nothing to do here
}
