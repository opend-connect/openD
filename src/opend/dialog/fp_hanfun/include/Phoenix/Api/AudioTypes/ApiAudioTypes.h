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
* Definition of the ApiAudioTypes interface.
*/


#ifndef APIAUDIOTYPES_H
#define APIAUDIOTYPES_H

/****************************************************************************
*                               Include files
****************************************************************************/

/****************************************************************************
*                               Macros/Defines
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

//#if (RTX_CORE_VERSION >= 0x0224)
//  #include <Standard/Common/RsPushPack1.h>
//#else
//  #pragma pack(push,1)
//#endif

/* Global mail primitives:
The global mail primitives MUST be defined in Global.h! */

/*! The enum defines the PCM FSC frequencies supported by the device. */
typedef enum RSENUMTAG(ApiPcmFscFreqType)
{
  AP_FSC_FREQ_8KHZ    = 0x00, /*!< PCM FSC frequency is 8 KHz. */
  AP_FSC_FREQ_16KHZ   = 0x01, /*!< PCM FSC frequency is 16 KHz. */
  AP_FSC_FREQ_32KHZ   = 0x02, /*!< PCM FSC frequency is 32 KHz. */
  AP_FSC_FREQ_INVALID = 0xFF  /*!< [0x03; 0xFF] is invalid. */
} RSENUM8(ApiPcmFscFreqType);

/*! This enum defines the FSC pulse length settings supported by the device
   when it is master on the PCM interface. */
typedef enum RSENUMTAG(ApiPcmFscLengthType)
{
  AP_FSC_LENGTH_1       = 0x00, /*!< The length of PCM FSC pulse is equal to 1 data bit.
                                      (Master) */
  AP_FSC_LENGTH_8       = 0x01, /*!< The length of PCM FSC pulse is equal to 8 data
                                   bits.   (Master) */
  AP_FSC_LENGTH_16      = 0x02, /*!< The length of PCM FSC pulse is equal to 16 data
                                   bits. (Master) */
  AP_FSC_LENGTH_32      = 0x03, /*!< The length of PCM FSC pulse is equal to 32 data
                                   bits. (Master) */
  AP_FSC_LENGTH_48      = 0x04, /*!< The length of PCM FSC pulse is equal to 48 data
                                   bits. (Master) */
  AP_FSC_LENGTH_NORMAL  = 0x05, /*!< Ch 0-5 shifted in after FSC edge. (Slave) */
  AP_FSC_LENGTH_SPLIT   = 0x06, /*!< Ch 0-2 shifted in after FSC edge, Ch 3-5 shifted
                                   after opposite FSC edge. (Slave) */
  AP_FSC_LENGTH_INVALID = 0xFF  /*!< [0x07; 0xFF] is invalid. */
} RSENUM8(ApiPcmFscLengthType);

/*! This enum defines the possible PCM_CLK frequencies (1 clock/bit)
   supported by the device module when it is master on the PCM interface. */
typedef enum RSENUMTAG(ApiPcmClkType)
{
  AP_PCM_CLK_1152    = 0x00, /*!< 1.152 MHz */
  AP_PCM_CLK_2304    = 0x01, /*!< 2.304 MHz */
  AP_PCM_CLK_4608    = 0x02, /*!< 4.608 MHz */
  AP_PCM_CLK_1536    = 0x03, /*!< 1.536 MHz */
  AP_PCM_CLK_INVALID = 0xFF  /*!< [0x04; 0xFF] is invalid. */
} RSENUM8(ApiPcmClkType);


/*! Mail without parameters. */
typedef struct ApiaudiotypesEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} ApiaudiotypesEmptySignalType;

//#if (RTX_CORE_VERSION >= 0x0224)
//  #include <Standard/Common/RsPopPack.h>
//#else
//  #pragma pack(pop)
//#endif
//
//#ifdef __cplusplus
//extern "C"
//{
//#endif
/** \cond internal */

/****************************************************************************
*     Function prototypes for mail packaging and sending(MPS) functions
****************************************************************************/

/** \endcond */
//#ifdef __cplusplus
//}
//#endif
#endif /*APIAUDIOTYPES_H */


