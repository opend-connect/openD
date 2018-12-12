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
* Macros and functions for alignment control.
*
* \note The Microsoft compiler can tell you where padding bytes are inserted in your structs. Define RS_SHOW_PADDING in the compiler options.
*/


#ifndef RS_ALIGN_H
#define RS_ALIGN_H

/****************************************************************************
*                               Include files
****************************************************************************/

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/** \name Alignment in Bytes
* Returns the struct alignment in bytes: 1, 2, 4 or 8. */
//@{
#define RS_ALIGN_SIZE RSOFFSETOF(RsAlignType,p) /*!< Returns the struct alignment in bytes: 1, 2, 4 or 8. */
//@}

/** \name Alignment bit mask
* Contains the bitmask for alignment: 0x0, 0x1, 0x3 or 0x7. */
//@{
#define RS_ALIGN_MASK (RS_ALIGN_SIZE-sizeof(rsuint8)) /*!< Bitmask for alignment: 0x0, 0x1, 0x3 or 0x7. */
//@}

/** \name Insert padding bytes.
* Inserts a uniquely named variable that is \e n bytes in size. */
//@{
#if (RS_SET_PACKING > 1)
  #define RS_PADDING(n) rsuint8 RS_PADy(_padding_,__LINE__)[n];
  #if (RS_POINTER_SIZE == 8)
    #define RS_PADDING64(n) rsuint8 RS_PADy(_padding_,__LINE__)[n];
  #else
    #define RS_PADDING64(n)
  #endif
#else
  #define RS_PADDING(n)   /*!< Insert \e n padding bytes. */
  #define RS_PADDING64(n) /*!< Insert \e n padding bytes when pointers are 64-bit wide. */
#endif
//@}

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/** \cond internal */
#define RS_PADx(x,y) x##y
#define RS_PADy(x,y) RS_PADx(x,y)

typedef struct
{
  rsuint8 b;
  RS_PADDING(RS_SET_PACKING-1)
  void* p;
} RsAlignType;

#if defined(_MSC_VER) && defined(RS_SHOW_PADDING)
  #pragma warning( default : 4820) // padding added
#endif
/** \endcond */

/****************************************************************************
*                           Global variables/const
****************************************************************************/

RS_BEGIN_EXTERN_C

/****************************************************************************
*                             Function prototypes
****************************************************************************/

#ifndef RS_C_INLINE
/// Check pointer alignment.
/** \param p is the pointer/address to be checked.
* \return TRUE if \a p is correctly aligned, and FALSE otherwise. */
rsbool RsIsAligned(const void* p);

/// Calculate padding bytes.
/** \param size of area.
* \return Number of bytes needed to properly align \a size bytes. */
rsuint8 RsPaddingSize(rsuintsz size);
#endif

/** \cond internal */
#ifdef RS_C_INLINE
RS_C_INLINE rsbool RsIsAligned(const void* p)
{
  #if (RS_SET_PACKING > 1)
  union
  {
    const void* p;
    rsuint32 v;
  } ac;
  ac.p = p;
  if (ac.v & RS_ALIGN_MASK)
  {
    return FALSE;
  }
  #endif
  return TRUE;
}

RS_C_INLINE rsuint8 RsPaddingSize(rsuintsz size)
{
  rsuint8 i = (rsuint8)(size & RS_ALIGN_MASK);
  return (i) ? RS_ALIGN_SIZE - i : 0;
}
#endif
/** \endcond */

RS_END_EXTERN_C

#endif

// End of file.

