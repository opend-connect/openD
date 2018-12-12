/*
 * Copyright (C) 2018 by Dialog Semiconductor. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of Dialog Semiconductor nor the names of its Affiliates
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */
#ifndef MMIFPPPCOMMON_H   
#define MMIFPPPCOMMON_H      

#include <Standard/Common/RsStandard.h>
/****************************************************************************
*                               Include files                                 
****************************************************************************/

/****************************************************************************
*                              Macro definitions                             
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs                  
****************************************************************************/

// Definition of MMI PDU, common to FP
typedef enum
{
   MMI_DATA_TYPE_NONE = 				0x00,	// dummy message
   MMI_DATA_TYPE_KEEP_AWAKE= 			0x01,	// Keep alive signal
   MMI_DATA_TYPE_SYNC_TIME= 			0x02,	// testing purposes (legacy)
   MMI_DATA_TYPE_VBAT=					0x03,	// Battery levels 
   MMI_DATA_TYPE_SET_LOCK_TIMEOUT=		0x10,	// Timeout for searching for FP
   MMI_DATA_TYPE_SET_SLEEP_TIME=		0x11,	// sleep time
   MMI_DATA_TYPE_RFID=					0x12,	// RFID content

   // Generic sensor/actuator
   MMI_DATA_TYPE_HAL=					0x13,	// HAL control
   MMI_DATA_TYPE_WAKEUP_CFG=			0x14,	// Wakeup control
   MMI_DATA_TYPE_ADC=					0x15,	// ADC value

   MMI_DATA_GOTOSLEEP=					0x16,
   MMI_DATA_ENTER_REGISTRATION=			0x17,
   MMI_DATA_SET_TIMER=					0x18,
   MMI_DATA_SET_DECT_MODE=				0x19,	// Set DECT Mode
   MMI_DATA_SET_NVS_DEFAULT=			0x1A,	// Set NVS Default
   MMI_DATA_SET_ACTIVITY_COUNTERS=      0x1B,	// Set ActivityCounters
   //////////////////////////////////////////////////////////////
   // Custom sensors
   //////////////////////////////////////////////////////////////
   // sensors and actuators | measurement
   MMI_DATA_TYPE_TEMP_MEAS= 			0x20,	// temperature readout
   MMI_DATA_TYPE_RHUM_MEAS= 			0x21,	// Relative humidity readout
   MMI_DATA_TYPE_ALARM_EVENT=			0x22,	// generic alarm event
   MMI_DATA_TYPE_BUTTON_EVENT=			0x23,	// generic button press event
   MMI_DATA_TYPE_E_METER_MEAS=			0x24,	// E-meter readout (legacy PDU packet)
     
   MMI_DATA_TYPE_RF_TEST=				0x27,	//
   MMI_DATA_TYPE_DIN_220=				0x28,	// DIN module readings
   MMI_DATA_TYPE_P1_METER_MEAS=			0x29,	// Quby P1-meter readings

   MMI_DATA_TYPE_FWS=			0x2F,	//
   // sensors and actuators | control
   MMI_DATA_TYPE_DOOR_CMD=				0x30,	// Door lock / open command
   MMI_DATA_TYPE_SWITCH_220=			0x31,	// Switch (220V relais) command
   MMI_DATA_TYPE_DIMMER_220=			0x32,	// Dimmer (220V dimmer) command

   MMI_DATA_TYPE_INVALID=				0x33	// keep this always at the end
} RSENUM8(MmiDataType_t);

typedef enum
{
   MMI_SENSOR_TYPE_NONE = 				0x00,
   MMI_SENSOR_TYPE_GENERIC = 			0x01,
   MMI_ACTUATOR_TYPE_GENERIC = 			0x02,
   MMI_HANDSET_TYPE_GENERIC =           0x03,
   MMI_HANDSET_TYPE_PENDANT =           0x04,
   MMI_BATTERY_ACTUATOR_TYPE_GENERIC =  0x05,

   //////////////////////////////////////////////////////////////
   // Custom sensors
   //////////////////////////////////////////////////////////////
   MMI_SENSOR_TYPE_MOTION= 				0x11,
   MMI_SENSOR_TYPE_SMOKE= 				0x12,
   MMI_SENSOR_TYPE_WINDOW= 				0x13,
   MMI_SENSOR_TYPE_BUTTON=				0x14,
   MMI_SENSOR_TYPE_TEMP=				0x15,
   MMI_SENSOR_TYPE_RHUM=				0x16,
   MMI_SENSOR_TYPE_E_METER=				0x17,
   MMI_SENSOR_TYPE_REEDRELAIS=			0x18,
   
   MMI_ACTUATOR_TYPE_RF_TEST=			0x42,
   MMI_ACTUATOR_TYPE_DIN_220=			0x43,
   MMI_ACTUATOR_TYPE_P1_METER=			0x44,
   MMI_ACTUATOR_TYPE_SWITCH_220=		0x45,
   MMI_ACTUATOR_TYPE_DIMMER=			0x46,
   MMI_ACTUATOR_TYPE_DOORLOCK=			0x47,

   //////////////////////////////////////////////////////////////
   // HanFun Nodes Profiles
   //////////////////////////////////////////////////////////////
   MMI_HF_SIMPLE_ONOFF_SWITCH=			0x81,
   MMI_HF_AC_OUTLET_WITH_POWER_METER=	0x82,
   MMI_HF_SIMPLE_LIGHT=					0x83,
   MMI_HF_MOTION_DETECTOR=				0x84,
   
   MMI_SENSOR_TYPE_INVALID=				0x85	// keep this always at the end
} RSENUM8(MmiUleSensHdr_t);

