#include "UUGreenRectifier.h"
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

static uint8_t CAN1_txfif1[CAN1_TX_FIFO_BUFFER_SIZE];

CAN_TX_BUFFER *CAN1_txbuffer = NULL;
CAN_RX_BUFFER *CAN1_rxbuffer = NULL;

/**
 * @brief Turn ON rectifier module
 *
 * @param rAddr
 * @return true
 * @return false
 */
bool rectifierPowerOn(uint32_t rAddr) {
    bool bStatus = false;
    memset(CAN1_txfif1, 0x00, CAN1_TX_FIFO_BUFFER_ELEMENT_SIZE);
    CAN1_txbuffer = (CAN_TX_BUFFER *) CAN1_txfif1;
    CAN1_txbuffer->id = rAddr;
    CAN1_txbuffer->xtd = 1;
    CAN1_txbuffer->dlc = 8;
    memset(CAN1_txbuffer->data, 0, 8);

    CAN1_txbuffer->data[0] = SET_DATA;
    CAN1_txbuffer->data[1] = POWER_MODULE;
    /*payload to power on the module is 0x00*/
    if (CAN1_MessageTransmitFifo(1, CAN1_txbuffer) == true) {
        ;
    }
//    memset(CAN1_rxFiFo0, 0x00, (1 * CAN1_RX_FIFO0_ELEMENT_SIZE));
//    if (CAN1_MessageReceiveFifo(CAN_RX_FIFO_0, 1, (CAN_RX_BUFFER *) CAN1_rxFiFo0) == true) {
//        bStatus = true;
//    }
    //vTaskDelay(200/portTICK_PERIOD_MS);
    return bStatus;
} // rectifierPowerOn

bool rectifierPowerOn_2(uint32_t rAddr) {
    bool bStatus = false;
    memset(CAN1_txfif1, 0x00, CAN1_TX_FIFO_BUFFER_ELEMENT_SIZE);
    CAN1_txbuffer = (CAN_TX_BUFFER *) CAN1_txfif1;
    CAN1_txbuffer->id = rAddr;
    CAN1_txbuffer->xtd = 1;
    CAN1_txbuffer->dlc = 8;
    memset(CAN1_txbuffer->data, 0, 8);

    CAN1_txbuffer->data[0] = SET_DATA_2;
    CAN1_txbuffer->data[1] = POWER_MODULE;
    /*payload to power on the module is 0x00*/
    if (CAN1_MessageTransmitFifo(1, CAN1_txbuffer) == true) {
        ;
    }
//    memset(CAN1_rxFiFo0, 0x00, (1 * CAN1_RX_FIFO0_ELEMENT_SIZE));
//    if (CAN1_MessageReceiveFifo(CAN_RX_FIFO_0, 1, (CAN_RX_BUFFER *) CAN1_rxFiFo0) == true) {
//        bStatus = true;
//    }
    //vTaskDelay(200/portTICK_PERIOD_MS);
    return bStatus;
} // rectifierPowerOn

/**
 * @brief Turn OFF rectifier module
 *
 * @param rAddr
 * @return true
 * @return false
 */
bool rectifierPowerOff(uint32_t rAddr) {
    bool bStatus = false;
//    memset(CAN1_txfif0, 0x00, CAN1_TX_FIFO_BUFFER_ELEMENT_SIZE);
//    CAN1_txbuffer = (CAN_TX_BUFFER *) CAN1_txfif0;
    CAN1_txbuffer->id = rAddr;
    CAN1_txbuffer->dlc = 8;
    CAN1_txbuffer->xtd = 1;
    memset(CAN1_txbuffer->data, 0, CAN1_txbuffer->dlc);
    CAN1_txbuffer->data[0] = SET_DATA;
    CAN1_txbuffer->data[1] = POWER_MODULE;
    /*payload to shut down module*/
    CAN1_txbuffer->data[7] = 0x01;
    if (CAN1_MessageTransmitFifo(1, CAN1_txbuffer) == true) {
        ;
    }
//    memset(CAN1_rxFiFo0, 0x00, (1 * CAN1_RX_FIFO0_ELEMENT_SIZE));
//    if (CAN1_MessageReceiveFifo(CAN_RX_FIFO_0, 1, (CAN_RX_BUFFER *) CAN1_rxFiFo0) == true) {
//        bStatus = true;
//    }
    //vTaskDelay(200/portTICK_PERIOD_MS);
    return bStatus;
} // rectifierPowerOff

