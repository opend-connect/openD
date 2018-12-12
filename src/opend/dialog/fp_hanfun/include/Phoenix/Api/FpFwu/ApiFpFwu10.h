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
* Definition of the ApiFpFwu10 interface.
*/


#ifndef APIFPFWU10_H
#define APIFPFWU10_H

/****************************************************************************
*                               Include files
****************************************************************************/
/*! The following API files must be included. */
//#include <Api/ApiCfg.h>

#include <Phoenix/Api/Types/ApiTypes.h>

/****************************************************************************
*                               Macros/Defines
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

#if (RTX_CORE_VERSION >= 0x0224)
  #include <Standard/Common/RsPushPack1.h>
#else
  #pragma pack(push,1)
#endif

/* Mail primitives:
  API_FP_FWU_DEVICE_NOTIFY10_IND = 0x4F02,
  API_FP_FWU_UPDATE10_REQ = 0x4F03,
  API_FP_FWU_UPDATE10_CFM = 0x4F04,
  API_FP_FWU_UPDATE10_IND = 0x4F05,
  API_FP_FWU_UPDATE10_RES = 0x4F06,
  API_FP_FWU_GET_BLOCK10_IND = 0x4F07,
  API_FP_FWU_GET_BLOCK10_RES = 0x4F08,
  API_FP_FWU_GET_CRC10_IND = 0x4F09,
  API_FP_FWU_GET_CRC10_RES = 0x4F0A,
  API_FP_FWU_STATUS10_IND = 0x4F0C,
  API_FP_FWU_MULTI_CRC10_IND = 0x4F0D,
  API_FP_FWU_MULTI_CRC10_RES = 0x4F0E,
End of mail primitives. */




/*! Mail without parameters. */
typedef struct Apifpfwu10EmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} Apifpfwu10EmptySignalType;

/*! This mail is used by the FWU Manager in the FP to inform the FWU
   Provider about the devices available for FW download. Only one device, the
   FP module self, is supported in this implementation. */
typedef struct ApiFpFwuDeviceNotify10IndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_DEVICE_NOTIFY10_IND = 0x4F02 */
  rsuint8 Present;                      /*!< 0: absent 
                                           1: present */
  rsuint8 DeviceNr;                     /*!< Device number. 0 = FP  (1..n=PP's) */
  rsuint32 DeviceId;                    /*!< Unique device id. */
  rsuint32 TargetData;                  /*!< Information block offset in area. */
  ApiFwuModeType FwuMode;               /*!< FWU Mode. */
  rsuint8 LinkDate[5];                  /*!< The link date of the current FW in the
                                           device. */
  ApiFwuRangeType Range;                /*!< The start address and the size of the FW in
                                           the target device. */
} PACKED_STRUCT ApiFpFwuDeviceNotify10IndType;

/*! This mail is used by the FWU Provider in the FP application to inform
   the FWU manager in the FP that a new FW is available for the device
   specified. */
typedef struct ApiFpFwuUpdate10ReqType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_UPDATE10_REQ = 0x4F03 */
  rsuint8 DeviceNr;                     /*!< Device number. 0 = 0 = FP  (1..n=PP's) */
  ApiFwuModeType FwuMode;               /*!< FWU Mode. */
} PACKED_STRUCT ApiFpFwuUpdate10ReqType;

/*! This mail is used by the FP to confirm the API_FP_FWU_UPDATE_REQ
   command. */
typedef struct ApiFpFwuUpdate10CfmType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_UPDATE10_CFM = 0x4F04 */
  rsuint8 DeviceNr;                     /*!< Device number. 0 = FP  (1..n=PP's) */
  RsStatusType Status;                  /*!< Indicates whether the command succeeded or
                                           not. */
} PACKED_STRUCT ApiFpFwuUpdate10CfmType;

/*! This mail is used by the FWU Manager in the FP to request information
   about the new FW available for the device specified. */
typedef struct ApiFpFwuUpdate10IndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_UPDATE10_IND = 0x4F05 */
  rsuint8 DeviceNr;                     /*!< Device number. 0 = FP  (1..n=PP's) */
  rsuint32 DeviceId;                    /*!< Unique device id. */
  rsuint32 TargetData;                  /*!< Information block offset in area. */
  ApiFwuModeType FwuMode;               /*!< FWU Mode. */
  rsuint8 LinkDate[5];                  /*!< The link date of the current FW in the
                                           device. */
  ApiFwuRangeType Range;                /*!< The start address and the size of the FW in
                                           the target. */
} PACKED_STRUCT ApiFpFwuUpdate10IndType;

/*! This mail is used by the FWU Provider in the FP to return FW
   information to the FWU Manager in the FP. */
