
#include <stddef.h>  // Defines NULL
#include <stdbool.h> // Defines true
#include <stdlib.h>  // Defines EXIT_FAILURE
#include "definitions.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "definesmacro.h"
#include "pwm_fan.h"
#include "string.h"
#include "stdio.h"
#include "PLC1.h"
#include "UUGreenRectifier.h"
#include "HMI_FOO.h"
#include "stdbool.h"
#include "peripheral/wdt/plib_wdt.h"
#include "flashdata.h"

uint8_t Can0MessageRAM[CAN0_MESSAGE_RAM_CONFIG_SIZE] __attribute__((address(0x20000010)));
uint8_t Can1MessageRAM[CAN1_MESSAGE_RAM_CONFIG_SIZE] __attribute__((address((0x20000010) + CAN0_MESSAGE_RAM_CONFIG_SIZE)));

TaskHandle_t defaultTaskHandle;
TaskHandle_t _50msecTask;
TaskHandle_t _200msecTask;
TaskHandle_t _500msecTask;
TaskHandle_t _1000msecTask;
TaskHandle_t RECTIFIER_TASKHandle;
TaskHandle_t _1_PLC_MANAGE_TASKHandle;
TaskHandle_t _2_PLC_MANAGE_TASKHandle;
TaskHandle_t ESP_SEND_TASKHandle;
TaskHandle_t RFID_SEND_TASKHandle;
TaskHandle_t ADC_TASKHandle;
TaskHandle_t RGB_SEND_TaskHandle;
TaskHandle_t I2c_TEMP_HUM_TASKHandle;
TaskHandle_t METER_RECEIVE_TaskHandle;
TaskHandle_t RFID_RX_TASKHandle;
TaskHandle_t ESP_RX_TASKHandle;
TaskHandle_t canrecievetask;
TaskHandle_t simulatortask;
TaskHandle_t HMI_RX_TASKHandle;
TaskHandle_t EMERGENCY_TASKHandle;
TaskHandle_t ERROR_CODE_TASKHandle;
TaskHandle_t SMOKE_LIMIT_TASKHandle;
TaskHandle_t MAINS_TASKHandle;
TaskHandle_t LED_TASKHandle;
TaskHandle_t GUN1_PARAM_TASKHandle;
TaskHandle_t GUN2_PARAM_TASKHandle;
TaskHandle_t HMI_SEND_TASKHandle;
TaskHandle_t FLASH_WRITE_TASKHandle;
TaskHandle_t FLASH_READ_TASKHandle;
TaskHandle_t DATA_POPULATE_TASKHandle;
TaskHandle_t AC_METER_SEND_TASKHandle;
TaskHandle_t DC1_METER_SEND_TASKHandle;
TaskHandle_t DC2_METER_SEND_TASKHandle;
TaskHandle_t FAN_TASKHandle;
QueueHandle_t GUN_DATAQUEUE = NULL;
QueueHandle_t METER_QUEUE = NULL;
QueueHandle_t ESP_QUEUE = NULL;
QueueHandle_t ESP_RX_QUEUE = NULL;
QueueHandle_t CAN0_QUEUE = NULL;
QueueHandle_t _50msQUEUE = NULL;
QueueHandle_t _200msQUEUE = NULL;
QueueHandle_t _500msQUEUE = NULL;
QueueHandle_t _1000msQUEUE = NULL;
QueueHandle_t _C101_QUEUE = NULL;
QueueHandle_t _C102_QUEUE = NULL;
QueueHandle_t _C103_QUEUE = NULL;
QueueHandle_t _C104_QUEUE = NULL;
QueueHandle_t _C105_QUEUE = NULL;
QueueHandle_t _C106_QUEUE = NULL;
QueueHandle_t _C107_QUEUE = NULL;
QueueHandle_t _C108_QUEUE = NULL;
QueueHandle_t _C109_QUEUE = NULL;
QueueHandle_t _C10A_QUEUE = NULL;
QueueHandle_t _C10B_QUEUE = NULL;
QueueHandle_t _C1FF_QUEUE = NULL;
QueueHandle_t _D101_QUEUE = NULL;
QueueHandle_t _C501_QUEUE = NULL;
QueueHandle_t _C502_QUEUE = NULL;
QueueHandle_t _C503_QUEUE = NULL;
QueueHandle_t _C504_QUEUE = NULL;
QueueHandle_t _C505_QUEUE = NULL;
QueueHandle_t _C506_QUEUE = NULL;
QueueHandle_t _C507_QUEUE = NULL;
QueueHandle_t _C508_QUEUE = NULL;
QueueHandle_t _C509_QUEUE = NULL;
QueueHandle_t _C50A_QUEUE = NULL;
QueueHandle_t _C50B_QUEUE = NULL;
QueueHandle_t _C5FF_QUEUE = NULL;
QueueHandle_t _D501_QUEUE = NULL;
QueueHandle_t RECTIFIER_QUEUE = NULL;
QueueHandle_t METER_DATA_QUEUE = NULL;
QueueHandle_t HMI_RX_QUEUE = NULL;
QueueHandle_t RFID_MSG_QUEUE = NULL;
QueueHandle_t RFID_COUNT_QUEUE = NULL;
QueueHandle_t LED1_QUEUE = NULL;
//QueueHandle_t LED2_QUEUE = NULL;
QueueHandle_t ESP_S_GROUND_M_V_QUEUE = NULL;
QueueHandle_t ESP_S_TEMP_QUEUE = NULL;
QueueHandle_t ESP_S_ERROR_W_QUEUE = NULL;
QueueHandle_t ESP_S_GUN1_P_QUEUE = NULL;
QueueHandle_t ESP_S_GUN2_P_QUEUE = NULL;
QueueHandle_t ESP_S_METER_D_QUEUE = NULL;
QueueHandle_t ESP_S_BT_QUEUE = NULL;
QueueHandle_t HMI_SEND_QUEUE = NULL;
QueueHandle_t FLASH_WRITE_QUEUE = NULL;
QueueHandle_t COLOR1_QUEUE = NULL;
QueueHandle_t COLOR2_QUEUE = NULL;
QueueHandle_t FLASH_READ_QUEUE = NULL;
QueueHandle_t CP_LEVEL1_QUEUE = NULL;
QueueHandle_t CP_LEVEL2_QUEUE = NULL;
QueueHandle_t RFID_DATA_COMPLETE_QUEUE = NULL;
QueueHandle_t ESP_S_RFID_QUEUE = NULL;
QueueHandle_t ESP_S_RFID_CONN_NO_QUEUE = NULL;
QueueHandle_t ESP_S_MAC_ID_QUEUE = NULL;
QueueHandle_t ESP_S_MAC_ID_CONN_NO_QUEUE = NULL;
QueueHandle_t WHICH_METER_QUEUE = NULL;
QueueHandle_t NEXT_METER_QUEUE = NULL;
QueueHandle_t GUN1_CHARGING_TIME_QUEUE = NULL;
QueueHandle_t GUN2_CHARGING_TIME_QUEUE = NULL;
QueueHandle_t REC_TEMP_QUEUE = NULL;
QueueHandle_t REC2_TEMP_QUEUE = NULL;
QueueHandle_t ESP_S_REC_TEMP_QUEUE = NULL;
QueueHandle_t RECTIFIERS_TEMP_QUEUE = NULL;




TimerHandle_t _50_sec_timer = NULL;
TimerHandle_t _200_sec_timer = NULL;
TimerHandle_t _500_sec_timer = NULL;
TimerHandle_t _1000_sec_timer = NULL;
TimerHandle_t merger_timer = NULL;
TimerHandle_t Gun1_Charging_timer = NULL;
TimerHandle_t Gun2_Charging_timer = NULL;
TimerHandle_t plc1_timer = NULL;
TimerHandle_t plc2_timer = NULL;
TimerHandle_t all_plc_timer = NULL;
TimerHandle_t live_mains_timer = NULL;
TimerHandle_t ac_timer = NULL;
TimerHandle_t dc1_timer = NULL;
TimerHandle_t dc2_timer = NULL;
TimerHandle_t rfid_timer = NULL;
TimerHandle_t hmi_timer = NULL;
TimerHandle_t modem_timer = NULL;
TimerHandle_t all_rec_timer = NULL;
TimerHandle_t rec1_timer = NULL;
TimerHandle_t rec2_timer = NULL;
TimerHandle_t rec3_timer = NULL;
TimerHandle_t rec4_timer = NULL;
TimerHandle_t rfiddata_timer = NULL;
TimerHandle_t meter_change_timer = NULL;
TimerHandle_t HMI_DATA_T = NULL;
TimerHandle_t esp_data_timer = NULL;
TimerHandle_t rfid_send_timer = NULL;
TimerHandle_t emergency_timer = NULL;


uint8_t RFID_DATA[RFID_BUFFER_SIZE] = {0};
volatile uint8_t CURRENT_RFID_RX_SIZE = RFID_WAKEUP_RX_SIZE;

float FIRMWARE_VERSION = 1.0;
float OCPP_VERSION = 1.6;
float PLC1_VERSION = 2.0;
float PLC2_VERSION = 2.0;

void StartDefaultTask(void *argument);
void Start_50msecTask(void *argument);
void Start_200msecTask(void *argument);
void Start_500msecTask(void *argument);
void Start_1000msecTask(void *argument);
void Start_RECTIFIER_TASK(void *argument);
void Start_1_PLC_MANAGE_TASK(void *argument);
void Start_2_PLC_MANAGE_TASK(void *argument);
void Start_ESP_SEND_TASK(void *argument);
void Start_RFID_SEND_TASk(void *argument);
void Start_ADC_TASK(void *argument);
void Start_RGB_SEND_TASK(void *argument);
void Start_I2C_TMP_HUM_TASK(void *argument);
void Start_METER_RX_TASK(void *arggument);
void Start_RFID_RX_TASK(void *argument);
void Start_ESP_RX_TASK(void *argument);
void StartCANrecieveTask(void *argument);
void Start_SIMULATOR_TASK(void *argument);
void Start_HMI_RX_TASK(void *argument);
void Start_HMI_TX_TASK(void *arggument);
void Start_EMERGENCY_TASK(void *argument);
void Start_ERROR_CODE_TASK(void *argument);
void Start_SMOKE_LIMIT_TASK(void *argument);
void Start_MAINS_TASK(void *argument);
void Start_LED_TASK(void *argument);
void Start_GUN1_PARAM_TASK(void *argument);
void Start_GUN2_PARAM_TASK(void *argument);
void Start_FLASH_WRITE_TASK(void *argument);
void Start_FLASH_READ_TASK(void *argument);
void Start_DATA_POPULATE_TASK(void *argument);
void Start_AC_METER_SEND_TASK(void *argument);
void Start_DC1_METER_SEND_TASK(void *argument);
void Start_DC2_METER_SEND_TASK(void *argument);
void Start_FAN_TASK(void *argument);

char bootloader_done[] = {"Application run after recieving command through bootloader done....\r\n"};
#define BTL_TRIGGER_PATTERN (0x5048434DUL)
#define BTL_TRIGGER_RAM_START  0x20000000U
static uint32_t *ramStart = (uint32_t *) BTL_TRIGGER_RAM_START;

static uint8_t GUN1_ENABLE_DISABLE = DEFAULT_GUN1_ENABLE;
static uint8_t GUN2_ENABLE_DISABLE = DEFAULT_GUN2_ENABLE;
static uint8_t DEFAULT_BODY_TEMP_UPPER_LIMIT_t = DEFAULT_BODY_TEMP_UPPER_LIMIT;
static uint8_t DEFAULT_BODY_TEMP_CLEAR_LIMIT_t = DEFAULT_BODY_TEMP_CLEAR_LIMIT;
static uint8_t DEFAULT_NE_VOLT_LIMIT_t = DEFAULT_NE_VOLT_LIMIT;
static uint16_t AC_OVER_VOLT_LIMIT_t = DEFAULT_AC_OVER_VOLT_LIMIT;
static uint16_t AC_UNDER_VOLT_LIMIT_t = DEFAULT_AC_UNDER_VOLT_LIMIT;
static uint8_t DEFAULT_GUN1_TEMP_LIMIT_t = DEFAULT_GUN1_TEMP_LIMIT;
static uint8_t DEFAULT_GUN2_TEMP_LIMIT_t = DEFAULT_GUN2_TEMP_LIMIT;
static uint8_t DEFAULT_GUN_TEMPERATURE_POINT_CLEAR_VALUE_t = DEFAULT_GUN_TEMPERATURE_POINT_CLEAR_VALUE;
static uint8_t DEFAULT_CHARGER_TYPE_t = DEFAULT_CHARGER_TYPE;
static uint8_t DEFAULT_ACEM_ALARM_t = DEFAULT_ACEM_ALARM;
static uint8_t DEFAULT_DCEM_GUN1_ALARM_t = DEFAULT_DCEM_GUN1_ALARM;
static uint8_t DEFAULT_DCEM_GUN2_ALARM_t = DEFAULT_DCEM_GUN2_ALARM;
static uint8_t DEFAULT_IMD1_ALARM_t = DEFAULT_IMD1_ALARM;
static uint8_t DEFAULT_IMD2_ALARM_t = DEFAULT_IMD2_ALARM;
static uint8_t DEFAULT_DOOR_ALARM_t = DEFAULT_DOOR_ALARM;
static uint8_t DEFAULT_SPD_ALARM_t = DEFALUT_SPD_ALARM;
static uint8_t DEFAULT_SMOKE_ALARM_t = DEFAULT_SMOKE_ALARM;
static uint8_t DEFAULT_GUN1_TEMP_ALARM_t = DEFAULT_GUN1_TEMP_ALARM;
static uint8_t DEFAULT_GUN2_TEMP_ALARM_t = DEFAULT_GUN2_TEMP_ALARM;
static uint8_t DEFAULT_LED_FAULT_ALARM_t = DEFAULT_LED_FAULT_ALARM;
static uint8_t DEFAULT_RFID_FAULT_ALARM_t = DEFAULT_RFID_FAULT_ALARM;
static uint8_t DEFAULT_AC_METER_t = DEFAULT_AC_METER_TYPE;
static uint8_t NO_OF_RECTIFIER = 4;
volatile uint8_t MACHINE_STATE = IDLE_STATE;
uint8_t em_rx_buff[170] = {0};
uint8_t ESP_RX_DATA_t[1] = {0};
uint8_t ESP_REC_DATA[ESP_RX_SIZE] = {0};
static uint8_t power_down = 0;
static uint8_t txFiFo[CAN0_TX_FIFO_BUFFER_SIZE];
static uint8_t rxFiFo0[CAN0_RX_FIFO0_SIZE];
static uint8_t rxFiFo1[CAN1_RX_FIFO1_SIZE];
static uint8_t heartbeat = 0;
CAN_TX_BUFFER *txBuffer = NULL;
static CAN_RX_BUFFER *rxBuf = NULL;
static CAN_RX_BUFFER *rxBuf1 = NULL;
volatile uint8_t CURRENT_PLC1_STATE = _1_PLC_STATE_IDLE_1;
volatile uint8_t CURRENT_PLC2_STATE = _2_PLC_STATE_IDLE_1;
volatile float POWER_VALUE = 0;
volatile float POWER_VALUE_X = (MAX_POWER_LIMIT * 10000);
volatile float POWER_VALUE_X1 = 0;
volatile float POWER_VALUE_X2 = 0;
volatile uint8_t SINGLE_GUN1_POWER = 0;
volatile uint8_t SINGLE_GUN2_POWER = 0;
volatile uint8_t GUN1_CONNECTED = 0;
volatile uint8_t GUN2_CONNECTED = 0;
char Simulator_buff[10] = {0};
static uint8_t GUN1_50_clear = 0, GUN1_200_clear = 0, GUN1_500_clear = 0, GUN1_1000_clear = 0, GUN2_50_clear = 0, GUN2_200_clear = 0, GUN2_500_clear = 0, GUN2_1000_clear = 0;
uint8_t GUN2_summary_close_flag = 0, GUN1_summary_close_flag = 0;
uint8_t OTP[4] = {0};
char bufferr[] = "INTERRUPTED\r\n";
uint8_t hmi_rx[1] = {0};
uint8_t rfid_rx[1] = {0};
volatile int ERROR_CODE_ARRAY[ERROR_LENGTH] = {0};
int ikf;
float act_volt_1 = 200, act_volt_2 = 200;
static uint8_t RFID_ID_RECEIVED[4] = {0};
uint8_t START_STOP_AR[3] = {0};
uint8_t START_STOP_AR1[3] = {0};
volatile uint8_t MAINS_HIGH = 0;
volatile uint8_t MAINS_LOW = 0;
volatile uint8_t plc1_fail = 0;
volatile uint8_t plc2_fail = 0;
volatile uint8_t all_plc_count = 0;
volatile uint8_t all_plc_state = 0;
volatile uint8_t ac_meter_comm = 0;
volatile uint8_t dc1_meter_comm = 0;
volatile uint8_t dc2_meter_comm = 0;
volatile uint8_t plc1_fail_inst = 0;
volatile uint8_t plc2_fail_inst = 0;
volatile float MAX_CURR_LIMIT1 = 0;
volatile float MAX_CURR_LIMIT2 = 0;
volatile uint8_t rec1_status = 0;
volatile uint8_t rec2_status = 0;
volatile uint8_t rec3_status = 0;
volatile uint8_t rec4_status = 0;
volatile uint8_t all_rec_status = 0;
volatile uint8_t STOP_BY = 0;
volatile uint8_t START_BY1 = 0;
volatile uint8_t START_BY2 = 0;
volatile uint16_t Stop_Code = 0;
volatile uint8_t Stop_connector_no = 0;
volatile uint32_t BOOKING_ID1 = 0;
volatile uint32_t BOOKING_ID2 = 0;
volatile uint16_t year = 0;
volatile uint8_t month = 0;
volatile uint8_t day = 0;
volatile uint8_t hour = 0;
volatile uint8_t minute = 0;
volatile uint8_t sec = 0;
volatile uint8_t CURRENT_PAGE = INTRO_PAGE;
volatile float IMPORT_ENERGY1 = 0, IMPORT_ENERGY2 = 0;
volatile uint8_t page_change[3] = {0};
volatile uint8_t mains_count = 0;
volatile uint8_t can_instance = 0;
char buffffff[250] = {0};
static uint8_t hmi_data_flag = 0;
static uint8_t esp_data_flag = 0;
static uint8_t rfid_count = 0;
static uint8_t mains_fail_led = 0;
static uint8_t CHARGER_LINK[] = {0x5A, 0xA5, 0x1B, 0x82, 0x52, 0x40, 0x68, 0x74, 0x74, 0x70, 0x73, 0x3A, 0x2F, 0x2F, 0x77, 0x77, 0x77, 0x2E, 0x73, 0x74, 0x61, 0x74, 0x69, 0x71, 0x2E, 0x69, 0x6E, 0x2F, 0xFF, 0xFF};
BaseType_t rfidxYieldRequired, meterxYieldRequired, hmixYieldRequired, espxYieldRequired;

void ENERGY_METER_CALLBACK(uintptr_t context) {
    meterxYieldRequired = xTaskResumeFromISR(METER_RECEIVE_TaskHandle);
    memcpy(meterrxdata.Meter_data, em_rx_buff, sizeof (meterrxdata.Meter_data));
    xQueueSendFromISR(METER_DATA_QUEUE, &meterrxdata, &meterxYieldRequired);
    portYIELD_FROM_ISR(meterxYieldRequired);
    vTaskResume(METER_RECEIVE_TaskHandle);
}

void RFID_CALLBACK(uintptr_t context) {
    //    xTimerStop(rfid_timer, 10);
    //    rfid_msg.rfid_buff[0] = rfid_rx[0];
    //    rfidxYieldRequired = xTaskResumeFromISR(RFID_RX_TASKHandle);
    //    xQueueSendFromISR(RFID_MSG_QUEUE, &rfid_msg, &rfidxYieldRequired);
    //    SERCOM4_USART_Read(rfid_rx, 1);
    //    portYIELD_FROM_ISR(rfidxYieldRequired);
    vTaskResume(RFID_RX_TASKHandle);
}

void HMI_CALLBACK(uintptr_t context) {
    ERROR_CODE_ARRAY[HMI_COMM_FAIL_IDX] = 0;
    xTimerStop(hmi_timer, 10);
    memcpy(hmi_msg.hmi_buff, hmi_rx, sizeof (hmi_rx));
    hmixYieldRequired = xTaskResumeFromISR(HMI_RX_TASKHandle);
    xQueueSendFromISR(HMI_RX_QUEUE, &hmi_msg, &hmixYieldRequired);
    SERCOM6_USART_Read(&hmi_rx, RX_SIZE);
    portYIELD_FROM_ISR(hmixYieldRequired);
}

void ESP_CALLBACK(uintptr_t context) {
    //    if (ESP_RX_DATA_t[0] == 0xAA && ESP_RX_DATA_t[1] == 0xAA && ESP_RX_DATA_t[2] == 0xAA && ESP_RX_DATA_t[3] == 0xAA && ESP_RX_DATA_t[69] == 0xBB) {
    //        memcpy(ESP_REC_DATA, ESP_RX_DATA_t, ESP_RX_SIZE);
    //        SERCOM7_USART_Read(ESP_RX_DATA_t, ESP_RX_SIZE);
    //        vTaskResume(ESP_RX_TASKHandle);
    //    } else {
    //        SERCOM7_USART_Read(ESP_RX_DATA_t, ESP_RX_SIZE);
    //    }
    esp_data.ESP_DATA[0] = ESP_RX_DATA_t[0];
    espxYieldRequired = xTaskResumeFromISR(ESP_RX_TASKHandle);
    xQueueSendFromISR(ESP_RX_QUEUE, &esp_data, &espxYieldRequired);
    SERCOM7_USART_Read(ESP_RX_DATA_t, 1);
    portYIELD_FROM_ISR(espxYieldRequired);
}

float map(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void APP_CAN_RxFifo0Callback(uint8_t numberOfMessage, uintptr_t context) {
    all_plc_state = 0;
    xTimerStart(all_plc_timer, 60000);
    if (can_instance == 0) {
        MACHINE_STATE = IDLE_STATE;
        can_instance = 1;
    }
    memset(rxFiFo0, 0x00, (CAN0_RX_FIFO0_ELEMENT_SIZE));
    CAN0_MessageReceiveFifo(CAN_RX_FIFO_0, 1, (CAN_RX_BUFFER *) rxFiFo0);
    rxBuf = (CAN_RX_BUFFER *) rxFiFo0;
    sendbuf.ID = rxBuf->id;
    memcpy((sendbuf.data), (rxBuf->data), rxBuf->dlc);
    BaseType_t xYieldRequired;
    xYieldRequired = xTaskResumeFromISR(canrecievetask);
    xQueueSendFromISR(CAN0_QUEUE, &sendbuf, &xYieldRequired);
    portYIELD_FROM_ISR(xYieldRequired);
}
static uint32_t rect_address = 0;

void APP_CAN_RxFifo1Callback(uint8_t numberOfMessage, uintptr_t context) {
    all_rec_status = 1;
    BaseType_t xYieldRequired;

    memset(rxFiFo1, 0x00, (1 * CAN1_RX_FIFO0_ELEMENT_SIZE));
    CAN1_MessageReceiveFifo(CAN_RX_FIFO_1, 1, (CAN_RX_BUFFER *) rxFiFo1);
    rxBuf1 = (CAN_RX_BUFFER *) rxFiFo1;
    rect_address = (rxBuf1->id >> 16);
    if (rect_address == Shift_rectifier_address1) {
        rec1_status = 1;
    }
    if (rect_address == Shift_rectifier_address2) {
        rec2_status = 1;
    }
    if (rect_address == Shift_rectifier_address3) {
        rec3_status = 1;
    }
    if (rect_address == Shift_rectifier_address4) {
        rec4_status = 1;
    }
    if ((rect_address == Shift_rectifier_address1) || (rect_address == Shift_rectifier_address2)) {
        if ((rxBuf1->data[0] == 0x13) && rxBuf1->data[1] == 0x1E) {
            sendbuf1.ID = rect_address;

            memcpy(sendbuf1.data, (rxBuf1->data), rxBuf1->dlc);
            xYieldRequired = xTaskResumeFromISR(SMOKE_LIMIT_TASKHandle);
            xQueueSendFromISR(REC_TEMP_QUEUE, &sendbuf1, &xYieldRequired);
            portYIELD_FROM_ISR(xYieldRequired);
        }
    }
    if ((rect_address == Shift_rectifier_address3) || (rect_address == Shift_rectifier_address4)) {
        if ((rxBuf1->data[0] == 0x23) && rxBuf1->data[1] == 0x1E) {
            sendbuf2.ID = rect_address;

            memcpy(sendbuf2.data, (rxBuf1->data), rxBuf1->dlc);
            xYieldRequired = xTaskResumeFromISR(SMOKE_LIMIT_TASKHandle);
            xQueueSendFromISR(REC2_TEMP_QUEUE, &sendbuf2, &xYieldRequired);
            portYIELD_FROM_ISR(xYieldRequired);
        }
    }
}

void all_rec_Callback(TimerHandle_t xTimer) {
    if (((CURRENT_PLC1_STATE == _1_PLC_STATE_CURRENT_DEMAND_1)) || ((CURRENT_PLC2_STATE == _2_PLC_STATE_CURRENT_DEMAND_1))) {
        ERROR_CODE_ARRAY[ALL_RECTI_FAIL_IDX] = 104;
        Update_All_Rectifier_Comm_Fail_Status(0x01);
    }
}

void rec1_Callback(TimerHandle_t xTimer) {
    if ((CURRENT_PLC1_STATE == _1_PLC_STATE_CURRENT_DEMAND_1)) {
        ERROR_CODE_ARRAY[RECTIFIER1_COMM_FAIL_IDX] = 124;
        ERROR_CODE_ARRAY[REC_GROUP_CONN_NO] = 1;
        Update_Rectifier1_Comm_Fail_Status(0x01);
    }
}

void rec2_Callback(TimerHandle_t xTimer) {
    if ((CURRENT_PLC1_STATE == _1_PLC_STATE_CURRENT_DEMAND_1)) {
        ERROR_CODE_ARRAY[RECTIFIER1_COMM_FAIL_IDX] = 124;
        ERROR_CODE_ARRAY[REC_GROUP_CONN_NO] = 2;
        Update_Rectifier2_Comm_Fail_Status(0x01);
    }
}

void rec3_Callback(TimerHandle_t xTimer) {
    if ((CURRENT_PLC2_STATE == _2_PLC_STATE_CURRENT_DEMAND_1)) {
        ERROR_CODE_ARRAY[RECTIFIER2_COMM_FAIL_IDX] = 125;
        ERROR_CODE_ARRAY[REC_GROUP_CONN_NO] = 1;
        Update_Rectifier3_Comm_Fail_Status(0x01);
    }
}

void rec4_Callback(TimerHandle_t xTimer) {
    if ((CURRENT_PLC2_STATE <= _2_PLC_STATE_CURRENT_DEMAND_1)) {
        ERROR_CODE_ARRAY[RECTIFIER2_COMM_FAIL_IDX] = 125;
        ERROR_CODE_ARRAY[REC_GROUP_CONN_NO] = 2;
        Update_Rectifier4_Comm_Fail_Status(0x01);
    }
}

void MainsCallback(TimerHandle_t xTimer) {
    mains_count++;
    Update_Mains_Fail_Status(0x01);
    power_down = 1;
    mains_fail_led = 1;
    START_STOP_AR[0] = 3;
    ERROR_CODE_ARRAY[MAIN_FAIL_IDX] = 101;
    CURRENT_PAGE = MAINS_FAIL_PAGE;
    Change_Page_to(CURRENT_PAGE);
    vTaskResume(EMERGENCY_TASKHandle);
    if (mains_count < 4) {
        xTimerStart(live_mains_timer, 30000);
    }
}

void RGB1_CALLBACK(uintptr_t context) {
    MACHINE_STATE = IDLE_STATE;
}

void RGB2_CALLBACK(uintptr_t context) {
    MACHINE_STATE = IDLE_STATE;
}

void EMERGENCY_BUTTON_CALLBACK(uintptr_t context) {
    xTimerStart(emergency_timer, 2000);
}

void GFCI_CALLBACK(uintptr_t context) {
    xTimerStart(emergency_timer, 2000);
}

/**CALLBACK FUNCTION FOR SPD**/
void SPD_DETECTION(uintptr_t context) {
    xTimerStart(emergency_timer, 2000);
}

void IMD1_CALLBACK(uintptr_t context) {
    xTimerStart(emergency_timer, 2000);
}

void IMD2_CALLBACK(uintptr_t context) {
    xTimerStart(emergency_timer, 2000);
}

void EMERGENCY_TIMER_CALL(TimerHandle_t xTimer) {
    MACHINE_STATE = IDLE_STATE;
}

void merger_callback(TimerHandle_t xTimer) {
    MERGER_Contactor_Clear();
}

void SIMULATOR_CALLBACK(uintptr_t context) {
    SERCOM5_USART_Read(Simulator_buff, SIM_RX_SIZE);
    vTaskResume(simulatortask);
}

void _50secCallback(TimerHandle_t xTimer) {

    vTaskResume(_50msecTask);
}

void _200secCallback(TimerHandle_t xTimer) {

    vTaskResume(_200msecTask);
}

void _500secCallback(TimerHandle_t xTimer) {

    vTaskResume(_500msecTask);
}

void _1000secCallback(TimerHandle_t xTimer) {
    xTimerStart(plc1_timer, 60000);
    xTimerStart(plc2_timer, 60000);
    vTaskResume(_1000msecTask);
}
char buff[40] = {0};

void Gun1_charge_timerCALLBACK(TimerHandle_t xTimer) {
    GUN1_CHARGING_TIME_Q value;
    value.value[0] = VALUE_1;
    xQueueOverwrite(GUN1_CHARGING_TIME_QUEUE, &value);
    xTimerStart(Gun1_Charging_timer, 60000);
}
char bufff[40] = {0};

void Gun2_charge_timerCALLBACK(TimerHandle_t xTimer) {
    GUN2_CHARGING_TIME_Q value;
    value.value[0] = VALUE_1;
    xQueueOverwrite(GUN2_CHARGING_TIME_QUEUE, &value);
    xTimerStart(Gun2_Charging_timer, 60000);
}

void plc1_Callback(TimerHandle_t xTimer) {
    plc1_fail = 1;
    MACHINE_STATE = IDLE_STATE;
    plc1_fail_inst = 0;
}

void plc2_Callback(TimerHandle_t xTimer) {
    plc2_fail = 1;
    MACHINE_STATE = IDLE_STATE;
    plc2_fail_inst = 0;
}

void all_plc_Callback(TimerHandle_t xTimer) {
    if (all_plc_count == 0) {
        all_plc_count = all_plc_count + 1;
        xTimerStart(all_plc_timer, 60000);
    }
    if (all_plc_count) {
        all_plc_state = 1;
        MACHINE_STATE = IDLE_STATE;
        can_instance = 0;
    }
}

void ac_Callback(TimerHandle_t xTimer) {
    ac_meter_comm = 1;
    MACHINE_STATE = IDLE_STATE;
}

void dc1_Callback(TimerHandle_t xTimer) {
    dc1_meter_comm = 1;
    MACHINE_STATE = IDLE_STATE;
}

void dc2_Callback(TimerHandle_t xTimer) {
    dc2_meter_comm = 1;
    MACHINE_STATE = IDLE_STATE;
}

void rfid_timer_Callback(TimerHandle_t xTimer) {
    ERROR_CODE_ARRAY[RFID_COMM_FAIL_IDX] = 114;
    Update_RFID_Comm_Fail_Status(0x01);
    CURRENT_PAGE = RFID_UNAVAILABLE_PAGE;
    Change_Page_to(CURRENT_PAGE);
    page_change[1] = 1;
    xTimerStart(rfid_timer, 40000);
}

void hmi_timer_Callback(TimerHandle_t xTimer) {
    ERROR_CODE_ARRAY[HMI_COMM_FAIL_IDX] = 131;

}

void modem_timer_Callback(TimerHandle_t xTimer) {
    Update_Modem_Comm_Fail_Status(0x01);
    xTimerStart(modem_timer, 40000);
}

void rfiddata_Callback(TimerHandle_t xTimer) {
    Update_RFID_Comm_Fail_Status(0x00);
    rfid_data_complete.rfid_data_complete[0] = 1;
    xQueueOverwrite(RFID_DATA_COMPLETE_QUEUE, &rfid_data_complete);
}

void meter_change_Callback(TimerHandle_t xTimer) {
    NEXT_METER_Q next_meter;
    if (xQueueReceive(NEXT_METER_QUEUE, &next_meter, 0)) {
        switch (next_meter.NEXT_METER[0]) {
            case AC_METER_1_IDT:
                vTaskResume(AC_METER_SEND_TASKHandle);
                break;
            case AC_METER_2_IDT:
                vTaskResume(AC_METER_SEND_TASKHandle);
                break;
            case DC_METER_1_IDT:
                vTaskResume(DC1_METER_SEND_TASKHandle);
                break;
            case DC_METER_2_IDT:
                vTaskResume(DC2_METER_SEND_TASKHandle);
                break;
        }
    }
}

void hmi_data_timercall(TimerHandle_t xTimer) {
    hmi_data_flag = 1;
}

void esp_data_callback(TimerHandle_t xTimer) {
    esp_data_flag = 1;
}

void rfid_send_callback(TimerHandle_t xTimer) {
    rfid_count = 0;
    vTaskResume(RFID_SEND_TASKHandle);
}

unsigned char CRC16_modbus(uint8_t *data, unsigned int dataLength, char check) // CRC 16 for modbus checksum
{
    unsigned int CheckSum, j, i;
    unsigned int highCRC, lowCRC;
    CheckSum = 0xffff;
    for (j = 0; j < dataLength; j++) {
        CheckSum = CheckSum ^ (unsigned int) data[j];
        for (i = 8; i > 0; i--)
            if ((CheckSum) & 0x0001)
                CheckSum = (CheckSum >> 1) ^ 0xa001;
            else
                CheckSum >>= 1;
    }
    highCRC = (uint8_t) (CheckSum >> 8);
    CheckSum <<= 8;
    lowCRC = (uint8_t) (CheckSum >> 8);
    if (check == 1) {
        if ((data[dataLength + 1] == highCRC) & (data[dataLength] == lowCRC))
            return 1;
        else
            return 0;
    } else {
        data[dataLength] = lowCRC;
        data[dataLength + 1] = highCRC;
        return 1;
    }
}

int main(void) {

    SYS_Initialize(NULL);
    //    WDT_Disable();
    CAN0_MessageRAMConfigSet(Can0MessageRAM);
    CAN1_MessageRAMConfigSet(Can1MessageRAM);

    METER_QUEUE = xQueueCreate(4, sizeof (METER_Q_STRUCTURE));
    METER_DATA_QUEUE = xQueueCreate(1, sizeof (METER_DATA_Q));
    ESP_QUEUE = xQueueCreate(1, sizeof (ESP_Q_DATA));
    ESP_RX_QUEUE = xQueueCreate(80, sizeof (ESP_RX_Q));
    LED1_QUEUE = xQueueCreate(1, sizeof (LED1_Q));
    //    LED2_QUEUE = xQueueCreate(1, sizeof (LED2_Q));
    CAN0_QUEUE = xQueueCreate(20, sizeof (CAN0_RECIEVE_Q));
    _50msQUEUE = xQueueCreate(5, sizeof (_50MS_Q));
    _200msQUEUE = xQueueCreate(5, sizeof (_200MS_Q));
    _500msQUEUE = xQueueCreate(5, sizeof (_500MS_Q));
    _1000msQUEUE = xQueueCreate(5, sizeof (_1000MS_Q));
    _C101_QUEUE = xQueueCreate(1, sizeof (_C101_Q));
    _C102_QUEUE = xQueueCreate(1, sizeof (_C102_Q));
    _C103_QUEUE = xQueueCreate(1, sizeof (_C103_Q));
    _C104_QUEUE = xQueueCreate(1, sizeof (_C104_Q));
    _C105_QUEUE = xQueueCreate(1, sizeof (_C105_Q));
    _C106_QUEUE = xQueueCreate(1, sizeof (_C106_Q));
    _C107_QUEUE = xQueueCreate(1, sizeof (_C107_Q));
    _C108_QUEUE = xQueueCreate(1, sizeof (_C108_Q));
    _C109_QUEUE = xQueueCreate(1, sizeof (_C109_Q));
    _C10A_QUEUE = xQueueCreate(1, sizeof (_C10A_Q));
    _C10B_QUEUE = xQueueCreate(1, sizeof (_C10B_Q));
    _C1FF_QUEUE = xQueueCreate(1, sizeof (_C1FF_Q));
    _D101_QUEUE = xQueueCreate(1, sizeof (_D101_Q));
    _C501_QUEUE = xQueueCreate(1, sizeof (_C501_Q));
    _C502_QUEUE = xQueueCreate(1, sizeof (_C502_Q));
    _C503_QUEUE = xQueueCreate(1, sizeof (_C503_Q));
    _C504_QUEUE = xQueueCreate(1, sizeof (_C504_Q));
    _C505_QUEUE = xQueueCreate(1, sizeof (_C505_Q));
    _C506_QUEUE = xQueueCreate(1, sizeof (_C506_Q));
    _C507_QUEUE = xQueueCreate(1, sizeof (_C507_Q));
    _C508_QUEUE = xQueueCreate(1, sizeof (_C508_Q));
    _C509_QUEUE = xQueueCreate(1, sizeof (_C509_Q));
    _C50A_QUEUE = xQueueCreate(1, sizeof (_C50A_Q));
    _C50B_QUEUE = xQueueCreate(1, sizeof (_C50B_Q));
    _C5FF_QUEUE = xQueueCreate(1, sizeof (_C5FF_Q));
    _D501_QUEUE = xQueueCreate(1, sizeof (_D501_Q));
    RECTIFIER_QUEUE = xQueueCreate(5, sizeof (RECTIFIER_Q));
    HMI_RX_QUEUE = xQueueCreate(30, sizeof (HMI_INPUT_Q));
    RFID_MSG_QUEUE = xQueueCreate(30, sizeof (RFID_MSG_Q));
    RFID_COUNT_QUEUE = xQueueCreate(1, sizeof (RFID_COUNT_Q));
    HMI_SEND_QUEUE = xQueueCreate(30, sizeof (HMI_SEND_DATA_Q));
    FLASH_WRITE_QUEUE = xQueueCreate(5, sizeof (FLASH_WRITE_Q));
    COLOR1_QUEUE = xQueueCreate(1, sizeof (COLOR1_Q));
    COLOR2_QUEUE = xQueueCreate(1, sizeof (COLOR2_Q));
    FLASH_READ_QUEUE = xQueueCreate(12, sizeof (FLASH_READ_Q));
    CP_LEVEL1_QUEUE = xQueueCreate(1, sizeof (CP_LEVEL1_Q));
    CP_LEVEL2_QUEUE = xQueueCreate(1, sizeof (CP_LEVEL2_Q));
    RFID_DATA_COMPLETE_QUEUE = xQueueCreate(1, sizeof (RFID_DATA_COMPLETE_Q));
    WHICH_METER_QUEUE = xQueueCreate(1, sizeof (WHICH_METER_Q));
    NEXT_METER_QUEUE = xQueueCreate(1, sizeof (NEXT_METER_Q));
    GUN1_CHARGING_TIME_QUEUE = xQueueCreate(1, sizeof (GUN1_CHARGING_TIME_Q));
    GUN2_CHARGING_TIME_QUEUE = xQueueCreate(1, sizeof (GUN2_CHARGING_TIME_Q));
    RECTIFIERS_TEMP_QUEUE = xQueueCreate(1, sizeof (RECTIFIERS_TEMP_Q));







    ESP_S_GROUND_M_V_QUEUE = xQueueCreate(1, sizeof (ESP_S_GROUND_M_V_Q));
    ESP_S_TEMP_QUEUE = xQueueCreate(1, sizeof (ESP_S_TEMP_Q));
    ESP_S_ERROR_W_QUEUE = xQueueCreate(1, sizeof (ESP_S_ERROR_W_Q));
    ESP_S_GUN1_P_QUEUE = xQueueCreate(1, sizeof (ESP_S_GUN1_P_Q));
    ESP_S_GUN2_P_QUEUE = xQueueCreate(1, sizeof (ESP_S_GUN2_P_Q));
    ESP_S_METER_D_QUEUE = xQueueCreate(4, sizeof (ESP_S_METER_D_Q));
    ESP_S_BT_QUEUE = xQueueCreate(1, sizeof (ESP_S_BT_Q));
    ESP_S_RFID_QUEUE = xQueueCreate(1, sizeof (ESP_S_RFID_Q));
    ESP_S_RFID_CONN_NO_QUEUE = xQueueCreate(1, sizeof (ESP_S_RFID_CONN_NO_Q));
    ESP_S_MAC_ID_QUEUE = xQueueCreate(1, sizeof (ESP_S_RFID_Q));
    ESP_S_MAC_ID_CONN_NO_QUEUE = xQueueCreate(1, sizeof (ESP_S_RFID_CONN_NO_Q));
    REC_TEMP_QUEUE = xQueueCreate(10, sizeof (CAN1_RECIEVE_Q));
    REC2_TEMP_QUEUE = xQueueCreate(20, sizeof (CAN2_RECIEVE_Q));
    ESP_S_REC_TEMP_QUEUE = xQueueCreate(2, sizeof (ESP_S_REC_TEMP_Q));


    all_rec_timer = xTimerCreate("all_rec_timer", 10000, pdFALSE, (void *) 0, all_rec_Callback);
    rec1_timer = xTimerCreate("rec1_timer", 10000, pdFALSE, (void *) 0, rec1_Callback);
    rec2_timer = xTimerCreate("rec2_timer", 10000, pdFALSE, (void *) 0, rec2_Callback);
    rec3_timer = xTimerCreate("rec3_timer", 10000, pdFALSE, (void *) 0, rec3_Callback);
    rec4_timer = xTimerCreate("rec4_timer", 20000, pdFALSE, (void *) 0, rec4_Callback);
    rfiddata_timer = xTimerCreate("rfiddata_timer", 1000, pdFALSE, (void *) 0, rfiddata_Callback);
    meter_change_timer = xTimerCreate("meter_change_timer", 2000, pdFALSE, (void *) 0, meter_change_Callback);
    live_mains_timer = xTimerCreate("live_mains_timer", 20000, pdFALSE, (void *) 0, MainsCallback);
    merger_timer = xTimerCreate("merger_timer", 500, pdFALSE, (void *) 0, merger_callback);
    Gun1_Charging_timer = xTimerCreate("Gun1_Charging_timer", 60000, pdFALSE, (void *) 0, Gun1_charge_timerCALLBACK);
    Gun2_Charging_timer = xTimerCreate("Gun2_Charging_timer", 60000, pdFALSE, (void *) 0, Gun2_charge_timerCALLBACK);
    _50_sec_timer = xTimerCreate("_50_sec_timer", 50, pdTRUE, (void *) 0, _50secCallback);
    _200_sec_timer = xTimerCreate("_200_sec_timer", 200, pdTRUE, (void *) 0, _200secCallback);
    _500_sec_timer = xTimerCreate("_500_sec_timer", 500, pdTRUE, (void *) 0, _500secCallback);
    _1000_sec_timer = xTimerCreate("_1000_sec_timer", 1000, pdTRUE, (void *) 0, _1000secCallback);

    plc1_timer = xTimerCreate("plc1_timer", 60000, pdTRUE, (void *) 0, plc1_Callback);
    plc2_timer = xTimerCreate("plc2_timer", 60000, pdTRUE, (void *) 0, plc2_Callback);
    all_plc_timer = xTimerCreate("all_plc_timer", 60000, pdTRUE, (void *) 0, all_plc_Callback);
    ac_timer = xTimerCreate("ac_timer", 60000, pdFALSE, (void *) 0, ac_Callback);
    dc1_timer = xTimerCreate("dc1_timer", 60000, pdFALSE, (void *) 0, dc1_Callback);
    dc2_timer = xTimerCreate("dc2_timer", 60000, pdFALSE, (void *) 0, dc2_Callback);
    rfid_timer = xTimerCreate("rfid_timer", 40000, pdFALSE, (void *) 0, rfid_timer_Callback);
    hmi_timer = xTimerCreate("hmi_timer", 40000, pdFALSE, (void *) 0, hmi_timer_Callback);
    modem_timer = xTimerCreate("modem_timer", 40000, pdFALSE, (void *) 0, modem_timer_Callback);
    HMI_DATA_T = xTimerCreate("HMI_DATA_T", 25, pdFALSE, (void *) 0, hmi_data_timercall);
    esp_data_timer = xTimerCreate("esp_data_timer", 200, pdFALSE, (void *) 0, esp_data_callback);
    rfid_send_timer = xTimerCreate("rfid_send_timer", 2000, pdFALSE, (void *) 0, rfid_send_callback);
    emergency_timer = xTimerCreate("emergency_timer", 2000, pdFALSE, (void *) 0, EMERGENCY_TIMER_CALL);

    xTaskCreate(StartDefaultTask, "StartDefaultTask", 512, NULL, 1, &defaultTaskHandle); // 2048-256
    xTaskCreate(Start_50msecTask, "Start50msecTask", 128, NULL, 1, &_50msecTask); // 1024-512
    xTaskCreate(Start_200msecTask, "Start200msecTask", 128, NULL, 1, &_200msecTask);
    xTaskCreate(Start_500msecTask, "Start500msecTask", 128, NULL, 1, &_500msecTask);
    xTaskCreate(Start_1000msecTask, "Start1000msecTask", 128, NULL, 1, &_1000msecTask);
    xTaskCreate(Start_RECTIFIER_TASK, "Start_RECTIFIER_TASK", 512, NULL, 1, &RECTIFIER_TASKHandle); // 2048-512
    xTaskCreate(Start_1_PLC_MANAGE_TASK, "Start_1_PLC_MANAGE_TASK", 1024, NULL, 2, &_1_PLC_MANAGE_TASKHandle); // 4256-1024
    xTaskCreate(Start_2_PLC_MANAGE_TASK, "Start_2_PLC_MANAGE_TASK", 1024, NULL, 2, &_2_PLC_MANAGE_TASKHandle); // 4256-1024
    xTaskCreate(Start_ESP_SEND_TASK, "Start_ESP_SEND_TASK", 256, NULL, 1, &ESP_SEND_TASKHandle); // 2560-512
    xTaskCreate(Start_RFID_SEND_TASk, "Start_RFID_SEND_TASk", 128, NULL, 1, &RFID_SEND_TASKHandle); // 512-256
    xTaskCreate(Start_ADC_TASK, "Start_ADC_TASK", 256, NULL, 1, &ADC_TASKHandle); // 1536-512
    xTaskCreate(Start_RGB_SEND_TASK, "Start_RGB_SEND_TASK", 128, NULL, 1, &RGB_SEND_TaskHandle); // 512-256
    xTaskCreate(Start_SMOKE_LIMIT_TASK, "Start_SMOKE_LIMIT_TASK", 512, NULL, 1, &SMOKE_LIMIT_TASKHandle);
    xTaskCreate(Start_I2C_TMP_HUM_TASK, "Start_I2C_TMP_HUM_TASK", 512, NULL, 1, &I2c_TEMP_HUM_TASKHandle);
    xTaskCreate(Start_METER_RX_TASK, "Start_METER_RX_TASK", 512, NULL, 1, &METER_RECEIVE_TaskHandle); // 3072-512
    xTaskCreate(Start_RFID_RX_TASK, "Start_RFID_RX_TASK", 256, NULL, 1, &RFID_RX_TASKHandle); // 1024-512
    xTaskCreate(Start_ESP_RX_TASK, "Start_ESP_RX_TASK", 256, NULL, 1, &ESP_RX_TASKHandle); // 2048-512
    xTaskCreate(StartCANrecieveTask, "StartCANrecieveTask", 512, NULL, 1, &canrecievetask); // 2048-512
    xTaskCreate(Start_SIMULATOR_TASK, "Start_SIMULATOR_TASK", 256, NULL, 1, &simulatortask);
    xTaskCreate(Start_HMI_TX_TASK, "Start_HMI_TX_TASK", 128, NULL, 2, &HMI_SEND_TASKHandle); // 512-256
    xTaskCreate(Start_HMI_RX_TASK, "Start_HMI_RX_TASK", 128, NULL, 1, &HMI_RX_TASKHandle); // 512-256
    xTaskCreate(Start_EMERGENCY_TASK, "Start_EMERGENCY_TASK", 256, NULL, 2, &EMERGENCY_TASKHandle); // 1024-512
    xTaskCreate(Start_ERROR_CODE_TASK, "Start_ERROR_CODE_TASK", 128, NULL, 1, &ERROR_CODE_TASKHandle); // 2048-256
    xTaskCreate(Start_MAINS_TASK, "Start_MAINS_TASK", 128, NULL, 0, &MAINS_TASKHandle);
    xTaskCreate(Start_LED_TASK, "Start_LED_TASK", 128, NULL, 1, &LED_TASKHandle);
    xTaskCreate(Start_GUN1_PARAM_TASK, "Start_GUN1_PARAM_TASK", 128, NULL, 2, &GUN1_PARAM_TASKHandle);
    xTaskCreate(Start_GUN2_PARAM_TASK, "Start_GUN2_PARAM_TASK", 128, NULL, 2, &GUN2_PARAM_TASKHandle);
    xTaskCreate(Start_FLASH_READ_TASK, "Start_FLASH_READ_TASK", 1536, NULL, 1, &FLASH_READ_TASKHandle);
    xTaskCreate(Start_FLASH_WRITE_TASK, "Start_FLASH_WRITE_TASK", 1536, NULL, 3, &FLASH_WRITE_TASKHandle);
    xTaskCreate(Start_DATA_POPULATE_TASK, "Start_DATA_POPULATE_TASK", 2048, NULL, 4, &DATA_POPULATE_TASKHandle); //1536-2048
    xTaskCreate(Start_AC_METER_SEND_TASK, "Start_METER_SEND_TASK", 256, NULL, 1, &AC_METER_SEND_TASKHandle);
    xTaskCreate(Start_DC1_METER_SEND_TASK, "Start_METER_SEND_TASK", 256, NULL, 1, &DC1_METER_SEND_TASKHandle);
    xTaskCreate(Start_DC2_METER_SEND_TASK, "Start_METER_SEND_TASK", 256, NULL, 1, &DC2_METER_SEND_TASKHandle);
    xTaskCreate(Start_FAN_TASK, "Start_FAN_TASK", 256, NULL, 1, &FAN_TASKHandle);



    SERCOM5_USART_ReadCallbackRegister(SIMULATOR_CALLBACK, 0);
    SERCOM5_USART_Read(Simulator_buff, SIM_RX_SIZE);
    SERCOM6_USART_ReadCallbackRegister(HMI_CALLBACK, 0);
    SERCOM6_USART_Read(&hmi_rx, RX_SIZE);
    vTaskSuspend(simulatortask);
    vTaskSuspend(_50msecTask);
    vTaskSuspend(_200msecTask);
    vTaskSuspend(_500msecTask);
    vTaskSuspend(_1000msecTask);
    vTaskSuspend(RECTIFIER_TASKHandle);
    vTaskSuspend(_1_PLC_MANAGE_TASKHandle);
    vTaskSuspend(_2_PLC_MANAGE_TASKHandle);
    vTaskSuspend(ESP_SEND_TASKHandle);
    vTaskSuspend(RFID_SEND_TASKHandle);
    vTaskSuspend(ADC_TASKHandle);
    vTaskSuspend(RGB_SEND_TaskHandle);
    vTaskSuspend(I2c_TEMP_HUM_TASKHandle);
    vTaskSuspend(METER_RECEIVE_TaskHandle);
    vTaskSuspend(RFID_RX_TASKHandle);
    vTaskSuspend(ESP_RX_TASKHandle);
    vTaskSuspend(canrecievetask);
    vTaskSuspend(EMERGENCY_TASKHandle);
    vTaskSuspend(SMOKE_LIMIT_TASKHandle);
    vTaskSuspend(LED_TASKHandle);
    vTaskSuspend(GUN1_PARAM_TASKHandle);
    vTaskSuspend(GUN2_PARAM_TASKHandle);
    vTaskSuspend(FLASH_READ_TASKHandle);
    vTaskSuspend(FLASH_WRITE_TASKHandle);
    vTaskSuspend(DATA_POPULATE_TASKHandle);
    vTaskSuspend(AC_METER_SEND_TASKHandle);
    vTaskSuspend(DC1_METER_SEND_TASKHandle);
    vTaskSuspend(DC2_METER_SEND_TASKHandle);
    vTaskSuspend(FAN_TASKHandle);
    vTaskStartScheduler();
    while (true) {
    }

    return (EXIT_FAILURE);
}

void Start_ERROR_CODE_TASK(void *argument) {
    //    char buffer[40] = {0};
    static int ERROR0_ARRAY[16] = {0};
    static uint8_t error0_count = 0;
    static int ERROR1_ARRAY[10] = {0};
    static uint8_t error1_count = 0;
    static int ERROR2_ARRAY[10] = {0};
    static uint8_t error2_count = 0;

    static bool array_bits[62] = {0};
    static uint16_t Error_Code0;
    static uint16_t Error_Code1;
    static uint16_t Error_Code2;
    static uint16_t Warning_Code0;
    static uint16_t Warning_Code1;
    static uint16_t Warning_Code2;
    ESP_S_ERROR_W_Q esp_s_error_data;
    for (;;) {

        for (ikf = 0; ikf < 32; ikf++) {
            switch (ikf) {
                case MAIN_FAIL_IDX:
                    ERROR0_ARRAY[0] = ERROR_CODE_ARRAY[ikf];
                    if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[MAIN_FAIL_IDX] == 0)) {
                        array_bits[MAIN_FAIL_IDX] = 1;
                        Error_Code0 = ERROR_CODE_ARRAY[ikf];
                        vTaskDelay(4000);
                    }
                    if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[MAIN_FAIL_IDX] == 1)) {
                        array_bits[MAIN_FAIL_IDX] = 0;
                    }
                    break;
                case SMOKE_DETECTED_IDX:
                    ERROR0_ARRAY[1] = ERROR_CODE_ARRAY[ikf];
                    if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[SMOKE_DETECTED_IDX] == 0)) {
                        array_bits[SMOKE_DETECTED_IDX] = 1;
                        Error_Code0 = ERROR_CODE_ARRAY[ikf];
                        vTaskDelay(4000);
                    }
                    if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[SMOKE_DETECTED_IDX] == 1)) {
                        array_bits[SMOKE_DETECTED_IDX] = 0;
                    }
                    break;
                case ALL_RECTI_FAIL_IDX:
                    ERROR0_ARRAY[2] = ERROR_CODE_ARRAY[ikf];
                    if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[ALL_RECTI_FAIL_IDX] == 0)) {
                        array_bits[ALL_RECTI_FAIL_IDX] = 1;
                        Error_Code0 = ERROR_CODE_ARRAY[ikf];
                        vTaskDelay(4000);
                    }
                    if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[ALL_RECTI_FAIL_IDX] == 1)) {
                        array_bits[ALL_RECTI_FAIL_IDX] = 0;
                    }
                    break;
                case ESD_PRESSED_IDX:
                    ERROR0_ARRAY[3] = ERROR_CODE_ARRAY[ikf];
                    if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[ESD_PRESSED_IDX] == 0)) {
                        array_bits[ESD_PRESSED_IDX] = 1;
                        Error_Code0 = ERROR_CODE_ARRAY[ikf];
                        vTaskDelay(4000);
                    }
                    if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[ESD_PRESSED_IDX] == 1)) {
                        array_bits[ESD_PRESSED_IDX] = 0;
                    }
                    break;
                case PLC_COMM_FAIL_IDX:
                    if (ERROR_CODE_ARRAY[PLC_COMM_FAIL_CONN_NO] == 1) {
                        ERROR1_ARRAY[0] = ERROR_CODE_ARRAY[ikf];
                        if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[PLC_COMM_FAIL_IDX1] == 0)) {
                            array_bits[PLC_COMM_FAIL_IDX1] = 1;
                            Error_Code1 = ERROR_CODE_ARRAY[ikf];
                            vTaskDelay(4000);
                        }
                        if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[PLC_COMM_FAIL_IDX1] == 1)) {
                            array_bits[PLC_COMM_FAIL_IDX1] = 0;
                        }
                    }
                    if (ERROR_CODE_ARRAY[PLC_COMM_FAIL_CONN_NO] == 2) {
                        ERROR2_ARRAY[0] = ERROR_CODE_ARRAY[ikf];
                        if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[PLC_COMM_FAIL_IDX2] == 0)) {
                            array_bits[PLC_COMM_FAIL_IDX2] = 1;
                            Error_Code2 = ERROR_CODE_ARRAY[ikf];
                            vTaskDelay(4000);
                        }
                        if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[PLC_COMM_FAIL_IDX2] == 1)) {
                            array_bits[PLC_COMM_FAIL_IDX2] = 0;
                        }
                    }
                    break;
                case SPD_FAULT_IDX:
                    ERROR0_ARRAY[4] = ERROR_CODE_ARRAY[ikf];
                    if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[SPD_FAULT_IDX] == 0)) {
                        array_bits[SPD_FAULT_IDX] = 1;

                        Error_Code0 = ERROR_CODE_ARRAY[ikf];
                        vTaskDelay(4000);
                    }
                    if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[SPD_FAULT_IDX] == 1)) {
                        array_bits[SPD_FAULT_IDX] = 0;
                    }
                    break;
                case HIGH_LEAKAGE_IDX:
                    ERROR0_ARRAY[5] = ERROR_CODE_ARRAY[ikf];
                    if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[HIGH_LEAKAGE_IDX] == 0)) {
                        array_bits[HIGH_LEAKAGE_IDX] = 1;
                        Error_Code0 = ERROR_CODE_ARRAY[ikf];
                        vTaskDelay(4000);
                    }
                    if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[HIGH_LEAKAGE_IDX] == 1)) {
                        array_bits[HIGH_LEAKAGE_IDX] = 0;
                    }
                    break;
                case HIGH_NE_IDX:
                    ERROR0_ARRAY[6] = ERROR_CODE_ARRAY[ikf];
                    if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[HIGH_NE_IDX] == 0)) {
                        array_bits[HIGH_NE_IDX] = 1;
                        Error_Code0 = ERROR_CODE_ARRAY[ikf];
                        vTaskDelay(4000);
                    }
                    if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[HIGH_NE_IDX] == 1)) {
                        array_bits[HIGH_NE_IDX] = 0;
                    }
                    break;
                case MAINS_LOW_IDX:
                    ERROR0_ARRAY[7] = ERROR_CODE_ARRAY[ikf];
                    if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[MAINS_LOW_IDX] == 0)) {
                        Error_Code0 = ERROR_CODE_ARRAY[ikf];
                        array_bits[MAINS_LOW_IDX] = 1;
                        vTaskDelay(4000);
                    }
                    if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[MAINS_LOW_IDX] == 1)) {
                        array_bits[MAINS_LOW_IDX] = 0;
                    }
                    break;
                case MAINS_HIGH_IDX:
                    ERROR0_ARRAY[8] = ERROR_CODE_ARRAY[ikf];
                    if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[MAINS_HIGH_IDX] == 0)) {
                        array_bits[MAINS_HIGH_IDX] = 1;
                        Error_Code0 = ERROR_CODE_ARRAY[ikf];
                        vTaskDelay(4000);
                    }
                    if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[MAINS_HIGH_IDX] == 1)) {
                        array_bits[MAINS_HIGH_IDX] = 0;
                    }
                    break;
                case AC_METER_FAIL_IDX:
                    ERROR0_ARRAY[9] = ERROR_CODE_ARRAY[ikf];

                    if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[AC_METER_FAIL_IDX] == 0)) {
                        array_bits[AC_METER_FAIL_IDX] = 1;
                        Error_Code0 = ERROR_CODE_ARRAY[ikf];
                        vTaskDelay(4000);
                    }
                    if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[AC_METER_FAIL_IDX] == 1)) {
                        array_bits[AC_METER_FAIL_IDX] = 0;
                    }
                    break;
                case RFID_COMM_FAIL_IDX:
                    ERROR0_ARRAY[10] = ERROR_CODE_ARRAY[ikf];
                    if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[RFID_COMM_FAIL_IDX] == 0)) {
                        array_bits[RFID_COMM_FAIL_IDX] = 1;
                        Warning_Code0 = ERROR_CODE_ARRAY[ikf];
                        vTaskDelay(4000);
                    }
                    if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[RFID_COMM_FAIL_IDX] == 1)) {
                        array_bits[RFID_COMM_FAIL_IDX] = 0;
                    }
                    break;
                case SYSTEM_TEMP_HIGH_IDX:
                    ERROR0_ARRAY[11] = ERROR_CODE_ARRAY[ikf];
                    if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[SYSTEM_TEMP_HIGH_IDX] == 0)) {
                        array_bits[SYSTEM_TEMP_HIGH_IDX] = 1;
                        Error_Code0 = ERROR_CODE_ARRAY[ikf];
                        vTaskDelay(4000);
                    }
                    if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[SYSTEM_TEMP_HIGH_IDX] == 1)) {
                        array_bits[SYSTEM_TEMP_HIGH_IDX] = 0;
                    }
                    break;
                    //                case GUN_TEMP_HIGH_IDX:
                    //                    if (ERROR_CODE_ARRAY[GUN_TEMP_CONN_NO] == 1) {
                    //                        ERROR1_ARRAY[1] = ERROR_CODE_ARRAY[ikf];
                    //                        if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[GUN_TEMP_HIGH_IDX1] == 0)) {
                    //                            array_bits[GUN_TEMP_HIGH_IDX1] = 1;
                    //                            Error_Code1 = ERROR_CODE_ARRAY[ikf];
                    //                            vTaskDelay(4000);
                    //                        }
                    //                        if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[GUN_TEMP_HIGH_IDX1] == 1)) {
                    //                            array_bits[GUN_TEMP_HIGH_IDX1] = 0;
                    //                        }
                    //                    }
                    //                    if (ERROR_CODE_ARRAY[GUN_TEMP_CONN_NO] == 2) {
                    //                        ERROR2_ARRAY[1] = ERROR_CODE_ARRAY[ikf];
                    //                        if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[GUN_TEMP_HIGH_IDX2] == 0)) {
                    //                            array_bits[GUN_TEMP_HIGH_IDX2] = 1;
                    //                            Error_Code2 = ERROR_CODE_ARRAY[ikf];
                    //                            vTaskDelay(4000);
                    //                        }
                    //                        if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[GUN_TEMP_HIGH_IDX2] == 1)) {
                    //                            array_bits[GUN_TEMP_HIGH_IDX2] = 0;
                    //                        }
                    //                    }
                    //                    break;
                case ISOLATION_FAIL_IDX:
                    if (ERROR_CODE_ARRAY[IMD_FAIL_CONN_NO] == 1) {
                        ERROR1_ARRAY[2] = ERROR_CODE_ARRAY[ikf];
                        if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[ISOLATION_FAIL_IDX1] == 0)) {
                            array_bits[ISOLATION_FAIL_IDX1] = 1;
                            Error_Code1 = ERROR_CODE_ARRAY[ikf];
                            vTaskDelay(4000);
                        }
                        if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[ISOLATION_FAIL_IDX1] == 1)) {
                            array_bits[ISOLATION_FAIL_IDX1] = 0;
                        }
                    }
                    if (ERROR_CODE_ARRAY[IMD_FAIL_CONN_NO] == 2) {
                        ERROR2_ARRAY[2] = ERROR_CODE_ARRAY[ikf];
                        if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[ISOLATION_FAIL_IDX2] == 0)) {
                            array_bits[ISOLATION_FAIL_IDX2] = 1;
                            Error_Code2 = ERROR_CODE_ARRAY[ikf];
                            vTaskDelay(4000);
                        }
                        if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[ISOLATION_FAIL_IDX2] == 1)) {
                            array_bits[ISOLATION_FAIL_IDX2] = 0;
                        }
                    }
                    break;
                case LED_BOARD_FAIL_IDX:
                    if (ERROR_CODE_ARRAY[LED_CONN_NO] == 1) {
                        ERROR1_ARRAY[3] = ERROR_CODE_ARRAY[ikf];
                        if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[LED_BOARD_FAIL_IDX1] == 0)) {
                            array_bits[LED_BOARD_FAIL_IDX1] = 1;
                            Warning_Code1 = ERROR_CODE_ARRAY[ikf];
                            vTaskDelay(4000);
                        }
                        if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[LED_BOARD_FAIL_IDX1] == 1)) {
                            array_bits[LED_BOARD_FAIL_IDX1] = 0;
                        }
                    }
                    if (ERROR_CODE_ARRAY[LED_CONN_NO] == 2) {
                        ERROR2_ARRAY[3] = ERROR_CODE_ARRAY[ikf];
                        if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[LED_BOARD_FAIL_IDX2] == 0)) {
                            array_bits[LED_BOARD_FAIL_IDX2] = 1;
                            Warning_Code2 = ERROR_CODE_ARRAY[ikf];
                            vTaskDelay(4000);
                        }
                        if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[LED_BOARD_FAIL_IDX2] == 1)) {
                            array_bits[LED_BOARD_FAIL_IDX2] = 0;
                        }
                    }

                    break;
                case RECTIFIER1_COMM_FAIL_IDX:
                    if (ERROR_CODE_ARRAY[REC_GROUP_CONN_NO] == 1) {
                        ERROR1_ARRAY[4] = ERROR_CODE_ARRAY[ikf];
                        if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[RECTIFIER1_COMM_FAIL_IDX1] == 0)) {
                            array_bits[RECTIFIER1_COMM_FAIL_IDX1] = 1;
                            Error_Code1 = ERROR_CODE_ARRAY[ikf];
                            vTaskDelay(4000);
                        }
                        if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[RECTIFIER1_COMM_FAIL_IDX1] == 1)) {
                            array_bits[RECTIFIER1_COMM_FAIL_IDX1] = 0;
                        }
                    }
                    if (ERROR_CODE_ARRAY[REC_GROUP_CONN_NO] == 2) {
                        ERROR2_ARRAY[4] = ERROR_CODE_ARRAY[ikf];
                        if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[RECTIFIER1_COMM_FAIL_IDX2] == 0)) {
                            array_bits[RECTIFIER1_COMM_FAIL_IDX2] = 1;
                            Error_Code2 = ERROR_CODE_ARRAY[ikf];
                            vTaskDelay(4000);
                        }
                        if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[RECTIFIER1_COMM_FAIL_IDX2] == 1)) {
                            array_bits[RECTIFIER1_COMM_FAIL_IDX2] = 0;
                        }
                    }
                    break;
                case RECTIFIER2_COMM_FAIL_IDX:
                    if (ERROR_CODE_ARRAY[REC_GROUP_CONN_NO] == 1) {
                        ERROR1_ARRAY[5] = ERROR_CODE_ARRAY[ikf];
                        if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[RECTIFIER2_COMM_FAIL_IDX1] == 0)) {
                            Error_Code1 = ERROR_CODE_ARRAY[ikf];
                            vTaskDelay(4000);
                        }
                        if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[RECTIFIER2_COMM_FAIL_IDX1] == 1)) {
                            array_bits[RECTIFIER2_COMM_FAIL_IDX1] = 0;
                        }
                    }
                    if (ERROR_CODE_ARRAY[REC_GROUP_CONN_NO] == 2) {
                        ERROR2_ARRAY[5] = ERROR_CODE_ARRAY[ikf];
                        if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[RECTIFIER2_COMM_FAIL_IDX2] == 0)) {
                            Error_Code2 = ERROR_CODE_ARRAY[ikf];
                            vTaskDelay(4000);
                        }
                        if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[RECTIFIER2_COMM_FAIL_IDX2] == 1)) {
                            array_bits[RECTIFIER2_COMM_FAIL_IDX2] = 0;
                        }
                    }
                    break;
                case DC_OVER_VOLTAGE_IDX:
                    if (ERROR_CODE_ARRAY[DC_OVER_CONN_NO] == 1) {
                        ERROR1_ARRAY[6] = ERROR_CODE_ARRAY[ikf];
                        if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[DC_OVER_VOLTAGE_IDX1] == 0)) {
                            Error_Code1 = ERROR_CODE_ARRAY[ikf];
                            vTaskDelay(4000);
                        }
                        if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[DC_OVER_VOLTAGE_IDX1] == 1)) {
                            array_bits[DC_OVER_VOLTAGE_IDX1] = 0;
                        }
                    }
                    if (ERROR_CODE_ARRAY[DC_OVER_CONN_NO] == 2) {
                        ERROR2_ARRAY[6] = ERROR_CODE_ARRAY[ikf];
                        if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[DC_OVER_VOLTAGE_IDX2] == 0)) {
                            Error_Code2 = ERROR_CODE_ARRAY[ikf];
                            vTaskDelay(4000);
                        }
                        if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[DC_OVER_VOLTAGE_IDX2] == 1)) {
                            array_bits[DC_OVER_VOLTAGE_IDX2] = 0;
                        }
                    }
                    break;
                case DC_UNDER_VOLT_IDX:
                    if (ERROR_CODE_ARRAY[DC_UNDER_CONN_NO] == 1) {
                        ERROR1_ARRAY[7] = ERROR_CODE_ARRAY[ikf];
                        if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[DC_UNDER_VOLT_IDX1] == 0)) {
                            Error_Code1 = ERROR_CODE_ARRAY[ikf];
                            vTaskDelay(4000);
                        }
                        if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[DC_UNDER_VOLT_IDX1] == 1)) {
                            array_bits[DC_UNDER_VOLT_IDX1] = 0;
                        }
                    }
                    if (ERROR_CODE_ARRAY[DC_UNDER_CONN_NO] == 2) {
                        ERROR2_ARRAY[7] = ERROR_CODE_ARRAY[ikf];
                        if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[DC_UNDER_VOLT_IDX2] == 0)) {
                            Error_Code2 = ERROR_CODE_ARRAY[ikf];
                            vTaskDelay(4000);
                        }
                        if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[DC_UNDER_VOLT_IDX2] == 1)) {
                            array_bits[DC_UNDER_VOLT_IDX2] = 0;
                        }
                    }
                    break;
                case DC_OVER_CURR_IDX:
                    if (ERROR_CODE_ARRAY[DC_CURRENT_OVER_CONN_NO] == 1) {
                        ERROR1_ARRAY[8] = ERROR_CODE_ARRAY[ikf];
                        if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[DC_OVER_CURR_IDX1] == 0)) {
                            Error_Code1 = ERROR_CODE_ARRAY[ikf];
                            vTaskDelay(4000);
                        }
                        if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[DC_OVER_CURR_IDX1] == 1)) {
                            array_bits[DC_OVER_CURR_IDX1] = 0;
                        }
                    }
                    if (ERROR_CODE_ARRAY[DC_CURRENT_OVER_CONN_NO] == 2) {
                        ERROR2_ARRAY[8] = ERROR_CODE_ARRAY[ikf];
                        if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[DC_OVER_CURR_IDX2] == 0)) {
                            Error_Code2 = ERROR_CODE_ARRAY[ikf];
                            vTaskDelay(4000);
                        }
                        if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[DC_OVER_CURR_IDX2] == 1)) {
                            array_bits[DC_OVER_CURR_IDX2] = 0;
                        }
                    }
                    break;
                case HMI_COMM_FAIL_IDX:
                    ERROR0_ARRAY[12] = ERROR_CODE_ARRAY[ikf];
                    if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[HMI_COMM_FAIL_IDX] == 0)) {
                        array_bits[HMI_COMM_FAIL_IDX] = 1;
                        Warning_Code0 = ERROR_CODE_ARRAY[ikf];
                        vTaskDelay(4000);
                    }
                    if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[HMI_COMM_FAIL_IDX] == 1)) {
                        array_bits[HMI_COMM_FAIL_IDX] = 0;
                    }
                    break;
                case DC_METER_COMM_FAIL_IDX:
                    if (ERROR_CODE_ARRAY[DC_METER_COMM_FAIL_CONN_NO] == 1) {
                        ERROR1_ARRAY[9] = ERROR_CODE_ARRAY[ikf];
                        if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[DC_METER_COMM_FAIL_IDX1] == 0)) {
                            Error_Code1 = ERROR_CODE_ARRAY[ikf];
                            vTaskDelay(4000);
                        }
                        if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[DC_METER_COMM_FAIL_IDX1] == 1)) {
                            array_bits[DC_METER_COMM_FAIL_IDX1] = 0;
                        }
                    }
                    if (ERROR_CODE_ARRAY[DC_METER_COMM_FAIL_CONN_NO] == 2) {
                        ERROR2_ARRAY[9] = ERROR_CODE_ARRAY[ikf];
                        if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[DC_METER_COMM_FAIL_IDX2] == 0)) {
                            Error_Code2 = ERROR_CODE_ARRAY[ikf];
                            vTaskDelay(4000);
                        }
                        if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[DC_METER_COMM_FAIL_IDX2] == 1)) {
                            array_bits[DC_METER_COMM_FAIL_IDX2] = 0;
                        }
                    }
                    break;
                case ALL_PLC_COMM_FAIL_IDX:
                    ERROR0_ARRAY[13] = ERROR_CODE_ARRAY[ikf];
                    if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[ALL_PLC_COMM_FAIL_IDX] == 0)) {
                        array_bits[ALL_PLC_COMM_FAIL_IDX] = 1;
                        Error_Code0 = ERROR_CODE_ARRAY[ikf];
                        vTaskDelay(4000);
                    }
                    if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[ALL_PLC_COMM_FAIL_IDX] == 1)) {
                        array_bits[ALL_PLC_COMM_FAIL_IDX] = 0;
                    }
                    break;
                case ALL_DC_METER_FAIL_IDX:
                    ERROR0_ARRAY[14] = ERROR_CODE_ARRAY[ikf];
                    if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[ALL_DC_METER_FAIL_IDX] == 0)) {
                        array_bits[ALL_DC_METER_FAIL_IDX] = 1;
                        Error_Code0 = ERROR_CODE_ARRAY[ikf];
                        vTaskDelay(4000);
                    }
                    if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[ALL_DC_METER_FAIL_IDX] == 1)) {
                        array_bits[ALL_DC_METER_FAIL_IDX] = 0;
                    }
                    break;
                    //                case DOOR_OPEN_IDX:
                    //                    ERROR0_ARRAY[14] = ERROR_CODE_ARRAY[ikf];
                    //                    if ((ERROR_CODE_ARRAY[ikf] != 0) && (array_bits[DOOR_OPEN_IDX] == 0)) {
                    //                        array_bits[DOOR_OPEN_IDX] = 1;
                    //                        Error_Code0 = ERROR_CODE_ARRAY[ikf];
                    //                        vTaskDelay(4000);
                    //                    }
                    //                    if ((ERROR_CODE_ARRAY[ikf] == 0) && (array_bits[DOOR_OPEN_IDX] == 1)) {
                    //                        array_bits[DOOR_OPEN_IDX] = 0;
                    //                    }
                    //                    break;
            }
            esp_s_error_data.Error_Code0 = Error_Code0;
            esp_s_error_data.Error_Code1 = Error_Code1;
            esp_s_error_data.Error_Code2 = Error_Code2;
            esp_s_error_data.Warning_Code0 = Warning_Code0;
            esp_s_error_data.Warning_Code1 = Warning_Code1;
            esp_s_error_data.Warning_Code2 = Warning_Code2;
            xQueueOverwrite(ESP_S_ERROR_W_QUEUE, &esp_s_error_data);
        }
        for (uint8_t i = 0; i < 16; i++) {
            if (ERROR0_ARRAY[i] != 0) {
                error0_count = error0_count + 1;
            }
        }
        if (error0_count == 0) {
            error0_count = 0;
            Error_Code0 = 0;
            Warning_Code0 = 0;
            esp_s_error_data.Error_Code0 = Error_Code0;
            esp_s_error_data.Error_Code1 = Error_Code1;
            esp_s_error_data.Error_Code2 = Error_Code2;
            esp_s_error_data.Warning_Code0 = Warning_Code0;
            esp_s_error_data.Warning_Code1 = Warning_Code1;
            esp_s_error_data.Warning_Code2 = Warning_Code2;
            xQueueOverwrite(ESP_S_ERROR_W_QUEUE, &esp_s_error_data);
        } else {
            error0_count = 0;
        }
        for (uint8_t j = 0; j < 10; j++) {
            if (ERROR1_ARRAY[j] != 0) {
                error1_count = error1_count + 1;
            }
        }
        if (error1_count == 0) {
            error1_count = 0;
            Error_Code1 = 0;
            Warning_Code1 = 0;
            esp_s_error_data.Error_Code0 = Error_Code0;
            esp_s_error_data.Error_Code1 = Error_Code1;
            esp_s_error_data.Error_Code2 = Error_Code2;
            esp_s_error_data.Warning_Code0 = Warning_Code0;
            esp_s_error_data.Warning_Code1 = Warning_Code1;
            esp_s_error_data.Warning_Code2 = Warning_Code2;
            xQueueOverwrite(ESP_S_ERROR_W_QUEUE, &esp_s_error_data);
        } else {
            error1_count = 0;
        }
        for (uint8_t k = 0; k < 10; k++) {
            if (ERROR2_ARRAY[k] != 0) {
                error2_count = error2_count + 1;
            }
        }
        if (error2_count == 0) {
            error2_count = 0;
            Error_Code2 = 0;
            Warning_Code2 = 0;
            esp_s_error_data.Error_Code0 = Error_Code0;
            esp_s_error_data.Error_Code1 = Error_Code1;
            esp_s_error_data.Error_Code2 = Error_Code2;
            esp_s_error_data.Warning_Code0 = Warning_Code0;
            esp_s_error_data.Warning_Code1 = Warning_Code1;
            esp_s_error_data.Warning_Code2 = Warning_Code2;
            xQueueOverwrite(ESP_S_ERROR_W_QUEUE, &esp_s_error_data);
        } else {

            error2_count = 0;
        }
        vTaskDelay(1000);
    }
}

void Start_EMERGENCY_TASK(void *argument) {
    _50MS_Q _50msmsg;
    _1_PLC_tx_50 _1_PLC_tx_50_t;
    RECTIFIER_Q rectimsg;
    _2_PLC_tx_50 _2_PLC_tx_50_t;
    for (;;) {

        if (CURRENT_PLC1_STATE == _1_PLC_STATE_CURRENT_DEMAND_1 || CURRENT_PLC2_STATE == _2_PLC_STATE_CURRENT_DEMAND_1) {
            vTaskResume(GUN1_PARAM_TASKHandle);
            vTaskResume(GUN2_PARAM_TASKHandle);
        }
        if (START_STOP_AR[0] == 1 && START_STOP_AR[2] == 1) {
            GUN1_CONNECTED = 0;

            _50msmsg.DATA[1] = _1_PLC_tx_50_t._002_EVSE_CHARGING_CONTROL_DATA1_t =
                    Charging_Control_Normal_Stop;
            _50msmsg.ID_t = _002;
            xQueueSend(_50msQUEUE, &_50msmsg, 100);
            vTaskDelay(10);

            rectimsg.RECTI_ON_OFF[0] = RECTIFIER_OFF;
            rectimsg.PLC_ID[0] = 0x01;

            DC1_Contactor_Set();
            xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
            vTaskDelay(3000);
            CURRENT_PLC1_STATE = _1_PLC_STATE_TERMINATED;
            //            CP_Level_1 = 9;
            memset(START_STOP_AR, 0, 3);
        }
        if (START_STOP_AR1[0] == 2 && START_STOP_AR1[2] == 1) {
            GUN2_CONNECTED = 0;
            _50msmsg.DATA[1] = _2_PLC_tx_50_t._402_EVSE_CHARGING_CONTROL_DATA1_t =
                    Charging_Control_Normal_Stop;
            _50msmsg.ID_t = _402;
            xQueueSend(_50msQUEUE, &_50msmsg, 100);
            vTaskDelay(10);

            rectimsg.RECTI_ON_OFF[0] = RECTIFIER_OFF;
            rectimsg.PLC_ID[0] = 0x02;
            DC2_Contactor_Set();
            xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
            vTaskDelay(3000);
            CURRENT_PLC2_STATE = _2_PLC_STATE_TERMINATED;
            memset(START_STOP_AR1, 0, 3);
        }
        if (START_STOP_AR[0] == 3) {

            AC_Contactor_Relay_Set();
            Update_GUN1_Session_End_Reason(0x04);
            Update_GUN2_Session_End_Reason(0x04);
            GUN2_CONNECTED = 0;
            _50msmsg.DATA[1] = _2_PLC_tx_50_t._402_EVSE_CHARGING_CONTROL_DATA1_t =
                    Charging_Control_Normal_Stop;
            _50msmsg.ID_t = _402;
            xQueueSend(_50msQUEUE, &_50msmsg, 100);
            vTaskDelay(10);

            rectimsg.RECTI_ON_OFF[0] = RECTIFIER_OFF;
            rectimsg.PLC_ID[0] = 0x02;
            DC2_Contactor_Set();
            xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
            vTaskDelay(3000);
            if (CURRENT_PLC2_STATE >= _2_PLC_STATE_PRE_CHARGE) {
                CURRENT_PLC2_STATE = _2_PLC_STATE_TERMINATED;
            }
            memset(START_STOP_AR, 0, 3);

            vTaskDelay(1000);

            GUN1_CONNECTED = 0;

            _50msmsg.DATA[1] = _1_PLC_tx_50_t._002_EVSE_CHARGING_CONTROL_DATA1_t =
                    Charging_Control_Normal_Stop;
            _50msmsg.ID_t = _002;
            xQueueSend(_50msQUEUE, &_50msmsg, 100);
            vTaskDelay(10);

            rectimsg.RECTI_ON_OFF[0] = RECTIFIER_OFF;
            rectimsg.PLC_ID[0] = 0x01;
            DC1_Contactor_Set();
            xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
            vTaskDelay(3000);
            if (CURRENT_PLC1_STATE >= _1_PLC_STATE_PRE_CHARGE) {
                CURRENT_PLC1_STATE = _1_PLC_STATE_TERMINATED;
            }
            memset(START_STOP_AR, 0, 3);
        }
        if (START_STOP_AR[0] == 4) {

            AC_Contactor_Relay_Set();
            GUN2_CONNECTED = 0;
            _50msmsg.DATA[1] = _2_PLC_tx_50_t._402_EVSE_CHARGING_CONTROL_DATA1_t =
                    Charging_Control_Normal_Stop;
            _50msmsg.ID_t = _402;
            xQueueSend(_50msQUEUE, &_50msmsg, 100);
            vTaskDelay(10);

            rectimsg.RECTI_ON_OFF[0] = RECTIFIER_OFF;
            rectimsg.PLC_ID[0] = 0x02;
            DC2_Contactor_Set();
            xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
            vTaskDelay(3000);
            if (CURRENT_PLC2_STATE >= _2_PLC_STATE_PRE_CHARGE) {
                CURRENT_PLC2_STATE = _2_PLC_STATE_TERMINATED;
            }
            memset(START_STOP_AR, 0, 3);

            vTaskDelay(1000);

            GUN1_CONNECTED = 0;

            _50msmsg.DATA[1] = _1_PLC_tx_50_t._002_EVSE_CHARGING_CONTROL_DATA1_t =
                    Charging_Control_Normal_Stop;
            _50msmsg.ID_t = _002;
            xQueueSend(_50msQUEUE, &_50msmsg, 100);
            vTaskDelay(10);

            rectimsg.RECTI_ON_OFF[0] = RECTIFIER_OFF;
            rectimsg.PLC_ID[0] = 0x01;
            DC1_Contactor_Set();
            xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
            vTaskDelay(3000);
            if (CURRENT_PLC1_STATE >= _1_PLC_STATE_PRE_CHARGE) {
                CURRENT_PLC1_STATE = _1_PLC_STATE_TERMINATED;
            }
            memset(START_STOP_AR, 0, 3);
        }

        vTaskSuspend(EMERGENCY_TASKHandle);
        vTaskDelay(1);
    }
}

void StartDefaultTask(void *argument) {
    AC_Contactor_Relay_Set();
    DC1_Contactor_Set();
    DC2_Contactor_Set();
    MERGER_Contactor_Set();
    POWER_BANK_RELAY_Set();
    ESP_Q_DATA espdata;
    COLOR1_Q color1msg;
    COLOR2_Q color2msg;
    char buffer[40] = {0};
    memset(espdata.ESP_ARRAY, 0, sizeof (espdata.ESP_ARRAY));
    FAN_ON(10000);
    BUZZER_Set();
    color1msg.COLOR1 = YELLOW;
    color2msg.COLOR2 = YELLOW2;
    xQueueOverwrite(COLOR1_QUEUE, &color1msg);
    xQueueOverwrite(COLOR2_QUEUE, &color2msg);
    vTaskDelay(1000);
    BUZZER_Clear();
    SERCOM7_USART_ReadCallbackRegister(ESP_CALLBACK, 0);
    SERCOM7_USART_Read(ESP_RX_DATA_t, 1);
    sprintf(buffer, "%0.1f.0 ", FIRMWARE_VERSION);
    Update_MCU_FW_VERSION((uint8_t) buffer[0], (uint8_t) buffer[1], (uint8_t) buffer[2], (uint8_t) buffer[3], (uint8_t) buffer[4], (uint8_t) buffer[5]);
    vTaskDelay(100);
    memset(buffer, 0, sizeof (buffer));
    sprintf(buffer, "%0.1f.0 ", OCPP_VERSION);
    Update_OCPP_FW_VERSION((uint8_t) buffer[0], (uint8_t) buffer[1], (uint8_t) buffer[2], (uint8_t) buffer[3], (uint8_t) buffer[4], (uint8_t) buffer[5]);
    vTaskDelay(100);
    memset(buffer, 0, sizeof (buffer));
    sprintf(buffer, "%0.1f.0 ", PLC1_VERSION);
    Update_PLC1_FW_VERSION((uint8_t) buffer[0], (uint8_t) buffer[1], (uint8_t) buffer[2], (uint8_t) buffer[3], (uint8_t) buffer[4], (uint8_t) buffer[5]);
    vTaskDelay(100);
    memset(buffer, 0, sizeof (buffer));
    sprintf(buffer, "%0.1f.0 ", PLC2_VERSION);
    Update_PLC2_FW_VERSION((uint8_t) buffer[0], (uint8_t) buffer[1], (uint8_t) buffer[2], (uint8_t) buffer[3], (uint8_t) buffer[4], (uint8_t) buffer[5]);
    vTaskDelay(100);
    memset(buffer, 0, sizeof (buffer));
    static uint8_t instance = 0;
    FAN_ON(65535);
    vTaskResume(DATA_POPULATE_TASKHandle);
    vTaskResume(AC_METER_SEND_TASKHandle);
    vTaskResume(ADC_TASKHandle);
    vTaskResume(I2c_TEMP_HUM_TASKHandle);
    vTaskResume(ESP_SEND_TASKHandle);
    vTaskResume(RGB_SEND_TaskHandle);
    Update_Gun1_stop_btn();
    Update_Gun2_stop_btn();
    for (;;) {


        switch (MACHINE_STATE) {
            case IDLE_STATE:
                Update_Controller_Fail_Status(0x00);
                Update_Rectifier1_Fault_Status(0x00);
                Update_Rectifier2_Fault_Status(0x00);
                Update_Rectifier3_Fault_Status(0x00);
                Update_Rectifier4_Fault_Status(0x00);

                if (RGB1_AVAILABLITY_Get()) {
                    Update_LED_Board_Fault1_Status(0x00);
                    vTaskDelay(100);
                } else {
                    ERROR_CODE_ARRAY[LED_BOARD_FAIL_IDX] = 120;
                    ERROR_CODE_ARRAY[LED_CONN_NO] = 1;
                    Update_LED_Board_Fault1_Status(0x01);
                    vTaskDelay(100);
                }
                if (RGB2_AVAILABLITY_Get()) {
                    Update_LED_Board_Fault2_Status(0x00);
                    vTaskDelay(100);
                } else {
                    ERROR_CODE_ARRAY[LED_BOARD_FAIL_IDX] = 120;
                    ERROR_CODE_ARRAY[LED_CONN_NO] = 2;
                    Update_LED_Board_Fault2_Status(0x01);
                    vTaskDelay(100);
                }
                if (RGB1_AVAILABLITY_Get() && RGB2_AVAILABLITY_Get()) {
                    ERROR_CODE_ARRAY[LED_BOARD_FAIL_IDX] = 0;
                }
                if (EMERGENCY_BUT_Get()) {
                    ERROR_CODE_ARRAY[ESD_PRESSED_IDX] = 0;
                    Update_Esd_Pressed_Status(0x00);
                    if (page_change[0] == 1) {
                        page_change[0] = 0;
                        CURRENT_PAGE = INTRO_PAGE;
                        Change_Page_to(CURRENT_PAGE);
                    }
                    vTaskDelay(100);
                } else {
                    START_STOP_AR[0] = 4;
                    ERROR_CODE_ARRAY[ESD_PRESSED_IDX] = 105;
                    Update_Esd_Pressed_Status(0x01);
                    vTaskDelay(100);
                    Update_GUN1_Session_End_Reason(0x05);
                    Update_GUN2_Session_End_Reason(0x05);
                    CURRENT_PAGE = WARNING_PAGE_NUMBER;
                    Change_Page_to(CURRENT_PAGE);
                    page_change[0] = 1;
                    vTaskSuspend(RECTIFIER_TASKHandle);
                    vTaskResume(EMERGENCY_TASKHandle);
                }

                if (GFCI_INT_Get()) {
                    START_STOP_AR[0] = 4;
                    Update_High_Leakage_Current_Status(0x01);
                    vTaskDelay(100);
                    vTaskResume(EMERGENCY_TASKHandle);
                    ERROR_CODE_ARRAY[HIGH_LEAKAGE_IDX] = 109;
                } else {
                    ERROR_CODE_ARRAY[HIGH_LEAKAGE_IDX] = 0;
                    Update_High_Leakage_Current_Status(0x00);
                    vTaskDelay(100);
                }

                if (SPD_RESPONSE_Get()) // Condition to check if SPD is HIGH or LOW
                {
                    ERROR_CODE_ARRAY[SPD_FAULT_IDX] = 0;
                    Update_Spd_Fault_Status(0x00);
                    vTaskDelay(100);
                } else {
                    START_STOP_AR[0] = 4;
                    ERROR_CODE_ARRAY[SPD_FAULT_IDX] = 108;
                    Update_Spd_Fault_Status(0x01);
                    vTaskDelay(100);
                    vTaskResume(EMERGENCY_TASKHandle);
                }
                if (IMD1_RESPONSE_Get()) // Condition to check if SPD is HIGH or LOW
                {
                    START_STOP_AR[0] = 1;
                    START_STOP_AR[2] = 1;
                    ERROR_CODE_ARRAY[ISOLATION_FAIL_IDX] = 119;
                    ERROR_CODE_ARRAY[IMD_FAIL_CONN_NO] = 1;
                    Update_Isolation_Fail1_Status(0x01);
                    vTaskDelay(100);
                    vTaskResume(EMERGENCY_TASKHandle);
                } else {
                    Update_Isolation_Fail1_Status(0x00);
                    vTaskDelay(100);
                }
                if (IMD2_RESPONSE_Get()) // Condition to check if SPD is HIGH or LOW
                {
                    START_STOP_AR1[0] = 2;
                    START_STOP_AR1[2] = 1;
                    ERROR_CODE_ARRAY[ISOLATION_FAIL_IDX] = 119;
                    ERROR_CODE_ARRAY[IMD_FAIL_CONN_NO] = 1;
                    Update_Isolation_Fail2_Status(0x01);
                    vTaskDelay(100);
                    vTaskResume(EMERGENCY_TASKHandle);
                } else {
                    Update_Isolation_Fail2_Status(0x00);
                    vTaskDelay(100);
                }
                if ((!IMD2_RESPONSE_Get()) && (!IMD1_RESPONSE_Get())) {
                    ERROR_CODE_ARRAY[ISOLATION_FAIL_IDX] = 0;
                }
                if (MAINS_HIGH) {
                    ERROR_CODE_ARRAY[MAINS_HIGH_IDX] = 112;
                    Update_Mains_High_Status(0x01);
                    vTaskDelay(100);
                } else {
                    ERROR_CODE_ARRAY[MAINS_HIGH_IDX] = 0;
                    Update_Mains_High_Status(0x00);
                    vTaskDelay(100);
                }
                if (MAINS_LOW) {
                    ERROR_CODE_ARRAY[MAINS_LOW_IDX] = 111;
                    Update_Mains_Low_Status(0x01);
                    vTaskDelay(100);
                } else {
                    ERROR_CODE_ARRAY[MAINS_LOW_IDX] = 0;
                    Update_Mains_Low_Status(0x00);
                    vTaskDelay(100);
                }

                if (plc1_fail) {
                    ERROR_CODE_ARRAY[PLC_COMM_FAIL_IDX] = 106;
                    ERROR_CODE_ARRAY[PLC_COMM_FAIL_CONN_NO] = 1;
                    Update_PLC1_Comm_Fail_Status(0x01);
                    vTaskDelay(100);
                    xTimerStart(plc1_timer, 60000);
                    Change_gun1_status_to(FAULT);
                } else {
                    ERROR_CODE_ARRAY[PLC_COMM_FAIL_IDX] = 0;
                    Update_PLC1_Comm_Fail_Status(0x00);
                    vTaskDelay(100);
                    plc1_fail = 0;
                }
                if (plc2_fail) {
                    ERROR_CODE_ARRAY[PLC_COMM_FAIL_IDX] = 106;
                    ERROR_CODE_ARRAY[PLC_COMM_FAIL_CONN_NO] = 2;
                    Update_PLC2_Comm_Fail_Status(0x01);
                    vTaskDelay(100);
                    xTimerStart(plc2_timer, 60000);
                    Change_gun2_status_to(FAULT);
                } else {
                    ERROR_CODE_ARRAY[PLC_COMM_FAIL_IDX] = 0;
                    Update_PLC2_Comm_Fail_Status(0x00);
                    vTaskDelay(100);
                    plc2_fail = 0;
                }
                if (all_plc_state) {
                    ERROR_CODE_ARRAY[ALL_PLC_COMM_FAIL_IDX] = 134;
                    ERROR_CODE_ARRAY[PLC_COMM_FAIL_CONN_NO] = 0;
                    xTimerStart(all_plc_timer, 60000);
                    Change_Page_to(CURRENT_PAGE);
                    vTaskDelay(100);
                    Change_gun1_status_to(FAULT);
                    Change_gun2_status_to(FAULT);
                    Update_PLC1_Comm_Fail_Status(0x01);
                    vTaskDelay(100);
                    Update_PLC2_Comm_Fail_Status(0x01);
                    vTaskDelay(100);
                } else {
                    ERROR_CODE_ARRAY[ALL_PLC_COMM_FAIL_IDX] = 0;
                    ERROR_CODE_ARRAY[PLC_COMM_FAIL_CONN_NO] = 0;
                    all_plc_count = 0;
                    all_plc_state = 0;
                    Update_PLC1_Comm_Fail_Status(0x00);
                    vTaskDelay(100);
                    Update_PLC2_Comm_Fail_Status(0x00);
                    vTaskDelay(100);
                }

                if (ac_meter_comm) {
                    ERROR_CODE_ARRAY[AC_METER_FAIL_IDX] = 113;
                    Update_ACEM_Comm_Fail_Status(0x01);
                    vTaskDelay(100);
                } else {
                    ERROR_CODE_ARRAY[AC_METER_FAIL_IDX] = 0;
                    Update_ACEM_Comm_Fail_Status(0x00);
                    vTaskDelay(100);
                }
                if (dc1_meter_comm) {

                    ERROR_CODE_ARRAY[DC_METER_COMM_FAIL_IDX] = 133;
                    ERROR_CODE_ARRAY[DC_METER_COMM_FAIL_CONN_NO] = 1;
                    Update_DCEM1_Comm_Fail_Status(0x01);
                    vTaskDelay(100);
                } else {
                    ERROR_CODE_ARRAY[DC_METER_COMM_FAIL_IDX] = 0;
                    Update_DCEM1_Comm_Fail_Status(0x00);
                    vTaskDelay(100);
                }
                if (dc2_meter_comm) {
                    ERROR_CODE_ARRAY[DC_METER_COMM_FAIL_IDX] = 133;
                    ERROR_CODE_ARRAY[DC_METER_COMM_FAIL_CONN_NO] = 2;
                    Update_DCEM2_Comm_Fail_Status(0x01);
                    vTaskDelay(100);
                } else {
                    ERROR_CODE_ARRAY[DC_METER_COMM_FAIL_IDX] = 0;
                    Update_DCEM2_Comm_Fail_Status(0x00);
                    vTaskDelay(100);
                }
                if (dc1_meter_comm && dc2_meter_comm) {
                    ERROR_CODE_ARRAY[DC_METER_COMM_FAIL_IDX] = 0;
                    ERROR_CODE_ARRAY[DC_METER_COMM_FAIL_CONN_NO] = 0;
                    ERROR_CODE_ARRAY[ALL_DC_METER_FAIL_IDX] = 135;
                }
                MACHINE_STATE = PLUGIN_STATE;
                break;
            case PLUGIN_STATE:
                EIC_CallbackRegister(EIC_PIN_5, RGB1_CALLBACK, 0);
                EIC_CallbackRegister(EIC_PIN_6, RGB2_CALLBACK, 0);
                EIC_CallbackRegister(EIC_PIN_1, EMERGENCY_BUTTON_CALLBACK, 0);
                EIC_CallbackRegister(EIC_PIN_2, SPD_DETECTION, 0);
                EIC_CallbackRegister(EIC_PIN_7, IMD1_CALLBACK, 0);
                EIC_CallbackRegister(EIC_PIN_8, IMD2_CALLBACK, 0);
                //                    EIC_CallbackRegister(EIC_PIN_9, LIVE_MAINS_CALLBACK, 0);
                EIC_CallbackRegister(EIC_PIN_12, GFCI_CALLBACK, 0);
                CAN0_RxFifoCallbackRegister(CAN_RX_FIFO_0, APP_CAN_RxFifo0Callback, 0);
                CAN1_RxFifoCallbackRegister(CAN_RX_FIFO_1, APP_CAN_RxFifo1Callback, 0);
                SERCOM2_USART_ReadCallbackRegister(ENERGY_METER_CALLBACK, 0);
                SERCOM2_USART_Read(em_rx_buff, ENERGY_METER_RX_SIZE);
                SERCOM6_USART_ReadCallbackRegister(HMI_CALLBACK, 0);
                SERCOM6_USART_Read(&hmi_rx, RX_SIZE);
                SERCOM7_USART_ReadCallbackRegister(ESP_CALLBACK, 0);
                SERCOM7_USART_Read(ESP_RX_DATA_t, 1);
                SERCOM4_USART_ReadCallbackRegister(RFID_CALLBACK, 0);
                //                SERCOM4_USART_Read(rfid_rx, 1);
                SERCOM4_USART_Read(RFID_DATA, CURRENT_RFID_RX_SIZE);
                MACHINE_STATE = CHARGING_STATE;
                vTaskResume(RFID_SEND_TASKHandle);
                break;
            case CHARGING_STATE:
                if (instance == 0) {

                    xTimerStart(all_plc_timer, 60000);

                    instance = 2;
                }
                break;
                SERCOM5_USART_Write(bootloader_done, sizeof (bootloader_done));
                while (!SERCOM5_USART_TransmitComplete());
        }
        vTaskDelay(3000);
    }
}

void Start_HMI_TX_TASK(void *argument) {
    HMI_SEND_DATA_Q msg;
    for (;;) {

        if (xQueueReceive(HMI_SEND_QUEUE, &msg, 0)) {

            ENABLE_HMI_Set();
            SERCOM6_USART_Write(msg.DATA, (msg.DATA[2] + 3));
            while (!(SERCOM6_USART_TransmitComplete()))
                ;
            ENABLE_HMI_Clear();
        }
        //WDT_Clear();
        vTaskDelay(50);
    }
}

void Start_HMI_RX_TASK(void *argument) {
    HMI_INPUT_Q msg1;
    FLASH_READ_Q flashreadmsg;
    CP_LEVEL1_Q cplevel1;
    CP_LEVEL2_Q cplevel2;
    static uint8_t CP_LEVEL1 = 12;
    static uint8_t CP_LEVEL2 = 12;
    ESP_S_RFID_CONN_NO_Q rfid_conn_no_data;
    char buffer_d[30] = {0};
    uint8_t data[30] = {0};
    static uint8_t idx = 0;
    for (;;) {

        if (xQueueReceive(CP_LEVEL1_QUEUE, &cplevel1, 0)) {
            CP_LEVEL1 = cplevel1.CP_LEVEL1[0];
        }
        if (xQueueReceive(CP_LEVEL2_QUEUE, &cplevel2, 0)) {
            CP_LEVEL2 = cplevel2.CP_LEVEL2[0];
        }
        if (xQueueReceive(HMI_RX_QUEUE, &msg1, 0)) {
            data[idx] = msg1.hmi_buff[0];
            idx++;
            if (idx == 1) {
                xTimerStart(HMI_DATA_T, 25);
            }
        }
        if (hmi_data_flag == 1) {
            idx = 0;
            hmi_data_flag = 0;

            if (data[0] == 0x5A) {
                vTaskSuspend(HMI_SEND_TASKHandle);
                if (data[4] == 0x15 && data[5] == 0x02) {
                    flashreadmsg.WHO_IS_READING = HMI_READ;
                    flashreadmsg.BT_READ_IDX = 0;
                    flashreadmsg.COUNT_READ_INC = 0;
                    flashreadmsg.PAGE_VIEW = 0;
                    xQueueSend(FLASH_READ_QUEUE, &flashreadmsg, 100);
                    vTaskResume(FLASH_READ_TASKHandle);
                }
                if (data[4] == 0x15 && data[5] == 0x03) {
                    flashreadmsg.WHO_IS_READING = HMI_READ;
                    flashreadmsg.BT_READ_IDX = 0;
                    flashreadmsg.COUNT_READ_INC = 0x01;
                    flashreadmsg.PAGE_VIEW = 0;
                    xQueueSend(FLASH_READ_QUEUE, &flashreadmsg, 100);
                    vTaskResume(FLASH_READ_TASKHandle);
                }
                if (data[4] == 0x15 && data[5] == 0x0D) {
                    flashreadmsg.WHO_IS_READING = HMI_READ;
                    flashreadmsg.BT_READ_IDX = 0;
                    flashreadmsg.COUNT_READ_INC = 0x02;
                    flashreadmsg.PAGE_VIEW = 0;
                    xQueueSend(FLASH_READ_QUEUE, &flashreadmsg, 100);
                    vTaskResume(FLASH_READ_TASKHandle);
                }
                if (data[4] == 0x15 && data[5] == 0x04) {
                    flashreadmsg.WHO_IS_READING = HMI_READ;
                    flashreadmsg.BT_READ_IDX = 0;
                    flashreadmsg.PAGE_VIEW = 1;
                    flashreadmsg.COUNT_READ_INC = 0x03;
                    xQueueSend(FLASH_READ_QUEUE, &flashreadmsg, 100);
                    vTaskResume(FLASH_READ_TASKHandle);
                }
                if (data[4] == 0x15 && data[5] == 0x05) {
                    flashreadmsg.WHO_IS_READING = HMI_READ;
                    flashreadmsg.BT_READ_IDX = 0;
                    flashreadmsg.PAGE_VIEW = 2;
                    flashreadmsg.COUNT_READ_INC = 0x03;
                    xQueueSend(FLASH_READ_QUEUE, &flashreadmsg, 100);
                    vTaskResume(FLASH_READ_TASKHandle);
                }
                if (data[4] == 0x15 && data[5] == 0x06) {
                    flashreadmsg.WHO_IS_READING = HMI_READ;
                    flashreadmsg.BT_READ_IDX = 0;
                    flashreadmsg.PAGE_VIEW = 3;
                    flashreadmsg.COUNT_READ_INC = 0x03;
                    xQueueSend(FLASH_READ_QUEUE, &flashreadmsg, 100);
                    vTaskResume(FLASH_READ_TASKHandle);
                }
                if (data[4] == 0x15 && data[5] == 0x07) {
                    flashreadmsg.WHO_IS_READING = HMI_READ;
                    flashreadmsg.BT_READ_IDX = 0;
                    flashreadmsg.PAGE_VIEW = 4;
                    flashreadmsg.COUNT_READ_INC = 0x03;
                    xQueueSend(FLASH_READ_QUEUE, &flashreadmsg, 100);
                    vTaskResume(FLASH_READ_TASKHandle);
                }
                if (data[4] == 0x15 && data[5] == 0x08) {
                    flashreadmsg.WHO_IS_READING = HMI_READ;
                    flashreadmsg.BT_READ_IDX = 0;
                    flashreadmsg.PAGE_VIEW = 5;
                    flashreadmsg.COUNT_READ_INC = 0x03;
                    xQueueSend(FLASH_READ_QUEUE, &flashreadmsg, 100);
                    vTaskResume(FLASH_READ_TASKHandle);
                }
                if (data[4] == 0x15 && data[5] == 0x09) {
                    flashreadmsg.WHO_IS_READING = HMI_READ;
                    flashreadmsg.BT_READ_IDX = 0;
                    flashreadmsg.PAGE_VIEW = 6;
                    flashreadmsg.COUNT_READ_INC = 0x03;
                    xQueueSend(FLASH_READ_QUEUE, &flashreadmsg, 100);
                    vTaskResume(FLASH_READ_TASKHandle);
                }
                if (data[4] == 0x15 && data[5] == 0x0A) {
                    flashreadmsg.WHO_IS_READING = HMI_READ;
                    flashreadmsg.BT_READ_IDX = 0;
                    flashreadmsg.PAGE_VIEW = 7;
                    flashreadmsg.COUNT_READ_INC = 0x03;
                    xQueueSend(FLASH_READ_QUEUE, &flashreadmsg, 100);
                    vTaskResume(FLASH_READ_TASKHandle);
                }
                if (data[4] == 0x15 && data[5] == 0x0B) {
                    flashreadmsg.WHO_IS_READING = HMI_READ;
                    flashreadmsg.BT_READ_IDX = 0;
                    flashreadmsg.PAGE_VIEW = 8;
                    flashreadmsg.COUNT_READ_INC = 0x03;
                    xQueueSend(FLASH_READ_QUEUE, &flashreadmsg, 100);
                    vTaskResume(FLASH_READ_TASKHandle);
                }
                if (data[4] == 0x12 && data[5] == 0x08) {
                    if (CP_LEVEL1 <= 9 && CP_LEVEL1 > 6) {
                        Change_Page_to(GUN1_AUTHENTICATION_PAGE);
                    }
                    if (CP_LEVEL1 <= 6 && CP_LEVEL1 >= 2) {
                        Change_Page_to(GUN1_PARAM_PAGE);
                    }
                    rfid_conn_no_data.RFID_CONN_NO[0] = CONNECTOR_NO_1;
                    xQueueOverwrite(ESP_S_RFID_CONN_NO_QUEUE, &rfid_conn_no_data);
                }
                if (data[4] == 0x12 && data[5] == 0x09) {
                    if (CP_LEVEL2 <= 9 && CP_LEVEL2 > 6) {
                        Change_Page_to(GUN2_AUTHENTICATION_PAGE);
                    }
                    if (CP_LEVEL2 <= 6 && CP_LEVEL2 >= 2) {
                        Change_Page_to(GUN2_PARAM_PAGE);
                    }
                    rfid_conn_no_data.RFID_CONN_NO[0] = CONNECTOR_NO_2;
                    xQueueOverwrite(ESP_S_RFID_CONN_NO_QUEUE, &rfid_conn_no_data);
                }
                if (data[4] == 0x12 && data[5] == 0x0A) {
                    if ((START_BY1 == BY_RFID)) {
                        Change_Page_to(GUN1_RFID_STOP_PAGE);
                    }
                    if ((START_BY1 == BY_REMOTE)) {
                        Change_Page_to(GUN1_MOBILE_STOP_PAGE);
                    }
                }
                if (data[4] == 0x12 && data[5] == 0x0D) {
                    if ((START_BY2 == BY_RFID)) {
                        Change_Page_to(GUN2_RFID_STOP_PAGE);
                    }
                    if ((START_BY2 == BY_REMOTE)) {
                        Change_Page_to(GUN2_MOBILE_STOP_PAGE);
                    }
                }
                if (data[4] == 0x12 && data[5] == 0x17) {
                    GUN1_summary_close_flag = 1;
                    CURRENT_PAGE = INTRO_PAGE;
                    Change_Page_to(CURRENT_PAGE);
                }
                if (data[4] == 0x12 && data[5] == 0x18) {
                    GUN2_summary_close_flag = 1;
                    CURRENT_PAGE = INTRO_PAGE;
                    Change_Page_to(CURRENT_PAGE);
                }
                if (data[4] == 0x12 && data[5] == 0x15) {
                    Change_Page_to(CURRENT_PAGE);
                }
                if (data[4] == 0x12 && data[5] == 0x16) {
                    Change_Page_to(CURRENT_PAGE);
                }
                vTaskResume(HMI_SEND_TASKHandle);
            }
        }
        vTaskDelay(1);
    }
}

void Start_50msecTask(void *argument) {
    _50MS_Q _50msMsg;
    memset(_50msMsg.DATA, 0, sizeof (_50msMsg.DATA));
    static uint8_t _002_TXDATA[8] = {0};
    static uint8_t _005_TXDATA[8] = {0};
    static uint8_t _006_TXDATA[8] = {0};
    static uint8_t _007_TXDATA[8] = {0};
    static uint8_t _402_TXDATA[8] = {0};
    static uint8_t _405_TXDATA[8] = {0};
    static uint8_t _406_TXDATA[8] = {0};
    static uint8_t _407_TXDATA[8] = {0};
    for (;;) {


        if (GUN1_50_clear == 1) {
            memset(_002_TXDATA, 0, sizeof (_002_TXDATA));
            memset(_005_TXDATA, 0, sizeof (_005_TXDATA));
            memset(_006_TXDATA, 0, sizeof (_006_TXDATA));
            memset(_007_TXDATA, 0, sizeof (_007_TXDATA));
            GUN1_50_clear = 0;
        }
        if (GUN2_50_clear == 1) {
            memset(_402_TXDATA, 0, sizeof (_402_TXDATA));
            memset(_405_TXDATA, 0, sizeof (_405_TXDATA));
            memset(_406_TXDATA, 0, sizeof (_406_TXDATA));
            memset(_407_TXDATA, 0, sizeof (_407_TXDATA));
            GUN2_50_clear = 0;
        }
        if (xQueueReceive(_50msQUEUE, &_50msMsg, 0)) {

            switch (_50msMsg.ID_t) {
                case _002:
                    memcpy(_002_TXDATA, _50msMsg.DATA, 8);
                    break;
                case _005:
                    memcpy(_005_TXDATA, _50msMsg.DATA, 8);
                    break;
                case _006:
                    memcpy(_006_TXDATA, _50msMsg.DATA, 8);
                    break;
                case _007:
                    memcpy(_007_TXDATA, _50msMsg.DATA, 8);
                    break;
                case _402:
                    memcpy(_402_TXDATA, _50msMsg.DATA, 8);
                    break;
                case _405:
                    memcpy(_405_TXDATA, _50msMsg.DATA, 8);
                    break;
                case _406:
                    memcpy(_406_TXDATA, _50msMsg.DATA, 8);
                    break;
                case _407:
                    memcpy(_407_TXDATA, _50msMsg.DATA, 8);

                    break;
            }
        }

        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) txFiFo;
        txBuffer->xtd = 1;
        txBuffer->id = _002;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _002_TXDATA, 8);
        txBuffer->data[0] = heartbeat++;
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) (txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _005;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _005_TXDATA, 8);
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) (txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _006;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _006_TXDATA, 8);
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) ((uint32_t) txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _007;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _007_TXDATA, 8);
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) txFiFo;
        txBuffer->xtd = 1;
        txBuffer->id = _402;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _402_TXDATA, 8);
        txBuffer->data[0] = heartbeat++;
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) (txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _405;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _405_TXDATA, 8);
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) (txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _406;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _406_TXDATA, 8);
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) ((uint32_t) txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _407;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _407_TXDATA, 8);
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        vTaskSuspend(_50msecTask);
        vTaskDelay(1);
    }
}

void Start_200msecTask(void *argument) {
    _200MS_Q _200msmsg;
    memset(_200msmsg.DATA, 0, sizeof (_200msmsg.DATA));
    static uint8_t _001_TXDATA[8] = {0};
    static uint8_t _003_TXDATA[8] = {0};
    static uint8_t _004_TXDATA[8] = {0};
    static uint8_t _401_TXDATA[8] = {0};
    static uint8_t _403_TXDATA[8] = {0};
    static uint8_t _404_TXDATA[8] = {0};
    for (;;) {


        if (GUN1_200_clear == 1) {
            memset(_001_TXDATA, 0, sizeof (_001_TXDATA));
            memset(_003_TXDATA, 0, sizeof (_003_TXDATA));
            memset(_004_TXDATA, 0, sizeof (_004_TXDATA));

            GUN1_200_clear = 0;
        }
        if (GUN2_200_clear == 1) {
            memset(_401_TXDATA, 0, sizeof (_401_TXDATA));
            memset(_403_TXDATA, 0, sizeof (_403_TXDATA));
            memset(_404_TXDATA, 0, sizeof (_404_TXDATA));

            GUN2_200_clear = 0;
        }
        if (xQueueReceive(_200msQUEUE, &_200msmsg, 0)) {

            switch (_200msmsg.ID_t) {
                case _001:
                    memcpy(_001_TXDATA, _200msmsg.DATA, 8);
                    break;
                case _003:
                    memcpy(_003_TXDATA, _200msmsg.DATA, 8);
                    break;
                case _004:
                    memcpy(_004_TXDATA, _200msmsg.DATA, 8);
                    break;
                case _401:
                    memcpy(_401_TXDATA, _200msmsg.DATA, 8);
                    break;
                case _403:
                    memcpy(_403_TXDATA, _200msmsg.DATA, 8);
                    break;
                case _404:
                    memcpy(_404_TXDATA, _200msmsg.DATA, 8);

                    break;
            }
        }
        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) (txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _001;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _001_TXDATA, 8);
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) (txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _003;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _003_TXDATA, 8);
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) (txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _004;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _004_TXDATA, 8);
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);

        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) (txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _401;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _401_TXDATA, 8);
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) (txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _403;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _403_TXDATA, 8);
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) (txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _404;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _404_TXDATA, 8);
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        vTaskSuspend(_200msecTask);
        vTaskDelay(1);
    }
}

void Start_500msecTask(void *argument) {
    _500MS_Q _500msMsg;
    memset(_500msMsg.DATA, 0, sizeof (_500msMsg.DATA));
    static uint8_t _008_TXDATA[8] = {0};
    static uint8_t _009_TXDATA[8] = {0};
    static uint8_t _00A_TXDATA[8] = {0};
    static uint8_t _00B_TXDATA[8] = {0};
    static uint8_t _00C_TXDATA[8] = {0};
    static uint8_t _00D_TXDATA[8] = {0};
    static uint8_t _408_TXDATA[8] = {0};
    static uint8_t _409_TXDATA[8] = {0};
    static uint8_t _40A_TXDATA[8] = {0};
    static uint8_t _40B_TXDATA[8] = {0};
    static uint8_t _40C_TXDATA[8] = {0};
    static uint8_t _40D_TXDATA[8] = {0};
    for (;;) {

        if (GUN1_500_clear == 1) {
            memset(_008_TXDATA, 0, sizeof (_008_TXDATA));
            memset(_009_TXDATA, 0, sizeof (_009_TXDATA));
            memset(_00A_TXDATA, 0, sizeof (_00A_TXDATA));
            memset(_00B_TXDATA, 0, sizeof (_00B_TXDATA));
            memset(_00C_TXDATA, 0, sizeof (_00C_TXDATA));
            memset(_00D_TXDATA, 0, sizeof (_00D_TXDATA));
            GUN1_500_clear = 0;
        }
        if (GUN2_500_clear == 1) {
            memset(_408_TXDATA, 0, sizeof (_408_TXDATA));
            memset(_409_TXDATA, 0, sizeof (_409_TXDATA));
            memset(_40A_TXDATA, 0, sizeof (_40A_TXDATA));
            memset(_40B_TXDATA, 0, sizeof (_40B_TXDATA));
            memset(_40C_TXDATA, 0, sizeof (_40C_TXDATA));
            memset(_40D_TXDATA, 0, sizeof (_40D_TXDATA));
            GUN2_500_clear = 0;
        }
        if (xQueueReceive(_500msQUEUE, &_500msMsg, 0)) {

            switch (_500msMsg.ID_t) {
                case _008:
                    memcpy(_008_TXDATA, _500msMsg.DATA, 8);
                    break;
                case _009:
                    memcpy(_009_TXDATA, _500msMsg.DATA, 8);
                    break;
                case _00A:
                    memcpy(_00A_TXDATA, _500msMsg.DATA, 8);
                    break;
                case _00B:
                    memcpy(_00B_TXDATA, _500msMsg.DATA, 8);
                    break;
                case _00C:
                    memcpy(_00C_TXDATA, _500msMsg.DATA, 8);
                    break;
                case _00D:
                    memcpy(_00D_TXDATA, _500msMsg.DATA, 8);
                    break;
                case _408:
                    memcpy(_408_TXDATA, _500msMsg.DATA, 8);
                    break;
                case _409:
                    memcpy(_409_TXDATA, _500msMsg.DATA, 8);
                    break;
                case _40A:
                    memcpy(_40A_TXDATA, _500msMsg.DATA, 8);
                    break;
                case _40B:
                    memcpy(_40B_TXDATA, _500msMsg.DATA, 8);
                    break;
                case _40C:
                    memcpy(_40C_TXDATA, _500msMsg.DATA, 8);
                    break;
                case _40D:
                    memcpy(_40D_TXDATA, _500msMsg.DATA, 8);

                    break;
            }
        }
        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) (txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _008;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _008_TXDATA, 8);
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) (txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _009;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _009_TXDATA, 8);
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) (txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _00A;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _00A_TXDATA, 8);
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) (txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _00B;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _00B_TXDATA, 8);
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) (txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _00C;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _00C_TXDATA, 8);
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) (txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _00D;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _00D_TXDATA, 8);
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);

        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) (txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _408;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _408_TXDATA, 8);
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) (txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _409;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _409_TXDATA, 8);
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) (txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _40A;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _40A_TXDATA, 8);
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) (txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _40B;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _40B_TXDATA, 8);
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) (txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _40C;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _40C_TXDATA, 8);
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) (txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _40D;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _40D_TXDATA, 8);
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        vTaskSuspend(_500msecTask);
        vTaskDelay(1);
    }
}

void Start_1000msecTask(void *argument) {
    _1000MS_Q _1000msMsg;
    memset(_1000msMsg.DATA, 0, sizeof (_1000msMsg.DATA));
    static uint8_t _ECD001_TXDATA[8] = {0};
    static uint8_t _ECD002_TXDATA[8] = {0};
    static uint8_t _ECD003_TXDATA[8] = {0};
    static uint8_t _ECD401_TXDATA[8] = {0};
    static uint8_t _ECD402_TXDATA[8] = {0};
    static uint8_t _ECD403_TXDATA[8] = {0};

    for (;;) {

        if (GUN1_1000_clear == 1) {
            memset(_ECD001_TXDATA, 0, sizeof (_ECD001_TXDATA));
            memset(_ECD002_TXDATA, 0, sizeof (_ECD002_TXDATA));
            memset(_ECD003_TXDATA, 0, sizeof (_ECD003_TXDATA));
            GUN1_1000_clear = 0;
        }
        if (GUN1_1000_clear == 1) {
            memset(_ECD401_TXDATA, 0, sizeof (_ECD401_TXDATA));
            memset(_ECD402_TXDATA, 0, sizeof (_ECD402_TXDATA));
            memset(_ECD403_TXDATA, 0, sizeof (_ECD403_TXDATA));
            GUN2_1000_clear = 0;
        }
        if (xQueueReceive(_1000msQUEUE, &_1000msMsg, 0)) {

            switch (_1000msMsg.ID_t) {
                case _D001:
                    memcpy(_ECD001_TXDATA, _1000msMsg.DATA, 8);
                    break;
                case _D002:
                    memcpy(_ECD002_TXDATA, _1000msMsg.DATA, 8);
                    break;
                case _D003:
                    memcpy(_ECD003_TXDATA, _1000msMsg.DATA, 8);
                    break;
                case _D401:
                    memcpy(_ECD401_TXDATA, _1000msMsg.DATA, 8);
                    break;
                case _D402:
                    memcpy(_ECD402_TXDATA, _1000msMsg.DATA, 8);
                    break;
                case _D403:
                    memcpy(_ECD403_TXDATA, _1000msMsg.DATA, 8);

                    break;
            }
        }
        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) (txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _D001;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _ECD001_TXDATA, 8);
        _ECD001_TXDATA[0] = 127;
        _ECD001_TXDATA[3] = 1;
        _ECD001_TXDATA[4] = (SA_Agent >> 8);
        _ECD001_TXDATA[5] = SA_Agent;
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) (txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _D002;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _ECD002_TXDATA, 8);
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) (txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _D003;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _ECD003_TXDATA, 8);
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);

        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) (txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _D401;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _ECD401_TXDATA, 8);
        _ECD401_TXDATA[0] = 127;
        _ECD401_TXDATA[3] = 1;
        _ECD401_TXDATA[4] = (SA_Agent >> 8);
        _ECD401_TXDATA[5] = SA_Agent;
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) (txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _D402;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _ECD402_TXDATA, 8);
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        memset(txFiFo, 0x00, CAN0_TX_FIFO_BUFFER_SIZE);
        txBuffer = (CAN_TX_BUFFER *) (txFiFo);
        txBuffer->xtd = 1;
        txBuffer->id = _D403;
        txBuffer->dlc = 8;
        memcpy(txBuffer->data, _ECD403_TXDATA, 8);
        CAN0_MessageTransmitFifo(1, (CAN_TX_BUFFER *) (txBuffer));
        vTaskDelay(1);
        vTaskSuspend(_1000msecTask);
        vTaskDelay(1);
    }
}

void Start_ESP_SEND_TASK(void *argument) {

    static ESP_Q_DATA txdata;
    memset(txdata.ESP_ARRAY, 0, sizeof (txdata.ESP_ARRAY));
    txdata.FW_Version = (uint32_t) FIRMWARE_VERSION;
    //    char buffer[30];
    ESP_S_GROUND_M_V_Q esp_s_ground_m_v;
    ESP_S_TEMP_Q esp_s_temp;
    ESP_S_ERROR_W_Q esp_s_error_data;
    ESP_S_GUN1_P_Q esp_s_gun1_p;
    ESP_S_GUN2_P_Q esp_s_gun2_p;
    ESP_S_METER_D_Q esp_s_meter_data;
    ESP_S_BT_Q esp_s_bt_data;
    ESP_S_RFID_Q rfid_data;
    ESP_S_RFID_CONN_NO_Q rfid_conn_no_data;
    ESP_S_MAC_ID_CONN_NO_Q mac_id_conn_no_data;
    ESP_S_MAC_ID_Q mac_id_data;
    ESP_S_REC_TEMP_Q esp_s_temp_data;
    xTimerStart(modem_timer, 40000);
    for (;;) {

        if (xQueueReceive(ESP_S_BT_QUEUE, &esp_s_bt_data, 0)) {
            txdata.IDX = esp_s_bt_data.IDX;
            txdata.IDX_DATA = esp_s_bt_data.IDX_DATA;
        }
        txdata.Start_bit = START_BIT;
        txdata.Stop_bit = STOP_BIT;
        if (xQueueReceive(ESP_S_GUN1_P_QUEUE, &esp_s_gun1_p, 0)) {
            txdata.SOC_1 = esp_s_gun1_p.SOC_1;
            txdata.CP_Level_1 = esp_s_gun1_p.CP_Level_1;
            txdata.Demand_Current1 = esp_s_gun1_p.Demand_Current1;
            txdata.Demand_Volatge1 = esp_s_gun1_p.Demand_Volatge1;
            txdata.Initial_SOC1 = esp_s_gun1_p.Initial_SOC1;
        }

        if (xQueueReceive(ESP_S_GUN2_P_QUEUE, &esp_s_gun2_p, 0)) {
            txdata.SOC_2 = esp_s_gun2_p.SOC_2;
            txdata.CP_Level_2 = esp_s_gun2_p.CP_Level_2;
            txdata.Demand_Current2 = esp_s_gun2_p.Demand_Current2;
            txdata.Demand_Volatge2 = esp_s_gun2_p.Demand_Volatge2;
            txdata.Initial_SOC2 = esp_s_gun2_p.Initial_SOC2;
        }

        if (xQueueReceive(ESP_S_ERROR_W_QUEUE, &esp_s_error_data, 0)) {
            txdata.Error_Code0 = esp_s_error_data.Error_Code0;
            txdata.Error_Code1 = esp_s_error_data.Error_Code1;
            txdata.Error_Code2 = esp_s_error_data.Error_Code2;
            txdata.Warning_Code0 = esp_s_error_data.Warning_Code0;
            txdata.Warning_Code1 = esp_s_error_data.Warning_Code1;
            txdata.Warning_Code2 = esp_s_error_data.Warning_Code2;
        }

        if (xQueueReceive(ESP_S_RFID_QUEUE, &rfid_data, 0)) {
            memcpy(txdata.RFID_ID, rfid_data.RFID_IS, RFID_DATA_FOR_ESP_SIZE);
            //            memcpy(txdata.RFID_ID, rfid_data.RFID_IS, 4);
        }
        //        txdata.RFID_ID[0] = 0x04;
        //        txdata.RFID_ID[1] = RFID_ID_RECEIVED[0];
        //        txdata.RFID_ID[2] = RFID_ID_RECEIVED[1];
        //        txdata.RFID_ID[3] = RFID_ID_RECEIVED[2];
        //        txdata.RFID_ID[4] = RFID_ID_RECEIVED[3];
        //        memcpy(txdata.RFID_ID,RFID_ID_RECEIVED,4);
        if (xQueueReceive(ESP_S_RFID_CONN_NO_QUEUE, &rfid_conn_no_data, 0)) {
            txdata.rfid_conn_no = rfid_conn_no_data.RFID_CONN_NO[0];
        }

        memcpy(txdata.OTP, OTP, 4);

        if (xQueueReceive(ESP_S_GROUND_M_V_QUEUE, &esp_s_ground_m_v, 0)) {
            txdata.Ground_Monitor_volt = esp_s_ground_m_v.Ground_Monitor_volt;
        }
        if (xQueueReceive(ESP_S_TEMP_QUEUE, &esp_s_temp, 0)) {
            txdata.body_temp = esp_s_temp.body_temp;
            txdata.Gun_temp_1 = esp_s_temp.Gun_temp_1;
            txdata.Gun_temp_1_1 = esp_s_temp.Gun_temp_1_1;
            txdata.Gun_temp_2 = esp_s_temp.Gun_temp_2;
            txdata.Gun_temp_2_1 = esp_s_temp.Gun_temp_2_1;
        }

        if (xQueueReceive(ESP_S_MAC_ID_QUEUE, &mac_id_data, 0)) {
            memcpy(txdata.MAC_ID, mac_id_data.MAC_ID_IS, MAC_ID_DATA_SIZE_FOR_ESP);
        }
        if (xQueueReceive(ESP_S_MAC_ID_CONN_NO_QUEUE, &mac_id_conn_no_data, 0)) {
            txdata.MAC_ID_CONN_NO = mac_id_conn_no_data.MAC_ID_CONN_NO[0];
        }

        txdata.Stop_Code = Stop_Code;
        txdata.Stop_connector_no = Stop_connector_no;

        if (xQueueReceive(ESP_S_METER_D_QUEUE, &esp_s_meter_data, 0)) {
            txdata.AC_CURRENT_L1 = esp_s_meter_data.AC_CURRENT_L1;
            txdata.AC_CURRENT_L2 = esp_s_meter_data.AC_CURRENT_L2;
            txdata.AC_CURRENT_L3 = esp_s_meter_data.AC_CURRENT_L3;
            txdata.AC_FREQUENCY = esp_s_meter_data.AC_FREQUENCY;
            txdata.AC_VOLT_L1 = esp_s_meter_data.AC_VOLT_L1;
            txdata.AC_VOLT_L2 = esp_s_meter_data.AC_VOLT_L2;
            txdata.AC_VOLT_L3 = esp_s_meter_data.AC_VOLT_L3;
            txdata.DC1_CURRENT = esp_s_meter_data.DC1_CURRENT;
            txdata.DC1_IMPORT_ENERGY = esp_s_meter_data.DC1_IMPORT_ENERGY;
            txdata.DC1_VOLTAGE = esp_s_meter_data.DC1_VOLTAGE;
            txdata.DC2_CURRENT = esp_s_meter_data.DC2_CURRENT;
            txdata.DC2_VOLTAGE = esp_s_meter_data.DC2_VOLTAGE;
            txdata.DC2_IMPORT_ENERGY = esp_s_meter_data.DC2_IMPORT_ENERGY;
            txdata.AC_POWER = esp_s_meter_data.AC_POWER;
            txdata.DC1_POWER = esp_s_meter_data.DC1_POWER;
            txdata.DC2_POWER = esp_s_meter_data.DC2_POWER;
            txdata.AC_ENERGY = esp_s_meter_data.AC_ENERGY;
        }
        if (xQueueReceive(ESP_S_REC_TEMP_QUEUE, &esp_s_temp_data, 0)) {
            txdata.REC_Group1 = esp_s_temp_data.rec_group1;
            txdata.REC_Group2 = esp_s_temp_data.rec_group2;
        }

        SERCOM7_USART_Write(txdata.ESP_ARRAY, sizeof (txdata.ESP_ARRAY));
        while (!(SERCOM7_USART_TransmitComplete()))
            ;
        if (txdata.Error_Code0 == 101) {
            vTaskSuspend(defaultTaskHandle);
            vTaskSuspend(simulatortask);
            vTaskSuspend(_50msecTask);
            vTaskSuspend(_200msecTask);
            vTaskSuspend(_500msecTask);
            vTaskSuspend(_1000msecTask);
            vTaskSuspend(RECTIFIER_TASKHandle);
            vTaskSuspend(_1_PLC_MANAGE_TASKHandle);
            vTaskSuspend(_2_PLC_MANAGE_TASKHandle);
            vTaskSuspend(AC_METER_SEND_TASKHandle);
            vTaskSuspend(DC1_METER_SEND_TASKHandle);
            vTaskSuspend(DC2_METER_SEND_TASKHandle);
            vTaskSuspend(RFID_SEND_TASKHandle);
            vTaskSuspend(ADC_TASKHandle);
            vTaskSuspend(RGB_SEND_TaskHandle);
            vTaskSuspend(HMI_RX_TASKHandle);
            vTaskSuspend(SMOKE_LIMIT_TASKHandle);
            vTaskSuspend(ERROR_CODE_TASKHandle);
            vTaskSuspend(I2c_TEMP_HUM_TASKHandle);
            vTaskSuspend(METER_RECEIVE_TaskHandle);
            vTaskSuspend(RFID_RX_TASKHandle);
            vTaskSuspend(ESP_RX_TASKHandle);
            vTaskSuspend(canrecievetask);
            vTaskSuspend(EMERGENCY_TASKHandle);
            vTaskSuspend(SMOKE_LIMIT_TASKHandle);
            vTaskSuspend(LED_TASKHandle);
            vTaskSuspend(GUN1_PARAM_TASKHandle);
            vTaskSuspend(GUN2_PARAM_TASKHandle);
            vTaskResume(MAINS_TASKHandle);
            vTaskSuspend(ESP_SEND_TASKHandle);
        }
        vTaskDelay(1500);
    }
}

void Start_ESP_RX_TASK(void *argument) {
    ESP_RX_DATA esprxdata;
    FLASH_WRITE_Q flashmsg;
    FLASH_READ_Q flashreadmsg;
    LED1_Q leddata;

    memset(esprxdata.DATA_ARRAY, 0, sizeof (esprxdata.DATA_ARRAY));
    ESP_RX_Q esprxdata_t;
    char buffer[70];
    static uint32_t rssi = 0;
    uint8_t OCPP_ID_t[30];
    uint8_t BLE_ID_t[30];

    uint8_t wifi_state = 0;
    uint8_t rssi_state = 0;
    ESP_S_RFID_Q rfid_data;
    static uint8_t i = 0;
    uint8_t ESP_DATA_t[80] = {0};
    for (;;) {

        if (xQueueReceive(ESP_RX_QUEUE, &esprxdata_t, 0)) {
            ESP_DATA_t[i] = esprxdata_t.ESP_DATA[0];
            i++;
            if (i == 1) {
                xTimerStart(esp_data_timer, 200);
            }
        }
        if (esp_data_flag == 1) {
            //            SERCOM5_USART_Write(ESP_DATA_t, sizeof (ESP_DATA_t));
            //            while (!(SERCOM5_USART_TransmitComplete()));
            xTimerStop(modem_timer, 10);
            Update_Modem_Comm_Fail_Status(0x00);
            xTimerStart(modem_timer, 40000);
            i = 0;
            esp_data_flag = 0;
            memcpy(esprxdata.DATA_ARRAY, ESP_DATA_t, sizeof (esprxdata.DATA_ARRAY));
            if (esprxdata.Start_bit == START_BIT && esprxdata.Stop_bit == STOP_BIT) {
                if (esprxdata.ID_S[0] == OCPP_ID) {
                    memcpy(OCPP_ID_t, &esprxdata.ID_S[1], 30);
                    flashmsg.WHAT_TYPE_OF_DATA = BT_DATA;
                    flashmsg.DATA_IDX = OCPP_ID_IDX;
                    flashmsg.ID_DATA[0] = ((uint32_t) OCPP_ID_t[0] << 24 & 0xFF000000) | ((uint32_t) OCPP_ID_t[1] << 16 & 0x00FF0000) | ((uint32_t) OCPP_ID_t[2] << 8 & 0x0000FF00) | ((uint32_t) OCPP_ID_t[3] & 0x000000FF);
                    flashmsg.ID_DATA[1] = ((uint32_t) OCPP_ID_t[4] << 24 & 0xFF000000) | ((uint32_t) OCPP_ID_t[5] << 16 & 0x00FF0000) | ((uint32_t) OCPP_ID_t[6] << 8 & 0x0000FF00) | ((uint32_t) OCPP_ID_t[7] & 0x000000FF);
                    flashmsg.ID_DATA[2] = ((uint32_t) OCPP_ID_t[8] << 24 & 0xFF000000) | ((uint32_t) OCPP_ID_t[9] << 16 & 0x00FF0000) | ((uint32_t) OCPP_ID_t[10] << 8 & 0x0000FF00) | ((uint32_t) OCPP_ID_t[11] & 0x000000FF);
                    flashmsg.ID_DATA[3] = ((uint32_t) OCPP_ID_t[12] << 24 & 0xFF000000) | ((uint32_t) OCPP_ID_t[13] << 16 & 0x00FF0000) | ((uint32_t) OCPP_ID_t[14] << 8 & 0x0000FF00) | ((uint32_t) OCPP_ID_t[15] & 0x000000FF);
                    flashmsg.ID_DATA[4] = ((uint32_t) OCPP_ID_t[16] << 24 & 0xFF000000) | ((uint32_t) OCPP_ID_t[17] << 16 & 0x00FF0000) | ((uint32_t) OCPP_ID_t[18] << 8 & 0x0000FF00) | ((uint32_t) OCPP_ID_t[19] & 0x000000FF);
                    flashmsg.ID_DATA[5] = ((uint32_t) OCPP_ID_t[20] << 24 & 0xFF000000) | ((uint32_t) OCPP_ID_t[21] << 16 & 0x00FF0000) | ((uint32_t) OCPP_ID_t[22] << 8 & 0x0000FF00) | ((uint32_t) OCPP_ID_t[23] & 0x000000FF);
                    flashmsg.ID_DATA[6] = ((uint32_t) OCPP_ID_t[24] << 24 & 0xFF000000) | ((uint32_t) OCPP_ID_t[25] << 16 & 0x00FF0000) | ((uint32_t) OCPP_ID_t[26] << 8 & 0x0000FF00) | ((uint32_t) OCPP_ID_t[27] & 0x000000FF);
                    flashmsg.ID_DATA[7] = ((uint32_t) OCPP_ID_t[28] << 24 & 0xFF000000) | ((uint32_t) OCPP_ID_t[29] << 16 & 0x00FF0000) | ((uint32_t) OCPP_ID_t[28] << 8 & 0x0000FF00) | ((uint32_t) OCPP_ID_t[29] & 0x000000FF);
                    xQueueSend(FLASH_WRITE_QUEUE, &flashmsg, 100);
                    vTaskResume(FLASH_WRITE_TASKHandle);
                }
                if (esprxdata.ID_S[0] == BLE_ID) {
                    memcpy(BLE_ID_t, &esprxdata.ID_S[1], 30);
                    flashmsg.WHAT_TYPE_OF_DATA = BT_DATA;
                    flashmsg.DATA_IDX = BLE_ID_IDX;
                    flashmsg.ID_DATA[0] = ((uint32_t) BLE_ID_t[0] << 24 & 0xFF000000) | ((uint32_t) BLE_ID_t[1] << 16 & 0x00FF0000) | ((uint32_t) BLE_ID_t[2] << 8 & 0x0000FF00) | ((uint32_t) BLE_ID_t[3] & 0x000000FF);
                    flashmsg.ID_DATA[1] = ((uint32_t) BLE_ID_t[4] << 24 & 0xFF000000) | ((uint32_t) BLE_ID_t[5] << 16 & 0x00FF0000) | ((uint32_t) BLE_ID_t[6] << 8 & 0x0000FF00) | ((uint32_t) BLE_ID_t[7] & 0x000000FF);
                    flashmsg.ID_DATA[2] = ((uint32_t) BLE_ID_t[8] << 24 & 0xFF000000) | ((uint32_t) BLE_ID_t[9] << 16 & 0x00FF0000) | ((uint32_t) BLE_ID_t[10] << 8 & 0x0000FF00) | ((uint32_t) BLE_ID_t[11] & 0x000000FF);
                    flashmsg.ID_DATA[3] = ((uint32_t) BLE_ID_t[12] << 24 & 0xFF000000) | ((uint32_t) BLE_ID_t[13] << 16 & 0x00FF0000) | ((uint32_t) BLE_ID_t[14] << 8 & 0x0000FF00) | ((uint32_t) BLE_ID_t[15] & 0x000000FF);
                    flashmsg.ID_DATA[4] = ((uint32_t) BLE_ID_t[16] << 24 & 0xFF000000) | ((uint32_t) BLE_ID_t[17] << 16 & 0x00FF0000) | ((uint32_t) BLE_ID_t[18] << 8 & 0x0000FF00) | ((uint32_t) BLE_ID_t[19] & 0x000000FF);
                    flashmsg.ID_DATA[5] = ((uint32_t) BLE_ID_t[20] << 24 & 0xFF000000) | ((uint32_t) BLE_ID_t[21] << 16 & 0x00FF0000) | ((uint32_t) BLE_ID_t[22] << 8 & 0x0000FF00) | ((uint32_t) BLE_ID_t[23] & 0x000000FF);
                    flashmsg.ID_DATA[6] = ((uint32_t) BLE_ID_t[24] << 24 & 0xFF000000) | ((uint32_t) BLE_ID_t[25] << 16 & 0x00FF0000) | ((uint32_t) BLE_ID_t[26] << 8 & 0x0000FF00) | ((uint32_t) BLE_ID_t[27] & 0x000000FF);
                    flashmsg.ID_DATA[7] = ((uint32_t) BLE_ID_t[28] << 24 & 0xFF000000) | ((uint32_t) BLE_ID_t[29] << 16 & 0x00FF0000) | ((uint32_t) BLE_ID_t[28] << 8 & 0x0000FF00) | ((uint32_t) BLE_ID_t[29] & 0x000000FF);
                    xQueueSend(FLASH_WRITE_QUEUE, &flashmsg, 100);
                    vTaskResume(FLASH_WRITE_TASKHandle);
                }
                if (esprxdata.restart == 1) {
                    NVIC_SystemReset();
                }
                if (esprxdata.bootloader == 1) {
                    sprintf(buffer, "BOOTLOADER bit is recieved from esp \r\n");
                    SERCOM5_USART_Write(buffer, sizeof (buffer));
                    while (!(SERCOM5_USART_TransmitComplete()))
                        ;

                    ramStart[0] = BTL_TRIGGER_PATTERN;
                    ramStart[1] = BTL_TRIGGER_PATTERN;
                    ramStart[2] = BTL_TRIGGER_PATTERN;
                    ramStart[3] = BTL_TRIGGER_PATTERN;
                    NVIC_SystemReset();
                }
                year = esprxdata.year;
                month = esprxdata.month;
                day = esprxdata.day;
                hour = esprxdata.hour;
                minute = esprxdata.minute;
                sec = esprxdata.sec;
                Update_Date_Time(year, month, day, hour, minute, sec);

                if ((esprxdata.start_charge == 1) || (esprxdata.start_charge == 2)) {

                    if (esprxdata.start_connector == 1) {
                        sprintf(buffer, "START CHARGE RECEIVED 1\r\n");
                        SERCOM5_USART_Write(buffer, sizeof (buffer));
                        while (!(SERCOM5_USART_TransmitComplete()))
                            ;
                        START_STOP_AR[0] = 1;
                        START_STOP_AR[1] = 1;
                        START_STOP_AR[2] = 0;
                        if ((esprxdata.start_charge == 2)) {
                            START_BY1 = BY_RFID;
                        }
                        if ((esprxdata.start_charge == 1)) {
                            START_BY1 = BY_REMOTE;
                        }
                        Change_Page_to(GUN1_WAITING_FOR_AUTH);
                    }
                    if (esprxdata.start_connector == 2) {
                        sprintf(buffer, "START CHARGE RECEIVED 2\r\n");
                        SERCOM5_USART_Write(buffer, sizeof (buffer));
                        while (!(SERCOM5_USART_TransmitComplete()))
                            ;
                        START_STOP_AR1[0] = 2;
                        START_STOP_AR1[1] = 1;
                        START_STOP_AR1[2] = 0;
                        if ((esprxdata.start_charge == 2)) {
                            START_BY2 = BY_RFID;
                        }
                        if ((esprxdata.start_charge == 1)) {
                            START_BY2 = BY_REMOTE;
                        }
                        Change_Page_to(GUN2_WAITING_FOR_AUTH);
                    }
                }
                if ((esprxdata.stop_charge == 1) || (esprxdata.stop_charge == 2) || (esprxdata.stop_charge == 3)) {

                    if (esprxdata.stop_connector == 1) {

                        sprintf(buffer, "STop RECEIVED 1 BOOKING ID : %ld\r\n", BOOKING_ID1);
                        SERCOM5_USART_Write(buffer, sizeof (buffer));
                        while (!(SERCOM5_USART_TransmitComplete()))
                            ;
                        START_STOP_AR[0] = 1;
                        START_STOP_AR[1] = 0;
                        START_STOP_AR[2] = 1;
                        if ((esprxdata.stop_charge == 2)) {
                            STOP_BY = BY_RFID;
                        }
                        if ((esprxdata.stop_charge == 1)) {
                            STOP_BY = BY_REMOTE;
                        }
                        if ((esprxdata.stop_charge == 3)) {
                            STOP_BY = BY_DE_AUTH;
                            CURRENT_PLC1_STATE = _1_PLC_STATE_CURRENT_DEMAND_1;
                            Change_Page_to(GUN1_AUTHENTICATION_FAIL_PAGE);
                        }
                    }
                    if (esprxdata.stop_connector == 2) {

                        sprintf(buffer, "STop RECEIVED 2 BOOKING ID : %ld\r\n", BOOKING_ID2);

                        SERCOM5_USART_Write(buffer, sizeof (buffer));
                        while (!(SERCOM5_USART_TransmitComplete()))
                            ;
                        START_STOP_AR1[0] = 2;
                        START_STOP_AR1[1] = 0;
                        START_STOP_AR1[2] = 1;
                        if ((esprxdata.stop_charge == 2)) {
                            STOP_BY = BY_RFID;
                        }
                        if ((esprxdata.stop_charge == 1)) {
                            STOP_BY = BY_REMOTE;
                        }
                        if ((esprxdata.stop_charge == 3)) {
                            STOP_BY = BY_DE_AUTH;
                            CURRENT_PLC2_STATE = _2_PLC_STATE_CURRENT_DEMAND_1;
                            Change_Page_to(GUN2_AUTHENTICATION_FAIL_PAGE);
                        }
                    }
                }
                BOOKING_ID1 = esprxdata.Booking_ID_1;
                BOOKING_ID2 = esprxdata.Booking_ID_2;
                rssi = esprxdata.rssi;
                if ((rssi <= 0x18) && (rssi >= 0x00)) {
                    Update_GSM_Signal_Strength(0x03);
                    Update_RSSI_Value((uint16_t) rssi);
                    rssi_state = 1;
                }
                if ((rssi <= 0x31) && (rssi >= 0x19)) {
                    Update_GSM_Signal_Strength(0x02);
                    Update_RSSI_Value((uint16_t) rssi);
                    rssi_state = 1;
                }
                if ((rssi <= 0x4B) && (rssi >= 0x32)) {
                    Update_GSM_Signal_Strength(0x01);
                    Update_RSSI_Value((uint16_t) rssi);
                    rssi_state = 1;
                }
                if ((rssi <= 0x63) && (rssi >= 0x4B)) {
                    Update_GSM_Signal_Strength(0x00);
                    Update_RSSI_Value((uint16_t) rssi);
                    rssi_state = 0;
                    //                    CURRENT_PAGE = NO_NETWORK_PAGE;
                }
                Update_RSSI_Value((uint16_t) rssi);
                if (esprxdata.auth_status == 1) {
                    memset(rfid_data.RFID_IS, 0, sizeof (rfid_data.RFID_IS));
                    xQueueOverwrite(ESP_S_RFID_QUEUE, &rfid_data);
                    memset(OTP, 0, sizeof (OTP));
                }
                switch (esprxdata.wifi_state) {

                    case 0:
                        Update_Wifi_Status(0x00);
                        wifi_state = 0;
                        break;
                    case 1:
                        Update_Wifi_Status(0x01);
                        wifi_state = 1;
                        break;
                }
                switch (esprxdata.server_connection) {
                    case 0:
                        Update_OCPP_Symbol(0x00);
                        leddata.GUN = OFFLINE;
                        xQueueOverwrite(LED1_QUEUE, &leddata);
                        //                        if (GUN1_CONNECTED == 0 && GUN2_CONNECTED == 0) {
                        //                            color1msg.COLOR1 = MAGENTA;
                        //                            color2msg.COLOR2 = MAGENTA2;
                        //                            xQueueOverwrite(COLOR1_QUEUE, &color1msg);
                        //                            xQueueOverwrite(COLOR2_QUEUE, &color2msg);
                        //                        }
                        //                        if (GUN1_CONNECTED == 1 && GUN2_CONNECTED == 0) {
                        //                            color2msg.COLOR2 = MAGENTA2;
                        //                            xQueueOverwrite(COLOR2_QUEUE, &color2msg);
                        //                        }
                        //                        if (GUN1_CONNECTED == 0 && GUN2_CONNECTED == 1) {
                        //                            color1msg.COLOR1 = MAGENTA;
                        //                            xQueueOverwrite(COLOR1_QUEUE, &color1msg);
                        //                        }
                        break;
                    case 1:
                        Update_OCPP_Symbol(0x01);
                        leddata.GUN = ONLINE;
                        xQueueOverwrite(LED1_QUEUE, &leddata);
                        //                        if (GUN1_CONNECTED == 0 && GUN2_CONNECTED == 0) {
                        //                            color1msg.COLOR1 = WHITE;
                        //                            color2msg.COLOR2 = WHITE2;
                        //                            xQueueOverwrite(COLOR1_QUEUE, &color1msg);
                        //                            xQueueOverwrite(COLOR2_QUEUE, &color2msg);
                        //                        }
                        //                        if (GUN1_CONNECTED == 1 && GUN2_CONNECTED == 0) {
                        //                            color2msg.COLOR2 = WHITE2;
                        //                            xQueueOverwrite(COLOR2_QUEUE, &color2msg);
                        //                        }
                        //                        if (GUN1_CONNECTED == 0 && GUN2_CONNECTED == 1) {
                        //                            color1msg.COLOR1 = WHITE;
                        //                            xQueueOverwrite(COLOR1_QUEUE, &color1msg);
                        //                        }
                        break;
                }

                switch (esprxdata.ethernet_state) {
                    case 0:
                        Update_Ethernet_status(0x00);
                        break;
                    case 1:
                        Update_Ethernet_status(0x01);
                        break;
                }
                if (wifi_state == 0 && rssi_state == 0) {
                    CURRENT_PAGE = NO_NETWORK_PAGE;
                }

                switch (esprxdata.limit_connector) {
                    case 5:
                        SINGLE_GUN1_POWER = 0;
                        SINGLE_GUN2_POWER = 0;
                        POWER_VALUE_X = esprxdata.power_limit * 1000;
                        if (esprxdata.power_limit == 0x0) {
                            POWER_VALUE_X = MAX_POWER_LIMIT * 10000;
                        }
                        memset(buffer, 0, sizeof (buffer));
                        sprintf(buffer, " year : %d , POWER REC chg : %d\r\n", year, esprxdata.power_limit);
                        SERCOM5_USART_Write(buffer, sizeof (buffer));
                        while (!(SERCOM5_USART_TransmitComplete()))
                            ;
                        flashmsg.WHAT_TYPE_OF_DATA = BT_DATA;
                        flashmsg.DATA_IDX = DLB_POWER_VALUES_IDX;
                        flashmsg.DATA_t = ZERO_DATA | (((uint32_t) POWER_VALUE_X / 1000) << 24) | (((uint32_t) POWER_VALUE_X / 1000) << 16) | ((uint32_t) SINGLE_GUN2_POWER << 8) | ((uint32_t) SINGLE_GUN1_POWER);
                        xQueueSend(FLASH_WRITE_QUEUE, &flashmsg, 100);
                        vTaskResume(FLASH_WRITE_TASKHandle);
                        break;
                    case 1:
                        SINGLE_GUN1_POWER = 1;
                        POWER_VALUE_X1 = esprxdata.power_limit * 1000;
                        memset(buffer, 0, sizeof (buffer));
                        sprintf(buffer, "POWER REC 1: %d\r\n", esprxdata.power_limit);
                        SERCOM5_USART_Write(buffer, sizeof (buffer));
                        while (!(SERCOM5_USART_TransmitComplete()))
                            ;
                        flashmsg.WHAT_TYPE_OF_DATA = BT_DATA;
                        flashmsg.DATA_IDX = DLB_POWER_VALUES_IDX;
                        flashmsg.DATA_t = ZERO_DATA | (((uint32_t) POWER_VALUE_X2 / 1000) << 24) | (((uint32_t) POWER_VALUE_X1 / 1000) << 16) | ((uint32_t) SINGLE_GUN2_POWER << 8) | ((uint32_t) SINGLE_GUN1_POWER);
                        xQueueSend(FLASH_WRITE_QUEUE, &flashmsg, 100);
                        vTaskResume(FLASH_WRITE_TASKHandle);
                        break;
                    case 2:
                        SINGLE_GUN2_POWER = 1;
                        POWER_VALUE_X2 = esprxdata.power_limit * 1000;
                        memset(buffer, 0, sizeof (buffer));
                        sprintf(buffer, "POWER REC 2: %d\r\n", esprxdata.power_limit);
                        SERCOM5_USART_Write(buffer, sizeof (buffer));
                        while (!(SERCOM5_USART_TransmitComplete()))
                            ;
                        flashmsg.WHAT_TYPE_OF_DATA = BT_DATA;
                        flashmsg.DATA_IDX = DLB_POWER_VALUES_IDX;
                        flashmsg.DATA_t = ZERO_DATA | (((uint32_t) POWER_VALUE_X2 / 1000) << 24) | (((uint32_t) POWER_VALUE_X1 / 1000) << 16) | ((uint32_t) SINGLE_GUN2_POWER << 8) | ((uint32_t) SINGLE_GUN1_POWER);
                        xQueueSend(FLASH_WRITE_QUEUE, &flashmsg, 100);
                        vTaskResume(FLASH_WRITE_TASKHandle);
                        break;
                    case 3:
                        SINGLE_GUN1_POWER = 0;
                        flashmsg.WHAT_TYPE_OF_DATA = BT_DATA;
                        flashmsg.DATA_IDX = DLB_POWER_VALUES_IDX;
                        flashmsg.DATA_t = ZERO_DATA | (((uint32_t) POWER_VALUE_X2 / 1000) << 24) | (((uint32_t) POWER_VALUE_X / 1000) << 16) | ((uint32_t) SINGLE_GUN2_POWER << 8) | ((uint32_t) SINGLE_GUN1_POWER);
                        xQueueSend(FLASH_WRITE_QUEUE, &flashmsg, 100);
                        vTaskResume(FLASH_WRITE_TASKHandle);
                        sprintf(buffer, "POWER REC 1: CLEARED\r\n");
                        SERCOM5_USART_Write(buffer, sizeof (buffer));
                        while (!(SERCOM5_USART_TransmitComplete()))
                            ;
                        break;
                    case 4:
                        SINGLE_GUN2_POWER = 0;
                        flashmsg.WHAT_TYPE_OF_DATA = BT_DATA;
                        flashmsg.DATA_IDX = DLB_POWER_VALUES_IDX;
                        flashmsg.DATA_t = ZERO_DATA | (((uint32_t) POWER_VALUE_X / 1000) << 24) | (((uint32_t) POWER_VALUE_X1 / 1000) << 16) | ((uint32_t) SINGLE_GUN2_POWER << 8) | ((uint32_t) SINGLE_GUN1_POWER);
                        xQueueSend(FLASH_WRITE_QUEUE, &flashmsg, 100);
                        vTaskResume(FLASH_WRITE_TASKHandle);
                        sprintf(buffer, "POWER REC 2: CLEARED\r\n");
                        SERCOM5_USART_Write(buffer, sizeof (buffer));
                        while (!(SERCOM5_USART_TransmitComplete()))
                            ;
                        break;
                }
                if (esprxdata.BT_DATA_COMING == 1) {
                    flashmsg.WHAT_TYPE_OF_DATA = BT_DATA;
                    flashmsg.DATA_IDX = esprxdata.BT_DATA_IDX;
                    flashmsg.DATA_t = esprxdata.DATA_t;
                    xQueueSend(FLASH_WRITE_QUEUE, &flashmsg, 100);
                    vTaskResume(FLASH_WRITE_TASKHandle);
                }
                if (esprxdata.BT_DATA_COMING == 2) {
                    flashreadmsg.WHO_IS_READING = ESP_READ;
                    flashreadmsg.BT_READ_IDX = esprxdata.BT_DATA_IDX;
                    flashreadmsg.COUNT_READ_INC = 0;
                    flashreadmsg.PAGE_VIEW = 0;
                    xQueueSend(FLASH_READ_QUEUE, &flashreadmsg, 100);
                    vTaskResume(FLASH_READ_TASKHandle);
                }

            }
        }
        vTaskDelay(1);
    }
}

void Start_AC_METER_SEND_TASK(void *argument) {
    SERCOM2_USART_ReadCallbackRegister(ENERGY_METER_CALLBACK, 0);
    uint8_t ENERGY_METER_READ1[8] = {0x01, 0x04, 0x00, 0x00, 0x00, 0x28, 0xF0, 0x14};
    uint8_t ENERGY_METER_READ2[8] = {0x01, 0x04, 0x00, 0x28, 0x00, 0x28, 0x70, 0x1C};
    //    uint8_t ENERGY_METER_READ1[8] = {0x04, 0x04, 0x00, 0x00, 0x00, 0x28, 0xF0, 0x41};
    //    uint8_t ENERGY_METER_READ2[8] = {0x04, 0x04, 0x00, 0x28, 0x00, 0x28, 0x70, 0x49};
    static uint8_t count = 0;
    WHICH_METER_Q which_meter;
    NEXT_METER_Q next_meter;
    for (;;) {
        switch (count) {
            case 0:
                memset(em_rx_buff, 0, sizeof (em_rx_buff));
                SERCOM2_USART_Read(em_rx_buff, ENERGY_METER_RX_SIZE);
                which_meter.Which_Meter_data[0] = AC_METER_1_IDT;
                xQueueOverwrite(WHICH_METER_QUEUE, &which_meter);
                next_meter.NEXT_METER[0] = AC_METER_2_IDT;
                xQueueOverwrite(NEXT_METER_QUEUE, &next_meter);
                ENABLE_EC_METER_Set();
                SERCOM2_USART_Write(ENERGY_METER_READ1, sizeof (ENERGY_METER_READ1));
                while (!(SERCOM2_USART_TransmitComplete()))
                    ;
                ENABLE_EC_METER_Clear();
                count = 1;
                xTimerStart(ac_timer, 60000);
                xTimerStart(meter_change_timer, 2000);
                break;
            case 1:
                memset(em_rx_buff, 0, sizeof (em_rx_buff));
                SERCOM2_USART_Read(em_rx_buff, ENERGY_METER_RX_SIZE);
                which_meter.Which_Meter_data[0] = AC_METER_2_IDT;
                xQueueOverwrite(WHICH_METER_QUEUE, &which_meter);
                next_meter.NEXT_METER[0] = DC_METER_1_IDT;
                xQueueOverwrite(NEXT_METER_QUEUE, &next_meter);
                ENABLE_EC_METER_Set();
                SERCOM2_USART_Write(ENERGY_METER_READ2, sizeof (ENERGY_METER_READ2));
                while (!(SERCOM2_USART_TransmitComplete()))
                    ;
                ENABLE_EC_METER_Clear();
                count = 0;
                xTimerStart(ac_timer, 60000);
                xTimerStart(meter_change_timer, 2000);
                break;
        }
        vTaskSuspend(AC_METER_SEND_TASKHandle);
        vTaskDelay(1);
    }
}

void Start_DC1_METER_SEND_TASK(void *argument) {
    uint8_t DC_METER_READ1[8] = {0x02, 0x04, 0x00, 0x00, 0x00, 0x28, 0xF0, 0x27};
    WHICH_METER_Q which_meter;
    NEXT_METER_Q next_meter;
    for (;;) {
        memset(em_rx_buff, 0, sizeof (em_rx_buff));
        SERCOM2_USART_Read(em_rx_buff, ENERGY_METER_RX_SIZE);
        which_meter.Which_Meter_data[0] = DC_METER_1_IDT;
        xQueueOverwrite(WHICH_METER_QUEUE, &which_meter);
        next_meter.NEXT_METER[0] = DC_METER_2_IDT;
        xQueueOverwrite(NEXT_METER_QUEUE, &next_meter);
        ENABLE_EC_METER_Set();
        SERCOM2_USART_Write(DC_METER_READ1, sizeof (DC_METER_READ1));
        while (!(SERCOM2_USART_TransmitComplete()))
            ;
        ENABLE_EC_METER_Clear();
        xTimerStart(dc1_timer, 60000);
        xTimerStart(meter_change_timer, 2000);
        vTaskSuspend(DC1_METER_SEND_TASKHandle);
        vTaskDelay(1);
    }
}

void Start_DC2_METER_SEND_TASK(void *argument) {
    uint8_t DC_METER_READ2[8] = {0x03, 0x04, 0x00, 0x00, 0x00, 0x28, 0xF1, 0xF6};
    WHICH_METER_Q which_meter;
    NEXT_METER_Q next_meter;
    for (;;) {
        memset(em_rx_buff, 0, sizeof (em_rx_buff));
        SERCOM2_USART_Read(em_rx_buff, ENERGY_METER_RX_SIZE);
        which_meter.Which_Meter_data[0] = DC_METER_2_IDT;
        xQueueOverwrite(WHICH_METER_QUEUE, &which_meter);
        next_meter.NEXT_METER[0] = AC_METER_1_IDT;
        xQueueOverwrite(NEXT_METER_QUEUE, &next_meter);
        ENABLE_EC_METER_Set();
        SERCOM2_USART_Write(DC_METER_READ2, sizeof (DC_METER_READ2));
        while (!(SERCOM2_USART_TransmitComplete()))
            ;
        ENABLE_EC_METER_Clear();
        xTimerStart(dc2_timer, 60000);
        xTimerStart(meter_change_timer, 2000);
        vTaskSuspend(DC2_METER_SEND_TASKHandle);
        vTaskDelay(1);
    }
}

void Start_METER_RX_TASK(void *arggument) {
    static uint8_t METER_DATA[83] = {0};
    static uint32_t u8dummyData = 0;
    char buf[30];
    BaseType_t xTaskWokenByReceive = pdFALSE;
    float VOLTAGE1 = 0, CURRENT1 = 0, POWER1 = 0, VOLTAGE2 = 0, CURRENT2 = 0, POWER2 = 0;
    float AC_VOLTAGE1_t, AC_VOLTAGE2, AC_VOLTAGE3, AC_CURRENT1, AC_CURRENT2, AC_CURRENT3, AC_FREQUENCY;
    ;
    uint32_t volt1, curr1, volt2, curr2, ac_volt1, ac_volt2, ac_volt3, ac_curr1, ac_curr2, ac_curr3, ac_freq, imp_energy1, imp_energy2, ac_imp_power_t, ac_energy_t;
    METER_DATA_Q meterdata;
    static uint8_t instance = 0;
    //    char data[35];
    static ESP_S_METER_D_Q esp_s_meter_data;
    WHICH_METER_Q which_meter;
    static uint8_t WHICH_METER_t = 0;
    for (;;) {

        if (xQueueReceive(WHICH_METER_QUEUE, &which_meter, 0)) {
            WHICH_METER_t = which_meter.Which_Meter_data[0];
        }
        if (xQueueReceiveFromISR(METER_DATA_QUEUE, &meterdata, &xTaskWokenByReceive)) {
            memcpy(METER_DATA, meterdata.Meter_data, (ENERGY_METER_RX_SIZE - 2));
            switch (WHICH_METER_t) {
                case AC_METER_1_IDT:
                    xTimerStop(ac_timer, 10);
                    if (CRC16_modbus(meterdata.Meter_data, 83, 1)) {
                        if (ac_meter_comm == 1) {
                            ac_meter_comm = 0;
                            MACHINE_STATE = IDLE_STATE;
                        }
                        if (DEFAULT_AC_METER_t == 'S') {
                            ac_volt1 = (METER_DATA[5] << 24 | METER_DATA[6] << 16 | METER_DATA[7] << 8 | METER_DATA[8]);
                            AC_VOLTAGE1_t = *((float *) &ac_volt1);
                            ac_volt2 = (METER_DATA[9] << 24 | METER_DATA[10] << 16 | METER_DATA[11] << 8 | METER_DATA[12]);
                            AC_VOLTAGE2 = *((float *) &ac_volt2);
                            ac_volt3 = (METER_DATA[13] << 24 | METER_DATA[14] << 16 | METER_DATA[15] << 8 | METER_DATA[16]);
                            AC_VOLTAGE3 = *((float *) &ac_volt3);
                            ac_curr1 = (METER_DATA[37] << 24 | METER_DATA[38] << 16 | METER_DATA[39] << 8 | METER_DATA[40]);
                            AC_CURRENT1 = *((float *) &ac_curr1);
                            ac_curr2 = (METER_DATA[41] << 24 | METER_DATA[42] << 16 | METER_DATA[43] << 8 | METER_DATA[44]);
                            AC_CURRENT2 = *((float *) &ac_curr2);
                            ac_curr3 = (METER_DATA[45] << 24 | METER_DATA[46] << 16 | METER_DATA[27] << 8 | METER_DATA[48]);
                            AC_CURRENT3 = *((float *) &ac_curr3);
                        } else {
                            ac_volt1 = (METER_DATA[3] << 24 | METER_DATA[4] << 16 | METER_DATA[5] << 8 | METER_DATA[6]);
                            AC_VOLTAGE1_t = *((float *) &ac_volt1);
                            ac_volt2 = (METER_DATA[7] << 24 | METER_DATA[8] << 16 | METER_DATA[9] << 8 | METER_DATA[10]);
                            AC_VOLTAGE2 = *((float *) &ac_volt2);
                            ac_volt3 = (METER_DATA[11] << 24 | METER_DATA[12] << 16 | METER_DATA[13] << 8 | METER_DATA[14]);
                            AC_VOLTAGE3 = *((float *) &ac_volt3);
                            ac_curr1 = (METER_DATA[15] << 24 | METER_DATA[16] << 16 | METER_DATA[17] << 8 | METER_DATA[18]);
                            AC_CURRENT1 = *((float *) &ac_curr1);
                            ac_curr2 = (METER_DATA[19] << 24 | METER_DATA[20] << 16 | METER_DATA[21] << 8 | METER_DATA[22]);
                            AC_CURRENT2 = *((float *) &ac_curr2);
                            ac_curr3 = (METER_DATA[23] << 24 | METER_DATA[24] << 16 | METER_DATA[25] << 8 | METER_DATA[26]);
                            AC_CURRENT3 = *((float *) &ac_curr3);
                        }

                        Update_AC_CURRENT1((int) AC_CURRENT1);
                        vTaskDelay(10);
                        Update_AC_CURRENT2((int) AC_CURRENT2);
                        vTaskDelay(10);
                        Update_AC_CURRENT3((int) AC_CURRENT3);
                        vTaskDelay(10);
                        Update_AC_VOLTAGE1((int) AC_VOLTAGE1_t);
                        vTaskDelay(10);
                        Update_AC_VOLTAGE2((int) AC_VOLTAGE2);
                        vTaskDelay(10);
                        Update_AC_VOLTAGE3((int) AC_VOLTAGE3);
                        vTaskDelay(10);
                        if (((int) AC_VOLTAGE1_t) > AC_OVER_VOLT_LIMIT_t) {
                            MAINS_HIGH = 1;
                            MACHINE_STATE = IDLE_STATE;
                            instance = 0;
                            break;
                        }
                        if (((int) AC_VOLTAGE1_t) < AC_UNDER_VOLT_LIMIT_t) {
                            MACHINE_STATE = IDLE_STATE;
                            MAINS_LOW = 1;
                            instance = 0;
                            break;
                        }
                        if (((((int) AC_VOLTAGE1_t) > AC_UNDER_VOLT_LIMIT_t) && (((int) AC_VOLTAGE1_t) < AC_OVER_VOLT_LIMIT_t)) && (instance == 0)) {
                            MAINS_HIGH = 0;
                            MAINS_LOW = 0;
                            MACHINE_STATE = IDLE_STATE;
                            instance = 1;
                        }

                        if (((int) AC_VOLTAGE2) > AC_OVER_VOLT_LIMIT_t) {
                            MAINS_HIGH = 1;
                            MACHINE_STATE = IDLE_STATE;
                            instance = 0;
                            break;
                        }
                        if (((int) AC_VOLTAGE2) < AC_UNDER_VOLT_LIMIT_t) {
                            MACHINE_STATE = IDLE_STATE;
                            MAINS_LOW = 1;
                            instance = 0;
                            break;
                        }
                        if (((((int) AC_VOLTAGE2) > AC_UNDER_VOLT_LIMIT_t) && (((int) AC_VOLTAGE2) < AC_OVER_VOLT_LIMIT_t)) && (instance == 0)) {
                            MAINS_HIGH = 0;
                            MAINS_LOW = 0;
                            MACHINE_STATE = IDLE_STATE;
                            instance = 1;
                        }
                        if (((int) AC_VOLTAGE3) > AC_OVER_VOLT_LIMIT_t) {
                            MAINS_HIGH = 1;
                            MACHINE_STATE = IDLE_STATE;
                            instance = 0;
                            break;
                        }
                        if (((int) AC_VOLTAGE3) < AC_UNDER_VOLT_LIMIT_t) {
                            MACHINE_STATE = IDLE_STATE;
                            MAINS_LOW = 1;
                            instance = 0;
                            break;
                        }
                        if (((((int) AC_VOLTAGE3) > AC_UNDER_VOLT_LIMIT_t) && (((int) AC_VOLTAGE3) < AC_OVER_VOLT_LIMIT_t)) && (instance == 0)) {
                            MAINS_HIGH = 0;
                            MAINS_LOW = 0;
                            MACHINE_STATE = IDLE_STATE;
                            instance = 1;
                        }
                        esp_s_meter_data.AC_CURRENT_L1 = ac_curr1;
                        esp_s_meter_data.AC_CURRENT_L2 = ac_curr2;
                        esp_s_meter_data.AC_CURRENT_L3 = ac_curr3;
                        esp_s_meter_data.AC_VOLT_L1 = ac_volt1;
                        esp_s_meter_data.AC_VOLT_L2 = ac_volt2;
                        esp_s_meter_data.AC_VOLT_L3 = ac_volt3;

                    } else {
                        sprintf(buf, "CRC NOT MATCH AC1\r\n");
                        SERCOM5_USART_Write(buf, sizeof (buf));
                        while (!(SERCOM5_USART_TransmitComplete()))
                            ;
                        u8dummyData = u8dummyData | SERCOM2_REGS->USART_INT.SERCOM_DATA;
                    }
                    break;
                case AC_METER_2_IDT:
                    xTimerStop(ac_timer, 10);
                    if (CRC16_modbus(meterdata.Meter_data, 83, 1)) {
                        if (DEFAULT_AC_METER_t == 'S') {
                            ac_freq = (METER_DATA[37] << 24 | METER_DATA[38] << 16 | METER_DATA[39] << 8 | METER_DATA[40]);
                            AC_FREQUENCY = *((float *) &ac_freq);
                            ac_energy_t = (METER_DATA[41] << 24 | METER_DATA[42] << 16 | METER_DATA[43] << 8 | METER_DATA[44]);
                            ac_imp_power_t = (METER_DATA[9] << 24 | METER_DATA[10] << 16 | METER_DATA[11] << 8 | METER_DATA[12]);
                        } else {
                            ac_freq = (METER_DATA[63] << 24 | METER_DATA[64] << 16 | METER_DATA[65] << 8 | METER_DATA[66]);
                            AC_FREQUENCY = *((float *) &ac_freq);
                            ac_energy_t = (METER_DATA[67] << 24 | METER_DATA[68] << 16 | METER_DATA[69] << 8 | METER_DATA[70]);
                            ac_imp_power_t = (METER_DATA[27] << 24 | METER_DATA[28] << 16 | METER_DATA[29] << 8 | METER_DATA[30]);
                        }
                        esp_s_meter_data.AC_FREQUENCY = ac_freq;
                        esp_s_meter_data.AC_POWER = ac_imp_power_t;
                        esp_s_meter_data.AC_ENERGY = ac_energy_t;
                        Update_AC_frequency((int) AC_FREQUENCY);
                        vTaskDelay(10);
                    } else {
                        sprintf(buf, "CRC NOT MATCH AC2\r\n");
                        SERCOM5_USART_Write(buf, sizeof (buf));
                        while (!(SERCOM5_USART_TransmitComplete()))
                            ;
                        u8dummyData = u8dummyData | SERCOM2_REGS->USART_INT.SERCOM_DATA;
                    }
                    break;
                case DC_METER_1_IDT:
                    xTimerStop(dc1_timer, 10);
                    if (CRC16_modbus(meterdata.Meter_data, 83, 1)) {
                        if (dc1_meter_comm == 1) {
                            dc1_meter_comm = 0;
                            MACHINE_STATE = IDLE_STATE;
                        }
                        volt1 = (METER_DATA[3] << 24 | METER_DATA[4] << 16 | METER_DATA[5] << 8 | METER_DATA[6]);
                        VOLTAGE1 = *((float *) &volt1);
                        curr1 = METER_DATA[7] << 24 | METER_DATA[8] << 16 | METER_DATA[9] << 8 | METER_DATA[10];
                        CURRENT1 = *((float *) &curr1);
                        imp_energy1 = METER_DATA[15] << 24 | METER_DATA[16] << 16 | METER_DATA[17] << 8 | METER_DATA[18];
                        IMPORT_ENERGY1 = *((float *) &imp_energy1);

                        memset(buf, 0, sizeof (buf));
                        if (CURRENT_PLC1_STATE == _1_PLC_STATE_CURRENT_DEMAND_1) {
                            if ((int) VOLTAGE1 > CHARGER_MAX_VOLT_LIMIT) {
                                ERROR_CODE_ARRAY[DC_OVER_VOLTAGE_IDX] = 128;
                                ERROR_CODE_ARRAY[DC_OVER_CONN_NO] = 1;
                                Update_DC_Over_Volt1_Status(0x01);
                                vTaskDelay(100);
                            } else if ((int) VOLTAGE1 < CHARGER_MIN_VOLT_LIMIT && VOLTAGE1 != 0) {
                                //                                ERROR_CODE_ARRAY[DC_UNDER_VOLT_IDX] = 129;
                                //                                ERROR_CODE_ARRAY[DC_UNDER_CONN_NO] = 1;
                                //                                Update_DC_Under_Volt1_Status(0x01);
                                //                                vTaskDelay(100);
                            } else {
                                ERROR_CODE_ARRAY[DC_UNDER_VOLT_IDX] = 0;
                                ERROR_CODE_ARRAY[DC_OVER_VOLTAGE_IDX] = 0;
                                Update_DC_Over_Volt1_Status(0x00);
                                vTaskDelay(100);
                                Update_DC_Under_Volt1_Status(0x00);
                                vTaskDelay(100);
                            }

                            if ((int) CURRENT1 > (MAX_CURR_LIMIT1) / 10) {
                                ERROR_CODE_ARRAY[DC_OVER_CURR_IDX] = 130;
                                ERROR_CODE_ARRAY[DC_CURRENT_OVER_CONN_NO] = 1;
                                Update_DC_Output_Over_Current1_Status(0x01);
                                vTaskDelay(100);
                            } else {
                                ERROR_CODE_ARRAY[DC_OVER_CURR_IDX] = 0;
                                Update_DC_Output_Over_Current1_Status(0x00);
                                vTaskDelay(100);
                            }
                        } else {
                            ERROR_CODE_ARRAY[DC_OVER_VOLTAGE_IDX] = 0;
                            ERROR_CODE_ARRAY[DC_OVER_CURR_IDX] = 0;
                            ERROR_CODE_ARRAY[DC_UNDER_VOLT_IDX] = 0;
                        }

                        POWER1 = (VOLTAGE1 * CURRENT1) / 1000;
                        Update_GUN1_Voltage((int) VOLTAGE1);
                        vTaskDelay(10);
                        Update_GUN1_Current((int) CURRENT1);
                        vTaskDelay(10);
                        Update_GUN1_Total_Power((int) POWER1);
                        vTaskDelay(10);
                        if (VOLTAGE1 > 200) {
                            act_volt_1 = VOLTAGE1;
                        }
                        esp_s_meter_data.DC1_CURRENT = curr1;
                        esp_s_meter_data.DC1_VOLTAGE = volt1;
                        esp_s_meter_data.DC1_IMPORT_ENERGY = imp_energy1;
                        esp_s_meter_data.DC1_POWER = *((uint32_t *) & POWER1);

                    } else {
                        sprintf(buf, "CRC NOT MATCH DC1\r\n");
                        SERCOM5_USART_Write(buf, sizeof (buf));
                        while (!(SERCOM5_USART_TransmitComplete()))
                            ;
                        u8dummyData = u8dummyData | SERCOM2_REGS->USART_INT.SERCOM_DATA;
                    }
                    break;
                case DC_METER_2_IDT:
                    xTimerStop(dc2_timer, 10);
                    if (CRC16_modbus(meterdata.Meter_data, 83, 1)) {
                        if (dc2_meter_comm == 1) {
                            dc2_meter_comm = 0;
                            MACHINE_STATE = IDLE_STATE;
                        }
                        volt2 = (METER_DATA[3] << 24 | METER_DATA[4] << 16 | METER_DATA[5] << 8 | METER_DATA[6]);
                        VOLTAGE2 = *((float *) &volt2);
                        curr2 = METER_DATA[7] << 24 | METER_DATA[8] << 16 | METER_DATA[9] << 8 | METER_DATA[10];
                        CURRENT2 = *((float *) &curr2);
                        imp_energy2 = METER_DATA[15] << 24 | METER_DATA[16] << 16 | METER_DATA[17] << 8 | METER_DATA[18];
                        IMPORT_ENERGY2 = *((float *) &imp_energy2);
                        POWER2 = (VOLTAGE2 * CURRENT2) / 1000;
                        Update_GUN2_Voltage((int) VOLTAGE2);
                        vTaskDelay(100);
                        if (VOLTAGE2 > 200) {
                            act_volt_2 = VOLTAGE2;
                        }
                        Update_GUN2_Current((int) CURRENT2);
                        vTaskDelay(100);
                        Update_GUN2_Total_Power((int) POWER2);
                        vTaskDelay(100);

                        if (CURRENT_PLC2_STATE == _2_PLC_STATE_CURRENT_DEMAND_1) {
                            if ((int) VOLTAGE2 > CHARGER_MAX_VOLT_LIMIT && VOLTAGE2 != 0) {
                                ERROR_CODE_ARRAY[DC_OVER_VOLTAGE_IDX] = 128;
                                ERROR_CODE_ARRAY[DC_OVER_CONN_NO] = 2;
                                Update_DC_Over_Volt2_Status(0x01);
                                vTaskDelay(10);
                            } else if ((int) VOLTAGE2 < CHARGER_MIN_VOLT_LIMIT) {
                                //                                ERROR_CODE_ARRAY[DC_UNDER_VOLT_IDX] = 129;
                                //                                ERROR_CODE_ARRAY[DC_UNDER_CONN_NO] = 2;
                                //                                Update_DC_Under_Volt2_Status(0x01);
                                //                                vTaskDelay(10);
                            } else {
                                ERROR_CODE_ARRAY[DC_UNDER_VOLT_IDX] = 0;
                                ERROR_CODE_ARRAY[DC_OVER_VOLTAGE_IDX] = 0;
                                Update_DC_Over_Volt2_Status(0x00);
                                vTaskDelay(100);
                                Update_DC_Under_Volt2_Status(0x00);
                                vTaskDelay(10);
                            }

                            if ((int) CURRENT2 > (MAX_CURR_LIMIT2) / 10) {
                                ERROR_CODE_ARRAY[DC_OVER_CURR_IDX] = 130;
                                ERROR_CODE_ARRAY[DC_CURRENT_OVER_CONN_NO] = 2;
                                Update_DC_Output_Over_Current2_Status(0x01);
                                vTaskDelay(10);
                            } else {
                                ERROR_CODE_ARRAY[DC_OVER_CURR_IDX] = 0;
                                Update_DC_Output_Over_Current2_Status(0x00);
                                vTaskDelay(10);
                            }
                        } else {
                            ERROR_CODE_ARRAY[DC_OVER_VOLTAGE_IDX] = 0;
                            ERROR_CODE_ARRAY[DC_OVER_CURR_IDX] = 0;
                            ERROR_CODE_ARRAY[DC_UNDER_VOLT_IDX] = 0;
                        }
                        esp_s_meter_data.DC2_CURRENT = curr2;
                        esp_s_meter_data.DC2_VOLTAGE = volt2;
                        esp_s_meter_data.DC2_IMPORT_ENERGY = imp_energy2;
                        esp_s_meter_data.DC2_POWER = *((uint32_t *) & POWER2);

                    } else {
                        sprintf(buf, "CRC NOT MATCH DC2\r\n");
                        SERCOM5_USART_Write(buf, sizeof (buf));
                        while (!(SERCOM5_USART_TransmitComplete()))
                            ;
                        u8dummyData = u8dummyData | SERCOM2_REGS->USART_INT.SERCOM_DATA;
                    }
                    break;
            }
            xQueueOverwrite(ESP_S_METER_D_QUEUE, &esp_s_meter_data);
        }
        vTaskSuspend(METER_RECEIVE_TaskHandle);
        vTaskDelay(1);
    }
}
//
//void Start_RFID_SEND_TASk(void *argument) {
//    uint8_t RFID_WAKEUP[] = {0x55, 0x55, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x03, 0xFD, 0xD4, 0x14, 0x01, 0x17, 0x00};
//    uint8_t RFID_READ_ID[] = {0x00, 0x00, 0xFF, 0x04, 0xFC, 0xD4, 0x4A, 0x02, 0x00, 0xE0, 0x00};
//    xTimerStart(rfid_timer, 40000);
//    for (;;) {

//        switch (rfid_count) {
//            case 0:
//
//                SERCOM4_USART_Read(rfid_rx, 1);
//                SERCOM4_USART_Write(RFID_WAKEUP, sizeof (RFID_WAKEUP));
//                while (!(SERCOM4_USART_TransmitComplete()))
//                    ;
//                break;
//
//            case 1:
//                SERCOM4_USART_Write(RFID_READ_ID, sizeof (RFID_READ_ID));
//                while (!(SERCOM4_USART_TransmitComplete()))
//                    ;
//                break;
//        }
//        vTaskSuspend(RFID_SEND_TASKHandle);
//        vTaskDelay(1);
//    }
//}
//
//void Start_RFID_RX_TASK(void *argument) {
//    uint8_t WAKEUP_RESPONSE[] = {0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x02, 0xFE, 0xD5, 0x15, 0x16, 0x00};
//    char buffer[30];
//    RFID_MSG_Q msg;
//    uint8_t RFID_DATA[30] = {0};
//    static uint8_t i = 0;
//    static uint8_t rfid_data_complete_t = 0;
//    RFID_DATA_COMPLETE_Q data;
//    ESP_S_RFID_Q rfid_data_t;
//    static uint8_t fault = 0;
//    for (;;) {

//        if (xQueueReceive(RFID_DATA_COMPLETE_QUEUE, &data, 0)) {
//            rfid_data_complete_t = data.rfid_data_complete[0];
//        }
//        if (xQueueReceive(RFID_MSG_QUEUE, &msg, 0)) {
//            RFID_DATA[i] = msg.rfid_buff[0];
//            i++;
//
//            if (i == 1) {
//
//                BUZZER_Set();
//                vTaskDelay(1000);
//                BUZZER_Clear();
//                xTimerStart(rfiddata_timer, 1000);
//            }
//        }
//        if (rfid_data_complete_t == 1) {
//            rfid_data_complete_t = 0;
//            i = 0;
//            switch (rfid_count) {
//                case 0:
//                    for (int j = 0; j < 15; j++) {
//                        if (RFID_DATA[j] != WAKEUP_RESPONSE[j]) {
//                            sprintf(buffer, "RFID_PROBLEM\r\n");
//                            SERCOM5_USART_Write(buffer, sizeof (buffer));
//                            while (!(SERCOM5_USART_TransmitComplete()));
//                            fault = 1;
//                            break;
//                        } else {
//                            fault = 0;
//                        }
//                    }
//                    if (fault == 0) {
//                        memset(RFID_DATA, 0, sizeof (RFID_DATA));
//                        rfid_count = 1;
//                        vTaskResume(RFID_SEND_TASKHandle);
//                    }
//
//                    break;
//                case 1:
//                    //                    SERCOM4_USART_Read(rfid_rx, 1);
//                    if ((RFID_DATA[0] == 0x00) && (RFID_DATA[1] == 0x00) && (RFID_DATA[2] == 0xFF) && (RFID_DATA[3] == 0x00) && (RFID_DATA[4] == 0xFF) && (RFID_DATA[5] == 0x00)) {
//                        rfid_count = 2;
//                        if (RFID_DATA[18] == 0x04 && RFID_DATA[11] == 0xD5 && RFID_DATA[12] == 0x4B) {
//                            rfid_data_t.RFID_IS[0] = 0x04;
//                            rfid_data_t.RFID_IS[1] = RFID_DATA[19];
//                            rfid_data_t.RFID_IS[2] = RFID_DATA[20];
//                            rfid_data_t.RFID_IS[3] = RFID_DATA[21];
//                            rfid_data_t.RFID_IS[4] = RFID_DATA[22];
//                            xQueueOverwrite(ESP_S_RFID_QUEUE, &rfid_data_t);
//                            sprintf(buffer, "RFID : %d %d %d %d", RFID_DATA[13], RFID_DATA[14], RFID_DATA[15], RFID_DATA[16]);
//                            SERCOM5_USART_Write(buffer, sizeof (buffer));
//                            while (!(SERCOM5_USART_TransmitComplete()));
//                            //                            vTaskDelay(1500);
//                            //                            memset(RFID_DATA, 0, sizeof (RFID_DATA));
//                            //                            rfid_count = 0;
//                            //                            vTaskResume(RFID_SEND_TASKHandle);
//                            xTimerStart(rfid_send_timer, 2000);
//                        }
//                        if (RFID_DATA[18] == 0x07 && RFID_DATA[11] == 0xD5 && RFID_DATA[12] == 0x4B) {
//                            rfid_data_t.RFID_IS[0] = 0x07;
//                            rfid_data_t.RFID_IS[1] = RFID_DATA[19];
//                            rfid_data_t.RFID_IS[2] = RFID_DATA[20];
//                            rfid_data_t.RFID_IS[3] = RFID_DATA[21];
//                            rfid_data_t.RFID_IS[4] = RFID_DATA[22];
//                            rfid_data_t.RFID_IS[5] = RFID_DATA[23];
//                            rfid_data_t.RFID_IS[6] = RFID_DATA[24];
//                            rfid_data_t.RFID_IS[7] = RFID_DATA[25];
//                            xQueueOverwrite(ESP_S_RFID_QUEUE, &rfid_data_t);
//                            sprintf(buffer, "RFID : %d %d %d %d %d %d %d", RFID_DATA[13], RFID_DATA[14], RFID_DATA[15], RFID_DATA[16], RFID_DATA[17], RFID_DATA[18], RFID_DATA[19]);
//                            SERCOM5_USART_Write(buffer, sizeof (buffer));
//                            while (!(SERCOM5_USART_TransmitComplete()));
//                            xTimerStart(rfid_send_timer, 2000);
//                            //                            vTaskDelay(1500);
//                            //                            rfid_count = 0;
//                            //                            memset(RFID_DATA, 0, sizeof (RFID_DATA));
//                            //                            vTaskResume(RFID_SEND_TASKHandle);
//                        }
//                    }
//                    //                    } else {
//                    //                        rfid_count = 0;
//                    //                        vTaskResume(RFID_SEND_TASKHandle);
//                    //                    }
//                    break;
//                case 2:
//                    vTaskSuspend(ESP_SEND_TASKHandle);
//                    if (RFID_DATA[12] == 0x04 && RFID_DATA[5] == 0xD5 && RFID_DATA[6] == 0x4B) {
//                        rfid_data_t.RFID_IS[0] = 0x04;
//                        rfid_data_t.RFID_IS[1] = RFID_DATA[13];
//                        rfid_data_t.RFID_IS[2] = RFID_DATA[14];
//                        rfid_data_t.RFID_IS[3] = RFID_DATA[15];
//                        rfid_data_t.RFID_IS[4] = RFID_DATA[16];
//                        xQueueOverwrite(ESP_S_RFID_QUEUE, &rfid_data_t);
//                        sprintf(buffer, "RFID : %d %d %d %d", RFID_DATA[13], RFID_DATA[14], RFID_DATA[15], RFID_DATA[16]);
//                        SERCOM5_USART_Write(buffer, sizeof (buffer));
//                        while (!(SERCOM5_USART_TransmitComplete()));
//                        xTimerStart(rfid_send_timer, 2000);
//                        //                        vTaskDelay(1500);
//                        //                        memset(RFID_DATA, 0, sizeof (RFID_DATA));
//                        //                        rfid_count = 0;
//                        //                        vTaskResume(RFID_SEND_TASKHandle);
//                    }
//                    if (RFID_DATA[12] == 0x07 && RFID_DATA[5] == 0xD5 && RFID_DATA[6] == 0x4B) {
//                        rfid_data_t.RFID_IS[0] = 0x07;
//                        rfid_data_t.RFID_IS[1] = RFID_DATA[13];
//                        rfid_data_t.RFID_IS[2] = RFID_DATA[14];
//                        rfid_data_t.RFID_IS[3] = RFID_DATA[15];
//                        rfid_data_t.RFID_IS[4] = RFID_DATA[16];
//                        rfid_data_t.RFID_IS[5] = RFID_DATA[17];
//                        rfid_data_t.RFID_IS[6] = RFID_DATA[18];
//                        rfid_data_t.RFID_IS[7] = RFID_DATA[19];
//                        xQueueOverwrite(ESP_S_RFID_QUEUE, &rfid_data_t);
//                        sprintf(buffer, "RFID : %d %d %d %d %d %d %d", RFID_DATA[13], RFID_DATA[14], RFID_DATA[15], RFID_DATA[16], RFID_DATA[17], RFID_DATA[18], RFID_DATA[19]);
//                        SERCOM5_USART_Write(buffer, sizeof (buffer));
//                        while (!(SERCOM5_USART_TransmitComplete()));
//                        xTimerStart(rfid_send_timer, 2000);
//                        //                        vTaskDelay(1500);
//                        //                        rfid_count = 0;
//                        ////                        memset(RFID_DATA, 0, sizeof (RFID_DATA));
//                        //                        vTaskResume(RFID_SEND_TASKHandle);
//                    }
//                    //                    else {
//                    //                        rfid_count = 0;
//                    //                        memset(RFID_DATA, 0, sizeof (RFID_DATA));
//                    //                        vTaskResume(RFID_SEND_TASKHandle);
//                    //                    }
//                    vTaskResume(ESP_SEND_TASKHandle);
//                    break;
//            }
//        }
//
//        vTaskDelay(1);
//    }
//}

void Start_RFID_SEND_TASk(void *argument) {
    SERCOM4_USART_ReadCallbackRegister(RFID_CALLBACK, 0);
    SERCOM4_USART_Read(RFID_DATA, CURRENT_RFID_RX_SIZE);
    uint8_t RFID_WAKEUP[] = {0x55, 0x55, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x03, 0xFD, 0xD4, 0x14, 0x01, 0x17, 0x00};
    uint8_t RFID_READ_ID[] = {0x00, 0x00, 0xFF, 0x04, 0xFC, 0xD4, 0x4A, 0x02, 0x00, 0xE0, 0x00};
    xTimerStart(rfid_timer, 40000);
    for (;;) {

        switch (CURRENT_RFID_RX_SIZE) {
            case RFID_WAKEUP_RX_SIZE:
                SERCOM4_USART_Write(RFID_WAKEUP, sizeof (RFID_WAKEUP));
                while (!(SERCOM4_USART_TransmitComplete()))
                    ;
                break;

            case RFID_PRE_RX_SIZE:
                SERCOM4_USART_Write(RFID_READ_ID, sizeof (RFID_READ_ID));
                while (!(SERCOM4_USART_TransmitComplete()))
                    ;
                vTaskSuspend(RFID_SEND_TASKHandle);

                break;
        }
        vTaskDelay(2200);
    }
}

void Start_RFID_RX_TASK(void *argument) {
    uint8_t WAKEUP_RESPONSE[] = {0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x02, 0xFE, 0xD5, 0x15, 0x16, 0x00};
    char buffer[30];
    ESP_S_RFID_Q rfid_data_t;
    for (;;) {

        switch (CURRENT_RFID_RX_SIZE) {
            case RFID_WAKEUP_RX_SIZE:
                xTimerStop(rfid_timer, 10);
                page_change[1] = 0;
                ERROR_CODE_ARRAY[RFID_COMM_FAIL_IDX] = 0;
                Update_RFID_Comm_Fail_Status(0x00);
                vTaskDelay(100);
                for (int i = 0; i < CURRENT_RFID_RX_SIZE; i++) {
                    if (RFID_DATA[i] != WAKEUP_RESPONSE[i]) {
                        CURRENT_RFID_RX_SIZE = RFID_ERROR_SIZE;
                        break;
                    }
                }
                CURRENT_RFID_RX_SIZE = RFID_PRE_RX_SIZE;
                break;

            case RFID_PRE_RX_SIZE:
                if ((RFID_DATA[0] == 0x00) && (RFID_DATA[1] == 0x00) && (RFID_DATA[2] == 0xFF) && (RFID_DATA[3] == 0x00) && (RFID_DATA[4] == 0xFF) && (RFID_DATA[5] == 0x00)) {
                    CURRENT_RFID_RX_SIZE = ID_RX_SIZE;
                }
                break;
            case ID_RX_SIZE:
                if ((RFID_DATA[3] == RFID_INDEX9_DATA) && (RFID_DATA[4] == RFID_INDEX10_DATA) && (RFID_DATA[5] == RFID_INDEX11_DATA) && (RFID_DATA[6] == RFID_INDEX12_DATA) && (RFID_DATA[7] == RFID_INDEX13_DATA)) {
                    RFID_ID_RECEIVED[0] = RFID_DATA[13];
                    RFID_ID_RECEIVED[1] = RFID_DATA[14];
                    RFID_ID_RECEIVED[2] = RFID_DATA[15];
                    RFID_ID_RECEIVED[3] = RFID_DATA[16];
                    //                    sprintf(buffer, "RFID : %d %d %d %d", RFID_ID_RECEIVED[0], RFID_ID_RECEIVED[1], RFID_ID_RECEIVED[2], RFID_ID_RECEIVED[3]);
                    //                    SERCOM5_USART_Write(buffer, sizeof (buffer));
                    //
                    //                    while (!(SERCOM5_USART_TransmitComplete()));
                    rfid_data_t.RFID_IS[1] = RFID_DATA[13];
                    rfid_data_t.RFID_IS[2] = RFID_DATA[14];
                    rfid_data_t.RFID_IS[3] = RFID_DATA[15];
                    rfid_data_t.RFID_IS[4] = RFID_DATA[16];
                    rfid_data_t.RFID_IS[0] = 0x04;
                    xQueueOverwrite(ESP_S_RFID_QUEUE, &rfid_data_t);
                    BUZZER_Set();
                    vTaskDelay(1000);
                    BUZZER_Clear();
                    CURRENT_RFID_RX_SIZE = RFID_WAKEUP_RX_SIZE;
                    xTimerStart(rfid_timer, 40000);
                    vTaskResume(RFID_SEND_TASKHandle);
                } else {
                    CURRENT_RFID_RX_SIZE = RFID_ERROR_SIZE;
                }
                break;
            case RFID_ERROR_SIZE:
                CURRENT_RFID_RX_SIZE = RFID_WAKEUP_RX_SIZE;
                vTaskResume(RFID_SEND_TASKHandle);
                break;
        }
        SERCOM4_USART_Read(RFID_DATA, CURRENT_RFID_RX_SIZE);
        vTaskSuspend(RFID_RX_TASKHandle);
        vTaskDelay(1);
    }
}

void Start_ADC_TASK(void *argument) {
    static float TEMPERATURE_ADC_RAW_NEW;
    static float TEMPERATURE_VOLTAGE;
    float TEMPERATURE_SENSOR_DATA = 0;
    static float NE_VOLTAGE = 0, ACT_NE_VOLT = 0, ACT_GUN1_TEMP = 0, ACT_GUN2_TEMP = 0, ACT_GUN3_TEMP = 0, ACT_GUN4_TEMP = 0;
    uint16_t ADC_READ;
    ADC0_Enable();
    ADC1_Enable();
    ESP_Q_DATA espdata;
    memset(espdata.ESP_ARRAY, 0, sizeof (espdata.ESP_ARRAY));
    static uint8_t instance = 0;
    static uint16_t body_temp = 0;
    char buffer[50] = {0};
    uint8_t i = 0, j = 0, k = 0, l = 0;
    float TEMP1_ARRAY[10];
    float TEMP2_ARRAY[10];
    float TEMP3_ARRAY[10];
    float TEMP4_ARRAY[10];
    float TEMP1_AVG = 0, TEMP2_AVG = 0, TEMP3_AVG = 0, TEMP4_AVG = 0;
    float AVG_GUN1_TEMP, AVG_GUN2_TEMP;
    ESP_S_TEMP_Q esp_s_temp_data;
    for (;;) {

        ADC0_ChannelSelect((ADC_POSINPUT) ADC_POSINPUT_AIN0, (ADC_NEGINPUT) ADC_NEGINPUT_GND);
        ADC0_ConversionStart();
        while (!ADC0_ConversionStatusGet())
            ;
        TEMPERATURE_ADC_RAW_NEW = ADC0_ConversionResultGet();
        TEMPERATURE_VOLTAGE = (TEMPERATURE_ADC_RAW_NEW - 7.65) / 309.05;
        TEMPERATURE_SENSOR_DATA = ((TEMPERATURE_VOLTAGE - 2.62) / -13.75) * 1000;
        body_temp = (((int) TEMPERATURE_SENSOR_DATA));
        Update_Ambient_Temp(body_temp);
        vTaskDelay(100);

        if (body_temp > DEFAULT_BODY_TEMP_UPPER_LIMIT_t) {
            instance = 0;
            ERROR_CODE_ARRAY[SYSTEM_TEMP_HIGH_IDX] = 116;
            Update_System_Temperature_High_Status(0x01);
            vTaskDelay(100);
        }
        if ((body_temp < DEFAULT_BODY_TEMP_CLEAR_LIMIT_t) && (instance == 0)) {
            instance = 1;
            ERROR_CODE_ARRAY[SYSTEM_TEMP_HIGH_IDX] = 0;
            Update_System_Temperature_High_Status(0x00);
            vTaskDelay(100);
        }

        memset(&TEMPERATURE_SENSOR_DATA, 0, sizeof (TEMPERATURE_SENSOR_DATA));
        TEMPERATURE_VOLTAGE = 0;

        ADC0_ChannelSelect((ADC_POSINPUT) ADC_POSINPUT_AIN9, (ADC_NEGINPUT) ADC_NEGINPUT_GND);
        ADC0_ConversionStart();
        while (!ADC0_ConversionStatusGet())
            ;
        ADC_READ = ADC0_ConversionResultGet();
        NE_VOLTAGE = (3.3 / 1024) * ADC_READ;

        ACT_NE_VOLT = map(NE_VOLTAGE, 1.655, 3.3, 0, 400);
        if (ACT_NE_VOLT < 0) {
            ACT_NE_VOLT = 0;
        }
        if (ACT_NE_VOLT > DEFAULT_NE_VOLT_LIMIT_t) {
            Update_High_NE_Voltage_Status(0x01);
            vTaskDelay(100);
            ERROR_CODE_ARRAY[HIGH_NE_IDX] = 110;
        } else {
            Update_High_NE_Voltage_Status(0x00);
            vTaskDelay(100);
            ERROR_CODE_ARRAY[HIGH_NE_IDX] = 0;
        }
        ADC_READ = 0;
        memset(buffer, 0, sizeof (buffer));
        ADC1_ChannelSelect((ADC_POSINPUT) ADC_POSINPUT_AIN10, (ADC_NEGINPUT) ADC_NEGINPUT_GND);
        ADC1_ConversionStart();
        while (!ADC1_ConversionStatusGet())
            ;
        ADC_READ = ADC1_ConversionResultGet();
        ACT_GUN1_TEMP = map(ADC_READ, 175, 557, 0, 65);
        TEMP1_ARRAY[i] = ACT_GUN1_TEMP;
        i++;
        if (i >= 10) {
            i = 0;
        }
        for (int a = 0; a < 10; a++) {
            TEMP1_AVG = TEMP1_AVG + TEMP1_ARRAY[a];
        }
        TEMP1_AVG = TEMP1_AVG / 10;
        ADC_READ = 0;
        memset(buffer, 0, sizeof (buffer));
        ADC1_ChannelSelect((ADC_POSINPUT) ADC_POSINPUT_AIN11, (ADC_NEGINPUT) ADC_NEGINPUT_GND);
        ADC1_ConversionStart();
        while (!ADC1_ConversionStatusGet())
            ;
        ADC_READ = ADC1_ConversionResultGet();
        ACT_GUN2_TEMP = map(ADC_READ, 175, 557, 0, 65);
        TEMP2_ARRAY[j] = ACT_GUN2_TEMP;
        j++;
        if (j >= 10) {
            j = 0;
        }
        for (int b = 0; b < 10; b++) {
            TEMP2_AVG = TEMP2_AVG + TEMP2_ARRAY[b];
        }
        TEMP2_AVG = TEMP2_AVG / 10;
        ADC_READ = 0;
        memset(buffer, 0, sizeof (buffer));
        ADC1_ChannelSelect((ADC_POSINPUT) ADC_POSINPUT_AIN4, (ADC_NEGINPUT) ADC_NEGINPUT_GND);
        ADC1_ConversionStart();
        while (!ADC1_ConversionStatusGet())
            ;
        ADC_READ = ADC1_ConversionResultGet();
        ACT_GUN3_TEMP = map(ADC_READ, 175, 557, 0, 65);
        TEMP3_ARRAY[k] = ACT_GUN3_TEMP;
        k++;
        if (k >= 10) {
            k = 0;
        }
        for (int c = 0; c < 10; c++) {
            TEMP3_AVG = TEMP3_AVG + TEMP3_ARRAY[c];
        }
        TEMP3_AVG = TEMP3_AVG / 10;
        ADC_READ = 0;
        memset(buffer, 0, sizeof (buffer));
        ADC1_ChannelSelect((ADC_POSINPUT) ADC_POSINPUT_AIN5, (ADC_NEGINPUT) ADC_NEGINPUT_GND);
        ADC1_ConversionStart();
        while (!ADC1_ConversionStatusGet())
            ;
        ADC_READ = ADC1_ConversionResultGet();
        ACT_GUN4_TEMP = map(ADC_READ, 175, 557, 0, 65);
        TEMP4_ARRAY[l] = ACT_GUN4_TEMP;
        l++;
        if (l >= 10) {
            l = 0;
        }
        for (int d = 0; d < 10; d++) {
            TEMP4_AVG = TEMP4_AVG + TEMP4_ARRAY[d];
        }
        TEMP4_AVG = TEMP4_AVG / 10;
        ADC_READ = 0;
        memset(buffer, 0, sizeof (buffer));

        esp_s_temp_data.body_temp = body_temp;
        esp_s_temp_data.Gun_temp_1 = TEMP1_AVG;
        esp_s_temp_data.Gun_temp_1_1 = TEMP2_AVG;
        esp_s_temp_data.Gun_temp_2 = TEMP3_AVG;
        esp_s_temp_data.Gun_temp_2_1 = TEMP4_AVG;
        xQueueOverwrite(ESP_S_TEMP_QUEUE, &esp_s_temp_data);

        AVG_GUN1_TEMP = TEMP2_AVG; //(TEMP1_AVG + TEMP2_AVG) / 2;
        AVG_GUN2_TEMP = TEMP4_AVG; //(TEMP3_AVG + TEMP4_AVG) / 2;
        Update_GUN1_Temp((uint16_t) AVG_GUN1_TEMP);
        vTaskDelay(100);
        Update_GUN2_Temp((uint16_t) AVG_GUN2_TEMP);
        vTaskDelay(100);
        //        if (AVG_GUN1_TEMP > DEFAULT_GUN1_TEMP_LIMIT_t) {
        //            Update_GUN1_Temp_High_Status(0x01);
        //            ERROR_CODE_ARRAY[GUN_TEMP_HIGH_IDX] = 117;
        //            ERROR_CODE_ARRAY[GUN_TEMP_CONN_NO] = 1;
        //        } else {
        //            Update_GUN1_Temp_High_Status(0x00);
        //        }
        //        if (AVG_GUN2_TEMP > DEFAULT_GUN2_TEMP_LIMIT_t) {
        //            Update_GUN2_Temp_High_Status(0x01);
        //            ERROR_CODE_ARRAY[GUN_TEMP_HIGH_IDX] = 117;
        //            ERROR_CODE_ARRAY[GUN_TEMP_CONN_NO] = 2;
        //        } else {
        //            Update_GUN2_Temp_High_Status(0x00);
        //        }
        //        if ((AVG_GUN1_TEMP < DEFAULT_GUN_TEMPERATURE_POINT_CLEAR_VALUE_t) && (AVG_GUN2_TEMP < DEFAULT_GUN_TEMPERATURE_POINT_CLEAR_VALUE_t)) {
        //
        //            Update_GUN2_Temp_High_Status(0x00);
        //            Update_GUN1_Temp_High_Status(0x00);
        //            ERROR_CODE_ARRAY[GUN_TEMP_HIGH_IDX] = 0;
        //        }
        vTaskDelay(2800);
    }
}

void Start_RGB_SEND_TASK(void *argument) {
    static uint8_t COLOR, COLOR2 = 0;
    COLOR1_Q color1msg;
    COLOR2_Q color2msg;
    for (;;) {

        if (xQueueReceive(COLOR1_QUEUE, &color1msg, 0)) {
            COLOR = color1msg.COLOR1;
        }
        if (xQueueReceive(COLOR2_QUEUE, &color2msg, 0)) {
            COLOR2 = color2msg.COLOR2;
        }
        if (mains_fail_led == 1) {
            COLOR = RED;
            COLOR2 = RED2;
        }
        switch (COLOR) {
            case RED:
                RED1_Set();
                GREEN1_Clear();
                BLUE1_Clear();
                vTaskDelay(1);
                break;

            case GREEN:
                RED1_Clear();
                GREEN1_Set();
                BLUE1_Clear();
                vTaskDelay(1);
                break;

            case BLUE:
                RED1_Clear();
                GREEN1_Clear();
                BLUE1_Set();
                vTaskDelay(1);
                break;

            case YELLOW:
                RED1_Set();
                GREEN1_Set();
                BLUE1_Clear();
                vTaskDelay(1);
                break;

            case CYAN:
                RED1_Clear();
                GREEN1_Set();
                BLUE1_Set();
                vTaskDelay(1);
                break;
            case MAGENTA:
                RED1_Set();
                GREEN1_Clear();
                BLUE1_Set();
                vTaskDelay(1);
                break;

            case NO_COLOR:
                RED1_Clear();
                GREEN1_Clear();
                BLUE1_Clear();
                vTaskDelay(1);
                break;

            case WHITE:
                RED1_Set();
                GREEN1_Set();
                BLUE1_Set();
                vTaskDelay(1);
                break;
        }
        switch (COLOR2) {
            case WHITE2:
                RED2_Set();
                GREEN2_Set();
                BLUE2_Set();
                vTaskDelay(1);
                break;
            case RED2:
                RED2_Set();
                GREEN2_Clear();
                BLUE2_Clear();
                vTaskDelay(1);
                break;
            case GREEN2:
                RED2_Clear();
                GREEN2_Set();
                BLUE2_Clear();
                vTaskDelay(1);
                break;

            case BLUE2:
                RED2_Clear();
                GREEN2_Clear();
                BLUE2_Set();
                vTaskDelay(1);
                break;

            case YELLOW2:
                RED2_Set();
                GREEN2_Set();
                BLUE2_Clear();
                vTaskDelay(1);
                break;

            case CYAN2:
                RED2_Clear();
                GREEN2_Set();
                BLUE2_Set();
                vTaskDelay(1);
                break;

            case MAGENTA2:
                RED2_Set();
                GREEN2_Clear();
                BLUE2_Set();
                vTaskDelay(1);
                break;
            case NO_COLOR2:
                RED2_Clear();
                GREEN2_Clear();
                BLUE2_Clear();
                vTaskDelay(1);

                break;
        }
        vTaskDelay(100);
    }
}

void Start_I2C_TMP_HUM_TASK(void *argument) {
    uint8_t I2C_SELECT_CHANNEL = I2C_CHANNEL0;
    uint8_t i2c_data_command = 0xFD;
    uint8_t i2c_receive_data[6] = {0};
    float t_ticks, rh_ticks, temp, hum;
    uint8_t command;
    char buffer[50] = {0};
    for (;;) {

        switch (I2C_SELECT_CHANNEL) {
            case I2C_CHANNEL0:
                command = 1 << 0;
                SERCOM3_I2C_Write((uint16_t) MUX_DEVICE_ADR, (uint8_t *)&(command), 1);
                vTaskDelay(10);
                SERCOM3_I2C_Write((uint16_t) SENSOR_DEVICE_ADR, (uint8_t *) & i2c_data_command, DEVICE_DATA_LENGTH);
                vTaskDelay(10);
                SERCOM3_I2C_Read((uint16_t) SENSOR_DEVICE_ADR, (uint8_t *) & i2c_receive_data, TEMP_DATA_LENGTH);
                vTaskDelay(10);
                t_ticks = (((float) i2c_receive_data[0] * 256) + (float) i2c_receive_data[1]);
                rh_ticks = (((float) i2c_receive_data[3] * 256) + (float) i2c_receive_data[4]);
                temp = -45 + (175 * (t_ticks / 65535));
                hum = -6 + (125 * (rh_ticks / 65535));
                memset(buffer,0,sizeof(buffer));
                sprintf(buffer, "Channel: 0, Temp: %.2f C, Humidity: %.2f %%\r\n", temp, hum);
                SERCOM5_USART_Write(buffer, sizeof (buffer));
                while (!(SERCOM5_USART_TransmitComplete()));
                Update_Rec1_temp((uint8_t) temp);
                temp = 0;
                hum = 0;
                I2C_SELECT_CHANNEL = I2C_CHANNEL1;

                break;
            case I2C_CHANNEL1:
                command = 1 << 1;
                SERCOM3_I2C_Write((uint16_t) MUX_DEVICE_ADR, (uint8_t *)&(command), 1);
                vTaskDelay(10);
                SERCOM3_I2C_Write((uint16_t) SENSOR_DEVICE_ADR, (uint8_t *) & i2c_data_command, DEVICE_DATA_LENGTH);
                vTaskDelay(10);
                SERCOM3_I2C_Read((uint16_t) SENSOR_DEVICE_ADR, (uint8_t *) & i2c_receive_data, TEMP_DATA_LENGTH);
                vTaskDelay(10);
                t_ticks = (((float) i2c_receive_data[0] * 256) + (float) i2c_receive_data[1]);
                rh_ticks = (((float) i2c_receive_data[3] * 256) + (float) i2c_receive_data[4]);
                temp = -45 + (175 * (t_ticks / 65535));
                hum = -6 + (125 * (rh_ticks / 65535));
                memset(buffer,0,sizeof(buffer));
                sprintf(buffer, "Channel: 1, Temp: %.2f C, Humidity: %.2f %%\r\n", temp, hum);
                SERCOM5_USART_Write(buffer, sizeof (buffer));
                while (!(SERCOM5_USART_TransmitComplete()));
                Update_Rec2_temp((uint8_t) temp);
                temp = 0;
                hum = 0;
                I2C_SELECT_CHANNEL = I2C_CHANNEL0;
                break;
                
        }
        vTaskDelay(3000);
    }
}

void StartCANrecieveTask(void *argument) {
    CAN0_RECIEVE_Q msg;
    _C101_Q _c101msg = {0};
    _C501_Q _c501msg = {0};
    _C102_Q _c102msg = {0};
    _C502_Q _c502msg = {0};
    _C103_Q _c103msg = {0};
    _C503_Q _c503msg = {0};
    _C104_Q _c104msg = {0};
    _C504_Q _c504msg = {0};
    _C105_Q _c105msg = {0};
    _C505_Q _c505msg = {0};
    _C106_Q _c106msg = {0};
    _C506_Q _c506msg = {0};
    _C107_Q _c107msg = {0};
    _C507_Q _c507msg = {0};
    _C108_Q _c108msg = {0};
    _C508_Q _c508msg = {0};
    _C109_Q _c109msg = {0};
    _C509_Q _c509msg = {0};
    _C10A_Q _c10Amsg = {0};
    _C50A_Q _c50Amsg = {0};
    _C10B_Q _c10Bmsg = {0};
    _C50B_Q _c50Bmsg = {0};
    _C1FF_Q _c1FFmsg = {0};
    _C5FF_Q _c5FFmsg = {0};
    _D101_Q _d101msg = {0};
    _D501_Q _d501msg = {0};
    static float current_to_give = 0, current_to_give1 = 0;

    char buffffffffff[70] = {0};
    memset(msg.data, 0, sizeof (msg.data));
    xTimerStart(_50_sec_timer, 50);
    xTimerStart(_200_sec_timer, 200);
    xTimerStart(_500_sec_timer, 500);
    xTimerStart(_1000_sec_timer, 1000);
    if (GUN1_ENABLE_DISABLE == DEFAULT_GUN1_DISABLE) {
        vTaskSuspend(_1_PLC_MANAGE_TASKHandle);
        Change_gun1_status_to(UNAVAILABLE);
    }
    if (GUN2_ENABLE_DISABLE == DEFAULT_GUN2_DISABLE) {
        vTaskSuspend(_2_PLC_MANAGE_TASKHandle);
        Change_gun2_status_to(UNAVAILABLE);
    }
    if (GUN1_ENABLE_DISABLE == DEFAULT_GUN1_ENABLE) {
        vTaskResume(_1_PLC_MANAGE_TASKHandle);
        Change_gun1_status_to(AVAILABLE);
    }
    if (GUN2_ENABLE_DISABLE == DEFAULT_GUN2_ENABLE) {
        vTaskResume(_2_PLC_MANAGE_TASKHandle);
        Change_gun2_status_to(AVAILABLE);
    }
    vTaskResume(SMOKE_LIMIT_TASKHandle);
    vTaskDelay(1000);
    ////////HMI/////////////
    Change_Page_to(CURRENT_PAGE);
    vTaskDelay(100);
    Change_gun1_status_to(AVAILABLE);
    vTaskDelay(100);
    Change_gun2_status_to(AVAILABLE);
    vTaskDelay(100);
    ////////////////////////
    BaseType_t xTaskWokenByReceive = pdFALSE;
    ENABLE_HMI_Set();
    SERCOM6_USART_Write(CHARGER_LINK, sizeof (CHARGER_LINK));
    while (!(SERCOM6_USART_TransmitComplete()))
        ;
    ENABLE_HMI_Clear();
    for (;;) {

        if (xQueueReceiveFromISR(CAN0_QUEUE, &msg, &xTaskWokenByReceive)) {
            switch (rxBuf->id) {
                case 0x15ECC101:
                    xTimerStop(plc1_timer, 1);
                    plc1_fail = 0;
                    if (plc1_fail_inst == 0) {
                        MACHINE_STATE = IDLE_STATE;
                        plc1_fail_inst = 1;
                    }
                    _c101msg.heartbeat = rxBuf->data[0];
                    _c101msg._101_SECC_Status_t = rxBuf->data[1];
                    _c101msg._101_SECC_evERRORCODE_t = rxBuf->data[2];
                    _c101msg._101_SECC_seccERROR_CODES_t = rxBuf->data[3];
                    _c101msg.seccVersionMajor = rxBuf->data[4];
                    _c101msg.seccVersionMinor = rxBuf->data[5];
                    _c101msg.seccVersionPatch = rxBuf->data[6];
                    _c101msg._101_SECC_PnCREADY_t = rxBuf->data[7];
                    xQueueOverwrite(_C101_QUEUE, &_c101msg);
                    vTaskDelay(100);
                    break;
                case 0x15ECC102:
                    _c102msg._102_SECC_CP_t = (rxBuf->data[0] & 0x01);
                    _c102msg.cpVoltage_msb = rxBuf->data[1];
                    _c102msg.cpVoltage_lsb = rxBuf->data[2];
                    _c102msg._102_SECC_HpgpLink_t = rxBuf->data[3];
                    _c102msg._102_SECC_TLSERROR_t = rxBuf->data[4];
                    xQueueOverwrite(_C102_QUEUE, &_c102msg);
                    vTaskDelay(100);
                    break;
                case 0x15ECC103:
                    _c103msg._103_SELECTED_CHARGING_PROTOCOL_t = rxBuf->data[0];
                    _c103msg._103_SELECTED_PAYMENT_OPTION_t = rxBuf->data[1];
                    _c103msg._103_SELECTED_ENERGY_TRANSFER_MODE_t = rxBuf->data[3];
                    _c103msg.selected_SAS_sch_tuple_id =
                            rxBuf->data[4];
                    _c103msg.Selected_service_EVCharging = (rxBuf->data[2]) & 0x01;
                    _c103msg.Selected_service_Internet = (rxBuf->data[2]) & 0x02;
                    _c103msg.Selected_Service_ContractCert = (rxBuf->data[2]) & 0x04;
                    _c103msg.Selected_OtherCustoms = (rxBuf->data[2]) & 0x08;
                    _c103msg.Selected_HPC1 = (rxBuf->data[2]) & 0x10;
                    _c103msg.Selected_ContractServiceInstallation = (rxBuf->data[2]) & 0x20;
                    _c103msg.Selected_contractServiceUpdate = (rxBuf->data[2]) & 0x40;
                    xQueueOverwrite(_C103_QUEUE, &_c103msg);
                    vTaskDelay(100);
                    break;
                case 0x15ECC104:
                    _c104msg.sessionID_msb3 = rxBuf->data[0];
                    _c104msg.sessionID_msb2 = rxBuf->data[1];
                    _c104msg.sessionID_msb1 = rxBuf->data[2];
                    _c104msg.sessionID_msb0 = rxBuf->data[3];
                    _c104msg.sessionID_lsb3 = rxBuf->data[4];
                    _c104msg.sessionID_lsb2 = rxBuf->data[5];
                    _c104msg.sessionID_lsb1 = rxBuf->data[6];
                    _c104msg.sessionID_lsb0 = rxBuf->data[7];
                    xQueueOverwrite(_C104_QUEUE, &_c104msg);
                    vTaskDelay(100);
                    break;
                case 0x15ECC105:
                    _c105msg.evccMAC_Data5 = rxBuf->data[0];
                    _c105msg.evccMAC_Data4 = rxBuf->data[1];
                    _c105msg.evccMAC_Data3 = rxBuf->data[2];
                    _c105msg.evccMAC_Data2 = rxBuf->data[3];
                    _c105msg.evccMAC_Data1 = rxBuf->data[4];
                    _c105msg.evccMAC_Data0 = rxBuf->data[5];
                    _c105msg.evccAttn = rxBuf->data[6];

                    //                    sprintf(buffffffffff, "attentuation1 %d \r\n", _c105msg.evccAttn);
                    //                    SERCOM5_USART_Write(buffffffffff, sizeof (buffffffffff));
                    //                    while (!SERCOM5_USART_TransmitComplete());
                    xQueueOverwrite(_C105_QUEUE, &_c105msg);
                    vTaskDelay(100);
                    break;
                case 0x15ECC106:
                    _c106msg.departure_timemsb1 = rxBuf->data[2];
                    _c106msg.departure_timemsb0 = rxBuf->data[3];
                    _c106msg.departure_timelsb1 = rxBuf->data[4];
                    _c106msg.departure_timelsb0 = rxBuf->data[5];
                    _c106msg.maxEntriesSAASSchedulemsb =
                            rxBuf->data[0];
                    _c106msg.maxEntriesSAASSchedulelsb =
                            rxBuf->data[1];
                    _c106msg.evMaximumPowerLimitmsb =
                            rxBuf->data[6];
                    _c106msg.evMaximumPowerLimitlsb =
                            rxBuf->data[7];
                    xQueueOverwrite(_C106_QUEUE, &_c106msg);
                    vTaskDelay(100);
                    break;
                case 0x15ECC107:
                    _c107msg.evMaximumCurrentLimitmsb =
                            rxBuf->data[0];
                    _c107msg.evMaximumCurrentLimitlsb =
                            rxBuf->data[1];
                    _c107msg.evMaximumVoltageLimitmsb =
                            rxBuf->data[2];
                    _c107msg.evMaximumVoltageLimitlsb =
                            rxBuf->data[3];
                    _c107msg.evEnergyCapacitymsb = rxBuf->data[4];
                    _c107msg.evEnergyCapacitylsb = rxBuf->data[5];
                    _c107msg.evEnergyRequestmsb = rxBuf->data[6];
                    _c107msg.evEnergyRequestlsb = rxBuf->data[7];
                    if ((_c107msg.evMaximumVoltageLimitmsb) > 0 && (_c107msg.evMaximumVoltageLimitlsb) > 0) {
                        xQueueOverwrite(_C107_QUEUE, &_c107msg);
                    }
                    vTaskDelay(100);
                    break;
                case 0x15ECC108:
                    _c108msg.Charging_Complete_t = (rxBuf->data[0]) & 0x03;
                    _c108msg.Charging_BULK_Complete = (rxBuf->data[0]) & 0x0C;
                    _c108msg.evSOC = rxBuf->data[1];
                    _c108msg.fullSOC = rxBuf->data[2];
                    _c108msg.bulkSOC = rxBuf->data[3];
                    _c108msg.remainingTimeToFullSOCmsb =
                            rxBuf->data[4];
                    _c108msg.remainingTimeToFullSOClsb =
                            rxBuf->data[5];
                    _c108msg.remainingTimeToBulkSOCmsb =
                            rxBuf->data[6];
                    _c108msg.remainingTimeToBulkSOClsb =
                            rxBuf->data[7];
                    xQueueOverwrite(_C108_QUEUE, &_c108msg);
                    vTaskDelay(100);
                    break;
                case 0x15ECC109:
                    _c109msg.targetVoltagemsb = rxBuf->data[0];
                    _c109msg.targetVoltagelsb = rxBuf->data[1];
                    _c109msg.targetCurrentmsb = rxBuf->data[2];
                    _c109msg.targetCurrentlsb = rxBuf->data[3];
                    if ((_c109msg.targetVoltagemsb) > 0 && (_c109msg.targetVoltagelsb) > 0) {
                        xQueueOverwrite(_C109_QUEUE, &_c109msg);
                    }
                    //                    current_to_give = (((_c109msg.targetCurrentlsb) << 8) + _c109msg.targetCurrentmsb) / 10;
                    //                    sprintf(buffffffffff, "current recieved from PLC1 : %f\r\n", current_to_give);
                    //                    SERCOM5_USART_Write(buffffffffff, sizeof (buffffffffff));
                    //                    while (!SERCOM5_USART_TransmitComplete());
                    vTaskDelay(100);
                    break;
                    //
                case 0x15ECC10A:
                    _c10Amsg.seccTimeStamp_Data0 = rxBuf->data[0];
                    _c10Amsg.seccTimeStamp_Data1 = rxBuf->data[1];
                    _c10Amsg.seccTimeStamp_Data2 = rxBuf->data[2];
                    _c10Amsg.seccTimeStamp_Data3 = rxBuf->data[3];
                    _c10Amsg.seccTimeStamp_Data4 = rxBuf->data[4];
                    _c10Amsg.seccTimeStamp_Data5 = rxBuf->data[5];
                    _c10Amsg.seccTimeStamp_Data6 = rxBuf->data[6];
                    _c10Amsg.seccTimeStamp_Data7 = rxBuf->data[7];
                    xQueueOverwrite(_C10A_QUEUE, &_c10Amsg);
                    vTaskDelay(100);
                    break;

                case 0x15ECC10B:
                    _c10Bmsg._10B_SECC_STATUS3_t = rxBuf->data[0];
                    _c10Bmsg._10B_SECC_STATUS3_ESTABLISHEDINFO_t = rxBuf->data[7];
                    xQueueOverwrite(_C10B_QUEUE, &_c10Bmsg);
                    vTaskDelay(100);
                    break;
                case 0x15ECC1FF:
                    _c1FFmsg.notificationCount = rxBuf->data[0];
                    xQueueOverwrite(_C1FF_QUEUE, &_c1FFmsg);
                    vTaskDelay(100);
                    break;
                case 0x15ECD101:
                    _d101msg._ECD101_SECC_COMM_STATUS_SAGENTINIT_Details_t = rxBuf->data[1];
                    _d101msg._ECD101_SECC_COMM_STATUS_SAGENTINIT_t = rxBuf->data[0];
                    xQueueOverwrite(_D101_QUEUE, &_d101msg);
                    vTaskDelay(100);
                    break;
                    //
                case 0x15ECC501:

                    xTimerStop(plc2_timer, 1);
                    plc2_fail = 0;
                    if (plc2_fail_inst == 0) {
                        MACHINE_STATE = IDLE_STATE;
                        plc2_fail_inst = 1;
                    }
                    _c501msg.heartbeat = rxBuf->data[0];
                    _c501msg._501_SECC_Status_t = rxBuf->data[1];
                    _c501msg._501_SECC_evERRORCODE_t = rxBuf->data[2];
                    _c501msg._501_SECC_seccERROR_CODES_t = rxBuf->data[3];
                    _c501msg.seccVersionMajor = rxBuf->data[4];
                    _c501msg.seccVersionMinor = rxBuf->data[5];
                    _c501msg.seccVersionPatch = rxBuf->data[6];
                    _c501msg._501_SECC_PnCREADY_t = rxBuf->data[7];
                    xQueueOverwrite(_C501_QUEUE, &_c501msg);
                    vTaskDelay(100);
                    break;
                case 0x15ECC502:
                    _c502msg._502_SECC_CP_t = (rxBuf->data[0] & 0x01);
                    _c502msg.cpVoltage_msb = rxBuf->data[1];
                    _c502msg.cpVoltage_lsb = rxBuf->data[2];
                    _c502msg._502_SECC_HpgpLink_t = rxBuf->data[3];
                    _c502msg._502_SECC_TLSERROR_t = rxBuf->data[4];
                    xQueueOverwrite(_C502_QUEUE, &_c502msg);
                    vTaskDelay(100);
                    break;
                case 0x15ECC503:
                    _c503msg._503_SELECTED_CHARGING_PROTOCOL_t = rxBuf->data[0];
                    _c503msg._503_SELECTED_PAYMENT_OPTION_t = rxBuf->data[1];
                    _c503msg._503_SELECTED_ENERGY_TRANSFER_MODE_t = rxBuf->data[3];
                    _c503msg.selected_SAS_sch_tuple_id =
                            rxBuf->data[4];
                    _c503msg.Selected_service_EVCharging = (rxBuf->data[2]) & 0x01;
                    _c503msg.Selected_service_Internet = (rxBuf->data[2]) & 0x02;
                    _c503msg.Selected_Service_ContractCert = (rxBuf->data[2]) & 0x04;
                    _c503msg.Selected_OtherCustoms = (rxBuf->data[2]) & 0x08;
                    _c503msg.Selected_HPC1 = (rxBuf->data[2]) & 0x10;
                    _c503msg.Selected_ContractServiceInstallation = (rxBuf->data[2]) & 0x20;
                    _c503msg.Selected_contractServiceUpdate = (rxBuf->data[2]) & 0x40;
                    xQueueOverwrite(_C503_QUEUE, &_c503msg);
                    vTaskDelay(100);
                    break;
                case 0x15ECC504:
                    _c504msg.sessionID_msb3 = rxBuf->data[0];
                    _c504msg.sessionID_msb2 = rxBuf->data[1];
                    _c504msg.sessionID_msb1 = rxBuf->data[2];
                    _c504msg.sessionID_msb0 = rxBuf->data[3];
                    _c504msg.sessionID_lsb3 = rxBuf->data[4];
                    _c504msg.sessionID_lsb2 = rxBuf->data[5];
                    _c504msg.sessionID_lsb1 = rxBuf->data[6];
                    _c504msg.sessionID_lsb0 = rxBuf->data[7];
                    xQueueOverwrite(_C504_QUEUE, &_c504msg);
                    vTaskDelay(100);
                    break;
                case 0x15ECC505:
                    _c505msg.evccMAC_Data5 = rxBuf->data[0];
                    _c505msg.evccMAC_Data4 = rxBuf->data[1];
                    _c505msg.evccMAC_Data3 = rxBuf->data[2];
                    _c505msg.evccMAC_Data2 = rxBuf->data[3];
                    _c505msg.evccMAC_Data1 = rxBuf->data[4];
                    _c505msg.evccMAC_Data0 = rxBuf->data[5];
                    _c505msg.evccAttn = rxBuf->data[6];
                    xQueueOverwrite(_C505_QUEUE, &_c505msg);
                    vTaskDelay(100);
                    break;
                case 0x15ECC506:
                    _c506msg.departure_timemsb1 = rxBuf->data[2];
                    _c506msg.departure_timemsb0 = rxBuf->data[3];
                    _c506msg.departure_timelsb1 = rxBuf->data[4];
                    _c506msg.departure_timelsb0 = rxBuf->data[5];
                    _c506msg.maxEntriesSAASSchedulemsb =
                            rxBuf->data[0];
                    _c506msg.maxEntriesSAASSchedulelsb =
                            rxBuf->data[1];
                    _c506msg.evMaximumPowerLimitmsb =
                            rxBuf->data[6];
                    _c506msg.evMaximumPowerLimitlsb =
                            rxBuf->data[7];
                    xQueueOverwrite(_C506_QUEUE, &_c506msg);
                    vTaskDelay(100);
                    break;
                case 0x15ECC507:
                    _c507msg.evMaximumCurrentLimitmsb =
                            rxBuf->data[0];
                    _c507msg.evMaximumCurrentLimitlsb =
                            rxBuf->data[1];
                    _c507msg.evMaximumVoltageLimitmsb =
                            rxBuf->data[2];
                    _c507msg.evMaximumVoltageLimitlsb =
                            rxBuf->data[3];
                    _c507msg.evEnergyCapacitymsb = rxBuf->data[4];
                    _c507msg.evEnergyCapacitylsb = rxBuf->data[5];
                    _c507msg.evEnergyRequestmsb = rxBuf->data[6];
                    _c507msg.evEnergyRequestlsb = rxBuf->data[7];
                    if ((_c507msg.evMaximumVoltageLimitmsb) > 0 && (_c507msg.evMaximumVoltageLimitlsb) > 0) {
                        xQueueOverwrite(_C507_QUEUE, &_c507msg);
                    }
                    vTaskDelay(100);
                    break;
                case 0x15ECC508:
                    _c508msg.Charging_Complete_t = (rxBuf->data[0]) & 0x03;
                    _c508msg.Charging_BULK_Complete = (rxBuf->data[0]) & 0x0C;
                    _c508msg.evSOC = rxBuf->data[1];
                    _c508msg.fullSOC = rxBuf->data[2];
                    _c508msg.bulkSOC = rxBuf->data[3];
                    _c508msg.remainingTimeToFullSOCmsb =
                            rxBuf->data[4];
                    _c508msg.remainingTimeToFullSOClsb =
                            rxBuf->data[5];
                    _c508msg.remainingTimeToBulkSOCmsb =
                            rxBuf->data[6];
                    _c508msg.remainingTimeToBulkSOClsb =
                            rxBuf->data[7];
                    xQueueOverwrite(_C508_QUEUE, &_c508msg);
                    vTaskDelay(100);
                    break;
                case 0x15ECC509:
                    _c509msg.targetVoltagemsb = rxBuf->data[0];
                    _c509msg.targetVoltagelsb = rxBuf->data[1];
                    _c509msg.targetCurrentmsb = rxBuf->data[2];
                    _c509msg.targetCurrentlsb = rxBuf->data[3];
                    if (_c509msg.targetVoltagemsb > 0 && _c509msg.targetVoltagelsb > 0) {
                        xQueueOverwrite(_C509_QUEUE, &_c509msg);
                    }
                    //                    current_to_give1 = (((_c509msg.targetCurrentlsb) << 8) + _c509msg.targetCurrentmsb) / 10;
                    //                    sprintf(buffffffffff, "current recieved from PLC2 : %f\r\n", current_to_give1);
                    //                    SERCOM5_USART_Write(buffffffffff, sizeof (buffffffffff));
                    //                    while (!SERCOM5_USART_TransmitComplete());
                    vTaskDelay(100);
                    break;

                case 0x15ECC50A:
                    _c50Amsg.seccTimeStamp_Data0 = rxBuf->data[0];
                    _c50Amsg.seccTimeStamp_Data1 = rxBuf->data[1];
                    _c50Amsg.seccTimeStamp_Data2 = rxBuf->data[2];
                    _c50Amsg.seccTimeStamp_Data3 = rxBuf->data[3];
                    _c50Amsg.seccTimeStamp_Data4 = rxBuf->data[4];
                    _c50Amsg.seccTimeStamp_Data5 = rxBuf->data[5];
                    _c50Amsg.seccTimeStamp_Data6 = rxBuf->data[6];
                    _c50Amsg.seccTimeStamp_Data7 = rxBuf->data[7];
                    xQueueOverwrite(_C50A_QUEUE, &_c50Amsg);
                    vTaskDelay(100);
                    break;
                case 0x15ECC50B:
                    _c50Bmsg._50B_SECC_STATUS3_t = rxBuf->data[0];
                    _c50Bmsg._50B_SECC_STATUS3_ESTABLISHEDINFO_t = rxBuf->data[7];
                    xQueueOverwrite(_C50B_QUEUE, &_c50Bmsg);
                    vTaskDelay(100);
                    break;
                case 0x15ECC5FF:
                    _c5FFmsg.notificationCount = rxBuf->data[0];
                    xQueueOverwrite(_C5FF_QUEUE, &_c5FFmsg);
                    vTaskDelay(100);
                    break;
                case 0x15ECD501:
                    _d501msg._ECD501_SECC_COMM_STATUS_SAGENTINIT_Details_t = rxBuf->data[1];
                    _d501msg._ECD501_SECC_COMM_STATUS_SAGENTINIT_t = rxBuf->data[0];
                    xQueueOverwrite(_D501_QUEUE, &_d501msg);
                    vTaskDelay(100);

                    break;
            }
        }
        vTaskSuspend(canrecievetask);
        vTaskDelay(1);
    }
}

void Start_1_PLC_MANAGE_TASK(void *argument) {
    _C101_Q _c101msg = {0};
    _C105_Q _c105msg = {0};
    _C102_Q _c102msg = {0};
    _C10B_Q _c10bmsg = {0};
    _C107_Q _c107msg = {0};
    _C109_Q _c109msg = {0};
    _C108_Q _c108msg = {0};
    _50MS_Q _50msmsg = {0};
    _200MS_Q _200msmsg = {0};
    _1000MS_Q _1000msmsg = {0};
    _1_PLC_tx_50 _1_PLC_tx_50_t = {0};
    _1_PLC_tx_1000 _1_PLC_tx_1000_t = {0};
    _1_PLC_tx_200 _1_PLC_tx_200_t = {0};
    RECTIFIER_Q rectimsg = {0};
    FLASH_WRITE_Q flashmsg;
    ESP_Q_DATA espmsg;
    memset(espmsg.ESP_ARRAY, 0, sizeof (espmsg.ESP_ARRAY));
    LED1_Q leddata;
    RELAY_Q relaymsg;
    static float MAX_VOLT_LIMIT = 0;
    static float voltage_to_give = 0;
    static float current_to_give = 0;
    static float act_current_to_give = 0;
    memset(relaymsg.RELAY_DATA, 0, sizeof (relaymsg.RELAY_DATA));
    static int count = 0;
    static int gun_count = 0;
    static int instance = 0;
    static int instance1 = 0;
    static uint8_t initial_SOC1 = 0;
    static float STARTING_UNIT = 0;
    static float STOPING_UNIT = 0;
    static uint32_t DIFF_UNIT = 0;
    static uint8_t CP_Level_1 = 0;
    static uint8_t SOC_1 = 0;
    static uint8_t SOC_1_ARRAY[5] = {0};
    static uint8_t i_count = 0;
    static uint8_t j_count = 0;
    static uint16_t Demand_Voltage1 = 0;
    static float Demand_Voltage1_ARRAY[5] = {0};
    static uint16_t Demand_Current1 = 0;
    static float Demand_Current1_ARRAY[5] = {0};
    static uint16_t GUN1_CHARGING_TIME = 0;
    static float MAX_CURR_LIMIT_PLC = 0;
    static uint8_t SOC1_INITIAL = 0;
    ESP_S_GUN1_P_Q esp_s_gun1_p;
    static uint8_t page_change_inst = 0;
    static float power = 0;
    static uint8_t FINAL_INITIAL_SOC = 0;
    CP_LEVEL1_Q cplevel1;
    static float Difference_in_VOLTAGE1 = 0;
    ESP_S_RFID_CONN_NO_Q rfid_conn_no_data;
    ESP_S_MAC_ID_CONN_NO_Q mac_id_conn_no_data;
    ESP_S_MAC_ID_Q mac_id_data;
    GUN1_CHARGING_TIME_Q value;
    static uint8_t slac_count = 0;
    for (;;) {

        switch (CURRENT_PLC1_STATE) {

            case _1_PLC_STATE_IDLE_1:
                vTaskResume(LED_TASKHandle);
                initial_SOC1 = 0;
                Demand_Current1 = 0;
                Demand_Voltage1 = 0;
                GUN1_CHARGING_TIME = 0;
                xQueueReceive(_C101_QUEUE, &_c101msg, 0);
                xQueueReceive(_C102_QUEUE, &_c102msg, 0);
                xQueueReceive(_C10B_QUEUE, &_c10bmsg, 0);
                if ((_c101msg._101_SECC_PnCREADY_t == seccPnCReady_NotReady) && (_c102msg._102_SECC_CP_t == seccCpOscillator_Duty_Cycle_OFF)) {
                    if ((_c102msg.cpVoltage_msb) / 10 >= 11) {
                        instance = 0;
                        instance1 = 0;
                        _50msmsg.ID_t = _002;
                        _50msmsg.DATA[6] = _1_PLC_tx_50_t._002_EVSE_PROCESSING_DATA6_t = (0x00 | (1 << EVSE_Trigger_State));
                        xQueueSend(_50msQUEUE, &_50msmsg, 100);
                        vTaskDelay(1000);
                        _50msmsg.ID_t = _002;
                        _50msmsg.DATA[6] = _1_PLC_tx_50_t._002_EVSE_PROCESSING_DATA6_t = (0x00 | (0 << EVSE_Trigger_State));
                        xQueueSend(_50msQUEUE, &_50msmsg, 100);
                        vTaskDelay(100);
                        CURRENT_PLC1_STATE = _1_PLC_STATE_IDLE_2;
                        CP_Level_1 = 12;
                    }
                    if ((_c102msg.cpVoltage_msb) / 10 <= 9) {
                        _50msmsg.ID_t = _002;
                        _50msmsg.DATA[6] = _1_PLC_tx_50_t._002_EVSE_PROCESSING_DATA6_t = (0x00 | (1 << EVSE_Trigger_State));
                        xQueueSend(_50msQUEUE, &_50msmsg, 100);
                        vTaskDelay(1000);
                        _50msmsg.ID_t = _002;
                        _50msmsg.DATA[6] = _1_PLC_tx_50_t._002_EVSE_PROCESSING_DATA6_t = (0x00 | (0 << EVSE_Trigger_State));
                        xQueueSend(_50msQUEUE, &_50msmsg, 100);
                        vTaskDelay(100);
                        CURRENT_PLC1_STATE = _1_PLC_STATE_IDLE_2;
                        //                        leddata.GUN1 = 3;
                        //                        xQueueOverwrite(LED1_QUEUE, &leddata);
                    }
                }
                break;
            case _1_PLC_STATE_IDLE_2:
                _200msmsg.ID_t = _001;
                _200msmsg.DATA[0] = 0x00;
                xQueueSend(_200msQUEUE, &_200msmsg, 100);
                vTaskDelay(100);
                _1000msmsg.ID_t = _D002;
                _1000msmsg.DATA[0] = _1_PLC_tx_1000_t._D002_EVSE_PKIENVSELECTION_DATA0_t = EVSE_PKIENVSELECTION_Public;
                _1000msmsg.DATA[1] = _1_PLC_tx_1000_t._D002_EVSE_CERTCHAINVALID_DATA1_t = EVSE_CERTCHAINVALID_None;
                _1000msmsg.DATA[2] = _1_PLC_tx_1000_t._D002_EVSE_RKEYOPTION_DATA2_t = EVSE_RKEYOPTION_False;
                xQueueSend(_1000msQUEUE, &_1000msmsg, 100);
                vTaskDelay(100);
                _50msmsg.ID_t = _002;
                _50msmsg.DATA[1] = _1_PLC_tx_50_t._002_EVSE_CHARGING_CONTROL_DATA1_t = Charging_Control_Initialised_PPMT;
                xQueueSend(_50msQUEUE, &_50msmsg, 100);
                vTaskDelay(100);
                xQueueReceive(_C10B_QUEUE, &_c10bmsg, 0);
                if (_c10bmsg._10B_SECC_STATUS3_t == seccStatus_Initialized) {
                    CURRENT_PLC1_STATE = _1_PLC_STATE_INITIALIZED_1;
                }
                break;
            case _1_PLC_STATE_INITIALIZED_1:

                _50msmsg.ID_t = _002;
                _50msmsg.DATA[6] = _1_PLC_tx_50_t._002_EVSE_PROCESSING_DATA6_t = (0x00 | (1 << EVSE_Trigger_State));
                xQueueSend(_50msQUEUE, &_50msmsg, 100);
                vTaskDelay(1000);
                _50msmsg.ID_t = _002;
                _50msmsg.DATA[6] = _1_PLC_tx_50_t._002_EVSE_PROCESSING_DATA6_t = (0x00 | (0 << EVSE_Trigger_State));
                xQueueSend(_50msQUEUE, &_50msmsg, 100);
                vTaskDelay(100);

                if (xQueueReceive(_C102_QUEUE, &_c102msg, 0)) {
                    if ((((_c102msg.cpVoltage_msb) / 10) >= 8) && (((_c102msg.cpVoltage_msb) / 10) <= 10)) {
                        ////////HMI/////////////
                        Change_gun1_status_to(CONNECTED);
                        ////////HMI/////////////
                        //                        vTaskResume(LED_TASKHandle);
                        AC_Contactor_Relay_Clear();
                        //                        leddata.GUN1 = 3;
                        //                        xQueueOverwrite(LED1_QUEUE, &leddata);
                        CP_Level_1 = 9;
                        GUN1_CONNECTED = 1;
                        if (instance == 1) {
                            mac_id_conn_no_data.MAC_ID_CONN_NO[0] = CONNECTOR_NO_0;
                            xQueueOverwrite(ESP_S_MAC_ID_CONN_NO_QUEUE, &mac_id_conn_no_data);
                            vTaskResume(ESP_SEND_TASKHandle);
                        }
                        if (START_STOP_AR[0] == 1 && START_STOP_AR[1] == 1) {
                            CURRENT_PLC1_STATE = _1_PLC_STATE_INITIALIZED_2;
                            rfid_conn_no_data.RFID_CONN_NO[0] = CONNECTOR_NO_0;
                            xQueueOverwrite(ESP_S_RFID_CONN_NO_QUEUE, &rfid_conn_no_data);
                            instance1 = 1;
                        }
                        if (instance == 0) {
                            CURRENT_PLC1_STATE = _1_PLC_STATE_INITIALIZED_2;
                        }
                        gun_count++;
                    }
                    if ((((_c102msg.cpVoltage_msb) / 10) >= 11)) {
                        if (GUN2_CONNECTED == 0) {
                            //                            vTaskSuspend(LED_TASKHandle);
                            AC_Contactor_Relay_Set();
                            vTaskSuspend(FAN_TASKHandle);
                            FAN_ON(65535);
                            instance = 0;
                            instance1 = 0;
                            if (page_change_inst == 0) {
                                page_change_inst = 1;
                                Change_Page_to(CURRENT_PAGE);
                            }


                        }
                        GUN1_CONNECTED = 0;
                        CP_Level_1 = 12;
                        Change_gun1_status_to(AVAILABLE);
                    }

                    if (gun_count > 30) {
                        gun_count = 0;
                        if (GUN2_CONNECTED == 0) {
                            AC_Contactor_Relay_Set();
                        }
                        CURRENT_PLC1_STATE = _1_PLC_STATE_IDLE_1;
                    }
                }
                break;
            case _1_PLC_STATE_INITIALIZED_2:
                gun_count = 0;
                _200msmsg.ID_t = _001;
                _200msmsg.DATA[3] = _1_PLC_tx_200_t._001SUPPORTENERGY_TRANSFER_DATA3_t = (0x00 | (1 << SupportEnergyTransfer_DCEXTD));
                xQueueSend(_200msQUEUE, &_200msmsg, 100);
                vTaskDelay(1000);

                _50msmsg.ID_t = _002;
                _50msmsg.DATA[4] = _1_PLC_tx_50_t._002_EVSE_ISOLATION_STATUS_DATA4_t = Isolation_Status_Invalid;
                _50msmsg.DATA[6] = _1_PLC_tx_50_t._002_EVSE_PROCESSING_DATA6_t = (0x00 | (0 << EVSE_Processing_CPD) | (0 << EVSE_Processing_Cable_check) | (0 << EVSE_Trigger_Negotation));
                _50msmsg.DATA[7] = _1_PLC_tx_50_t._002_EVSE_VCP_LIMIT_DATA7_t = (0x00 | (0 << EVSE_Current_Limit) | (0 << EVSE_Voltage_Limit) | (0 << EVSE_Power_Limit));
                xQueueSend(_50msQUEUE, &_50msmsg, 100);
                vTaskDelay(1000);

                _50msmsg.ID_t = _002;
                _50msmsg.DATA[1] = _1_PLC_tx_50_t._002_EVSE_CHARGING_CONTROL_DATA1_t = Charging_Control_Start_Charging;
                xQueueSend(_50msQUEUE, &_50msmsg, 100);
                vTaskDelay(100);

                CURRENT_PLC1_STATE = _1_PLC_STATE_WAITING_FOR_PLUG_IN;

                break;
            case _1_PLC_STATE_WAITING_FOR_PLUG_IN:
                xQueueReceive(_C102_QUEUE, &_c102msg, 0);
                xQueueReceive(_C10B_QUEUE, &_c10bmsg, 0);
                if ((_c102msg._102_SECC_CP_t == seccCpOscillator_Duty_Cycle_ON) && ((((_c102msg.cpVoltage_msb) / 10) >= 8) && (((_c102msg.cpVoltage_msb) / 10) <= 10))) {
                    CURRENT_PLC1_STATE = _1_PLC_STATE_PROCESSING_SLAC;
                }
                if (_c10bmsg._10B_SECC_STATUS3_t == seccStatus_TERMINATE || _c10bmsg._10B_SECC_STATUS3_t == seccStatus_ERROR || _c10bmsg._10B_SECC_STATUS3_t == seccStatus_IDLE) {
                    CURRENT_PLC1_STATE = _1_PLC_STATE_IDLE_1;
                }
                if ((((_c102msg.cpVoltage_msb) / 10) >= 11)) {
                    if (GUN2_CONNECTED == 0) {
                        AC_Contactor_Relay_Set();
                    }
                    GUN1_CONNECTED = 0;
                    CP_Level_1 = 12;
                    CURRENT_PLC1_STATE = _1_PLC_STATE_IDLE_1;
                }
                break;
            case _1_PLC_STATE_PROCESSING_SLAC:
                page_change_inst = 0;
                xQueueReceive(_C10B_QUEUE, &_c10bmsg, 0);
                if (_c10bmsg._10B_SECC_STATUS3_t >= seccStatus_ServiceDiscovery) {
                    if (instance == 1) {
                        CURRENT_PLC1_STATE = _1_PLC_STATE_AUTHORIZATION_EIM;
                    }
                    if (instance == 0) {

                        if (xQueueReceive(_C105_QUEUE, &_c105msg, 0)) {
                            mac_id_data.MAC_ID_IS[0] = _c105msg.evccMAC_Data0;
                            mac_id_data.MAC_ID_IS[1] = _c105msg.evccMAC_Data1;
                            mac_id_data.MAC_ID_IS[2] = _c105msg.evccMAC_Data2;
                            mac_id_data.MAC_ID_IS[3] = _c105msg.evccMAC_Data3;
                            mac_id_data.MAC_ID_IS[4] = _c105msg.evccMAC_Data4;
                            mac_id_data.MAC_ID_IS[5] = _c105msg.evccMAC_Data5;
                            //                            sprintf(buffer, "MAC ID %d %d %d %d %d %d", MAC_ID[0], MAC_ID[1], MAC_ID[2], MAC_ID[3], MAC_ID[4], MAC_ID[5]);
                            //                            SERCOM5_USART_Write(buffer, sizeof (buffer));
                            //                            while (!SERCOM5_USART_TransmitComplete());
                            xQueueOverwrite(ESP_S_MAC_ID_QUEUE, &mac_id_data);
                            if (mac_id_data.MAC_ID_IS[0] > 0) {
                                instance = 1;
                                CURRENT_PLC1_STATE = _1_PLC_STATE_AUTHORIZATION_EIM;
                                mac_id_conn_no_data.MAC_ID_CONN_NO[0] = CONNECTOR_NO_1;
                                vTaskResume(ESP_SEND_TASKHandle);

                                xQueueOverwrite(ESP_S_MAC_ID_CONN_NO_QUEUE, &mac_id_conn_no_data);
                            }
                        }
                    }
                }
                if (_c10bmsg._10B_SECC_STATUS3_t == seccStatus_TERMINATE || _c10bmsg._10B_SECC_STATUS3_t == seccStatus_ERROR || _c10bmsg._10B_SECC_STATUS3_t == seccStatus_IDLE) {
                    if (instance == 1) {
                        CURRENT_PLC1_STATE = _1_PLC_STATE_IDLE_1;
                        instance = 1;
                        //                        Stop_Code = 307;
                        //                        Stop_connector_no = 1;
                        //                        Change_Page_to(GUN1_FAILING_REASON_PAGE);
                    }
                    if (instance == 0) {
                        CURRENT_PLC1_STATE = _1_PLC_STATE_IDLE_1;
                        instance = 1;
                    }
                }
                if (_c10bmsg._10B_SECC_STATUS3_t == seccStatus_Waiting_SLAC) {
                    slac_count++;
                    if (slac_count == 240) {
                        slac_count = 0;
                        CURRENT_PLC1_STATE = _1_PLC_STATE_IDLE_1;
                        Stop_Code = 307;
                        Stop_connector_no = 1;
                        Change_Page_to(GUN1_FAILING_REASON_PAGE);
                    }
                }
                break;
            case _1_PLC_STATE_AUTHORIZATION_EIM:
                slac_count = 0;
                if (instance1 == 0) {
                    if (START_STOP_AR[0] == 1 && START_STOP_AR[1] == 1) {
                        rfid_conn_no_data.RFID_CONN_NO[0] = CONNECTOR_NO_0;
                        xQueueOverwrite(ESP_S_RFID_CONN_NO_QUEUE, &rfid_conn_no_data);
                        _50msmsg.ID_t = _002;
                        _50msmsg.DATA[6] = _1_PLC_tx_50_t._002_EVSE_PROCESSING_DATA6_t = (0x00 | (1 << EVSE_Processing_Auth_EIM));
                        xQueueSend(_50msQUEUE, &_50msmsg, 100);
                        vTaskDelay(100);
                        xQueueReceive(_C10B_QUEUE, &_c10bmsg, 1000);
                        CURRENT_PLC1_STATE = _1_PLC_STATE_CHARGE_PARAMETER_DISCOVERY;
                        ////////////HMI//////////////////
                        Change_Page_to(GUN1_AUTHENTICATION_SUCCESS_PAGE);
                        ////////////HMI//////////////////
                    }
                }
                if (instance1 == 1) {
                    _50msmsg.ID_t = _002;
                    _50msmsg.DATA[6] = _1_PLC_tx_50_t._002_EVSE_PROCESSING_DATA6_t = (0x00 | (1 << EVSE_Processing_Auth_EIM));
                    xQueueSend(_50msQUEUE, &_50msmsg, 100);
                    vTaskDelay(100);
                    xQueueReceive(_C10B_QUEUE, &_c10bmsg, 1000);
                    CURRENT_PLC1_STATE = _1_PLC_STATE_CHARGE_PARAMETER_DISCOVERY;
                    ////////////HMI//////////////////
                    Change_Page_to(GUN1_AUTHENTICATION_SUCCESS_PAGE);
                    ////////////HMI//////////////////
                }
                xQueueReceive(_C10B_QUEUE, &_c10bmsg, 0);
                if (_c10bmsg._10B_SECC_STATUS3_t == seccStatus_TERMINATE || _c10bmsg._10B_SECC_STATUS3_t == seccStatus_ERROR || _c10bmsg._10B_SECC_STATUS3_t == seccStatus_IDLE) {
                    CURRENT_PLC1_STATE = _1_PLC_STATE_IDLE_1;
                    instance = 1;
                    Stop_Code = 308;
                    Stop_connector_no = 1;
                    Update_GUN1_Session_End_Reason(0x06);
                    Change_Page_to(GUN1_FAILING_REASON_PAGE);
                }

                break;
            case _1_PLC_STATE_CHARGE_PARAMETER_DISCOVERY:
                MERGER_Contactor_Set();
                rectimsg.CURRENT_VALUE[0] = 0;
                rectimsg.VOLTAGE_VALUE[0] = 200;
                rectimsg.RECTI_ON_OFF[0] = RECTIFIER_ON;
                rectimsg.PLC_ID[0] = 0x01;
                xQueueSend(RECTIFIER_QUEUE, &rectimsg, 100);
                vTaskResume(RECTIFIER_TASKHandle);
                instance1 = 1;
                if (xQueueReceive(_C107_QUEUE, &_c107msg, 0)) {
                    MAX_VOLT_LIMIT = (((_c107msg.evMaximumVoltageLimitlsb) << 8) + (_c107msg.evMaximumVoltageLimitmsb)) / 10;
                    MAX_CURR_LIMIT_PLC = (((_c107msg.evMaximumCurrentLimitlsb) << 8) + (_c107msg.evMaximumCurrentLimitmsb)) / 10;
                    MAX_CURR_LIMIT1 = ((MAX_POWER_LIMIT * 10000) / (int) MAX_VOLT_LIMIT) * 10;
                    if (MAX_CURR_LIMIT1 > (MAX_CURR_LIMIT_PLC * 10)) {
                        MAX_CURR_LIMIT1 = (MAX_CURR_LIMIT_PLC * 10);
                    }
                    _50msmsg.ID_t = _002;
                    _50msmsg.DATA[6] = _1_PLC_tx_50_t._002_EVSE_PROCESSING_DATA6_t = (0x00 | (0 << EVSE_Processing_CPD));
                    xQueueSend(_50msQUEUE, &_50msmsg, 100);
                    vTaskDelay(100);
                    _200msmsg.ID_t = _003;
                    _200msmsg.DATA[0] = _1_PLC_tx_200_t._003_EVSE_MAX_CURRENT_LIMIT_MSB_DATA0 =
                            (uint16_t) MAX_CURR_LIMIT1 & 0x00FF;
                    _200msmsg.DATA[1] = _1_PLC_tx_200_t._003_EVSE_MAX_CURRENT_LIMIT_LSB_DATA1 =
                            ((uint16_t) MAX_CURR_LIMIT1 >> 8) & 0x00FF;
                    _200msmsg.DATA[2] = _1_PLC_tx_200_t._003_EVSE_MAX_POWER_LIMIT_MSB_DATA2 =
                            ((MAX_POWER_LIMIT * 10000) / 10) - ((((MAX_POWER_LIMIT * 10000) / 10) >> 8) << 8);
                    _200msmsg.DATA[3] = _1_PLC_tx_200_t._003_EVSE_MAX_POWER_LIMIT_LSB_DATA3 =
                            ((MAX_POWER_LIMIT * 10000) / 10) >> 8;
                    _200msmsg.DATA[4] = _1_PLC_tx_200_t._003_EVSE_MAX_VOLTAGE_LIMIT_MSB_DATA4 =
                            EVSE_MAX_VOLTAGE_DATA0;
                    _200msmsg.DATA[5] = _1_PLC_tx_200_t._003_EVSE_MAX_VOLTAGE_LIMIT_LSB_DATA5 =
                            EVSE_MAX_VOLTAGE_DATA1;
                    _200msmsg.DATA[6] = _1_PLC_tx_200_t._003_EVSE_PEAK_CURRENT_RIPPLE_MSB_DATA6 =
                            EVSE_PEAK_CURRENT_RIPPLE_DATA0;
                    _200msmsg.DATA[7] = _1_PLC_tx_200_t._003_EVSE_PEAK_CURRENT_RIPPLE_LSB_DATA7 =
                            EVSE_PEAK_CURRENT_RIPPLE_DATA1;
                    xQueueSend(_200msQUEUE, &_200msmsg, 100);
                    vTaskDelay(500);

                    _200msmsg.DATA[0] = _1_PLC_tx_200_t._004_EVSE_MIN_CURRENT_LIMIT_MSB_DATA0 =
                            EVSE_MIN_CURRENT_DATA0;
                    _200msmsg.DATA[1] = _1_PLC_tx_200_t._004_EVSE_MIN_CURRENT_LIMIT_LSB_DATA1 =
                            EVSE_MIN_CURRENT_DATA1;

                    _200msmsg.DATA[2] = _1_PLC_tx_200_t._004_EVSE_MIN_VOLTAGE_LIMIT_MSB_DATA2 =
                            EVSE_MIN_VOLTAGE_DATA0;
                    _200msmsg.DATA[3] = _1_PLC_tx_200_t._004_EVSE_MIN_VOLTAGE_LIMIT_LSB_DATA3 =
                            EVSE_MIN_VOLTAGE_DATA1;

                    _200msmsg.DATA[4] =
                            _1_PLC_tx_200_t._004_EVSE_CURRENT_REGULATION_TOLERANCE_MSB_DATA4 =
                            EVSE_PEAK_CURRENT_TOLERANCE_DATA0;
                    _200msmsg.DATA[5] =
                            _1_PLC_tx_200_t._004_EVSE_CURRENT_REGULATION_TOLERANCE_LSB_DATA5 =
                            EVSE_PEAK_CURRENT_TOLERANCE_DATA1;

                    _200msmsg.DATA[6] = _1_PLC_tx_200_t._004_EVSE_ENERGY_TO_DELIVERED_MSB_DATA6 =
                            EVSE_ENERGY_TO_DELIVERED_DATA0;
                    _200msmsg.DATA[7] = _1_PLC_tx_200_t._004_EVSE_ENERGY_TO_DELIVERED_LSB_DATA7 =
                            EVSE_ENERGY_TO_DELIVERED_DATA1;

                    _200msmsg.ID_t = _004;
                    xQueueSend(_200msQUEUE, &_200msmsg, 100);
                    vTaskDelay(500);

                    _50msmsg.DATA[6] = _1_PLC_tx_50_t._002_EVSE_PROCESSING_DATA6_t = (0x00 | (1 << EVSE_Processing_CPD));
                    _50msmsg.ID_t = _002;
                    xQueueSend(_50msQUEUE, &_50msmsg, 100);
                    vTaskDelay(500);
                    ////////////HMI//////////////////
                    Change_Page_to(GUN1_PREPARING_TO_CHARGE_PAGE);
                    ////////////HMI//////////////////
                    xQueueReceive(_C10B_QUEUE, &_c10bmsg, 0);
                    if ((_c10bmsg._10B_SECC_STATUS3_t > seccStatus_ChargeParameterDiscovery) && (_c10bmsg._10B_SECC_STATUS3_t < seccStatus_PreCharge)) {
                        CURRENT_PLC1_STATE = _1_PLC_STATE_CABLE_CHECK;
                        vTaskDelay(1000);
                        DC1_Contactor_Clear();
                    }
                    if (_c10bmsg._10B_SECC_STATUS3_t == seccStatus_TERMINATE || _c10bmsg._10B_SECC_STATUS3_t == seccStatus_ERROR || _c10bmsg._10B_SECC_STATUS3_t == seccStatus_IDLE) {
                        CURRENT_PLC1_STATE = _1_PLC_STATE_IDLE_1;
                        Stop_Code = 309;
                        Stop_connector_no = 1;
                        Update_GUN1_Session_End_Reason(0x08);
                        Change_Page_to(GUN1_FAILING_REASON_PAGE);
                    }
                }
                memset(mac_id_data.MAC_ID_IS, 0, sizeof (mac_id_data.MAC_ID_IS));
                mac_id_conn_no_data.MAC_ID_CONN_NO[0] = CONNECTOR_NO_0;
                xQueueOverwrite(ESP_S_MAC_ID_CONN_NO_QUEUE, &mac_id_conn_no_data);
                xQueueOverwrite(ESP_S_MAC_ID_QUEUE, &mac_id_data);
                memset(START_STOP_AR, 0, sizeof (START_STOP_AR));

                break;
            case _1_PLC_STATE_CABLE_CHECK:


                xQueueReceive(_C102_QUEUE, &_c102msg, 0);
                if ((_c102msg.cpVoltage_msb) / 10 >= 5) {
                    if (!IMD1_RESPONSE_Get()) {
                        _50msmsg.DATA[4] = _1_PLC_tx_50_t._002_EVSE_ISOLATION_STATUS_DATA4_t =
                                Isolation_Status_Valid;
                        _50msmsg.DATA[6] = _1_PLC_tx_50_t._002_EVSE_PROCESSING_DATA6_t = (0x00 | (1 << EVSE_Processing_Cable_check) | (1 << EVSE_Isolation_Mointor));
                        _50msmsg.ID_t = _002;
                        xQueueSend(_50msQUEUE, &_50msmsg, 100);
                        vTaskDelay(100);
                        CURRENT_PLC1_STATE = _1_PLC_STATE_PRE_CHARGE;
                    } else {
                        CURRENT_PLC1_STATE = _1_PLC_STATE_IDLE_1;
                        Stop_Code = 309;
                        Stop_connector_no = 1;
                        Update_GUN1_Session_End_Reason(0x07);
                        Change_Page_to(GUN1_FAILING_REASON_PAGE);
                    }
                }
                vTaskDelay(1000);
                break;
            case _1_PLC_STATE_PRE_CHARGE:

                //                if (xQueueReceive(_C109_QUEUE, &_c109msg, 0)) {
                xQueueReceive(_C109_QUEUE, &_c109msg, 0);
                voltage_to_give = ((((_c109msg.targetVoltagelsb) << 8) + _c109msg.targetVoltagemsb)) / 10;
                current_to_give = (((_c109msg.targetCurrentlsb) << 8) + _c109msg.targetCurrentmsb) / 10;
                rectimsg.CURRENT_VALUE[0] = 2;
                rectimsg.VOLTAGE_VALUE[0] = voltage_to_give;
                rectimsg.RECTI_ON_OFF[0] = RECTIFIER_ON;
                rectimsg.PLC_ID[0] = 0x01;
                xQueueSend(RECTIFIER_QUEUE, &rectimsg, 100);
                vTaskResume(RECTIFIER_TASKHandle);
                //                vTaskDelay(2000);
                _50msmsg.DATA[0] = _1_PLC_tx_50_t._005_EVSE_PRESENT_VOLTAGE_MSB_DATA0 =
                        _c109msg.targetVoltagemsb;
                _50msmsg.DATA[1] = _1_PLC_tx_50_t._005_EVSE_PRESENT_VOLTAGE_LSB_DATA1 =
                        _c109msg.targetVoltagelsb;
                //                _50msmsg.DATA[2] = _1_PLC_tx_50_t._005_EVSE_PRESENT_CURRENT_MSB_DATA2 =
                //                        _c109msg.targetCurrentmsb;
                //                _50msmsg.DATA[3] = _1_PLC_tx_50_t._005_EVSE_PRESENT_CURRENT_LSB_DATA3 =
                //                        _c109msg.targetCurrentlsb;
                _50msmsg.ID_t = _005;
                xQueueSend(_50msQUEUE, &_50msmsg, 100);
                vTaskDelay(10);

                /////////HMI/////////////////////
                Change_Page_to(GUN1_PARAM_PAGE);

                //                }
                if (xQueueReceive(_C10B_QUEUE, &_c10bmsg, 0)) {
                    if (_c10bmsg._10B_SECC_STATUS3_t == seccStatus_CurrentDemand) {
                        xTimerStart(Gun1_Charging_timer, 60000);
                        xTimerStart(all_rec_timer, 60000);
                        xTimerStart(rec1_timer, 60000);
                        xTimerStart(rec2_timer, 60000);
                        xTimerStart(rec3_timer, 60000);
                        xTimerStart(rec4_timer, 60000);
                        CURRENT_PLC1_STATE = _1_PLC_STATE_CURRENT_DEMAND_1;
                        Update_GUN1_Charging_Start_date(day);
                        vTaskDelay(100);
                        Update_GUN1_Charging_Start_month(month);
                        vTaskDelay(100);
                        Update_GUN1_Charging_Start_year(year);
                        vTaskDelay(100);
                        Update_GUN1_Charging_Start_mins(minute);
                        vTaskDelay(100);
                        Update_GUN1_Charging_Start_hour(hour);
                        vTaskDelay(100);
                        Update_GUN1_Charging_Start_sec(sec);
                        vTaskDelay(100);
                        STARTING_UNIT = IMPORT_ENERGY1;
                        //                        vTaskResume(LED_TASKHandle);
                        flashmsg.START_DATE = (year << 16) | (month << 8) | day;
                        flashmsg.START_TIME = (hour << 16) | (minute << 8) | sec;
                    }
                    if (_c10bmsg._10B_SECC_STATUS3_t == seccStatus_TERMINATE || _c10bmsg._10B_SECC_STATUS3_t == seccStatus_ERROR || _c10bmsg._10B_SECC_STATUS3_t == seccStatus_IDLE) {
                        CURRENT_PLC1_STATE = _1_PLC_STATE_TERMINATED;
                        Stop_Code = 310;
                        Stop_connector_no = 1;
                        Update_GUN1_Session_End_Reason(0x08);
                        Change_Page_to(GUN1_FAILING_REASON_PAGE);
                    }
                }
                break;
            case _1_PLC_STATE_CURRENT_DEMAND_1:
                if (xQueueReceive(GUN1_CHARGING_TIME_QUEUE, &value, 0)) {
                    GUN1_CHARGING_TIME = GUN1_CHARGING_TIME + value.value[0];
                }
                vTaskResume(FAN_TASKHandle);
                //                leddata.GUN1 = 1;
                //                xQueueOverwrite(LED1_QUEUE, &leddata);
                Change_gun1_status_to(CHARGING);
                Update_GUN1_Duration(GUN1_CHARGING_TIME);
                if (initial_SOC1 == 7) {
                    Update_GUN1_Initial_SOC(FINAL_INITIAL_SOC);
                }
                if (xQueueReceive(_C109_QUEUE, &_c109msg, 0)) {
                    current_to_give =
                            ((uint16_t) (((((_c109msg.targetCurrentlsb) << 8) + _c109msg.targetCurrentmsb)) / 10));
                    voltage_to_give =
                            ((uint16_t) (((((_c109msg.targetVoltagelsb) << 8) + _c109msg.targetVoltagemsb)) / 10));
                    //                    if (current_to_give > 250) {
                    //                        current_to_give = 250;
                    //                    }
                    power = (current_to_give * voltage_to_give);

                    if (SINGLE_GUN1_POWER == 0) {
                        POWER_VALUE = POWER_VALUE_X;
                        if (power < POWER_VALUE) {
                            if (GUN2_CONNECTED == 0) {
                                rectimsg.VOLTAGE_VALUE[0] = voltage_to_give + Difference_in_VOLTAGE1;
                                act_current_to_give = (POWER_VALUE) / act_volt_1;
                                if (act_current_to_give <= current_to_give) {
                                    rectimsg.CURRENT_VALUE[0] = act_current_to_give / NO_OF_RECTIFIER;
                                } else if (act_current_to_give > current_to_give) {

                                    rectimsg.CURRENT_VALUE[0] = current_to_give / NO_OF_RECTIFIER;
                                }
                                rectimsg.PLC_ID[0] = 0x03;
                                rectimsg.RECTI_ON_OFF[0] = RECTIFIER_ON;
                                xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
                            }
                            if (GUN2_CONNECTED == 1 && CURRENT_PLC2_STATE >= _2_PLC_STATE_CHARGE_PARAMETER_DISCOVERY) {
                                MERGER_Contactor_Set();
                                rectimsg.VOLTAGE_VALUE[0] = voltage_to_give + Difference_in_VOLTAGE1;
                                act_current_to_give = (POWER_VALUE / 2) / act_volt_1;
                                if (act_current_to_give <= current_to_give) {
                                    rectimsg.CURRENT_VALUE[0] = act_current_to_give / (NO_OF_RECTIFIER >> 1);
                                } else if (act_current_to_give > current_to_give) {

                                    rectimsg.CURRENT_VALUE[0] = current_to_give / (NO_OF_RECTIFIER >> 1);
                                }
                                rectimsg.PLC_ID[0] = 0x01;
                                rectimsg.RECTI_ON_OFF[0] = RECTIFIER_ON;
                                xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
                            } else if (GUN2_CONNECTED == 1 && CURRENT_PLC2_STATE < _2_PLC_STATE_CHARGE_PARAMETER_DISCOVERY) {
                                rectimsg.VOLTAGE_VALUE[0] = voltage_to_give + Difference_in_VOLTAGE1;
                                act_current_to_give = (POWER_VALUE) / act_volt_1;
                                if (act_current_to_give <= current_to_give) {
                                    rectimsg.CURRENT_VALUE[0] = act_current_to_give / NO_OF_RECTIFIER;
                                } else if (act_current_to_give > current_to_give) {

                                    rectimsg.CURRENT_VALUE[0] = current_to_give / NO_OF_RECTIFIER;
                                }
                                rectimsg.PLC_ID[0] = 0x03;
                                rectimsg.RECTI_ON_OFF[0] = RECTIFIER_ON;
                                xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
                            }
                        }
                        if (power > POWER_VALUE) {

                            if (GUN2_CONNECTED == 0) {
                                rectimsg.VOLTAGE_VALUE[0] = voltage_to_give + Difference_in_VOLTAGE1;
                                act_current_to_give = (POWER_VALUE) / act_volt_1;
                                if (act_current_to_give <= current_to_give) {
                                    rectimsg.CURRENT_VALUE[0] = act_current_to_give / NO_OF_RECTIFIER;
                                } else if (act_current_to_give > current_to_give) {

                                    rectimsg.CURRENT_VALUE[0] = current_to_give / NO_OF_RECTIFIER;
                                }
                                rectimsg.PLC_ID[0] = 0x03;
                                rectimsg.RECTI_ON_OFF[0] = RECTIFIER_ON;
                                xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
                            }
                            if (GUN2_CONNECTED == 1 && CURRENT_PLC2_STATE >= _2_PLC_STATE_CHARGE_PARAMETER_DISCOVERY) {
                                MERGER_Contactor_Set();
                                rectimsg.VOLTAGE_VALUE[0] = voltage_to_give + Difference_in_VOLTAGE1;
                                act_current_to_give = (POWER_VALUE / 2) / act_volt_1;
                                if (act_current_to_give <= current_to_give) {
                                    rectimsg.CURRENT_VALUE[0] = act_current_to_give / (NO_OF_RECTIFIER >> 1);
                                } else if (act_current_to_give > current_to_give) {

                                    rectimsg.CURRENT_VALUE[0] = current_to_give / (NO_OF_RECTIFIER >> 1);
                                }
                                rectimsg.PLC_ID[0] = 0x01;
                                rectimsg.RECTI_ON_OFF[0] = RECTIFIER_ON;
                                xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
                            } else if (GUN2_CONNECTED == 1 && CURRENT_PLC2_STATE < _2_PLC_STATE_CHARGE_PARAMETER_DISCOVERY) {
                                rectimsg.VOLTAGE_VALUE[0] = voltage_to_give + Difference_in_VOLTAGE1;
                                act_current_to_give = (POWER_VALUE) / act_volt_1;
                                if (act_current_to_give <= current_to_give) {
                                    rectimsg.CURRENT_VALUE[0] = act_current_to_give / NO_OF_RECTIFIER;
                                } else if (act_current_to_give > current_to_give) {

                                    rectimsg.CURRENT_VALUE[0] = current_to_give / NO_OF_RECTIFIER;
                                }
                                rectimsg.PLC_ID[0] = 0x03;
                                rectimsg.RECTI_ON_OFF[0] = RECTIFIER_ON;
                                xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
                            }
                        }
                    }
                    if (SINGLE_GUN1_POWER == 1) {
                        if (GUN2_CONNECTED == 0) {
                            rectimsg.VOLTAGE_VALUE[0] = voltage_to_give + Difference_in_VOLTAGE1;
                            act_current_to_give = (POWER_VALUE_X1) / act_volt_1;
                            if (act_current_to_give <= current_to_give) {
                                rectimsg.CURRENT_VALUE[0] = act_current_to_give / NO_OF_RECTIFIER;
                            } else if (act_current_to_give > current_to_give) {

                                rectimsg.CURRENT_VALUE[0] = current_to_give / NO_OF_RECTIFIER;
                            }
                            rectimsg.PLC_ID[0] = 0x03;
                            rectimsg.RECTI_ON_OFF[0] = RECTIFIER_ON;
                            xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
                        }
                        if (GUN2_CONNECTED == 1 && CURRENT_PLC2_STATE >= _2_PLC_STATE_CHARGE_PARAMETER_DISCOVERY) {
                            MERGER_Contactor_Set();
                            if (POWER_VALUE_X1 > ((MAX_POWER_LIMIT * 10000) / 2)) {
                                POWER_VALUE_X1 = ((MAX_POWER_LIMIT * 10000) / 2);
                            }
                            rectimsg.VOLTAGE_VALUE[0] = voltage_to_give + Difference_in_VOLTAGE1;
                            act_current_to_give = (POWER_VALUE_X1) / act_volt_1;
                            if (act_current_to_give <= current_to_give) {
                                rectimsg.CURRENT_VALUE[0] = act_current_to_give / (NO_OF_RECTIFIER >> 1);
                            } else if (act_current_to_give > current_to_give) {

                                rectimsg.CURRENT_VALUE[0] = current_to_give / (NO_OF_RECTIFIER >> 1);
                            }
                            rectimsg.PLC_ID[0] = 0x01;
                            rectimsg.RECTI_ON_OFF[0] = RECTIFIER_ON;
                            xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
                        } else if (GUN2_CONNECTED == 1 && CURRENT_PLC2_STATE < _2_PLC_STATE_CHARGE_PARAMETER_DISCOVERY) {
                            rectimsg.VOLTAGE_VALUE[0] = voltage_to_give + Difference_in_VOLTAGE1;
                            act_current_to_give = (POWER_VALUE_X1) / act_volt_1;
                            if (act_current_to_give <= current_to_give) {
                                rectimsg.CURRENT_VALUE[0] = act_current_to_give / NO_OF_RECTIFIER;
                            } else if (act_current_to_give > current_to_give) {

                                rectimsg.CURRENT_VALUE[0] = current_to_give / NO_OF_RECTIFIER;
                            }
                            rectimsg.PLC_ID[0] = 0x03;
                            rectimsg.RECTI_ON_OFF[0] = RECTIFIER_ON;
                            xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
                        }
                    }
                    Demand_Voltage1_ARRAY[j_count] = act_volt_1;
                    Demand_Current1_ARRAY[j_count] = ((uint16_t) (((((_c109msg.targetCurrentlsb) << 8) + _c109msg.targetCurrentmsb)) / 10));
                    j_count = j_count + 1;
                    //                                    vTaskDelay(100);
                    _50msmsg.DATA[0] = _1_PLC_tx_50_t._005_EVSE_PRESENT_VOLTAGE_MSB_DATA0 =
                            _c109msg.targetVoltagemsb;
                    _50msmsg.DATA[1] = _1_PLC_tx_50_t._005_EVSE_PRESENT_VOLTAGE_LSB_DATA1 =
                            _c109msg.targetVoltagelsb;
                    _50msmsg.DATA[2] = _1_PLC_tx_50_t._005_EVSE_PRESENT_CURRENT_MSB_DATA2 =
                            _c109msg.targetCurrentmsb;
                    _50msmsg.DATA[3] = _1_PLC_tx_50_t._005_EVSE_PRESENT_CURRENT_LSB_DATA3 =
                            _c109msg.targetCurrentlsb;
                    _50msmsg.ID_t = _005;
                    xQueueSend(_50msQUEUE, &_50msmsg, 100);
                    vTaskDelay(50);
                }

                ///////////HMI////////////////
                if (xQueueReceive(_C108_QUEUE, &_c108msg, 0)) {

                    SOC_1_ARRAY[i_count] = _c108msg.evSOC;
                    CP_Level_1 = 6;
                    i_count = i_count + 1;
                    if (initial_SOC1 < 5) {
                        Update_GUN1_Initial_SOC(_c108msg.evSOC);
                        initial_SOC1 = initial_SOC1 + 1;
                        FINAL_INITIAL_SOC = (_c108msg.evSOC);
                    }
                    if (initial_SOC1 == 5) {
                        SOC1_INITIAL = _c108msg.evSOC;
                        initial_SOC1 = 7;
                    }
                }
                if (j_count == 5) {
                    j_count = 0;
                    for (uint8_t i = 0; i < 5; i++) {
                        if (Demand_Current1_ARRAY[0] <= Demand_Current1_ARRAY[i]) {
                            Demand_Current1_ARRAY[0] = Demand_Current1_ARRAY[i];
                            Demand_Current1 = Demand_Current1_ARRAY[0];
                        }
                        if (Demand_Voltage1_ARRAY[0] <= Demand_Voltage1_ARRAY[i]) {
                            Demand_Voltage1_ARRAY[0] = Demand_Voltage1_ARRAY[i];
                            Demand_Voltage1 = Demand_Voltage1_ARRAY[0];
                        }
                    }
                    Update_GUN1_Demand_Current(Demand_Current1_ARRAY[0]);
                    Update_GUN1_Demand_Voltage(Demand_Voltage1_ARRAY[0]);
                }
                if (i_count == 5) {
                    i_count = 0;
                    for (uint8_t i = 0; i < 5; i++) {
                        if (SOC_1_ARRAY[0] <= SOC_1_ARRAY[i]) {
                            SOC_1_ARRAY[0] = SOC_1_ARRAY[i];
                            SOC_1 = SOC_1_ARRAY[0];
                        }
                    }
                    Update_GUN1_Battery_SOC(SOC_1_ARRAY[0]);
                }

                if ((GUN1_CONNECTED == 1) && (GUN2_CONNECTED == 0)) {
                    rfid_conn_no_data.RFID_CONN_NO[0] = CONNECTOR_NO_0;
                    xQueueOverwrite(ESP_S_RFID_CONN_NO_QUEUE, &rfid_conn_no_data);
                }
                if ((GUN1_CONNECTED == 1) && (GUN2_CONNECTED == 1) && (CURRENT_PLC2_STATE >= _2_PLC_STATE_PRE_CHARGE)) {
                    rfid_conn_no_data.RFID_CONN_NO[0] = CONNECTOR_NO_0;
                    xQueueOverwrite(ESP_S_RFID_CONN_NO_QUEUE, &rfid_conn_no_data);
                }
                if ((_c10bmsg._10B_SECC_STATUS3_t == seccStatus_SessionStop) || (_c10bmsg._10B_SECC_STATUS3_t == seccStatus_TERMINATE) || (_c10bmsg._10B_SECC_STATUS3_t == seccStatus_ERROR)) {
                    CURRENT_PLC1_STATE = _1_PLC_STATE_TERMINATED;
                    CP_Level_1 = 9;
                    Stop_Code = 202;
                    Stop_connector_no = 1;
                    Update_GUN1_Session_End_Reason(0x0A);
                    STOPING_UNIT = IMPORT_ENERGY1;
                }
                if (_c108msg.Charging_Complete_t == CHARGING_COMPLETE) {
                    CURRENT_PLC1_STATE = _1_PLC_STATE_TERMINATED;
                    CP_Level_1 = 9;
                    Stop_Code = 201;
                    Stop_connector_no = 1;
                    Update_GUN1_Session_End_Reason(0x09);
                    STOPING_UNIT = IMPORT_ENERGY1;
                }
                if (START_STOP_AR[0] == 1 && START_STOP_AR[2] == 1) {
                    CURRENT_PLC1_STATE = _1_PLC_STATE_TERMINATED;
                    CP_Level_1 = 9;
                    memset(START_STOP_AR, 0, 3);
                    STOPING_UNIT = IMPORT_ENERGY1;
                }
                break;
            case _1_PLC_STATE_TERMINATED:
                if (GUN1_CONNECTED == 1 && GUN2_CONNECTED == 0) {
                    rectimsg.RECTI_ON_OFF[0] = RECTIFIER_OFF;
                    rectimsg.PLC_ID[0] = 0x03;
                    xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
                    vTaskDelay(3000);
                }
                if (GUN1_CONNECTED == 1 && GUN2_CONNECTED == 1) {
                    rectimsg.RECTI_ON_OFF[0] = RECTIFIER_OFF;
                    rectimsg.PLC_ID[0] = 0x01;
                    xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
                    vTaskDelay(3000);
                }

                _50msmsg.DATA[1] = _1_PLC_tx_50_t._002_EVSE_CHARGING_CONTROL_DATA1_t =
                        Charging_Control_Normal_Stop;
                _50msmsg.ID_t = _002;
                xQueueSend(_50msQUEUE, &_50msmsg, 100);
                vTaskDelay(50);
                _50msmsg.DATA[0] = _1_PLC_tx_50_t._005_EVSE_PRESENT_VOLTAGE_MSB_DATA0 = 0;

                _50msmsg.DATA[1] = _1_PLC_tx_50_t._005_EVSE_PRESENT_VOLTAGE_LSB_DATA1 = 0;
                _50msmsg.ID_t = _005;
                xQueueSend(_50msQUEUE, &_50msmsg, 100);
                vTaskDelay(50);
                DC1_Contactor_Set();
                STOPING_UNIT = IMPORT_ENERGY1;
                //                leddata.GUN1 = 0;
                //                xQueueOverwrite(LED1_QUEUE, &leddata);
                GUN1_CONNECTED = 0;

                rectimsg.RECTI_ON_OFF[0] = RECTIFIER_OFF;
                rectimsg.PLC_ID[0] = 0x01;
                xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
                vTaskDelay(3000);
                _50msmsg.DATA[1] = _1_PLC_tx_50_t._002_EVSE_CHARGING_CONTROL_DATA1_t =
                        Charging_Control_Normal_Stop;
                _50msmsg.ID_t = _002;
                xQueueSend(_50msQUEUE, &_50msmsg, 100);
                vTaskDelay(50);
                _50msmsg.DATA[0] = _1_PLC_tx_50_t._005_EVSE_PRESENT_VOLTAGE_MSB_DATA0 = 0;

                _50msmsg.DATA[1] = _1_PLC_tx_50_t._005_EVSE_PRESENT_VOLTAGE_LSB_DATA1 = 0;
                _50msmsg.ID_t = _005;
                xQueueSend(_50msQUEUE, &_50msmsg, 100);
                vTaskDelay(50);
                DC1_Contactor_Set();
                //                if ((GUN2_CONNECTED == 0) && (GUN1_CONNECTED == 0)) {
                //                    vTaskSuspend(LED_TASKHandle);
                //                }
                xTimerStop(Gun1_Charging_timer, 10);
                /////////HMI/////////////////////
                Update_GUN1_Charging_Stop_date(day);
                Update_GUN1_Charging_Stop_month(month);
                Update_GUN1_Charging_Stop_year(year);
                Update_GUN1_Charging_Stop_mins(minute);
                Update_GUN1_Charging_Stop_hour(hour);
                Update_GUN1_Charging_Stop_sec(sec);
                Update_GUN1_Booking_ID(BOOKING_ID1);
                DIFF_UNIT = (((uint32_t) STOPING_UNIT) - ((uint32_t) STARTING_UNIT));
                if (DIFF_UNIT < 0) {
                    DIFF_UNIT = 0;
                }
                Update_GUN1_Uint_Consumed(DIFF_UNIT);
                if (STOP_BY == BY_RFID) {
                    Update_GUN1_Session_End_Reason(BY_RFID);
                }
                if (STOP_BY == BY_REMOTE) {
                    Update_GUN1_Session_End_Reason(BY_REMOTE);
                }
                if (STOP_BY == BY_DE_AUTH) {
                    Update_GUN1_Session_End_Reason(BY_DE_AUTH);
                }
                CURRENT_PAGE = GUN1_SUMMARY_PAGE;
                Change_gun1_status_to(CHARGING_COMPLETED);
                /////////HMI/////////////////////
                flashmsg.BOOKING_ID = BOOKING_ID1;
                flashmsg.STOP_DATE = (year << 16) | (month << 8) | day;
                flashmsg.STOP_TIME = (hour << 16) | (minute << 8) | sec;
                flashmsg.START_SOC_AND_END_SOC = (FINAL_INITIAL_SOC << 16) | SOC_1;
                flashmsg.UNIT_CONSUMED_AND_CONN_ID = (0x01 << 16) | (uint32_t) DIFF_UNIT;
                flashmsg.SESSION_STOP_REASON_AND_DURATION = (STOP_BY << 16) | GUN1_CHARGING_TIME;
                flashmsg.WHAT_TYPE_OF_DATA = CHARGING_DATA;
                xQueueSend(FLASH_WRITE_QUEUE, &flashmsg, 100);
                vTaskResume(FLASH_WRITE_TASKHandle);

                count = 1;
                GUN1_CHARGING_TIME = 0;
                GUN1_200_clear = GUN1_500_clear = GUN1_50_clear = GUN1_1000_clear = 1;

                break;
        }
        esp_s_gun1_p.CP_Level_1 = CP_Level_1;
        esp_s_gun1_p.Demand_Current1 = Demand_Current1;
        esp_s_gun1_p.Demand_Volatge1 = Demand_Voltage1;
        esp_s_gun1_p.Initial_SOC1 = SOC1_INITIAL;
        esp_s_gun1_p.SOC_1 = SOC_1;
        xQueueOverwrite(ESP_S_GUN1_P_QUEUE, &esp_s_gun1_p);
        cplevel1.CP_LEVEL1[0] = CP_Level_1;
        xQueueOverwrite(CP_LEVEL1_QUEUE, &cplevel1);
        if (count == 1) {

            count = 0;
            CURRENT_PLC1_STATE = _1_PLC_STATE_IDLE_1;
            vTaskResume(GUN1_PARAM_TASKHandle);
            vTaskSuspend(_1_PLC_MANAGE_TASKHandle);
        }

        vTaskDelay(500);
    }
}

void Start_2_PLC_MANAGE_TASK(void *argument) {
    _C501_Q _c501msg = {0};
    _C502_Q _c502msg = {0};
    _C50B_Q _c50bmsg = {0};
    _C507_Q _c507msg = {0};
    _C509_Q _c509msg = {0};
    _C508_Q _c508msg = {0};
    _C505_Q _c505msg = {0};
    _50MS_Q _50msmsg = {0};
    _200MS_Q _200msmsg = {0};
    _1000MS_Q _1000msmsg = {0};
    _2_PLC_tx_50 _2_PLC_tx_50_t = {0};
    _2_PLC_tx_1000 _2_PLC_tx_1000_t = {0};
    _2_PLC_tx_200 _2_PLC_tx_200_t = {0};
    RECTIFIER_Q rectimsg;
    FLASH_WRITE_Q flashmsg;
    //    LED2_Q leddata;
    ESP_Q_DATA espmsg;
    memset(espmsg.ESP_ARRAY, 0, sizeof (espmsg.ESP_ARRAY));
    RELAY_Q relaymsg;
    static float MAX_VOLT_LIMIT = 0;
    static float MAX_CURR_LIMIT_PLC1 = 0;
    static float voltage_to_give = 0;
    static float current_to_give = 0;
    memset(relaymsg.RELAY_DATA, 0, sizeof (relaymsg.RELAY_DATA));
    static int count = 0;
    static int gun_count = 0;
    static int instance = 0;
    static int instance1 = 0;
    static uint8_t initial_SOC2 = 0;
    static float STARTING_UNIT = 0;
    static float STOPING_UNIT = 0;
    static float DIFF_UNIT = 0;
    static uint8_t CP_Level_2 = 0;
    static uint8_t SOC_2 = 0;
    static uint8_t SOC_2_ARRAY[5] = {0};
    static uint8_t i_count = 0;
    static uint16_t Demand_Voltage2 = 0;
    static float Demand_Voltage2_ARRAY[5] = {0};
    static uint8_t j_count = 0;
    static uint16_t Demand_Current2 = 0;
    static float Demand_Current2_ARRAY[5] = {0};
    static float act_current_to_give = 0;
    static uint16_t GUN2_CHARGING_TIME = 0;
    static uint8_t SOC2_INITIAL = 0;
    ESP_S_GUN2_P_Q esp_s_gun2_p;
    static uint8_t page_change_inst = 0;
    static float power = 0;
    static uint8_t FINAL_INITIAL_SOC = 0;
    CP_LEVEL2_Q cplevel2;
    static float Difference_in_VOLTAGE2 = 0;
    ESP_S_RFID_CONN_NO_Q rfid_conn_no_data;
    ESP_S_MAC_ID_CONN_NO_Q mac_id_conn_no_data;
    ESP_S_MAC_ID_Q mac_id_data;
    GUN2_CHARGING_TIME_Q value;
    static uint8_t slac_count = 0;
    char buffffffffff[30] = {0};
    for (;;) {

        if (xQueueReceive(GUN2_CHARGING_TIME_QUEUE, &value, 0)) {
            GUN2_CHARGING_TIME = GUN2_CHARGING_TIME + value.value[0];
        }
        switch (CURRENT_PLC2_STATE) {
            case _2_PLC_STATE_IDLE_1:
                vTaskResume(LED_TASKHandle);
                Demand_Current2 = 0;
                Demand_Voltage2 = 0;
                initial_SOC2 = 0;
                GUN2_CHARGING_TIME = 0;
                xQueueReceive(_C501_QUEUE, &_c501msg, 0);
                xQueueReceive(_C502_QUEUE, &_c502msg, 0);
                xQueueReceive(_C50B_QUEUE, &_c50bmsg, 0);
                if ((_c501msg._501_SECC_PnCREADY_t == seccPnCReady_NotReady) && (_c502msg._502_SECC_CP_t == seccCpOscillator_Duty_Cycle_OFF)) {
                    if ((_c502msg.cpVoltage_msb) / 10 >= 11) {
                        instance = 0;
                        instance1 = 0;
                        _50msmsg.ID_t = _402;
                        _50msmsg.DATA[6] = _2_PLC_tx_50_t._402_EVSE_PROCESSING_DATA6_t = (0x00 | (1 << EVSE_Trigger_State));
                        xQueueSend(_50msQUEUE, &_50msmsg, 100);
                        vTaskDelay(1000);
                        _50msmsg.ID_t = _402;
                        _50msmsg.DATA[6] = _2_PLC_tx_50_t._402_EVSE_PROCESSING_DATA6_t = (0x00 | (0 << EVSE_Trigger_State));
                        xQueueSend(_50msQUEUE, &_50msmsg, 100);
                        vTaskDelay(100);
                        CURRENT_PLC2_STATE = _2_PLC_STATE_IDLE_2;
                        CP_Level_2 = 12;
                    }
                    if ((_c502msg.cpVoltage_msb) / 10 <= 9) {
                        _50msmsg.ID_t = _402;
                        _50msmsg.DATA[6] = _2_PLC_tx_50_t._402_EVSE_PROCESSING_DATA6_t = (0x00 | (1 << EVSE_Trigger_State));
                        xQueueSend(_50msQUEUE, &_50msmsg, 100);
                        vTaskDelay(1000);
                        _50msmsg.ID_t = _402;
                        _50msmsg.DATA[6] = _2_PLC_tx_50_t._402_EVSE_PROCESSING_DATA6_t = (0x00 | (0 << EVSE_Trigger_State));
                        xQueueSend(_50msQUEUE, &_50msmsg, 100);
                        vTaskDelay(100);
                        CURRENT_PLC2_STATE = _2_PLC_STATE_IDLE_2;
                        //                        leddata.GUN2 = 4;
                        //                        xQueueOverwrite(LED2_QUEUE, &leddata);
                    }
                }

                break;
            case _2_PLC_STATE_IDLE_2:
                _200msmsg.ID_t = _401;
                _200msmsg.DATA[0] = 0x00;
                xQueueSend(_200msQUEUE, &_200msmsg, 100);
                vTaskDelay(100);
                _1000msmsg.ID_t = _D402;
                _1000msmsg.DATA[0] = _2_PLC_tx_1000_t._D402_EVSE_PKIENVSELECTION_DATA0_t = EVSE_PKIENVSELECTION_Public;
                _1000msmsg.DATA[1] = _2_PLC_tx_1000_t._D402_EVSE_CERTCHAINVALID_DATA1_t = EVSE_CERTCHAINVALID_None;
                _1000msmsg.DATA[2] = _2_PLC_tx_1000_t._D402_EVSE_RKEYOPTION_DATA2_t = EVSE_RKEYOPTION_False;
                xQueueSend(_1000msQUEUE, &_1000msmsg, 100);
                vTaskDelay(100);
                _50msmsg.ID_t = _402;
                _50msmsg.DATA[1] = _2_PLC_tx_50_t._402_EVSE_CHARGING_CONTROL_DATA1_t = Charging_Control_Initialised_PPMT;
                xQueueSend(_50msQUEUE, &_50msmsg, 100);
                vTaskDelay(100);
                xQueueReceive(_C50B_QUEUE, &_c50bmsg, 0);
                if (_c50bmsg._50B_SECC_STATUS3_t == seccStatus_Initialized) {
                    CURRENT_PLC2_STATE = _2_PLC_STATE_INITIALIZED_1;
                }
                break;
            case _2_PLC_STATE_INITIALIZED_1:

                _50msmsg.ID_t = _402;
                _50msmsg.DATA[6] = _2_PLC_tx_50_t._402_EVSE_PROCESSING_DATA6_t = (0x00 | (1 << EVSE_Trigger_State));
                xQueueSend(_50msQUEUE, &_50msmsg, 100);

                vTaskDelay(1000);
                _50msmsg.ID_t = _402;
                _50msmsg.DATA[6] = _2_PLC_tx_50_t._402_EVSE_PROCESSING_DATA6_t = (0x00 | (0 << EVSE_Trigger_State));
                xQueueSend(_50msQUEUE, &_50msmsg, 100);
                vTaskDelay(100);
                if (xQueueReceive(_C502_QUEUE, &_c502msg, 0)) {
                    if ((((_c502msg.cpVoltage_msb) / 10) >= 8) && (((_c502msg.cpVoltage_msb) / 10) <= 10)) {
                        ////////HMI/////////////
                        Change_gun2_status_to(CONNECTED);
                        //                        vTaskResume(LED_TASKHandle);
                        ////////HMI/////////////
                        AC_Contactor_Relay_Clear();
                        //                        leddata.GUN2 = 4;
                        //                        xQueueOverwrite(LED2_QUEUE, &leddata);
                        CP_Level_2 = 9;
                        GUN2_CONNECTED = 1;
                        if (instance == 1) {
                            mac_id_conn_no_data.MAC_ID_CONN_NO[0] = CONNECTOR_NO_0;
                            xQueueOverwrite(ESP_S_MAC_ID_CONN_NO_QUEUE, &mac_id_conn_no_data);
                            vTaskResume(ESP_SEND_TASKHandle);
                        }
                        if ((START_STOP_AR1[0] == 2 && START_STOP_AR1[1] == 1)) {
                            CURRENT_PLC2_STATE = _2_PLC_STATE_INITIALIZED_2;
                            rfid_conn_no_data.RFID_CONN_NO[0] = CONNECTOR_NO_0;
                            xQueueOverwrite(ESP_S_RFID_CONN_NO_QUEUE, &rfid_conn_no_data);
                            instance1 = 1;

                        }
                        if (instance == 0) {
                            CURRENT_PLC2_STATE = _2_PLC_STATE_INITIALIZED_2;
                        }
                        gun_count++;
                    }
                    if ((((_c502msg.cpVoltage_msb) / 10) >= 11)) {
                        if (GUN1_CONNECTED == 0) {
                            //                            vTaskSuspend(LED_TASKHandle);
                            AC_Contactor_Relay_Set();
                            vTaskSuspend(FAN_TASKHandle);
                            FAN_ON(65535);
                            instance = 0;
                            instance1 = 0;
                            if (page_change_inst == 0) {
                                page_change_inst = 1;
                                Change_Page_to(CURRENT_PAGE);
                            }
                        }
                        GUN2_CONNECTED = 0;
                        CP_Level_2 = 12;
                        Change_gun2_status_to(AVAILABLE);
                    }

                    if (gun_count > 30) {
                        gun_count = 0;
                        if (GUN1_CONNECTED == 0) {
                            AC_Contactor_Relay_Set();
                        }
                        CURRENT_PLC2_STATE = _2_PLC_STATE_IDLE_1;
                    }
                }
                break;
            case _2_PLC_STATE_INITIALIZED_2:
                gun_count = 0;
                _200msmsg.ID_t = _401;
                _200msmsg.DATA[3] = _2_PLC_tx_200_t._401SUPPORTENERGY_TRANSFER_DATA3_t = (0x00 | (1 << SupportEnergyTransfer_DCEXTD));
                xQueueSend(_200msQUEUE, &_200msmsg, 100);
                vTaskDelay(1000);

                _50msmsg.ID_t = _402;
                _50msmsg.DATA[4] = _2_PLC_tx_50_t._402_EVSE_ISOLATION_STATUS_DATA4_t = Isolation_Status_Invalid;
                _50msmsg.DATA[6] = _2_PLC_tx_50_t._402_EVSE_PROCESSING_DATA6_t = (0x00 | (0 << EVSE_Processing_CPD) | (0 << EVSE_Processing_Cable_check) | (0 << EVSE_Trigger_Negotation));
                _50msmsg.DATA[7] = _2_PLC_tx_50_t._402_EVSE_VCP_LIMIT_DATA7_t = (0x00 | (0 << EVSE_Current_Limit) | (0 << EVSE_Voltage_Limit) | (0 << EVSE_Power_Limit));
                xQueueSend(_50msQUEUE, &_50msmsg, 100);
                vTaskDelay(1000);

                xQueueReceive(_C50B_QUEUE, &_c50bmsg, 0);
                _50msmsg.ID_t = _402;
                _50msmsg.DATA[1] = _2_PLC_tx_50_t._402_EVSE_CHARGING_CONTROL_DATA1_t = Charging_Control_Start_Charging;
                xQueueSend(_50msQUEUE, &_50msmsg, 100);
                vTaskDelay(100);
                CURRENT_PLC2_STATE = _2_PLC_STATE_WAITING_FOR_PLUG_IN;
                break;
            case _2_PLC_STATE_WAITING_FOR_PLUG_IN:
                xQueueReceive(_C502_QUEUE, &_c502msg, 0);
                xQueueReceive(_C50B_QUEUE, &_c50bmsg, 0);
                if ((_c502msg._502_SECC_CP_t == seccCpOscillator_Duty_Cycle_ON) && ((((_c502msg.cpVoltage_msb) / 10) >= 8) && (((_c502msg.cpVoltage_msb) / 10) <= 10))) {
                    CURRENT_PLC2_STATE = _2_PLC_STATE_PROCESSING_SLAC;
                }
                if (_c50bmsg._50B_SECC_STATUS3_t == seccStatus_TERMINATE || _c50bmsg._50B_SECC_STATUS3_t == seccStatus_ERROR || _c50bmsg._50B_SECC_STATUS3_t == seccStatus_IDLE) {
                    CURRENT_PLC2_STATE = _2_PLC_STATE_IDLE_1;
                }
                if ((((_c502msg.cpVoltage_msb) / 10) >= 11)) {
                    if (GUN1_CONNECTED == 0) {
                        AC_Contactor_Relay_Set();
                    }
                    GUN2_CONNECTED = 0;
                    CP_Level_2 = 12;
                    CURRENT_PLC2_STATE = _2_PLC_STATE_IDLE_1;
                }
                break;
            case _2_PLC_STATE_PROCESSING_SLAC:
                page_change_inst = 0;
                xQueueReceive(_C50B_QUEUE, &_c50bmsg, 0);
                if (_c50bmsg._50B_SECC_STATUS3_t >= seccStatus_ServiceDiscovery) {
                    if (instance == 1) {
                        CURRENT_PLC2_STATE = _2_PLC_STATE_AUTHORIZATION_EIM;
                    }
                    if (instance == 0) {

                        if (xQueueReceive(_C505_QUEUE, &_c505msg, 0)) {
                            mac_id_data.MAC_ID_IS[0] = _c505msg.evccMAC_Data0;
                            mac_id_data.MAC_ID_IS[1] = _c505msg.evccMAC_Data1;
                            mac_id_data.MAC_ID_IS[2] = _c505msg.evccMAC_Data2;
                            mac_id_data.MAC_ID_IS[3] = _c505msg.evccMAC_Data3;
                            mac_id_data.MAC_ID_IS[4] = _c505msg.evccMAC_Data4;
                            mac_id_data.MAC_ID_IS[5] = _c505msg.evccMAC_Data5;
                            //                            sprintf(buffer, "MAC ID %d %d %d %d %d %d", MAC_ID[0], MAC_ID[1], MAC_ID[2], MAC_ID[3], MAC_ID[4], MAC_ID[5]);
                            //                            SERCOM5_USART_Write(buffer, sizeof (buffer));
                            //                            while (!SERCOM5_USART_TransmitComplete());
                            xQueueOverwrite(ESP_S_MAC_ID_QUEUE, &mac_id_data);
                            if (mac_id_data.MAC_ID_IS[0] > 0) {
                                instance = 1;
                                CURRENT_PLC2_STATE = _2_PLC_STATE_AUTHORIZATION_EIM;
                                mac_id_conn_no_data.MAC_ID_CONN_NO[0] = CONNECTOR_NO_2;
                                xQueueOverwrite(ESP_S_MAC_ID_CONN_NO_QUEUE, &mac_id_conn_no_data);
                                vTaskResume(ESP_SEND_TASKHandle);
                            }
                        }
                    }
                }
                if (_c50bmsg._50B_SECC_STATUS3_t == seccStatus_TERMINATE || _c50bmsg._50B_SECC_STATUS3_t == seccStatus_ERROR || _c50bmsg._50B_SECC_STATUS3_t == seccStatus_IDLE) {
                    if (instance == 1) {
                        CURRENT_PLC2_STATE = _2_PLC_STATE_IDLE_1;
                        instance = 1;
                        //                        Stop_Code = 307;
                        //                        Stop_connector_no = 2;
                        //                        Change_Page_to(GUN2_FAILING_REASON_PAGE);
                    }
                    if (instance == 0) {
                        CURRENT_PLC2_STATE = _2_PLC_STATE_IDLE_1;
                        instance = 1;
                    }
                }
                if (_c50bmsg._50B_SECC_STATUS3_t == seccStatus_Waiting_SLAC) {
                    slac_count++;
                    if (slac_count == 240) {
                        slac_count = 0;
                        CURRENT_PLC2_STATE = _2_PLC_STATE_IDLE_1;
                        Stop_Code = 307;
                        Stop_connector_no = 2;
                        Change_Page_to(GUN2_FAILING_REASON_PAGE);
                    }
                }
                break;
            case _2_PLC_STATE_AUTHORIZATION_EIM:
                slac_count = 0;
                if (instance1 == 0) {
                    if (START_STOP_AR1[0] == 2 && START_STOP_AR1[1] == 1) {
                        rfid_conn_no_data.RFID_CONN_NO[0] = CONNECTOR_NO_0;
                        xQueueOverwrite(ESP_S_RFID_CONN_NO_QUEUE, &rfid_conn_no_data);
                        _50msmsg.ID_t = _402;
                        _50msmsg.DATA[6] = _2_PLC_tx_50_t._402_EVSE_PROCESSING_DATA6_t = (0x00 | (1 << EVSE_Processing_Auth_EIM));
                        xQueueSend(_50msQUEUE, &_50msmsg, 100);
                        vTaskDelay(100);
                        xQueueReceive(_C50B_QUEUE, &_c50bmsg, 0);
                        CURRENT_PLC2_STATE = _2_PLC_STATE_CHARGE_PARAMETER_DISCOVERY;
                        Change_Page_to(GUN2_AUTHENTICATION_SUCCESS_PAGE);
                        ////////////HMI//////////////////
                    }
                }
                if (instance1 == 1) {
                    _50msmsg.ID_t = _402;
                    _50msmsg.DATA[6] = _2_PLC_tx_50_t._402_EVSE_PROCESSING_DATA6_t = (0x00 | (1 << EVSE_Processing_Auth_EIM));
                    xQueueSend(_50msQUEUE, &_50msmsg, 100);
                    vTaskDelay(100);
                    xQueueReceive(_C50B_QUEUE, &_c50bmsg, 0);
                    CURRENT_PLC2_STATE = _2_PLC_STATE_CHARGE_PARAMETER_DISCOVERY;
                    ////////////HMI//////////////////
                    Change_Page_to(GUN2_AUTHENTICATION_SUCCESS_PAGE);
                    ////////////HMI//////////////////
                }
                xQueueReceive(_C50B_QUEUE, &_c50bmsg, 0);
                if (_c50bmsg._50B_SECC_STATUS3_t == seccStatus_TERMINATE || _c50bmsg._50B_SECC_STATUS3_t == seccStatus_ERROR || _c50bmsg._50B_SECC_STATUS3_t == seccStatus_IDLE) {
                    CURRENT_PLC2_STATE = _2_PLC_STATE_IDLE_1;
                    instance = 1;
                    Stop_Code = 308;
                    Stop_connector_no = 2;
                    Update_GUN2_Session_End_Reason(0x06);
                    Change_Page_to(GUN2_FAILING_REASON_PAGE);
                }
                break;
            case _2_PLC_STATE_CHARGE_PARAMETER_DISCOVERY:
                instance1 = 1;
                MERGER_Contactor_Set();
                rectimsg.CURRENT_VALUE[0] = 0;
                rectimsg.VOLTAGE_VALUE[0] = 200;
                rectimsg.RECTI_ON_OFF[0] = RECTIFIER_ON;
                rectimsg.PLC_ID[0] = 0x02;
                xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
                vTaskResume(RECTIFIER_TASKHandle);
                if (xQueueReceive(_C507_QUEUE, &_c507msg, 0)) {
                    MAX_VOLT_LIMIT = (((_c507msg.evMaximumVoltageLimitlsb) << 8) + (_c507msg.evMaximumVoltageLimitmsb)) / 10;
                    MAX_CURR_LIMIT_PLC1 = (((_c507msg.evMaximumCurrentLimitlsb) << 8) + (_c507msg.evMaximumCurrentLimitmsb)) / 10;
                    MAX_CURR_LIMIT2 = ((MAX_POWER_LIMIT * 10000) / (int) MAX_VOLT_LIMIT) * 10;
                    if (MAX_CURR_LIMIT2 > (MAX_CURR_LIMIT_PLC1 * 10)) {
                        MAX_CURR_LIMIT2 = (MAX_CURR_LIMIT_PLC1 * 10);
                    }
                    _50msmsg.ID_t = _402;
                    _50msmsg.DATA[6] = _2_PLC_tx_50_t._402_EVSE_PROCESSING_DATA6_t = (0x00 | (0 << EVSE_Processing_CPD));
                    xQueueSend(_50msQUEUE, &_50msmsg, 100);
                    vTaskDelay(100);
                    _200msmsg.ID_t = _403;
                    _200msmsg.DATA[0] = _2_PLC_tx_200_t._403_EVSE_MAX_CURRENT_LIMIT_MSB_DATA0 =
                            (uint16_t) MAX_CURR_LIMIT2 & 0x00FF;
                    _200msmsg.DATA[1] = _2_PLC_tx_200_t._403_EVSE_MAX_CURRENT_LIMIT_LSB_DATA1 =
                            ((uint16_t) MAX_CURR_LIMIT2 >> 8) & 0x00FF;
                    _200msmsg.DATA[2] = _2_PLC_tx_200_t._403_EVSE_MAX_POWER_LIMIT_MSB_DATA2 =
                            ((MAX_POWER_LIMIT * 10000) / 10) - ((((MAX_POWER_LIMIT * 10000) / 10) >> 8) << 8);
                    _200msmsg.DATA[3] = _2_PLC_tx_200_t._403_EVSE_MAX_POWER_LIMIT_LSB_DATA3 =
                            ((MAX_POWER_LIMIT * 10000) / 10) >> 8;
                    _200msmsg.DATA[4] = _2_PLC_tx_200_t._403_EVSE_MAX_VOLTAGE_LIMIT_MSB_DATA4 =
                            EVSE_MAX_VOLTAGE_DATA0;
                    _200msmsg.DATA[5] = _2_PLC_tx_200_t._403_EVSE_MAX_VOLTAGE_LIMIT_LSB_DATA5 =
                            EVSE_MAX_VOLTAGE_DATA1;
                    _200msmsg.DATA[6] = _2_PLC_tx_200_t._403_EVSE_PEAK_CURRENT_RIPPLE_MSB_DATA6 =
                            EVSE_PEAK_CURRENT_RIPPLE_DATA0;
                    _200msmsg.DATA[7] = _2_PLC_tx_200_t._403_EVSE_PEAK_CURRENT_RIPPLE_LSB_DATA7 =
                            EVSE_PEAK_CURRENT_RIPPLE_DATA1;
                    xQueueSend(_200msQUEUE, &_200msmsg, 100);
                    vTaskDelay(300);

                    _200msmsg.DATA[0] = _2_PLC_tx_200_t._404_EVSE_MIN_CURRENT_LIMIT_MSB_DATA0 =
                            EVSE_MIN_CURRENT_DATA0;
                    _200msmsg.DATA[1] = _2_PLC_tx_200_t._404_EVSE_MIN_CURRENT_LIMIT_LSB_DATA1 =
                            EVSE_MIN_CURRENT_DATA1;

                    _200msmsg.DATA[2] = _2_PLC_tx_200_t._404_EVSE_MIN_VOLTAGE_LIMIT_MSB_DATA2 =
                            EVSE_MIN_VOLTAGE_DATA0;
                    _200msmsg.DATA[3] = _2_PLC_tx_200_t._404_EVSE_MIN_VOLTAGE_LIMIT_LSB_DATA3 =
                            EVSE_MIN_VOLTAGE_DATA1;

                    _200msmsg.DATA[4] =
                            _2_PLC_tx_200_t._404_EVSE_CURRENT_REGULATION_TOLERANCE_MSB_DATA4 =
                            EVSE_PEAK_CURRENT_TOLERANCE_DATA0;
                    _200msmsg.DATA[5] =
                            _2_PLC_tx_200_t._404_EVSE_CURRENT_REGULATION_TOLERANCE_LSB_DATA5 =
                            EVSE_PEAK_CURRENT_TOLERANCE_DATA1;

                    _200msmsg.DATA[6] = _2_PLC_tx_200_t._404_EVSE_ENERGY_TO_DELIVERED_MSB_DATA6 =
                            EVSE_ENERGY_TO_DELIVERED_DATA0;
                    _200msmsg.DATA[7] = _2_PLC_tx_200_t._404_EVSE_ENERGY_TO_DELIVERED_LSB_DATA7 =
                            EVSE_ENERGY_TO_DELIVERED_DATA1;

                    _200msmsg.ID_t = _004;
                    xQueueSend(_200msQUEUE, &_200msmsg, 100);
                    vTaskDelay(300);

                    _50msmsg.DATA[6] = _2_PLC_tx_50_t._402_EVSE_PROCESSING_DATA6_t = (0x00 | (1 << EVSE_Processing_CPD));
                    _50msmsg.ID_t = _402;
                    xQueueSend(_50msQUEUE, &_50msmsg, 100);
                    vTaskDelay(100);
                    ////////////HMI//////////////////
                    Change_Page_to(GUN2_PREPARING_TO_CHARGE_PAGE);
                    ////////////HMI//////////////////
                    xQueueReceive(_C50B_QUEUE, &_c50bmsg, 0);
                    if ((_c50bmsg._50B_SECC_STATUS3_t > seccStatus_ChargeParameterDiscovery) && (_c50bmsg._50B_SECC_STATUS3_t < seccStatus_PreCharge)) {
                        CURRENT_PLC2_STATE = _2_PLC_STATE_CABLE_CHECK;
                        DC2_Contactor_Clear();
                    }
                    if (_c50bmsg._50B_SECC_STATUS3_t == seccStatus_TERMINATE || _c50bmsg._50B_SECC_STATUS3_t == seccStatus_ERROR || _c50bmsg._50B_SECC_STATUS3_t == seccStatus_IDLE) {
                        CURRENT_PLC2_STATE = _2_PLC_STATE_IDLE_1;
                        Stop_Code = 309;
                        Stop_connector_no = 2;
                        Update_GUN2_Session_End_Reason(0x08);
                        Change_Page_to(GUN2_FAILING_REASON_PAGE);
                    }
                }
                memset(mac_id_data.MAC_ID_IS, 0, sizeof (mac_id_data.MAC_ID_IS));
                xQueueOverwrite(ESP_S_MAC_ID_QUEUE, &mac_id_data);
                mac_id_conn_no_data.MAC_ID_CONN_NO[0] = CONNECTOR_NO_0;
                xQueueOverwrite(ESP_S_MAC_ID_CONN_NO_QUEUE, &mac_id_conn_no_data);
                memset(START_STOP_AR1, 0, sizeof (START_STOP_AR1));
                break;
            case _2_PLC_STATE_CABLE_CHECK:


                xQueueReceive(_C502_QUEUE, &_c502msg, 0);
                if ((_c502msg.cpVoltage_msb) / 10 >= 5) {
                    if (!IMD2_RESPONSE_Get()) {

                        _50msmsg.DATA[4] = _2_PLC_tx_50_t._402_EVSE_ISOLATION_STATUS_DATA4_t =
                                Isolation_Status_Valid;
                        _50msmsg.DATA[6] = _2_PLC_tx_50_t._402_EVSE_PROCESSING_DATA6_t = (0x00 | (1 << EVSE_Processing_Cable_check) | (1 << EVSE_Isolation_Mointor));
                        _50msmsg.ID_t = _402;
                        xQueueSend(_50msQUEUE, &_50msmsg, 100);
                        vTaskDelay(100);
                        CURRENT_PLC2_STATE = _2_PLC_STATE_PRE_CHARGE;
                    } else {
                        CURRENT_PLC2_STATE = _2_PLC_STATE_IDLE_1;
                        Stop_Code = 309;
                        Stop_connector_no = 2;
                        Update_GUN2_Session_End_Reason(0x07);
                        Change_Page_to(GUN2_FAILING_REASON_PAGE);
                    }
                }
                break;
            case _2_PLC_STATE_PRE_CHARGE:

                //                                if (xQueueReceive(_C509_QUEUE, &_c509msg, 0)) {
                xQueueReceive(_C509_QUEUE, &_c509msg, 0);
                voltage_to_give = ((((_c509msg.targetVoltagelsb) << 8) + _c509msg.targetVoltagemsb)) / 10;
                current_to_give = (((_c509msg.targetCurrentlsb) << 8) + _c509msg.targetCurrentmsb) / 10;
                rectimsg.CURRENT_VALUE[0] = 2;
                rectimsg.VOLTAGE_VALUE[0] = voltage_to_give;
                rectimsg.RECTI_ON_OFF[0] = RECTIFIER_ON;
                rectimsg.PLC_ID[0] = 0x02;
                xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
                vTaskResume(RECTIFIER_TASKHandle);
                //                vTaskDelay(2000);
                _50msmsg.DATA[0] = _2_PLC_tx_50_t._405_EVSE_PRESENT_VOLTAGE_MSB_DATA0 =
                        _c509msg.targetVoltagemsb;
                _50msmsg.DATA[1] = _2_PLC_tx_50_t._405_EVSE_PRESENT_VOLTAGE_LSB_DATA1 =
                        _c509msg.targetVoltagelsb;
                //                _50msmsg.DATA[2] = _2_PLC_tx_50_t._405_EVSE_PRESENT_CURRENT_MSB_DATA2 =
                //                        _c509msg.targetCurrentmsb;
                //                _50msmsg.DATA[3] = _2_PLC_tx_50_t._405_EVSE_PRESENT_CURRENT_LSB_DATA3 =
                //                        _c509msg.targetCurrentlsb;
                _50msmsg.ID_t = _405;
                xQueueSend(_50msQUEUE, &_50msmsg, 100);
                vTaskDelay(100);
                /////////HMI/////////////////////
                Change_Page_to(GUN2_PARAM_PAGE);

                //                }
                if (xQueueReceive(_C50B_QUEUE, &_c50bmsg, 0)) {
                    if (_c50bmsg._50B_SECC_STATUS3_t == seccStatus_CurrentDemand) {
                        xTimerStart(all_rec_timer, 60000);
                        xTimerStart(rec1_timer, 60000);
                        xTimerStart(rec2_timer, 60000);
                        xTimerStart(rec3_timer, 60000);
                        xTimerStart(rec4_timer, 60000);
                        xTimerStart(Gun2_Charging_timer, 60000);
                        CURRENT_PLC2_STATE = _2_PLC_STATE_CURRENT_DEMAND_1;
                        Update_GUN2_Charging_Start_date(day);
                        vTaskDelay(100);
                        Update_GUN2_Charging_Start_month(month);
                        vTaskDelay(100);
                        Update_GUN2_Charging_Start_year(year);
                        vTaskDelay(100);
                        Update_GUN2_Charging_Start_mins(minute);
                        vTaskDelay(100);
                        Update_GUN2_Charging_Start_hour(hour);
                        vTaskDelay(100);
                        Update_GUN2_Charging_Start_sec(sec);
                        vTaskDelay(100);

                        STARTING_UNIT = IMPORT_ENERGY2;
                        //                        vTaskResume(LED_TASKHandle);
                        flashmsg.START_DATE = (year << 16) | (month << 8) | day;
                        flashmsg.START_TIME = (hour << 16) | (minute << 8) | sec;

                    }
                    if (_c50bmsg._50B_SECC_STATUS3_t == seccStatus_TERMINATE || _c50bmsg._50B_SECC_STATUS3_t == seccStatus_ERROR || _c50bmsg._50B_SECC_STATUS3_t == seccStatus_IDLE) {
                        CURRENT_PLC2_STATE = _2_PLC_STATE_TERMINATED;
                        Stop_Code = 310;
                        Stop_connector_no = 2;
                        Update_GUN2_Session_End_Reason(0x08);
                        Change_Page_to(GUN2_FAILING_REASON_PAGE);
                    }
                }


                break;
            case _2_PLC_STATE_CURRENT_DEMAND_1:
                vTaskResume(FAN_TASKHandle);
                //                leddata.GUN2 = 1;
                //                xQueueOverwrite(LED2_QUEUE, &leddata);
                Change_gun2_status_to(CHARGING);
                Update_GUN2_Duration(GUN2_CHARGING_TIME);
                if (initial_SOC2 == 7) {
                    Update_GUN2_Initial_SOC(FINAL_INITIAL_SOC);
                }
                if (xQueueReceive(_C509_QUEUE, &_c509msg, 0)) {
                    current_to_give =
                            ((uint16_t) (((((_c509msg.targetCurrentlsb) << 8) + _c509msg.targetCurrentmsb)) / 10));

                    voltage_to_give =
                            ((uint16_t) (((((_c509msg.targetVoltagelsb) << 8) + _c509msg.targetVoltagemsb)) / 10));
                    //                    if (current_to_give > 2500) {
                    //                        current_to_give = 250;
                    //                    }
                    sprintf(buffffffffff, "current : %f\r\n", current_to_give);
                    SERCOM5_USART_Write(buffffffffff, sizeof (buffffffffff));
                    while (!SERCOM5_USART_TransmitComplete());
                    power = (current_to_give * voltage_to_give);

                    if (SINGLE_GUN2_POWER == 0) {
                        POWER_VALUE = POWER_VALUE_X;
                        if ((power) < POWER_VALUE) {
                            if (GUN1_CONNECTED == 0) {
                                rectimsg.VOLTAGE_VALUE[0] = voltage_to_give + Difference_in_VOLTAGE2;
                                act_current_to_give = (POWER_VALUE) / act_volt_2;
                                if (act_current_to_give <= current_to_give) {
                                    rectimsg.CURRENT_VALUE[0] = act_current_to_give / NO_OF_RECTIFIER;
                                } else if (act_current_to_give > current_to_give) {

                                    rectimsg.CURRENT_VALUE[0] = current_to_give / NO_OF_RECTIFIER;
                                }
                                rectimsg.PLC_ID[0] = 0x03;
                                rectimsg.RECTI_ON_OFF[0] = RECTIFIER_ON;
                                xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
                            }
                            if (GUN1_CONNECTED == 1 && CURRENT_PLC1_STATE >= _1_PLC_STATE_CHARGE_PARAMETER_DISCOVERY) {
                                MERGER_Contactor_Set();

                                rectimsg.VOLTAGE_VALUE[0] = voltage_to_give + Difference_in_VOLTAGE2;
                                act_current_to_give = (POWER_VALUE / 2) / act_volt_2;
                                if (act_current_to_give <= current_to_give) {
                                    rectimsg.CURRENT_VALUE[0] = act_current_to_give / (NO_OF_RECTIFIER >> 1);
                                } else if (act_current_to_give > current_to_give) {

                                    rectimsg.CURRENT_VALUE[0] = current_to_give / (NO_OF_RECTIFIER >> 1);
                                }
                                rectimsg.PLC_ID[0] = 0x02;
                                rectimsg.RECTI_ON_OFF[0] = RECTIFIER_ON;
                                xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
                            } else if (GUN1_CONNECTED == 1 && CURRENT_PLC1_STATE < _1_PLC_STATE_CHARGE_PARAMETER_DISCOVERY) {
                                rectimsg.VOLTAGE_VALUE[0] = voltage_to_give + Difference_in_VOLTAGE2;
                                act_current_to_give = (POWER_VALUE) / act_volt_2;
                                if (act_current_to_give <= current_to_give) {
                                    rectimsg.CURRENT_VALUE[0] = act_current_to_give / NO_OF_RECTIFIER;
                                } else if (act_current_to_give > current_to_give) {

                                    rectimsg.CURRENT_VALUE[0] = current_to_give / NO_OF_RECTIFIER;
                                }
                                rectimsg.PLC_ID[0] = 0x03;
                                rectimsg.RECTI_ON_OFF[0] = RECTIFIER_ON;
                                xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
                            }
                        }
                        if (power > POWER_VALUE) {

                            if (GUN1_CONNECTED == 0) {
                                rectimsg.VOLTAGE_VALUE[0] = voltage_to_give + Difference_in_VOLTAGE2;
                                act_current_to_give = (POWER_VALUE) / act_volt_2;
                                if (act_current_to_give <= current_to_give) {
                                    rectimsg.CURRENT_VALUE[0] = act_current_to_give / NO_OF_RECTIFIER;
                                } else if (act_current_to_give > current_to_give) {

                                    rectimsg.CURRENT_VALUE[0] = current_to_give / NO_OF_RECTIFIER;
                                }
                                rectimsg.PLC_ID[0] = 0x03;
                                rectimsg.RECTI_ON_OFF[0] = RECTIFIER_ON;
                                xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
                            }
                            if (GUN1_CONNECTED == 1 && CURRENT_PLC1_STATE >= _1_PLC_STATE_CHARGE_PARAMETER_DISCOVERY) {
                                MERGER_Contactor_Set();

                                rectimsg.VOLTAGE_VALUE[0] = voltage_to_give + Difference_in_VOLTAGE2;
                                act_current_to_give = (POWER_VALUE / 2) / act_volt_2;
                                if (act_current_to_give <= current_to_give) {
                                    rectimsg.CURRENT_VALUE[0] = act_current_to_give / (NO_OF_RECTIFIER >> 1);
                                } else if (act_current_to_give > current_to_give) {

                                    rectimsg.CURRENT_VALUE[0] = current_to_give / (NO_OF_RECTIFIER >> 1);
                                }
                                rectimsg.PLC_ID[0] = 0x02;
                                rectimsg.RECTI_ON_OFF[0] = RECTIFIER_ON;
                                xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
                            } else if (GUN1_CONNECTED == 1 && CURRENT_PLC1_STATE < _1_PLC_STATE_CHARGE_PARAMETER_DISCOVERY) {
                                rectimsg.VOLTAGE_VALUE[0] = voltage_to_give + Difference_in_VOLTAGE2;
                                act_current_to_give = (POWER_VALUE) / act_volt_2;
                                if (act_current_to_give <= current_to_give) {
                                    rectimsg.CURRENT_VALUE[0] = act_current_to_give / NO_OF_RECTIFIER;
                                } else if (act_current_to_give > current_to_give) {

                                    rectimsg.CURRENT_VALUE[0] = current_to_give / NO_OF_RECTIFIER;
                                }
                                rectimsg.PLC_ID[0] = 0x03;
                                rectimsg.RECTI_ON_OFF[0] = RECTIFIER_ON;
                                xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
                            }
                        }
                    }
                    if (SINGLE_GUN2_POWER == 1) {
                        if (GUN1_CONNECTED == 0) {
                            rectimsg.VOLTAGE_VALUE[0] = voltage_to_give + Difference_in_VOLTAGE2;
                            act_current_to_give = (POWER_VALUE_X2) / act_volt_2;
                            if (act_current_to_give <= current_to_give) {
                                rectimsg.CURRENT_VALUE[0] = act_current_to_give / NO_OF_RECTIFIER;
                            } else if (act_current_to_give > current_to_give) {

                                rectimsg.CURRENT_VALUE[0] = current_to_give / NO_OF_RECTIFIER;
                            }
                            rectimsg.PLC_ID[0] = 0x03;
                            rectimsg.RECTI_ON_OFF[0] = RECTIFIER_ON;
                            xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
                        }
                        if (GUN1_CONNECTED == 1 && CURRENT_PLC1_STATE >= _1_PLC_STATE_CHARGE_PARAMETER_DISCOVERY) {
                            MERGER_Contactor_Set();
                            if (POWER_VALUE_X2 > ((MAX_POWER_LIMIT * 10000) / 2)) {
                                POWER_VALUE_X2 = ((MAX_POWER_LIMIT * 10000) / 2);
                            }
                            rectimsg.VOLTAGE_VALUE[0] = voltage_to_give + Difference_in_VOLTAGE2;
                            act_current_to_give = (POWER_VALUE_X2) / act_volt_2;
                            if (act_current_to_give <= current_to_give) {
                                rectimsg.CURRENT_VALUE[0] = act_current_to_give / (NO_OF_RECTIFIER >> 1);
                            } else if (act_current_to_give > current_to_give) {

                                rectimsg.CURRENT_VALUE[0] = current_to_give / (NO_OF_RECTIFIER >> 1);
                            }
                            rectimsg.PLC_ID[0] = 0x02;
                            rectimsg.RECTI_ON_OFF[0] = RECTIFIER_ON;
                            xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
                        } else if (GUN1_CONNECTED == 1 && CURRENT_PLC1_STATE < _1_PLC_STATE_CHARGE_PARAMETER_DISCOVERY) {
                            rectimsg.VOLTAGE_VALUE[0] = voltage_to_give + Difference_in_VOLTAGE2;
                            act_current_to_give = (POWER_VALUE_X2) / act_volt_2;
                            if (act_current_to_give <= current_to_give) {
                                rectimsg.CURRENT_VALUE[0] = act_current_to_give / NO_OF_RECTIFIER;
                            } else if (act_current_to_give > current_to_give) {

                                rectimsg.CURRENT_VALUE[0] = current_to_give / NO_OF_RECTIFIER;
                            }
                            rectimsg.PLC_ID[0] = 0x03;
                            rectimsg.RECTI_ON_OFF[0] = RECTIFIER_ON;
                            xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
                        }
                    }
                    Demand_Current2_ARRAY[j_count] = ((uint16_t) (((((_c509msg.targetCurrentlsb) << 8) + _c509msg.targetCurrentmsb)) / 10));
                    ;
                    Demand_Voltage2_ARRAY[j_count] = act_volt_2;
                    j_count = j_count + 1;

                    _50msmsg.DATA[0] = _2_PLC_tx_50_t._405_EVSE_PRESENT_VOLTAGE_MSB_DATA0 =
                            _c509msg.targetVoltagemsb;
                    _50msmsg.DATA[1] = _2_PLC_tx_50_t._405_EVSE_PRESENT_VOLTAGE_LSB_DATA1 =
                            _c509msg.targetVoltagelsb;
                    _50msmsg.DATA[2] = _2_PLC_tx_50_t._405_EVSE_PRESENT_CURRENT_MSB_DATA2 =
                            _c509msg.targetCurrentmsb;
                    _50msmsg.DATA[3] = _2_PLC_tx_50_t._405_EVSE_PRESENT_CURRENT_LSB_DATA3 =
                            _c509msg.targetCurrentlsb;
                    _50msmsg.ID_t = _405;
                    xQueueSend(_50msQUEUE, &_50msmsg, 100);
                    vTaskDelay(50);
                }

                if (xQueueReceive(_C508_QUEUE, &_c508msg, 0)) {

                    SOC_2_ARRAY[i_count] = _c508msg.evSOC;
                    CP_Level_2 = 6;
                    i_count = i_count + 1;
                    if (initial_SOC2 < 5) {
                        Update_GUN2_Initial_SOC(_c508msg.evSOC);
                        FINAL_INITIAL_SOC = _c508msg.evSOC;
                        initial_SOC2 = initial_SOC2 + 1;
                    }
                    if (initial_SOC2 == 5) {
                        initial_SOC2 = 7;
                        SOC2_INITIAL = _c508msg.evSOC;
                    }
                }
                if (j_count == 5) {
                    j_count = 0;
                    for (uint8_t i = 0; i < 5; i++) {
                        if (Demand_Current2_ARRAY[0] <= Demand_Current2_ARRAY[i]) {
                            Demand_Current2_ARRAY[0] = Demand_Current2_ARRAY[i];
                            Demand_Current2 = Demand_Current2_ARRAY[0];
                        }
                        if (Demand_Voltage2_ARRAY[0] <= Demand_Voltage2_ARRAY[i]) {
                            Demand_Voltage2_ARRAY[0] = Demand_Voltage2_ARRAY[i];
                            Demand_Voltage2 = Demand_Voltage2_ARRAY[0];
                        }
                    }
                    Update_GUN2_Demand_Current(Demand_Current2_ARRAY[0]);
                    Update_GUN2_Demand_Voltage(Demand_Voltage2_ARRAY[0]);
                }
                if (i_count == 5) {
                    i_count = 0;
                    for (uint8_t i = 0; i < 5; i++) {
                        if (SOC_2_ARRAY[0] <= SOC_2_ARRAY[i]) {
                            SOC_2_ARRAY[0] = SOC_2_ARRAY[i];
                            SOC_2 = SOC_2_ARRAY[0];
                        }
                    }
                    Update_GUN2_Battery_SOC(SOC_2_ARRAY[0]);
                }

                if ((GUN1_CONNECTED == 0) && (GUN2_CONNECTED == 1)) {
                    rfid_conn_no_data.RFID_CONN_NO[0] = CONNECTOR_NO_0;
                    xQueueOverwrite(ESP_S_RFID_CONN_NO_QUEUE, &rfid_conn_no_data);
                }
                if ((GUN1_CONNECTED == 1) && (GUN2_CONNECTED == 1) && (CURRENT_PLC1_STATE >= _1_PLC_STATE_PRE_CHARGE)) {
                    rfid_conn_no_data.RFID_CONN_NO[0] = CONNECTOR_NO_0;
                    xQueueOverwrite(ESP_S_RFID_CONN_NO_QUEUE, &rfid_conn_no_data);
                }
                if ((_c50bmsg._50B_SECC_STATUS3_t == seccStatus_SessionStop) || (_c50bmsg._50B_SECC_STATUS3_t == seccStatus_TERMINATE) || (_c50bmsg._50B_SECC_STATUS3_t == seccStatus_ERROR)) {
                    CURRENT_PLC2_STATE = _2_PLC_STATE_TERMINATED;
                    CP_Level_2 = 9;
                    Stop_Code = 202;
                    Stop_connector_no = 2;
                    Update_GUN2_Session_End_Reason(0x0A);
                    STOPING_UNIT = IMPORT_ENERGY2;
                }
                if (_c508msg.Charging_Complete_t == CHARGING_COMPLETE) {
                    CURRENT_PLC2_STATE = _2_PLC_STATE_TERMINATED;
                    CP_Level_2 = 9;
                    Stop_Code = 201;
                    Stop_connector_no = 2;
                    Update_GUN2_Session_End_Reason(0x0A);
                    STOPING_UNIT = IMPORT_ENERGY2;
                }
                if (START_STOP_AR1[0] == 2 && START_STOP_AR1[2] == 1) {
                    CURRENT_PLC2_STATE = _2_PLC_STATE_TERMINATED;
                    CP_Level_2 = 9;
                    memset(START_STOP_AR1, 0, 3);
                    STOPING_UNIT = IMPORT_ENERGY2;
                }
                break;
            case _2_PLC_STATE_TERMINATED:

                if (GUN2_CONNECTED == 1 && GUN1_CONNECTED == 0) {
                    rectimsg.RECTI_ON_OFF[0] = RECTIFIER_OFF;
                    rectimsg.PLC_ID[0] = 0x03;
                    xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
                    vTaskDelay(3000);
                }
                if (GUN1_CONNECTED == 1 && GUN2_CONNECTED == 1) {
                    rectimsg.RECTI_ON_OFF[0] = RECTIFIER_OFF;
                    rectimsg.PLC_ID[0] = 0x02;
                    xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
                    vTaskDelay(3000);
                }

                _50msmsg.DATA[1] = _2_PLC_tx_50_t._402_EVSE_CHARGING_CONTROL_DATA1_t =
                        Charging_Control_Normal_Stop;
                _50msmsg.ID_t = _402;
                xQueueSend(_50msQUEUE, &_50msmsg, 100);
                vTaskDelay(50);
                _50msmsg.DATA[0] = _2_PLC_tx_50_t._405_EVSE_PRESENT_VOLTAGE_MSB_DATA0 = 0;
                _50msmsg.DATA[1] = _2_PLC_tx_50_t._405_EVSE_PRESENT_VOLTAGE_LSB_DATA1 = 0;
                _50msmsg.ID_t = _405;
                xQueueSend(_50msQUEUE, &_50msmsg, 100);
                vTaskDelay(50);
                DC2_Contactor_Set();
                STOPING_UNIT = IMPORT_ENERGY2;
                //                leddata.GUN2 = 0;
                //                xQueueOverwrite(LED2_QUEUE, &leddata);
                GUN2_CONNECTED = 0;

                rectimsg.PLC_ID[0] = 0x02;

                rectimsg.RECTI_ON_OFF[0] = RECTIFIER_OFF;
                rectimsg.PLC_ID[0] = 0x02;
                xQueueOverwrite(RECTIFIER_QUEUE, &rectimsg);
                vTaskDelay(3000);
                _50msmsg.DATA[1] = _2_PLC_tx_50_t._402_EVSE_CHARGING_CONTROL_DATA1_t =
                        Charging_Control_Normal_Stop;
                _50msmsg.ID_t = _402;
                xQueueSend(_50msQUEUE, &_50msmsg, 100);
                vTaskDelay(50);
                _50msmsg.DATA[0] = _2_PLC_tx_50_t._405_EVSE_PRESENT_VOLTAGE_MSB_DATA0 = 0;
                _50msmsg.DATA[1] = _2_PLC_tx_50_t._405_EVSE_PRESENT_VOLTAGE_LSB_DATA1 = 0;
                _50msmsg.ID_t = _405;
                xQueueSend(_50msQUEUE, &_50msmsg, 100);
                vTaskDelay(50);
                DC2_Contactor_Set();
                //                if ((GUN2_CONNECTED == 0) && (GUN1_CONNECTED == 0)) {
                //                    vTaskSuspend(LED_TASKHandle);
                //                }
                xTimerStop(Gun2_Charging_timer, 10);
                /////////HMI/////////////////////
                Update_GUN2_Charging_Stop_date(day);
                Update_GUN2_Charging_Stop_month(month);
                Update_GUN2_Charging_Stop_year(year);
                Update_GUN2_Charging_Stop_mins(minute);
                Update_GUN2_Charging_Stop_hour(hour);
                Update_GUN2_Charging_Stop_sec(sec);
                Update_GUN2_Booking_ID(BOOKING_ID2);
                if (STOP_BY == BY_RFID) {
                    Update_GUN2_Session_End_Reason(BY_RFID);
                }
                if (STOP_BY == BY_REMOTE) {
                    Update_GUN2_Session_End_Reason(BY_REMOTE);
                }
                if (STOP_BY == BY_DE_AUTH) {
                    Update_GUN2_Session_End_Reason(BY_DE_AUTH);
                }
                DIFF_UNIT = (((uint32_t) STOPING_UNIT) - ((uint32_t) STARTING_UNIT));
                if (DIFF_UNIT < 0) {
                    DIFF_UNIT = 0;
                }
                Update_GUN2_Uint_Consumed(DIFF_UNIT);
                CURRENT_PAGE = GUN2_SUMMARY_PAGE;
                Change_gun2_status_to(CHARGING_COMPLETED);
                /////////HMI/////////////////////
                flashmsg.BOOKING_ID = BOOKING_ID2;
                flashmsg.STOP_DATE = (year << 16) | (month << 8) | day;
                flashmsg.STOP_TIME = (hour << 16) | (minute << 8) | sec;
                flashmsg.START_SOC_AND_END_SOC = (FINAL_INITIAL_SOC << 16) | SOC_2;
                flashmsg.UNIT_CONSUMED_AND_CONN_ID = (0x02 << 16) | (uint32_t) DIFF_UNIT;
                flashmsg.SESSION_STOP_REASON_AND_DURATION = (STOP_BY << 16) | GUN2_CHARGING_TIME;
                flashmsg.WHAT_TYPE_OF_DATA = CHARGING_DATA;
                xQueueSend(FLASH_WRITE_QUEUE, &flashmsg, 100);
                vTaskResume(FLASH_WRITE_TASKHandle);
                count = 1;
                GUN2_CHARGING_TIME = 0;
                GUN2_200_clear = GUN2_500_clear = GUN2_50_clear = GUN2_1000_clear = 1;
                break;
        }
        esp_s_gun2_p.CP_Level_2 = CP_Level_2;
        esp_s_gun2_p.Demand_Current2 = Demand_Current2;
        esp_s_gun2_p.Demand_Volatge2 = Demand_Voltage2;
        esp_s_gun2_p.Initial_SOC2 = SOC2_INITIAL;
        esp_s_gun2_p.SOC_2 = SOC_2;
        cplevel2.CP_LEVEL2[0] = CP_Level_2;
        xQueueOverwrite(ESP_S_GUN2_P_QUEUE, &esp_s_gun2_p);
        xQueueOverwrite(CP_LEVEL2_QUEUE, &cplevel2);
        if (count == 1) {

            count = 0;
            CURRENT_PLC2_STATE = _2_PLC_STATE_IDLE_1;
            vTaskResume(GUN2_PARAM_TASKHandle);
            vTaskSuspend(_2_PLC_MANAGE_TASKHandle);
        }

        vTaskDelay(800);
    }
}

void Start_RECTIFIER_TASK(void *argument) {
    static float current_t = 0;
    static float voltage_t = 200;
    RECTIFIER_Q msg;
    RELAY_Q relaymsg;
    memset(relaymsg.RELAY_DATA, 0, sizeof (relaymsg.RELAY_DATA));
    static uint8_t merger_flag = 0;
    char buffer[50] = {0};

    for (;;) {

        if (xQueueReceive(RECTIFIER_QUEUE, &msg, 0)) {
            switch (msg.PLC_ID[0]) {
                case 0x01:
                    merger_flag = 0;

                    current_t = msg.CURRENT_VALUE[0];
                    //                    sprintf(buffer, "current1 : %f\r\n", current_t);
                    //                    SERCOM5_USART_Write(buffer, sizeof (buffer));
                    //                    while (!(SERCOM5_USART_TransmitComplete()));
                    if (current_t < 1) {
                        current_t = 2;
                    }
                    voltage_t = msg.VOLTAGE_VALUE[0];
                    if (voltage_t > 500) {
                        setRectifierVoltMode(RECTIFIER1_GROUP1, HIGH_V_MODE);
                        vTaskDelay(50);
                        setRectifierVoltMode(RECTIFIER2_GROUP1, HIGH_V_MODE);
                        vTaskDelay(50);
                    }
                    if (voltage_t <= 500) {
                        setRectifierVoltMode(RECTIFIER1_GROUP1, LOW_V_MODE);
                        vTaskDelay(50);
                        setRectifierVoltMode(RECTIFIER2_GROUP1, LOW_V_MODE);
                        vTaskDelay(50);
                    }
                    if ((current_t * 2) >= 250) {
                        current_t = 62;
                    }
                    setRectifierVoltage(RECTIFIER1_GROUP1, (uint32_t) (voltage_t * 1000));
                    vTaskDelay(50);
                    setRectifierCurrent(RECTIFIER1_GROUP1, (uint32_t) (current_t * 1000));
                    vTaskDelay(50);
                    rectifierPowerOn(RECTIFIER1_GROUP1);
                    vTaskDelay(50);
                    setRectifierVoltage(RECTIFIER2_GROUP1, (uint32_t) (voltage_t * 1000));
                    vTaskDelay(50);
                    setRectifierCurrent(RECTIFIER2_GROUP1, (uint32_t) (current_t * 1000));
                    vTaskDelay(50);
                    rectifierPowerOn(RECTIFIER2_GROUP1);
                    vTaskDelay(50);

                    if ((msg.RECTI_ON_OFF) == RECTIFIER_OFF) {
                        DC1_Contactor_Set();
                        rectifierPowerOff(RECTIFIER2_GROUP1);
                        vTaskDelay(2);
                        rectifierPowerOff(RECTIFIER1_GROUP1);
                        vTaskDelay(2);
                    }
                    break;
                case 0x02:
                    merger_flag = 0;

                    current_t = msg.CURRENT_VALUE[0];
                    //                    sprintf(buffer, "current2 : %f\r\n", current_t);
                    //                    SERCOM5_USART_Write(buffer, sizeof (buffer));
                    //                    while (!(SERCOM5_USART_TransmitComplete()));
                    voltage_t = msg.VOLTAGE_VALUE[0];
                    if (voltage_t > 500) {
                        setRectifierVoltMode2(RECTIFIER1_GROUP2, HIGH_V_MODE);
                        vTaskDelay(50);
                        setRectifierVoltMode2(RECTIFIER2_GROUP2, HIGH_V_MODE);
                        vTaskDelay(50);
                    }
                    if (voltage_t <= 500) {
                        setRectifierVoltMode2(RECTIFIER1_GROUP2, LOW_V_MODE);
                        vTaskDelay(50);
                        setRectifierVoltMode2(RECTIFIER2_GROUP2, LOW_V_MODE);
                        vTaskDelay(50);
                    }
                    if (current_t < 1) {
                        current_t = 1;
                    }
                    if ((current_t * 2) >= 250) {
                        current_t = 62;
                    }
                    setRectifierVoltage_2(RECTIFIER1_GROUP2, (uint32_t) (voltage_t * 1000));
                    vTaskDelay(50);
                    setRectifierCurrent_2(RECTIFIER1_GROUP2, (uint32_t) (current_t * 1000));
                    vTaskDelay(50);
                    rectifierPowerOn_2(RECTIFIER1_GROUP2);
                    vTaskDelay(50);
                    setRectifierVoltage_2(RECTIFIER2_GROUP2, (uint32_t) (voltage_t * 1000));
                    vTaskDelay(50);
                    setRectifierCurrent_2(RECTIFIER2_GROUP2, (uint32_t) (current_t * 1000));
                    vTaskDelay(50);
                    rectifierPowerOn_2(RECTIFIER2_GROUP2);
                    vTaskDelay(50);

                    if ((msg.RECTI_ON_OFF) == RECTIFIER_OFF) {
                        DC2_Contactor_Set();
                        rectifierPowerOff_2(RECTIFIER2_GROUP2);
                        vTaskDelay(50);
                        rectifierPowerOff_2(RECTIFIER1_GROUP2);
                        vTaskDelay(50);
                    }
                    break;
                case 0x03:
                    if (!MERGER_Contactor_Get()) {
                        xTimerStart(merger_timer, 10000);
                    }
                    current_t = msg.CURRENT_VALUE[0];
                    if (current_t < 1) {
                        current_t = 2;
                    }
                    //                    sprintf(buffer, "merger_current : %f\r\n", current_t);
                    //                    SERCOM5_USART_Write(buffer, sizeof (buffer));
                    //                    while (!(SERCOM5_USART_TransmitComplete()));
                    if ((current_t * 4) >= 250) {
                        current_t = 62;
                    }
                    voltage_t = msg.VOLTAGE_VALUE[0];
                    if (voltage_t > 500) {
                        setRectifierVoltMode2(RECTIFIER1_GROUP2, HIGH_V_MODE);
                        vTaskDelay(50);
                        setRectifierVoltMode2(RECTIFIER2_GROUP2, HIGH_V_MODE);
                        vTaskDelay(50);
                        setRectifierVoltMode(RECTIFIER1_GROUP1, HIGH_V_MODE);
                        vTaskDelay(50);
                        setRectifierVoltMode(RECTIFIER2_GROUP1, HIGH_V_MODE);
                        vTaskDelay(50);
                    }
                    if (voltage_t <= 500) {
                        setRectifierVoltMode2(RECTIFIER1_GROUP2, LOW_V_MODE);
                        vTaskDelay(50);
                        setRectifierVoltMode2(RECTIFIER2_GROUP2, LOW_V_MODE);
                        vTaskDelay(50);
                        setRectifierVoltMode(RECTIFIER1_GROUP1, LOW_V_MODE);
                        vTaskDelay(50);
                        setRectifierVoltMode(RECTIFIER2_GROUP1, LOW_V_MODE);
                        vTaskDelay(50);
                    }
                    setRectifierVoltage(RECTIFIER1_GROUP1, (uint32_t) (voltage_t * 1000));
                    vTaskDelay(50);
                    setRectifierCurrent(RECTIFIER1_GROUP1, (uint32_t) (current_t * 1000));
                    vTaskDelay(50);
                    rectifierPowerOn(RECTIFIER1_GROUP1);
                    vTaskDelay(50);
                    setRectifierVoltage(RECTIFIER2_GROUP1, (uint32_t) (voltage_t * 1000));
                    vTaskDelay(50);
                    setRectifierCurrent(RECTIFIER2_GROUP1, (uint32_t) (current_t * 1000));
                    vTaskDelay(50);
                    rectifierPowerOn(RECTIFIER2_GROUP1);
                    vTaskDelay(50);

                    setRectifierVoltage_2(RECTIFIER1_GROUP2, (uint32_t) (voltage_t * 1000));
                    vTaskDelay(50);
                    setRectifierCurrent_2(RECTIFIER1_GROUP2, (uint32_t) (current_t * 1000));
                    vTaskDelay(50);
                    rectifierPowerOn_2(RECTIFIER1_GROUP2);
                    vTaskDelay(50);
                    setRectifierVoltage_2(RECTIFIER2_GROUP2, (uint32_t) (voltage_t * 1000));
                    vTaskDelay(50);
                    setRectifierCurrent_2(RECTIFIER2_GROUP2, (uint32_t) (current_t * 1000));
                    vTaskDelay(50);
                    rectifierPowerOn_2(RECTIFIER2_GROUP2);
                    vTaskDelay(50);

                    if ((msg.RECTI_ON_OFF) == RECTIFIER_OFF) {
                        DC2_Contactor_Set();
                        DC1_Contactor_Set();
                        MERGER_Contactor_Set();
                        rectifierPowerOff(RECTIFIER2_GROUP2);
                        vTaskDelay(50);
                        rectifierPowerOff(RECTIFIER1_GROUP2);
                        vTaskDelay(50);
                        rectifierPowerOff_2(RECTIFIER2_GROUP1);
                        vTaskDelay(2);
                        rectifierPowerOff_2(RECTIFIER1_GROUP1);
                        vTaskDelay(2);
                    }
                    merger_flag = 1;
                    break;
            }
        }
        if (GUN1_CONNECTED == 1 && merger_flag == 0) {
            //            getRectifierStatus(RECTIFIER1_GROUP1);
            //            vTaskDelay(50);
            //            getRectifierStatus(RECTIFIER2_GROUP1);
            //            vTaskDelay(50);
            getRectifiertempMode(RECTIFIER1_GROUP1);
            vTaskDelay(50);
            getRectifiertempMode(RECTIFIER2_GROUP1);

        }
        if (GUN2_CONNECTED == 1 && merger_flag == 0) {
            //            getRectifierStatus_2(RECTIFIER1_GROUP2);
            //            vTaskDelay(50);
            //            getRectifierStatus_2(RECTIFIER2_GROUP2);
            //            vTaskDelay(50);
            getRectifiertemp2Mode(RECTIFIER1_GROUP2);
            vTaskDelay(50);
            getRectifiertemp2Mode(RECTIFIER2_GROUP2);
        }
        if (merger_flag == 1) {

            //            getRectifierStatus(RECTIFIER1_GROUP1);
            //            vTaskDelay(50);
            //            getRectifierStatus(RECTIFIER2_GROUP1);
            //            vTaskDelay(50);
            //            getRectifierStatus_2(RECTIFIER1_GROUP2);
            //            vTaskDelay(50);
            //            getRectifierStatus_2(RECTIFIER2_GROUP2);
            //            vTaskDelay(50);
            getRectifiertemp2Mode(RECTIFIER1_GROUP2);
            vTaskDelay(50);
            getRectifiertemp2Mode(RECTIFIER2_GROUP2);
            vTaskDelay(50);
            getRectifiertempMode(RECTIFIER1_GROUP1);
            vTaskDelay(50);
            getRectifiertempMode(RECTIFIER2_GROUP1);

        }
        vTaskDelay(100);
    }
}

void Start_SIMULATOR_TASK(void *argument) {
    _C102_Q _c102msg = {0};
    _C502_Q _c502msg = {0};
    _C10B_Q _c10bmsg = {0};
    _C50B_Q _c50bmsg = {0};
    _C107_Q _c107msg = {0};
    _C507_Q _c507msg = {0};
    _C109_Q _c109msg = {0};
    _C509_Q _c509msg = {0};
    for (;;) {

        switch (Simulator_buff[0]) {
            case 0xCC:
                SINGLE_GUN1_POWER = 0;
                SINGLE_GUN2_POWER = 0;
                if (Simulator_buff[1] == 0x0A) {
                    POWER_VALUE_X = 10000;
                }
                if (Simulator_buff[1] == 0x14) {
                    POWER_VALUE_X = 20000;
                }
                if (Simulator_buff[1] == 0x32) {
                    POWER_VALUE_X = 50000;
                }
                break;
            case 0xCE:
                SINGLE_GUN1_POWER = 1;
                if (Simulator_buff[1] == 0x0A) {
                    POWER_VALUE_X1 = 10000;
                }
                if (Simulator_buff[1] == 0x14) {
                    POWER_VALUE_X1 = 20000;
                }
                if (Simulator_buff[1] == 0x32) {
                    POWER_VALUE_X1 = 50000;
                }
                break;
            case 0xCD:
                SINGLE_GUN2_POWER = 1;
                if (Simulator_buff[1] == 0x0A) {
                    POWER_VALUE_X2 = 10000;
                }
                if (Simulator_buff[1] == 0x14) {
                    POWER_VALUE_X2 = 20000;
                }
                if (Simulator_buff[1] == 0x32) {
                    POWER_VALUE_X2 = 50000;
                }
                break;
            case 0xAA:
                NVIC_SystemReset();
                break;
            case 0xFF:
                CAN0_SleepModeEnter();

                break;
            case 0x0F:
                CAN0_SleepModeExit();
                CAN0_RxFifoCallbackRegister(CAN_RX_FIFO_0, APP_CAN_RxFifo0Callback, 0);

                break;
            case 0xF0:
                _c102msg._102_SECC_CP_t = seccCpOscillator_Duty_Cycle_ON;
                _c102msg.cpVoltage_msb = 0x5A;
                xQueueOverwrite(_C102_QUEUE, &_c102msg);
                break;
            case 0xF1:
                _c10bmsg._10B_SECC_STATUS3_t = seccStatus_Processing_SLAC;
                xQueueOverwrite(_C10B_QUEUE, &_c10bmsg);
                break;
            case 0xF2:
                _c10bmsg._10B_SECC_STATUS3_t = seccStatus_SDP;
                xQueueOverwrite(_C10B_QUEUE, &_c10bmsg);
                break;
            case 0xF3:
                _c10bmsg._10B_SECC_STATUS3_t = seccStatus_ServiceDiscovery;
                xQueueOverwrite(_C10B_QUEUE, &_c10bmsg);
                break;
            case 0xF4:
                _c107msg.evMaximumVoltageLimitlsb = Simulator_buff[9];
                _c107msg.evMaximumVoltageLimitmsb = Simulator_buff[8];
                xQueueOverwrite(_C107_QUEUE, &_c107msg);
                _c10bmsg._10B_SECC_STATUS3_t = seccStatus_ChargeParameterDiscovery;
                xQueueOverwrite(_C10B_QUEUE, &_c10bmsg);
                break;
            case 0xF5:
                _c10bmsg._10B_SECC_STATUS3_t = seccStatus_Cable_Check;
                xQueueOverwrite(_C10B_QUEUE, &_c10bmsg);

                _c102msg._102_SECC_CP_t = seccCpOscillator_Duty_Cycle_ON;
                _c102msg.cpVoltage_msb = 0x3C;
                xQueueOverwrite(_C102_QUEUE, &_c102msg);
                break;
                // F5 00 00 0A 00 00 00 00 A0 0F
            case 0xF6:
                _c109msg.targetCurrentlsb = Simulator_buff[4];
                _c109msg.targetCurrentmsb = Simulator_buff[3];
                _c109msg.targetVoltagelsb = Simulator_buff[9];
                _c109msg.targetVoltagemsb = Simulator_buff[8];
                xQueueOverwrite(_C109_QUEUE, &_c109msg);
                break;
            case 0xF7:
                _c10bmsg._10B_SECC_STATUS3_t = seccStatus_CurrentDemand;
                xQueueOverwrite(_C10B_QUEUE, &_c10bmsg);
                _c109msg.targetCurrentlsb = Simulator_buff[4];
                _c109msg.targetCurrentmsb = Simulator_buff[3];
                _c109msg.targetVoltagelsb = Simulator_buff[9];
                _c109msg.targetVoltagemsb = Simulator_buff[8];
                xQueueOverwrite(_C109_QUEUE, &_c109msg);
                break;
            case 0xF8:
                _c10bmsg._10B_SECC_STATUS3_t = seccStatus_PowerDelivery_Renotiate;
                xQueueOverwrite(_C10B_QUEUE, &_c10bmsg);
                break;
            case 0xF9:
                _c10bmsg._10B_SECC_STATUS3_t = seccStatus_SessionStop;
                xQueueOverwrite(_C10B_QUEUE, &_c10bmsg);
                break;
            case 0xFA:
                START_STOP_AR[0] = 1;
                START_STOP_AR[1] = 1;
                START_STOP_AR[2] = 0;
                break;
            case 0xFB:
                START_STOP_AR[0] = 1;
                START_STOP_AR[1] = 0;
                START_STOP_AR[2] = 1;
                break;
            case 0xE0:
                _c502msg._502_SECC_CP_t = seccCpOscillator_Duty_Cycle_ON;
                _c502msg.cpVoltage_msb = 0x5A;
                xQueueOverwrite(_C502_QUEUE, &_c502msg);
                break;
            case 0xE1:
                _c50bmsg._50B_SECC_STATUS3_t = seccStatus_Processing_SLAC;
                xQueueOverwrite(_C50B_QUEUE, &_c50bmsg);
                break;
            case 0xE2:
                _c50bmsg._50B_SECC_STATUS3_t = seccStatus_SDP;
                xQueueOverwrite(_C50B_QUEUE, &_c50bmsg);
                break;
            case 0xE3:
                _c50bmsg._50B_SECC_STATUS3_t = seccStatus_ServiceDiscovery;
                xQueueOverwrite(_C50B_QUEUE, &_c50bmsg);
                break;
            case 0xE4:
                _c507msg.evMaximumVoltageLimitlsb = Simulator_buff[9];
                _c507msg.evMaximumVoltageLimitmsb = Simulator_buff[8];
                xQueueOverwrite(_C507_QUEUE, &_c507msg);
                _c50bmsg._50B_SECC_STATUS3_t = seccStatus_ChargeParameterDiscovery;
                xQueueOverwrite(_C50B_QUEUE, &_c50bmsg);
                break;
            case 0xE5:
                _c50bmsg._50B_SECC_STATUS3_t = seccStatus_Cable_Check;
                xQueueOverwrite(_C50B_QUEUE, &_c50bmsg);

                _c502msg._502_SECC_CP_t = seccCpOscillator_Duty_Cycle_ON;
                _c502msg.cpVoltage_msb = 0x3C;
                xQueueOverwrite(_C502_QUEUE, &_c502msg);
                break;
                // F5 00 00 0A 00 00 00 00 A0 0F
            case 0xE6:
                _c509msg.targetCurrentlsb = Simulator_buff[4];
                _c509msg.targetCurrentmsb = Simulator_buff[3];
                _c509msg.targetVoltagelsb = Simulator_buff[9];
                _c509msg.targetVoltagemsb = Simulator_buff[8];
                xQueueOverwrite(_C509_QUEUE, &_c509msg);
                break;
            case 0xE7:
                _c50bmsg._50B_SECC_STATUS3_t = seccStatus_CurrentDemand;
                xQueueOverwrite(_C50B_QUEUE, &_c50bmsg);
                _c509msg.targetCurrentlsb = Simulator_buff[4];
                _c509msg.targetCurrentmsb = Simulator_buff[3];
                _c509msg.targetVoltagelsb = Simulator_buff[9];
                _c509msg.targetVoltagemsb = Simulator_buff[8];
                xQueueOverwrite(_C509_QUEUE, &_c509msg);
                break;
            case 0xE8:
                _c50bmsg._50B_SECC_STATUS3_t = seccStatus_PowerDelivery_Renotiate;
                xQueueOverwrite(_C50B_QUEUE, &_c50bmsg);
                break;
            case 0xE9:
                _c50bmsg._50B_SECC_STATUS3_t = seccStatus_SessionStop;
                xQueueOverwrite(_C50B_QUEUE, &_c50bmsg);
                break;
            case 0xEA:
                START_STOP_AR1[0] = 2;
                START_STOP_AR1[1] = 1;
                START_STOP_AR1[2] = 0;
                break;
            case 0xEB:
                START_STOP_AR1[0] = 2;
                START_STOP_AR1[1] = 0;
                START_STOP_AR1[2] = 1;

                break;
        }
        vTaskSuspend(simulatortask);
        vTaskDelay(1);
    }
}

void Start_SMOKE_LIMIT_TASK(void *argument) {
    COLOR1_Q color1msg;
    COLOR2_Q color2msg;
    CAN1_RECIEVE_Q msg;
    CAN2_RECIEVE_Q msg1;
    ESP_S_REC_TEMP_Q espdata;
    static uint8_t read_temp[4] = {0};
    BaseType_t xTaskWokenByReceive = pdFALSE;
    char buffer[70] = {0};
    static float GUN1_RECT_AVG_TEMP = 0.0, GUN2_RECT_AVG_TEMP = 0.0;
    char tilted[] = "CHARGER IS TILTED\r\n";
    char water_level[] = "WATER LEVEL IS HIGH\r\n";
    RECTIFIERS_TEMP_Q temp_data;
    for (;;) {

        if (!TILT_Get()) {
            //            SERCOM5_USART_Write(tilted, sizeof (tilted));
            //            while (!(SERCOM5_USART_TransmitComplete()))
            ;
        }
        if (WATER_LEVEL_Get()) {
            //            SERCOM5_USART_Write(water_level, sizeof (water_level));
            //            while (!(SERCOM5_USART_TransmitComplete()))
            ;
        }
        if (SMOKE_Get()) // Condition to check voltage level of SMOKE GPIO PIN.
        {
            ERROR_CODE_ARRAY[SMOKE_DETECTED_IDX] = 103;
            color1msg.COLOR1 = RED;
            color2msg.COLOR2 = RED2;
            Update_Smoke_Detected_Status(0x01);
            vTaskDelay(100);
            xQueueOverwrite(COLOR1_QUEUE, &color1msg);
            xQueueOverwrite(COLOR2_QUEUE, &color2msg);
        } else {
            ERROR_CODE_ARRAY[SMOKE_DETECTED_IDX] = 0;
            Update_Smoke_Detected_Status(0x00);
            vTaskDelay(100);
        }

        if (LIMIT_SWITCH_Get()) {
            ERROR_CODE_ARRAY[DOOR_OPEN_IDX] = 0;
            Update_Door_Status(0x00);
            vTaskDelay(100);
        } else {
            Update_Door_Status(0x01);
            vTaskDelay(100);
        }

        if (all_rec_status == 1) {
            all_rec_status = 0;
            xTimerStop(all_rec_timer, 10);
            xTimerStart(all_rec_timer, 30000);
            ERROR_CODE_ARRAY[ALL_RECTI_FAIL_IDX] = 0;
            Update_All_Rectifier_Comm_Fail_Status(0x00);
        }
        if ((rec1_status == 1) && (rec2_status == 1)) {
            ERROR_CODE_ARRAY[RECTIFIER1_COMM_FAIL_IDX] = 0;
        }
        if ((rec3_status == 1) && (rec4_status == 1)) {
            ERROR_CODE_ARRAY[RECTIFIER2_COMM_FAIL_IDX] = 0;
        }
        if (rec1_status == 1) {
            xTimerStop(rec1_timer, 10);
            rec1_status = 0;
            Update_Rectifier1_Comm_Fail_Status(0x00);
            memset(buffer, 0, sizeof (buffer));
            sprintf(buffer, "rectifier1_status : %d\r\n", rec1_status);
            SERCOM5_USART_Write(buffer, sizeof (buffer));
            while (!SERCOM5_USART_TransmitComplete());


            if (CURRENT_PLC1_STATE == _1_PLC_STATE_CURRENT_DEMAND_1) {
                xTimerStart(rec1_timer, 30000);
            }
        }
        if (rec2_status == 1) {
            xTimerStop(rec2_timer, 10);
            rec2_status = 0;
            Update_Rectifier2_Comm_Fail_Status(0x00);
            memset(buffer, 0, sizeof (buffer));
            sprintf(buffer, "rectifier2_status : %d\r\n", rec2_status);
            SERCOM5_USART_Write(buffer, sizeof (buffer));
            while (!SERCOM5_USART_TransmitComplete());
            if (CURRENT_PLC1_STATE == _1_PLC_STATE_CURRENT_DEMAND_1) {
                xTimerStart(rec2_timer, 40000);
            }
        }
        if (rec3_status == 1) {
            xTimerStop(rec3_timer, 10);
            rec3_status = 0;
            Update_Rectifier3_Comm_Fail_Status(0x00);
            memset(buffer, 0, sizeof (buffer));
            sprintf(buffer, "rectifier3_status : %d\r\n", rec3_status);
            SERCOM5_USART_Write(buffer, sizeof (buffer));
            while (!SERCOM5_USART_TransmitComplete());
            if (CURRENT_PLC2_STATE == _2_PLC_STATE_CURRENT_DEMAND_1) {
                xTimerStart(rec3_timer, 50000);
            }
        }
        if (rec4_status == 1) {

            xTimerStop(rec4_timer, 10);
            rec4_status = 0;
            Update_Rectifier4_Comm_Fail_Status(0x00);
            memset(buffer, 0, sizeof (buffer));
            sprintf(buffer, "rectifier4_status : %d\r\n", rec4_status);
            SERCOM5_USART_Write(buffer, sizeof (buffer));
            while (!SERCOM5_USART_TransmitComplete());
            if (CURRENT_PLC2_STATE == _2_PLC_STATE_CURRENT_DEMAND_1) {
                xTimerStart(rec4_timer, 60000);
            }
        }
        if (xQueueReceiveFromISR(REC_TEMP_QUEUE, &msg, &xTaskWokenByReceive)) {
            switch (msg.ID) {
                case Shift_rectifier_address1:

                    read_temp[0] = (uint8_t) ((int) (((msg.data[4] << 24) | (msg.data[5] << 16) | (msg.data[6] << 8) | (msg.data[7])) / 1000));
                    break;
                case Shift_rectifier_address2:
                    read_temp[1] = (uint8_t) ((int) (((msg.data[4] << 24) | (msg.data[5] << 16) | (msg.data[6] << 8) | (msg.data[7])) / 1000));
                    break;

            }
            if ((read_temp[0] > 0) && (read_temp[1] > 0)) {
                GUN1_RECT_AVG_TEMP = (read_temp[0] + read_temp[1]) >> 1;
                if (GUN1_RECT_AVG_TEMP != 0) {
                    Update_REC_GUN1_Temp((uint16_t) GUN1_RECT_AVG_TEMP);
                    espdata.rec_group1 = (uint8_t) ((int) (GUN1_RECT_AVG_TEMP));
                }
                //                vTaskDelay(50);
                //                memset(buffer, 0, sizeof (buffer));
                //                sprintf(buffer, "GUN1_TEMP : %f\r\n", GUN1_RECT_AVG_TEMP);
                //                SERCOM5_USART_Write(buffer, sizeof (buffer));
                //                while (!(SERCOM5_USART_TransmitComplete()));
            }

        }

        if (xQueueReceiveFromISR(REC2_TEMP_QUEUE, &msg1, &xTaskWokenByReceive)) {
            switch (msg1.ID) {
                case Shift_rectifier_address3:
                    read_temp[2] = (uint8_t) ((int) (((msg1.data[4] << 24) | (msg1.data[5] << 16) | (msg1.data[6] << 8) | (msg1.data[7])) / 1000));

                    break;
                case Shift_rectifier_address4:

                    read_temp[3] = (uint8_t) ((int) (((msg1.data[4] << 24) | (msg1.data[5] << 16) | (msg1.data[6] << 8) | (msg1.data[7])) / 1000));

                    break;

            }
            if ((read_temp[2] > 0) && (read_temp[3] > 0)) {

                GUN2_RECT_AVG_TEMP = (read_temp[2] + read_temp[3]) >> 1;
                if (GUN2_RECT_AVG_TEMP != 0) {
                    Update_REC_GUN2_Temp((uint16_t) GUN2_RECT_AVG_TEMP);
                    espdata.rec_group2 = (uint8_t) ((int) (GUN2_RECT_AVG_TEMP));
                }
                //                vTaskDelay(50);
                //                memset(buffer, 0, sizeof (buffer));
                //                sprintf(buffer, "GUN2_TEMP : %f\r\n", GUN2_RECT_AVG_TEMP);
                //                SERCOM5_USART_Write(buffer, sizeof (buffer));
                //                while (!(SERCOM5_USART_TransmitComplete()));
            }

        }


        memcpy(temp_data.TEMPS, read_temp, 4);
        xQueueOverwrite(RECTIFIERS_TEMP_QUEUE, &temp_data);
        xQueueOverwrite(ESP_S_REC_TEMP_QUEUE, &espdata);




        vTaskDelay(5000);
    }
}

void Start_MAINS_TASK(void *argument) {
    //    char BUFFER[30] = {0};
    uint8_t instance = 0;
    for (;;) {

        if (!MAINS_SWITCH_Get()) {
            page_change[2] = 0;
            xTimerStop(live_mains_timer, 10);
            xTimerStart(live_mains_timer, 20000);
            if (instance == 0) {
                Update_Mains_Fail_Status(0x00);
                instance = 1;
            }
            if (power_down == 1) {
                mains_fail_led = 0;
                power_down = 0;
                Update_Mains_Fail_Status(0x00);
                NVIC_SystemReset();
            }
        }
        WDT_Clear();
        vTaskDelay(2);
    }
}

void Start_LED_TASK(void *argument) {
    LED1_Q led1data;
    //    LED2_Q led2data;
    static uint8_t colo_state = 0;
    static uint8_t colo_state1 = 0;
    static uint8_t GUN_state = 0;
    //    static uint8_t GUN2_state = 0;
    static uint8_t Battery_icon1 = 0;
    static uint8_t Battery_icon2 = 0;
    COLOR1_Q color1msg;
    COLOR2_Q color2msg;
    for (;;) {

        if (xQueueReceive(LED1_QUEUE, &led1data, 0)) {
            GUN_state = led1data.GUN;
        }
        //        if (xQueueReceive(LED2_QUEUE, &led2data, 0)) {
        //            GUN2_state = led2data.GUN2;
        //        }
        switch (GUN1_CONNECTED) {
            case 0:
                if (GUN_state == OFFLINE) {
                    color1msg.COLOR1 = MAGENTA;

                    xQueueOverwrite(COLOR1_QUEUE, &color1msg);

                } else if (GUN_state == ONLINE) {
                    color1msg.COLOR1 = WHITE;

                    xQueueOverwrite(COLOR1_QUEUE, &color1msg);
                }
                break;
            case 1:
                if (CURRENT_PLC1_STATE <= _1_PLC_STATE_PRE_CHARGE) {
                    color1msg.COLOR1 = GREEN;

                    xQueueOverwrite(COLOR1_QUEUE, &color1msg);
                }
                if (CURRENT_PLC1_STATE == _1_PLC_STATE_CURRENT_DEMAND_1) {
                    switch (colo_state) {
                        case 0:
                            colo_state = 1;
                            color1msg.COLOR1 = NO_COLOR;
                            xQueueOverwrite(COLOR1_QUEUE, &color1msg);
                            break;
                        case 1:
                            color1msg.COLOR1 = GREEN;
                            colo_state = 0;
                            xQueueOverwrite(COLOR1_QUEUE, &color1msg);
                            break;
                    }
                    switch (Battery_icon1) {
                        case 0:
                            Update_GUN1_Battery_Percent(0);
                            Battery_icon1 = 1;
                            break;
                        case 1:
                            Update_GUN1_Battery_Percent(3);
                            Battery_icon1 = 2;
                            break;
                        case 2:
                            Update_GUN1_Battery_Percent(6);
                            Battery_icon1 = 0;
                            break;
                    }
                }
                break;

        }
        switch (GUN2_CONNECTED) {
            case 0:
                if (GUN_state == OFFLINE) {
                    color2msg.COLOR2 = MAGENTA2;

                    xQueueOverwrite(COLOR2_QUEUE, &color2msg);

                } else if (GUN_state == ONLINE) {
                    color2msg.COLOR2 = WHITE2;

                    xQueueOverwrite(COLOR2_QUEUE, &color2msg);
                }
                break;
            case 1:
                if (CURRENT_PLC2_STATE <= _2_PLC_STATE_PRE_CHARGE) {
                    color2msg.COLOR2 = GREEN2;

                    xQueueOverwrite(COLOR2_QUEUE, &color2msg);
                }
                if (CURRENT_PLC2_STATE == _2_PLC_STATE_CURRENT_DEMAND_1) {
                    switch (colo_state1) {
                        case 0:
                            colo_state1 = 1;
                            color2msg.COLOR2 = NO_COLOR;
                            xQueueOverwrite(COLOR2_QUEUE, &color2msg);
                            break;
                        case 1:
                            color2msg.COLOR2 = GREEN2;
                            colo_state1 = 0;
                            xQueueOverwrite(COLOR2_QUEUE, &color2msg);
                            break;
                    }
                    switch (Battery_icon2) {
                        case 0:
                            Update_GUN2_Battery_Percent(0);
                            Battery_icon2 = 1;
                            break;
                        case 1:
                            Update_GUN2_Battery_Percent(3);
                            Battery_icon2 = 2;
                            break;
                        case 2:
                            Update_GUN2_Battery_Percent(6);
                            Battery_icon2 = 0;
                            break;
                    }
                }
                break;

        }



        /* if (GUN1_state == 3) {
             color1msg.COLOR1 = GREEN;
             xQueueOverwrite(COLOR1_QUEUE, &color1msg);
         }
         if (GUN2_state == 4) {
             color2msg.COLOR2 = GREEN2;
             xQueueOverwrite(COLOR2_QUEUE, &color2msg);
         }
         if (GUN1_state == 1) {
             switch (colo_state) {
                 case 0:
                     colo_state = 1;
                     color1msg.COLOR1 = NO_COLOR;
                     xQueueOverwrite(COLOR1_QUEUE, &color1msg);
                     break;
                 case 1:
                     color1msg.COLOR1 = GREEN;
                     colo_state = 0;
                     xQueueOverwrite(COLOR1_QUEUE, &color1msg);
                     break;
             }
             switch (Battery_icon1) {
                 case 0:
                     Update_GUN1_Battery_Percent(0);
                     Battery_icon1 = 1;
                     break;
                 case 1:
                     Update_GUN1_Battery_Percent(3);
                     Battery_icon1 = 2;
                     break;
                 case 2:
                     Update_GUN1_Battery_Percent(6);
                     Battery_icon1 = 0;
                     break;
             }
         }
         if (GUN2_state == 1) {
             switch (colo_state1) {
                 case 0:
                     colo_state1 = 1;
                     color2msg.COLOR2 = NO_COLOR2;
                     xQueueOverwrite(COLOR2_QUEUE, &color2msg);
                     break;
                 case 1:
                     color2msg.COLOR2 = GREEN2;
                     colo_state1 = 0;
                     xQueueOverwrite(COLOR2_QUEUE, &color2msg);
                     break;
             }
             switch (Battery_icon2) {
                 case 0:
                     Update_GUN2_Battery_Percent(0);
                     Battery_icon2 = 1;
                     break;
                 case 1:
                     Update_GUN2_Battery_Percent(3);
                     Battery_icon2 = 2;
                     break;
                 case 2:
                     Update_GUN2_Battery_Percent(6);
                     Battery_icon2 = 0;

                     break;
             }
         }*/
        vTaskDelay(1000);
    }
}

void Start_GUN1_PARAM_TASK(void *argument) {
    static uint8_t count = 0;
    for (;;) {

        count = count + 1;
        CURRENT_PAGE = GUN1_SUMMARY_PAGE;
        Change_Page_to(CURRENT_PAGE);
        Change_gun1_status_to(CHARGING_COMPLETED);
        if (GUN1_summary_close_flag == 1) {
            count = 5;
        }
        if (count == 5) {

            vTaskSuspend(FAN_TASKHandle);
            FAN_ON(65535);
            START_BY2 = 0;
            STOP_BY = 0;
            BOOKING_ID1 = 0;
            Update_GUN1_Initial_SOC(0);
            Update_GUN1_Battery_SOC(0);
            Update_GUN1_Demand_Current(0);
            Update_GUN1_Demand_Voltage(0);
            Update_GUN1_Voltage(0);
            Update_GUN1_Current(0);
            Update_GUN1_Duration(0);
            Update_GUN1_Battery_Percent(0);
            Update_GUN1_Session_End_Reason(0x00);
            count = 0;
            GUN1_summary_close_flag = 0;
            vTaskResume(_1_PLC_MANAGE_TASKHandle);
            vTaskSuspend(GUN1_PARAM_TASKHandle);
        }
        vTaskDelay(10000);
    }
}

void Start_GUN2_PARAM_TASK(void *argument) {
    static uint8_t count = 0;
    for (;;) {

        count = count + 1;
        CURRENT_PAGE = GUN2_SUMMARY_PAGE;
        Change_Page_to(CURRENT_PAGE);
        Change_gun2_status_to(CHARGING_COMPLETED);
        if (GUN2_summary_close_flag == 1) {
            count = 5;
        }
        if (count == 5) {

            vTaskSuspend(FAN_TASKHandle);
            FAN_ON(65535);
            START_BY2 = 0;
            STOP_BY = 0;
            BOOKING_ID2 = 0;
            Update_GUN2_Initial_SOC(0);
            Update_GUN2_Battery_SOC(0);
            Update_GUN2_Demand_Current(0);
            Update_GUN2_Demand_Voltage(0);
            Update_GUN2_Voltage(0);
            Update_GUN2_Current(0);
            Update_GUN2_Duration(0);
            Update_GUN2_Battery_Percent(0);
            Update_GUN2_Session_End_Reason(0x00);
            count = 0;
            GUN2_summary_close_flag = 0;
            vTaskResume(_2_PLC_MANAGE_TASKHandle);
            vTaskSuspend(GUN2_PARAM_TASKHandle);
        }
        vTaskDelay(10000);
    }
}

void Start_FLASH_WRITE_TASK(void *argument) {
    FLASH_WRITE_Q flashmsg;
    uint32_t BT_DATA_ARRAY_0_127[128] = {0};
    //    uint32_t BT_DATA_ARRAY_128_255[128] = {0};
    //    uint32_t BT_DATA_ARRAY_256_383[128] = {0};
    //    uint32_t BT_DATA_ARRAY_383_512[128] = {0};
    uint32_t CHARGING_DATA_ARRAY_1_16[128] = {0};
    uint32_t CHARGING_DATA_ARRAY_17_32[128] = {0};
    uint32_t CHARGING_DATA_ARRAY_33_48[128] = {0};
    uint32_t CHARGING_DATA_ARRAY_49_64[128] = {0};
    for (;;) {

        if (xQueueReceive(FLASH_WRITE_QUEUE, &flashmsg, 0)) {
            if (flashmsg.WHAT_TYPE_OF_DATA == BT_DATA) {
                memcpy(BT_DATA_ARRAY_0_127, (void *) FLASH_START_ADDRESS_BT, 512);
                while (NVMCTRL_IsBusy())
                    ;
                switch (flashmsg.DATA_IDX) {
                    case BLE_ID_IDX:
                        memcpy(&BT_DATA_ARRAY_0_127[BLE_ID_IDX], flashmsg.ID_DATA, 32);
                        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        break;
                    case OCPP_ID_IDX:
                        memcpy(&BT_DATA_ARRAY_0_127[OCPP_ID_IDX], flashmsg.ID_DATA, 32);
                        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        break;
                    case DLB_POWER_VALUES_IDX:
                        BT_DATA_ARRAY_0_127[DLB_POWER_VALUES_IDX] = flashmsg.DATA_t;
                        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        break;
                    case PRICE_VALUE_IDX:
                        BT_DATA_ARRAY_0_127[PRICE_VALUE_IDX] = flashmsg.DATA_t;
                        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        Update_Unit_price((uint16_t) BT_DATA_ARRAY_0_127[PRICE_VALUE_IDX]);
                        break;
                    case GUN1_CONFIG_IDX:
                        BT_DATA_ARRAY_0_127[GUN1_CONFIG_IDX] = flashmsg.DATA_t;
                        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        GUN1_ENABLE_DISABLE = BT_DATA_ARRAY_0_127[GUN1_CONFIG_IDX];
                        if (GUN1_ENABLE_DISABLE == DEFAULT_GUN1_DISABLE) {
                            vTaskSuspend(_1_PLC_MANAGE_TASKHandle);
                            Change_gun1_status_to(UNAVAILABLE);
                        }
                        if (GUN1_ENABLE_DISABLE == DEFAULT_GUN1_ENABLE) {
                            vTaskResume(_1_PLC_MANAGE_TASKHandle);
                            Change_gun1_status_to(AVAILABLE);
                        }
                        break;
                    case GUN2_CONFIG_IDX:
                        BT_DATA_ARRAY_0_127[GUN2_CONFIG_IDX] = flashmsg.DATA_t;
                        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        GUN2_ENABLE_DISABLE = BT_DATA_ARRAY_0_127[GUN2_CONFIG_IDX];
                        if (GUN2_ENABLE_DISABLE == DEFAULT_GUN2_DISABLE) {
                            vTaskSuspend(_2_PLC_MANAGE_TASKHandle);
                            Change_gun2_status_to(UNAVAILABLE);
                        }
                        if (GUN2_ENABLE_DISABLE == DEFAULT_GUN2_ENABLE) {
                            vTaskResume(_2_PLC_MANAGE_TASKHandle);
                            Change_gun2_status_to(AVAILABLE);
                        }
                        break;
                    case SYSTEM_TEMP_LIMIT_IDX:
                        BT_DATA_ARRAY_0_127[SYSTEM_TEMP_LIMIT_IDX] = flashmsg.DATA_t;
                        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        DEFAULT_BODY_TEMP_UPPER_LIMIT_t = BT_DATA_ARRAY_0_127[SYSTEM_TEMP_LIMIT_IDX];
                        break;
                    case NE_VOLT_LIMIT_IDX:
                        BT_DATA_ARRAY_0_127[NE_VOLT_LIMIT_IDX] = flashmsg.DATA_t;
                        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        DEFAULT_NE_VOLT_LIMIT_t = BT_DATA_ARRAY_0_127[NE_VOLT_LIMIT_IDX];
                        break;
                    case AC_OVER_VOLT_LIMIT_IDX:
                        BT_DATA_ARRAY_0_127[AC_OVER_VOLT_LIMIT_IDX] = flashmsg.DATA_t;
                        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        AC_OVER_VOLT_LIMIT_t = BT_DATA_ARRAY_0_127[AC_OVER_VOLT_LIMIT_IDX];
                        break;
                    case AC_UNDER_VOLT_LIMIT_IDX:
                        BT_DATA_ARRAY_0_127[AC_OVER_VOLT_LIMIT_IDX] = flashmsg.DATA_t;
                        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        AC_UNDER_VOLT_LIMIT_t = BT_DATA_ARRAY_0_127[AC_UNDER_VOLT_LIMIT_IDX];
                        break;
                    case GUN1_TEMPERATURE_LIMIT_IDX:
                        BT_DATA_ARRAY_0_127[GUN1_TEMPERATURE_LIMIT_IDX] = flashmsg.DATA_t;
                        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        DEFAULT_GUN1_TEMP_LIMIT_t = BT_DATA_ARRAY_0_127[GUN1_TEMPERATURE_LIMIT_IDX];
                        break;
                    case GUN2_TEMPERATURE_LIMIT_IDX:
                        BT_DATA_ARRAY_0_127[GUN2_TEMPERATURE_LIMIT_IDX] = flashmsg.DATA_t;
                        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        DEFAULT_GUN2_TEMP_LIMIT_t = BT_DATA_ARRAY_0_127[GUN2_TEMPERATURE_LIMIT_IDX];
                        break;
                    case GUN_TEMPERATURE_POINT_CLEAR_IDX:
                        BT_DATA_ARRAY_0_127[GUN_TEMPERATURE_POINT_CLEAR_IDX] = flashmsg.DATA_t;
                        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        DEFAULT_GUN_TEMPERATURE_POINT_CLEAR_VALUE_t = BT_DATA_ARRAY_0_127[GUN_TEMPERATURE_POINT_CLEAR_IDX];
                        break;
                    case MAX_POWER_CAPACITY_IDX:
                        BT_DATA_ARRAY_0_127[MAX_POWER_CAPACITY_IDX] = flashmsg.DATA_t;
                        POWER_VALUE_X = BT_DATA_ARRAY_0_127[MAX_POWER_CAPACITY_IDX] * 10000;
                        BT_DATA_ARRAY_0_127[DLB_POWER_VALUES_IDX] = ZERO_DATA | (((uint32_t) POWER_VALUE_X / 1000) << 24) | (((uint32_t) POWER_VALUE_X / 1000) << 16) | ((uint32_t) SINGLE_GUN2_POWER << 8) | ((uint32_t) SINGLE_GUN1_POWER);

                        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        break;
                    case CHARGER_TYPE_SIN_DUAL_IDX:
                        BT_DATA_ARRAY_0_127[CHARGER_TYPE_SIN_DUAL_IDX] = flashmsg.DATA_t;
                        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        DEFAULT_CHARGER_TYPE_t = BT_DATA_ARRAY_0_127[CHARGER_TYPE_SIN_DUAL_IDX];
                        break;
                    case ACEM_ALARM_IDX:
                        BT_DATA_ARRAY_0_127[ACEM_ALARM_IDX] = flashmsg.DATA_t;
                        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        DEFAULT_ACEM_ALARM_t = BT_DATA_ARRAY_0_127[ACEM_ALARM_IDX];
                        break;

                    case DCEM1_ALARM_IDX:
                        BT_DATA_ARRAY_0_127[DCEM1_ALARM_IDX] = flashmsg.DATA_t;
                        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        DEFAULT_DCEM_GUN1_ALARM_t = BT_DATA_ARRAY_0_127[DCEM1_ALARM_IDX];
                        break;

                    case DCEM2_ALARM_IDX:
                        BT_DATA_ARRAY_0_127[DCEM2_ALARM_IDX] = flashmsg.DATA_t;
                        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        DEFAULT_DCEM_GUN2_ALARM_t = BT_DATA_ARRAY_0_127[DCEM2_ALARM_IDX];
                        break;

                    case DOOR_ALARM_IDX:
                        BT_DATA_ARRAY_0_127[DOOR_ALARM_IDX] = flashmsg.DATA_t;
                        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        DEFAULT_DOOR_ALARM_t = BT_DATA_ARRAY_0_127[DOOR_ALARM_IDX];
                        break;

                    case IMD1_ALARM_IDX:
                        BT_DATA_ARRAY_0_127[IMD1_ALARM_IDX] = flashmsg.DATA_t;
                        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        DEFAULT_IMD1_ALARM_t = BT_DATA_ARRAY_0_127[IMD1_ALARM_IDX];
                        break;

                    case IMD2_ALARM_IDX:
                        BT_DATA_ARRAY_0_127[IMD2_ALARM_IDX] = flashmsg.DATA_t;
                        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        DEFAULT_IMD2_ALARM_t = BT_DATA_ARRAY_0_127[IMD2_ALARM_IDX];
                        break;

                    case SPD_ALARM_IDX:
                        BT_DATA_ARRAY_0_127[SPD_ALARM_IDX] = flashmsg.DATA_t;
                        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        DEFAULT_SPD_ALARM_t = BT_DATA_ARRAY_0_127[SPD_ALARM_IDX];
                        break;

                    case SMOKE_ALARM_IDX:
                        BT_DATA_ARRAY_0_127[SMOKE_ALARM_IDX] = flashmsg.DATA_t;
                        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        DEFAULT_SMOKE_ALARM_t = BT_DATA_ARRAY_0_127[SMOKE_ALARM_IDX];
                        break;

                    case GUN1_TEMP_ALARM_IDX:
                        BT_DATA_ARRAY_0_127[GUN1_TEMP_ALARM_IDX] = flashmsg.DATA_t;
                        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        DEFAULT_GUN1_TEMP_ALARM_t = BT_DATA_ARRAY_0_127[GUN1_TEMP_ALARM_IDX];
                        break;

                    case GUN2_TEMP_ALARM_IDX:
                        BT_DATA_ARRAY_0_127[GUN2_TEMP_ALARM_IDX] = flashmsg.DATA_t;
                        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        DEFAULT_GUN2_TEMP_ALARM_t = BT_DATA_ARRAY_0_127[GUN2_TEMP_ALARM_IDX];
                        break;

                    case LED_FAULT_ALARM_IDX:
                        BT_DATA_ARRAY_0_127[LED_FAULT_ALARM_IDX] = flashmsg.DATA_t;
                        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        DEFAULT_LED_FAULT_ALARM_t = BT_DATA_ARRAY_0_127[LED_FAULT_ALARM_IDX];
                        break;

                    case RFID_FAULT_ALARM_IDX:
                        BT_DATA_ARRAY_0_127[RFID_FAULT_ALARM_IDX] = flashmsg.DATA_t;
                        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        DEFAULT_RFID_FAULT_ALARM_t = BT_DATA_ARRAY_0_127[RFID_FAULT_ALARM_IDX];
                        break;
                    case ACEM_TYPE_IDX:
                        BT_DATA_ARRAY_0_127[ACEM_TYPE_IDX] = flashmsg.DATA_t;
                        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
                        while (NVMCTRL_IsBusy())
                            ;
                        DEFAULT_RFID_FAULT_ALARM_t = BT_DATA_ARRAY_0_127[ACEM_TYPE_IDX];
                        break;
                }
            }
            if (flashmsg.WHAT_TYPE_OF_DATA == CHARGING_DATA) {
                memset(CHARGING_DATA_ARRAY_1_16, 0, sizeof (CHARGING_DATA_ARRAY_1_16));
                memset(CHARGING_DATA_ARRAY_17_32, 0, sizeof (CHARGING_DATA_ARRAY_17_32));
                memset(CHARGING_DATA_ARRAY_33_48, 0, sizeof (CHARGING_DATA_ARRAY_33_48));
                memset(CHARGING_DATA_ARRAY_49_64, 0, sizeof (CHARGING_DATA_ARRAY_49_64));
                //WDT_Clear();
                memcpy(&CHARGING_DATA_ARRAY_1_16[8], (void *) (FLASH_START_ADDRESS_CHARGING_SESSION_1_62), 480);
                while (NVMCTRL_IsBusy());
                memcpy(CHARGING_DATA_ARRAY_17_32, (void *) (FLASH_START_ADDRESS_CHARGING_SESSION_1_62 + FLASH_WRITE_LIMIT - FLASH_WRITE_BACK_LIMIT), 32);
                while (NVMCTRL_IsBusy());
                memcpy(&CHARGING_DATA_ARRAY_17_32[8], (void *) (FLASH_START_ADDRESS_CHARGING_SESSION_1_62 + FLASH_WRITE_LIMIT), 480);
                while (NVMCTRL_IsBusy());
                memcpy(CHARGING_DATA_ARRAY_33_48, (void *) (FLASH_START_ADDRESS_CHARGING_SESSION_1_62 + FLASH_WRITE_LIMIT1 - FLASH_WRITE_BACK_LIMIT), 32);
                while (NVMCTRL_IsBusy());
                memcpy(&CHARGING_DATA_ARRAY_33_48[8], (void *) (FLASH_START_ADDRESS_CHARGING_SESSION_1_62 + FLASH_WRITE_LIMIT1), 480);
                while (NVMCTRL_IsBusy());
                memcpy(CHARGING_DATA_ARRAY_49_64, (void *) (FLASH_START_ADDRESS_CHARGING_SESSION_1_62 + FLASH_WRITE_LIMIT2 - FLASH_WRITE_BACK_LIMIT), 32);
                while (NVMCTRL_IsBusy());
                memcpy(&CHARGING_DATA_ARRAY_49_64[8], (void *) (FLASH_START_ADDRESS_CHARGING_SESSION_1_62 + FLASH_WRITE_LIMIT2), 432);
                while (NVMCTRL_IsBusy());
                //WDT_Clear();
                CHARGING_DATA_ARRAY_1_16[0] = flashmsg.BOOKING_ID;
                CHARGING_DATA_ARRAY_1_16[1] = flashmsg.START_DATE;
                CHARGING_DATA_ARRAY_1_16[2] = flashmsg.STOP_DATE;
                CHARGING_DATA_ARRAY_1_16[3] = flashmsg.START_TIME;
                CHARGING_DATA_ARRAY_1_16[4] = flashmsg.STOP_TIME;
                CHARGING_DATA_ARRAY_1_16[5] = flashmsg.SESSION_STOP_REASON_AND_DURATION;
                CHARGING_DATA_ARRAY_1_16[6] = flashmsg.START_SOC_AND_END_SOC;
                CHARGING_DATA_ARRAY_1_16[7] = flashmsg.UNIT_CONSUMED_AND_CONN_ID;
                NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_CHARGING_SESSION_1_62);
                while (NVMCTRL_IsBusy());
                NVMCTRL_PageWrite((uint32_t *) CHARGING_DATA_ARRAY_1_16, (uint32_t) FLASH_START_ADDRESS_CHARGING_SESSION_1_62);
                while (NVMCTRL_IsBusy());
                //WDT_Clear();
                NVMCTRL_PageWrite((uint32_t *) CHARGING_DATA_ARRAY_17_32, (uint32_t) (FLASH_START_ADDRESS_CHARGING_SESSION_1_62 + FLASH_WRITE_LIMIT));
                while (NVMCTRL_IsBusy());
                //WDT_Clear();
                NVMCTRL_PageWrite((uint32_t *) CHARGING_DATA_ARRAY_33_48, (uint32_t) (FLASH_START_ADDRESS_CHARGING_SESSION_1_62 + FLASH_WRITE_LIMIT1));
                while (NVMCTRL_IsBusy());
                //WDT_Clear();
                NVMCTRL_PageWrite((uint32_t *) CHARGING_DATA_ARRAY_49_64, (uint32_t) (FLASH_START_ADDRESS_CHARGING_SESSION_1_62 + FLASH_WRITE_LIMIT2));

                while (NVMCTRL_IsBusy());
            }
            //WDT_Clear();
        }
        vTaskSuspend(FLASH_WRITE_TASKHandle);
        vTaskDelay(1);
    }
}

void Start_FAN_TASK(void *argument) {
    RECTIFIERS_TEMP_Q temp_data;
    uint8_t i;
    uint8_t max = 0;
    for (;;) {
        if (xQueueReceive(RECTIFIERS_TEMP_QUEUE, &temp_data, 0)) {
            max = 0;
            for (i = 0; i < 4; i++) {
                if (temp_data.TEMPS[i] > max) {
                    max = temp_data.TEMPS[i];
                }
            }
            if (max <= 25) {
                FAN_ON(40000);
            } else if (max <= 35) {
                FAN_ON(20000);
            } else if (max <= 45) {
                FAN_ON(10000);
            } else if (max <= 55) {
                FAN_ON(1000);
            } else if (max <= 65) {
                FAN_ON(10);
            }
        }
        vTaskDelay(1000);
    }
}

void Start_FLASH_READ_TASK(void *argument) {
    FLASH_READ_Q flashreadmsg;
    ESP_S_BT_Q espdata;
    uint32_t BT_DATA_ARRAY_0_127[128] = {0};
    //    uint32_t BT_DATA_ARRAY_128_255[128] = {0};
    //    uint32_t BT_DATA_ARRAY_256_383[128] = {0};
    //    uint32_t BT_DATA_ARRAY_383_512[128] = {0};
    uint32_t CHARGING_DATA_ARRAY_1_16[128] = {0};
    uint32_t CHARGING_DATA_ARRAY_17_32[128] = {0};
    uint32_t CHARGING_DATA_ARRAY_33_48[128] = {0};
    uint32_t CHARGING_DATA_ARRAY_49_64[128] = {0};
    static int count = 0;
    for (;;) {

        if (xQueueReceive(FLASH_READ_QUEUE, &flashreadmsg, 0)) {
            if (flashreadmsg.WHO_IS_READING == ESP_READ) {
                memset(BT_DATA_ARRAY_0_127, 0, sizeof (BT_DATA_ARRAY_0_127));
                memcpy(BT_DATA_ARRAY_0_127, (void *) FLASH_START_ADDRESS_BT, 512);
                while (NVMCTRL_IsBusy())
                    ;
                espdata.IDX = flashreadmsg.BT_READ_IDX;
                espdata.IDX_DATA = BT_DATA_ARRAY_0_127[flashreadmsg.BT_READ_IDX];
                xQueueOverwrite(ESP_S_BT_QUEUE, &espdata);
            }
            if (flashreadmsg.WHO_IS_READING == HMI_READ) {
                if (flashreadmsg.COUNT_READ_INC == 0) {
                    count = 0;
                    memset(CHARGING_DATA_ARRAY_1_16, 0, sizeof (CHARGING_DATA_ARRAY_1_16));
                    memset(CHARGING_DATA_ARRAY_17_32, 0, sizeof (CHARGING_DATA_ARRAY_17_32));
                    memset(CHARGING_DATA_ARRAY_33_48, 0, sizeof (CHARGING_DATA_ARRAY_33_48));
                    memset(CHARGING_DATA_ARRAY_49_64, 0, sizeof (CHARGING_DATA_ARRAY_49_64));
                    //WDT_Clear();
                    memcpy(CHARGING_DATA_ARRAY_1_16, (void *) (FLASH_START_ADDRESS_CHARGING_SESSION_1_62), 512);
                    while (NVMCTRL_IsBusy())
                        ;
                    memcpy(CHARGING_DATA_ARRAY_17_32, (void *) (FLASH_START_ADDRESS_CHARGING_SESSION_1_62 + FLASH_WRITE_LIMIT), 512);
                    while (NVMCTRL_IsBusy())
                        ;
                    memcpy(CHARGING_DATA_ARRAY_33_48, (void *) (FLASH_START_ADDRESS_CHARGING_SESSION_1_62 + FLASH_WRITE_LIMIT1), 512);
                    while (NVMCTRL_IsBusy())
                        ;
                    memcpy(CHARGING_DATA_ARRAY_49_64, (void *) (FLASH_START_ADDRESS_CHARGING_SESSION_1_62 + FLASH_WRITE_LIMIT2), 464);
                    while (NVMCTRL_IsBusy())
                        ;
                    //WDT_Clear();
                } else if (flashreadmsg.COUNT_READ_INC == 1) {
                    count = count + 1;
                    if (count == 8) {
                        count = 0;
                    }
                } else if (flashreadmsg.COUNT_READ_INC == 2) {
                    count = count - 1;
                    if (count < 0) {
                        count = 7;
                    }
                }
                switch (count) {
                    case 0:

                        Write_Sno_for_page1();
                        Update_page1_data(CHARGING_DATA_ARRAY_1_16);
                        //WDT_Clear();
                        switch (flashreadmsg.PAGE_VIEW) {
                            case 1:
                                Update_page1_line1_data(CHARGING_DATA_ARRAY_1_16);
                                //WDT_Clear();
                                break;
                            case 2:
                                Update_page1_line2_data(CHARGING_DATA_ARRAY_1_16);
                                //WDT_Clear();
                                break;
                            case 3:
                                Update_page1_line3_data(CHARGING_DATA_ARRAY_1_16);
                                //WDT_Clear();
                                break;
                            case 4:
                                Update_page1_line4_data(CHARGING_DATA_ARRAY_1_16);
                                //WDT_Clear();
                                break;
                            case 5:
                                Update_page1_line5_data(CHARGING_DATA_ARRAY_1_16);
                                //WDT_Clear();
                                break;
                            case 6:
                                Update_page1_line6_data(CHARGING_DATA_ARRAY_1_16);
                                //WDT_Clear();
                                break;
                            case 7:
                                Update_page1_line7_data(CHARGING_DATA_ARRAY_1_16);
                                //WDT_Clear();
                                break;
                            case 8:
                                Update_page1_line8_data(CHARGING_DATA_ARRAY_1_16);
                                //WDT_Clear();
                                break;
                        }
                        break;
                    case 1:
                        Write_Sno_for_page2();
                        Update_page2_data(CHARGING_DATA_ARRAY_1_16);
                        //WDT_Clear();
                        switch (flashreadmsg.PAGE_VIEW) {
                            case 1:
                                Update_page2_line1_data(CHARGING_DATA_ARRAY_1_16);
                                //WDT_Clear();
                                break;
                            case 2:
                                Update_page2_line2_data(CHARGING_DATA_ARRAY_1_16);
                                //WDT_Clear();
                                break;
                            case 3:
                                Update_page2_line3_data(CHARGING_DATA_ARRAY_1_16);
                                //WDT_Clear();
                                break;
                            case 4:
                                Update_page2_line4_data(CHARGING_DATA_ARRAY_1_16);
                                //WDT_Clear();
                                break;
                            case 5:
                                Update_page2_line5_data(CHARGING_DATA_ARRAY_1_16);
                                //WDT_Clear();
                                break;
                            case 6:
                                Update_page2_line6_data(CHARGING_DATA_ARRAY_1_16);
                                //WDT_Clear();
                                break;
                            case 7:
                                Update_page2_line7_data(CHARGING_DATA_ARRAY_1_16);
                                //WDT_Clear();
                                break;
                            case 8:
                                Update_page2_line8_data(CHARGING_DATA_ARRAY_1_16);
                                //WDT_Clear();
                                break;
                        }
                        break;
                    case 2:
                        Write_Sno_for_page3();
                        Update_page3_data(CHARGING_DATA_ARRAY_17_32);
                        //WDT_Clear();
                        switch (flashreadmsg.PAGE_VIEW) {
                            case 1:
                                Update_page3_line1_data(CHARGING_DATA_ARRAY_17_32);
                                //WDT_Clear();
                                break;
                            case 2:
                                Update_page3_line2_data(CHARGING_DATA_ARRAY_17_32);
                                //WDT_Clear();
                                break;
                            case 3:
                                Update_page3_line3_data(CHARGING_DATA_ARRAY_17_32);
                                //WDT_Clear();
                                break;
                            case 4:
                                Update_page3_line4_data(CHARGING_DATA_ARRAY_17_32);
                                //WDT_Clear();
                                break;
                            case 5:
                                Update_page3_line5_data(CHARGING_DATA_ARRAY_17_32);
                                //WDT_Clear();
                                break;
                            case 6:
                                Update_page3_line6_data(CHARGING_DATA_ARRAY_17_32);
                                //WDT_Clear();
                                break;
                            case 7:
                                Update_page3_line7_data(CHARGING_DATA_ARRAY_17_32);
                                //WDT_Clear();
                                break;
                            case 8:
                                Update_page3_line8_data(CHARGING_DATA_ARRAY_17_32);
                                //WDT_Clear();
                                break;
                        }
                        break;
                    case 3:
                        Write_Sno_for_page4();
                        Update_page4_data(CHARGING_DATA_ARRAY_17_32);
                        switch (flashreadmsg.PAGE_VIEW) {
                            case 1:
                                Update_page4_line1_data(CHARGING_DATA_ARRAY_17_32);

                                break;
                            case 2:
                                Update_page4_line2_data(CHARGING_DATA_ARRAY_17_32);
                                //WDT_Clear();
                                break;
                            case 3:
                                Update_page4_line3_data(CHARGING_DATA_ARRAY_17_32);
                                //WDT_Clear();
                                break;
                            case 4:
                                Update_page4_line4_data(CHARGING_DATA_ARRAY_17_32);
                                //WDT_Clear();
                                break;
                            case 5:
                                Update_page4_line5_data(CHARGING_DATA_ARRAY_17_32);
                                //WDT_Clear();
                                break;
                            case 6:
                                Update_page4_line6_data(CHARGING_DATA_ARRAY_17_32);
                                //WDT_Clear();
                                break;
                            case 7:
                                Update_page4_line7_data(CHARGING_DATA_ARRAY_17_32);
                                //WDT_Clear();
                                break;
                            case 8:
                                Update_page4_line8_data(CHARGING_DATA_ARRAY_17_32);
                                //WDT_Clear();
                                break;
                        }
                        break;
                    case 4:
                        Write_Sno_for_page5();
                        Update_page5_data(CHARGING_DATA_ARRAY_33_48);
                        //WDT_Clear();
                        switch (flashreadmsg.PAGE_VIEW) {
                            case 1:
                                Update_page5_line1_data(CHARGING_DATA_ARRAY_33_48);
                                //WDT_Clear();
                                break;
                            case 2:
                                Update_page5_line2_data(CHARGING_DATA_ARRAY_33_48);
                                //WDT_Clear();
                                break;
                            case 3:
                                Update_page5_line3_data(CHARGING_DATA_ARRAY_33_48);
                                //WDT_Clear();
                                break;
                            case 4:
                                Update_page5_line4_data(CHARGING_DATA_ARRAY_33_48);
                                //WDT_Clear();
                                break;
                            case 5:
                                Update_page5_line5_data(CHARGING_DATA_ARRAY_33_48);
                                //WDT_Clear();
                                break;
                            case 6:
                                Update_page5_line6_data(CHARGING_DATA_ARRAY_33_48);
                                //WDT_Clear();
                                break;
                            case 7:
                                Update_page5_line7_data(CHARGING_DATA_ARRAY_33_48);
                                //WDT_Clear();
                                break;
                            case 8:
                                Update_page5_line8_data(CHARGING_DATA_ARRAY_33_48);
                                //WDT_Clear();
                                break;
                        }
                        break;
                    case 5:
                        Write_Sno_for_page6();
                        Update_page6_data(CHARGING_DATA_ARRAY_33_48);
                        //WDT_Clear();
                        switch (flashreadmsg.PAGE_VIEW) {
                            case 1:
                                Update_page6_line1_data(CHARGING_DATA_ARRAY_33_48);
                                //WDT_Clear();
                                break;
                            case 2:
                                Update_page6_line2_data(CHARGING_DATA_ARRAY_33_48);
                                //WDT_Clear();
                                break;
                            case 3:
                                Update_page6_line3_data(CHARGING_DATA_ARRAY_33_48);
                                //WDT_Clear();
                                break;
                            case 4:
                                Update_page6_line4_data(CHARGING_DATA_ARRAY_33_48);
                                //WDT_Clear();
                                break;
                            case 5:
                                Update_page6_line5_data(CHARGING_DATA_ARRAY_33_48);
                                //WDT_Clear();
                                break;
                            case 6:
                                Update_page6_line6_data(CHARGING_DATA_ARRAY_33_48);
                                //WDT_Clear();
                                break;
                            case 7:
                                Update_page6_line7_data(CHARGING_DATA_ARRAY_33_48);
                                //WDT_Clear();
                                break;
                            case 8:
                                Update_page6_line8_data(CHARGING_DATA_ARRAY_33_48);
                                //WDT_Clear();
                                break;
                        }
                        break;
                    case 6:
                        Write_Sno_for_page7();
                        Update_page7_data(CHARGING_DATA_ARRAY_49_64);
                        //WDT_Clear();
                        switch (flashreadmsg.PAGE_VIEW) {
                            case 1:
                                Update_page7_line1_data(CHARGING_DATA_ARRAY_49_64);
                                //WDT_Clear();
                                break;
                            case 2:
                                Update_page7_line2_data(CHARGING_DATA_ARRAY_49_64);
                                //WDT_Clear();
                                break;
                            case 3:
                                Update_page7_line3_data(CHARGING_DATA_ARRAY_49_64);
                                //WDT_Clear();
                                break;
                            case 4:
                                Update_page7_line4_data(CHARGING_DATA_ARRAY_49_64);
                                //WDT_Clear();
                                break;
                            case 5:
                                Update_page7_line5_data(CHARGING_DATA_ARRAY_49_64);
                                //WDT_Clear();
                                break;
                            case 6:
                                Update_page7_line6_data(CHARGING_DATA_ARRAY_49_64);
                                //WDT_Clear();
                                break;
                            case 7:
                                Update_page7_line7_data(CHARGING_DATA_ARRAY_49_64);
                                //WDT_Clear();
                                break;
                            case 8:
                                Update_page7_line8_data(CHARGING_DATA_ARRAY_49_64);
                                //WDT_Clear();
                                break;
                        }
                        break;
                    case 7:
                        Write_Sno_for_page8();
                        Update_page8_data(CHARGING_DATA_ARRAY_49_64);
                        //WDT_Clear();
                        switch (flashreadmsg.PAGE_VIEW) {
                            case 1:
                                Update_page8_line1_data(CHARGING_DATA_ARRAY_49_64);
                                //WDT_Clear();
                                break;
                            case 2:
                                Update_page8_line2_data(CHARGING_DATA_ARRAY_49_64);
                                //WDT_Clear();
                                break;
                            case 3:
                                Update_page8_line3_data(CHARGING_DATA_ARRAY_49_64);
                                //WDT_Clear();
                                break;
                            case 4:
                                Update_page8_line4_data(CHARGING_DATA_ARRAY_49_64);
                                //WDT_Clear();
                                break;
                            case 5:
                                Update_page8_line5_data(CHARGING_DATA_ARRAY_49_64);
                                //WDT_Clear();
                                break;
                            case 6:
                                Update_page8_line6_data(CHARGING_DATA_ARRAY_49_64);
                                //WDT_Clear();
                                break;
                            case 7:
                                Update_page8_line7_data(CHARGING_DATA_ARRAY_49_64);
                                //WDT_Clear();
                                break;
                            case 8:
                                Update_page8_line8_data(CHARGING_DATA_ARRAY_49_64);
                                //WDT_Clear();

                                break;
                        }
                        break;
                }
            }
        }
        vTaskSuspend(FLASH_READ_TASKHandle);
        vTaskDelay(1);
    }
}

void Start_DATA_POPULATE_TASK(void *argument) {
    uint32_t BT_DATA_ARRAY_0_127[128] = {0};
    //    uint32_t BT_DATA_ARRAY_128_255[128] = {0};
    //    uint32_t BT_DATA_ARRAY_256_383[128] = {0};
    //    uint32_t BT_DATA_ARRAY_383_512[128] = {0};
    char buff[50] = {0};
    uint32_t CHARGING_DATA_ARRAY_1_16[128] = {0};
    uint32_t CHARGING_DATA_ARRAY_17_32[128] = {0};
    uint32_t CHARGING_DATA_ARRAY_33_48[128] = {0};
    uint32_t CHARGING_DATA_ARRAY_49_64[128] = {0};
    //    sprintf(buff, "SYSTEM RESTARTED\r\n");
    //    SERCOM5_USART_Write(buff, sizeof (buff));
    //    while (!(SERCOM5_USART_TransmitComplete()));

    //    uint8_t BLE_ID_t_t[30] = {0};
    //    uint8_t OCPP_ID_t_t[30] = {0};
    for (;;) {

        /////////////COPY BT DATA to BUFFER/////////////////////

        memcpy(BT_DATA_ARRAY_0_127, (void *) FLASH_START_ADDRESS_BT, 512);
        while (NVMCTRL_IsBusy())
            ;
        //        memcpy(BT_DATA_ARRAY_128_255, (void *) (FLASH_START_ADDRESS_BT + FLASH_WRITE_LIMIT), 512);
        //        while (NVMCTRL_IsBusy());
        //        memcpy(BT_DATA_ARRAY_256_383, (void *) (FLASH_START_ADDRESS_BT + FLASH_WRITE_LIMIT1), 512);
        //        while (NVMCTRL_IsBusy());
        //        memcpy(BT_DATA_ARRAY_383_512, (void *) (FLASH_START_ADDRESS_BT + FLASH_WRITE_LIMIT2), 464);
        //        while (NVMCTRL_IsBusy());
        memcpy(CHARGING_DATA_ARRAY_1_16, (void *) (FLASH_START_ADDRESS_CHARGING_SESSION_1_62), 512);
        while (NVMCTRL_IsBusy())
            ;
        memcpy(CHARGING_DATA_ARRAY_17_32, (void *) (FLASH_START_ADDRESS_CHARGING_SESSION_1_62 + FLASH_WRITE_LIMIT), 512);
        while (NVMCTRL_IsBusy())
            ;
        memcpy(CHARGING_DATA_ARRAY_33_48, (void *) (FLASH_START_ADDRESS_CHARGING_SESSION_1_62 + FLASH_WRITE_LIMIT1), 512);
        while (NVMCTRL_IsBusy())
            ;
        memcpy(CHARGING_DATA_ARRAY_49_64, (void *) (FLASH_START_ADDRESS_CHARGING_SESSION_1_62 + FLASH_WRITE_LIMIT2), 464);
        while (NVMCTRL_IsBusy())
            ;
        //        BLE_ID_t_t[0] = (BT_DATA_ARRAY[BLE_ID_IDX]&0xFF000000) >> 24;
        //        OCPP_ID_t_t[0] = (BT_DATA_ARRAY[OCPP_ID_IDX]&0x00FF0000) >> 24;
        //        BLE_ID_t_t[1] = (BT_DATA_ARRAY[BLE_ID_IDX]&0x00FF0000) >> 16;
        //        OCPP_ID_t_t[1] = (BT_DATA_ARRAY[OCPP_ID_IDX]&0xFF000000) >> 16;
        //        BLE_ID_t_t[2] = (BT_DATA_ARRAY[BLE_ID_IDX]&0x0000FF00) >> 8;
        //        OCPP_ID_t_t[2] = (BT_DATA_ARRAY[OCPP_ID_IDX]&0x0000FF00) >> 8;
        //        BLE_ID_t_t[3] = (BT_DATA_ARRAY[BLE_ID_IDX]&0x000000FF);
        //        OCPP_ID_t_t[3] = (BT_DATA_ARRAY[OCPP_ID_IDX]&0x000000FF);
        //        //WDT_Clear();
        //        BLE_ID_t_t[4] = (BT_DATA_ARRAY[BLE_ID_IDX1]&0xFF000000) >> 24;
        //        OCPP_ID_t_t[4] = (BT_DATA_ARRAY[OCPP_ID_IDX1]&0x00FF0000) >> 24;
        //        BLE_ID_t_t[5] = (BT_DATA_ARRAY[BLE_ID_IDX1]&0x00FF0000) >> 16;
        //        OCPP_ID_t_t[5] = (BT_DATA_ARRAY[OCPP_ID_IDX1]&0xFF000000) >> 16;
        //        BLE_ID_t_t[6] = (BT_DATA_ARRAY[BLE_ID_IDX1]&0x0000FF00) >> 8;
        //        OCPP_ID_t_t[6] = (BT_DATA_ARRAY[OCPP_ID_IDX1]&0x0000FF00) >> 8;
        //        BLE_ID_t_t[7] = (BT_DATA_ARRAY[BLE_ID_IDX1]&0x000000FF);
        //        OCPP_ID_t_t[7] = (BT_DATA_ARRAY[OCPP_ID_IDX1]&0x000000FF);
        //        //WDT_Clear();
        //        BLE_ID_t_t[8] = (BT_DATA_ARRAY[BLE_ID_IDX2]&0xFF000000) >> 24;
        //        OCPP_ID_t_t[8] = (BT_DATA_ARRAY[OCPP_ID_IDX2]&0x00FF0000) >> 24;
        //        BLE_ID_t_t[9] = (BT_DATA_ARRAY[BLE_ID_IDX2]&0x00FF0000) >> 16;
        //        OCPP_ID_t_t[9] = (BT_DATA_ARRAY[OCPP_ID_IDX2]&0xFF000000) >> 16;
        //        BLE_ID_t_t[10] = (BT_DATA_ARRAY[BLE_ID_IDX2]&0x0000FF00) >> 8;
        //        OCPP_ID_t_t[10] = (BT_DATA_ARRAY[OCPP_ID_IDX2]&0x0000FF00) >> 8;
        //        BLE_ID_t_t[11] = (BT_DATA_ARRAY[BLE_ID_IDX2]&0x000000FF);
        //        OCPP_ID_t_t[11] = (BT_DATA_ARRAY[OCPP_ID_IDX2]&0x000000FF);
        //        //WDT_Clear();
        //        BLE_ID_t_t[12] = (BT_DATA_ARRAY[BLE_ID_IDX3]&0xFF000000) >> 24;
        //        OCPP_ID_t_t[12] = (BT_DATA_ARRAY[OCPP_ID_IDX3]&0x00FF0000) >> 24;
        //        BLE_ID_t_t[13] = (BT_DATA_ARRAY[BLE_ID_IDX3]&0x00FF0000) >> 16;
        //        OCPP_ID_t_t[13] = (BT_DATA_ARRAY[OCPP_ID_IDX3]&0xFF000000) >> 16;
        //        BLE_ID_t_t[14] = (BT_DATA_ARRAY[BLE_ID_IDX3]&0x0000FF00) >> 8;
        //        OCPP_ID_t_t[14] = (BT_DATA_ARRAY[OCPP_ID_IDX3]&0x0000FF00) >> 8;
        //        BLE_ID_t_t[15] = (BT_DATA_ARRAY[BLE_ID_IDX3]&0x000000FF);
        //        OCPP_ID_t_t[15] = (BT_DATA_ARRAY[OCPP_ID_IDX3]&0x000000FF);
        //        //WDT_Clear();
        //        BLE_ID_t_t[16] = (BT_DATA_ARRAY[BLE_ID_IDX4]&0xFF000000) >> 24;
        //        OCPP_ID_t_t[16] = (BT_DATA_ARRAY[OCPP_ID_IDX4]&0x00FF0000) >> 24;
        //        BLE_ID_t_t[17] = (BT_DATA_ARRAY[BLE_ID_IDX4]&0x00FF0000) >> 16;
        //        OCPP_ID_t_t[17] = (BT_DATA_ARRAY[OCPP_ID_IDX4]&0xFF000000) >> 16;
        //        BLE_ID_t_t[18] = (BT_DATA_ARRAY[BLE_ID_IDX4]&0x0000FF00) >> 8;
        //        OCPP_ID_t_t[18] = (BT_DATA_ARRAY[OCPP_ID_IDX4]&0x0000FF00) >> 8;
        //        BLE_ID_t_t[19] = (BT_DATA_ARRAY[BLE_ID_IDX4]&0x000000FF);
        //        OCPP_ID_t_t[19] = (BT_DATA_ARRAY[OCPP_ID_IDX4]&0x000000FF);
        //        //WDT_Clear();
        //        BLE_ID_t_t[20] = (BT_DATA_ARRAY[BLE_ID_IDX5]&0xFF000000) >> 24;
        //        OCPP_ID_t_t[20] = (BT_DATA_ARRAY[OCPP_ID_IDX5]&0x00FF0000) >> 24;
        //        BLE_ID_t_t[21] = (BT_DATA_ARRAY[BLE_ID_IDX5]&0x00FF0000) >> 16;
        //        OCPP_ID_t_t[21] = (BT_DATA_ARRAY[OCPP_ID_IDX5]&0xFF000000) >> 16;
        //        BLE_ID_t_t[22] = (BT_DATA_ARRAY[BLE_ID_IDX5]&0x0000FF00) >> 8;
        //        OCPP_ID_t_t[22] = (BT_DATA_ARRAY[OCPP_ID_IDX5]&0x0000FF00) >> 8;
        //        BLE_ID_t_t[23] = (BT_DATA_ARRAY[BLE_ID_IDX5]&0x000000FF);
        //        OCPP_ID_t_t[23] = (BT_DATA_ARRAY[OCPP_ID_IDX5]&0x000000FF);
        //        //WDT_Clear();
        //        BLE_ID_t_t[24] = (BT_DATA_ARRAY[BLE_ID_IDX6]&0xFF000000) >> 24;
        //        OCPP_ID_t_t[24] = (BT_DATA_ARRAY[OCPP_ID_IDX6]&0x00FF0000) >> 24;
        //        BLE_ID_t_t[25] = (BT_DATA_ARRAY[BLE_ID_IDX6]&0x00FF0000) >> 16;
        //        OCPP_ID_t_t[25] = (BT_DATA_ARRAY[OCPP_ID_IDX6]&0xFF000000) >> 16;
        //        BLE_ID_t_t[26] = (BT_DATA_ARRAY[BLE_ID_IDX6]&0x0000FF00) >> 8;
        //        OCPP_ID_t_t[26] = (BT_DATA_ARRAY[OCPP_ID_IDX6]&0x0000FF00) >> 8;
        //        BLE_ID_t_t[27] = (BT_DATA_ARRAY[BLE_ID_IDX6]&0x000000FF);
        //        OCPP_ID_t_t[27] = (BT_DATA_ARRAY[OCPP_ID_IDX6]&0x000000FF);
        //        //WDT_Clear();
        //        BLE_ID_t_t[28] = (BT_DATA_ARRAY[BLE_ID_IDX7]&0xFF000000) >> 24;
        //        OCPP_ID_t_t[28] = (BT_DATA_ARRAY[OCPP_ID_IDX7]&0x00FF0000) >> 24;
        //        BLE_ID_t_t[29] = (BT_DATA_ARRAY[BLE_ID_IDX7]&0x00FF0000) >> 16;
        //        OCPP_ID_t_t[29] = (BT_DATA_ARRAY[OCPP_ID_IDX7]&0xFF000000) >> 16;
        //WDT_Clear();

        //        Update_BLE_ID(BLE_ID_t_t);
        //        Update_OCPP_ID(OCPP_ID_t_t);
        if (CHARGING_DATA_ARRAY_1_16[0] == BLANK_DATA || CHARGING_DATA_ARRAY_17_32[0] == BLANK_DATA || CHARGING_DATA_ARRAY_33_48[0] == BLANK_DATA || CHARGING_DATA_ARRAY_49_64[0] == BLANK_DATA) {
            memset(CHARGING_DATA_ARRAY_1_16, 0, sizeof (CHARGING_DATA_ARRAY_1_16));
            memset(CHARGING_DATA_ARRAY_17_32, 0, sizeof (CHARGING_DATA_ARRAY_17_32));
            memset(CHARGING_DATA_ARRAY_33_48, 0, sizeof (CHARGING_DATA_ARRAY_33_48));
            memset(CHARGING_DATA_ARRAY_49_64, 0, sizeof (CHARGING_DATA_ARRAY_49_64));
            //WDT_Clear();
            NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_CHARGING_SESSION_1_62);
            while (NVMCTRL_IsBusy())
                ;
            NVMCTRL_PageWrite((uint32_t *) CHARGING_DATA_ARRAY_1_16, (uint32_t) FLASH_START_ADDRESS_CHARGING_SESSION_1_62);
            while (NVMCTRL_IsBusy())
                ;
            NVMCTRL_PageWrite((uint32_t *) CHARGING_DATA_ARRAY_17_32, (uint32_t) (FLASH_START_ADDRESS_CHARGING_SESSION_1_62 + FLASH_WRITE_LIMIT));
            while (NVMCTRL_IsBusy())
                ;
            NVMCTRL_PageWrite((uint32_t *) CHARGING_DATA_ARRAY_33_48, (uint32_t) (FLASH_START_ADDRESS_CHARGING_SESSION_1_62 + FLASH_WRITE_LIMIT1));
            while (NVMCTRL_IsBusy())
                ;
            NVMCTRL_PageWrite((uint32_t *) CHARGING_DATA_ARRAY_49_64, (uint32_t) (FLASH_START_ADDRESS_CHARGING_SESSION_1_62 + FLASH_WRITE_LIMIT2));
            while (NVMCTRL_IsBusy())
                ;
        }
        //WDT_Clear();
        /////////////////////////////////////////////////////////////////////////////
        ////////////////////////////CHECK AND UPDATE DATA///////////////////////////////////////
        if (BT_DATA_ARRAY_0_127[SYSTEM_RESTART_IDX] == BLANK_DATA) {
            BT_DATA_ARRAY_0_127[SYSTEM_RESTART_IDX] = ZERO_DATA;
        }
        BT_DATA_ARRAY_0_127[SYSTEM_RESTART_IDX] = BT_DATA_ARRAY_0_127[SYSTEM_RESTART_IDX] + 1;

        if (BT_DATA_ARRAY_0_127[PRICE_VALUE_IDX] == BLANK_DATA) {
            BT_DATA_ARRAY_0_127[PRICE_VALUE_IDX] = DEFAULT_PRICE;
            Update_Unit_price(DEFAULT_PRICE);
        } else {
            Update_Unit_price((uint16_t) BT_DATA_ARRAY_0_127[PRICE_VALUE_IDX]);
        }

        if (BT_DATA_ARRAY_0_127[GUN1_CONFIG_IDX] == BLANK_DATA) {
            BT_DATA_ARRAY_0_127[GUN1_CONFIG_IDX] = (DEFAULT_GUN1_ENABLE);
        } else {
            GUN1_ENABLE_DISABLE = BT_DATA_ARRAY_0_127[GUN1_CONFIG_IDX];
        }
        if (BT_DATA_ARRAY_0_127[GUN2_CONFIG_IDX] == BLANK_DATA) {
            BT_DATA_ARRAY_0_127[GUN2_CONFIG_IDX] = (DEFAULT_GUN1_ENABLE);
        } else {
            GUN2_ENABLE_DISABLE = BT_DATA_ARRAY_0_127[GUN2_CONFIG_IDX];
        }

        if (BT_DATA_ARRAY_0_127[SYSTEM_TEMP_LIMIT_IDX] == BLANK_DATA) {
            BT_DATA_ARRAY_0_127[SYSTEM_TEMP_LIMIT_IDX] = (DEFAULT_BODY_TEMP_UPPER_LIMIT);
        } else {
            DEFAULT_BODY_TEMP_UPPER_LIMIT_t = BT_DATA_ARRAY_0_127[SYSTEM_TEMP_LIMIT_IDX];
        }

        if (BT_DATA_ARRAY_0_127[NE_VOLT_LIMIT_IDX] == BLANK_DATA) {
            BT_DATA_ARRAY_0_127[NE_VOLT_LIMIT_IDX] = DEFAULT_NE_VOLT_LIMIT;
        } else {
            DEFAULT_NE_VOLT_LIMIT_t = BT_DATA_ARRAY_0_127[NE_VOLT_LIMIT_IDX];
        }

        if (BT_DATA_ARRAY_0_127[AC_UNDER_VOLT_LIMIT_IDX] == BLANK_DATA) {
            BT_DATA_ARRAY_0_127[AC_UNDER_VOLT_LIMIT_IDX] = DEFAULT_AC_UNDER_VOLT_LIMIT;
        } else {
            AC_UNDER_VOLT_LIMIT_t = BT_DATA_ARRAY_0_127[AC_UNDER_VOLT_LIMIT_IDX];
        }

        if (BT_DATA_ARRAY_0_127[AC_OVER_VOLT_LIMIT_IDX] == BLANK_DATA) {
            BT_DATA_ARRAY_0_127[AC_OVER_VOLT_LIMIT_IDX] = DEFAULT_AC_OVER_VOLT_LIMIT;
        } else {
            AC_OVER_VOLT_LIMIT_t = BT_DATA_ARRAY_0_127[AC_OVER_VOLT_LIMIT_IDX];
        }

        if (BT_DATA_ARRAY_0_127[GUN1_TEMPERATURE_LIMIT_IDX] == BLANK_DATA) {
            BT_DATA_ARRAY_0_127[GUN1_TEMPERATURE_LIMIT_IDX] = DEFAULT_GUN1_TEMP_LIMIT;
        } else {
            DEFAULT_GUN1_TEMP_LIMIT_t = BT_DATA_ARRAY_0_127[GUN1_TEMPERATURE_LIMIT_IDX];
        }

        if (BT_DATA_ARRAY_0_127[GUN2_TEMPERATURE_LIMIT_IDX] == BLANK_DATA) {
            BT_DATA_ARRAY_0_127[GUN2_TEMPERATURE_LIMIT_IDX] = DEFAULT_GUN2_TEMP_LIMIT;
        } else {
            DEFAULT_GUN2_TEMP_LIMIT_t = BT_DATA_ARRAY_0_127[GUN2_TEMPERATURE_LIMIT_IDX];
        }

        if (BT_DATA_ARRAY_0_127[GUN_TEMPERATURE_POINT_CLEAR_IDX] == BLANK_DATA) {
            BT_DATA_ARRAY_0_127[GUN_TEMPERATURE_POINT_CLEAR_IDX] = DEFAULT_GUN_TEMPERATURE_POINT_CLEAR_VALUE;
        } else {
            DEFAULT_GUN_TEMPERATURE_POINT_CLEAR_VALUE_t = BT_DATA_ARRAY_0_127[GUN_TEMPERATURE_POINT_CLEAR_IDX];
        }

        if (BT_DATA_ARRAY_0_127[MAX_POWER_CAPACITY_IDX] == BLANK_DATA) {
            BT_DATA_ARRAY_0_127[MAX_POWER_CAPACITY_IDX] = MAX_POWER_LIMIT;
        } else {
            POWER_VALUE_X = BT_DATA_ARRAY_0_127[MAX_POWER_CAPACITY_IDX] * 10000;
        }

        if (BT_DATA_ARRAY_0_127[CHARGER_TYPE_SIN_DUAL_IDX] == BLANK_DATA) {
            BT_DATA_ARRAY_0_127[CHARGER_TYPE_SIN_DUAL_IDX] = DEFAULT_CHARGER_TYPE;
        } else {
            DEFAULT_CHARGER_TYPE_t = BT_DATA_ARRAY_0_127[CHARGER_TYPE_SIN_DUAL_IDX];
        }

        if (BT_DATA_ARRAY_0_127[ACEM_ALARM_IDX] == BLANK_DATA) {
            BT_DATA_ARRAY_0_127[ACEM_ALARM_IDX] = DEFAULT_ACEM_ALARM;
        } else {
            DEFAULT_ACEM_ALARM_t = BT_DATA_ARRAY_0_127[ACEM_ALARM_IDX];
        }

        if (BT_DATA_ARRAY_0_127[DCEM1_ALARM_IDX] == BLANK_DATA) {
            BT_DATA_ARRAY_0_127[DCEM1_ALARM_IDX] = DEFAULT_DCEM_GUN1_ALARM;
        } else {
            DEFAULT_DCEM_GUN1_ALARM_t = BT_DATA_ARRAY_0_127[DCEM1_ALARM_IDX];
        }

        if (BT_DATA_ARRAY_0_127[DCEM2_ALARM_IDX] == BLANK_DATA) {
            BT_DATA_ARRAY_0_127[DCEM2_ALARM_IDX] = DEFAULT_DCEM_GUN2_ALARM;
        } else {
            DEFAULT_DCEM_GUN2_ALARM_t = BT_DATA_ARRAY_0_127[DCEM2_ALARM_IDX];
        }

        if (BT_DATA_ARRAY_0_127[DOOR_ALARM_IDX] == BLANK_DATA) {
            BT_DATA_ARRAY_0_127[DOOR_ALARM_IDX] = DEFAULT_DOOR_ALARM;
        } else {
            DEFAULT_DOOR_ALARM_t = BT_DATA_ARRAY_0_127[DOOR_ALARM_IDX];
        }

        if (BT_DATA_ARRAY_0_127[IMD1_ALARM_IDX] == BLANK_DATA) {
            BT_DATA_ARRAY_0_127[IMD1_ALARM_IDX] = DEFAULT_IMD1_ALARM;
        } else {
            DEFAULT_IMD1_ALARM_t = BT_DATA_ARRAY_0_127[IMD1_ALARM_IDX];
        }

        if (BT_DATA_ARRAY_0_127[IMD2_ALARM_IDX] == BLANK_DATA) {
            BT_DATA_ARRAY_0_127[IMD2_ALARM_IDX] = DEFAULT_IMD2_ALARM;
        } else {
            DEFAULT_IMD2_ALARM_t = BT_DATA_ARRAY_0_127[IMD2_ALARM_IDX];
        }

        if (BT_DATA_ARRAY_0_127[SPD_ALARM_IDX] == BLANK_DATA) {
            BT_DATA_ARRAY_0_127[SPD_ALARM_IDX] = DEFAULT_IMD1_ALARM;
        } else {
            DEFAULT_SPD_ALARM_t = BT_DATA_ARRAY_0_127[SPD_ALARM_IDX];
        }

        if (BT_DATA_ARRAY_0_127[SMOKE_ALARM_IDX] == BLANK_DATA) {
            BT_DATA_ARRAY_0_127[SMOKE_ALARM_IDX] = DEFAULT_SMOKE_ALARM;
        } else {
            DEFAULT_SMOKE_ALARM_t = BT_DATA_ARRAY_0_127[SMOKE_ALARM_IDX];
        }

        if (BT_DATA_ARRAY_0_127[GUN1_TEMP_ALARM_IDX] == BLANK_DATA) {
            BT_DATA_ARRAY_0_127[GUN1_TEMP_ALARM_IDX] = DEFAULT_GUN1_TEMP_ALARM;
        } else {
            DEFAULT_GUN1_TEMP_ALARM_t = BT_DATA_ARRAY_0_127[GUN1_TEMP_ALARM_IDX];
        }

        if (BT_DATA_ARRAY_0_127[GUN2_TEMP_ALARM_IDX] == BLANK_DATA) {
            BT_DATA_ARRAY_0_127[GUN2_TEMP_ALARM_IDX] = DEFAULT_GUN2_TEMP_LIMIT;
        } else {
            DEFAULT_GUN2_TEMP_ALARM_t = BT_DATA_ARRAY_0_127[GUN2_TEMP_ALARM_IDX];
        }

        if (BT_DATA_ARRAY_0_127[LED_FAULT_ALARM_IDX] == BLANK_DATA) {
            BT_DATA_ARRAY_0_127[LED_FAULT_ALARM_IDX] = DEFAULT_LED_FAULT_ALARM;
        } else {
            DEFAULT_LED_FAULT_ALARM_t = BT_DATA_ARRAY_0_127[LED_FAULT_ALARM_IDX];
        }

        if (BT_DATA_ARRAY_0_127[RFID_FAULT_ALARM_IDX] == BLANK_DATA) {
            BT_DATA_ARRAY_0_127[RFID_FAULT_ALARM_IDX] = DEFAULT_RFID_FAULT_ALARM;
        } else {
            DEFAULT_RFID_FAULT_ALARM_t = BT_DATA_ARRAY_0_127[RFID_FAULT_ALARM_IDX];
        }

        if (BT_DATA_ARRAY_0_127[ACEM_TYPE_IDX] == BLANK_DATA) {
            BT_DATA_ARRAY_0_127[ACEM_TYPE_IDX] = DEFAULT_RFID_FAULT_ALARM;
        } else {
            DEFAULT_RFID_FAULT_ALARM_t = BT_DATA_ARRAY_0_127[ACEM_TYPE_IDX];
        }
        //        if (BT_DATA_ARRAY[] == BLANK_DATA) {
        //            BT_DATA_ARRAY[] =;
        //        } else {
        //            = BT_DATA_ARRAY[];
        //        }
        //
        //        if (BT_DATA_ARRAY[] == BLANK_DATA) {
        //            BT_DATA_ARRAY[] =;
        //        } else {
        //            = BT_DATA_ARRAY[];
        //        }
        /////////////////////////////////////////////////////////////////////AGAIN WRITE TO FLASH WITH UPDATED DATA//////////////////////

        if (BT_DATA_ARRAY_0_127[DLB_POWER_VALUES_IDX] == BLANK_DATA) {
            BT_DATA_ARRAY_0_127[DLB_POWER_VALUES_IDX] = ZERO_DATA | (((uint32_t) POWER_VALUE_X / 1000) << 24) | (((uint32_t) POWER_VALUE_X / 1000) << 16) | ((uint32_t) SINGLE_GUN2_POWER << 8) | ((uint32_t) SINGLE_GUN1_POWER);
        } else {
            SINGLE_GUN1_POWER = (uint8_t) (BT_DATA_ARRAY_0_127[DLB_POWER_VALUES_IDX] & 0x000000FF);
            SINGLE_GUN2_POWER = (uint8_t) ((BT_DATA_ARRAY_0_127[DLB_POWER_VALUES_IDX] & 0x0000FF00) >> 8);
            if (SINGLE_GUN1_POWER == 1) {
                POWER_VALUE_X1 = (float) (((BT_DATA_ARRAY_0_127[DLB_POWER_VALUES_IDX] & 0x00FF0000) >> 16)) * 1000;
            }
            if (SINGLE_GUN2_POWER == 1) {
                POWER_VALUE_X2 = (float) (((BT_DATA_ARRAY_0_127[DLB_POWER_VALUES_IDX] & 0xFF000000) >> 24)) * 1000;
            }
            if (SINGLE_GUN1_POWER == 0 || SINGLE_GUN2_POWER == 0) {
                POWER_VALUE_X = (float) (((BT_DATA_ARRAY_0_127[DLB_POWER_VALUES_IDX] & 0xFF000000) >> 24)) * 1000;
            }
        }

        NVMCTRL_BlockErase((uint32_t) FLASH_START_ADDRESS_BT);
        while (NVMCTRL_IsBusy())
            ;

        NVMCTRL_PageWrite((uint32_t *) BT_DATA_ARRAY_0_127, (uint32_t) FLASH_START_ADDRESS_BT);
        while (NVMCTRL_IsBusy())
            ;
        memset(buff, 0, sizeof (buff));
        sprintf(buff, "RESTART COUNT after bootloader is : %ld\r\n", BT_DATA_ARRAY_0_127[SYSTEM_RESTART_IDX]);
        SERCOM5_USART_Write(buff, sizeof (buff));
        while (!(SERCOM5_USART_TransmitComplete()))
            ;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        vTaskSuspend(DATA_POPULATE_TASKHandle);
        vTaskDelay(1000);
    }
}