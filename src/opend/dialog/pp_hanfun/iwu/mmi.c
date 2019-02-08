/*
 * Copyright (c) by RTX A/S, Denmark
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of RTX A/S nor the names of its contributors
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

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


#include "log.h"
#include "hdlc.h"
#include "opend_ll_serial.h"
#include "mmi_def.h"

#ifndef HANFUN
// FIXME: Defining with HanFun application creates SegFault at some point
// 		  This is mainly observed on linux
#define DEBUG_MMI_MSG
#endif

#ifdef DEBUG_MMI_MSG
/* For Debugging */
# include "enum_to_string.h"
# include "RosPrimitivDebug.h"

# define GENERATE_ENUM_STRINGS
# include "RosPrimitivDebug.h"
# undef GENERATE_ENUM_STRING
#endif



MmiCtrl_t MmiCtrl;
uint8_t j,k;
static struct _state
{
      uint8_t going_to_sleep : 1;
      uint8_t doing_init : 1;
      uint8_t is_booted  : 1;
      uint8_t reserved   : 5;

      uint32_t sync_time;

} g_state = { .going_to_sleep = 0, .doing_init = 1, .is_booted = 0 };


// Activity counters used to control what will happen during ULE resume cycle
//  CheckPage:  QuickSearch checks for pageing and suspend again immediately if not paged
//  StartApp:   Application is called with MAC layer disabled
//  KeepAlive:  No QS page check and MAC is enabled (Normal startup)
// If ResumeCounter modulus ActivityCounter is zero then the activity is enabled
// In case more than one activity is enabled the priority is: KeepAlive, Checkpage, and StartApp
// This means that:
//  If KeepAlive is enabled then the Keep alive cycle is started
//  If both CheckPage and StartApp is activated then QS will check for paging and if not paged,
//  disable the MAC layer before starting the Application
// If no activity is selected the keep alive cycle is started
// The ActivityCounters is part of the API_PP_ULE_INIT_REQ mail send by SendApiPpUleInitReq
#ifdef HANFUN
# ifdef BATTERY_ACTUATOR
static ApiPpUleActivityCounters_t MmiActivityCounters = {.CheckPage=1, .StartApp=1, .KeepAlive=0};
# else
static ApiPpUleActivityCounters_t MmiActivityCounters = {.CheckPage=0, .StartApp=0, .KeepAlive=1};
# endif
#endif

uint16_t TimerCtrlVal;


/****************************************************************************
 * MMI Timers
 ****************************************************************************/

static const RosTimerConfigType MmiStateTimerConfig = ROSTIMER(COLA_TASK, MMI_STATE_TIMEOUT_ind, MMI_STATE_TIMER);

const RosTimerConfigType LockTimeoutTimerConfig = { COLA_TASK, { TIMEOUT, LOCK_TIMER } };

const RosTimerConfigType LocateRegTimerConfig = { COLA_TASK, { TIMEOUT, LR_TIMER } };

const RosTimerConfigType ComeBackRegTimerConfig = { COLA_TASK, { TIMEOUT, DUMMY_MESSAGE_TIMER } };




uint32_t setupagaintimer = 2000;
uint8_t is_setup_again = 0;

static void ResetPvcConfig(void)
{
	// Start PVC configuration
	MmiCtrl.pvc = 1;
	if (1) {
		SendApiPpUlePvcConfigReq(API_PP_ULE_APP_TASK, 0, 0, 0, 0, 0, 0, 0, API_ULE_PP_INITIATOR);
	} else {
		SendApiPpUlePvcConfigReq(COLA_TASK, API_ULE_PROTOCOL_FUN_1, API_ULE_PROTOCOL_VERSION_0,
									0, API_ULE_MTU_SIZE_DEFAULT, API_ULE_MTU_SIZE_DEFAULT,
									API_ULE_MTU_LIFETIME_DEFAULT, API_ULE_WINDOW_SIZE_DEFAULT, API_ULE_PP_INITIATOR);
	}
	// Clear configuration flag
}


#ifdef DYNAMIC_ACTIVITY_COUNTERS

/* This is a custom INITTASK to be sent in case of delayed init execution */
void mmi_ColaMail_InitTask () {
	RosMailType* pm = RosMailAllocate(COLA_TASK, COLA_TASK, sizeof(RosMailP2Type));
	pm->Primitive = INITTASK;
	pm->P2.P1 = 0xDE;
	pm->P2.P2 = 0xAD;
	RosMailDeliver(pm);
}

/* Check if the INITTASK p_mail is the one from mmi_ColaMail_InitTask */
rsbool mmi_ColaMail_CheckCustomInit ( const RosMailType* p_mail ) {
	return ((p_mail->P2.P1 == 0xDE) && (p_mail->P2.P2 == 0xAD));
}

/* Just an SendApiHalWriteReq wrapper */
void SaveActivityCountersToNvs (ApiPpUleActivityCounters_t *in_counters) {

	MmiCtrl.nvs.ActvtCounters.CheckPage = in_counters->CheckPage;
	MmiCtrl.nvs.ActvtCounters.StartApp  = in_counters->StartApp;
	MmiCtrl.nvs.ActvtCounters.KeepAlive = in_counters->KeepAlive;
	SendApiHalWriteReq(COLA_TASK, AHA_NVS, NVS_USR_ACT_CNT_BASE, NVS_ACT_CNT_LEN, (uint8_t*) &(MmiCtrl.nvs.ActvtCounters));
}
#endif /* DYNAMIC_ACTIVITY_COUNTERS */


