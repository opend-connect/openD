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
* Error handling.
*/


#ifndef RS_ERROR_H
#define RS_ERROR_H

/****************************************************************************
*                               Include files
****************************************************************************/

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/** \name Assertion macros.
* \anchor assert_macros
* These macros are used in the source code to assert that a critical condition is correct.
* If the assertion fails, an \ref RsError "error" is issued.
*/
//@{
#ifndef RS_OVERRIDE_ASSERT
  #define RSASSERT(p) ((p) ? (void)0 : RsAssert()) /*!< Asserts \a p. */
#endif
#ifdef DEBUG
  #define RSASSERTDEBUG(p) RSASSERT(p)
#else
  #define RSASSERTDEBUG(p) /*!< Only asserts \a p in debug builds. */
#endif
#if (RS_TARGET_FAMILY == RSTF_WINDOWS)
  #define RSASSERTPC(p) RSASSERT(p) /*!< Only asserts \a p in PcSim builds. */
#else
  #define RSASSERTPC(p)
#endif
//@}

#ifndef RSASSERTSTATIC
/** \name Static asserts.
 *        Static asserts are used are used like standard asserts
 *        with one difference: they fire at compile time rather
 *        than at run time, and does consequently not use any
 *        resources at run time at all.
 *
 *        Static asserts are entering the upcoming C++ standard,
 *        and will likely show up in the next C standard too.
 *
 *        Using the RSASSERTSTATIC is very similar to the normal
 *        RSASSERT macro, with two exceptions:
 *
 *        1) it may be used anywhere at file scope, and at
 *        function scope or block scope provided it occurs
 *        before any automatic variables are defined. Placing
 *        it after these will cause a compiler error.
 *
 *        2) as static asserts are not yet supported by
 *        compilers it must be constructed from existing parts
 *        of the language. This means that the compiler will not
 *        emit a message saying "static assertion fail" but
 *        rather something not related to static asserts at all.
 *        The file and line info will still point to the assert
 *        though.
*/
//@{
#define RSASSERTSTATIC(e) typedef char RS_PADy(assertion_failed_at_line_, __LINE__) [(e) ? 1 : -1]   /*!< Static/compile time assert. */
//@}
#endif

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/// Error identification values.
typedef enum RSENUMTAG(RsErrorIdType)
{
  RSE_NONE              = 0x0000, /*!< No error. */
  RSE_BAD_TARGET_FAMILY = 0x0001, /*!< RS_TARGET_FAMILY mismatch. */
  RSE_BAD_TOOL_ID       = 0x0002, /*!< RS_TOOL_ID mismatch. */
  RSE_BAD_RTOS_ID       = 0x0003, /*!< RS_RTOS_ID mismatch. */
  RSE_BAD_ALIGN_SIZE    = 0x0004, /*!< RS_ALIGN_SIZE mismatch. */
  RSE_ASSERT            = 0x0005, /*!< Assertion failed. */
  RSE_UNALIGNED_ADDRESS = 0x0006, /*!< Pointer/address alignment check failed. */
  RSE_DUMMY_ISR         = 0x0007, /*!< An interrupt was directed to a dummy interrupt service routine. */
  RSE_INTERRUPTS_KILLED = 0x0008, /*!< Someone called \ref RsDisableInterrupts, but forgot to call \ref RsEnableInterrupts. */
  RSE_INTERRUPTS_HANG   = 0x0009, /*!< \ref RsInterruptsPending always returns true. */
  RSE_CALL_FROM_ISR     = 0x000A, /*!< A core function was called from an interrupt service routine. */
  RSE_BAD_CONFIG        = 0x000B, /*!< Core configuration mismatch. */
  RSE_LICENSE_VIOLATION = 0x000C, /*!< License violation e.g. attempt to run on wrong hardware. */
  RSE_TIMEOUT           = 0x000D, /*!< Timeout. */

  RSE_EXCEPTION_RES_00  = 0x0010, /*!< Exception: Reserved 00. */
  RSE_EXCEPTION_NMI_01  = 0x0011, /*!< Exception: Non-maskable (watchdog). */
  RSE_EXCEPTION_RES_02  = 0x0012, /*!< Exception: Reserved 02. */
  RSE_EXCEPTION_RES_03  = 0x0013, /*!< Exception: Reserved 03. */
  RSE_EXCEPTION_RES_04  = 0x0014, /*!< Exception: Reserved 04. */
  RSE_EXCEPTION_SVC_05  = 0x0015, /*!< Exception: Supervisor call. */
  RSE_EXCEPTION_DVZ_06  = 0x0016, /*!< Exception: Divide by zero. */
  RSE_EXCEPTION_FLG_07  = 0x0017, /*!< Exception: Flag. */
  RSE_EXCEPTION_BPT_08  = 0x0018, /*!< Exception: Breakpoint. */
  RSE_EXCEPTION_TRC_09  = 0x0019, /*!< Exception: Trace. */
  RSE_EXCEPTION_UND_10  = 0x001A, /*!< Exception: Undefined instruction. */
  RSE_EXCEPTION_RES_11  = 0x001B, /*!< Exception: Reserved 11. */
  RSE_EXCEPTION_IAD_12  = 0x001C, /*!< Exception: Illegal address. */
  RSE_EXCEPTION_RES_13  = 0x001D, /*!< Exception: Reserved 13. */
  RSE_EXCEPTION_DBG_14  = 0x001E, /*!< Exception: Debug. */
  RSE_EXCEPTION_ISE_15  = 0x001F, /*!< Exception: In-System emulator. */

  RSE_CM_STACK_00       = 0x0020, /*!< Stack frame start address. */
  RSE_CM_RESET_01       = 0x0021, /*!< Exception: Reset. */
  RSE_CM_NMI_02         = 0x0022, /*!< Exception: NMI. */
  RSE_CM_HARDFAULT_03   = 0x0023, /*!< Exception: Hard fault. */
  RSE_CM_MMU_04         = 0x0024, /*!< Exception: Memory management fault. */
  RSE_CM_BUSFAULT_05    = 0x0025, /*!< Exception: Bus fault. */
  RSE_CM_USAGEFAULT_06  = 0x0026, /*!< Exception: Usage fault. */
  RSE_CM_RES_07         = 0x0027, /*!< Exception: Reserved 07. */
  RSE_CM_RES_08         = 0x0028, /*!< Exception: Reserved 08. */
  RSE_CM_RES_09         = 0x0029, /*!< Exception: Reserved 09. */
  RSE_CM_RES_10         = 0x002A, /*!< Exception: Reserved 10. */
  RSE_CM_SVC_11         = 0x002B, /*!< Exception: Supervisor call. */
  RSE_CM_DEBUGMON_12    = 0x002C, /*!< Exception: Debug monitor. */
  RSE_CM_RES_13         = 0x002D, /*!< Exception: Reserved 13. */
  RSE_CM_PENDSV_14      = 0x002E, /*!< Exception: PendSV. */

  RSE_ROS_BAD_MAILQUEUE             = 0x0040, /*!< Invalid address or size for a mailqueue. */
  RSE_ROS_MAIL_QUEUE_FULL           = 0x0041, /*!< Mail queue full. */
  RSE_ROS_MAIL_TOO_SMALL            = 0x0042, /*!< Task attempted to allocate a too small mail. */
  RSE_ROS_MAIL_TOO_LARGE            = 0x0043, /*!< Task attempted to allocate a too large mail. */
  RSE_ROS_TAIL_OVERWRITE            = 0x0044, /*!< Data written beyond the end of a mail. */
  RSE_ROS_MAIL_DELIVER_MISMATCH     = 0x0045, /*!< RosMailDeliver called too few or too many times. */
  RSE_ROS_MAIL_COUNT_MISMATCH       = 0x0046, /*!< Mail queue integrity check failed. */
  RSE_ROS_QUEUE_SIZE_MISMATCH       = 0x0047, /*!< Mail queue integrity check failed. */
  RSE_ROS_QUEUE_STALL_TIMEOUT       = 0x0048, /*!< Mail queue stalled for too long. */
  RSE_ROS_TASK_MAP_NEEDED           = 0x0049, /*!< Non-consecutive TaskId found in \ref RosTaskConfig. */
  RSE_ROS_MAIL_WAS_MODIFIED         = 0x004A, /*!< Task mail handler modified a received mail. */
  RSE_ROS_TOO_MANY_GROUPS           = 0x004B, /*!< Application defined too many ROS groups in \ref RosGroupConfig. */

  RSE_HEAP_BAD_ADDRESS              = 0x0050, /*!< Pointer/address does not refer a heap block. Can be issued from almost all heap functions. */
  RSE_HEAP_BAD_SIZE                 = 0x0051, /*!< Invalid heap block size given in RcHeapAllocEx or RcHeapReallocEx, or found by RcHeapCheck. */
  RSE_HEAP_BAD_HEADER               = 0x0052, /*!< Invalid heap block header found by RcHeapCheck. */
  RSE_HEAP_FREE_NULL                = 0x0053, /*!< Attempt to free a NULL-pointer (only when option RHF_ERROR_ON_NULL_PTR enabled). */
  RSE_HEAP_NOT_ALLOCATED            = 0x0054, /*!< Attempt to use/free a block that is not marked allocated. Typically because RcHeapFree called twice on the same block. */
  RSE_HEAP_TAIL_OVERWRITE           = 0x0055, /*!< Data written beyond the end of a heap block. */
  RSE_HEAP_EMPTY_OVERWRITE          = 0x0056, /*!< Header and/or data in empty heap block overwritten. */
  RSE_HEAP_BLOCK_COUNT_MISMATCH     = 0x0057, /*!< Heap integrity check failed. */
  RSE_HEAP_SIZE_MISMATCH            = 0x0058, /*!< Heap integrity check failed. */
  RSE_HEAP_FULL                     = 0x0059, /*!< Allocation request cannot be satisfied. */

  RSE_FOS_TOO_SMALL_STACK           = 0x0070, /*!< Task stack size too small during fosTaskCreate. */
  RSE_FOS_STACK_ERROR               = 0x0071, /*!< Task stack check failed (stack has overflowed or been overwritten). */
  RSE_FOS_STACK_OVERFLOW            = 0x0072, /*!< Task stack check failed (stack has overflowed or been overwritten). */

  RSE_PROJECT_0                     = 0x0080, /*!< Project specific errorcode. */
  RSE_PROJECT_1                     = 0x0081, /*!< Project specific errorcode. */
  RSE_PROJECT_2                     = 0x0082, /*!< Project specific errorcode. */
  RSE_PROJECT_3                     = 0x0083, /*!< Project specific errorcode. */
  RSE_PROJECT_4                     = 0x0084, /*!< Project specific errorcode. */
  RSE_PROJECT_5                     = 0x0085, /*!< Project specific errorcode. */
  RSE_PROJECT_6                     = 0x0086, /*!< Project specific errorcode. */
  RSE_PROJECT_7                     = 0x0087, /*!< Project specific errorcode. */
  RSE_PROJECT_8                     = 0x0088, /*!< Project specific errorcode. */
  RSE_PROJECT_9                     = 0x0089, /*!< Project specific errorcode. */

  RSE_MAX = 0xFFFF
} RSENUM16(RsErrorIdType);

