#include "Arduino_UnifiedStorage.h"
#include "Utils.h"

bool Arduino_UnifiedStorage::debuggingModeEnabled = false;

void Arduino_UnifiedStorage::testPrint(String message){
    #if defined(HAS_SERIAL)
      if(Serial){
        Serial.println(message);       
      }
    #elif defined(HAS_RS485) && !defined(HAS_SERIAL)    
      debugPrintRS485(message);        
    #endif
}

void Arduino_UnifiedStorage::debugPrint(String message){
    if(debuggingModeEnabled){
        testPrint(message);
    }
}