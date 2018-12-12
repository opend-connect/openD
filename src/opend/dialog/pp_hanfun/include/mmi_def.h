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

/****************************************************************************
* Includes
****************************************************************************/
#ifndef MMI_DEF_H
#define MMI_DEF_H

#include <stdint.h>
#include <stdbool.h>

#include <Core/RtxCore.h>
#include <Ros/RosCfg.h>
#include <Cola/Cola.h>
#include <ProjCfg.h>
#include <PortDef.h>
#include <RtxEai/RtxEaiCfg.h>

#include <Phoenix/Api/Api.h>
#include <Phoenix/Api/PpUle/ApiPpUle.h>
#include <Phoenix/Api/PpMm/ApiPpMm.h>
#include <Api/ApiPpProject.h>

#include <Phoenix/Api/FpFwu/ApiFwsMps.h>
#include <Phoenix/Api/Types/ApiTypes.h>
#include <Phoenix/Api/ProdTest/ApiProdTest.h>

#include <Phoenix/Api/HAL/ApiHalMps.h>

#include "MmiFpPpCommon.h"
#include "fws.h"
#include "PtCmdDef.h"
#include "git_version.h"


#define ACTUATOR
#define EMULATE_ROS_TIMERS


#if defined(HF_SIMPLE_LIGHT) || defined(HF_AC_OUTLET) || defined(HF_SIMPLE_SWITCH)
#define HANFUN
#define HANFUN_MESSAGE DUMMY_DATA
#endif


#define MMI_SUBSCRIPTION     1

// Initial sleep time and port configuration for sensors [s]
#if defined(BATTERY_ACTUATOR) || defined(TEMP_SENSOR)
#define INITIAL_SLEEP_TIME 10
#else
#define INITIAL_SLEEP_TIME 30
#endif

#define MIN_LOCK_TIMEOUT     5000  // 150 ms
#define DEFAULT_LOCK_TIMEOUT 5000  // 800 ms
#define DEFAULT_LR_TIMEOUT   15000  // 800 ms

#define T_MMI_WAIT_LOCK  ( MmiCtrl.nvs.lock_timeout * RS_T1MS )
#define T_MMI_WAIT_LR  ( MmiCtrl.nvs.lr_timeout * RS_T1MS )


#define ON 1
#define OFF 0

#define NVS_USER_LEN 100

#define ACCESS_CODE 0x0000
#define HF_OFFSET    7


typedef enum RSENUMTAG(ApiPpDelaySleep_t) {
	DELAYSLEEP_IDLE,
	DELAYSLEEP_CHECK,
	DELAYSLEEP_REENABLE,
	DELAYSLEEP_RESERVED,
	DELAYSLEEP_REGISTERDELAY,
}RSENUM8(ApiPpDelaySleep_t);

//#define NVS_USER_LEN 			10	// Length of User Task NVS data
#define NVS_ACT_CNT_LEN			6	// Length of ActivityCounter data
#define NVS_USR_BASE			0x700								// Base for all user Read/Writes
#define NVS_USR_SMARTPLUG_BASE	(NVS_USR_BASE + 20)					// Base for Smartplug area (0x714)
#ifdef DYNAMIC_ACTIVITY_COUNTERS
#define NVS_USR_ACT_CNT_BASE	(NVS_USR_BASE + NVS_USER_LEN + 2)	// Base for ActivityCounters (0x70C)
#define ACTCNT_CHCKPAGE_LSB	0
#define ACTCNT_CHCKPAGE_MSB	1
#define ACTCNT_STARTAPP_LSB	2
#define ACTCNT_STARTAPP_MSB	3
#define ACTCNT_KEEPALIV_LSB	4
#define ACTCNT_KEEPALIV_MSB	5
#endif


#ifdef HANFUN
typedef enum RSENUMTAG(ApiPpAppMsg_t) {
	HANFUN_INIT,
	HANFUN_RECEIVE,
	HANFUN_CONNECT,
	HANFUN_CONNECT_COMPLETE,
	HANFUN_NVS_SET,
	HANFUN_NVS_SAVE,
	HANFUN_SMARTPLUG_MSR,
	HANFUN_SMARTPLUG_INTERVAL,
	HANFUN_SMARTPLUG_PERIODIC,
	HANFUN_SWITCH_TOGGLE,
	HANFUN_AC_TOGGLE,
	HANFUN_AC_ON,
	HANFUN_AC_OFF,
	HANFUN_REG_COMPLETE,
	HANFUN_DETECTOR_ALERT,
} RSENUM8 (ApiPpAppMsg_t);

