#include <Arduino.h>
#include <SPI.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include "slave_I2C.h"
#include "ui/ui.h"
#include "ui/images.h"
/* ================= TOUCH PINS ================= */
#define XPT2046_IRQ   36
#define XPT2046_MOSI  32
#define XPT2046_MISO  39
#define XPT2046_CLK   25
#define XPT2046_CS    33

/* ================= LCD ================= */
#define LCD_BACKLIGHT_PIN 21
static const uint16_t screenWidth  = 800;
static const uint16_t screenHeight = 480;
#define LED_PIN 27
/* ================= LVGL BUFFER ================= */
static lv_color_t buf[screenWidth * 10];

/* ================= OBJECTS ================= */
TFT_eSPI tft;
XPT2046_Touchscreen touch(XPT2046_CS, XPT2046_IRQ);
/* ================================================= */
/*               DISPLAY FLUSH CALLBACK              */
/* ================================================= */
void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *color_p)
{
    uint32_t w = area->x2 - area->x1 + 1;
    uint32_t h = area->y2 - area->y1 + 1;

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)color_p, w * h, true);
    tft.endWrite();

    lv_display_flush_ready(disp);
}

// static void my_horizontal_slider_event (lv_event_t *event){
//     // lv_obj_t *my_horizontal_slider = (lv_obj_t *) lv_event_get_target(event);
//     // lv_obj_t *feels_like_text = (lv_obj_t *) lv_event_get_user_data(event);

//     char buf[8];
//     lv_snprintf(buf, sizeof(buf), "%d", (int) lv_slider_get_value(objects.main_slider));
//     lv_label_set_text(objects.label_feels_like, buf);
// }

// Callback for changing the switch status

// static void switch_toggle_event(lv_event_t *event){
//     static bool switchState = false;
//     switchState = !switchState;
//     lv_obj_t *switchItem = lv_event_get_target_obj(event);
//     lv_event_code_t code = lv_event_get_code(event);
//     lv_obj_t *switch_widget = (lv_obj_t *)lv_event_get_user_data(event);
//     lv_label_set_text(switch_widget, switchState? "ON":"OFF");
// }
//Setting the callback function for the event listener

// static void my_horizontal_slider_value_changed_event_cb(lv_event_t * e) {
//   lv_obj_t * my_horizontal_slider = (lv_obj_t *)lv_event_get_target(e);            //--> Slider that generated the event.
//   lv_obj_t * my_label_horizontal_slider = (lv_obj_t *)lv_event_get_user_data(e);   //--> Label or other UI elements we want to update (Optional).
  
//   char buf[8];
//   lv_snprintf(buf, sizeof(buf), "%d", (int)lv_slider_get_value(my_horizontal_slider));
//   lv_label_set_text(my_label_horizontal_slider, buf);
// }


/* ================================================= */
/*                 TOUCH READ CALLBACK               */
/* ================================================= */
void my_touch_read(lv_indev_t *indev, lv_indev_data_t *data)
{
    if (!touch.touched()) {
        data->state = LV_INDEV_STATE_RELEASED;
        return;
    }

    TS_Point p = touch.getPoint();

    // Raw calibration values (typical CYD)
    const int X_MIN = 300;
    const int X_MAX = 3800;
    const int Y_MIN = 300;
    const int Y_MAX = 3800;

    // Step 1: swap axes
    int16_t x = map(p.y, Y_MIN, Y_MAX, 0, screenWidth);
    int16_t y = map(p.x, X_MIN, X_MAX, 0, screenHeight);

    // Step 2: invert X only (CYD specific)
    x = screenWidth - x;

    // Clamp
    x = constrain(x, 0, screenWidth - 1);
    y = constrain(y, 0, screenHeight - 1);

    data->point.x = x;
    data->point.y = y;
    data->state   = LV_INDEV_STATE_PRESSED;
}

//________________________________________________________________________________ my_button_test_bar_event_handler()
// Callback that is triggered when "my_button_test_bar" is clicked



//________________________________________________________________________________ my_image_esp32_event_handler()
// Callback that is triggered when "my_image_esp32" is clicked.
// static void my_image_esp32_event_handler(lv_event_t * e) {
//   lv_event_code_t code = lv_event_get_code(e);  //--> Get the event code.
  
