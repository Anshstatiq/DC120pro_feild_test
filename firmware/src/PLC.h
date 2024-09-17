

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true

#include "definitions.h"

#define CHARGING_NONE	3
#define CHARGING_COMPLETE	1
#define CHARGING_NOT_COMPLETE	0
#define PLC_STATE_IDLE_1	0
#define PLC_STATE_IDLE_2	1
#define PLC_STATE_INITIALIZED_1	2
#define PLC_STATE_INITIALIZED_2	3
#define PLC_STATE_WAITING_FOR_PLUG_IN	4
#define PLC_STATE_WAITING_SLAC	5
#define PLC_STATE_PROCESSING_SLAC	6
#define PLC_STATE_SDP	7
#define PLC_STATE_ESTABLISHING_TCP	8
#define PLC_STATE_COMMON_ERROR	9
#define PLC_STATE_SAP_SESSION_SERVICEDISCOVERY	10
#define PLC_STATE_SERVICE_DETAIL	11
#define PLC_STATE_PAYMENT_SERVICE_SELECTION	12
#define PLC_STATE_CERTIFICATE_INSTALL	13
#define PLC_STATE_CERTIFICATE_UPDATE	14
#define PLC_STATE_PAYMENT_DETAILS	15
#define PLC_STATE_AUTHORIZATION_EIM	16
#define PLC_STATE_AUTHORIZATION_PNC	17
#define PLC_STATE_CHARGE_PARAMETER_DISCOVERY	18
#define PLC_STATE_CABLE_CHECK	19
#define PLC_STATE_PRE_CHARGE	20
#define PLC_STATE_POWER_DELIVERED	21
#define PLC_STATE_CURRENT_DEMAND_1	22
#define PLC_STATE_CURRENT_DEMAND_2	23
#define PLC_STATE_CURRENT_DEMAND_3	24
#define PLC_STATE_POWER_DELIVERY_RENOGOTIATE	25
#define PLC_STATE_POWER_DELIVERY_EVINITSTOP	26
#define PLC_STATE_POWER_DELIVERY_EVSEINITSTOP	27
#define PLC_STATE_WELDING_DETECTION	28
#define PLC_STATE_SESSION_STOP	29
#define PLC_STATE_TERMINATED	30
#define PLC_STATE_ERROR_STATE	31

#define _2_CHARGING_NONE	3
#define _2_CHARGING_COMPLETE	1
#define _2_CHARGING_NOT_COMPLETE	0
#define _2_PLC_STATE_IDLE_1	0
#define _2_PLC_STATE_IDLE_2	1
#define _2_PLC_STATE_INITIALIZED_1	2
#define _2_PLC_STATE_INITIALIZED_2	3
#define _2_PLC_STATE_WAITING_FOR_PLUG_IN	4
#define _2_PLC_STATE_WAITING_SLAC	5
#define _2_PLC_STATE_PROCESSING_SLAC	6
#define _2_PLC_STATE_SDP	7
#define _2_PLC_STATE_ESTABLISHING_TCP	8
#define _2_PLC_STATE_COMMON_ERROR	9
#define _2_PLC_STATE_SAP_SESSION_SERVICEDISCOVERY	10
#define _2_PLC_STATE_SERVICE_DETAIL	11
#define _2_PLC_STATE_PAYMENT_SERVICE_SELECTION	12
#define _2_PLC_STATE_CERTIFICATE_INSTALL	13
#define _2_PLC_STATE_CERTIFICATE_UPDATE	14
#define _2_PLC_STATE_PAYMENT_DETAILS	15
#define _2_PLC_STATE_AUTHORIZATION_EIM	16
#define _2_PLC_STATE_AUTHORIZATION_PNC	17
#define _2_PLC_STATE_CHARGE_PARAMETER_DISCOVERY	18
#define _2_PLC_STATE_CABLE_CHECK	19
#define _2_PLC_STATE_PRE_CHARGE	20
#define _2_PLC_STATE_POWER_DELIVERED	21
#define _2_PLC_STATE_CURRENT_DEMAND_1	22
#define _2_PLC_STATE_CURRENT_DEMAND_2	23
#define _2_PLC_STATE_CURRENT_DEMAND_3	24
#define _2_PLC_STATE_POWER_DELIVERY_RENOGOTIATE	25
#define _2_PLC_STATE_POWER_DELIVERY_EVINITSTOP	26
#define _2_PLC_STATE_POWER_DELIVERY_EVSEINITSTOP	27
#define _2_PLC_STATE_WELDING_DETECTION	28
#define _2_PLC_STATE_SESSION_STOP	29
#define _2_PLC_STATE_TERMINATED	30
#define _2_PLC_STATE_ERROR_STATE	31





#define _001	0x15ECC001
#define _002	0x15ECC002
#define _003	0x15ECC003
#define _004	0x15ECC004
#define _005	0x15ECC005
#define _006	0x15ECC006
#define _007	0x15ECC007
#define _008	0x15ECC008
#define _009	0x15ECC009
#define _00A	0x15ECC00A
#define _00B	0x15ECC00B
#define _00C	0x15ECC00C
#define _00D	0x15ECC00D
#define _D001  0x15ECD001
#define _D002  0x15ECD002
#define _D003  0x15ECD003

#define _101	0x15ECC101
#define _102	0x15ECC102
#define _103	0x15ECC103
#define _104	0x15ECC104
#define _105	0x15ECC105
#define _106	0x15ECC106
#define _107	0x15ECC107
#define _108	0x15ECC108
#define _109	0x15ECC109
#define _10A	0x15ECC10A
#define _10B	0x15ECC10B
#define _10C	0x15ECC10C
#define _10D	0x15ECC10D
#define _D101  0x15ECD101
#define _D102  0x15ECD102
#define _D103  0x15ECD103

#define _401	0x15ECC401
#define _402	0x15ECC402
#define _403	0x15ECC403
#define _404	0x15ECC404
#define _405	0x15ECC405
#define _406	0x15ECC406
#define _407	0x15ECC407
#define _408	0x15ECC408
#define _409	0x15ECC409
#define _40A	0x15ECC40A
#define _40B	0x15ECC40B
#define _40C	0x15ECC40C
#define _40D	0x15ECC40D
#define _D401   0x15ECD401
#define _D402   0x15ECD402
#define _D403   0x15ECD403

#define _501	0x15ECC501
#define _502	0x15ECC502
#define _503	0x15ECC503
#define _504	0x15ECC504
#define _505	0x15ECC505
#define _506	0x15ECC506
#define _507	0x15ECC507
#define _508	0x15ECC508
#define _509	0x15ECC509
#define _50A	0x15ECC50A
#define _50B	0x15ECC50B
#define _50C	0x15ECC50C
#define _50D	0x15ECC50D
#define _D501   0x15ECD501
#define _D502   0x15ECD502
#define _D503   0x15ECD503


#define EVSE_MAX_CURRENT_LIMIT	990

#define EVSE_MAX_VOLTAGE_DATA0   16
#define EVSE_MAX_VOLTAGE_DATA1    39

//#define EVSE_MAX_POWER_DATA0     184//30kw
//#define EVSE_MAX_POWER_DATA1     11


//#define EVSE_MAX_POWER_DATA0     112//60kw
//#define EVSE_MAX_POWER_DATA1     23

#define MAX_POWER_LIMIT		30000

//#define MAX_POWER_LIMIT		60000

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


