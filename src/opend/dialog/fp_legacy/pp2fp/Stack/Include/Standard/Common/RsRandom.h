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
* Pseudo-random number generation.<br>
* To reinitialize the generator, use 1 as the seed argument. Any other value for seed sets the generator to a random starting point.
*/


#ifndef RS_RANDOM_H
#define RS_RANDOM_H

/****************************************************************************
*                               Include files
****************************************************************************/

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/****************************************************************************
*                           Global variables/const
****************************************************************************/

RS_BEGIN_EXTERN_C

/****************************************************************************
*                             Function prototypes
****************************************************************************/

/// Get random number.
/** \param Seed points to the seed for random-number generation.
* \return Pseudorandom number in the range 0 to 32767. */
rsuint16 RsGetRandom(rsuint32* Seed);

RS_END_EXTERN_C

#endif

// End of file.

