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
#ifndef APIFPPRODTESTMPS_H
#define APIFPPRODTESTMPS_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <Phoenix/Api/FpCc/ApiFpCc.h>

//#ifdef __cplusplus
//extern "C"
//{
//#endif
void SendApiProdTestReq ( RosTaskIdType Src,
                          rsuint16 Opcode,
                          rsuint16 ParameterLength,
                          rsuint8 Parameters [1]);

#ifdef PROJECT_FP_PROD_TEST_EXTENSION
/* Added By ED. Sitel */
/****************************************************************************
* FUNCTION:      SendApiFpCcSetupAudioLbReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_SETUP_LOOPBACK_REQ
****************************************************************************/
void SendApiFpCcSetupAudioLbReq(   RosTaskIdType Dst,
                                   rsbool LoopBack,
                                   rsuint8 LoopBackMode);
/****************************************************************************
* FUNCTION:      SendApiFpCcSetupAudioLbCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_CC_SETUP_LOOPBACK_CFM
****************************************************************************/
void SendApiFpCcSetupAudioLbCfm(  RosTaskIdType Dst,
                                  RsStatusType status,
                                  rsuint8 LoopBackMode);
/****************************************************************************
* FUNCTION:      SendApiFpProdTestGpioModeReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_SET_GPIO_MODE_REQ
****************************************************************************/
void SendApiFpProdTestGpioModeReq(  RosTaskIdType Dst,
                                    rsuint16 GpioId,
                                    rsuint8 ModeType );
/****************************************************************************
* FUNCTION:      SendApiFpProdTestGpioModeCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_SET_GPIO_MODE_CFM
****************************************************************************/
void SendApiFpProdTestGpioModeCfm(  RosTaskIdType Dst,
                                    RsStatusType status );

/****************************************************************************
* FUNCTION:      SendApiFpProdTestGetGpioModeReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_GET_GPIO_MODE_REQ
****************************************************************************/
void SendApiFpProdTestGetGpioModeReq( RosTaskIdType Dst,
                                      rsuint16 GpioId );

/****************************************************************************
* FUNCTION:      SendApiFpProdTestGpioModeCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_SET_GPIO_MODE_CFM
****************************************************************************/
void SendApiFpProdTestGetGpioModeCfm(  RosTaskIdType Dst,
                                       rsuint8 ModeType );

/****************************************************************************
* FUNCTION:      SendApiFpProdTestSetGpioStateReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_SET_GPIO_STATE_REQ
****************************************************************************/
void SendApiFpProdTestSetGpioStateReq( RosTaskIdType Dst,
                                       rsuint16 GpioId,
                                       rsuint8 GpioState);

/****************************************************************************
* FUNCTION:      SendApiFpProdTestSetGpioStateCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_SET_GPIO_STATE_CFM
****************************************************************************/
void SendApiFpProdTestSetGpioStateCfm(  RosTaskIdType Dst,
                                        RsStatusType status );

/****************************************************************************
* FUNCTION:      SendApiFpProdTestGetGpioStateReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_GET_GPIO_STATE_REQ
****************************************************************************/
void SendApiFpProdTestGetGpioStateReq( RosTaskIdType Dst,
                                       rsuint16 GpioId);

/****************************************************************************
* FUNCTION:      SendApiFpProdTestGetGpioStateCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_GET_GPIO_STATE_CFM
****************************************************************************/
void SendApiFpProdTestGetGpioStateCfm(  RosTaskIdType Dst,
                                        rsuint8 GpioState );

/****************************************************************************
* FUNCTION:      SendApiFpProdTestSetMacAddReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_SET_MAC_ADD_REQ
****************************************************************************/
void SendApiFpProdTestSetMacAddReq( RosTaskIdType Dst,
                                    rsuint8 *MacAddPtr,
                                    rsuint8  EthPort);

/****************************************************************************
* FUNCTION:      SendApiFpProdTestSetMacAddCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_SET_MAC_ADD_CFM
****************************************************************************/
void SendApiFpProdTestSetMacAddCfm(  RosTaskIdType Dst,
                                     RsStatusType status );

/****************************************************************************
* FUNCTION:      SendApiFpProdTestGetMacAddReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_GET_MAC_ADD_REQ
****************************************************************************/
void SendApiFpProdTestGetMacAddReq( RosTaskIdType Dst,
                                    rsuint8  EthPort);

