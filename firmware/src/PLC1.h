/* 
 * File:   PLC1.h
 * Author: Amit
 *
 * Created on 29 January, 2024, 12:34 PM
 */

#ifndef PLC1_H
#define	PLC1_H

#ifdef	__cplusplus
extern "C" {
    
#endif


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

#define _1_CHARGING_NONE	3
#define _1_CHARGING_COMPLETE	1
#define _1_CHARGING_NOT_COMPLETE	0
#define _1_PLC_STATE_IDLE_1	1
#define _1_PLC_STATE_IDLE_2	2
#define _1_PLC_STATE_INITIALIZED_1	3
#define _1_PLC_STATE_INITIALIZED_2	4
#define _1_PLC_STATE_WAITING_FOR_PLUG_IN	5
#define _1_PLC_STATE_WAITING_SLAC	6
#define _1_PLC_STATE_PROCESSING_SLAC	7
#define _1_PLC_STATE_SDP	8
#define _1_PLC_STATE_ESTABLISHING_TCP	9
#define _1_PLC_STATE_COMMON_ERROR	10
#define _1_PLC_STATE_SAP_SESSION_SERVICEDISCOVERY	11
#define _1_PLC_STATE_SERVICE_DETAIL	12
#define _1_PLC_STATE_PAYMENT_SERVICE_SELECTION	13
#define _1_PLC_STATE_CERTIFICATE_INSTALL	14
#define _1_PLC_STATE_CERTIFICATE_UPDATE	15
#define _1_PLC_STATE_PAYMENT_DETAILS	16
#define _1_PLC_STATE_AUTHORIZATION_EIM	17
#define _1_PLC_STATE_AUTHORIZATION_PNC	18
#define _1_PLC_STATE_CHARGE_PARAMETER_DISCOVERY	19
#define _1_PLC_STATE_CABLE_CHECK	20
#define _1_PLC_STATE_PRE_CHARGE	21
#define _1_PLC_STATE_POWER_DELIVERED	22
#define _1_PLC_STATE_CURRENT_DEMAND_1	23
#define _1_PLC_STATE_CURRENT_DEMAND_2	24
#define _1_PLC_STATE_CURRENT_DEMAND_3	25
#define _1_PLC_STATE_POWER_DELIVERY_RENOGOTIATE	26
#define _1_PLC_STATE_POWER_DELIVERY_EVINITSTOP	27
#define _1_PLC_STATE_POWER_DELIVERY_EVSEINITSTOP	28
#define _1_PLC_STATE_WELDING_DETECTION	29
#define _1_PLC_STATE_SESSION_STOP	30
#define _1_PLC_STATE_TERMINATED	31
#define _1_PLC_STATE_ERROR_STATE	32
#define _1_PLC_STATE_RE_NEGO_STATE	33   
#define _1_PLC_STATE_NONE    0
    
#define _2_PLC_STATE_NONE    0    
#define _2_CHARGING_NONE	3
#define _2_CHARGING_COMPLETE	1
#define _2_CHARGING_NOT_COMPLETE	0
#define _2_PLC_STATE_IDLE_1	1
#define _2_PLC_STATE_IDLE_2	2
#define _2_PLC_STATE_INITIALIZED_1	3
#define _2_PLC_STATE_INITIALIZED_2	4
#define _2_PLC_STATE_WAITING_FOR_PLUG_IN	5
#define _2_PLC_STATE_WAITING_SLAC	6
#define _2_PLC_STATE_PROCESSING_SLAC	7
#define _2_PLC_STATE_SDP	8
#define _2_PLC_STATE_ESTABLISHING_TCP	9
#define _2_PLC_STATE_COMMON_ERROR	10
#define _2_PLC_STATE_SAP_SESSION_SERVICEDISCOVERY	11
#define _2_PLC_STATE_SERVICE_DETAIL	12
#define _2_PLC_STATE_PAYMENT_SERVICE_SELECTION	13
#define _2_PLC_STATE_CERTIFICATE_INSTALL	14
#define _2_PLC_STATE_CERTIFICATE_UPDATE	15
#define _2_PLC_STATE_PAYMENT_DETAILS	16
#define _2_PLC_STATE_AUTHORIZATION_EIM	17
#define _2_PLC_STATE_AUTHORIZATION_PNC	18
#define _2_PLC_STATE_CHARGE_PARAMETER_DISCOVERY	19
#define _2_PLC_STATE_CABLE_CHECK	20
#define _2_PLC_STATE_PRE_CHARGE	21
#define _2_PLC_STATE_POWER_DELIVERED	22
#define _2_PLC_STATE_CURRENT_DEMAND_1	23
#define _2_PLC_STATE_CURRENT_DEMAND_2	24
#define _2_PLC_STATE_CURRENT_DEMAND_3	25
#define _2_PLC_STATE_POWER_DELIVERY_RENOGOTIATE	26
#define _2_PLC_STATE_POWER_DELIVERY_EVINITSTOP	27
#define _2_PLC_STATE_POWER_DELIVERY_EVSEINITSTOP	28
#define _2_PLC_STATE_WELDING_DETECTION	29
#define _2_PLC_STATE_SESSION_STOP	30
#define _2_PLC_STATE_TERMINATED	31
#define _2_PLC_STATE_ERROR_STATE	32



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
    } SECC_Status;



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
    } SECC_evERRORCODE;


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

    } SECC_seccERROR_CODES;

    typedef enum {
        seccPnCReady_NONE = 0, seccPnCReady_NotReady = 1, seccPnCReady_Ready = 2,
    } SECC_PnCREADY;


    typedef struct {
        uint8_t heartbeat;
        uint8_t seccVersionMajor;
        uint8_t seccVersionMinor;
        uint8_t seccVersionPatch;
        SECC_Status _101_SECC_Status_t;
        SECC_evERRORCODE _101_SECC_evERRORCODE_t;
        SECC_seccERROR_CODES _101_SECC_seccERROR_CODES_t;
        SECC_PnCREADY _101_SECC_PnCREADY_t;
    } _C101_Q;

    typedef struct {
        uint8_t heartbeat;
        uint8_t seccVersionMajor;
        uint8_t seccVersionMinor;
        uint8_t seccVersionPatch;
        SECC_Status _501_SECC_Status_t;
        SECC_evERRORCODE _501_SECC_evERRORCODE_t;
        SECC_seccERROR_CODES _501_SECC_seccERROR_CODES_t;
        SECC_PnCREADY _501_SECC_PnCREADY_t;
    } _C501_Q;

    typedef enum {
        seccCpOscillator_Duty_Cycle_OFF = 0, seccCpOscillator_Duty_Cycle_ON = 1,
    } SECC_CP;


    typedef enum {
        seccHpgpLink_Link_Down = 0, seccHpgpLink_Link_UP = 1,
    } SECC_HpgpLink;



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
    } SECC_TLSERROR;


    typedef struct {
        uint8_t cpVoltage_lsb;
        uint8_t cpVoltage_msb;
        SECC_CP _102_SECC_CP_t;
        SECC_HpgpLink _102_SECC_HpgpLink_t;
        SECC_TLSERROR _102_SECC_TLSERROR_t;
    } _C102_Q;

    typedef struct {
        uint8_t cpVoltage_lsb;
        uint8_t cpVoltage_msb;
        SECC_CP _502_SECC_CP_t;
        SECC_HpgpLink _502_SECC_HpgpLink_t;
        SECC_TLSERROR _502_SECC_TLSERROR_t;
    } _C502_Q;

    typedef enum {
        seccEVSS_CHG_DIN = 0,
        seccEVSS_CHG_ISO_2013 = 1,
        seccEVSS_CHG_ISO_2016 = 2,
        seccEVSS_CHG_NONE = 255, //Need to Ask Not sure
    } SELECTED_CHARGING_PROTOCOL;


    typedef enum {
        seccEVSS_PAY_CONTRACT = 0,
        seccEVSS_PAY_EXTERNAL = 1,
        seccEVSS_PAY_NONE = 255, //Need to Ask Not sure
    } SELECTED_PAYMENT_OPTION;

    typedef enum {
        seccEVSS_ENERGY_AC_SINGLE_PHASE = 0,
        seccEVSS_ENERGY_AC_THREE_PHASE = 1,
        seccEVSS_ENERGY_DC_CORE = 2,
        seccEVSS_ENERGY_DC_EXTENDED = 3,
        seccEVSS_ENERGY_DC_COMBO_CORE = 4,
        seccEVSS_ENERGY_DC_UNIQUE = 5,
        seccEVSS_ENERGY_DC_NONE = 255, //NEED TO ASK
    } SELECTED_ENERGY_TRANSFER_MODE;



    typedef struct {
        uint8_t selected_SAS_sch_tuple_id;
        bool Selected_service_EVCharging;
        bool Selected_service_Internet;
        bool Selected_Service_ContractCert;
        bool Selected_OtherCustoms;
        bool Selected_HPC1;
        bool Selected_ContractServiceInstallation;
        bool Selected_contractServiceUpdate;
        SELECTED_CHARGING_PROTOCOL _103_SELECTED_CHARGING_PROTOCOL_t;
        SELECTED_ENERGY_TRANSFER_MODE _103_SELECTED_ENERGY_TRANSFER_MODE_t;
        SELECTED_PAYMENT_OPTION _103_SELECTED_PAYMENT_OPTION_t;
    } _C103_Q;

    typedef struct {
        uint8_t selected_SAS_sch_tuple_id;
        bool Selected_service_EVCharging;
        bool Selected_service_Internet;
        bool Selected_Service_ContractCert;
        bool Selected_OtherCustoms;
        bool Selected_HPC1;
        bool Selected_ContractServiceInstallation;
        bool Selected_contractServiceUpdate;
        SELECTED_CHARGING_PROTOCOL _503_SELECTED_CHARGING_PROTOCOL_t;
        SELECTED_ENERGY_TRANSFER_MODE _503_SELECTED_ENERGY_TRANSFER_MODE_t;
        SELECTED_PAYMENT_OPTION _503_SELECTED_PAYMENT_OPTION_t;
    } _C503_Q;

    typedef struct {
        uint8_t sessionID_lsb0;
        uint8_t sessionID_lsb1;
        uint8_t sessionID_lsb2;
        uint8_t sessionID_lsb3;
        uint8_t sessionID_msb0;
        uint8_t sessionID_msb1;
        uint8_t sessionID_msb2;
        uint8_t sessionID_msb3;
    } _C104_Q;

    typedef struct {
        uint8_t sessionID_lsb0;
        uint8_t sessionID_lsb1;
        uint8_t sessionID_lsb2;
        uint8_t sessionID_lsb3;
        uint8_t sessionID_msb0;
        uint8_t sessionID_msb1;
        uint8_t sessionID_msb2;
        uint8_t sessionID_msb3;
    } _C504_Q;

    typedef struct {
        uint8_t evccMAC_Data0;
        uint8_t evccMAC_Data1;
        uint8_t evccMAC_Data2;
        uint8_t evccMAC_Data3;
        uint8_t evccMAC_Data4;
        uint8_t evccMAC_Data5;
        uint8_t evccAttn;
    } _C105_Q;

    typedef struct {
        uint8_t evccMAC_Data0;
        uint8_t evccMAC_Data1;
        uint8_t evccMAC_Data2;
        uint8_t evccMAC_Data3;
        uint8_t evccMAC_Data4;
        uint8_t evccMAC_Data5;
        uint8_t evccAttn;
    } _C505_Q;

    typedef struct {
        uint8_t maxEntriesSAASSchedulelsb;
        uint8_t maxEntriesSAASSchedulemsb;
        uint8_t departure_timelsb0;
        uint8_t departure_timelsb1;
        uint8_t departure_timemsb0;
        uint8_t departure_timemsb1;
        uint8_t evMaximumPowerLimitlsb;
        uint8_t evMaximumPowerLimitmsb;
    } _C106_Q;

    typedef struct {
        uint8_t maxEntriesSAASSchedulelsb;
        uint8_t maxEntriesSAASSchedulemsb;
        uint8_t departure_timelsb0;
        uint8_t departure_timelsb1;
        uint8_t departure_timemsb0;
        uint8_t departure_timemsb1;
        uint8_t evMaximumPowerLimitlsb;
        uint8_t evMaximumPowerLimitmsb;
    } _C506_Q;

    typedef struct {
        uint8_t evMaximumCurrentLimitlsb;
        uint8_t evMaximumCurrentLimitmsb;
        uint8_t evMaximumVoltageLimitlsb;
        uint8_t evMaximumVoltageLimitmsb;
        uint8_t evEnergyCapacitylsb;
        uint8_t evEnergyCapacitymsb;
        uint8_t evEnergyRequestlsb;
        uint8_t evEnergyRequestmsb;
    } _C107_Q;

    typedef struct {
        uint8_t evMaximumCurrentLimitlsb;
        uint8_t evMaximumCurrentLimitmsb;
        uint8_t evMaximumVoltageLimitlsb;
        uint8_t evMaximumVoltageLimitmsb;
        uint8_t evEnergyCapacitylsb;
        uint8_t evEnergyCapacitymsb;
        uint8_t evEnergyRequestlsb;
        uint8_t evEnergyRequestmsb;
    } _C507_Q;

    typedef struct {
        uint8_t Charging_Complete_t;
        uint8_t Charging_BULK_Complete;
        uint8_t evSOC;
        uint8_t fullSOC;
        uint8_t bulkSOC;
        uint8_t remainingTimeToFullSOClsb;
        uint8_t remainingTimeToFullSOCmsb;
        uint8_t remainingTimeToBulkSOClsb;
        uint8_t remainingTimeToBulkSOCmsb;
    } _C108_Q;

    typedef struct {
        uint8_t Charging_Complete_t;
        uint8_t Charging_BULK_Complete;
        uint8_t evSOC;
        uint8_t fullSOC;
        uint8_t bulkSOC;
        uint8_t remainingTimeToFullSOClsb;
        uint8_t remainingTimeToFullSOCmsb;
        uint8_t remainingTimeToBulkSOClsb;
        uint8_t remainingTimeToBulkSOCmsb;
    } _C508_Q;

    typedef struct {
        uint8_t targetVoltagelsb;
        uint8_t targetVoltagemsb;
        uint8_t targetCurrentlsb;
        uint8_t targetCurrentmsb;
    } _C109_Q;

    typedef struct {
        uint8_t targetVoltagelsb;
        uint8_t targetVoltagemsb;
        uint8_t targetCurrentlsb;
        uint8_t targetCurrentmsb;
    } _C509_Q;

    typedef struct {
        uint8_t seccTimeStamp_Data0;
        uint8_t seccTimeStamp_Data1;
        uint8_t seccTimeStamp_Data2;
        uint8_t seccTimeStamp_Data3;
        uint8_t seccTimeStamp_Data4;
        uint8_t seccTimeStamp_Data5;
        uint8_t seccTimeStamp_Data6;
        uint8_t seccTimeStamp_Data7;
    } _C10A_Q;

    typedef struct {
        uint8_t seccTimeStamp_Data0;
        uint8_t seccTimeStamp_Data1;
        uint8_t seccTimeStamp_Data2;
        uint8_t seccTimeStamp_Data3;
        uint8_t seccTimeStamp_Data4;
        uint8_t seccTimeStamp_Data5;
        uint8_t seccTimeStamp_Data6;
        uint8_t seccTimeStamp_Data7;
    } _C50A_Q;

    typedef enum {
        seccEstablishedInfo_NONE = 0,
        seccEstablishedInfo_NonTLS_Established = 1,
        seccEstablishedInfo_PublicTLS_Established = 2,
        seccEstablishedInfo_PrivateTLS_Established = 3,
    } SECC_STATUS3_ESTABLISHEDINFO;



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

    } SECC_STATUS3;



    typedef struct {
        SECC_STATUS3 _10B_SECC_STATUS3_t;
        SECC_STATUS3_ESTABLISHEDINFO _10B_SECC_STATUS3_ESTABLISHEDINFO_t;
    } _C10B_Q;

    typedef struct {
        SECC_STATUS3 _50B_SECC_STATUS3_t;
        SECC_STATUS3_ESTABLISHEDINFO _50B_SECC_STATUS3_ESTABLISHEDINFO_t;
    } _C50B_Q;

    typedef struct {
        uint8_t notificationCount;
    } _C1FF_Q;

    typedef struct {
        uint8_t notificationCount;
    } _C5FF_Q;

    typedef enum {
        seccEVSE_saAgentINIT_NONE = 0,
        seccEVSE_saAgentINIT_NON_TLS = 1,
        seccEVSE_saAgentINIT_PUBLIC_TLS = 2,
        seccEVSE_saAgentINIT_Private_TLS = 3,
    } SECC_COMM_STATUS_SAGENTINIT;



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
    } SECC_COMM_STATUS_SAGENTINIT_Details;



    typedef struct {
        SECC_COMM_STATUS_SAGENTINIT _ECD101_SECC_COMM_STATUS_SAGENTINIT_t;
        SECC_COMM_STATUS_SAGENTINIT_Details _ECD101_SECC_COMM_STATUS_SAGENTINIT_Details_t;
    } _D101_Q;

    typedef struct {
        SECC_COMM_STATUS_SAGENTINIT _ECD501_SECC_COMM_STATUS_SAGENTINIT_t;
        SECC_COMM_STATUS_SAGENTINIT_Details _ECD501_SECC_COMM_STATUS_SAGENTINIT_Details_t;

    } _D501_Q;

    typedef enum {
        Charging_Control_None = 0,
        Charging_Control_Initialised_PPMT = 1,
        Charging_Control_Start_Charging = 2,
        Charging_Control_Normal_Stop = 3,
        Charging_Control_EMG_Stop = 4,
        _
    } EVSE_CHARGING_CONTROL_DATA1;

    typedef enum {
        Isolation_Status_Invalid = 0,
        Isolation_Status_Valid = 1,
        Isolation_Status_Warning = 2,
        Isolation_Status_Fault = 3,
        Isolation_Status_NoIMD = 4, //Need to Check all the time if fault need to Stop Charging Control need to invalid after Charging
    } EVSE_ISOLATION_STATUS_DATA4;

    typedef enum {
        EVSE_Processing_Auth_EIM = 0,
        EVSE_Processing_CPD = 1,
        EVSE_Processing_Cable_check = 2,
        EVSE_Isolation_Mointor = 3,
        EVSE_Trigger_Negotation = 4,
        EVSE_Trigger_State = 6,

        //Initialized all to zero after each Session except heartbeat and charging Control and trigger state
    } EVSE_PROCESSING_DATA6;

    typedef enum {
        EVSE_Current_Limit = 0,
        EVSE_Voltage_Limit = 1,
        EVSE_Power_Limit = 2,
    } EVSE_VCP_LIMIT_DATA7;

    typedef struct {
        uint8_t _002_EVSE_STATUS_HEARTBEAT_DATA0;
        uint8_t _002_EVSE_NOTIFICATION_DELAY_LSB_DATA2;
        uint8_t _002_EVSE_NOTIFICATION_DELAY_MSB_DATA3;
        EVSE_CHARGING_CONTROL_DATA1 _002_EVSE_CHARGING_CONTROL_DATA1_t;
        EVSE_ISOLATION_STATUS_DATA4 _002_EVSE_ISOLATION_STATUS_DATA4_t;
        EVSE_PROCESSING_DATA6 _002_EVSE_PROCESSING_DATA6_t;
        EVSE_VCP_LIMIT_DATA7 _002_EVSE_VCP_LIMIT_DATA7_t;
        uint8_t _005_EVSE_PRESENT_VOLTAGE_LSB_DATA1;
        uint8_t _005_EVSE_PRESENT_VOLTAGE_MSB_DATA0;
        uint8_t _005_EVSE_PRESENT_CURRENT_LSB_DATA3;
        uint8_t _005_EVSE_PRESENT_CURRENT_MSB_DATA2;
        uint32_t _006_EVSE_DIN_ID1_LSB;
        uint32_t _006_EVSE_DIN_ID1_MSB;
        uint32_t _007_EVSE_DIN_ID2_LSB;
        uint32_t _007_EVSE_DIN_ID2_MSB;
    } _1_PLC_tx_50;

    typedef struct {
        uint8_t _402_EVSE_STATUS_HEARTBEAT_DATA0;
        uint8_t _402_EVSE_NOTIFICATION_DELAY_LSB_DATA2;
        uint8_t _402_EVSE_NOTIFICATION_DELAY_MSB_DATA3;
        uint8_t _405_EVSE_PRESENT_VOLTAGE_LSB_DATA1;
        uint8_t _405_EVSE_PRESENT_VOLTAGE_MSB_DATA0;
        uint8_t _405_EVSE_PRESENT_CURRENT_LSB_DATA3;
        uint8_t _405_EVSE_PRESENT_CURRENT_MSB_DATA2;
        uint32_t _406_EVSE_DIN_ID1_LSB;
        uint32_t _406_EVSE_DIN_ID1_MSB;
        uint32_t _407_EVSE_DIN_ID2_LSB;
        uint32_t _407_EVSE_DIN_ID2_MSB;
        EVSE_CHARGING_CONTROL_DATA1 _402_EVSE_CHARGING_CONTROL_DATA1_t;
        EVSE_ISOLATION_STATUS_DATA4 _402_EVSE_ISOLATION_STATUS_DATA4_t;
        EVSE_PROCESSING_DATA6 _402_EVSE_PROCESSING_DATA6_t;
        EVSE_VCP_LIMIT_DATA7 _402_EVSE_VCP_LIMIT_DATA7_t;
    } _2_PLC_tx_50;

    typedef enum {
        EVSE_PKIENVSELECTION_None = 0,
        EVSE_PKIENVSELECTION_Public = 1,
        EVSE_PKIENVSELECTION_Private = 2,
    } EVSE_PKIENVSELECTION_DATA0;

    typedef enum {
        EVSE_CERTCHAINVALID_None = 0,
        EVSE_CERTCHAINVALID_Passive = 1,
        EVSE_CERTCHAINVALID_Active = 2,
        EVSE_CERTCHAINVALID_Forced = 3,
    } EVSE_CERTCHAINVALID_DATA1;

    typedef enum {
        EVSE_RKEYOPTION_False = 0, EVSE_RKEYOPTION_True = 1,
    } EVSE_RKEYOPTION_DATA2;

    typedef struct {
        uint8_t _D001_EVSE_SAAGENTIPADDR1_DATA0;
        uint8_t _D001_EVSE_SAAGENTIPADDR2_DATA1;
        uint8_t _D001_EVSE_SAAGENTIPADDR3_DATA2;
        uint8_t _D001_EVSE_SAAGENTIPADDR4_DATA3;
        uint8_t _D001_EVSE_SAAGENTPORT_LSB_DATA4;
        uint8_t _D001_EVSE_SAAGENTPORT_MSB_DATA5;
        EVSE_PKIENVSELECTION_DATA0 _D002_EVSE_PKIENVSELECTION_DATA0_t;
        EVSE_CERTCHAINVALID_DATA1 _D002_EVSE_CERTCHAINVALID_DATA1_t;
        EVSE_RKEYOPTION_DATA2 _D002_EVSE_RKEYOPTION_DATA2_t;
        uint8_t _D003_EVSE_SAAGENTHELLORESPONSE_DATA1;
        uint8_t _D003_EVSE_SAAGENTGETCERTIFICATIONSTATUSRESPONSE_DATA2;
        uint8_t _D003_EVSE_SAAGENTCERTINSTALL_DATA3;
        uint8_t _D003_EVSE_SAAGENTCERTUPDATE_DATA4;
        uint8_t _D003_EVSE_SAAGENTAUTHORIZE_DATA5;
    } _1_PLC_tx_1000;

    typedef struct {
        uint8_t _D401_EVSE_SAAGENTIPADDR1_DATA0;
        uint8_t _D401_EVSE_SAAGENTIPADDR2_DATA1;
        uint8_t _D401_EVSE_SAAGENTIPADDR3_DATA2;
        uint8_t _D401_EVSE_SAAGENTIPADDR4_DATA3;
        uint8_t _D401_EVSE_SAAGENTPORT_LSB_DATA4;
        uint8_t _D401_EVSE_SAAGENTPORT_MSB_DATA5;
        EVSE_PKIENVSELECTION_DATA0 _D402_EVSE_PKIENVSELECTION_DATA0_t;
        EVSE_CERTCHAINVALID_DATA1 _D402_EVSE_CERTCHAINVALID_DATA1_t;
        EVSE_RKEYOPTION_DATA2 _D402_EVSE_RKEYOPTION_DATA2_t;
        uint8_t _D403_EVSE_SAAGENTHELLORESPONSE_DATA1;
        uint8_t _D403_EVSE_SAAGENTGETCERTIFICATIONSTATUSRESPONSE_DATA2;
        uint8_t _D403_EVSE_SAAGENTCERTINSTALL_DATA3;
        uint8_t _D403_EVSE_SAAGENTCERTUPDATE_DATA4;
        uint8_t _D403_EVSE_SAAGENTAUTHORIZE_DATA5;
    } _2_PLC_tx_1000;

    typedef enum {
        evseIDConfig_DIN = 0, evseIDConfig_ISO = 1, environmentConfig = 4,
    } EVSECONFIG_DATA0;

    typedef enum {
        SupportEnergyTransfer_DCCORE = 2,

        SupportEnergyTransfer_DCEXTD = 3,

        SupportEnergyTransfer_DCCC = 4,

        SupportEnergyTransfer_DCUNI = 5,
        //at least one energy transfer mode is selected
    } SUPPORTENERGY_TRANSFER_DATA3;

    typedef enum {
        Paid_Service_EvCharging = 0,
        Free_Service_EvCharging = 1,
        Free_Service_Contract_Paid = 0,
        Free_Service_Contract_Free = 4,
        Free_Service_OtherCustom_Paid = 0,
        Free_Service_OtherCustom_Free = 8,
    } SERVICE_TYPE_DATA5;

    typedef enum {
        Schedule_Mgt_Default = 0,
        Schedule_Mgt_OCPP = 1,
        Schedule_Mgt_Interoperability = 2,
    } SCHEDULE_MGT_DATA6;

    typedef enum {
        CP_Mointor_Mode_Passive = 0,
        CP_Mointor_Mode_Active = 1,
        CP_Voltage_Senstivity_WS5 = 0,
        CP_Voltage_Senstivity_WS10 = 2,
        CP_Voltage_Senstivity_WS3 = 4,
        CP_Voltage_Senstivity_WS1 = 6,
    } CP_MOINTOR_MODE_DATA7;

    typedef struct {
        EVSECONFIG_DATA0 _001EVSECONFIG_DATA0_t;
        SUPPORTENERGY_TRANSFER_DATA3 _001SUPPORTENERGY_TRANSFER_DATA3_t;
        SERVICE_TYPE_DATA5 _001SERVICE_TYPE_DATA5_t;
        SCHEDULE_MGT_DATA6 _001_SCHEDULE_MGT_DATA6_t;
        CP_MOINTOR_MODE_DATA7 _001_CP_MOINTOR_MODE_DATA7_t;
        uint8_t _001EVSEIDLENGTH_DIN_DATA1;
        uint8_t _001EVSEIDLENGTH_ISO_DATA2;
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
    } _1_PLC_tx_200;

    typedef struct {
        uint8_t _401EVSEIDLENGTH_DIN_DATA1;
        uint8_t _401EVSEIDLENGTH_ISO_DATA2;
        EVSECONFIG_DATA0 _401EVSECONFIG_DATA0_t;
        SUPPORTENERGY_TRANSFER_DATA3 _401SUPPORTENERGY_TRANSFER_DATA3_t;
        SERVICE_TYPE_DATA5 _401SERVICE_TYPE_DATA5_t;
        SCHEDULE_MGT_DATA6 _401_SCHEDULE_MGT_DATA6_t;
        CP_MOINTOR_MODE_DATA7 _401_CP_MOINTOR_MODE_DATA7_t;
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




#ifdef	__cplusplus
}
#endif

#endif	/* PLC1_H */

