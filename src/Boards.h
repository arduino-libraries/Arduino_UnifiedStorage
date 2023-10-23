#if defined(ARDUINO_PORTENTA_C33)
    #define HAS_SD
    #define HAS_USB
    #define HAS_QSPI
    #define USES_RENESAS_CORE
#endif 

#if defined(ARDUINO_PORTENTA_H7_M7)
    #define HAS_SD
    #define HAS_USB
    #define HAS_QSPI
    #define USES_MBED_CORE
#endif 

#if defined(ARDUINO_OPTA)
    #define HAS_USB
    #define HAS_QSPI
    #define USES_MBED_CORE
#endif 

#if defined(ARDUINO_NICLA_VISION)
    #define HAS_QSPI
    #define USES_MBED_CORE
#endif 