bool rectifierPowerOff_2(uint32_t rAddr) {
    bool bStatus = false;
//    memset(CAN1_txfif0, 0x00, CAN1_TX_FIFO_BUFFER_ELEMENT_SIZE);
//    CAN1_txbuffer = (CAN_TX_BUFFER *) CAN1_txfif0;
    CAN1_txbuffer->id = rAddr;
    CAN1_txbuffer->dlc = 8;
    CAN1_txbuffer->xtd = 1;
    memset(CAN1_txbuffer->data, 0, CAN1_txbuffer->dlc);
    CAN1_txbuffer->data[0] = SET_DATA_2;
    CAN1_txbuffer->data[1] = POWER_MODULE;
    /*payload to shut down module*/
    CAN1_txbuffer->data[7] = 0x01;
    if (CAN1_MessageTransmitFifo(1, CAN1_txbuffer) == true) {
        ;
    }
//    memset(CAN1_rxFiFo0, 0x00, (1 * CAN1_RX_FIFO0_ELEMENT_SIZE));
//    if (CAN1_MessageReceiveFifo(CAN_RX_FIFO_0, 1, (CAN_RX_BUFFER *) CAN1_rxFiFo0) == true) {
//        bStatus = true;
//    }
    //vTaskDelay(200/portTICK_PERIOD_MS);
    return bStatus;
} // rectifierPowerOff

/**
 * @brief Set the Rectifier Voltage object
 *
 * @param rAddr
 * @param nVoltage
 * @return true
 * @return false
 */
bool setRectifierVoltage(uint32_t rAddr, uint32_t nVoltage) {
    bool bStatus = false;
    memset(CAN1_txfif1, 0x00, CAN1_TX_FIFO_BUFFER_ELEMENT_SIZE);
    CAN1_txbuffer = (CAN_TX_BUFFER *) CAN1_txfif1;
    CAN1_txbuffer->id = rAddr;
    CAN1_txbuffer->xtd = 1;
    CAN1_txbuffer->dlc = 8;
    memset(CAN1_txbuffer->data, 0, CAN1_txbuffer->dlc);
    CAN1_txbuffer->data[0] = SET_DATA;
    CAN1_txbuffer->data[1] = MODULE_OUTPUT_REFERENCE_VOLTAGE;
    CAN1_txbuffer->data[4] = (uint8_t) (nVoltage >> 24);
    CAN1_txbuffer->data[5] = (uint8_t) (nVoltage >> 16);
    CAN1_txbuffer->data[6] = (uint8_t) (nVoltage >> 8);
    CAN1_txbuffer->data[7] = (uint8_t) (nVoltage);
    if (CAN1_MessageTransmitFifo(1, CAN1_txbuffer) == true) {
        ;
    }
//    memset(CAN1_rxFiFo0, 0x00, (1 * CAN1_RX_FIFO0_ELEMENT_SIZE));
//    if (CAN1_MessageReceiveFifo(CAN_RX_FIFO_0, 1, (CAN_RX_BUFFER *) CAN1_rxFiFo0) == true) {
//        bStatus = true;
//    }
    //vTaskDelay(200/portTICK_PERIOD_MS);
    return bStatus;
} // setRectifierVoltage

