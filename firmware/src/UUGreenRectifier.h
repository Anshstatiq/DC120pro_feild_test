/**
 * @author			 : @anmol.aggarwal
 * @company			 : @statiq.in
 * @description      : This header file is amde for CAN 0 peripheral of microchip controllers. 
 * @Can baudrate     : 125 kbps
 * @peripheral clock : 1MHz
 */

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes

#ifndef  _UUGREEN_RECTIFIER_H_
#define  _UUGREEN_RECTIFIER_H_

#define RECTIFIER1_GROUP1      0x02204000 
#define RESP_RECTIFIER1_GROUP1      35677097
#define RECTIFIER2_GROUP1      0x02208000  
#define RESP_RECTIFIER2_GROUP1      35693171
#define RECTIFIER1_GROUP2      0x0220C000
#define RESP_RECTIFIER1_GROUP2      35708013
#define RECTIFIER2_GROUP2      0x02210000
#define RESP_RECTIFIER2_GROUP2      35724390

#define SET_DATA             	0x10
#define SET_DATA_RESPONSE    	0x11
#define READ_DATA            	0x12
#define READ_DATA_RESPONSE   	0x13
#define READ_SERIAL          	0x14

#define SET_DATA_2             	0x20
#define SET_DATA_RESPONSE_2    	0x21
#define READ_DATA_2            	0x22
#define READ_DATA_RESPONSE_2   	0x23
#define READ_SERIAL_2          	0x24


typedef enum {

	MODULE_OUTPUT_VOLTAGE 				= 0,
	MODULE_OUTPUT_CURRENT,
	MODULE_OUTPUT_REFERENCE_VOLTAGE,
	MODULE_OUTPUT_CURRENT_LIMIT,
	POWER_MODULE,
	SERIAL,
	MODULE_STATUS_FLAG 					= 8,
	VOLTAGE_AB 							= 20,
	VOLTAGE_BC 							= 21,
	VOLTAGE_AC 							= 22,
	INLET_TEMPERATURE 					= 30,
	GROUP_ADDRESS 						= 89,
	MODE_SELECTION 						= 95,
	MODE_STATUS 						= 96,
	OUTPUT_CURRENT_CAPABILITY 			= 104

}RECTIFIER_COMMAND_TYPE;

typedef struct {
	uint8_t AcOV				:1; // 0 AC input overvoltage
	uint8_t AcUV				:1; // 1 AC input undervoltage
	uint8_t AcOVDisconnected	:1; // 2 AC input overvoltage shutdown (disconnect)
	uint8_t PfcOV				:1; // 3 PFC Bus Over voltage
	uint8_t PfcUV				:1; // 4 PFC Bus Under voltage
	uint8_t PfcUnbalance		:1; // 5 PFC Bus Unbalance
	uint8_t DcOV				:1; // 6 DC output overvoltage
	uint8_t DcOVShutDown		:1; // 7 DC output overvoltage shutdown
	uint8_t DcUV				:1; // 8 DC output undervoltage
	uint8_t FanNotRun			:1; // 9 fan failure
	uint8_t Reserved_10			:1; // 10
	uint8_t FanDriverFail		:1; // 11 Fan driver Fail
	uint8_t AmbientOT			:1; // 12 Ambient temperature over temperature protection
	uint8_t AmbientUT			:1; // 13Ambient temperature under temperature protection
	uint8_t Pfc1_OT				:1; // 14 PFC over temperature protection 1
	uint8_t OutputRelayFault	:1; // 15 Ouput Relay Fault
	uint8_t Dcdc1_OT			:1; // 16 DC over temperature protection 1
	uint8_t Reserved_17			:1; // 17 Reserved
	uint8_t SciIsNotOK			:1; // 18 Communication failure between PFC and DCDC
	uint8_t Reserved_19			:1; // 19
	uint8_t PfcFail				:1; // 20 PFC fault
	uint8_t DcdcFail			:1; // 21 DCDC failure
	uint8_t Reserved_22			:1; // 22
	uint8_t Reserved_23			:1; // 23
	uint8_t Reserved_24			:1; // 24
	uint8_t DcdcNotRun			:1; // 25 power on / off
	uint8_t Reserved_2627		:2; // 26:27 Output loop status
	uint8_t DcVoltageUnbalance	:1; // 28 DC ouput Voltage Unbalance
	uint8_t GetSameSN			:1; // 29 Modules with the same serial number were found
	uint8_t Reserved_30			:1; // 30
	uint8_t ModuleFail			:1; // 31 Bleeder Not Work
}MODULE_STATUS_BITS;

typedef union {

uint32_t  status_reg;
MODULE_STATUS_BITS statusBits;

}RECTIFIER_STATUS_REG;

typedef enum {
    LOW_V_MODE = 0,
    HIGH_V_MODE
}high_low_v_mode;

bool setRectifierVoltage(uint32_t, uint32_t);
bool setRectifierVoltage_2(uint32_t, uint32_t);
void setRectifierCurrent(uint32_t, uint32_t);
void setRectifierCurrent_2(uint32_t, uint32_t);
bool getRectifierVoltage(uint32_t, uint32_t*);
bool getRectifierCurrent(uint32_t, uint32_t*);
bool rectifierPowerOn(uint32_t);
bool rectifierPowerOff(uint32_t);
bool rectifierPowerOn_2(uint32_t);
bool rectifierPowerOff_2(uint32_t);
uint32_t getRectifierStatus(uint32_t);
uint32_t getRectifierStatus_2(uint32_t);
bool setRectifierVoltMode(uint32_t, high_low_v_mode);

#endif /* _UUGREEN_RECTIFIER_H_ */