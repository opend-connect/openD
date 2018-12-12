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

#ifndef IULPMNG_H
#define IULPMNG_H

/****************************************************************************
* Includes
****************************************************************************/
#include <Core/RtxCore.h>
#include <ProjCfg.h>
#include <Ros/RosCfg.h> 
#include <Ulp/ulpcfg.h>
#include <DevDrv/RtxDevDrv.h>


/****************************************************************************
* Macro Definitions
****************************************************************************/

/****************************************************************************
* Types 
****************************************************************************/

typedef enum
{
  ULP_MNG_SUSPEND_MODE_SLEEP     = DRV_SUSPEND_SLEEP,    // 1to1 map   
  ULP_MNG_SUSPEND_MODE_HIBERNATE = DRV_SUSPEND_HIBERNATE, // 1to1 map 

} UlpMngSuspendMode_t;


typedef struct
{
  RosTaskIdType     TaskId;

} RosTaskExtConfig_t;

extern RS_CONST RosTaskExtConfig_t RosTaskExtConfig[];

typedef enum
{
  ULP_NVS_CLIENT_ULP_MNG=0,
  ULP_NVS_CLIENT_MAC,
  ULP_NVS_CLIENT_ULP_DLC,  
  ULP_NVS_CLIENT_APP,    
  ULP_NVS_CLIENT_CNT,

} UlpNvsClientId_t;

typedef enum
{
  ULE_MNG_AS_UNDEF=       0x00,
  ULE_MNG_APP_ONLY=       0x01,  
  ULE_MNG_QS_PAGE_CHECK=  0x02,
  ULE_MNG_KEEP_ALIVE=     0x04,  
} UlpMngActionFlags_t;

typedef struct 
{  
  rsuint16  PageCheck;  
  rsuint16  AppSart;
  rsuint16  keepAlive;
} UlpMngStartUpCounters_t;


/****************************************************************************
* 
****************************************************************************/

typedef void                  (*UlpMngSetSuspendModeFn_t)(UlpMngSuspendMode_t n_Mode);
typedef UlpMngSuspendMode_t   (*UlpMngGetSuspendModeFn_t)(void);
typedef DrvErrorType          (*UlpMngSuspendFn_t)(void);
typedef DrvErrorType          (*UlpMngGoToSleepFn_t)(void);
typedef rsuint32              (*UlpMngGetSuspendTimeFn_t)(void);
typedef void                  (*UlpMngSetSuspendTimeFn_t)(rsuint32 TimeRef);
typedef rsbool                (*UlpMngCalcAndSuspendFn_t)(rsuint32 Time);
typedef void                  (*UlpMngAdjustWakeupTimeFn_t)(rsuint32 Time);
typedef void                  (*UlpMngSetStartupCountersFn_t)(UlpMngStartUpCounters_t Counters);

typedef rsuint8               (*UlpMngGetActionFlagsFn_t)(void);
typedef rsbool                (*UlpMngIsActionFlagsSetFn_t)(rsuint8 Flags);

typedef rsuint16              (*UlpMngGetWakeUpCountFn_t)(void);


typedef void         (*UlpMngNvsSetupFn_t)(UlpNvsClientId_t client_id,  rsuint8 *p_data, rsuint16 n_len);
typedef rsbool       (*UlpMngNvsGetFn_t)(UlpNvsClientId_t client_id,  rsuint8 *p_data, rsuint16 n_len);
typedef rsuint16     (*UlpMngNvsGetSizeFn_t)(UlpNvsClientId_t client_id);


typedef void         (*UlpMngNvsGet2Fn_t)(UlpNvsClientId_t client_id,  rsuint8 *p_data);
typedef void         (*UlpMngNvsSet2Fn_t)(UlpNvsClientId_t client_id,  rsuint8 *p_data, rsuint16 n_len);


typedef void         (*UlpMngPortEventFn_t)(void);

extern RS_CONST UlpMngPortEventFn_t UlpMngPortEventFn[];


typedef struct UlpMng_CmdData_s
{
  // mandatory interface
  DrvCdiType                   Cdi; 
  
  UlpMngSetSuspendModeFn_t     SetSuspendMode;
  UlpMngGetSuspendModeFn_t     GetSuspendMode;  
  UlpMngSuspendFn_t            Suspend;  
  UlpMngGoToSleepFn_t          GoToSleep;
  UlpMngGetSuspendTimeFn_t     GetSuspendTime;
  UlpMngSetSuspendTimeFn_t     SetSuspendTime;
  UlpMngCalcAndSuspendFn_t     CalcAndSuspend; 
  UlpMngAdjustWakeupTimeFn_t   AdjustWakeupTime;

  UlpMngNvsGetFn_t             NvsGet;       // Restore 
  UlpMngNvsSetupFn_t           NvsSetup;     // Init
  UlpMngNvsGetSizeFn_t         NvsGetSize;
  UlpMngNvsGet2Fn_t            NvsGet2;     // Get
  UlpMngNvsSet2Fn_t            NvsSet2;     // Set
  
  UlpMngSetStartupCountersFn_t SetStartUpCounters;  
  UlpMngGetActionFlagsFn_t     GetActionFlags;
  UlpMngIsActionFlagsSetFn_t   IsActionFlagsSet;
  UlpMngGetWakeUpCountFn_t     GetWakeUpCount;
} UlpMng_CmdData_t;

typedef const UlpMng_CmdData_t * UlpMng_CmdData_Ptr_t;

UlpMng_CmdData_Ptr_t UlpMng_GetInterface(void);



#endif // #ifndef IULPMNG_H

