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

#ifndef APIFPCCLOG_H
#define APIFPCCLOG_H

/****************************************************************************
*                               Include files
****************************************************************************/
//#include <Core/RtxCore.h>
#include <Phoenix/Api/FpCc/ApiFpCc.h>
#ifdef APICFG_LEGACY_TERMINALID_SUPPORT
  #include <Phoenix/Api/FpCc/ApiFpCc10.h>
#endif
#include <Phoenix/Api/Types/ApiIeTypesLog.h>
#include <Phoenix/Api/FpCc/ApiFpCcLogC.h>

/****************************************************************************
*                              Macro definitions
****************************************************************************/

#define APIFPCC_CUSTOM_LOG_START(s,m,t) ApiFpCcLogCStart(s,(const RosMailType*)m,t,iColor)
#ifdef APICFG_LEGACY_TERMINALID_SUPPORT
  #define APIFPCC_CUSTOM_LOG_START10(s,m,t) ApiFpCcLogCStart10(s,(const RosMailType*)m,t,iColor)
#endif
//#define APIFPCC_CUSTOM_LOG(x,y,z) ApiFpCcLogC(x,y,z)

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/****************************************************************************
*                           Global variables/const
****************************************************************************/

/****************************************************************************
*                             Function prototypes
****************************************************************************/

void ApiFpCcComLog(rsuint32 iSendingTaskId, rsuint32 iRecievingTaskId, rsuint32 iMailLength, rsuint8 *MailPtr, char *szText, rsuint32 *iColor);
#ifdef APICFG_LEGACY_TERMINALID_SUPPORT
void ApiFpCcLog10(rsuint32 iSendingTaskId, rsuint32 iRecievingTaskId, rsuint32 iMailLength, rsuint8 *MailPtr, char *szText, rsuint32 *iColor);
#endif
void ApiFpCcLog(rsuint32 iSendingTaskId, rsuint32 iRecievingTaskId, rsuint32 iMailLength, rsuint8 *MailPtr, char *szText, rsuint32 *iColor);


#endif

