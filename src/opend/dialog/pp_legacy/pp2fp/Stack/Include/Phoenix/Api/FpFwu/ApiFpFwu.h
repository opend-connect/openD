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
* Definition of the ApiFpFwu interface.
*/


#ifndef APIFPFWU_H
#define APIFPFWU_H

/****************************************************************************
*                               Include files
****************************************************************************/
/*! The following API files must be included. */
#include <Api/ApiCfg.h>

#include <Phoenix/Api/Types/ApiTypes.h>

/****************************************************************************
*                               Macros/Defines
****************************************************************************/

/*! This type describes features available in this API. */
#define API_FWU_EXTENDED_TERMINAL_ID_SUPPORT 0x01

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

#if (RTX_CORE_VERSION >= 0x0224)
  #include <Standard/Common/RsPushPack1.h>
#else
  #pragma pack(push,1)
#endif

/* Mail primitives:
  API_FP_FWU_ENABLE_REQ = 0x4F00,
  API_FP_FWU_ENABLE_CFM = 0x4F01,
  API_FP_FWU_DEVICE_NOTIFY_IND = 0x4F02,
  API_FP_FWU_UPDATE_REQ = 0x4F03,
  API_FP_FWU_UPDATE_CFM = 0x4F04,
  API_FP_FWU_UPDATE_IND = 0x4F05,
  API_FP_FWU_UPDATE_RES = 0x4F06,
  API_FP_FWU_GET_BLOCK_IND = 0x4F07,
  API_FP_FWU_GET_BLOCK_RES = 0x4F08,
  API_FP_FWU_GET_CRC_IND = 0x4F09,
  API_FP_FWU_GET_CRC_RES = 0x4F0A,
  API_FP_FWU_COMPLETE_IND = 0x4F0B,
  API_FP_FWU_STATUS_IND = 0x4F0C,
  API_FP_FWU_MULTI_CRC_IND = 0x4F0D,
  API_FP_FWU_MULTI_CRC_RES = 0x4F0E,
  API_FP_FWU_FEATURES_REQ = 0x4F10,
  API_FP_FWU_FEATURES_CFM = 0x4F11,
End of mail primitives. */



/*! This enum identifies the FWU modes supported by the FP firmware. */
typedef enum RSENUMTAG(ApiFwuModeType)
{
  AFM_FWU         = 0x00, /*!< The FWU/temp area. */
  AFM_MAIN        = 0x01, /*!< The main area. */
  AFM_AUX         = 0x10, /*!< Auxiliary area. This is a flag  that is set together with
                             one of the other modes. */
  AFM_UNSPECIFIED = 0xFF  /*!< Invalid. */
} RSENUM8(ApiFwuModeType);

/*! This type is used to specify the range of FWU blocks. */
typedef struct 
{
  rsuint32 StartAddr;                   /*!< The start address of the block. */
  rsuint32 Size;                        /*!< The size of the block. */
} ApiFwuRangeType;

/*! This bit set identifies the FWU features supported by the host
   application. */
typedef enum RSENUMTAG(ApiFwuFeaturesType)
{
  AFF_STANDARD  = 0x01, /*!< Standard FWU mails supported. */
  AFF_MULTI_CRC = 0x02, /*!< API_FP_FWU_MULTI_CRC_IND supported. */
} RSENUM8(ApiFwuFeaturesType);

/*! This type is used for a range of CRC blocks. */
typedef struct 
{
  rsuint16 Size;                        /*!< The size of the block. */
  rsuint16 Crc;                         /*!< The CRC of the block. */
} ApiFwuCrcType;

/*! This type is used to exchange features between the host and the DECT
   module. */
typedef rsuint8 ApiFwuFeatureType;


/*! Mail without parameters. */
typedef struct ApifpfwuEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} ApifpfwuEmptySignalType;

/*! The FWU Provider in the FP application uses this mail to enable or
   disable the FWU manager in the FP. The FWU manager is enabled when the FP
   starts after reset. */
typedef struct ApiFpFwuEnableReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_ENABLE_REQ = 0x4F00 */
  rsuint8 Enable;                       /*!< 1: The FWU manger is enabled.
                                           0: The FWU manger is disabled. */
  ApiFwuFeaturesType Features;          /*!< Feature set supported by the host
                                           application. */
} ApiFpFwuEnableReqType;

/*! This mail is used by the FP to confirm the API_FP_FWU_ENABLE_REQ
   command. */
typedef struct ApiFpFwuEnableCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_ENABLE_CFM = 0x4F01 */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
} ApiFpFwuEnableCfmType;

/*! This mail is used by the FWU Manager in the FP to inform the FWU
   Provider about the devices available for FW download. Only one device, the
   FP module self, is supported in this implementation. */
