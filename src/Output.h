 
#ifndef Output_H
#define Output_H

#include <Arduino.h>

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

static int printFormatted(bool b){
    if(b)
        printFormatted("true");
    else 
        printFormatted("false");
}

static int printFormatted(String s){
    #if defined(ARDUINO_PORTENTA_C33) || defined(ARDUINO_PORTENTA_H7_M7)
        Serial.print(s);
    #elif defined(ARDUINO_OPTA)
        RS485.beginTransmission();
        RS485.write(s.c_str(), strlen(s.c_str()));
        RS485.endTransmission();
    #endif 
}



static int printFormatted(char *format, ...){
    va_list args;
    va_start(args, format);

    // Determine the length of the formatted string
    int length = vsnprintf(NULL, 0, format, args);

    // Allocate memory to hold the formatted string
    char *buffer = (char *)malloc(length + 1);
    if (buffer == NULL) {
        va_end(args);
        return -1; // Memory allocation error
    }

    // Format the string and store it in the buffer
    vsnprintf(buffer, length + 1, format, args);
    va_end(args);

    #if defined(ARDUINO_PORTENTA_C33) || defined(ARDUINO_PORTENTA_H7_M7)
        Serial.print(buffer);
    #elif defined(ARDUINO_OPTA)
        RS485.beginTransmission();
        RS485.write(buffer, length);
        RS485.endTransmission();
    #endif 

    free(buffer);

    return length;
}
#endif