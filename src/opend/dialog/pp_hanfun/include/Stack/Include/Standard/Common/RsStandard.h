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
* Standard types and macros.
*/


#ifndef RS_STANDARD_H
#define RS_STANDARD_H

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/** \name Values for rsbool
* Values for the \ref rsbool type. */
//@{
#ifndef TRUE
  #define TRUE  1  /*!< Boolean true. */
#endif
#ifndef FALSE
  #define FALSE 0  /*!< Boolean false. */
#endif
//@}

/*! \name Value for null pointers
*/
#ifndef NULL
  #ifdef __cplusplus
    #define NULL 0
  #else
    #define NULL ((void*)0)
  #endif
#endif

/** \name Mimimum and maximum computation
*/
//@{
#ifndef RSMIN
  #define RSMIN(a, b) (((a) < (b)) ? (a) : (b)) /*!< Computes the minimum of \a a and \a b. */
  #define RSMAX(a, b) (((a) > (b)) ? (a) : (b)) /*!< Computes the maximum of \a a and \a b. */
#endif
//@}

/** \name Field offset computation for structs and unions
*/
//@{
#ifndef RSOFFSETOF
  /*! \def RSOFFSETOF(type, field)
  * Computes the byte offset of \a field from the beginning of \a type. */
  #define RSOFFSETOF(type, field) ((size_t)(&((type*)0)->field))
#endif
#ifndef RSCONTAININGOFFSET
  /*! \def RSCONTAININGOFFSET(address, type, field)
  * Computes the beginning of \a type from \a field. This the reverse of \ref RSOFFSETOF. */
  #define RSCONTAININGOFFSET(address, type, field) ((type*)((rsuint8*)(address)-(size_t)(&((type*)0)->field)))
#endif
//@}

#ifndef RSDEBUG
  #if defined(DBG) || defined(_DEBUG)
    #define RSDEBUG
  #endif
#endif

/*! \name Debug-only code
* For code that should only be included in debug compilation. */
#ifdef RSDEBUG
  #define RSDEBUGCODE(code) {code;}
#else
  #define RSDEBUGCODE(code) {}
#endif

/** \name Enumeration Macros
* \anchor enum_macros
* For defining enumerated values for use in external interfaces.
* The following code fragment shows the use of RSENUMTAG and RSENUM16.
*
* \code
* typedef enum RSENUMTAG(RsErrorIdType)
*   RSE_NONE,
*   ...
*   RSE_MAX = 0xFFFF
* } RSENUM16(RsErrorIdType);
* \endcode
*
*/
//@{
#ifndef RS_OVERRIDE_ENUMS
  #ifdef RS_AUTOSIZE_ENUMS
    // For compilers that can auto-size enums.
    #define RSENUM8(EnumName)   EnumName  /*!< For enums sized to 8-bits (unsigned). */
    #define RSENUM8S(EnumName)  EnumName  /*!< For enums sized to 8-bits (signed). */
    #define RSENUM16(EnumName)  EnumName  /*!< For enums sized to 16-bits. */
    #define RSENUM32(EnumName)  EnumName  /*!< For enums sized to 32-bits. */
    #define RSENUMTAG(EnumName) EnumName  /*!< For setting the tagname. */
  #else
    // For compilers that enforce enum=int.
    #define RSENUM8(EnumName)   Enum_##EnumName; typedef rsuint8  EnumName
    #define RSENUM8S(EnumName)  Enum_##EnumName; typedef rsint8   EnumName
    #define RSENUM16(EnumName)  Enum_##EnumName; typedef rsuint16 EnumName
    #define RSENUM32(EnumName)  Enum_##EnumName; typedef rsuint32 EnumName
    #define RSENUMTAG(EnumName) Enum_##EnumName
  #endif
#endif
//@}

