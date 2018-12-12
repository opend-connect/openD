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
/*! \file
* Definition of the ApiPpUlp interface.
*/


#ifndef APIPPULETYPES_H
#define APIPPULETYPES_H

/****************************************************************************
* Includes
****************************************************************************/
#include <Core/RtxCore.h>
#include <ProjCfg.h>
#include <Ros/RosCfg.h> 
#include <Ulp/ulpcfg.h>
#include <Ulp/Mng/iulpmng.h>
#include <DevDrv/Classes/Ulp/IDrvUlp.h>

/****************************************************************************
* Macro Definitions
****************************************************************************/

/****************************************************************************
* Macro Definitions - temp 
****************************************************************************/

#ifdef API_PP_ULE_OLD_TYPES

#define ApiPpUleMiInit(m,sm,suspm,dirm, trigm)    SendApiPpUleInitReqFix(API_PP_ULE_APP_TASK,m,sm,suspm,dirm,trigm)
#define ApiPpUleDiRegisterCb(CbFn)                SendApiPpUleRegisterCbReq(API_PP_ULE_APP_TASK,CbFn)  
#define ApiPpUleMiNvsReq(ptr,len,init)            SendApiPpUleNvsReq(API_PP_ULE_APP_TASK,init,len,ptr)
#define ApiPpUleMiSendServiceReq(a)               SendApiPpUleServiceReq(API_PP_ULE_APP_TASK,*a)  
#define ApiPpUleMiAcceptUlpService()              SendApiPpUleServiceAcceptReq(API_PP_ULE_APP_TASK)
#define ApiPpUleMiServiceLocateReq()              SendApiPpUleServiceLocateReq(API_PP_ULE_APP_TASK)
#define ApiPpUleMiSuspendReq(a)                   SendApiPpUleSuspendReq(API_PP_ULE_APP_TASK,a)
#define ApiPpUleMiInitCfm_t                       ApiPpUleInitCfmType
#define ApiPpUleMiNvsCfm_t                        ApiPpUleNvsCfmType 
#define ApiPpUleMiServiceCfm_t                    ApiPpUleServiceCfmType
#define ApiPpUleMiServiceAcceptCfm_t             ApiPpUleServiceAcceptCfmType

void ApiPpUleRegisterMps(const rsuint8 *p_ac);
void ApiPpUleStopRegisterMps(void);
void ApiPpUleLockMps(void);

#endif

/****************************************************************************
* Types 
****************************************************************************/



#endif // #ifndef APIPPULETYPES_H

