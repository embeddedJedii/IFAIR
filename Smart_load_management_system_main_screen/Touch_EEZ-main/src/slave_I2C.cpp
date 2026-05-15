#include <Arduino.h>
#include <Wire.h>
// #define SLAVE_ADDR 0x08

// struct SensorData
// {
//   float energy1;
//   float energy2;
//   float energy3;

//   float voltage1;
//   float voltage2;
//   float voltage3;

//   float current1;
//   float current2;
//   float current3;

//   float frequency;

//   float power1;
//   float power2;
//   float power3;

//   float batteryVoltage;
//   float temperature;
//   float totalLoad;
//   u_int8_t percentage;
// };

// SensorData receivedData;



// void receiveEvent(int bytes)
// {
//   if (bytes == sizeof(receivedData))
//   {
//     Wire.readBytes((byte *)&receivedData, sizeof(receivedData));

//     Serial.println("------ RECEIVED DATA ------");

//     Serial.println(receivedData.energy1);
//     Serial.println(receivedData.energy2);
//     Serial.println(receivedData.energy3);

//     Serial.println(receivedData.voltage1);
//     Serial.println(receivedData.voltage2);
//     Serial.println(receivedData.voltage3);

//     Serial.println(receivedData.current1);
//     Serial.println(receivedData.current2);
//     Serial.println(receivedData.current3);

//     Serial.println(receivedData.frequency);

//     Serial.println(receivedData.power1);
//     Serial.println(receivedData.power2);
//     Serial.println(receivedData.power3);

//     Serial.println(receivedData.batteryVoltage);
//     Serial.println(receivedData.temperature);
//     Serial.println(receivedData.totalLoad);
//     Serial.println(receivedData.percentage);
//     Serial.println("---------------------------");
//   }
// }

#define I2C_SDA    17
#define I2C_SCL    18
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
  uint8_t percentage;
};

SensorData receivedData;
volatile bool dataReady = false;

void receiveEvent(int bytes)
{
  if (bytes == sizeof(SensorData))
  {
    // ✅ Use Wire1 NOT Wire — and no Serial inside ISR
    Wire1.readBytes((byte *)&receivedData, sizeof(SensorData));
    dataReady = true;  // ✅ Set flag, handle outside ISR
  }
  else
  {
    // Flush bad data
    while (Wire1.available()) Wire1.read();
  }
}

void requestEvent()
{
  Wire1.write("ACK");
}

void printData()
{
  Serial.println("------ RECEIVED DATA ------");
  Serial.println(receivedData.energy1);
  Serial.println(receivedData.energy2);
  Serial.println(receivedData.energy3);

  Serial.println(receivedData.voltage1);
  Serial.println(receivedData.voltage2);
  Serial.println(receivedData.voltage3);

  Serial.println(receivedData.current1);
  Serial.println(receivedData.current2);
  Serial.println(receivedData.current3);

  Serial.println(receivedData.frequency);

  Serial.println(receivedData.power1);
  Serial.println(receivedData.power2);
  Serial.println(receivedData.power3);

  Serial.println(receivedData.batteryVoltage);
  Serial.println(receivedData.temperature);
  Serial.println(receivedData.totalLoad);
  Serial.println(receivedData.percentage);
  Serial.println("---------------------------");
}
