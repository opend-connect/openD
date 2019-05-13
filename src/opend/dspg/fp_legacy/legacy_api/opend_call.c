#ifdef __cplusplus
extern "C"
{
#endif
/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_call.c
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber, Heiko Berger
 * @brief
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 */

#include <stdio.h>

#include "opend_dataTypes.h"
#include "opend.h"
#include "opend_api.h"
#include "opend_call.h"
#include "opend_call_api.h"

#include "apphan.h"
#include "appmsgparser.h"
#include "appsrv.h"
#include "tcx_util.h"
#include "cmbs_han.h"
#include "appcall.h"

openD_callApiPrimitives_t _cPrimitives;

extern void keyb_ReleaseNotify(u16 u16_CallId);
extern u16 _keyb_CallIdInput(void);

static void opend_call_setup_cllb(uint8_t callId);

static void opend_call_terminated_cllb();

openD_status_t openD_callApi_init( openD_callApiPrimitives_t *cPrimitives )
{
  if( !cPrimitives )
  {
    return OPEND_STATUS_ARGUMENT_INVALID;
  }

  _cPrimitives.openD_callApiCfm = cPrimitives->openD_callApiCfm;
  _cPrimitives.openD_callApiInd = cPrimitives->openD_callApiInd;
  initMsgParserCall(opend_call_setup_cllb, opend_call_terminated_cllb);

  return OPEND_STATUS_OK;
}

static void opend_call_setup_cllb(uint8_t callId)
{
}

static void opend_call_terminated_cllb()
{
  openD_callApiCfm_t openD_callApiCfm;
  openD_callApiCfm.service = OPEND_CALLAPI_RELEASE;
  openD_callApiCfm.status = OPEND_STATUS_OK;

  _cPrimitives.openD_callApiCfm(&openD_callApiCfm);
}

openD_status_t openD_callApi_request( openD_callApiReq_t *cRequest )
{
  openD_status_t ret;

  if( !cRequest )
  {
    return OPEND_STATUS_ARGUMENT_INVALID;
  }

  /* Call setup request. */
  ST_APPCALL_PROPERTIES st_Properties[8];
  int n_Prop = 0;
  char ch_cli[40];
  char ch_cni[40];
  char ch_cld[20];
  char ch_clineid[20];
  char s_codecs[CMBS_AUDIO_CODEC_MAX * 2] = { 0 };
  char codec;
  char ch_melody[20];
  char ch_call_direction[20];
  char ch_linesubtype[10];
  static char lineId = 1;
  char handsetID[2];

  /* Call release. */
  u16 u16_CallId;
  char ch_Reason[2];
  char ch;
  char HsNr[20];
  ST_APPCALL_PROPERTIES st_Properties_release;
  uint32_t u32_CallId;
  PST_CALL_OBJ pst_Call;

  switch( cRequest->service ) {

    case OPEND_CALLAPI_SETUP:
      memcpy(ch_cli, "n", 1);
      memcpy(ch_cni, "0", 1);
      memcpy(ch_clineid, &lineId, 1);
      lineId++;
      if(lineId == 10) lineId = 1;
      strcpy(handsetID, "h");
      strcat(handsetID, cRequest->param.setup.pmid);
      memcpy(ch_cld, handsetID, 2);
      memcpy(&codec, "w", 1);
      memcpy(ch_melody, "3", 1);
      memcpy(ch_linesubtype, "n", 1);
      switch (codec)
      {
      case 'w':
        sprintf(s_codecs, "%d,%d", (CMBS_AUDIO_CODEC_PCM_LINEAR_WB), (CMBS_AUDIO_CODEC_PCM_LINEAR_NB));
        break;
      case 'a':
        sprintf(s_codecs, "%d", (CMBS_AUDIO_CODEC_PCMA));
        break;
      case 'u':
        sprintf(s_codecs, "%d", (CMBS_AUDIO_CODEC_PCMU));
        break;
      case '8':
        sprintf(s_codecs, "%d", (CMBS_AUDIO_CODEC_PCM8));
        break;
      case 'A':
        sprintf(s_codecs, "%d", (CMBS_AUDIO_CODEC_PCMA_WB));
        break;
      case 'U':
        sprintf(s_codecs, "%d", (CMBS_AUDIO_CODEC_PCMU_WB));
        break;
      case 'n':
      default:
        sprintf(s_codecs, "%d", (CMBS_AUDIO_CODEC_PCM_LINEAR_NB));
      }
      memcpy(ch_call_direction, "1", 1);
	    memset(&st_Properties, 0x00, sizeof(st_Properties));
      st_Properties[0].e_IE = CMBS_IE_CALLERPARTY;
      st_Properties[0].psz_Value = ch_cli;
      st_Properties[1].e_IE = CMBS_IE_CALLEDPARTY;
      st_Properties[1].psz_Value = ch_cld;
      st_Properties[2].e_IE = CMBS_IE_MEDIADESCRIPTOR;
      st_Properties[2].psz_Value = s_codecs;
      st_Properties[3].e_IE = CMBS_IE_LINE_ID;
      st_Properties[3].psz_Value = ch_clineid;
      if ( strlen(ch_cni) && (ch_cni[0] != '0') )
      {
        st_Properties[4].e_IE = CMBS_IE_CALLERNAME;
        st_Properties[4].psz_Value = ch_cni;
        n_Prop = 5;
      }
      else
      {
        n_Prop = 4;
      }
      st_Properties[n_Prop].e_IE = CMBS_IE_MELODY;
      st_Properties[n_Prop].psz_Value = ch_melody;
      n_Prop++;
      st_Properties[n_Prop].e_IE = CMBS_IE_CALL_DIRECTION;
      st_Properties[n_Prop].psz_Value = ch_call_direction;
      n_Prop++;
      if ( strlen(ch_linesubtype) && (ch_linesubtype[0] != 'n') )
      {
        st_Properties[n_Prop].e_IE = CMBS_IE_LINE_SUBTYPE;
        st_Properties[n_Prop].psz_Value = ch_linesubtype;
        n_Prop++;
      }
      appcall_EstablishCall(st_Properties, n_Prop);

      ret = OPEND_STATUS_OK;
      break;

    case OPEND_CALLAPI_RELEASE:

      memcpy(&u32_CallId, (char*)&cRequest->param.setup.pmid[1], 1);

      pst_Call = _appcall_CallObjGetById(u32_CallId);
      if ( pst_Call )
        if ( pst_Call->u32_CallInstance )
          u16_CallId = (uint16_t)u32_CallId;
        else return OPEND_STATUS_ARGUMENT_INVALID;

      if ( u16_CallId == 0xFFFF )
      {
        printf(" \n Invalid Caller ID - Retry with the correct ID \n");
      }
      else
      {
        ch_Reason[0] = 0;
        ch_Reason[1] = 0;

        st_Properties_release.e_IE = CMBS_IE_CALLRELEASE_REASON;
        st_Properties_release.psz_Value = ch_Reason;

        appcall_ReleaseCall(&st_Properties_release, 1, u16_CallId, 0);

        keyb_ReleaseNotify(u16_CallId);
      }
      ret = OPEND_STATUS_OK;
      break;

    default:
      ret = OPEND_STATUS_SERVICE_UNKNOWN;
    }

    return ret;
}

void openD_call_confirmation( openD_callApiCfm_t *cConfirm ) {

    if( _cPrimitives.openD_callApiCfm ) {
        _cPrimitives.openD_callApiCfm( cConfirm );
    }
    return;
}

void openD_call_indication( openD_callApiInd_t *cIndication ) {

    if( _cPrimitives.openD_callApiInd ) {
        _cPrimitives.openD_callApiInd( cIndication );
    }
    return;
}

#ifdef __cplusplus
}
#endif
