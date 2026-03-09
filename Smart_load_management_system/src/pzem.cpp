
#include "pzem.h"
#include <PZEM004Tv30.h>
#define COIL_1 27
#define COIL_2 26
#define COIL_3 25

//Variable declearations
uint8_t status1 = 1;
uint8_t status2 = 1;
uint8_t status3 = 1;
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

void shutDownPiority(PZEM004Tv30 &pzem1, PZEM004Tv30 &pzem2, PZEM004Tv30 &pzem3, int batteryPercentage)
{
    float power1 = pzem1.power();
    float power2 = pzem2.power();
    float power3 = pzem3.power();

    if(batteryPercentage <= 70 && batteryPercentage > 45) {
        if (power1 > power2 && power1 > power3) {
        Serial.println("PZEM 1 has the highest power consumption.");
        //disconnect the load connected to the pzem with power1
        digitalWrite(COIL_1, LOW); // Assuming LOW turns off the load
        digitalWrite(COIL_2, HIGH);
        digitalWrite(COIL_3, HIGH);
        status1 = 0; // Assuming 0 means off
    } else if (power2 > power1 && power2 > power3) {
        Serial.println("PZEM 2 has the highest power consumption.");
        digitalWrite(COIL_2, LOW); // Assuming LOW turns off the load
        digitalWrite(COIL_1, HIGH);
        digitalWrite(COIL_3, HIGH);
        status2 = 0; // Assuming 0 means off
    } else if (power3 > power1 && power3 > power2) {
        Serial.println("PZEM 3 has the highest power consumption.");
        digitalWrite(COIL_3, LOW); // Assuming LOW turns off the load
        digitalWrite(COIL_1, HIGH);
        digitalWrite(COIL_2, HIGH);
        status3 = 0; // Assuming 0 means off
    } else {
        Serial.println("Two or more PZEMs have the same highest power consumption.");
    }
    }
    
    else if(batteryPercentage<= 45 && batteryPercentage > 25){
     if(!status1){
        if(power2 > power3){
        digitalWrite(COIL_2, LOW); // Assuming LOW turns off the load
        digitalWrite(COIL_3, HIGH);
        status2 = 0;
     }else{
        digitalWrite(COIL_3, LOW); // Assuming LOW turns off the load
        digitalWrite(COIL_2, HIGH);
        status3 = 0;
     }
     }else if(!status2){
         if(power1 > power3){
        digitalWrite(COIL_1, LOW); // Assuming LOW turns off the load
        digitalWrite(COIL_3, HIGH);
        status1 = 0;
     }else{
        digitalWrite(COIL_3, LOW); // Assuming LOW turns off the load
        digitalWrite(COIL_1, HIGH);
        status3 = 0;
     }
     }else if(!status3){

      if(power2 > power1){
        digitalWrite(COIL_2, LOW); // Assuming LOW turns off the load
        digitalWrite(COIL_1, HIGH);
        status2 = 0;
     }else{
        digitalWrite(COIL_1, LOW); // Assuming LOW turns off the load
        digitalWrite(COIL_2, HIGH);
        status1 = 0;
     }
     }
   
    }

   else{
        //turn off all loads
        digitalWrite(COIL_1, LOW);
        digitalWrite(COIL_2, LOW);
        digitalWrite(COIL_3, LOW);
        status1 = status2= status3 = 0;
    }
}
void turnOnPiority(PZEM004Tv30 &pzem1, PZEM004Tv30 &pzem2, PZEM004Tv30 &pzem3, int batteryPercentage){

}