RosMailType *RosMailAllocate(RosTaskIdType uProgramId, RosTaskIdType uTaskId, RosMailSizeType u16Size)
{
	uint8_t *bConPtr;
	bConPtr = (uint8_t *)malloc(u16Size+5); // 2: u16Size, 1: infohdr, 1: uProgramId, 1: uTaskId
	if(!bConPtr){
		printf("Inside %s MALLOC FAILED  !!!!!!!!!!!!!!!!! \n\n\n\n", __FUNCTION__);
		while(1);
	}
	*bConPtr 	 = (uint8_t) ((u16Size&0xff00)>>8);
	*(bConPtr+1) = (uint8_t) (u16Size&0x00ff);
	*(bConPtr+2) = 0;
	*(bConPtr+3) = uProgramId;
	*(bConPtr+4) = uTaskId;

	return (RosMailType*)(bConPtr+5);
}

void RosMailDeliver(RosMailType *Mail)
{

	uint8_t* bConPtr	= (uint8_t*)Mail-5;
	uint8_t  ConTask 	= (uint8_t) *(bConPtr+4);
	uint16_t ConLength 	= (uint16_t) (*(bConPtr)*256+*(bConPtr+1));

	hdlc_infoFrameCreate( ConTask, (uint8_t *) Mail, ConLength );

	free(bConPtr);
}



#ifdef EMULATE_ROS_TIMERS
/*
 * Emulate RosTimerStart/RosTimerStop by using posix timer_create functionality
 */

#define MMI_ROS_TIMER_MAX_TIMERS 10

typedef struct mmiRosTimerEmu_Timer {
	RosTimerIdType timerId;
	RsTimerTickType timerValue;
	RosPrimitiveType timerConfigPrim;
	RosTimerParameterType timerConfigParam;
	timer_t timerIdInternal;
	bool enabled;
} mmiRosTimerEmu_Timer_T ;

struct mmiRosTimerEmu_Timer* mmiRosTimerEmu_Timer_Array[MMI_ROS_TIMER_MAX_TIMERS];


void mmiRosTimerEmu_Init() {

	uint8_t i;

	for (i=0; i<MMI_ROS_TIMER_MAX_TIMERS; i++) {
		mmiRosTimerEmu_Timer_Array[i] = malloc(sizeof(mmiRosTimerEmu_Timer_T));
		mmiRosTimerEmu_Timer_Array[i]->timerId = 0;
	}

}

//TODO: commended nucleo port
// static void mmiRosTimerEmu_TimerHandler( int sig, siginfo_t *si, void *uc )
// {
// 	timer_t *tidp;
// 	tidp = si->si_value.sival_ptr;
// 	uint8_t  i;

// 	for (i=0; i<MMI_ROS_TIMER_MAX_TIMERS; i++) {
// 		if ( mmiRosTimerEmu_Timer_Array[i]->enabled &&
// 				mmiRosTimerEmu_Timer_Array[i]->timerIdInternal == *tidp ) {

// 			//printf("[%s] TICKED ID:%04X PAR:%04X\n ", __FUNCTION__, mmiRosTimerEmu_Timer_Array[i]->timerId,
// 			//		mmiRosTimerEmu_Timer_Array[i]->timerConfigParam);

// 			RosMailTimeoutType* my_timeout = (RosMailTimeoutType*) RosMailAllocate(COLA_TASK,
// 																					COLA_TASK, sizeof(RosMailTimeoutType));

// 			my_timeout->Primitive = mmiRosTimerEmu_Timer_Array[i]->timerConfigPrim;
// 			my_timeout->Parameter = mmiRosTimerEmu_Timer_Array[i]->timerConfigParam;

// 			ColaTask((RosMailType*) my_timeout);
// 			return;
// 		}

// 	}
// }


static int mmiRosTimerEmu_SetTimer( timer_t *timer_id, int expire_ms, int interval_ms ) {

//TODO: commended nucleo port
	// struct itimerspec its;
	int errornum = 0;

	// its.it_interval.tv_sec = interval_ms / 1000;
	// its.it_interval.tv_nsec = (interval_ms % 1000) * 1000000;
	// its.it_value.tv_sec = expire_ms / 1000;
	// its.it_value.tv_nsec = (expire_ms % 1000) * 1000000;
	// if (timer_settime(*timer_id, 0, &its, NULL))
	// 	errornum = errno;

	return errornum;
}


static int mmiRosTimerEmu_CreateTimer(timer_t *timer_id, int expire_ms, int interval_ms )
{

//TODO: commended nucleo port

// 	struct sigevent         te;
// 	struct itimerspec       its;
// 	struct sigaction        sa;
//  ;

// 	/* Set up signal handler. */
// 	sa.sa_flags = SA_SIGINFO;
// 	sa.sa_sigaction = mmiRosTimerEmu_TimerHandler;
// 	sigemptyset(&sa.sa_mask);
// 	if (sigaction(SIGRTMIN, &sa, NULL) == -1)
// 	{
// 		printf("%s: Failed to setup signal handling for\n", __FUNCTION__);
// 		return(-1);
// 	}

// 	/* Set and enable alarm */
// 	te.sigev_notify = SIGEV_SIGNAL;
// 	te.sigev_signo = SIGRTMIN;
// 	te.sigev_value.sival_ptr = timer_id;
// 	timer_create(CLOCK_REALTIME, &te, timer_id);

// 	its.it_interval.tv_sec = interval_ms / 1000;
// 	its.it_interval.tv_nsec = (interval_ms % 1000) * 1000000;
// 	its.it_value.tv_sec = expire_ms / 1000;
// 	its.it_value.tv_nsec = (expire_ms % 1000) * 1000000;
// 	timer_settime(*timer_id, 0, &its, NULL);

	return(0);
}


