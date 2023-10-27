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

#include "Arduino_UnifiedStorage.h"
#include "Logger.h"
#include <vector>


#if defined(ARDUINO_PORTENTA_H7_M7)
#define USB_MOUNTED_LED LED_BLUE
#elif defined(ARDUINO_PORTENTA_C33)
#define USB_MOUNTED_LED LEDB
#elif defined(ARDUINO_OPTA)
#define USB_MOUNTED_LED LED_D0
#endif


InternalStorage internalStorage = InternalStorage();
USBStorage usbStorage = USBStorage();
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

  printlnToSerialOrRS485("Last update bytes: " + String(lastUpdateBytes));

  if (lastUpdateBytes >= bytesWritten) {
    printlnToSerialOrRS485("No new data to copy. ");
    backupFile.close();
    lastUpdateFile.close();
    backingUP = false;
    return;
  }

  logFile.seek(lastUpdateBytes);  // Move the file pointer to the last update position
  unsigned long totalBytesToMove = bytesWritten - lastUpdateBytes;
  printlnToSerialOrRS485("New update bytes: " + String(totalBytesToMove));

  uint8_t* buffer = new uint8_t[totalBytesToMove];

  size_t bytesRead = logFile.read(buffer, totalBytesToMove);
  size_t bytesMoved = backupFile.write(buffer, bytesRead);  // Only write the bytes that haven't been backed up yet

  printlnToSerialOrRS485("Successfully copied " + String(bytesMoved) + " new bytes. ");

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
      printlnToSerialOrRS485("First drive insertion, creating folders... ");
      Folder usbRoot = usbStorage.getRootFolder();
      String folderName = "LoggerBackup" + String(random(9999));
      backupFolder = usbRoot.createSubfolder(folderName);
      printlnToSerialOrRS485("Successfully created backup folder: " + backupFolder.getPathAsString());
      usbStorage.unmount();
      usbIntialized = true;
  }
  else if(usbAvailable && usbIntialized) {
    printlnToSerialOrRS485("USB Mass storage is available ");
    delay(100);
    if (!usbStorage.isMounted()) {

      printlnToSerialOrRS485("Mounting USB Mass Storage ");
      digitalWrite(USB_MOUNTED_LED, LOW);
      if(usbStorage.begin()){
        performUpdate();
      } 

    } else if (usbStorage.isMounted()) {
      printlnToSerialOrRS485("USB Mass storage is connected, performing update ");
      performUpdate();

    }
  } else {
    printlnToSerialOrRS485("USB Mass storage is not available ");
  }


}


void setup() {
  //beginRS485(baudrate);
  randomSeed(analogRead(A0));

  #if !defined(ARDUINO_OPTA)
    Serial.begin(115200);
    while(!Serial);
  #else
    beginRS485(115200);
  #endif

  usbStorage.onConnect(connectionCallback);
  usbStorage.onDisconnect(disconnectionCallback);

  pinMode(USB_MOUNTED_LED, OUTPUT);
  printlnToSerialOrRS485("Formatting internal storage... ");
  int formatted = internalStorage.format(FS_LITTLEFS);
  printlnToSerialOrRS485("QSPI Format status: " + String(formatted));



  if (!internalStorage.begin()) {
    printlnToSerialOrRS485("Failed to initialize internal storage ");
    return;
  } else {
    printlnToSerialOrRS485("Initialized storage ");
  }

}

void loop() {

  
  runPeriodically(logDataToRAM, 100, &lastLog);
  runPeriodically(moveDataToQSPI, 1000, &lastMove);
  runPeriodically(backupToUSB, 10000, &lastBackup);
}