typedef struct {

    enum {
        evseIDConfig_DIN = 0, evseIDConfig_ISO = 1, environmentConfig = 4,

    } _001EVSECONFIG_DATA0;

    uint8_t _001EVSEIDLENGTH_DIN_DATA1;
    uint8_t _001EVSEIDLENGTH_ISO_DATA2;

    enum {
        SupportEnergyTransfer_DCCORE = 2,

        SupportEnergyTransfer_DCEXTD = 3,

        SupportEnergyTransfer_DCCC = 4,

        SupportEnergyTransfer_DCUNI = 5,
        //at least one energy transfer mode is selected
    } _001SUPPORTENERGY_TRANSFER_DATA3;

    enum {
        Paid_Service_EvCharging = 0,
        Free_Service_EvCharging = 1,
        Free_Service_Contract_Paid = 0,
        Free_Service_Contract_Free = 4,
        Free_Service_OtherCustom_Paid = 0,
        Free_Service_OtherCustom_Free = 8,
    } _001SERVICE_TYPE_DATA5;

    enum {
        Schedule_Mgt_Default = 0,
        Schedule_Mgt_OCPP = 1,
        Schedule_Mgt_Interoperability = 2,
    } _001_SCHEDULE_MGT_DATA6;

    enum {
        CP_Mointor_Mode_Passive = 0,
        CP_Mointor_Mode_Active = 1,
        CP_Voltage_Senstivity_WS5 = 0,
        CP_Voltage_Senstivity_WS10 = 2,
        CP_Voltage_Senstivity_WS3 = 4,
        CP_Voltage_Senstivity_WS1 = 6,
    } _001_CP_MOINTOR_MODE_DATA7;
    uint8_t _003_EVSE_MAX_CURRENT_LIMIT_LSB_DATA1;
    uint8_t _003_EVSE_MAX_CURRENT_LIMIT_MSB_DATA0;
    uint8_t _003_EVSE_MAX_POWER_LIMIT_LSB_DATA3;
    uint8_t _003_EVSE_MAX_POWER_LIMIT_MSB_DATA2;
    uint8_t _003_EVSE_MAX_VOLTAGE_LIMIT_LSB_DATA5;
    uint8_t _003_EVSE_MAX_VOLTAGE_LIMIT_MSB_DATA4;
    uint8_t _003_EVSE_PEAK_CURRENT_RIPPLE_LSB_DATA7;
    uint8_t _003_EVSE_PEAK_CURRENT_RIPPLE_MSB_DATA6;
    uint8_t _004_EVSE_MIN_CURRENT_LIMIT_LSB_DATA1;
    uint8_t _004_EVSE_MIN_CURRENT_LIMIT_MSB_DATA0;
    uint8_t _004_EVSE_MIN_VOLTAGE_LIMIT_LSB_DATA3;
    uint8_t _004_EVSE_MIN_VOLTAGE_LIMIT_MSB_DATA2;
    uint8_t _004_EVSE_CURRENT_REGULATION_TOLERANCE_LSB_DATA5;
    uint8_t _004_EVSE_CURRENT_REGULATION_TOLERANCE_MSB_DATA4;
    uint8_t _004_EVSE_ENERGY_TO_DELIVERED_LSB_DATA7;
    uint8_t _004_EVSE_ENERGY_TO_DELIVERED_MSB_DATA6;



} PLC_tx_200;

typedef struct {

    enum {
        _2_evseIDConfig_DIN = 0, _2_evseIDConfig_ISO = 1, _2_environmentConfig = 4,

    } _401EVSECONFIG_DATA0;

    uint8_t _401EVSEIDLENGTH_DIN_DATA1;
    uint8_t _401EVSEIDLENGTH_ISO_DATA2;

    enum {
        _2_SupportEnergyTransfer_DCCORE = 2,

        _2_SupportEnergyTransfer_DCEXTD = 3,

        _2_SupportEnergyTransfer_DCCC = 4,

        _2_SupportEnergyTransfer_DCUNI = 5,
        //at least one energy transfer mode is selected
    } _401SUPPORTENERGY_TRANSFER_DATA3;

    enum {
        _2_Paid_Service_EvCharging = 0,
        _2_Free_Service_EvCharging = 1,
        _2_Free_Service_Contract_Paid = 0,
        _2_Free_Service_Contract_Free = 4,
        _2_Free_Service_OtherCustom_Paid = 0,
        _2_Free_Service_OtherCustom_Free = 8,
    } _401SERVICE_TYPE_DATA5;

    enum {
        _2_Schedule_Mgt_Default = 0,
        _2_Schedule_Mgt_OCPP = 1,
        _2_Schedule_Mgt_Interoperability = 2,
    } _401_SCHEDULE_MGT_DATA6;

    enum {
        _2_CP_Mointor_Mode_Passive = 0,
        _2_CP_Mointor_Mode_Active = 1,
        _2_CP_Voltage_Senstivity_WS5 = 0,
        _2_CP_Voltage_Senstivity_WS10 = 2,
        _2_CP_Voltage_Senstivity_WS3 = 4,
        _2_CP_Voltage_Senstivity_WS1 = 6,
    } _401_CP_MOINTOR_MODE_DATA7;
    uint8_t _403_EVSE_MAX_CURRENT_LIMIT_LSB_DATA1;
    uint8_t _403_EVSE_MAX_CURRENT_LIMIT_MSB_DATA0;
    uint8_t _403_EVSE_MAX_POWER_LIMIT_LSB_DATA3;
    uint8_t _403_EVSE_MAX_POWER_LIMIT_MSB_DATA2;
    uint8_t _403_EVSE_MAX_VOLTAGE_LIMIT_LSB_DATA5;
    uint8_t _403_EVSE_MAX_VOLTAGE_LIMIT_MSB_DATA4;
    uint8_t _403_EVSE_PEAK_CURRENT_RIPPLE_LSB_DATA7;
    uint8_t _403_EVSE_PEAK_CURRENT_RIPPLE_MSB_DATA6;
    uint8_t _404_EVSE_MIN_CURRENT_LIMIT_LSB_DATA1;
    uint8_t _404_EVSE_MIN_CURRENT_LIMIT_MSB_DATA0;
    uint8_t _404_EVSE_MIN_VOLTAGE_LIMIT_LSB_DATA3;
    uint8_t _404_EVSE_MIN_VOLTAGE_LIMIT_MSB_DATA2;
    uint8_t _404_EVSE_CURRENT_REGULATION_TOLERANCE_LSB_DATA5;
    uint8_t _404_EVSE_CURRENT_REGULATION_TOLERANCE_MSB_DATA4;
    uint8_t _404_EVSE_ENERGY_TO_DELIVERED_LSB_DATA7;
    uint8_t _404_EVSE_ENERGY_TO_DELIVERED_MSB_DATA6;

} _2_PLC_tx_200;

typedef struct {
    uint8_t _002_EVSE_STATUS_HEARTBEAT_DATA0;

    enum {
        Charging_Control_None = 0,
        Charging_Control_Initialised_PPMT = 1,
        Charging_Control_Start_Charging = 2,
        Charging_Control_Normal_Stop = 3,
        Charging_Control_EMG_Stop = 4,
        _
    } _002_EVSE_CHARGING_CONTROL_DATA1;
    uint8_t _002_EVSE_NOTIFICATION_DELAY_LSB_DATA2;
    uint8_t _002_EVSE_NOTIFICATION_DELAY_MSB_DATA3;

    enum {
        Isolation_Status_Invalid = 0,
        Isolation_Status_Valid = 1,
        Isolation_Status_Warning = 2,
        Isolation_Status_Fault = 3,
        Isolation_Status_NoIMD = 4, //Need to Check all the time if fault need to Stop Charging Control need to invalid after Charging
    } _002_EVSE_ISOLATION_STATUS_DATA4;

    enum {
        EVSE_Processing_Auth_EIM = 0,
        EVSE_Processing_CPD = 1,
        EVSE_Processing_Cable_check = 2,
        EVSE_Isolation_Mointor = 3,
        EVSE_Trigger_Negotation = 4,
        EVSE_Trigger_State = 6,

        //Initialized all to zero after each Session except heartbeat and charging Control and trigger state
    } _002_EVSE_PROCESSING_DATA6;

    enum {
        EVSE_Current_Limit = 0,
        EVSE_Voltage_Limit = 1,
        EVSE_Power_Limit = 2,
    } _002_EVSE_VCP_LIMIT_DATA7;
    uint8_t _005_EVSE_PRESENT_VOLTAGE_LSB_DATA1;
    uint8_t _005_EVSE_PRESENT_VOLTAGE_MSB_DATA0;
    uint8_t _005_EVSE_PRESENT_CURRENT_LSB_DATA3;
    uint8_t _005_EVSE_PRESENT_CURRENT_MSB_DATA2;
    uint32_t _006_EVSE_DIN_ID1_LSB;
    uint32_t _006_EVSE_DIN_ID1_MSB;
    uint32_t _007_EVSE_DIN_ID2_LSB;
    uint32_t _007_EVSE_DIN_ID2_MSB;

} PLC_tx_50;

