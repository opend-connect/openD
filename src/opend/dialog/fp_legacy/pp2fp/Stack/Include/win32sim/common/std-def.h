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

#ifndef __STD_DEF_H__
#define __STD_DEF_H__


typedef signed char       int8;
typedef unsigned char     uint8;
typedef unsigned short    uint16;
typedef signed short      int16;
typedef unsigned long     uint32;
typedef signed long       int32;
typedef unsigned char     boolean;

// The colors
#define CLR_BLUE           RGB( 0x00, 0x00, 0xff )
#define CLR_RED            RGB( 0xff, 0x00, 0x00 )
#define CLR_GREEN          RGB( 0x00, 0xff, 0x00 )
#define CLR_BLACK          RGB( 0x00, 0x00, 0x00 )
#define CLR_YELLOW         RGB( 0xff, 0xff, 0x00 )
#define CLR_CYAN           RGB( 0x00, 0xff, 0xff )
#define CLR_PINK           RGB( 0xff, 0x00, 0xff )
#define CLR_GRAY           RGB( 0x80, 0x80, 0x80 )
#define CLR_WHITE          RGB( 0xff, 0xff, 0xff )
#define CLR_DARKRED        RGB( 0x80, 0x00, 0x00 )
#define CLR_DARKGREEN      RGB( 0x00, 0x80, 0x00 )
#define CLR_DARKBLUE       RGB( 0x00, 0x00, 0x80 )
#define CLR_DARKPINK       RGB( 0x80, 0x00, 0x80 )
#define CLR_DARKGRAY       RGB( 0x50, 0x50, 0x50 )
#define CLR_LIGHTBLUE      RGB( 0x00, 0x80, 0xff )
#define CLR_LIGHTGRAY      RGB( 0xC0, 0xC0, 0xC0 )
#define CLR_LIGHTGREEN     RGB( 0x00, 0xff, 0x80 )
#define CLR_LIGHTRED       RGB( 0xff, 0x00, 0x80 )


#ifndef min
  #define min(x,y) ( (x<y) ? x : y )
  #define max(x,y) ( (x>y) ? x : y )
#endif

#ifndef BIT0
  #define BIT0               0x01
  #define BIT1               0x02
  #define BIT2               0x04
  #define BIT3               0x08
  #define BIT4               0x10
  #define BIT5               0x20
  #define BIT6               0x40
  #define BIT7               0x80

  #define BIT8             0x0100
  #define BIT9             0x0200
  #define BIT10            0x0400
  #define BIT11            0x0800
  #define BIT12            0x1000
  #define BIT13            0x2000
  #define BIT14            0x4000
  #define BIT15            0x8000

  #define BIT16        0x00010000
  #define BIT17        0x00020000
  #define BIT18        0x00040000
  #define BIT19        0x00080000
  #define BIT20        0x00100000
  #define BIT21        0x00200000
  #define BIT22        0x00400000
  #define BIT23        0x00800000

  #define BIT24        0x01000000
  #define BIT25        0x02000000
  #define BIT26        0x04000000
  #define BIT27        0x08000000
  #define BIT28        0x10000000
  #define BIT29        0x20000000
  #define BIT30        0x40000000
  #define BIT31        0x80000000
#endif

 // Macros to force the compiler to regard compound type declarations as packed (no padding).
#ifndef RTX_PACKED_STRUCT_BEGIN
#define RTX_PACKED_STRUCT_BEGIN     struct            // use at start of declaration
#define RTX_PACKED_STRUCT_END(name) name              // use at end of declaration
#define RTX_PACKED_UNION_BEGIN      union             // use at start of declaration
#define RTX_PACKED_UNION_END(name)  name              // use at end of declaration
#define RTX_PACKED_MEMBER                             // use with members of a packed type
#define RTX_PACKED_PTR                                // use with pointers to a packed type

/******************************************************************************
* Enumerations.
******************************************************************************/

#define ENUM8(EnumName)  Enum_##EnumName; typedef uint8  EnumName
#define ENUM16(EnumName) Enum_##EnumName; typedef uint16 EnumName
#define ENUM32(EnumName) Enum_##EnumName; typedef uint32 EnumName
#endif
/******************************************************************************
* Warnings.
******************************************************************************/

#ifdef _MSC_VER
  #pragma warning( disable : 4100) // unreferenced formal parameter
  #pragma warning( disable : 4127) // conditional expression is constant
  #pragma warning( disable : 4244) // '+=' : conversion from 'int' to 'uint16', possible loss of data
  #pragma warning( disable : 4245) // 'initializing' : conversion from 'int' to 'uint32', signed/unsigned mismatch
#endif

#endif
