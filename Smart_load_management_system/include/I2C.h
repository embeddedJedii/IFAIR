#ifndef I2C_H
#define I2C_H

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

extern SensorData data;

void sendData();

#endif