typedef enum
{
	IGNORE=								0,
	WRITE_ONCE=							1,
	WRITE_TO_NVS=						2,
	READ=								3
} RSENUM8(MmiUleAction_t);

typedef enum
{
	CLOSE=								0,
	OPEN=								1
} RSENUM8(MmiUleReedRelaisState_t);


//////////////////////////////////////////////////////////////
// Message structs
//////////////////////////////////////////////////////////////

typedef struct
{
  rsuint16         	Length;
  MmiDataType_t    	Type;
} __attribute__((packed)) MmiUlePduHdr_t;

typedef struct
{  
  MmiUlePduHdr_t   Hdr;
  MmiUleSensHdr_t  SensorType;
  rsuint8		   NextMess;
  rsuint8          Data[500];
} __attribute__((packed)) MmiUlePdu_common_t;

//////////////////////////////////////////////////////////////
// Data structs
//////////////////////////////////////////////////////////////
// MMI_DATA_TYPE_NONE

// MMI_DATA_TYPE_KEEP_AWAKE

// MMI_DATA_TYPE_VBAT
typedef struct
{  
  rsuint8			vbat_value;			// Battery value in procent
  rsuint8          	DummyData[15];
} MmiUleData_MmiDataTypeVbat;

// MMI_DATA_TYPE_SET_LOCK_TIMEOUT
typedef struct
{  
  MmiUleAction_t	Cmd_Action;			// 
  rsuint16          LockTimeout;		// LOCK timeout in ms
  rsuint8          	DummyData[13];
} MmiUleData_MmiDataTypeSetLockTimeout;

// MMI_DATA_TYPE_SET_SLEEP_TIME
typedef struct
{  
  MmiUleAction_t	Cmd_Action;		
  rsuint32          SleepTime;			// Sleep time in ms
  rsuint8          	DummyData[11];
} MmiUleData_MmiDataTypeSetSleepTime;

// MMI_DATA_TYPE_RFID
#define MMI_ULPPDU_RFID_LEN 4
typedef struct
{  
  rsuint8           Id[MMI_ULPPDU_RFID_LEN];
  rsuint8          	DummyData[16-MMI_ULPPDU_RFID_LEN];
} MmiUleData_MmiDataTypeRfid;

// MMI_DATA_TYPE_HAL
typedef struct
{  
  MmiUleAction_t	Led_Cmd_Action;		
  rsuint8			LedNr;				// 1 = LED4, 0 = LED3
  rsuint8			LedCmd;				// 2 = 5mA, 1 = 2.5mA, 0 = off
  
  MmiUleAction_t	Adc_Cmd_Action;		
  rsuint8			AdcNr;				// 1 = ADC1, 0 = ADC0
  
  MmiUleAction_t	Gpio_Cmd_Action;	
  rsuint8			GpioNrCmd;			// [7-0] = P3[7-0]
  rsuint8			GpioValue;			// 1 = high, 0 = low
  
  MmiUleAction_t	Gpio_Cfg_Action;	
  rsuint8			GpioNrCfg;			// [7-0] = P3[7-0]
  rsuint8			GpioCfg;			// 3 = I-PD, 2 = I-PU, 1 = I, 0 = O
  
  MmiUleAction_t	ChargePump_Action;
  rsuint8			ChargePump_level;	// 3 = 4.5V, 2 = 3.5V, 1 = 3.0V, 0 = 2.5V
  rsuint8			ChargePump_en;		// 1 = enabled, 0 = disabled
    
  rsuint8          	DummyData[2];
  
} MmiUleData_MmiDataTypeHal;

// MMI_DATA_TYPE_WAKEUP_CFG
typedef struct
{  
  MmiUleAction_t	Wakeup_Action;	
  rsuint8			WakeupCause;		// 2 = Timer or PORT, 1 = Timer only, 0 = Port only
  rsuint8			WakeupPortCfg;		// 3 = Neg. edge trigger, 2 = Pos. edge trigger, 1 = Low level trigger, 0 = high level trigger

  rsuint8          	DummyData[13];

    
} MmiUleData_MmiDataTypeWakeupCfg;
//  MMI_DATA_TYPE_ADC
typedef struct
{
  rsuint8			AdcNumber;
  rsuint16			AdcValue;		// ADC value
  rsuint8          	DummyData[13];


} MmiUleData_MmiDataTypeAdc;


