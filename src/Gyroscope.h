#ifndef Gyroscope_h
#define Gyroscope_h

#include <SPI.h>

class gyroscope_ICG_1020S{
  public:
    int _scaleFactor;
    int _scaleGyroscope;
    double _scaleRange;
    int _offset;

    gyroscope_ICG_1020S(int MISO, int MOSI, int SCLK, int SS, int SPI_CLK);
    double getTemperature();
    String getTilt();
    int whoAmI();
    void setScale(int factor, int gyroscope, int range, int offset);
    void begin();

  private:
    int _MISO;
    int _MOSI;
    int _SCLK;
    int _SS;
    int _SPI_CLK;
    SPISettings _spiSetting;

    void _writeRegister(int reg, int data);
    int _readRegister(int reg);
    void _configureGyroscope();
    int _getXValue();
    int _getYValue();
};
#endif