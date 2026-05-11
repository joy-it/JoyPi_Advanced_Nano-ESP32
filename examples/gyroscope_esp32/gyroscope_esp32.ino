#include <SPI.h>
#include "Gyroscope.h"

// initialize gyroscope
gyroscope_ICG_1020S gyroscope(19, 23, 18, 32, 2000000);

void setup() {
  // setup serial communication
  Serial.begin(115200);
  // setup SPI
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
