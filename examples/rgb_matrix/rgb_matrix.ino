// Import necessary library
#include "RGBmatrix_RP2040.h"
#include <Wire.h>

// define object for led matrix
RGB_Matrix led_matrix;

// define shape of a heart
int heart [] = {1,6,8,9,10,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,41,42,43,44,45,46,50,51,52,53,59,60};

void setup() {
  // setup serial communication
  Serial.begin(115200);
  // setup led matrix
  Wire.begin();
  led_matrix.begin();
  led_matrix.setBrightness(125);
  led_matrix.show();
}

void loop() {
  // Some example procedures showing how to display the pixels:
  
  // colorWipe animation with different colours
  led_matrix.colorWipe(RGBW(255, 0, 0));  //  Red
  led_matrix.colorWipe(RGBW(0, 255, 0));  //  Green
  led_matrix.colorWipe(RGBW(0, 0, 255));  //  Blue

  // clear LED matrix
  led_matrix.clean();

  // theaterChase animation with different colours
  led_matrix.theaterChase(RGBW(255, 255, 255)); //  White
  led_matrix.theaterChase(RGBW(255, 0, 0));     //  Red
  led_matrix.theaterChase(RGBW(0, 0, 255));     // Blue

  // clear LED matrix
  led_matrix.clean();

  // show different colours each 2 seconds
  led_matrix.RGB_on(RGBW(255, 255, 0)); //  Yellow
  delay(2000);
  led_matrix.RGB_on(RGBW(0, 255, 255)); //  Turquise
  delay(2000);
  led_matrix.RGB_on(RGBW(255, 0, 255)); //  Purple
  delay(2000);

  // clear LED matrix
  led_matrix.clean();

  // display a heart
  int index_symbol = 0;
  for (int i = 0; i < led_matrix.getPixelNumber(); i++) {
    if (heart[index_symbol] == i){
      led_matrix.setPixel(i, RGBW(255, 0, 0));
      index_symbol++;
     }
  }
  led_matrix.show();

  // clear LED matrix after 5 seconds
  delay(5000);
  led_matrix.clean();

  // start rainbow animation
  led_matrix.rainbow();
}
