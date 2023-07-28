/*
This examples demonstrates the usage of the "UnifiedStorage" library,
which allows the program to easily switch between different storage mediums.

By uncommenting the appropriate lines, you can choose to use either an SD card, 
a USB storage device, or internal storage as the storage medium. 

The example code is set up to use an SD card by default.

In the setup function, the code initializes the serial communication and checks if the storage medium is successfully mounted. 
It then creates a root directory and three subdirectories within it.
After creating the subdirectories, the code creates three files inside each subdirectory and writes data to them.

Next, the code demonstrates how to read data from the files using the "seek" and "available" methods.
It changes the mode of the files to read mode, moves the file pointers to the beginning, and reads the data from each file using a while loop.
The read data is printed to the serial monitor.
*/

#include "UnifiedStorage.h"

SDStorage unifiedStorage = SDStorage(); // or
//USBStorage unifiedStorage = USBStorage() // or
//InternalStorage unifiedStorage = InternalStorage();

void setup() {
  Serial.begin(115200);
  while (!Serial);

  if(!unifiedStorage.begin()==0){
    Serial.println("error mounting SD Card");
  }
  // Create a root directory
  
  Folder root = unifiedStorage.getRootFolder();

  // Create subdirectories inside the root directory
  Folder subdir1 = root.createSubfolder("subdir1");
  Folder subdir2 = root.createSubfolder("subdir2");
  Folder subdir3 = root.createSubfolder("subdir3");

  // Create files inside the subdirectories
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
    Serial.write(data);
  }
  Serial.println();

  // Read data from file3
  file3.seek(0); // Move the file pointer to the beginning
  while (file3.available()) {
    char data = file3.read();
    Serial.write(data);
  }
  Serial.println();
}

void loop() {
  // Nothing to do here
}
