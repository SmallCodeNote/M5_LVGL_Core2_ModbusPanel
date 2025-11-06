#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *config;
    lv_obj_t *input_keyboard;
    lv_obj_t *screen_sensor1_config;
    lv_obj_t *screen_sensor1_config_input_keyboard_integer;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *userwidget_motorinfo_button_switch_run_1;
    lv_obj_t *obj2;
    lv_obj_t *obj3;
    lv_obj_t *obj4;
    lv_obj_t *obj5;
    lv_obj_t *mainpage_textarea_sv;
    lv_obj_t *obj6;
    lv_obj_t *svinput_textarea_sv_keyboard_1;
    lv_obj_t *textarea_config_sensor_top_left_x;
    lv_obj_t *textarea_config_sensor_top_left_y;
    lv_obj_t *textarea_config_sensor_bottom_right_x;
    lv_obj_t *textarea_config_sensor_bottom_right_y;
    lv_obj_t *obj7;
    lv_obj_t *textarea_config_sensor_bottom_right_y_1;
    lv_obj_t *keyboard_input_keyboard_integer_1;
    lv_obj_t *userwidget_motorinfo_button_switch_run_label_1;
    lv_obj_t *mainpage_arc_progress;
    lv_obj_t *obj8;
    lv_obj_t *obj9;
    lv_obj_t *obj10;
    lv_obj_t *obj11;
    lv_obj_t *panel_pv_1;
    lv_obj_t *panel_pv_2;
    lv_obj_t *panel_pv_3;
    lv_obj_t *mainpage_roller_mode;
    lv_obj_t *obj12;
    lv_obj_t *obj13;
    lv_obj_t *obj14;
    lv_obj_t *obj15;
    lv_obj_t *input_keyboard_textarea;
    lv_obj_t *label_input_keyboard_integer;
    lv_obj_t *textarea_input_keyboard_integer_1;
    lv_obj_t *label_input_keyboard_integer_1;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_CONFIG = 2,
    SCREEN_ID_INPUT_KEYBOARD = 3,
    SCREEN_ID_SCREEN_SENSOR1_CONFIG = 4,
    SCREEN_ID_SCREEN_SENSOR1_CONFIG_INPUT_KEYBOARD_INTEGER = 5,
};

void create_screen_main();
void tick_screen_main();

void create_screen_config();
void tick_screen_config();

void create_screen_input_keyboard();
void tick_screen_input_keyboard();

void create_screen_screen_sensor1_config();
void tick_screen_screen_sensor1_config();

void create_screen_screen_sensor1_config_input_keyboard_integer();
void tick_screen_screen_sensor1_config_input_keyboard_integer();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/