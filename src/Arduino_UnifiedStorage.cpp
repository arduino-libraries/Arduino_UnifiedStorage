#include "Arduino_UnifiedStorage.h"

#if !defined(HAS_SERIAL) && defined(HAS_RS485)
#include <ArduinoRS485.h>


[[gnu::unused]] static void beginRS485(const int baudrate){
    const auto bitduration { 1.f / baudrate };
    const auto wordlen { 9.6f }; // OR 10.0f depending on the channel configuration
    const auto preDelayBR { bitduration * wordlen * 3.5f * 1e6 };
    const auto postDelayBR { bitduration * wordlen * 3.5f * 1e6 };

    RS485.begin(baudrate);
    RS485.setDelays(preDelayBR, postDelayBR);
    RS485.noReceive();
}

[[gnu::unused]] static void debugPrintRS485(String s){
    static bool rs485Initialized = false;
    if (!rs485Initialized) {
      beginRS485(115200);
      rs485Initialized = true;
    }
    RS485.beginTransmission();
    RS485.write(s.c_str(), strlen(s.c_str()));
    RS485.write('\n');
    RS485.endTransmission();
}

#endif

bool Arduino_UnifiedStorage::loggingEnabled = false;

void Arduino_UnifiedStorage::debugPrint(String message){
    #if defined(HAS_SERIAL)
      if(Serial){
        Serial.println(message);       
      }
    #elif defined(HAS_RS485) && !defined(HAS_SERIAL)    
      debugPrintRS485(message);        
    #endif
}