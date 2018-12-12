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
#ifndef APIFPPRODTEST_H
#define APIFPPRODTEST_H

/****************************************************************************
*                               Include files
****************************************************************************/
/*! The following API files must be included. */
#include <Phoenix/Api/Types/ApiTypes.h>

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
typedef struct ApiProdTestReqType
{
  RosPrimitiveType Primitive;            /*!< API_PROD_TEST_REQ = 0x4FFE */
  rsuint16 Opcode;                      /*!< Op-code identifying the HW test command. */
  rsuint16 ParameterLength;             /*!< The total length in bytes of the
                                           parameters. */
  rsuint8 Parameters [1];               /*!< Optional parameters. */
} PACKED_STRUCT ApiProdTestReqType;

typedef struct ApiProdTestCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PROD_TEST_CFM = 0x4FFF */
  rsuint16 Opcode;                      /*!< Op-code identifying the HW test command. */
  rsuint16 ParameterLength;             /*!< The total length in bytes of the
                                                 parameters. */
  rsuint8 Parameters [1];               /*!< Optional parameters. */
}PACKED_STRUCT ApiProdTestCfmType;

#ifdef PROJECT_FP_PROD_TEST_EXTENSION
/* Added By ED. Sitel */
/*----------------------------------------------------------------------------------------- */
/*! This mail is used by the FP to set the MCU/DSP in Loop Back mode for product test */
typedef struct ApiFpCcSetupAudioLbReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_CC_SETUP_LOOPBACK_REQ = 0x4430. */
  rsbool LoopBack;                       /*!< TRUE: start audio loop back; FALSE: stop audio loop back. */
  rsuint8 LoopBackMode;                 /*!< 0 = Handset LoopBack; 1 = HandsFree LoopBack */

}PACKED_STRUCT ApiFpCcSetupAudioLbReqType;

/*! This mail is used by the FP to set the MCU/DSP in Loop Back mode for product test */
typedef struct ApiFpCcSetupAudioLbCfmType
{
  RosPrimitiveType Primitive;           /*!< API_FP_CC_SETUP_LOOPBACK_CFM = 0x4431. */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
  rsuint8 LoopBackMode;                 /*!< 0 = Handset LoopBack; 1 = HandsFree LoopBack */
}PACKED_STRUCT ApiFpCcSetupAudioLbCfmType;

/*! This mail is used by the FP to set Base GPIO mode for product test */
typedef struct ApiFpProdTestSetGpioModeReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_PRODTEST_SET_GPIO_MODE_REQ = 0x4432. */
  rsuint16 GpioId;                       /*!< Available GPIOs: [0-15], [100-115], [200-215] and [300-308]. */
  rsuint8 ModeType;                     /*!< Refer to PtGpioModeType */

}PACKED_STRUCT ApiFpProdTestSetGpioModeReqType;

/*! This mail is used by the Base to confirm to FP that GPIO is set */
typedef struct ApiFpProdTestSetGpioModeCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_PRODTEST_SET_GPIO_MODE_CFM = 0x4433. */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                             not. */
}PACKED_STRUCT ApiFpProdTestSetGpioModeCfmType;

/*! This mail is used by the FP to Get Base GPIO mode for product test */
typedef struct ApiFpProdTestGetGpioModeReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_PRODTEST_GET_GPIO_MODE_REQ = 0x4434. */
  rsuint16 GpioId;                       /*!< Available GPIOs: [0-15], [100-115], [200-215] and [300-308]. */

}PACKED_STRUCT ApiFpProdTestGetGpioModeReqType;

/*! This mail is used by the FP to Get Base GPIO mode for product test */
typedef struct ApiFpProdTestGetGpioModeCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_PRODTEST_GET_GPIO_MODE_CFM = 0x4435. */
  rsuint8 ModeType;                      /*!< Refer to PtGpioModeType */

}PACKED_STRUCT ApiFpProdTestGetGpioModeCfmType;

/*! This mail is used by the FP to set Base GPIO state for product test */
typedef struct ApiFpProdTestSetGpioStateReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_PRODTEST_SET_GPIO_STATE_REQ = 0x4436. */
  rsuint16 GpioId;                       /*!< Available GPIOs: [0-15], [100-115], [200-215] and [300-308]. */
  rsuint8 GpioState;                    /*!< Set to 1-High or 0-LOW */

}PACKED_STRUCT ApiFpProdTestSetGpioStateReqType;

