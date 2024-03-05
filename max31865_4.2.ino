/*************************************************** 
  This is a library for the Adafruit PT100/P1000 RTD Sensor w/MAX31865

  Designed specifically to work with the Adafruit RTD Sensor
  ----> https://www.adafruit.com/products/3328

  This sensor uses SPI to communicate, 4 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Adafruit_MAX31865.h>

// Use software SPI: CS, DI, DO, CLK
// To add multiple sensors they will need to have different CS pins 
Adafruit_MAX31865 thermo_1 = Adafruit_MAX31865(10, 11, 12, 13);
Adafruit_MAX31865 thermo_2 = Adafruit_MAX31865(9, 11, 12, 13);
Adafruit_MAX31865 thermo_3 = Adafruit_MAX31865(8, 11, 12, 13);
Adafruit_MAX31865 thermo_4 = Adafruit_MAX31865(7, 11, 12, 13);

// use hardware SPI, just pass in the CS pin
//Adafruit_MAX31865 thermo = Adafruit_MAX31865(10);

// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF      430.0
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  100.0

void setup() {
  Serial.begin(115200);
  Serial.println("Temperature 1, Temperature 2, Temperature 3, Temperature 4;");

  thermo_1.begin(MAX31865_2WIRE);  // set to 2WIRE or 4WIRE as necessary
  thermo_2.begin(MAX31865_2WIRE);  // set to 2WIRE or 4WIRE as necessary
  thermo_3.begin(MAX31865_2WIRE);  // set to 2WIRE or 4WIRE as necessary
  thermo_4.begin(MAX31865_2WIRE);  // set to 2WIRE or 4WIRE as necessary
}


void loop() {
  uint16_t rtd1 = thermo_1.readRTD();
  uint16_t rtd2 = thermo_2.readRTD();
  uint16_t rtd3 = thermo_3.readRTD();
  uint16_t rtd4 = thermo_4.readRTD();

  Serial.print(thermo_1.temperature(RNOMINAL, RREF)); Serial.print(",");
  Serial.print(thermo_2.temperature(RNOMINAL, RREF)); Serial.print(",");
  Serial.print(thermo_3.temperature(RNOMINAL, RREF)); Serial.print(",");
  Serial.print(thermo_4.temperature(RNOMINAL, RREF)); Serial.print(";");

  // Check and print any faults
  uint8_t fault = thermo_1.readFault();
  uint8_t fault2 = thermo_2.readFault();
  if (fault) {
    Serial.print("Fault 0x"); Serial.println(fault, HEX);
    if (fault & MAX31865_FAULT_HIGHTHRESH) {
      Serial.println("RTD High Threshold"); 
    }
    if (fault & MAX31865_FAULT_LOWTHRESH) {
      Serial.println("RTD Low Threshold"); 
    }
    if (fault & MAX31865_FAULT_REFINLOW) {
      Serial.println("REFIN- > 0.85 x Bias"); 
    }
    if (fault & MAX31865_FAULT_REFINHIGH) {
      Serial.println("REFIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault & MAX31865_FAULT_RTDINLOW) {
      Serial.println("RTDIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault & MAX31865_FAULT_OVUV) {
      Serial.println("Under/Over voltage"); 
    }
    thermo_1.clearFault();
  }
  Serial.println();
  delay(1000);
}
