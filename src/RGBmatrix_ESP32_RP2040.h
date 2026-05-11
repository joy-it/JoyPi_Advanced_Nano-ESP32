#ifndef RGBmatrix_ESP32_RP2040_h
#define RGBmatrix_ESP32_RP2040_h

class rgbmatrix_esp32{
    public:
        rgbmatrix_esp32()
        begin(void);
        show(void);
        void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
        void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t w);
        void setPixelColor(uint16_t n, uint32_t c);
        void fill(uint32_t c = 0, uint16_t first = 0, uint16_t count = 0);
        void setBrightness(uint8_t);
        void clear(void);
        void colorWipe();
        void rainbow();
        theaterChase();
        RGB_on();
        

        static uint32_t Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
            return ((uint32_t)w << 24) | ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
        }
        static uint32_t Color(uint8_t r, uint8_t g, uint8_t b) {
            return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
        }
    private:
        int _address;

}