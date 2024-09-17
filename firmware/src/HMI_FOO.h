
#include <stddef.h>                     
#include <stdbool.h>                    
#include <stdlib.h>                     
#include "definitions.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

typedef struct{
    uint8_t DATA[40];    
}HMI_SEND_DATA_Q;

extern QueueHandle_t HMI_SEND_QUEUE;

#define DATA_1  0x01

#define OCPP_SYMBOL_ADD_MSB 0x12
#define OCPP_SYMBOL_ADD_LSB 0x00    
#define ETH_ADD_MSB 0x12
#define ETH_ADD_LSB 0x01  
#define GSM_SIG_ADD_MSB 0x12
#define GSM_SIG_ADD_LSB 0x02
#define GSM_INT_ADD_MSB 0x12
#define GSM_INT_ADD_LSB 0x03    
#define WIFI_ADD_MSB 0x12
#define WIFI_ADD_LSB 0x04
#define WIFIA_ADD_MSB 0x12
#define WIFIA_ADD_LSB 0x05
#define GUN1_STATUS_ADD_MSB 0x12
#define GUN1_STATUS_ADD_LSB 0x06
#define GUN2_STATUS_ADD_MSB 0x12
#define GUN2_STATUS_ADD_LSB 0x07
#define GUN1_RFID_ADD_MSB 0x12
#define GUN1_RFID_ADD_LSB 0x08
#define GUN2_RFID_ADD_MSB 0x12
#define GUN2_RFID_ADD_LSB 0x09    
#define UNIT_PRICE_ADD_MSB 0x10
#define UNIT_PRICE_ADD_LSB 0x00
#define G1_BATTERY_SOC_ADD_MSB 0x10
#define G1_BATTERY_SOC_ADD_LSB 0x02    
#define G1_INITIAL_SOC_ADD_MSB 0x10
#define G1_INITIAL_SOC_ADD_LSB 0x04
#define G1_DURATION_ADD_MSB 0x10
#define G1_DURATION_ADD_LSB 0x06 
#define G1_DEMAND_VOLTAGE_ADD_MSB 0x10
#define G1_DEMAND_VOLTAGE_ADD_LSB 0x0A
#define G1_DEMAND_CURRENT_ADD_MSB 0x10
#define G1_DEMAND_CURRENT_ADD_LSB 0x0E
#define G1_CURRENT_ADD_MSB 0x10
#define G1_CURRENT_ADD_LSB 0x12
#define G1_VOLTAGE_ADD_MSB 0x10
#define G1_VOLTAGE_ADD_LSB 0x16
#define G1_TOTAL_POWER_ADD_MSB 0x10
#define G1_TOTAL_POWER_ADD_LSB 0x1A    
#define G1_STOP_ICON_ADD_MSB 0x12
#define G1_STOP_ICON_ADD_LSB 0x0A
#define G1_STOP_BUTTON_ADD_MSB 0x12
#define G1_STOP_BUTTON_ADD_LSB 0x0B
#define G1_CHARGING_DURATION_ADD_MSB 0x10
#define G1_CHARGING_DURATION_ADD_LSB 0x06
#define G1_CHARGING_STOP_DATE_ADD_MSB 0x10
#define G1_CHARGING_STOP_DATE_ADD_LSB 0x1C
#define G1_CHARGING_STOP_MONTH_ADD_MSB 0x10
#define G1_CHARGING_STOP_MONTH_ADD_LSB 0x1E
#define G1_CHARGING_STOP_YEAR_ADD_MSB 0x10
#define G1_CHARGING_STOP_YEAR_ADD_LSB 0x20
#define G1_CHARGING_STOP_HOUR_ADD_MSB 0x10
#define G1_CHARGING_STOP_HOUR_ADD_LSB 0x22
#define G1_CHARGING_STOP_MIN_ADD_MSB 0x10
#define G1_CHARGING_STOP_MIN_ADD_LSB 0x24
#define G1_CHARGING_STOP_SEC_ADD_MSB 0x10
#define G1_CHARGING_STOP_SEC_ADD_LSB 0x26

