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
* Endian-swapping macros.
*/


#ifndef RS_ENDIAN_H
#define RS_ENDIAN_H

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/** \name Values for RS_ENDIAN_TYPE
*/
//@{
#define RS_LITTLE_ENDIAN   1 /*!< Intel-like CPU's. */
#define RS_BIG_ENDIAN      2 /*!< Motorola-like CPU's */
//@}

#ifndef RS_ENDIAN_TYPE
  #define RS_ENDIAN_TYPE RS_LITTLE_ENDIAN // Default.
#endif

/** \name General byte-swapping macros
* \anchor byte_swapping
* For swapping the bytes in 16-bit or 32-bit variables.
*/
//@{
#define RS_SWAPBYTES_16(var) ((((rsuint16)var) << 8) + (((rsuint16)var) >> 8)) /*!< Swap the bytes in a 16-bit value. */
#define RS_SWAPBYTES_32(var) (((var) << 24) + (((var) << 8) & 0x00FF0000L) + (((var) >> 8) & 0x0000FF00L) + ((var) >> 24)) /*!< Swap the bytes in a 32-bit value. */
//@}

/** \name Endian-conversion macros.
* \anchor endian_macros
* For conversion between the native endianess and litte- or big-endian.
*/
//@{
#if (RS_ENDIAN_TYPE == RS_LITTLE_ENDIAN)
  #define RS_UINT16_TO_LITTLE_ENDIAN(var)  var /*!< Convert a native 16-bit value to little-endian layout. */
  #define RS_LITTLE_ENDIAN_TO_UINT16(var)  var /*!< Convert a little-endian value native 16-bit layout. */
  #define RS_UINT32_TO_LITTLE_ENDIAN(var)  var /*!< Convert a native 32-bit value to little-endian layout. */
  #define RS_LITTLE_ENDIAN_TO_UINT32(var)  var /*!< Convert a little-endian value native 32-bit layout. */
  #define RS_UINT16_TO_BIG_ENDIAN(var)     RS_SWAPBYTES_16(var) /*!< Convert a native 16-bit value to big-endian layout. */
  #define RS_BIG_ENDIAN_TO_UINT16(var)     RS_SWAPBYTES_16(var) /*!< Convert a big-endian value native 16-bit layout. */
  #define RS_UINT32_TO_BIG_ENDIAN(var)     RS_SWAPBYTES_32(var) /*!< Convert a native 32-bit value to big-endian layout. */
  #define RS_BIG_ENDIAN_TO_UINT32(var)     RS_SWAPBYTES_32(var) /*!< Convert a big-endian value native 32-bit layout. */
#endif

#if (RS_ENDIAN_TYPE == RS_BIG_ENDIAN)
  #define RS_UINT16_TO_LITTLE_ENDIAN(var)  RS_SWAPBYTES_16(var)
  #define RS_LITTLE_ENDIAN_TO_UINT16(var)  RS_SWAPBYTES_16(var)
  #define RS_UINT32_TO_LITTLE_ENDIAN(var)  RS_SWAPBYTES_32(var)
  #define RS_LITTLE_ENDIAN_TO_UINT32(var)  RS_SWAPBYTES_32(var)
  #define RS_UINT16_TO_BIG_ENDIAN(var)     var // Nothing.
  #define RS_BIG_ENDIAN_TO_UINT16(var)     var // Nothing.
  #define RS_UINT32_TO_BIG_ENDIAN(var)     var // Nothing.
  #define RS_BIG_ENDIAN_TO_UINT32(var)     var // Nothing.
#endif
//@}

#endif

// End of file.

