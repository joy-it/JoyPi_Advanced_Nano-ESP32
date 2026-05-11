#ifndef ADC_ESP32_h
#define ADC_ESP32_h

#include <SPI.h>

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
        ADC_TLA2518(int V_MISO, int V_MOSI, int V_SCLK, int V_SS, int V_SPI_CLK);
        int read_adc_value(int channel);
        double read_voltage(int channel, int value = -1);
        void begin();
    private:
        int _V_MISO;
        int _V_MOSI;
        int _V_SCLK;
        int _V_SS;
        int _V_SPI_CLK;
        SPISettings _V_spiSettings;

        int read_register(int reg);
        void write_register(int reg, int data);
        int read_status();
};
#endif 