void RosTimerStart(RosTimerIdType TimerId, RsTimerTickType Value, const RosTimerConfigType* Config)
{
	uint8_t i;
	bool found = false;

//	printf("\r\n"
//			"#######################################################################\n"
//			"###  [%s] START TIMER: %04X FOR %ld MS\n"
//			"#######################################################################\r\n",
//			__FUNCTION__, TimerId, Value);


	/* Check if timer exists */
	for (i=0; i<MMI_ROS_TIMER_MAX_TIMERS; i++) {

		if (mmiRosTimerEmu_Timer_Array[i]->timerId == TimerId) {
			found = true;
			if (!mmiRosTimerEmu_Timer_Array[i]->enabled)
				mmiRosTimerEmu_Timer_Array[i]->enabled = true;

			mmiRosTimerEmu_Timer_Array[i]->timerValue = Value;
			// Arm old timer
			mmiRosTimerEmu_SetTimer(&mmiRosTimerEmu_Timer_Array[i]->timerIdInternal, Value, Value);
			return;
		}
	}

	if (!found) {
		i = 0;
		while ( mmiRosTimerEmu_Timer_Array[i]->timerId != 0) {
			i++;
			if (i>=MMI_ROS_TIMER_MAX_TIMERS) {
				printf("\n#### CANNOT CREATE MORE TIMERS!!! ####\n");
				return;
			}
		}

		// add timer
		mmiRosTimerEmu_Timer_Array[i]->timerId = TimerId;
		mmiRosTimerEmu_Timer_Array[i]->timerValue = Value;
		mmiRosTimerEmu_Timer_Array[i]->timerConfigPrim = Config->Mail.Primitive;
		mmiRosTimerEmu_Timer_Array[i]->timerConfigParam = Config->Mail.Parameter;
		mmiRosTimerEmu_Timer_Array[i]->enabled = true;
		mmiRosTimerEmu_CreateTimer(&mmiRosTimerEmu_Timer_Array[i]->timerIdInternal, Value, Value);

	}

}


void RosTimerStop(RosTimerIdType TimerId)
{
	uint8_t i;

//	printf("\r\n"
//			"#######################################################################\n"
//			"###  [%s] STOP TIMER: %04X \n"
//			"#######################################################################\r\n",
//			__FUNCTION__, TimerId);

	for (i=0; i<MMI_ROS_TIMER_MAX_TIMERS; i++) {

		if (mmiRosTimerEmu_Timer_Array[i]->timerId == TimerId) {
			if (mmiRosTimerEmu_Timer_Array[i]->enabled) {
				mmiRosTimerEmu_Timer_Array[i]->enabled = false;
			}
			// Disarm timer
			mmiRosTimerEmu_SetTimer(&mmiRosTimerEmu_Timer_Array[i]->timerIdInternal, 0, 0);

		}
	}
}

#endif /* EMULATER_ROS_TIMERS */


void mmi_SoftResetModule(void) {
	SendApiProdTestReq(COLA_TASK, PT_CMD_SW_RESET, 0, NULL);
}

void mmi_SetModuleNvsDefault(void) {
    uint8_t params = 1;
    SendApiProdTestReq(COLA_TASK, PT_CMD_NVS_DEFAULT, 1, &params);
}

void mmi_SetModuleDectModeEU(void) {
    uint8_t eu_diviation = 0x25;
    uint8_t dect_reg = 0;
    SendApiHalWriteReq(COLA_TASK, AHA_NVS, 0x5, 1, &eu_diviation);
    SendApiProdTestReq(COLA_TASK, PT_CMD_SET_DECT_MODE, 1, &dect_reg);
}