/** \name Structure packing macros
* \anchor struct_packing
* For defining structs/unions that must be packed to 1-byte alignment.
*
* \code
* typedef RS_PACKED_STRUCT_BEGIN SampleType
* {
*   rsuint8 Field1;
*   rsuint32 Field2;
* } RS_PACKED_STRUCT_END(SampleType);
* \endcode
*
*/
//@{
#ifndef RS_PACKED_STRUCT_BEGIN
  #define RS_PACKED_STRUCT_BEGIN     struct  /*!< Use at start of struct declaration */
  #define RS_PACKED_STRUCT_END(name) name    /*!< Use at end of struct declaration */
  #define RS_PACKED_UNION_BEGIN      union   /*!< Use at start of union declaration */
  #define RS_PACKED_UNION_END(name)  name    /*!< Use at end of union  declaration */
  #define RS_PACKED_MEMBER                   /*!< Use with members of a packed type */
  #define RS_PACKED_PTR                      /*!< Use with pointers to a packed type */
#endif
//@}

/** \name Function/variable Macros
* Macros for modifying the default signature and placement of functions and variables. */
//@{
#ifndef RS_FAR_ADR
  #define RS_FAR_ADR         /*!< Places variables and constants in far memory. */
  #define RS_NEAR_ADR        /*!< Places variables and constants in near memory. */
  #define RS_RAM_ADR         /*!< Places functions in RAM (instead of ROM/flash). */
  #define RS_NO_INIT         /*!< Surpresses initialization of variables. */
  #define RS_ROOT_SYMBOL     /*!< Ensures that a function or variable is included in the object code even if unused. */
  #define RS_NOP             /*!< Inserts no operation instruction. */
#endif
//@}

/** \name C-linking specifiers.
* Macros for modifying the link specification of functions and variables. */
//@{
#ifdef __cplusplus
  #define RS_EXTERN_C extern "C"  /*!< Force C-linking for a single function or variable. */
  #define RS_BEGIN_EXTERN_C extern "C" { /*!< Begin C-linking for a group of function and/or variables. */
  #define RS_END_EXTERN_C } /*!< End C-linking for a group of function and/or variables. */
#else
  #define RS_EXTERN_C
  #define RS_BEGIN_EXTERN_C
  #define RS_END_EXTERN_C
#endif
//@}

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

#ifndef RS_CHAR_SIZE
  #define RS_CHAR_SIZE 1 /*!< Size of a char, 1 or 2 bytes. */
#endif

#ifndef RS_POINTER_SIZE
  #define RS_POINTER_SIZE 4 /*!< Size of a pointer, 32 or 64 bits. */
#endif

#ifndef RS_OVERRIDE_TYPES
  typedef char rschar;                  /*!< Plain char for strings. */
  typedef unsigned char rsuint8;        /*!< 8-bit unsigned quantity. */
  typedef signed char rsint8;           /*!< 8-bit signed quantity. */
  typedef unsigned short rsuint16;      /*!< 16-bit unsigned quantity. */
  typedef signed short rsint16;         /*!< 16-bit signed quantity. */
  typedef unsigned long rsuint32;       /*!< 32-bit unsigned quantity. */
  typedef signed long rsint32;          /*!< 32-bit signed quantity. */
  typedef unsigned char rsbitfield;     /*!< For use as bitfields. */
  typedef unsigned char rsbool;         /*!< boolean quantity. */
  #ifdef RS_ENABLE_INT64
  typedef unsigned long long rsuint64;  /*!< 64-bit unsigned quantity. */
  typedef signed long long rsint64;     /*!< 64-bit signed quantity. */
  #endif
  #if (RS_POINTER_SIZE == 4)
  typedef unsigned long rsuintptr;      /*!< Unsigned quantity, same size as a pointer, 32 or 64 bits. */
  #endif
  #if (RS_POINTER_SIZE == 8)
  typedef unsigned long long rsuintptr; /*!< Unsigned quantity, same size as a pointer, 32 or 64 bits. */
  #endif
#endif

#ifndef RS_CONST
  #define RS_CONST const /*!< Place Core configuration in const memory (Core internal use). */
#endif

/** \cond internal */

#define RS_QUOTEx(x) #x
#define RS_QUOTEy(x) RS_QUOTEx(x)

#ifndef RS_FASTCODE_ADR
  #define RS_FASTCODE_ADR
#endif
#ifndef RS_FASTDATA_ADR
  #define RS_FASTDATA_ADR
#endif
#ifndef RS_DATA_ADR
  #define RS_DATA_ADR
#endif

#ifndef RS_CHECK_CALL_FROM_ISR
  #define RS_CHECK_CALL_FROM_ISR 1
