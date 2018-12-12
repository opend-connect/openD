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
/*========================== Include files ==================================*/

#ifndef __ULERESOURCEMANAGER_H__
#define __ULERESOURCEMANAGER_H__


pthread_t TimerThreadId; // timer thread handle
//pthread_t DectThreadId; // Dect thread handle
pthread_t HandleRcvPckThreadId; // event thread handle
volatile int ULE_SystemIsRunning; // Variable to state if ULE is running or not - trigger exit message for threads

/* Resource Manager variables.
 * User does not have direct access to those variables.
 * They are semaphore protected */

PpItem_t PP_Array[PP_COUNT_MAX]; // This were the status of ALL PP is held
SysInfo_t sysInfoDb; // System config parameters
PIStatusInfo_t PiStatus; // Status info received from sect PI
UleInitStatus_e ULESysInit = ULE_Init_Fail; // System init state
rsbool ULE_Init_Done = 0; // Global variable to make sure ULE is initialized properly. It is checked in every PI
rsuint32 pp_timeout_default = 3660; // default node timeout = 1 hour. (set 0 to disable)
rsuint32 tx_timeout_default = 0; // Default to 0 (timeout is disabled)
#ifdef POWERPLUG_CYCLE_TEST
rsuint32 timeoutPowerCycle_default=0;
#endif
extern char EMULATE_SRV_ADDRESS[64];
char EMULATE_SRV_ADDRESS[64];

extern char VERSION[50];
char VERSION[50];

rsuint8 DBG_ULE_PI;
rsuint8 DBG_ULE_API;
rsuint8 DBG_ULE_MUTEX;
extern rsuint8 DECT_BRIDGE_MODE;
extern rsuint8 DECT_UPGRADE;
extern rsuint8 DECT_NVSDEFAULT;
extern rsuint8 DECT_DECTMODE_US;
extern rsuint8 DECT_DECTMODE_EU;
extern rsuint8 DECT_DECTMODE_JP;

#define API_TASK 0x01

#define HANDLED 1
#define UNHANDLED 0

#define FFCF_CHECK		0
#define FFCF_LOAD		1

#define FWS_MAX_BUF_SIZE			500
#define FWS_LIVENESS_TIMEOUT_SECS	30

#define TPS_NOW			ULE_Get_Sys_Time()
#define TPS_GE(t, v)	((TPS_NOW - t) >= v)
// rate-limiting check: returns true at most 1x per v secs
#define TPS_RATE(t, v)	( (TPS_NOW - t) >= v ? ((t = TPS_NOW)) : FALSE )

#define STRINGIFY(x)     #x
#define TOSTRING(x)      STRINGIFY(x)
#define ENUM_DECLARE(member, ...)										STRINGIFY(member),

const char* FwsStateNames[] =
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
};

typedef struct s_RcvPckt { // Structure to hold received packets not procceesed yet
	DataPacket_t *DatPckt;
	rsuint8 portID;
	rsbool IsProccesed;
} RcvPckt_t;

#define RCVPCKTSIZE 50 // This size size allows multiple packets to received at the same time while processed at a later stage
rsuint8 SPI_retries = 3; // NUmber of times code will try to reset SPI bus
RcvPckt_t RcvPckt[RCVPCKTSIZE]; // Array to hold received packets not procceesed yet
rsuint8 WriteLoc = 0; // Write location in RcvPckt array
// Array of function pointers used to store event callback functions
void (*ULE_Event_CallBack_Arr[MAX_SENSOR_TYPES_CNT][MAX_DATA_TYPES_CNT])(rsuint8 portid, DataPacket_t *dataPacketPtr);
void (*ULE_Pck_Process_CallBack)(rsuint8 portid, DataPacket_t *dataPacketPtr);

pthread_mutex_t semULEData; // mutex semaphore to protect ULE data


#define MUTEXOBTAIN_semULEData ULE_MUTEX_MSG("%s: semULEData lock req \n", __FUNCTION__); pthread_mutex_lock( &semULEData ); ULE_MUTEX_MSG("%s: semULEData lock ack \n", __FUNCTION__);
#define MUTEXRELEASE_semULEData pthread_mutex_unlock( &semULEData ); ULE_MUTEX_MSG("%s: semULEData lock rel \n", __FUNCTION__);

pthread_mutex_t semDect_RcvPckt; // mutex semaphore to handshake with Receive Packet API
#define CLEAREVENT_RCVPCKT pthread_mutex_unlock( &semDect_RcvPckt ); pthread_mutex_lock( &semDect_RcvPckt ); ULE_MUTEX_MSG("%s: Clear RcvPckt Event \n", __FUNCTION__);
#define WAITEVENT_RCVPCKT  ULE_MUTEX_MSG("%s: Wait RcvPckt event \n", __FUNCTION__); pthread_mutex_lock( &semDect_RcvPckt );
#define RAISEEVENT_RCVPCKT ULE_MUTEX_MSG("%s: Raise RcvPckt event \n", __FUNCTION__); pthread_mutex_unlock( &semDect_RcvPckt );

