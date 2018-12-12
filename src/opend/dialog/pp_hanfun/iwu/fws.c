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

#include <stdbool.h>
#include "mmi_def.h"
#include "log.h"


rsuint16	ColaRev = GIT_TAG_REV;
rsuint16	ColaBuildNo = BUILD_NUMBER;
rsuint8		ColaLinkDate[5] = {BUILD_DATE_ARRAY};
/*
const char SclName[] = SCL_DEVICENAME;
const ApiGuidType SclGuid = SCL_GUID;

#ifdef __IAR_SYSTEMS_ICC__
  #pragma location="FWSINFO"
#endif
const RS_ROOT_SYMBOL FwsInfoType FwsInfo __attribute__((section("FWSINFO"))) = { (GuidType*)&SclGuid, ColaLinkDate, SclName, (const char*)ReleaseLabel, { 'F', 'W', 'S', '\0' } };
*/

/****************************************************************************
 * Timers
 ****************************************************************************/

const RosTimerConfigType FWSTimerConfig = { COLA_TASK, { TIMEOUT, FWS_TIMER } };

#define FWS_TIMEOUT_INITIAL		1 * RS_T1SEC
#define FWS_TIMEOUT_XFER		1 * RS_T1SEC
#define FWS_TIMEOUT_REPEAT		2 * RS_T1SEC

void FwsSetNextAction(MdtFwsAction Action);
/****************************************************************************
 * Api Mail handler functions
 ****************************************************************************/

void FwsSendStartTransferCfm(void)
{
	FwsSetNextAction(MDT_FWS_START_TRANSFER_CFM);
	RosTimerStart(FWS_TIMER, FWS_TIMEOUT_INITIAL, &FWSTimerConfig);
}

void FwsApiFwsStatusInd(const ApiFwsStatusIndType *m)
{
	switch (m->FwsStatus) {
	case AF_STATUS_IDLE:
		LogString("############## FWS API: AF_STATUS_IDLE %u, setting Offset 0", m->Progress);
		MmiCtrl.FWS.Offst = 0;
		FwsSendStartTransferCfm();
		break;
	case AF_STATUS_RESUME:
		LogString("############## FWS API: AF_STATUS_RESUME %u, setting Offset %u", m->Progress, m->Progress);
		MmiCtrl.FWS.Offst = m->Progress;
		FwsSendStartTransferCfm();
		break;
	case AF_STATUS_ERASING:
		LogString("############## FWS API: AF_STATUS_ERASING %u", m->Progress);
		break;
	case AF_STATUS_WRITING:
		LogString("############## FWS API: AF_STATUS_WRITING %u", m->Progress);
		break;
	case AF_STATUS_CHECKING:
		LogString("############## FWS API: AF_STATUS_CHECKING %u", m->Progress);
		break;
	case AF_STATUS_BOOTING:
		LogString("$$$$$$$$$$$$$ FWS API: SUCCESS: AF_STATUS_BOOTING %u", m->Progress);
		FwsSetNextAction(MDT_FWS_RESULT_SUCCESS_IND);
		//MmiCtrl.FWS.Enabled = 0; // do not FWS disable here, done at reset (prevents unwanted msgs before reboot)
		break;
	case AF_STATUS_DONE:
		LogString("$$$$$$$$$$$$$ FWS API: SUCCESS: AF_STATUS_DONE %u", m->Progress);
		FwsSetNextAction(MDT_FWS_RESULT_SUCCESS_IND);
		SendApiFwsTerminateReq(COLA_TASK, true/*Reboot*/);
		//MmiCtrl.FWS.Enabled = 0; // do not FWS disable here, done at reset (prevents unwanted msgs before reboot)
		break;
	case AF_STATUS_FAILED:
		LogString("@@@@@@@@@@@@@ FWS API: upgrade FAIL %u", m->Progress);
		FwsSetNextAction(MDT_FWS_RESULT_FAILED_IND);
		SendApiFwsTerminateReq(COLA_TASK, true/*Reboot*/);
		//MmiCtrl.FWS.Enabled = 0; // do not FWS disable here, done at reset (prevents unwanted msgs before reboot)
		break;
	default:
		break;
	}
}

