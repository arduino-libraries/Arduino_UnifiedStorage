#include "Arduino_UnifiedStorage.h"


bool Arduino_UnifiedStorage::loggingEnabled = false;

void Arduino_UnifiedStorage::debugPrint(String message){
            if(Arduino_UnifiedStorage::loggingEnabled){
                Serial.println(message);
            }
        }