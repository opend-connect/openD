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
 *//****************************************************************************
*                               Notes
****************************************************************************/
/****************************************************************************
*                               Include files
****************************************************************************/

#include <Core/RtxCore.h>
#include <Ros/RosCfg.h>
#include <Cola/Cola.h>
#include <Phoenix/Api/Api.h>
#include "system.h"
#include "CfState.h"
#include "keyMessage.h"
#ifdef PCCOMPILE
 #include "HostUtil.h"
#endif //PCCOMPILE

/****************************************************************************
*                            Global variables/const
****************************************************************************/
const RosTimerConfigType ColaTimerCfgTable[NO_OF_COLA_TIMER]=
{
    { COLA_TASK, { TIMEOUT, KEY_SCAN_TIMER            } },
    { COLA_TASK, { TIMEOUT, LED1_FLASH_TIMER          } },
    { COLA_TASK, { TIMEOUT, LED2_FLASH_TIMER          } },
    { COLA_TASK, { TIMEOUT, LED3_FLASH_TIMER          } },
    { COLA_TASK, { TIMEOUT, LED4_FLASH_TIMER          } },
    { COLA_TASK, { TIMEOUT, LED5_FLASH_TIMER          } },
    { COLA_TASK, { TIMEOUT, LED6_FLASH_TIMER          } },
    { COLA_TASK, { TIMEOUT, LED7_FLASH_TIMER          } },
    { COLA_TASK, { TIMEOUT, REGISTRATION_TIMER        } },
    { COLA_TASK, { TIMEOUT, CONNECTION_TIMER          } },
    { COLA_TASK, { TIMEOUT, MELODY_RELOAD_TIMER       } },
    { COLA_TASK, { TIMEOUT, UNMUTE_AUDIO_TIMER        } },
    { COLA_TASK, { TIMEOUT, CF_STATE_TIMER            } },
};

/****************************************************************************
*                            Local variables/const
****************************************************************************/

/****************************************************************************
*                          Local Function prototypes
****************************************************************************/

/****************************************************************************
*                                Implementation
***************************************************************************/
void ColaTask(const RosMailType* Mail)
{

  if(INITTASK == Mail->Primitive) {
    /* INITTASK */
    RosTimerStart(KEY_SCAN_TIMER, KEY_SCAN_TIME, &ColaTimerCfgTable[ColaTimerCfgTableIdx(KEY_SCAN_TIMER)]);
    // LedCtrlInit();
    CfTaskInit();

  } else {
    CfTaskHandler(Mail);
  }


}

// End of file.

