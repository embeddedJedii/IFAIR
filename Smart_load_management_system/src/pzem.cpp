
#include "pzem.h"
#include <PZEM004Tv30.h>
#include <batteryPercentage.h>
const uint8_t COIL_1 = 27;
const uint8_t COIL_2 = 26;
const uint8_t COIL_3 = 25;

//Variable declearations
uint8_t status1 = 1;
uint8_t status2 = 1;
uint8_t status3 = 1;
uint8_t systemStatus = 1;
uint8_t percentage = getBatteryPercentage(readVoltage() + 2.57);
uint8_t lastPercentage = 100;
bool status_75 = false; // Flag to track if battery percentage has dropped below 75% at least once
bool status_45 = false; // Flag to track if battery percentage has dropped below 45% at least once
bool chargeDone_75 = false;
bool chargeDone_75_45 = false;
bool chargeDone_45_25 = false;
bool chargeDone_25 = false;
//to reset the PZEM energy, use pzem.resetEnergy(); 

//If battery percentage is increasing, this means turn on piority according to the specified order.


//If battery percentage is decreasing, turn off load, i.e shed load according to the specified logic.


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

void shutDownPiority(PZEM004Tv30 &pzem1, PZEM004Tv30 &pzem2, PZEM004Tv30 &pzem3, float batteryPercentage)
{
    Serial.printf("Battery Percentage: %.2f%%\n", batteryPercentage);
  int delta = (int)batteryPercentage - lastPercentage;
bool isCharging    = delta >=1;
bool isDischarging = delta <= -1;
    float power1 = pzem1.power(); 
    float power2 = pzem2.power();
    float power3 = pzem3.power(); 
 

    if(isnan(power1)) power1 = 0;
    if(isnan(power2)) power2 = 0;
    if(isnan(power3)) power3 = 0;
   
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//This block of code works for when the PZEM is dishcarging, i.e when the battery voltage is reducing
//it will shed load according to the specified logic. It will run only once when the battery percentage drops below the specified thresholds to avoid rapid on/off switching of loads. 
if(isDischarging){

        // -------- ABOVE 70% --------
        if(batteryPercentage > 70 && batteryPercentage <= 100) {

            digitalWrite(COIL_1, HIGH);
            digitalWrite(COIL_2, HIGH);
            digitalWrite(COIL_3, HIGH);

            status1 = status2 = status3 = 1;
            systemStatus = 1;

            Serial.println("Battery > 70% → All loads ON");

            status_75 = false; // reset

        } 

        // -------- 70% → 45% --------
        else if(batteryPercentage <= 70 && batteryPercentage > 45) {

            if (!status_75) { // ✅ RUN ONLY ONCE

                // Ignore already OFF loads
                if (!status1) power1 = -1;
                if (!status2) power2 = -1;
                if (!status3) power3 = -1;

                if (power1 > power2 && power1 > power3) {
                    Serial.println("PZEM 1 has the highest power consumption.");
                    digitalWrite(COIL_1, LOW);
                    // digitalWrite(COIL_2, HIGH);  0 
                    // digitalWrite(COIL_3, HIGH);
                    status1 = 0;

                } else if (power2 > power1 && power2 > power3) {
                    Serial.println("PZEM 2 has the highest power consumption.");
                    digitalWrite(COIL_2, LOW);
                    // digitalWrite(COIL_1, HIGH);
                    // digitalWrite(COIL_3, HIGH);
                    status2 = 0;

                } else if (power3 > power1 && power3 > power2) {
                    Serial.println("PZEM 3 has the highest power consumption.");
                    digitalWrite(COIL_3, LOW);
                    // digitalWrite(COIL_1, HIGH);
                    // digitalWrite(COIL_2, HIGH);
                    status3 = 0;
                }

                updateSystemStatus();
                status_75 = true; // 
            }
        }// -------- 45% → 25% --------
else if (batteryPercentage <= 45 && batteryPercentage > 25) {

    if (!status_45) { // ✅ run only once

        // Ignore OFF loads
        if (!status1) power1 = -1;
        if (!status2) power2 = -1;
        if (!status3) power3 = -1;

        // Count active loads
        int activeCount = status1 + status2 + status3;

        if (activeCount == 2) {

            // Compare ONLY the 2 active ones
            if (status1 && status2) {

                if (power1 > power2) {
                    Serial.println("Stage 45%: Turning OFF Load 1");
                    digitalWrite(COIL_1, LOW);
                    status1 = 0;
                } else {
                    Serial.println("Stage 45%: Turning OFF Load 2");
                    digitalWrite(COIL_2, LOW);
                    status2 = 0;
                }

            } else if (status1 && status3) {

                if (power1 > power3) {
                    Serial.println("Stage 45%: Turning OFF Load 1");
                    digitalWrite(COIL_1, LOW);
                    status1 = 0;
                } else {
                    Serial.println("Stage 45%: Turning OFF Load 3");
                    digitalWrite(COIL_3, LOW);
                    status3 = 0;
                }

            } else if (status2 && status3) {

                if (power2 > power3) {
                    Serial.println("Stage 45%: Turning OFF Load 2");
                    digitalWrite(COIL_2, LOW);
                    status2 = 0;
                } else {
                    Serial.println("Stage 45%: Turning OFF Load 3");
                    digitalWrite(COIL_3, LOW);
                    status3 = 0;
                }
            }

            updateSystemStatus();
        }

        status_45 = true; //
    }
}

        // -------- BELOW 45% (fallback safety) --------
        else {
            Serial.println("Battery < 45% → All loads OFF");

            digitalWrite(COIL_1, LOW);
            digitalWrite(COIL_2, LOW);
            digitalWrite(COIL_3, LOW);

            status1 = status2 = status3 = systemStatus = 0;
        }
    } 
// ---------------- CHARGING ----------------
else if(isCharging){

    Serial.println("Battery is charging. Smart energy-based restore...");

    float energy1 = (pzem1.energy() *1000) + 0.1;
    float energy2 = (pzem2.energy() *1000) + 0.2;
    float energy3 = (pzem3.energy() *1000) + 0.3;

    if(isnan(energy1)) energy1 = 0;
    if(isnan(energy2)) energy2 = 0;
    if(isnan(energy3)) energy3 = 0;

    // -------- ABOVE 75% --------
    if(batteryPercentage > 75) {

        if(!chargeDone_75){

            Serial.println("Battery > 75% → All loads ON");

            digitalWrite(COIL_1, HIGH);
            digitalWrite(COIL_2, HIGH);
            digitalWrite(COIL_3, HIGH);

            status1 = status2 = status3 = 1;
            systemStatus = 1;

            chargeDone_75 = true;

            // reset others
            chargeDone_75_45 = false;
            chargeDone_45_25 = false;
            chargeDone_25 = false;
        }
    }

    // -------- 75% → 45% --------
    else if(batteryPercentage <= 75 && batteryPercentage > 45) {

        if(!chargeDone_75_45){

            Serial.println("Battery 75% → 45% → Turning ON 2 lowest energy loads");

            int first = 0, second;
            float e[3] = {energy1, energy2, energy3};

            for(int i = 1; i < 3; i++){
                if(e[i] < e[first]) first = i;
            }

            second = (first == 0) ? 1 : 0;
            for(int i = 0; i < 3; i++){
                if(i != first && e[i] < e[second]) second = i;
            }

            digitalWrite(COIL_1, LOW);
            digitalWrite(COIL_2, LOW);
            digitalWrite(COIL_3, LOW);

            status1 = status2 = status3 = 0;

            if(first == 0 || second == 0){
                digitalWrite(COIL_1, HIGH);
                status1 = 1;
            }
            if(first == 1 || second == 1){
                digitalWrite(COIL_2, HIGH);
                status2 = 1;
            }
            if(first == 2 || second == 2){
                digitalWrite(COIL_3, HIGH);
                status3 = 1;
            }

            updateSystemStatus();

            chargeDone_75_45 = true;

            // reset others
            chargeDone_75 = false;
            chargeDone_45_25 = false;
            chargeDone_25 = false;
        }
    }

    // -------- 45% → 25% --------
    else if(batteryPercentage <= 45 && batteryPercentage > 25) {

        if(!chargeDone_45_25){

            Serial.println("Battery 45% → 25% → Turning ON lowest energy load only");

            int lowest = 0;
            float e[3] = {energy1, energy2, energy3};

            for(int i = 1; i < 3; i++){
                if(e[i] < e[lowest]) lowest = i;
            }

            digitalWrite(COIL_1, LOW);
            digitalWrite(COIL_2, LOW);
            digitalWrite(COIL_3, LOW);

            status1 = status2 = status3 = 0;

            if(lowest == 0){
                digitalWrite(COIL_1, HIGH);
                status1 = 1;
            }
            else if(lowest == 1){
                digitalWrite(COIL_2, HIGH);
                status2 = 1;
            }
            else{
                digitalWrite(COIL_3, HIGH);
                status3 = 1;
            }

            updateSystemStatus();

            chargeDone_45_25 = true;

            // reset others
            chargeDone_75 = false;
            chargeDone_75_45 = false;
            chargeDone_25 = false;
        }
    }

    // -------- BELOW 25% --------
    else {

        if(!chargeDone_25){

            Serial.println("Battery < 25% → All loads OFF");

            digitalWrite(COIL_1, LOW);
            digitalWrite(COIL_2, LOW);
            digitalWrite(COIL_3, LOW);

            status1 = status2 = status3 = systemStatus = 0;

            chargeDone_25 = true;

            // reset others
            chargeDone_75 = false;
            chargeDone_75_45 = false;
            chargeDone_45_25 = false;
        }
    }
}
 
    lastPercentage = batteryPercentage;
}  
