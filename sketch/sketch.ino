// Including display library
#include "TM1637.h"

// Defining pins
#define FSR_Pin 2
#define CLK 2
#define DIO 1

// IMPORTANT note: display must be read like 00.00 kg

float r0 = 10000;                  // Aux resistance value
float Vin = 5;              // V in
int tare = 0;                // Tare
TM1637 tm1637(CLK,DIO);       // Display

void setup() {
  // Initializing diplay
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);
  tm1637.point(POINT_OFF);
  Serial.begin(9600);
}

void loop() {
  float FSRead = analogRead(FSR_Pin) * Vin / 1024;   // Reading FSR measure

  Serial.print(FSRead);
  Serial.print(" ");

  FSRead = pow(271.0 / ( r0 * ( (Vin/FSRead) -1 ) ),(1/0.69))*100;

  Serial.println(FSRead);

  int weight = int(FSRead*100) - tare;       // Calibrating

  // Displaing the weight measure
  tm1637.display(3,weight % 10);
  weight = int(weight/10);
  tm1637.display(2,weight % 10);
  weight = int(weight/10);
  tm1637.display(1,weight % 10);
  weight = int(weight/10);
  tm1637.display(0,weight % 10);

  // Some delay
  delay(200);
}
