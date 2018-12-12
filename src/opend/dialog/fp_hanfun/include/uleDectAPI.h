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
#ifndef __ULEDECTAPI_H__
#define __ULEDECTAPI_H__

#ifdef IPBS_452_BUILD
#include <microhttpd.h>
#include <unistd.h>
#endif

#include <stdbool.h>
#include <stdio.h>
#include <errno.h>
//#include <unistd.h>
#include <string.h>

/*========================== Macros / Definitions ==================================*/
#define TRUE 1
#define FALSE 0

#define PP_COUNT_MAX 24 // Max ULE Sensor support
#define PP_COUNT_ALL (PP_COUNT_MAX + 1) // This is to signal that action for ALL sensors has to be taken
#define RX_BUFF_SIZE  8 // Each ULE sensor is assigned a receive buffer. This is the size of this buffer.
#define MAXUSERATTRIB 9 // Max number of values used in user application
#define CHECK_PERIOD 1 // timer thread takes action  every this amount of seconds
#define PAYLOADDATASIZE 496 // Define for hardcoded value in MniFpPpCommon.h   rsuint8   Data[16];
#define DATA_TRANSMIT_MAX_SIZE (PAYLOADDATASIZE + 4) // Max number of bytes for TX. Each TX message cannot contain more of this # of bytes.

#ifndef WIN_BUILD
//Define this to add power cycle test option (power cycle plug testing)
#define POWERPLUG_CYCLE_TEST
//Define this to add CRON support (switch plug on/off based on a calendar schedule)
#define CRON_SUPPORT
#endif

// define this to automatically enable RsxCustomer tracing every time the module/base starts up
#define ENABLE_AUTO_RSX_TRACING

// 500 byte Data Link stress test, should also be enabled on PP
//#define DATA_LINK_TEST
//#define DATA_LINK_TEST_PACKET_SIZE 500

#include <include/uleAppEnum.h>
#include <include/uleAppAPI.h>

#ifdef IPBS_452_BUILD
#define FWS_FILE_SAVE_DIR "/mnt/flash/"
#else
#define CONFIG_CATIQ_V11_SUPPORT
#define FWS_FILE_SAVE_DIR "./"
#define PC_BUILD
#endif


#define ULE_INIT_CONNECT_WITH_REPS -2
#define ULE_INIT_CONNECT_ON_LINUX_HOST -3


#define DECTMODE_EUROPE 0
#define DECTMODE_US		1
#define DECTMODE_JP_5CH 2
#define NVS_DEFAULT 3

#define ACCESSCODE 0xFFFF0000
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

#ifdef POWERPLUG_CYCLE_TEST
	extern rsbool setSmartplugTimer;
#endif

typedef enum { // Enum for  valid ULE initialization state
	ULE_Init_Success, ULE_Init_Fail, ULE_Init_Pending,
} UleInitStatus_e;

typedef enum { //State for Tx Buffer
	Tx_Buff_Empty, Tx_Buff_Empty_TxSuccess, //Is empty after last Tx transmition succedded (RTS received)
	Tx_Buff_Empty_TxRejected,//Is empty after last Tx transmition failed (Reject received)
	Tx_Buff_Empty_TxAborted,//Is empty after last Tx transmition was aborted (Abort command send)
	Tx_Buff_Full,
//Send commands are rejected since Tx buff is full
} TxBufStatus_e;

typedef struct { // Enum holds state of registration mode and access code values
	rsbool registrationMode;
	rsuint32 registrationMode_timeout;
	rsuint8 Ac[4];
	rsbool AcChanged;
	rsuint8 RFPI[5];
} SysInfo_t;

typedef struct { // This enum holds the return values of all Confirmation commands from Dect PI
	RsStatusType GetAccessCodeStatus;
	rsuint8 Ac[4];
	rsuint8 DectMode;
	rsuint8 DevRegCnt;
	RsStatusType DectModeStatus;
	RsStatusType SetAccessCodeStatus;
	RsStatusType RegCountStatus;
	RsStatusType AbortStatus;
	RsStatusType IPUIstatus;
	RsStatusType RFPIstatus;
	RsStatusType SetRegModeStatus;
	RsStatusType Deregister;
	RsStatusType RSSIstatus;
} PIStatusInfo_t;