#define G1_CHARGING_START_DATE_ADD_MSB 0x10
#define G1_CHARGING_START_DATE_ADD_LSB 0x28
#define G1_CHARGING_START_MONTH_ADD_MSB 0x10
#define G1_CHARGING_START_MONTH_ADD_LSB 0x2A
#define G1_CHARGING_START_YEAR_ADD_MSB 0x10
#define G1_CHARGING_START_YEAR_ADD_LSB 0x2C
#define G1_CHARGING_START_HOUR_ADD_MSB 0x10
#define G1_CHARGING_START_HOUR_ADD_LSB 0x2E
#define G1_CHARGING_START_MIN_ADD_MSB 0x10
#define G1_CHARGING_START_MIN_ADD_LSB 0x30
#define G1_CHARGING_START_SEC_ADD_MSB 0x10
#define G1_CHARGING_START_SEC_ADD_LSB 0x32
#define G1_START_SOC_ADD_MSB 0x10
#define G1_START_SOC_ADD_LSB 0x04
#define G1_END_SOC_ADD_MSB 0x10
#define G1_END_SOC_ADD_LSB 0x02
#define G1_UNIT_CONSUMED_ADD_MSB 0x10
#define G1_UNIT_CONSUMED_ADD_LSB 0x34
#define G1_BOOKING_ID_ADD_MSB 0x10
#define G1_BOOKING_ID_ADD_LSB 0x38
#define G1_SESSION_END_REASON_ADD_MSB 0x12
#define G1_SESSION_END_REASON_ADD_LSB 0x0C

#define G2_BATTERY_SOC_ADD_MSB 0x10
#define G2_BATTERY_SOC_ADD_LSB 0x3C    
#define G2_INITIAL_SOC_ADD_MSB 0x10
#define G2_INITIAL_SOC_ADD_LSB 0x3E
#define G2_DURATION_ADD_MSB 0x10
#define G2_DURATION_ADD_LSB 0x40  
#define G2_DEMAND_VOLTAGE_ADD_MSB 0x10
#define G2_DEMAND_VOLTAGE_ADD_LSB 0x44
#define G2_DEMAND_CURRENT_ADD_MSB 0x10
#define G2_DEMAND_CURRENT_ADD_LSB 0x48
#define G2_CURRENT_ADD_MSB 0x10
#define G2_CURRENT_ADD_LSB 0x4C
#define G2_VOLTAGE_ADD_MSB 0x10
#define G2_VOLTAGE_ADD_LSB 0x50
#define G2_TOTAL_POWER_ADD_MSB 0x10
#define G2_TOTAL_POWER_ADD_LSB 0x54    
#define G2_STOP_ICON_ADD_MSB 0x12
#define G2_STOP_ICON_ADD_LSB 0x0D
#define G2_STOP_BUTTON_ADD_MSB 0x12
#define G2_STOP_BUTTON_ADD_LSB 0x0E
#define G2_CHARGING_DURATION_ADD_MSB 0x10
#define G2_CHARGING_DURATION_ADD_LSB 0x58
#define G2_CHARGING_START_DATE_ADD_MSB 0x10
#define G2_CHARGING_START_DATE_ADD_LSB 0x5C
#define G2_CHARGING_START_MONTH_ADD_MSB 0x10
#define G2_CHARGING_START_MONTH_ADD_LSB 0x5E
#define G2_CHARGING_START_YEAR_ADD_MSB 0x10
#define G2_CHARGING_START_YEAR_ADD_LSB 0x60
#define G2_CHARGING_START_HOUR_ADD_MSB 0x10
#define G2_CHARGING_START_HOUR_ADD_LSB 0x62
#define G2_CHARGING_START_MIN_ADD_MSB 0x10
#define G2_CHARGING_START_MIN_ADD_LSB 0x64
#define G2_CHARGING_START_SEC_ADD_MSB 0x10
#define G2_CHARGING_START_SEC_ADD_LSB 0x66
#define G2_CHARGING_STOP_DATE_ADD_MSB 0x10
#define G2_CHARGING_STOP_DATE_ADD_LSB 0x68
#define G2_CHARGING_STOP_MONTH_ADD_MSB 0x10
#define G2_CHARGING_STOP_MONTH_ADD_LSB 0x6A
#define G2_CHARGING_STOP_YEAR_ADD_MSB 0x10
#define G2_CHARGING_STOP_YEAR_ADD_LSB 0x6C
#define G2_CHARGING_STOP_HOUR_ADD_MSB 0x10
#define G2_CHARGING_STOP_HOUR_ADD_LSB 0x6E
#define G2_CHARGING_STOP_MIN_ADD_MSB 0x10
#define G2_CHARGING_STOP_MIN_ADD_LSB 0x70
#define G2_CHARGING_STOP_SEC_ADD_MSB 0x10
#define G2_CHARGING_STOP_SEC_ADD_LSB 0x72
#define G2_START_SOC_ADD_MSB 0x10
#define G2_START_SOC_ADD_LSB 0x3E
#define G2_END_SOC_ADD_MSB 0x10
#define G2_END_SOC_ADD_LSB 0x3C
#define G2_UNIT_CONSUMED_ADD_MSB 0x10
#define G2_UNIT_CONSUMED_ADD_LSB 0x74
#define G2_BOOKING_ID_ADD_MSB 0x10
#define G2_BOOKING_ID_ADD_LSB 0x78
#define G2_SESSION_END_REASON_ADD_MSB 0x12
#define G2_SESSION_END_REASON_ADD_LSB 0x0F
#define GUN1_BATTERY_PERCENT_ADD_MSB    0x12
#define GUN1_BATTERY_PERCENT_ADD_LSB    0x10
#define GUN2_BATTERY_PERCENT_ADD_MSB    0x12
#define GUN2_BATTERY_PERCENT_ADD_LSB    0x11
#define AMBIENT_TEMP_ADD_MSB    0x10
#define AMBIENT_TEMP_ADD_LSB 0x8A
#define RSSI_VALUE_ADD_MSB 0x10
#define RSSI_VALUE_ADD_LSB  0x8C
#define GUN1_TEMP_ADD_MSB   0x10
#define GUN1_TEMP_ADD_LSB   0x8E
#define GUN2_TEMP_ADD_MSB   0x10
#define GUN2_TEMP_ADD_LSB   0x90

