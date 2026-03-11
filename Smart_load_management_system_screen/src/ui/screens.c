#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint32_t active_theme_index = 0;

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff464653), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // panel_weather_description
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.panel_weather_description = obj;
            lv_obj_set_pos(obj, 6, 4);
            lv_obj_set_size(obj, 310, 100);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff262635), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff323333), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 13, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_margin_top(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_margin_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_margin_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_margin_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // panel_temperature_data
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.panel_temperature_data = obj;
            lv_obj_set_pos(obj, 6, 109);
            lv_obj_set_size(obj, 160, 90);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff262635), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff323333), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // panel_humidity_data
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.panel_humidity_data = obj;
            lv_obj_set_pos(obj, 175, 110);
            lv_obj_set_size(obj, 140, 90);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff323333), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff262635), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // panel_slider_button
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.panel_slider_button = obj;
            lv_obj_set_pos(obj, 6, 208);
            lv_obj_set_size(obj, 309, 24);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff262635), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff323333), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 10, 10);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_icon_location_11p);
        }
        {
            // label_city
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_city = obj;
            lv_obj_set_pos(obj, 31, 10);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "NIGERIA");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 243, 16);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_icon_10d_72p);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 10, 110);
            lv_obj_set_size(obj, 25, 30);
            lv_image_set_src(obj, &img_icon_temp_22p);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 16, 157);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_icon_max_11p);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 16, 177);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_icon_min_11p);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 186, 118);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_icon_humd_22p);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 188, 149);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_icon_wind_11p);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 188, 166);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_icon_pressure_11p);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 188, 183);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_icon_visibility_11p);
        }
        {
            // label_time
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_time = obj;
            lv_obj_set_pos(obj, 31, 46);
            lv_obj_set_size(obj, 144, 36);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "16:03:17");
        }
        {
            // label_date
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_date = obj;
            lv_obj_set_pos(obj, 6, 82);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "WEDNESDAY, 25-DECEMBER, 2025");
        }
        {
            // label_weather_main
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_weather_main = obj;
            lv_obj_set_pos(obj, 226, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "RAIN");
        }
        {
            // label_temperature
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_temperature = obj;
            lv_obj_set_pos(obj, 35, 110);
            lv_obj_set_size(obj, 83, 34);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "29.1C");
        }
        {
            // label_feels_like
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_feels_like = obj;
            lv_obj_set_pos(obj, 16, 140);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Feels like:                32.6C");
        }
        {
            // label_temp_max
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_temp_max = obj;
            lv_obj_set_pos(obj, 31, 157);
            lv_obj_set_size(obj, 130, 16);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "MAX      :              31.2C");
        }
        {
            // label_temp_min
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_temp_min = obj;
            lv_obj_set_pos(obj, 31, 173);
            lv_obj_set_size(obj, 128, 16);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "MIN    :                28.4C");
        }
        {
            // label_humidity
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_humidity = obj;
            lv_obj_set_pos(obj, 214, 114);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "68%");
        }
        {
            // label_wind
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_wind = obj;
            lv_obj_set_pos(obj, 202, 149);
            lv_obj_set_size(obj, 114, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Wind       :    13.5km/hr");
        }
        {
            // label_pressure
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_pressure = obj;
            lv_obj_set_pos(obj, 201, 166);
            lv_obj_set_size(obj, 114, 11);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Pressure  :    1000KPa");
        }
        {
            // label_visibility
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_visibility = obj;
            lv_obj_set_pos(obj, 199, 184);
            lv_obj_set_size(obj, 116, 11);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, " Vissibility:    50km");
        }
        {
            // main_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.main_slider = obj;
            lv_obj_set_pos(obj, 20, 215);
            lv_obj_set_size(obj, 150, 10);
            lv_slider_set_value(obj, 50, LV_ANIM_OFF);
        }
        {
            // main_switch
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.main_switch = obj;
            lv_obj_set_pos(obj, 211, 211);
            lv_obj_set_size(obj, 50, 18);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff502a2a), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
}