/****************************************************************************
* FUNCTION:      SendApiFpProdTestGetMacAddCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_GET_MAC_ADD_CFM
****************************************************************************/
void SendApiFpProdTestGetMacAddCfm(  RosTaskIdType Dst,
                                     rsuint8 *MacAddPtr );

/****************************************************************************
* FUNCTION:      SendApiFpProdTestSetEnvBandGapReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_SET_ENV_BAND_GAP_REQ
****************************************************************************/
void SendApiFpProdTestSetEnvBandGapReq(  RosTaskIdType Dst,
                                         rsuint8 BandGap );

/****************************************************************************
* FUNCTION:      SendApiFpProdTestSetEnvBandGapCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_SET_ENV_BAND_GAP_CFM
****************************************************************************/
void SendApiFpProdTestSetEnvBandGapCfm(  RosTaskIdType Dst,
                                         RsStatusType status );

/****************************************************************************
* FUNCTION:      SendApiFpProdTestGetEnvBandGapReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_GET_ENV_BAND_GAP_REQ
****************************************************************************/
void SendApiFpProdTestGetEnvBandGapReq(  RosTaskIdType Dst );

/****************************************************************************
* FUNCTION:      SendApiFpProdTestGetEnvBandGapCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_GET_ENV_BAND_GAP_CFM
****************************************************************************/
void SendApiFpProdTestGetEnvBandGapCfm(  RosTaskIdType Dst,
                                         rsuint8 BandGap );

/****************************************************************************
* FUNCTION:      SendApiFpProdTestSetResetOpReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_SET_RESET_OP_REQ
****************************************************************************/
void SendApiFpProdTestSetResetOpReq(  RosTaskIdType Dst,
                                      rsuint8       OpMode);

/****************************************************************************
* FUNCTION:      SendApiFpProdTestSetResetOpCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_SET_RESET_OP_CFM
****************************************************************************/
void SendApiFpProdTestSetResetOpCfm(  RosTaskIdType Dst,
                                      RsStatusType status);

/****************************************************************************
* FUNCTION:      SendApiFpProdTestSetResetModuleReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_SET_RESET_MODULE_REQ
****************************************************************************/
void SendApiFpProdTestSetResetModuleReq(  RosTaskIdType Dst,
                                          rsuint8       OpMode );

/****************************************************************************
* FUNCTION:      SendApiFpProdTestSetResetModuleCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_SET_RESET_MODULE_CFM
****************************************************************************/
void SendApiFpProdTestSetResetModuleCfm(  RosTaskIdType Dst,
                                          RsStatusType status);

/****************************************************************************
* FUNCTION:      SendApiFpProdTestSetEnvVarStrReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_SET_ENV_VAR_STR_REQ
****************************************************************************/
void SendApiFpProdTestSetEnvVarStrReq(  RosTaskIdType Dst,
                                         rsuint8 EnvVarID,
                                         rschar *EnvVarPtr);

/****************************************************************************
* FUNCTION:      SendApiFpProdTestSetEnvVarStrCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_SET_ENV_VAR_STR_CFM
****************************************************************************/
void SendApiFpProdTestSetEnvVarStrCfm(  RosTaskIdType Dst,
                                        RsStatusType status );

/****************************************************************************
* FUNCTION:      SendApiFpProdTestGetEnvVarStrReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_GET_ENV_VAR_STR_REQ
****************************************************************************/
void SendApiFpProdTestGetEnvVarStrReq(  RosTaskIdType Dst,
                                        rsuint8 EnvVarID );

/****************************************************************************
* FUNCTION:      SendApiFpProdTestGetEnvVarStrCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_GET_ENV_VAR_STR_CFM
****************************************************************************/
void SendApiFpProdTestGetEnvVarStrCfm(  RosTaskIdType Dst,
                                        rschar* EnvVarPtr );


/****************************************************************************
* FUNCTION:      SendApiFpProdTestSetEnvVarIntReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_SET_ENV_VAR_INT_REQ
****************************************************************************/
void SendApiFpProdTestSetEnvVarIntReq(  RosTaskIdType Dst,
                                         rsuint8 EnvVarID,
                                         rsuint32 EnvVarInt);

/****************************************************************************
* FUNCTION:      SendApiFpProdTestSetEnvVarIntCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_SET_ENV_VAR_INT_CFM
****************************************************************************/
void SendApiFpProdTestSetEnvVarIntCfm(  RosTaskIdType Dst,
                                        RsStatusType status );

