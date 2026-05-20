#include <SPI.h>
#include "Gyroscope.h"

#define MISO 12
#define MOSI 11
#define SCLK 13

// initialize gyroscope
gyroscope_ICG_1020S gyroscope(A1, 2000000, MISO, MOSI, SCLK, &SPI);

void setup() {
  // setup serial communication
  Serial.begin(9600);
  // setup SPI communication
  SPI.begin();
  // setup gyroscope
  gyroscope.begin();
}

void loop() {
  // print the read values from the gyroscope
  // frist the tilt
  Serial.print("Tilt:\t");
  Serial.println(gyroscope.getTilt());
  // then the temperature
  Serial.print("Temperature:\t");
  Serial.println(gyroscope.getTemperature());
  
  // wait for 1 second
  delay(1000);
}
