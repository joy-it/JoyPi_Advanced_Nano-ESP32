#ifndef Gyroscope_ESP32_h
#define Gyroscope_ESP32_h

#include <SPI.h>

class gyroscope_ICG_1020S{
  public:
    int _scaleFactor;
    int _scaleGyroscope;
    double _scaleRange;
    int _offset;

    gyroscope_ICG_1020S(int V_MISO, int V_MOSI, int V_SCLK, int V_SS, int V_SPI_CLK);
    double getTemperature();
    String getTilt();
    int whoAmI();
    void setScale(int factor, int gyroscope, int range, int offset);
    void begin();

  private:
    int _V_MISO;
    int _V_MOSI;
    int _V_SCLK;
    int _V_SS;
    int _V_SPI_CLK;
    SPISettings _V_spiSetting;

    void _writeRegister(int reg, int data);
    int _readRegister(int reg);
    void _configureGyroscope();
    int _getXValue();
    int _getYValue();
};
#endif