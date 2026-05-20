#include "ADC.h"

ADC_TLA2518::ADC_TLA2518(int CS, int SPI_CLK, int MISO, int MOSI, int SCLK, SPIClass* spi) {
    (*this)._MISO = MISO;
    (*this)._MOSI = MOSI;
    (*this)._SCLK = SCLK;
    (*this)._CS = CS;
    if (SPI_CLK < this->_maximum_spi_speed) (*this)._SPI_CLK = SPI_CLK;
    else (*this)._SPI_CLK = this->_maximum_spi_speed;
    (*this)._spi = spi;  
    (*this)._spiSetting = SPISettings((*this)._SPI_CLK, MSBFIRST, SPI_MODE0);
}

void ADC_TLA2518::begin() {
    pinMode((*this)._CS, OUTPUT);
    digitalWrite((*this)._CS, HIGH);
    delay(100);
    int data = this->read_register(SEQUENCE_CFG);
    this->write_register(SEQUENCE_CFG, data & 0xFC);
    this->write_register(PIN_CFG, 0x00);
    this->write_register(SEQUENCE_CFG, 0x00);
}

int ADC_TLA2518::read_adc_value(int channel) {
    if (channel < 0 || channel > 7) {
        return -1;
    }

    this->write_register(CHANNEL_SEL, channel);

    // Dummy-Conversion
    this->_spi->beginTransaction(this->_spiSetting);
    digitalWrite((*this)._CS, LOW);
    this->_spi->transfer(0x00);
    this->_spi->transfer(0x00);
    digitalWrite((*this)._CS, HIGH);

    // read now real values
    digitalWrite((*this)._CS, LOW);
    uint8_t msb = this->_spi->transfer(0x00);
    uint8_t lsb = this->_spi->transfer(0x00);
    digitalWrite((*this)._CS, HIGH);
    this->_spi->endTransaction();

    int raw = (msb << 8) | lsb;
    return raw >> 4;
}

double ADC_TLA2518::read_voltage(int channel, int value){
    if (value == -1) return (double(this->read_adc_value(channel)) / 4096.0) * 5.0;
    return (double(value) / 4096.0) * 5.0;
}

int ADC_TLA2518::read_register(int reg){
    this->_spi->beginTransaction((*this)._spiSetting);
    digitalWrite((*this)._CS, LOW);
    this->_spi->transfer(Read_CMD);
    this->_spi->transfer(reg);
    this->_spi->transfer(0x00); // dummy
    digitalWrite((*this)._CS, HIGH);

    digitalWrite((*this)._CS, LOW);
    unsigned int data = this->_spi->transfer(0x00);
    this->_spi->transfer(0x00);
    digitalWrite((*this)._CS, HIGH);
    this->_spi->endTransaction();

    return data;
}

void ADC_TLA2518::write_register(int reg, int data) {
    this->_spi->beginTransaction((*this)._spiSetting);
    digitalWrite((*this)._CS, LOW);
    this->_spi->transfer(Write_CMD);
    this->_spi->transfer(reg);
    this->_spi->transfer(data);
    digitalWrite((*this)._CS, HIGH);
    this->_spi->endTransaction();
}

int ADC_TLA2518::read_status() {
    return this->read_register(SYSTEM_STATUS);
}