#include <Arduino.h>
#include <Wire.h>
#define SLAVE_ADDR 0x08

struct SensorData
{
  float energy1;
  float energy2;
  float energy3;

  float voltage1;
  float voltage2;
  float voltage3;

  float current1;
  float current2;
  float current3;

  float frequency;

  float power1;
  float power2;
  float power3;

  float batteryVoltage;
  float temperature;
  float totalLoad;
  float percentage;
};

SensorData data;
void sendData()
{
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write((byte *)&data, sizeof(data));
  Wire.endTransmission();

  Serial.println("Data Sent");
}
// void setup()
// {
//   Serial.begin(115200);

//   Wire.begin(); // Master mode
// }

// void loop()
// {
//   // Example values (replace with real sensor readings)
//   data.energy1 = 10.5;
//   data.energy2 = 11.2;
//   data.energy3 = 12.1;

//   data.voltage1 = 220.5;
//   data.voltage2 = 221.1;
//   data.voltage3 = 219.8;

//   data.current1 = 5.2;
//   data.current2 = 4.8;
//   data.current3 = 6.1;

//   data.frequency = 50.0;

//   data.power1 = 1150;
//   data.power2 = 1100;
//   data.power3 = 1200;

//   data.batteryVoltage = 27.5;
//   data.temperature = 32.4;
//   data.totalLoad = 3450;

//   sendData();

// }

