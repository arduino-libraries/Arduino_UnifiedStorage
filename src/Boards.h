#if defined(ARDUINO_PORTENTA_C33)
    #define HAS_SD
    #define HAS_USB
    #define HAS_QSPI
    #define USES_RENESAS_CORE
    #define QSPI_STORAGE_SIZE 16384
    #define HAS_SERIAL
#endif 

#if defined(ARDUINO_PORTENTA_H7_M7)
    #define HAS_SD
    #define HAS_USB
    #define HAS_QSPI
    #define USES_MBED_CORE
    #define QSPI_STORAGE_SIZE 16384
    #define HAS_SERIAL
#endif 

#if defined(ARDUINO_OPTA)
    #define HAS_USB
    #define HAS_QSPI
    #define USES_MBED_CORE
    #define QSPI_STORAGE_SIZE 16384
    #define HAS_RS485
#endif 

#if defined(ARDUINO_NICLA_VISION)
    #define HAS_QSPI
    #define USES_MBED_CORE
    #define QSPI_STORAGE_SIZE 16384
    #define HAS_SERIAL
#endif 