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
* Wrapper interface to the host systems poll() function.
* <br><br>
*/


#ifndef RS_POLL_H
#define RS_POLL_H

/****************************************************************************
*                               Include files
****************************************************************************/

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/** \name Maximum number of file descriptors for poll(). */
//@{
#ifndef RS_POLL_MAX
  #define RS_POLL_MAX 10 /*!< Maximum number of file descriptors for poll(). */
#endif
//@}

#ifdef _WIN32
typedef HANDLE RsPollHandleType; /*!< Poll handle. (Windows handle or nix file descriptor) */
#else
typedef int RsPollHandleType; /*!< Poll handle. (Windows handle or nix file descriptor) */
#endif

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/*!
  \brief Prototype for poll notification function.
  \details This is a user-provided function that is called when poll() triggers with the file descriptor.
  \param Handle Poll handle. (Windows handle or nix file descriptor).
  \param revents output event flags, a set of POLLxx flags.
  \param Context The Context parameter provided in RsPollAdd.
*/
typedef void RsPollNotifyType(RsPollHandleType Handle, short int revents, void* Context);

/** \cond internal */
typedef struct
{
  RsPollNotifyType* Notify;
  void* Context;
} RsPollEntryType;
/** \endcond */

/****************************************************************************
*                           Global variables/const
****************************************************************************/

RS_BEGIN_EXTERN_C

/** \cond internal */
extern rsuint16 RsPollCount;
extern RsPollEntryType RsPollEntries[RS_POLL_MAX];
/** \endcond */

/****************************************************************************
*                             Function prototypes
****************************************************************************/

/*!
  \brief Add a file descriptor for poll().
  \param Handle Poll handle. (Windows handle or nix file descriptor).
  \param events input event flags, a set of POLLxx flags.
  \param Notify User-provided function that is called when poll() triggers with the file descriptor.
  \param Context User-provided context (optional).
*/
void RsPollAdd(RsPollHandleType Handle, short int events, RsPollNotifyType* Notify, void* Context);

/*!
  \brief Modify poll() event flags.
  \param Handle Poll handle. (Windows handle or nix file descriptor).
  \param events input event flags, a set of POLLxx flags.
*/
void RsPollModify(RsPollHandleType Handle, short int events);

/*!
  \brief Remove a file descriptor for poll().
  \param Handle Poll handle. (Windows handle or nix file descriptor).
*/
void RsPollRemove(RsPollHandleType Handle);

/*!
  \brief Execute poll().
  \return Number of handles signalled.
*/
int RsPollWait(void);

/*!
  \brief Dispatch notifications for signalled handles.
  \param nset Number of handles signalled.
*/
void RsPollDispatch(int nset);

/*!
  \brief Find poll handle.
  \param Handle Handle to find.
  \return Index for handle or \ref RS_POLL_MAX.
*/
rsuint16 RsPollFind(RsPollHandleType Handle);

/** \cond internal */
// Deprecated.
#define RsPollMax !deprecated
/** \endcond */

RS_END_EXTERN_C

#endif

// End of file.

