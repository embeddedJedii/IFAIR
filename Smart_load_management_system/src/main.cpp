#include <Arduino.h>
#include <PZEM004Tv30.h>
#include "pzem.h"
#include "batteryPercentage.h"
#include "I2C.h"
// put function declarations here:
//Setting up the PZEM hardwareSerial 

//vARIABLE declarations
float batteryPerecntage = 70; // Assuming battery percentage is 70 for testing
HardwareSerial pzemSerial(2); // Use UART1 for PZEM communication
PZEM004Tv30 pzem1(pzemSerial, 16, 17, 0x01); // Initialize PZEM with the hardware serial
PZEM004Tv30 pzem2(pzemSerial, 16, 17, 0x44); // Initialize second PZEM with the same hardware serial but different pins and address
PZEM004Tv30 pzem3(pzemSerial, 16, 17, 0x55); // Initialize third PZEM with the same hardware serial but different pins and address

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  Serial.printf("Getting the Energy Meter started");
  Wire.begin(); // Master mode
}

void loop() {
// put your main code here, to run repeatedly:
readPZEM(pzem1, "The address for this pzem is 0x01");
readPZEM(pzem2, "The address for this PZEM is 0x44");
readPZEM(pzem3, "The address for this PZEM is 0x55");
 float voltage = readVoltage() + 2.77;
 float batteryPercentage = getBatteryPercentage(voltage);

 if(voltage > 30) Serial.println("48V Battery Detected");
 else Serial.println("24V Battery Detected");

 Serial.print("Voltage: "); Serial.println(voltage);
 Serial.print("Battery: "); Serial.print(batteryPercentage); Serial.println("%");
 Serial.println("----------------------");

shutDownPiority(pzem1, pzem2, pzem3, batteryPerecntage); // Assuming battery percentage is 70 for testing
turnOnPiority(batteryPerecntage); 
Serial.println("==============================");

  data.energy1 = 10.5;
  data.energy2 = 11.2;
  data.energy3 = 12.1;

  data.voltage1 = 220.5;
  data.voltage2 = 221.1;
  data.voltage3 = 219.8;

  data.current1 = 5.2;
  data.current2 = 4.8;
  data.current3 = 6.1;

  data.frequency = 50.0;

  data.power1 = 1150;
  data.power2 = 1100;
  data.power3 = 1200;

  data.batteryVoltage = 27.5;
  data.temperature = 32.4;
  data.totalLoad = 3450;
  sendData();
delay(2000);
}
