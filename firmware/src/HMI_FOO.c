#include "HMI_FOO.h"


HMI_SEND_DATA_Q msg;
extern TaskHandle_t HMI_SEND_TASKHandle;
void SINGLE_BIT_HEADER(void) {
    memset(msg.DATA, 0, sizeof (msg.DATA));
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x05;
    msg.DATA[3] = 0x82;
    msg.DATA[6] = 0x00;
}

void DOUBLE_BYTE_HEADER(void) {
    memset(msg.DATA, 0, sizeof (msg.DATA));
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x05;
    msg.DATA[3] = 0x82;
}

void LONG_BYTE_HEADER(void) {
    memset(msg.DATA, 0, sizeof (msg.DATA));
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x07;
    msg.DATA[3] = 0x82;
}

void Update_AC_VOLTAGE1(uint16_t volt) {
    DOUBLE_BYTE_HEADER();
    msg.DATA[4] = AC_VOLTAGE1_ADD_MSB;
    msg.DATA[5] = AC_VOLTAGE1_ADD_LSB;
    msg.DATA[6] = (volt & 0xFF00) >> 8;
    msg.DATA[7] = volt & 0x00FF;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);
}

void Update_AC_VOLTAGE2(uint16_t volt) {

    DOUBLE_BYTE_HEADER();
    msg.DATA[4] = AC_VOLTAGE2_ADD_MSB;
    msg.DATA[5] = AC_VOLTAGE2_ADD_LSB;
    msg.DATA[6] = (volt & 0xFF00) >> 8;
    msg.DATA[7] = volt & 0x00FF;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);
}

void Update_AC_VOLTAGE3(uint16_t volt) {

    DOUBLE_BYTE_HEADER();
    msg.DATA[4] = AC_VOLTAGE3_ADD_MSB;
    msg.DATA[5] = AC_VOLTAGE3_ADD_LSB;
    msg.DATA[6] = (volt & 0xFF00) >> 8;
    msg.DATA[7] = volt & 0x00FF;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);

}

void Update_AC_CURRENT1(uint16_t current) {

    DOUBLE_BYTE_HEADER();
    msg.DATA[4] = AC_CURRENT1_ADD_MSB;
    msg.DATA[5] = AC_CURRENT1_ADD_LSB;
    msg.DATA[6] = (current & 0xFF00) >> 8;
    msg.DATA[7] = current & 0x00FF;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);

}

void Update_AC_CURRENT2(uint16_t current) {

    DOUBLE_BYTE_HEADER();
    msg.DATA[4] = AC_CURRENT2_ADD_MSB;
    msg.DATA[5] = AC_CURRENT2_ADD_LSB;
    msg.DATA[6] = (current & 0xFF00) >> 8;
    msg.DATA[7] = current & 0x00FF;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);
}

void Update_AC_CURRENT3(uint16_t current) {

    DOUBLE_BYTE_HEADER();
    msg.DATA[4] = AC_CURRENT3_ADD_MSB;
    msg.DATA[5] = AC_CURRENT3_ADD_LSB;
    msg.DATA[6] = (current & 0xFF00) >> 8;
    msg.DATA[7] = current & 0x00FF;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);
}

void Update_AC_frequency(uint16_t frequency) {

    DOUBLE_BYTE_HEADER();
    msg.DATA[4] = AC_FREQUENCY_ADD_MSB;
    msg.DATA[5] = AC_FREQUENCY_ADD_LSB;
    msg.DATA[6] = (frequency & 0xFF00) >> 8;
    msg.DATA[7] = frequency & 0x00FF;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);
}

void Change_gun1_status_to(uint8_t status) {


    SINGLE_BIT_HEADER();
    msg.DATA[4] = 0x12;
    msg.DATA[5] = 0x06;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);
}

void Change_gun2_status_to(uint8_t status) {


    SINGLE_BIT_HEADER();
    msg.DATA[4] = 0x12;
    msg.DATA[5] = 0x07;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);
}

void Change_Page_to(uint8_t page_no) {

    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x07;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = 0x00;
    msg.DATA[5] = 0x84;
    msg.DATA[6] = 0x5A;
    msg.DATA[7] = 0x01;
    msg.DATA[8] = 0x00;
    msg.DATA[9] = page_no;
    //    xQueueSend(HMI_SEND_QUEUE, &msg, 100);
    vTaskSuspend(HMI_SEND_TASKHandle);
    ENABLE_HMI_Set();
    SERCOM6_USART_Write(msg.DATA, (msg.DATA[2] + 3));
    while (!(SERCOM6_USART_TransmitComplete()))
        ;
    ENABLE_HMI_Clear();
    vTaskResume(HMI_SEND_TASKHandle);
}

void Update_Date_Time(uint16_t year, uint8_t month, uint8_t date, uint8_t hour, uint8_t minute, uint8_t sec) {

    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x0B;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = 0x00;
    msg.DATA[5] = 0x9C;
    msg.DATA[6] = 0x5A;
    msg.DATA[7] = 0xA5;
    msg.DATA[8] = (uint8_t) year;
    msg.DATA[9] = month;
    msg.DATA[10] = date;
    msg.DATA[11] = hour;
    msg.DATA[12] = minute;
    msg.DATA[13] = sec;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);
}

