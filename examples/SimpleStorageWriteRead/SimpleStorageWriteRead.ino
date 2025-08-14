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

// Set one of the following to "true" and the rest to "false" in order to select one storage medium
#define USE_SD_STORAGE              false
#define USE_USB_STORAGE             false
#define USE_INTERNAL_STORAGE        true

#if defined(USE_SD_STORAGE) && (USE_SD_STORAGE == true)
SDStorage storage;             // Create an instance for interacting with SD card storage
#elif defined(USE_USB_STORAGE) && (USE_USB_STORAGE == true)
USBStorage storage;            // Create an instance for interacting with USB storage
#elif defined(USE_INTERNAL_STORAGE) && (USE_INTERNAL_STORAGE == true)
InternalStorage storage;
#else
#error "No valid storage option defined! Please define one of USE_SD_STORAGE, USE_USB_STORAGE, or USE_INTERNAL_STORAGE as true."
#endif

void printFolderContents(Folder dir, int indentation = 0) {
  std::vector<Folder> directories = dir.getFolders();
  std::vector<UFile> files = dir.getFiles();

  // Print directories
  for (Folder subdir : directories) {
    for (int i = 0; i < indentation; i++) {
      Arduino_UnifiedStorage::testPrint("  ");
    }
    Arduino_UnifiedStorage::testPrint("[D] ");
    Arduino_UnifiedStorage::testPrint(subdir.getPath());
    printFolderContents(subdir, indentation + 1);
  }

  // Print files
  for (UFile file : files) {
    for (int i = 0; i < indentation; i++) {
      Arduino_UnifiedStorage::testPrint("  ");
    }
    Arduino_UnifiedStorage::testPrint("[F] ");
    Arduino_UnifiedStorage::testPrint(file.getPath());
  }
}

void setup() {

  uint8_t index = 0u;
  char data[20];

// if we are on the Arduino Opta, and have decided to log on an USB drive connected to the USB-C connecter, we have to output the serial data through the RJ45 channel.
#if (defined(ARDUINO_OPTA)) && (defined(USE_USB_STORAGE) &&  (USE_USB_STORAGE == true))
    beginRS485(115200);
#else
    Serial.begin(115200);
    while (!Serial);
#endif

  // toggle this to enable debugging output
  Arduino_UnifiedStorage::debuggingModeEnabled = false;

  if(!storage.begin()){
    Arduino_UnifiedStorage::testPrint("Error mounting storage device.");
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
  Arduino_UnifiedStorage::testPrint("Reading data from files using seek and available:");
  Arduino_UnifiedStorage::testPrint("\n\r");

  // Close and open files in reading mode
  file1.changeMode(FileMode::READ);
  file2.changeMode(FileMode::READ);
  file3.changeMode(FileMode::READ);


  // Read data from file1
  file1.seek(0); // Move the file pointer to the beginning
  //memset(data, 0u, sizeof(data));
  std::fill(std::begin(data), std::end(data), 0u);
  while (file1.available()) {
  data[index++] = file1.read();
  }
  Arduino_UnifiedStorage::testPrint(data);

  // Read data from file2
  file2.seek(0); // Move the file pointer to the beginning
  index = 0u;
  //memset(data, 0u, sizeof(data));
  std::fill(std::begin(data), std::end(data), 0u);
  while (file2.available()) {
    data[index++] = file2.read();
  }
  Arduino_UnifiedStorage::testPrint(data);

  // Read data from file3
  file3.seek(0); // Move the file pointer to the beginning
  index = 0u;
  //memset(data, 0u, sizeof(data));
  std::fill(std::begin(data), std::end(data), 0u);
  while (file3.available()) {
    data[index++] = file3.read();
  }
  Arduino_UnifiedStorage::testPrint(data);
  Arduino_UnifiedStorage::testPrint("\n\r");

  printFolderContents(storage.getRootFolder());
}

void loop() {
  // Nothing to do here
}
