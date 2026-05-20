#include "Gyroscope.h"

gyroscope_ICG_1020S::gyroscope_ICG_1020S(int CS, int SPI_CLK, int MISO, int MOSI, int SCLK, SPIClass* spi) {
  (*this)._spi = spi;
  (*this)._MISO = MISO;
  (*this)._MOSI = MOSI;
  (*this)._SCLK = SCLK;
  (*this)._CS = CS;
  (*this)._SPI_CLK = SPI_CLK;
  (*this)._spiSetting = SPISettings((*this)._SPI_CLK, MSBFIRST, SPI_MODE0);

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
  pinMode(this->_CS, OUTPUT);
  digitalWrite(this->_CS, HIGH);
  delay(100);
  this->_configureGyroscope();
}

void gyroscope_ICG_1020S::_writeRegister(int reg, int data){
  this->_spi->beginTransaction((*this)._spiSetting);
  digitalWrite((*this)._CS, LOW);
  this->_spi->transfer(reg & 0x7F);
  this->_spi->transfer(data);
  digitalWrite((*this)._CS, HIGH);
  this->_spi->endTransaction();
}

int gyroscope_ICG_1020S::_readRegister(int reg){
  this->_spi->beginTransaction((*this)._spiSetting);
  digitalWrite((*this)._CS, LOW);
  this->_spi->transfer(reg | 0x80);
  int data = this->_spi->transfer(0);
  digitalWrite((*this)._CS, HIGH);
  this->_spi->endTransaction();
  return data;
}

void gyroscope_ICG_1020S::_configureGyroscope(){
  int tmp = this->_readRegister(0x1B) & 0x26;
  this->_writeRegister(0x1B, 0x18 | tmp);
}

int gyroscope_ICG_1020S::_getXValue(){
  int xH = this->_readRegister(0x43) << 8;
  int xL = this->_readRegister(0x44);
  int x = xH | xL;
  if (x / (*this)._scaleGyroscope > (*this)._scaleRange) return x / (*this)._scaleGyroscope - (2 * (*this)._scaleRange);
  else return x / (*this)._scaleGyroscope;
}

int gyroscope_ICG_1020S::_getYValue(){
  int yH = this->_readRegister(0x45) << 8;
  int yL = this->_readRegister(0x46);
  int y = yH | yL;
  if (y / (*this)._scaleGyroscope > (*this)._scaleRange) return y / (*this)._scaleGyroscope - (2 * (*this)._scaleRange);
  else return y / (*this)._scaleGyroscope;
}

double gyroscope_ICG_1020S::getTemperature(){
  int tempH = this->_readRegister(0x41) << 8;
  int tempL = this->_readRegister(0x42);
  double temp = tempH | tempL;
  return temp / 100;
}

String gyroscope_ICG_1020S::getTilt(){
  int x = this->_getXValue();
  int y = this->_getYValue();
  if (y > 2) return "Right";
  else if (y < -2) return "Left";
  else if (x > 3) return "Forwards";
  else if (x < -3) return "Backwards";
  else return "No movement";
}

int gyroscope_ICG_1020S::whoAmI(){
  return this->_readRegister(0x75);
}