typedef struct ApiFpFwuUpdate10ResType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_UPDATE10_RES = 0x4F06 */
  rsuint8 DeviceNr;                     /*!< Device number. 0 = FP  (1..n=PP's) */
  rsuint8 LinkDate[5];                  /*!< Link date for current area. */
  rsuint32 PrvContext;                  /*!< Provider context. Used in all subsequent
                                           mails to identify the FWU update sessions. */
  rsuint32 RangesCount;                 /*!< The number of FWU ranges. */
  ApiFwuRangeType Ranges[1];            /*!< Array holding the address and size of each
                                           block range. The size of Ranges[] is
                                           RangesCount*sizeof (RtxFwuRangeType). */
} PACKED_STRUCT ApiFpFwuUpdate10ResType;

/*! This mail is used by the FWU Manager in the FP to request a FW block
   from the FWU Provider in the FP application . */
typedef struct ApiFpFwuGetBlock10IndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_GET_BLOCK10_IND = 0x4F07 */
  rsuint8 DeviceNr;                     /*!< Device number. 0 = FP  (1..n=PP's) */
  rsuint32 PrvContext;                  /*!< Provider context; identifies the FWU
                                           session. */
  rsuint32 Address;                     /*!< Current address. */
  rsuint32 Size;                        /*!< Max size of returned block. */
} PACKED_STRUCT ApiFpFwuGetBlock10IndType;

/*! This mail is used by the FWU Provider in the FP application to return a
   FW block to the FWU Manager in the FP. */
typedef struct ApiFpFwuGetBlock10ResType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_GET_BLOCK10_RES = 0x4F08 */
  rsuint8 DeviceNr;                     /*!< Device number. 0 = FP  (1..n=PP's) */
  rsuint32 PrvContext;                  /*!< Provider context; identifies the FWU
                                           session. */
  rsuint32 Address;                     /*!< Current address. */
  rsuint32 DataLength;                  /*!< Size of data. */
  rsuint8 Data[1];                      /*!< DataLength bytes of FW data. */
} PACKED_STRUCT ApiFpFwuGetBlock10ResType;

/*! This mail is used by the FWU Manager in the FP to request the CRC for a
   FW block from the FWU Provider in the FP application. */
typedef struct ApiFpFwuGetCrc10IndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_GET_CRC10_IND = 0x4F09 */
  rsuint8 DeviceNr;                     /*!< Device number. 0 = FP  (1..n=PP's) */
  rsuint32 PrvContext;                  /*!< Provider context; identifies the FWU
                                           session. */
  rsuint32 Address;                     /*!< Current address. */
  rsuint32 Size;                        /*!< Max size of block CRC?ed. */
} PACKED_STRUCT ApiFpFwuGetCrc10IndType;

/*! This mail is used by the FWU Provider in the FP application to return
   the requested CRC to the FWU Manager in the FP. */
typedef struct ApiFpFwuGetCrc10ResType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_GET_CRC10_RES = 0x4F0A */
  rsuint8 DeviceNr;                     /*!< Device number. 0 = FP  (1..n=PP's) */
  rsuint32 PrvContext;                  /*!< Provider context; identifies the FWU
                                           session. */
  rsuint32 Address;                     /*!< Address. */
  rsuint32 Size;                        /*!< Size of block CRC?ed. */
  rsuint16 Crc;                         /*!< CRC. */
} PACKED_STRUCT ApiFpFwuGetCrc10ResType;

/*! The FWU Manager in the FP uses this mail to indicate the current status
   to the FWU Provider in the FP aplpication. The FP application does not have
   to handle this mail. */
typedef struct ApiFpFwuStatus10IndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_STATUS10_IND = 0x4F0C */
  rsuint8 BusyDeviceNr;                 /*!< The id of the device being updated
                                           currently. 0xFF is used if no device is active. */
  rsuint8 StatusLength;                 /*!< Size of Status[]. */
  rsuint8
 Status[1];                   /*!< The FWU status of each device in the
                                           system. */
} PACKED_STRUCT ApiFpFwuStatus10IndType;

/*! This mail is used by the FWU Manager in the FP to request the CRC for a
   set FW block from the FWU Provider in the FP application. */
typedef struct ApiFpFwuMultiCrc10IndType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_MULTI_CRC10_IND = 0x4F0D */
  rsuint8 DeviceNr;                     /*!< Device number. 0 = FP  (1..n=PP's) */
  rsuint32 PrvContext;                  /*!< Provider context; identifies the FWU
                                           session. */
  rsuint32 Address;                     /*!< Current address. */
  rsuint8 CrcSizesCount;                /*!< The number of CRC sizes. */
  rsuint16 CrcSizes[1];                 /*!< Array holding the size of each block to
                                           caculate CRC over. The size of CrcSizes[] is
                                           CrcSizesCount*sizeof (rsuint16). */
} PACKED_STRUCT ApiFpFwuMultiCrc10IndType;

