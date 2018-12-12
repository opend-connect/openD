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

#ifndef ULPCFG_H
#define ULPCFG_H

/****************************************************************************
*                              Macro definitions                              
****************************************************************************/

//#define ULP_ENABLE_DBG_REG_DUMP
#define BREAK_AFTER_DUMP    TRUE
#define CONTINUE_AFTER_DUMP FALSE 

//#define ULP_ENABLE_DBG_MAILS 

#define  ULP_CFG_NVS_START_ADDRESS  EENIR_OFFS(UlpData)
#define  ULP_CFG_NVS_SIZE           sizeof(UlpNvsData_t)

// Let's MMI transmit datatx counter
//  instead of the pot. value
//#define ULP_MMI_USE_TXDATA_COUNTER

// *** Enable's ULP function logging

// Enable log to ULP API functions 
//#define ULP_ENABLE_DBG_LOG_API_FCN

// Enable log to ULP manager functions
//#define ULP_ENABLE_DBG_LOG_MNG_FCN

// Enable log to ULP Driver functions
//#define ULP_ENABLE_DBG_LOG_DRV_FCN

// Put call time in log
//#define ULP_ENABLE_DBG_LOG_FCN_TIME

// Put Callers address in log
#define ULP_ENABLE_DBG_LOG_FCN_RETURN

// Define ULP log length 
#define ULPDBG_LOG_ARR_LENGTH  64 

#ifdef ULP_ENABLE_DBG_LOG_API_FCN
  #define ULP_ENABLE_DBG_LOG_FCN
#endif
#ifdef ULP_ENABLE_DBG_LOG_MNG_FCN
  #define ULP_ENABLE_DBG_LOG_FCN
#endif
#ifdef ULP_ENABLE_DBG_LOG_DRV_FCN
  #define ULP_ENABLE_DBG_LOG_FCN
#endif

/****************************************************************************
*                     Enumerations/Type definitions/Structs                   
****************************************************************************/



#ifdef ULP_ENABLE_DBG_LOG_FCN  
  typedef void (*UlpDbgFcnPtrType) (void);

  typedef struct { 
	UlpDbgFcnPtrType fcn;
	#ifdef ULP_ENABLE_DBG_LOG_FCN_RETURN
	  UlpDbgFcnPtrType ret;
    #endif
    #ifdef ULP_ENABLE_DBG_LOG_FCN_TIME
	  RsTimerTickType  tim;
    #endif
  } UlpDbgFcnArrType;
#endif

/****************************************************************************
*                            Global variables/const                           
****************************************************************************/

/****************************************************************************
*                             Function prototypes
****************************************************************************/

#ifdef ULP_ENABLE_DBG_LOG_FCN      
  #ifndef PCCOMPILE
    extern void UlpDbgFcnLog(UlpDbgFcnPtrType *Fcn, RsRaType ra);
    
    #ifdef ULP_ENABLE_DBG_LOG_API_FCN
      #define ULP_DBG_LOG_API_FCN(f)  UlpDbgFcnLog((UlpDbgFcnPtrType*)&f,RsReturnAddress()); 
    #else
      #define ULP_DBG_LOG_API_FCN(f)
    #endif

    #ifdef ULP_ENABLE_DBG_LOG_MNG_FCN
      #define ULP_DBG_LOG_MNG_FCN(f)  UlpDbgFcnLog((UlpDbgFcnPtrType*)&f,RsReturnAddress()); 
    #else
      #define ULP_DBG_LOG_MNG_FCN(f)
    #endif

    #ifdef ULP_ENABLE_DBG_LOG_DRV_FCN
      #define ULP_DBG_LOG_DRV_FCN(f)  UlpDbgFcnLog((UlpDbgFcnPtrType*)&f,RsReturnAddress()); 
    #else
      #define ULP_DBG_LOG_DRV_FCN(f)
    #endif

  #else
    #define ULP_DBG_LOG_API_FCN(f)
    #define ULP_DBG_LOG_MNG_FCN(f)
    #define ULP_DBG_LOG_DRV_FCN(f)
  #endif
#else
  #define ULP_DBG_LOG_API_FCN(f)
  #define ULP_DBG_LOG_MNG_FCN(f)
  #define ULP_DBG_LOG_DRV_FCN(f)
#endif 

#ifdef ULP_ENABLE_DBG_REG_DUMP
  extern void DumpAllRegisters(rsbool DoBreak);
#endif 

#ifdef ULP_ENABLE_DBG_MAILS
  extern void UlpDbgMails(RosPrimitiveType Primitiv);
#endif

#endif //  #ifndef ULPCFG_H

