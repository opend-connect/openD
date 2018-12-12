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
* Definition of the ApiLinux interface.
*/


#ifndef APILINUX_H
#define APILINUX_H

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

//#if (RTX_CORE_VERSION >= 0x0224)
//  #include <Standard/Common/RsPushPack1.h>
//#else
//  #pragma pack(push,1)
//#endif

/* Mail primitives:
  API_LINUX_INIT_GET_SYSTEM_INFO_REQ = 0x4700,
  API_LINUX_INIT_GET_SYSTEM_INFO_CFM = 0x4701,
  API_LINUX_INIT_REQ = 0x4702,
  API_LINUX_INIT_CFM = 0x4703,
  API_LINUX_NVS_UPDATE_IND = 0x4704,
  API_LINUX_INTERNAL_ERROR_IND = 0x4705,
End of mail primitives. */



/*! This enum identifies the linux kernel driver error codes. */
typedef enum RSENUMTAG(ApiLinuxErrorCodeType)
{
  API_LINUX_EC_SUCCES         = 0x00, /*!< Command was successfully executed */
  API_LINUX_EC_WRONG_NVS_SIZE = 0x01, /*!< Initialization failed due to incorrect NVS
                                         size. */
  API_LINUX_EC_ISR_TOO_SLOW   = 0x02  /*!< ISR was serviced too slow. */
} RSENUM8(ApiLinuxErrorCodeType);


/*! Mail without parameters. */
typedef struct ApilinuxEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} ApilinuxEmptySignalType;

/*! This mail is used by the application to retrieve information from the
   DECT driver before it is initialized. 
    NB: This mail can be sent before the system is initialized. */
typedef ApilinuxEmptySignalType ApiLinuxInitGetSystemInfoReqType;

/*! The mail contains important information about the DECT driver that must
   be used by the application in ordet to initialize the system correctly. */
typedef struct ApiLinuxInitGetSystemInfoCfmType
{
  RosPrimitiveType Primitive;            /*!< API_LINUX_INIT_GET_SYSTEM_INFO_CFM = 0x4701 */
  rsuint32 NvsSize;                     /*!< Size of the NVS */
  rsuint16 MaxMailSize;                 /*!< Maximum size of API mails */
} PACKED_STRUCT ApiLinuxInitGetSystemInfoCfmType;

/*! This mail is used by the application to start the DECT driver. The mail
   contains the NVS data stored by the DECT driver during earlier uses (See API_LINUX_NVS_UPDATE_IND).
    
    NB:
    This mail must be sent as the first after driver load. Until it is sent
   all other mails will be ignored. 
    This mail can only be sent once.  
    The MaxMailSize limitation does not apply to this mail. */
typedef struct ApiLinuxInitReqType
{
  RosPrimitiveType Primitive;            /*!< API_LINUX_INIT_REQ = 0x4702 */
  rsuint32 LengthOfData;                /*!< Length of the NVS data. This must be
                                           exactly the same size as indicated in
                                           API_LINUX_INIT_GET_SYSTEM_INFO_CFM or
                                           0 if this is the first time the DECT driver is
                                           used. In case the length is set to 0 the DECT
                                           driver will set all NVS values to their default values.
                                           
                                           All other lengths will make the initialization
                                           fail. */
  rsuint8 Data[1];                      /*!< NVS Data. */
} PACKED_STRUCT ApiLinuxInitReqType;

/*! The mail contains information about the addresses of the voice channel
   buffers used by the device driver. */
typedef struct ApiLinuxInitCfmType
{
  RosPrimitiveType Primitive;            /*!< API_LINUX_INIT_CFM = 0x4703 */
  ApiLinuxErrorCodeType Status;         /*!< Indicates whether the command succeeded or
                                           not. */
} PACKED_STRUCT ApiLinuxInitCfmType;

/*! This mail is sent from the DECT driver, when changes have to be stored
   in NVS. The application must save the data in order to supply it the next
   time the DECT driver is initialized with API_LINUX_INIT_REQ. There is no
   confirmation mail. 
     */
typedef struct ApiLinuxNvsUpdateIndType
{
  RosPrimitiveType Primitive;            /*!< API_LINUX_NVS_UPDATE_IND = 0x4704 */
  rsuint32 NvsOffset;                   /*!< Offset into NVS to store this data. */
  rsuint16 NvsDataLength;               /*!< Length of NvsData field. */
  rsuint8 NvsData[1];                   /*!< Variable length data contains length bytes
                                           of NVS data to be stored. */
} PACKED_STRUCT ApiLinuxNvsUpdateIndType;

/*! This mail is sent from the DECT driver, in case of critical internal
   errors. See the error code for additional information 
     */
typedef struct ApiLinuxInternalErrorIndType
{
  RosPrimitiveType Primitive;            /*!< API_LINUX_INTERNAL_ERROR_IND = 0x4705 */
  ApiLinuxErrorCodeType ErrorCode;      /*!< Error code. */
} PACKED_STRUCT ApiLinuxInternalErrorIndType;

//#if (RTX_CORE_VERSION >= 0x0224)
//  #include <Standard/Common/RsPopPack.h>
//#else
//  #pragma pack(pop)
//#endif

#ifdef __cplusplus
extern "C"
{
#endif
/** \cond internal */

/****************************************************************************
*     Function prototypes for mail packaging and sending(MPS) functions
****************************************************************************/

/****************************************************************************
* FUNCTION:      SendApiLinuxInitGetSystemInfoReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LINUX_INIT_GET_SYSTEM_INFO_REQ = 0x4700
****************************************************************************/
void SendApiLinuxInitGetSystemInfoReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiLinuxInitReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LINUX_INIT_REQ = 0x4702
****************************************************************************/
void SendApiLinuxInitReq ( RosTaskIdType Src,
                           rsuint32 LengthOfData,            /*!< Length of the NVS
                                                                data. This must be exactly
                                                                the same size as indicated
                                                                in
                                                                API_LINUX_INIT_GET_SYSTEM_INF
                                                                O_CFM or
                                                                0 if this is the first time
                                                                the DECT driver is used. In
                                                                case the length is set to 0
                                                                the DECT driver will set all
                                                                NVS values to their default values.
                                                                
                                                                All other lengths will make
                                                                the initialization fail. */
                           rsuint8 Data[1]);                 /*!< NVS Data. */

/****************************************************************************
* FUNCTION:      SendApiLinuxNvsUpdateInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LINUX_NVS_UPDATE_IND = 0x4704
****************************************************************************/
void SendApiLinuxNvsUpdateInd ( RosTaskIdType Src,
                                rsuint32 NvsOffset,          /*!< Offset into NVS to
                                                                store this data. */
                                rsuint16 NvsDataLength,      /*!< Length of NvsData
                                                                field. */
                                rsuint8 NvsData[1]);         /*!< Variable length data
                                                                contains length bytes of NVS
                                                                data to be stored. */

/****************************************************************************
* FUNCTION:      SendApiLinuxInternalErrorInd
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_LINUX_INTERNAL_ERROR_IND = 0x4705
****************************************************************************/
void SendApiLinuxInternalErrorInd ( RosTaskIdType Src,
                                    ApiLinuxErrorCodeType ErrorCode);
                                                             /*!< Error code. */

/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APILINUX_H */


