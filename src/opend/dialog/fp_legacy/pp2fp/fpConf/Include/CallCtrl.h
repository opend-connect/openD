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
#ifndef CALL_CTRL_H
#define CALL_CTRL_H

/****************************************************************************
*                               Include files
****************************************************************************/

#include <Core/RtxCore.h>
#include <Ros/RosCfg.h>
#include <Cola/Cola.h>

/****************************************************************************
*                              Macro definitions
****************************************************************************/
#define REG_TIMEOUT_TIME (180*RS_T1SEC)


/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/****************************************************************************
*                            Global variables/const
****************************************************************************/
extern CallStateInfoType CallState[NO_HANDSETS]; // HandsetId [1;6]
/****************************************************************************
*                            Local variables/const
****************************************************************************/

/****************************************************************************
*                          Local Function prototypes
****************************************************************************/

/****************************************************************************
*                                Implementation
***************************************************************************/
extern rsuint8 FindNoOfActiveCalls(void);
extern rsuint8 FindFirstActiveCall(void);
extern void CfSetCallState(rsuint8 HandsetId, CallStateType State);


extern rsuint8 LsGetLine(rsuint8 HandsetId, rsuint8 RequestLineId);
extern void ConnectAudioToLine(rsuint8 HandsetId, rsuint8 LineId);

extern void StartDelayAudioOpenTimer(rsuint8 LineId);
extern void StopDelayAudioOpenTimer(rsuint8 LineId);

extern void CallCtrlMailHandler( RosMailType* p_Mail);

extern void ApiFpCcSetupReq( ApiCallReferenceType CallReference, rsuint8 handsetId );
extern void SendHsLocator(void);
extern void StopHsLocating(void);
extern rsbool CheckPagingMode(void);

extern rsuint8 CfGetLineUserNo(rsuint8 LineId );
extern rsuint8 CfGetLineId(rsuint8 HandsetId );
#endif //CALL_CTRL_H
// End of file.
