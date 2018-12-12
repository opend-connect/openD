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
#include <dirent.h>
#include <stdint.h>
#include <pthread.h>


#include <Phoenix/Api/Api.h>
#include <Phoenix/Api/FpUle/ApiFpUle.h>
#include <Phoenix/Api/HAL/ApiHAL.h>
#include <Phoenix/Api/HAL/ApiHalMps.h>
#include <Phoenix/Api/FpCc/ApiFpCcMps.h>
#include <Phoenix/Api/FpNoEmission/ApiFpNoEmissionMps.h>
#include <Phoenix/FpProductTest/ApiFpProdTestMps.h>

#include <include/uleDectAPI.h>
#include <include/uleAppAPI.h>
#include <dect_driver.h>
#include <uleResourceManager.h>
//#include <legacy_apps/ulehtmlHandler.h>

#ifdef POWERPLUG_CYCLE_TEST
//#include <legacy_apps/sensor_handlers.h>
#endif


#ifdef WIN_BUILD
#include "bus232.h"
#include "RepsInterface.h"
#define REPS_SERVER_NAME "DialogUleDemoFPServer"
#else
#include "hdlc.h"
#endif

#include "opend_ll_serial.h"

#include "dect_driver.h"

#ifdef HANFUN
// #include <hanfun_apps/hf_web_http_interface.h>
#endif

#if defined(ENABLE_AUTO_RSX_TRACING)
/* RTX_EAI_TASK, API_TASK, COLA_TASK enabled */
rsuint8 trace_cmd[] = {0x81, 0xDC, 0x42, 0x13, 0x13, 0x00, 0x13, 0x00, 0x00,
					   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x58,
					   0x3C, 0xC8};
#endif

#undef CONFIG_SOUND

#define DECT_NATALIE
#undef CONFIG_CVM480_DECT_SUPPORT
#ifdef PC_BUILD
#undef CONFIG_SOUND
#endif

// for sys_sleep functions
#if defined _WIN32 || defined _WIN64
#include <windows.h>
#include <malloc.h>	// alloca definition
#else
#include <unistd.h>
#include <alloca.h>
#endif


unsigned char  *m;

cJSON* (*ULE_UserWebReqHandler_CallBack)(char *UserJSONstring);

int fwsApiFpUleDataInd(rsuint8 portid,const MmiUlePdu_common_t* pdu);
static int fwsApiFpUleDataInd_MdtFwsGetVersionCfm(rsuint8 portid, MmiUlePdu_common_t* pdu);
char fws_cola_name[256];
char fws_stack_name[256];
char fws_file_name[256];

const char* patternCola = "Cola_r%4u_b%4u.fws";
const char* patternStack = "Stack_v%4X.fws";
rsuint8 FP_TXPASS[PP_COUNT_MAX];
DataPacket_t SwitchData;

rsbool pendSwVerReq[PP_COUNT_MAX];
rsbool FWS_Active[PP_COUNT_MAX];
rsbool fws_file_manual_set[PP_COUNT_MAX];

char* FWS_FileData = NULL;
rsuint32 FWS_FileSize = 0;
rsuint8 FWS_FileData_Count = 0;
#ifdef IPBS_452_BUILD
unsigned char mailbuf[MAX_MSG_LEN];
#endif
rsuint8 deregisterAllUpdateTimer = 0;

static rsbool UseRepsConnection = 0;	// Set this in UleInit to use REPS instead of direct serial connection

int initLedPorts(void){return 0;}
int switchLed(ledType_t ledNumber, rsbool on){(void)(ledNumber); (void)(on); return 0;}
int toggleLed(ledType_t ledNumber, int numberOfTimes){(void)(ledNumber); (void)(numberOfTimes); return 0;}


/* Helper Functions */

unsigned sys_sleep (unsigned seconds)
{
#if defined _WIN32 || defined _WIN64
	Sleep(1000 * seconds);
	return 0;
#else
	return sleep(seconds);
#endif
}


int sys_usleep(unsigned useconds)
{
#if defined _WIN32 || defined _WIN64
	Sleep(useconds);
	return 0;
#else
	return usleep(useconds);
#endif

}


unsigned char *BUSM_AllocateMail(uint8 uProgramId, uint8 uTaskId, uint16 u16Size)
{
	uint8 *bConPtr;
	bConPtr = (uint8 *)malloc(u16Size+4);//1: uProgramId, 1: uTaskId, 2: u16Size
	if(!bConPtr){
		printf("Inside %s MALLOC FAILED  !!!!!!!!!!!!!!!!! \n\n\n\n", __FUNCTION__);
		while(1);
	}
	*bConPtr = uProgramId;
	*(bConPtr+1) = uTaskId;
	*(uint16*)(bConPtr+2) = u16Size;

	return(bConPtr+4);
}

void BUSM_DeliverMail(uint8 *Mail)
{

	uint8 *bConPtr=Mail-4;
	uint8  ConTask = *(bConPtr+1);
	uint16 ConLength = *(uint16*)(bConPtr+2);

	//int i;
	//printf("\n BUSM_DeliverMail: ");
	//for(i=0; i<ConLength; i++) printf("%X ", Mail[i]);
	//printf("\n ");

#ifdef WIN_BUILD
	if (UseRepsConnection)
		RepsSendPacket(ConTask, Mail, ConLength);
	else
		bus232_SendPacketToUnit(ConTask, ConLength, Mail);
#else
	// hdlc_SendPacketToUnit(ConTask, ConLength, Mail);

	hdlc_infoFrameCreate( ConTask, (uint8_t *) Mail, ConLength );

#endif
	free(bConPtr);
}

rsuint8 PcmEnable = 0x1, IsMaster = 0x1, DoClockSync = 0x0, PcmFscFreq = 0x1, PcmFscLength = 0x0, PcmFscStartAligned = 0x0;
rsuint8 PcmClk = 0x0, PcmClkOnRising = 0x0, PcmClksPerBit = 0x1, PcmFscInvert = 0x0, PcmCh0Delay = 0x0, PcmDoutIsOpenDrain = 0x0, PcmIsOpenDrain = 0x0;


void ULE_Configure_Hdlc_Port(const char* portname) {
#ifdef WIN_BUILD
	(void) portname;
#else
	// hdlc_SetPortname(portname);
#endif
}

void _allocateMemory( uint8_t **data, uint16_t length ) {

  *data = (uint8_t *) malloc( length );
}

void _freeMemory( uint8_t *data ) {
  free( data );
}

void hdlc_parsedPacket( uint8_t *data, uint16_t length ) {

	ULE_mail_switch( (unsigned short) length, (unsigned char*) &data[2] );

	return;
}


UleErr_e ULE_Init(rsuint32 AccessCodeDefault, rsuint32 SensorTimeoutDefault, rsuint32 TxTimeoutDefault,
		char *WebSiteLocation, rsuint32 HTTPport, char *BoardIPaddr,rsuint8 DbgPI,rsuint8 DbgAPI,rsuint8 DbgMUTEX, rsint8 Comport) {

	ULE_API_ENTRY

	(void) BoardIPaddr; // unused
	rsuint8 i, RegDev, MaxDevices;

	PRINT_MESSAGE("ULE INIT \n");
	if (ULE_Init_Done == 1) {
		return ULE_AlreadyInitialized;
	}

	// use REPS connection to communicate with board
	if ( Comport == ULE_INIT_CONNECT_WITH_REPS )
		UseRepsConnection = 1;

#if defined(LEGACY_CODE_TBR) && !defined(PC_BUILD)
	get_app_mode();
#endif

	initLedPorts();
	switchLed(DECT_LED3, 1);

	DBG_ULE_PI = DbgPI;
	DBG_ULE_API = DbgAPI;
	DBG_ULE_MUTEX = DbgMUTEX;

	tx_timeout_default = TxTimeoutDefault;
	pp_timeout_default = SensorTimeoutDefault;
	sysInfoDb.Ac[0] = (rsuint8) (AccessCodeDefault);
	sysInfoDb.Ac[1] = (rsuint8) ((AccessCodeDefault) >> 8);
	sysInfoDb.Ac[2] = (rsuint8) ((AccessCodeDefault  >> 16));
	sysInfoDb.Ac[3] = (rsuint8) ((AccessCodeDefault) >> 24);
	sysInfoDb.AcChanged = 1;

#ifndef PC_BUILD
	signal(SIGINT, ULE_Exit); //install signal handlers for safe exit
	signal(SIGKILL, ULE_Exit);
	signal(SIGTERM, ULE_Exit);
	signal(SIGABRT, ULE_Exit);
#endif

	pthread_mutex_init(&semULEData, 0);
	pthread_mutex_init(&semDect_RcvPckt, 0);
	pthread_mutex_init(&semDect_SetAC, 0);
	pthread_mutex_init(&semDect_GetAC, 0);
	pthread_mutex_init(&semDect_SysInit, 0);
	pthread_mutex_init(&semDect_GetRegCount, 0);
	pthread_mutex_init(&semDect_Abort, 0);
	pthread_mutex_init(&semDect_IPUI, 0);
	pthread_mutex_init(&semDect_RFPI, 0);
	pthread_mutex_init(&semDect_SetRegMode, 0);
	pthread_mutex_init(&semDect_DeReg, 0);

#ifndef DECT_FUNCTIONS
	if (DECT_BRIDGE_MODE==0){
		//Initialize HTML Handler
		//ULE_InitUleHtmlHandler(HTTPport, WebSiteLocation);
	}
#endif

	// ******************  Init dect communication

	Register_AllocateMailFunction(&BUSM_AllocateMail);
	Register_DeliverMailFunction(&BUSM_DeliverMail);

#ifdef WIN_BUILD
	if (UseRepsConnection) {
		if (RepsMainTaskInit(REPS_SERVER_NAME)) {
			printf("FAILED !!! - could not initialize REPS connection.\n");
			return 1;
		}
		Register_MainTaskMailSwitch(&ULE_mail_switch);

	} else {
		// Use serial connection
		InitTestBus();
		printf("InitRs232: Comport=%d, Bps=115200\n", Comport);
		if(InitRs232(Comport, 115200)) {
			printf("FAILED !!! - could not open comport.\n");
			return 1;
		}
	}
#else
	if ( hdlc_init( hdlc_parsedPacket, _allocateMemory, _freeMemory, openD_ll_serial_send) != 0) {
		printf("FAILED !!! - could not open comport.\n");
		return 1;
	}
#endif

	HandleResetIndULE(0);

#if defined(LEGACY_CODE_TBR)
	execute_app_mode();
#endif

	//SendApiFpInitPcmReq( API_TASK, PcmEnable, IsMaster,DoClockSync, PcmFscFreq, PcmFscLength, PcmFscStartAligned ,PcmClk, PcmClkOnRising,
	//                     PcmClksPerBit,  PcmFscInvert, PcmCh0Delay, PcmDoutIsOpenDrain, PcmIsOpenDrain);

	SendApiFpMacNoEmissionModeDisableReq(API_TASK);

	PRINT_MESSAGE("\n Setting Access code \n");
	if (ULE_Set_Access_Code(sysInfoDb.Ac[3], sysInfoDb.Ac[2], sysInfoDb.Ac[1], sysInfoDb.Ac[0]) != ULE_Success) {
		return ULE_InitFail;
	}

		ULESysInit = ULE_Init_Fail;

		CLEAREVENT_SYSINIT;

#ifdef DECT_NATALIE
#if defined(CONFIG_CATIQ_V11_SUPPORT) || defined(CONFIG_CATIQ_V12_SUPPORT)
		SendApiFpUleInitReq(API_TASK, PP_COUNT_MAX);
#else
		SendApiFpUleInitReq(API_TASK, PP_COUNT_MAX, 0x40, 0x1D, 0x40, 0x1D); // For V7 default is encryption disabled
#endif
#else
		SendApiFpUleInitReq(API_TASK, PP_COUNT_MAX, 0x40, 0x1D, 0xF0F1, 0);
		//SendApiFpUleInitReq(API_TASK, PP_COUNT_MAX, 0x40, 0x1D,  0x40, 0x1D); // For V9 default is encryption enabled 0xF0F1
#endif
		PRINT_MESSAGE("\n InitDone !!!!!!!!!!!! \n");
		WAITEVENT_SYSINIT;


		if (ULESysInit != ULE_Init_Success) return ULE_InitFail;

		for (i = 0; i < PP_COUNT_MAX; i++) {
			ULE_PP_add(i);
			PP_Array[i].State.State = S_PP_NOT_REGISTERED;
		}

		if (ULE_Get_Registration_Count(&RegDev,&MaxDevices) != ULE_Success) {
				return ULE_InitFail;
		}

	// Initialize all threads
	ULE_InitTimer();
	ULE_InitRcvRcktThread();

	ULE_Init_Done = 1;

	return ULE_Success;
}

#ifdef CRON_SUPPORT
//Return values
//0: don't do anything, 1: switch ON, -1: switch OFF
static char get_cron_switch_mode(rsuint8 ppId){

	char filename[25];
	char command[30];

	sprintf(filename, "/tmp/switchON_%02d", ppId);
	FILE *fp = fopen(filename,"r");
	if( fp ) {
		fclose(fp);
		sprintf(command, "rm %s", filename);
		//system(command);
		return(1);
	}

	sprintf(filename, "/tmp/switchOFF_%02d", ppId);
	FILE *fp1 = fopen(filename,"r");
	if( fp1 ) {
		fclose(fp1);
		sprintf(command, "rm %s", filename);
		//system(command);
		return(-1);
	}

	return(0);
}
#endif