/// For saving additional information about an error.
typedef rsuint32 RsErrorInfoType;

/****************************************************************************
*                           Global variables/const
****************************************************************************/

RS_BEGIN_EXTERN_C

/// Error ID.
extern RS_DATA_ADR RsErrorIdType RsErrorId;

/****************************************************************************
*                             Function prototypes
****************************************************************************/

/** \name Check for debugger.
*/
//@{
#if (RS_IS_DEBUGGER_CONNECTED == 1)
/// Check if a debugger is connected. This function is called when \ref RS_IS_DEBUGGER_CONNECTED is set to 1.
/** \return TRUE if a debugger is connected. */
rsbool RsIsDebuggerConnected(void);
#else
  #define RsIsDebuggerConnected !disabled
#endif
//@}

/** \name Issue Error.
*/
//@{
/// Issue an error.
/** \param Error identifies the type of error that was detected.
* \param Info is a user-provided value with additional information about the error. */
void RsError(RsErrorIdType Error, RsErrorInfoType Info);
//@}

/** \name Save error information.
*/
//@{
#if (RS_DUMP_ERROR == 1)
/// Called from Core to save error information (to NVS). This function is called when \ref RS_DUMP_ERROR is set to 1. The system will be reset or powered off following this call. The NVS driver may wait (spin) until the storage device has finished any pending writes.
/** \param Error identifies the type of error that occured.
* \param Info is a user-provided value with additional information about the error.
* \param Address The code address when the error occured. */
void RsDumpError(RsErrorIdType Error, RsErrorInfoType Info, rsuint32 Address);
#else
  #define RsDumpError !disabled
#endif
//@}

/** \name Save assertion information.
*/
//@{
#if (RS_DUMP_ASSERT == 1)
/// Called from Core to save RSASSERT information (to NVS). This function is called when \ref RS_DUMP_ASSERT is set to 1. The system will continue following this call.
/** \param Address The code address when the error occured. */
void RsDumpAssert(rsuint32 Address);
#else
  #define RsDumpAssert !disabled
#endif
//@}


/** \cond internal */
void RsAssert(void);
/** \endcond */

RS_END_EXTERN_C

#endif

// End of file.

