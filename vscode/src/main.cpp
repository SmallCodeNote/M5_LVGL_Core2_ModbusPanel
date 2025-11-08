#include <Arduino.h>
#include <M5Unified.h>

#include "sensor_control.h"

#include "ui/ui.h"
#include "ui/eez-flow.h"
#include "ui/screens.h"
#include "ui/vars.h"

#include "my_common_code.h"
#include "my_debug.h"
#include "main.h"

bool inUpdateCall = false;

ModbusRTU mb;


bool buff_run;
bool buff_freeSwitch;
uint32_t buff_mv;
uint32_t buff_sv;
uint32_t buff_rem;
uint32_t buff_remRate;
uint32_t buff_info_1;
uint32_t buff_info_2;
uint32_t buff_info_3;


bool prev_run;
bool prev_freeSwitch;
uint32_t prev_mv;
uint32_t prev_sv;
uint32_t prev_rem;
uint32_t prev_remRate;
uint32_t prev_info_1;
uint32_t prev_info_2;
uint32_t prev_info_3;

void setup_modbus_reg(){

Serial2.begin(MODBUS_BAUD, SERIAL_8E1, MODBUS_RX_PIN, MODBUS_TX_PIN);
  mb.begin(&Serial2);
  mb.slave(SLAVE_ID);
  mb.addHreg(REG_RUN, 0, REG_COUNT);

  mb.Hreg(REG_RUN, 0);
  mb.Hreg(REG_FREE, 0);
  mb.Hreg(REG_MV, 0);
  mb.Hreg(REG_SV, 0);
  mb.Hreg(REG_REM, 0);
  mb.Hreg(REG_REMRATE, 0);

  prev_run = mb.Hreg(REG_RUN);
  prev_freeSwitch = mb.Hreg(REG_FREE);
  prev_mv = mb.Hreg(REG_MV);
  prev_sv = mb.Hreg(REG_SV);
  prev_rem = mb.Hreg(REG_REM);
  prev_remRate = mb.Hreg(REG_REMRATE);
  prev_info_1 = mb.Hreg(REG_INFO_1);
  prev_info_2 = mb.Hreg(REG_INFO_2);
  prev_info_3 = mb.Hreg(REG_INFO_3);

}


void setup()
{
  EEPROM_ADDRESS_SPRM = 0;
  EEPROM_SIZE_SPRM = sizeof(SensorParam);

  auto cfg = M5.config();
  cfg.internal_imu = false;
  M5.begin(cfg);

  String LVGL_Arduino = "LVGL information : ";
  LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
  Serial.begin(115200);
  Serial.println(LVGL_Arduino);

  my_device_initialize(M5.Display);
  lv_init();
  ui_init();

  setup_modbus_reg();

  // SensorSetup =================
  sensorParam = loadSPRMfromEEPROM();
  setupSensor();

  updateUI(sensorParam);
  saveEEPROM(sensorParam);
}

int waitCountUnit = 10;
int waitCountSum = 0;

void update_modbus_reg()
{
  buff_run = mb.Hreg(REG_RUN);
  buff_freeSwitch = mb.Hreg(REG_FREE);
  buff_mv = mb.Hreg(REG_MV);
  buff_sv = mb.Hreg(REG_SV);
  buff_rem = mb.Hreg(REG_REM);
  buff_remRate = mb.Hreg(REG_REMRATE);
  buff_info_1 = mb.Hreg(REG_INFO_1);
  buff_info_2 = mb.Hreg(REG_INFO_2);
  buff_info_3 = mb.Hreg(REG_INFO_3);

  if (buff_mv != prev_mv)
  {
    set_var_mv(buff_mv);
    prev_mv = buff_mv;
  }
  if (buff_sv != prev_sv)
  {
    set_var_sv(buff_sv);
    prev_sv = buff_sv;
  }
  if (buff_rem != prev_rem)
  {
    set_var_rem(buff_rem);
    prev_rem = buff_rem;
  }
  if (buff_remRate != prev_remRate)
  {
    set_var_rem_rate(buff_remRate);
    prev_remRate = buff_remRate;
  }
  if (buff_info_1 != prev_info_1)
  {
    set_var_info_1(buff_info_1);
    prev_info_1 = buff_info_1;
  }
  if (buff_info_2 != prev_info_2)
  {
    set_var_info_2(buff_info_2);
    prev_info_2 = buff_info_2;
  }
  if (buff_info_3 != prev_info_3)
  {
    set_var_info_3(buff_info_3);
    prev_info_3 = buff_info_3;
  }
}

void loop()
{
  M5.update();
  lv_task_handler();
  ui_tick();
  vTaskDelay(waitCountUnit);
  waitCountSum += waitCountUnit;
  update_modbus_reg();

}
