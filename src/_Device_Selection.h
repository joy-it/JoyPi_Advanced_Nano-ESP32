#ifndef _Device_Selection_h
#define _Device_Selection_h

#if defined(ARDUINO_ARCH_ESP32) || defined(ESP32)
    #define BOARD_ESP32
    #define BOARD_NAME "ESP32"
#else
    #define BOARD_NANO
    #define BOARD_NAME "NANO"
#endif

#ifndef MSBFIRST
    #if defined(SPI_MSBFIRST)
        #define MSBFIRST SPI_MSBFIRST
    #endif
#endif

#endif