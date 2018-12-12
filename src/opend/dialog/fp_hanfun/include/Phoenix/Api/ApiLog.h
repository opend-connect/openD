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

#ifndef APILOG_H
#define APILOG_H

/****************************************************************************
*                               Include files
****************************************************************************/

/****************************************************************************
*                              Macro definitions
****************************************************************************/

// HTML RBG color values. Google "html color names".
#define APILOG_AQUA     0x00FFFFUL
#define APILOG_BLACK    0x000000UL
#define APILOG_BLUE     0x0000FFUL
#define APILOG_FUCHSIA  0xFF00FFUL
#define APILOG_GRAY     0x808080UL
#define APILOG_GREEN    0x008000UL // CC.
#define APILOG_LIME     0x00FF00UL
#define APILOG_MAROON   0x800000UL
#define APILOG_NAVY     0x000080UL
#define APILOG_OLIVE    0x808000UL // MM, Audio.
#define APILOG_PURPLE   0x800080UL // LAS.
#define APILOG_RED      0xFF0000UL // Errors.
#define APILOG_SILVER   0xC0C0C0UL
#define APILOG_TEAL     0x008080UL
#define APILOG_WHITE    0xFFFFFFUL
#define APILOG_YELLOW   0xFFFF00UL

#ifndef APILOG_COLORS
  #define APILOG_COLORS 0 // Disabled.
#endif

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/****************************************************************************
*                           Global variables/const
****************************************************************************/

/****************************************************************************
*                             Function prototypes
****************************************************************************/

void ApiLog(rsuint32 iSendingTaskId,
            rsuint32 iRecievingTaskId,
            rsuint32 iMailLength,
            rsuint8 *MailPtr,
            char *szText,
            rsuint32 *iColor);

#endif

