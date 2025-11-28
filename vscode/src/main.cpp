#include <Arduino.h>
#include <M5Unified.h>
#include <Unit_Sonic.h>
#include <EEPROM.h>

#include "driver/gpio.h"

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

void onDEfallingChange()
{
  int state = gpio_get_level((gpio_num_t)MODBUS_DE_PIN);
  Serial.printf("[%d] DE changed: %s\n", millis(), state ? "HIGH" : "LOW");
  while (Serial2.available())
  {
    Serial2.read();
  }
}

void setup_modbus_reg(uint8_t slaveid)
{
  Serial2.begin(MODBUS_BAUD, SERIAL_8E1, MODBUS_RX_PIN, MODBUS_TX_PIN);

  mb.begin(&Serial2, MODBUS_DE_PIN, true);

  mb.setInterFrameTime(200 * 1000);
  mb.slave(slaveid);
  mb.addHreg(REG_RUN, 0, REG_COUNT);

  // Clear loop back from RS485
  attachInterrupt(digitalPinToInterrupt(MODBUS_DE_PIN), onDEfallingChange, FALLING);
}

void setup()
{
  EEPROM_ADDRESS_SPRM = 0;
  EEPROM_SIZE_SPRM = sizeof(SensorParam);

  auto cfg = M5.config();
  cfg.internal_imu = false;
  M5.begin(cfg);
  M5.Log.setLogLevel(m5::log_target_serial, ESP_LOG_VERBOSE);

  String LVGL_Arduino = "LVGL information : ";
  LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
  Serial.begin(115200);
  Serial.println(LVGL_Arduino);

  my_device_initialize(M5.Display);
  lv_init();
  ui_init();

  setup_modbus_reg(SLAVE_ID);

  // SensorSetup =================
  sensorParam = loadSPRMfromEEPROM();

  usSensor.begin(&Wire, 0x57, SDA, SCL, 100000L);
  setupTofSensor(&Wire);

  updateUI(sensorParam);
  saveEEPROM(sensorParam);
}

void update_modbus_reg()
{
  buff_run = mb.Hreg(REG_RUN) > 0;
  buff_freeSwitch = mb.Hreg(REG_FREE) > 0;
  buff_mv = mb.Hreg(REG_MV);
  buff_sv = mb.Hreg(REG_SV);
  buff_rem = mb.Hreg(REG_REM);
  buff_remRate = mb.Hreg(REG_REMRATE);
  buff_info_1 = mb.Hreg(REG_INFO_1);
  buff_info_2 = mb.Hreg(REG_INFO_2);
  buff_info_3 = mb.Hreg(REG_INFO_3);

  if (buff_run != prev_run)
  {
    set_var_run(buff_run);
    prev_run = buff_run;
  }

  if (buff_freeSwitch != prev_freeSwitch)
  {
    set_var_free_switch(buff_freeSwitch);
    prev_freeSwitch = buff_freeSwitch;
  }

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

uint32_t interval_I2C_AccessInt = 10;
uint32_t interval_UI = 33;

uint64_t lastMillis_ToF = 0;
uint64_t lastMillis_US = 0;
uint64_t lastMillis_I2C_Access = 0;
uint64_t lastMillis_UI = 0;

void loop()
{
  M5.update();
  unsigned long Millis = millis();

  if (Millis - lastMillis_UI > interval_UI)
  {
    lv_task_handler();
    ui_tick();
    lastMillis_UI = Millis;
  }

  Millis = millis();
  if (Millis - lastMillis_US > sensorParam.interval_US && Millis - lastMillis_I2C_Access > interval_I2C_AccessInt)
  {
    Wire.beginTransmission(0x57);
    int32_t d = (int32_t)usSensor.getDistance();
    Wire.endTransmission();
    Serial.printf("[%d] %d", Millis, d);

    set_var_pv_2(d);
    mb.Hreg(REG_PV_2, (uint16_t)d);
    lastMillis_US = Millis;
    lastMillis_I2C_Access = Millis;
  }

  Millis = millis();
  if (Millis - lastMillis_ToF > sensorParam.interval_ToF && Millis - lastMillis_I2C_Access > interval_I2C_AccessInt)
  {
    Wire.beginTransmission(0x29);
    int32_t d = (int32_t)tofSensor.read();
    Wire.endTransmission();
    Serial.printf("[%d] %d", Millis, d);

    set_var_pv_1(d);
    mb.Hreg(REG_PV_1, (uint16_t)d);
    lastMillis_ToF = Millis;
    lastMillis_I2C_Access = Millis;
  }

  mb.task();
  update_modbus_reg();

  yield();
}
