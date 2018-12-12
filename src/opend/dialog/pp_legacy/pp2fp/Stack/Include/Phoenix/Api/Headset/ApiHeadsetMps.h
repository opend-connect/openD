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
#ifndef APIHEADSETMPS_H
#define APIHEADSETMPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/Headset/ApiHeadset.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
* FUNCTION:      SendApiHeadsetDetectHeadsetInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_HEADSET_DETECT_HEADSET_IND = 0x5D00
****************************************************************************/
void SendApiHeadsetDetectHeadsetInd ( RosTaskIdType Dst,
                                      ApiHeadsetDetectHeadsetStateType HeadsetState);
                                                             /*!< Indicates the state of
                                                                the headset - if it is
                                                                plugged or unplugged. */

/****************************************************************************
* FUNCTION:      SendApiHeadsetHookInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_HEADSET_HOOK_IND = 0x5D01
****************************************************************************/
void SendApiHeadsetHookInd ( RosTaskIdType Dst,
                             ApiHeadsetHookStateType HookState);
                                                             /*!< Indicates the state of
                                                                the hook button - if it is
                                                                pressed or released. */

#ifdef __cplusplus
}
#endif
#endif /*APIHEADSETMPS_H */


