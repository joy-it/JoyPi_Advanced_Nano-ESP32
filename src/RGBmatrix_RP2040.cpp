#include "RGBmatrix_RP2040.h"

//++++++++++++++++++++++++++LED_Transfer_Data Class++++++++++++++++++++++++++
LED_Transfer_Data::LED_Transfer_Data() {
    this->clearObject();
}
void LED_Transfer_Data::setFunc(FunctionEnum func){
    (this->_func) = static_cast<uint8_t>(func);
}
uint8_t LED_Transfer_Data::getFunc() const{
    return this->_func;
}
void LED_Transfer_Data::setPos(uint8_t pos){
    (this->_pos) = pos;
}
uint8_t LED_Transfer_Data::getPos() const{
    return this->_pos;
}
void LED_Transfer_Data::setRed(uint8_t red){
    (this->_red) = red;
}
uint8_t LED_Transfer_Data::getRed() const{
    return this->_red;
}
void LED_Transfer_Data::setGreen(uint8_t green){
    (this->_green) = green;
}
uint8_t LED_Transfer_Data::getGreen() const{
    return this->_green;
}
void LED_Transfer_Data::setBlue(uint8_t blue){
    (this->_blue) = blue;
}
uint8_t LED_Transfer_Data::getBlue() const{
    return this->_blue;
}
void LED_Transfer_Data::setWhite(uint8_t white){
    (this->_white) = white;
}
uint8_t LED_Transfer_Data::getWhite() const{
    return this->_white;
}
void LED_Transfer_Data::setC(uint8_t c){
    (this->_c) = c;
}
uint8_t LED_Transfer_Data::getC() const{
    return this->_c;
}
void LED_Transfer_Data::setBright(uint8_t bright){
    (this->_bright) = bright;
}
uint8_t LED_Transfer_Data::getBright() const{
    return this->_bright;
}
void LED_Transfer_Data::setFirst(uint8_t first){
    (this->_first) = first;
}
uint8_t LED_Transfer_Data::getFirst() const{
    return this->_first;
}
void LED_Transfer_Data::setCount(uint8_t count){
    (this->_count) = count;
}
uint8_t LED_Transfer_Data::getCount() const{
    return this->_count;
}
void LED_Transfer_Data::setData0(uint8_t data0){
    (this->_data0) = data0;
}
uint8_t LED_Transfer_Data::getData0() const{
    return this->_data0;
}
void LED_Transfer_Data::setData1(uint8_t data1){
    (this->_data1) = data1;
}
uint8_t LED_Transfer_Data::getData1() const{
    return this->_data1;
}
void LED_Transfer_Data::getData(uint8_t* _transferData){
    _transferData[0]  = this->_func;
    _transferData[1]  = this->_pos;
    _transferData[2]  = this->_red;
    _transferData[3]  = this->_green;
    _transferData[4]  = this->_blue;
    _transferData[5]  = this->_white;
    _transferData[6]  = this->_c;
    _transferData[7]  = this->_bright;
    _transferData[8]  = this->_first;
    _transferData[9]  = this->_count;
    _transferData[10] = this->_data0;
    _transferData[11] = this->_data1;
}
void LED_Transfer_Data::clearObject(){
    this->_func = 0;
    this->_pos = 0;
    this->_red = 0;
    this->_green = 0;
    this->_blue = 0;
    this->_white = 0;
    this->_c = 0;
    this->_bright = 0;
    this->_first = 0;
    this->_count = 0;
    this->_data0 = 0;
    this->_data1 = 0;
}

