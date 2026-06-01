#ifndef RGBmatrix_RP2040_h
#define RGBmatrix_RP2040_h

#include <Wire.h>
#include <Arduino.h>

enum class FunctionEnum : uint8_t {
    SHOW          = 0,
    SETPIXELCOLOR = 1,
    FILL          = 2,
    SETBRIGHTNESS = 3,
    GAMMA8        = 4,
    GAMMA32       = 5,
    NUMPIXEL      = 6,
    COLORHSV      = 7,
    CLEAR         = 8,
    SENDDATA2SHOW = 9,
    SENDALLPIXRGB0 = 10,
    SENDALLPIXRGB1 = 11,
    SENDALLPIXRGB2 = 12,
    SENDALLPIXRGB3 = 13,
    SENDALLPIXRGB4 = 14,
    SENDALLPIXRGB5 = 15
};

class LED_Transfer_Data{
    private:
        uint8_t _func;
        uint8_t _pos;
        uint8_t _red;
        uint8_t _green;
        uint8_t _blue;
        uint8_t _white;
        uint8_t _c;
        uint8_t _bright;
        uint8_t _first;
        uint8_t _count;
        uint8_t _data0;
        uint8_t _data1;
        //uint8_t _transferData[12];
    public:
        LED_Transfer_Data();
        void setFunc(FunctionEnum func);
        uint8_t getFunc() const;
        void setPos(uint8_t pos);
        uint8_t getPos() const;
        void setRed(uint8_t red);
        uint8_t getRed() const;
        void setGreen(uint8_t green);
        uint8_t getGreen() const;
        void setBlue(uint8_t blue);
        uint8_t getBlue() const;
        void setWhite(uint8_t white);
        uint8_t getWhite() const;
        void setC(uint8_t c);
        uint8_t getC() const;
        void setBright(uint8_t bright);
        uint8_t getBright() const;
        void setFirst(uint8_t first);
        uint8_t getFirst() const;
        void setCount(uint8_t count);
        uint8_t getCount() const;
        void setData0(uint8_t data0);
        uint8_t getData0() const;
        void setData1(uint8_t data1);
        uint8_t getData1() const;
        void getData(uint8_t* _transferData);
        void clearObject();
};

class RGBW{
    public:
        RGBW(uint32_t color);
        RGBW(uint8_t r, uint8_t g, uint8_t b);
        RGBW(uint8_t r, uint8_t g, uint8_t b, uint8_t w);
        uint8_t getR() const;
        uint8_t getG() const;
        uint8_t getB() const;
        uint8_t getW() const;
        uint32_t getValue() const;
        void getValue(uint8_t* tranfer_data);
    private:
        uint32_t _value;
};

class Pixelstrip{
    public:
        Pixelstrip(int i2c_address=0x66, uint8_t led_count=64, uint8_t brightness=10,TwoWire * awire = &Wire) : _i2c_address(i2c_address), _led_count(led_count), 
                    _brightness(brightness), _wire(awire) {};
        void begin();
        void send(uint8_t cmd);
        void clear();
        void show();
        uint8_t* getWRGB(int color);
        void setPixelColor(uint8_t pos, RGBW color);
        void setPixelColorRGB(uint8_t pos, uint8_t r, uint8_t g, uint8_t b, uint8_t w);
        void sendPos2Show(uint8_t* pos, uint8_t pos_length, uint8_t r, uint8_t g, uint8_t b);
        void sendColor2Show(uint8_t* pos, uint8_t pos_length, RGBW color);
        void fill(uint8_t r, uint8_t g, uint8_t b, uint8_t w, uint8_t first, uint8_t end);
        void fillColor(RGBW color, uint8_t first, uint8_t end);
        void setBrightness(uint8_t brightness);
        uint8_t getNumPixels() const;
        uint8_t getGamma8(uint8_t color);
        uint32_t getGamma32(uint32_t color);
        uint8_t getColorHSV(uint8_t x);
    private:
        uint8_t _brightness;
        int _i2c_address;
        uint8_t _led_count;
        TwoWire * _wire;
        LED_Transfer_Data _data;
        void _write(uint8_t cmd, const uint8_t* data, uint8_t length);
        uint8_t _read();
};

class RGB_Matrix{
    public:
        RGB_Matrix(int i2c_address = 0x66, uint8_t led_count = 64, uint8_t brightness = 10, const uint8_t* left_border=_default_left_border, 
                    const uint8_t* right_border=_default_right_border, TwoWire* awire = &Wire)
        : _led_count(led_count), _brightness(brightness), _left_border(left_border), _right_border(right_border), _pixelstrip(i2c_address, led_count, brightness, awire)
        {}
        void begin();
        void show();
        void clean();
        void setPixel(uint8_t position, RGBW colour);
        void colorWipe(RGBW colour, uint8_t wait_ms=50);
        void rainbow(uint8_t wait_ms=20, uint8_t iterations=1);
        void theaterChase(RGBW colour, uint8_t wait_ms=50, uint8_t iterations=10);
        void RGB_on(RGBW colour);
        void RGB_off();
        RGBW wheel(uint8_t position);
        void demo1();
        void demo2();
        void setBrightness(uint8_t brightness);
        uint8_t getPixelNumber();
    private:
        uint8_t _led_count;
        uint8_t _brightness;
        const uint8_t* _left_border;
        const uint8_t* _right_border;
        Pixelstrip _pixelstrip;
        static const uint8_t _default_left_border[8];
        static const uint8_t PROGMEM _default_right_border[8];
};
#endif