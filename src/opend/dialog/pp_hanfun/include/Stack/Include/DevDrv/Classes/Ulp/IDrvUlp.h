#ifndef IDRVULP_H
#define IDRVULP_H
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


/****************************************************************************
* Includes
****************************************************************************/
#include <DevDrv/RtxDevDrv.h>

/****************************************************************************
* Macro definitions                             
****************************************************************************/
// Define the version of the interface added by the class. This number MUST be 
// incremented whenever the class interface changes.
#define DRV_CLASS_ULP_ADDITIONAL_IF_VERSION  0x02

// Compose a common version number from both interface version numbers
#define DRV_CLASS_ULP_IF_VERSION ((DRV_BASECLASS_IF_VERSION << 8) + DRV_CLASS_ULP_ADDITIONAL_IF_VERSION)


/****************************************************************************
* Type definitions                  
****************************************************************************/
/****************************************************************************
*                     Enumerations/Type definitions/Structs                  
****************************************************************************/


// ***************************
// Class device ID's
// ***************************
typedef enum
{
   DRV_CLASS_ULP_SC144XX,
   
}  Drv_Class_Port_IdType;



// ***************************
// Device Driver Error Codes
// ***************************
typedef enum
{
   DRV_CLASS_ULP_ERR_NONE         = DRV_ERR_NONE,
   DRV_CLASS_ULP_ERR_UNSUPPORTED  = DRV_ERR_UNSUPPORTED,
   DRV_CLASS_ULP_ERR_NO_RESOURCES = DRV_ERR_NO_RESOURCES ,

   DRV_CLASS_ULP_ERR_FIRST = DRV_ERR_FIRST_CLASS_DEFINED_ERROR, //DRV_ERR_COMMON_ERROR_COUNT,   
   DRV_CLASS_ULP_ERR_NO_CLOCK,
   DRV_CLASS_ULP_ERR_SUSPEND_NOT_ALLOWED,


}  DrvClassUlpError_t;



/****************************************************************************
*  ULP driver
****************************************************************************/

typedef enum
{
  ULP_MODE_UNDEF = 0,
  ULP_MODE_UNSYNCHRONIZED,
  ULP_MODE_UNLOCKED_SYNCHRONIZED,  
  ULP_MODE_SYNCHRONIZED,
  ULP_MODE_OFF,


} UlpMode_t;

typedef enum
{
  ULP_PORT_DIR_MODE_UNDEF,
  ULP_PORT_DIR_MODE_IN_PULLUP,
  ULP_PORT_DIR_MODE_IN_PULLDOWN,
  ULP_PORT_DIR_MODE_OUT_H,
  ULP_PORT_DIR_MODE_OUT_L,

} UlpPortDirMode_t;


typedef enum
{
  ULP_PORT_MODE_UNDEF,
  ULP_PORT_TRIG_MODE_RISING_EDGE,
  ULP_PORT_TRIG_MODE_FALLING_EDGE,
  ULP_PORT_TRIG_MODE_ACTIV_HIGH_LEVEL,
  ULP_PORT_TRIG_MODE_ACTIV_LOW_LEVEL,

} UlpPortTrigMode_t;


typedef enum
{
  ULP_SLEEPMODE_UNDEF,
  ULP_SLEEPMODE_WAKEON_PORT_AND_TIMER,
  ULP_SLEEPMODE_WAKEON_PORT,
  ULP_SLEEPMODE_WAKEON_TIMER,          

} UlpSleepMode_t;

typedef enum
{
  ULP_WAKEUP_EVENT_UNDEF,
  ULP_WAKEUP_EVENT_NON_ULP,    //COLDSTART,
  ULP_WAKEUP_EVENT_PORT,   
  ULP_WAKEUP_EVENT_TIMER,      

} UlpWakeupEventType_t;


typedef enum
{
  ULP_TIMER_MODE_NORMAL,
  ULP_TIMER_MODE_DCF,

} UlpTimerMode_t;

typedef enum
{
  ULP_CALLBACK_REASON_WAKEUP,
  ULP_CALLBACK_REASON_XTAL_ON,            
  ULP_CALLBACK_REASON_SUSPEND_ENABLED,
  ULP_CALLBACK_REASON_SLEEP_REQUESTED,
  ULP_CALLBACK_REASON_SET_WAKEUP_TIME,
  
} UlpCallbackReason_t;

