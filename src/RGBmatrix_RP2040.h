#ifndef RGBmatrix_RP2040_h
#define RGBmatrix_RP2040_h

#include "Wire.h"

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
        

        static uint32_t Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
            return ((uint32_t)w << 24) | ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
        }
        static uint32_t Color(uint8_t r, uint8_t g, uint8_t b) {
            return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
        }
    private:
        uint8_t _led_count;
        uint8_t _brightness;
        int* _left_border;
        int* _right_border;
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
        void setPos(uint8_t pos);
        void setRed(uint8_t red);
        void setGreen(uint8_t green);
        void setBlue(uint8_t blue);
        void setWhite(uint8_t white);
        void setC(uint8_t c);
        void setBright(uint8_t bright);
        void setFrist(uint8_t first);
        void setCount(uint8_t count);
        void setData0(uint8_t data0);
        void setData1(uint8_t data1);
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
        operator uint32_t() const;
    private:
        uint32_t value;
}

class Pixelstrip{
    public:

    private:
        uint8_t _led_count;
        int _i2c_address;
        TwoWire * _wire;


}