#define MAIN_FAIL_ADD_MSB 0x13
#define MAIN_FAIL_ADD_LSB 0x00
#define HIGH_LEAKAGE_ADD_MSB 0x13
#define HIGH_LEAKAGE_ADD_LSB 0x01
#define HIGH_NE_ADD_MSB 0x13
#define HIGH_NE_ADD_LSB 0x02
#define MAINS_LOW_ADD_MSB 0x13
#define MAINS_LOW_ADD_LSB 0x03
#define MAINS_HIGH_ADD_MSB 0x13
#define MAINS_HIGH_ADD_LSB 0x04
#define SMOKE_DETECTED_ADD_MSB 0x13
#define SMOKE_DETECTED_ADD_LSB 0x05
#define ESD_PRESSED_ADD_MSB 0x13
#define ESD_PRESSED_ADD_LSB 0x06
#define SPD_PRESSED_ADD_MSB 0x13
#define SPD_PRESSED_ADD_LSB 0x07
#define ACEM_COMM_FAIL_ADD_MSB 0x13
#define ACEM_COMM_FAIL_ADD_LSB 0x08
#define SYSTEM_TEMP_HIGH_ADD_MSB 0x13
#define SYSTEM_TEMP_HIGH_ADD_LSB 0x09
#define ALL_REC_FAIL_ADD_MSB 0x13
#define ALL_REC_FAIL_ADD_LSB 0x0A
#define REC1_FAIL_ADD_MSB 0x13
#define REC1_FAIL_ADD_LSB 0x0B
#define REC2_FAIL_ADD_MSB 0x13
#define REC2_FAIL_ADD_LSB 0x0C
#define REC3_FAIL_ADD_MSB 0x13
#define REC3_FAIL_ADD_LSB 0x0D
#define REC4_FAIL_ADD_MSB 0x13
#define REC4_FAIL_ADD_LSB 0x0E
#define DCEM1_COMM_FAIL_ADD_MSB 0x13
#define DCEM1_COMM_FAIL_ADD_LSB 0x0F
#define DCEM2_COMM_FAIL_ADD_MSB 0x13
#define DCEM2_COMM_FAIL_ADD_LSB 0x10
#define PLC1_COMM_FAIL_ADD_MSB 0x13
#define PLC1_COMM_FAIL_ADD_LSB 0x11
#define PLC2_COMM_FAIL_ADD_MSB 0x13
#define PLC2_COMM_FAIL_ADD_LSB 0x12
#define DOOR_OPEN_ADD_MSB 0x13
#define DOOR_OPEN_ADD_LSB 0x13
#define RFID_COMM_FAIL_ADD_MSB 0x13
#define RFID_COMM_FAIL_ADD_LSB 0x14
#define CONTROLLER_FAIL_ADD_MSB 0x13
#define CONTROLLER_FAIL_ADD_LSB 0x15
#define ISOLATION_FAIL1_ADD_MSB 0x13
#define ISOLATION_FAIL1_ADD_LSB 0x16
#define ISOLATION_FAIL2_ADD_MSB 0x13
#define ISOLATION_FAIL2_ADD_LSB 0x25
#define LEDBOARD_FAULT1_ADD_MSB 0x13
#define LEDBOARD_FAULT1_ADD_LSB 0x17
#define LEDBOARD_FAULT2_ADD_MSB 0x13
#define LEDBOARD_FAULT2_ADD_LSB 0x27
#define HMI_COMM_FAIL_ADD_MSB 0x13
#define HMI_COMM_FAIL_ADD_LSB 0x18
#define MODEM_COMM_FAIL_ADD_MSB 0x13
#define MODEM_COMM_FAIL_ADD_LSB 0x19
#define GUN1_TEMP_HIGH_ADD_MSB 0x13
#define GUN1_TEMP_HIGH_ADD_LSB 0x1A
#define GUN2_TEMP_HIGH_ADD_MSB 0x13
#define GUN2_TEMP_HIGH_ADD_LSB 0x1B
#define REC1_FAULT_ADD_MSB 0x13
#define REC1_FAULT_ADD_LSB 0x1E
#define REC2_FAULT_ADD_MSB 0x13
#define REC2_FAULT_ADD_LSB 0x1F
#define REC3_FAULT_ADD_MSB 0x13
#define REC3_FAULT_ADD_LSB 0x20
#define REC4_FAULT_ADD_MSB 0x13
#define REC4_FAULT_ADD_LSB 0x21
#define DC_OVERVOLTAGE1_ADD_MSB 0x13
#define DC_OVERVOLTAGE1_ADD_LSB 0x22
#define DC_OVERVOLTAGE2_ADD_MSB 0x13
#define DC_OVERVOLTAGE2_ADD_LSB 0x1C
#define DC_UNDERVOLTAGE1_ADD_MSB 0x13
#define DC_UNDERVOLTAGE1_ADD_LSB 0x23
#define DC_UNDERVOLTAGE2_ADD_MSB 0x13
#define DC_UNDERVOLTAGE2_ADD_LSB 0x26
#define DC_OUT_OVERCURRENT2_ADD_MSB 0x13
#define DC_OUT_OVERCURRENT2_ADD_LSB 0x1D
#define DC_OUT_OVERCURRENT1_ADD_MSB 0x13
#define DC_OUT_OVERCURRENT1_ADD_LSB 0x24
#define AC_VOLTAGE1_ADD_MSB 0x10
#define AC_VOLTAGE1_ADD_LSB 0x7C
#define AC_VOLTAGE2_ADD_MSB 0x10
#define AC_VOLTAGE2_ADD_LSB 0x7E
#define AC_VOLTAGE3_ADD_MSB 0x10
#define AC_VOLTAGE3_ADD_LSB 0x80
#define AC_CURRENT1_ADD_MSB 0x10
#define AC_CURRENT1_ADD_LSB 0x82
#define AC_CURRENT2_ADD_MSB 0x10
#define AC_CURRENT2_ADD_LSB 0x84
#define AC_CURRENT3_ADD_MSB 0x10
#define AC_CURRENT3_ADD_LSB 0x86
#define AC_FREQUENCY_ADD_MSB    0x10
#define AC_FREQUENCY_ADD_LSB    0x88
#define OCPP_ID_ADD_MSB 0x10
#define OCPP_ID_ADD_LSB 0xDE
#define BLE_ID_ADD_MSB 0x10
#define BLE_ID_ADD_LSB 0xAE
#define REC1_TEMP_ADD_MSB   0x10
#define REC1_TEMP_ADD_LSB   0x92
#define REC2_TEMP_ADD_MSB   0x10
#define REC2_TEMP_ADD_LSB   0x94
#define GUN1_STOP_BTN_ADD_MSB   0x12
#define GUN1_STOP_BTN_ADD_LSB   0x30
#define GUN2_STOP_BTN_ADD_MSB   0x12
#define GUN2_STOP_BTN_ADD_LSB   0x31
#define REC1_STATUS_ADD_MSB     0x60
#define REC1_STATUS_ADD_LSB     0x00
#define REC2_STATUS_ADD_MSB     0x60
#define REC2_STATUS_ADD_LSB     0x04
#define REC3_STATUS_ADD_MSB     0x60
#define REC3_STATUS_ADD_LSB     0x08
#define REC4_STATUS_ADD_MSB     0x60
#define REC4_STATUS_ADD_LSB     0x0C