pthread_mutex_t semDect_SetAC; // mutex semaphore to handshake with Set Access Code API
#define CLEAREVENT_SETAC pthread_mutex_unlock( &semDect_SetAC ); pthread_mutex_lock( &semDect_SetAC ); ULE_MUTEX_MSG("%s: Clear SetAC Event \n", __FUNCTION__);
#define WAITEVENT_SETAC  ULE_MUTEX_MSG("%s: Wait Set AC event \n", __FUNCTION__);pthread_mutex_lock( &semDect_SetAC );
#define RAISEEVENT_SETAC ULE_MUTEX_MSG("%s: Raise Set AC event \n", __FUNCTION__); pthread_mutex_unlock( &semDect_SetAC );

pthread_mutex_t semDect_GetAC; // mutex semaphore to handshake with Get Access Code API
#define CLEAREVENT_GETAC pthread_mutex_unlock( &semDect_GetAC ); pthread_mutex_lock( &semDect_GetAC ); ULE_MUTEX_MSG("%s: Clear GetAC Event \n", __FUNCTION__);
#define WAITEVENT_GETAC  ULE_MUTEX_MSG("%s: Wait Get AC event \n", __FUNCTION__);pthread_mutex_lock( &semDect_GetAC );
#define RAISEEVENT_GETAC ULE_MUTEX_MSG("%s: Raise Get AC event \n", __FUNCTION__); pthread_mutex_unlock( &semDect_GetAC );

pthread_mutex_t semDect_SysInit; // mutex semaphore to handshake with SysInit Code API
#define CLEAREVENT_SYSINIT pthread_mutex_unlock( &semDect_SysInit ); pthread_mutex_lock( &semDect_SysInit ); ULE_MUTEX_MSG("%s: Clear SysInit Event \n", __FUNCTION__);
#define WAITEVENT_SYSINIT  ULE_MUTEX_MSG("%s: Wait SysInit event \n", __FUNCTION__);pthread_mutex_lock( &semDect_SysInit );
#define RAISEEVENT_SYSINIT ULE_MUTEX_MSG("%s: Raise SysInit event \n", __FUNCTION__); pthread_mutex_unlock( &semDect_SysInit );

pthread_mutex_t semDect_GetRegCount; // mutex semaphore to handshake with GetRegCount Code API
#define CLEAREVENT_REGCOUNT pthread_mutex_unlock( &semDect_GetRegCount ); pthread_mutex_lock( &semDect_GetRegCount ); ULE_MUTEX_MSG("%s: Clear GetRegCount Event \n", __FUNCTION__);
#define WAITEVENT_REGCOUNT  ULE_MUTEX_MSG("%s: Wait GetRegCount event \n", __FUNCTION__);pthread_mutex_lock( &semDect_GetRegCount );
#define RAISEEVENT_REGCOUNT ULE_MUTEX_MSG("%s: Raise GetRegCount event \n", __FUNCTION__); pthread_mutex_unlock( &semDect_GetRegCount );

pthread_mutex_t semDect_Abort; // mutex semaphore to handshake with TxABort Code API
#define CLEAREVENT_TXABORT pthread_mutex_unlock( &semDect_Abort ); pthread_mutex_lock( &semDect_Abort ); ULE_MUTEX_MSG("%s: Clear TxABort Event \n", __FUNCTION__);
#define WAITEVENT_TXABORT   ULE_MUTEX_MSG("%s: Wait TxABort event \n", __FUNCTION__);pthread_mutex_lock( &semDect_Abort );
#define RAISEEVENT_TXABORT ULE_MUTEX_MSG("%s: Raise TxABort event \n", __FUNCTION__); pthread_mutex_unlock( &semDect_Abort );

pthread_mutex_t semDect_IPUI; // mutex semaphore to handshake with IPUI Code API
#define CLEAREVENT_IPUI pthread_mutex_unlock( &semDect_IPUI ); pthread_mutex_lock( &semDect_IPUI ); ULE_MUTEX_MSG("%s: Clear IPUI Event \n", __FUNCTION__);
#define WAITEVENT_IPUI  ULE_MUTEX_MSG("%s: Wait IPUI event \n", __FUNCTION__);pthread_mutex_lock( &semDect_IPUI );
#define RAISEEVENT_IPUI ULE_MUTEX_MSG("%s: Raise IPUI event \n", __FUNCTION__); pthread_mutex_unlock( &semDect_IPUI );

pthread_mutex_t semDect_RFPI; // mutex semaphore to handshake with RFPI Code API
#define CLEAREVENT_RFPI pthread_mutex_unlock( &semDect_RFPI ); pthread_mutex_lock( &semDect_RFPI ); ULE_MUTEX_MSG("%s: Clear RFPI Event \n", __FUNCTION__);
#define WAITEVENT_RFPI  ULE_MUTEX_MSG("%s: Wait RFPI event \n", __FUNCTION__);pthread_mutex_lock( &semDect_RFPI );
#define RAISEEVENT_RFPI ULE_MUTEX_MSG("%s: Raise RFPI event \n", __FUNCTION__); pthread_mutex_unlock( &semDect_RFPI );