#ifdef LEGACY_CODE_TBR
static void get_app_mode(){


	#ifdef DECT_FUNCTIONS
		FILE *fp1 = fopen("/tmp/dectupgrade","r");
		if( fp1 ) {
		DECT_UPGRADE = 1; // Override normal ULE init to  upgrade CVM FW
		fclose(fp1);
		}
	#endif
		FILE *fp2 = fopen("/tmp/decteu","r");
		if( fp2 ) {
		DECT_DECTMODE_EU = 1; // Override normal ULE init to set DECT mode to EU
		fclose(fp2);
		}
		FILE *fp3 = fopen("/tmp/dectus","r");
		if( fp3 ) {
		DECT_DECTMODE_US = 1; // Override normal ULE init to set DECT mode to US
		fclose(fp3);
		}
		FILE *fp4 = fopen("/tmp/dectjp","r");
		if( fp4 ) {
		DECT_DECTMODE_JP = 1; // Override normal ULE init to set DECT mode to Japan 5-ch
		fclose(fp4);
		}
		FILE *fp5 = fopen("/tmp/dectnvsdefault","r");
		if( fp5 ) {
		DECT_NVSDEFAULT = 1; // Override normal ULE init to run an nvs default
		fclose(fp5);
		}
}

static void execute_app_mode(){

#ifdef DECT_FUNCTIONS
	if (DECT_UPGRADE){
#ifdef CONFIG_CVM480_DECT_SUPPORT
		ULE_SystemIsRunning =1;
		ULE_UpdateCVMFW();
		while (ULE_SystemIsRunning) {
			sys_sleep(3);
		}
		sys_sleep(10);
		exit(1);
#else
		PRINT_MESSAGE(" \n This is a flat design dect update binary.  \n ");
		PRINT_MESSAGE(" Dect FW upgrade is only applicable to CVM boards. \n ");
		exit(1);
#endif
	}
#endif
	if (DECT_NVSDEFAULT){
		ULE_DectMode(NVS_DEFAULT);
		sys_sleep(5);
		//system("reboot;");
		exit(1);
	}

	if (DECT_DECTMODE_EU){
		ULE_DectMode(DECTMODE_EUROPE);
		sys_sleep(5);
		//system("reboot;");
		exit(1);
	}
	if (DECT_DECTMODE_US){
		ULE_DectMode(DECTMODE_US);
		sys_sleep(5);
		//system("reboot;");
		exit(1);
	}
	if (DECT_DECTMODE_JP){
		ULE_DectMode(DECTMODE_JP_5CH);
		sys_sleep(5);
		//system("reboot;");
		exit(1);
	}

}
#endif // LEGACY_CODE_TBR

#ifdef DECT_FUNCTIONS

void SetFwuMode(rsbool Enable);
void InitFwu();

UleErr_e ULE_UpdateCVMFW() {

	PRINT_MESSAGE ("CVM FW upgrade! \n");

	InitFwu();
	sys_sleep(3);

	SetFwuMode(1);


	return ULE_Success;
}
#endif


UleErr_e ULE_DectMode(rsuint8 DectMode){
	unsigned char param[2];
	if (DectMode == NVS_DEFAULT){
		PRINT_MESSAGE ("Setting NVSDEFAULT 1 ! \n");
		//param[0]=0x01;
		//SendApiProdTestReq(1,0x0102,1,param); // ID
		param[0]=0x92; param[1]=0x94;
		SendApiProdTestReq(1,0x001B,2,param); // ID
		param[0]=0x00; param[1]=0x11;
		SendApiProdTestReq(1,0x0204,2,param); // FREQ
		param[0]=0x00; param[1]=0x08;
		SendApiProdTestReq(1,0x003F,2,param); // BAND
	}

	if (DectMode == DECTMODE_EUROPE){
		PRINT_MESSAGE ("Setting DECT mode to EUROPE \n");
	   param[0]=0x00;
	   SendApiProdTestReq(1,0x0200,1,param); // ID
	}

	if (DectMode == DECTMODE_US){
		PRINT_MESSAGE ("Setting DECT mode to US \n");
		param[0]=0x08;
		SendApiProdTestReq(1,0x0200,1,param); // ID
	}

	if (DectMode == DECTMODE_JP_5CH){
		PRINT_MESSAGE ("Setting DECT mode to JAPAN 5-CH !!\n");
		param[0]=0x0B;
		SendApiProdTestReq(1,0x0200,1,param); // ID

	}

	PRINT_MESSAGE ("Done! \n");

	return ULE_Success;
}

UleErr_e ULE_Get_DectMode(rsuint8 *DectMode){


	if (PiStatus.DectModeStatus) {
		return ULE_DectModereadError;
	}

	*DectMode = PiStatus.DectMode;
	return ULE_Success;
}

void  ULE_PI_DectMode(rsuint8 status,rsuint8 DectMode){

	 PiStatus.DectModeStatus = status;
	 PiStatus.DectMode= DectMode;
}


UleErr_e ULE_Exit() {

	ULE_API_ENTRY
	PRINT_MESSAGE("\n ULE APP exiting \n");
	switchLed(DECT_LED3, 0);
	ULE_SystemIsRunning = 0;

	// Unlock this to release ULE_HandleRcvRcktThread
	pthread_mutex_unlock( &semDect_RcvPckt );
	pthread_mutex_destroy(&semDect_RcvPckt);

	// All others
//	pthread_mutex_unlock(&semULEData);
//	pthread_mutex_unlock(&semDect_SetAC);
//	pthread_mutex_unlock(&semDect_GetAC);
//	pthread_mutex_unlock(&semDect_SysInit);
//	pthread_mutex_unlock(&semDect_GetRegCount);
//	pthread_mutex_unlock(&semDect_Abort);
//	pthread_mutex_unlock(&semDect_IPUI);
//	pthread_mutex_unlock(&semDect_RFPI);
//	pthread_mutex_unlock(&semDect_SetRegMode);
//	pthread_mutex_unlock(&semDect_DeReg);
//
//	pthread_mutex_destroy(&semULEData);
//	pthread_mutex_destroy(&semDect_SetAC);
//	pthread_mutex_destroy(&semDect_GetAC);
//	pthread_mutex_destroy(&semDect_SysInit);
//	pthread_mutex_destroy(&semDect_GetRegCount);
//	pthread_mutex_destroy(&semDect_Abort);
//	pthread_mutex_destroy(&semDect_IPUI);
//	pthread_mutex_destroy(&semDect_RFPI);
//	pthread_mutex_destroy(&semDect_SetRegMode);
//	pthread_mutex_destroy(&semDect_DeReg);

	sys_usleep(10);

	//ULE_StopUleHtmlHandler();
#ifdef WIN_BUILD
	if (UseRepsConnection) {
		RepsMainTaskExit();	// Close REPS
	}
	else {
		CloseRs232(); // Close serial
	}
#endif
#ifndef PC_BUILD
#ifdef CONFIG_CVM480_DECT_SUPPORT
	hdlc_Exit();
#endif
#ifdef CONFIG_SOUND
	//sip_signal_handler(); // Needs to be the last to call in ULE_exit
#else
	exit(0);
#endif
#endif
	return ULE_Success;
}


/*
 *  Send a command to reset to CVM module or reboot the linux baestation
 */
void ULE_Fp_Reset() {
	ULE_API_ENTRY

#if defined(WIN_BUILD)
	PRINT_MESSAGE("\n\n #################################\n # USER SENDING MODULE RESET CMD #\n #################################\n\n");
	SendApiFpResetReq(API_TASK);
#elif defined(IPBS_452_BUILD)
	PRINT_MESSAGE("\n\n ################################\n # USER SENDING BASE REBOOT CMD #\n ################################\n\n");
	system("reboot");
#endif

}


/*
 * 	Enable RsxCustomer tracing by default.
 *	This is a custom RosAllocate/RosDeliver implementation using RepsSendPacketCustom
 *	to be able to set the RsxCustomer ProgramId on the mail (usual ProgramId is the one of our application).
 *	If the UseRepsConnection is disabled the traditional SendApiFpTraceReq api is used.
 */
