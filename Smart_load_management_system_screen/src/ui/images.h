#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_logo;
extern const lv_img_dsc_t img_plug;
extern const lv_img_dsc_t img_battery_volt_icon;
extern const lv_img_dsc_t img_energy_resize2;
extern const lv_img_dsc_t img_full_batt;
extern const lv_img_dsc_t img_power_button_resize;
extern const lv_img_dsc_t img_red_power_button;
extern const lv_img_dsc_t img_t_emp;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[8];

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/