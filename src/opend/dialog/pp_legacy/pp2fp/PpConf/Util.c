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
/****************************************************************************
*                               Include files
****************************************************************************/

#include <Core/RtxCore.h>
#include <Ros/RosCfg.h>
#include "Util.h"

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

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
/****************************************************************************
* Name   : util_memset
* Input  :
* Return :
*---------------------------------------------------------------------------
* Usage  : Set a block of memory to a certain value
****************************************************************************/
void *util_memset(void *dst, rsuint8 c, rsuint8 n)
{
    if (n) {
        char *d = dst;

        do {
            *d++ = c;
        } while (--n);
    }
    return dst;
}

/****************************************************************************
* Name   : util_memcpy
* Input  :
* Return :
*---------------------------------------------------------------------------
* Usage  : copy a block of memory to a another place
****************************************************************************/
void *util_memcpy(void *dst, const void *src, rsuint8 len)
{
  rsuint8 i;
  char *d = dst;
  const char *s = src;
  
  for (i=0; i<len; i++) 
  {
    *(d+i)= *(s+i);
  }
  return dst;
}

/****************************************************************************
* Name   : util_convert2hex
* Input  :
* Return :
*---------------------------------------------------------------------------
* Usage  : copy a block of memory to a another place
****************************************************************************/
rsuint8 util_convert2hex(void *dst, const void *src, rsuint8 len)
{
  rsuint8 i,j,val;
  char *d = dst;
  const char *s = src;
  
  j=0;
  for (i=0; i<len; i++) 
  {
    val = *(s+i);
    *(d+j++)=(val/16>9)?(val/16-10+'A'):(val/16+'0');
    *(d+j++)=(val%16>9)?(val%16-10+'A'):(val%16+'0');;
  }
  return j;
}

/****************************************************************************
* Name   : util_memcmp
* Input  :
* Return :
*---------------------------------------------------------------------------
* Usage  : compare 2 blocks of memories, return 0 if they are the same
****************************************************************************/
rsuint8 util_memcmp(const void *Ptr1, const void *Ptr2, rsuint8 len)
{
    rsuint8 v = 0;
    rsuint8 *p1 = (rsuint8*)Ptr1;
    rsuint8 *p2 = (rsuint8 *)Ptr2;

    while(len-- > 0 && v == 0) {
        v = *(p1++) - *(p2++);
    }

    return v;
}

/****************************************************************************
* Name   : itos
* Input  :
* Return :
*---------------------------------------------------------------------------
* Usage  : convert an integer into a string
****************************************************************************/
void *itos(rsuint8 i, void *buf )
{
  char    *d = buf;
  
  *d = (i/16<10)?('0'+i/16):(i/16-10+'A');
  *(d+1) = (i%16<10)?('0'+i%16):(i%16-10+'A');

  return buf;
}
// End of file.