#endif

// Fusion standard types.
#ifndef __KERNEL__
  // Same names used in linux/include/asm/types.h
  #define u8 rsuint8
  #define u16 rsuint16
  #define u32 rsuint32
#endif
#define i32 rsint32

#ifndef __GNUC__
  #define __attribute__(p)
#endif

/** \endcond */

/// memcpy macro optimized for small fixed sizes.
/** \param dst Destination pointer.
* \param src Source pointer.
* \param size Number of bytes to copy. */
#define RSMEMCPYF(dst, src, size) \
  { \
    typedef struct { unsigned char m[(size > 24) ? -1 : 1]; } cpchk; \
    { \
      typedef struct { unsigned char m[(size > 12) ? 12 : size]; } cpst1; \
      cpst1* d = (cpst1*)(dst); \
      cpst1* s = (cpst1*)(src); \
      *d = *s; \
    } \
    if (size > 12) \
    { \
      typedef struct { unsigned char m[(size > 12) ? size-12 : size]; } cpst2; \
      cpst2* d = (cpst2*)(((char*)(dst))+12) ; \
      cpst2* s = (cpst2*)(((char*)(src))+12) ; \
      *d = *s; \
    } \
  }

/// memset macro optimized for small fixed sizes.
/** \param dst Destination pointer.
* \param val Value to set.
* \param size Number of bytes to set. */
#define RSMEMSETF(dst, val, size) \
{ \
  typedef struct { unsigned char m[(size > 12) ? -1 : 1]; } mschk; \
  rsuint8* d = (rsuint8*)dst; \
  if (size == 1) \
  { \
    d[0] = val; \
  } \
  else if (size == 2) \
  { \
    d[0] = val; \
    d[1] = val; \
  } \
  else if (size == 3) \
  { \
    d[0] = val; \
    d[1] = val; \
    d[2] = val; \
  } \
  else if (size == 4) \
  { \
    d[0] = val; \
    d[1] = val; \
    d[2] = val; \
    d[3] = val; \
  } \
  else if (size == 5) \
  { \
    d[0] = val; \
    d[1] = val; \
    d[2] = val; \
    d[3] = val; \
    d[4] = val; \
  } \
  else if (size == 6) \
  { \
    d[0] = val; \
    d[1] = val; \
    d[2] = val; \
    d[3] = val; \
    d[4] = val; \
    d[5] = val; \
  } \
  else if (size == 7) \
  { \
    d[0] = val; \
    d[1] = val; \
    d[2] = val; \
    d[3] = val; \
    d[4] = val; \
    d[5] = val; \
    d[6] = val; \
  } \
  else if (size == 8) \
  { \
    d[0] = val; \
    d[1] = val; \
    d[2] = val; \
    d[3] = val; \
    d[4] = val; \
    d[5] = val; \
    d[6] = val; \
    d[7] = val; \
  } \
  else if (size == 9) \
  { \
    d[0] = val; \
    d[1] = val; \
    d[2] = val; \
    d[3] = val; \
    d[4] = val; \
    d[5] = val; \
    d[6] = val; \
    d[7] = val; \
    d[8] = val; \
  } \
  else if (size == 10) \
  { \
    d[0] = val; \
    d[1] = val; \
    d[2] = val; \
    d[3] = val; \
    d[4] = val; \
    d[5] = val; \
    d[6] = val; \
    d[7] = val; \
    d[8] = val; \
    d[9] = val; \
  } \
  else if (size == 11) \
  { \
    d[0] = val; \
    d[1] = val; \
    d[2] = val; \
    d[3] = val; \
    d[4] = val; \
    d[5] = val; \
    d[6] = val; \
    d[7] = val; \
    d[8] = val; \
    d[9] = val; \
    d[10] = val; \
  } \
  else if (size == 12) \
  { \
    d[0] = val; \
    d[1] = val; \
    d[2] = val; \
    d[3] = val; \
    d[4] = val; \
    d[5] = val; \
    d[6] = val; \
    d[7] = val; \
    d[8] = val; \
    d[9] = val; \
    d[10] = val; \
    d[11] = val; \
  } \
}

#endif

// End of file.

