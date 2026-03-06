
#include "pzem.h"
#include <PZEM004Tv30.h>
// void readPzem(PZEM004Tv30 &pzem, String name) {
//   float voltage = pzem.voltage();
//   float current = pzem.current();
//   float power = pzem.power();
//   float energy = pzem.energy();
//   uint16_t frequency = pzem.frequency();
// //   uint8_t pf = pzem.pf();

//   Serial.printf("Voltage: %.2f V\n", voltage);
//   Serial.printf("Current: %.2f A\n", current);
//   Serial.printf("Power: %.2f W\n", power);
//   Serial.printf("Energy: %.2f Wh\n", energy);
//   Serial.printf("Frequency: %d Hz\n", frequency);
// //   Serial.printf("Power Factor: %d%%\n", pf);
// }

void readPZEM(PZEM004Tv30 &pzem, String name)
{
    float voltage = pzem.voltage();
    float current = pzem.current();
    float power = pzem.power();
    float energy = pzem.energy();
    float frequency = pzem.frequency();
   //loat pf = pzem.pf();

    Serial.println(name);
    Serial.printf("Voltage: %.2f V\n", voltage);
    Serial.printf("Current: %.2f A\n", current);
    Serial.printf("Power: %.2f W\n", power);
    Serial.printf("Energy: %.2f Wh\n", energy);
    Serial.printf("Frequency: %.2f Hz\n", frequency);
}
