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

/* Based on Stack/Include/Ros/RosPrimitive.h */


//#ifndef ROSPRIMITIVDEBUG_H
//#define ROSPRIMITIVDEBUG_H

#include "enum_to_string.h"

BEGIN_ENUM(RosPrimDbg)
{
  DECL_ENUM_ELEMENT_VAL( __DUMMY_DATA, 0x0000 )                                                 //Phoenix
  DECL_ENUM_ELEMENT_VAL( __KEY_MESSAGE, 0x0001 )                                                //Phoenix
  DECL_ENUM_ELEMENT_VAL( __KEY_RELEASE, 0x0002 )                                                //Phoenix
  DECL_ENUM_ELEMENT_VAL( __KEY_PRESS, 0x0003 )                                                  //Phoenix
  DECL_ENUM_ELEMENT_VAL( __TIMEOUT, 0x0004 )                                                    //Phoenix
  DECL_ENUM_ELEMENT_VAL( __HELLO_STATE_ind, 0x0005 )                                            //Phoenix
  DECL_ENUM_ELEMENT_VAL( __GOODBYE_STATE_ind, 0x0006 )                                          //Phoenix
  DECL_ENUM_ELEMENT_VAL( __INITTASK, 0x0007 )                                                   //Phoenix
  DECL_ENUM_ELEMENT_VAL( __TERMINATETASK, 0x0008 )                                              //Phoenix
  DECL_ENUM_ELEMENT_VAL( __TEST_PRIMITIVE, 0x0009 )                                             //Phoenix
  DECL_ENUM_ELEMENT_VAL( __ROS_PM_WAKEUP_ind, 0x000A )                                          //Phoenix
  DECL_ENUM_ELEMENT_VAL( __ROS_PM_SUSPEND_ind, 0x000B )                                         //Phoenix

  DECL_ENUM_ELEMENT_VAL( __API_PP_VBATT_REQ, 0x4380 )                                           //ApiPpProject
  DECL_ENUM_ELEMENT_VAL( __API_PP_VBATT_CFM, 0x4381 )                                           //ApiPpProject
  DECL_ENUM_ELEMENT_VAL( __API_PP_VBATT_ENABLE_REQ, 0x4382 )                                    //ApiPpProject
  DECL_ENUM_ELEMENT_VAL( __API_PP_VBATT_ENABLE_CFM, 0x4383 )                                    //ApiPpProject
  DECL_ENUM_ELEMENT_VAL( __API_FWU_ENABLE_REQ, 0x4F00 )                                         //ApiFwu
  DECL_ENUM_ELEMENT_VAL( __API_FWU_ENABLE_CFM, 0x4F01 )                                         //ApiFwu
  DECL_ENUM_ELEMENT_VAL( __API_FWU_DEVICE_NOTIFY_IND, 0x4F02 )                                  //ApiFwu
  DECL_ENUM_ELEMENT_VAL( __API_FWU_UPDATE_REQ, 0x4F03 )                                         //ApiFwu
  DECL_ENUM_ELEMENT_VAL( __API_FWU_UPDATE_CFM, 0x4F04 )                                         //ApiFwu
  DECL_ENUM_ELEMENT_VAL( __API_FWU_UPDATE_IND, 0x4F05 )                                         //ApiFwu
  DECL_ENUM_ELEMENT_VAL( __API_FWU_UPDATE_RES, 0x4F06 )                                         //ApiFwu
  DECL_ENUM_ELEMENT_VAL( __API_FWU_GET_BLOCK_IND, 0x4F07 )                                      //ApiFwu
  DECL_ENUM_ELEMENT_VAL( __API_FWU_GET_BLOCK_RES, 0x4F08 )                                      //ApiFwu
  DECL_ENUM_ELEMENT_VAL( __API_FWU_GET_CRC_IND, 0x4F09 )                                        //ApiFwu
  DECL_ENUM_ELEMENT_VAL( __API_FWU_GET_CRC_RES, 0x4F0A )                                        //ApiFwu
  DECL_ENUM_ELEMENT_VAL( __API_FWU_COMPLETE_IND, 0x4F0B )                                       //ApiFwu
  DECL_ENUM_ELEMENT_VAL( __API_FWU_STATUS_IND, 0x4F0C )                                         //ApiFwu
  DECL_ENUM_ELEMENT_VAL( __API_FWU_MULTI_CRC_IND, 0x4F0D )                                      //ApiFwu
  DECL_ENUM_ELEMENT_VAL( __API_FWU_MULTI_CRC_RES, 0x4F0E )                                      //ApiFwu
  DECL_ENUM_ELEMENT_VAL( __API_FWU_FEATURES_REQ, 0x4F10 )                                       //ApiFwu
  DECL_ENUM_ELEMENT_VAL( __API_FWU_FEATURES_CFM, 0x4F11 )                                       //ApiFwu
  DECL_ENUM_ELEMENT_VAL( __API_FWS_INIT_REQ, 0x4F80 )                                           //ApiFws
  DECL_ENUM_ELEMENT_VAL( __API_FWS_INIT_CFM, 0x4F81 )                                           //ApiFws
  DECL_ENUM_ELEMENT_VAL( __API_FWS_TERMINATE_REQ, 0x4F82 )                                      //ApiFws
  DECL_ENUM_ELEMENT_VAL( __API_FWS_TERMINATE_CFM, 0x4F83 )                                      //ApiFws
  DECL_ENUM_ELEMENT_VAL( __API_FWS_STATUS_IND, 0x4F84 )                                         //ApiFws
  DECL_ENUM_ELEMENT_VAL( __API_FWS_INFO_IND, 0x4F85 )                                           //ApiFws
  DECL_ENUM_ELEMENT_VAL( __API_FWS_WRITE_REQ, 0x4F86 )                                          //ApiFws
  DECL_ENUM_ELEMENT_VAL( __API_FWS_WRITE_CFM, 0x4F87 )                                          //ApiFws
  DECL_ENUM_ELEMENT_VAL( __API_FWS_WRITE_EXT_DATA_REQ, 0x4F88 )                                 //ApiFws
  DECL_ENUM_ELEMENT_VAL( __API_FWS_WRITE_EXT_DATA_CFM, 0x4F89 )                                 //ApiFws
  DECL_ENUM_ELEMENT_VAL( __API_PROD_TEST_REQ, 0x4FFE )                                          //ApiProdTest
  DECL_ENUM_ELEMENT_VAL( __API_PROD_TEST_CFM, 0x4FFF )                                          //ApiProdTest

  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_GET_ID_REQ, 0x5100 )                                       //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_GET_ID_CFM, 0x5101 )                                       //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_GET_MODEL_REQ, 0x5102 )                                    //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_GET_MODEL_CFM, 0x5103 )                                    //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_READ_RSSI_REQ, 0x5104 )                                    //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_READ_RSSI_CFM, 0x5105 )                                    //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_LOCK_REQ, 0x5106 )                                         //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_LOCKED_REQ, 0x5107 )                                       //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_LOCKED_IND, 0x5108 )                                       //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_UNLOCKED_IND, 0x5109 )                                     //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_STOP_PROTOCOL_REQ, 0x510A )                                //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_REGISTRATION_AUTO_REQ, 0x510B )                            //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_REGISTRATION_SEARCH_REQ, 0x510C )                          //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_REGISTRATION_SEARCH_IND, 0x510D )                          //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_REGISTRATION_SELECTED_REQ, 0x510E )                        //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_REGISTRATION_STOP_REQ, 0x510F )                            //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_REGISTRATION_COMPLETE_IND, 0x5110 )                        //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_REGISTRATION_FAILED_IND, 0x5111 )                          //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_REGISTRATION_SELECTED_WITH_PLI_REQ, 0x5112 )               //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_DELETE_LOCAL_REGISTRATION_REQ, 0x5114 )                    //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_DELETE_LOCAL_REGISTRATION_CFM, 0x5115 )                    //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_UPI_AUTHENTICATE_IND, 0x5117 )                             //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_UPI_AUTHENTICATE_RES, 0x5118 )                             //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_UNITDATA_IND, 0x5119 )                                     //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_ALERT_BROADCAST_IND, 0x511A )                              //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_ACC_RIGHTS_TERM_IND, 0x511B )                              //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_FP_NAME_IND, 0x511D )                                      //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_ENCRYPTION_NOT_STARTED_IND, 0x511E )                       //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_GET_EXT_HIGHER_LAYER_CAP2_REQ, 0x511F )                    //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_GET_EXT_HIGHER_LAYER_CAP2_CFM, 0x5120 )                    //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_EASY_PAIRING_SEARCH_REQ, 0x5121 )                          //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_EASY_PAIRING_SEARCH_CFM, 0x5122 )                          //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_GET_SUBSCRIPTION_RFPI_REQ, 0x5123 )                        //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_GET_SUBSCRIPTION_RFPI_CFM, 0x5124 )                        //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_SET_TERMCAP_REQ, 0x5125 )                                 //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_SET_TERMCAP_CFM, 0x5126 )                                 //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_GET_TERMCAP_REQ, 0x5127 )                                 //ApiPpMm
  DECL_ENUM_ELEMENT_VAL( __API_PP_MM_GET_TERMCAP_CFM, 0x5128 )                                 //ApiPpMm
  
  DECL_ENUM_ELEMENT_VAL( __API_IMAGE_INFO_REQ, 0x5800 )                                         //ApiImageControl
  DECL_ENUM_ELEMENT_VAL( __API_IMAGE_INFO_CFM, 0x5801 )                                         //ApiImageControl
  DECL_ENUM_ELEMENT_VAL( __API_IMAGE_ACTIVATE_REQ, 0x5802 )                                     //ApiImageControl
  DECL_ENUM_ELEMENT_VAL( __API_IMAGE_ACTIVATE_CFM, 0x5803 )                                     //ApiImageControl

  DECL_ENUM_ELEMENT_VAL( __API_HAL_DEVICE_CONTROL_REQ, 0x5900 )                                 //ApiHal
  DECL_ENUM_ELEMENT_VAL( __API_HAL_DEVICE_CONTROL_CFM, 0x5901 )                                 //ApiHal
  DECL_ENUM_ELEMENT_VAL( __API_HAL_LED_REQ, 0x5902 )                                            //ApiHal
  DECL_ENUM_ELEMENT_VAL( __API_HAL_LED_CFM, 0x5903 )                                            //ApiHal
  DECL_ENUM_ELEMENT_VAL( __API_HAL_READ_REQ, 0x5904 )                                           //ApiHal
  DECL_ENUM_ELEMENT_VAL( __API_HAL_READ_CFM, 0x5905 )                                           //ApiHal
  DECL_ENUM_ELEMENT_VAL( __API_HAL_WRITE_REQ, 0x5906 )                                          //ApiHal
  DECL_ENUM_ELEMENT_VAL( __API_HAL_WRITE_CFM, 0x5907 )                                          //ApiHal
  DECL_ENUM_ELEMENT_VAL( __API_HAL_GPIO_FN_REGISTER_REQ, 0x5910 )                               //ApiHal
  DECL_ENUM_ELEMENT_VAL( __API_HAL_GPIO_FN_REGISTER_CFM, 0x5911 )                               //ApiHal
  DECL_ENUM_ELEMENT_VAL( __API_HAL_SET_GPIO_PORT_PIN_MODE_REQ, 0x5912 )                         //ApiHal
  DECL_ENUM_ELEMENT_VAL( __API_HAL_SET_GPIO_PORT_PIN_MODE_CFM, 0x5913 )                         //ApiHal
  DECL_ENUM_ELEMENT_VAL( __API_HAL_SET_GPIO_PORT_REQ, 0x5914 )                                  //ApiHal
  DECL_ENUM_ELEMENT_VAL( __API_HAL_SET_GPIO_PORT_CFM, 0x5915 )                                  //ApiHal
  DECL_ENUM_ELEMENT_VAL( __API_HAL_RESET_GPIO_PORT_REQ, 0x5916 )                                //ApiHal
  DECL_ENUM_ELEMENT_VAL( __API_HAL_RESET_GPIO_PORT_CFM, 0x5917 )                                //ApiHal
  DECL_ENUM_ELEMENT_VAL( __API_HAL_GET_GPIO_PORT_REQ, 0x5918 )                                  //ApiHal
  DECL_ENUM_ELEMENT_VAL( __API_HAL_GET_GPIO_PORT_CFM, 0x5919 )                                  //ApiHal
  DECL_ENUM_ELEMENT_VAL( __API_HAL_GET_ADC_REQ, 0x5920 )                                        //ApiHal
  DECL_ENUM_ELEMENT_VAL( __API_HAL_GET_ADC_CFM, 0x5921 )                                        //ApiHal

  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_INIT_REQ, 0x5A00 )                                        //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_INIT_CFM, 0x5A01 )                                        //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_LOCATE_REQ, 0x5A07 )                                      //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_INFO_REQ, 0x5A08 )                                        //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_INFO_CFM, 0x5A09 )                                        //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_WAKEUP_TIME_REQ, 0x5A0A )                                 //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_SUSPEND_REQ, 0x5A0B )                                     //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_HIBERNATE_READ_REQ, 0x5A0E )                              //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_HIBERNATE_READ_CFM, 0x5A0F )                              //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_HIBERNATE_WRITE_REQ, 0x5A10 )                             //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_HIBERNATE_WRITE_CFM, 0x5A11 )                             //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_READY_IND, 0x5A15 )                                       //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_DTR_IND, 0x5A16 )                                         //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_DATA_IND, 0x5A17 )                                        //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_DATA_REQ, 0x5A18 )                                        //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_HAL_SET_PORT_REQ, 0x5A1A )                                //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_HAL_GET_PORT_REQ, 0x5A1B )                                //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_HAL_GET_PORT_CFM, 0x5A1C )                                //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_HAL_PORT_IND, 0x5A1D )                                    //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_SUBS_STATUS_REQ, 0x5A1E )                                 //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_SUBS_STATUS_CFM, 0x5A1F )                                 //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_SUBS_DELETE_REQ, 0x5A20 )                                 //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_SUBS_DELETE_CFM, 0x5A21 )                                 //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_DB_PAGE_ENABLE_REQ, 0x5A22 )                              //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_DB_PAGE_ENABLE_CFM, 0x5A23 )                              //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_DB_PAGE_IND, 0x5A24 )                                     //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_DATA_CFM, 0x5A25 )                                        //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_RESUME_ERROR_IND, 0x5A26 )                                //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_PVC_CONFIG_REQ, 0x5A27 )                                  //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_PVC_CONFIG_CFM, 0x5A28 )                                  //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_PVC_CONFIG_REJ, 0x5A29 )                                  //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_PVC_PENDING_IND, 0x5A2A )                                 //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_PVC_PENDING_RES, 0x5A2B )                                 //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_PVC_IWU_DATA_REQ, 0x5A2C )                                //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_PVC_IWU_DATA_IND, 0x5A2D )                                //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_PVC_CONFIG_IND, 0x5A2E )                                  //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_SETUP_AGAIN_IND, 0x5A2F )                                 //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_START_LOCATE_IND, 0x5A30 )                                //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_HIGH_PAGING_MODE_IND, 0x5A31 )                            //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_LCE_PAGING_MODE_IND, 0x5A32 )                             //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_START_VOICE_CALL_IND, 0x5A33 )                            //ApiPpUle
  DECL_ENUM_ELEMENT_VAL( __API_PP_ULE_LOCATE_REJ, 0x5A34 )   