typedef struct {
    uint8_t _402_EVSE_STATUS_HEARTBEAT_DATA0;

    enum {
        _2_Charging_Control_None = 0,
        _2_Charging_Control_Initialised_PPMT = 1,
        _2_Charging_Control_Start_Charging = 2,
        _2_Charging_Control_Normal_Stop = 3,
        _2_Charging_Control_EMG_Stop = 4,
    
    } _402_EVSE_CHARGING_CONTROL_DATA1;
    uint8_t _402_EVSE_NOTIFICATION_DELAY_LSB_DATA2;
    uint8_t _402_EVSE_NOTIFICATION_DELAY_MSB_DATA3;

    enum {
        _2_Isolation_Status_Invalid = 0,
        _2_Isolation_Status_Valid = 1,
        _2_Isolation_Status_Warning = 2,
        _2_Isolation_Status_Fault = 3,
        _2_Isolation_Status_NoIMD = 4, //Need to Check all the time if fault need to Stop Charging Control need to invalid after Charging
    } _402_EVSE_ISOLATION_STATUS_DATA4;

    enum {
        _2_EVSE_Processing_Auth_EIM = 0,
        _2_EVSE_Processing_CPD = 1,
        _2_EVSE_Processing_Cable_check = 2,
        _2_EVSE_Isolation_Mointor = 3,
        _2_EVSE_Trigger_Negotation = 4,
        _2_EVSE_Trigger_State = 6,

        //Initialized all to zero after each Session except heartbeat and charging Control and trigger state
    } _402_EVSE_PROCESSING_DATA6;

    enum {
        _2_EVSE_Current_Limit = 0,
        _2_EVSE_Voltage_Limit = 1,
        _2_EVSE_Power_Limit = 2,
    } _402_EVSE_VCP_LIMIT_DATA7;
    uint8_t _405_EVSE_PRESENT_VOLTAGE_LSB_DATA1;
    uint8_t _405_EVSE_PRESENT_VOLTAGE_MSB_DATA0;
    uint8_t _405_EVSE_PRESENT_CURRENT_LSB_DATA3;
    uint8_t _405_EVSE_PRESENT_CURRENT_MSB_DATA2;
    uint32_t _406_EVSE_DIN_ID1_LSB;
    uint32_t _406_EVSE_DIN_ID1_MSB;
    uint32_t _407_EVSE_DIN_ID2_LSB;
    uint32_t _407_EVSE_DIN_ID2_MSB;


} _2_PLC_tx_50;

typedef struct {
    uint32_t _008_EVSE_DIN_ID3_LSB;
    uint32_t _008_EVSE_DIN_ID3_MSB;
    uint32_t _009_EVSE_DIN_ID4_LSB;
    uint32_t _009_EVSE_DIN_ID4_MSB;
    uint32_t _00A_EVSE_ISO_ID1_LSB;
    uint32_t _00A_EVSE_ISO_ID1_MSB;
    uint32_t _00B_EVSE_ISO_ID2_LSB;
    uint32_t _00B_EVSE_ISO_ID2_MSB;
    uint32_t _00C_EVSE_ISO_ID3_LSB;
    uint32_t _00C_EVSE_ISO_ID3_MSB;
    uint32_t _00D_EVSE_ISO_ID4_LSB;
    uint32_t _00D_EVSE_ISO_ID4_MSB;
    uint32_t _00E_EVSE_ISO_ID5_LSB;
    uint32_t _00E_EVSE_ISO_ID5_MSB;




} PLC_tx_500;

typedef struct {
    uint32_t _408_EVSE_DIN_ID3_LSB;
    uint32_t _408_EVSE_DIN_ID3_MSB;
    uint32_t _409_EVSE_DIN_ID4_LSB;
    uint32_t _409_EVSE_DIN_ID4_MSB;
    uint32_t _40A_EVSE_ISO_ID1_LSB;
    uint32_t _40A_EVSE_ISO_ID1_MSB;
    uint32_t _40B_EVSE_ISO_ID2_LSB;
    uint32_t _40B_EVSE_ISO_ID2_MSB;
    uint32_t _40C_EVSE_ISO_ID3_LSB;
    uint32_t _40C_EVSE_ISO_ID3_MSB;
    uint32_t _40D_EVSE_ISO_ID4_LSB;
    uint32_t _40D_EVSE_ISO_ID4_MSB;
    uint32_t _40E_EVSE_ISO_ID5_LSB;
    uint32_t _40E_EVSE_ISO_ID5_MSB;

} _2_PLC_tx_500;

typedef struct {
    uint8_t _D001_EVSE_SAAGENTIPADDR1_DATA0;
    uint8_t _D001_EVSE_SAAGENTIPADDR2_DATA1;
    uint8_t _D001_EVSE_SAAGENTIPADDR3_DATA2;
    uint8_t _D001_EVSE_SAAGENTIPADDR4_DATA3;
    uint8_t _D001_EVSE_SAAGENTPORT_LSB_DATA4;
    uint8_t _D001_EVSE_SAAGENTPORT_MSB_DATA5;

    enum {
        EVSE_PKIENVSELECTION_None = 0,
        EVSE_PKIENVSELECTION_Public = 1,
        EVSE_PKIENVSELECTION_Private = 2,
    } _D002_EVSE_PKIENVSELECTION_DATA0;

    enum {
        EVSE_CERTCHAINVALID_None = 0,
        EVSE_CERTCHAINVALID_Passive = 1,
        EVSE_CERTCHAINVALID_Active = 2,
        EVSE_CERTCHAINVALID_Forced = 3,
    } _D002_EVSE_CERTCHAINVALID_DATA1;

    enum {
        EVSE_RKEYOPTION_False = 0, EVSE_RKEYOPTION_True = 1,
    } _D002_EVSE_RKEYOPTION_DATA2;
    uint8_t _D003_EVSE_SAAGENTHELLORESPONSE_DATA1;
    uint8_t _D003_EVSE_SAAGENTGETCERTIFICATIONSTATUSRESPONSE_DATA2;
    uint8_t _D003_EVSE_SAAGENTCERTINSTALL_DATA3;
    uint8_t _D003_EVSE_SAAGENTCERTUPDATE_DATA4;
    uint8_t _D003_EVSE_SAAGENTAUTHORIZE_DATA5;





} PLC_tx_1000;

typedef struct {
    uint8_t _D401_EVSE_SAAGENTIPADDR1_DATA0;
    uint8_t _D401_EVSE_SAAGENTIPADDR2_DATA1;
    uint8_t _D401_EVSE_SAAGENTIPADDR3_DATA2;
    uint8_t _D401_EVSE_SAAGENTIPADDR4_DATA3;
    uint8_t _D401_EVSE_SAAGENTPORT_LSB_DATA4;
    uint8_t _D401_EVSE_SAAGENTPORT_MSB_DATA5;

    enum {
        _2_EVSE_PKIENVSELECTION_None = 0,
        _2_EVSE_PKIENVSELECTION_Public = 1,
        _2_EVSE_PKIENVSELECTION_Private = 2,
    } _D402_EVSE_PKIENVSELECTION_DATA0;

    enum {
        _2_EVSE_CERTCHAINVALID_None = 0,
        _2_EVSE_CERTCHAINVALID_Passive = 1,
        _2_EVSE_CERTCHAINVALID_Active = 2,
        _2_EVSE_CERTCHAINVALID_Forced = 3,
    } _D402_EVSE_CERTCHAINVALID_DATA1;

    enum {
        _2_EVSE_RKEYOPTION_False = 0, _2_EVSE_RKEYOPTION_True = 1,
    } _D402_EVSE_RKEYOPTION_DATA2;
    uint8_t _D403_EVSE_SAAGENTHELLORESPONSE_DATA1;
    uint8_t _D403_EVSE_SAAGENTGETCERTIFICATIONSTATUSRESPONSE_DATA2;
    uint8_t _D403_EVSE_SAAGENTCERTINSTALL_DATA3;
    uint8_t _D403_EVSE_SAAGENTCERTUPDATE_DATA4;
    uint8_t _D403_EVSE_SAAGENTAUTHORIZE_DATA5;

} _2_PLC_tx_1000;

