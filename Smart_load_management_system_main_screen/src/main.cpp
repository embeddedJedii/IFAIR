#include <Arduino.h>
#include <math.h>
#include <esp32_smartdisplay.h>
#include "ui/ui.h"
#include "slave_I2C.h"
#include "ui/screens.h"
#include "ui/actions.h"
#include "ui/images.h"
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
                  receivedData.frequency1, receivedData.energy1, receivedData.current1, 
                  receivedData.voltage1, receivedData.power1, receivedData.totalLoad, receivedData.batteryVoltage, receivedData.voltage1);
    //            
if (isnan(receivedData.frequency1)) {
    receivedData.frequency1 = 0.0;
}
if (isnan(receivedData.energy1)) {
    receivedData.energy1 = 0.0;
}
if (isnan(receivedData.current1)) {
    receivedData.current1 = 0.0;
}
if (isnan(receivedData.voltage1)) {
    receivedData.voltage1 = 0.0;
}
if (isnan(receivedData.power1)) {
    receivedData.power1 = 0.0;
}
if (isnan(receivedData.totalLoad)) {
    receivedData.totalLoad = 0.0;
}
if (isnan(receivedData.batteryVoltage)) {
    receivedData.batteryVoltage = 0.0;
}
if (isnan(receivedData.voltage2)) {
    receivedData.voltage2 = 0.0;
}
if (isnan(receivedData.energy2)) {
    receivedData.energy2 = 0.0;
}
if (isnan(receivedData.current2)) {
    receivedData.current2 = 0.0;
}
if (isnan(receivedData.voltage2)) {
    receivedData.voltage2 = 0.0;
}
if (isnan(receivedData.power2)) {
    receivedData.power2 = 0.0;
}
if (isnan(receivedData.voltage3)) {
    receivedData.voltage3 = 0.0;
}
if (isnan(receivedData.energy3)) {
    receivedData.energy3 = 0.0;
}
if (isnan(receivedData.current3)) {
    receivedData.current3 = 0.0;
}
if (isnan(receivedData.power3)) {
    receivedData.power3 = 0.0;
}
if (isnan(receivedData.percentage)) {
    receivedData.percentage = 0.0;
}
if (isnan(receivedData.temperature)) {
    receivedData.temperature = 0.0;
}
    char buf[64];
    sprintf(buf, "%.2f", receivedData.frequency1);
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
    sprintf(buf, "%.2f", receivedData.voltage2);
    lv_label_set_text(objects.ac_voltage, buf);

    ////////////////////////////////////////////////////////
    sprintf(buf, "%.2f", receivedData.frequency2);
    lv_label_set_text(objects.freq_value2, buf);
    sprintf(buf, "%.2f", receivedData.energy2);
    lv_label_set_text(objects.energy_value2, buf);
    sprintf(buf, "%.2f", receivedData.current2);
    lv_label_set_text(objects.current_value2, buf);
    sprintf(buf, "%.2f", receivedData.voltage2);
    lv_label_set_text(objects.voltage_value2, buf);
    sprintf(buf, "%.2f", receivedData.power2); 
    lv_label_set_text(objects.power_value2, buf); 
   

    sprintf(buf, "%.2f", receivedData.frequency3);
    lv_label_set_text(objects.freq_value3, buf);
    sprintf(buf, "%.2f", receivedData.energy3);
    lv_label_set_text(objects.energy_value3, buf);
    sprintf(buf, "%.2f", receivedData.current3);
    lv_label_set_text(objects.current_value3, buf);
    sprintf(buf, "%.2f", receivedData.voltage3);
    lv_label_set_text(objects.voltage_value3, buf);
    sprintf(buf, "%.2f", receivedData.power3); 
    lv_label_set_text(objects.power_value3, buf);
    sprintf(buf, "%d%%", (int)receivedData.percentage); 
    lv_label_set_text(objects.battery_percent, buf); 
    sprintf(buf, "%d", (int)receivedData.temperature); 
    lv_label_set_text(objects.temp_value, buf); 
    if (receivedData.percentage >= 80) {
        lv_image_set_src(objects.full_battery, &img_full_batt);
    } else if(receivedData.percentage >= 50 && receivedData.percentage < 80) {
        lv_image_set_src(objects.full_battery, &img_half_battery);
    } else if(receivedData.percentage < 50 && receivedData.percentage >= 35) {
        lv_image_set_src(objects.full_battery, &img_low_battery_resize);
    }else {
        lv_image_set_src(objects.full_battery, &img_battery_dead);
    }
    lv_obj_clear_flag(objects.full_battery, LV_OBJ_FLAG_HIDDEN);

  }

  if(receivedData.current1 > 0.01) {
     lv_image_set_src(objects.green_power_button, &img_power_button_resize);
  } else {
    lv_image_set_src(objects.green_power_button, &img_red_power_button);
  }
  if(receivedData.current2 > 0.01) {
     lv_image_set_src(objects.red_power_button, &img_power_button_resize);
  } else {
    lv_image_set_src(objects.red_power_button, &img_red_power_button);
  }
   if(receivedData.current3 > 0.01) {
     lv_image_set_src(objects.green_power_button_2_, &img_power_button_resize);
  } else {
    lv_image_set_src(objects.green_power_button_2_, &img_red_power_button);
  }
  // Update LVGL tick
  lv_tick_inc(now - lv_last_tick);
  lv_last_tick = now;

  // Handle LVGL and EEZ UI
  lv_timer_handler();
  ui_tick();
}