// MMI_DATA_TYPE_FWS
typedef enum
{
	MDT_FWS_GET_VERSION_REQ,
	MDT_FWS_GET_VERSION_CFM,
	MDT_FWS_START_TRANSFER_REQ,
	MDT_FWS_START_TRANSFER_CFM,
	MDT_FWS_ABORT_TRANSFER_REQ,
	MDT_FWS_ABORT_TRANSFER_IND, //5
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
PACKED_STRUCT MmiUleData_MmiDataTypeFws;
typedef struct
{
	MdtFwsAction	Action;
	rsuint32		Offset;
	rsuint8         DummyData[11];
}
PACKED_STRUCT MmiUleData_MmiDataTypeFwsOffs;



#define ENUM_DECLARE(member, ...)										member,


typedef enum FwsState
{
	ENUM_DECLARE(FWSS_NEW)
	ENUM_DECLARE(FWSS_VER_REQUESTED)
	ENUM_DECLARE(FWSS_VER_HAVE_UPDATE)
	ENUM_DECLARE(FWSS_XFER_REQUESTED)
	ENUM_DECLARE(FWSS_XFER_STARTED)
	ENUM_DECLARE(FWSS_XFER_COMPLETED)
	ENUM_DECLARE(FWSS_DONE_REBOOTED)
	ENUM_DECLARE(FWSS_DONE_VER_REQUESTED)
	ENUM_DECLARE(FWSS_DONE_VER_UP_TO_DATE)
	ENUM_DECLARE(FWSS_DONE_VER_STILL_DIFFERENT)
	ENUM_DECLARE(FWSS_ABORT_PENDING)
	ENUM_DECLARE(FWSS_ABORT_SENT)
	ENUM_DECLARE(FWSS_DISABLED)


	#undef ENUM_DECLARE
}
FwsState;



typedef struct FwsContextType
{
	//HLST_NEXT_PREV_DECL(struct FwsContextType);

	rsuint16 Pp;                     /*!< Device number. 0 = FP  (1..n=PP's) */
	FwsState State;

	rsuint8 SensorType;

	// current
	rsuint16		StackVersion;
	rsuint16		ColaRev;
	rsuint16		ColaBuildNo;
	rsuint8			ColaLinkDate[5];

	rsuint32 FileSize;
	char* FileData; // needs to be free'd

	rsuint32 BytesSent;
	rsuint32 BytesAcked;
	rsuint32 LastBlockLen;
	rsuint32 TotalBytes;
	unsigned long IncomingDTR;
	unsigned long IncomingDATA;

	time_t LastActivity;
	time_t LastAlive;
	rsuint32 LivenessTimer;
}
FwsContextType;


//RSASSERTSTATIC(sizeof(MmiUleData_MmiDataTypeFws) == 16);
#define COLOR_OFF       "\e[00m"
#define COLOR_RESET     "\e[0;31m"
#define COLOR_ERROR     "\e[1;31m"
#define COLOR_WARNING   "\e[0;31m"
#define COLOR_DEBUG     "\e[0;32m"
#define COLOR_PI     	"\e[0;33m"

typedef struct s_TxBuff {
	TxBufStatus_e TxPacketStatus; // State for the Tx packet. One Tx packet at a time is allowed
	rsuint32 TxkeepAlive; // Live counter to measure when to Abort the send of the Tx packet
	rsuint32 TxtimeoutStatusValue; // Timeout value to Abort the send of Tx packet. This happens when TxkeepAlive=TxtimeoutStatusValue
	rsuint16 TxShadowLen;
	rsuint8  TxShadowPaging;
	rsuint8  *TxShadowData;
} TxBuff_t;

typedef struct s_RxBuff {
	DataPacket_t LatestEventData[MAX_DATA_TYPES_CNT]; // Structure holding latest data for a specific event
	DataPacket_t RxDataBuff[RX_BUFF_SIZE]; // Refer to comment art the beginning
	rsuint32 RxBufWritePos; //Variable to implement RxDataBuff as circular buffer. It will reset to 0 if it becomes RX_BUFF_SIZE
	rsuint32 RcvPckID; // Counter for unique ID of each received packet
} RxBuff_t;

typedef struct s_PPstate {
	PpState_e State; // The state of the ULE sensor
	rsuint32 keepAlive; // Live counter to measure when a sensor is considered OFFLINE
	rsuint32 timeoutStatusValue; // Timeout value to consider a sensor OFFLINE. This happens when keepAlive=timeoutStatusValue
#ifdef	POWERPLUG_CYCLE_TEST
	rsuint32 timeoutPowerCycle; // Timeout value to power cycle the actuator (Power Plug, in power cycle test mode)
	rsuint32 amp; // Current value read in last power cycle
	rsuint32 cycle_cnt; // Counts power cycles
#endif
} PPstate_t;

/*
 * RxDataBuff[RX_BUFF_SIZE] is local storage of received packets.
 * User can connect any time through http and request sensor data received from sensors
 * in the past, up to RX_BUFF_SIZE. Each received packet is assigned an incremental pack ID.
 * A read request with packID=X will return all packets received after X. Therefore a read
 * with PackID=0 will return all the packets in the RxBuff. This mechanism allows multiple users
 * (consumers) to asyncronsly read values from a single sensor (producer). Each consumer can read
 * in different intervals the same data assuring that not a single read packet is missed.
 */

typedef struct {
	PPstate_t State;
	MmiUleSensHdr_t SensorType; // Sensor type as defined in DatapacketPayload
	rsuint8 IPUI[5]; // Unique sensor ID value
	rsuint32 userAttrib[MAXUSERATTRIB]; //Property values specified in user application
	RxBuff_t RxBuff;
	TxBuff_t TxBuff;
	FwsContextType FWS;
	rsuint8 RSSI;
} PpItem_t;



extern rsuint8 DBG_ULE_PI; // Enable Debug messages from porting interface
extern rsuint8 DBG_ULE_API; // Enable Debug messages from API
extern rsuint8 DBG_ULE_MUTEX; // Enable Debug messages from semaphore handling


#ifdef PC_BUILD

#define PRINT_MESSAGE(args...) 	fprintf(stdout,args);
#define ULE_ERR_MSG(args...) 	fprintf(stdout,"****************** ERROR START ******************\n");fprintf(stdout,args);fprintf(stdout,"****************** ERROR END ******************\n")
#define ULE_PI_MSG(args...) 	if(DBG_ULE_PI){fprintf(stdout,args);}
#define ULE_MUTEX_MSG(args...) 	if(DBG_ULE_MUTEX){fprintf(stdout,args);}
#define ULE_API_ENTRY 			if(DBG_ULE_API){fprintf(stdout,"ULE API: Entering function %s\n", __FUNCTION__);}
#define ULE_API_MSG(args...) 	if(DBG_ULE_API){fprintf(stdout,args);}

#else

#define PRINT_MESSAGE(args...) 	printf(COLOR_OFF args );syslog(LOG_INFO, args);
#define ULE_ERR_MSG(args...) 	syslog(LOG_INFO, args);printf(COLOR_ERROR args);
#define ULE_PI_MSG(args...) 	if(DBG_ULE_PI){printf(COLOR_PI args );syslog(LOG_INFO, args);}
#define ULE_MUTEX_MSG(args...) 	if(DBG_ULE_MUTEX){printf(args);syslog(LOG_INFO, args);}
#define ULE_API_ENTRY 			if(DBG_ULE_API){printf("ULE API: Entering function %s\n", __FUNCTION__);}
#define ULE_API_MSG(args...) 	if(DBG_ULE_API){printf(args);syslog(LOG_INFO, args);}

#endif
/******************************************************************************
 *           ULE API TO PORTING INTERFACE  (dect_driver)                      *
 ******************************************************************************/

// These functions are used in dect driver when CVM sends messages to 452.
int  ULE_InitUleHtmlHandler(int port, char *www_path);
void ULE_PP_add(rsuint8 portId);
void ULE_Set_SysInit(UleInitStatus_e SysInit);
void ULE_Fp_Reset(void);
void ULE_Receive_Data(rsuint8 portId, DataPacket_t *dataPacketPtr);
void ULE_RTS_Rcv(rsuint8 portId);
void ULE_Data_reject(rsuint8 portId, RsStatusType Status);
void ULE_Enable_AutoRsxTracing(void);
//void ULE_EE();
void ULE_Get_Ac_Code_Write(RsStatusType st, rsuint8 Ac_1, rsuint8 Ac_2, rsuint8 Ac_3, rsuint8 Ac_4);
void ULE_Set_Ac_Code_Write(RsStatusType st);
void ULE_Get_Registration_Count_Cfm(RsStatusType Status, rsuint8 Offst, rsuint8 len, rsuint8 DevBitArr[]);
void ULE_TxAbort_Cfm(RsStatusType Status);
void ULE_GetIPUI_Cfm(RsStatusType Status, rsuint8 portId, rsuint8 IPUIarr[]);
void ULE_GetRFPI_Cfm(RsStatusType Status, rsuint8 RFPIarr[]);
void ApiGetPpRssiCfm(rsuint8 portId, rsuint8 rssi);
void ULE_SetRegMode_Cfm(RsStatusType Status);
void ULE_Deregister_Cfm(RsStatusType Status, rsuint8 ID);
void ULE_PI_DectMode(rsuint8 status,rsuint8 DectMode);
void ULE_DefaultDectHandler(unsigned char *MailPtr);
#endif //__ULEDECTAPI_H__
