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
 *                               Include files
 ****************************************************************************/

#include "mmi_def.h"
#include "log.h"

#include "HanFunTask.h"



const RosTimerConfigType UserTimerConfig = { COLA_TASK, { TIMEOUT, USER_SW_COUNTER_TIMER } };

rsuint16 AdcValue, temp, TxPass, TxFail;
rsuint8 SmartplugData[20];


void ColaMail(ApiPpAppMsg_t A1) {
	ApiPpUleHanfunCmdType* m = (ApiPpUleHanfunCmdType*) RosMailAllocate(
			API_TASK, COLA_TASK, (rsuint16) (sizeof(ApiPpUleHanfunCmdType)));

	m->Primitive = 0x0000;
	m->dummy = 0x1;
	m->cmd = A1;
	RosMailDeliver((RosMailType *) m);
}


void ColaMail_SetupAgain() {
	ApiPpUleHanfunCmdType* m = (ApiPpUleHanfunCmdType*) RosMailAllocate(
			API_TASK, COLA_TASK, (rsuint16) (sizeof(ApiPpUleHanfunCmdType)));

	m->Primitive = API_PP_ULE_SETUP_AGAIN_IND;
	RosMailDeliver((RosMailType *) m);
}

void ColaMailPtr(ApiPpAppMsg_t A1, rsuint32 Addr) {
	ApiPpUleHanfunCmdType* m = (ApiPpUleHanfunCmdType*) RosMailAllocate(
			API_TASK, COLA_TASK, (rsuint16) (sizeof(ApiPpUleHanfunCmdType)));

	m->Primitive = 0x0000;
	m->dummy = 0x1;
	m->cmd = A1;
	m->Ptr = Addr;
	RosMailDeliver((RosMailType *) m);
}

rsuint8 jj,cntpm;
rsbool PlugState;


//ApiPpUleHanfunSmartMeasureType CurMeasurement;
static volatile bool gotosleep = 0;


void SetLED3(bool led_on)
{
	SendApiPpUleHalSetPortReq(COLA_TASK, API_PP_ULE_GPIO_LED3, led_on);
}

void SetLED4(bool led_on)
{
	SendApiPpUleHalSetPortReq(COLA_TASK, API_PP_ULE_GPIO_LED4, led_on);
}



void Sleep (rsuint8 txstatus)
{
   if (MmiCtrl.FWS.Enabled) return; // Skip if we are in FWS update mode

   if (gotosleep)
   {
      // Cold Boot or Port Trigger
      // On COLD BOOT set the UMODE to the initial values
      // On PORT TRIGGER change edge to trigger relais both ways

      // Positive edge if ULE port if low for Reed relais
      MmiCtrl.nvs.PortDirMode = ULP_PORT_DIR_MODE_IN_PULLDOWN;
      MmiCtrl.nvs.PortTrigMode = ULP_PORT_TRIG_MODE_RISING_EDGE;


      GoToSleep ();
   }
}

void Enable_Sleep ()
{
#ifdef HF_SENSOR
   gotosleep = 1;
#endif
}

void Disable_Sleep ()
{
   gotosleep = 0;
}


