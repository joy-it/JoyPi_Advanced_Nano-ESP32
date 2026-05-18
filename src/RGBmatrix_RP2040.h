#ifndef RGBmatrix_RP2040_h
#define RGBmatrix_RP2040_h

#include "Wire.h"

enum FunctionEnum{
    SHOW = 0;
    SETPIXELCOLOR = 1;
    FILL = 2;
    SETBRIGHTNESS = 3;
    GAMMA8 = 4;
    GAMMA32 = 5;
    NUMPIXEL = 6;
    COLORHSV = 7;
    CLEAR = 8;
    SENDDATA2SHOW = 9;
    SENDALLPIXRGB0 = 10;
    SENDALLPIXRGB1 = 11;
    SENDALLPIXRGB2 = 12;
    SENDALLPIXRGB3 = 13;
    SENDALLPIXRGB4 = 14;
    SENDALLPIXRGB5 = 15;
}

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
    public:
        void setFunc(uint8_t func);
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
        uint8_t* getData();
        void clearObject();
}

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
    private:
        uint32_t _value;
}

class Pixelstrip{
    public:
        Pixelstrip(int i2c_adress, uint8_t led_count, uint8_t brightness, TwoWire * awire=&Wire);
        void begin();
        void send(uint8_t cmd);
        void clear();
        void show();
        uint8_t* getWRGB(int color);
        void setPixelColor(uint8_t pos, RGBW color);
        void setPixelColorRGB(uint8_t pos, uint8_t r, uint8_t g, uint8_t b, uint8_t w);
        void sendPos2Show(uint8_t pos, uint8_t r, uint8_t g, uint8_t b);
        void sendColor2Send(uint8_t* pos, uint32_t color);
        void sendAllPixRGB(uint32_t color);
        void fill(uint8_t r, uint8_t g, uint8_t b, uint8_t w, uint8_t first, uint8_t end);
        void fillColor(uint32_t color, uint8_t first, uint8_t end);
        void setBrightness(uint8_t brightness);
        uint8_t getNumPixels() const;
        uint8_t getGamma8(uint8_t color);
        uint32_t getGamma32(uint32_t color);
        uint8_t getColorHSV(uint8_t x);
    private:
        uint8_t ;
        uint8_t _brightness;
        int _i2c_address;
        TwoWire * _wire;
        LED_Transfer_Data _data;
        void _write(uint8_t cmd, uint8_t* data);
        uint8_t _read();



}

class RGB_Matrix{
    public:
        RGB_Matrix(int i2c_adress, uint8_t led_count, uint8_t brightness, int* left_border, int*right_border, TwoWire * awire=&Wire)
        void begin();
        void show();
        void clean();
        void setPixel(uint8_t position, uint32_t colour);
        void colorWipe(uint32_t colour, uint8_t wait_ms);
        void rainbow(uint8_t wait_ms, uint8_t iterations);
        void theaterChase(uint32_t colour, uint8_t wait_ms, uint8_t iterations);
        void RGB_on(uint32_t colour);
        void RGB_off();
        void wheel(uint8_t position);
        void demo1();
        void demo2();
    private:
        uint8_t _led_count;
        uint8_t _brightness;
        int* _left_border;
        int* _right_border;
        Pixelstrip _strip;
}