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

#include <Core/RtxCore.h>
#include <Ros/RosCfg.h>
#include <Cola/Cola.h>
#include <Phoenix/Api/Api.h>
#include <Phoenix/Api/PpMm/ApiPpMm.h>
#include "system.h"
#include "CfState.h"
#include "LedCtrl.h"
#include "Util.h"
#include "MmiCtrl.h"

#include "keyMessage.h"


#include "opend_sub.h"

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/****************************************************************************
*                            Global variables/const
****************************************************************************/

/****************************************************************************
*                            Local variables/const
****************************************************************************/

/****************************************************************************
*                          Local Function prototypes
****************************************************************************/

/****************************************************************************
*                                Implementation
***************************************************************************/

/*************************************************************************
* FUNCTION:         S_PpStateRegistration
* INPUTS:           WtMailType *p_Mail
* OUTPUTS:          none
* DESCRIPTION:      State function, called when system is in "Registration" state
*************************************************************************/
DECL_STATE_FN(S_CfStateRegistration)
{
  openD_subApiCfm_t sConfirm;

  switch (((RosMailType *)p_Mail)->Primitive)
  {
    case CF_S_INIT:
      {
        //for simplicity do a auto registration.
        SendApiPpMmRegistrationAutoReq ( COLA_TASK,
                                         pCfSysCtrl->PpSysPara.bMacSubNo,
                                         pCfSysCtrl->Ac );

        RosTimerStart(REGISTRATION_TIMER, REGISTRATION_TIMEOUT, &ColaTimerCfgTable[ColaTimerCfgTableIdx(REGISTRATION_TIMER)]);
        MmiShowLedStatus();
      }
      break;

    case API_PP_MM_LOCKED_IND:
      pCfSysCtrl->PpSysPara.MmiMacLocked=TRUE;
      break;


    case KEY_MESSAGE:
      switch(((RosMailType *)p_Mail)->P1.P1)
      {
        case KEY_REG:
          SendApiPpMmRegistrationStopReq(COLA_TASK);            //stop searching
          pCfSysCtrl->PpSysPara.MmiMacLocked=FALSE;
          CfEnterState(CF_STATE_UNLOCKED);

          /* Send openD subscription confirmation to the application. */
          sConfirm.service = OPEND_SUBAPI_SUBSCRIBE;
          sConfirm.status = OPEND_STATUS_FAIL;
          openD_sub_confirmation( &sConfirm );
          break;
      }
      break;

   case TIMEOUT:
      switch (((RosMailType*)p_Mail)->Timeout.Parameter)
      {
        case REGISTRATION_TIMER:
          SendApiPpMmRegistrationStopReq(COLA_TASK);            //stop searching
          pCfSysCtrl->PpSysPara.MmiMacLocked=FALSE;
          CfEnterState(CF_STATE_UNLOCKED);

          /* Send openD subscription confirmation to the application. */
          sConfirm.service = OPEND_SUBAPI_SUBSCRIBE;
          sConfirm.status = OPEND_STATUS_FAIL;
          openD_sub_confirmation( &sConfirm );
          break;
      }
      break;

    case API_PP_MM_REGISTRATION_COMPLETE_IND:
      pCfSysCtrl->PpSysPara.MmiMacLocked=TRUE;
      pCfSysCtrl->PpSysPara.PpMmiPara.HandsetId = ((ApiPpMmRegistrationCompleteIndType*)p_Mail)->HandsetId;

      SendApiHalWriteReq( COLA_TASK,                                                      //save Audio volume and Audio Mode
                          AHA_NVS,
                          ColaNvsOffset+RSOFFSETOF(PpMmiParaType, HandsetId),
                          sizeof(rsuint8),
                          (rsuint8*)&(pCfSysCtrl->PpSysPara.PpMmiPara.HandsetId));

      CfEnterState(CF_STATE_STANDBY);

      /* Send openD subscription confirmation to the application. */
      sConfirm.service = OPEND_SUBAPI_SUBSCRIBE;
      sConfirm.param.handsetId.id = pCfSysCtrl->PpSysPara.PpMmiPara.HandsetId;
      sConfirm.status = OPEND_STATUS_OK;
      openD_sub_confirmation( &sConfirm );
      break;

    case API_PP_MM_REGISTRATION_FAILED_IND:
      pCfSysCtrl->PpSysPara.MmiMacLocked=FALSE;
      CfEnterState(CF_STATE_UNLOCKED);

      /* Send openD subscription confirmation to the application. */
      sConfirm.service = OPEND_SUBAPI_SUBSCRIBE;
      sConfirm.status = OPEND_STATUS_FAIL;
      openD_sub_confirmation( &sConfirm );
      break;

    case CF_S_LEAVE:
      RosTimerStop(REGISTRATION_TIMER);
      break;
  }
}

// End of file.

