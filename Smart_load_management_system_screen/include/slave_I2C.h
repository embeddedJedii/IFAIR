#ifndef SLAVE_I2C_H
#define SLAVE_I2C_H

#include <Arduino.h>
#include <Wire.h>

/**
 * I2C slave address used by the ESP32/Arduino board.
 */
#define SLAVE_ADDR 0x08

/**
 * Data packet received from the master.  The layout must match the
 * format used by the master device so that Wire.readBytes can
 * deserialize it directly into this structure.
 */
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
};

/*
 * Global instance that holds the most recently received packet.
 * Defined in slave_I2C.cpp so other modules can reference it.
 */
extern SensorData receivedData;

/*
 * Convenience wrappers around the sketch-style functions in
 * slave_I2C.cpp.  These may be called from the main application
 * (e.g. in `setup()` and `loop()`) to initialise and poll the I2C
 * subsystem.  The raw handlers are also exposed in case the user
 * wants to attach them directly to Wire.
 */

void receiveEvent(int bytes);

#endif // SLAVE_I2C_H