bool setRectifierVoltage_2(uint32_t rAddr, uint32_t nVoltage) {
    bool bStatus = false;
    memset(CAN1_txfif1, 0x00, CAN1_TX_FIFO_BUFFER_ELEMENT_SIZE);
    CAN1_txbuffer = (CAN_TX_BUFFER *) CAN1_txfif1;
    CAN1_txbuffer->id = rAddr;
    CAN1_txbuffer->xtd = 1;
    CAN1_txbuffer->dlc = 8;
    memset(CAN1_txbuffer->data, 0, CAN1_txbuffer->dlc);
    CAN1_txbuffer->data[0] = SET_DATA_2;
    CAN1_txbuffer->data[1] = MODULE_OUTPUT_REFERENCE_VOLTAGE;
    CAN1_txbuffer->data[4] = (uint8_t) (nVoltage >> 24);
    CAN1_txbuffer->data[5] = (uint8_t) (nVoltage >> 16);
    CAN1_txbuffer->data[6] = (uint8_t) (nVoltage >> 8);
    CAN1_txbuffer->data[7] = (uint8_t) (nVoltage);
    if (CAN1_MessageTransmitFifo(1, CAN1_txbuffer) == true) {
        ;
    }
//    memset(CAN1_rxFiFo0, 0x00, (1 * CAN1_RX_FIFO0_ELEMENT_SIZE));
//    if (CAN1_MessageReceiveFifo(CAN_RX_FIFO_0, 1, (CAN_RX_BUFFER *) CAN1_rxFiFo0) == true) {
//        bStatus = true;
//    }
    //vTaskDelay(200/portTICK_PERIOD_MS);
    return bStatus;
} // setRectifierVoltage

/**
 * @brief Set the Rectifier Current object
 *
 * @param rAddr
 * @param nCurrent
 * @return true
 * @return false
 */
void setRectifierCurrent(uint32_t rAddr, uint32_t nCurrent) {
    bool bStatus = false;

    
    CAN1_txbuffer->xtd = 1;
    CAN1_txbuffer->id = rAddr;
    CAN1_txbuffer->dlc = 8;
    CAN1_txbuffer->xtd = 1;
        CAN1_txbuffer->data[0] = SET_DATA;
    CAN1_txbuffer->data[1] = MODULE_OUTPUT_CURRENT_LIMIT;
    CAN1_txbuffer->data[4] = (uint8_t) (nCurrent >> 24);
    CAN1_txbuffer->data[5] = (uint8_t) (nCurrent >> 16);
    CAN1_txbuffer->data[6] = (uint8_t) (nCurrent >> 8);
    CAN1_txbuffer->data[7] = (uint8_t) (nCurrent);
    bStatus = CAN1_MessageTransmitFifo(1, CAN1_txbuffer);
//    printf("TRANSMIT VALUE = %d\r\n",bStatus);
} // setRectifierCurrent

void setRectifierCurrent_2(uint32_t rAddr, uint32_t nCurrent) {
    bool bStatus = false;

    
    CAN1_txbuffer->xtd = 1;
    CAN1_txbuffer->id = rAddr;
    CAN1_txbuffer->dlc = 8;
    CAN1_txbuffer->xtd = 1;
        CAN1_txbuffer->data[0] = SET_DATA_2;
    CAN1_txbuffer->data[1] = MODULE_OUTPUT_CURRENT_LIMIT;
    CAN1_txbuffer->data[4] = (uint8_t) (nCurrent >> 24);
    CAN1_txbuffer->data[5] = (uint8_t) (nCurrent >> 16);
    CAN1_txbuffer->data[6] = (uint8_t) (nCurrent >> 8);
    CAN1_txbuffer->data[7] = (uint8_t) (nCurrent);
    bStatus = CAN1_MessageTransmitFifo(1, CAN1_txbuffer);
//    printf("TRANSMIT VALUE = %d\r\n",bStatus);
} // setRectifierCurrent

/**
 * @brief Get the Rectifier Voltage object
 *
 * @param rAddr
 * @param rVoltage
 * @return true
 * @return false
 */