#define INTRO_PAGE  0x03
#define GUN1_AUTHENTICATION_PAGE 0x2A
#define GUN1_AUTHENTICATION_SUCCESS_PAGE    0x05
#define GUN1_AUTHENTICATION_FAIL_PAGE   0x06
#define GUN1_PREPARING_TO_CHARGE_PAGE   0x07
#define GUN1_FAILING_REASON_PAGE    0x08
#define GUN1_PARAM_PAGE 0x09
#define GUN1_MANUAL_STOP_PAGE   0x0A
#define GUN1_MOBILE_STOP_PAGE   0x0A
#define GUN1_RFID_STOP_PAGE 0x0B
#define GUN1_SUMMARY_PAGE   0x0C
#define GUN2_AUTHENTICATION_PAGE 0x2B
#define GUN2_AUTHENTICATION_SUCCESS_PAGE    0x0E
#define GUN2_AUTHENTICATION_FAIL_PAGE   0x0F
#define GUN2_PREPARING_TO_CHARGE_PAGE   0x10
#define GUN2_FAILING_REASON_PAGE    0x11
#define GUN1_WAITING_FOR_AUTH   0x04
#define GUN2_WAITING_FOR_AUTH   0x0D


#define GUN2_PARAM_PAGE 0x12
#define GUN2_MOBILE_STOP_PAGE   0x13
#define GUN2_RFID_STOP_PAGE 0x14
#define GUN2_SUMMARY_PAGE   0x15
#define WARNING_PAGE_NUMBER 0x22
#define RFID_UNAVAILABLE_PAGE 0x23
#define MAINS_FAIL_PAGE 0x24
#define NO_NETWORK_PAGE 0x25



