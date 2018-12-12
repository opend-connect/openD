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
*
* \section startup_sequence Startup Sequence
*
* The variable \ref RsRunLevel tracks the current system state.
*
* The following listing shows the startup sequence, along with the functions
* performed by the Core and the hook functions called.
*
* - Execution starts from RsEntryPoint (if powerup or hardware reset)
* - Setup stack pointer.
* - Call RsHookColdStart().
* - Execution starts from RsWarmStart (if last shutdown requested warmstart)
* - Setup stack pointer.
* - Configure CPU (setup interrupt vectors etc.).
* - Call RsHookWarmStart().
* - Fill stacks with known pattern.
* - Call RsHookCacheInit().
* - Perform segment initialization (zero-initialized variables).
* - Perform segment initialization (copy-initialized variables).
* - Call constructors of static objects.
* - Execution starts from RsMain (RsRunStartup).
* - Initialize RsLocks module.
* - Initialize RsError module.
* - Initialize heap.
* - Initialize FOS.
* - Initialize ROS.
* - Call RsHookReady().
* - Enable interrupts globally.
* - Run ROS and FOS.
* - Call RsHookPreTask().
* - Call ROS task init functions.
* - Call RsHookRunning().
*
* \section shutdown_sequence Shutdown Sequence
*
* The following listing shows the shutdown sequence, executed when \ref RsShutdown is called.
*
* - \ref RsShutdown called.
* - (wait for all ROS tasks terminated).
* - Disable interrupts globally.
* - Call RsHookExit().
* - Execution starts from RsExit.
* - Call destructors of static objects.
* - Call RsHookDead() (executes \ref RsShutDownActionType).
*
* \section hooks Hook functions (callbacks)
*
* Hook functions are called from the Core at strategic places,
* and allow the application to initalize and also monitor the Core operation.
* The application simply implements the hook functions it wants.
* Unused (or empty) hook functions does not need to be implemented in the application.
*
* <hr>
*
*/


#ifndef RS_RUN_H
#define RS_RUN_H

/****************************************************************************
*                               Include files
****************************************************************************/

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/// The \ref RsRunLevel, corresponding to the <i>boot sequence</i> described above.
typedef enum RSENUMTAG(RsRunLevelType)
{
  RRL_ENTRYPOINT        = 0x00, /*!< At RsEntryPoint. */
  RRL_HOOK_COLDSTART    = 0x01, /*!< Calling \ref RsHookColdStart. */
  RRL_WARMSTART         = 0x02, /*!< At RsWarmStart. */
  RRL_HOOK_WARMSTART    = 0x03, /*!< Calling \ref RsHookWarmStart. */
  RRL_CPU_CONFIG        = 0x04, /*!< Configuring CPU (interrupt table pointer etc.). */
  RRL_FILL_STACKS       = 0x05, /*!< Fill stack(s) with known pattern. */
  RRL_SEG_ZERO_INIT     = 0x06, /*!< Performing segment initialization (zero-initialized variables). */
  RRL_SEG_COPY_INIT     = 0x07, /*!< Performing segment initialization (copy-initialized variables). */
  RRL_FIXUP             = 0x08, /*!< Performing fixup of functions in RAM. */
  RRL_CONSTRUCT_OBJECTS = 0x09, /*!< Calling constructors of static objects. */
  RRL_MAIN              = 0x0A, /*!< Calling main(). */
  RRL_CRASH_DUMP        = 0x0B, /*!< Crash dump in progress. */
  RRL_RS_EXIT           = 0x0C, /*!< At RsExit. */
  RRL_DESTRUCT_OBJECTS  = 0x0D, /*!< Calling destructors of static objects. */
  RRL_HOOK_DEAD         = 0x0E, /*!< Calling RsHookDead() (executes RosShutDownActionType). */
  RRL_INIT_LOCKS        = 0x0F, /*!< Initializing the RsLocks module. */
  RRL_INIT_ERROR        = 0x10, /*!< Initializing the RsError module. */
  RRL_CHECK             = 0x11, /*!< This value is deprecated in Core v3.x. */
  RRL_INIT_HEAP         = 0x12, /*!< Call \ref RcHeapInit(). */
  RRL_HOOK_PREINIT      = 0x13, /*!< Deprecated. */
  RRL_INIT_ROS          = 0x14, /*!< Initializing FOS. */
  RRL_INIT_FOS          = 0x15, /*!< Initializing ROS. */
  RRL_HOOK_READY        = 0x16, /*!< Calling RsHookReady(). */
  RRL_RUNNING           = 0x17, /*!< Running. */
  RRL_SHUTDOWN          = 0x18, /*!< \ref RsShutdown requested. */
  RRL_CLEANUP_FOS       = 0x19, /*!< Terminating FOS. */
  RRL_CLEANUP_ROS       = 0x1A, /*!< Terminating ROS. */
  RRL_CLEANUP_HEAP      = 0x1B, /*!< Terminating heap. */
  RRL_CLEANUP_ERROR     = 0x1C, /*!< Terminating the RsError module. */
  RRL_CLEANUP_LOCKS     = 0x1D, /*!< Terminating the RsLocks module. */
  RRL_HOOK_EXIT         = 0x1E, /*!< Calling RsHookExit(). */
  RRL_MAX
} RSENUM8(RsRunLevelType);