bool getRectifierVoltage(uint32_t rAddr, uint32_t *rVoltage) {
    bool bStatus = false;
    uint8_t read_voltage[4];
    memset(CAN1_txfif1, 0x00, CAN1_TX_FIFO_BUFFER_ELEMENT_SIZE);
    CAN1_txbuffer = (CAN_TX_BUFFER *) CAN1_txfif1;
    CAN1_txbuffer->xtd = 1;
    CAN1_txbuffer->id = rAddr;
    CAN1_txbuffer->dlc = 8;
    CAN1_txbuffer->xtd = 1;
    memset(CAN1_txbuffer->data, 0, CAN1_txbuffer->dlc);
    CAN1_txbuffer->data[0] = READ_DATA;
    CAN1_txbuffer->data[1] = MODULE_OUTPUT_VOLTAGE;
    if (CAN1_MessageTransmitFifo(1, CAN1_txbuffer) == true) {
        ;
    }
//    memset(CAN1_rxFiFo1, 0x00, (1 * CAN1_RX_FIFO0_ELEMENT_SIZE));
//    if (CAN1_MessageReceiveFifo(CAN_RX_FIFO_0, 1, (CAN_RX_BUFFER *) CAN1_rxFiFo1) == true) {
//        CAN1_rxbuffer = (CAN_RX_BUFFER *) CAN1_rxFiFo1;
//        /* big endian format */
//        read_voltage[0] = CAN1_rxbuffer->data[7];
//        read_voltage[1] = CAN1_rxbuffer->data[6];
//        read_voltage[2] = CAN1_rxbuffer->data[5];
//        read_voltage[3] = CAN1_rxbuffer->data[4];
//        bStatus = true;
//    }
//    memcpy(rVoltage, read_voltage, sizeof (read_voltage));
    //vTaskDelay(200/portTICK_PERIOD_MS);
    return bStatus;
} // getRectifierVoltage

/**
 * @brief Get the Rectifier Current object
 * 
 * @param rAddr 
 * @param rCurrent 
 * @return true 
 * @return false 
 */
bool getRectifierCurrent(uint32_t rAddr, uint32_t *rCurrent) {
    bool bStatus = false;
    uint8_t read_current[4];
    memset(CAN1_txfif1, 0x00, CAN1_TX_FIFO_BUFFER_ELEMENT_SIZE);
    CAN1_txbuffer = (CAN_TX_BUFFER *) CAN1_txfif1;
    CAN1_txbuffer->xtd = 1;
    CAN1_txbuffer->id = rAddr;
    CAN1_txbuffer->dlc = 8;
    CAN1_txbuffer->xtd = 1;
    memset(CAN1_txbuffer->data, 0, CAN1_txbuffer->dlc);
    CAN1_txbuffer->data[0] = READ_DATA;
    CAN1_txbuffer->data[1] = MODULE_OUTPUT_CURRENT;
    if (CAN1_MessageTransmitFifo(1, CAN1_txbuffer) == true) {
        ;
    }
//    memset(CAN1_rxFiFo1, 0x00, (1 * CAN1_RX_FIFO0_ELEMENT_SIZE));
//    if (CAN1_MessageReceiveFifo(CAN_RX_FIFO_0, 1, (CAN_RX_BUFFER *) CAN1_rxFiFo1) == true) {
//        CAN1_rxbuffer = (CAN_RX_BUFFER *) CAN1_rxFiFo1;
//        /* big endian format */
//        read_current[0] = CAN1_rxbuffer->data[7];
//        read_current[1] = CAN1_rxbuffer->data[6];
//        read_current[2] = CAN1_rxbuffer->data[5];
//        read_current[3] = CAN1_rxbuffer->data[4];
//        bStatus = true;
//    }
//    memcpy(rCurrent, read_current, sizeof (read_current));
    //vTaskDelay(200/portTICK_PERIOD_MS);
    return bStatus;
}//getRectifierCurrent

/**
 * @brief Get the Rectifier Status register
 * 
 * @param rAddr
 * @return 
 */
