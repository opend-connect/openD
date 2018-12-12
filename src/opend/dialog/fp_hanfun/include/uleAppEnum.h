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
 */#ifndef __ULERESOURCES_H__
#define __ULERESOURCES_H__
/*========================== Include files ==================================*/
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
//#include <unistd.h>
//#include <fcntl.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include <time.h>
#include <signal.h>
#include <errno.h>
#include <include/cJSON.h>
#include <include/targetip.h>

#ifdef IPBS_452_BUILD
#include <sys/signal.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <syslog.h>
#include <pthread.h>
#include <linux-2.6.x/include/linux/autoconf.h>
#include <Phoenix/Api/PhoenixApi.h>
#else
#include <Phoenix/Api/RsStandard.h>
#endif


/*========================== Macros / Definitions ==================================*/
#define TRUE 1
#define FALSE 0
#define PACKED_STRUCT __attribute__((packed))

#ifndef IPBS_452_BUILD
#define CONFIG_CATIQ_V11_SUPPORT
#define PC_BUILD
#endif

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

#define MAX_STR_LEN_FWS 50
#define MAX_FWS_FILE_NUM 8

#ifdef PC_BUILD
#define PRINT_MESSAGE(args...) 	fprintf(stdout,args);
#define ULE_ERR_MSG(args...) 	fprintf(stdout,"****************** ERROR START ******************\n");fprintf(stdout,args);fprintf(stdout,"****************** ERROR END ******************\n")
#else
#define PRINT_MESSAGE(args...) 	printf(args);syslog(LOG_INFO, args);
#define ULE_ERR_MSG(args...) 	printf("****************** ERROR START ******************\n");printf(args);syslog(LOG_INFO, args);printf("****************** ERROR END ******************\n")

#endif

#define MAX_SENSOR_TYPES_CNT (MMI_SENSOR_TYPE_INVALID) // Max number of different sensor types
#define MAX_DATA_TYPES_CNT (MMI_DATA_TYPE_INVALID) // Max number of different data/event types
#define ANY_SENSOR_TYPE (MMI_SENSOR_TYPE_INVALID) // define declaring function handler for any sensor type
#define ANY_DATA_TYPE (MMI_DATA_TYPE_INVALID) // define declaring function handler of different data/event type


typedef enum
{
	// housekeeping
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

   // <QubyAdditions>
   MMI_DATA_TYPE_RF_TEST=				0x27,	//
   MMI_DATA_TYPE_DIN_220=				0x28,	// DIN module readings
   // </QubyAdditions>

   MMI_DATA_TYPE_P1_METER_MEAS=			0x29,	// Quby P1-meter readings

   MMI_DATA_TYPE_FWS=			0x2F,	//
   // sensors and actuators | control
   MMI_DATA_TYPE_DOOR_CMD=				0x30,	// Door lock / open command
   MMI_DATA_TYPE_SWITCH_220=			0x31,	// Switch (220V relais) command
   MMI_DATA_TYPE_DIMMER_220=			0x32,	// Dimmer (220V dimmer) command

   MMI_DATA_TYPE_INVALID=				0x33	// // keep this always at the end

} RSENUM8(MmiDataType_t);

typedef enum
{
   MMI_SENSOR_TYPE_NONE = 				0x00,
   MMI_SENSOR_TYPE_GENERIC = 			0x01,
   MMI_ACTUATOR_TYPE_GENERIC = 			0x02,
   MMI_HANDSET_TYPE_GENERIC = 			0x03,
   MMI_HANDSET_TYPE_PENDANT = 			0x04,
   MMI_BATTERY_ACTUATOR_TYPE_GENERIC =	0x05,

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
   EARLY_BIT_OFF = 				0x00,
   EARLY_BIT_ON = 		    	0x01,
   EARLY_BIT_DISABLE = 			0x02,

} RSENUM8(EarlyBit_t);
//////////////////////////////////////////////////////////////
// Message structs
//////////////////////////////////////////////////////////////

typedef struct
{
#if defined(CONFIG_CATIQ_V11_SUPPORT) || defined(CONFIG_CATIQ_V12_SUPPORT)
	unsigned short           	Length;
#else
	unsigned char          Length;
#endif
  MmiDataType_t    	Type;
}PACKED_STRUCT MmiUlePduHdr_t;

typedef struct
{
  MmiUlePduHdr_t   Hdr;
  MmiUleSensHdr_t  SensorType;
  unsigned char		   NextMess;
  unsigned char          Data[PAYLOADDATASIZE];
}PACKED_STRUCT MmiUlePdu_common_t;

