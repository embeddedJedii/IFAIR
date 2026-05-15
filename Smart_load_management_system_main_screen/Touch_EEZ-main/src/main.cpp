#include <Arduino.h>
#include <esp32_smartdisplay.h>
#include "ui/ui.h"
#include "slave_I2C.h"
#include "ui/screens.h"
#include "ui/actions.h"
unsigned long lv_last_tick = 0;
#define I2C_SDA 17
#define I2C_SCL 18
#define SLAVE_ADDR 0x08
void setup()
{
  Serial.begin(115200);

  // Initialize display and UI
  smartdisplay_init();
  ui_init();
    // Wire.begin(SLAVE_ADDR);
    // Wire.onReceive(receiveEvent);
  //  Wire1.begin(SLAVE_ADDR, I2C_SDA, I2C_SCL, 100000);
  // Wire1.onReceive(receiveEvent);
  Wire1.setBufferSize(128);  // sizeof(SensorData) = 65 bytes, 128 is safe
  Wire1.begin(SLAVE_ADDR, I2C_SDA, I2C_SCL, 100000);
  Wire1.onReceive(receiveEvent);
  Wire1.onRequest(requestEvent);
  lv_scr_load(objects.main);
  Serial.println("I am printing over I2C");
  // Initialize LVGL ticker
  lv_last_tick = millis();
}

void loop()
{
  auto const now = millis();
   if (dataReady)
  {
    dataReady = false;
    printData();    // Serial output
    // Debug: Print received values
    Serial.printf("Updating UI - Freq: %.2f, Energy: %.2f, Current: %.2f, Voltage: %.2f, Power: %.2f, TotalLoad: %.2f, BatteryVoltage: %.2f, ACVoltage: %.2f\n", 
                  receivedData.frequency, receivedData.energy1, receivedData.current1, 
                  receivedData.voltage1, receivedData.power1, receivedData.totalLoad, receivedData.batteryVoltage, receivedData.voltage1);
    //                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         Update UI labels with received data using formatted strings
    char buf[32];
    sprintf(buf, "%.2f", receivedData.frequency);
    lv_label_set_text(objects.freq_value1, buf);
    sprintf(buf, "%.2f", receivedData.energy1);
    lv_label_set_text(objects.energy_value1, buf);
    sprintf(buf, "%.2f", receivedData.current1);
    lv_label_set_text(objects.current_value1, buf);
    sprintf(buf, "%.2f", receivedData.voltage1);
    lv_label_set_text(objects.voltage_value1, buf);
    sprintf(buf, "%.2f", receivedData.power1);
    lv_label_set_text(objects.power_value1, buf);
    sprintf(buf, "%.2f", receivedData.totalLoad);
    lv_label_set_text(objects.load_consumption_value, buf);
    sprintf(buf, "%.2f", receivedData.batteryVoltage);
    lv_label_set_text(objects.battery_voltage_value, buf);
    sprintf(buf, "%.2f", receivedData.voltage1);
    lv_label_set_text(objects.ac_voltage, buf);
  }
  // Update LVGL tick
  lv_tick_inc(now - lv_last_tick);
  lv_last_tick = now;

  // Handle LVGL and EEZ UI
  lv_timer_handler();
  ui_tick();
}