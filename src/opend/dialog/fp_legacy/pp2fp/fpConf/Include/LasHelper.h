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
#ifndef LAS_HELPER_H
#define LAS_HELPER_H

/****************************************************************************
*                               Include files
****************************************************************************/

#include <Core/RtxCore.h>
#include <Ros/RosCfg.h>
#include <Cola/Cola.h>
#include <Phoenix/Api/Api.h>
#include <Phoenix/Api/Las/ApiLas.h>

/****************************************************************************
*                              Macro definitions
****************************************************************************/
#define LAS_STATE_NO_ACTIVE 0xFF

#define NUMBER_OF_LISTS_IN_LAS API_LAS_LINE_SETTINGS+1 
/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/
typedef enum
{
  LINE_STATE_INIT_SYSTEM,
  LINE_STATE_OPEN_SESSION, 
  LINE_STATE_DELETE_ALL_LINES,  
  LINE_STATE_CREATE_ALL_LINES,   
  LINE_STATE_CREATE_LINE1,
  LINE_STATE_CREATE_LINE2,
  LINE_STATE_CREATE_LINE3,
  LINE_STATE_INIT_ALL_LINES,
  LINE_STATE_GET_LINE_ALL_SETTINGS,
  LINE_STATE_ATTACH_NEW_HS_READ,
  LINE_STATE_ATTACH_NEW_HS_EDIT,
  LINE_STATE_ATTACH_NEW_HS_SAVE
} LasLineSettingsStateType;


/****************************************************************************
*                            Global variables/const
****************************************************************************/

/****************************************************************************
*                            Local variables/const
****************************************************************************/

/****************************************************************************
*                          Local Function prototypes
****************************************************************************/

/****************************************************************************
*                                Implementation
***************************************************************************/                   
/***************************************************************************
*  FUNCTION: HostLasTask
*  INPUTS  : 
*  OUTPUTS : 
*  ------------------------------------------------------------------------- 
*  DESCRIPTION: 
*****************************************************************************/
extern void HostLasTask(RosMailType *MailPtr);

/***************************************************************************
*  FUNCTION: HostLasAttachHsToAllLines
*  INPUTS  : HandsetId, detach or attach handset from Line
*  OUTPUTS : 
*  ------------------------------------------------------------------------- 
*  DESCRIPTION:
*   Attach or detach a specific handset to all the lines
*****************************************************************************/
extern void HostLasAttachHsToAllLines(rsuint8 Hs, rsbool ClearHs);     

/***************************************************************************
*  FUNCTION: ClearLasSessionData
*  INPUTS  : 
*  OUTPUTS : 
*  ------------------------------------------------------------------------- 
*  DESCRIPTION: reads the attached handsets of a specific line
*****************************************************************************/
extern void ClearLasSessionData(ApiLasListIdType Index);     

/***************************************************************************
*  FUNCTION: HostLasInitialzeLineSettings
*  INPUTS  : 
*  OUTPUTS : 
*  ------------------------------------------------------------------------- 
*  DESCRIPTION: 
*****************************************************************************/
extern void HostLasInitialzeLineSettings(void);
#endif //API_HELPER_H

