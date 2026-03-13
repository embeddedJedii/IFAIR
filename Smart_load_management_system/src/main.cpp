#include <Arduino.h>
#include <PZEM004Tv30.h>
#include "pzem.h"
#include "batteryPercentage.h"
#include "I2C.h"
#include "thermistor.h"
// put function declarations here:
//Setting up the PZEM hardwareSerial 
#define fanPin 18
//vARIABLE declarations
float batteryPerecntage; // Assuming battery percentage is 70 for testing
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
 float static voltage = readVoltage() + 2.77;
 float static batteryPercentage = getBatteryPercentage(voltage);

 if(voltage > 30) Serial.println("48V Battery Detected");
 else Serial.println("24V Battery Detected");

 Serial.print("Voltage: "); Serial.println(voltage);
 Serial.print("Battery: "); Serial.print(batteryPercentage); Serial.println("%");
 Serial.println("----------------------");

shutDownPiority(pzem1, pzem2, pzem3, batteryPerecntage); // Assuming battery percentage is 70 for testing
turnOnPiority(batteryPerecntage); 
float static temperature = tempData();
if(temperature >32.00) digitalWrite(fanPin, HIGH);
else digitalWrite(fanPin, LOW);
Serial.println("==============================");

  data.energy1 = 10.5; //pzem1.energy();
  data.energy2 = 11.2; //pzem2.energy();
  data.energy3 = 12.1; //pzem3.energy();

  data.voltage1 = 220.5; //pzem1.voltage();
  data.voltage2 = 221.1; //pzem2.voltage();
  data.voltage3 = 219.8; //pzem3.voltage();
  data.current1 = 5.2; //pzem1.current();
  data.current2 = 4.8; //pzem2.current();
  data.current3 = 6.1; //pzem3.current();

  data.frequency = 50.0; //pzem1.frequency(); All pzems should have the same frequency since they are all from the same inverter

  data.power1 = 1150; //pzem1.power();
  data.power2 = 1100; //pzem2.power();
  data.power3 = 1200; //pzem3.power();

  data.batteryVoltage = 27.5; // voltage
  data.temperature = 32.4; //temperature;
  data.totalLoad = 3450;  //total energy consumed
  data.percentage = batteryPercentage;
  sendData();
delay(2000);
}
    