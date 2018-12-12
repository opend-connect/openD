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

/****************************************************************************
*                              Macro definitions
****************************************************************************/
#define STATETBL_ENTRY( Proc, DebugText ) {Proc}

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/****************************************************************************
*                            Global variables/const
****************************************************************************/
DECL_STATE_FN(S_CfStateInit          );
DECL_STATE_FN(S_CfStateUnlocked      );
DECL_STATE_FN(S_CfStateRegistration  );
DECL_STATE_FN(S_CfStateStandby       );
DECL_STATE_FN(S_CfStateAlerting      );
DECL_STATE_FN(S_CfStateConnecting    );
DECL_STATE_FN(S_CfStateConnected     );

const CfStateTblType  CF_STATE_TBL[CF_STATE_TOTAL] =
{
  STATETBL_ENTRY( S_CfStateInit       ,    "INITIALIZING" ),
  STATETBL_ENTRY( S_CfStateUnlocked   ,    "UNLOCKED"     ),
  STATETBL_ENTRY( S_CfStateRegistration,   "REGISTRATION" ),
  STATETBL_ENTRY( S_CfStateStandby    ,    "STANDBY"      ),
 STATETBL_ENTRY( S_CfStateAlerting   ,    "ALERTING"     ),
  STATETBL_ENTRY( S_CfStateConnecting ,    "CONNECTING"   ),
  STATETBL_ENTRY( S_CfStateConnected  ,    "CONNECTED"    ),
};

CfSysCtrlType CfSysCtrl, *pCfSysCtrl;


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
* Name  : LiStateFnExec
* Input :
* Return:
*-------------------------------------------------------------------------
* Usage : From the state variable the function determines the the
*         appropriate state function and executes it (if valid)
**************************************************************************/
static void
CfStateFnExec( CfStateType n_State, CfMailType *p_Mail )
{
  CfStateFnType StateFn;

  if (n_State<CF_STATE_TOTAL)
  {
    StateFn = CF_STATE_TBL[ n_State ].StateFn;
    if (StateFn)
    {
      StateFn(p_Mail);
    }
  }
}

/*************************************************************************
* Name  : CfStateExec
* Input :
* Return:
*-------------------------------------------------------------------------
* Usage : From the state variable the function determines the the
*         appropriate state function and executes it (if valid)
**************************************************************************/
static void
CfStateExec(  CfMailType *p_Mail)
{
  CfStateType   s;

  s = CfGetState();

  CfStateFnExec(s,p_Mail);
}


/****************************************************************************
* Name   : LiStateExec_EvLeave
* Return :
*---------------------------------------------------------------------------
* Usage  :
****************************************************************************/
static void
CfStateExec_EvLeave( CfStateType n_State)
{
  CfInitTaskType EvMail;

  EvMail.Primitive=CF_S_LEAVE;
  CfStateFnExec(n_State,(void *) &EvMail);
}

/****************************************************************************
* Name   : LiStateExec_EvInit
* Return :
*---------------------------------------------------------------------------
* Usage  :
****************************************************************************/
static void
CfStateExec_EvInit( CfStateType n_State )
{
  CfInitTaskType EvMail;

  pCfSysCtrl->CfStateCtrl.CfState=n_State;
  pCfSysCtrl->CfStateCtrl.InitState=0;
  EvMail.Primitive=CF_S_INIT;
  CfStateFnExec(n_State,(void *) &EvMail);

  if (!CfIsStateChanged())
  {
    EvMail.Primitive=CF_S_ENTER;
    CfStateFnExec(n_State,(void *) &EvMail);
  }
}


/******************************************************************************
* Name   : CfStopStateTimer
* Input  :
*-----------------------------------------------------------------------------
* Usage  : Starts the STATE time-out timer for the specified
*          line-device.
******************************************************************************/
void
CfStartStateTimer(rsuint16 n_Time1Ms)
{
  if (n_Time1Ms==0)
  {
    n_Time1Ms=1;
  }
  RosTimerStart(CF_STATE_TIMER, n_Time1Ms, &ColaTimerCfgTable[ColaTimerCfgTableIdx(CF_STATE_TIMER)]);
}


/******************************************************************************
* Name   : CfStopStateTimer
* Input  : <LineId> PSTN line device id - NOT A OS TIMER ID
*-----------------------------------------------------------------------------
* Usage  : Stops the STATE time-out timer for the specified
*          line-device.
******************************************************************************/
void
CfStopStateTimer(void)
{
  RosTimerStop(CF_STATE_TIMER);
}

/****************************************************************************
* Name   : CfGetState
* Input  :
* Return :
*---------------------------------------------------------------------------
* Usage  :
****************************************************************************/
CfStateType
CfGetState(void)
{
  return(pCfSysCtrl->CfStateCtrl.CfState);
}