typedef enum {
    SeccStatus_Idle_Wait = 0,
    SeccStatus_Idle = 1,
    SeccStatus_Ready = 2,
    SeccStatus_Low_Level_Comm = 3,
    SeccStatus_High_level_Comm = 4,
    SeccStatus_Authorize = 5,
    SeccStatus_ChargeParameter = 6,
    SeccStatus_CableCheck = 7,
    SeccStatus_Precharge = 8,
    SeccStatus_Charging = 9,
    SeccStatus_Renegotation = 10,
    SeccStatus_EV_Init_Stop_CHG = 11,
    SeccStatus_EVSE_Init_Stop_CHG = 12,
    SeccStatus_Pause = 13,
    SeccStatus_Terminate = 14,
    SeccStatus_Certificate = 15,
    SeccStatus_Certificate_Update = 16,
    SeccStatus_Error = 17,
    SeccStatus_Authorized = 18,
    SeccStatus_Metering = 19,
} _101_SECC_Status;

typedef enum {
    _2_SeccStatus_Idle_Wait = 0,
    _2_SeccStatus_Idle = 1,
    _2_SeccStatus_Ready = 2,
    _2_SeccStatus_Low_Level_Comm = 3,
    _2_SeccStatus_High_level_Comm = 4,
    _2_SeccStatus_Authorize = 5,
    _2_SeccStatus_ChargeParameter = 6,
    _2_SeccStatus_CableCheck = 7,
    _2_SeccStatus_Precharge = 8,
    _2_SeccStatus_Charging = 9,
    _2_SeccStatus_Renegotation = 10,
    _2_SeccStatus_EV_Init_Stop_CHG = 11,
    _2_SeccStatus_EVSE_Init_Stop_CHG = 12,
    _2_SeccStatus_Pause = 13,
    _2_SeccStatus_Terminate = 14,
    _2_SeccStatus_Certificate = 15,
    _2_SeccStatus_Certificate_Update = 16,
    _2_SeccStatus_Error = 17,
    _2_SeccStatus_Authorized = 18,
    _2_SeccStatus_Metering = 19,
} _501_SECC_Status;

typedef enum {
    evERRORCODE_NO_ERROR = 0,
    evERRORCODE_FAILED_RESSTemperature = 1,
    evERRORCODE_FAILED_EVShiftPosition = 2,
    evERRORCODE_FAILED_ChargerConnectorLockFault = 3,
    evERRORCODE_FAILED_EVRESSMalFunction = 4,
    evERRORCODE_FAILED_ChargingCurrentdifferential = 5,
    evERRORCODE_FAILED_ChargingVoltageOutofRange = 6,
    evERRORCODE_RESERVED_A = 7,
    evERRORCODE_RESERVED_B = 8,
    evERRORCODE_RESERVED_C = 9,
    evERRORCODE_FAILED_ChargingSystemIncomp = 10,
    evERRORCODE_NO_DATA = 11,
} _101_SECC_evERRORCODE;

typedef enum {
    _2_evERRORCODE_NO_ERROR = 0,
    _2_evERRORCODE_FAILED_RESSTemperature = 1,
    _2_evERRORCODE_FAILED_EVShiftPosition = 2,
    _2_evERRORCODE_FAILED_ChargerConnectorLockFault = 3,
    _2_evERRORCODE_FAILED_EVRESSMalFunction = 4,
    _2_evERRORCODE_FAILED_ChargingCurrentdifferential = 5,
    _2_evERRORCODE_FAILED_ChargingVoltageOutofRange = 6,
    _2_evERRORCODE_RESERVED_A = 7,
    _2_evERRORCODE_RESERVED_B = 8,
    _2_evERRORCODE_RESERVED_C = 9,
    _2_evERRORCODE_FAILED_ChargingSystemIncomp = 10,
    _2_evERRORCODE_NO_DATA = 11,
} _501_SECC_evERRORCODE;

typedef enum {
    seccERRORCODE_NO_ERROR = 0,
    seccERRORCODE_FAILED = 1,
    seccERRORCODE_FAILED_SequenceError = 2,
    seccERRORCODE_FAILED_ServiceIDInvalid = 3,
    seccERRORCODE_FAILED_UnknownSession = 4,
    seccERRORCODE_FAILED_ServiceSelectionInvalid = 5,
    seccERRORCODE_FAILED_PaymentSelectionInvalid = 6,
    seccERRORCODE_FAILED_CertificateExpired = 7,
    seccERRORCODE_FAILED_SignatureError = 8,
    seccERRORCODE_FAILED_NoCertificateAvailable = 9,
    seccERRORCODE_FAILED_CertChainError = 10,
    seccERRORCODE_FAILED_ChallangeInvalid = 11,
    seccERRORCODE_FAILED_ContractCancelled = 12,
    seccERRORCODE_FAILED_WrongChargeParameter = 13,
    seccERRORCODE_FAILED_PowerDeliveryNotApplied = 14,
    seccERRORCODE_FAILED_TariffSelectionInvalid = 15,
    seccERRORCODE_FAILED_ChargingProfileInvalid = 16,
    seccERRORCODE_FAILED_MeteringSignatureNotValid = 17,
    seccERRORCODE_FAILED_NoChargeServiceSelected = 18,
    seccERRORCODE_FAILED_WrongEnergyTransferMode = 19,
    seccERRORCODE_FAILED_CertificateRevoked = 22,
    seccERRORCODE_FAILED_NoNegotiation = 23,
    seccERRORCODE_TIMEOUT_CommunicationSetup = 30,
    seccERRORCODE_TIMEOUT_Sequence = 31,
    seccERRORCODE_TIMEOUT_NotificationMaxDelay = 32,
    seccERRORCODE_TIMEOUT_WeldingDetection = 33,
    seccERRORCODE_FAULT_WrongCPLevel = 40,
    seccERRORCODE_FAULT_ProximityError = 41,
    seccERRORCODE_FAULT_HLCError = 42,
    seccERRORCODE_FAULT_HeartBeatError = 43,
    seccERRORCODE_FAULT_EVSECANINIT = 44,
    seccERRORCODE_FAULT_HPGPLinkDown = 45,
    seccERRORCODE_FAULT_TLS_ErrorAlert = 46,

} _101_SECC_seccERROR_CODES;

