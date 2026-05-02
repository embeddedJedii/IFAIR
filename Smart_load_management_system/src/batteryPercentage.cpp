#include <Arduino.h>
#define BATTERY_PIN 35

float R1 = 56000.0; // 56k
float R2 = 3300.0;  // 3.3k

float adcMax = 4095.0; // ESP32 12-bit ADC
float vRef = 3.3;

float filteredVoltage = -1;  // use -1 to detect first run

float readVoltage() {
    const int samples = 30;
    uint32_t sum = 0;

    // take multiple samples
    for (int i = 0; i < samples; i++) {
        sum += analogRead(BATTERY_PIN);
        delayMicroseconds(200);  // small delay improves stability
    }

    float adc = sum / (float)samples;

    // convert to voltage
    float vOut = (adc / adcMax) * vRef;
    float vin = vOut * (R1 + R2) / R2;

    // initialize filter properly
    if (filteredVoltage < 0) {
        filteredVoltage = vin;  // first reading = real value
    } else {
        // exponential smoothing
        float alpha = 0.2;  // increase for faster response (0.1–0.3)
        filteredVoltage = (alpha * vin) + ((1 - alpha) * filteredVoltage);
    }
   
    return filteredVoltage +2.57;
}

float getBatteryPercentage(float voltage) {
    float minV, maxV;

    // Detect battery system
    if(voltage > 33) { // > 35V → 48V battery
        minV = 42.0; 
        maxV = 58.8;
    } else {           // 24V battery
        minV = 21.0;
        maxV = 29.1;
    }

    float percentage = ((voltage - minV) / (maxV - minV)) * 100;
    percentage = constrain(percentage, 0, 100);
    Serial.printf("The percentage is %.2f", percentage);
    return percentage;
}
