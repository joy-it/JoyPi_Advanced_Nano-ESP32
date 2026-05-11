#include <SPI.h>
#include "ADC.h"

ADC_TLA2518::ADC_TLA2518(int MISO, int MOSI, int SCLK, int SS, int SPI_CLK) {
    (*this)._MISO = MISO;
    (*this)._MOSI = MOSI;
    (*this)._SCLK = SCLK;
    (*this)._SS = SS;
    (*this)._SPI_CLK = SPI_CLK;
}

void ADC_TLA2518::begin() {
    SPI.setClockDivider(SPI_CLOCK_DIV16);
    SPI.setDataMode(SPI_MODE0);
    pinMode((*this)._SS, OUTPUT);
    digitalWrite((*this)._SS, HIGH);

    int data = read_register(SEQUENCE_CFG);
    write_register(SEQUENCE_CFG, data & 0xFC);
    write_register(PIN_CFG, 0x00);
    write_register(SEQUENCE_CFG, 0x00);
}

int ADC_TLA2518::read_adc_value(int channel) {
    write_register(CHANNEL_SEL, channel);

    digitalWrite((*this)._SS, LOW);
    SPI.transfer(0x00);
    SPI.transfer(0x00);
    digitalWrite((*this)._SS, HIGH);

    digitalWrite((*this)._SS, LOW);
    unsigned int temp0 = SPI.transfer(0x00);
    unsigned int temp1 = SPI.transfer(0x00);
    digitalWrite((*this)._SS, HIGH);

    return ((temp0 << 8) | temp1) >> 4;
}

double ADC_TLA2518::read_voltage(int channel, int value = -1){
    if (value == -1) return (double(read_adc_value(channel)) / 4096.0) * 5.0;
    return (double(value) / 4096.0) * 5.0;
}

int ADC_TLA2518::read_register(int reg){
    digitalWrite((*this)._SS, LOW);

    SPI.transfer(Read_CMD);
    SPI.transfer(reg);
    SPI.transfer(0x00); //dummy data
    digitalWrite((*this)._SS, HIGH);
    digitalWrite((*this)._SS, LOW);
    unsigned int data = SPI.transfer(0);

    digitalWrite((*this)._SS, HIGH);

    return data;
}

void ADC_TLA2518::write_register(int reg, int data) {
    digitalWrite((*this)._SS, LOW);

    SPI.transfer(Write_CMD);
    SPI.transfer(reg);
    SPI.transfer(data);
    
    digitalWrite((*this)._SS, HIGH);
}

int ADC_TLA2518::read_status() {
    SPI.beginTransaction((*this)._spiSettings);
    
    digitalWrite((*this)._SS, LOW);
    
    unsigned int temp = read_register(SYSTEM_STATUS);

    digitalWrite((*this)._SS, HIGH);
    SPI.endTransaction();
    
    return temp;
}