typedef enum {
    _2_seccERRORCODE_NO_ERROR = 0,
    _2_seccERRORCODE_FAILED = 1,
    _2_seccERRORCODE_FAILED_SequenceError = 2,
    _2_seccERRORCODE_FAILED_ServiceIDInvalid = 3,
    _2_seccERRORCODE_FAILED_UnknownSession = 4,
    _2_seccERRORCODE_FAILED_ServiceSelectionInvalid = 5,
    _2_seccERRORCODE_FAILED_PaymentSelectionInvalid = 6,
    _2_seccERRORCODE_FAILED_CertificateExpired = 7,
    _2_seccERRORCODE_FAILED_SignatureError = 8,
    _2_seccERRORCODE_FAILED_NoCertificateAvailable = 9,
    _2_seccERRORCODE_FAILED_CertChainError = 10,
    _2_seccERRORCODE_FAILED_ChallangeInvalid = 11,
    _2_seccERRORCODE_FAILED_ContractCancelled = 12,
    _2_seccERRORCODE_FAILED_WrongChargeParameter = 13,
    _2_seccERRORCODE_FAILED_PowerDeliveryNotApplied = 14,
    _2_seccERRORCODE_FAILED_TariffSelectionInvalid = 15,
    _2_seccERRORCODE_FAILED_ChargingProfileInvalid = 16,
    _2_seccERRORCODE_FAILED_MeteringSignatureNotValid = 17,
    _2_seccERRORCODE_FAILED_NoChargeServiceSelected = 18,
    _2_seccERRORCODE_FAILED_WrongEnergyTransferMode = 19,
    _2_seccERRORCODE_FAILED_CertificateRevoked = 22,
    _2_seccERRORCODE_FAILED_NoNegotiation = 23,
    _2_seccERRORCODE_TIMEOUT_CommunicationSetup = 30,
    _2_seccERRORCODE_TIMEOUT_Sequence = 31,
    _2_seccERRORCODE_TIMEOUT_NotificationMaxDelay = 32,
    _2_seccERRORCODE_TIMEOUT_WeldingDetection = 33,
    _2_seccERRORCODE_FAULT_WrongCPLevel = 40,
    _2_seccERRORCODE_FAULT_ProximityError = 41,
    _2_seccERRORCODE_FAULT_HLCError = 42,
    _2_seccERRORCODE_FAULT_HeartBeatError = 43,
    _2_seccERRORCODE_FAULT_EVSECANINIT = 44,
    _2_seccERRORCODE_FAULT_HPGPLinkDown = 45,
    _2_seccERRORCODE_FAULT_TLS_ErrorAlert = 46,

} _501_SECC_seccERROR_CODES;

typedef enum {
    seccPnCReady_NONE = 0, seccPnCReady_NotReady = 1, seccPnCReady_Ready = 2,
} _101_SECC_PnCREADY;

typedef enum {
    _2_seccPnCReady_NONE = 0, _2_seccPnCReady_NotReady = 1, _2_seccPnCReady_Ready = 2,
} _501_SECC_PnCREADY;

typedef enum {
    seccCpOscillator_Duty_Cycle_OFF = 0, seccCpOscillator_Duty_Cycle_ON = 1,
} _102_SECC_CP;

typedef enum {
    _2_seccCpOscillator_Duty_Cycle_OFF = 0, _2_seccCpOscillator_Duty_Cycle_ON = 1,
} _502_SECC_CP;

typedef enum {
    seccHpgpLink_Link_Down = 0, seccHpgpLink_Link_UP = 1,
} _102_SECC_HpgpLink;

typedef enum {
    _2_seccHpgpLink_Link_Down = 0, _2_seccHpgpLink_Link_UP = 1,
} _502_SECC_HpgpLink;

typedef enum {
    secctlsError_Close_Notify = 0,
    secctlsError_Unexpected_Message = 10,
    secctlsError_Bad_record = 20,
    secctlsError_Decryption = 21,
    secctlsError_Record_Overflow = 22,
    secctlsError_Decompression = 30,
    secctlsError_Handshake_Failure = 40,
    secctlsError_No_Certificate = 41,
    secctlsError_Bad_Certificate = 42,
    secctlsError_unsupported_certificate = 43,
    secctlsError_certificateRevoked = 44,
    secctlsError_CertificateExpired = 45,
    secctlsError_CertificateUnknown = 46,
    secctlsError_illegal_parameter = 47,
    secctlsError_unknown_ca = 48,
    secctlsError_access_Denied = 49,
    secctlsError_Decode_error = 50,
    secctlsError_Decrypt_error = 51,
    secctlsError_Export_restriction_RESERVED = 60,
    secctlsError_ProtocolVersion = 70,
    secctlsError_Insufficient_Security = 71,
    secctlsError_Internal_Error = 80,
    secctlsError_usercanclled = 90,
    secctlsError_no_renegotiation = 100,
    secctlsError_unsupportedExtension = 110,
} _102_SECC_TLSERROR;

typedef enum {
    _2_secctlsError_Close_Notify = 0,
    _2_secctlsError_Unexpected_Message = 10,
    _2_secctlsError_Bad_record = 20,
    _2_secctlsError_Decryption = 21,
    _2_secctlsError_Record_Overflow = 22,
    _2_secctlsError_Decompression = 30,
    _2_secctlsError_Handshake_Failure = 40,
    _2_secctlsError_No_Certificate = 41,
    _2_secctlsError_Bad_Certificate = 42,
    _2_secctlsError_unsupported_certificate = 43,
    _2_secctlsError_certificateRevoked = 44,
    _2_secctlsError_CertificateExpired = 45,
    _2_secctlsError_CertificateUnknown = 46,
    _2_secctlsError_illegal_parameter = 47,
    _2_secctlsError_unknown_ca = 48,
    _2_secctlsError_access_Denied = 49,
    _2_secctlsError_Decode_error = 50,
    _2_secctlsError_Decrypt_error = 51,
    _2_secctlsError_Export_restriction_RESERVED = 60,
    _2_secctlsError_ProtocolVersion = 70,
    _2_secctlsError_Insufficient_Security = 71,
    _2_secctlsError_Internal_Error = 80,
    _2_secctlsError_usercanclled = 90,
    _2_secctlsError_no_renegotiation = 100,
    _2_secctlsError_unsupportedExtension = 110,
} _502_SECC_TLSERROR;

typedef enum {
    seccStatus_IDLE = 0,
    seccStatus_Initialized = 1,
    seccStatus_Waiting_plugIN = 2,
    seccStatus_Waiting_SLAC = 10,
    seccStatus_Processing_SLAC = 11,
    seccStatus_SDP = 20,
    seccStatus_EstablishingTCP = 21,
    seccStatus_SAP = 30,
    seccStatus_SessionSetup = 40,
    seccStatus_SessionStop = 41,
    seccStatus_SessionPause = 42,
    seccStatus_ServiceDiscovery = 50,
    seccStatus_ServiceDetails = 51,
    seccStatus_PaymentServiceSelection = 60,
    seccStatus_CerticficateInstallation = 70,
    seccStatus_CertificateUpdate = 71,
    seccStatus_Payment_Details = 80,
    seccStatus_Authorization_EIM = 81,
    seccStatus_Authorization_pnC = 82,
    seccStatus_ChargeParameterDiscovery = 90,
    seccStatus_Cable_Check = 100,
    seccStatus_PreCharge = 101,
    seccStatus_Welding_Detection = 102,
    seccStatus_PowerDeliveryStart = 110,
    seccStatus_Power_deliveryEvStop = 111,
    seccStatus_Power_deliveryEVSEStop = 112,
    seccStatus_PowerDelivery_Renotiate = 113,
    seccStatus_CurrentDemand = 120,
    seccStatus_MeteringReceipt = 121,
    seccStatus_TERMINATE = 250,
    seccStatus_PAUSE = 251,
    seccStatus_ERROR = 252,

} _10B_SECC_STATUS3;

typedef enum {
    _2_seccStatus_IDLE = 0,
    _2_seccStatus_Initialized = 1,
    _2_seccStatus_Waiting_plugIN = 2,
    _2_seccStatus_Waiting_SLAC = 10,
    _2_seccStatus_Processing_SLAC = 11,
    _2_seccStatus_SDP = 20,
    _2_seccStatus_EstablishingTCP = 21,
    _2_seccStatus_SAP = 30,
    _2_seccStatus_SessionSetup = 40,
    _2_seccStatus_SessionStop = 41,
    _2_seccStatus_SessionPause = 42,
    _2_seccStatus_ServiceDiscovery = 50,
    _2_seccStatus_ServiceDetails = 51,
    _2_seccStatus_PaymentServiceSelection = 60,
    _2_seccStatus_CerticficateInstallation = 70,
    _2_seccStatus_CertificateUpdate = 71,
    _2_seccStatus_Payment_Details = 80,
    _2_seccStatus_Authorization_EIM = 81,
    _2_seccStatus_Authorization_pnC = 82,
    _2_seccStatus_ChargeParameterDiscovery = 90,
    _2_seccStatus_Cable_Check = 100,
    _2_seccStatus_PreCharge = 101,
    _2_seccStatus_Welding_Detection = 102,
    _2_seccStatus_PowerDeliveryStart = 110,
    _2_seccStatus_Power_deliveryEvStop = 111,
    _2_seccStatus_Power_deliveryEVSEStop = 112,
    _2_seccStatus_PowerDelivery_Renotiate = 113,
    _2_seccStatus_CurrentDemand = 120,
    _2_seccStatus_MeteringReceipt = 121,
    _2_seccStatus_TERMINATE = 250,
    _2_seccStatus_PAUSE = 251,
    _2_seccStatus_ERROR = 252,

} _50B_SECC_STATUS3;

