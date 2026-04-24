// // #include <Arduino.h>
// // #include <PZEM004Tv30.h>
// // #include "pzem.h"
// // #include "batteryPercentage.h"
// // #include "I2C.h"
// // #include "thermistor.h"
// // // put function declarations here:
// // //Setting up the PZEM hardwareSerial 
// // #define fanPin 18
// // //vARIABLE declarations
// // float batteryPercentage; // Assuming battery percentage is 70 for testing
// // HardwareSerial pzemSerial(2); // Use UART1 for PZEM communication
// // PZEM004Tv30 pzem1(pzemSerial, 16, 17, 0x01); // Initialize PZEM with the hardware serial
// // PZEM004Tv30 pzem2(pzemSerial, 16, 17, 0x02); // Initialize second PZEM with the same hardware serial but different pins and address
// // PZEM004Tv30 pzem3(pzemSerial, 16, 17, 0x03); // Initialize third PZEM with the same hardware serial but different pins and address
// // //HardwareSerial pzemSerial3(2); // Use UART2
// // //PZEM004Tv30 pzem1(pzemSerial3, 12, 13, 0x01); // Use UART2 for third PZEM
// // void setup() {
// //   // put your setup code here, to run once:
// //   pzemSerial.begin(9600, SERIAL_8N1, 16, 17);
// //   //pzemSerial3.begin(9600, SERIAL_8N1, 12, 13); // RX = 12, TX = 13
// //   Serial.begin(115200);
// //   Serial.printf("Getting the Energy Meter started");
// //   Wire.begin(); // Master mode
// // }

// // void loop() {
// // // put your main code here, to run repeatedly: 
// // readPZEM(pzem1, "The address for this pzem is 0x01");
// // delay(100);
// // readPZEM(pzem2, "The address for this PZEM is 0x44");
// // delay(100);
// // readPZEM(pzem3, "The address for this PZEM is 0x55");
// //  float  voltage = readVoltage() + 2.77;
// //  batteryPercentage = getBatteryPercentage(voltage);

// //  if(voltage > 30) Serial.println("48V Battery Detected");
// //  else Serial.println("24V Battery Detected");

// //  Serial.print("Voltage: "); Serial.println(voltage);
// //  Serial.print("Battery: "); Serial.print(batteryPercentage); Serial.println("%");
// //  Serial.println("----------------------");

// // shutDownPiority(pzem1, pzem2, pzem3, batteryPercentage); // Assuming battery percentage is 70 for testing
// // turnOnPiority(batteryPercentage); 
// // float static temperature = tempData();
// // if(temperature >32.00) digitalWrite(fanPin, HIGH);
// // else digitalWrite(fanPin, LOW);
// // Serial.println("==============================");

// //   data.energy1 = 10.5; //pzem1.energy();
// //   data.energy2 = 11.2; //pzem2.energy();
// //   data.energy3 = 12.1; //pzem3.energy();

// //   data.voltage1 = 220.5; //pzem1.voltage();
// //   data.voltage2 = 221.1; //pzem2.voltage();
// //   data.voltage3 = 219.8; //pzem3.voltage();
// //   data.current1 = 5.2; //pzem1.current();
// //   data.current2 = 4.8; //pzem2.current();
// //   data.current3 = 6.1; //pzem3.current();

// //   data.frequency = 50.0; //pzem1.frequency(); All pzems should have the same frequency since they are all from the same inverter

// //   data.power1 = 1150; //pzem1.power();
// //   data.power2 = 1100; //pzem2.power();
// //   data.power3 = 1200; //pzem3.power();

// //   data.batteryVoltage = 27.5; // voltage
// //   data.temperature = 32.4; //temperature;
// //   data.totalLoad = 3450;  //total energy consumed
// //   data.percentage = batteryPercentage;
// //   sendData();
// // delay(2000);
// // }
//     #include <Arduino.h>
// #include <PZEM004Tv30.h>
// #include "pzem.h"
// #include "batteryPercentage.h"
// #include "I2C.h"
// #include "thermistor.h"

// // PINS
// #define fanPin 18

// // VARIABLES
// float batteryPercentage;

// // UART instances
// HardwareSerial pzemSerial1(2); // UART2 for PZEM1 (0x01)
// HardwareSerial pzemSerial2(1); // UART1 for PZEM2 & PZEM3

// // PZEM instances
// PZEM004Tv30 pzem1(pzemSerial1, 2, 4, 0x01); // Dedicated UART2, pins 12(RX)/13(TX)
// PZEM004Tv30 pzem2(pzemSerial2, 16, 17, 0x02); // UART1, pins 16(RX)/17(TX)
// PZEM004Tv30 pzem3(pzemSerial2, 16, 17, 0x03); // UART1, same pins as pzem2

// void setup() {
//   // Start Serial
// Serial.begin(115200);
//   Serial.println("Getting the Energy Meter started");
  
//   // Start UARTs
//   pzemSerial1.begin(9600, SERIAL_8N1, 2, 4); // PZEM1
//   pzemSerial2.begin(9600, SERIAL_8N1, 16, 17); // PZEM2 & PZEM3
//   Wire.begin(); // I2C master
// }