typedef struct ApiFpFwuDeviceNotifyIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_DEVICE_NOTIFY_IND = 0x4F02 */
  rsuint8 Present;                      /*!< 0: absent 
                                           1: present */
  ApiTerminalIdType DeviceNr;           /*!< Device number. 0 = FP  (1..n=PP's) */
  rsuint32 DeviceId;                    /*!< Unique device id. */
  rsuint32 TargetData;                  /*!< Information block offset in area. */
  ApiFwuModeType FwuMode;               /*!< FWU Mode. */
  rsuint8 LinkDate[5];                  /*!< The link date of the current FW in the
                                           device. */
  ApiFwuRangeType Range;                /*!< The start address and the size of the FW in
                                           the target device. */
} ApiFpFwuDeviceNotifyIndType;

/*! This mail is used by the FWU Provider in the FP application to inform
   the FWU manager in the FP that a new FW is available for the device
   specified. */
typedef struct ApiFpFwuUpdateReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_UPDATE_REQ = 0x4F03 */
  ApiTerminalIdType DeviceNr;           /*!< Device number. 0 = 0 = FP  (1..n=PP's) */
  ApiFwuModeType FwuMode;               /*!< FWU Mode. */
} ApiFpFwuUpdateReqType;

/*! This mail is used by the FP to confirm the API_FP_FWU_UPDATE_REQ
   command. */
typedef struct ApiFpFwuUpdateCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_UPDATE_CFM = 0x4F04 */
  ApiTerminalIdType DeviceNr;           /*!< Device number. 0 = FP  (1..n=PP's) */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
} ApiFpFwuUpdateCfmType;

/*! This mail is used by the FWU Manager in the FP to request information
   about the new FW available for the device specified. */
typedef struct ApiFpFwuUpdateIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_UPDATE_IND = 0x4F05 */
  ApiTerminalIdType DeviceNr;           /*!< Device number. 0 = FP  (1..n=PP's) */
  rsuint32 DeviceId;                    /*!< Unique device id. */
  rsuint32 TargetData;                  /*!< Information block offset in area. */
  ApiFwuModeType FwuMode;               /*!< FWU Mode. */
  rsuint8 LinkDate[5];                  /*!< The link date of the current FW in the
                                           device. */
  ApiFwuRangeType Range;                /*!< The start address and the size of the FW in
                                           the target. */
} ApiFpFwuUpdateIndType;

/*! This mail is used by the FWU Provider in the FP to return FW
   information to the FWU Manager in the FP. */
typedef struct ApiFpFwuUpdateResType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_UPDATE_RES = 0x4F06 */
  ApiTerminalIdType DeviceNr;           /*!< Device number. 0 = FP  (1..n=PP's) */
  rsuint8 LinkDate[5];                  /*!< Link date for current area. */
  rsuint32 PrvContext;                  /*!< Provider context. Used in all subsequent
                                           mails to identify the FWU update sessions. */
  rsuint32 RangesCount;                 /*!< The number of FWU ranges. */
  ApiFwuRangeType Ranges[1];            /*!< Array holding the address and size of each
                                           block range. The size of Ranges[] is
                                           RangesCount*sizeof (RtxFwuRangeType). */
} ApiFpFwuUpdateResType;

/*! This mail is used by the FWU Manager in the FP to request a FW block
   from the FWU Provider in the FP application . */
typedef struct ApiFpFwuGetBlockIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_GET_BLOCK_IND = 0x4F07 */
  ApiTerminalIdType DeviceNr;           /*!< Device number. 0 = FP  (1..n=PP's) */
  rsuint32 PrvContext;                  /*!< Provider context; identifies the FWU
                                           session. */
  rsuint32 Address;                     /*!< Current address. */
  rsuint32 Size;                        /*!< Max size of returned block. */
} ApiFpFwuGetBlockIndType;

/*! This mail is used by the FWU Provider in the FP application to return a
   FW block to the FWU Manager in the FP. */
typedef struct ApiFpFwuGetBlockResType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_GET_BLOCK_RES = 0x4F08 */
  ApiTerminalIdType DeviceNr;           /*!< Device number. 0 = FP  (1..n=PP's) */
  rsuint32 PrvContext;                  /*!< Provider context; identifies the FWU
                                           session. */
  rsuint32 Address;                     /*!< Current address. */
  rsuint32 DataLength;                  /*!< Size of data. */
  rsuint8 Data[1];                      /*!< DataLength bytes of FW data. */
} ApiFpFwuGetBlockResType;

/*! This mail is used by the FWU Manager in the FP to request the CRC for a
   FW block from the FWU Provider in the FP application. */
typedef struct ApiFpFwuGetCrcIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_GET_CRC_IND = 0x4F09 */
  ApiTerminalIdType DeviceNr;           /*!< Device number. 0 = FP  (1..n=PP's) */
  rsuint32 PrvContext;                  /*!< Provider context; identifies the FWU
                                           session. */
  rsuint32 Address;                     /*!< Current address. */
  rsuint32 Size;                        /*!< Max size of block CRC?ed. */
} ApiFpFwuGetCrcIndType;

/*! This mail is used by the FWU Provider in the FP application to return
   the requested CRC to the FWU Manager in the FP. */
typedef struct ApiFpFwuGetCrcResType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_GET_CRC_RES = 0x4F0A */
  ApiTerminalIdType DeviceNr;           /*!< Device number. 0 = FP  (1..n=PP's) */
  rsuint32 PrvContext;                  /*!< Provider context; identifies the FWU
                                           session. */
  rsuint32 Address;                     /*!< Address. */
  rsuint32 Size;                        /*!< Size of block CRC?ed. */
  rsuint16 Crc;                         /*!< CRC. */
} ApiFpFwuGetCrcResType;

/*! The FWU Manager in the FP uses this mail to indicate to the FWU
   Provider in the FP application that the FWU session is terminated. The FWU
   session is terminates when the complete FW ha been downloaded to the FP,
   but it will also be terminated  before a reset needed to switch from e.g.
   the main program to the FWU program. Finally the session can be terminated
   as result of an error detected by the FWU manager in the FP. It is hence
   necessary for the FWU provider to check the link date and the FwuMode in
   the API_FP_FWU_DEVICE_NOTIFY_IND and restart the FWU process if needed.
   Normally the FWU process must be restarted once, that is after the FP has
   reset to switch from the mian program to the FWU program in the FLASH. */
typedef struct ApiFpFwuCompleteIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_COMPLETE_IND = 0x4F0B */
  rsuint32 PrvContext;                  /*!< Provider context; identifies the FWU
                                           session. */
} ApiFpFwuCompleteIndType;

/*! The FWU Manager in the FP uses this mail to indicate the current status
   to the FWU Provider in the FP aplpication. The FP application does not have
   to handle this mail. */
typedef struct ApiFpFwuStatusIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_STATUS_IND = 0x4F0C */
  ApiTerminalIdType BusyDeviceNr;       /*!< The id of the device being updated
                                           currently. 0xFFFF is used if no device is active. */
  rsuint8 StatusLength;                 /*!< Size of Status[]. */
  rsuint8
 Status[1];                   /*!< The FWU status of each device in the
                                           system. */
} ApiFpFwuStatusIndType;

/*! This mail is used by the FWU Manager in the FP to request the CRC for a
   set FW block from the FWU Provider in the FP application. */
typedef struct ApiFpFwuMultiCrcIndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_MULTI_CRC_IND = 0x4F0D */
  ApiTerminalIdType DeviceNr;           /*!< Device number. 0 = FP  (1..n=PP's) */
  rsuint32 PrvContext;                  /*!< Provider context; identifies the FWU
                                           session. */
  rsuint32 Address;                     /*!< Current address. */
  rsuint8 CrcSizesCount;                /*!< The number of CRC sizes. */
  rsuint16 CrcSizes[1];                 /*!< Array holding the size of each block to
                                           caculate CRC over. The size of CrcSizes[] is
                                           CrcSizesCount*sizeof (rsuint16). */
} ApiFpFwuMultiCrcIndType;

/*! This mail is used by the FWU Provider in the FP application to return
   the requested CRC to the FWU Manager in the FP. */
typedef struct ApiFpFwuMultiCrcResType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_MULTI_CRC_RES = 0x4F0E */
  ApiTerminalIdType DeviceNr;           /*!< Device number. 0 = FP  (1..n=PP's) */
  rsuint32 PrvContext;                  /*!< Provider context; identifies the FWU
                                           session. */
  rsuint32 Address;                     /*!< Address. */
  rsuint8 CrcsCount;                    /*!< The number of CRC results. */
  ApiFwuCrcType Crcs[1];                /*!< Array holding the CRC result of each block.
                                           
The size of Crcs[] is CrcsCount*sizeof
                                           (ApiFwuCrcType). */
} ApiFpFwuMultiCrcResType;

/*! This command is used to enable/disable features in the FWU API.
    Enabling/disabling of extended terminal id will also affect all other APIs
   using TerminalId. */
typedef struct ApiFpFwuFeaturesReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_FEATURES_REQ = 0x4F10 */
  ApiFwuFeatureType ApiFwuFeature;      /*!< Requested features */
} ApiFpFwuFeaturesReqType;

/*! This command confirms the new feature settings. */
typedef struct ApiFpFwuFeaturesCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_FEATURES_CFM = 0x4F11 */
  RsStatusType Status;
  ApiFwuFeatureType ApiFwuFeature;      /*!< Supported features */
} ApiFpFwuFeaturesCfmType;

