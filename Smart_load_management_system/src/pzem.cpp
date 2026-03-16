
#include "pzem.h"
#include <PZEM004Tv30.h>
const uint8_t COIL_1 = 27;
const uint8_t COIL_2 = 26;
const uint8_t COIL_3 = 25;

//Variable declearations
uint8_t status1 = 1;
uint8_t status2 = 1;
uint8_t status3 = 1;
uint8_t systemStatus = 1;
void updateSystemStatus()
{
    systemStatus = status1 || status2 || status3;
}
void readPZEM(PZEM004Tv30 &pzem, String name)
{
    float voltage = pzem.voltage();
    float current = pzem.current();
    float power = pzem.power();
    float energy = pzem.energy();
    float frequency = pzem.frequency();
    uint8_t address = pzem.readAddress();
   //loat pf = pzem.pf();
    Serial.printf("The address is 0x%02X\n", address);
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
    if(isnan(power1)) power1 = 0;
    if(isnan(power2)) power2 = 0;
    if(isnan(power3)) power3 = 0;

    if(batteryPercentage <= 70 && batteryPercentage > 45) {
        if (power1 > power2 && power1 > power3) {
        Serial.println("PZEM 1 has the highest power consumption.");
        //disconnect the load connected to the pzem with power1
        digitalWrite(COIL_1, LOW); // Assuming LOW turns off the load
        digitalWrite(COIL_2, HIGH);
        digitalWrite(COIL_3, HIGH);
        status1 = 0; // Assuming 0 means off
        updateSystemStatus();
    } else if (power2 > power1 && power2 > power3) {
        Serial.println("PZEM 2 has the highest power consumption.");
        digitalWrite(COIL_2, LOW); // Assuming LOW turns off the load
        digitalWrite(COIL_1, HIGH);
        digitalWrite(COIL_3, HIGH);
        status2 = 0; // Assuming 0 means off
        updateSystemStatus();
    } else if (power3 > power1 && power3 > power2) {
        Serial.println("PZEM 3 has the highest power consumption.");
        digitalWrite(COIL_3, LOW); // Assuming LOW turns off the load
        digitalWrite(COIL_1, HIGH);
        digitalWrite(COIL_2, HIGH);
        status3 = 0; // Assuming 0 means off
        updateSystemStatus();
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
        updateSystemStatus();
     }else{
        digitalWrite(COIL_3, LOW); // Assuming LOW turns off the load
        digitalWrite(COIL_2, HIGH);
        status3 = 0;
        updateSystemStatus();
     }
     }else if(!status2){
         if(power1 > power3){
        digitalWrite(COIL_1, LOW); // Assuming LOW turns off the load
        digitalWrite(COIL_3, HIGH);
        status1 = 0;
        updateSystemStatus();
     }else{
        digitalWrite(COIL_3, LOW); // Assuming LOW turns off the load
        digitalWrite(COIL_1, HIGH);
        status3 = 0;
        updateSystemStatus();
     }
     }else if(!status3){

      if(power2 > power1){
        digitalWrite(COIL_2, LOW); // Assuming LOW turns off the load
        digitalWrite(COIL_1, HIGH);
        status2 = 0;
        updateSystemStatus();
     }else{
        digitalWrite(COIL_1, LOW); // Assuming LOW turns off the load
        digitalWrite(COIL_2, HIGH);
        status1 = 0;
        updateSystemStatus();
     }
     }
   
    }

   else{
        //turn off all loads
        digitalWrite(COIL_1, LOW);
        digitalWrite(COIL_2, LOW);
        digitalWrite(COIL_3, LOW);
        status1 = status2= status3 = systemStatus = 0; // Assuming 0 means off
    }
}
void turnOnPiority(int batteryPercentage){
if(!systemStatus){
    // This means that all the loads are currently off
    if(batteryPercentage >25 && batteryPercentage <=45){
          //This means that all the loads are currently off
          digitalWrite(COIL_1, HIGH);
          status1 = 1; //TURN ON THE LOAD ATTACHED TO COIL 1
          updateSystemStatus();  
    }
    
}else {
    // This means that atleast one of the outputs is currently on
    //i.e the battery percentage is greater than 45 percent
    if(batteryPercentage > 45 && batteryPercentage <= 70){
        if(!status1){
            digitalWrite(COIL_1, HIGH);
            status1 = 1; //TURN ON THE LOAD ATTACHED TO COIL 1
            updateSystemStatus();
        }
        else if(!status2){
            digitalWrite(COIL_2, HIGH);
            status2 = 1; //TURN ON THE LOAD ATTACHED TO COIL 2 
            updateSystemStatus();
        }
    }else if(batteryPercentage > 70){
        if(!status1 || !status2 || !status3){
       digitalWrite(COIL_1, HIGH);
       digitalWrite(COIL_2, HIGH);
       digitalWrite(COIL_3, HIGH);
       status1 = status2=status3=systemStatus = 1; 
    //TURN ON THE LOAD ATTACHED TO COIL 1, COIL 2 AND COIL 3
        }
   
    } 
}
}