//static bool initOneTime = false;
static void s_mmi_default(const RosMailType* p_mail)
/*************************************************************************
 *
 **************************************************************************/
{

	switch (p_mail->Primitive) {

	/*************************************************************************
	 * General
	 **************************************************************************/
	case 0xF0F4:	/* RTX_EAP_TARGET_RESET_IND */
        if(MmiCtrl.isRegistered)
		{
		  break;
		}
		//no break
	case INITTASK:
      {
#ifdef DYNAMIC_ACTIVITY_COUNTERS
         // This is an internal INITTASK message, SKIP init, it is already executed
         if (mmi_ColaMail_CheckCustomInit(p_mail)) return;
#endif
         if (g_state.going_to_sleep)
         {
			return;
		}
#ifdef DYNAMIC_ACTIVITY_COUNTERS
         SendApiHalReadReq(COLA_TASK, AHA_NVS, NVS_USR_ACT_CNT_BASE, NVS_ACT_CNT_LEN);
#endif
		MmiInit();
		return;

      }
      case API_PP_ULE_INIT_CFM:
      {
         ApiPpUleInitCfmType *lpm = (ApiPpUleInitCfmType *) p_mail;

        // Keep activity Status
        MmiCtrl.activity_status 		= lpm->ActivityStatus;
        MmiCtrl.activity_resume_counter = lpm->ResumeCounter;
         MmiCtrl.wakeup_event = lpm->WakeupEvent; // store wakeup event
         SendApiPpUleHibernateReadReq(COLA_TASK, API_PP_ULE_NVS_CLIENT_APP);

         if ((MmiCtrl.wakeup_event == API_PP_ULE_WAKEUP_EVENT_NON_ULP) || (lpm->IsUlpWakeup == 0))
         {
            MmiCtrl.wakeup_event = API_PP_ULE_WAKEUP_EVENT_NON_ULP;
            SendApiHalReadReq(COLA_TASK, AHA_NVS, NVS_USR_BASE, NVS_USER_LEN);
         }

         break;
      }
      case API_PP_ULE_HIBERNATE_READ_CFM:
      {
         if (g_state.doing_init == 0)
            break;
		ApiPpUleHibernateReadCfmType *lpm = (ApiPpUleHibernateReadCfmType *) p_mail;
         if (lpm->nvs_client_id != API_PP_ULE_NVS_CLIENT_APP)
            break;
		MmiCtrl.nvsReady=1;
         if (lpm->Length == sizeof(MmiCtrl.nvs))
         {
			memcpy(&MmiCtrl.nvs, lpm->Data, sizeof(MmiCtrl.nvs));
            if (MmiCtrl.nvs.sleep_time < 1)
            {
				MmiCtrl.nvs.sleep_time = INITIAL_SLEEP_TIME;
			}
         }
         else
         {
            MmiCtrl.nvs.PortDirMode = API_PP_ULE_PORT_DIR_MODE_IN_PULLDOWN;
            MmiCtrl.nvs.PortTrigMode = API_PP_ULE_PORT_TRIG_MODE_RISING_EDGE;
			MmiCtrl.nvs.sleep_time = INITIAL_SLEEP_TIME;
	        MmiCtrl.nvs.lock_timeout = DEFAULT_LOCK_TIMEOUT;
	        MmiCtrl.nvs.lr_timeout = DEFAULT_LR_TIMEOUT;
		}

         MmiCtrl.nvs.sync_time = g_state.sync_time;

        switch (MmiCtrl.wakeup_event)
        {
          case  API_PP_ULE_WAKEUP_EVENT_TIMER:
          case  API_PP_ULE_WAKEUP_EVENT_PORT:
          {
                if (MmiCtrl.activity_status == API_PP_ULE_START_APP_ONLY) {
#if defined(BATTERY_ACTUATOR)
                    UserAppOnlyTask();
#endif
                     MmiCtrl.awake_time = 0;
                     GoToSleep();
                  }
                  if (!MmiCtrl.islocked) {
                      RosTimerStart(LOCK_TIMER, T_MMI_WAIT_LOCK, &LockTimeoutTimerConfig);
                      //MmiCtrl.isRegistered=1;
                      //break;
                 }
          }
          case API_PP_ULE_WAKEUP_EVENT_NON_ULP:
            case API_PP_ULE_WAKEUP_EVENT_UNDEF:
          default:
            SendApiPpUleSubsStatusReq(COLA_TASK);
            break;
        }
		}
		break;


	case API_PP_ULE_SUBS_STATUS_CFM:
	{
		if (g_state.doing_init==0) break;
		g_state.doing_init=0;
		// COMMENT SL: new API
		// lpm->IsUlpWakeup shows cold boot / ULE wake-up
		ApiPpUleSubsStatusCfmType *lpm = (ApiPpUleSubsStatusCfmType *) p_mail;

		if (lpm->Status == RSS_NO_DATA) {
			// not registered ...
		  // report to the user that the system is not registered and remain in init state
		  // user must init registration state. Read DECT REGION
		  RosTimerStop(LOCK_TIMER);
		  //SendApiHalReadReq(COLA_TASK, AHA_NVS, 0x20, 1); // Read band offset
		  SendApiProdTestReq(COLA_TASK, PT_CMD_GET_DECT_MODE, 1, 0); // Request dect mode
		  MmiCtrl.isRegistered=0;
		} else {
			// registered!
			//MmiCtrl.isRegistered=1;
			if(MmiCtrl.wakeup_event == API_PP_ULE_WAKEUP_EVENT_NON_ULP) {
            // Start PVC configuration
			MmiCtrl.pvc = 1;
               ResetPvcConfig();
            //SendApiPpUlePvcConfigReq ( COLA_TASK, API_ULE_PROTOCOL_FUN_1, API_ULE_PROTOCOL_VERSION_0, 0,
            //                           API_ULE_MTU_SIZE_DEFAULT, API_ULE_MTU_SIZE_DEFAULT, API_ULE_MTU_LIFETIME_DEFAULT,
             //                          API_ULE_WINDOW_SIZE_DEFAULT, API_ULE_PP_INITIATOR);
			}
	        //if((!MmiCtrl.islocked) && (MmiCtrl.wakeup_event == API_PP_ULE_WAKEUP_EVENT_NON_ULP)){
			if (!MmiCtrl.islocked) {
	            // Start new search for lock
	            //  wait for API_PP_MM_LOCKED_IND and API_PP_ULE_DATA_IND
	            SendApiPpMmLockReq(COLA_TASK, MMI_SUBSCRIPTION);
	          }
		}
	}
		break;
	 case API_PP_ULE_PVC_CONFIG_CFM:
	 {
		ApiPpUlePvcConfigCfmType *Mp = (ApiPpUlePvcConfigCfmType*) p_mail;

		// This is the parameters that is commited
		//  If other than default was requested we can check
		//  if this was accepted by the FP
         if (Mp->ProtocolVer) {
         }
		if (Mp->MtuPtSize) {
		}
		if (Mp->MtuFtSize) {
		}
		if (Mp->MtuLifetime) {
		}
		if (Mp->WindowSize) {
		}
		// This is the paging parameters
		// Usage TBD!
		if (Mp->Page_1.Id) {
			// Descriptor;       // Selects broadcast or paging
			// Id;               // Paging id
			// Period;            //Periodicity in frames
		}

		// PVC is config done
		MmiCtrl.pvc = 0;
		// Wait for API_PP_ULE_DTR_IND
        RosTimerStart(LR_TIMER, T_MMI_WAIT_LR, &LocateRegTimerConfig);
	}
		break;

	case API_PP_ULE_PVC_CONFIG_REJ:
	{
		ApiPpUlePvcConfigRejType *Mp = (ApiPpUlePvcConfigRejType*) p_mail;

		// Handle Reject
		switch (Mp->Reason)
		{
		case API_PP_ULE_ERR_NO_RESOURCES:
			// TBD
			break;
		case API_PP_ULE_ERR_BUSY:
			// Connection ongoing, wait
			break;
		case API_PP_ULE_ERR_UNKNOWN:
			// Restart PVC configuration
            // Start PVC configuration
			MmiCtrl.pvc =1;
               SendApiPpUlePvcConfigReq(COLA_TASK, API_ULE_PROTOCOL_FUN_1,
                                        API_ULE_PROTOCOL_VERSION_0, 0, API_ULE_MTU_SIZE_DEFAULT,
                                        API_ULE_MTU_SIZE_DEFAULT, API_ULE_MTU_LIFETIME_DEFAULT,
                                       API_ULE_WINDOW_SIZE_DEFAULT, API_ULE_PP_INITIATOR);
			break;
		case API_PP_ULE_ERR_NOT_LOCATED:
			// Start locate registration

	    	SendApiPpUleLocateReq(COLA_TASK);
	    	MmiCtrl.PendTDR=0;
	  		MmiCtrl.UleReadyReceived=0; // Wait for a new READY indication
			RosTimerStop(LR_TIMER);
			RosTimerStop(LOCK_TIMER);
	        RosTimerStart(LR_TIMER, T_MMI_WAIT_LR, &LocateRegTimerConfig);

			break;
		default:
			break;
		}
	}
		break;

	case API_PP_ULE_PVC_CONFIG_IND:
	{
		ApiPpUlePvcConfigIndType *Mp = (ApiPpUlePvcConfigIndType*) p_mail;
         Disable_Sleep();
		// Handle Config indication
		switch (Mp->Reason)
		{
		case API_PP_ULE_ERR_FP_PVC_REQ:
            {
               MmiCtrl.pvc = 1;
               SendApiPpUlePvcConfigReq(API_PP_ULE_APP_TASK, 0, 0, 0, 0, 0, 0, 0, API_ULE_FP_INITIATOR);
              // SendApiPpUlePvcConfigReq(COLA_TASK, API_ULE_PROTOCOL_FUN_1,
             //                           API_ULE_PROTOCOL_VERSION_0, 0, API_ULE_MTU_SIZE_DEFAULT,
             //                           API_ULE_MTU_SIZE_DEFAULT, API_ULE_MTU_LIFETIME_DEFAULT,
             //                           API_ULE_WINDOW_SIZE_DEFAULT, API_ULE_FP_INITIATOR);
            }
               break;
            case API_PP_ULE_ERR_FP_CCM:{
               SendApiPpUlePvcConfigReq(API_PP_ULE_APP_TASK, 0, 0, 0, 0, 0, 0, 0, API_ULE_PP_INITIATOR);
            }
            break;
		case API_PP_ULE_ERR_PVC_SUSPENDED:
            case API_PP_ULE_ERR_FP_PVC_SUSPENDED:
            {
			// This is an PP requested Service call
			MmiCtrl.pvc = 1;
               ResetPvcConfig();
             //  SendApiPpUlePvcConfigReq(COLA_TASK, API_ULE_PROTOCOL_FUN_1,
              //                          API_ULE_PROTOCOL_VERSION_0, 0, API_ULE_MTU_SIZE_DEFAULT,
               //                         API_ULE_MTU_SIZE_DEFAULT, API_ULE_MTU_LIFETIME_DEFAULT,
               //                         API_ULE_WINDOW_SIZE_DEFAULT, API_ULE_PP_INITIATOR);
		}
			break;
		default:
			break;
		}
	}
		break;

      case API_PP_ULE_PVC_PENDING_IND:
      {
    	Disable_Sleep();
		// Test Messages
        uint8_t Content[] = { 0x81, 0x01, 0x01, 0x00, 0x01 };//0x77,0x06,0x85,
		ApiIwuToIwuType *IeData;
		uint8_t IeLength = RSOFFSETOF(ApiIwuToIwuType,Content)+ sizeof(Content);
		ApiInfoElementType *IeBlockPtr = malloc(sizeof(ApiIwuToIwuType));
		uint16_t IeBlockLength = 0;

		IeData = (ApiIwuToIwuType*) malloc(IeLength);
		IeData->TransmitReject = true; /* send*/
		IeData->Length = sizeof(Content);
		IeData->IwuProtocolDiscriminator = 0x85; /*User specific*/

		memcpy(IeData->Content, Content, sizeof(Content));

		/* Build info,NOTE:
		 * ApiBuildInfoElement internally uses realloc() or equivalent on IeBlockPtr
		 * and the copies over all data again, we only need malloc() initialization of IeBlockPtr
		 */
		ApiBuildInfoElement(&IeBlockPtr, &IeBlockLength, API_IE_IWU_TO_IWU, IeLength,
							(uint8_t *) IeData);

		// PP send this messages and the FP should answers in order for us to send
		// the PVC pending response
#if defined(HF_ACTUATOR) || defined(BATTERY_ACTUATOR) || defined(ACTUATOR) || defined(SMARTPLUG)
            SendApiPpUlePvcIwuDataReq(COLA_TASK, IeBlockLength, (uint8_t*) IeBlockPtr);
#endif
		SendApiPpUlePvcPendingRes(COLA_TASK, API_PP_ULE_ERR_NO_ERROR);
	//	sendonce=1;
		//}

	}
		break;

	case API_PP_ULE_PVC_IWU_DATA_IND:
	{
		ApiPpUlePvcIwuDataIndType *pIwu = (ApiPpUlePvcIwuDataIndType*) p_mail;
		ApiInfoElementType *pIe = ApiGetInfoElement((ApiInfoElementType*) pIwu->InfoElement,
														pIwu->InfoElementLength, API_IE_IWU_TO_IWU);
		/* Handle IWU data, UNUSED here */
		(void) pIe;
	}
		break;

		//*** FP initiated actions ******************
	case API_PP_ULE_SETUP_AGAIN_IND:
         RosTimerStop(DUMMY_MESSAGE_TIMER);
         RosTimerStart(DUMMY_MESSAGE_TIMER, setupagaintimer, &ComeBackRegTimerConfig);
         setupagaintimer=setupagaintimer+4000;
		break;

	case API_PP_ULE_HIGH_PAGING_MODE_IND:
		// TBD
		break;

	case API_PP_ULE_LCE_PAGING_MODE_IND:
		// TBD
		break;

	case API_PP_ULE_START_VOICE_CALL_IND:
		//TBD
		break;

    case API_PP_ULE_START_LOCATE_IND:
      // Most likely a FP power cycle
      //  - so start a new location registration
         if ((MmiCtrl.UleReadyReceived) && (MmiCtrl.PendTDR))
         { // A TX attempted had started, we need to notify user that it failed.
    	}
    	SendApiPpUleLocateReq(COLA_TASK);
        // MmiCtrl.pvc = 1;
         //SendApiPpUlePvcConfigReq(COLA_TASK, API_ULE_PROTOCOL_FUN_1, API_ULE_PROTOCOL_VERSION_0, 0,
         //                         API_ULE_MTU_SIZE_DEFAULT, API_ULE_MTU_SIZE_DEFAULT,
         //                         API_ULE_MTU_LIFETIME_DEFAULT, API_ULE_WINDOW_SIZE_DEFAULT,
    	MmiCtrl.PendTDR=0;
         //MmiCtrl.UleReadyReceived = 0; // Wait for a new READY indication
		RosTimerStop(LR_TIMER);
		RosTimerStop(LOCK_TIMER);
        RosTimerStart(LR_TIMER, T_MMI_WAIT_LR, &LocateRegTimerConfig);
		//MmiCtrl.islocked= 0;
		break;

	case API_PP_MM_REGISTRATION_COMPLETE_IND:
		MmiCtrl.pvc = 1;
        SendApiPpUlePvcConfigReq ( COLA_TASK, API_ULE_PROTOCOL_FUN_1, API_ULE_PROTOCOL_VERSION_0, 0,
                                  API_ULE_MTU_SIZE_DEFAULT, API_ULE_MTU_SIZE_DEFAULT,
                                  API_ULE_MTU_LIFETIME_DEFAULT, API_ULE_WINDOW_SIZE_DEFAULT,
                                  API_ULE_PP_INITIATOR);
        RosTimerStart(LOCK_TIMER, T_MMI_WAIT_LOCK, &LockTimeoutTimerConfig);
		//MmiCtrl.isRegistered=1;
		MmiCtrl.RegistrationMode = false;
		break;

	case API_PP_MM_REGISTRATION_FAILED_IND:
		MmiCtrl.RegistrationMode = false;
		RosTimerStop(LR_TIMER);
		RosTimerStop(LOCK_TIMER);
		MmiCtrl.isRegistered=0;
		break;

	case API_PP_MM_LOCKED_IND:
#ifndef SMARTPLUG
#if 0
         if ((MmiCtrl.nvs.sync_time = RsPerformanceTicks2Time(RsReadPerformanceCounter()
               - MmiCtrl.inittask_timestamp)) & RS_PTIME_MS)
         {
            MmiCtrl.nvs.sync_time &= ~RS_PTIME_MS;
         }
         else
         {
            MmiCtrl.nvs.sync_time /= 1000;
         }
#endif
		g_state.sync_time=MmiCtrl.nvs.sync_time;
#endif
		RosTimerStop(LOCK_TIMER);
		PagingMode(MmiCtrl.pagingInitiated); // We should re-enable paging if node temporarily got out of lock.
		MmiCtrl.islocked= 1;
		break;

	case API_PP_MM_UNLOCKED_IND:
		// Wait a while for PP to find lock again before
		//  resetting MAC layer by starting a new search
		MmiCtrl.PendTDR=0;
		MmiCtrl.islocked= 0;
		RosTimerStop(LOCK_TIMER);
		RosTimerStop(LR_TIMER);
		if (MmiCtrl.RegistrationMode) {
			Enable_Registration(ACCESS_CODE);
		} else {
            MmiCtrl.PendTDR=0;
            RosTimerStart(LOCK_TIMER, T_MMI_WAIT_LOCK, &LockTimeoutTimerConfig);
		}
		break;


	case API_PP_ULE_DATA_CFM:
		{
	     // Is data accepted by the the transmitter
         if (((ApiPpUleDataCfmType *) p_mail)->Result == API_PP_ULE_ERR_NO_ERROR)
         {
            if(is_setup_again==0){setupagaintimer=2000;}
            is_setup_again=0;
				 // Don't transmit again before a new DTR is received
			SendApiPpMmReadRssiReq(COLA_TASK);
         }
         else
         {
	        	MmiCtrl.PendTDR=0;
	        }
	    }
		break;

    case API_PP_ULE_READY_IND:
      // Ready for data
    	//if(MmiCtrl.RegistrationMode) break;

	    // Calculate sync_time
	    MmiCtrl.UleReadyReceived=1;
    	PagingMode(MmiCtrl.pagingInitiated);
    	MmiCtrl.PendTDR=0; // Do not wait for DTR during boot up

    	SendApiPpMmReadRssiReq(COLA_TASK);

		RosTimerStop(LOCK_TIMER);
		RosTimerStop(LR_TIMER);
        break;

    case API_PP_MM_READ_RSSI_CFM:{
    	MmiCtrl.nvs.rssi = ((ApiPpMmReadRssiCfmType *)p_mail)->Rssi;
		}
    	break;
	case API_PP_ULE_DTR_IND:
  		 MmiCtrl.PendTDR = 0;
		// Received DTR indication on previous data transmission

		SendApiPpMmReadRssiReq(COLA_TASK);

		RosTimerStop(MMI_STATE_TIMER); // Not registered.. No need to count for anything..
		RosTimerStop(LOCK_TIMER);
		break;


	case API_FWS_STATUS_IND:
		FwsApiFwsStatusInd((const ApiFwsStatusIndType *)p_mail);
				break;
	case API_FWS_WRITE_CFM:
	case API_FWS_WRITE_EXT_DATA_CFM:
		FwsApiFwsWriteExtDataCfm((const ApiFwsWriteExtDataCfmType *)p_mail);
		break;

      case API_PP_ULE_DATA_IND:{
    	  MmiUlePdu_common_t* DataReceived;
    	  DataReceived = (MmiUlePdu_common_t*) (&(p_mail->Data.Data[1]));
    	   if (((const ApiPpUleDataIndType*) p_mail)->Length>400) {
    		   MmiCtrl.FWS.TaskDisable=1;
    	   }
    	   if (MmiCtrl.FWS.TaskDisable==1) FwsApiPpUleDataInd((const ApiPpUleDataIndType*) p_mail);
    	   if ((MmiCtrl.FWS.TaskDisable==1)&&(MmiCtrl.FWS.Enabled==0)) FwsApiPpUleDataInd_MdtFws((const MmiUleData_MmiDataTypeFws*)DataReceived->Data);
      }
		break;

	case API_PP_MM_DELETE_LOCAL_REGISTRATION_CFM:
	case API_PP_MM_ACC_RIGHTS_TERM_IND: //0x511B
		// FP has deleted registration
		MmiCtrl.isRegistered = 0;
		MmiCtrl.UleReadyReceived = 0;
		MmiCtrl.PendTDR = 0;
		RosTimerStop(LOCK_TIMER);
		RosTimerStop(LR_TIMER);
		RosTimerStop(MMI_STATE_TIMER);
		break;

	case MMI_STATE_TIMEOUT_ind:
		MmiCtrl.awake_time=0;
		GoToSleep();
		break;

	case TERMINATETASK:
		//RosTaskTerminated(ColaIf->ColaTaskId);
		break;

	case UART_TX_DONE:
	case UART_RX_DATA_READY:
		//UartTask(p_mail);
		break;

	case API_HAL_DEVICE_CONTROL_CFM:
		//ApiHalDeviceControlCfm((const ApiHalDeviceControlCfmType*) p_mail);
		break;

	case API_PP_ULE_SUBS_DELETE_CFM:
		MmiCtrl.isRegistered = false;
		break;

	case API_HAL_READ_CFM:
		{
#ifdef DYNAMIC_ACTIVITY_COUNTERS
			ApiHalReadCfmType* hlrdcfm = (ApiHalReadCfmType*) p_mail;
			if ((hlrdcfm->Status == RSS_SUCCESS) &&
				(hlrdcfm->Area == AHA_NVS) &&
				(hlrdcfm->Address == NVS_USR_ACT_CNT_BASE) &&
				(hlrdcfm->Length == NVS_ACT_CNT_LEN))
			{
				MmiCtrl.nvs.ActvtCounters.CheckPage = ((hlrdcfm->Data[ACTCNT_CHCKPAGE_MSB] << 8) +
														hlrdcfm->Data[ACTCNT_CHCKPAGE_LSB]);
				MmiCtrl.nvs.ActvtCounters.StartApp  = ((hlrdcfm->Data[ACTCNT_STARTAPP_MSB] << 8) +
														hlrdcfm->Data[ACTCNT_STARTAPP_LSB]);
				MmiCtrl.nvs.ActvtCounters.KeepAlive = ((hlrdcfm->Data[ACTCNT_KEEPALIV_MSB] << 8) +
														hlrdcfm->Data[ACTCNT_KEEPALIV_LSB]);
				mmi_ColaMail_InitTask();
			}
#endif
		}
		break;
	case API_PROD_TEST_CFM: // API_PROD_TEST_CFM
		{
			ApiProdTestCfmType* prodTestCfm = (ApiProdTestCfmType*) p_mail;
			switch(prodTestCfm->Opcode) {
				case PT_CMD_GET_SW_VERSION:
					MmiCtrl.StackVersion = (uint16_t) ((prodTestCfm->Parameters[1] << 8)
														+ prodTestCfm->Parameters[0]);
					break;

				case PT_CMD_SET_DECT_MODE:
					// Soft reset after successful Dect Mode change
					if (prodTestCfm->Parameters[0] == RSS_SUCCESS) {
				SendApiProdTestReq(COLA_TASK, PT_CMD_SW_RESET, 0, NULL);
			}
					break;
				case PT_CMD_GET_DECT_MODE:
					if ( prodTestCfm->Parameters[0] == 0x00 ) {
						MmiCtrl.nvs.region=0;
					} else if ( prodTestCfm->Parameters[0] == 0x08 ) {
						MmiCtrl.nvs.region=1;
					} else if ( prodTestCfm->Parameters[0] == 0x0A ) {
						MmiCtrl.nvs.region=2;
					} else {
						break;
		}
					break;

				default:
					break;
			}
		}
		break;

	case API_HAL_SET_GPIO_PORT_CFM:
	case API_HAL_WRITE_CFM:
	case ROS_PM_WAKEUP_ind:
	case MMI_RESET_TIMEOUT_ind:
	case API_PP_MM_EASY_PAIRING_SEARCH_CFM:
	case API_PP_ULE_DB_PAGE_IND:
	case API_PP_ULE_HAL_GET_PORT_CFM:
	case API_PP_ULE_HAL_PORT_IND:
		break;
	/*************************************************************************
	 * TIMER functions
	 **************************************************************************/
	case TIMEOUT:
		switch (p_mail->Timeout.Parameter) {
//			case REGISTRATION_TIMER:
//				RosTimerStop(REGISTRATION_TIMER);
//				if(MmiCtrl.RegistrationMode == true){
//					MmiCtrl.RegistrationMode = false;
//					//ATString("\r\n+UTIMEOUT:0x03,");NewATLine();
//					SendApiPpMmRegistrationStopReq(COLA_TASK);
//				}
//				break;
			case LR_TIMER:
//				MmiCtrl.PendTDR=0;
//				RosTimerStop(LR_TIMER);
               //SendApiPpUleLocateReq(COLA_TASK);
              // MmiCtrl.pvc = 1;
              // SendApiPpUlePvcConfigReq(COLA_TASK, API_ULE_PROTOCOL_FUN_1,
              //                          API_ULE_PROTOCOL_VERSION_0, 0, API_ULE_MTU_SIZE_DEFAULT,
              //                         API_ULE_WINDOW_SIZE_DEFAULT, API_ULE_PP_INITIATOR);
              // MmiCtrl.PendTDR = 0;
              // MmiCtrl.UleReadyReceived = 0; // Wait for a new READY indication
              // RosTimerStop(LR_TIMER);
              // RosTimerStop(LOCK_TIMER);
				RosTimerStart(LR_TIMER, T_MMI_WAIT_LR, &LocateRegTimerConfig);
				break;
            case DUMMY_MESSAGE_TIMER:
               is_setup_again=1;
#ifndef HANFUN
               RosTimerStop(DUMMY_MESSAGE_TIMER);
#endif
               //SendApiPpUleDataReq (COLA_TASK, API_ULE_DLC_CTRL_ACKNOWLEDGED, 0, NULL);
				break;
			case LOCK_TIMER:
				MmiCtrl.PendTDR=0;
				RosTimerStop(LOCK_TIMER);
				break;
			case FWS_TIMER:
#ifndef HANFUN
			FwsTimeout();
#endif
				break;
		}
		break;

	default:
		//MmiUnknowPrim=p_mail->Primitive;
		break;
	}

}