#if (RTX_CORE_VERSION >= 0x0224)
  #include <Standard/Common/RsPopPack.h>
#else
  #pragma pack(pop)
#endif

#ifdef __cplusplus
extern "C"
{
#endif
/** \cond internal */

/****************************************************************************
*     Function prototypes for mail packaging and sending(MPS) functions
****************************************************************************/

/****************************************************************************
* FUNCTION:      SendApiFpFwuEnableReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_FWU_ENABLE_REQ = 0x4F00
****************************************************************************/
void SendApiFpFwuEnableReq ( RosTaskIdType Src,
                             rsuint8 Enable,                 /*!< 1: The FWU manger is enabled.
                                                                0: The FWU manger is
                                                                disabled. */
                             ApiFwuFeaturesType Features);   /*!< Feature set supported
                                                                by the host application. */

/****************************************************************************
* FUNCTION:      SendApiFpFwuUpdateReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_FWU_UPDATE_REQ = 0x4F03
****************************************************************************/
void SendApiFpFwuUpdateReq ( RosTaskIdType Src,
                             ApiTerminalIdType DeviceNr,     /*!< Device number. 0 = 0 =
                                                                FP  (1..n=PP's) */
                             ApiFwuModeType FwuMode);        /*!< FWU Mode. */

/****************************************************************************
* FUNCTION:      SendApiFpFwuUpdateRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_FWU_UPDATE_RES = 0x4F06
****************************************************************************/
void SendApiFpFwuUpdateRes ( RosTaskIdType Src,
                             ApiTerminalIdType DeviceNr,     /*!< Device number. 0 = FP 
                                                                (1..n=PP's) */
                             rsuint8 LinkDate[5],            /*!< Link date for current
                                                                area. */
                             rsuint32 PrvContext,            /*!< Provider context. Used
                                                                in all subsequent mails to
                                                                identify the FWU update
                                                                sessions. */
                             rsuint32 RangesCount,           /*!< The number of FWU
                                                                ranges. */
                             ApiFwuRangeType Ranges[1]);     /*!< Array holding the
                                                                address and size of each
                                                                block range. The size of
                                                                Ranges[] is
                                                                RangesCount*sizeof
                                                                (RtxFwuRangeType). */

/****************************************************************************
* FUNCTION:      SendApiFpFwuGetBlockRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_FWU_GET_BLOCK_RES = 0x4F08
****************************************************************************/
void SendApiFpFwuGetBlockRes ( RosTaskIdType Src,
                               ApiTerminalIdType DeviceNr,   /*!< Device number. 0 = FP 
                                                                (1..n=PP's) */
                               rsuint32 PrvContext,          /*!< Provider context;
                                                                identifies the FWU session. */
                               rsuint32 Address,             /*!< Current address. */
                               rsuint32 DataLength,          /*!< Size of data. */
                               rsuint8 Data[1]);             /*!< DataLength bytes of FW
                                                                data. */

/****************************************************************************
* FUNCTION:      SendApiFpFwuGetCrcRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_FWU_GET_CRC_RES = 0x4F0A
****************************************************************************/
void SendApiFpFwuGetCrcRes ( RosTaskIdType Src,
                             ApiTerminalIdType DeviceNr,     /*!< Device number. 0 = FP 
                                                                (1..n=PP's) */
                             rsuint32 PrvContext,            /*!< Provider context;
                                                                identifies the FWU session. */
                             rsuint32 Address,               /*!< Address. */
                             rsuint32 Size,                  /*!< Size of block CRC?ed. */
                             rsuint16 Crc);                  /*!< CRC. */

/****************************************************************************
* FUNCTION:      SendApiFpFwuMultiCrcRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_FWU_MULTI_CRC_RES = 0x4F0E
****************************************************************************/
void SendApiFpFwuMultiCrcRes ( RosTaskIdType Src,
                               ApiTerminalIdType DeviceNr,   /*!< Device number. 0 = FP 
                                                                (1..n=PP's) */
                               rsuint32 PrvContext,          /*!< Provider context;
                                                                identifies the FWU session. */
                               rsuint32 Address,             /*!< Address. */
                               rsuint8 CrcsCount,            /*!< The number of CRC
                                                                results. */
                               ApiFwuCrcType Crcs[1]);       /*!< Array holding the CRC
                                                                result of each block. 
The
                                                                size of Crcs[] is
                                                                CrcsCount*sizeof
                                                                (ApiFwuCrcType). */

/****************************************************************************
* FUNCTION:      SendApiFpFwuFeaturesReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_FWU_FEATURES_REQ = 0x4F10
****************************************************************************/
void SendApiFpFwuFeaturesReq ( RosTaskIdType Src,
                               ApiFwuFeatureType ApiFwuFeature);
                                                             /*!< Requested features */

/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APIFPFWU_H */