// MMI_DATA_TYPE_TEMP_MEAS
typedef struct
{  
  rsuint16			Temperature;		// Temperature value in C
  rsuint8          	DummyData[14];

    
} MmiUleData_MmiDataTypeTempMeas;

// MMI_DATA_TYPE_RHUM_MEAS
typedef struct
{  
  rsuint16			RhumLevel;			// Relative humidity level in %
  rsuint8          	DummyData[14];

    
} MmiUleData_MmiDataTypeRhumMeas;

// MMI_DATA_TYPE_ALARM_EVENT

// MMI_DATA_TYPE_BUTTON_EVENT

// MMI_DATA_TYPE_DOOR_CMD
typedef struct
{
  MmiUleAction_t	Door_Cmd_Action;	
  rsuint8			Door_Cmd;			// 1 = Lock, 0 = unlock
  
  rsuint8          	DummyData[14];

} MmiUleData_MmiDataTypeDoorCmd;

// MMI_DATA_TYPE_SWITCH_220
typedef struct
{
  MmiUleAction_t	Switch_Cmd_Action;	
  rsuint8			Switch_Cmd;			// 1 = On, 0 = Off
  
  rsuint8          	DummyData[14];

} MmiUleData_MmiDataTypeSwitch220;
	 
// MMI_DATA_TYPE_DIMMER_220
typedef struct
{
  MmiUleAction_t	Dimmer_Cmd_Action;	
  rsuint8			Dimmer_Lev;			// Dimmer level in procent (0 - 100)
  
  rsuint8          	DummyData[14];

} MmiUleData_MmiDataTypeDimmer220;
	 
// MMI_SENSOR_TYPE_REEDRELAIS
typedef struct
{
  MmiUleReedRelaisState_t	Reed_Relais_State;	// Reed relais state (open/close)
  rsuint8          			DummyData[15];

} MmiUleData_MmiDataTypeReedRelais;

// MMI_DATA_TYPE_FWS
typedef enum
{
	MDT_FWS_GET_VERSION_REQ,
	MDT_FWS_GET_VERSION_CFM,
	MDT_FWS_START_TRANSFER_REQ,
	MDT_FWS_START_TRANSFER_CFM,
	MDT_FWS_ABORT_TRANSFER_REQ,
	MDT_FWS_ABORT_TRANSFER_IND,
	MDT_FWS_XFER_SUCCESS_IND,
	MDT_FWS_XFER_TIMEOUT_IND,
	MDT_FWS_RESULT_SUCCESS_IND,
	MDT_FWS_RESULT_FAILED_IND,
	MDT_FWS_XFER_PENDED_ON_DTR_IND,

}
RSENUM8(MdtFwsAction);

typedef struct
{
	MdtFwsAction	Action;
	rsuint16		StackVersion;
	rsuint16		ColaRev;
	rsuint16		ColaBuildNo;
	rsuint8			ColaLinkDate[5];
	rsuint8         DummyData[4];
}
MmiUleData_MmiDataTypeFws;
typedef struct
{
	MdtFwsAction	Action;
	rsuint32		Offset;
	rsuint8         DummyData[11];
}
MmiUleData_MmiDataTypeFwsOffs;

 
//////////////////////////////////////////////////////////////
// Legacy PDUs
//////////////////////////////////////////////////////////////
typedef struct
{
  rsuint8          	Length;
  MmiDataType_t    	Type;   
} MmiUlpPduHdr_t;

typedef struct
{  
  rsuint8          Length;
  MmiDataType_t    Type;      
  rsuint16         Data;

} MmiUlpPdu_t;

typedef struct
{  
  MmiUlpPduHdr_t   Hdr;
  rsuint16         Data;

} MmiUlpPdu_Adc_t;

typedef struct
{
  MmiUlpPduHdr_t   Hdr;
  rsuint8          Xtal32;
  rsuint32         Time;
  rsuint16         LockTimeout;
  rsuint16         TxLatency;
} MmiUlpPdu_SyncTime_t;

// E-METER READOUT
typedef struct
{  
  MmiUlpPduHdr_t   	Hdr;
  char				MeterId[16];			// Meter ID string
  char				Power[8];				// Meter Power measurement    
} MmiUlePdu_E_meter;



#define MMI_ULPPDU_RFID_LEN 4
typedef struct
{
  MmiUlpPduHdr_t   Hdr;
  rsuint8          Id[MMI_ULPPDU_RFID_LEN];

} MmiUlpPdu_Rfid_t;

typedef enum
{
  MMI_ULP_DOOR_UNLOCK=0,
  MMI_ULP_DOOR_LOCK=1,

} RSENUM8(MmiUlpDoorCmd_t);

typedef struct
{
  MmiUlpPduHdr_t   Hdr;
  MmiUlpDoorCmd_t  Cmd;

} MmiUlpPdu_DoorCmd_t;


#endif

