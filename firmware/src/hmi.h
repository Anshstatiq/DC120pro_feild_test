
#include <stddef.h>                     
#include <stdbool.h>                               
#include "definitions.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"



#define HEADER1_t     0x5A
#define HEADER2_t     0xA5
#define DATA_SIZE     0xFF
#define ERROR_SIZE    0x46
#define SENDING_CMD_t 0x82
#define ADD_DATA_MSB_t     0x10
#define ADD_DATA_LSB_t     0x00
#define ADD_ERROR_MSB_t    0x10
#define ADD_ERROR_LSB_t    0x7D

typedef union {
    uint8_t HMI_DATA_ARRAY[256];

    struct {
        /////////////////////GUN1 Parameter//////////////////
        // char PAGE_CNG[9];
        uint8_t HEADER1;
        uint8_t HEADER2;
        uint16_t SIZE;
        uint8_t SENDING_CMD;
        uint8_t ADD_MSB;
        uint8_t ADD_LSB;
        ///////////////////Gun1 Parameter///////////////////////
        char G1_INITIAL_SOC[4];
        char G1_VOLTAGE[6];
        char G1_CURRENT[4];
        char G1_CHG_VOLTAGE[6];
        char G1_CHG_Current[4];
        char G1_CURRENT_SOC[4];
        char G1_Duration[6];
        char G1_ENERGY_CONSUME[6];
        char G1_GUN_MIN_CURRENT[4];
        /////////////////////GUN2 Parameter//////////////////
        char G2_INITIAL_SOC[4];
        char G2_VOLTAGE[6];
        char G2_CURRENT[4];
        char G2_CHG_VOLTAGE[6];
        char G2_CHG_Current[4];
        char G2_CURRENT_SOC[4];
        char G2_Duration[6];
        char G2_ENERGY_CONSUME[6];
        char G2_GUN_MIN_CURRENT[4];

        //////////////////////AC Meter Parameter//////////////////
        char L1_VOLTAGE[6];
        char L2_VOLTAGE[6];
        char L3_VOLTAGE[6];
        char AVG_VOLTAGE[6];
        char FREQ[4];
        char POW_FACTOR[4];
        char L1_CURRENT[4];
        char L2_CURRENT[4];
        char L3_CURRENT[4];
        char AVG_CURR[4];
        char ACTIVE_POW[6];
        char TOTAL_POWER[6];
        /////////////////////DC Meter1 Parameter//////////////////
        char G1_OUTPUT_VOLTAGE[6]; //1016
        char G1_OUTPUT_CURRENT[4]; //1018
        char G1_OUTPUT_POWER[6]; //1020
        char G1_IMPORT_ENERGY[6];
        char G1_EXPORT_ENERGY[6];
        char G1_MAX_VOLTAGE[6];
        char G1_MIN_VOLTAGE[6];
        char G1_MAX_CURRENT[4];
        char G1_MIN_CURRENT[4];
        //////////////////////DC Meter2 Parameter//////////////////
        char G2_OUTPUT_VOLTAGE[6];
        char G2_OUTPUT_CURRENT[4];
        char G2_OUTPUT_POWER[6];
        char G2_IMPORT_ENERGY[6];
        char G2_EXPORT_ENERGY[6];
        char G2_MAX_VOLTAGE[6];
        char G2_MIN_VOLTAGE[6];
        char G2_MAX_CURRENT[6];
        char G2_MIN_CURRENT[4];
        char RESERVED[6];
    };
} HMI_DATA;

