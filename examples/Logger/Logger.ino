/*
  This example demonstrates the usage of the "Arduino_UnifiedStorage" library for logging and backing up data to USB storage in case a USB Mass Storage device is inserted. 

  The "logData" function simulates sensor data by reading reading a random value every 100ms and saving it in memory.
  Afterwards, every 1000ms "moveDataToQSPI" moves those readings to a file in the Internal Storage of your board.

  If a USB device is connected "performUpdate" function performs the update process every 10 seconds by:
  *  reading the last update size from a file (number of bytes)
  *  copying the new data from the log file to a backup file 
  *  and updating the last update size.

  INSTRUCTIONS
  - Make sure you have "POSIXStorage" and "Arduino_UnifiedStorage" installed
  - If you are using this sketch on an Arduino OPTA, use another board or an USB adaptor to view RS485 messages
  - This sketch will log data, and check if there is any USB MSD Device connected to the USB Port of your board.
  - Insert a USB Drive whenever you want 
  - Every 10 seconds data is transferred from the internal storage to the USB Mass storage device
  - Unplug the USB device and inspect its contents. 
  
  NOTES: The USB device is mounted and unmounted after every update operation. The first status LED is on when the USB drive is mounted. 
    So as long as the status LED is off you can safely remove the drive. 
    The sketch will log to internal storage in the meantime, and wait for the USB drive to be inserted again. 
*/
#define ARDUINO_UNIFIED_STORAGE_DEBUG
#include "Arduino_UnifiedStorage.h"
#include <vector>


#if defined(ARDUINO_PORTENTA_H7_M7)
#define USB_MOUNTED_LED LED_BLUE
#elif defined(ARDUINO_PORTENTA_C33)
#define USB_MOUNTED_LED LEDB
#elif defined(ARDUINO_OPTA)
#define USB_MOUNTED_LED LED_D0
#endif


InternalStorage internalStorage;
USBStorage usbStorage;

Folder backupFolder = Folder();
bool usbIntialized = false;
std::vector<String> sensorDataBuffer;

unsigned long bytesWritten = 0;
unsigned long lastLog = 0;
unsigned long lastMove = 0;
unsigned long lastBackup = 0;

volatile bool usbAvailable = false;
bool backingUP = false;

void connectionCallback(){
    usbAvailable = true;
    usbStorage.removeOnConnectCallback();
}

void disconnectionCallback(){
    usbAvailable = false;
    usbStorage.onConnect(connectionCallback);

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
  String line = String(timeStamp) + "," + String(random(9999));
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
  UFile logFile = internalStorage.getRootFolder().createFile("log.txt", FileMode::READ);
  UFile backupFile = backupFolder.createFile("backup_file.txt", FileMode::APPEND);  // Create or open the backup file
  UFile lastUpdateFile = backupFolder.createFile("diff.txt", FileMode::READ);  // Create or open the last update file

  backingUP = true;
  unsigned lastUpdateBytes = lastUpdateFile.readAsString().toInt();  // Read the last update size from the file

  Arduino_UnifiedStorage::debugPrint("Last update bytes: " + String(lastUpdateBytes));

  if (lastUpdateBytes >= bytesWritten) {
    Arduino_UnifiedStorage::debugPrint("No new data to copy. ");
    backupFile.close();
    lastUpdateFile.close();
    backingUP = false;
    return;
  }

  logFile.seek(lastUpdateBytes);  // Move the file pointer to the last update position
  unsigned long totalBytesToMove = bytesWritten - lastUpdateBytes;
  Arduino_UnifiedStorage::debugPrint("New update bytes: " + String(totalBytesToMove));

  uint8_t* buffer = new uint8_t[totalBytesToMove];

  size_t bytesRead = logFile.read(buffer, totalBytesToMove);
  size_t bytesMoved = backupFile.write(buffer, bytesRead);  // Only write the bytes that haven't been backed up yet

  Arduino_UnifiedStorage::debugPrint("Successfully copied " + String(bytesMoved) + " new bytes. ");

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
  if(usbAvailable && !usbIntialized){
      usbStorage.begin();
      Arduino_UnifiedStorage::debugPrint("First drive insertion, creating folders... ");
      Folder usbRoot = usbStorage.getRootFolder();
      String folderName = "LoggerBackup" + String(random(9999));
      backupFolder = usbRoot.createSubfolder(folderName);
      Arduino_UnifiedStorage::debugPrint("Successfully created backup folder: " + backupFolder.getPathAsString());
      usbStorage.unmount();
      usbIntialized = true;
  }
  else if(usbAvailable && usbIntialized) {
    Arduino_UnifiedStorage::debugPrint("USB Mass storage is available ");
    delay(100);
    if (!usbStorage.isMounted()) {

      Arduino_UnifiedStorage::debugPrint("Mounting USB Mass Storage ");
      digitalWrite(USB_MOUNTED_LED, LOW);
      if(usbStorage.begin()){
        performUpdate();
      } 

    } else if (usbStorage.isMounted()) {
      Arduino_UnifiedStorage::debugPrint("USB Mass storage is connected, performing update ");
      performUpdate();

    }
  } else {
    Arduino_UnifiedStorage::debugPrint("USB Mass storage is not available ");
  }


}


void setup() {
  randomSeed(analogRead(A0));

  #if !defined(ARDUINO_OPTA)
    Serial.begin(115200);
    while(!Serial);
  #else
    beginRS485(115200);
  #endif

  // toggle this to enable debugging output
  Arduino_UnifiedStorage::debuggingModeEnabled = false;

  usbStorage = USBStorage();
  internalStorage = InternalStorage();

  usbStorage.onConnect(connectionCallback);
  usbStorage.onDisconnect(disconnectionCallback);

  pinMode(USB_MOUNTED_LED, OUTPUT);
  Arduino_UnifiedStorage::debugPrint("Formatting internal storage... ");
  int formatted = internalStorage.format(FS_LITTLEFS);
  Arduino_UnifiedStorage::debugPrint("QSPI Format status: " + String(formatted));



  if (!internalStorage.begin()) {
    Arduino_UnifiedStorage::debugPrint("Failed to initialize internal storage ");
    return;
  } else {
    Arduino_UnifiedStorage::debugPrint("Initialized storage ");
  }

}

void loop() {

  
  runPeriodically(logDataToRAM, 100, &lastLog);
  runPeriodically(moveDataToQSPI, 1000, &lastMove);
  runPeriodically(backupToUSB, 10000, &lastBackup);
}