/****************************************************************************
* Name   : CfGetSubState
* Input  :
* Return :
*---------------------------------------------------------------------------
* Usage  :
****************************************************************************/
CfSubStateType
CfGetSubState(void)
{
  return(pCfSysCtrl->CfStateCtrl.CfSubState);
}

/****************************************************************************
* Name   : CfSetSubState
* Input  :
* Return :
*---------------------------------------------------------------------------
* Usage  :
****************************************************************************/
void CfSetSubState( CfSubStateType ss )
{
  pCfSysCtrl->CfStateCtrl.CfSubState = ss;
}

/****************************************************************************
* Name   : CfProcessMail
* Input  :
* Return :
*---------------------------------------------------------------------------
* Usage  : Processes a mail
****************************************************************************/
void
CfProcessMail( rsuint8 *p_Mail  )
{
  CfStateType   s,s_next;


  if (p_Mail!=NULL)
  {
    CfStateExec((CfMailType *) p_Mail);
  }


  while (pCfSysCtrl->CfStateCtrl.InitState)
  {
    s      = CfGetState();
    s_next = pCfSysCtrl->CfStateCtrl.NextState;
    if (s_next!=s)
    {
      CfStateExec_EvLeave(s);
    }

    CfStateExec_EvInit(s_next);
  }
}

/****************************************************************************
* Name   : CfSetStateExt_
* Input  :
* Return :
*---------------------------------------------------------------------------
* Usage  :
****************************************************************************/
void
CfSetStateExt_( CfStateType n_State,
                rsuint16      n_TimeOut)
{
  if (n_TimeOut!=CF_STATE_TIMEOUT_KEEP)
  {
    if (n_TimeOut>0)
    {
      CfStartStateTimer(n_TimeOut);
    }
    else
    {
      CfStopStateTimer();
    }
  }

  pCfSysCtrl->CfStateCtrl.NextState = n_State;
  pCfSysCtrl->CfStateCtrl.InitState = 1;
}

/****************************************************************************
* Name   : CfIsStateChanged
* Input  :
* Return :
*---------------------------------------------------------------------------
* Usage  :
****************************************************************************/
rsbool
CfIsStateChanged(void)
{
  return(pCfSysCtrl->CfStateCtrl.InitState==1);
}

/****************************************************************************
* Name   : CfSetState_
* Input  :
* Return :
*---------------------------------------------------------------------------
* Usage  :
****************************************************************************/
void
CfSetState_(CfStateType n_State)
{
  CfSetStateExt_(n_State,0);
}

/****************************************************************************
* Name   : CfEnterStateExt
* Input  :
* Return :
*---------------------------------------------------------------------------
* Usage  : Enters state <n_State> immediately. EV_INIT will be
*          executed for the new state
****************************************************************************/
void
CfEnterStateExt(CfStateType n_State, rsuint16 n_TimeOut)
{
  CfSetStateExt_(n_State,n_TimeOut);

  pCfSysCtrl->CfStateCtrl.InitState=1;

  CfProcessMail(NULL);    // NULL indicates that no mail is associated with
                            // the state-processing i.e. just run initialization
}

/****************************************************************************
* Name   : CfEnterState
* Input  :
* Return :
*---------------------------------------------------------------------------
* Usage  : Enters state <n_State> immediately. EV_INIT will be
*          executed for the new state
****************************************************************************/
void
CfEnterState(CfStateType n_State)
{
  CfEnterStateExt(n_State,0);
}


/*************************************************************************
* Name  : CfTaskInit
* Input :
* Return:
*-------------------------------------------------------------------------
* Usage :
**************************************************************************/
void CfTaskInit(void)
{
  CfMailType EvMail;
  pCfSysCtrl = &CfSysCtrl;

  pCfSysCtrl->CfStateCtrl.CfState    = CF_STATE_INIT;
  pCfSysCtrl->CfStateCtrl.NextState  = CF_STATE_INIT;
  pCfSysCtrl->CfStateCtrl.CfSubState = CF_SUB_STATE_NULL;
  pCfSysCtrl->CfStateCtrl.InitState  = FALSE;

 // for(i=0; i<sizeof(CfSysStatusType); i++)
 // {
 //   ((rsuint8*)&pCfSysCtrl->CfSysStatus)[i] = 0;
 // }
 // util_memset((void *)(&pCfSysCtrl->CfSysStatus), 0, sizeof(CfSysStatusType));

  EvMail.CfStateTaskMsg.Primitive = CF_S_INIT;
  CfStateFnExec(pCfSysCtrl->CfStateCtrl.CfState, (void *) &EvMail);
}

/*************************************************************************
* Name  : CfTaskHandler
* Input :
* Return:
*-------------------------------------------------------------------------
* Usage :
**************************************************************************/
void CfTaskHandler(const RosMailType* p_Mail)
{
  CfStateFnExec(pCfSysCtrl->CfStateCtrl.CfState, (CfMailType *)p_Mail);
}

// End of file.