typedef union {
    uint8_t HMI_ERROR_STATUS_ARRAY[70];

    struct {
        //////////////////////////Error and Status///////////////////////////
        uint8_t HEADER1;
        uint8_t HEADER2;
        uint8_t SIZE;
        uint8_t SENDING_CMD;
        uint8_t ADD_MSB;
        uint8_t ADD_LSB;
        uint8_t MAIN_OK_FAIL[2];
        uint8_t HIGH_NE_VOLTAGE_OK_FAIL[2];
        uint8_t MAINS_UNDER_VOLTAGE[2];
        uint8_t MAINS_OVER_VOLTAGE[2];
        uint8_t RFID_COMM[2];
        uint8_t ACEM_COMM1[2];
        uint8_t GUN_TEMP[2];
        uint8_t SPD[2];
        uint8_t HIGH_LEAKAGE[2];
        uint8_t SYSTEM_TEMP[2];
        uint8_t PLC_COMM[2];
        uint8_t CONTROLLER_DASH[2];
        uint8_t SMOKE_DETECT[2];
        uint8_t ESD_PRESSED[2];
        uint8_t All_RECTI_COMM[2];
        uint8_t ISOLATION[2];
        uint8_t LED_BOARD[2];
        uint8_t RECTI_1_COMM[2];
        uint8_t RECTI_2_COMM[2];
        uint8_t DC_OVER_VOLTAGE[2];
        uint8_t DC_UNDER_VOLTAGE[2];
        uint8_t DC_OP_OVER_CURRENT[2];
        uint8_t HMI_COMM_FAIL[2];
        uint8_t MODEM_COMM_FAIL[2];
        uint8_t DCEM_COMM_FAIL[2];
        uint8_t ALL_PLC_COMM_FAIL[2];
        uint8_t ALL_DCEM_COMM_FAIL[2];
        uint8_t LIMIT_SWITCH[2];
        uint8_t ALL_STATUS[2];
        uint8_t CHARGING_STATUS[2];
        uint8_t ETHERNET_STATUS[2];
        uint8_t OCPP_STATUS[2];
    };
} HMI_ERROR;

typedef union {
    uint8_t METER_DATA_ARRAY[170];

    struct {
        /////////////////////GUN1 Parameter//////////////////
        // char PAGE_CNG[9];
        uint8_t HEADER1;
        uint8_t HEADER2;
        uint16_t SIZE;
        uint8_t SENDING_CMD;
        uint8_t ADD_MSB;
        uint8_t ADD_LSB;
        //////////////////////AC Meter Parameter//////////////////
        char L1_VOLTAGE[6];
        char L2_VOLTAGE[6];
        char L3_VOLTAGE[6];
        char AVG_VOLTAGE[6];
        char FREQ[4];
        char POW_FACTOR[4];
        char L1_CURRENT[4];
        char L2_CURRENT[4];
        char L3_CURRENT[4];
        char AVG_CURR[4];
        char ACTIVE_POW[6];
        char TOTAL_POWER[6];
        /////////////////////DC Meter1 Parameter//////////////////
        char G1_OUTPUT_VOLTAGE[6]; //1016
        char G1_OUTPUT_CURRENT[4]; //1018
        char G1_OUTPUT_POWER[6]; //1020
        char G1_IMPORT_ENERGY[6];
        char G1_EXPORT_ENERGY[6];
        char G1_MAX_VOLTAGE[6];
        char G1_MIN_VOLTAGE[6];
        char G1_MAX_CURRENT[4];
        char G1_MIN_CURRENT[4];
        //////////////////////DC Meter2 Parameter//////////////////
        char G2_OUTPUT_VOLTAGE[6];
        char G2_OUTPUT_CURRENT[4];
        char G2_OUTPUT_POWER[6];
        char G2_IMPORT_ENERGY[6];
        char G2_EXPORT_ENERGY[6];
        char G2_MAX_VOLTAGE[6];
        char G2_MIN_VOLTAGE[6];
        char G2_MAX_CURRENT[6];
        char G2_MIN_CURRENT[4];
        char RESERVED[6];
    };
} METER_DATA;




typedef union {
    uint8_t GUN_DATA_ARRAY[94];
struct {
    /////////////////////GUN1 Parameter//////////////////
    // char PAGE_CNG[9];
    uint8_t HEADER1;
    uint8_t HEADER2;
    uint16_t SIZE;
    uint8_t SENDING_CMD;
    uint8_t ADD_MSB;
    ///////////////////Gun1 Parameter///////////////////////
    char G1_INITIAL_SOC[4];
    char G1_VOLTAGE[6];
    char G1_CURRENT[4];
    char G1_CHG_VOLTAGE[6];
    char G1_CHG_Current[4];
    char G1_CURRENT_SOC[4];
    char G1_Duration[6];
    char G1_ENERGY_CONSUME[6];
    char G1_GUN_MIN_CURRENT[4];
    /////////////////////GUN2 Parameter//////////////////
    char G2_INITIAL_SOC[4];
    char G2_VOLTAGE[6];
    char G2_CURRENT[4];
    char G2_CHG_VOLTAGE[6];
    char G2_CHG_Current[4];
    char G2_CURRENT_SOC[4];
    char G2_Duration[6];
    char G2_ENERGY_CONSUME[6];
    char G2_GUN_MIN_CURRENT[4];

};
}GUN_DATA;




