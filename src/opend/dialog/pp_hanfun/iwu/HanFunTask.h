/*
 * Copyright (C) 2018 by Dialog Semiconductor. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of Dialog Semiconductor nor the names of its Affiliates
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

#ifndef HANFUNTASK_H
#define HANFUNTASK_H

// =========================================================================
// Defines
// =========================================================================

//#define ENABLE_RSX_TRACE   1
#define RSX_TRACE_FULL     1

// === Transmission Status ===
#define TX_PASS   0
#define TX_FAIL   1

// === NVS Offsets ===
#define TXPASS_MSB   0
#define TXPASS_LSB   1
#define TXFAIL_MSB   2
#define TXFAIL_LSB   3
#define TIMERVALUE   4
#define FPCNT        5
#define LNGSLPCNT    6
#define HF_OFFSET    7

// === HAN-FUN Devices ===

#ifdef HF_SIMPLE_SWITCH
#define HF_SENSOR
#endif
#ifdef HF_SIMPLE_REED
#define HF_SENSOR
#endif

#ifdef HF_SIMPLE_LIGHT
#define HF_ACTUATOR
#endif

#ifdef HF_AC_OUTLET
#define HF_ACTUATOR
#endif

#if (defined(HF_SENSOR) && defined(HF_ACTUATOR))
#pragma GCC error "The device MUST be a sensor or an Actuator."
#endif

// =========================================================================
// API
// =========================================================================

#ifdef __cplusplus
extern "C" {
#endif

#include "mmi_def.h"

// =========================================================================
// Type Definitions
// =========================================================================
typedef struct ApiPpUleHanfunCmdType
{
  RosPrimitiveType Primitive;
  rsuint8 dummy;
  rsuint8 cmd;
  rsuint32 Ptr;
} ApiPpUleHanfunCmdType;

// =========================================================================
// Helper Functions
// =========================================================================

// =========================================================================
// HAN-FUN Task.
// =========================================================================

//void HanfunTask(const RosMailType* p_mail);


void hanfun_data_save();
void ColaMail_SetupAgain();



#ifdef __cplusplus
}
#endif

#endif /* HANFUNTASK_H */
