#ifndef ADC_h
#define ADC_h

#include "_Device_Selection.h"
#include <SPI.h>
#include <Arduino.h>

#define SYSTEM_STATUS   0x00
#define GENERAL_CFG     0x01
#define DATA_CFG        0x02
#define OSR_CFG         0x03
#define OPMODE_CFG      0x04
#define PIN_CFG         0x05
#define GPIO_CFG        0x06
#define GPO_DRIVE_CFG   0x07
#define GPO_VALUE       0x0B
#define GPI_VALUE       0x0D
#define SEQUENCE_CFG    0x10
#define CHANNEL_SEL     0x11
#define AUTO_SEQ_CH_SEL 0x12
#define Read_CMD        0x10
#define Write_CMD       0x08

class ADC_TLA2518{    
    public:
        ADC_TLA2518(int CS, int SPI_CLK, int MISO, int MOSI, int SCLK, SPIClass* spi = &SPI);
        int read_adc_value(int channel);
        double read_voltage(int channel, int value = -1);
        void begin();
    private:
        int _MISO;
        int _MOSI;
        int _SCLK;
        int _CS;
        int _SPI_CLK;

        SPIClass* _spi;
        SPISettings _spiSetting;
        const int _maximum_spi_speed = 1000000;

        int read_register(int reg);
        void write_register(int reg, int data);
        int read_status();
};
#endif 