#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations



// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_CONFIG_TARGET_ITEM_INDEX = 0,
    FLOW_GLOBAL_VARIABLE_CONFIG_TARGET_ITEM_LIST = 1,
    FLOW_GLOBAL_VARIABLE_SENSOR_CONFIG_TARGET_INDEX = 2,
    FLOW_GLOBAL_VARIABLE_SENSOR_CONFIG_TARGET_ITEM_LIST = 3
};

// Native global variables

extern int32_t get_var_mv();
extern void set_var_mv(int32_t value);
extern const char *get_var_mvunit();
extern void set_var_mvunit(const char *value);
extern int32_t get_var_sv();
extern void set_var_sv(int32_t value);
extern const char *get_var_svunit();
extern void set_var_svunit(const char *value);
extern int32_t get_var_pv_1();
extern void set_var_pv_1(int32_t value);
extern int32_t get_var_pv_2();
extern void set_var_pv_2(int32_t value);
extern int32_t get_var_pv_3();
extern void set_var_pv_3(int32_t value);
extern int32_t get_var_rem();
extern void set_var_rem(int32_t value);
extern const char *get_var_remunit();
extern void set_var_remunit(const char *value);
extern int32_t get_var_rem_rate();
extern void set_var_rem_rate(int32_t value);
extern bool get_var_run();
extern void set_var_run(bool value);
extern int32_t get_var_sensor_bottom_right_x();
extern void set_var_sensor_bottom_right_x(int32_t value);
extern int32_t get_var_sensor_bottom_right_y();
extern void set_var_sensor_bottom_right_y(int32_t value);
extern int32_t get_var_sensor_interval();
extern void set_var_sensor_interval(int32_t value);
extern int32_t get_var_sensor_top_left_x();
extern void set_var_sensor_top_left_x(int32_t value);
extern int32_t get_var_sensor_top_left_y();
extern void set_var_sensor_top_left_y(int32_t value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/