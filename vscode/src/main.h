#ifndef MY_MAIN_H
#define MY_MAIN_H

#include <ModbusRTU.h>

#define MODBUS_TX_PIN 25
#define MODBUS_RX_PIN 34
#define MODBUS_BAUD 115200

extern bool inUpdateCall;

// ===== Modbus config =====
#define SLAVE_ID 2

// レジスタ定義を enum で管理
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
    T,
    REG_COUNT
};


// Modbus object
extern ModbusRTU mb;

#endif