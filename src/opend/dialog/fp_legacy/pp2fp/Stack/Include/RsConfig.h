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

#ifndef RS_CONFIG_H
#define RS_CONFIG_H

/****************************************************************************
*                               Include files
****************************************************************************/

// None allowed.

/****************************************************************************
*                              Macro definitions
****************************************************************************/

#if (PX_PCOUNT_SOURCE == 3 || PX_PCOUNT_SOURCE == 4)
  #define RS_PERFORMANCE_TICKS_PER_SECOND 10368000
  #if (PX_PCOUNT_SOURCE == 4)
  #ifdef __IAR_SYSTEMS_ICC__
  _Pragma("inline=forced")
  #endif
  #ifdef __GNUC__
  __inline__ __attribute__((always_inline)) static
  #endif
  unsigned long RsReadPerformanceCounter(void)
  {
    return *((volatile unsigned long*)0x1027FF8);
  }
  #endif
#else
  #define RS_PERFORMANCE_TICKS_PER_SECOND 1115200
#endif
#ifndef PCCOMPILE
  #define RC_HEAP_ENABLE_NEWDEL
#endif
#ifdef RS_OVERRIDE_ASSERT
  #define RSASSERT(p)
#endif

#define ROS_INIT_MAIL_PRIMITIVE 0x0007 // INITTASK
#define ROS_SHUTDOWN_MAIL_PRIMITIVE 0x0008 // TERMINATETASK

#define ROS_MAX_CHECK_INTERVAL 432UL

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