typedef enum {
    seccEstablishedInfo_NONE = 0,
    seccEstablishedInfo_NonTLS_Established = 1,
    seccEstablishedInfo_PublicTLS_Established = 2,
    seccEstablishedInfo_PrivateTLS_Established = 3,
} _10B_SECC_STATUS3_ESTABLISHEDINFO;

typedef enum {
    _2_seccEstablishedInfo_NONE = 0,
    _2_seccEstablishedInfo_NonTLS_Established = 1,
    _2_seccEstablishedInfo_PublicTLS_Established = 2,
    _2_seccEstablishedInfo_PrivateTLS_Established = 3,
} _50B_SECC_STATUS3_ESTABLISHEDINFO;

typedef enum {
    seccEVSS_CHG_DIN = 0,
    seccEVSS_CHG_ISO_2013 = 1,
    seccEVSS_CHG_ISO_2016 = 2,
    seccEVSS_CHG_NONE = 255, //Need to Ask Not sure
} _103_SELECTED_CHARGING_PROTOCOL;

typedef enum {
    _2_seccEVSS_CHG_DIN = 0,
    _2_seccEVSS_CHG_ISO_2013 = 1,
    _2_seccEVSS_CHG_ISO_2016 = 2,
    _2_seccEVSS_CHG_NONE = 255, //Need to Ask Not sure
} _503_SELECTED_CHARGING_PROTOCOL;

typedef enum {
    seccEVSS_PAY_CONTRACT = 0,
    seccEVSS_PAY_EXTERNAL = 1,
    seccEVSS_PAY_NONE = 255, //Need to Ask Not sure
} _103_SELECTED_PAYMENT_OPTION;

typedef enum {
    _2_seccEVSS_PAY_CONTRACT = 0,
    _2_seccEVSS_PAY_EXTERNAL = 1,
    _2_seccEVSS_PAY_NONE = 255, //Need to Ask Not sure
} _503_SELECTED_PAYMENT_OPTION;

typedef enum {
    seccEVSS_ENERGY_AC_SINGLE_PHASE = 0,
    seccEVSS_ENERGY_AC_THREE_PHASE = 1,
    seccEVSS_ENERGY_DC_CORE = 2,
    seccEVSS_ENERGY_DC_EXTENDED = 3,
    seccEVSS_ENERGY_DC_COMBO_CORE = 4,
    seccEVSS_ENERGY_DC_UNIQUE = 5,
    seccEVSS_ENERGY_DC_NONE = 255, //NEED TO ASK
} _103_SELECTED_ENERGY_TRANSFER_MODE;

typedef enum {
    _2_seccEVSS_ENERGY_AC_SINGLE_PHASE = 0,
    _2_seccEVSS_ENERGY_AC_THREE_PHASE = 1,
    _2_seccEVSS_ENERGY_DC_CORE = 2,
    _2_seccEVSS_ENERGY_DC_EXTENDED = 3,
    _2_seccEVSS_ENERGY_DC_COMBO_CORE = 4,
    _2_seccEVSS_ENERGY_DC_UNIQUE = 5,
    _2_seccEVSS_ENERGY_DC_NONE = 255, //NEED TO ASK
} _503_SELECTED_ENERGY_TRANSFER_MODE;

typedef enum {
    seccEVSE_saAgentINIT_NONE = 0,
    seccEVSE_saAgentINIT_NON_TLS = 1,
    seccEVSE_saAgentINIT_PUBLIC_TLS = 2,
    seccEVSE_saAgentINIT_Private_TLS = 3,
} _ECD101_SECC_COMM_STATUS_SAGENTINIT;

typedef enum {
    _2_seccEVSE_saAgentINIT_NONE = 0,
    _2_seccEVSE_saAgentINIT_NON_TLS = 1,
    _2_seccEVSE_saAgentINIT_PUBLIC_TLS = 2,
    _2_seccEVSE_saAgentINIT_Private_TLS = 3,
} _ECD501_SECC_COMM_STATUS_SAGENTINIT;

typedef enum {
    seccEVSE_saAgentINITDetails_NONE = 0,
    seccEVSE_saAgentINITDetails_HELLO = 10,
    seccEVSE_saAgentINITDetails_GET_CERTIFICATE = 11,
    seccEVSE_saAgentINITDetails_SIGN_SECCCERT = 12,
    seccEVSE_saAgentINITDetails_CERT_INSTALL = 13,
    seccEVSE_saAgentINITDetails_CERT_UPDATE = 14,
    seccEVSE_saAgentINITDetails_PNCAUTH = 15,
    seccEVSE_saAgentINITDetails_FAULT_SAAGENTCOMM = 20,
    seccEVSE_saAgentINITDetails_FAULT_PARSEJSON = 21,
    seccEVSE_saAgentINITDetails_FAULT_CREATECSR = 22,
    seccEVSE_saAgentINITDetails_FAULT_RECIEVED_CERTCHAIN = 23,
    seccEVSE_saAgentINITDetails_FAULT_DECODE_EXI = 40
} _ECD101_SECC_COMM_STATUS_SAGENTINIT_Details;

typedef enum {
    _2_seccEVSE_saAgentINITDetails_NONE = 0,
    _2_seccEVSE_saAgentINITDetails_HELLO = 10,
    _2_seccEVSE_saAgentINITDetails_GET_CERTIFICATE = 11,
    _2_seccEVSE_saAgentINITDetails_SIGN_SECCCERT = 12,
    _2_seccEVSE_saAgentINITDetails_CERT_INSTALL = 13,
    _2_seccEVSE_saAgentINITDetails_CERT_UPDATE = 14,
    _2_seccEVSE_saAgentINITDetails_PNCAUTH = 15,
    _2_seccEVSE_saAgentINITDetails_FAULT_SAAGENTCOMM = 20,
    _2_seccEVSE_saAgentINITDetails_FAULT_PARSEJSON = 21,
    _2_seccEVSE_saAgentINITDetails_FAULT_CREATECSR = 22,
    _2_seccEVSE_saAgentINITDetails_FAULT_RECIEVED_CERTCHAIN = 23,
    _2_seccEVSE_saAgentINITDetails_FAULT_DECODE_EXI = 40
} _ECD501_SECC_COMM_STATUS_SAGENTINIT_Details;

typedef enum {
    seccEVSE_saAgentCERTINSTALLATION_NONE = 0,
    seccEVSE_saAgentCERTINSTALLATION_HELLO = 10,
    seccEVSE_saAgentCERTINSTALLATION_GET_CERTIFICATE = 11,
    seccEVSE_saAgentCERTINSTALLATION_SIGN_SECCCERT = 12,
    seccEVSE_saAgentCERTINSTALLATION_CERT_INSTALL = 13,
    seccEVSE_saAgentCERTINSTALLATION_CERT_UPDATE = 14,
    seccEVSE_saAgentCERTINSTALLATION_PNCAUTH = 15,
    seccEVSE_saAgentCERTINSTALLATION_FAULT_SAAGENTCOMM = 20,
    seccEVSE_saAgentCERTINSTALLATION_FAULT_PARSEJSON = 21,
    seccEVSE_saAgentCERTINSTALLATION_FAULT_CREATECSR = 22,
    seccEVSE_saAgentCERTINSTALLATION_FAULT_RECIEVED_CERTCHAIN = 23,
    seccEVSE_saAgentCERTINSTALLATION_FAULT_DECODE_EXI = 40
} _ECD101_SECC_COMM_STATUS_SAGENTCERT_INSTALLATION;