typedef enum RSENUMTAG(ApiPpType_t) {
	HANFUN_SENSOR,
	HANFUN_LIGHT,
	HANFUN_SMARTPLUG,
	HANFUN_REED,
} RSENUM8 (ApiPpType_t);

void ColaMail(ApiPpAppMsg_t A1);
void ColaMailPtr(ApiPpAppMsg_t A1, rsuint32 Addr);

#endif

typedef struct __attribute__ ((__packed__)) UlePdu {
	rsuint8 dev_id;
	rsuint16 size;
	rsuint8 data[];
} UlePdu;

typedef struct ApiPpUleHanfunSmartMeasureType {
	rsuint32 voltage;
	rsuint32 current;
	rsuint32 power;
	rsuint32 energy;
} ApiPpUleHanfunSmartMeasureType;

typedef struct {
  rsuint8 region;
  ApiPpUlePortDirMode_t PortDirMode;
  ApiPpUlePortTrigMode_t PortTrigMode;
  rsuint16 sleep_time; // in seconds
  rsuint16 lock_timeout;
  rsuint16 lr_timeout;
  rsuint16 tx_latency;
  rsuint16 sync_time;
  rsuint8 rssi;
  rsuint8 UserData[NVS_USER_LEN];
#ifdef DYNAMIC_ACTIVITY_COUNTERS
  ApiPpUleActivityCounters_t ActvtCounters;
#endif
} MmiNvsData_t;



// MMI control data structure
typedef struct {
  MmiNvsData_t              nvs;
  rsuint8					hanfun_address;
  rsuint8					hanfun_registered;
  rsuint8 					nvsReady;
  rsuint32                  awake_time;
  RsPerformanceTickType     inittask_timestamp;
  RsPerformanceTickType     tx_start;
  rsuint8				    AccessCode[4];
  rsuint8 					UleReadyReceived;
  rsuint8 					islocked;
  rsuint8 					isRegistered;
  rsbool 					RegistrationMode;
  rsuint8 					PendTDR;
  rsuint8					pageAck;
  rsuint8 					pagingInitiated;
  ApiPpUleWakeupEventType_t wakeup_event;
  rsuint8 					ulpPort;
  rsuint8 					led6;
  rsuint8 					led7;
  rsuint8 					pvc;
  rsuint8 					delaysleep;
  rsuint16					StackVersion;
  rsuint16					Primitive;
  MmiFWS_t					FWS;
#ifdef SENSOR_RSSI_MEASURE
  rsbool					pendDelayedRssi;
#endif
  ApiPpUleActivityStatus_t  activity_status;
  rsuint16					activity_resume_counter;
} MmiCtrl_t;

extern MmiCtrl_t MmiCtrl;


/****************************************************************************
* Function prototypes
****************************************************************************/
void MmiInit(void);
void PagingMode(rsuint8 Enable);
void GoToSleep();
void Enable_Sleep();	// Should be defined in application
void Disable_Sleep();	// Should be defined in application
void Enable_Registration(rsuint16 AccessCode);
void SetWakeUpSetting(ApiPpUlePortDirMode_t PortDirMode,
		ApiPpUlePortTrigMode_t PortTrigMode, rsuint16 sleep_time);

// function definition to send data
void Sleep(rsuint8 txstatus);
void ColaTask(const RosMailType* p_mail);
void UserTask(const RosMailType* p_mail);
void RtxTask(const RosMailType* p_mail);
void HanfunTask(const RosMailType* p_mail);
void UserAppOnlyTask(void);

void SetLED3(bool led_on);
void SetLED4(bool led_on);

void mmiRosTimerEmu_Init(void);
void mmi_SoftResetModule(void);

void hanfun_state_machine(const RosMailType* p_mail);

#ifdef DYNAMIC_ACTIVITY_COUNTERS
void SaveActivityCountersToNvs(ApiPpUleActivityCounters_t *actvt_cnt);
#endif

#endif