// *******************************************************************************
// *                               Phoenix API end                               *
// *******************************************************************************

  DECL_ENUM_ELEMENT( __UART_TX_DONE )
  DECL_ENUM_ELEMENT( __UART_RX_DATA_READY )

  DECL_ENUM_ELEMENT( __SPI_RX_DATA_READY )                                          //RosCfg
  DECL_ENUM_ELEMENT( __SPI_TX_DONE )                                                //RosCfg

  DECL_ENUM_ELEMENT( __MMI_STATE_INIT_ind )
  DECL_ENUM_ELEMENT( __MMI_SET_STATE_ind )
  DECL_ENUM_ELEMENT( __MMI_SUSPEND_ind )
  DECL_ENUM_ELEMENT( __MMI_STATE_TIMEOUT_ind )
  DECL_ENUM_ELEMENT( __MMI_LED_TIMEOUT_ind )
  DECL_ENUM_ELEMENT( __MMI_USER_TIMEOUT_ind )
  DECL_ENUM_ELEMENT( __MMI_LOG_STATE_ind )
  DECL_ENUM_ELEMENT( __MMI_POLL_TIMEOUT_ind )
  DECL_ENUM_ELEMENT( __MMI_DATA_ind )
  DECL_ENUM_ELEMENT( __MMI_RESET_ind )
  DECL_ENUM_ELEMENT( __MMI_RESET_TIMEOUT_ind )
  DECL_ENUM_ELEMENT( __CAPP_INIT_ind )
  DECL_ENUM_ELEMENT( __CAPP_TIMEOUT_ind )
  DECL_ENUM_ELEMENT( __CAPP_MESSAGES_ind )
  
  
  DECL_ENUM_ELEMENT(__NUMBER_OF_PRIMITIVES)
}
END_ENUM(RosPrimDbg)

/****************************************************************************
*                           Global variables/const
****************************************************************************/

/****************************************************************************
*                             Function prototypes
****************************************************************************/

//#endif /* ROSPRIMITIVDEBUG_H */