//++++++++++++++++++++++++++RGBW Class++++++++++++++++++++++++++
RGBW::RGBW(uint32_t color){
    this->_value = color;
}
RGBW::RGBW(uint8_t r, uint8_t g, uint8_t b){
    this->_value = ((uint32_t)r << 16) | ((uint32_t)g << 8) | (uint32_t)b;
}
RGBW::RGBW(uint8_t r, uint8_t g, uint8_t b, uint8_t w){
    this->_value = ((uint32_t)w << 24) | ((uint32_t)r << 16) | ((uint32_t)g << 8) | (uint32_t)b;
}
uint8_t RGBW::getR() const{
    return (this->_value >> 16) & 0xFF;
}
uint8_t RGBW::getG() const{
    return (this->_value >> 8) & 0xFF;
}
uint8_t RGBW::getB() const{
    return this->_value & 0xFF;
}
uint8_t RGBW::getW() const{
    return (this->_value >> 24) & 0xFF;
}
uint32_t RGBW::getValue() const{
    return this->_value;
}
void RGBW::getValue(uint8_t* transfer_data){
    transfer_data[0] = this->getR();
    transfer_data[1] = this->getG();
    transfer_data[2] = this->getB();
    transfer_data[3] = this->getW();
}
//++++++++++++++++++++++++++Pixelstrip Class++++++++++++++++++++++++++
void Pixelstrip::begin(){
    this->_data.clearObject();
    this->setBrightness(this->_brightness);
}
void Pixelstrip::send(uint8_t cmd){
    uint8_t buffer[12];
    this->_data.getData(buffer);
    this->_write(cmd, buffer, sizeof(buffer) / sizeof(buffer[0]));
    this->_data.clearObject();
}
void Pixelstrip::_write(uint8_t cmd, const uint8_t* data, uint8_t length){
    uint8_t buffer[2 + length];
    buffer[0] = static_cast<uint8_t>(cmd & 0xFF);
    buffer[1] = static_cast<uint8_t>(length & 0xFF);
    for (uint8_t i = 0; i < length; i++) {
        buffer[i + 2] = static_cast<uint8_t>(data[i] & 0xFF);
    }
    this->_wire->beginTransmission(this->_i2c_address);
    this->_wire->write(buffer, sizeof(buffer));
    uint8_t result = this->_wire->endTransmission();
    delay(3);
}
uint8_t Pixelstrip::_read(){
    this->_wire->requestFrom(this->_i2c_address, 1);
    if (this->_wire->available()){
        return this->_wire->read();
    }
    return -1;
}
void Pixelstrip::clear(){
    this->_data.setFunc(FunctionEnum::CLEAR);
    this->send(0x00);
}
void Pixelstrip::show(){
    this->_data.setFunc(FunctionEnum::SHOW);
    this->send(0x00);
}
void Pixelstrip::setPixelColor(uint8_t pos, RGBW color){
    this->setPixelColorRGB(pos, color.getR(), color.getG(), color.getB(), color.getW());
}
void Pixelstrip::setPixelColorRGB(uint8_t pos, uint8_t r, uint8_t g, uint8_t b, uint8_t w){
    this->_data.setFunc(FunctionEnum::SETPIXELCOLOR);
    this->_data.setPos(pos);
    this->_data.setRed(r);
    this->_data.setGreen(g);
    this->_data.setBlue(b);
    this->_data.setWhite(w);
    this->send(0x00);
}
void Pixelstrip::sendPos2Show(uint8_t* pos, uint8_t pos_length, uint8_t r, uint8_t g, uint8_t b){
    this->_data.setFunc(FunctionEnum::SENDDATA2SHOW);
    this->_data.setRed(r);
    this->_data.setGreen(g);
    this->_data.setBlue(b);
    for (uint8_t i = 0; i < pos_length; i++){
        if (pos[i] >= 0 && pos[i] <= 7) this->_data.setPos(this->_data.getPos() | (1 << pos[i]));
        if (pos[i] >= 8 && pos[i] <= 15)this->_data.setWhite(this->_data.getWhite() | (1 << (pos[i] - 8)));
        if (pos[i] >= 16 && pos[i] <= 23) this->_data.setC(this->_data.getC() | (1 << (pos[i] - 16)));
        if (pos[i] >= 24 && pos[i] <= 31) this->_data.setBright(this->_data.getBright() | (1 << (pos[i] - 24)));
        if (pos[i] >= 32 && pos[i] <= 39) this->_data.setFirst(this->_data.getFirst() | (1 << (pos[i] - 32)));
        if (pos[i] >= 40 && pos[i] <= 47) this->_data.setCount(this->_data.getCount() | (1 << (pos[i] - 40)));
        if (pos[i] >= 48 && pos[i] <= 55) this->_data.setData0(this->_data.getData0() | (1 << (pos[i] - 48)));
        if (pos[i] >= 56 && pos[i] <= 63) this->_data.setData1(this->_data.getData1() | (1 << (pos[i] - 56)));
    }
    this->send(0x00);
}
void Pixelstrip::sendColor2Show(uint8_t* pos, uint8_t pos_length, RGBW color){
    this->sendPos2Show(pos, pos_length, color.getR(), color.getG(), color.getB());
}
void Pixelstrip::fill(uint8_t r, uint8_t g, uint8_t b, uint8_t w, uint8_t first, uint8_t end){
    this->_data.setFunc(FunctionEnum::FILL);
    this->_data.setRed(r);
    this->_data.setGreen(g);
    this->_data.setBlue(b);
    this->_data.setWhite(w);
    this->_data.setFirst(first);
    this->_data.setCount(end - first);
    this->send(0x00);
}
void Pixelstrip::fillColor(RGBW color, uint8_t first, uint8_t end){
    this->fill(color.getR(), color.getG(), color.getB(), color.getW(), first, end);
}
void Pixelstrip::setBrightness(uint8_t brightness){
    this->_brightness = brightness;
    this->_data.setFunc(FunctionEnum::SETBRIGHTNESS);
    this->_data.setBright(brightness);
    this->send(0x00);
}
uint8_t Pixelstrip::getNumPixels() const{
    return this->_led_count;
}
uint8_t Pixelstrip::getGamma8(uint8_t color){
    this->_data.setFunc(FunctionEnum::GAMMA8);
    this->_data.setData0(color);
    this->send(0x01);
    return this->_read();
}
uint32_t Pixelstrip::getGamma32(uint32_t color){
    this->_data.setFunc(FunctionEnum::GAMMA32);
    // ToDo smth wrong here
    this->_data.setData0((color >> 16) & 0xFF);
    this->_data.setData1((color >> 8) & 0xFF);
    this->send(0x01);
    return this->_read();
}
uint8_t Pixelstrip::getColorHSV(uint8_t x){
    this->_data.setFunc(FunctionEnum::COLORHSV);
    this->_data.setData0(x);
    this->send(0x01);
    return this->_read();
}

