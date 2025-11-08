#include <string>
#include "ui/vars.h"

std::string t; extern "C" const char *get_var_t() { return t.c_str(); }
extern "C" void set_var_t(const char *value) { t = value; }

int32_t mv; extern "C" int32_t get_var_mv() { return mv; }
extern "C" void set_var_mv(int32_t value) { mv = value; }

std::string mvunit; extern "C" const char *get_var_mvunit() { return mvunit.c_str(); }
extern "C" void set_var_mvunit(const char *value) { mvunit = value; }

int32_t sv; extern "C" int32_t get_var_sv() { return sv; }
extern "C" void set_var_sv(int32_t value) { sv = value; }

std::string svunit; extern "C" const char *get_var_svunit() { return svunit.c_str(); }
extern "C" void set_var_svunit(const char *value) { svunit = value; }

int32_t pv_1; extern "C" int32_t get_var_pv_1() { return pv_1; }
extern "C" void set_var_pv_1(int32_t value) { pv_1 = value; }

int32_t pv_2; extern "C" int32_t get_var_pv_2() { return pv_2; }
extern "C" void set_var_pv_2(int32_t value) { pv_2 = value; }

int32_t pv_3; extern "C" int32_t get_var_pv_3() { return pv_3; }
extern "C" void set_var_pv_3(int32_t value) { pv_3 = value; }

int32_t rem; extern "C" int32_t get_var_rem() { return rem; }
extern "C" void set_var_rem(int32_t value) { rem = value; }

std::string remunit; extern "C" const char *get_var_remunit() { return remunit.c_str(); }
extern "C" void set_var_remunit(const char *value) { remunit = value; }

int32_t rem_rate; extern "C" int32_t get_var_rem_rate() { return rem_rate; }
extern "C" void set_var_rem_rate(int32_t value) { rem_rate = value; }

bool run; extern "C" bool get_var_run() { return run; }
extern "C" void set_var_run(bool value) { run = value; }

bool free_switch; extern "C" bool get_var_free_switch() { return free_switch; }
extern "C" void set_var_free_switch(bool value) { free_switch = value; }

float info_1; extern "C" float get_var_info_1() { return info_1; }
extern "C" void set_var_info_1(float value) { info_1 = value; }

float info_2; extern "C" float get_var_info_2() { return info_2; }
extern "C" void set_var_info_2(float value) { info_2 = value; }

float info_3; extern "C" float get_var_info_3() { return info_3; }
extern "C" void set_var_info_3(float value) { info_3 = value; }

int32_t sensor_bottom_right_x; extern "C" int32_t get_var_sensor_bottom_right_x() { return sensor_bottom_right_x; }
extern "C" void set_var_sensor_bottom_right_x(int32_t value) { sensor_bottom_right_x = value; }

int32_t sensor_bottom_right_y; extern "C" int32_t get_var_sensor_bottom_right_y() { return sensor_bottom_right_y; }
extern "C" void set_var_sensor_bottom_right_y(int32_t value) { sensor_bottom_right_y = value; }

int32_t sensor_interval; extern "C" int32_t get_var_sensor_interval() { return sensor_interval; }
extern "C" void set_var_sensor_interval(int32_t value) { sensor_interval = value; }

int32_t sensor_top_left_x; extern "C" int32_t get_var_sensor_top_left_x() { return sensor_top_left_x; }
extern "C" void set_var_sensor_top_left_x(int32_t value) { sensor_top_left_x = value; }

int32_t sensor_top_left_y; extern "C" int32_t get_var_sensor_top_left_y() { return sensor_top_left_y; }
extern "C" void set_var_sensor_top_left_y(int32_t value) { sensor_top_left_y = value; }

