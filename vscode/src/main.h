#ifndef MY_MAIN_H
#define MY_MAIN_H

//Core2 Port.C
#define MODBUS_TX_PIN 14 //(HY2.0-4P/Yellow)Connect RS485 module Rx
#define MODBUS_RX_PIN 13 //(HY2.0-4P/White)Connect RS485 module Tx
#define MODBUS_DE_PIN 20 //Dammy PIN attach Interrupt RS485 loop back clear code (M5Core2 N.C.)

//CoreS3 series Port.C
//#define MODBUS_TX_PIN 17 //(HY2.0-4P/Yellow)Connect RS485 module Rx
//#define MODBUS_RX_PIN 18 //(HY2.0-4P/White)Connect RS485 module Tx

#include <ModbusRTU.h>

//#define MODBUS_BAUD 115200
#define MODBUS_BAUD 9600

extern bool inUpdateCall;

// ===== Modbus config =====
#define SLAVE_ID 2

// Register adress offset enum
enum HoldingRegister {
    REG_RUN = 0,
    REG_FREE,
    REG_MV,
    REG_SV,
    REG_REM,
    REG_REMRATE,
    REG_PV_1,
    REG_PV_2,
    REG_PV_3,
    REG_INFO_1,
    REG_INFO_2,
    REG_INFO_3,
    REG_TIMECODE,
    REG_COUNT
};

// Modbus object
extern ModbusRTU mb;

#endif