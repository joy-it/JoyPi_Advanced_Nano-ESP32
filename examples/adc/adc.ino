// import necessary libraries
#include <SPI.h>
#include "ADC.h"

// initialize adc
ADC_TLA2518 adc(12, 11, 13, 10, 2000000);

void setup() {
  // setup serial communication for serial monitor
  Serial.begin(9600);
  // setup SPI
  SPI.begin();
  // setup adc
  adc.begin();

  // print a table header to the serial monitor
  for(int i = 0; i < 8; i++){
    Serial.print("| RawVal CH");
    Serial.print(i);
    Serial.print("  |    V   ");
  }
  Serial.println("|");
  for (int i = 0; i < 195; i++){
    Serial.print("-");
  }
  Serial.println();

}

void loop() {
  // read values from ADC in each run and print it
  for (int i = 0; i < 8; i++){
    int value = adc.read_adc_value(i);
    // without giving value to the method the channel value will be read again
    double voltage = adc.read_voltage(i, value);

    // print table
    Serial.print("|     ");
    Serial.print(value);
    Serial.print("    |  ");
    Serial.print(voltage);
    Serial.print("  ");

    // delay this 100 ms
    delay(100);
  }
  // print next line
  Serial.println("|");
  // wait 2 seconds
  delay(2000);
}