pthread_mutex_t semDect_SetRegMode; // mutex semaphore to handshake with SetRegMode Code API
#define CLEAREVENT_SETREGMODE pthread_mutex_unlock( &semDect_SetRegMode ); pthread_mutex_lock( &semDect_SetRegMode ); ULE_MUTEX_MSG("%s: Clear SetRegMode Event \n", __FUNCTION__);
#define WAITEVENT_SETREGMODE   ULE_MUTEX_MSG("%s: Wait SetRegMode event \n", __FUNCTION__);pthread_mutex_lock( &semDect_SetRegMode );
#define RAISEEVENT_SETREGMODE ULE_MUTEX_MSG("%s: Raise SetRegMode event \n", __FUNCTION__); pthread_mutex_unlock( &semDect_SetRegMode );

pthread_mutex_t semDect_DeReg; // mutex semaphore to handshake with DeRegister Code API
#define CLEAREVENT_DEREGMODE pthread_mutex_unlock( &semDect_DeReg ); pthread_mutex_lock( &semDect_DeReg ); ULE_MUTEX_MSG("%s: Clear DeRegister Event \n", __FUNCTION__);
#define WAITEVENT_DEREGMODE  ULE_MUTEX_MSG("%s: Wait DeRegister event \n", __FUNCTION__);pthread_mutex_lock( &semDect_DeReg );
#define RAISEEVENT_DEREGMODE ULE_MUTEX_MSG("%s: Raise DeRegister event \n", __FUNCTION__); pthread_mutex_unlock( &semDect_DeReg );

const rsuint8 RfLMX4x68DataEU_DECT[] = {0x0C,0xB0,0x00,0x68,0x03,0x88};
const rsuint8 bFreqBandOffsetEU_DECT[] = {0x00};
const rsuint8 UsedRfCarriersEU_DECT[] = {0x03, 0xff};
const rsuint8 bRssiScanTypeEU_DECT[] = {0x00};
const rsuint8 ImageCfgEU_DECT[] = {0x80};

const rsuint8 RfLMX4x68DataUS_DECT[] = {0x1a,0x80,0x00,0x56,0x03,0x98};
const rsuint8 bFreqBandOffsetUS_DECT[] = {0xee};
const rsuint8 UsedRfCarriersUS_DECT[] = {0x03, 0xe0};
const rsuint8 bRssiScanTypeUS_DECT[] = {0x01};
const rsuint8 ImageCfgUS_DECT[] = {0x80};

const rsuint8 RfLMX4x68DataJAPAN_DECT[] = {0x1a,0x80,0x00,0x56,0x03,0x98};
const rsuint8 bFreqBandOffsetJAPAN_DECT[] = {0xfd};
const rsuint8 UsedRfCarriersJAPAN_DECT[] = {0x03, 0xe0};
const rsuint8 bRssiScanTypeJAPAN_DECT[] = {0x01};
const rsuint8 ImageCfgJAPAN_DECT[] = {0x80};


/* Standard checks in the code */
#define ASSERT_ULE_INIT_SUCCESS do{if(ULE_Init_Done==0){return ULE_NotInitialized;}}while(0)
#define ASSERT_ULE_PORTID_INRANGE do{if(portId >= PP_COUNT_MAX){return ULE_PP_OutOfRangeError;}}while(0)
#define ASSERT_PI_PORTID_INRANGE do{if(portId >= PP_COUNT_MAX){return;}}while(0)

#ifdef LEGACY_CODE_TBR
static void get_app_mode();
static void execute_app_mode();
#endif
static UleErr_e ULE_DeRegister_Internal(rsuint8 portId);
void ULE_InitRcvRcktThread(void);
void *ULE_HandleRcvRcktThread(void*);
void ULE_EmptyEventHandler(rsuint8 portid, DataPacket_t *dataPacketPtr);
void ULE_InitTimer(void);
void *ULE_TimerThread(void*);
void InitTestBus();
void HandleResetIndULE(void *MailPtr);
static void fwsStartTransfer(rsuint8 portid);
int fwsApiFpMmHandsetPresentInd(const ApiFpMmHandsetPresentIndType* m);
int fwsFindUpgradableFirmware(rsuint8 portid,rsuint8 oper);
static int fwsSendNextPacket(rsuint8 portid, char retry);
static int fwsApiFpUleDtrInd(const rsuint8 portid);
static int fwsApiFpUleDataRejectInd(rsuint8 portid, RsStatusType Status);
static int fwsSendAbort(rsuint8 portid);
static int fwsSendUleGetVersion(rsuint8 portid);
static void fwsLivenessStop(rsuint8 portid);
static void fwsLivenessTickle(rsuint8 portid);

#endif //__ULERESOURCEMANAGER_H__