static void FwsSendNextExtData(const char* origin)
{
	//SendApiFwsWriteExtDataReq(COLA_TASK, MmiCtrl.FWS.Offst, MmiCtrl.FWS.len, MmiCtrl.FWS.DataBuf);
	SendApiFwsWriteReq(COLA_TASK, MmiCtrl.FWS.Offst, MmiCtrl.FWS.len, MmiCtrl.FWS.DataBuf);
	LogString("## FWS write offset: 0x%08X (%d) (%s)", MmiCtrl.FWS.Offst, MmiCtrl.FWS.Offst, origin);
	MmiCtrl.FWS.Ready = false;
	MmiCtrl.FWS.DataAvail = false;
	RosTimerStop(FWS_TIMER);
	if(MmiCtrl.FWS.Offst){ // In first sector write postpone send to allow time for possible sector erase
		MmiCtrl.FWS.Offst += MmiCtrl.FWS.len;
		FwsSetNextAction(MDT_FWS_XFER_SUCCESS_IND);
		RosTimerStart(FWS_TIMER, FWS_TIMEOUT_XFER, &FWSTimerConfig);
	}else{
		MmiCtrl.FWS.Offst += MmiCtrl.FWS.len;
		RosTimerStart(FWS_TIMER, 15*FWS_TIMEOUT_XFER, &FWSTimerConfig);
	}

}

void FwsApiFwsWriteExtDataCfm(const ApiFwsWriteExtDataCfmType *m)
{
	if (!MmiCtrl.FWS.Enabled)
		return;
	MmiCtrl.FWS.Ready = true;
	// is there data in the buf ready to WriteExt?
	if (MmiCtrl.FWS.DataAvail) {
		FwsSendNextExtData("API_FWS_WRITE_EXT_DATA_CFM");
	}
}

void FwsApiPpUleDataInd(const ApiPpUleDataIndType* m)
{
	RosTimerStop(FWS_TIMER);
	if (!MmiCtrl.FWS.Enabled)
		return;

	// detect DEADDEAD magic
	if (	(m->Length >= 8)
		&&	(m->Data[3] == MDT_FWS_ABORT_TRANSFER_REQ)
		&&	(m->Data[4] == 0xDE) && (m->Data[5] == 0xAD)
		&&	(m->Data[6] == 0xDE) && (m->Data[7] == 0xAD) )
	{
		LogString("## FWS 0xDEADDEAD: abort! offset: %d (API_PP_ULE_DATA_IND)", MmiCtrl.FWS.Offst);
		FwsAbort("0xDEADDEAD detected");
		return;
	}

	if (MmiCtrl.FWS.DataAvail) {
		LogString("## FWS old data not yet WriteExt: Drama! offset: %d (API_PP_ULE_DATA_IND)", MmiCtrl.FWS.Offst);
	}
	MmiCtrl.FWS.DataAvail = true;
	MmiCtrl.FWS.len = (rsuint16) m->Length;
	MmiCtrl.FWS.XferTimeouts = 0;
	rsuint16 cnt;
	for (cnt = 0; cnt < MmiCtrl.FWS.len; cnt++) {
		MmiCtrl.FWS.DataBuf[cnt] = m->Data[cnt];
	}
	// can we WriteExt this data right away?
	if (MmiCtrl.FWS.Ready) {
		FwsSendNextExtData("API_PP_ULE_DATA_IND");
	} else {
		LogString("############## FWS Not READY, postpone WriteExt");
	}
}