typedef enum
{
   DECT_LED0 = 0,
   DECT_LED1 = 1,
   DECT_LED2 = 2,
   DECT_LED3 = 3,
   DECT_REG_LED =4
} RSENUM8(ledType_t);

/*========================== Local functions =============*/
int initLedPorts(void);
int switchLed(ledType_t ledNumber, rsbool on);
int toggleLed(ledType_t ledNumber, int numberOfTimes);


typedef enum {  // ULE sensor valid states
	S_PP_NOT_REGISTERED, S_PP_ULE_ONLINE, S_PP_ULE_OFFLINE,
} PpState_e;


typedef struct {
	unsigned long DataPackId;
	unsigned long DataPackTimeStmp;
	MmiUlePdu_common_t Payload;
} DataPacket_t;

typedef struct s_DataPackets {
	DataPacket_t *DatPckt;
	struct s_DataPackets* next;
} DataPackets_t;

typedef enum {  // All error codes are placed here
	ULE_Success, // Operation Succeed
	ULE_Fail,	// ULE generic error
	ULE_InitFail, // ULE failed to initialize
	ULE_NotInitialized, // ULE is not initialized. Run ULE_Init first
	ULE_PP_OutOfRangeError, // Tried to access a portable device out of range: id > PP_COUNT_MAX (64)
	ULE_PP_AttrOutOfRangeError, // Tried to read an attribute value out of range MAXUSERATTRIB
	ULE_PP_BusTimeOutError, // SPI bus failed to initialize during ULE system Init
	ULE_AlreadyInitialized, // ULE sys is already initialized
	ULE_PP_Reserved2,
	ULE_PP_Reserved3,
	ULE_SetRegModeError,//10 // Failed to set ULE registration mode
	ULE_PP_Reserved4,
	ULE_PP_SetCodeError, // Failed to set ULE access code
	ULE_PP_GetCodeError, // Failed to get ULE access code
	ULE_PP_NotRegisteredError, // ULE ID device in not registered
	ULE_Get_Registration_CountError, // Failed to read which devices are registered
	ULE_TxAbortError,  // Failed to Abort TX data transmit
	ULE_TxBuffNoSpaceError, // Tx buffer is full
	ULE_CmdTypeFmtWrong, // Json string : Format of Cmdtype field is wrong
	ULE_IncorrectJsonInput, // Json string : Cannot parse Json string
	ULE_CmdTypeWrongValue,//20 // Json string : cmd type field is out of range
	ULE_PortIdFmtWrong, // Json string : Format of portID field is wrong
	ULE_PackIdFmtWrong,  // Json string : Format of PackID field is wrong
	ULE_DataFmtWrong, // Json string : Cannot read data field
	ULE_DataFmtTypeMismatch, // Json string : data field is not an array
	ULE_DataArrayTooLarge, // Json string : data field array is too large
	ULE_sysParamTypeFmtWrong, // Json string : SysParamType format error
	ULE_WriteOnly, // Json string : Can only write to property. Need to specify ParamValue
	ULE_sysParamTypeUnknown, // Json string : SysParamType is out of range
	ULE_ConfPortIdFmtWrong, // Json string : portID is not specified or is not a number
	ULE_ParamFmtWrong,//30  // Json string : Need to specify parameter array
	ULE_ConfParamFmtIsnNotArray,// Json string : Need to specify parameter array
	ULE_ConfParamFmtArrayErr, // Json string : Need to specify parameter array
	ULE_ConfParamTypeFmtWrongID, // Json string : ParameterID is not specified
	ULE_sysParamTypeFmtWrongVal, // Json string : Parameter value is not specified
	ULE_NotImplemented, // Feature not implemented yet
	ULE_ReadOnly, //Json string : Can only read this attribute and not set
	ULE_ParamTypeUnknown, // Json string : Parameter ID is unknown
	ULE_DeregistrationError, // Failed to deregister device
	ULE_SensortypeoutOfRange, // User registers a function for a non valid sensor type
	ULE_DatatypeoutOfRange, // 40 // User registers a function for a non valid data type
	ULE_UserDataJSONOBJECTNotDefined, // JSON user command does not specify UserData field
	ULE_UserDatahandleFunctionNotDefined, // JSON user command handler function is not specified yet
	ULE_EarlyBitConfigurationInvalid, // JSON early send configuration bit is not 0,1 or 2
	ULE_IPUIreadError, // Dect API failed to read IPUI
	ULE_RFPIreadError, // Dect API failed to read IPUI
	ULE_DectModereadError, // Dect API failed to read DectMode
} UleErr_e;



#endif // __ULERESOURCES_H__