//++++++++++++++++++++++++++RGB_Matrix Class++++++++++++++++++++++++++
const uint8_t RGB_Matrix::_default_left_border[8] = {
    0, 8, 16, 24, 32, 40, 48, 56
};
const uint8_t RGB_Matrix::_default_right_border[8] = {
    7, 15, 23, 31, 39, 47, 55, 63
};
void RGB_Matrix::begin(){
    this->_pixelstrip.begin();
}
void RGB_Matrix::show(){
    this->_pixelstrip.show();
}
void RGB_Matrix::clean(){
    this->RGB_off();
}
void RGB_Matrix::setPixel(uint8_t position, RGBW colour){
    this->_pixelstrip.setPixelColor(position, colour);
}
void RGB_Matrix::colorWipe(RGBW colour, uint8_t wait){
    for (uint8_t i = 0; i < this->_led_count; i++){
        this->setPixel(i, colour);
        this->show();
        delay(wait);
    }
}
void RGB_Matrix::rainbow(uint8_t wait_ms, uint8_t iterations){
    for (int j = 0; j < 256*iterations; j++){
        for (uint8_t i = 0; i < this->_led_count; i++){
            this->setPixel(i, this->wheel(i + j));
        }
        this->show();
        delay(wait_ms);
    }
}
void RGB_Matrix::theaterChase(RGBW colour, uint8_t wait_ms, uint8_t iterations){
    for (int j = 0; j < iterations; j++){
        for (int q = 0; q < 3; q++){
            for (uint8_t i = 0; i < this->_led_count; i += 3){
                this->setPixel(i + q, colour);
            }
            this->show();
            delay(wait_ms);
            for (uint8_t i = 0; i < this->_led_count; i += 3){
                this->setPixel(i + q, RGBW(0));
            }
        }
    }
}
void RGB_Matrix::RGB_on(RGBW colour){
    for (uint8_t i = 0; i < this->_led_count; i++){
        this->setPixel(i, colour);
    }
    this->show();
}
void RGB_Matrix::RGB_off(){
    for(uint8_t i = 0; i < this->_led_count; i++){
        this->setPixel(i, RGBW(0));
    }
    this->show();
}
void RGB_Matrix::setBrightness(uint8_t brightness){
    this->_pixelstrip.setBrightness(brightness);
}
RGBW RGB_Matrix::wheel(uint8_t position){
    if (position < 85){
        return RGBW(position * 3, 255 - position * 3, 0, 0);
    } 
    else if (position < 170){
        position -= 85;
        return RGBW(255 - position * 3, 0, position * 3, 0);
    } else {
        position -= 170;
        return RGBW(0, position * 3, 255 - position * 3, 0);
    }
}
void RGB_Matrix::demo1(){
    // white chaser
    this->theaterChase(RGBW(127, 127, 127, 0), 50, 10);
    // red chaser
    this->theaterChase(RGBW(127, 0, 0, 0), 50, 10);
    // blue chaser
    this->theaterChase(RGBW(0, 0, 127,0), 50, 10);
    this->rainbow(20, 1);
    this->clean();
}
void RGB_Matrix::demo2(){
    for (uint8_t i = 0; i < 3; i++){
        this->demo1();
    }
    uint8_t heart[] = {1,6,8,9,10,13,14,15,16,17,18,19,20,21,22,23,
                         24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,
                         41,42,43,44,45,46,50,51,52,53,59,60};
    for (uint8_t i = 0; i < sizeof(heart); i++){
        this->setPixel(heart[i], RGBW(255, 0, 0, 0));
    }
    this->show();
}
uint8_t RGB_Matrix::getPixelNumber(){
    return this->_led_count;
}