#define UNAVAILABLE 0x00
#define AVAILABLE   0x01
#define CONNECTED   0x02
#define CHARGING   0x03
#define RESERVED    0x04
#define CHARGING_COMPLETED   0x05
#define FAULT   0x06



void SINGLE_BIT_HEADER(void);
void DOUBLE_BYTE_HEADER(void);
void LONG_BYTE_HEADER(void);



void Change_Page_to(uint8_t page_no);
void Change_gun1_status_to(uint8_t status);
void Change_gun2_status_to(uint8_t status);

void Update_GUN1_Battery_Percent(uint8_t percent);
void Update_GUN2_Battery_Percent(uint8_t percent);

void Update_OCPP_ID(uint8_t data[]);
void Update_BLE_ID(uint8_t data[]);

void Update_Ambient_Temp(uint16_t temp);
void Update_RSSI_Value(uint16_t rssi);
void Update_GUN1_Temp(uint16_t temp);
void Update_GUN2_Temp(uint16_t temp);
void Update_MCU_FW_VERSION(uint8_t data1,uint8_t data2,uint8_t data3,uint8_t data4,uint8_t data5,uint8_t data6);
void Update_OCPP_FW_VERSION(uint8_t data1,uint8_t data2,uint8_t data3,uint8_t data4,uint8_t data5,uint8_t data6);
void Update_PLC1_FW_VERSION(uint8_t data1,uint8_t data2,uint8_t data3,uint8_t data4,uint8_t data5,uint8_t data6);
void Update_PLC2_FW_VERSION(uint8_t data1,uint8_t data2,uint8_t data3,uint8_t data4,uint8_t data5,uint8_t data6);

