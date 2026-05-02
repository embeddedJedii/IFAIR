

 



// #include "pzem.h"
// #include <PZEM004Tv30.h>

// #define NUM_LOADS 3

// const uint8_t coilPins[NUM_LOADS] = {27, 26, 25};

// // Thresholds
// #define TH_HIGH 70
// #define TH_MED  45
// #define TH_LOW  25

// struct Load {
//     uint8_t pin;
//     bool status;
//     float power;
// };

// Load loads[NUM_LOADS];

// PZEM004Tv30 pzem1, pzem2, pzem3;
// PZEM004Tv30* pzems[NUM_LOADS] = {&pzem1, &pzem2, &pzem3};

// int lastBatteryPercentage = 100;

// // ---------------- INIT ----------------
// void initLoads() {
//     for (int i = 0; i < NUM_LOADS; i++) {
//         loads[i].pin = coilPins[i];
//         loads[i].status = true;
//         loads[i].power = 0;

//         pinMode(loads[i].pin, OUTPUT);
//         digitalWrite(loads[i].pin, HIGH);
//     }
// }

// // ---------------- READ POWER ----------------
// void updatePowerReadings() {
//     for (int i = 0; i < NUM_LOADS; i++) {
//         float p = pzems[i]->power();

//         if (isnan(p)) {
//             loads[i].power = 9999; // force OFF priority
//         } else {
//             loads[i].power = p;
//         }
//     }
// }

// // ---------------- SORT BY POWER ----------------
// void sortLoadsByPower() {
//     for (int i = 0; i < NUM_LOADS - 1; i++) {
//         for (int j = i + 1; j < NUM_LOADS; j++) {
//             if (loads[j].power > loads[i].power) {
//                 Load temp = loads[i];
//                 loads[i] = loads[j];
//                 loads[j] = temp;
//             }
//         }
//     }
// }

// // ---------------- APPLY ----------------
// void applyLoads() {
//     for (int i = 0; i < NUM_LOADS; i++) {
//         digitalWrite(loads[i].pin, loads[i].status ? HIGH : LOW);
//     }
// }

// // ---------------- MAIN LOGIC ----------------
// void manageLoads(int batteryPercentage) {

//     bool isCharging = batteryPercentage > lastBatteryPercentage;

//     Serial.printf("Battery: %d%% | %s\n",
//                   batteryPercentage,
//                   isCharging ? "CHARGING" : "DISCHARGING");

//     // ---------------- DISCHARGING ----------------
//     if (!isCharging) {

//         updatePowerReadings();
//         sortLoadsByPower();

//         // Start with all ON
//         for (int i = 0; i < NUM_LOADS; i++) {
//             loads[i].status = true;
//         }

//         if (batteryPercentage > TH_HIGH) {
//             // All ON

//         } else if (batteryPercentage > TH_MED) {
//             // Turn OFF highest
//             loads[0].status = false;

//         } else if (batteryPercentage > TH_LOW) {
//             // Turn OFF top 2
//             loads[0].status = false;
//             loads[1].status = false;

//         } else {
//             // All OFF
//             for (int i = 0; i < NUM_LOADS; i++) {
//                 loads[i].status = false;
//             }
//         }
//     }

//     // ---------------- CHARGING ----------------
//     else {

//         // Restore loads in fixed order
//         if (batteryPercentage > TH_LOW) {
//             loads[0].status = true;  // Load 1 ON
//         }

//         if (batteryPercentage > TH_MED) {
//             loads[1].status = true;  // Load 2 ON
//         }

//         if (batteryPercentage > TH_HIGH) {
//             loads[2].status = true;  // Load 3 ON
//         }
//     }

//     applyLoads();
//     lastBatteryPercentage = batteryPercentage;
// }