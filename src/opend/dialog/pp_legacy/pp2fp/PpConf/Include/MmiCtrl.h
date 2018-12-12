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
#ifndef MMICTRL_H
#define MMICTRL_H

/****************************************************************************
*                               Include files
****************************************************************************/

/****************************************************************************
*                              Macro definitions
****************************************************************************/
#define REGISTRATION_TIMEOUT  (20*RS_T1SEC)//(180*RS_T1SEC)              //Registration Timeout: 3 minutes
#define CONNECTION_TIMEOUT    (30*RS_T1SEC)                 //Connection Timeout: 30 seconds
// #define MELODY_RELOAD_TIMEOUT (5*RS_T1SEC)                  //Melody reload Timeout: 5 seconds
#define UNMUTE_AUDIO_TIMEOUT  (1*RS_T1SEC)                  //Audio muted for 1 second after connected

#define FREE_ALL 0xFF

#define AUDIO_NUMBER_OF_VOL_STEPS   6
#define RINGER_NUMBER_OF_VOL_STEPS  10

#define DEFAULT_GROUP_ID 0x1234

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/
typedef struct {
  ApiCcBasicServiceType   MmiBasicService;
  ApiCcCallClassType      MmiCallClass;
  ApiSystemCallIdType     MmiIeSystemCallId;
  ApiCallStatusType       MmiIeCallStatus;
  ApiLineIdType           MmiIeApiLineId;
  ApiCallingNumberType*   MmiClipPtr;
  ApiCallingNameType*     MmiCnipPtr;
} MmiInstanceType;

/****************************************************************************
*                            Global variables/const
****************************************************************************/
extern rsuint8 VolAdjustDir;
/****************************************************************************
*                            Local variables/const
****************************************************************************/

/****************************************************************************
*                          Local Function prototypes
****************************************************************************/

/****************************************************************************
*                                Implementation
***************************************************************************/
extern void MmiShowLedStatus(void);
extern void SetupExtOutgoingCall( ApiCcConEiType MmiConEi, Ia5CharType pMultikeypad );
void MmiCcSetupIndGetCallCtrlPara( ApiCcSetupIndType *p_Mail );
extern void SetupIntOutgoingCall( ApiCcConEiType MmiConEi, rsuint8 DestHsId );
extern void HandleConnectReq(void);
extern void MmiHandleIntCallingPartyNumber(rsuint8 *InfoElement, rsuint16 InfoElementLength);

#endif //MMICTRL_H