/*! This mail is used by the FWU Provider in the FP application to return
   the requested CRC to the FWU Manager in the FP. */
typedef struct ApiFpFwuMultiCrc10ResType
{
  RosPrimitiveType Primitive;            /*!< API_FP_FWU_MULTI_CRC10_RES = 0x4F0E */
  rsuint8 DeviceNr;                     /*!< Device number. 0 = FP  (1..n=PP's) */
  rsuint32 PrvContext;                  /*!< Provider context; identifies the FWU
                                           session. */
  rsuint32 Address;                     /*!< Address. */
  rsuint8 CrcsCount;                    /*!< The number of CRC results. */
  ApiFwuCrcType Crcs[1];                /*!< Array holding the CRC result of each block.
                                           
The size of Crcs[] is CrcsCount*sizeof
                                           (ApiFwuCrcType). */
} PACKED_STRUCT ApiFpFwuMultiCrc10ResType;

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

/****************************************************************************
* FUNCTION:      SendApiFpFwuUpdate10Req
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_FWU_UPDATE10_REQ = 0x4F03
****************************************************************************/
void SendApiFpFwuUpdate10Req ( RosTaskIdType Src,
                               rsuint8 DeviceNr,             /*!< Device number. 0 = 0 =
                                                                FP  (1..n=PP's) */
                               ApiFwuModeType FwuMode);      /*!< FWU Mode. */

/****************************************************************************
* FUNCTION:      SendApiFpFwuUpdate10Res
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_FWU_UPDATE10_RES = 0x4F06
****************************************************************************/
void SendApiFpFwuUpdate10Res ( RosTaskIdType Src,
                               rsuint8 DeviceNr,             /*!< Device number. 0 = FP 
                                                                (1..n=PP's) */
                               rsuint8 LinkDate[5],          /*!< Link date for current
                                                                area. */
                               rsuint32 PrvContext,          /*!< Provider context. Used
                                                                in all subsequent mails to
                                                                identify the FWU update
                                                                sessions. */
                               rsuint32 RangesCount,         /*!< The number of FWU
                                                                ranges. */
                               ApiFwuRangeType Ranges[1]);   /*!< Array holding the
                                                                address and size of each
                                                                block range. The size of
                                                                Ranges[] is
                                                                RangesCount*sizeof
                                                                (RtxFwuRangeType). */

/****************************************************************************
* FUNCTION:      SendApiFpFwuGetBlock10Res
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_FWU_GET_BLOCK10_RES = 0x4F08
****************************************************************************/
void SendApiFpFwuGetBlock10Res ( RosTaskIdType Src,
                                 rsuint8 DeviceNr,           /*!< Device number. 0 = FP 
                                                                (1..n=PP's) */
                                 rsuint32 PrvContext,        /*!< Provider context;
                                                                identifies the FWU session. */
                                 rsuint32 Address,           /*!< Current address. */
                                 rsuint32 DataLength,        /*!< Size of data. */
                                 rsuint8 Data[1]);           /*!< DataLength bytes of FW
                                                                data. */

/****************************************************************************
* FUNCTION:      SendApiFpFwuGetCrc10Res
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_FWU_GET_CRC10_RES = 0x4F0A
****************************************************************************/
void SendApiFpFwuGetCrc10Res ( RosTaskIdType Src,
                               rsuint8 DeviceNr,             /*!< Device number. 0 = FP 
                                                                (1..n=PP's) */
                               rsuint32 PrvContext,          /*!< Provider context;
                                                                identifies the FWU session. */
                               rsuint32 Address,             /*!< Address. */
                               rsuint32 Size,                /*!< Size of block CRC?ed. */
                               rsuint16 Crc);                /*!< CRC. */

/****************************************************************************
* FUNCTION:      SendApiFpFwuMultiCrc10Res
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FP_FWU_MULTI_CRC10_RES = 0x4F0E
****************************************************************************/
void SendApiFpFwuMultiCrc10Res ( RosTaskIdType Src,
                                 rsuint8 DeviceNr,           /*!< Device number. 0 = FP 
                                                                (1..n=PP's) */
                                 rsuint32 PrvContext,        /*!< Provider context;
                                                                identifies the FWU session. */
                                 rsuint32 Address,           /*!< Address. */
                                 rsuint8 CrcsCount,          /*!< The number of CRC
                                                                results. */
                                 ApiFwuCrcType Crcs[1]);     /*!< Array holding the CRC
                                                                result of each block. 
The
                                                                size of Crcs[] is
                                                                CrcsCount*sizeof
                                                                (ApiFwuCrcType). */

/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APIFPFWU10_H */


