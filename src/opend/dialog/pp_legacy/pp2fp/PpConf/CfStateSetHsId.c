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
#include "LedCtrl.h"
// #include "keyboardcfg.h"
#include "ApiHelper.h"
#include "Util.h"
#include "MmiCtrl.h"

#include "keyMessage.h"

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
****************************************************************************/
/*************************************************************************
* FUNCTION:         S_CfStateSetHsId
* INPUTS:           CfMailType *p_Mail
* OUTPUTS:          none
* DESCRIPTION:      State function, called when system is in "SET_HS_ID" state.
*************************************************************************/
DECL_STATE_FN(S_CfStateSetHsId)
{
  switch (((RosMailType *)p_Mail)->Primitive)
  {
    case CF_S_ENTER:
      MmiShowLedStatus();
      break;

    case KEY_MESSAGE:
      switch(((RosMailType *)p_Mail)->P1.P1)
      {
        case KEY_REG:
          if(pCfSysCtrl->PpSysPara.PpNvsPara.HsId>0&&pCfSysCtrl->PpSysPara.PpNvsPara.HsId<NO_HANDSETS)                   //handset ID not set yet
          {
            SendApiPp2ppEnterReq(COLA_TASK, pCfSysCtrl->PpSysPara.PpNvsPara.WtGroupId, pCfSysCtrl->PpSysPara.PpNvsPara.HsId);
          }
          break;

        case KEY_1:
        case KEY_2:
        case KEY_3:
        case KEY_4:
        case KEY_5:
        case KEY_6:
        case KEY_7:
          pCfSysCtrl->PpSysPara.PpNvsPara.HsId=((RosMailType *)p_Mail)->P1.P1-KEY_1+1;
          SendApiPp2ppEnterReq(COLA_TASK, pCfSysCtrl->PpSysPara.PpNvsPara.WtGroupId, pCfSysCtrl->PpSysPara.PpNvsPara.HsId);
          break;

        case KEY_DEFAULT:                                               //force EEPROM default
          util_memset((rsuint8*)&(pCfSysCtrl->PpSysPara.PpNvsPara), 0xFF, sizeof(PpNvsParaType));     //force EEPROM default
          SendApiProdTestReq(COLA_TASK, PT_CMD_NVS_DEFAULT, 1, (rsuint8  *)nvs_force_default_cmd);  //force default
          CfEnterState(CF_STATE_INIT);
          break;
      }
      break;

    case API_PP2PP_ENTER_CFM:
      CfEnterState(CF_STATE_STANDBY);
      break;

    case CF_S_LEAVE:
      SendApiHalWriteReq( COLA_TASK,                                                                //save everything -- Handset Id, Audio volume and Audio Mode
                          AHA_NVS,
                          ColaNvsOffset,
                          sizeof(PpNvsParaType),
                          (rsuint8*)&(pCfSysCtrl->PpSysPara.PpNvsPara));
      break;
  }
}


// End of file.

