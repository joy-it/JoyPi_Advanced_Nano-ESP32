# JoyPi_Advanced_Nano-ESP32
 This library is a collection for the Arduino and ESP32 for two modules on the Joy-Pi Advanced. See [here](https://www.joy-pi.net) for more information.

## Included modules
This library includes the following modules:
- `ADC_TLA2518`
- `gyroscope_ICG_1020S`
- `RGB_Matrix`
- [`Keypad_MCP`](https://github.com/joeyoung/arduino_keypads/tree/master/Keypad_MCP)

## Necessary libraries for the Joy-Pi Advanced
> [!NOTE]
> This is a list of all necessary libraries that are needed for the Joy-Pi Advanced and the Arduino Nano or ESP32. All these libraries are set as dependencies and will be automatically installed in the Arduino IDE.

| Repository | Needed for |
|---|---|
| `ADC_TLA2518` | Library to use the Analog-Digital-Converter |
| `gyroscope_ICG_1020S` | Library to use the gyroscope|
| `RGB_Matrix` | Library to use the led matrix on Joy-Pi Advanced 2 - RP2040 is used to communicate with led matrix |
| [`Adafruit NeoPixel`](https://github.com/adafruit/Adafruit_NeoPixel) | Library to use the led matrix on Joy-Pi Advanced (older versions) - led matrix is directly connected to microcontroller |
| [`Keypad_MCP`](https://github.com/joeyoung/arduino_keypads/tree/master/Keypad_MCP) [`Keypad`](https://github.com/Chris--A/Keypad) | Library to use the button matrix|
| [`MFRC522`](https://github.com/miguelbalboa/rfid) | Library to use the RFID module|
| [`OneWire`](https://www.pjrc.com/teensy/td_libs_OneWire.html) | Library for OneWire communication to use the DS18B20|
| [`Servo`](https://docs.arduino.cc/libraries/servo/) | Library to use the servo motor with Arduino Nano|
| [`ESP32Servo`](https://madhephaestus.github.io/ESP32Servo/annotated.html) | Library to use the servo motor with ESP32|
| [`VEML6040`](https://github.com/thewknd/VEML6040) | Library to use the colour sensor|
| [`Adafruit MPR121`](https://github.com/adafruit/Adafruit_MPR121) [`Adafruit BusIO`](https://github.com/adafruit/Adafruit_BusIO) | Library to use the touch pads|
| [`DHT sensor library`](https://github.com/adafruit/DHT-sensor-library) [`Adafruit Unified Sensor`](https://github.com/adafruit/Adafruit_Sensor)| Library to use the DHT11|
| [`hd44780`](https://github.com/duinoWitchery/hd44780)| Library to use the 16x2 LCD|
| [`IRremote`](https://github.com/Arduino-IRremote/Arduino-IRremote) | Library to use the infrared sensor and easily decode the signal|
| [`Adafruit SSD1306`](https://github.com/adafruit/Adafruit_SSD1306) [`Adafruit GFX Library`](https://github.com/adafruit/Adafruit-GFX-Library) [`Adafruit BusIO`](https://github.com/adafruit/Adafruit_BusIO)| Library to use OLED display|
| [`SSD1306Ascii`](https://github.com/greiman/SSD1306Ascii) | Library to use OLED for project interactive safe because other library needs more dynamic memory|
| [`Adafruit ST7735 and ST7789 Library`](https://github.com/adafruit/Adafruit-ST7735-Library) [`Adafruit GFX Library`](https://github.com/adafruit/Adafruit-GFX-Library) [`Adafruit seesaw Library`](https://github.com/adafruit/Adafruit_Seesaw) [`Adafruit BusIO`](https://github.com/adafruit/Adafruit_BusIO) [`SD`](https://docs.arduino.cc/libraries/sd/)| Library to use the TFT display|
| [`RTCDS1307`](https://github.com/offcircuit/RTCDS1307) | Library to use the Real Time Clock |
| [`MS5xxx`](https://github.com/Schm1tz1/arduino-ms5xxx) | Library to use the barometer|
| [`PinChangeInterrupt`](https://github.com/NicoHood/PinChangeInterrupt) | Library to use other pins as interrupt than the interrupt pins on the Arduino Nano|

## Library Guide

### `ADC_TLA2518`
- `ADC_TLA2518(int CS, int SPI_CLK, int MISO, int MOSI, int SCLK, SPIClass* spi = &SPI)` - initialize ADC
- `void begin()` - starts communication
- `int read_adc_value(int channel)` - returns raw value from a selected channel
- `double read_voltage(int channel, int value = -1)` - returns measured voltage from a selected channel, raw value can also be calculated into voltage with this method

### `gyroscope_ICG_1020S`
- `gyroscope_ICG_1020S(int CS, int SPI_CLK, int MISO, int MOSI, int SCLK, SPIClass* spi = &SPI)`- initialize gyroscope
- `void begin()` - starts communication
- `double getTemperature()` - returns measured temperature
- `String getTilt()` - returns the tilted direction
- ` void setScale(int factor, int gyroscope, int range, int offset)` - sets scale factors of the gyroscope
- `int whoAmI()` - returns specified value to identify itself

### `RGB_Matrix`
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

#### `RGBW`
> [!NOTE]
> This object is for an easier and more flexible use of colour codes. 
> You can use the hexadecimal value, separate RGB values or separate RGBW values.

- `RGBW(uint32_t color)` - constructor for hexadecimal colour value
- `RGBW(uint8_t r, uint8_t g, uint8_t b)` - constructor for separate RGB values
- `RGBW(uint8_t r, uint8_t g, uint8_t b, uint8_t w)` - constructor for separate RGBW values

### [`Keypad_MCP`](https://github.com/joeyoung/arduino_keypads/tree/master/Keypad_MCP)
> [!NOTE]
> This library is copied into this repository because it is normally necessary to download it and to manually install it. Therefore, to make the installation easier, the files are included in this repository. The licence of the library can be found [here](https://github.com/joy-it/JoyPi_Advanced_Nano-ESP32/blob/main/src/Keypad_MCP_LICENSE).
- `Keypad_MCP(char* userKeymap, byte* row, byte* col, byte numRows, byte numCols, byte address, TwoWire * awire=&Wire)` - initialize button matrix with keymap,  array with pins of MCP which are the rows, array with pins of MCP which are the columns, number of rows, number of columns and I2C addres
- `void begin(char *userKeymap)` -  start communication with defined keymap (how buttons are arranged)
- `void begin(void)` - start communication with already set keymap
- `void pin_mode(byte pinNum, byte mode)` - set a certain pin of MCP as input(`INPUT`) or output(`OUTPUT`) in the IODIR register
- `void pin_write(byte pinNum, boolean level)` - set value of a certain pin of MCP
- `int  pin_read(byte pinNum)` - get current state of a certain pin of MCP
- `byte pinState_set( )` - get current state of all 8 bits of the port
- `void port_write( byte i2cportval )` -  write a whole byte to i2c port
- `byte iodir_read( )` - get current state of all 8 bits of MCP IODIR register
- `void iodir_write( byte iodir )` - write value to all 8 bits of MCP IODIR register

#### [`Keypad`](https://github.com/Chris--A/Keypad)
> [!NOTE]
> [`Keypad_MCP`](https://github.com/joeyoung/arduino_keypads/tree/master/Keypad_MCP) inherts from [`Keypad`](https://github.com/Chris--A/Keypad).
> Therefore the following methods can also be used with [`Keypad_MCP`](https://github.com/joeyoung/arduino_keypads/tree/master/Keypad_MCP)
- `char getKey()` - returns one key which was pressed
- `bool getKeys()` - returns true if a key was pressed
- `KeyState getState()` - returns state of keys
- `bool isPressed(char keyChar)` - return if a certain key was pressed
- `void setDebounceTime(uint)` - set debounce time of button matrix (min = 1 ms)
- `void setHoldTime(uint)` - set hold time of button matrix (how long a key has to be pressed to be recognized)
- `void addEventListener(void (*listener)(char))` - 
- `int findInList(char keyChar)` - searches by character for a key in list of active keys (returns -1 if none is found)
- `int findInList(int keyCode)` - searches by code for a key in list of active keys (returns -1 if none is found)
- `char waitForKey()` - blocks everything till a key was pressed
- `bool keyStateChanged()` - returns true if state of any key changed
- `byte numKeys()` - returns number of keys in the key list
- `typedef enum{ IDLE, PRESSED, HOLD, RELEASED } KeyState` - enum to define possible states of a key