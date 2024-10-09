/* 
 * File:   definesmacro.h
 * Author: Amit
 *
 * Created on 23 January, 2024, 12:33 PM
 */

#ifndef DEFINESMACRO_H
#define	DEFINESMACRO_H

#ifdef	__cplusplus
extern "C" {
#endif



#define EVSE_PEAK_CURRENT_RIPPLE_DATA0    20
#define EVSE_PEAK_CURRENT_RIPPLE_DATA1     0

#define EVSE_MIN_CURRENT_DATA0         20
#define EVSE_MIN_CURRENT_DATA1          0

#define EVSE_MIN_VOLTAGE_DATA0         200
#define EVSE_MIN_VOLTAGE_DATA1          0

#define EVSE_PEAK_CURRENT_TOLERANCE_DATA0    20
#define EVSE_PEAK_CURRENT_TOLERANCE_DATA1     0

#define  EVSE_ENERGY_TO_DELIVERED_DATA0   100
#define  EVSE_ENERGY_TO_DELIVERED_DATA1   0

#define EVSE_MAX_VOLTAGE_DATA0   16
#define EVSE_MAX_VOLTAGE_DATA1    39
#define CHARGER_MAX_VOLT_LIMIT    ((EVSE_MAX_VOLTAGE_DATA1<<8)+EVSE_MAX_VOLTAGE_DATA0)/10    
#define CHARGER_MIN_VOLT_LIMIT  200

#define MAX_POWER_LIMIT 12
#define EVSE_MAX_CURRENT_LIMIT	990 


#define IDLE_STATE      0
#define PLUGIN_STATE    1 
#define CHARGING_STATE  2    
#define OK                      0
#define NOT_OK                  1
#define START_BIT 0xAAAAAAAA
#define STOP_BIT 0xBB    


#define RED                 0            //Define to state & write duty cycle to timer for red color. 
#define GREEN               1            //Define to state & write duty cycle to timer for green color. 
#define BLUE                2            //Define to state & write duty cycle to timer for blue color. 
#define YELLOW              3            //Define to state & write duty cycle to timer for yellow color. 
#define CYAN                4            //Define to state & write duty cycle to timer for cyan color. 
#define MAGENTA             5            //Define to state & write duty cycle to timer for magenta color. 
#define ORANGE              6            //Define to state & write duty cycle to timer for orange color. 
#define YELLOW_GREEN        7            //Define to state & write duty cycle to timer for yellow-green color. 
#define CYAN_GREEN          8            //Define to state & write duty cycle to timer for cyan-green color. 
#define CYAN_BLUE           9            //Define to state & write duty cycle to timer for cyan-blue color. 
#define BLUE_MAGENTA        10            //Define to state & write duty cycle to timer for blue-magenta color. 
#define RED_MAGENTA         11            //Define to state & write duty cycle to timer for red-magenta color. 
#define NO_COLOR         12            //Define to state & write duty cycle to timer for green blink color.
#define WHITE               13  
#define RED2                 14            //Define to state & write duty cycle to timer for red color. 
#define GREEN2               15            //Define to state & write duty cycle to timer for green color. 
#define BLUE2                16            //Define to state & write duty cycle to timer for blue color. 
#define YELLOW2              17           //Define to state & write duty cycle to timer for yellow color. 
#define CYAN2                18           //Define to state & write duty cycle to timer for cyan color. 
#define MAGENTA2             19           //Define to state & write duty cycle to timer for magenta color. 
#define ORANGE2              20            //Define to state & write duty cycle to timer for orange color. 
#define YELLOW_GREEN2        21           //Define to state & write duty cycle to timer for yellow-green color. 
#define CYAN_GREEN2          22           //Define to state & write duty cycle to timer for cyan-green color. 
#define CYAN_BLUE2           23           //Define to state & write duty cycle to timer for cyan-blue color. 
#define BLUE_MAGENTA2        24            //Define to state & write duty cycle to timer for blue-magenta color. 
#define RED_MAGENTA2         25            //Define to state & write duty cycle to timer for red-magenta color. 
#define NO_COLOR2         26            //Define to state & write duty cycle to timer for green blink color.
#define WHITE2               27  
#define ONLINE               1
#define OFFLINE              0

    char PHASE_OK[] = "PHASE_OK\r\n";
    char PHASE_NOT_OK[] = "PHASE NOT OK\r\n";
    char RGB1_ON[] = "RGB1_ON\r\n";
    char RGB2_ON[] = "RGB2_ON\r\n";
    char RGB1_OFF[] = "RGB1 OFF\r\n";
    char RGB2_OFF[] = "RGB2 OFF\r\n";
    char SPD_OK[] = "SPD OK\r\n";
    char SPD_NOT_OK[] = "SPD NOT OK\r\n";
    char GFCI_OK[] = "GFCI OK\r\n";
    char GFCI_NOT_OK[] = "GFCI NOT OK\r\n";
    char SMOKE_OK[] = "SMOKE NOT THERE\r\n";
    char SMOKE_NOT_OK[] = "SMOKE IS PRESENT\r\n";
    char EMERGENCY_OK[] = "EMERGENCY BUTTON OFF\r\n";
    char EMERGENCY_NOT_OK[] = "EMERGENCY_BUTTON_PRESSED/ON\r\n";
    char IMD1_OK[] = "IMD1 OK\r\n";
    char IMD1_NOT_OK[] = "IMD1 NOT OK\r\n";
    char IMD2_OK[] = "IMD2 OK\r\n";
    char IMD2_NOT_OK[] = "IMD2 NOT OK\r\n";
    char LIMIT_SW_OK[] = "GATE CLOSED\r\n";
    char LIMIT_SW_NOT_OK[] = "GATE OPEN\r\n";
    uint16_t SA_Agent = 19119;

#define RFID_WAKEUP_RX_SIZE     15
#define RFID_PRE_RX_SIZE         6
#define ID_RX_SIZE              19
#define RFID_ERROR_SIZE 1
#define RFID_DEFAULT_RX_SIZE    RFID_WAKEUP_RX_SIZE    
#define RFID_BUFFER_SIZE        50
#define RFID_INDEX9_DATA        0x0C
#define RFID_INDEX10_DATA       0xF4
#define RFID_INDEX11_DATA       0xD5
#define RFID_INDEX12_DATA       0x4B
#define RFID_INDEX13_DATA       0x01


#define MUX_DEVICE_ADR          0x70
#define SENSOR_DEVICE_ADR       0x44
#define DEVICE_DATA_LENGTH      1
#define TEMP_DATA_LENGTH        16
#define I2C_CHANNEL0            0
#define I2C_CHANNEL1            1    



#define RX_SIZE     1

#define GUN_NOT_CONNECTED   0x00
#define GUN_CONNECTED   0x01
#define GUN_CHARGING    0x02
#define GUN_SELECTION   0x03 

#define BY_REMOTE       0x02
#define BY_RFID         0x01 
#define BY_DE_AUTH      0x03    

#define ERROR_LENGTH 41   
#define MAIN_FAIL_IDX   0
#define SMOKE_DETECTED_IDX  1
#define ALL_RECTI_FAIL_IDX  2
#define ESD_PRESSED_IDX 3
#define PLC_COMM_FAIL_IDX   4
#define CONTROLLER_FAIL_IDX 5
#define SPD_FAULT_IDX   6
#define HIGH_LEAKAGE_IDX    7
#define HIGH_NE_IDX 8
#define MAINS_LOW_IDX   9
#define MAINS_HIGH_IDX  10
#define AC_METER_FAIL_IDX   11
#define RFID_COMM_FAIL_IDX  12
#define SYSTEM_TEMP_HIGH_IDX 13
#define GUN_TEMP_HIGH_IDX   14
#define ISOLATION_FAIL_IDX  15
#define LED_BOARD_FAIL_IDX  16
#define RECTIFIER1_COMM_FAIL_IDX    17 
#define RECTIFIER2_COMM_FAIL_IDX    18
#define DC_OVER_VOLTAGE_IDX 19
#define DC_UNDER_VOLT_IDX   20
#define DC_OVER_CURR_IDX    21
#define HMI_COMM_FAIL_IDX   22
#define MODEM_COMM_FAIL_IDX 23
#define DC_METER_COMM_FAIL_IDX  24
#define ALL_PLC_COMM_FAIL_IDX   25
#define ALL_DC_METER_FAIL_IDX   26
#define DOOR_OPEN_IDX       27
#define EV_SOC_100_STOP_IDX 28
#define SLAC_ERROR_IDX  29
#define AUTH_FAIL_IDX   30
#define CABLE_CHECK_FAIL_IDX    31 
#define PRE_CHARGE_FAIL_IDX     32 
#define PLC_COMM_FAIL_CONN_NO   33 
#define IMD_FAIL_CONN_NO    34 
#define DC_METER_COMM_FAIL_CONN_NO  35 
#define DC_OVER_CONN_NO 36
#define DC_UNDER_CONN_NO    37
#define DC_CURRENT_OVER_CONN_NO 38
#define REC_GROUP_CONN_NO     39 
#define GUN_TEMP_CONN_NO    40  
#define LED_CONN_NO 41  



#define GUN_TEMP_HIGH_IDX1 42
#define GUN_TEMP_HIGH_IDX2 43 
#define PLC_COMM_FAIL_IDX1   44 
#define PLC_COMM_FAIL_IDX2   45 
#define ISOLATION_FAIL_IDX1  46
#define ISOLATION_FAIL_IDX2  47 
#define LED_BOARD_FAIL_IDX1  48
#define LED_BOARD_FAIL_IDX2  49
#define RECTIFIER1_COMM_FAIL_IDX1    50 
#define RECTIFIER1_COMM_FAIL_IDX2    51  
#define RECTIFIER2_COMM_FAIL_IDX1    52
#define RECTIFIER2_COMM_FAIL_IDX2    53 
#define DC_OVER_VOLTAGE_IDX1 54
#define DC_OVER_VOLTAGE_IDX2 55
#define DC_UNDER_VOLT_IDX1   56
#define DC_UNDER_VOLT_IDX2   57 
#define DC_OVER_CURR_IDX1    58
#define DC_OVER_CURR_IDX2   59
#define DC_METER_COMM_FAIL_IDX1  60
#define DC_METER_COMM_FAIL_IDX2  61    



#define ENERGY_METER_RX_SIZE    85
#define AC_METER_1_IDT              1
#define AC_METER_2_IDT              2
#define DC_METER_1_IDT              3
#define DC_METER_2_IDT              4    
#define FW_IDT  5
#define CP_LEVEL_PLC1_IDT    6
#define CP_LEVEL_PLC2_IDT    18
#define ERROR_IDT   7
#define RFID_IDT      8  
#define SOC_IDT_PLC1 9  
#define SOC_IDT_PLC2 19  
#define GROUND_MONITOR_IDT 10       
#define BODY_TEMP_IDT   11
#define GUN_TEMP1_IDT    12
#define GUN_TEMP1_1_IDT    20
#define GUN_TEMP2_IDT    21
#define GUN_TEMP2_1_IDT    22
#define AUTO_CUT_IDT    13
#define THRESOLD_UV_IDT 14
#define THRESOLD_OV_IDT 15
#define THRESOLD_TR_IDT 16    
#define THRESOLD_NE_IDT 17   

    //BYTE 1 : AC, BYTE 2 : DC1, BYTE 3 : DC2, BYTE 4 : MERGER, BYTE 5 : POWER_BANK.
#define AC_CONTACTOR_POS    0    
#define DC1_CONTACTOR_POS   1
#define DC2_CONTACTOR_POS   2
#define MERGER_CONTACTOR_POS    3
#define POWER_BANK_RELAY_POS    4
#define RELAY_ON    1
#define RELAY_OFF   2
#define RECTIFIER_ON    1
#define RECTIFIER_OFF   0
#define CHARGING_COMPLETE	1
#define SIM_RX_SIZE             10

#define CONNECTOR_NO_0  0    
#define CONNECTOR_NO_1  1
#define CONNECTOR_NO_2  2   

#define RFID_DATA_FOR_ESP_SIZE  8
#define MAC_ID_DATA_SIZE_FOR_ESP    6    

    typedef struct {
        float CURRENT_VALUE[1];
        float VOLTAGE_VALUE[1];
        uint8_t RECTI_ON_OFF[1];
        uint8_t PLC_ID[1];
    } RECTIFIER_Q;

    typedef struct {
        uint8_t IDT;
        uint8_t Meter_data[170];
    } METER_Q_STRUCTURE;

    typedef struct {
        uint8_t Meter_data[170];
    } METER_DATA_Q;
    METER_DATA_Q meterrxdata;

    typedef struct {
        uint8_t Which_Meter_data[1];
    } WHICH_METER_Q;

    typedef struct {
        uint8_t NEXT_METER[1];
    } NEXT_METER_Q;

    typedef struct {
        uint8_t data[8];
        uint32_t ID;

    } CAN0_RECIEVE_Q;
    CAN0_RECIEVE_Q sendbuf;

    typedef struct {
        uint32_t ID_t;
        uint8_t DATA[8];
    } _50MS_Q;

    typedef struct {
        uint32_t ID_t;
        uint8_t DATA[8];
    } _200MS_Q;

    typedef struct {
        uint32_t ID_t;
        uint8_t DATA[8];
    } _500MS_Q;

    typedef struct {
        uint32_t ID_t;
        uint8_t DATA[8];
    } _1000MS_Q;

    typedef struct {
        uint8_t RELAY_DATA[8];
    } RELAY_Q;

    typedef struct {
        uint8_t hmi_buff[1];
    } HMI_INPUT_Q;
    HMI_INPUT_Q hmi_msg;

    typedef struct {
        uint8_t rfid_buff[1];
    } RFID_MSG_Q;
    RFID_MSG_Q rfid_msg;

    typedef struct {
        uint8_t rfid_count[1];
    } RFID_COUNT_Q;

    typedef struct {
        uint8_t rfid_data_complete[1];
    } RFID_DATA_COMPLETE_Q;
    RFID_DATA_COMPLETE_Q rfid_data_complete;

    typedef struct {
        uint8_t GUN;
    } LED1_Q;



    typedef struct {
        uint8_t CP_LEVEL1[1];
    } CP_LEVEL1_Q;

    typedef struct {
        uint8_t CP_LEVEL2[1];
    } CP_LEVEL2_Q;

    typedef union {
        uint8_t ESP_ARRAY[144];
        //        uint8_t ESP_ARRAY[160];

        struct {
            uint32_t Start_bit;
            uint32_t IDX_DATA;
            uint32_t FW_Version;
            uint32_t AC_VOLT_L1;
            uint32_t AC_VOLT_L2;
            uint32_t AC_VOLT_L3;
            uint32_t AC_CURRENT_L1;
            uint32_t AC_CURRENT_L2;
            uint32_t AC_CURRENT_L3;
            uint32_t AC_FREQUENCY;
            uint32_t DC1_VOLTAGE;
            uint32_t DC1_CURRENT;
            uint32_t DC2_VOLTAGE;
            uint32_t DC2_CURRENT;
            uint32_t DC1_IMPORT_ENERGY;
            uint32_t DC2_IMPORT_ENERGY;
            uint32_t DC1_POWER;
            uint32_t DC2_POWER;
            uint32_t AC_POWER;
            uint32_t AC_ENERGY;
            //1
            uint16_t Ground_Monitor_volt; //2
            uint16_t body_temp; //3
            uint16_t Gun_temp_1; //3
            uint16_t Gun_temp_1_1; //3
            uint16_t Gun_temp_2; //3
            uint16_t Gun_temp_2_1; //3
            uint16_t Stop_Code; //4
            uint16_t Error_Code0; //5
            uint16_t Error_Code1; //5
            uint16_t Error_Code2; //5
            uint16_t Warning_Code0; //5
            uint16_t Warning_Code1; //5
            uint16_t Warning_Code2; //5
            uint16_t Demand_Volatge1; //4
            uint16_t Demand_Volatge2; //4
            uint16_t Demand_Current1; //4
            uint16_t Demand_Current2; //4
            //            uint8_t Meter_data[84]; //6
            uint8_t MAC_ID[6]; //7
            //            uint8_t RFID_ID[4]; //8
            uint8_t RFID_ID[8]; //8
            uint8_t rfid_conn_no; //8
            uint8_t MAC_ID_CONN_NO; //7
            uint8_t SOC_1; //4
            uint8_t SOC_2; //4
            uint8_t Stop_connector_no; //4
            uint8_t CP_Level_1; //4
            uint8_t CP_Level_2; //4
            uint8_t Initial_SOC1; //4
            uint8_t Initial_SOC2; //4
            uint8_t Charge_history_bit;
            uint8_t OTP[4];
            uint8_t IDX;
            uint8_t Stop_bit;
        };
    } ESP_Q_DATA;

    typedef struct {
        uint16_t Ground_Monitor_volt;
    } ESP_S_GROUND_M_V_Q;

    typedef struct {
        uint8_t RFID_IS[8];
    } ESP_S_RFID_Q;

    typedef struct {
        uint8_t RFID_CONN_NO[1];
    } ESP_S_RFID_CONN_NO_Q;

    typedef struct {
        uint8_t MAC_ID_IS[6];
    } ESP_S_MAC_ID_Q;

    typedef struct {
        uint8_t MAC_ID_CONN_NO[1];
    } ESP_S_MAC_ID_CONN_NO_Q;

    typedef struct {
        uint16_t body_temp; //3
        uint16_t Gun_temp_1; //3
        uint16_t Gun_temp_1_1; //3
        uint16_t Gun_temp_2; //3
        uint16_t Gun_temp_2_1; //3
    } ESP_S_TEMP_Q;

    typedef struct {
        uint16_t Error_Code0; //5
        uint16_t Error_Code1; //5
        uint16_t Error_Code2; //5
        uint16_t Warning_Code0; //5
        uint16_t Warning_Code1; //5
        uint16_t Warning_Code2;
    } ESP_S_ERROR_W_Q;

    typedef struct {
        uint16_t Demand_Volatge1; //4
        uint16_t Demand_Current1; //4
        uint8_t SOC_1; //4
        uint8_t CP_Level_1; //4
        uint8_t Initial_SOC1; //4
    } ESP_S_GUN1_P_Q;

    typedef struct {
        uint16_t Demand_Volatge2; //4
        uint16_t Demand_Current2;
        uint8_t SOC_2; //4
        uint8_t CP_Level_2; //4
        uint8_t Initial_SOC2; //4
    } ESP_S_GUN2_P_Q;

    typedef struct {
        uint32_t AC_VOLT_L1;
        uint32_t AC_VOLT_L2;
        uint32_t AC_VOLT_L3;
        uint32_t AC_CURRENT_L1;
        uint32_t AC_CURRENT_L2;
        uint32_t AC_CURRENT_L3;
        uint32_t AC_FREQUENCY;
        uint32_t DC1_VOLTAGE;
        uint32_t DC1_CURRENT;
        uint32_t DC2_VOLTAGE;
        uint32_t DC2_CURRENT;
        uint32_t DC1_IMPORT_ENERGY;
        uint32_t DC2_IMPORT_ENERGY; //6
        uint32_t DC1_POWER;
        uint32_t DC2_POWER;
        uint32_t AC_POWER;
        uint32_t AC_ENERGY;
    } ESP_S_METER_D_Q;

    typedef struct {
        uint8_t IDX;
        uint32_t IDX_DATA;
    } ESP_S_BT_Q;

    typedef struct {
        uint8_t value[1];
    } GUN1_CHARGING_TIME_Q;

    typedef struct {
        uint8_t value[1];
    } GUN2_CHARGING_TIME_Q;



    //#define ESP_RX_SIZE             28
#define ESP_RX_SIZE             70    
#define OCPP_ID 1
#define BLE_ID  2   
#define VALUE_1 1

    typedef union {
        //        uint8_t DATA_ARRAY[28];
        uint8_t DATA_ARRAY[74];

        struct {
            uint32_t Start_bit : 32;
            uint32_t DATA_t : 32;
            uint32_t rssi : 32;
            uint32_t Booking_ID_1 : 32;
            uint32_t Booking_ID_2 : 32;
            uint8_t wifi_state : 8;
            uint8_t gsm_state : 8;
            uint8_t ethernet_state : 8;
            uint8_t server_connection : 8;
            uint8_t year : 8;
            uint8_t month : 8;
            uint8_t day : 8;
            uint8_t hour : 8;
            uint8_t minute : 8;
            uint8_t sec : 8;
            uint8_t auth_status : 8;
            uint8_t reserv_status : 8;
            uint8_t start_charge : 8;
            uint8_t start_connector : 8;
            uint8_t stop_charge : 8;
            uint8_t stop_connector : 8;
            uint8_t restart : 8;
            uint8_t bootloader : 8;
            uint8_t power_limit : 8;
            uint8_t limit_connector : 8;
            uint8_t BT_DATA_COMING : 8; //0-no data//1-data incoming//2-data out going
            uint8_t BT_DATA_IDX : 8;
            uint8_t ID_S[31];
            uint8_t Stop_bit : 8;
        };
    } ESP_RX_DATA;

    typedef struct {
        uint8_t ESP_DATA[1];
    } ESP_RX_Q;
    ESP_RX_Q esp_data;

    typedef struct {
        uint8_t COLOR1;
    } COLOR1_Q;

    typedef struct {
        uint8_t COLOR2;
    } COLOR2_Q;


    typedef struct {
        uint8_t data[8];
        uint32_t ID;

    } CAN1_RECIEVE_Q;
    CAN1_RECIEVE_Q sendbuf1;
        typedef struct {
        uint8_t data[8];
        uint32_t ID;

    } CAN2_RECIEVE_Q;
    CAN2_RECIEVE_Q sendbuf2;
#ifdef	__cplusplus
}
#endif

#endif	/* DEFINESMACRO_H */

