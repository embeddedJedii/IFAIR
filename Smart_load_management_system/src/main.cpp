#include <Arduino.h>
#include <PZEM004Tv30.h>
#include "pzem.h"
#include "batteryPercentage.h"
#include "I2C.h"
#include "thermistor.h"
#define BATTERY_PIN 35
#define fanPin 18
const uint8_t COIL_1 = 27;
const uint8_t COIL_2 = 26;
const uint8_t COIL_3 = 25;


float batteryPercentage;

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
    
  digitalWrite(COIL_1, HIGH);
  digitalWrite(COIL_2, HIGH);
  digitalWrite(COIL_3, HIGH);
  Serial.println("Energy Meter System Starting...");
  analogSetPinAttenuation(BATTERY_PIN, ADC_11db);
}

void loop() {                                                                                                                                                                                                                                                                                                                                                                                    

readPZEM(pzem1, "PZEM 1 (0x01)");
  delay(100);
readPZEM(pzem2, "PZEM 2 (0x02)");
  delay(100);

readPZEM(pzem3, "PZEM 3 (0x03)");
  delay(100);
  float voltage = readVoltage();
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

static bool resetDone = false;

if(batteryPercentage >= 100 && !resetDone){
    pzem1.resetEnergy();
    pzem2.resetEnergy();
    pzem3.resetEnergy();
    resetDone = true;
}

if(batteryPercentage < 100){++
    resetDone = false;
}
shutDownPiority(pzem1, pzem2, pzem3, batteryPercentage);
 //turnOnPiority(batteryPercentage);

  float temperature = tempData();

  if(temperature > 38.0)
      digitalWrite(fanPin, HIGH); 
  else
      digitalWrite(fanPin, LOW);

  Serial.println("==============================");
  //   // Data sending (replace with actual readings if desired)
  data.energy1 = pzem1.energy()*1000; 
  data.energy2 = pzem2.energy()*1000;
  data.energy3 = pzem3.energy()*1000;

  data.voltage1 = pzem1.voltage();
  data.voltage2 = pzem2.voltage();
  data.voltage3 = pzem3.voltage();
  // data.totalVoltage = data.voltage1 || data.voltage2 ||data.voltage3;
  data.current1 = pzem1.current();
  data.current2 = pzem2.current();
  data.current3 = pzem3.current();

  data.frequency = pzem1.frequency(); // Same frequency
  // data.frequency2 = pzem2.frequency(); // Same frequency
  // data.frequency3 = pzem3.frequency(); // Same frequency

  data.power1 = pzem1.power();
  data.power2 = pzem2.power();
  data.power3 = pzem3.power();
  data.batteryVoltage = voltage;
  data.temperature =temperature;
  data.totalLoad = pzem1.energy() + pzem2.energy() + pzem3.energy();
  data.percentage =batteryPercentage;

  sendData();

  delay(2000);
}

