/*
This example demonstrates the usage of the "UnifiedStorage" library with USB storage and internal storage.
The code includes the necessary library and defines instances of the "USBStorage" and "InternalStorage" classes.

In the setup function, the code initializes the serial communication and mounts the USB storage and internal storage.
It also reformats the internal storage to ensure a clean file system. 
Then, it creates a root directory in the internal storage and creates a subdirectory and a file inside it

The code writes some data to the file and demonstrates file operations. 
It copies the file from internal storage to USB storage and moves the subdirectory from internal storage to USB storage.

After the file operations, the code prints the contents of both the USB storage and the internal storage. 
It recursively prints the directories (marked as "[D]") and files (marked as "[F]") using the "printFolderContents" function.
*/

#include "src/UnifiedStorage.h"


USBStorage usbStorage = USBStorage();
InternalStorage internalStorage = InternalStorage();


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

  // Mount the USB storage
  usbStorage.begin();
  Serial.println("USB storage mounted.");

  // Mount the internal storage
  Serial.println("Reformatting internal storage to make sure we have a clean FS");
  internalStorage.reformatQSPIPartition();

  internalStorage.begin();
  Serial.println("Internal storage mounted.");

  // Create a root directory in the internal storage
  Folder root = internalStorage.getRootFolder();

  // Create a subdirectory and a file inside the root directory
  Folder subdir = root.createSubfolder("subdir");
  UFile file = root.createFile("file.txt", FileMode::WRITE);

  // Write some data to the file
  file.write("Hello, world!");

  // Copy the file from internal storage to USB storage
  bool success = file.copyTo(usbStorage.getRootFolder());
  if (success) {
    Serial.println("File copied successfully from internal storage to USB storage.");
  } else {
    Serial.println("Failed to copy file from internal storage to USB storage.");
    Serial.println(getErrInfo(errno));
  }

  // Move the subdirectory from internal storage to USB storage
  success = subdir.moveTo(usbStorage.getRootFolder());
  if (success) {
    Serial.println("Subdirectory moved successfully from internal storage to USB storage.");
  } else {
    Serial.println("Failed to move subdirectory from internal storage to USB storage.");
    Serial.println(getErrInfo(errno));
  }

  // Print the content of the USB storage
  Serial.println("USB storage contents:");
  printFolderContents(usbStorage.getRootFolder());

  // Print the content of the internal storage
  Serial.println("Internal storage contents:");
  printFolderContents(internalStorage.getRootFolder());
}

void loop() {
  // Nothing to do here
}