/*! This mail is used by the FP to set Base GPIO state for product test */
typedef struct ApiFpProdTestSetGpioStateCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_PRODTEST_SET_GPIO_STATE_CFM = 0x4437. */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                               not. */
}PACKED_STRUCT ApiFpProdTestSetGpioStateCfmType;

/*! This mail is used by the FP to get Base GPIO state for product test */
typedef struct ApiFpProdTestGetGpioStateReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_PRODTEST_GET_GPIO_STATE_REQ = 0x4438. */
  rsuint16 GpioId;                       /*!< Available GPIOs: [0-15], [100-115], [200-215] and [300-308]. */

}PACKED_STRUCT ApiFpProdTestGetGpioStateReqType;

/*! This mail is used by the FP to get Base GPIO state for product test */
typedef struct ApiFpProdTestGetGpioStateCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_PRODTEST_GET_GPIO_STATE_CFM = 0x4439. */
  rsuint8 GpioState;                    /*!<  1-High or 0-LOW */

}PACKED_STRUCT ApiFpProdTestGetGpioStateCfmType;

/*! This mail is used by the FP to set MAC Address for product test */
typedef struct ApiFpProdTestSetMacAddReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_PRODTEST_SET_MAC_ADD_REQ = 0x443a. */
  rsuint8 EthPort;
  rsuint8 MacAdd[6];                     /*!< MAC Address */

}PACKED_STRUCT ApiFpProdTestSetMacAddReqType;

/*! This mail is used by the FP to set Base GPIO state for product test */
typedef struct ApiFpProdTestSetMacAddCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_PRODTEST_SET_MAC_ADD_CFM = 0x443b. */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                               not. */
}PACKED_STRUCT ApiFpProdTestSetMacAddCfmType;

/*! This mail is used by the FP to get Base Mac Add product test */
typedef struct ApiFpProdTestGetMacAddReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_PRODTEST_GET_MAC_ADD_REQ = 0x443c. */
  rsuint8 EthPort;

}PACKED_STRUCT ApiFpProdTestGetMacAddReqType;

/*! This mail is used by the FP to get Base Mac Add product test */
typedef struct ApiFpProdTestGetMacAddCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_PRODTEST_GET_MAC_ADD_CFM = 0x443d. */
  rsuint8 MacAdd[6];                     /*!< MAC Address */

}PACKED_STRUCT ApiFpProdTestGetMacAddCfmType;

/*! This mail is used by the FP to set Band Gap env variable */
typedef struct ApiFpProdTestSetEnvBandGapReqType
{
  RosPrimitiveType Primitive;         /*!< API_FP_PRODTEST_SET_ENV_BAND_GAP_REQ = 0x443e. */
  rsuint8 BandGap;                    /*!< The Band Gap */

}PACKED_STRUCT ApiFpProdTestSetEnvBandGapReqType;

/*! This mail is used by the FP to set Band Gap env variable */
typedef struct ApiFpProdTestSetEnvBandGapCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_PRODTEST_SET_ENV_BAND_GAP_CFM = 0x443f. */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                                 not. */
}PACKED_STRUCT ApiFpProdTestSetEnvBandGapCfmType;

/*! This mail is used by the FP to get Band Gap env variable */
typedef struct ApiFpProdTestGetEnvBandGapReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_PRODTEST_GET_ENV_BAND_GAP_REQ = 0x4440. */

}PACKED_STRUCT ApiFpProdTestGetEnvBandGapReqType;

/*! This mail is used by the FP to get Band Gap env variable */
typedef struct ApiFpProdTestGetEnvBandGapCfmType
{
  RosPrimitiveType Primitive;           /*!< API_FP_PRODTEST_GET_ENV_BAND_GAP_CFM = 0x4441. */
  rsuint8 BandGap;                      /*!< The Band Gap */

}PACKED_STRUCT ApiFpProdTestGetEnvBandGapCfmType;

/*! This mail is used by the FP to set operation mode after reset */
typedef struct ApiFpProdTestSetResetOpReqType
{
  RosPrimitiveType Primitive;         /*!< API_FP_PRODTEST_SET_RESET_OP_REQ = 0x4442. */
  rsuint8          OpMode;            /*!< Operation mode after reset */

}PACKED_STRUCT ApiFpProdTestSetResetOpReqType;

typedef struct ApiFpProdTestSetResetOpCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_PRODTEST_SET_RESET_OP_CFM = 0x4443. */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                                 not. */
}PACKED_STRUCT ApiFpProdTestSetResetOpCfmType;

/*! This mail is used by the FP to reset the DECT module */
typedef struct ApiFpProdTestSetResetModuleReqType
{
  RosPrimitiveType Primitive;         /*!< API_FP_PRODTEST_SET_RESET_MODULE_REQ = 0x4444. */
  rsuint8          OpMode;            /*!< Operation mode after reset */

}PACKED_STRUCT ApiFpProdTestSetResetModuleReqType;

typedef struct ApiFpProdTestSetResetModuleCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_PRODTEST_SET_RESET_MODULE_CFM = 0x4445. */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                                 not. */
}PACKED_STRUCT ApiFpProdTestSetResetModuleCfmType;

/*! This mail is used by the FP to set Env Vars of type string */
typedef struct ApiFpProdTestSetEnvVarStrReqType
{
RosPrimitiveType Primitive;           /*!< API_FP_PRODTEST_SET_ENV_VAR_STR_REQ = 0x4446. */
  rsuint8          EnvVarID;
  rschar           EnvVarStr[30];

}PACKED_STRUCT ApiFpProdTestSetEnvVarStrReqType;

typedef struct ApiFpProdTestSetEnvVarStrCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_PRODTEST_SET_ENV_VAR_STR_CFM = 0x4447. */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                                 not. */
}PACKED_STRUCT ApiFpProdTestSetEnvVarStrCfmType;

typedef struct ApiFpProdTestGetEnvVarStrReqType
{
RosPrimitiveType Primitive;           /*!< API_FP_PRODTEST_GET_ENV_VAR_STR_REQ = 0x4448. */
  rsuint8          EnvVarID;

}PACKED_STRUCT ApiFpProdTestGetEnvVarStrReqType;

typedef struct ApiFpProdTestGetEnvVarStrCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_PRODTEST_GET_ENV_VAR_STR_CFM = 0x4449. */
  rschar           EnvVarStr[30];
}PACKED_STRUCT ApiFpProdTestGetEnvVarStrCfmType;

/*! This mail is used by the FP to set Env Vars of type integer */
typedef struct ApiFpProdTestSetEnvVarIntReqType
{
RosPrimitiveType Primitive;           /*!< API_FP_PRODTEST_SET_ENV_VAR_INT_REQ = 0x4450. */
  rsuint8          EnvVarID;
  rsuint32         EnvVarInt;

}PACKED_STRUCT ApiFpProdTestSetEnvVarIntReqType;

typedef struct ApiFpProdTestSetEnvVarIntCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_PRODTEST_SET_ENV_VAR_INT_CFM = 0x4451. */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                                 not. */
}PACKED_STRUCT ApiFpProdTestSetEnvVarIntCfmType;

typedef struct ApiFpProdTestGetEnvVarIntReqType
{
RosPrimitiveType Primitive;           /*!< API_FP_PRODTEST_GET_ENV_VAR_INT_REQ = 0x4452. */
  rsuint8          EnvVarID;

}PACKED_STRUCT ApiFpProdTestGetEnvVarIntReqType;

typedef struct ApiFpProdTestGetEnvVarIntCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_PRODTEST_GET_ENV_VAR_INT_CFM = 0x4453. */
  rschar           EnvVarStr[10];
}PACKED_STRUCT ApiFpProdTestGetEnvVarIntCfmType;

/*! This mail is used by the FP to set the state of LEDs */
typedef struct ApiFpProdTestSetLEDReqType
{
  RosPrimitiveType Primitive;           /*!< API_FP_PRODTEST_SET_LED_REQ = 0x4454. */
  rsuint8     state;                    /*!< ON/OFF . */
  rsuint8     ledID;                   /*!< 0xFF sets all LEDs. */

}PACKED_STRUCT ApiFpProdTestSetLEDReqType;

typedef struct ApiFpProdTestSetLEDCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_PRODTEST_SET_LED_CFM = 0x4455. */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                                 not. */
}PACKED_STRUCT ApiFpProdTestSetLEDCfmType;

