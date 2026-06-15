# JoyPi_Advanced_Arduino-ESP32
 This library is a collection for the Arduino and ESP32 for two modules on the Joy-Pi Advanced. See [here](https://www.joy-pi.net) for more information.

## Included modules
This library includes the following modules:
- ADC
- Gyroscope
- RGB-Matrix
- [Keypad_MCP](https://github.com/joeyoung/arduino_keypads/tree/master/Keypad_MCP) with 

## Dependencies
[![strompi3-python](https://img.shields.io/badge/GitHub-strompi3--python-blue?logo=github)](https://github.com/joy-it/strompi3-python)

## Library Guide

### ADC
- `ADC_TLA2518(int CS, int SPI_CLK, int MISO, int MOSI, int SCLK, SPIClass* spi = &SPI)` - initialize ADC
- `void begin()` - starts communication
- `int read_adc_value(int channel)` - returns raw value from a selected channel
- `double read_voltage(int channel, int value = -1)` - returns measured voltage from a selected channel, raw value can also be calculated into voltage with this method

### Gyroscope
- `gyroscope_ICG_1020S(int CS, int SPI_CLK, int MISO, int MOSI, int SCLK, SPIClass* spi = &SPI)`- initialize gyroscope
- `void begin()` - starts communication
- `double getTemperature()` - returns measured temperature
- `String getTilt()` - returns the tilted direction
- ` void setScale(int factor, int gyroscope, int range, int offset)` - sets scale factors of the gyroscope
- `int whoAmI()` - returns specified value to identify itself

### RGB-Matrix
- `RGB_Matrix(int i2c_address = 0x66, uint8_t led_count = 64, uint8_t brightness = 10, const uint8_t* left_border=_default_left_border, const uint8_t* right_border=_default_right_border, TwoWire* awire = &Wire)` - initialize led matrix with default values
- `void begin()` - starts communication with RP2040 chip to communicate with led matrix
- `void show()` - displays set pixels
- `void clean()` - clears the LED matrix
- `void setPixel(uint8_t position, RGBW colour)` - ts specific pixel to a selected colour with `RGBW`-object
- `void colorWipe(RGBW colour, uint8_t wait_ms=50)` - Move selected colour pixel by pixel onto the matrix with default speed
- `void rainbow(uint8_t wait_ms=20, uint8_t iterations=1)` - rainbow effect on the whole matrix with default values
- `void theaterChase(RGBW colour, uint8_t wait_ms=50, uint8_t iterations=10)` - chaser animation with a selected colour with deafult speed
- `void RGB_on(RGBW colour)` - sets the complete matrix to one selected colour
- `void RGB_off()` - turns the complete matrix off
- `RGBW wheel(uint8_t position)` - helper
- `void demo1()` - demo program version 1
- `void demo2()` - demo program version 2
- `void setBrightness(uint8_t brightness)` - set brightness of led matrix
- `uint8_t getPixelNumber()` - returns number of pixel

#### RGBW
> [!NOTE]
> This object is for an easier and more felxible use of colour codes. 
> You can use the hexadecimal value, seperate RGB values or seperate RGBW values.

- `RGBW(uint32_t color)` - constructor for hexadecimal colour value
- `RGBW(uint8_t r, uint8_t g, uint8_t b)` - constructor for seperate RGB values
- `RGBW(uint8_t r, uint8_t g, uint8_t b, uint8_t w)` - constructor for seperate RGBW values