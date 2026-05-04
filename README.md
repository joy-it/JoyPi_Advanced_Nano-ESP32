# JoyPi_Advanced_Arduino
 This library is a collection for the Arduino for two modules on the Joy-Pi Advanced. See [here](https://www.joy-pi.net) for more information.

## Included modules

This library includes the following modules:
- ADC
- Gyroscope

## Library Guide
### ADC
- `ADC_TLA2518(int MISO, int MOSI, int SCLK, int SS, int SPI_CLK)` - initialize ADC
- `void begin()` - starts communication
- `int read_adc_value(int channel)` - returns raw value from a selected channel
- `double read_voltage(int channel, int value = -1)` - returns measured voltage from a selected channel, raw value can also be calculated into voltage with this method
### Gyroscope
- `gyroscope_ICG_1020S(int MISO, int MOSI, int SCLK, int SS, int SPI_CLK)`- initialize gyroscope
- `void begin()` - starts communication
- `double getTemperature()` - returns measured temperature
- `String getTilt()` - returns the tilted direction
- ` void setScale(int factor, int gyroscope, int range, int offset)` - sets scale factors of the gyroscope
- `int whoAmI()` - returns specified value to identify itself