void Update_OCPP_Symbol(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = OCPP_SYMBOL_ADD_MSB;
    msg.DATA[5] = OCPP_SYMBOL_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);
}

void Update_Ethernet_status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = ETH_ADD_MSB;
    msg.DATA[5] = ETH_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);
}

void Update_GSM_Signal_Strength(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = GSM_SIG_ADD_MSB;
    msg.DATA[5] = GSM_SIG_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);
}

void Update_GSM_Internet_Connectivity(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = GSM_INT_ADD_MSB;
    msg.DATA[5] = GSM_INT_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);
}

void Update_Wifi_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = WIFI_ADD_MSB;
    msg.DATA[5] = WIFI_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);
}

void Update_Wifi_Availablity(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = WIFIA_ADD_MSB;
    msg.DATA[5] = WIFIA_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);
}

void Update_Gun1_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = GUN1_STATUS_ADD_MSB;
    msg.DATA[5] = GUN1_STATUS_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);
}

void Update_Gun2_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = GUN2_STATUS_ADD_MSB;
    msg.DATA[5] = GUN2_STATUS_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_Unit_price(uint16_t price) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = UNIT_PRICE_ADD_MSB;
    msg.DATA[5] = UNIT_PRICE_ADD_LSB;
    msg.DATA[6] = ((price)&0xFF00) >> 8;
    msg.DATA[7] = (price)&0x00FF;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN1_Battery_SOC(uint16_t SOC) {

    DOUBLE_BYTE_HEADER();
    msg.DATA[4] = G1_BATTERY_SOC_ADD_MSB;
    msg.DATA[5] = G1_BATTERY_SOC_ADD_LSB;
    msg.DATA[6] = (SOC & 0xFF00) >> 8;
    msg.DATA[7] = SOC & 0x00FF;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN1_Initial_SOC(uint16_t SOC) {

    DOUBLE_BYTE_HEADER();
    msg.DATA[4] = G1_INITIAL_SOC_ADD_MSB;
    msg.DATA[5] = G1_INITIAL_SOC_ADD_LSB;
    msg.DATA[6] = (SOC & 0xFF00) >> 8;
    msg.DATA[7] = SOC & 0x00FF;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN1_Duration(uint32_t duration) {

    LONG_BYTE_HEADER();
    msg.DATA[4] = G1_DURATION_ADD_MSB;
    msg.DATA[5] = G1_DURATION_ADD_LSB;
    msg.DATA[6] = (duration & 0xFF000000) >> 24;
    msg.DATA[7] = (duration & 0x00FF0000) >> 16;
    msg.DATA[8] = (duration & 0x0000FF00) >> 8;
    msg.DATA[9] = (duration & 0x000000FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN1_Demand_Voltage(uint32_t voltage) {

    LONG_BYTE_HEADER();
    msg.DATA[4] = G1_DEMAND_VOLTAGE_ADD_MSB;
    msg.DATA[5] = G1_DEMAND_VOLTAGE_ADD_LSB;
    msg.DATA[6] = (voltage & 0xFF000000) >> 24;
    msg.DATA[7] = (voltage & 0x00FF0000) >> 16;
    msg.DATA[8] = (voltage & 0x0000FF00) >> 8;
    msg.DATA[9] = (voltage & 0x000000FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN1_Demand_Current(uint32_t current) {

    LONG_BYTE_HEADER();
    msg.DATA[4] = G1_DEMAND_CURRENT_ADD_MSB;
    msg.DATA[5] = G1_DEMAND_CURRENT_ADD_LSB;
    msg.DATA[6] = (current & 0xFF000000) >> 24;
    msg.DATA[7] = (current & 0x00FF0000) >> 16;
    msg.DATA[8] = (current & 0x0000FF00) >> 8;
    msg.DATA[9] = (current & 0x000000FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN1_Voltage(uint32_t voltage) {

    LONG_BYTE_HEADER();
    msg.DATA[4] = G1_VOLTAGE_ADD_MSB;
    msg.DATA[5] = G1_VOLTAGE_ADD_LSB;
    msg.DATA[6] = (voltage & 0xFF000000) >> 24;
    msg.DATA[7] = (voltage & 0x00FF0000) >> 16;
    msg.DATA[8] = (voltage & 0x0000FF00) >> 8;
    msg.DATA[9] = (voltage & 0x000000FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN1_Current(uint32_t current) {

    LONG_BYTE_HEADER();
    msg.DATA[4] = G1_CURRENT_ADD_MSB;
    msg.DATA[5] = G1_CURRENT_ADD_LSB;
    msg.DATA[6] = (current & 0xFF000000) >> 24;
    msg.DATA[7] = (current & 0x00FF0000) >> 16;
    msg.DATA[8] = (current & 0x0000FF00) >> 8;
    msg.DATA[9] = (current & 0x000000FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN1_Total_Power(uint32_t power) {

    LONG_BYTE_HEADER();
    msg.DATA[4] = G1_TOTAL_POWER_ADD_MSB;
    msg.DATA[5] = G1_TOTAL_POWER_ADD_LSB;
    msg.DATA[6] = (power & 0xFF000000) >> 24;
    msg.DATA[7] = (power & 0x00FF0000) >> 16;
    msg.DATA[8] = (power & 0x0000FF00) >> 8;
    msg.DATA[9] = (power & 0x000000FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN1_Charging_Start_date(uint16_t date) {
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x05;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = G1_CHARGING_START_DATE_ADD_MSB;
    msg.DATA[5] = G1_CHARGING_START_DATE_ADD_LSB;
    msg.DATA[6] = (date & 0xFF00) >> 8;
    msg.DATA[7] = (date & 0x00FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN1_Charging_Start_month(uint16_t month) {
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x05;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = G1_CHARGING_START_MONTH_ADD_MSB;
    msg.DATA[5] = G1_CHARGING_START_MONTH_ADD_LSB;
    msg.DATA[6] = (month & 0xFF00) >> 8;
    msg.DATA[7] = (month & 0x00FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN1_Charging_Start_year(uint16_t year) {
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x05;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = G1_CHARGING_START_YEAR_ADD_MSB;
    msg.DATA[5] = G1_CHARGING_START_YEAR_ADD_LSB;
    msg.DATA[6] = (year & 0xFF00) >> 8;
    msg.DATA[7] = (year & 0x00FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN1_Charging_Start_hour(uint16_t hour) {
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x05;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = G1_CHARGING_START_HOUR_ADD_MSB;
    msg.DATA[5] = G1_CHARGING_START_HOUR_ADD_LSB;
    msg.DATA[6] = (hour & 0xFF00) >> 8;
    msg.DATA[7] = (hour & 0x00FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN1_Charging_Start_mins(uint16_t mins) {
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x05;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = G1_CHARGING_START_MIN_ADD_MSB;
    msg.DATA[5] = G1_CHARGING_START_MIN_ADD_LSB;
    msg.DATA[6] = (mins & 0xFF00) >> 8;
    msg.DATA[7] = (mins & 0x00FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN1_Charging_Start_sec(uint16_t sec) {
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x05;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = G1_CHARGING_START_SEC_ADD_MSB;
    msg.DATA[5] = G1_CHARGING_START_SEC_ADD_LSB;
    msg.DATA[6] = (sec & 0xFF00) >> 8;
    msg.DATA[7] = (sec & 0x00FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN1_Charging_Stop_date(uint16_t date) {
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x05;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = G1_CHARGING_STOP_DATE_ADD_MSB;
    msg.DATA[5] = G1_CHARGING_STOP_DATE_ADD_LSB;
    msg.DATA[6] = (date & 0xFF00) >> 8;
    msg.DATA[7] = (date & 0x00FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN1_Charging_Stop_month(uint16_t month) {
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x05;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = G1_CHARGING_STOP_MONTH_ADD_MSB;
    msg.DATA[5] = G1_CHARGING_STOP_MONTH_ADD_LSB;
    msg.DATA[6] = (month & 0xFF00) >> 8;
    msg.DATA[7] = (month & 0x00FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN1_Charging_Stop_year(uint16_t year) {
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x05;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = G1_CHARGING_STOP_YEAR_ADD_MSB;
    msg.DATA[5] = G1_CHARGING_STOP_YEAR_ADD_LSB;
    msg.DATA[6] = (year & 0xFF00) >> 8;
    msg.DATA[7] = (year & 0x00FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN1_Charging_Stop_hour(uint16_t hour) {
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x05;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = G1_CHARGING_STOP_HOUR_ADD_MSB;
    msg.DATA[5] = G1_CHARGING_STOP_HOUR_ADD_LSB;
    msg.DATA[6] = (hour & 0xFF00) >> 8;
    msg.DATA[7] = (hour & 0x00FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN1_Charging_Stop_mins(uint16_t mins) {
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x05;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = G1_CHARGING_STOP_MIN_ADD_MSB;
    msg.DATA[5] = G1_CHARGING_STOP_MIN_ADD_LSB;
    msg.DATA[6] = (mins & 0xFF00) >> 8;
    msg.DATA[7] = (mins & 0x00FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN1_Charging_Stop_sec(uint16_t sec) {
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x05;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = G1_CHARGING_STOP_SEC_ADD_MSB;
    msg.DATA[5] = G1_CHARGING_STOP_SEC_ADD_LSB;
    msg.DATA[6] = (sec & 0xFF00) >> 8;
    msg.DATA[7] = (sec & 0x00FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN1_Start_SOC(uint16_t SOC) {

    DOUBLE_BYTE_HEADER();
    msg.DATA[4] = G1_START_SOC_ADD_MSB;
    msg.DATA[5] = G1_START_SOC_ADD_LSB;
    msg.DATA[6] = (SOC & 0xFF00) >> 8;
    msg.DATA[7] = SOC & 0x00FF;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN1_End_SOC(uint16_t SOC) {

    DOUBLE_BYTE_HEADER();
    msg.DATA[4] = G1_END_SOC_ADD_MSB;
    msg.DATA[5] = G1_END_SOC_ADD_LSB;
    msg.DATA[6] = (SOC & 0xFF00) >> 8;
    msg.DATA[7] = SOC & 0x00FF;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN1_Uint_Consumed(uint32_t units) {

    LONG_BYTE_HEADER();
    msg.DATA[4] = G1_UNIT_CONSUMED_ADD_MSB;
    msg.DATA[5] = G1_UNIT_CONSUMED_ADD_LSB;
    msg.DATA[6] = (units & 0xFF000000) >> 24;
    msg.DATA[7] = (units & 0x00FF0000) >> 16;
    msg.DATA[8] = (units & 0x0000FF00) >> 8;
    msg.DATA[9] = (units & 0x000000FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN1_Booking_ID(uint32_t ID) {

    LONG_BYTE_HEADER();
    msg.DATA[4] = G1_BOOKING_ID_ADD_MSB;
    msg.DATA[5] = G1_BOOKING_ID_ADD_LSB;
    msg.DATA[6] = (ID & 0xFF000000) >> 24;
    msg.DATA[7] = (ID & 0x00FF0000) >> 16;
    msg.DATA[8] = (ID & 0x0000FF00) >> 8;
    msg.DATA[9] = (ID & 0x000000FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN1_Session_End_Reason(uint8_t reason) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = G1_SESSION_END_REASON_ADD_MSB;
    msg.DATA[5] = G1_SESSION_END_REASON_ADD_LSB;
    msg.DATA[7] = reason;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN2_Battery_SOC(uint16_t SOC) {

    DOUBLE_BYTE_HEADER();
    msg.DATA[4] = G2_BATTERY_SOC_ADD_MSB;
    msg.DATA[5] = G2_BATTERY_SOC_ADD_LSB;
    msg.DATA[6] = (SOC & 0xFF00) >> 8;
    msg.DATA[7] = SOC & 0x00FF;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN2_Initial_SOC(uint16_t SOC) {

    DOUBLE_BYTE_HEADER();
    msg.DATA[4] = G2_INITIAL_SOC_ADD_MSB;
    msg.DATA[5] = G2_INITIAL_SOC_ADD_LSB;
    msg.DATA[6] = (SOC & 0xFF00) >> 8;
    msg.DATA[7] = SOC & 0x00FF;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN2_Duration(uint32_t duration) {

    LONG_BYTE_HEADER();
    msg.DATA[4] = G2_DURATION_ADD_MSB;
    msg.DATA[5] = G2_DURATION_ADD_LSB;
    msg.DATA[6] = (duration & 0xFF000000) >> 24;
    msg.DATA[7] = (duration & 0x00FF0000) >> 16;
    msg.DATA[8] = (duration & 0x0000FF00) >> 8;
    msg.DATA[9] = (duration & 0x000000FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN2_Demand_Voltage(uint32_t voltage) {

    LONG_BYTE_HEADER();
    msg.DATA[4] = G2_DEMAND_VOLTAGE_ADD_MSB;
    msg.DATA[5] = G2_DEMAND_VOLTAGE_ADD_LSB;
    msg.DATA[6] = (voltage & 0xFF000000) >> 24;
    msg.DATA[7] = (voltage & 0x00FF0000) >> 16;
    msg.DATA[8] = (voltage & 0x0000FF00) >> 8;
    msg.DATA[9] = (voltage & 0x000000FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN2_Demand_Current(uint32_t current) {

    LONG_BYTE_HEADER();
    msg.DATA[4] = G2_DEMAND_CURRENT_ADD_MSB;
    msg.DATA[5] = G2_DEMAND_CURRENT_ADD_LSB;
    msg.DATA[6] = (current & 0xFF000000) >> 24;
    msg.DATA[7] = (current & 0x00FF0000) >> 16;
    msg.DATA[8] = (current & 0x0000FF00) >> 8;
    msg.DATA[9] = (current & 0x000000FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN2_Voltage(uint32_t voltage) {

    LONG_BYTE_HEADER();
    msg.DATA[4] = G2_VOLTAGE_ADD_MSB;
    msg.DATA[5] = G2_VOLTAGE_ADD_LSB;
    msg.DATA[6] = (voltage & 0xFF000000) >> 24;
    msg.DATA[7] = (voltage & 0x00FF0000) >> 16;
    msg.DATA[8] = (voltage & 0x0000FF00) >> 8;
    msg.DATA[9] = (voltage & 0x000000FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN2_Current(uint32_t current) {

    LONG_BYTE_HEADER();
    msg.DATA[4] = G2_CURRENT_ADD_MSB;
    msg.DATA[5] = G2_CURRENT_ADD_LSB;
    msg.DATA[6] = (current & 0xFF000000) >> 24;
    msg.DATA[7] = (current & 0x00FF0000) >> 16;
    msg.DATA[8] = (current & 0x0000FF00) >> 8;
    msg.DATA[9] = (current & 0x000000FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN2_Total_Power(uint32_t power) {

    LONG_BYTE_HEADER();
    msg.DATA[4] = G2_TOTAL_POWER_ADD_MSB;
    msg.DATA[5] = G2_TOTAL_POWER_ADD_LSB;
    msg.DATA[6] = (power & 0xFF000000) >> 24;
    msg.DATA[7] = (power & 0x00FF0000) >> 16;
    msg.DATA[8] = (power & 0x0000FF00) >> 8;
    msg.DATA[9] = (power & 0x000000FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN2_Charging_Start_date(uint16_t date) {
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x05;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = G2_CHARGING_START_DATE_ADD_MSB;
    msg.DATA[5] = G2_CHARGING_START_DATE_ADD_LSB;
    msg.DATA[6] = (date & 0xFF00) >> 8;
    msg.DATA[7] = (date & 0x00FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN2_Charging_Start_month(uint16_t month) {
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x05;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = G2_CHARGING_START_MONTH_ADD_MSB;
    msg.DATA[5] = G2_CHARGING_START_MONTH_ADD_LSB;
    msg.DATA[6] = (month & 0xFF00) >> 8;
    msg.DATA[7] = (month & 0x00FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN2_Charging_Start_year(uint16_t year) {
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x05;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = G2_CHARGING_START_YEAR_ADD_MSB;
    msg.DATA[5] = G2_CHARGING_START_YEAR_ADD_LSB;
    msg.DATA[6] = (year & 0xFF00) >> 8;
    msg.DATA[7] = (year & 0x00FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN2_Charging_Start_hour(uint16_t hour) {
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x05;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = G2_CHARGING_START_HOUR_ADD_MSB;
    msg.DATA[5] = G2_CHARGING_START_HOUR_ADD_LSB;
    msg.DATA[6] = (hour & 0xFF00) >> 8;
    msg.DATA[7] = (hour & 0x00FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN2_Charging_Start_mins(uint16_t mins) {
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x05;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = G2_CHARGING_START_MIN_ADD_MSB;
    msg.DATA[5] = G2_CHARGING_START_MIN_ADD_LSB;
    msg.DATA[6] = (mins & 0xFF00) >> 8;
    msg.DATA[7] = (mins & 0x00FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN2_Charging_Start_sec(uint16_t sec) {
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x05;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = G2_CHARGING_START_SEC_ADD_MSB;
    msg.DATA[5] = G2_CHARGING_START_SEC_ADD_LSB;
    msg.DATA[6] = (sec & 0xFF00) >> 8;
    msg.DATA[7] = (sec & 0x00FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN2_Charging_Stop_date(uint16_t date) {
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x05;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = G2_CHARGING_STOP_DATE_ADD_MSB;
    msg.DATA[5] = G2_CHARGING_STOP_DATE_ADD_LSB;
    msg.DATA[6] = (date & 0xFF00) >> 8;
    msg.DATA[7] = (date & 0x00FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN2_Charging_Stop_month(uint16_t month) {
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x05;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = G2_CHARGING_STOP_MONTH_ADD_MSB;
    msg.DATA[5] = G2_CHARGING_STOP_MONTH_ADD_LSB;
    msg.DATA[6] = (month & 0xFF00) >> 8;
    msg.DATA[7] = (month & 0x00FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN2_Charging_Stop_year(uint16_t year) {
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x05;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = G2_CHARGING_STOP_YEAR_ADD_MSB;
    msg.DATA[5] = G2_CHARGING_STOP_YEAR_ADD_LSB;
    msg.DATA[6] = (year & 0xFF00) >> 8;
    msg.DATA[7] = (year & 0x00FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN2_Charging_Stop_hour(uint16_t hour) {
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x05;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = G2_CHARGING_STOP_HOUR_ADD_MSB;
    msg.DATA[5] = G2_CHARGING_STOP_HOUR_ADD_LSB;
    msg.DATA[6] = (hour & 0xFF00) >> 8;
    msg.DATA[7] = (hour & 0x00FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN2_Charging_Stop_mins(uint16_t mins) {
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x05;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = G2_CHARGING_STOP_MIN_ADD_MSB;
    msg.DATA[5] = G2_CHARGING_STOP_MIN_ADD_LSB;
    msg.DATA[6] = (mins & 0xFF00) >> 8;
    msg.DATA[7] = (mins & 0x00FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN2_Charging_Stop_sec(uint16_t sec) {
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x05;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = G2_CHARGING_STOP_SEC_ADD_MSB;
    msg.DATA[5] = G2_CHARGING_STOP_SEC_ADD_LSB;
    msg.DATA[6] = (sec & 0xFF00) >> 8;
    msg.DATA[7] = (sec & 0x00FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN2_Start_SOC(uint16_t SOC) {

    DOUBLE_BYTE_HEADER();
    msg.DATA[4] = G2_START_SOC_ADD_MSB;
    msg.DATA[5] = G2_START_SOC_ADD_LSB;
    msg.DATA[6] = (SOC & 0xFF00) >> 8;
    msg.DATA[7] = SOC & 0x00FF;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN2_End_SOC(uint16_t SOC) {

    DOUBLE_BYTE_HEADER();
    msg.DATA[4] = G2_END_SOC_ADD_MSB;
    msg.DATA[5] = G2_END_SOC_ADD_LSB;
    msg.DATA[6] = (SOC & 0xFF00) >> 8;
    msg.DATA[7] = SOC & 0x00FF;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN2_Uint_Consumed(uint32_t units) {

    LONG_BYTE_HEADER();
    msg.DATA[4] = G2_UNIT_CONSUMED_ADD_MSB;
    msg.DATA[5] = G2_UNIT_CONSUMED_ADD_LSB;
    msg.DATA[6] = (units & 0xFF000000) >> 24;
    msg.DATA[7] = (units & 0x00FF0000) >> 16;
    msg.DATA[8] = (units & 0x0000FF00) >> 8;
    msg.DATA[9] = (units & 0x000000FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN2_Booking_ID(uint32_t ID) {

    LONG_BYTE_HEADER();
    msg.DATA[4] = G2_BOOKING_ID_ADD_MSB;
    msg.DATA[5] = G2_BOOKING_ID_ADD_LSB;
    msg.DATA[6] = (ID & 0xFF000000) >> 24;
    msg.DATA[7] = (ID & 0x00FF0000) >> 16;
    msg.DATA[8] = (ID & 0x0000FF00) >> 8;
    msg.DATA[9] = (ID & 0x000000FF);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN2_Session_End_Reason(uint8_t reason) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = G2_SESSION_END_REASON_ADD_MSB;
    msg.DATA[5] = G2_SESSION_END_REASON_ADD_LSB;
    msg.DATA[7] = reason;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_Mains_Fail_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = MAIN_FAIL_ADD_MSB;
    msg.DATA[5] = MAIN_FAIL_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_High_Leakage_Current_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = HIGH_LEAKAGE_ADD_MSB;
    msg.DATA[5] = HIGH_LEAKAGE_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_High_NE_Voltage_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = HIGH_NE_ADD_MSB;
    msg.DATA[5] = HIGH_NE_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_Mains_Low_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = MAINS_LOW_ADD_MSB;
    msg.DATA[5] = MAINS_LOW_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_Mains_High_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = MAINS_HIGH_ADD_MSB;
    msg.DATA[5] = MAINS_HIGH_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_Smoke_Detected_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = SMOKE_DETECTED_ADD_MSB;
    msg.DATA[5] = SMOKE_DETECTED_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_Esd_Pressed_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = ESD_PRESSED_ADD_MSB;
    msg.DATA[5] = ESD_PRESSED_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_Spd_Fault_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = SPD_PRESSED_ADD_MSB;
    msg.DATA[5] = SPD_PRESSED_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_ACEM_Comm_Fail_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = ACEM_COMM_FAIL_ADD_MSB;
    msg.DATA[5] = ACEM_COMM_FAIL_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_System_Temperature_High_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = SYSTEM_TEMP_HIGH_ADD_MSB;
    msg.DATA[5] = SYSTEM_TEMP_HIGH_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_Gun1_stop_btn(void) {
    SINGLE_BIT_HEADER();
    msg.DATA[4] = GUN1_STOP_BTN_ADD_MSB;
    msg.DATA[5] = GUN1_STOP_BTN_ADD_LSB;
    msg.DATA[7] = DATA_1;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);
}

void Update_Gun2_stop_btn(void) {
    SINGLE_BIT_HEADER();
    msg.DATA[4] = GUN2_STOP_BTN_ADD_MSB;
    msg.DATA[5] = GUN2_STOP_BTN_ADD_LSB;
    msg.DATA[7] = DATA_1;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);
}

void Update_All_Rectifier_Comm_Fail_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = ALL_REC_FAIL_ADD_MSB;
    msg.DATA[5] = ALL_REC_FAIL_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_Rectifier1_Comm_Fail_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = REC1_FAIL_ADD_MSB;
    msg.DATA[5] = REC1_FAIL_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_Rectifier2_Comm_Fail_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = REC2_FAIL_ADD_MSB;
    msg.DATA[5] = REC2_FAIL_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_Rectifier3_Comm_Fail_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = REC3_FAIL_ADD_MSB;
    msg.DATA[5] = REC3_FAIL_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_Rectifier4_Comm_Fail_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = REC4_FAIL_ADD_MSB;
    msg.DATA[5] = REC4_FAIL_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_DCEM1_Comm_Fail_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = DCEM1_COMM_FAIL_ADD_MSB;
    msg.DATA[5] = DCEM1_COMM_FAIL_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_DCEM2_Comm_Fail_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = DCEM2_COMM_FAIL_ADD_MSB;
    msg.DATA[5] = DCEM2_COMM_FAIL_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_PLC1_Comm_Fail_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = PLC1_COMM_FAIL_ADD_MSB;
    msg.DATA[5] = PLC1_COMM_FAIL_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_PLC2_Comm_Fail_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = PLC2_COMM_FAIL_ADD_MSB;
    msg.DATA[5] = PLC2_COMM_FAIL_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_Door_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = DOOR_OPEN_ADD_MSB;
    msg.DATA[5] = DOOR_OPEN_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_RFID_Comm_Fail_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = RFID_COMM_FAIL_ADD_MSB;
    msg.DATA[5] = RFID_COMM_FAIL_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_Controller_Fail_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = CONTROLLER_FAIL_ADD_MSB;
    msg.DATA[5] = CONTROLLER_FAIL_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_Isolation_Fail1_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = ISOLATION_FAIL1_ADD_MSB;
    msg.DATA[5] = ISOLATION_FAIL1_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_Isolation_Fail2_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = ISOLATION_FAIL2_ADD_MSB;
    msg.DATA[5] = ISOLATION_FAIL2_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_LED_Board_Fault1_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = LEDBOARD_FAULT1_ADD_MSB;
    msg.DATA[5] = LEDBOARD_FAULT1_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_LED_Board_Fault2_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = LEDBOARD_FAULT2_ADD_MSB;
    msg.DATA[5] = LEDBOARD_FAULT2_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_HMI_Comm_Fail_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = HMI_COMM_FAIL_ADD_MSB;
    msg.DATA[5] = HMI_COMM_FAIL_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_Modem_Comm_Fail_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = MODEM_COMM_FAIL_ADD_MSB;
    msg.DATA[5] = MODEM_COMM_FAIL_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN1_Temp_High_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = GUN1_TEMP_HIGH_ADD_MSB;
    msg.DATA[5] = GUN1_TEMP_HIGH_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN2_Temp_High_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = GUN2_TEMP_HIGH_ADD_MSB;
    msg.DATA[5] = GUN2_TEMP_HIGH_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_DC_Under_Volt1_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = DC_UNDERVOLTAGE1_ADD_MSB;
    msg.DATA[5] = DC_UNDERVOLTAGE1_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_DC_Over_Volt1_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = DC_OVERVOLTAGE1_ADD_MSB;
    msg.DATA[5] = DC_OVERVOLTAGE1_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_DC_Output_Over_Current1_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = DC_OUT_OVERCURRENT1_ADD_MSB;
    msg.DATA[5] = DC_OUT_OVERCURRENT1_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_DC_Under_Volt2_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = DC_UNDERVOLTAGE2_ADD_MSB;
    msg.DATA[5] = DC_UNDERVOLTAGE2_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_DC_Over_Volt2_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = DC_OVERVOLTAGE2_ADD_MSB;
    msg.DATA[5] = DC_OVERVOLTAGE2_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_DC_Output_Over_Current2_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = DC_OUT_OVERCURRENT2_ADD_MSB;
    msg.DATA[5] = DC_OUT_OVERCURRENT2_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_Rectifier1_Fault_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = REC1_FAULT_ADD_MSB;
    msg.DATA[5] = REC1_FAULT_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_Rectifier2_Fault_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = REC2_FAULT_ADD_MSB;
    msg.DATA[5] = REC2_FAULT_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_Rectifier3_Fault_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = REC3_FAULT_ADD_MSB;
    msg.DATA[5] = REC3_FAULT_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_Rectifier4_Fault_Status(uint8_t status) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = REC4_FAULT_ADD_MSB;
    msg.DATA[5] = REC4_FAULT_ADD_LSB;
    msg.DATA[7] = status;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN1_Battery_Percent(uint8_t percent) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = GUN1_BATTERY_PERCENT_ADD_MSB;
    msg.DATA[5] = GUN1_BATTERY_PERCENT_ADD_LSB;
    msg.DATA[7] = percent;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN2_Battery_Percent(uint8_t percent) {

    SINGLE_BIT_HEADER();
    msg.DATA[4] = GUN2_BATTERY_PERCENT_ADD_MSB;
    msg.DATA[5] = GUN2_BATTERY_PERCENT_ADD_LSB;
    msg.DATA[7] = percent;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_Rec1_temp(uint8_t temp) {
    SINGLE_BIT_HEADER();
    msg.DATA[4] = REC1_TEMP_ADD_MSB;
    msg.DATA[5] = REC1_TEMP_ADD_LSB;
    msg.DATA[7] = temp;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);
}

void Update_Rec2_temp(uint8_t temp) {
    SINGLE_BIT_HEADER();
    msg.DATA[4] = REC2_TEMP_ADD_MSB;
    msg.DATA[5] = REC2_TEMP_ADD_LSB;
    msg.DATA[7] = temp;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);
}

void Update_Ambient_Temp(uint16_t temp) {

    DOUBLE_BYTE_HEADER();
    msg.DATA[4] = AMBIENT_TEMP_ADD_MSB;
    msg.DATA[5] = AMBIENT_TEMP_ADD_LSB;
    msg.DATA[6] = temp >> 8;
    msg.DATA[7] = temp & 0x00FF;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_RSSI_Value(uint16_t rssi) {

    DOUBLE_BYTE_HEADER();
    msg.DATA[4] = RSSI_VALUE_ADD_MSB;
    msg.DATA[5] = RSSI_VALUE_ADD_LSB;
    msg.DATA[6] = rssi >> 8;
    msg.DATA[7] = rssi & 0x00FF;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN1_Temp(uint16_t temp) {

    DOUBLE_BYTE_HEADER();
    msg.DATA[4] = GUN1_TEMP_ADD_MSB;
    msg.DATA[5] = GUN1_TEMP_ADD_LSB;
    msg.DATA[6] = temp >> 8;
    msg.DATA[7] = temp & 0x00FF;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_GUN2_Temp(uint16_t temp) {

    DOUBLE_BYTE_HEADER();
    msg.DATA[4] = GUN2_TEMP_ADD_MSB;
    msg.DATA[5] = GUN2_TEMP_ADD_LSB;
    msg.DATA[6] = temp >> 8;
    msg.DATA[7] = temp & 0x00FF;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_MCU_FW_VERSION(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4, uint8_t data5, uint8_t data6) {

    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x09;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = 0x10;
    msg.DATA[5] = 0x96;
    msg.DATA[6] = data1;
    msg.DATA[7] = data2;
    msg.DATA[8] = data3;
    msg.DATA[9] = data4;
    msg.DATA[10] = data5;
    msg.DATA[11] = data6;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_OCPP_FW_VERSION(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4, uint8_t data5, uint8_t data6) {

    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x09;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = 0x10;
    msg.DATA[5] = 0x9C;
    msg.DATA[6] = data1;
    msg.DATA[7] = data2;
    msg.DATA[8] = data3;
    msg.DATA[9] = data4;
    msg.DATA[10] = data5;
    msg.DATA[11] = data6;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_PLC1_FW_VERSION(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4, uint8_t data5, uint8_t data6) {

    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x09;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = 0x10;
    msg.DATA[5] = 0xA2;
    msg.DATA[6] = data1;
    msg.DATA[7] = data2;
    msg.DATA[8] = data3;
    msg.DATA[9] = data4;
    msg.DATA[10] = data5;
    msg.DATA[11] = data6;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_PLC2_FW_VERSION(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4, uint8_t data5, uint8_t data6) {

    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x09;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = 0x10;
    msg.DATA[5] = 0xA8;
    msg.DATA[6] = data1;
    msg.DATA[7] = data2;
    msg.DATA[8] = data3;
    msg.DATA[9] = data4;
    msg.DATA[10] = data5;
    msg.DATA[11] = data6;
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);




}

void Update_OCPP_ID(uint8_t data[]) {
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x21;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = OCPP_ID_ADD_MSB;
    msg.DATA[5] = OCPP_ID_ADD_LSB;
    memcpy(&msg.DATA[6], data, 30);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);
}

void Update_BLE_ID(uint8_t data[]) {
    msg.DATA[0] = 0x5A;
    msg.DATA[1] = 0xA5;
    msg.DATA[2] = 0x21;
    msg.DATA[3] = 0x82;
    msg.DATA[4] = BLE_ID_ADD_MSB;
    msg.DATA[5] = BLE_ID_ADD_LSB;
    memcpy(&msg.DATA[6], data, 30);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);
}

void Update_Rec1_status(uint8_t data[]) {
    LONG_BYTE_HEADER();
    msg.DATA[4] = REC1_STATUS_ADD_MSB;
    msg.DATA[5] = REC1_STATUS_ADD_LSB;
    memcpy(&msg.DATA[6], data, 4);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);
}

void Update_Rec2_status(uint8_t data[]) {
    LONG_BYTE_HEADER();
    msg.DATA[4] = REC2_STATUS_ADD_MSB;
    msg.DATA[5] = REC2_STATUS_ADD_LSB;
    memcpy(&msg.DATA[6], data, 4);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);
}

void Update_Rec3_status(uint8_t data[]) {
    LONG_BYTE_HEADER();
    msg.DATA[4] = REC3_STATUS_ADD_MSB;
    msg.DATA[5] = REC3_STATUS_ADD_LSB;
    memcpy(&msg.DATA[6], data, 4);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);
}

void Update_Rec4_status(uint8_t data[]) {
    LONG_BYTE_HEADER();
    msg.DATA[4] = REC4_STATUS_ADD_MSB;
    msg.DATA[5] = REC4_STATUS_ADD_LSB;
    memcpy(&msg.DATA[6], data, 4);
    xQueueSend(HMI_SEND_QUEUE, &msg, 100);
}