/*! This mail is used by the FP to get FXO/FXS status */
typedef struct ApiFpProdTestGetFxStatusReqType
{
  RosPrimitiveType Primitive;           /*!< API_FP_PRODTEST_GET_FX_STATUS_REQ = 0x4456. */
  rsuint8     LineID;                    /*!< Line={0,1,2,3} . */
  rsuint8     StatusID;                   /*!< Status ID */

}PACKED_STRUCT ApiFpProdTestGetFxStatusReqType;

typedef struct ApiFpProdTestGetFxStatusCfmType
{
  RosPrimitiveType  Primitive;            /*!< API_FP_PRODTEST_GET_FX_STATUS_CFM = 0x4457. */
  rsuint8            FxStatus;                  /*!< Returns the StatusID state */
}PACKED_STRUCT ApiFpProdTestGetFxStatusCfmType;

/*! This mail is used by the FP to set FXO/FXS Hook state */
typedef struct ApiFpProdTestSetFxHookStateReqType
{
  RosPrimitiveType Primitive;           /*!< API_FP_PRODTEST_SET_FX_HOOK_STATE_REQ = 0x4458. */
  rsuint8     LineID;                    /*!< Line={0,1,2,3} . */
  rsuint8     HookState;                  /*!< On-Hook, Off-Hook */

}PACKED_STRUCT ApiFpProdTestSetFxHookStateReqType;

typedef struct ApiFpProdTestSetFxHookStateCfmType
{
  RosPrimitiveType  Primitive;            /*!< API_FP_PRODTEST_SET_FX_HOOK_STATE_CFM = 0x4459. */
  RsStatusType Status;               /*!< Indicates whether the command succeeded or
                                                 not. */
}PACKED_STRUCT ApiFpProdTestSetFxHookStateCfmType;

/*! This mail is used by the FP to set FXS/FXO Loop Back mode */
typedef struct ApiFpProdTestSetFxLBReqType
{
  RosPrimitiveType Primitive;           /*!< API_FP_PRODTEST_SET_FX_LB_REQ = 0x4460. */
  rsuint8   LineID;                    /*!< Line={0,1,2,3} . */
  rsuint8   LBMode;      /*!< LINE_TO_CRECV = 0x00, CMIC_TO_LINE  = 0x01 */
  rsuint8   LBStatus;    /*!< 1=ON, 0=OFF */

}PACKED_STRUCT ApiFpProdTestSetFxLBReqType;

typedef struct ApiFpProdTestSetFxLBCfmType
{
  RosPrimitiveType  Primitive;            /*!< API_FP_PRODTEST_SET_FX_LB_CFM = 0x4461. */
  RsStatusType Status;               /*!< Indicates whether the command succeeded or
                                                 not. */
}PACKED_STRUCT ApiFpProdTestSetFxLBCfmType;

/*! This mail is used by the FP to clear the FXO Caller ID message */
typedef struct ApiFpProdTestSetFxFSKReqType
{
  RosPrimitiveType Primitive;           /*!< API_FP_PRODTEST_SET_FX_FSK_REQ = 0x4462. */
  rsuint8   LineID;                    /*!< Line={0,1,2,3} . */
}PACKED_STRUCT ApiFpProdTestSetFxFSKReqType;

typedef struct ApiFpProdTestSetFxFSKCfmType
{
  RosPrimitiveType  Primitive;            /*!< API_FP_PRODTEST_SET_FX_FSK_CFM = 0x4463. */
  RsStatusType Status;               /*!< Indicates whether the command succeeded or
                                                 not. */
}PACKED_STRUCT ApiFpProdTestSetFxFSKCfmType;

/*! This mail is used by the FP to get FXO Caller ID message */
typedef struct ApiFpProdTestGetFxFSKReqType
{
  RosPrimitiveType Primitive;           /*!< API_FP_PRODTEST_GET_FX_FSK_REQ = 0x4462. */
  rsuint8   LineID;                    /*!< Line={0,1,2,3} . */
}PACKED_STRUCT ApiFpProdTestGetFxFSKReqType;

typedef struct ApiFpProdTestGetFxFSKCfmType
{
  RosPrimitiveType  Primitive;            /*!< API_FP_PRODTEST_GET_FX_FSK_CFM = 0x4463. */
  rschar      Cid[256];                 /*!<  Returns the CID message */
}PACKED_STRUCT ApiFpProdTestGetFxFSKCfmType;
/*------------------------------------------------------------------------------------------*/
#endif //PROJECT_FP_PROD_TEST_EXTENSION*/
#endif /*APIFPPRODTEST_H */
