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

#ifndef ROSPRIMITIV_H
#define ROSPRIMITIV_H

/****************************************************************************
*                               Include files
****************************************************************************/

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

typedef enum
{
  DUMMY_DATA=0x0000,
  KEY_MESSAGE=0x0001,
  KEY_RELEASE=0x0002,
  KEY_PRESS=0x0003,
  TIMEOUT=0x0004,
  HELLO_STATE_ind=0x0005,
  GOODBYE_STATE_ind=0x0006, 
  INITTASK=0x0007,
  TERMINATETASK=0x0008,
  TEST_PRIMITIVE=0x0009,
  ROS_PM_WAKEUP_ind=0x000A,
  ROS_PM_SUSPEND_ind=0x000B,

  /**************************************************************************************
  /                               Phoenix FP API Begin
  / NB: DO NOT CHANGE ORDER OR NUMBERING OF PRIMITIVES - ONLY ADD TO END OF EACH GROUP
  ***************************************************************************************/
  API_FP_RESET_REQ=0x4000,                                           //ApiFpGeneral
  API_FP_RESET_IND=0x4001,                                           //ApiFpGeneral
  API_FP_GET_FW_VERSION_REQ=0x4002,                                  //ApiFpGeneral
  API_FP_GET_FW_VERSION_CFM=0x4003,                                  //ApiFpGeneral

  API_FP_MM_GET_ID_REQ=0x4004,                                       //ApiFpMm
  API_FP_MM_GET_ID_CFM=0x4005,                                       //ApiFpMm
  API_FP_MM_GET_MODEL_REQ=0x4006,                                    //ApiFpMm
  API_FP_MM_GET_MODEL_CFM=0x4007,                                    //ApiFpMm
  API_FP_MM_SET_ACCESS_CODE_REQ=0x4008,                              //ApiFpMm
  API_FP_MM_SET_ACCESS_CODE_CFM=0x4009,                              //ApiFpMm
  API_FP_MM_GET_ACCESS_CODE_REQ=0x400A,                              //ApiFpMm
  API_FP_MM_GET_ACCESS_CODE_CFM=0x400B,                              //ApiFpMm
 
  API_FP_SET_CRADLE_STATUS_REQ=0x407F,                               //ApiFpGeneral
  API_FP_CRADLE_DETECT_REQ=0x4080,                                   //ApiFpGeneral
  API_FP_CRADLE_DETECT_IND=0x4081,                                   //ApiFpGeneral
  API_FP_SET_TIME_REQ=0x4082,                                        //ApiFpGeneral
  API_FP_SET_TIME_CFM=0x4083,                                        //ApiFpGeneral
  API_FP_GET_TIME_REQ=0x4084,                                        //ApiFpGeneral
  API_FP_GET_TIME_CFM=0x4085,                                        //ApiFpGeneral
  API_FP_SET_TIME_IND=0x4086,                                        //ApiFpGeneral
  API_FP_SYNC_TIME_REQ=0x4087,                                       //ApiFpGeneral
  API_FP_SET_FEATURES_REQ=0x40A0,                                    //ApiFpGeneral
  API_FP_SET_FEATURES_CFM=0x40A1,                                    //ApiFpGeneral
  API_FP_GET_FEATURES_REQ=0x40A2,                                    //ApiFpGeneral
  API_FP_GET_FEATURES_CFM=0x40A3,                                    //ApiFpGeneral
  
  API_FP_MM_GET_REGISTRATION_COUNT_REQ=0x4100,                       //ApiFpMm
  API_FP_MM_GET_REGISTRATION_COUNT_CFM=0x4101,                       //ApiFpMm
  API_FP_MM_DELETE_REGISTRATION_REQ=0x4102,                          //ApiFpMm
  API_FP_MM_DELETE_REGISTRATION_CFM=0x4103,                          //ApiFpMm
  API_FP_MM_REGISTRATION_FAILED_IND=0x4104,                          //ApiFpMm
  API_FP_MM_SET_REGISTRATION_MODE_REQ=0x4105,                        //ApiFpMm
  API_FP_MM_SET_REGISTRATION_MODE_CFM=0x4106,                        //ApiFpMm
  API_FP_MM_REGISTRATION_COMPLETE_IND=0x4107,                        //ApiFpMm
  API_FP_MM_HANDSET_PRESENT_IND=0x4108,                              //ApiFpMm
  API_FP_MM_GET_HANDSET_IPUI_REQ=0x4109,                             //ApiFpMm
  API_FP_MM_GET_HANDSET_IPUI_CFM=0x410A,                             //ApiFpMm
  API_FP_MM_STOP_PROTOCOL_REQ=0x410B,                                //ApiFpMm
  API_FP_MM_EXT_HIGHER_LAYER_CAP2_REQ=0x410C,                        //ApiFpMm
  API_FP_MM_START_PROTOCOL_REQ=0x410D,                               //ApiFpMm
  API_FP_MM_HANDSET_DETACH_IND=0x410E,                               //ApiFpMm
  API_FP_MM_HANDSET_DEREGISTERED_IND=0x410F,                         //ApiFpMm
  API_FP_MM_GET_NAME_REQ=0x4110,                                     //ApiFpMm
  API_FP_MM_GET_NAME_CFM=0x4111,                                     //ApiFpMm
  API_FP_MM_SET_NAME_REQ=0x4112,                                     //ApiFpMm
  API_FP_MM_SET_NAME_CFM=0x4113,                                     //ApiFpMm
  API_FP_MM_REGISTRATION_MODE_DISABLED_IND=0x4114,                   //ApiFpMm
  API_FP_MM_SET_FEATURES_REQ=0x4160,                                 //ApiFpMm
  API_FP_MM_SET_FEATURES_CFM=0x4161,                                 //ApiFpMm
  API_FP_MM_GET_FEATURES_REQ=0x4162,                                 //ApiFpMm
  API_FP_MM_GET_FEATURES_CFM=0x4163,                                 //ApiFpMm
  API_FP_MM_GET_FP_CAPABILITIES_REQ=0x4170,                          //ApiFpMm
  API_FP_MM_GET_FP_CAPABILITIES_CFM=0x4171,                          //ApiFpMm
  API_FP_MM_UNITDATA_REQ=0x4180,                                     //ApiFpMm
  API_FP_MM_ALERT_BROADCAST_REQ=0x4182,                              //ApiFpMm
  API_FP_MM_START_PROTOCOL_PCM_SYNC_REQ=0x4183,                      //ApiFpMm

  API_FP_ULE_DATA_IND=0x4185,                                        //ApiFpUle
  API_FP_ULE_DATA_REQ=0x4186,                                        //ApiFpUle
  API_FP_ULE_DTR_IND=0x4187,                                         //ApiFpUle
  API_FP_ULE_INIT_REQ=0x4188,                                        //ApiFpUle
  API_FP_ULE_INIT_CFM=0x4189,                                        //ApiFpUle
  API_FP_ULE_TESTCMD_REQ=0x418A,                                     //ApiFpUle
  API_FP_ULE_DATA_CFM=0x418B,                                        //ApiFpUle
  API_FP_ULE_GET_REGISTRATION_COUNT_REQ=0x418C,                      //ApiFpUle
  API_FP_ULE_GET_REGISTRATION_COUNT_CFM=0x418D,                      //ApiFpUle
  API_FP_ULE_GET_DEVICE_IPUI_REQ=0x418E,                             //ApiFpUle
  API_FP_ULE_GET_DEVICE_IPUI_CFM=0x418F,                             //ApiFpUle
  API_FP_ULE_ABORT_DATA_REQ=0x4190,                                  //ApiFpUle
  API_FP_ULE_ABORT_DATA_CFM=0x4191,                                  //ApiFpUle
  API_FP_ULE_DELETE_REGISTRATION_REQ=0x4192,                         //ApiFpUle
  API_FP_ULE_DELETE_REGISTRATION_CFM=0x4193,                         //ApiFpUle
  API_FP_ULE_SET_FEATURES_REQ=0x41A0,                                //ApiFpUle
  API_FP_ULE_SET_FEATURES_CFM=0x41A1,                                //ApiFpUle
  API_FP_ULE_PVC_CONFIG_RES=0x41A2,                                  //ApiFpUle
  API_FP_ULE_PVC_CONFIG_CFM=0x41A3,                                  //ApiFpUle
  API_FP_ULE_PVC_CONFIG_REJ=0x41A4,                                  //ApiFpUle
  API_FP_ULE_PVC_CONFIG_IND=0x41A5,                                  //ApiFpUle
  API_FP_ULE_PVC_PENDING_IND=0x41A6,                                 //ApiFpUle
  API_FP_ULE_PVC_PENDING_RES=0x41A7,                                 //ApiFpUle
  API_FP_ULE_PVC_IWU_DATA_REQ=0x41A8,                                //ApiFpUle
  API_FP_ULE_PVC_IWU_DATA_IND=0x41A9,                                //ApiFpUle
  API_FP_ULE_GET_FEATURES_REQ=0x41AA,                                //ApiFpUle
  API_FP_ULE_GET_FEATURES_CFM=0x41AB,                                //ApiFpUle

  //These may be changed due to new audio interface
  API_FP_INIT_PCM_REQ=0x4200,                                        //ApiFpAudio
  API_FP_INIT_PCM_CFM=0x4201,                                        //ApiFpAudio
  API_FP_SET_PCM_LOOPBACK_REQ=0x4204,                                //ApiFpAudio
  API_FP_SET_PCM_LOOPBACK_CFM=0x4205,                                //ApiFpAudio
  API_FP_INIT_USB_REQ=0x4206,                                        //ApiFpAudio
  API_FP_INIT_USB_CFM=0x4207,                                        //ApiFpAudio
  API_FP_SET_AUDIO_FORMAT_REQ=0x4210,                                //ApiFpAudio
  API_FP_SET_AUDIO_FORMAT_CFM=0x4211,                                //ApiFpAudio
  API_FP_AUDIO_MUTE_REQ=0x4212,                                      //ApiFpAudio
  API_FP_AUDIO_MUTE_CFM=0x4213,                                      //ApiFpAudio
  API_FP_AUDIO_UNMUTE_REQ=0x4214,                                    //ApiFpAudio
  API_FP_AUDIO_UNMUTE_CFM=0x4215,                                    //ApiFpAudio
  API_FP_AUDIO_INTERNAL_CODEC_SETUP_REQ=0x4216,                      //ApiFpAudio
  API_FP_AUDIO_INTERNAL_CODEC_SETUP_CFM=0x4217,                      //ApiFpAudio
  API_FP_AUDIO_SET_HW_SRC_REQ=0x4218,                                //ApiFpAudio
  API_FP_AUDIO_SET_HW_SRC_CFM=0x4219,                                //ApiFpAudio
  API_FP_AUDIO_SET_CODEC_GAIN_REQ=0x421A,                            //ApiFpAudio
  API_FP_AUDIO_SET_CODEC_GAIN_CFM=0x421B,                            //ApiFpAudio
  API_FP_AUDIO_ENABLE_EC_REQ=0x421C,                                 //ApiFpAudio
  API_FP_AUDIO_ENABLE_EC_CFM=0x421D,                                 //ApiFpAudio
  API_FP_AUDIO_SET_FEATURES_REQ=0x4220,                              //ApiFpAudio
  API_FP_AUDIO_SET_FEATURES_CFM=0x4221,                              //ApiFpAudio
  API_FP_AUDIO_GET_FEATURES_REQ=0x4223,                              //ApiFpAudio
  API_FP_AUDIO_GET_FEATURES_CFM=0x4224,                              //ApiFpAudio
  
  API_FP_CC_SETUP_IND=0x4400,                                        //ApiFpCc
  API_FP_CC_SETUP_RES=0x4401,                                        //ApiFpCc
  API_FP_CC_SETUP_REQ=0x4402,                                        //ApiFpCc
  API_FP_CC_SETUP_CFM=0x4403,                                        //ApiFpCc
  API_FP_CC_ALERT_IND=0x4404,                                        //ApiFpCc
  API_FP_CC_ALERT_REQ=0x4405,                                        //ApiFpCc
  API_FP_CC_ALERT_CFM=0x4406,                                        //ApiFpCc
  API_FP_CC_CONNECT_IND=0x4407,                                      //ApiFpCc
  API_FP_CC_CONNECT_RES=0x4408,                                      //ApiFpCc
  API_FP_CC_CONNECT_REQ=0x4409,                                      //ApiFpCc
  API_FP_CC_CONNECT_CFM=0x440A,                                      //ApiFpCc
  API_FP_CC_RELEASE_IND=0x440F,                                      //ApiFpCc
  API_FP_CC_RELEASE_RES=0x4410,                                      //ApiFpCc
  API_FP_CC_RELEASE_REQ=0x4411,                                      //ApiFpCc
  API_FP_CC_RELEASE_CFM=0x4412,                                      //ApiFpCc
  API_FP_CC_REJECT_IND=0x4413,                                       //ApiFpCc
  API_FP_CC_CALL_PROC_REQ=0x4415,                                    //ApiFpCc
  API_FP_CC_CALL_PROC_CFM=0x4416,                                    //ApiFpCc
  API_FP_CC_MODIFY_CODEC_REQ=0x441D,                                 //ApiFpCc
  API_FP_CC_MODIFY_CODEC_CFM=0x441E,                                 //ApiFpCc
  API_FP_CC_MODIFY_CODEC_IND=0x441F,                                 //ApiFpCc
  API_FP_CC_MODIFY_CODEC_RES=0x4420,                                 //ApiFpCc
  API_FP_CC_IWU_INFO_CODEC_IND=0x4421,                               //ApiFpCc
  API_FP_CC_SETUP_ACK_REQ=0x4423,                                    //ApiFpCc
  API_FP_CC_SETUP_ACK_CFM=0x4424,                                    //ApiFpCc
  API_FP_CC_SYSTEM_CALL_ID_REQ=0x4427,                               //ApiFpCc
  API_FP_CC_SYSTEM_CALL_ID_CFM=0x4428,                               //ApiFpCc
  API_FP_CC_RECONNECT_AUDIO_REQ=0x442C,                              //ApiFpCc
  API_FP_CC_INFO_IND=0x442D,                                         //ApiFpCc
  API_FP_CC_INFO_REQ=0x442E,                                         //ApiFpCc
  API_FP_CC_DISCONNECT_AUDIO_REQ=0x442F,                             //ApiFpCc
  API_FP_CC_SELECTED_ADPCM_IND=0x4430,                               //ApiFpCc
  API_FP_CC_SET_FEATURES_REQ=0x4450,                                 //ApiFpCc
  API_FP_CC_SET_FEATURES_CFM=0x4451,                                 //ApiFpCc
  API_FP_CC_GET_FEATURES_REQ=0x4452,                                 //ApiFpCc
  API_FP_CC_GET_FEATURES_CFM=0x4453,                                 //ApiFpCc

  API_TAM_PLAY_ICM_REQ=0x4500,                                       //ApiTam
  API_TAM_PLAY_ICM_CFM=0x4501,                                       //ApiTam
  API_TAM_ICM_SEARCH_REQ=0x4502,                                     //ApiTam
  API_TAM_ICM_SEARCH_CFM=0x4503,                                     //ApiTam
  API_TAM_ICM_STATUS_REQ=0x4504,                                     //ApiTam
  API_TAM_ICM_STATUS_CFM=0x4505,                                     //ApiTam
  API_TAM_DELETE_ICM_REQ=0x4506,                                     //ApiTam
  API_TAM_DELETE_ICM_CFM=0x4507,                                     //ApiTam
  API_TAM_STOP_REQ=0x4508,                                           //ApiTam
  API_TAM_STOP_CFM=0x4509,                                           //ApiTam
  API_TAM_MARK_CURRENT_ICM_REQ=0x450A,                               //ApiTam
  API_TAM_MARK_CURRENT_ICM_CFM=0x450B,                               //ApiTam
  API_TAM_STATUS_IND=0x450C,                                         //ApiTam
  API_TAM_RECORD_MEMO_REQ=0x450D,                                    //ApiTam
  API_TAM_RECORD_MEMO_CFM=0x450E,                                    //ApiTam
  API_TAM_RECORD_VOICETAG_REQ=0x450F,                                //ApiTam
  API_TAM_RECORD_VOICETAG_CFM=0x4510,                                //ApiTam
  API_TAM_PLAY_VOICEPROMPT_REQ=0x4511,                               //ApiTam
  API_TAM_PLAY_VOICEPROMPT_CFM=0x4512,                               //ApiTam
  API_TAM_PLAY_VOICETAG_REQ=0x4513,                                  //ApiTam
  API_TAM_PLAY_VOICETAG_CFM=0x4514,                                  //ApiTam
  API_TAM_DELETE_VOICETAG_REQ=0x4515,                                //ApiTam
  API_TAM_DELETE_VOICETAG_CFM=0x4516,                                //ApiTam
  API_TAM_SET_SETTINGS_REQ=0x4517,                                   //ApiTam
  API_TAM_SET_SETTINGS_CFM=0x4518,                                   //ApiTam
  API_TAM_GET_SETTINGS_REQ=0x4519,                                   //ApiTam
  API_TAM_GET_SETTINGS_CFM=0x451A,                                   //ApiTam
  API_TAM_SET_SYSTEM_SETTINGS_REQ=0x451B,                            //ApiTam
  API_TAM_SET_SYSTEM_SETTINGS_CFM=0x451C,                            //ApiTam
  API_TAM_GET_SYSTEM_SETTINGS_REQ=0x451D,                            //ApiTam
  API_TAM_GET_SYSTEM_SETTINGS_CFM=0x451E,                            //ApiTam
  API_TAM_READ_DATA_REQ=0x451F,                                      //ApiTam
  API_TAM_READ_DATA_CFM=0x4520,                                      //ApiTam
  API_TAM_WRITE_DATA_REQ=0x4521,                                     //ApiTam
  API_TAM_WRITE_DATA_CFM=0x4522,                                     //ApiTam
  API_TAM_DELETE_ALL_ICMS_REQ=0x4523,                                //ApiTam
  API_TAM_DELETE_ALL_ICMS_CFM=0x4524,                                //ApiTam
  API_TAM_SETUP_REQ=0x4525,                                          //ApiTam
  API_TAM_RELEASE_REQ=0x4526,                                        //ApiTam
  API_TAM_RELEASE_CFM=0x4527,                                        //ApiTam
  API_TAM_CONNECT_IND=0x4528,                                        //ApiTam
  API_TAM_REJECT_IND=0x4529,                                         //ApiTam

  API_FP_MAC_NO_EMISSION_MODE_ENABLE_REQ=0x4600,                     //ApiFpNoEmission
  API_FP_MAC_NO_EMISSION_MODE_DISABLE_REQ=0x4601,                    //ApiFpNoEmission
  API_FP_MAC_NO_EMISSION_MODE_STOP_REQ=0x4602,                       //ApiFpNoEmission
  API_FP_MAC_NO_EMISSION_MODE_PENDING_IND=0x4603,                    //ApiFpNoEmission
  API_FP_MAC_NO_EMISSION_MODE_ACTIVE_IND=0x4604,                     //ApiFpNoEmission
  API_FP_MAC_NO_EMISSION_MODE_STOP_IND=0x4605,                       //ApiFpNoEmission
  API_FP_MAC_NO_EMISSION_MODE_SET_PREF_CARRIER_REQ=0x4606,           //ApiFpNoEmission

  API_SCL_GET_MODE_REQ=0x4740,                                       //ApiScl
  API_SCL_GET_MODE_CFM=0x4741,                                       //ApiScl
  API_SCL_SET_MODE_REQ=0x4742,                                       //ApiScl
  API_SCL_SET_MODE_CFM=0x4743,                                       //ApiScl
  API_SCL_GET_URL_REQ=0x4744,                                        //ApiScl
  API_SCL_GET_URL_CFM=0x4745,                                        //ApiScl
  API_SCL_SET_URL_REQ=0x4746,                                        //ApiScl
  API_SCL_SET_URL_CFM=0x4747,                                        //ApiScl
  API_SCL_OPERATION_REQ=0x4748,                                      //ApiScl
  API_SCL_OPERATION_CFM=0x4749,                                      //ApiScl
  API_SCL_STATUS_IND=0x474A,                                         //ApiScl
  API_SCL_VERSIONS_IND=0x474B,                                       //ApiScl
  API_SCL_GET_GUID_REQ=0x474C,                                       //ApiScl
  API_SCL_GET_GUID_CFM=0x474D,                                       //ApiScl
  API_SCL_SET_GUID_REQ=0x474E,                                       //ApiScl
  API_SCL_SET_GUID_CFM=0x474F,                                       //ApiScl

  API_FP_LLME_GET_RSSI_REQ=0x47B0,                                   //ApiFpLlme
  API_FP_LLME_GET_RSSI_CFM=0x47B1,                                   //ApiFpLlme
  API_FP_LLME_GET_PERFORMANCE_TABLE_REQ=0x47B2,                      //ApiFpLlme
  API_FP_LLME_GET_PERFORMANCE_TABLE_CFM=0x47B3,                      //ApiFpLlme
  API_FP_LLME_SET_FEATURES_REQ=0x47B4,                               //ApiFpLlme
  API_FP_LLME_SET_FEATURES_CFM=0x47B5,                               //ApiFpLlme
  API_FP_LLME_GET_FEATURES_REQ=0x47B6,                               //ApiFpLlme
  API_FP_LLME_GET_FEATURES_CFM=0x47B7,                               //ApiFpLlme

  API_LDS_OPEN_REQ=0x4800,                                           //ApiLds
  API_LDS_OPEN_CFM=0x4801,                                           //ApiLds
  API_LDS_OPEN_IND=0x4802,                                           //ApiLds
  API_LDS_OPEN_RES=0x4803,                                           //ApiLds
  API_LDS_CLOSE_REQ=0x4804,                                          //ApiLds
  API_LDS_CLOSE_CFM=0x4805,                                          //ApiLds
  API_LDS_CLOSE_IND=0x4806,                                          //ApiLds
  API_LDS_REJECT_REQ=0x4807,                                         //ApiLds
  API_LDS_REJECT_IND=0x4808,                                         //ApiLds
  API_LDS_TX_READY_IND=0x4820,                                       //ApiLds
  API_LDS_TX_DATA_REQ=0x4821,                                        //ApiLds
  API_LDS_TX_DATA_CFM=0x4822,                                        //ApiLds
  API_LDS_RX_DATA_IND=0x4823,                                        //ApiLds
  API_LDS_SET_FEATURES_REQ=0x4830,                                   //ApiLds
  API_LDS_SET_FEATURES_CFM=0x4831,                                   //ApiLds
  API_LDS_GET_FEATURES_REQ=0x4832,                                   //ApiLds
  API_LDS_GET_FEATURES_CFM=0x4833,                                   //ApiLds

  API_SUOTA_SW_VERSION_INFO_REQ=0x4880,                              //ApiSuota
  API_SUOTA_SW_VERSION_INFO_IND=0x4881,                              //ApiSuota
  API_SUOTA_NEW_SW_AVAILABLE_REQ=0x4882,                             //ApiSuota
  API_SUOTA_NEW_SW_AVAILABLE_IND=0x4883,                             //ApiSuota
  API_SUOTA_NEGATIVE_ACK_REQ=0x4884,                                 //ApiSuota
  API_SUOTA_NEGATIVE_ACK_IND=0x4885,                                 //ApiSuota
  API_SUOTA_SET_FEATURES_REQ=0x4890,                                 //ApiSuota
  API_SUOTA_SET_FEATURES_CFM=0x4891,                                 //ApiSuota
  API_SUOTA_GET_FEATURES_REQ=0x4892,                                 //ApiSuota
  API_SUOTA_GET_FEATURES_CFM=0x4893,                                 //ApiSuota

  API_PP2PP_ENTER_REQ=0x4920,                                        //ApiPp2Pp
  API_PP2PP_ENTER_CFM=0x4921,                                        //ApiPp2Pp
  API_PP2PP_EXIT_REQ=0x4922,                                         //ApiPp2Pp
  API_PP2PP_EXIT_CFM=0x4923,                                         //ApiPp2Pp
  API_PP2PP_ENTER_FP_MODE_REQ=0x4924,                                //ApiPp2Pp
  API_PP2PP_ENTER_FP_MODE_CFM=0x4925,                                //ApiPp2Pp
  API_PP2PP_SETUP_REQ=0x4926,                                        //ApiPp2Pp
  API_PP2PP_CONNECT_IND=0x4927,                                      //ApiPp2Pp
  API_PP2PP_SETUP_IND=0x4928,                                        //ApiPp2Pp
  API_PP2PP_CONNECT_REQ=0x4929,                                      //ApiPp2Pp
  API_PP2PP_CONNECT_CFM=0x492A,                                      //ApiPp2Pp
  API_PP2PP_RELEASE_REQ=0x492B,                                      //ApiPp2Pp
  API_PP2PP_RELEASE_CFM=0x492C,                                      //ApiPp2Pp
  API_PP2PP_RELEASE_IND=0x492D,                                      //ApiPp2Pp

  API_FWU_ENABLE_REQ=0x4F00,                                         //ApiFwu
  API_FWU_ENABLE_CFM=0x4F01,                                         //ApiFwu
  API_FWU_DEVICE_NOTIFY_IND=0x4F02,                                  //ApiFwu
  API_FWU_UPDATE_REQ=0x4F03,                                         //ApiFwu
  API_FWU_UPDATE_CFM=0x4F04,                                         //ApiFwu
  API_FWU_UPDATE_IND=0x4F05,                                         //ApiFwu
  API_FWU_UPDATE_RES=0x4F06,                                         //ApiFwu
  API_FWU_GET_BLOCK_IND=0x4F07,                                      //ApiFwu
  API_FWU_GET_BLOCK_RES=0x4F08,                                      //ApiFwu
  API_FWU_GET_CRC_IND=0x4F09,                                        //ApiFwu
  API_FWU_GET_CRC_RES=0x4F0A,                                        //ApiFwu
  API_FWU_COMPLETE_IND=0x4F0B,                                       //ApiFwu
  API_FWU_STATUS_IND=0x4F0C,                                         //ApiFwu
  API_FWU_MULTI_CRC_IND=0x4F0D,                                      //ApiFwu
  API_FWU_MULTI_CRC_RES=0x4F0E,                                      //ApiFwu
  API_FWU_SET_FEATURES_REQ=0x4F10,                                   //ApiFwu
  API_FWU_SET_FEATURES_CFM=0x4F11,                                   //ApiFwu
  API_FWU_GET_FEATURES_REQ=0x4F12,                                   //ApiFwu
  API_FWU_GET_FEATURES_CFM=0x4F13,                                   //ApiFwu
  
  API_PROD_TEST_REQ=0x4FFE,                                          //ApiProdTest
  API_PROD_TEST_CFM=0x4FFF,                                          //ApiProdTest

  /**************************************************************************************
  /                               Phoenix PP API Begin
  / NB: DO NOT CHANGE ORDER OR NUMBERING OF PRIMITIVES - ONLY ADD TO END OF EACH GROUP
  ***************************************************************************************/
  API_CC_SETUP_REQ=0x5000,
  API_CC_SETUP_ACK_IND=0x5001,
  API_CC_CALL_PROC_IND=0x5002,
  API_CC_ALERT_IND=0x5003,
  API_CC_CONNECT_IND=0x5004,
  API_CC_CONNECT_RES=0x5005,
  API_CC_MULTIKEYPAD_REQ=0x5006,
  API_CC_MULTI_DISPLAY_IND=0x5007,
  API_CC_CALLED_NUMBER_REQ=0x5008,
  API_CC_CALLED_NUMBER_IND=0x5009,
  API_CC_SETUP_IND=0x500A,
  API_CC_ALERT_REQ=0x500B,
  API_CC_CONNECT_REQ=0x500C,
  API_CC_CONNECT_CFM=0x500D,
  API_CC_SIGNAL_IND=0x500E,
  API_CC_CLIP_IND=0x500F,
  API_CC_IWU_TO_IWU_IND=0x5010,
  API_CC_IWU_TO_IWU_REQ=0x5011,
  API_CC_PROPRIETARY_IND=0x5012,
  API_CC_PROPRIETARY_REQ=0x5013,
  API_CC_RELEASE_REQ=0x5014,
  API_CC_RELEASE_CFM=0x5015,
  API_CC_RELEASE_IND=0x5016,
  API_CC_RELEASE_RES=0x5017,
  API_CC_REJECT_IND=0x5018,
  API_CC_REJECT_REQ=0x5019,
  API_CC_MODIFY_CODEC_REQ=0x501A,
  API_CC_MODIFY_CODEC_CFM=0x501B,
  API_CC_MODIFY_CODEC_IND=0x501C,
  API_CC_MODIFY_CODEC_RES=0x501D,
  API_CC_IWU_INFO_CODEC_IND=0x501E, //previously API_CC_CODEC_INFO_IND
  API_CC_CALL_WAITING_IND=0x501F,
  API_CC_CALL_WAITING_RES=0x5020,
  API_CC_SECOND_CALL_INTERCOM_REQ=0x5021,
  API_CC_SECOND_CALL_EXTERNAL_REQ=0x5022,
  API_CC_MULTIPARTY_REQ=0x5023,
  API_CC_TRANSFER_CALL_REQ=0x5024,
  API_CC_TOGGLE_CALL_REQ=0x5025,
  API_CC_END_CALL_REQ=0x5026,
//  API_CC_END_ACTIVE_CALL_REQ=0x5026,
//  API_CC_END_HELD_CALL_REQ=0x5027,
  API_CC_CALL_INFO_REQ=0x5028,
  API_CC_CALL_INFO_IND=0x5029,
  API_CC_CONEI_CHANGE_IND=0x502A,
  API_CC_HOLD_CALL_REQ=0x502B,
  API_CC_RETRIEVE_CALL_REQ=0x502C,
  API_CC_EXT_CALL_DEFLECTION_REQ=0x502D,
  API_CC_INT_CALL_DEFLECTION_REQ=0x502E,
  API_CC_PROPRIETARY_CFM=0x5030,
  API_CC_INFO_IND=0x5031,
  API_CC_INFO_REQ=0x5032,
  API_CC_IWU_INFO_IND=0x5033,
  API_CC_IWU_INFO_REQ=0x5034,
  API_CC_CLMS_DATA_IND=0x5035,
  API_CC_GET_CONEI_REQ=0x5036,
  API_CC_GET_CONEI_CFM=0x5037,
  API_CC_CALL_SCREENING_ACCEPT_REQ=0x5038,
  API_CC_CALL_SCREENING_INTERCEPT_REQ=0x5039, 

  API_PP_MM_GET_ID_REQ=0x5100,                                       //ApiPpMm
  API_PP_MM_GET_ID_CFM=0x5101,                                       //ApiPpMm
  API_PP_MM_GET_MODEL_REQ=0x5102,                                    //ApiPpMm
  API_PP_MM_GET_MODEL_CFM=0x5103,                                    //ApiPpMm
  API_PP_MM_READ_RSSI_REQ=0x5104,                                    //ApiPpMm
  API_PP_MM_READ_RSSI_CFM=0x5105,                                    //ApiPpMm
  API_PP_MM_LOCK_REQ=0x5106,                                         //ApiPpMm
  API_PP_MM_LOCKED_REQ=0x5107,                                       //ApiPpMm
  API_PP_MM_LOCKED_IND=0x5108,                                       //ApiPpMm
  API_PP_MM_UNLOCKED_IND=0x5109,                                     //ApiPpMm
  API_PP_MM_STOP_PROTOCOL_REQ=0x510A,                                //ApiPpMm
  API_PP_MM_REGISTRATION_AUTO_REQ=0x510B,                            //ApiPpMm
  API_PP_MM_REGISTRATION_SEARCH_REQ=0x510C,                          //ApiPpMm
  API_PP_MM_REGISTRATION_SEARCH_IND=0x510D,                          //ApiPpMm
  API_PP_MM_REGISTRATION_SELECTED_REQ=0x510E,                        //ApiPpMm
  API_PP_MM_REGISTRATION_STOP_REQ=0x510F,                            //ApiPpMm
  API_PP_MM_REGISTRATION_COMPLETE_IND=0x5110,                        //ApiPpMm
  API_PP_MM_REGISTRATION_FAILED_IND=0x5111,                          //ApiPpMm
  API_PP_MM_REGISTRATION_SELECTED_WITH_PLI_REQ=0x5112,               //ApiPpMm
  API_PP_MM_DELETE_LOCAL_REGISTRATION_REQ=0x5114,                    //ApiPpMm
  API_PP_MM_DELETE_LOCAL_REGISTRATION_CFM=0x5115,                    //ApiPpMm
  API_PP_MM_UPI_AUTHENTICATE_IND=0x5117,                             //ApiPpMm
  API_PP_MM_UPI_AUTHENTICATE_RES=0x5118,                             //ApiPpMm
  API_PP_MM_UNITDATA_IND=0x5119,                                     //ApiPpMm
  API_PP_MM_ALERT_BROADCAST_IND=0x511A,                              //ApiPpMm
  API_PP_MM_ACC_RIGHTS_TERM_IND=0x511B,                              //ApiPpMm
  API_PP_MM_FP_NAME_IND=0x511D,                                      //ApiPpMm
  API_PP_MM_ENCRYPTION_NOT_STARTED_IND=0x511E,                       //ApiPpMm
  API_PP_MM_GET_EXT_HIGHER_LAYER_CAP2_REQ=0x511F,                    //ApiPpMm
  API_PP_MM_GET_EXT_HIGHER_LAYER_CAP2_CFM=0x5120,                    //ApiPpMm
  API_PP_MM_EASY_PAIRING_SEARCH_REQ=0x5121,                          //ApiPpMm
  API_PP_MM_EASY_PAIRING_SEARCH_CFM=0x5122,                          //ApiPpMm
  API_PP_MM_GET_SUBSCRIPTION_RFPI_REQ=0x5123,                        //ApiPpMm
  API_PP_MM_GET_SUBSCRIPTION_RFPI_CFM=0x5124,                        //ApiPpMm

  API_PP_GET_FW_VERSION_REQ=0x5200,
  API_PP_GET_FW_VERSION_CFM=0x5201,
  API_PP_RESET_REQ=0x5202,
  API_PP_RESET_IND=0x5203,
  API_PP_POWER_OFF_REQ=0x5204,
  API_PP_CRADLE_DETECT_REQ=0x5205,
  API_PP_CRADLE_DETECT_IND=0x5206,
  API_PP_SET_TIME_REQ=0x5207,
  API_PP_SET_TIME_CFM=0x5208,
  API_PP_GET_TIME_REQ=0x5209,
  API_PP_GET_TIME_CFM=0x520A,
  API_PP_SYNC_TIME_REQ=0x520B,

  API_PP_AUDIO_MUTE_REQ=0x5300,
  API_PP_AUDIO_UNMUTE_REQ=0x5301,
  API_PP_AUDIO_SET_MODE_REQ=0x5302,
  API_PP_AUDIO_SET_VOLUME_REQ=0x5303,
  API_PP_AUDIO_START_TONE_REQ=0x5306,
  API_PP_AUDIO_START_TONE_CFM=0x5314,
  API_PP_AUDIO_STOP_TONE_REQ=0x5307,
  API_PP_AUDIO_STOP_TONE_CFM=0x5315,
  API_PP_AUDIO_TONE_END_IND=0x5313,
  API_PP_AUDIO_START_MIDI_REQ=0x530B,
  API_PP_AUDIO_START_MIDI_CFM=0x5316,
  API_PP_AUDIO_STOP_MIDI_REQ=0x530C,
  API_PP_AUDIO_STOP_MIDI_CFM=0x5317,
  API_PP_AUDIO_MIDI_END_IND=0x530D,
  API_PP_AUDIO_SET_ACTIVE_SOUND_VOLUME_REQ=0x530E,
  API_PP_AUDIO_TEST_CMD_REQ=0x530F,
  API_PP_AUDIO_START_MEDIA_SEQ_REQ=0x5310,
  API_PP_AUDIO_START_MEDIA_SEQ_CFM=0x5318,
  API_PP_AUDIO_STOP_MEDIA_SEQ_REQ=0x5311,
  API_PP_AUDIO_STOP_MEDIA_SEQ_CFM=0x5319,
  API_PP_AUDIO_MEDIA_SEQ_END_IND=0x5312,
  API_PP_AUDIO_START_TEXT_TO_SPEECH_REQ=0x531a,
  API_PP_AUDIO_START_TEXT_TO_SPEECH_CFM=0x531b,
  API_PP_AUDIO_STOP_TEXT_TO_SPEECH_REQ=0x531c,
  API_PP_AUDIO_STOP_TEXT_TO_SPEECH_CFM=0x531d,
  API_PP_AUDIO_TEXT_TO_SPEECH_END_IND=0x531e,
  API_PP_AUDIO_START_DTMF_REQ=0x531f,
  API_PP_AUDIO_START_DTMF_CFM=0x5320,
  API_PP_AUDIO_STOP_DTMF_REQ=0x5321,
  API_PP_AUDIO_STOP_DTMF_CFM=0x5322,
  API_PP_AUDIO_OPEN_REQ=0x5323,
  API_PP_AUDIO_CLOSE_REQ=0x5324,
  API_PP_AUDIO_START_VOICE_DETECTION_REQ=0x5325,                     //ApiPpAudio
  API_PP_AUDIO_STOP_VOICE_DETECTION_REQ=0x5326,                      //ApiPpAudio
  API_PP_AUDIO_INFO_VOICE_DETECTION_IND=0x5327,                      //ApiPpAudio
  API_PP_AUDIO_START_TONE_EXT_REQ=0x5328,                            //ApiPpAudio
  API_PP_AUDIO_START_MIDI_EXT_REQ=0x5329,                            //ApiPpAudio
  API_PP_AUDIO_INIT_PCM_REQ = 0x532A,
  API_PP_AUDIO_INIT_PCM_CFM = 0x532B,
  API_PP_BAT_CAPACITY_REQ=0x5400,                                    //ApiPpBattery
  API_PP_BAT_CAPACITY_IND=0x5401,                                    //ApiPpBattery
  API_PP_BAT_LOW_IND=0x5402,                                         //ApiPpBattery
  API_PP_BAT_EMPTY_IND=0x5403,                                       //ApiPpBattery
  API_PP_BAT_POWER_ON_REASON_REQ=0x5404,                             //ApiPpBattery
  API_PP_BAT_POWER_ON_REASON_IND=0x5405,                             //ApiPpBattery
  API_PP_BAT_CHARGE_REQ=0x5406,                                      //ApiPpBattery
  API_PP_BAT_CHARGE_IND=0x5407,                                      //ApiPpBattery
  API_PP_BAT_RESET_CHARGING_STATE_REQ=0x5408,                        //ApiPpBattery
  API_PP_BAT_RESET_CHARGING_STATE_CFM=0x5409,                        //ApiPpBattery
  API_PP_BAT_NON_CHARGEABLE_IND=0x5410,                              //ApiPpBattery

  // List Access Service (LAS)
    API_LAS_START_SESSION_REQ=0x5500,                                  //ApiLas
  API_LAS_START_SESSION_CFM=0x5501,                                  //ApiLas
  API_LAS_END_SESSION_REQ=0x5502,                                    //ApiLas
  API_LAS_END_SESSION_CFM=0x5503,                                    //ApiLas
  API_LAS_QUERY_SUPPORTED_ENTRY_FIELDS_REQ=0x5504,                   //ApiLas
  API_LAS_QUERY_SUPPORTED_ENTRY_FIELDS_CFM=0x5505,                   //ApiLas
  API_LAS_READ_ENTRIES_REQ=0x5506,                                   //ApiLas
  API_LAS_READ_ENTRIES_CFM=0x5507,                                   //ApiLas
  API_LAS_EDIT_ENTRY_REQ=0x5508,                                     //ApiLas
  API_LAS_EDIT_ENTRY_CFM=0x5509,                                     //ApiLas
  API_LAS_SAVE_ENTRY_REQ=0x550A,                                     //ApiLas
  API_LAS_SAVE_ENTRY_CFM=0x550B,                                     //ApiLas
  API_LAS_DELETE_ENTRY_REQ=0x550C,                                   //ApiLas
  API_LAS_DELETE_ENTRY_CFM=0x550D,                                   //ApiLas
  API_LAS_DELETE_LIST_REQ=0x550E,                                    //ApiLas
  API_LAS_DELETE_LIST_CFM=0x550F,                                    //ApiLas
  API_LAS_SEARCH_ENTRIES_REQ=0x5510,                                 //ApiLas
  API_LAS_SEARCH_ENTRIES_CFM=0x5511,                                 //ApiLas
  API_LAS_NEGATIVE_ACKNOWLEDGE_IND=0x5512,                           //ApiLas
  API_LAS_DATA_PACKET_IND=0x5513,                                    //ApiLas
  API_LAS_BASE_RESET_IND=0x5580,                                     //ApiLas
  API_LAS_STATUS_IND=0x5581,                                         //ApiLas
  API_LAS_GET_FIELD_PROTECTION_REQ=0x5582,                           //ApiLas
  API_LAS_GET_FIELD_PROTECTION_CFM=0x5583,                           //ApiLas
  API_LAS_SET_FIELD_PROTECTION_REQ=0x5584,                           //ApiLas
  API_LAS_SET_FIELD_PROTECTION_CFM=0x5585,                           //ApiLas
  API_LAS_GET_LOCKED_ENTRIES_LIST_REQ=0x5586,                        //ApiLas
  API_LAS_GET_LOCKED_ENTRIES_LIST_CFM=0x5587,                        //ApiLas
  API_LAS_SET_FIELD_DEFAULT_REQ=0x5588,                              //ApiLas
  API_LAS_SET_FIELD_DEFAULT_CFM=0x5589,                              //ApiLas
  API_LAS_DB_CLEAR_REQ=0x55C0,                                       //ApiLas
  API_LAS_DB_CLEAR_CFM=0x55C1,                                       //ApiLas
  
  API_LAS_DB_QUERY_SUPPORTED_LISTS_IND=0x5600,                       //ApiLasDb
  API_LAS_DB_QUERY_SUPPORTED_LISTS_RES=0x5601,                       //ApiLasDb
  API_LAS_DB_QUERY_SUPPORTED_ENTRY_FIELDS_IND=0x5602,                //ApiLasDb
  API_LAS_DB_QUERY_SUPPORTED_ENTRY_FIELDS_RES=0x5603,                //ApiLasDb
  API_LAS_DB_LIST_SORTING_REQUEST_IND=0x5604,                        //ApiLasDb
  API_LAS_DB_LIST_SORTING_REQUEST_RES=0x5605,                        //ApiLasDb
  API_LAS_DB_LIST_SORTING_RELEASE_IND=0x5606,                        //ApiLasDb
  API_LAS_DB_LIST_SORTING_RELEASE_RES=0x5607,                        //ApiLasDb
  API_LAS_DB_TOTAL_ENTRIES_IND=0x5608,                               //ApiLasDb
  API_LAS_DB_TOTAL_ENTRIES_RES=0x5609,                               //ApiLasDb
  API_LAS_DB_READ_IND=0x560A,                                        //ApiLasDb
  API_LAS_DB_READ_RES=0x560B,                                        //ApiLasDb
  API_LAS_DB_EDIT_IND=0x560C,                                        //ApiLasDb
  API_LAS_DB_EDIT_RES=0x560D,                                        //ApiLasDb
  API_LAS_DB_SAVE_IND=0x560E,                                        //ApiLasDb
  API_LAS_DB_SAVE_RES=0x560F,                                        //ApiLasDb
  API_LAS_DB_SEARCH_IND=0x5610,                                      //ApiLasDb
  API_LAS_DB_SEARCH_RES=0x5611,                                      //ApiLasDb
  API_LAS_DB_DELETE_IND=0x5612,                                      //ApiLasDb
  API_LAS_DB_DELETE_RES=0x5613,                                      //ApiLasDb
  API_LAS_DB_DELETE_LIST_IND=0x5614,                                 //ApiLasDb
  API_LAS_DB_DELETE_LIST_RES=0x5615,                                 //ApiLasDb
  API_LAS_DB_NEGATIVE_ACKNOWLEDGE_REQ=0x5616,                        //ApiLasDb
  API_LAS_DB_NEGATIVE_ACKNOWLEDGE_IND=0x5617,                        //ApiLasDb
  API_LAS_DB_DATA_PACKET_IND=0x5618,                                 //ApiLasDb
  API_LAS_DB_DATA_PACKET_RES=0x5619,                                 //ApiLasDb
  API_LAS_DB_DATA_PACKET_REQ=0x561A,                                 //ApiLasDb
  API_LAS_DB_DATA_PACKET_CFM=0x561B,                                 //ApiLasDb
  API_LAS_DB_RESET_IND=0x5630,                                       //ApiLasDb
  API_LAS_DB_RESET_RES=0x5631,                                       //ApiLasDb
  API_LAS_DB_GET_FIELD_PROTECTION_IND=0x5632,                        //ApiLasDb
  API_LAS_DB_GET_FIELD_PROTECTION_RES=0x5633,                        //ApiLasDb
  API_LAS_DB_SET_FIELD_PROTECTION_IND=0x5634,                        //ApiLasDb
  API_LAS_DB_SET_FIELD_PROTECTION_RES=0x5635,                        //ApiLasDb
  API_LAS_DB_SET_FIELD_DEFAULT_IND=0x5636,                           //ApiLasDb
  API_LAS_DB_SET_FIELD_DEFAULT_RES=0x5637,                           //ApiLasDb
  API_LAS_DB_SET_ACTIVE_DB_REQ=0x5650,                               //ApiLasDb
  API_LAS_DB_SET_ACTIVE_DB_CFM=0x5651,                               //ApiLasDb
  API_LAS_DB_GET_ACTIVE_DB_REQ=0x5652,                               //ApiLasDb
  API_LAS_DB_GET_ACTIVE_DB_CFM=0x5653,                               //ApiLasDb
  API_LAS_DB_CLEAR_DB_IND=0x56C0,                                    //ApiLasDb
  API_LAS_DB_CLEAR_DB_RES=0x56C1,                                    //ApiLasDb 

  // General Event Notification
  API_FP_GENEVENOT_EVENT_REQ=0x5700,                                 //ApiGenEveNot
  API_FP_GENEVENOT_EVENT_IND=0x5701,                                 //ApiGenEveNot
  API_FP_GENEVENOT_PP_EVENT_IND=0x5702,                              //ApiGenEveNot
  API_PP_GENEVENOT_EVENT_REQ=0x5703,                                 //ApiGenEveNot
  API_PP_GENEVENOT_EVENT_IND=0x5704,                                 //ApiGenEveNot
  API_FP_GENEVENOT_FEATURES_REQ=0x5708,                              //ApiGenEveNot
  API_FP_GENEVENOT_FEATURES_CFM=0x5709,                              //ApiGenEveNot
  API_IMAGE_INFO_REQ=0x5800,
  API_IMAGE_INFO_CFM=0x5801,
  API_IMAGE_ACTIVATE_REQ=0x5802,
  API_IMAGE_ACTIVATE_CFM=0x5803,
  API_IMAGE_ACTIVATE_TIMEOUT,

  // HAl.
  API_HAL_DEVICE_CONTROL_REQ=0x5900,
  API_HAL_DEVICE_CONTROL_CFM=0x5901,
  API_HAL_LED_REQ=0x5902,
  API_HAL_LED_CFM=0x5903,
  API_HAL_READ_REQ=0x5904,
  API_HAL_READ_CFM=0x5905,
  API_HAL_WRITE_REQ=0x5906,
  API_HAL_WRITE_CFM=0x5907,

  API_HAL_GPIO_FN_REGISTER_REQ=0x5910,
  API_HAL_GPIO_FN_REGISTER_CFM=0x5911,  
  API_HAL_SET_GPIO_PORT_PIN_MODE_REQ=0x5912,
  API_HAL_SET_GPIO_PORT_PIN_MODE_CFM=0x5913,
  API_HAL_SET_GPIO_PORT_REQ=0x5914,
  API_HAL_SET_GPIO_PORT_CFM=0x5915,
  API_HAL_RESET_GPIO_PORT_REQ=0x5916,
  API_HAL_RESET_GPIO_PORT_CFM=0x5917,
  API_HAL_GET_GPIO_PORT_REQ=0x5918,
  API_HAL_GET_GPIO_PORT_CFM=0x5919,

  API_HAL_LED_TIMEOUT,

//  PP ULE API Begin
  API_PP_ULE_INIT_REQ=0x5A00,
  API_PP_ULE_INIT_CFM=0x5A01,
  API_PP_ULE_SERVICE_REQ=0x5A02,
  API_PP_ULE_SERVICE_CFM=0x5A03,
  API_PP_ULE_SERVICE_ACCEPT_REQ=0x5A04,
  API_PP_ULE_SERVICE_ACCEPT_CFM=0x5A05,
  API_PP_ULE_SERVICE_LOST_IND=0x5A06,
  API_PP_ULE_SERVICE_LOCATE_REQ=0x5A07,
  API_PP_ULE_INFO_REQ=0x5A08,
  API_PP_ULE_INFO_CFM=0x5A09,
  API_PP_ULE_WAKEUP_TIME_REQ=0x5A0A,
  API_PP_ULE_SUSPEND_REQ=0x5A0B,
  API_PP_ULE_NVS_READ_REQ=0x5A0E,
  API_PP_ULE_NVS_READ_CFM=0x5A0F,
  API_PP_ULE_NVS_WRITE_REQ=0x5A10,
  API_PP_ULE_NVS_WRITE_CFM=0x5A11,
  API_PP_ULE_REGISTER_CB_REQ=0x5A12,
  API_PP_ULE_REGISTER_CB_CFM=0x5A13,
  API_PP_ULE_DEBUG_DATA_IND=0x5A14,
  API_PP_ULE_DEBUG_DATA_REQ=0x5A15,
  API_PP_ULE_DTR_IND=0x5A16,
  API_PP_ULE_DATA_IND=0x5A17,
  API_PP_ULE_DATA_REQ=0x5A18,
  API_PP_ULE_HAL_SET_PORT_REQ=0x5A1A,
  API_PP_ULE_HAL_GET_PORT_REQ=0x5A1B,
  API_PP_ULE_HAL_GET_PORT_CFM=0x5A1C,
  API_PP_ULE_HAL_PORT_IND=0x5A1D,
  API_PP_ULE_SUBS_STATUS_REQ=0x5A1E,
  API_PP_ULE_SUBS_STATUS_CFM=0x5A1F,
  API_PP_ULE_SUBS_DELETE_REQ=0x5A20,
  API_PP_ULE_SUBS_DELETE_CFM=0x5A21,

  API_PP_MAC_NO_EMISSION_MODE_ENABLE_REQ=0x5C00,                     //ApiPpNoEmission
  API_PP_MAC_NO_EMISSION_MODE_DISABLE_REQ=0x5C01,                    //ApiPpNoEmission
  API_PP_MAC_NO_EMISSION_MODE_STOP_REQ=0x5C02,                       //ApiPpNoEmission
  API_PP_MAC_NO_EMISSION_MODE_PENDING_IND=0x5C03,                    //ApiPpNoEmission
  API_PP_MAC_NO_EMISSION_MODE_ACTIVE_IND=0x5C04,                     //ApiPpNoEmission
  API_PP_MAC_NO_EMISSION_MODE_STOP_IND=0x5C05,                       //ApiPpNoEmission

  API_CLSS_REQ=0x5C40,                                               //ApiClss
  API_CLSS_IND=0x5C41,                                               //ApiClss
  API_CLSS_SET_IWU_TO_IWU_REQ=0x5C42,                                //ApiClss
  API_CLSS_SET_IWU_TO_IWU_CFM=0x5C43,                                //ApiClss
  API_CLSS_SET_FEATURES_REQ=0x5C48,                                  //ApiClss
  API_CLSS_SET_FEATURES_CFM=0x5C49,                                  //ApiClss
  API_CLSS_GET_FEATURES_REQ=0x5C4A,                                  //ApiClss
  API_CLSS_GET_FEATURES_CFM=0x5C4B,                                  //ApiClss

  API_HEADSET_DETECT_HEADSET_IND=0x5D00,                             //ApiHeadset
  API_HEADSET_HOOK_IND=0x5D01,                                       //ApiHeadset

// *******************************************************************************
// *                               Phoenix API end                               *
// *******************************************************************************

  UART_TX_DONE,
  UART_RX_DATA_READY,

  SPI_RX_DATA_READY,                                          //RosCfg
  SPI_TX_DONE,                                                //RosCfg

  MMI_STATE_INIT_ind,
  MMI_SET_STATE_ind,
  MMI_SUSPEND_ind,
  MMI_STATE_TIMEOUT_ind,
  MMI_LED_TIMEOUT_ind,
  MMI_USER_TIMEOUT_ind,
  MMI_LOG_STATE_ind,
  MMI_POLL_TIMEOUT_ind,
  MMI_DATA_ind,
  MMI_RESET_ind,

  NUMBER_OF_PRIMITIVES
} RSENUM16(PrimitiveType);


/****************************************************************************
*                           Global variables/const
****************************************************************************/

/****************************************************************************
*                             Function prototypes
****************************************************************************/

#endif