void Update_Date_Time(uint16_t year,uint8_t month,uint8_t date,uint8_t hour,uint8_t minute,uint8_t sec);
void Update_OCPP_Symbol(uint8_t status);
void Update_Ethernet_status(uint8_t status);
void Update_GSM_Signal_Strength(uint8_t status);
void Update_GSM_Internet_Connectivity(uint8_t status);
void Update_Wifi_Status(uint8_t status);
void Update_Wifi_Availablity(uint8_t status);
void Update_Gun1_Status(uint8_t status);
void Update_Gun2_Status(uint8_t status);
void Update_Unit_price(uint16_t price);

void Update_GUN1_Battery_SOC(uint16_t SOC);
void Update_GUN1_Initial_SOC(uint16_t SOC);
void Update_GUN1_Duration(uint32_t duration);
void Update_GUN1_Demand_Voltage(uint32_t voltage);
void Update_GUN1_Demand_Current(uint32_t current);
void Update_GUN1_Voltage(uint32_t voltage);
void Update_GUN1_Current(uint32_t current);
void Update_GUN1_Total_Power(uint32_t power);
void Update_GUN1_Charging_Start_date(uint16_t date);
void Update_GUN1_Charging_Start_month(uint16_t month);
void Update_GUN1_Charging_Start_year(uint16_t year);
void Update_GUN1_Charging_Start_hour(uint16_t hour);
void Update_GUN1_Charging_Start_mins(uint16_t mins);
void Update_GUN1_Charging_Start_sec(uint16_t sec);
void Update_GUN1_Charging_Stop_date(uint16_t date);
void Update_GUN1_Charging_Stop_month(uint16_t month);
void Update_GUN1_Charging_Stop_year(uint16_t year);
void Update_GUN1_Charging_Stop_hour(uint16_t hour);
void Update_GUN1_Charging_Stop_mins(uint16_t mins);
void Update_GUN1_Charging_Stop_sec(uint16_t sec);
void Update_GUN1_Start_SOC(uint16_t SOC);
void Update_GUN1_End_SOC(uint16_t SOC);
void Update_GUN1_Uint_Consumed(uint32_t units);
void Update_GUN1_Booking_ID(uint32_t ID);
void Update_GUN1_Session_End_Reason(uint8_t reason);

void Update_GUN2_Battery_SOC(uint16_t SOC);
void Update_GUN2_Initial_SOC(uint16_t SOC);
void Update_GUN2_Duration(uint32_t duration);
void Update_GUN2_Demand_Voltage(uint32_t voltage);
void Update_GUN2_Demand_Current(uint32_t current);
void Update_GUN2_Voltage(uint32_t voltage);
void Update_GUN2_Current(uint32_t current);
void Update_GUN2_Total_Power(uint32_t power);
void Update_GUN2_Charging_Start_date(uint16_t date);
void Update_GUN2_Charging_Start_month(uint16_t month);
void Update_GUN2_Charging_Start_year(uint16_t year);
void Update_GUN2_Charging_Start_hour(uint16_t hour);
void Update_GUN2_Charging_Start_mins(uint16_t mins);
void Update_GUN2_Charging_Start_sec(uint16_t sec);
void Update_GUN2_Charging_Stop_date(uint16_t date);
void Update_GUN2_Charging_Stop_month(uint16_t month);
void Update_GUN2_Charging_Stop_year(uint16_t year);
void Update_GUN2_Charging_Stop_hour(uint16_t hour);
void Update_GUN2_Charging_Stop_mins(uint16_t mins);
void Update_GUN2_Charging_Stop_sec(uint16_t sec);
void Update_GUN2_Start_SOC(uint16_t SOC);
void Update_GUN2_End_SOC(uint16_t SOC);
void Update_GUN2_Uint_Consumed(uint32_t uints);
void Update_GUN2_Booking_ID(uint32_t ID);
void Update_GUN2_Session_End_Reason(uint8_t reason);