uint32_t getRectifierStatus(uint32_t rAddr) {
    
    uint8_t read_status[4];
    uint32_t statusBits;
    memset(CAN1_txfif1, 0x00, CAN1_TX_FIFO_BUFFER_ELEMENT_SIZE);
    CAN1_txbuffer = (CAN_TX_BUFFER *) CAN1_txfif1;
    CAN1_txbuffer->id = rAddr;
    CAN1_txbuffer->dlc = 8;
    CAN1_txbuffer->xtd = 1;
    memset(CAN1_txbuffer->data, 0, CAN1_txbuffer->dlc);
    CAN1_txbuffer->data[0] = READ_DATA;
    CAN1_txbuffer->data[1] = MODULE_STATUS_FLAG;
    if (CAN1_MessageTransmitFifo(1, CAN1_txbuffer) == true) {
        ;
    }
//    memset(CAN1_rxFiFo1, 0x00, (1 * CAN1_RX_FIFO0_ELEMENT_SIZE));
//    if (CAN1_MessageReceiveFifo(CAN_RX_FIFO_0, 1, (CAN_RX_BUFFER *) CAN1_rxFiFo1) == true) {
//        CAN1_rxbuffer = (CAN_RX_BUFFER *) CAN1_rxFiFo1;
//        read_status[0] = CAN1_rxbuffer->data[7];
//        read_status[1] = CAN1_rxbuffer->data[6];
//        read_status[2] = CAN1_rxbuffer->data[5];
//        read_status[3] = CAN1_rxbuffer->data[4];
//    }
//    memcpy(&statusBits, read_status, sizeof (read_status));
    //vTaskDelay(200/portTICK_PERIOD_MS);
    return statusBits;
}//getRectifierStatus

uint32_t getRectifierStatus_2(uint32_t rAddr) {
    
    uint8_t read_status[4];
    uint32_t statusBits;
    memset(CAN1_txfif1, 0x00, CAN1_TX_FIFO_BUFFER_ELEMENT_SIZE);
    CAN1_txbuffer = (CAN_TX_BUFFER *) CAN1_txfif1;
    CAN1_txbuffer->id = rAddr;
    CAN1_txbuffer->dlc = 8;
    CAN1_txbuffer->xtd = 1;
    memset(CAN1_txbuffer->data, 0, CAN1_txbuffer->dlc);
    CAN1_txbuffer->data[0] = READ_DATA_2;
    CAN1_txbuffer->data[1] = MODULE_STATUS_FLAG;
    if (CAN1_MessageTransmitFifo(1, CAN1_txbuffer) == true) {
        ;
    }
//    memset(CAN1_rxFiFo1, 0x00, (1 * CAN1_RX_FIFO0_ELEMENT_SIZE));
//    if (CAN1_MessageReceiveFifo(CAN_RX_FIFO_0, 1, (CAN_RX_BUFFER *) CAN1_rxFiFo1) == true) {
//        CAN1_rxbuffer = (CAN_RX_BUFFER *) CAN1_rxFiFo1;
//        read_status[0] = CAN1_rxbuffer->data[7];
//        read_status[1] = CAN1_rxbuffer->data[6];
//        read_status[2] = CAN1_rxbuffer->data[5];
//        read_status[3] = CAN1_rxbuffer->data[4];
//    }
//    memcpy(&statusBits, read_status, sizeof (read_status));
    //vTaskDelay(200/portTICK_PERIOD_MS);
    return statusBits;
}//getRectifierStatus

/**
 * @brief Set the Rectifier High voltage mode ON/OFF
 * 
 * @param rAddr
 * @param vMode (0:OFF, 1: ON)
 * @return 
 */
bool setRectifierVoltMode(uint32_t rAddr, high_low_v_mode vMode)
{
    bool bStatus = false;
	memset(CAN1_txfif1, 0x00, CAN1_TX_FIFO_BUFFER_ELEMENT_SIZE);
    CAN1_txbuffer = (CAN_TX_BUFFER *)CAN1_txfif1;
    CAN1_txbuffer->id = rAddr;
    CAN1_txbuffer->xtd = 1;
    CAN1_txbuffer->dlc = 8;
    memset(CAN1_txbuffer->data, 0, CAN1_txbuffer->dlc);
	CAN1_txbuffer->data[0] = SET_DATA;
	CAN1_txbuffer->data[1] = MODE_SELECTION;
	CAN1_txbuffer->data[7] = vMode;
	if (CAN1_MessageTransmitFifo(1, CAN1_txbuffer) == true){ 
	        ;
        }
//	memset(CAN1_rxFiFo1, 0x00, (1* CAN1_RX_FIFO0_ELEMENT_SIZE));	
//    if (CAN1_MessageReceiveFifo(CAN_RX_FIFO_0,1, (CAN_RX_BUFFER *)CAN1_rxFiFo1) == true){
//		bStatus = true;
//	}
    //vTaskDelay(200/portTICK_PERIOD_MS);
	return bStatus;		
}//setRectifierVoltMode

