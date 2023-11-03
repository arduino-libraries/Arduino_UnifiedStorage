
/*
  Callbacks 

  This code demonstrates the usage of the "Arduino_UnifiedStorage" library to handle USB Mass Storage device connection and disconnection callbacks for different supported Arduino boards.
  The code defines callback functions for USB device connection and uses LED indicators to signal when a USB device is connected (LED turned on) or disconnected (LED turned off).

  INSTRUCTIONS:
  - Make sure you have "POSIXStorage" and "Arduino_UnifiedStorage" installed
  - Connect an Arduino board to a computer via USB and run this code.
  - The code will turn on the designated LED when a USB Mass Storage device is connected and turn it off when the device is disconnected.
  - This code can be adapted to perform actions or operations when a USB device is connected or disconnected.
  - You can also customize the LED indicators for different boards according to your hardware configuration.
*/


#include "Arduino_UnifiedStorage.h"

#if defined(ARDUINO_PORTENTA_H7_M7)
#define CALLBACK_LED LED_BLUE
#elif defined(ARDUINO_PORTENTA_C33)
#define CALLBACK_LED LEDB
#elif defined(ARDUINO_OPTA)
#define CALLBACK_LED LED_D0
#endif

USBStorage usbStorage = USBStorage();

void connectionCallback(){
    digitalWrite(CALLBACK_LED, HIGH);
}

void disconnectionCallback(){
    digitalWrite(CALLBACK_LED, LOW);
}

void setup(){
    pinMode(CALLBACK_LED, OUTPUT);
    usbStorage.onConnect(connectionCallback);
    usbStorage.onDisconnect(disconnectionCallback);
}

void loop(){
}