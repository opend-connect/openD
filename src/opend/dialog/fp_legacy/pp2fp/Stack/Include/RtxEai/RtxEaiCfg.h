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

#ifndef RTXEAICFG_H
#define RTXEAICFG_H

/****************************************************************************
*                               Include files
****************************************************************************/

#include <Ros/RosCfg.h>

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/******************************************************************************
*                           RTX EAI DRIVER / BUFFER                           *
******************************************************************************/

#define RTX_EAI_SUPPORT

#define RTX_EAI_NO_INSTANCES 1
#define RTX_EAI_HDLC_SUPPORT 0
#define RTX_EAI_REPS_SET_TL 0

#ifndef RTX_EAI_RX_BUFFER_SIZE
  #define RTX_EAI_RX_BUFFER_SIZE 0x100
#endif
#ifndef RTX_EAI_TX_BUFFER_SIZE
  #define RTX_EAI_TX_BUFFER_SIZE 0x100
#endif
#ifndef RTX_EAI_DATA_LOC
  #define RTX_EAI_DATA_LOC
#endif

// The RtxEai module sends an RTX_EAP_TARGET_RESET_IND from the RtxEaiInit()
// function when the following macro is defined.
#define RTX_EAI_SEND_RESET_IND_AT_INIT

// The RtxEai module sends an RTX_EAP_PACKET_CFM when a packet is received
// when the following macro is defined.
//#define RTX_EAI_SEND_PACKET_CFM

// The RtxEai module supports the RTX_EAP_PRINTF_XXX_REQ messages and printf
// messages are sent to the host / PC using the program id and task id sent
// in the RTX_EAP_PRINTF_START_REQ message
#define RTX_EAI_RSX_PRINTF_SUPPORT

// The following defines are used to configure the "log / trace" functionality
// in the RtxEai module.
#define RTX_EAI_PRINTF_BUFFER_SIZE          80 // The size of the temp buffer used by the printf() implementation in RtxEai.c
#define RTX_EAI_NO_OF_TASKS                 NULL_TASK
#define RTX_EAI_NO_OF_LOG_PRIMITIVES        8
#define RTX_EAI_NO_OF_EXCLUDE_PRIMITIVES    8
#define RTX_EAI_TRACE_INIT                  FALSE   // start trace at RtxEaiInit
//#define RTX_EAI_REINTRANT

//#define RTX_EAI_ALT_LOG_CH1_ID 0xF1
//#define RTX_EAI_ALT_LOG_CH2_ID 0xF2
//#define RTX_EAI_ALT_LOG_CH3_ID 0xF3

// The following defines are used to enable the trace functions in RtxEai.c:
#define RTX_EAI_LOG_TRACE_SUPPORT
#define RTX_EAI_LOG_COMMENT_SUPPORT
#define RTX_EAI_LOG_PDU_SUPPORT
#define RTX_EAI_LOG_FUNCTION_SUPPORT
#define RTX_EAI_LOG_RAW_DATA_SUPPORT
#define RTX_EAI_LOG_RUNTIMER_ERROR_SUPPORT
#define RTX_EAI_LOG_ASSERT_SUPPORT
#define RTX_EAI_LOG_TIMER_SUPPORT
#define RTX_EAI_LOG_RT_TIMER_SUPPORT
#define RTX_EAI_LOG_HEAP_SUPPORT
#define RTX_EAI_LOG_WATCH_SUPPORT
#define RTX_EAI_LOG_PRINTF_SUPPORT
#define RTX_EAI_LOG_CLEAR_SCREEN_SUPPORT
#define RTX_EAI_LOG_SCREEN_GOTOXY_SUPPORT

#ifdef PCCOMPILE
  #define RTX_EAI_PRINTF_TO_WIN32SIM
  #define RTX_EAI_LOG_COMMENT_TO_WIN32SIM
#endif


//#define RTX_EAI_MEMORY_READ_SUPPORT
//#define RTX_EAI_MEMORY_WRITE_SUPPORT
//#define RTX_EAI_MEMORY_MEMSET_SUPPORT
//#define RTX_EAI_MEMORY_SET_DEFAULT_SUPPORT
#define RTX_EAI_RAM_WRITE_SUPPORT
#define RTX_EAI_RAM_READ_SUPPORT
#define RTX_EAI_RAM_MEMSET_SUPPORT
//#define RTX_EAI_NVS_READ_SUPPORT
//#define RTX_EAI_NVS_WRITE_SUPPORT
//#define RTX_EAI_NVS_SET_DEFAULT_SUPPORT
//#define RTX_EAI_NVS_CACHE_EMPTY_SUPPORT


// The following defines are used to link "call back" functions in RtxEai.c
// with the application.
// Prototypes of the functions can be found i IRtxEai.h
#ifndef RTX_EAI_VSNPRINTF
  #ifdef __IAR_SYSTEMS_ICC__
    #if _ADDED_C_LIB
      #define RTX_EAI_VSNPRINTF vsnprintf
    #endif
    #ifdef _DLIB_CONFIG_FILE
      #define RTX_EAI_VSNPRINTF vsnprintf // we use the vsnprintf from the dlib!
    #endif
  #endif
#endif
#ifndef RTX_EAI_VSNPRINTF
  #define RTX_EAI_VSNPRINTF RtxEaiStdCfgVsnprintf
  rsuint16 RtxEaiStdCfgVsnprintf(char *dest, rsuint16 max, const char *format, va_list argptr);
