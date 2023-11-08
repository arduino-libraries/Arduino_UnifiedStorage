/*
    SimpleStorageWriteRead

    Demonstrates basic usage of the "Arduino_UnifiedStorage" library to write and read data to storage.
    Supports SD card, USB storage, and internal storage (default, uncomment to choose).

    In the setup function, the code initializes serial communication, mounts the storage medium,
    creates a root directory with three subdirectories, and writes data to three files in each subdirectory.

    Following this, the code showcases reading data from files by using "seek" and "available" methods,
    switching file modes to read, resetting file pointers to the start,
    and printing the read data to the serial monitor using a while loop.

    INSTRUCTIONS
      1. Check compatibility with your board and make sure you have "POSIXStorage" and "Arduino_UnifiedStorage" installed
      2. Connect your board to the serial monitor
      3. Wait for the sketch to run 


    Created 28th July 2023
    By Cristian Dragomir

    Modified 24th August 2023
    By Ali Jahangiri

    https://github.com/arduino-libraries/Arduino_UnifiedStorage/blob/main/examples/SimpleStorageWriteRead/SimpleStorageWriteRead.ino

*/

#include "Arduino_UnifiedStorage.h"


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


// Uncomment one of the three lines below to select between SD card, USB or internal storage
//SDStorage storage;             // Create an instance for interacting with SD card storage
//USBStorage storage;            // Create an instance for interacting with USB storage
InternalStorage storage;


void setup() {
  Serial.begin(115200);
  while (!Serial);

  // toggle this to enable debugging output
  Arduino_UnifiedStorage::debuggingModeEnabled = false;


  storage = InternalStorage();
  // storage = SDStorage(); // Uncomment this line to use SD card storage
  // storage = USBStorage(); // Uncomment this line to use USB storage

  if(!storage.begin()){
    Serial.println("Error mounting storage device.");
  }
  
  // Create a root directory in storage device
  Folder root = storage.getRootFolder();

  // Create subdirectories inside the root directory
  Folder subdir1 = root.createSubfolder("subdir1");
  Folder subdir2 = root.createSubfolder("subdir2");
  Folder subdir3 = root.createSubfolder("subdir3");

  // Create .txt files inside the subdirectories
  UFile file1 = subdir1.createFile("file1.txt", FileMode::WRITE);
  UFile file2 = subdir2.createFile("file2.txt", FileMode::WRITE);
  UFile file3 = subdir3.createFile("file3.txt", FileMode::WRITE);

  // Write data to the files
  file1.write("This is file 1.");
  file2.write("This is file 2.");
  file3.write("This is file 3.");

  // Read data from the files using seek and available
  Serial.println("Reading data from files using seek and available:");

  // Close and open files in reading mode
  file1.changeMode(FileMode::READ);
  file2.changeMode(FileMode::READ);
  file3.changeMode(FileMode::READ);


  // Read data from file1
  file1.seek(0); // Move the file pointer to the beginning
  while (file1.available()) {
  char data = file1.read();
    Serial.write(data);
  }
  Serial.println();

  // Read data from file2
  file2.seek(0); // Move the file pointer to the beginning
  while (file2.available()) {
    char data = file2.read();
    Serial.print(data);
  }
  Serial.println();

  // Read data from file3
  file3.seek(0); // Move the file pointer to the beginning
  while (file3.available()) {
    char data = file3.read();
    Serial.print(data);
  }
  Serial.println();

  printFolderContents(storage.getRootFolder());
}

void loop() {
  // Nothing to do here
}
