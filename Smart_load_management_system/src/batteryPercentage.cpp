#include <Arduino.h>
#define BATTERY_PIN 35

float R1 = 56000.0; // 56k
float R2 = 3300.0;  // 3.3k

float adcMax = 4095.0; // ESP32 12-bit ADC
float vRef = 3.3;

float readVoltage() {
    int adc = analogRead(BATTERY_PIN);
    Serial.printf("The ADC value is %d", adc);
    float vOut = (adc / adcMax) * vRef;
    float vin = vOut * (R1 + R2) / R2; // actual battery voltage
    return vin;
} 

float getBatteryPercentage(float voltage) {
    float minV, maxV;

    // Detect battery system
    if(voltage > 30) { // > 35V → 48V battery
        minV = 42.0; 
        maxV = 58.8;
    } else {           // 24V battery
        minV = 21.0;
        maxV = 29.4;
    }

    float percentage = ((voltage - minV) / (maxV - minV)) * 100;
    percentage = constrain(percentage, 0, 100);
    Serial.printf("The percentage is %.2f", percentage);
    return percentage;
}


// void loop() {
//     float voltage = readVoltage() + 2.77;
//     float percent = getBatteryPercentage(voltage);

//     if(voltage > 30) Serial.println("48V Battery Detected");
//     else Serial.println("24V Battery Detected");

//     Serial.print("Voltage: "); Serial.println(voltage);
//     Serial.print("Battery: "); Serial.print(percent); Serial.println("%");
//     Serial.println("----------------------");

//     delay(2000);
// }