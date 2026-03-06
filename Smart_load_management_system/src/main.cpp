#include <Arduino.h>
#include <PZEM004Tv30.h>
#include "pzem.h"
// put function declarations here:
//Setting up the PZEM hardwareSerial 
HardwareSerial pzemSerial(2); // Use UART1 for PZEM communication
PZEM004Tv30 pzem1(pzemSerial, 16, 17, 0x01); // Initialize PZEM with the hardware serial
PZEM004Tv30 pzem2(pzemSerial, 16, 17, 0x44); // Initialize second PZEM with the same hardware serial but different pins and address
PZEM004Tv30 pzem3(pzemSerial, 16, 17, 0x55); // Initialize third PZEM with the same hardware serial but different pins and address

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  Serial.printf("Getting the Energy Meter started");
}

void loop() {
// put your main code here, to run repeatedly:
readPZEM(pzem1, "The address for this pzem is 0x01");
readPZEM(pzem2, "The address for this PZEM is 0x44");
readPZEM(pzem3, "The address for this PZEM is 0x55");
Serial.println("==============================");
delay(2000);
}

