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
  u_int8_t percentage;
};


SensorData data;
void sendData()
{
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write((byte *)&data, sizeof(data));
  Wire.endTransmission();

  Serial.println("Data Sent");
}