void ULE_Enable_AutoRsxTracing() {
#if defined(ENABLE_AUTO_RSX_TRACING)

	rsuint16 length = sizeof(trace_cmd) + 2 ; // 2 for Primitive
#ifndef WIN_BUILD
    if (0) {
#else
	if (UseRepsConnection) {

		// Allocate mail
		rsuint8 *bConPtr;
		bConPtr = (rsuint8 *)malloc(length);
		if(!bConPtr){
			printf("Inside %s MALLOC FAILED  !!!!!!!!!!!!!!!!! \n\n\n\n", __FUNCTION__);
			while(1);
		}

		*(rsuint16*)(bConPtr) = RTX_EAP_TRACE_DOWNLOAD_START_REQ; //0xF006
		memcpy ((bConPtr+2), trace_cmd, length);

		// 0x81: RsxCustomer PorgramId
		// 0x00: TaskId of RtxEAI Task
		RepsSendPacketCustom(0x80, 0x00, bConPtr, length);
#endif
	} else {
		// Use classic tracing command
		// Output to be shown by the secondary UART
		SendApiFpTraceReq(API_TASK, length, trace_cmd);
	}
#endif
}


void ULE_PP_add(rsuint8 portId) {

	ULE_API_ENTRY

	if (portId >= PP_COUNT_MAX ) {
		ULE_ERR_MSG("ULE tried to add a PP out of range!\n");
		return;
	}
	memset(&PP_Array[portId],0,sizeof(PpItem_t));
	PP_Array[portId].State.State = S_PP_ULE_OFFLINE;
	PP_Array[portId].State.keepAlive = ULE_Get_Sys_Time();
	PP_Array[portId].State.timeoutStatusValue = pp_timeout_default;
#ifdef	POWERPLUG_CYCLE_TEST
	PP_Array[portId].State.timeoutPowerCycle = 0;
	PP_Array[portId].State.amp = 0;
	PP_Array[portId].State.cycle_cnt = 0;
#endif
	PP_Array[portId].TxBuff.TxkeepAlive = ULE_Get_Sys_Time();
	PP_Array[portId].TxBuff.TxtimeoutStatusValue = tx_timeout_default;

	if (portId < 7) {
		PP_Array[portId].State.State = S_PP_ULE_ONLINE;
		PP_Array[portId].State.timeoutStatusValue = 100000;
		PP_Array[portId].SensorType=0x3;
	}

	return;
}


UleErr_e ULE_Set_Access_Code(rsuint8 Ac_1, rsuint8 Ac_2, rsuint8 Ac_3, rsuint8 Ac_4) {
	ULE_API_ENTRY

	MUTEXOBTAIN_semULEData;

	sysInfoDb.Ac[0] = Ac_1;
	sysInfoDb.Ac[1] = Ac_2;
	sysInfoDb.Ac[2] = Ac_3;
	sysInfoDb.Ac[3] = Ac_4;

	CLEAREVENT_SETAC;

	SendApiFpMmSetAccessCodeReq(API_TASK, sysInfoDb.Ac);

	WAITEVENT_SETAC;

	if (PiStatus.SetAccessCodeStatus) {

		MUTEXRELEASE_semULEData;
		return ULE_PP_SetCodeError;
	}

	sysInfoDb.AcChanged = 1;
	MUTEXRELEASE_semULEData;
	return ULE_Success;

}

UleErr_e ULE_Get_Access_Code_Internal(rsuint8 *Ac_1Ptr, rsuint8 *Ac_2Ptr, rsuint8 *Ac_3Ptr, rsuint8 *Ac_4Ptr, rsbool forceGet) {
	ULE_API_ENTRY

	MUTEXOBTAIN_semULEData;

	if (sysInfoDb.AcChanged || forceGet) {
		CLEAREVENT_GETAC;
		SendApiFpMmGetAccessCodeReq(API_TASK);

		WAITEVENT_GETAC;

		if (PiStatus.GetAccessCodeStatus) {
			MUTEXRELEASE_semULEData;
			return ULE_PP_GetCodeError;
		}

		*Ac_1Ptr = PiStatus.Ac[0];
		*Ac_2Ptr = PiStatus.Ac[1];
		*Ac_3Ptr = PiStatus.Ac[2];
		*Ac_4Ptr = PiStatus.Ac[3];
		sysInfoDb.AcChanged = 0;
	} else {
		*Ac_1Ptr = sysInfoDb.Ac[0];
		*Ac_2Ptr = sysInfoDb.Ac[1];
		*Ac_3Ptr = sysInfoDb.Ac[2];
		*Ac_4Ptr = sysInfoDb.Ac[3];
	}

	sysInfoDb.AcChanged = 0;
	MUTEXRELEASE_semULEData;
	return ULE_Success;
}
UleErr_e ULE_Get_Access_Code(rsuint8 *Ac_1Ptr, rsuint8 *Ac_2Ptr, rsuint8 *Ac_3Ptr, rsuint8 *Ac_4Ptr) {
	return ULE_Get_Access_Code_Internal(Ac_1Ptr, Ac_2Ptr, Ac_3Ptr, Ac_4Ptr, 0);
}
UleErr_e ULE_Get_Access_Code_Force(rsuint8 *Ac_1Ptr, rsuint8 *Ac_2Ptr, rsuint8 *Ac_3Ptr, rsuint8 *Ac_4Ptr) {
	return ULE_Get_Access_Code_Internal(Ac_1Ptr, Ac_2Ptr, Ac_3Ptr, Ac_4Ptr, 1);
}

void ULE_Get_Ac_Code_Write(RsStatusType st, rsuint8 Ac_1, rsuint8 Ac_2, rsuint8 Ac_3, rsuint8 Ac_4) {
	ULE_API_ENTRY

	PiStatus.GetAccessCodeStatus = st;
	PiStatus.Ac[0] = Ac_1;
	PiStatus.Ac[1] = Ac_2;
	PiStatus.Ac[2] = Ac_3;
	PiStatus.Ac[3] = Ac_4;

	RAISEEVENT_GETAC;

}

void ULE_Set_Ac_Code_Write(RsStatusType st) {
	ULE_API_ENTRY
	PiStatus.SetAccessCodeStatus = st;
	RAISEEVENT_SETAC;
}

UleErr_e ULE_Get_Registration_Count(rsuint8 *Registered,rsuint8 *MaxSupported) {
	ULE_API_ENTRY
	MUTEXOBTAIN_semULEData;

	CLEAREVENT_REGCOUNT;
	//SendApiFpMmGetRegistrationCountReq(API_TASK);
	SendApiFpUleGetRegistrationCountReq(API_TASK);

	WAITEVENT_REGCOUNT;

	if (PiStatus.RegCountStatus) {
		MUTEXRELEASE_semULEData;
		return ULE_Get_Registration_CountError;
	}
	*MaxSupported = PP_COUNT_MAX;
	*Registered = PiStatus.DevRegCnt;
	MUTEXRELEASE_semULEData;
	return ULE_Success;
}

void ULE_Get_Registration_Count_Cfm(RsStatusType Status, rsuint8 Offst, rsuint8 len, rsuint8 DevBitArr[]) {

	ULE_API_ENTRY

	rsuint8 i, j, cnt;
	rsuint8 SM;

	PiStatus.RegCountStatus = Status;
	PiStatus.DevRegCnt=0;

	if (Status != RSS_SUCCESS) {
		RAISEEVENT_REGCOUNT;
		return;
	}

	cnt = 1;

	for (i = 0; i < len; i++) {
		SM = 128;
		for (j = 0; j < 8; j++) {
			if ((DevBitArr[i] & SM) && (cnt > Offst)) {
				ULE_PP_add( cnt);
				PiStatus.DevRegCnt++;
			}
			SM = SM / 2;
			cnt++;
		}
	}

	RAISEEVENT_REGCOUNT;

}

static const char* fwsStateName(enum FwsState st)
{
	return FwsStateNames[st];
}

static int fwsStateTo(rsuint8 portid, enum FwsState state)
{

	// check if we need to cleanup for the new state
	char cleanup = FALSE;
	switch (state)
	{
		case FWSS_DONE_VER_UP_TO_DATE:
		case FWSS_DONE_VER_STILL_DIFFERENT:
		case FWSS_DISABLED:
			FWS_Active[portid] = 0; // FWS procedure completed
			break;
		case FWSS_ABORT_SENT:
		case FWSS_XFER_COMPLETED:
			cleanup = TRUE;
			break;
		default:
			break;
	}

	if (PP_Array[portid].FWS.State != state)
	{

		PRINT_MESSAGE("\r\n (PortID %02i changed FWS state from %s to %s \r\n",portid, fwsStateName(PP_Array[portid].FWS.State), fwsStateName(state));

		PP_Array[portid].FWS.State = state;

		if (cleanup)
		{
			fwsLivenessStop(portid);
			//fwsContextReset(fc, state, reason);
			if (PP_Array[portid].FWS.FileData != NULL) {
				PP_Array[portid].FWS.FileData = NULL;
				FWS_FileData_Count--;
				if (FWS_FileData_Count == 0) {
					free(FWS_FileData);
					FWS_FileData = NULL;
					FWS_FileSize = 0;
				}
			}
		}
	}
	else
	{
		PRINT_MESSAGE("\r\n (PortID %02i remains in FWS state %s \r\n",portid, fwsStateName(state));
	}

	return HANDLED;
}

void fwsNotifyMessageSent(rsuint8 portid)
{
	PP_Array[portid].FWS.IncomingDTR = 0;
	PP_Array[portid].FWS.IncomingDATA = 0;
}

void SendMmiUleDataReq(rsuint8 portid, MmiDataType_t dataType, MmiUleSensHdr_t sensType, rsuint16 dataLen, rsuint8 data[])
{

	if (!PP_Array[portid].FWS.IncomingDTR){
		PRINT_MESSAGE("\r\n !!!!!!! DTR is still pending... -> wait for DTR !!!!!!");
		return ;
	}


	int totalLen = sizeof(MmiUlePdu_common_t)/*includes 16 data bytes*/ + dataLen - 16;
	MmiUlePdu_common_t* Payload = alloca(totalLen);
	memset(Payload, 0, totalLen);

	Payload->Hdr.Length = /* Type + NextMess + SensorType = */ 3 + dataLen;
	Payload->Hdr.Type = dataType;
	Payload->NextMess = 0;
	Payload->SensorType = sensType;
	memcpy(&Payload->Data[0], data, dataLen);
	rsuint8 DlcCtrl = (/*EARLY_BIT_ON*/3 << 6) | ULP_DLC_CTRL_ACKNOWLEDGED;

	SendApiFpUleDataReq(API_TASK, portid, DlcCtrl, Payload->Hdr.Length, &Payload->Hdr.Type);

	// FWS wants to keep some message administration, so let 'im!
	fwsNotifyMessageSent(portid);
}

static int fwsSendAbort(rsuint8 portid)
{
	if (!PP_Array[portid].FWS.IncomingDTR)
	{
		fwsStateTo(portid, FWSS_ABORT_PENDING);
	}
	else // ready: send now
	{
		fwsStateTo(portid, FWSS_ABORT_SENT);

		rsuint8 data[] = { MDT_FWS_ABORT_TRANSFER_REQ, 0xDE, 0xAD, 0xDE, 0xAD };
		SendMmiUleDataReq(portid, MMI_DATA_TYPE_FWS, 0, sizeof(data), data);
	}

	return HANDLED;
}


static int fwsApiFpUleDataRejectInd(rsuint8 portid, RsStatusType Status)
{

	if (Status!= RSS_SUCCESS)
	{
		// were we far along to tell em to stop?
		switch (PP_Array[portid].FWS.State)
		{
			case FWSS_XFER_STARTED:
				fwsSendAbort(portid);
				// not that sending this one itself might trigger a new ApiFpUleDataRejectInd,
				// but then we will not be in FWSS_XFER_STARTED anymore...
				return fwsStateTo(portid, FWSS_DISABLED);
				break;
			case FWSS_DISABLED:
				break;
			default:
				return fwsStateTo(portid, FWSS_DISABLED);
				break;
		}

	}
	return UNHANDLED;
}



static int fwsApiFpUleDtrInd(const rsuint8 portid)
{

	PP_Array[portid].FWS.IncomingDTR++;

	switch (PP_Array[portid].FWS.State)
	{
		case FWSS_NEW:
		case FWSS_DONE_REBOOTED:
			//return fwsSendUleGetVersion(portid);
			if (pendSwVerReq[portid] == TRUE) {
				pendSwVerReq[portid] = FALSE;
				fwsSendUleGetVersion(portid);
			}
			return UNHANDLED;
		// only serve nextPacket if we already were....
		// the first is sent after MDT_FWS_START_TRANSFER_CFM
		case FWSS_XFER_STARTED:
			return fwsSendNextPacket(portid, FALSE);

		case FWSS_ABORT_PENDING:
			PRINT_MESSAGE("fwsApiFpUleDtrInd : delayed-until-dtr ");
			return fwsSendAbort(portid);
		default:
			break;
	}
	// maybe others are interested in this DTR?
	return UNHANDLED;
}

 int fwsApiFpUleDataInd(rsuint8 portid,const MmiUlePdu_common_t* pdu)
{
	//MmiUlePdu_common_t* pdu = (MmiUlePdu_common_t*)&m->Length;
	// show if we receive non-FWS data
	if (pdu->Hdr.Type != MMI_DATA_TYPE_FWS)
	{
		return UNHANDLED;
	}

	PP_Array[portid].FWS.IncomingDATA++;



	MmiUleData_MmiDataTypeFwsOffs* d = (MmiUleData_MmiDataTypeFwsOffs*)&pdu->Data[0];
	//char *what = AA(MG("MDT_FWS_UNEXPECTED_STATE_0x%02X"), d->Action);
	switch (d->Action)
	{
		case MDT_FWS_GET_VERSION_CFM:
			return fwsApiFpUleDataInd_MdtFwsGetVersionCfm(portid, (MmiUlePdu_common_t*) pdu);

		case MDT_FWS_START_TRANSFER_CFM:
			return fwsSendNextPacket(portid, FALSE);

		case MDT_FWS_ABORT_TRANSFER_IND:
			return fwsStateTo(portid, FWSS_DISABLED);

		case MDT_FWS_RESULT_SUCCESS_IND:
			fwsStateTo(portid, FWSS_XFER_COMPLETED);
			return HANDLED;

		case MDT_FWS_RESULT_FAILED_IND:
			return fwsStateTo(portid, FWSS_DISABLED);

		case MDT_FWS_XFER_SUCCESS_IND:
			//what = "MDT_FWS_XFER_SUCCESS_IND";
			break; // continue with nextPacket

		case MDT_FWS_XFER_TIMEOUT_IND:
			//what = "MDT_FWS_XFER_TIMEOUT_IND";
			break; // continue with nextPacket

		case MDT_FWS_XFER_PENDED_ON_DTR_IND:
			//what = "MDT_FWS_XFER_PENDED_ON_DTR_IND";
			break; // continue with nextPacket
	}

	// let Fws world know it's still there
	fwsLivenessTickle(portid);

	// if we are not transferring
	if (!PP_Array[portid].FWS.BytesSent)
	{
		return fwsSendAbort(portid);
	}
	else if (d->Offset == PP_Array[portid].FWS.FileSize) // are we done?
	{
		PP_Array[portid].FWS.BytesAcked = d->Offset;
		if (PP_Array[portid].FWS.State == FWSS_XFER_STARTED)
		{
			fwsStateTo(portid, FWSS_XFER_COMPLETED);
			// now we wait for reboot msg + signs
			return HANDLED;
		}
		else
			PRINT_MESSAGE("\r\n XferDone + Unexpected state: do nothing! \n");
	}
	else // we're transferring...
	{
		PP_Array[portid].FWS.BytesAcked = d->Offset;
		//FWSS_INFO(fc, "%s: d->Offset: %08X (%u)", what, d->Offset, d->Offset);

		char allBytesSent = (PP_Array[portid].FWS.BytesSent == PP_Array[portid].FWS.FileSize);
		rsuint32 bytesRecvdShortage = (PP_Array[portid].FWS.BytesSent - PP_Array[portid].FWS.BytesAcked - PP_Array[portid].FWS.LastBlockLen);

		//char *extra = " [offset-ok]";

		if (allBytesSent && (bytesRecvdShortage == 0))
		{
			//extra = " [all-bytes-transferred]";

			// LastBlock has been processed, set 0
			PP_Array[portid].FWS.LastBlockLen = 0;
		}

		if (bytesRecvdShortage != 0)
		{
			if (PP_Array[portid].FWS.State == FWSS_XFER_STARTED)
			{
				if (bytesRecvdShortage == FWS_MAX_BUF_SIZE)
				{


				}
				else // too much
				{
					//extra = AA(" ["MG("Missing %i bytes, too much: abort")"]", bytesRecvdShortage);
				}

				// stop at 2nd missing packet
				if (bytesRecvdShortage >= 2 * FWS_MAX_BUF_SIZE){
					return fwsSendAbort(portid);
				}
			}
		}

		char restartXmission = FALSE;
		const char* action = "do nothing";

		if (PP_Array[portid].FWS.State == FWSS_XFER_STARTED)
		{
			// if we missed a DTR, then start again after 2nd incoming DATA_IND
			if (PP_Array[portid].FWS.IncomingDATA > 1)
			{
				restartXmission = TRUE;
				action = "stalled -> try sending a packet";
			}
			else
				action = "we send @DTR -> do nothing";
		}

		PRINT_MESSAGE( "FWS: %s (Offset %lu + LastBlock %lu = BytesSent %lu) \n",
				action, PP_Array[portid].FWS.BytesAcked,
				PP_Array[portid].FWS.LastBlockLen, PP_Array[portid].FWS.BytesSent);

		if (restartXmission)
			fwsSendNextPacket(portid, FALSE);
	}

	return HANDLED;
}


static int fwsSendNextPacket(rsuint8 portid, char retry){
	// also trigger liveness when we are sending something ourselves: the timer is for inactivity, so we
	// know when the process has failed. As long as we are sending something we're still 'working on it'.
	//FWS_Active[portid] = 1;

	(void)retry; // unused
	fwsLivenessTickle(portid);
	if (!PP_Array[portid].FWS.IncomingDTR){
		PRINT_MESSAGE("\r\n !DTR -> wait for DTR");
		return HANDLED;
	}
	// ready: send now
	if (PP_Array[portid].FWS.State == FWSS_XFER_REQUESTED)
	{

		fwsStateTo(portid, FWSS_XFER_STARTED);
	}
	// did we go too far?
	if (PP_Array[portid].FWS.BytesSent > PP_Array[portid].FWS.FileSize)
	{
		return fwsSendAbort(portid);
	}
	// send less than 1 full packet?

	PP_Array[portid].FWS.LastBlockLen = min(PP_Array[portid].FWS.FileSize - PP_Array[portid].FWS.BytesSent, FWS_MAX_BUF_SIZE);

#if 0
	#warning HACK-abort-at-10-pct
	if (fc->BytesSent * 100 / fc->FileSize == 10)
			return fwsSendAbort(pp, "HACK-abort-at-10-pct");
#endif

	// send raw message, without MmiUleData structure
	rsuint8 DlcCtrl = (/*EARLY_BIT_DISABLE*/0 << 6) | ULP_DLC_CTRL_ACKNOWLEDGED;
	SendApiFpUleDataReq(API_TASK, PP_Array[portid].FWS.Pp, DlcCtrl, PP_Array[portid].FWS.LastBlockLen, &PP_Array[portid].FWS.FileData[PP_Array[portid].FWS.BytesSent]);

	PP_Array[portid].FWS.BytesSent += PP_Array[portid].FWS.LastBlockLen;

	PRINT_MESSAGE ("Sent BytesSent: %lu fileSize: %lu blockLen: %lu Progress: %lu%% (cDTR %lu cDATA %lu) \n",
			(long unsigned) PP_Array[portid].FWS.BytesSent,
			(long unsigned) PP_Array[portid].FWS.FileSize, (long unsigned) PP_Array[portid].FWS.LastBlockLen,
			(long unsigned) (PP_Array[portid].FWS.BytesSent * 100 / PP_Array[portid].FWS.FileSize),
			(long unsigned) PP_Array[portid].FWS.IncomingDTR, (long unsigned)PP_Array[portid].FWS.IncomingDATA);

	// reset counters
	PP_Array[portid].FWS.IncomingDTR = 0;
	PP_Array[portid].FWS.IncomingDATA = 0;

	return HANDLED;
}

int fwsApiFpMmHandsetPresentInd(const ApiFpMmHandsetPresentIndType* m)
{
	rsuint8 portid = m->TerminalId;

	if(portid >= PP_COUNT_MAX){return HANDLED;}

	// let Fws world know it's still there
	//fwsLivenessTickle(portid);


	switch (PP_Array[portid].FWS.State)
	{
		case FWSS_NEW:
			//if (PP_Array[portid].FWS.IncomingDTR)
			//{
			//	PRINT_MESSAGE("fwsApiFpMmHandsetPresentInd + DTR: unlikely?");
			//	FWS_Active[portid] = 0;
			//	fwsSendUleGetVersion(portid);
			//}
			pendSwVerReq[portid] = TRUE;
			// prevent ColaTask from handling
			return UNHANDLED;

		// if this happens somewhere in the middle: bad juju
		case FWSS_XFER_REQUESTED:
		case FWSS_XFER_STARTED:
			FWS_Active[portid] = 0;
			fwsStateTo(portid, FWSS_DISABLED);
			fwsSendUleGetVersion(portid);
			// prevent ColaTask from handling
			return HANDLED;

		case FWSS_XFER_COMPLETED:
			//FWS_Active[portid] = 0;
			fwsStateTo(portid, FWSS_DONE_REBOOTED);
			//fwsSendUleGetVersion(portid);
			pendSwVerReq[portid] = TRUE;
			// allow ColaTask to handle from here
			return HANDLED;

		case FWSS_ABORT_PENDING:
			FWS_Active[portid] = 0;
			fwsStateTo(portid, FWSS_DISABLED);
			fwsSendUleGetVersion(portid);
			// allow ColaTask to handle from here
			return UNHANDLED;

		// we can always fetch ver info
		default:
			FWS_Active[portid] = 0;
			fwsSendUleGetVersion(portid);
			break;
			//FWSS_INFO(fc, "unhandled here");
	}

	// allow ColaTask to handle
	return UNHANDLED;
}


static void fwsStartTransfer(rsuint8 portid)
{
	fwsStateTo(portid, FWSS_XFER_REQUESTED);
	rsuint8 data[] = { MDT_FWS_START_TRANSFER_REQ };
	SendMmiUleDataReq(PP_Array[portid].FWS.Pp, MMI_DATA_TYPE_FWS, 0, sizeof(data), data);
}


static int fwsSendUleGetVersion(rsuint8 portid)
{
#ifndef IPBS_452_BUILD
	//PRINT_MESSAGE("skip!");
	return HANDLED;
#endif
	PRINT_MESSAGE("send MDT_FWS_GET_VERSION_REQ \n");
	// ask only once
	switch (PP_Array[portid].FWS.State)
	{
		case FWSS_NEW:
			if(FWS_Active[portid]) fwsStateTo(portid, FWSS_VER_REQUESTED);
			break;

		case FWSS_DONE_REBOOTED:
			if(FWS_Active[portid]) fwsStateTo(portid, FWSS_DONE_VER_REQUESTED);
			break;

		case FWSS_DISABLED:
			PRINT_MESSAGE("ask-anyway \n");
			break;

		default:
			// don't send the request
			return HANDLED;
	}

	PP_Array[portid].FWS.Pp=portid;
	rsuint8 data[] = { MDT_FWS_GET_VERSION_REQ };
	SendMmiUleDataReq(PP_Array[portid].FWS.Pp, MMI_DATA_TYPE_FWS, 0, sizeof(data), data);

	return HANDLED;
}


static int fwsApiFpUleDataInd_MdtFwsGetVersionCfm(rsuint8 portid, MmiUlePdu_common_t* pdu)
{
	MmiUleData_MmiDataTypeFws* d = (MmiUleData_MmiDataTypeFws*)&pdu->Data[0];

	PRINT_MESSAGE(" \r\n\r\n ######### PP Firmware version: Sensor=%X, StackVersion=0x%04X, Cola Rev=%2u Build=%2u LinkDate=%2X %2X %2X %2X %2X  ########\r\n\r\n ",
		pdu->SensorType, d->StackVersion, d->ColaRev, d->ColaBuildNo, d->ColaLinkDate[0],
		d->ColaLinkDate[1],d->ColaLinkDate[2],d->ColaLinkDate[3],d->ColaLinkDate[4]);

	switch (PP_Array[portid].FWS.State)
	{
		case FWSS_NEW:
		case FWSS_DONE_REBOOTED:
			PP_Array[portid].FWS.SensorType = pdu->SensorType;
			PP_Array[portid].FWS.StackVersion = d->StackVersion;
			PP_Array[portid].FWS.ColaRev = d->ColaRev;
			PP_Array[portid].FWS.ColaBuildNo = d->ColaBuildNo;
			memcpy(PP_Array[portid].FWS.ColaLinkDate, d->ColaLinkDate, 5);
			break;
		case FWSS_VER_REQUESTED:
		{
			PP_Array[portid].FWS.SensorType = pdu->SensorType;
			PP_Array[portid].FWS.StackVersion = d->StackVersion;
			PP_Array[portid].FWS.ColaRev = d->ColaRev;
			PP_Array[portid].FWS.ColaBuildNo = d->ColaBuildNo;
			memcpy(PP_Array[portid].FWS.ColaLinkDate, d->ColaLinkDate, 5);

			// fetch best upgradable firmware
			if (fwsFindUpgradableFirmware(portid, FFCF_LOAD))
			{
				fwsStateTo(portid, FWSS_VER_HAVE_UPDATE);

				// we can do an update
				fwsStartTransfer(portid);
			}
			else // no upgradable files found? Older?
			{
				fwsStateTo(portid, FWSS_DONE_VER_UP_TO_DATE);
			}
			break;
		}

		// check how the update went...
		case FWSS_DONE_VER_REQUESTED:
		{
			// update vars
			PP_Array[portid].FWS.SensorType = pdu->SensorType;
			PP_Array[portid].FWS.StackVersion = d->StackVersion;
			PP_Array[portid].FWS.ColaRev = d->ColaRev;
			PP_Array[portid].FWS.ColaBuildNo = d->ColaBuildNo;
			memcpy(PP_Array[portid].FWS.ColaLinkDate, d->ColaLinkDate, 5);

			if (fwsFindUpgradableFirmware(portid, FFCF_CHECK))
			{
				fwsStateTo(portid, FWSS_DONE_VER_STILL_DIFFERENT);
			}
			else
			{
				fwsStateTo(portid, FWSS_DONE_VER_UP_TO_DATE);
			}

			break;
		}

		default:
			//PRINT_MESSAGE("ignored incoming MDT_FWS_GET_VERSION_CFM");
			break;
	}

	return HANDLED;
}

static void fwsLivenessTickle(rsuint8 portid)
{
	PP_Array[portid].FWS.LivenessTimer = FWS_LIVENESS_TIMEOUT_SECS;
}


static void fwsLivenessStop(rsuint8 portid)
{
	PP_Array[portid].FWS.LivenessTimer=0;
}

void FWSInit(rsuint8 portid){

	if(PP_Array[portid].State.State != S_PP_ULE_ONLINE){
		PRINT_MESSAGE( "\r\n PP %d is not ONLINE yet. Try again later... \r\n",portid);
		return;
	}

	if (!FWS_Active[portid]) {
		FWS_Active[portid] = 1;
		fwsStateTo(portid, FWSS_NEW);
		PP_Array[portid].FWS.IncomingDTR = 1; //Bypass initial DTR check error
		fwsSendUleGetVersion(portid);
	} else {
		fwsSendAbort(portid);
	}
	return;

}


void FWSInitALL(const char* fileToUse) {
	rsuint8 i;
	rsbool fileGiven = (strlen(fileToUse) > 0) ? TRUE : FALSE;
	for (i=7;i< PP_COUNT_MAX; i++) {
		if (PP_Array[i].State.State == S_PP_ULE_ONLINE) {
			if (fileGiven)
				setFwsFilenameToUse(i, fileToUse);
			FWSInit(i);
		}
	}
}


rsuint8 getAvailableFwsFilesNumber() {
	rsuint8 arrLen=0;
	rsuint16 aNum;
	DIR* dp = opendir(FWS_FILE_SAVE_DIR);
	if (dp) {
		struct dirent* de;
		for (de = readdir(dp); de; de = readdir(dp)) {
			if (arrLen >= MAX_FWS_FILE_NUM) break;
			if ((sscanf(de->d_name, patternCola, &aNum, &aNum) == 2)
					|| (sscanf(de->d_name, patternStack, &aNum) == 1)) {
				arrLen++;
			}
		}
		closedir(dp);
	}
	return arrLen;
}


rsuint8 getAvailableFwsFileNames(char *fileNames[]) {
	rsuint8 arrLen=0;
	rsuint16 aNum;
	DIR* dp = opendir(FWS_FILE_SAVE_DIR);
	if (dp) {
		struct dirent* de;
		for (de = readdir(dp); de; de = readdir(dp)) {
			if (arrLen >= MAX_FWS_FILE_NUM) break;
			if (sscanf(de->d_name, patternCola, &aNum, &aNum) == 2){
				memset(fileNames[arrLen], 0, MAX_STR_LEN_FWS);
				strncpy(fileNames[arrLen], de->d_name, MAX_STR_LEN_FWS);
				arrLen++;
			}
			if (sscanf(de->d_name, patternStack, &aNum) == 1) {
				memset(fileNames[arrLen], 0, MAX_STR_LEN_FWS);
				strncpy(fileNames[arrLen], de->d_name, MAX_STR_LEN_FWS);
				arrLen++;
			}
		}
		closedir(dp);
	}
	return arrLen;
}


void setFwsFilenameToUse(rsuint8 portId, const char* fileName) {
	snprintf(fws_file_name,127,"%s%s",FWS_FILE_SAVE_DIR,fileName);
	fws_file_manual_set[portId] = TRUE;
}
rsuint8 deleteFwsFile(const char *fileName) {
	char *existing[MAX_FWS_FILE_NUM];
	rsuint8 arrLen,i;
	rsuint8 result = 3; // initial code: file not found or not allowed
	char *fileToDel;
	if (strlen(fileName) > MAX_STR_LEN_FWS) return 2; // filename  length out of bounds
	fileToDel = malloc(strlen(FWS_FILE_SAVE_DIR)+strlen(fileName)+1);
	strcpy(fileToDel, FWS_FILE_SAVE_DIR);
	strcat(fileToDel, fileName);
	arrLen = getAvailableFwsFilesNumber();
	for(i=0;i<arrLen;i++)
		existing[i] = (char *) malloc(MAX_STR_LEN_FWS * sizeof(char));
	arrLen = getAvailableFwsFileNames(existing);
	for(i=0; i < arrLen; i++ ) {
		if (strcmp(existing[i], fileName) == 0) {
			if (remove(fileToDel) == 0) {
				PRINT_MESSAGE("Successfully deleted file \"%s\"\n",fileToDel);
				result = 0; // success in delete
			} else {
				PRINT_MESSAGE("Error while deleting file \"%s\"\n",fileToDel);
				result = 1; // fail in delete
			}
		}
	}
	free(fileToDel);
	for(i=0;i<arrLen;i++)
		free(existing[i]);
	return result;
}


int fwsFindUpgradableFirmware(rsuint8 portid,rsuint8 flags){


	// find highest ColaTask firmware for this SensorType
	// find highest Stack firmware for this SensorType
	rsuint32 ColaRev = 0;
	rsuint32 ColaBuild = 0;
	rsuint32 StackVersion = 0;

	if (!fws_file_manual_set[portid]) { // if fws_file_name was given by web page, skip auto search

		DIR* dp = opendir(FWS_FILE_SAVE_DIR);
	if (dp)
	{
		struct dirent* de;
		for (de = readdir(dp); de; de = readdir(dp))
		{
			rsuint32 rev = 0;
			rsuint32 build = 0;
			rsuint32 stack = 0;

			if (sscanf(de->d_name, patternCola, &rev, &build) == 2)
			{
				//if ((rev >= ColaRev) && (build >= ColaBuild))
				if ((rev >= 150) && (build >= 1))
				{
					ColaRev = rev;
					ColaBuild = build;
						strncpy(fws_cola_name,de->d_name,128);
					PRINT_MESSAGE("\r\n  Found Cola App: %s ",de->d_name);
				}
			}
			if (sscanf(de->d_name, patternStack, &stack) == 1)
				//if (stack >= StackVersion){
				if (stack >= 1100){
					StackVersion = stack;
						strncpy(fws_stack_name,de->d_name,128);
					PRINT_MESSAGE("\r\n  Found Stack: %s ",de->d_name);
				}
		}
		closedir(dp);
	}

	if (StackVersion && (StackVersion != PP_Array[portid].FWS.StackVersion))
	{
			snprintf(fws_file_name,127,"%s%s",FWS_FILE_SAVE_DIR,fws_stack_name);
	}
	else if (ColaRev && ColaBuild && ((ColaRev != PP_Array[portid].FWS.ColaRev) || (ColaBuild != PP_Array[portid].FWS.ColaBuildNo)))
	{
			snprintf(fws_file_name,127,"%s%s",FWS_FILE_SAVE_DIR,fws_cola_name);
	}
	else
	{
			PRINT_MESSAGE( "\r\n No newer .fws files found in %s for module type %X (Stack %04lX Rev %lu Build %lu) \n",
					FWS_FILE_SAVE_DIR, PP_Array[portid].FWS.SensorType, StackVersion, ColaRev, ColaBuild);
		return FALSE;
		}
	}

	fws_file_manual_set[portid] = FALSE; // reset for next use
	PRINT_MESSAGE( "\r\n Loading File : %s \n",fws_file_name);

	if (FWS_FileData != NULL) {
		PP_Array[portid].FWS.FileData = FWS_FileData;
		PP_Array[portid].FWS.FileSize = FWS_FileSize;
	} else {
	FILE *pFile = fopen(fws_file_name, "r");
	if (pFile == NULL)
	{
			PRINT_MESSAGE( "File '%s' not found \n", fws_file_name);
		return FALSE;
	}
	fseek(pFile, 0, SEEK_END);
		FWS_FileSize = ftell(pFile);
	rewind(pFile);

		FWS_FileData = malloc(FWS_FileSize + 20);
		if (FWS_FileData == NULL )
	{
			PRINT_MESSAGE( "Cannot allocate RAM :  %lu \n", FWS_FileSize);
		return FALSE;
	}
		fread(FWS_FileData, 1, FWS_FileSize, pFile);
	if (ferror(pFile))
	{
			PRINT_MESSAGE("Cannot read file '%s' \n", fws_file_name);
		fclose(pFile);
			free(FWS_FileData);
			FWS_FileData = NULL;
		return FALSE;
	}
	fclose(pFile);
		FWS_FileData_Count = 0;
		PP_Array[portid].FWS.FileData = FWS_FileData;
		PP_Array[portid].FWS.FileSize = FWS_FileSize;
	}
	FWS_FileData_Count++;

	if (flags & FFCF_LOAD)
	{
		//FWSS_INFO(fc, "successfully opened file '%s'", file);
		PP_Array[portid].FWS.BytesSent = 0;
		PP_Array[portid].FWS.BytesAcked = 0;
	}
	else // just FFCF_CHECK
	{
		// cleanup
		if (PP_Array[portid].FWS.FileData != NULL) {
		PP_Array[portid].FWS.FileData = NULL;
			FWS_FileData_Count--;
			if (FWS_FileData_Count == 0) {
				free(FWS_FileData);
				FWS_FileData = NULL;
				FWS_FileSize = 0;
			}
		}
	}

	return TRUE;

}


UleErr_e ULE_TxAbort(rsuint8 portId) {
ULE_API_ENTRY	ASSERT_ULE_INIT_SUCCESS;
	ASSERT_ULE_PORTID_INRANGE;

	MUTEXOBTAIN_semULEData;

	if (PP_Array[portId].State.State == S_PP_NOT_REGISTERED) {
		MUTEXRELEASE_semULEData;
		return ULE_PP_NotRegisteredError;
	}

	CLEAREVENT_TXABORT;

	SendApiFpUleAbortDataReq(API_TASK, portId);

	WAITEVENT_TXABORT;

	if (PiStatus.AbortStatus) {
		MUTEXRELEASE_semULEData;
		return ULE_TxAbortError;
	}

	PP_Array[portId].TxBuff.TxPacketStatus = Tx_Buff_Empty_TxAborted;

	MUTEXRELEASE_semULEData;
	return ULE_Success;

}

void ULE_TxAbort_Cfm(RsStatusType Status) {
	ULE_API_ENTRY

	PiStatus.AbortStatus = Status;
	RAISEEVENT_TXABORT;

}

UleErr_e ULE_GetIPUI(rsuint8 portId,rsuint8 IPUIval[]) {
ULE_API_ENTRY	ASSERT_ULE_INIT_SUCCESS;
	ASSERT_ULE_PORTID_INRANGE;

	*IPUIval = 0;

	MUTEXOBTAIN_semULEData;

	if (PP_Array[portId].State.State == S_PP_NOT_REGISTERED) {
		MUTEXRELEASE_semULEData;
		return ULE_PP_NotRegisteredError;
	}

	CLEAREVENT_IPUI;

	SendApiFpUleGetDeviceIpuiReq(API_TASK, portId);

	WAITEVENT_IPUI;

	if (PiStatus.IPUIstatus) {
		MUTEXRELEASE_semULEData;
		return ULE_IPUIreadError;
	}

	IPUIval[0] = PP_Array[portId].IPUI[0];
	IPUIval[1] = PP_Array[portId].IPUI[1];
	IPUIval[2] = PP_Array[portId].IPUI[2];
	IPUIval[3] = PP_Array[portId].IPUI[3];
	IPUIval[4] = PP_Array[portId].IPUI[4];

	MUTEXRELEASE_semULEData;
	return ULE_Success;

}

void ULE_GetIPUI_Cfm(RsStatusType Status,rsuint8 portId, rsuint8 IPUIarr[]) {

	ULE_API_ENTRY
	ASSERT_PI_PORTID_INRANGE;
	PiStatus.IPUIstatus = Status;

	if (PiStatus.IPUIstatus) {
		RAISEEVENT_IPUI;
		return;
	}

	PP_Array[portId].IPUI[0] = IPUIarr[0];
	PP_Array[portId].IPUI[1] = IPUIarr[1];
	PP_Array[portId].IPUI[2] = IPUIarr[2];
	PP_Array[portId].IPUI[3] = IPUIarr[3];
	PP_Array[portId].IPUI[4] = IPUIarr[4];

	RAISEEVENT_IPUI;

}


UleErr_e ULE_GetRFPI(rsuint8 RFPIval[]) {
	ULE_API_ENTRY;
	ASSERT_ULE_INIT_SUCCESS;

	MUTEXOBTAIN_semULEData;

	CLEAREVENT_RFPI;

	SendApiFpMmGetIdReq(API_TASK);

	WAITEVENT_RFPI;


	if (PiStatus.RFPIstatus) {
		MUTEXRELEASE_semULEData;
		return ULE_RFPIreadError;
	}

	RFPIval[0] = sysInfoDb.RFPI[0];
	RFPIval[1] = sysInfoDb.RFPI[1];
	RFPIval[2] = sysInfoDb.RFPI[2];
	RFPIval[3] = sysInfoDb.RFPI[3];
	RFPIval[4] = sysInfoDb.RFPI[4];


	MUTEXRELEASE_semULEData;
	return ULE_Success;

}

void ULE_GetRFPI_Cfm(RsStatusType Status, rsuint8 RFPIarr[]) {
	ULE_API_ENTRY


	PiStatus.RFPIstatus = Status;

	if (PiStatus.RFPIstatus ) {
		RAISEEVENT_RFPI;
		return;
	}

	sysInfoDb.RFPI[0] = RFPIarr[0];
	sysInfoDb.RFPI[1] = RFPIarr[1];
	sysInfoDb.RFPI[2] = RFPIarr[2];
	sysInfoDb.RFPI[3] = RFPIarr[3];
	sysInfoDb.RFPI[4] = RFPIarr[4];

	RAISEEVENT_RFPI;

}


void ULE_Deregister_Cfm(RsStatusType Status, rsuint8 ID) {
	ULE_API_ENTRY

	(void) ID;	// unused

	PiStatus.Deregister = Status;
	RAISEEVENT_DEREGMODE;

}

void ULE_SetRegMode_Cfm(RsStatusType Status) {
	ULE_API_ENTRY

	PiStatus.SetRegModeStatus = Status;
	RAISEEVENT_SETREGMODE;

}

UleErr_e ULE_Enable_Registration(rsuint32 registration_timeout) {
ULE_API_ENTRY	ASSERT_ULE_INIT_SUCCESS;

	MUTEXOBTAIN_semULEData;

	CLEAREVENT_SETREGMODE;
	SendApiFpMmSetRegistrationModeReq(API_TASK, 0x01, 0x01);
	WAITEVENT_SETREGMODE;

	if (PiStatus.SetRegModeStatus) {
		MUTEXRELEASE_semULEData;
		return ULE_SetRegModeError;
	}
	switchLed(DECT_REG_LED, 1);
	sysInfoDb.registrationMode = 1;
	sysInfoDb.registrationMode_timeout = registration_timeout; // Disable registration after this amount of time.
	MUTEXRELEASE_semULEData;
	return ULE_Success;
}

UleErr_e ULE_Disable_Registration() {
ULE_API_ENTRY	ASSERT_ULE_INIT_SUCCESS;

	MUTEXOBTAIN_semULEData;

	CLEAREVENT_SETREGMODE;
	SendApiFpMmSetRegistrationModeReq(API_TASK, 0x00, 0x01);
	WAITEVENT_SETREGMODE;

	if (PiStatus.SetRegModeStatus) {
		MUTEXRELEASE_semULEData;
		return ULE_SetRegModeError;
	}
	switchLed(DECT_REG_LED, 0);
	sysInfoDb.registrationMode = 0;
	sysInfoDb.registrationMode_timeout = 0;
	MUTEXRELEASE_semULEData;
	return ULE_Success;
}

rsbool ULE_Get_Registration_Mode() {
	ULE_API_ENTRY
	return sysInfoDb.registrationMode;
}

UleErr_e ULE_DeRegister_all() {
ULE_API_ENTRY	ASSERT_ULE_INIT_SUCCESS;

	rsuint8  RegDev, MaxDevices;

#ifdef CONFIG_SOUND
	dect_deregister();
#endif

	ULE_Get_Registration_Count(&RegDev,&MaxDevices);

	MUTEXOBTAIN_semULEData;
	rsuint8 i;
	UleErr_e st;

	for (i = 0; i < PP_COUNT_MAX; i++) {
		st = ULE_DeRegister_Internal(i);
	}

	MUTEXRELEASE_semULEData;

	// set timer to update PiStatus after 20 seconds
	deregisterAllUpdateTimer = 20;

	return st;
}

UleErr_e ULE_DeRegister(rsuint8 portId) {
ULE_API_ENTRY	ASSERT_ULE_INIT_SUCCESS;
	ASSERT_ULE_PORTID_INRANGE;

	MUTEXOBTAIN_semULEData;
	UleErr_e st;

	if (PP_Array[portId].State.State == S_PP_NOT_REGISTERED) {
		MUTEXRELEASE_semULEData;
		return ULE_PP_NotRegisteredError;
	}

	st = ULE_DeRegister_Internal(portId);

	MUTEXRELEASE_semULEData;
	return st;
}

static UleErr_e ULE_DeRegister_Internal(rsuint8 portId) {
	ULE_API_ENTRY

	if (PP_Array[portId].State.State == S_PP_NOT_REGISTERED) {
		return ULE_Success;
	}

	CLEAREVENT_DEREGMODE;
//#if  defined( CONFIG_CATIQ_V711_SUPPORT )
	SendApiFpMmDeleteRegistrationReq(API_TASK, portId);
//#else
//	SendApiFpUleDeleteRegistrationReq(API_TASK, portId);
//#endif
	WAITEVENT_DEREGMODE;
	ULE_PP_add(portId);
	PP_Array[portId].State.State = S_PP_NOT_REGISTERED;
	return ULE_Success;
}

UleErr_e ULE_Set_TxData_timeout(rsuint8 portId, rsuint32 timeout_val) {
ULE_API_ENTRY	ASSERT_ULE_INIT_SUCCESS;
	ASSERT_ULE_PORTID_INRANGE;

	MUTEXOBTAIN_semULEData;

	if (PP_Array[portId].State.State == S_PP_NOT_REGISTERED) {
		MUTEXRELEASE_semULEData;
		return ULE_PP_NotRegisteredError;
	} else {
		PP_Array[portId].TxBuff.TxtimeoutStatusValue = timeout_val;
	}
	MUTEXRELEASE_semULEData;
	return ULE_Success;
}

UleErr_e ULE_Get_TxData_timeout(rsuint8 portId, rsuint32 *timeoutPtr) {
	ULE_API_ENTRY
	*timeoutPtr = 0;

	ASSERT_ULE_INIT_SUCCESS;
	ASSERT_ULE_PORTID_INRANGE;

	MUTEXOBTAIN_semULEData;

	if (PP_Array[portId].State.State == S_PP_NOT_REGISTERED) {
		MUTEXRELEASE_semULEData;
		return ULE_PP_NotRegisteredError;
	} else {
		*timeoutPtr = PP_Array[portId].TxBuff.TxtimeoutStatusValue;
	}
	MUTEXRELEASE_semULEData;
	return ULE_Success;
}

UleErr_e ULE_Set_PP_timeout(rsuint8 portId, rsuint32 timeout_val) {
ULE_API_ENTRY	ASSERT_ULE_INIT_SUCCESS;
	ASSERT_ULE_PORTID_INRANGE;

	MUTEXOBTAIN_semULEData;

	if (PP_Array[portId].State.State == S_PP_NOT_REGISTERED) {
		MUTEXRELEASE_semULEData;
		return ULE_PP_NotRegisteredError;
	} else {
		PP_Array[portId].State.timeoutStatusValue = timeout_val;
	}
	MUTEXRELEASE_semULEData;
	return ULE_Success;
}

UleErr_e ULE_Get_PP_timeout(rsuint8 portId, rsuint32 *timeoutPtr,rsuint32 *timeoutPtr1) {
	ULE_API_ENTRY
	*timeoutPtr = 0;

	ASSERT_ULE_INIT_SUCCESS;
	ASSERT_ULE_PORTID_INRANGE;

	MUTEXOBTAIN_semULEData;

	if (PP_Array[portId].State.State == S_PP_NOT_REGISTERED) {
		MUTEXRELEASE_semULEData;
		return ULE_PP_NotRegisteredError;
	} else {
		*timeoutPtr = ULE_Get_Sys_Time() - PP_Array[portId].State.keepAlive;
		*timeoutPtr1 = PP_Array[portId].State.timeoutStatusValue;
	}
	MUTEXRELEASE_semULEData;
	return ULE_Success;
}

rsuint32 ULE_Get_Sys_Time() {
	//ULE_API_ENTRY

	time_t rawtime;
	time(&rawtime);
	return rawtime;
}

char *ULE_Get_SW_Version() {
	ULE_API_ENTRY


	return &VERSION[0];
}

UleErr_e ULE_Get_PP_transmit_status(rsuint8 portId, rsuint8 *statusPtr) {
ULE_API_ENTRY	ASSERT_ULE_INIT_SUCCESS;
	ASSERT_ULE_PORTID_INRANGE;

	MUTEXOBTAIN_semULEData;

	*statusPtr = 0;

	if (PP_Array[portId].State.State == S_PP_NOT_REGISTERED) {
		MUTEXRELEASE_semULEData;
		return ULE_PP_NotRegisteredError;
	} else {
		*statusPtr = PP_Array[portId].TxBuff.TxPacketStatus;
	}
	MUTEXRELEASE_semULEData;
	return ULE_Success;
}

UleErr_e ULE_Get_PP_status(rsuint8 portId, rsuint8 *statusPtr) {
ULE_API_ENTRY	ASSERT_ULE_INIT_SUCCESS;
	ASSERT_ULE_PORTID_INRANGE;

	MUTEXOBTAIN_semULEData;
	*statusPtr = (rsuint8) PP_Array[portId].State.State;
	MUTEXRELEASE_semULEData;
	return ULE_Success;
}


UleErr_e ULE_Set_Time_Server(char *addr) {
ULE_API_ENTRY	ASSERT_ULE_INIT_SUCCESS;

	FILE *file;
#ifdef IPBS_452_BUILD
	file = fopen("/mnt/flash/rdate_server","w");
#else
	file = fopen("./rdate_server","w");
#endif
	if (file == NULL) {
		return ULE_Fail;
	}
	fprintf(file,"%s",addr);
	fclose(file); /*done!*/
	return ULE_Success;
}


UleErr_e ULE_Get_PP_type(rsuint8 portId, rsuint8 *statusPtr) {
ULE_API_ENTRY	ASSERT_ULE_INIT_SUCCESS;
	ASSERT_ULE_PORTID_INRANGE;

	MUTEXOBTAIN_semULEData;

	if (PP_Array[portId].State.State == S_PP_NOT_REGISTERED) {
		MUTEXRELEASE_semULEData;
		return ULE_PP_NotRegisteredError;
	}

#ifdef CONFIG_SOUND
	if ((portId<7)&&(Pendants[portId].ispendant>1)){
		*statusPtr = 0x4;
	}else
#endif
	{
		*statusPtr = (rsuint8) PP_Array[portId].SensorType;
	}
	MUTEXRELEASE_semULEData;
	return ULE_Success;
}


UleErr_e ULE_Set_PP_RSSI_Val(rsuint8 portId, rsuint8 rssiVal) {
	ULE_API_ENTRY	ASSERT_ULE_INIT_SUCCESS;
	ASSERT_ULE_PORTID_INRANGE;

	MUTEXOBTAIN_semULEData;

	if (PP_Array[portId].State.State == S_PP_NOT_REGISTERED) {
		MUTEXRELEASE_semULEData;
		return ULE_PP_NotRegisteredError;
	}

	PP_Array[portId].RSSI = rssiVal;

	MUTEXRELEASE_semULEData;
	return ULE_Success;
}


UleErr_e ULE_Get_PP_RSSI_Val(rsuint8 portId, rsuint8 *rssiVal) {
	ULE_API_ENTRY	ASSERT_ULE_INIT_SUCCESS;
	ASSERT_ULE_PORTID_INRANGE;

	MUTEXOBTAIN_semULEData;

	if (PP_Array[portId].State.State == S_PP_NOT_REGISTERED) {
		MUTEXRELEASE_semULEData;
		return ULE_PP_NotRegisteredError;
	}

	*rssiVal = (rsuint8) PP_Array[portId].RSSI;

	MUTEXRELEASE_semULEData;
	return ULE_Success;
}


UleErr_e ULE_Get_PP_SW_Version_Info(rsuint8 portId, rsuint8 swVersion[]) {
	ULE_API_ENTRY	ASSERT_ULE_INIT_SUCCESS;
	ASSERT_ULE_PORTID_INRANGE;

	//MUTEXOBTAIN_semULEData;
	rsuint8 i;

	// initialize it, swVersion should always have 12 elements
	memset(swVersion, 0, (sizeof(swVersion[0])*12));

	if (PP_Array[portId].State.State == S_PP_NOT_REGISTERED) {
		//MUTEXRELEASE_semULEData;
		return ULE_PP_NotRegisteredError;
	}
	swVersion[0] = (rsuint8) (PP_Array[portId].SensorType);
	swVersion[1] = (rsuint8) ((PP_Array[portId].FWS.StackVersion) >> 8);
	swVersion[2] = (rsuint8) ((PP_Array[portId].FWS.StackVersion) & 0xFF);
	swVersion[3] = (rsuint8) ((PP_Array[portId].FWS.ColaRev) >> 8);
	swVersion[4] = (rsuint8) ((PP_Array[portId].FWS.ColaRev) & 0xFF);
	swVersion[5] = (rsuint8) ((PP_Array[portId].FWS.ColaBuildNo) >> 8);
	swVersion[6] = (rsuint8) ((PP_Array[portId].FWS.ColaBuildNo) & 0xFF);
	for(i=0; i<5; i++) {
		swVersion[7+i] = (rsuint8) (PP_Array[portId].FWS.ColaLinkDate[i]);
	}

	//MUTEXRELEASE_semULEData;
	return ULE_Success;
}


UleErr_e ULE_Get_PP_FWS_Status_Info(rsuint8 portId, rsuint8 *ppState, rsuint8 *fwsStatus, rsuint8 *fwsProgress) {

	ULE_API_ENTRY	ASSERT_ULE_INIT_SUCCESS;
	ASSERT_ULE_PORTID_INRANGE;

	//MUTEXOBTAIN_semULEData;
	//rsuint8 i;//, progress;
	*ppState = 0;
	*fwsStatus = 0;
	*fwsProgress = 0;

	if (PP_Array[portId].State.State == S_PP_NOT_REGISTERED) {
		//MUTEXRELEASE_semULEData;
		*fwsStatus = 255;
		*fwsProgress = 255;
		return ULE_PP_NotRegisteredError;
	}

	*ppState   = (rsuint8) (PP_Array[portId].State.State);
	*fwsStatus = (rsuint8) (PP_Array[portId].FWS.State);
	*fwsProgress = (rsuint8) (PP_Array[portId].FWS.BytesSent * 100 / PP_Array[portId].FWS.FileSize);

	//MUTEXRELEASE_semULEData;
	return ULE_Success;

}


UleErr_e ULE_Get_PP_Attribute(rsuint8 portId, rsuint8 num, rsuint32 *valPtr) {
ULE_API_ENTRY	ASSERT_ULE_INIT_SUCCESS;
	ASSERT_ULE_PORTID_INRANGE;

	if (num>=MAXUSERATTRIB) {
		return ULE_PP_AttrOutOfRangeError;
	}

	MUTEXOBTAIN_semULEData;

	if (PP_Array[portId].State.State == S_PP_NOT_REGISTERED) {
		MUTEXRELEASE_semULEData;
		return ULE_PP_NotRegisteredError;
	}

	*valPtr = (rsuint32) PP_Array[portId].userAttrib[num];
	MUTEXRELEASE_semULEData;
	return ULE_Success;
}

UleErr_e ULE_Set_PP_Attribute(rsuint8 portId, rsuint8 num, rsuint32 valPtr) {
ULE_API_ENTRY	ASSERT_ULE_INIT_SUCCESS;
	ASSERT_ULE_PORTID_INRANGE;

	if (num>=MAXUSERATTRIB) {
		return ULE_PP_AttrOutOfRangeError;
	}

	MUTEXOBTAIN_semULEData;

	if (PP_Array[portId].State.State == S_PP_NOT_REGISTERED) {
		MUTEXRELEASE_semULEData;
		return ULE_PP_NotRegisteredError;
	}

	PP_Array[portId].userAttrib[num]=valPtr;
	MUTEXRELEASE_semULEData;
	return ULE_Success;
}

DataPackets_t *ULE_create_datpck(DataPacket_t *pckPtr) {
	DataPackets_t *newWords = malloc(sizeof(DataPackets_t));
	if (NULL != newWords) {
		newWords->DatPckt = pckPtr;
		newWords->next = NULL;
	}
	return newWords;
}

DataPackets_t *ULE_add_datpck(DataPackets_t *pckListPtr, DataPacket_t *pckPtr) {
	DataPackets_t *newpck = ULE_create_datpck(pckPtr);
	if (NULL != newpck) {
		newpck->next = pckListPtr;
	}
	return newpck;
}

void ULE_delete_dat_pck(DataPackets_t *pckPtr) {
	if (pckPtr == NULL) {
		return;
	}
	if (NULL != pckPtr->next) {
		ULE_delete_dat_pck(pckPtr->next);
	}
	free(pckPtr);
}

UleErr_e ULE_Read_Data(rsuint8 portId, rsuint32 PctID, DataPackets_t **pcklst) {
ULE_API_ENTRY	ASSERT_ULE_INIT_SUCCESS;
	ASSERT_ULE_PORTID_INRANGE;

	rsuint8 j;
	MUTEXOBTAIN_semULEData;

	if (PP_Array[portId].State.State == S_PP_NOT_REGISTERED) {
		MUTEXRELEASE_semULEData;
		return ULE_PP_NotRegisteredError;
	}

	for (j = 0; j < RX_BUFF_SIZE; j++) {
		if (PP_Array[portId].RxBuff.RxDataBuff[j].DataPackId > PctID) {
			*pcklst = ULE_add_datpck(*pcklst, &(PP_Array[portId].RxBuff.RxDataBuff[j]));
		}
	}

	MUTEXRELEASE_semULEData;
	return ULE_Success;
}

UleErr_e ULE_Read_Latest_Event_Data(rsuint8 portId, rsuint8 Event, DataPacket_t *dataPacketPtr) {
ULE_API_ENTRY	ASSERT_ULE_INIT_SUCCESS;
	ASSERT_ULE_PORTID_INRANGE;

	MUTEXOBTAIN_semULEData;

	if (PP_Array[portId].State.State == S_PP_NOT_REGISTERED) {
		MUTEXRELEASE_semULEData;
		return ULE_PP_NotRegisteredError;
	}
	if (Event >= MAX_DATA_TYPES_CNT){
		return ULE_DatatypeoutOfRange;
	}
	memcpy(dataPacketPtr,&(PP_Array[portId].RxBuff.LatestEventData[Event].DataPackId), sizeof(DataPacket_t));

	MUTEXRELEASE_semULEData;
	return ULE_Success;
}

UleErr_e ULE_Send_Data(rsuint8 portId,  rsuint8 EarlyBit, DataPacket_t *dataPacketPtr) {
ULE_API_ENTRY	ASSERT_ULE_INIT_SUCCESS;
	ASSERT_ULE_PORTID_INRANGE;

	if(FWS_Active[portId]) return ULE_Fail;
#ifndef DATA_LINK_TEST
	MUTEXOBTAIN_semULEData;
#endif

	if (PP_Array[portId].State.State == S_PP_NOT_REGISTERED) {
#ifndef DATA_LINK_TEST
		MUTEXRELEASE_semULEData;
#endif
		return ULE_PP_NotRegisteredError;
	}

	if (PP_Array[portId].TxBuff.TxPacketStatus == Tx_Buff_Full) {
#ifndef DATA_LINK_TEST
		MUTEXRELEASE_semULEData;
#endif
		return ULE_TxBuffNoSpaceError;
	}

	if ((*dataPacketPtr).Payload.Hdr.Length > DATA_TRANSMIT_MAX_SIZE) {
#ifndef DATA_LINK_TEST
		MUTEXRELEASE_semULEData;
#endif
		return ULE_DataArrayTooLarge;
	}
	if (EarlyBit == 0){
		EarlyBit=2;
	}else if (EarlyBit == 1){
		EarlyBit=3;
	}else if (EarlyBit == 2){
		EarlyBit=0;
	}else{
#ifndef DATA_LINK_TEST
		MUTEXRELEASE_semULEData;
#endif
		return ULE_EarlyBitConfigurationInvalid;
	}
	EarlyBit = EarlyBit << 6 ;
	switchLed(DECT_LED0, 1);
	SendApiFpUleDataReq(API_TASK, (rsuint16)portId, EarlyBit | ULP_DLC_CTRL_ACKNOWLEDGED, //,ULP_DLC_CTRL_UNACKNOWLEDGED
			(*dataPacketPtr).Payload.Hdr.Length,&((*dataPacketPtr).Payload.Hdr.Type));

	PP_Array[portId].TxBuff.TxPacketStatus = Tx_Buff_Full;
	PP_Array[portId].TxBuff.TxkeepAlive = ULE_Get_Sys_Time();
	fwsNotifyMessageSent(portId);
#ifndef DATA_LINK_TEST
	MUTEXRELEASE_semULEData;
#endif
	return ULE_Success;
}

UleErr_e ULE_Send_Data_Raw(rsuint8 portId,  rsuint8 EarlyBit, rsuint16 Len, rsuint8 *Data) {
ULE_API_ENTRY	ASSERT_ULE_INIT_SUCCESS;
	ASSERT_ULE_PORTID_INRANGE;

	//MUTEXOBTAIN_semULEData;

	if (PP_Array[portId].State.State == S_PP_NOT_REGISTERED) {
		MUTEXRELEASE_semULEData;
		return ULE_PP_NotRegisteredError;
	}

	if (PP_Array[portId].TxBuff.TxPacketStatus == Tx_Buff_Full) {

		if(PP_Array[portId].TxBuff.TxShadowLen==0){
			PP_Array[portId].TxBuff.TxShadowLen=Len;
			if (EarlyBit == 0){
				EarlyBit=2;
			}else if (EarlyBit == 1){
				EarlyBit=3;
			}else if (EarlyBit == 2){
				EarlyBit=0;
			}else{
				MUTEXRELEASE_semULEData;
				return ULE_EarlyBitConfigurationInvalid;
			}
			EarlyBit = EarlyBit << 6 ;
			PP_Array[portId].TxBuff.TxShadowPaging=EarlyBit;
			PP_Array[portId].TxBuff.TxShadowData = Data;
			MUTEXRELEASE_semULEData;
			return ULE_Success;
		}else
		{
			MUTEXRELEASE_semULEData;
			return ULE_TxBuffNoSpaceError;
		}
	}

//if (Len > DATA_TRANSMIT_MAX_SIZE) {
//		MUTEXRELEASE_semULEData;
//		return ULE_DataArrayTooLarge;
//	}
	if (EarlyBit == 0){
		EarlyBit=2;
	}else if (EarlyBit == 1){
		EarlyBit=3;
	}else if (EarlyBit == 2){
		EarlyBit=0;
	}else{
		MUTEXRELEASE_semULEData;
		return ULE_EarlyBitConfigurationInvalid;
	}
	EarlyBit = EarlyBit << 6 ;
	switchLed(DECT_LED0, 1);
	SendApiFpUleDataReq(API_TASK, (rsuint16)portId, EarlyBit | ULP_DLC_CTRL_ACKNOWLEDGED, //,ULP_DLC_CTRL_UNACKNOWLEDGED
			Len,Data);

	PP_Array[portId].TxBuff.TxPacketStatus = Tx_Buff_Full;
	PP_Array[portId].TxBuff.TxkeepAlive = ULE_Get_Sys_Time();
	fwsNotifyMessageSent(portId);
	//MUTEXRELEASE_semULEData;
	return ULE_Success;
}


void ULE_Set_SysInit(UleInitStatus_e SysInit) {
	ULE_API_ENTRY
	//MUTEXOBTAIN_semULEData;
	ULESysInit = SysInit;
	//MUTEXRELEASE_semULEData;
	RAISEEVENT_SYSINIT;
}

void ULE_Receive_Data(rsuint8 portId, DataPacket_t *dataPacketPtr) {
	ULE_API_ENTRY

	rsuint32 secondCount;
	switchLed(DECT_LED0, 1);


	if (portId >= PP_COUNT_MAX) {
		ULE_ERR_MSG("ULE received data from PP Id number out of bounds!\n");
		return;
	}

	if (PP_Array[portId].State.State == S_PP_NOT_REGISTERED) {
		return;
	}
	if ((*dataPacketPtr).Payload.Hdr.Length > DATA_TRANSMIT_MAX_SIZE) {
		ULE_ERR_MSG("ULE received more data then permitted! %d %d \n",DATA_TRANSMIT_MAX_SIZE,(*dataPacketPtr).Payload.Hdr.Length);
		return;
	}
	if ((*dataPacketPtr).Payload.Hdr.Type >= MAX_DATA_TYPES_CNT) {
		ULE_ERR_MSG("ULE received payload data type out of range ! %d %d \n",MAX_DATA_TYPES_CNT,(*dataPacketPtr).Payload.Hdr.Type);
		return;
	}
	if ((*dataPacketPtr).Payload.SensorType >= MAX_SENSOR_TYPES_CNT) {
		ULE_ERR_MSG("ULE received payload sensor type out of range ! %d %d \n",MAX_SENSOR_TYPES_CNT,(*dataPacketPtr).Payload.SensorType);
		return;
	}
	// MUTEXOBTAIN_semULEData; TODO : Should do some handling here
	secondCount = ULE_Get_Sys_Time();
	PP_Array[portId].RxBuff.RxDataBuff[PP_Array[portId].RxBuff.RxBufWritePos].DataPackTimeStmp = secondCount;
	PP_Array[portId].RxBuff.LatestEventData[(*dataPacketPtr).Payload.Hdr.Type].DataPackTimeStmp = secondCount;
	memset(&(PP_Array[portId].RxBuff.LatestEventData[(*dataPacketPtr).Payload.Hdr.Type].Payload.Hdr.Type),0,
			sizeof(MmiUlePdu_common_t)-1); // First clear old values
	memset(&(PP_Array[portId].RxBuff.RxDataBuff[PP_Array[portId].RxBuff.RxBufWritePos].Payload.Hdr.Type),0,
			sizeof(MmiUlePdu_common_t)-1); // First clear old values
	memcpy(&(PP_Array[portId].RxBuff.RxDataBuff[PP_Array[portId].RxBuff.RxBufWritePos].Payload.Hdr.Type),
			&((*dataPacketPtr).Payload.Hdr.Type), (*dataPacketPtr).Payload.Hdr.Length );
	memcpy(&(PP_Array[portId].RxBuff.LatestEventData[(*dataPacketPtr).Payload.Hdr.Type].Payload.Hdr.Type),
				&((*dataPacketPtr).Payload.Hdr.Type), (*dataPacketPtr).Payload.Hdr.Length);
	PP_Array[portId].RxBuff.RxDataBuff[PP_Array[portId].RxBuff.RxBufWritePos].Payload.Hdr.Length
				= (*dataPacketPtr).Payload.Hdr.Length;
	PP_Array[portId].RxBuff.LatestEventData[(*dataPacketPtr).Payload.Hdr.Type].Payload.Hdr.Length
			= (*dataPacketPtr).Payload.Hdr.Length;

	if ((PP_Array[portId].SensorType != MMI_SENSOR_TYPE_NONE) && (PP_Array[portId].SensorType
			!= (*dataPacketPtr).Payload.SensorType)) {
		ULE_PI_MSG("Warning: ULE sensor type suddenly changed !!\n");
	}
	PP_Array[portId].SensorType = (*dataPacketPtr).Payload.SensorType;


	PP_Array[portId].State.State = S_PP_ULE_ONLINE;
	PP_Array[portId].State.keepAlive = secondCount;

	PP_Array[portId].RxBuff.RcvPckID++;
	PP_Array[portId].RxBuff.RxDataBuff[PP_Array[portId].RxBuff.RxBufWritePos].DataPackId = PP_Array[portId].RxBuff.RcvPckID;
	PP_Array[portId].RxBuff.LatestEventData[(*dataPacketPtr).Payload.Hdr.Type].DataPackId = PP_Array[portId].RxBuff.RcvPckID;
	RcvPckt[WriteLoc].DatPckt = &(PP_Array[portId].RxBuff.RxDataBuff[PP_Array[portId].RxBuff.RxBufWritePos]);
	RcvPckt[WriteLoc].portID = portId;
	RcvPckt[WriteLoc].IsProccesed = FALSE;
	WriteLoc++;
	if ((WriteLoc % RCVPCKTSIZE) == 0) {
		WriteLoc = 0;
	}

	PP_Array[portId].RxBuff.RxBufWritePos++;
	if ((PP_Array[portId].RxBuff.RxBufWritePos % RX_BUFF_SIZE) == 0) {
		PP_Array[portId].RxBuff.RxBufWritePos = 0;
	}
	#ifndef DATA_LINK_TEST
		RAISEEVENT_RCVPCKT;
	#endif
	// MUTEXRELEASE_semULEData;
	return;
}

void ULE_RTS_Rcv(rsuint8 portId) {
	ULE_API_ENTRY

	ASSERT_PI_PORTID_INRANGE;

	if (fwsApiFpUleDtrInd(portId)) return;

	if(PP_Array[portId].TxBuff.TxShadowLen!=0){
				switchLed(DECT_LED0, 1);
				SendApiFpUleDataReq(API_TASK, (rsuint16)portId, PP_Array[portId].TxBuff.TxShadowPaging | ULP_DLC_CTRL_ACKNOWLEDGED, //,ULP_DLC_CTRL_UNACKNOWLEDGED
							PP_Array[portId].TxBuff.TxShadowLen,PP_Array[portId].TxBuff.TxShadowData);
				PP_Array[portId].TxBuff.TxShadowLen=0;
				printf(" Actuator send shadow!  \n");
	}else{
		if (portId < PP_COUNT_MAX) {
			PP_Array[portId].TxBuff.TxPacketStatus = Tx_Buff_Empty_TxSuccess;
		}
	}

#ifdef DATA_LINK_TEST
	SwitchData.Payload.Hdr.Type = MMI_DATA_TYPE_RFID;
	SwitchData.Payload.NextMess = FP_TXPASS[portId];
	SwitchData.Payload.SensorType = MMI_DATA_TYPE_RFID;
	SwitchData.Payload.Hdr.Length = DATA_LINK_TEST_PACKET_SIZE;
	SwitchData.Payload.Data[0] = 1;
	EarlyBit_t EarlyBit=EARLY_BIT_ON;
	SwitchData.Payload.Data[1] = portId;
	rsuint16 n;
	FP_TXPASS[portId]++;
	for (n=2;n<DATA_LINK_TEST_PACKET_SIZE;n++){
		SwitchData.Payload.Data[n] = n + portId;
	}
	ULE_Send_Data(portId, EarlyBit, &SwitchData);
#endif

}

void ULE_Data_reject(rsuint8 portId, RsStatusType Status) {
	ULE_API_ENTRY
	//MUTEXOBTAIN_semULEData;
	ASSERT_PI_PORTID_INRANGE;

	if(fwsApiFpUleDataRejectInd(portId,Status))return;

	if (portId < PP_COUNT_MAX) {
		//if (Status == RSS_SUCCESS) {
		PP_Array[portId].TxBuff.TxPacketStatus = Tx_Buff_Empty_TxRejected;
		//}
	}
	//MUTEXRELEASE_semULEData;
}


void ULE_InitTimer(void) {
	ULE_API_ENTRY
	ULE_SystemIsRunning = 1;
	int i;
	i = pthread_create(&TimerThreadId, NULL, ULE_TimerThread, NULL);
	if (i) {
		exit(1);
	}
	pthread_detach(TimerThreadId);

}

void ULE_InitRcvRcktThread(void) {
	ULE_API_ENTRY
	ULE_SystemIsRunning = 1;
	int k;
	rsuint8 i, j;

	for (i = 0; i < RCVPCKTSIZE; i++) {
		RcvPckt[i].IsProccesed = TRUE;
	}

	for (i = 0; i <= MAX_SENSOR_TYPES_CNT; i++) {
		for (j = 0; j <= MAX_DATA_TYPES_CNT; j++) {
			ULE_RegisterEventCallback(i, j, &ULE_EmptyEventHandler);
		}
	}

	k = pthread_create(&HandleRcvPckThreadId, NULL, ULE_HandleRcvRcktThread, NULL);
	if (k) {
		exit(1);
	}
	pthread_detach(HandleRcvPckThreadId);

}
void* ULE_HandleRcvRcktThread(void *x) {
	ULE_API_ENTRY

	(void)x; // unused
	rsuint8 ReadLoc = 0;

	do {
		CLEAREVENT_RCVPCKT;
		WAITEVENT_RCVPCKT;
		while (RcvPckt[ReadLoc].IsProccesed == FALSE) {
			ULE_Event_CallBack_Arr[(*RcvPckt[ReadLoc].DatPckt).Payload.SensorType][(*RcvPckt[ReadLoc].DatPckt).Payload.Hdr.Type](
					RcvPckt[ReadLoc].portID, RcvPckt[ReadLoc].DatPckt);

			ULE_Pck_Process_CallBack(RcvPckt[ReadLoc].portID, RcvPckt[ReadLoc].DatPckt);
			RcvPckt[ReadLoc].IsProccesed = TRUE;
			ReadLoc++;
			if ((ReadLoc % RCVPCKTSIZE) == 0) {
				ReadLoc = 0;
			}
		}

	} while (ULE_SystemIsRunning);

	return NULL;
}

UleErr_e ULE_RegisterWebReqCallback( cJSON* (*CallBack)(char *UserJSONstring)) {
	ULE_UserWebReqHandler_CallBack = CallBack;
	return ULE_Success;
}

UleErr_e ULE_RegisterEventCallback(rsuint8 sensor_type, rsuint8 data_type, void(*CallBack)(rsuint8 portId,
		DataPacket_t *dataPacketPtr)) {
	//ULE_API_ENTRY

	if (sensor_type > MAX_SENSOR_TYPES_CNT)
		return ULE_SensortypeoutOfRange;
	if (data_type > MAX_DATA_TYPES_CNT)
		return ULE_DatatypeoutOfRange;

	if ((sensor_type == ANY_SENSOR_TYPE) || (data_type == ANY_DATA_TYPE)) {
		ULE_Pck_Process_CallBack = CallBack;
		return ULE_Success;
	}

	ULE_Event_CallBack_Arr[sensor_type][data_type] = CallBack;

	return ULE_Success;
}

void ULE_DefaultDectHandler(unsigned char *MailPtr ) {
	ULE_ERR_MSG("ULE PI got a message which is not handled! %X %X %X %X %X %X %X %X %X %X \n ",
			MailPtr[0], MailPtr[1] , MailPtr[2] , MailPtr[3] , MailPtr[4] ,
			 MailPtr[5] , MailPtr[6] , MailPtr[7] , MailPtr[8] , MailPtr[9] );
}

void ULE_EmptyEventHandler(rsuint8 portId, DataPacket_t *dataPacketPtr) {
ULE_API_ENTRY}


#ifdef HANFUN
/*
 *  Extra functions used by the Hanfun WebInterface Unit
 */
rsuint8 ULE_Set_PP_Status(rsuint8 portId, rsuint8 status) {
	ULE_API_ENTRY	ASSERT_ULE_INIT_SUCCESS;
	ASSERT_ULE_PORTID_INRANGE;

	MUTEXOBTAIN_semULEData;
	PP_Array[portId].State.State = (rsuint8) status;
	MUTEXRELEASE_semULEData;
	return (rsuint8) ULE_Success;
}


rsuint8 ULE_Set_PP_SensorType(rsuint8 portId, rsuint8 sensType) {
	ULE_API_ENTRY	ASSERT_ULE_INIT_SUCCESS;
	ASSERT_ULE_PORTID_INRANGE;

	MUTEXOBTAIN_semULEData;
	PP_Array[portId].SensorType = (MmiUleSensHdr_t) sensType;
	MUTEXRELEASE_semULEData;
	return (rsuint8) ULE_Success;

}


rsuint8 ULE_Update_PP_KeepAlive(rsuint8 portId) {
	ULE_API_ENTRY	ASSERT_ULE_INIT_SUCCESS;
	ASSERT_ULE_PORTID_INRANGE;

	MUTEXOBTAIN_semULEData;
	PP_Array[portId].State.State = S_PP_ULE_ONLINE;
	PP_Array[portId].State.keepAlive = ULE_Get_Sys_Time();
	MUTEXRELEASE_semULEData;
	return (rsuint8) ULE_Success;

}

#endif


#ifdef POWERPLUG_CYCLE_TEST
// void Reset_Smartplug_MinMax_Values(rsuint8 portid) {
// 	// If portId == 0, reset every Smartplug values
// 	rsuint8 i;

// 	if (portid > 0) {
// 		ULE_Set_PP_Attribute(portid, SWITCH_MIN_WATT, 50000000);
// 		ULE_Set_PP_Attribute(portid, SWITCH_MAX_WATT, 0);
// 	} else {
// 		// reset values for every smartplug
// 		for (i=0; i < PP_COUNT_MAX; i++) {
// 			if ((PP_Array[i].State.State != S_PP_NOT_REGISTERED) && (PP_Array[i].SensorType == MMI_ACTUATOR_TYPE_SWITCH_220)) {
// 				ULE_Set_PP_Attribute(i, SWITCH_MIN_WATT, 50000000);
// 				ULE_Set_PP_Attribute(i, SWITCH_MAX_WATT, 0);
// 			}
// 		}
// 	}
// }



// void SetActuatorTimer(rsuint8 ppId, rsuint8 timeout) {

// 	// Set Actuator Timer
// 	DataPacket_t TimerData;
// 	TimerData.Payload.Hdr.Type = 0x18;//MMI_DATA_TYPE_SWITCH_220;
// 	TimerData.Payload.NextMess = 0;
// 	TimerData.Payload.SensorType = PP_Array[ppId].SensorType;// sensor_tp;
// 	TimerData.Payload.Hdr.Length = 6;
// 	TimerData.Payload.Data[0] = timeout; //Timeout to set on PP
// 	TimerData.Payload.Data[1] = 0;
// 	TimerData.Payload.Data[2] = 0;

// 	ULE_Send_Data(ppId, 1, &TimerData);
// 	PRINT_MESSAGE("Setting Actuator Timer to %d sec...\n", timeout);

// }

// rsbool setSmartplugTimer = FALSE;
// static rsuint8 cycleTestPhase = 0;

#endif

#ifdef HANFUN
static rsuint16 keepAliveCheckTimer = 0;
// FIX: this was lowered to 60 to work aroung HF_Light report back issue
#define KEEP_ALIVE_CHECK_SEC	60 // Was 300
#endif


void *ULE_TimerThread(void *x) {

	ULE_API_ENTRY

	(void)x; // unused
	rsuint16 i;
	rsuint32 secondCount;
	//DataPacket_t Packet;
	rsuint8  RegDev, MaxDevices;

	sys_usleep(5000);
#ifdef POWERPLUG_CYCLE_TEST
	rsuint32 amp_new=0;
#endif
#ifdef CRON_SUPPORT
	char cron_cmd=0;
	DataPacket_t SwitchData;
	rsuint32 latestdat;
#endif
	while (ULE_SystemIsRunning) {

		sys_sleep(1);

		TxBuff_Send();

		switchLed(DECT_LED0, 0); // Switch OFF Rx/Tx LED
		secondCount = ULE_Get_Sys_Time();

		if (sysInfoDb.registrationMode_timeout>0){
				sysInfoDb.registrationMode_timeout --;
				if (sysInfoDb.registrationMode_timeout==0){
					ULE_Disable_Registration();
					PRINT_MESSAGE("########### TIMER CHECK Disable_Registration ########## \n");
				}
			}

		if ((secondCount % CHECK_PERIOD) != 0) {
			continue;
		}


		if (deregisterAllUpdateTimer > 0) {
			deregisterAllUpdateTimer--;
			if (deregisterAllUpdateTimer == 0){
				ULE_Get_Registration_Count(&RegDev,&MaxDevices);
			}

		}

#ifdef HANFUN
		// Request a report-back from every registered PP
		if (keepAliveCheckTimer++ >= KEEP_ALIVE_CHECK_SEC) {
			keepAliveCheckTimer = 0;
			for (i = 0; i < PP_COUNT_MAX; i++) {
				if (PP_Array[i].State.State != S_PP_NOT_REGISTERED) {
					// WebInterface_request_device_core_info(i);
				}
			}
		}
#endif

		for (i = 0; i < PP_COUNT_MAX; i++) {

			if(PP_Array[i].FWS.LivenessTimer!=0)
			{
				PP_Array[i].FWS.LivenessTimer--;
				if (PP_Array[i].FWS.LivenessTimer!=0) continue;
				switch (PP_Array[i].FWS.State)
				{
					case FWSS_XFER_STARTED:
						fwsSendAbort(i);
						break;

					default:
//						PRINT_MESSAGE( "PortId %d : fwsLivenessTimerCb timeout %i secs passed!", i,FWS_LIVENESS_TIMEOUT_SECS);
						break;
				}
			}


			if ((PP_Array[i].State.State == S_PP_ULE_ONLINE) && ((secondCount - PP_Array[i].State.keepAlive)
					> PP_Array[i].State.timeoutStatusValue)) {
				PP_Array[i].State.State = S_PP_ULE_OFFLINE;
				PRINT_MESSAGE("########### TIMER CHECK set OFFLINE portID: %d ########## \n", i);
			}
			if ((PP_Array[i].TxBuff.TxtimeoutStatusValue != 0)&& (PP_Array[i].TxBuff.TxPacketStatus == Tx_Buff_Full)
					&& ((secondCount - PP_Array[i].TxBuff.TxkeepAlive)> PP_Array[i].TxBuff.TxtimeoutStatusValue)) {
				ULE_TxAbort(i);
			}
#ifdef CRON_SUPPORT

			if (PP_Array[i].State.State == S_PP_ULE_ONLINE)
				cron_cmd=get_cron_switch_mode(i);

			if (cron_cmd && (PP_Array[i].State.State == S_PP_ULE_ONLINE) &&
					((PP_Array[i].SensorType == MMI_ACTUATOR_TYPE_SWITCH_220)|| (PP_Array[i].SensorType == MMI_ACTUATOR_TYPE_GENERIC)) ){
				//Create packet for switch
				SwitchData.Payload.Hdr.Type = MMI_DATA_TYPE_SWITCH_220;
				SwitchData.Payload.NextMess = 0;
				SwitchData.Payload.SensorType = PP_Array[i].SensorType;;
				SwitchData.Payload.Hdr.Length = 6;
				SwitchData.Payload.Data[0] = 1;

				if (cron_cmd == 1) {
					latestdat = 1;
				}
				else if (cron_cmd == -1){
					latestdat = 0;
				}
				SwitchData.Payload.Data[1] = (rsuint8) latestdat;
				SwitchData.Payload.Data[2] = 0;

				ULE_Send_Data(i, 1, &SwitchData);
				PRINT_MESSAGE("CRON TOGGLE actuator switch: %d (state: %d) \n", i,latestdat );
			}
#endif
#ifdef	POWERPLUG_CYCLE_TEST
			// if (PP_Array[i].State.State == S_PP_ULE_ONLINE){
			// 	/*Start the test*/
			// 	if((PP_Array[i].State.timeoutPowerCycle == 0)){


			// 		if (timeoutPowerCycle_default) {
			// 		PP_Array[i].State.timeoutPowerCycle=timeoutPowerCycle_default;
			// 		PP_Array[i].State.amp=0xFFFFFFFF;//Invalid value for getting the first measurement
			// 		PP_Array[i].State.cycle_cnt=0;


			// 			SetActuatorTimer(i, 0xFF); // Disable Actuator Timer(0xFF = disable)

			// 		} else if (setSmartplugTimer){
			// 			SetActuatorTimer(i, 0x05); // Reset Actuator Timer to default (5sec)
			// 			setSmartplugTimer = FALSE;
			// 		}
			// 		//cycleTestPhase = 0;

			// 	}
			// 	/*Test in progress*/
			// 	if (PP_Array[i].State.timeoutPowerCycle > 0){
			// 		PP_Array[i].State.timeoutPowerCycle--;
			// 		if(PP_Array[i].State.timeoutPowerCycle == 0){

			// 			if (++cycleTestPhase == 1) {
			// 			PRINT_MESSAGE("########### TIMER CHECK set POWER CYCLE portID: %d, cycle counter = %d ########## \n", i,(int) PP_Array[i].State.cycle_cnt);
			// 					PP_Array[i].State.cycle_cnt++;
			// 			}

			// 			{
			// 				//PP_Array[i].State.timeoutPowerCycle = timeoutPowerCycle_default;
			// 				//ULE_Get_PP_Attribute(i, CURRENT_ATTR, &amp_new);

			// 				//Create packet for switch
			// 				DataPacket_t SwitchData2;
			// 				rsuint32 latestdat;
			// 				//rsuint32 ampToCheck;

			// 				SwitchData2.Payload.Hdr.Type = 0x31;//MMI_DATA_TYPE_SWITCH_220;
			// 				SwitchData2.Payload.NextMess = 0;
			// 				SwitchData2.Payload.SensorType = PP_Array[i].SensorType;// sensor_tp;
			// 				SwitchData2.Payload.Hdr.Length = 6;
			// 				SwitchData2.Payload.Data[0] = 1;
			// 				ULE_Get_PP_Attribute(i, POWER_SWITCH_ATTR, &latestdat);
			// 				if (latestdat == 0) {
			// 					latestdat = 1; // next switch ON
			// 				} else {
			// 					latestdat = 0; // next switch OFF
			// 				}

			// 				SwitchData2.Payload.Data[1] = (rsuint8) latestdat;
			// 				SwitchData2.Payload.Data[2] = 0;

			// 				ULE_Send_Data(i, latestdat, &SwitchData2);
			// 				PRINT_MESSAGE("TOGGLE actuator switch: %d (state: %d) \n",(int) i, (int)latestdat )

			// 				PP_Array[i].State.timeoutPowerCycle = timeoutPowerCycle_default;
			// 				ULE_Get_PP_Attribute(i, CURRENT_ATTR, &amp_new);

			// 				/*Check current measurement. If first measurement skip. Else fail if 2 subsequent measurements are both 0 or non-zero*/
			// 				if(PP_Array[i].State.amp==0xFFFFFFFF){
			// 					PP_Array[i].State.amp=amp_new;
			// 				}
			// 				else{

			// 					//PRINT_MESSAGE("\r\n AMP: %d, AMP_NEW: %d, STATE: %d \r\n", PP_Array[i].State.amp, amp_new, latestdat);
			// 					//if((PP_Array[i].State.amp && latestdat) || (!PP_Array[i].State.amp && !latestdat))
			// 					if((amp_new && latestdat) || (!amp_new && !latestdat))
			// 					{
			// 						//								fail++;
			// 						//							if(fail){
			// 						PRINT_MESSAGE("============ POWER CYCLE FAILED !!!! ============== \nPrevious current measured = %d, Last current measured = %d \n",(int)PP_Array[i].State.amp,(int) amp_new );
			// 						/*Stop test*/
			// 						PP_Array[i].State.timeoutPowerCycle = timeoutPowerCycle_default = 0;
			// 						setSmartplugTimer = TRUE;

			// 					}
			// 					else {
			// 						PP_Array[i].State.amp=amp_new;
			// 				}


			// 				}

			// 			}
			// 			if (cycleTestPhase == 2) cycleTestPhase = 0;
			// 		}

			// 		if(PP_Array[i].State.timeoutPowerCycle == 5){
			// 			// Send a dummy packet to receive updated measurements
			// 			DataPacket_t DummyData;

			// 			DummyData.Payload.Hdr.Type = 0x00;//MMI_DATA_TYPE_NONE;
			// 			DummyData.Payload.NextMess = 0;
			// 			DummyData.Payload.SensorType = PP_Array[i].SensorType;// sensor_tp;
			// 			DummyData.Payload.Hdr.Length = 4;
			// 			DummyData.Payload.Data[0] = 0;
			// 			PRINT_MESSAGE("Sending Dummy Packet to Powerplug...\n");
			// 			ULE_Send_Data(i, latestdat, &DummyData);

			// 		}

			// 	}
			// }
#endif

		} // end of for loop
	} // end of while

	return NULL;
}