void FwsApiPpUleDataInd_MdtFws(const MmiUleData_MmiDataTypeFws* d)
{
	switch (d->Action)
	{
		case MDT_FWS_GET_VERSION_REQ:
			FwsSetNextAction(MDT_FWS_GET_VERSION_CFM);
			break;

		case MDT_FWS_START_TRANSFER_REQ:
			FwsStart();
			break;

		case MDT_FWS_ABORT_TRANSFER_REQ:
			FwsAbort("MDT_FWS_ABORT_TRANSFER_REQ");
			break;

		// not received on this end:
		case MDT_FWS_RESULT_SUCCESS_IND:
		case MDT_FWS_RESULT_FAILED_IND:
		case MDT_FWS_GET_VERSION_CFM:
		case MDT_FWS_START_TRANSFER_CFM:
		case MDT_FWS_ABORT_TRANSFER_IND:
		case MDT_FWS_XFER_SUCCESS_IND:
		case MDT_FWS_XFER_TIMEOUT_IND:
		case MDT_FWS_XFER_PENDED_ON_DTR_IND:
			break;
	}
}

void
FwsTriggerSwReset(const char* reason)
{
	LogString("Triggering SW Reset (%s)", reason);
	//WRITE_REG(0xFF5004,0x0080);
	//WRITE_REG(0xFF5004,0x0000);
}

void FwsTimeout()
{

	if (!MmiCtrl.FWS.Enabled)
		return;

	LogString("FWS TIMEOUT %d :  %i sec", FWS_TIMEOUT_XFER / 1000, MmiCtrl.FWS.XferTimeouts);

	if (MmiCtrl.isRegistered)
	{
		if (MmiCtrl.FWS.XferTimeouts >= 5)
		{
			FwsAbort("max XferTimeouts 5 reached");

			// if still no DTR seen, then we need to take stronger measures!
			if (MmiCtrl.PendTDR)
			{
				// TODO: Handle properly reset..
				// FwsTriggerSwReset("max XferTimeouts 5 reached + !DTR");
			}
			return;
		}
		++MmiCtrl.FWS.XferTimeouts;
		FwsSetNextAction(MDT_FWS_XFER_TIMEOUT_IND);
	}
	RosTimerStart(FWS_TIMER, FWS_TIMEOUT_REPEAT, &FWSTimerConfig);
}

/****************************************************************************
 * Other functions
 ****************************************************************************/

void FwsStart(void)
{
	LogString("### Enable FW upgrade process");

	SetLED4(0); // set LED4 off

	MmiCtrl.FWS.DataAvail = false;
	MmiCtrl.FWS.Ready = true;
	MmiCtrl.FWS.Enabled = true;
	MmiCtrl.FWS.Offst = 0;
	MmiCtrl.FWS.len = 0;
	MmiCtrl.FWS.XferTimeouts = 0;
	SendApiFwsInitReq(COLA_TASK, true);
	// response will be sent when we receive AF_STATUS_{IDLE,RESUME}

	if(MmiCtrl.pagingInitiated==API_ULE_DLC_DB_PAGE_MODE_0){
		LogString("Paging was disabled.. Enable paging..");
		PagingMode(API_ULE_DLC_DB_PAGE_MODE_2);
	}

}

void FwsAbort(const char* reason)
{
	LogString("### Abort FW upgrade process (%s)", reason);

	MmiCtrl.FWS.DataAvail = false;
	MmiCtrl.FWS.Ready = false;
	MmiCtrl.FWS.Enabled = false;
	MmiCtrl.FWS.Offst = 0;
	MmiCtrl.FWS.len = 0;
	MmiCtrl.FWS.XferTimeouts = 0;
	RosTimerStop(FWS_TIMER);
	SendApiFwsTerminateReq(COLA_TASK, false);

	FwsSetNextAction(MDT_FWS_ABORT_TRANSFER_IND);

}

