#include <SPI.h>
#include "Arduino.h"
#include "ADC_ESP32.h"

ADC_TLA2518::ADC_TLA2518(int V_MISO, int V_MOSI, int V_SCLK, int V_SS, int V_SPI_CLK) {
    (*this)._V_MISO = V_MISO;
    (*this)._V_MOSI = V_MOSI;
    (*this)._V_SCLK = V_SCLK;
    (*this)._V_SS = V_SS;
    (*this)._V_SPI_CLK = V_SPI_CLK;
    (*this)._V_spiSettings = SPISettings((*this)._V_SPI_CLK, MSBFIRST, SPI_MODE0);
}

void ADC_TLA2518::begin() {
    SPI.setClockDivider(SPI_CLOCK_DIV16);
    SPI.setDataMode(SPI_MODE0);
    pinMode((*this)._V_SS, OUTPUT);
    digitalWrite((*this)._V_SS, HIGH);

    int data = read_register(SEQUENCE_CFG);
    write_register(SEQUENCE_CFG, data & 0xFC);
    write_register(PIN_CFG, 0x00);
    write_register(SEQUENCE_CFG, 0x00);
}

int ADC_TLA2518::read_adc_value(int channel) {
    write_register(CHANNEL_SEL, channel);

    digitalWrite((*this)._V_SS, LOW);
    SPI.transfer(0x00);
    SPI.transfer(0x00);
    digitalWrite((*this)._V_SS, HIGH);

    digitalWrite((*this)._V_SS, LOW);
    unsigned int temp0 = SPI.transfer(0x00);
    unsigned int temp1 = SPI.transfer(0x00);
    digitalWrite((*this)._V_SS, HIGH);

    return ((temp0 << 8) | temp1) >> 4;
}

double ADC_TLA2518::read_voltage(int channel, int value){
    if (value == -1) return (double(read_adc_value(channel)) / 4096.0) * 5.0;
    return (double(value) / 4096.0) * 5.0;
}

int ADC_TLA2518::read_register(int reg){
    digitalWrite((*this)._V_SS, LOW);

    SPI.transfer(Read_CMD);
    SPI.transfer(reg);
    SPI.transfer(0x00); //dummy data
    digitalWrite((*this)._V_SS, HIGH);
    digitalWrite((*this)._V_SS, LOW);
    unsigned int data = SPI.transfer(0);

    digitalWrite((*this)._V_SS, HIGH);

    return data;
}

void ADC_TLA2518::write_register(int reg, int data) {
    digitalWrite((*this)._V_SS, LOW);

    SPI.transfer(Write_CMD);
    SPI.transfer(reg);
    SPI.transfer(data);
    
    digitalWrite((*this)._V_SS, HIGH);
}

int ADC_TLA2518::read_status() {
    SPI.beginTransaction((*this)._V_spiSettings);
    
    digitalWrite((*this)._V_SS, LOW);
    
    unsigned int temp = read_register(SYSTEM_STATUS);

    digitalWrite((*this)._V_SS, HIGH);
    SPI.endTransaction();
    
    return temp;
}