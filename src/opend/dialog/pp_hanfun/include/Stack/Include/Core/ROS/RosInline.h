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
* Inlines some ROS functions in order to save code space.
*/

/** \cond internal */


#ifndef ROS_INLINE_H
#define ROS_INLINE_H

/****************************************************************************
*                               Include files
****************************************************************************/

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

typedef struct
{
  RosPrimitiveType Primitive;
  RosTimerParameterType Parameter;
  RosTimerIdType TimerId;
  RS_PADDING(2)
  RsTimerTickType Value;
} RosMailIntTimeoutType;

#ifdef ROS_DFC_H
typedef struct
{
  RosPrimitiveType Primitive;
  RS_PADDING(RS_POINTER_SIZE-2)
  RosDfcType* Function;
  RosDfcParameterType Parameter;
  RS_PADDING64(4)
} RosMailDfcType;
#endif

typedef struct
{
  #if (RS_QUEUES == RSQT_HEAP)
  RsListEntryType Link;
  RS_PADDING64(4)
  #endif
  RosMailSizeType Size;
  RS_PADDING(2)
  rsuint8 Extra;
  rsuint8 Flags;
  RosTaskIdType Src;
  RosTaskIdType Dst;
  union
  {
    RosMailType Mail;
    RosMailIntTimeoutType Timeout;
    #ifdef ROS_DFC_H
    RosMailDfcType Dfc;
    #endif
  };
} RosMailEntryType;

/****************************************************************************
*                           Global variables/const
****************************************************************************/

/****************************************************************************
*                             Function prototypes
****************************************************************************/

#if (RS_ROS_INLINE == 1)
#if (RS_QUEUES == RSQT_STATIC)
RS_C_INLINE RosMailSizeType RosMailGetSize(const RosMailType* Mail)
{
  RosMailEntryType* pe = RSCONTAININGOFFSET(Mail, RosMailEntryType, Mail);
  return pe->Size - RSOFFSETOF(RosMailEntryType,Mail) - pe->Extra;
}
#endif

RS_C_INLINE RosTaskIdType RosMailGetSrc(const RosMailType* Mail)
{
  RosMailEntryType* pe = RSCONTAININGOFFSET(Mail, RosMailEntryType, Mail);
  return pe->Src;
}

RS_C_INLINE RosTaskIdType RosMailGetDst(const RosMailType* Mail)
{
  RosMailEntryType* pe = RSCONTAININGOFFSET(Mail, RosMailEntryType, Mail);
  return pe->Dst;
}

RS_C_INLINE void RosMailSetSrc(RosMailType* Mail, RosTaskIdType Src)
{
  RosMailEntryType* pe = RSCONTAININGOFFSET(Mail, RosMailEntryType, Mail);
  pe->Src = Src;
}

RS_C_INLINE void RosMailSetDst(RosMailType* Mail, RosTaskIdType Dst)
{
  RosMailEntryType* pe = RSCONTAININGOFFSET(Mail, RosMailEntryType, Mail);
  pe->Dst = Dst;
}
#endif

#endif

/** \endcond */

// End of file.

