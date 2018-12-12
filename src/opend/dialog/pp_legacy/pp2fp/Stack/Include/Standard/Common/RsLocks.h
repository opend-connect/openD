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
* Functions for locking access to variables.
* The \a interrupt functions are for protecting variables shared with interrupt routines.<br>
* Typical usage:
*
* \code
* void f(void)
* {
*   RsIntStatusType saved;
*   saved = RsDisableInterrupts();
*   // Read/modify shared variables here.
*   RsEnableInterrupts(saved);
* }
* \endcode
* <br>
*/


#ifndef RS_LOCKS_H
#define RS_LOCKS_H

/****************************************************************************
*                               Include files
****************************************************************************/

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/** \cond internal */
#if (RS_UNICOI == 0)
  #define FOSMUTEXDECLARE(name)
  #define FOSMUTEXCREATE(p1,p2)
  #define FOSMUTEXOBTAIN(p1,p2,p3)
  #define FOSMUTEXRELEASE(p1)
  #define FOSMUTEXDELETE(p1,p2)
#endif
/** \endcond */

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/****************************************************************************
*                           Global variables/const
****************************************************************************/

RS_BEGIN_EXTERN_C

/** \cond internal */
extern RS_FASTDATA_ADR volatile rsuint8 RsHwiCount;
/** \endcond */

/****************************************************************************
*                             Function prototypes
****************************************************************************/

#ifndef RS_OVERRIDE_INTERRUPTS
/** \name Interrupt functions.
*/
//@{
/// Disable interrupts.
/** \return The previous interrupt state (enabled or disabled). Must be saved in a stack variable. */
RsIntStatusType RsDisableInterrupts(void);

/// Enable interrupts.
/** \param Saved is the previous interrupt state, returned from RsDisableInterrupts. */
void RsEnableInterrupts(RsIntStatusType Saved);

/// Check if interrupts are enabled.
/** \return TRUE if interrupts are enabled, FALSE otherwise. */
rsbool RsInterruptsEnabled(void);
//@}

/** \cond internal */

/** \name Interrupt nesting (manual/direct control).
*/
//@{
/// Disable interrupt nesting (manual/direct control).
void RsDisableNesting(void);

/// Enable interrupt nesting (manual/direct control).
void RsEnableNesting(void);
//@}

/** \name Interrupt functions (manual/direct control).
*/
//@{
/// Disable interrupts (manual/direct control).
void RsDisableIntsForced(void);

/// Enable interrupts (manual/direct control).
void RsEnableIntsForced(void);
//@}

/** \endcond */

#endif

/// Check if interrupts are pending.
/** Called from the Core to check if one or more interrupts are pending.
* \return TRUE if one or more interrupts pending, FALSE otherwise. */
rsbool RsInterruptsPending(void);

/// Check if an interrupt handler is active.
/** \return TRUE if one or more interrupt handlers are active, FALSE otherwise. */
#ifndef RS_C_INLINE
rsbool RsInterruptActive(void);
#endif

/** \cond internal */
#ifdef RS_C_INLINE
RS_C_INLINE rsbool RsInterruptActive(void)
{
  return RsHwiCount;
}
#endif
/** \endcond */

RS_END_EXTERN_C

#endif

// End of file.