/****************************************************************************
* FUNCTION:      SendApiFpProdTestGetEnvVarIntReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_GET_ENV_VAR_INT_REQ
****************************************************************************/
void SendApiFpProdTestGetEnvVarIntReq(  RosTaskIdType Dst,
                                        rsuint8 EnvVarID );

/****************************************************************************
* FUNCTION:      SendApiFpProdTestGetEnvVarIntCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_GET_ENV_VAR_INT_CFM
****************************************************************************/
void SendApiFpProdTestGetEnvVarIntCfm(  RosTaskIdType Dst,
                                        rsuint8 *EnvVarPtr);

/****************************************************************************
* FUNCTION:      SendApiFpProdTestSetLEDReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_SET_LED_REQ
****************************************************************************/
void SendApiFpProdTestSetLEDReq(  RosTaskIdType Dst,
                                  rsuint8 state,
                                  rsuint8 ledID);

/****************************************************************************
* FUNCTION:      SendApiFpProdTestSetLEDCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_SET_LED_CFM
****************************************************************************/
void SendApiFpProdTestSetLEDCfm(  RosTaskIdType Dst,
                                  RsStatusType status );

/****************************************************************************
* FUNCTION:      SendApiFpProdTestGetFxStatusReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_GET_FX_STATUS_REQ
****************************************************************************/
void SendApiFpProdTestGetFxStatusReq(  RosTaskIdType Dst,
                                       rsuint8 LineID,
                                       rsuint8 StatusID);

/****************************************************************************
* FUNCTION:      SendApiFpProdTestGetFxStatusCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_GET_FX_STATUS_CFM
****************************************************************************/
void SendApiFpProdTestGetFxStatusCfm(  RosTaskIdType Dst,
                                       rsuint8 FxStatus );

/****************************************************************************
* FUNCTION:      SendApiFpProdTestGetFxHookStateReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_SET_FX_HOOK_STATE_REQ
****************************************************************************/
void SendApiFpProdTestGetFxHookStateReq(  RosTaskIdType Dst,
                                       rsuint8 LineID,
                                       rsuint8 HookState);

/****************************************************************************
* FUNCTION:      SendApiFpProdTestGetFxHookStateCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_GET_FX_STATUS_CFM
****************************************************************************/
void SendApiFpProdTestGetFxHookStateCfm(  RosTaskIdType Dst,
                                          RsStatusType Status );

/****************************************************************************
* FUNCTION:      SendApiFpProdTestSetFxLBReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_SET_FX_LB_REQ
****************************************************************************/
void SendApiFpProdTestSetFxLBReq(  RosTaskIdType Dst,
                                       rsuint8 LineID,
                                       rsuint8 LBMode,
                                       rsuint8 LBStatus);

/****************************************************************************
* FUNCTION:      SendApiFpProdTestSetFxLBCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_SET_FX_LB_CFM
****************************************************************************/
void SendApiFpProdTestSetFxLBCfm(  RosTaskIdType Dst,
                                   RsStatusType Status );

/****************************************************************************
* FUNCTION:      SendApiFpProdTestSetFxFSKReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_SET_FX_FSK_REQ
****************************************************************************/
void SendApiFpProdTestSetFxFSKReq(  RosTaskIdType Dst,
                                    rsuint8 LineID );

/****************************************************************************
* FUNCTION:      SendApiFpProdTestSetEnvVarIntCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_SET_FX_FSK_CFM
****************************************************************************/
void SendApiFpProdTestSetFxFSKCfm(  RosTaskIdType Dst,
                                    RsStatusType Status );

/****************************************************************************
* FUNCTION:      SendApiFpProdTestGetFxFSKReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_GET_FX_FSK_REQ
****************************************************************************/
void SendApiFpProdTestGetFxFSKReq(  RosTaskIdType Dst,
                                    rsuint8 LineID );

/****************************************************************************
* FUNCTION:      SendApiFpProdTestGetEnvVarIntCfm
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_PRODTEST_GET_FX_FSK_CFM
****************************************************************************/
void SendApiFpProdTestGetFxFSKCfm(  RosTaskIdType Dst,
                                        rschar* CidPtr);

//#ifdef __cplusplus
//}
//#endif
#endif //PROJECT_FP_PROD_TEST_EXTENSION*/
#endif /*APIFPPRODTESTMPS_H */
