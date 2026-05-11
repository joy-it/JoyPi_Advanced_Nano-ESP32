#include <SPI.h>
#include "Arduino.h"
#include "Gyroscope_ESP32.h"

gyroscope_ICG_1020S::gyroscope_ICG_1020S(int V_MISO, int V_MOSI, int V_SCLK, int V_SS, int V_SPI_CLK){
  (*this)._V_MISO = V_MISO;
  (*this)._V_MOSI = V_MOSI;
  (*this)._V_SCLK = V_SCLK;
  (*this)._V_SS = V_SS;
  (*this)._V_SPI_CLK = V_SPI_CLK;
  (*this)._V_spiSetting = SPISettings((*this)._V_SPI_CLK, MSBFIRST, SPI_MODE3);

  (*this)._scaleFactor = 0;
  (*this)._scaleGyroscope = 700;
  (*this)._scaleRange = 46.5;
  (*this)._offset = 0;
}

void gyroscope_ICG_1020S::setScale(int factor, int gyroscope, int range, int offset){
  (*this)._scaleFactor = factor;
  (*this)._scaleGyroscope = gyroscope;
  (*this)._scaleRange = range;
  (*this)._offset = offset;
}

void gyroscope_ICG_1020S::begin(){
  pinMode((*this)._V_SS, OUTPUT);
  digitalWrite((*this)._V_SS, HIGH);
  
  _configureGyroscope();
}

void gyroscope_ICG_1020S::_writeRegister(int reg, int data){
  SPI.beginTransaction((*this)._V_spiSetting);
  digitalWrite((*this)._V_SS, LOW);
  SPI.transfer(reg & 0x7F);
  SPI.transfer(data);
  digitalWrite((*this)._V_SS, HIGH);
  SPI.endTransaction();
}

int gyroscope_ICG_1020S::_readRegister(int reg){
  SPI.beginTransaction((*this)._V_spiSetting);
  digitalWrite((*this)._V_SS, LOW);
  SPI.transfer(reg | 0x80);
  int data = SPI.transfer(0);
  digitalWrite((*this)._V_SS, HIGH);
  SPI.endTransaction();
  return data;
}

void gyroscope_ICG_1020S::_configureGyroscope(){
  int tmp = _readRegister(0x1B) & 0x26;
  _writeRegister(0x1B, 0x18 | tmp);
}

int gyroscope_ICG_1020S::_getXValue(){
  int xH = (_readRegister(0x43) << 8);
  int xL = _readRegister(0x44);
  int x = xH | xL;
  if (x / (*this)._scaleGyroscope > (*this)._scaleRange) return x / (*this)._scaleGyroscope - (2 * (*this)._scaleRange);
  else return x / (*this)._scaleGyroscope;
}

int gyroscope_ICG_1020S::_getYValue(){
  int yH = (_readRegister(0x45) << 8);
  int yL = _readRegister(0x46);
  int y = yH | yL;
  if (y / (*this)._scaleGyroscope > (*this)._scaleRange) return y / (*this)._scaleGyroscope - (2 * (*this)._scaleRange);
  else return y / (*this)._scaleGyroscope;
}

double gyroscope_ICG_1020S::getTemperature(){
  int tempH = (_readRegister(0x41) << 8);
  int tempL = _readRegister(0x42);
  double temp = tempH | tempL;
  return temp / 100;
}

String gyroscope_ICG_1020S::getTilt(){
  int x = _getXValue();
  int y = _getYValue();
  if (y > 2) return "Right";
  else if (y < -2) return "Left";
  else if (x > 3) return "Backwards";
  else if (x < -3) return "Forwards";
  else return "No movement";
}

int gyroscope_ICG_1020S::whoAmI(){
  return _readRegister(0x75);
}