//   if (code == LV_EVENT_CLICKED) {
//     lv_label_set_text(objects.my_label_img_sta, "ESP32 image is\nTouched.");
//   }
// }
//________________________________________________________________________________ 



//________________________________________________________________________________ my_image_lvgl_event_handler()
// Callback that is triggered when "my_image_lvgl" is clicked.
// static void my_image_lvgl_event_handler(lv_event_t * e) {
//   lv_event_code_t code = lv_event_get_code(e);  //--> Get the event code.
  
//   if (code == LV_EVENT_CLICKED) {
//     lv_label_set_text(objects.my_label_img_sta, "LVGL image is\nTouched.");
//   }
// }
// //________________________________________________________________________________ 



//________________________________________________________________________________ my_image_eez_event_handler()
// // Callback that is triggered when "my_image_eez" is clicked.
// static void my_image_eez_event_handler(lv_event_t * e) {
//   lv_event_code_t code = lv_event_get_code(e);  //--> Get the event code.
  
//   if (code == LV_EVENT_CLICKED) {
//     lv_label_set_text(objects.my_label_img_sta, "EEZ image is\nTouched.");
//   }
// }
// //________________________________________________________________________________ 



/* ================================================= */
/*                       SETUP                       */
/* ================================================= */
void setup()
{
    Serial.begin(115200);
    Serial.println("LVGL + EEZ + Touch starting");

    /* ---------- BACKLIGHT ---------- */
    pinMode(LCD_BACKLIGHT_PIN, OUTPUT);
    digitalWrite(LCD_BACKLIGHT_PIN, HIGH);
    
     /* ---------- I2C Communication ---------- */
    //Enabling I2C communication within the master and the slave

      Wire.begin(SLAVE_ADDR);
      Wire.onReceive(receiveEvent);

    /* ---------- DISPLAY ---------- */
    tft.init();
    tft.setRotation(2);
    tft.fillScreen(TFT_BLACK);

    /* ---------- TOUCH SPI INIT ---------- */
    SPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
    touch.begin();               // <-- CORRECT
    touch.setRotation(2);        // MUST match display

    /* ---------- LVGL INIT ---------- */
    lv_init();

    lv_display_t *disp = lv_display_create(screenWidth, screenHeight);
    lv_display_set_buffers(
        disp,
        buf,
        NULL,
        sizeof(buf),
        LV_DISPLAY_RENDER_MODE_PARTIAL
    );
    lv_display_set_flush_cb(disp, my_disp_flush);

    /* ---------- REGISTER TOUCH (LVGL 9) ---------- */
    lv_indev_t *touch_indev = lv_indev_create();
    lv_indev_set_type(touch_indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(touch_indev, my_touch_read);

    /* ---------- EEZ UI ---------- */
    ui_init();
    // Register "my_button_test_bar" event handler.
  //lv_obj_add_event_cb(objects.my_button_test_bar, my_button_test_bar_event_handler, LV_EVENT_ALL, NULL);

  // Register "my_image_esp32" event handler.
  //lv_obj_add_event_cb(objects.my_image_esp32, my_image_esp32_event_handler, LV_EVENT_ALL, NULL);

  // Register "my_image_lvgl" event handler.
  //lv_obj_add_event_cb(objects.my_image_lvgl, my_image_lvgl_event_handler, LV_EVENT_ALL, NULL);

  // Register "my_image_eez" event handler.
  //lv_obj_add_event_cb(objects.my_image_eez, my_image_eez_event_handler, LV_EVENT_ALL, NULL);
   // lv_obj_add_event_cb(btn, my_event_cb, LV_EVENT_CLICKED, user_data);   /* Assign an event callback */

   // Registering the event
//      
}

/* ================================================= */
/*                        LOOP                       */
/* ================================================= */
void loop()
{
    Serial.println(receivedData.energy1);
    // lv_label_set_text_fmt(objects.freq_value1, "%d", receivedData.frequency);
    // lv_label_set_text_fmt(objects.energy_value1, "%d", receivedData.energy1);
    // lv_label_set_text_fmt(objects.energy_value2, "%d", receivedData.energy2);
    // lv_label_set_text_fmt(objects.energy_value3, "%d", receivedData.energy3);
    lv_tick_inc(5);
    lv_timer_handler();
    delay(5);
}