/// Shutdown reasons.
typedef enum RSENUMTAG(RsShutDownReasonType)
{
  RSR_NONE,           /*!< None (shutdown not in progress). */
  RSR_ERROR,          /*!< Shutdown because of an \ref RsError. */
  RSR_USER_REQUESTED, /*!< The user requested shutdown e.g. power off button. */
  RSR_EXT_CMD,        /*!< External command (e.g. from test bus). */
  RSR_LOW_BATTERY,    /*!< Battery level too low. */
  RSR_USB_SUSPEND,    /*!< USB suspend was ordered. */
  RSR_FWU_DONE,       /*!< Firmware Update done. */
  RSR_LINK_LOST,      /*!< Communication link lost. */
  RSR_SIGNAL,         /*!< A signal was received e.g. SIGTERM. */
  RSR_CUSTOM = 0x80,  /*!< Application/project specific reasons. */
  RSR_MAX
} RSENUM8(RsShutDownReasonType);

/// Shutdown actions.
typedef enum RSENUMTAG(RsShutDownActionType)
{
  RSA_NONE,           /*!< None (shutdown not in progress). */
  RSA_POWER_OFF,      /*!< Power off (release power latch). */
  RSA_HW_RESET,       /*!< Perform a hardware reset. */
  RSA_WARMSTART,      /*!< Perform a warmstart. The value of \ref RS_NO_INIT variables are preserved. */
  RSA_MAX
} RSENUM8(RsShutDownActionType);

/****************************************************************************
*                           Global variables/const
****************************************************************************/

RS_BEGIN_EXTERN_C

/// Run level.
extern RS_DATA_ADR volatile RsRunLevelType RsRunLevel;

/// Shutdown reason.
extern RS_DATA_ADR RsShutDownReasonType RsShutDownReason;

/// Shutdown action.
extern RS_DATA_ADR RsShutDownActionType RsShutDownAction;

/// Shutdown source.
extern RS_DATA_ADR RsRaType RsShutDownRa;

/****************************************************************************
*                             Function prototypes
****************************************************************************/

/** \cond internal */

/// Perform system startup (only heavy-OS targets).
/** Initiates system startup. */
void RsStartup(void);

/// Perform post-dead cleanup (only heavy-OS targets).
/** Performs system cleanup. */
void RsCleanup(void);

// Deprecated.
#define RsHookPreInit !disabled

/** \endcond */

/// Perform warm startup.
/** Initiates system warm-startup. */
void RsWarmStart(void);

/// Shutdown handler.
/** Initiates system shutdown, by sending a mail with \ref ROS_SHUTDOWN_MAIL_PRIMITIVE to all ROS tasks.
* \a Action is performed when shutdown is complete.
* \param Reason The reason for the shutdown.
* \param Action The action to perform when shutdown is complete. */
void RsShutdown(RsShutDownReasonType Reason, RsShutDownActionType Action);

#if (RS_HOOK_COLD_START == 1)
/// Cold startup. This function is called when \ref RS_HOOK_COLD_START is set to 1.
/** This function is for initializing \ref RS_NO_INIT variables, and noting else.
* Only the stack pointer is setup at this point. Called from the bootcode. */
void RsHookColdStart(void);
#else
  #define RsHookColdStart !disabled
#endif

#if (RS_HOOK_WARM_START == 1)
/// Warm startup. This function is called when \ref RS_HOOK_WARM_START is set to 1.
/** This function is for initialization of registers critical to the startup,
* typically including power-on latch, memory map and basic system clock configuration.
* Only the stack pointer is setup at this point. Called from the bootcode. */
void RsHookWarmStart(void);
#else
  #define RsHookWarmStart !disabled
#endif

#if (RS_HOOK_CACHE_INIT == 1)
/// Cache initalization. This function is called when \ref RS_HOOK_CACHE_INIT is set to 1.
/** This function is for initialization of the systems cache unit. Called from the bootcode. */
void RsHookCacheInit(void);
#else
  #define RsHookCacheInit !disabled
#endif

#if (RS_HOOK_READY == 1)
/// Ready to run. This function is called when \ref RS_HOOK_READY is set to 1.
/** Called from main, when ROS and/or FOS are ready to run. */
void RsHookReady(void);
#else
  #define RsHookReady !disabled
#endif

#if (RS_HOOK_PRE_TASK == 1)
/// Pre-task initialization. This function is called when \ref RS_HOOK_PRE_TASK is set to 1.
/** Called from ROS before the first ROS task is initialized. */
void RsHookPreTask(void);
#else
  #define RsHookPreTask !disabled
#endif

#if (RS_HOOK_RUNNING == 1)
/// Running. This function is called when \ref RS_HOOK_RUNNING is set to 1.
/** Called from ROS when all tasks have been initialized. */
void RsHookRunning(void);
#else
  #define RsHookRunning !disabled
#endif

#if (RS_HOOK_EXIT == 1)
/// Exit from RsMain. This function is called when \ref RS_HOOK_EXIT is set to 1.
/** Called when RsMain is about to exit. */
void RsHookExit(void);
#else
  #define RsHookExit !disabled
#endif

#if (RS_HOOK_PRE_HWI == 1)
/// Interrupt entry. This function is called when \ref RS_HOOK_PRE_HWI is set to 1.
/** Called from FOS when an interrupt is about to be processed. */
void RsHookPreHwi(void);
#else
  #define RsHookPreHwi !disabled
#endif

#if (RS_HOOK_IDLE == 1)
/// System idle. This function is called when \ref RS_HOOK_IDLE is set to 1.
/** Called from FOS (with interrupts enabled) or ROS (with interrupts disabled) when the system is idle. */
void RsHookIdle(void);
#else
  #define RsHookIdle !disabled
#endif

#if (RS_HOOK_DEAD == 1)
/// Shutdown complete. This function is called when \ref RS_HOOK_DEAD is set to 1.
/** Called when shutdown is complete. The application can now execute \ref RsShutDownActionType. */
void RsHookDead(void);
#else
  #define RsHookDead !disabled
#endif

RS_END_EXTERN_C

#endif

// End of file.

