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
* ROS mail types, macros and functions. Also see \ref ros_manual.
*/


#ifndef ROS_MAILS_H
#define ROS_MAILS_H

/****************************************************************************
*                               Include files
****************************************************************************/

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/** \name Inlining of ROS functions.
* Controls inlining of \ref RosMailGetSize, \ref RosMailGetSrc, \ref RosMailGetDst, \ref RosMailSetSrc and \ref RosMailSetDst. */
//@{
#ifndef RS_ROS_INLINE
  #ifdef RS_C_INLINE
    #define RS_ROS_INLINE 1 /*!< Set to 1 to enable inlining of ROS functions (default), set to 0 to disable inlining of ROS functions. */
  #else
    #define RS_ROS_INLINE 0 /*!< Set to 1 to enable inlining of ROS functions (default), set to 0 to disable inlining of ROS functions. */
  #endif
#endif
//@}

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/****************************************************************************
*                           Global variables/const
****************************************************************************/

RS_BEGIN_EXTERN_C

/****************************************************************************
*                             Function prototypes
****************************************************************************/

/** \name Mail allocation functions.
*/
//@{

/// Allocate a mail.
/** \param Src Source (sender) task ID.
* \param Dst Destination (receiver) task ID.
* \param Size Mail size needed, including primitive.
* \return Mail packet. */
RosMailType* RosMailAllocate(RosTaskIdType Src, RosTaskIdType Dst, RosMailSizeType Size);

/// Deliver (queue) a mail.
/** \param Mail The mail packet, from \ref RosMailAllocate. */
void RosMailDeliver(RosMailType* Mail);
//@}

/** \cond internal */

#if (RS_QUEUES == RSQT_HEAP)
void RosMailFree(RosMailType* Mail);
RosMailSizeType RosMailGetSize(const RosMailType* Mail);
#endif

/** \endcond */

#if (RS_ROS_INLINE == 0)
/** \name Get mail information.
*/
//@{

/// Get size of a mail.
/** \param Mail The mail packet.
* \return Mail size, including primitive. */
RosMailSizeType RosMailGetSize(const RosMailType* Mail);

/// Get source of a mail.
/** \param Mail The mail packet.
* \return Source (sender) task ID. */
RosTaskIdType RosMailGetSrc(const RosMailType* Mail);

/// Get destination for a mail.
/** \param Mail The mail packet.
* \return Destination (receiver) task ID. */
RosTaskIdType RosMailGetDst(const RosMailType* Mail);
//@}

/** \name Set mail information.
*/
//@{

/// Set source of a mail.
/** \param Mail The mail packet.
* \param Src Source (sender) task ID. */
void RosMailSetSrc(RosMailType* Mail, RosTaskIdType Src);

/// Set destination for a mail.
/** \param Mail The mail packet.
* \param Dst Destination (receiver) task ID. */
void RosMailSetDst(RosMailType* Mail, RosTaskIdType Dst);
//@}
#endif

/** \name Mail utilities.
*/
//@{

/// Send a mail without parameters.
/** \param Src Source (sender) task ID.
* \param Dst Destination (receiver) task ID.
* \param Primitive Mail primtive. */
void RosMailSendP0(RosTaskIdType Src, RosTaskIdType Dst, RosPrimitiveType Primitive);

/// Send a mail with 1 byte parameter.
/** \param Src Source (sender) task ID.
* \param Dst Destination (receiver) task ID.
* \param Primitive Mail primtive.
* \param P1 First parameter. */
void RosMailSendP1(RosTaskIdType Src, RosTaskIdType Dst, RosPrimitiveType Primitive, rsuint8 P1);

/// Send a mail with 2 byte parameters.
/** \param Src Source (sender) task ID.
* \param Dst Destination (receiver) task ID.
* \param Primitive Mail primtive.
* \param P1 First parameter.
* \param P2 Second parameter. */
void RosMailSendP2(RosTaskIdType Src, RosTaskIdType Dst, RosPrimitiveType Primitive, rsuint8 P1, rsuint8 P2);

/// Send a mail with 3 byte parameters.
/** \param Src Source (sender) task ID.
* \param Dst Destination (receiver) task ID.
* \param Primitive Mail primtive.
* \param P1 First parameter.
* \param P2 Second parameter.
* \param P3 Third parameter. */
void RosMailSendP3(RosTaskIdType Src, RosTaskIdType Dst, RosPrimitiveType Primitive, rsuint8 P1, rsuint8 P2, rsuint8 P3);

/// Send a mail with 4 byte parameters.
/** \param Src Source (sender) task ID.
* \param Dst Destination (receiver) task ID.
* \param Primitive Mail primtive.
* \param P1 First parameter.
* \param P2 Second parameter.
* \param P3 Third parameter.
* \param P4 Fourth parameter. */
void RosMailSendP4(RosTaskIdType Src, RosTaskIdType Dst, RosPrimitiveType Primitive, rsuint8 P1, rsuint8 P2, rsuint8 P3, rsuint8 P4);

/// Send a copy of a mail.
/** \param Src Source (sender) task ID.
* \param Dst Destination (receiver) task ID.
* \param Mail The original mail.
* \param Size Original mail size. */
void RosMailSendCopy(RosTaskIdType Src, RosTaskIdType Dst, const RosMailType* Mail, RosMailSizeType Size);
//@}

RS_END_EXTERN_C

#endif

// End of file.