void UserTask(const RosMailType* p_mail) {

	switch (p_mail->Primitive) {
	case HANFUN_MESSAGE: {
		ApiPpUleHanfunCmdType *Mp = (ApiPpUleHanfunCmdType*) p_mail;
		switch ((ApiPpAppMsg_t)Mp->cmd) {
		case HANFUN_CONNECT_COMPLETE:
			if (MmiCtrl.hanfun_registered)  {
//				Enable_Sleep();
//				if (MmiCtrl.wakeup_event == API_PP_ULE_WAKEUP_EVENT_NON_ULP) {
//					Sleep ( TX_PASS);
//				}
				RosTimerStop( USER_SW_COUNTER_TIMER);
				RosTimerStart(USER_SW_COUNTER_TIMER, 1000, &UserTimerConfig);
			}

	#ifdef HF_SIMPLE_SWITCH

			if (MmiCtrl.wakeup_event == API_PP_ULE_WAKEUP_EVENT_PORT && MmiCtrl.hanfun_registered)
			{
				// RosTimerStop(DUMMY_MESSAGE_TIMER);
				Enable_Sleep();
				ColaMail(HANFUN_SWITCH_TOGGLE);

			}
			if (MmiCtrl.wakeup_event == API_PP_ULE_WAKEUP_EVENT_TIMER && MmiCtrl.hanfun_registered) {
				// RosTimerStop(DUMMY_MESSAGE_TIMER);
				Enable_Sleep();
				SendApiPpUleDataReq (COLA_TASK, API_ULE_DLC_CTRL_ACKNOWLEDGED, 0, NULL);
			}

	#endif
	#ifdef HF_SIMPLE_REED

		if (MmiCtrl.wakeup_event == API_PP_ULE_WAKEUP_EVENT_PORT && MmiCtrl.hanfun_registered)
		{
			// RosTimerStop(DUMMY_MESSAGE_TIMER);
			Enable_Sleep();
			ColaMail(HANFUN_DETECTOR_ALERT);

		}
		if (MmiCtrl.wakeup_event == API_PP_ULE_WAKEUP_EVENT_TIMER && MmiCtrl.hanfun_registered) {
			// RosTimerStop(DUMMY_MESSAGE_TIMER);
			Enable_Sleep();
			SendApiPpUleDataReq (COLA_TASK, API_ULE_DLC_CTRL_ACKNOWLEDGED, 0, NULL);
		}

	#endif
			break;

		case HANFUN_REG_COMPLETE:
			Enable_Sleep();
			Sleep ( TX_PASS);
			RosTimerStop( USER_SW_COUNTER_TIMER);
			RosTimerStart(USER_SW_COUNTER_TIMER, 1000, &UserTimerConfig);
			break;
		case HANFUN_NVS_SAVE:
			MmiCtrl.nvs.UserData[HF_OFFSET] = MmiCtrl.hanfun_address;
			SendApiHalWriteReq(COLA_TASK, AHA_NVS, NVS_USR_BASE, NVS_USER_LEN, &MmiCtrl.hanfun_address);
			if(MmiCtrl.delaysleep==DELAYSLEEP_REGISTERDELAY){
				MmiCtrl.delaysleep=DELAYSLEEP_IDLE;
				Enable_Sleep();
				Sleep(TX_PASS);
			}
			break;
		default:
			break;

		}

	}
		break;
	case 0xF0F4:	/* RTX_EAP_TARGET_RESET_IND */
	case INITTASK: // Module booted up - Non Dect initialization code goes here
	{
#ifdef HF_SIMPLE_SWITCH
		ColaMailPtr(HANFUN_INIT, HANFUN_SENSOR);
#endif

#ifdef HF_SIMPLE_LIGHT
		ColaMailPtr(HANFUN_INIT, HANFUN_LIGHT);
#endif

#ifdef HF_SIMPLE_REED
		ColaMailPtr(HANFUN_INIT, HANFUN_REED);
#endif

#ifdef HF_AC_OUTLET
		ColaMailPtr(HANFUN_INIT, HANFUN_SMARTPLUG);
		port_setup();
		SendApiPpVbattEnableReq(COLA_TASK, FALSE);
		SmartPlugInit();
		RosTimerStart(SMARTPLUG_TIMER, SMARTPLUG_TIMER_VAL,
				&SmartplugTimerConfig);
#endif
		break;
	}

	case API_PP_ULE_SUBS_STATUS_CFM: // DECT is initialized - Dect initialization code goes here
	{

#ifdef HF_AC_OUTLET
		USRNVSTIMERVALUE_normal=USRNVSTIMERVALUE;
		SmartPlugUCREG();
#endif

		if ( MmiCtrl.isRegistered == 0 ) {
			// The device is not registered so automatically the device will go into registration mode
			// Enable_Registration(ACCESS_CODE);
			// ColaMailPtr(HANFUN_NVS_SET, 0);
			// ColaMail(HANFUN_NVS_SAVE);
			// SetLED3(TRUE);
		}

		MmiCtrl.nvs.sleep_time = INITIAL_SLEEP_TIME;

		break;
	}
#ifdef HF_AC_OUTLET
		case API_PP_ULE_PVC_CONFIG_CFM:

		if(MmiCtrl.UleReadyReceived==1) SmartPlugUCREG();
		break;
#endif

	case API_PP_ULE_HIBERNATE_READ_CFM:
		ColaMailPtr(HANFUN_NVS_SET, MmiCtrl.nvs.UserData[HF_OFFSET]);
		//no break
	case API_PP_ULE_READY_IND: //  DECT Stack is ready to accept packet
	{
#ifdef HF_AC_OUTLET
		if(MmiCtrl.pvc==0) SmartPlugUCREG();
		if (SmartPlugCalibrationActive()) break;
#endif
		if (MmiCtrl.UleReadyReceived == 0) {
			break;
		}

		if (MmiCtrl.nvsReady == 0) {
			break;
		}

		//ColaMail(HANFUN_CONNECT);

		break;
	}
	case API_PP_ULE_DATA_CFM: {
		// Is data accepted by the stack
		if (((ApiPpUleDataCfmType *) p_mail)->Result != API_PP_ULE_ERR_NO_ERROR) {
			rsuint16 TxFail = (rsuint16) (MmiCtrl.nvs.UserData[TXFAIL_MSB]
					* 255 + MmiCtrl.nvs.UserData[TXFAIL_LSB]);
			TxFail++;
			MmiCtrl.nvs.UserData[TXFAIL_MSB] = (rsuint8) (TxFail >> 8);
			MmiCtrl.nvs.UserData[TXFAIL_LSB] = (rsuint8) (TxFail & 0xFF);
		//	Sleep (TX_FAIL); // If this is not an actuator go to sleep, to save power.
		}

		break;
	}
	case API_PP_MM_LOCKED_IND: // PP can see the base
		break;
	case API_PP_ULE_DTR_IND: {
		// A TX operation from PP is finished
		ApiPpUleDtrIndType *lpm = (ApiPpUleDtrIndType *) p_mail;
		if (lpm->Status == API_PP_ULE_ERR_NO_ERROR) {
			rsuint16 TxPass =
					(rsuint16) ((rsuint16) (MmiCtrl.nvs.UserData[TXPASS_MSB]
							<< 8) + MmiCtrl.nvs.UserData[TXPASS_LSB]);
			TxPass++;
			MmiCtrl.nvs.UserData[TXPASS_MSB] = (rsuint8) (TxPass >> 8);
			MmiCtrl.nvs.UserData[TXPASS_LSB] = (rsuint8) (TxPass & 0xFF);
			if(MmiCtrl.delaysleep==DELAYSLEEP_REENABLE) {Enable_Sleep();MmiCtrl.delaysleep=DELAYSLEEP_IDLE;}
			Sleep(TX_PASS);
		} else {
			rsuint16 TxFail =
					(rsuint16) ((rsuint16) (MmiCtrl.nvs.UserData[TXFAIL_MSB]
							<< 8) + MmiCtrl.nvs.UserData[TXFAIL_LSB]);
			TxFail++;
			MmiCtrl.nvs.UserData[TXFAIL_MSB] = (rsuint8) (TxFail >> 8);
			MmiCtrl.nvs.UserData[TXFAIL_LSB] = (rsuint8) (TxFail & 0xFF);

			if (MmiCtrl.UleReadyReceived == 1) {
				// Don't sleep if waiting for ULE Ready after Locate Request
				Sleep(TX_FAIL);
			}
		}

		break;
	}

		// Received a page from fixed part: indicates data must be fetched from the FP!
	case API_PP_ULE_DB_PAGE_IND: {
		break;
	}

		// Received a packet from fixed part
	case API_PP_ULE_DATA_IND: {
		 if (MmiCtrl.FWS.Enabled)
		 {
		 break; // Skip if we are in FWS update mode
		 }

		break;
	}

	case TIMEOUT: {
		switch (p_mail->Timeout.Parameter) {
		case LOCK_TIMER:
		case LR_TIMER: {
			// If this is not an actuator go to sleep, to save power.
			Sleep (TX_FAIL);
			break;
		}
		case USER_SW_COUNTER_TIMER:
#ifdef HF_AC_OUTLET
			SmartplugData[0] = PlugState;
			//if(SmartPlugFillDatapacket(&SmartplugData[0]) == -1) {
			//	// don't send anything
			//	break;
			//}

			CurMeasurement.power= SmartplugData[3]*256*256 + SmartplugData[2]*256 + SmartplugData[1];
			CurMeasurement.voltage= 10 * ( ((rsuint32)SmartplugData[5]<<8) + ((rsuint32)SmartplugData[4]));
			CurMeasurement.current= 10 * ( ((rsuint32)SmartplugData[7]<<8) + ((rsuint32)SmartplugData[6]));
			CurMeasurement.energy= SmartplugData[11]*256*256*256 + SmartplugData[10]*256*256 + SmartplugData[9]*256 + SmartplugData[8];

			ColaMailPtr(HANFUN_SMARTPLUG_MSR,(rsuint32)&CurMeasurement);
			ColaMailPtr(HANFUN_SMARTPLUG_INTERVAL,10);
			ColaMailPtr(HANFUN_SMARTPLUG_PERIODIC,cntpm++);

#endif

#ifdef HF_SIMPLE_LIGHT
			//CurMeasurement.power= 10 + cntpm;
			//CurMeasurement.voltage= 20 + cntpm;
			//CurMeasurement.current= 30 + cntpm;
			//CurMeasurement.energy= 40 + cntpm;
#ifdef HF_SMARTPLUG_SIM
			ColaMailPtr(HANFUN_SMARTPLUG_MSR,(rsuint32)&CurMeasurement);
			ColaMailPtr(HANFUN_SMARTPLUG_INTERVAL,10);
			ColaMailPtr(HANFUN_SMARTPLUG_PERIODIC,cntpm++);
#endif
#endif

#ifdef HF_SENSOR
			SendApiPpUleDataReq (COLA_TASK, API_ULE_DLC_CTRL_ACKNOWLEDGED, 0, NULL);
#endif

			RosTimerStop( USER_SW_COUNTER_TIMER);
			RosTimerStart(USER_SW_COUNTER_TIMER, 1000, &UserTimerConfig);

			break;
		}
		break;
	}

	case API_PP_MM_REGISTRATION_COMPLETE_IND: {

		SetLED3(0);
		break;
	}

	case API_PP_MM_ACC_RIGHTS_TERM_IND: {
		Enable_Registration(ACCESS_CODE);
		// SetLED3(1);
		// ColaMailPtr(HANFUN_NVS_SET, 0);
		// ColaMail(HANFUN_NVS_SAVE);

		break;
	}

	case API_PP_MM_REGISTRATION_FAILED_IND: {

		Enable_Registration(ACCESS_CODE);

		// Sleep(TX_FAIL);

		break;
	}
	case API_PP_ULE_START_LOCATE_IND: {
		break;
	}

	case API_PP_VBATT_CFM: {

		break;
	}

	case API_PP_ULE_HAL_GET_PORT_CFM: {

		break;
	}

	case API_HAL_READ_CFM: {

		ApiHalReadCfmType* readcfm = (ApiHalReadCfmType*) p_mail;
		if(readcfm->Address==0x700) ColaMailPtr(HANFUN_NVS_SET, readcfm->Data[0]);

#ifdef HF_AC_OUTLET
		{
			ApiHalReadCfmType* HalReadCfm = (ApiHalReadCfmType*) p_mail;
			SmartPlugGetNvs(HalReadCfm->Length,HalReadCfm->Data);
		}
#endif
		break;
	}

	case API_HAL_WRITE_CFM: {
#ifdef HF_AC_OUTLET
		SmartPlugSetNvs();
#endif
		break;
	}

	case API_PP_MM_GET_ID_CFM: {
		break;
	}

	default: {
		break;
	}
	}
}