typedef enum
{
  ULP_SIM_CMD_SET_WAKEUP_EVENT,

} UlpSimCmdId_t;

typedef rsuint32 UlpTimerVal_t;

// ***************************
// Device Driver Commands
// ***************************
typedef void                 (*DrvClassUlpSetModeFn_t)(UlpMode_t n_mode);
typedef UlpMode_t            (*DrvClassUlpGetModeFn_t)(void);
typedef void                 (*DrvClassUlpSetPortDirModeFn_t)(UlpPortDirMode_t  n_mode);
typedef void                 (*DrvClassUlpSetPortTrigModeFn_t)(UlpPortTrigMode_t n_mode);
typedef void                 (*DrvClassUlpSetSleepModeFn_t)(UlpSleepMode_t n_mode);
typedef void                 (*DrvClassUlpEnableSuspendFn_t)(void);
typedef DrvErrorType         (*DrvClassUlpSuspendFn_t)(DrvSuspendType n_Suspend);
typedef DrvErrorType         (*DrvClassUlpUnsolicitedSuspendFn_t)(void);
typedef void                 (*DrvUlpWaitUleClkEdgeFn_t)(void);
typedef UlpTimerVal_t        (*DrvClassUlpGetTimerFn_t)(void);
typedef UlpWakeupEventType_t (*DrvClassUlpGetWakeupEventFn_t)(void);
typedef void                 (*DrvClassUlpSetCalibrationFn_t)(rsbool l_on);
typedef void                 (*DrvClassUlpSetTimerModeFn_t)(UlpTimerMode_t n_mode);
typedef rsuint16             (*DrvClassUlpGetCalibrationPhaseFn_t)(void);


typedef void                 (*DrvClassUlpSetWakeupTimeFn_t)(UlpTimerVal_t n_val);
typedef void                 (*DrvClassUlpSetTriggerTimeFn_t)(rsuint16 n_val);
typedef rsuint16             (*DrvClassUlpGetTriggerTimeFn_t)(void);
typedef rsbool               (*DrvClassUlpIsUlpWakeupFn_t)(void);
typedef void                 (*DrvUlpEnableTriggerFn_t)(rsbool Enable);




// ***************************
// Device Driver Command Table
// ***************************
typedef struct DrvClassUlp_CmdData_s
{
  // mandatory interface
  DrvCdiType                           Cdi; 
   
  // class interface
  DrvClassUlpSetModeFn_t               SetMode;
  DrvClassUlpGetModeFn_t               GetMode;
  DrvClassUlpSetPortDirModeFn_t        SetPortDir;
  DrvClassUlpSetPortTrigModeFn_t       SetPortTrig;

  DrvClassUlpSetSleepModeFn_t          SetSleepMode;
  DrvClassUlpEnableSuspendFn_t         EnableSuspend;
  DrvClassUlpSuspendFn_t               Suspend;
  DrvClassUlpUnsolicitedSuspendFn_t    UnsolicitedSuspend;
  DrvUlpWaitUleClkEdgeFn_t             WaitUleClkEdge;
  DrvClassUlpSetTimerModeFn_t          SetTimerMode;
  DrvClassUlpGetTimerFn_t              GetTimer;
  
  DrvClassUlpSetWakeupTimeFn_t         SetWakeupTime;
  DrvClassUlpGetTimerFn_t              GetWakeupTime;
      
  DrvClassUlpGetWakeupEventFn_t        GetWakeupEvent;
  DrvClassUlpIsUlpWakeupFn_t           IsUlpWakeup;

  DrvClassUlpSetCalibrationFn_t        SetCalibration;
  DrvClassUlpGetCalibrationPhaseFn_t   GetPhase;

  DrvClassUlpSetTriggerTimeFn_t        SetTriggerTime;
  DrvClassUlpGetTriggerTimeFn_t        GetTriggerTime;
  DrvUlpEnableTriggerFn_t              EnableTrigger;   
 
} DrvClassUlp_CmdData_t;

typedef  const DrvClassUlp_CmdData_t  * DrvClassUlp_CmdData_Ptr_t;


/****************************************************************************
*  END OF FILE (IDRVULP.H) 
****************************************************************************/

#endif // #ifndef IDRVULP_H
