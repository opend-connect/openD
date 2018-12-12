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

/**************************************************************************************
/                               Phoenix PP API Begin
/ NB: DO NOT CHANGE ORDER OR NUMBERING OF PRIMITIVES
***************************************************************************************/

typedef enum
{
  DUMMY_DATA=0x0000,                                                 //Phoenix
  KEY_MESSAGE=0x0001,                                                //Phoenix
  KEY_RELEASE=0x0002,                                                //Phoenix
  KEY_PRESS=0x0003,                                                  //Phoenix
  TIMEOUT=0x0004,                                                    //Phoenix
  HELLO_STATE_ind=0x0005,                                            //Phoenix
  GOODBYE_STATE_ind=0x0006,                                          //Phoenix
  INITTASK=0x0007,                                                   //Phoenix
  TERMINATETASK=0x0008,                                              //Phoenix
  TEST_PRIMITIVE=0x0009,                                             //Phoenix
  ROS_PM_WAKEUP_ind=0x000A,                                          //Phoenix
  ROS_PM_SUSPEND_ind=0x000B,                                         //Phoenix

  API_PP_VBATT_REQ=0x4380,                                           //ApiPpProject
  API_PP_VBATT_CFM=0x4381,                                           //ApiPpProject
  API_PP_VBATT_ENABLE_REQ=0x4382,                                    //ApiPpProject
  API_PP_VBATT_ENABLE_CFM=0x4383,                                    //ApiPpProject
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
  API_FWU_FEATURES_REQ=0x4F10,                                       //ApiFwu
  API_FWU_FEATURES_CFM=0x4F11,                                       //ApiFwu
  API_FWS_INIT_REQ=0x4F80,                                           //ApiFws
  API_FWS_INIT_CFM=0x4F81,                                           //ApiFws
  API_FWS_TERMINATE_REQ=0x4F82,                                      //ApiFws
  API_FWS_TERMINATE_CFM=0x4F83,                                      //ApiFws
  API_FWS_STATUS_IND=0x4F84,                                         //ApiFws
  API_FWS_INFO_IND=0x4F85,                                           //ApiFws
  API_FWS_WRITE_REQ=0x4F86,                                          //ApiFws
  API_FWS_WRITE_CFM=0x4F87,                                          //ApiFws
  API_FWS_WRITE_EXT_DATA_REQ=0x4F88,                                 //ApiFws
  API_FWS_WRITE_EXT_DATA_CFM=0x4F89,                                 //ApiFws
  API_PROD_TEST_REQ=0x4FFE,                                          //ApiProdTest
  API_PROD_TEST_CFM=0x4FFF,                                          //ApiProdTest

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
  API_PP_MM_SET_TERMCAP_REQ=0x5125,                                  //ApiPpMm
  API_PP_MM_SET_TERMCAP_CFM=0x5126,                                  //ApiPpMm
  API_PP_MM_GET_TERMCAP_REQ=0x5127,                                  //ApiPpMm
  API_PP_MM_GET_TERMCAP_CFM=0x5128,                                  //ApiPpMm
  
  API_IMAGE_INFO_REQ=0x5800,                                         //ApiImageControl
  API_IMAGE_INFO_CFM=0x5801,                                         //ApiImageControl
  API_IMAGE_ACTIVATE_REQ=0x5802,                                     //ApiImageControl
  API_IMAGE_ACTIVATE_CFM=0x5803,                                     //ApiImageControl

  API_HAL_DEVICE_CONTROL_REQ=0x5900,                                 //ApiHal
  API_HAL_DEVICE_CONTROL_CFM=0x5901,                                 //ApiHal
  API_HAL_LED_REQ=0x5902,                                            //ApiHal
  API_HAL_LED_CFM=0x5903,                                            //ApiHal
  API_HAL_READ_REQ=0x5904,                                           //ApiHal
  API_HAL_READ_CFM=0x5905,                                           //ApiHal
  API_HAL_WRITE_REQ=0x5906,                                          //ApiHal
  API_HAL_WRITE_CFM=0x5907,                                          //ApiHal
  API_HAL_GPIO_FN_REGISTER_REQ=0x5910,                               //ApiHal
  API_HAL_GPIO_FN_REGISTER_CFM=0x5911,                               //ApiHal
  API_HAL_SET_GPIO_PORT_PIN_MODE_REQ=0x5912,                         //ApiHal
  API_HAL_SET_GPIO_PORT_PIN_MODE_CFM=0x5913,                         //ApiHal
  API_HAL_SET_GPIO_PORT_REQ=0x5914,                                  //ApiHal
  API_HAL_SET_GPIO_PORT_CFM=0x5915,                                  //ApiHal
  API_HAL_RESET_GPIO_PORT_REQ=0x5916,                                //ApiHal
  API_HAL_RESET_GPIO_PORT_CFM=0x5917,                                //ApiHal
  API_HAL_GET_GPIO_PORT_REQ=0x5918,                                  //ApiHal
  API_HAL_GET_GPIO_PORT_CFM=0x5919,                                  //ApiHal
  API_HAL_GET_ADC_REQ=0x5920,                                        //ApiHal
  API_HAL_GET_ADC_CFM=0x5921,                                        //ApiHal

  API_PP_ULE_INIT_REQ=0x5A00,                                        //ApiPpUle
  API_PP_ULE_INIT_CFM=0x5A01,                                        //ApiPpUle
  API_PP_ULE_FP_LOST_IND=0x5A06,                                     //ApiPpUle
  API_PP_ULE_LOCATE_REQ=0x5A07,                                      //ApiPpUle
  API_PP_ULE_INFO_REQ=0x5A08,                                        //ApiPpUle
  API_PP_ULE_INFO_CFM=0x5A09,                                        //ApiPpUle
  API_PP_ULE_WAKEUP_TIME_REQ=0x5A0A,                                 //ApiPpUle
  API_PP_ULE_SUSPEND_REQ=0x5A0B,                                     //ApiPpUle
  API_PP_ULE_HIBERNATE_READ_REQ=0x5A0E,                              //ApiPpUle
  API_PP_ULE_HIBERNATE_READ_CFM=0x5A0F,                              //ApiPpUle
  API_PP_ULE_HIBERNATE_WRITE_REQ=0x5A10,                             //ApiPpUle
  API_PP_ULE_HIBERNATE_WRITE_CFM=0x5A11,                             //ApiPpUle
  API_PP_ULE_READY_IND=0x5A15,                                       //ApiPpUle
  API_PP_ULE_DTR_IND=0x5A16,                                         //ApiPpUle
  API_PP_ULE_DATA_IND=0x5A17,                                        //ApiPpUle
  API_PP_ULE_DATA_REQ=0x5A18,                                        //ApiPpUle
  API_PP_ULE_HAL_SET_PORT_REQ=0x5A1A,                                //ApiPpUle
  API_PP_ULE_HAL_GET_PORT_REQ=0x5A1B,                                //ApiPpUle
  API_PP_ULE_HAL_GET_PORT_CFM=0x5A1C,                                //ApiPpUle
  API_PP_ULE_HAL_PORT_IND=0x5A1D,                                    //ApiPpUle
  API_PP_ULE_SUBS_STATUS_REQ=0x5A1E,                                 //ApiPpUle
  API_PP_ULE_SUBS_STATUS_CFM=0x5A1F,                                 //ApiPpUle
  API_PP_ULE_SUBS_DELETE_REQ=0x5A20,                                 //ApiPpUle
  API_PP_ULE_SUBS_DELETE_CFM=0x5A21,                                 //ApiPpUle
  API_PP_ULE_DB_PAGE_ENABLE_REQ=0x5A22,                              //ApiPpUle
  API_PP_ULE_DB_PAGE_ENABLE_CFM=0x5A23,                              //ApiPpUle
  API_PP_ULE_DB_PAGE_IND=0x5A24,                                     //ApiPpUle
  API_PP_ULE_DATA_CFM=0x5A25,                                        //ApiPpUle  
  API_PP_ULE_RESUME_ERROR_IND=0x5A26,                                //ApiPpUle
  API_PP_ULE_PVC_CONFIG_REQ=0x5A27,                                  //ApiPpUle
  API_PP_ULE_PVC_CONFIG_CFM=0x5A28,                                  //ApiPpUle
  API_PP_ULE_PVC_CONFIG_REJ=0x5A29,                                  //ApiPpUle
  API_PP_ULE_PVC_PENDING_IND=0x5A2A,                                 //ApiPpUle
  API_PP_ULE_PVC_PENDING_RES=0x5A2B,                                 //ApiPpUle
  API_PP_ULE_PVC_IWU_DATA_REQ=0x5A2C,                                //ApiPpUle
  API_PP_ULE_PVC_IWU_DATA_IND=0x5A2D,                                //ApiPpUle
  API_PP_ULE_PVC_CONFIG_IND=0x5A2E,                                  //ApiPpUle
  API_PP_ULE_SETUP_AGAIN_IND=0x5A2F,                                 //ApiPpUle
  API_PP_ULE_START_LOCATE_IND=0x5A30,                                //ApiPpUle
  API_PP_ULE_HIGH_PAGING_MODE_IND=0x5A31,                            //ApiPpUle
  API_PP_ULE_LCE_PAGING_MODE_IND=0x5A32,                             //ApiPpUle
  API_PP_ULE_START_VOICE_CALL_IND=0x5A33,                            //ApiPpUle
  API_PP_ULE_LOCATE_REJ=0x5A34,                                      //ApiPpUle
  

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
  MMI_RESET_TIMEOUT_ind,
  CAPP_INIT_ind,
  CAPP_TIMEOUT_ind,
  CAPP_MESSAGES_ind,

  NUMBER_OF_PRIMITIVES
} RSENUM16(PrimitiveType);

/****************************************************************************
*                           Global variables/const
****************************************************************************/

/****************************************************************************
*                             Function prototypes
****************************************************************************/

#endif