typedef enum {
    _2_seccEVSE_saAgentCERTINSTALLATION_NONE = 0,
    _2_seccEVSE_saAgentCERTINSTALLATION_HELLO = 10,
    _2_seccEVSE_saAgentCERTINSTALLATION_GET_CERTIFICATE = 11,
    _2_seccEVSE_saAgentCERTINSTALLATION_SIGN_SECCCERT = 12,
    _2_seccEVSE_saAgentCERTINSTALLATION_CERT_INSTALL = 13,
    _2_seccEVSE_saAgentCERTINSTALLATION_CERT_UPDATE = 14,
    _2_seccEVSE_saAgentCERTINSTALLATION_PNCAUTH = 15,
    _2_seccEVSE_saAgentCERTINSTALLATION_FAULT_SAAGENTCOMM = 20,
    _2_seccEVSE_saAgentCERTINSTALLATION_FAULT_PARSEJSON = 21,
    _2_seccEVSE_saAgentCERTINSTALLATION_FAULT_CREATECSR = 22,
    _2_seccEVSE_saAgentCERTINSTALLATION_FAULT_RECIEVED_CERTCHAIN = 23,
    _2_seccEVSE_saAgentCERTINSTALLATION_FAULT_DECODE_EXI = 40
} _ECD501_SECC_COMM_STATUS_SAGENTCERT_INSTALLATION;

typedef enum {
    seccEVSE_saAgentCERTUPDATE_NONE = 0,
    seccEVSE_saAgentCERTUPDATE_HELLO = 10,
    seccEVSE_saAgentCERTUPDATE_GET_CERTIFICATE = 11,
    seccEVSE_saAgentCERTUPDATE_SIGN_SECCCERT = 12,
    seccEVSE_saAgentCERTUPDATE_CERT_INSTALL = 13,
    seccEVSE_saAgentCERTUPDATE_CERT_UPDATE = 14,
    seccEVSE_saAgentCERTUPDATE_PNCAUTH = 15,
    seccEVSE_saAgentCERTUPDATE_FAULT_SAAGENTCOMM = 20,
    seccEVSE_saAgentCERTUPDATE_FAULT_PARSEJSON = 21,
    seccEVSE_saAgentCERTUPDATE_FAULT_CREATECSR = 22,
    seccEVSE_saAgentCERTUPDATE_FAULT_RECIEVED_CERTCHAIN = 23,
    seccEVSE_saAgentCERTUPDATE_FAULT_DECODE_EXI = 40
} _ECD101_SECC_COMM_STATUS_SAGENTCERT_UPDATE;

typedef enum {
    _2_seccEVSE_saAgentCERTUPDATE_NONE = 0,
    _2_seccEVSE_saAgentCERTUPDATE_HELLO = 10,
    _2_seccEVSE_saAgentCERTUPDATE_GET_CERTIFICATE = 11,
    _2_seccEVSE_saAgentCERTUPDATE_SIGN_SECCCERT = 12,
    _2_seccEVSE_saAgentCERTUPDATE_CERT_INSTALL = 13,
    _2_seccEVSE_saAgentCERTUPDATE_CERT_UPDATE = 14,
    _2_seccEVSE_saAgentCERTUPDATE_PNCAUTH = 15,
    _2_seccEVSE_saAgentCERTUPDATE_FAULT_SAAGENTCOMM = 20,
    _2_seccEVSE_saAgentCERTUPDATE_FAULT_PARSEJSON = 21,
    _2_seccEVSE_saAgentCERTUPDATE_FAULT_CREATECSR = 22,
    _2_seccEVSE_saAgentCERTUPDATE_FAULT_RECIEVED_CERTCHAIN = 23,
    _2_seccEVSE_saAgentCERTUPDATE_FAULT_DECODE_EXI = 40
} _ECD501_SECC_COMM_STATUS_SAGENTCERT_UPDATE;

typedef enum {
    seccEVSE_saAgentCERTUPDATE_DETAILS_NONE = 0,
    seccEVSE_saAgentCERTUPDATE_DETAILS_HELLO = 10,
    seccEVSE_saAgentCERTUPDATE_DETAILS_GET_CERTIFICATE = 11,
    seccEVSE_saAgentCERTUPDATE_DETAILS_SIGN_SECCCERT = 12,
    seccEVSE_saAgentCERTUPDATE_DETAILS_CERT_INSTALL = 13,
    seccEVSE_saAgentCERTUPDATE_DETAILS_CERT_UPDATE = 14,
    seccEVSE_saAgentCERTUPDATE_DETAILS_PNCAUTH = 15,
    seccEVSE_saAgentCERTUPDATE_DETAILS_FAULT_SAAGENTCOMM = 20,
    seccEVSE_saAgentCERTUPDATE_DETAILS_FAULT_PARSEJSON = 21,
    seccEVSE_saAgentCERTUPDATE_DETAILS_FAULT_CREATECSR = 22,
    seccEVSE_saAgentCERTUPDATE_DETAILS_FAULT_RECIEVED_CERTCHAIN = 23,
    seccEVSE_saAgentCERTUPDATE_DETAILS_FAULT_DECODE_EXI = 40
} _ECD101_SECC_COMM_STATUS_SAGENTCERT_UPDATE_DETAILS;

typedef enum {
    _2_seccEVSE_saAgentCERTUPDATE_DETAILS_NONE = 0,
    _2_seccEVSE_saAgentCERTUPDATE_DETAILS_HELLO = 10,
    _2_seccEVSE_saAgentCERTUPDATE_DETAILS_GET_CERTIFICATE = 11,
    _2_seccEVSE_saAgentCERTUPDATE_DETAILS_SIGN_SECCCERT = 12,
    _2_seccEVSE_saAgentCERTUPDATE_DETAILS_CERT_INSTALL = 13,
    _2_seccEVSE_saAgentCERTUPDATE_DETAILS_CERT_UPDATE = 14,
    _2_seccEVSE_saAgentCERTUPDATE_DETAILS_PNCAUTH = 15,
    _2_seccEVSE_saAgentCERTUPDATE_DETAILS_FAULT_SAAGENTCOMM = 20,
    _2_seccEVSE_saAgentCERTUPDATE_DETAILS_FAULT_PARSEJSON = 21,
    _2_seccEVSE_saAgentCERTUPDATE_DETAILS_FAULT_CREATECSR = 22,
    _2_seccEVSE_saAgentCERTUPDATE_DETAILS_FAULT_RECIEVED_CERTCHAIN = 23,
    _2_seccEVSE_saAgentCERTUPDATE_DETAILS_FAULT_DECODE_EXI = 40
} _ECD501_SECC_COMM_STATUS_SAGENTCERT_UPDATE_DETAILS;

typedef enum {
    seccEVSE_saAgentAUTHORIZE_NONE = 0,
    seccEVSE_saAgentAUTHORIZE_HELLO = 10,
    seccEVSE_saAgentAUTHORIZE_GET_CERTIFICATE = 11,
    seccEVSE_saAgentAUTHORIZE_SIGN_SECCCERT = 12,
    seccEVSE_saAgentAUTHORIZE_CERT_INSTALL = 13,
    seccEVSE_saAgentAUTHORIZE_CERT_UPDATE = 14,
    seccEVSE_saAgentAUTHORIZE_PNCAUTH = 15,
    seccEVSE_saAgentAUTHORIZE_FAULT_SAAGENTCOMM = 20,
    seccEVSE_saAgentAUTHORIZE_FAULT_PARSEJSON = 21,
    seccEVSE_saAgentAUTHORIZE_FAULT_CREATECSR = 22,
    seccEVSE_saAgentAUTHORIZE_FAULT_RECIEVED_CERTCHAIN = 23,
    seccEVSE_saAgentAUTHORIZE_FAULT_DECODE_EXI = 40
} _ECD101_SECC_COMM_STATUS_SAGENTAUTHORIZE;

