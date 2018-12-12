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

#ifndef APICFG_H
#define APICFG_H

/****************************************************************************
*                               Include files
****************************************************************************/

/****************************************************************************
*                              Macro definitions
****************************************************************************/

#define PHOENIX_API_IMAGECONTROL
#define PHOENIX_API_HAL
#define NUMBER_OF_CODEC_LIST_ENTRIES 2

// #define _PP_


#ifdef _FP_
  #define PHOENIX_API_FP_CC
  #define PHOENIX_API_CODECLIST
  #define PHOENIX_API_FP_CODECLIST
  #define PHOENIX_API_FP_GENERAL
  #define PHOENIX_API_FP_MM
  #define PHOENIX_API_FP_ULE
  #define PHOENIX_API_FP_AUDIO
  #define PHOENIX_API_LAS
  #define PHOENIX_API_LASDB
  #define PHOENIX_API_FP_NO_EMISSION
  #define PHOENIX_API_GENEVENOT
  #define PHOENIX_API_PROD_TEST
#endif
#ifdef _PP_
  #define PHOENIX_API_CC
  #define PHOENIX_API_PP_GENERAL
  #define PHOENIX_API_PP_AUDIO
  #define PHOENIX_API_PP_BATTERY
  #define PHOENIX_API_PP_MM
  #define PHOENIX_API_CODECLIST
  #define PHOENIX_API_PP_CODECLIST
  #define PHOENIX_API_LAS
  //#define PHOENIX_API_PP_NO_EMISSION
  #define PHOENIX_API_GENEVENOT
  #define PHOENIX_API_PROD_TEST
#endif
#ifdef _ULP_
  #define PHOENIX_API_PP_MM
  #define PHOENIX_API_PP_ULE
#endif

#define APIIMAGECONTROL_TASK  API_TASK
#define APIHAL_TASK           API_TASK
#define APIFPAUDIO_TASK       API_TASK
#define APIFPMM_TASK          API_TASK
#define API_FP_MM_APP_TASK    API_TASK
#define APIFPGENERAL_TASK     API_TASK
#define APIFPFWU_TASK         API_TASK
#define API_FP_FWU_APP_TASK   API_TASK
#define APIFPCC_TASK          API_TASK
#define APIFPFWU_TASK         API_TASK
#define APIPROJECT_TASK       API_TASK
#define API_FP_CC_APP_TASK    API_TASK
#define APIFPNOEMISSION_TASK  API_TASK
#define APILAS_TASK           API_TASK
#define APILASDB_TASK         API_TASK
#define APIGENEVENOT_TASK     API_TASK
#define APIFPULE_TASK         API_TASK
#define APICLSS_TASK          API_TASK
#define APIFPLLME_TASK        API_TASK
#define APIHEADSET_TASK       API_TASK
#define APILDS_TASK           API_TASK
#define APIPP2PP_TASK         API_TASK
#define APISCL_TASK           API_TASK
#define APITAM_TASK           API_TASK
#define APISUOTA_TASK         API_TASK
                       
#define APICC_TASK            API_TASK
#define APIPPMM_TASK          API_TASK
#define APIPPGENERAL_TASK     API_TASK
#define APIPPAUDIO_TASK       API_TASK
#define APIPPBATTERY_TASK     API_TASK
#define APILAS_TASK           API_TASK
#define APIPPNOEMISSION_TASK  API_TASK
#define APIGENEVENOT_TASK     API_TASK
#define APIPRODTEST_TASK      API_TASK
#define APIPPULE_TASK         API_TASK
#define API_PP_ULE_APP_TASK   API_TASK

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


RS_END_EXTERN_C

#endif

