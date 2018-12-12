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
#include "system.h"
#include "CfState.h"
#include "Util.h"
#include "LedCtrl.h"
#include "MmiCtrl.h"

#include "keyMessage.h"


#include "opend_sub.h"
#include "opend_call.h"

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/****************************************************************************
*                            Global variables/const
****************************************************************************/
const rsuint8 nvs_force_default_cmd[1] = {1};                                      //Force EEPROM default

/****************************************************************************
*                            Local variables/const
****************************************************************************/

/****************************************************************************
*                          Local Function prototypes
****************************************************************************/

/****************************************************************************
*                                Implementation
***************************************************************************/
DECL_STATE_FN(S_CfStateStandby)
{
  openD_subApiInd_t sIndication;
  openD_subApiCfm_t sConfirm;
  openD_callApiInd_t cIndication;

  switch(((RosMailType *)p_Mail)->Primitive)
  {
    case CF_S_ENTER:
      SendApiPpAudioMuteReq(COLA_TASK, API_MUTE_BOTH);
      SendApiPpAudioCloseReq(COLA_TASK);
      MmiShowLedStatus();
      break;

    case KEY_MESSAGE:
      switch(((RosMailType *)p_Mail)->P1.P1)
      {
        case KEY_HOOK:
          pCfSysCtrl->PpSysPara.DestHsId = ((RosMailP2Type *)p_Mail)->P2;
          CfEnterState(CF_STATE_CONNECTING);
          break;

        case KEY_MESSAGE_REQ_REG:
          CfEnterState(CF_STATE_REGISTRATION);
          break;

        case KEY_MESSAGE_REQ_DEREG:
          SendApiPpMmDeleteLocalRegistrationReq( COLA_TASK, pCfSysCtrl->PpSysPara.PpMmiPara.HandsetId );
          break;

        case KEY_MESSAGE_REQ_SET_AC:
          pCfSysCtrl->Ac[0] = ((RosMailP5Type *)p_Mail)->P2;
          pCfSysCtrl->Ac[1] = ((RosMailP5Type *)p_Mail)->P3;
          pCfSysCtrl->Ac[2] = ((RosMailP5Type *)p_Mail)->P4;
          pCfSysCtrl->Ac[3] = ((RosMailP5Type *)p_Mail)->P5;

          /* Send openD subscription confirmation to the application. */
          sConfirm.service = OPEND_SUBAPI_SET_AC;
          sConfirm.status = OPEND_STATUS_OK;
          openD_sub_confirmation( &sConfirm );
          break;
      }
      break;

    case API_PP_MM_UNLOCKED_IND:
      CfEnterState(CF_STATE_UNLOCKED);

      /* Send openD subscription indication to the application. */
      sIndication.service = OPEND_SUBAPI_SUBSCRIPTION_DELETE;
      openD_sub_indication( &sIndication );
      break;

    case API_CC_SETUP_IND:
        MmiCcSetupIndGetCallCtrlPara((ApiCcSetupIndType*) p_Mail);              // store CallClass, ConEi and BasicService for later use

        SendApiCcAlertReq ( COLA_TASK,                                          //RosTaskIdType Src,
                            pCfSysCtrl->PpSysPara.CallCtrlPara.ConEi,           //ApiCcConEiType ConEi,
                            0,                                                  //rsuint16 InfoElemenength,
                            NULL);                                              //rsuint8 InfoElement[1])

        CfEnterState(CF_STATE_ALERTING);

        /* Send openD call confirmation to the application. */
        cIndication.service = OPEND_CALLAPI_CONNECTION_STATUS_RINGING;
        openD_call_indication( &cIndication );
        break;
    case CF_S_LEAVE:
      break;
  }
}


// End of file.
