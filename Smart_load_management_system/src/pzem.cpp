
#include "pzem.h"
#include <PZEM004Tv30.h>
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

void HighestPower(PZEM004Tv30 &pzem1, PZEM004Tv30 &pzem2, PZEM004Tv30 &pzem3, int batteryPercentage)
{
    float power1 = pzem1.power();
    float power2 = pzem2.power();
    float power3 = pzem3.power();

    if(batteryPercentage <= 70 && batteryPercentage > 45) {
        if (power1 > power2 && power1 > power3) {
        Serial.println("PZEM 1 has the highest power consumption.");
        //disconnect the load connected to the pzem with power1
    } else if (power2 > power1 && power2 > power3) {
        Serial.println("PZEM 2 has the highest power consumption.");
    } else if (power3 > power1 && power3 > power2) {
        Serial.println("PZEM 3 has the highest power consumption.");
    } else {
        Serial.println("Two or more PZEMs have the same highest power consumption.");
    }
    }
    
    if(batteryPercentage<= 45 && batteryPercentage > 20){
        //turn off the load with the next highest power
    }

    if(batteryPercentage <= 20){
        //turn off all loads
    }
}