// void loop() {
//   // Read PZEMs
//   readPZEM(pzem1, "PZEM 0x01 (UART2)");
//   delay(100);
//   readPZEM(pzem2, "PZEM 0x02 (UART1)");
//   delay(100);
//   readPZEM(pzem3, "PZEM 0x03 (UART1)");
//   delay(100);

//   // Battery voltage & percentage
//   float voltage = readVoltage() + 2.77;
//   batteryPercentage = getBatteryPercentage(voltage);

//   if(voltage > 30) Serial.println("48V Battery Detected");
//   else Serial.println("24V Battery Detected");

//   Serial.print("Voltage: "); Serial.println(voltage);
//   Serial.print("Battery: "); Serial.print(batteryPercentage); Serial.println("%");
//   Serial.println("----------------------");

//   // Load control
//   shutDownPiority(pzem1, pzem2, pzem3, batteryPercentage);
//   turnOnPiority(batteryPercentage);

//   // Fan control
//   float temperature = tempData();
//   digitalWrite(fanPin, temperature > 32.0 ? HIGH : LOW);
//   Serial.println("==============================");

//   // Data sending (replace with actual readings if desired)
//   data.energy1 = pzem1.energy();
//   data.energy2 = pzem2.energy();
//   data.energy3 = pzem3.energy();

//   data.voltage1 = pzem1.voltage();
//   data.voltage2 = pzem2.voltage();
//   data.voltage3 = pzem3.voltage();

//   data.current1 = pzem1.current();
//   data.current2 = pzem2.current();
//   data.current3 = pzem3.current();

//   data.frequency = 50.0; // Same frequency
//   data.power1 = pzem1.power();
//   data.power2 = pzem2.power();
//   data.power3 = pzem3.power();

//   data.batteryVoltage = voltage;
//   data.temperature = temperature;
//   data.totalLoad = data.power1 + data.power2 + data.power3;
//   data.percentage = batteryPercentage;

//   sendData();
//   delay(2000);
// }
#include <Arduino.h>
#include <PZEM004Tv30.h>
#include "pzem.h"
#include "batteryPercentage.h"
#include "I2C.h"
#include "thermistor.h"

#define fanPin 18
const uint8_t COIL_1 = 27;
const uint8_t COIL_2 = 26;
const uint8_t COIL_3 = 25;


float batteryPercentage = 43; // Assuming battery percentage is 70 for testing

// UART2 for first two PZEMs
HardwareSerial pzemSerial(2);

// UART1 for third PZEM
HardwareSerial pzemSerial3(1);

// PZEMs on UART2
PZEM004Tv30 pzem1(pzemSerial, 16, 17, 0x01);
PZEM004Tv30 pzem2(pzemSerial, 16, 17, 0x02);

// Third PZEM on different UART
PZEM004Tv30 pzem3(pzemSerial3, 2, 4, 0x03);

void setup() {

  Serial.begin(115200);

  // Start UART2
  pzemSerial.begin(9600, SERIAL_8N1, 16, 17);

  // Start UART1 for third PZEM
  pzemSerial3.begin(9600, SERIAL_8N1, 2, 4);

  Wire.begin();
    pinMode(COIL_1, OUTPUT);
    pinMode(COIL_2, OUTPUT);
    pinMode(COIL_3, OUTPUT);
    pinMode(fanPin, OUTPUT);
  Serial.println("Energy Meter System Starting...");
}

void loop() {

readPZEM(pzem1, "PZEM 1 (0x01)");
  delay(100);
// digitalWrite(COIL_1, HIGH);
// digitalWrite(COIL_2, HIGH);
// digitalWrite(COIL_3, HIGH);
readPZEM(pzem2, "PZEM 2 (0x02)");
  delay(100);

readPZEM(pzem3, "PZEM 3 (0x03)");
  delay(100);

  float voltage = readVoltage() + 2.47;

  batteryPercentage = getBatteryPercentage(voltage);

  if(voltage > 20)
      Serial.println("48V Battery Detected");
  else
      Serial.println("24V Battery Detected");

  Serial.print("Voltage: ");
  Serial.println(voltage);

  Serial.print("Battery: ");
  Serial.print(batteryPercentage);
  Serial.println("%");

  Serial.println("----------------------");

 shutDownPiority(pzem1, pzem2, pzem3, batteryPercentage);
 turnOnPiority(batteryPercentage);

  float temperature = tempData();

  if(temperature > 38.0)
      digitalWrite(fanPin, HIGH); 
  else
      digitalWrite(fanPin, LOW);

  Serial.println("==============================");
  //   // Data sending (replace with actual readings if desired)
  data.energy1 = pzem1.energy(); 
  data.energy2 = pzem2.energy();
  data.energy3 = pzem3.energy();

  data.voltage1 = pzem1.voltage();
  data.voltage2 = pzem2.voltage();
  data.voltage3 = pzem3.voltage();

  data.current1 = pzem1.current();
  data.current2 = pzem2.current();
  data.current3 = pzem3.current();

  data.frequency = pzem3.frequency(); // Same frequency
  data.power1 = pzem1.power();
  data.power2 = pzem2.power();
  data.power3 = pzem3.power();
  data.batteryVoltage = voltage;
  data.temperature =temperature;
  data.totalLoad = data.power1 + data.power2 + data.power3;
  data.percentage =batteryPercentage;

  sendData();

  delay(2000);
}