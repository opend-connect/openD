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
* Bit-position macros, and bit/port manipulation macros.
*/


#ifndef RS_BITMACROS_H
#define RS_BITMACROS_H

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/** \name Bit positions
*/
//@{
#define RSBIT0        0x01
#define RSBIT1        0x02
#define RSBIT2        0x04
#define RSBIT3        0x08
#define RSBIT4        0x10
#define RSBIT5        0x20
#define RSBIT6        0x40
#define RSBIT7        0x80

#define RSBIT8      0x0100
#define RSBIT9      0x0200
#define RSBIT10     0x0400
#define RSBIT11     0x0800
#define RSBIT12     0x1000
#define RSBIT13     0x2000
#define RSBIT14     0x4000
#define RSBIT15     0x8000

#define RSBIT16 0x00010000
#define RSBIT17 0x00020000
#define RSBIT18 0x00040000
#define RSBIT19 0x00080000
#define RSBIT20 0x00100000
#define RSBIT21 0x00200000
#define RSBIT22 0x00400000
#define RSBIT23 0x00800000

#define RSBIT24 0x01000000
#define RSBIT25 0x02000000
#define RSBIT26 0x04000000
#define RSBIT27 0x08000000
#define RSBIT28 0x10000000
#define RSBIT29 0x20000000
#define RSBIT30 0x40000000
#define RSBIT31 0x80000000
//@}

/** \name Bit manipulation macros.
*/
//@{
#define RSSETBIT(var,bitno) ((var) |= (bitno))
#define RSCLRBIT(var,bitno) ((var) &= ~(bitno))
#define RSTSTBIT(var,bitno) ((var) & (bitno))
//@}

/** \name I/O port macros.
*/
//@{
#define RSSETPORT(port,bit)    (port |=  (1<<bit))
#define RSCLRPORT(port,bit)    (port &= ~(1<<bit))
#define RSTOGGLEPORT(port,bit) (port ^= (1<<bit))
#define RSGETPORT(port,bit)    (port & (1<<bit))
#define RSINPUTPORT(port,bit)  (port &= ~(1<<bit))
#define RSOUTPUTPORT(port,bit) (port |=  (1<<bit))
//@}

#endif

// End of file.