#endif

//#define RTX_EAI_VSNPRINTF _vsnprintf

//#define RTX_EAI_TRACE_STARTED
//#define RTX_EAI_TRACE_STOPPED

//#define RTX_EAI_TRACE_SET_ALT_LOG_CH1 BtCoreInterfaceSetLogoptions
//#define RTX_EAI_TRACE_SET_ALT_LOG_CH2
//#define RTX_EAI_TRACE_SET_ALT_LOG_CH3

#define RTX_EAI_SEND_MAIL RtxEaiStdCfgSendMail
//#define RTX_EAI_SEND_MAIL_ALT_CH1
//#define RTX_EAI_SEND_MAIL_ALT_CH2
//#define RTX_EAI_SEND_MAIL_ALT_CH3

#define RTX_EAI_KEY_PRESS_HANDLER RtxEaiStdCfgSendKeyPress
//#define RTX_EAI_KEY_PRESS_HANDLER_ALT_CH1 BtCoreInterfaceSendKeyPress
//#define RTX_EAI_KEY_PRESS_HANDLER_ALT_CH2
//#define RTX_EAI_KEY_PRESS_HANDLER_ALT_CH3

/******************************************************************************
*                                PRODUCT TEST                                 *
******************************************************************************/
//#define RTX_EAI_NVS_READ              RtxEaiStdCfgEepromRead
//#define RTX_EAI_NVS_READ_NB
//#define RTX_EAI_NVS_WRITE             RtxEaiStdCfgEepromWrite
//#define RTX_EAI_NVS_WRITE_NB
//#define RTX_EAI_NVS_SET_DEFAULT       RtxEaiStdCfgEepromSetDefault
//#define RTX_EAI_NVS_GET_CACHE_STATE   EepromCacheEmpty
//#define RTX_EAI_DSP_READ
//#define RTX_EAI_DSP_WRITE
//#define RTX_EAI_DSP_MEMSET

//#define RTX_EAI_FPGA_READ
//#define RTX_EAI_FPGA_WRITE
//#define RTX_EAI_FPGA_MEMSET

//#define RTX_EAI_SEQUENCER_READ
//#define RTX_EAI_SEQUENCER_WRITE
//#define RTX_EAI_SEQUENCER_MEMSET

//#ifndef RTX_EAI_HW_TEST_HANDLER
//  #define RTX_EAI_HW_TEST_HANDLER EaiProductTestHandler
//#endif
//#define RTX_EAI_PROJECT_COMMAND_HANDLER RtxEaiCfgProjectCommandHandler


/******************************************************************************
*                            RTX EAI Driver config                            *
******************************************************************************/

#ifdef PCCOMPILE
  #define RTX_EAI_DRIVER_INIT                    RtxEaiRepsDrvInit
  #define RTX_EAI_DRIVER_TERMINATE               RtxEaiRepsDrvTerminate
  #define RTX_EAI_DRIVER_KICK                    RtxEaiRepsDrvReadPacket
  #define RTX_EAI_DRIVER_TX_GET_BUFFER           RtxEaiRepsDrvGetTxBuffer
  #define RTX_EAI_DRIVER_TX_DELIVER_BUFFER       RtxEaiRepsDrvDeliverTxBuffer
  #define RTX_EAI_DRIVER_TX_GET_SPACE            RtxEaiRepsDrvGetTxSpace
  #define RTX_EAI_DRIVER_TX_GET_TRACE_BUFFER     RtxEaiRepsDrvGetTraceBuffer
  #define RTX_EAI_DRIVER_TX_DELIVER_TRACE_BUFFER RtxEaiRepsDrvDeliverTraceBuffer
  #define RTX_EAI_DRIVER_TX_BUFFER_EMPTY         RtxEaiRepsDrvTxBufferEmpty
#else
  #define RTX_EAI_DRIVER_INIT                    RtxEaiDrvInit
  #define RTX_EAI_DRIVER_TERMINATE               RtxEaiDrvTerminate
//  #define RTX_EAI_DRIVER_KICK                    RtxEaiDrvKick
  #define RTX_EAI_DRIVER_TX_GET_BUFFER           RtxEaiDrvGetTxBuffer
  #define RTX_EAI_DRIVER_TX_DELIVER_BUFFER       RtxEaiDrvDeliverTxBuffer
  #define RTX_EAI_DRIVER_TX_GET_SPACE            RtxEaiDrvGetTxSpace
  #define RTX_EAI_DRIVER_TX_GET_TRACE_BUFFER     RtxEaiDrvGetTraceBuffer
  #define RTX_EAI_DRIVER_TX_DELIVER_TRACE_BUFFER RtxEaiDrvDeliverTraceBuffer
  #define RTX_EAI_DRIVER_TX_BUFFER_EMPTY         RtxEaiDrvTxBufferEmpty
#endif

/******************************************************************************
*                                  Mail log                                   *
******************************************************************************/

#define PRIM_ALLOW_JUMP

/******************************************************************************
*                                PC SIM / REPS                                *
******************************************************************************/

// This macro can be used in RtxEaiRepsDrv.c to get the name of the shared memory
// used by the RTX EAI Port Server.
#define RTX_EAI_REPS_SHM_NAME "COLAppsim"

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/****************************************************************************
*                           Global variables/const
****************************************************************************/

/****************************************************************************
*                             Function prototypes
****************************************************************************/

#endif

// End of file.

