/*
This example demonstrates the usage of the "Arduino_UnifiedStorage" library for logging and backing up data to USB storage in case a USB Mass Storage device is inserted. 

The code defines two main functions: "logData" and "performUpdate". 
The "logData" function logs sensor data by reading an analog sensor and writing the data to the log file.

The "performUpdate" function performs the update process by:
*  reading the last update size from a file (number of bytes)
*  copying the new data from the log file to a backup file 
*  and updating the last update size.

INSTRUCTIONS
* Make sure the QSPI storage of your board is properly partitioned. 
    * You can do that by flashing the QSPIFormat example that can be found in the STM32H747_System folder
    * Open the serial monitor and select answer with "Y" when this appears "Do you want to use partition scheme 1? Y/[n]"
    * Reboot the board
* This sketch will log data, and check if there is any USB MSD Device connected to the USB Port of the Opta. 
  The USB device is mounted and unmounted after every update operation. The first status LED is on when the USB drive is mounted. 
  So as long as the status LED is off you can safely remove the drive. 
  The sketch will log to internal storage in the meantime, and wait for the USB drive to be inserted again. 
*/

#include "Arduino_UnifiedStorage.h"
#include <vector>

constexpr auto baudrate { 115200 };


#define USB_MOUNTED_LED LED_D0
#define SUCCESFULLY_COPIED_LED



InternalStorage internalStorage = InternalStorage(]);
USBStorage usbStorage = USBStorage();
std::vector<String> sensorDataBuffer;

unsigned long bytesWritten = 0;
unsigned long lastLog = 0;
unsigned long lastMove = 0;
unsigned long lastBackup = 0;


volatile bool usbAvailable = false;
bool backingUP = false;

void connectionCallback(){
    usbAvailable = true;
}

void disconnectionCallback(){
    usbAvailable = false;
}
// Function to run a given method periodically
void runPeriodically(void (*method)(), unsigned long interval, unsigned long* variable) {
  unsigned long currentMillis = millis();

  if (currentMillis - *variable >= interval) {
    *variable = currentMillis;
    method();  // Call the provided method
  }
}

// Function to log sensor data
void logDataToRAM() {
  int timeStamp = millis();
  int sensorReading = analogRead(A0);
  String line = String(timeStamp) + "," + String(sensorReading) + "\n";
  sensorDataBuffer.push_back(line);
}

void moveDataToQSPI() {
  if(!backingUP){
    UFile _logFile = internalStorage.getRootFolder().createFile("log.txt", FileMode::APPEND);
    for (const auto& line : sensorDataBuffer) {
      bytesWritten += _logFile.write(line);  // Write the log line to the file
    }
    _logFile.close();
    sensorDataBuffer.clear();
  }
}


void performUpdate() {
  Folder usbRoot = usbStorage.getRootFolder();  // Get the root folder of the USB storage
  UFile logFile = internalStorage.getRootFolder().createFile("log.txt", FileMode::READ);
  UFile backupFile = usbRoot.createFile("backup_file.txt", FileMode::APPEND);  // Create or open the backup file
  UFile lastUpdateFile = usbRoot.createFile("diff.txt", FileMode::READ);  // Create or open the last update file

  backingUP = true;
  unsigned lastUpdateBytes = lastUpdateFile.readAsString().toInt();  // Read the last update size from the file

  printToSerialOrRS485("Last update bytes: " + String(lastUpdateBytes) + "\n");

  if (lastUpdateBytes >= bytesWritten) {
    printToSerialOrRS485("No new data to copy. \n");
    backupFile.close();
    lastUpdateFile.close();
    backingUP = false;
    return;
  }

  logFile.seek(lastUpdateBytes);  // Move the file pointer to the last update position
  unsigned long totalBytesToMove = bytesWritten - lastUpdateBytes;
  printToSerialOrRS485("New update bytes: " + String(totalBytesToMove) + "\n");

  uint8_t* buffer = new uint8_t[totalBytesToMove];

  size_t bytesRead = logFile.read(buffer, totalBytesToMove);
  size_t bytesMoved = backupFile.write(buffer, bytesRead);  // Only write the bytes that haven't been backed up yet

  printToSerialOrRS485("Successfully copied " + String(bytesMoved) + " new bytes.");

  lastUpdateFile.changeMode(FileMode::WRITE);  // Open the last update file in write mode
  lastUpdateFile.write(String(lastUpdateBytes + bytesMoved));  // Update the last update size

  backupFile.close();
  logFile.close();
  lastUpdateFile.close();


  usbStorage.unmount();  // Unmount the USB storage

  digitalWrite(USB_MOUNTED_LED, HIGH);
  backingUP = false;
  delete[] buffer;
}


// Function to backup data to USB storage
void backupToUSB() {
  if (usbAvailable) {
    printToSerialOrRS485("USB Mass storage is available \n");
    delay(100);
    if (!usbStorage.isMounted()) {

      printToSerialOrRS485("Mounting USB Mass Storage \n");
      digitalWrite(USB_MOUNTED_LED, LOW);
      if(usbStorage.begin()){
        performUpdate();
      } 

    } else if (usbStorage.isMounted()) {
      printToSerialOrRS485("USB Mass storage is connected, performing update \n");
      performUpdate();

    }
  } else {
    printToSerialOrRS485("USB Mass storage is not available \n");
  }

}


void setup() {
  beginRS485(baudrate);


  usbStorage.onConnect(connectionCallback);
  usbStorage.onDisconnect(disconnectionCallback);

  pinMode(USB_MOUNTED_LED, OUTPUT);
  printToSerialOrRS485("Formatting internal storage... \n");
  int formatted = internalStorage.format(FS_LITTLEFS);
  printToSerialOrRS485("QSPI Format status: " + String(formatted) + "\n");
 


  if (!internalStorage.begin()) {
    printToSerialOrRS485("Failed to initialize internal storage \n");
    return;
  } else {
    printToSerialOrRS485("Initialized storage \n");
  }

}

void loop() {

  
  runPeriodically(logDataToRAM, 100, &lastLog);
  runPeriodically(moveDataToQSPI, 1000, &lastMove);
  runPeriodically(backupToUSB, 10000, &lastBackup);
}
