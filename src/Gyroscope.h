#ifndef Gyroscope_h
#define Gyroscope_h
#include "_Device_Selection.h"

#include <SPI.h>
#include <Arduino.h>

class gyroscope_ICG_1020S{
  public:
    int _scaleFactor;
    int _scaleGyroscope;
    double _scaleRange;
    int _offset;

    gyroscope_ICG_1020S(int CS, int SPI_CLK, int MISO, int MOSI, int SCLK, SPIClass* spi = &SPI);
    double getTemperature();
    String getTilt();
    int whoAmI();
    void setScale(int factor, int gyroscope, int range, int offset);
    void begin();

  private:
    int _MISO;
    int _MOSI;
    int _SCLK;
    int _CS;
    int _SPI_CLK;

    SPIClass* _spi;
    SPISettings _spiSetting;

    void _writeRegister(int reg, int data);
    int _readRegister(int reg);
    void _configureGyroscope();
    int _getXValue();
    int _getYValue();
};
#endif