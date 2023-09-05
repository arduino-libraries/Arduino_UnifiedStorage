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

#if defined(ARDUINO_PORTENTA_H7_M7)
#define USB_MOUNTED_LED LED_BLUE
#elif defined(ARDUINO_PORTENTA_C33)
#endif 


InternalStorage internalStorage = InternalStorage();
USBStorage usbStorage = USBStorage();
std::vector<String> sensorDataBuffer;

unsigned long bytesWritten = 0;
unsigned long lastLog = 0;
unsigned long lastMove = 0;
unsigned long lastBackup = 0;


bool backingUP = false;


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

  Serial.print("Last update bytes: "); Serial.println(lastUpdateBytes);

  if (lastUpdateBytes >= bytesWritten) {
    Serial.println("No new data to copy.");
    backupFile.close();
    lastUpdateFile.close();
    backingUP = false;
    return;
  }

  logFile.seek(lastUpdateBytes);  // Move the file pointer to the last update position
  unsigned long totalBytesToMove = bytesWritten - lastUpdateBytes;
  Serial.print("New update bytes: "); Serial.println(totalBytesToMove);

  uint8_t* buffer = new uint8_t[totalBytesToMove];

  size_t bytesRead = logFile.read(buffer, totalBytesToMove);
  size_t bytesMoved = backupFile.write(buffer, bytesRead);  // Only write the bytes that haven't been backed up yet

  Serial.println("Successfully copied " + String(bytesMoved) + " new bytes.");

  lastUpdateFile.changeMode(FileMode::WRITE);  // Open the last update file in write mode
  lastUpdateFile.write(String(lastUpdateBytes + bytesMoved));  // Update the last update size

  backupFile.close();
  logFile.close();
  lastUpdateFile.close();

  Serial.println();
  usbStorage.unmount();  // Unmount the USB storage

  digitalWrite(USB_MOUNTED_LED, HIGH);
  backingUP = false;
  delete[] buffer;
}


void disconnect(){

}
// Function to backup data to USB storage
void backupToUSB() {
  if (usbStorage.isAvailable()) {
    Serial.println("USB Mass storage is available");
    delay(100);
    if (!usbStorage.isConnected()) {

      Serial.println("Mounting USB Mass Storage");
      digitalWrite(USB_MOUNTED_LED, LOW);
      if(usbStorage.begin()){
        performUpdate();
      } 



    } else if (usbStorage.isConnected()) {
      Serial.println("USB Mass storage is connected, performing update");
      performUpdate();

    }
  } else {
    Serial.println("USB Mass storage is not available");
  }


}


void setup() {
  Serial.begin(115200);
  while (!Serial);
  pinMode(USB_MOUNTED_LED, OUTPUT);
  Serial.println("Formatting internal storage...");
  int formatted = internalStorage.format(FS_FAT);
  Serial.print("QSPI Format status: "); Serial.println(formatted);

  //configureRS485(baudrate);
  //Serial.println("RS485 goes brrr...");

  if (!internalStorage.begin()) {
    Serial.println("Failed to initialize internal storage");
    return;
  } else {
    Serial.println("Initialized storage");
  }

}

void loop() {

  usbStorage.checkConnection();
  
  runPeriodically(logDataToRAM, 100, &lastLog);
  runPeriodically(moveDataToQSPI, 1000, &lastMove);
  runPeriodically(backupToUSB, 10000, &lastBackup);
}
