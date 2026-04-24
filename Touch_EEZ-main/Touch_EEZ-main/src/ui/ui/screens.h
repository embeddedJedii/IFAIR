#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_MAIN = 1,
    _SCREEN_ID_LAST = 1
};

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *total_load_consumption;
    lv_obj_t *total_load_;
    lv_obj_t *load_consumption_value;
    lv_obj_t *obj0;
    lv_obj_t *battery_voltage;
    lv_obj_t *obj1;
    lv_obj_t *battery_voltage_value;
    lv_obj_t *obj2;
    lv_obj_t *ac_input_voltage;
    lv_obj_t *obj3;
    lv_obj_t *ac_voltage;
    lv_obj_t *obj4;
    lv_obj_t *battery_percent;
    lv_obj_t *temp_value;
    lv_obj_t *logo;
    lv_obj_t *obj5;
    lv_obj_t *obj6;
    lv_obj_t *green_power_button;
    lv_obj_t *obj7;
    lv_obj_t *obj8;
    lv_obj_t *obj9;
    lv_obj_t *obj10;
    lv_obj_t *obj11;
    lv_obj_t *obj12;
    lv_obj_t *obj13;
    lv_obj_t *obj14;
    lv_obj_t *obj15;
    lv_obj_t *obj16;
    lv_obj_t *obj17;
    lv_obj_t *freq_value1;
    lv_obj_t *current_value1;
    lv_obj_t *voltage_value1;
    lv_obj_t *energy_value1;
    lv_obj_t *power_value1;
    lv_obj_t *obj18;
    lv_obj_t *obj19;
    lv_obj_t *obj20;
    lv_obj_t *obj21;
    lv_obj_t *obj22;
    lv_obj_t *obj23;
    lv_obj_t *obj24;
    lv_obj_t *red_power_button;
    lv_obj_t *obj25;
    lv_obj_t *obj26;
    lv_obj_t *obj27;
    lv_obj_t *obj28;
    lv_obj_t *obj29;
    lv_obj_t *obj30;
    lv_obj_t *obj31;
    lv_obj_t *obj32;
    lv_obj_t *obj33;
    lv_obj_t *obj34;
    lv_obj_t *obj35;
    lv_obj_t *freq_value2;
    lv_obj_t *current_value2;
    lv_obj_t *voltage_value2;
    lv_obj_t *energy_value2;
    lv_obj_t *power_value2;
    lv_obj_t *obj36;
    lv_obj_t *obj37;
    lv_obj_t *obj38;
    lv_obj_t *obj39;
    lv_obj_t *obj40;
    lv_obj_t *obj41;
    lv_obj_t *obj42;
    lv_obj_t *green_power_button_2_;
    lv_obj_t *obj43;
    lv_obj_t *obj44;
    lv_obj_t *obj45;
    lv_obj_t *obj46;
    lv_obj_t *obj47;
    lv_obj_t *obj48;
    lv_obj_t *obj49;
    lv_obj_t *obj50;
    lv_obj_t *obj51;
    lv_obj_t *obj52;
    lv_obj_t *obj53;
    lv_obj_t *freq_value3;
    lv_obj_t *current_value3;
    lv_obj_t *voltage_value3;
    lv_obj_t *energy_value3;
    lv_obj_t *power_value3;
    lv_obj_t *obj54;
    lv_obj_t *obj55;
    lv_obj_t *obj56;
    lv_obj_t *obj57;
    lv_obj_t *obj58;
    lv_obj_t *obj59;
    lv_obj_t *full_battery;
    lv_obj_t *obj60;
} objects_t;

extern objects_t objects;

void create_screen_main();
void tick_screen_main();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/