void GoToSleep()
/*************************************************************************
 *
 **************************************************************************/
{
	if(MmiCtrl.awake_time){
		RosTimerStart(MMI_STATE_TIMER, MmiCtrl.awake_time, &MmiStateTimerConfig);
		return;
	}

	 g_state.going_to_sleep=1;


   SendApiPpUleHibernateWriteReq(COLA_TASK, API_PP_ULE_NVS_CLIENT_APP, sizeof(MmiCtrl.nvs),
                                 (uint8_t *) &MmiCtrl.nvs);
   SendApiPpUleSuspendReq(COLA_TASK, MmiCtrl.nvs.sleep_time, API_PP_ULE_TIME_UNIT_S,
                          MmiCtrl.nvs.PortDirMode, MmiCtrl.nvs.PortTrigMode);


}

void Enable_Registration (uint16_t AccessCode)
{
	RosTimerStop(LR_TIMER);
	RosTimerStop(LOCK_TIMER);
	MmiCtrl.AccessCode[2] =(uint8_t)(AccessCode>>8);
	MmiCtrl.AccessCode[3] =(uint8_t)(AccessCode&0xFF);
   if (MmiCtrl.RegistrationMode == 0)
      SendApiPpUleSubsDeleteReq(COLA_TASK);
	MmiCtrl.RegistrationMode = true;
	SendApiPpMmRegistrationAutoReq(COLA_TASK, MMI_SUBSCRIPTION, MmiCtrl.AccessCode);
	MmiCtrl.PendTDR=0;
}