void FwsFillDataPacket(MmiUlePdu_common_t* packet)
{
	// check if there is an action we want to send
	MdtFwsAction Action = (MmiCtrl.FWS.NextMsgAction >> 1);
	if (!Action)
	{
		LogString("No NextMsgAction, using default MDT_FWS_XFER_TIMEOUT_IND");
		Action = MDT_FWS_XFER_TIMEOUT_IND;
	}

	// mark it as being sent
	MmiCtrl.FWS.NextMsgAction = 0;

	MmiUleData_MmiDataTypeFwsOffs* d = (MmiUleData_MmiDataTypeFwsOffs*)&packet->Data[0];

	packet->Hdr.Length = sizeof(packet->Hdr.Type) + sizeof(packet->SensorType) + sizeof(packet->NextMess)
			+ sizeof(d->Action) + sizeof(d->Offset); // min length
	packet->Hdr.Type = MMI_DATA_TYPE_FWS;
#ifdef SENSOR_TYPE //HANFUN workaround
	packet->SensorType = SENSOR_TYPE; // P1 or DIN
	packet->NextMess = USRNVSFPCNT;
#endif

	d->Action = Action;
	d->Offset = MmiCtrl.FWS.Offst;
	char* what = "";
	switch (Action)
	{
		case MDT_FWS_GET_VERSION_CFM:
		{
			// override the outgoing msg type
			MmiUleData_MmiDataTypeFws* dfws = (MmiUleData_MmiDataTypeFws*)d;
			what = "MDT_FWS_GET_VERSION_CFM";
			packet->Hdr.Length += /*Offset = StackVersion + ColaRev*/ + sizeof(dfws->ColaBuildNo) + sizeof(dfws->ColaLinkDate); // add fields
			dfws->StackVersion = MmiCtrl.StackVersion;
			dfws->ColaRev = ColaRev;
			dfws->ColaBuildNo = ColaBuildNo;
			memcpy(dfws->ColaLinkDate, ColaLinkDate, 5);
			break;
		}
		case MDT_FWS_START_TRANSFER_CFM:
			what = "MDT_FWS_START_TRANSFER_CFM";
			break;
		case MDT_FWS_ABORT_TRANSFER_IND:
			what = "MDT_FWS_ABORT_TRANSFER_IND";
			break;
		case MDT_FWS_XFER_SUCCESS_IND:
			what = "MDT_FWS_XFER_SUCCESS_IND";
			break;
		case MDT_FWS_XFER_TIMEOUT_IND:
			what = "MDT_FWS_XFER_TIMEOUT_IND";
			break;
		case MDT_FWS_RESULT_SUCCESS_IND:
			what = "MDT_FWS_RESULT_SUCCESS_IND";
			break;
		case MDT_FWS_RESULT_FAILED_IND:
			what = "MDT_FWS_RESULT_FAILED_IND";
			break;
		case MDT_FWS_XFER_PENDED_ON_DTR_IND:
			what = "MDT_FWS_XFER_DTR_IND";
			break;

		// not sent from this end:
		case MDT_FWS_GET_VERSION_REQ:
		case MDT_FWS_START_TRANSFER_REQ:
		case MDT_FWS_ABORT_TRANSFER_REQ:
			break;
	}

	LogString("Sending %s ...", what);
}

void FwsSetNextAction(MdtFwsAction Action)
{
	// check if there was an action we did not send yet
	MdtFwsAction OldAction = (MmiCtrl.FWS.NextMsgAction >> 1);
	if (OldAction)
		LogString("NextMsgAction was MDT_FWS_0x%02x while trying to send MDT_FWS_0x%02x, using last.", OldAction, Action);

	MmiCtrl.FWS.NextMsgAction = (Action << 1);

	if ((MmiCtrl.PendTDR) || (MmiCtrl.islocked == 0))
	{
		LogString("DTR is still pending, XferTimeouts %i -> Cannot send MDT_FWS_0x%02x!", MmiCtrl.FWS.XferTimeouts, Action);

		return;
	}

	// apparently we can send it right away
	//SendData();
}

// EOF.

