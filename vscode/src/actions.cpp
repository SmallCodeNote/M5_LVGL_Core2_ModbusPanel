#include <Arduino.h>
#include <M5Unified.h>

#include "ui/actions.h"
#include "ui/vars.h"

#include "sensor_control.h"
#include "my_debug.h"
#include "main.h"

extern "C" void action_sensor_param_update_1(lv_event_t *e)
{
    readUI(sensorParam);
    saveEEPROM(sensorParam);
}

extern "C" void action_sensor_param_update_2(lv_event_t *e)
{
    readUI(sensorParam);
    saveEEPROM(sensorParam);
}

extern "C" void action_send_message(lv_event_t *e)
{


}