/*************************************************************************
 * MAIN COLA TASK AND INIT
 **************************************************************************/

/*************************************************************************
 * FUNCTION: MmiTask
 * INPUTS  : Mail pointer
 * OUTPUTS : None
 *
 * DESCRIPTION: The MMI task is used to handle the registration of the PP,
 *       this includes handling the ULP connection parameters.
 *
 *       The MMI task is also used to handle the Suspend and WakeUp mails,
 *       but in this aplication what needs to be done is handled in the
 *       MmiTaskInit and the callback function. So during the Suspend/Awake
 *       cycle the only thing the MMI task is doing is counting number of
 *       suspends.
 *
 **************************************************************************/
void ColaTask(const RosMailType* p_mail) {

#ifdef DEBUG_MMI_MSG
	// check hdlc.c -> RxThread -> DataReceiverContainer
	// super ugly but didn't want to break ColaTask convention
	uint16_t mail_len =  (uint16_t) (  *((uint8_t *)p_mail-5) * 256 + *((uint8_t *)p_mail-4));
	// mail_len is 3+PRIM+DATA,
	if (mail_len >= 5) mail_len -= 5; // it can't be less than 5 (3+PRIM)
	else mail_len -= 2; // this is the case of custom RosAllocate packet, remove only PRIM
#endif

	if(g_state.is_booted==0){
		g_state.is_booted=1;
	}

	// First direct all messages to default function
	s_mmi_default(p_mail);
#ifdef DYNAMIC_ACTIVITY_COUNTERS
    if (p_mail->Primitive == INITTASK) {
        /* In case of "delayed init" pass only the custom INITTASK to User tasks */
        if (!mmi_ColaMail_CheckCustomInit(p_mail)) return;
    }
#endif
    if (MmiCtrl.FWS.TaskDisable==0)
        UserTask(p_mail);
#ifdef HANFUN
    if (MmiCtrl.FWS.TaskDisable==0)
        // HanfunTask(p_mail);
		hanfun_state_machine(p_mail);
#endif
}