typedef enum {
    _2_seccEVSE_saAgentAUTHORIZE_NONE = 0,
    _2_seccEVSE_saAgentAUTHORIZE_HELLO = 10,
    _2_seccEVSE_saAgentAUTHORIZE_GET_CERTIFICATE = 11,
    _2_seccEVSE_saAgentAUTHORIZE_SIGN_SECCCERT = 12,
    _2_seccEVSE_saAgentAUTHORIZE_CERT_INSTALL = 13,
    _2_seccEVSE_saAgentAUTHORIZE_CERT_UPDATE = 14,
    _2_seccEVSE_saAgentAUTHORIZE_PNCAUTH = 15,
    _2_seccEVSE_saAgentAUTHORIZE_FAULT_SAAGENTCOMM = 20,
    _2_seccEVSE_saAgentAUTHORIZE_FAULT_PARSEJSON = 21,
    _2_seccEVSE_saAgentAUTHORIZE_FAULT_CREATECSR = 22,
    _2_seccEVSE_saAgentAUTHORIZE_FAULT_RECIEVED_CERTCHAIN = 23,
    _2_seccEVSE_saAgentAUTHORIZE_FAULT_DECODE_EXI = 40
} _ECD501_SECC_COMM_STATUS_SAGENTAUTHORIZE;

typedef struct {

    struct {
        uint8_t heartbeat;
        uint8_t seccVersionMajor;
        uint8_t seccVersionMinor;
        uint8_t seccVersionPatch;
    } _ECC101;

    struct {
        uint8_t cpVoltage_lsb;
        uint8_t cpVoltage_msb;
    } _ECC102;

    struct {
        uint8_t selected_SAS_sch_tuple_id;
    } _ECC103;

    struct {
        uint8_t sessionID_lsb0;
        uint8_t sessionID_lsb1;
        uint8_t sessionID_lsb2;
        uint8_t sessionID_lsb3;
        uint8_t sessionID_msb0;
        uint8_t sessionID_msb1;
        uint8_t sessionID_msb2;
        uint8_t sessionID_msb3;
    } _ECC104;

    struct {
        uint8_t evccMAC_Data0;
        uint8_t evccMAC_Data1;
        uint8_t evccMAC_Data2;
        uint8_t evccMAC_Data3;
        uint8_t evccMAC_Data4;
        uint8_t evccMAC_Data5;
        uint8_t evccAttn;
    } _ECC105;

    struct {
        uint8_t maxEntriesSAASSchedulelsb;
        uint8_t maxEntriesSAASSchedulemsb;
        uint8_t departure_timelsb0;
        uint8_t departure_timelsb1;
        uint8_t departure_timemsb0;
        uint8_t departure_timemsb1;
        uint8_t evMaximumPowerLimitlsb;
        uint8_t evMaximumPowerLimitmsb;
    } _ECC106;

    struct {
        uint8_t evMaximumCurrentLimitlsb;
        uint8_t evMaximumCurrentLimitmsb;
        uint8_t evMaximumVoltageLimitlsb;
        uint8_t evMaximumVoltageLimitmsb;
        uint8_t evEnergyCapacitylsb;
        uint8_t evEnergyCapacitymsb;
        uint8_t evEnergyRequestlsb;
        uint8_t evEnergyRequestmsb;
    } _ECC107;

    struct {
        uint8_t evSOC;
        uint8_t fullSOC;
        uint8_t bulkSOC;
        uint8_t remainingTimeToFullSOClsb;
        uint8_t remainingTimeToFullSOCmsb;
        uint8_t remainingTimeToBulkSOClsb;
        uint8_t remainingTimeToBulkSOCmsb;
    } _ECC108;

    struct {
        uint8_t seccTimeStamp_Data0;
        uint8_t seccTimeStamp_Data1;
        uint8_t seccTimeStamp_Data2;
        uint8_t seccTimeStamp_Data3;
        uint8_t seccTimeStamp_Data4;
        uint8_t seccTimeStamp_Data5;
        uint8_t seccTimeStamp_Data6;
        uint8_t seccTimeStamp_Data7;

    } _ECC10A;

    struct {
        uint8_t notificationCount;

    } _ECC1FF;

    struct {
        uint8_t seccIpAddr1;
        uint8_t seccIpAddr2;
        uint8_t seccIpAddr3;
        uint8_t seccIpAddr4;
    } _ECD102;




} PLC_Rx;

typedef struct {

    struct {
        uint8_t heartbeat;
        uint8_t seccVersionMajor;
        uint8_t seccVersionMinor;
        uint8_t seccVersionPatch;
    } _ECC501;

    struct {
        uint8_t selected_SAS_sch_tuple_id;
    } _ECC503;

 struct {
        uint8_t cpVoltage_lsb;
        uint8_t cpVoltage_msb;
    } _ECC502;

    struct {
        uint8_t sessionID_lsb0;
        uint8_t sessionID_lsb1;
        uint8_t sessionID_lsb2;
        uint8_t sessionID_lsb3;
        uint8_t sessionID_msb0;
        uint8_t sessionID_msb1;
        uint8_t sessionID_msb2;
        uint8_t sessionID_msb3;
    } _ECC504;

    struct {
        uint8_t evccMAC_Data0;
        uint8_t evccMAC_Data1;
        uint8_t evccMAC_Data2;
        uint8_t evccMAC_Data3;
        uint8_t evccMAC_Data4;
        uint8_t evccMAC_Data5;
        uint8_t evccAttn;
    } _ECC505;

    struct {
        uint8_t maxEntriesSAASSchedulelsb;
        uint8_t maxEntriesSAASSchedulemsb;
        uint8_t departure_timelsb0;
        uint8_t departure_timelsb1;
        uint8_t departure_timemsb0;
        uint8_t departure_timemsb1;
        uint8_t evMaximumPowerLimitlsb;
        uint8_t evMaximumPowerLimitmsb;
    } _ECC506;

    struct {
        uint8_t evMaximumCurrentLimitlsb;
        uint8_t evMaximumCurrentLimitmsb;
        uint8_t evMaximumVoltageLimitlsb;
        uint8_t evMaximumVoltageLimitmsb;
        uint8_t evEnergyCapacitylsb;
        uint8_t evEnergyCapacitymsb;
        uint8_t evEnergyRequestlsb;
        uint8_t evEnergyRequestmsb;
    } _ECC507;

    struct {
        uint8_t evSOC;
        uint8_t fullSOC;
        uint8_t bulkSOC;
        uint8_t remainingTimeToFullSOClsb;
        uint8_t remainingTimeToFullSOCmsb;
        uint8_t remainingTimeToBulkSOClsb;
        uint8_t remainingTimeToBulkSOCmsb;
    } _ECC508;

    struct {
        uint8_t seccTimeStamp_Data0;
        uint8_t seccTimeStamp_Data1;
        uint8_t seccTimeStamp_Data2;
        uint8_t seccTimeStamp_Data3;
        uint8_t seccTimeStamp_Data4;
        uint8_t seccTimeStamp_Data5;
        uint8_t seccTimeStamp_Data6;
        uint8_t seccTimeStamp_Data7;

    } _ECC50A;

    struct {
        uint8_t notificationCount;

    } _ECC5FF;

    struct {
        uint8_t seccIpAddr1;
        uint8_t seccIpAddr2;
        uint8_t seccIpAddr3;
        uint8_t seccIpAddr4;
    } _ECD502;

} _2_PLC_Rx;

typedef struct {
    uint8_t targetVoltagelsb;
    uint8_t targetVoltagemsb;
    uint8_t targetCurrentlsb;
    uint8_t targetCurrentmsb;

} PLC_RX_ECC109;

typedef struct {
    uint8_t targetVoltagelsb;
    uint8_t targetVoltagemsb;
    uint8_t targetCurrentlsb;
    uint8_t targetCurrentmsb;

   

} _2_PLC_RX_ECC509;