void Update_Mains_Fail_Status(uint8_t status);
void Update_High_Leakage_Current_Status(uint8_t status);
void Update_High_NE_Voltage_Status(uint8_t status);
void Update_Mains_Low_Status(uint8_t status);
void Update_Mains_High_Status(uint8_t status);
void Update_Smoke_Detected_Status(uint8_t status);
void Update_Esd_Pressed_Status(uint8_t status);
void Update_Spd_Fault_Status(uint8_t status);
void Update_ACEM_Comm_Fail_Status(uint8_t status);
void Update_System_Temperature_High_Status(uint8_t status);
void Update_All_Rectifier_Comm_Fail_Status(uint8_t status);
void Update_Rectifier1_Comm_Fail_Status(uint8_t status);
void Update_Rectifier2_Comm_Fail_Status(uint8_t status);
void Update_Rectifier3_Comm_Fail_Status(uint8_t status);
void Update_Rectifier4_Comm_Fail_Status(uint8_t status);
void Update_DCEM1_Comm_Fail_Status(uint8_t status);
void Update_DCEM2_Comm_Fail_Status(uint8_t status);
void Update_PLC1_Comm_Fail_Status(uint8_t status);
void Update_PLC2_Comm_Fail_Status(uint8_t status);
void Update_Door_Status(uint8_t status);
void Update_RFID_Comm_Fail_Status(uint8_t status);
void Update_Controller_Fail_Status(uint8_t status);
void Update_Isolation_Fail1_Status(uint8_t status);
void Update_Isolation_Fail2_Status(uint8_t status);
void Update_LED_Board_Fault1_Status(uint8_t status);
void Update_LED_Board_Fault2_Status(uint8_t status);
void Update_HMI_Comm_Fail_Status(uint8_t status);
void Update_Modem_Comm_Fail_Status(uint8_t status);
void Update_GUN1_Temp_High_Status(uint8_t status);
void Update_GUN2_Temp_High_Status(uint8_t status);
void Update_DC_Under_Volt2_Status(uint8_t status);
void Update_DC_Over_Volt2_Status(uint8_t status);
void Update_DC_Output_Over_Current2_Status(uint8_t status);
void Update_DC_Under_Volt1_Status(uint8_t status);
void Update_DC_Over_Volt1_Status(uint8_t status);
void Update_DC_Output_Over_Current1_Status(uint8_t status);
void Update_Rectifier1_Fault_Status(uint8_t status);
void Update_Rectifier2_Fault_Status(uint8_t status);
void Update_Rectifier3_Fault_Status(uint8_t status);
void Update_Rectifier4_Fault_Status(uint8_t status);



void Update_AC_VOLTAGE1(uint16_t volt);
void Update_AC_VOLTAGE2(uint16_t volt);
void Update_AC_VOLTAGE3(uint16_t volt);
void Update_AC_CURRENT1(uint16_t current);
void Update_AC_CURRENT2(uint16_t current);
void Update_AC_CURRENT3(uint16_t current);
void Update_AC_frequency(uint16_t frequency);

void Update_Rec1_temp(uint8_t temp);
void Update_Rec2_temp(uint8_t temp);
void Update_Rec1_status(uint8_t data[]);
void Update_Rec2_status(uint8_t data[]);
void Update_Rec3_status(uint8_t data[]);
void Update_Rec4_status(uint8_t data[]);

void Update_Gun1_stop_btn(void);
void Update_Gun2_stop_btn(void);