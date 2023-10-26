#ifndef Logger_H
#define Logger_H

#if defined(ARDUINO_OPTA)
#include <ArduinoRS485.h>

static void beginRS485(const int baudrate)
{
    const auto bitduration { 1.f / baudrate };
    const auto wordlen { 9.6f }; // OR 10.0f depending on the channel configuration
    const auto preDelayBR { bitduration * wordlen * 3.5f * 1e6 };
    const auto postDelayBR { bitduration * wordlen * 3.5f * 1e6 };

    RS485.begin(baudrate);
    RS485.setDelays(preDelayBR, postDelayBR);
    RS485.noReceive();
}
#endif

static void printlnToSerialOrRS485(String s){
    #if !defined(ARDUINO_OPTA)
        Serial.println(s);
    #else
        RS485.beginTransmission();
        RS485.write(s.c_str(), strlen(s.c_str()));
        RS485.write('\n');
        RS485.endTransmission();
  #endif
}

#endif