void PagingMode(uint8_t Enable) {
	if((MmiCtrl.islocked)&&(MmiCtrl.UleReadyReceived)){
		SendApiPpUleDbPageEnableReq( COLA_TASK, (Enable > 0)? API_ULE_DLC_DB_PAGE_MODE_1:0 ); // If enabled always set to API_ULE_DLC_DB_PAGE_MODE_1, in order to scan in every frame
	}
	MmiCtrl.pagingInitiated = Enable;
}

void MmiInit(void) {

#ifdef PCCOMPILE
  memset(&MmiCtrl,0x00,sizeof(MmiCtrl));
#endif
#ifdef HANFUN
	uint8_t * pdu;
	pdu = (uint8_t *) calloc(34, sizeof(uint8_t));
	free(pdu);
#endif

	MmiCtrl.AccessCode[0]=	0xff;
	MmiCtrl.AccessCode[1]=	0xff;
	MmiCtrl.AccessCode[2]=	0x0;
	MmiCtrl.AccessCode[3]=	0x0;

	MmiCtrl.ulpPort = 0; //(uint8_t)(ULP_PORT_REG_bit.ULP_PORT_VAL);

    // Send SW version command
    uint8_t DummyParameters = 0;
    SendApiProdTestReq(COLA_TASK, PT_CMD_GET_SW_VERSION, 0, &DummyParameters);

#ifdef HANFUN
    SendApiPpUleInitReq(COLA_TASK,  API_PP_ULE_MODE_UNLOCKED,
    					API_PP_ULE_SLEEPMODE_WAKEON_PORT_AND_TIMER,
    					API_PP_ULE_SUSPEND_MODE_HIBERNATE,
    					MmiActivityCounters);
#endif

    MmiCtrl.pagingInitiated = API_ULE_DLC_DB_PAGE_MODE_1;

    g_state.doing_init=1;

}

