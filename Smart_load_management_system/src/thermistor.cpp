#include <Arduino.h>

#define THERMISTOR_PIN 32

const float SERIES_RESISTOR = 10000.0;   // 10k resistor
const float NOMINAL_RESISTANCE = 10000.0; // Thermistor resistance at 25°C
const float NOMINAL_TEMPERATURE = 25.0;  // 25°C
const float BETA_COEFFICIENT = 3950;     // Common Beta value
const float ADC_MAX = 4095.0;


//Thermistor value is 10k, hence the voltage divider resistor will be 10k ohms as well
float tempData(){

  // int adcValue = analogRead(THERMISTOR_PIN);

  // // Convert ADC value to resistance
  // float voltage = adcValue / ADC_MAX;
  // float resistance = SERIES_RESISTOR * (1.0 / voltage - 1.0);

  // // Apply Beta equation
  // float steinhart;
  // steinhart = resistance / NOMINAL_RESISTANCE;
  // steinhart = log(steinhart);
  // steinhart /= BETA_COEFFICIENT;
  // steinhart += 1.0 / (NOMINAL_TEMPERATURE + 273.15);
  // steinhart = 1.0 / steinhart;
  // steinhart -= 273.15;

  // Serial.print("Temperature: ");
  // Serial.print(steinhart);
  // Serial.println(" °C");
    int adcValue = analogRead(THERMISTOR_PIN);

  float voltage = adcValue * (3.3 / 4095.0);

  // Correct formula for your configuration
  float resistance = SERIES_RESISTOR * (voltage / (3.3 - voltage));

  // Beta equation
  float tempK = 1.0 / (
    (1.0 / (NOMINAL_TEMPERATURE + 273.15)) +
    (1.0 / BETA_COEFFICIENT) * log(resistance / NOMINAL_RESISTANCE)
  );

  float tempC = tempK - 273.15;

  Serial.print("Temp: ");
  Serial.print(tempC);
  Serial.println(" °C");
  return tempC;
}


// #define SERIES_RESISTOR 10000
// #define NOMINAL_RESISTANCE 10000
// #define NOMINAL_TEMPERATURE 25
// #define BETA_COEFFICIENT 3950

// void setup() {
//   Serial.begin(115200);
// }

// void loop() {
//   int adcValue = analogRead(THERMISTOR_PIN);

//   float voltage = adcValue * (3.3 / 4095.0);

//   // Correct formula for your configuration
//   float resistance = SERIES_RESISTOR * (voltage / (3.3 - voltage));

//   // Beta equation
//   float tempK = 1.0 / (
//     (1.0 / (NOMINAL_TEMPERATURE + 273.15)) +
//     (1.0 / BETA_COEFFICIENT) * log(resistance / NOMINAL_RESISTANCE)
//   );

//   float tempC = tempK - 273.15;

//   Serial.print("Temp: ");
//   Serial.print(tempC);
//   Serial.println(" °C");

//   delay(1000);
// }