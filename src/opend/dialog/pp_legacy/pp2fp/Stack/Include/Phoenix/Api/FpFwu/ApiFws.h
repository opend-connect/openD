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
* Definition of the ApiFws interface.
*/


#ifndef APIFWS_H
#define APIFWS_H

/****************************************************************************
*                               Include files
****************************************************************************/
/*! Include of API configuration. */
#include <Api/ApiCfg.h>

/****************************************************************************
*                               Macros/Defines
****************************************************************************/

/*! API internal usage. */
#ifndef APIFWS_TASK
  #define APIFWS_TASK API_TASK
#endif

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

#if (RTX_CORE_VERSION >= 0x0224)
  #include <Standard/Common/RsPushPack1.h>
#else
  #pragma pack(push,1)
#endif

/* Mail primitives:
  API_FWS_INIT_REQ = 0x4F80,
  API_FWS_INIT_CFM = 0x4F81,
  API_FWS_TERMINATE_REQ = 0x4F82,
  API_FWS_TERMINATE_CFM = 0x4F83,
  API_FWS_STATUS_IND = 0x4F84,
  API_FWS_INFO_IND = 0x4F85,
  API_FWS_WRITE_REQ = 0x4F86,
  API_FWS_WRITE_CFM = 0x4F87,
  API_FWS_WRITE_EXT_DATA_REQ = 0x4F88,
  API_FWS_WRITE_EXT_DATA_CFM = 0x4F89,
End of mail primitives. */


/*! This enum identifies the different modes supported by the FWS
   implementation. */
typedef enum RSENUMTAG(ApiFwsStatusType)
{
  AF_STATUS_IDLE     = 0x00, /*!< Idle; ready to receive new FW. */
  AF_STATUS_RESUME   = 0x01, /*!< Idle; but ready to continue previous interrupted FW
                                download. */
  AF_STATUS_ERASING  = 0x02, /*!< Erasing the area of the FLASH where the new FW data
                                will be written. */
  AF_STATUS_WRITING  = 0x03, /*!< Writing FW data to FLASH */
  AF_STATUS_CHECKING = 0x04, /*!< Checking the check sum (MD5) of the data written to
                                the FLASH. */
  AF_STATUS_BOOTING  = 0x05, /*!< Rebooting; FW download done successfully. */
  AF_STATUS_DONE     = 0x06, /*!< FW download done successfully. The application should
                                reboot when ready. */
  AF_STATUS_FAILED   = 0x07, /*!< FW download failed. */
  AF_STATUS_INVALID  = 0xFF  /*!< Invalid. */
} RSENUM8(ApiFwsStatusType);

/*! This type is used to hold a GUID. */
#ifndef APITYPES_H
typedef struct
{
  rsuint32 Data1;                       /*!< Part 1 */
  rsuint16 Data2;                       /*!< Part 2 */
  rsuint16 Data3;                       /*!< Part 3 */
  rsuint8 Data4[8];                     /*!< Part 4 */
} ApiGuidType;
#endif


/*! Mail without parameters. */
typedef struct ApifwsEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} ApifwsEmptySignalType;

/*! This mail is used to initialise the FWS handler. */
typedef struct ApiFwsInitReqType
{
  RosPrimitiveType Primitive;            /*!< API_FWS_INIT_REQ = 0x4F80 */
  rsbool ResetWhenDone;                 /*!< Set to TRUE if the FWS task should reset
                                           the device when a complete FW has been written
                                           successfully. Set to FALSE if the application
                                           will reboot the device (Needed if e.g. the
                                           application must close data connection before
                                           reset, or notify someone before the reset.). */
} ApiFwsInitReqType;

/*! This mail is used to confirm API_FWS_INIT_CFM. */
typedef struct ApiFwsInitCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FWS_INIT_CFM = 0x4F81 */
  RsStatusType Status;                  /*!< RSS_SUCCESS if the FWS module is ready to
                                           handle / write new FW. */
  rsuint16 MaxMsgSize;                  /*!< Maximum size of an API message. */
} ApiFwsInitCfmType;

/*! This mail is used to request the FWS handler to clean-up and free all
   resources. Used if FW download is interrupted or cancelled. A new
   API_FWS_INIT_REQ must be sent before a new FW download is started. This
   mail is also used to reboot the system when the application is ready in the
   case where the API_FWS_INIT_REQ mail is sent with ResetWhenDone = FALSE. */
typedef struct ApiFwsTerminateReqType
{
  RosPrimitiveType Primitive;            /*!< API_FWS_TERMINATE_REQ = 0x4F82 */
  rsbool Boot;                          /*!< Set to TRUE if the FWS task should reboot
                                           the system to execute/commit the new FW. */
} ApiFwsTerminateReqType;

/*! This mail is used to confirm API_FWS_TERMIATE_REQ. */
typedef struct ApiFwsTerminateCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FWS_TERMINATE_CFM = 0x4F83 */
  RsStatusType Status;                  /*!< Status. */
} ApiFwsTerminateCfmType;

/*! This mail is used to inform the application about the current
   state/status of the FWS module, and to report the progress of the FWS write
   process. */
typedef struct ApiFwsStatusIndType
{
  RosPrimitiveType Primitive;            /*!< API_FWS_STATUS_IND = 0x4F84 */
  ApiFwsStatusType FwsStatus;           /*!< Current status/state of the FWS module. */
  rsuint32 Progress;                    /*!< The numbers of bytes read/processed from
                                           the .fws file. The offset of the next byte
                                           expected if FwsStatus = AF_STATUS_RESUME. */
} ApiFwsStatusIndType;

/*! This mail is used to inform the application about the current FW
   version etc. */
typedef struct ApiFwsInfoIndType
{
  RosPrimitiveType Primitive;            /*!< API_FWS_INFO_IND = 0x4F85 */
  ApiGuidType Guid;                     /*!< The id of the device. */
  rsuint32 ImageId;                     /*!< The image ID can be used to distinguish
                                           between the different images in a system where
                                           the FW is spilt in multiple images. E.g. in
                                           system having one image with the main program and
                                           another with the CoLA image. */
  rsuint8 LinkDate[5];                  /*!< The link date of the current FW in the
                                           device. */
  rsuint8 NameLength;                   /*!< The length of Name[] */
  rsuint8 Name[1];                      /*!< The name of the application/device. */
} ApiFwsInfoIndType;

/*! This mail is used to write FWS file data to the FWS handler. */
typedef struct ApiFwsWriteReqType
{
  RosPrimitiveType Primitive;            /*!< API_FWS_WRITE_REQ = 0x4F86 */
  rsuint32 Offset;                      /*!< The offset of this data block in the .fws
                                           file. */
  rsuint32 Length;                      /*!< The length of data in bytes */
  rsuint8* DataPtr;                     /*!< Pointer to the data to write. The data must
                                           be available to API_FWS_WRITE_CFM is received. */
} ApiFwsWriteReqType;

/*! This mail is sent to the application when the data has been processed. */
typedef struct ApiFwsWriteCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FWS_WRITE_CFM = 0x4F87 */
  RsStatusType Status;                  /*!< Status. */
} ApiFwsWriteCfmType;

/*! This mail is used to write FWS file data to the FWS handler. A copy of
   the data is included in the mail, making it possible to use this mail from
   an application not sharing the memory space with the FWS handler. This mail
   is e.g. used when writing a *.fws file from a PC to a device via the RTX
   Embedded Access Interface (RtxEai). */
typedef struct ApiFwsWriteExtDataReqType
{
  RosPrimitiveType Primitive;            /*!< API_FWS_WRITE_EXT_DATA_REQ = 0x4F88 */
  rsuint32 Offset;                      /*!< The offset of this data block in the .fws
                                           file. */
  rsuint8 Length;                       /*!< The length of data in bytes */
  rsuint8 Data[1];                      /*!< The data to write. */
} ApiFwsWriteExtDataReqType;

/*! This mail is sent to the application when the data has been processed. */
typedef struct ApiFwsWriteExtDataCfmType
{
  RosPrimitiveType Primitive;            /*!< API_FWS_WRITE_EXT_DATA_CFM = 0x4F89 */
  RsStatusType Status;                  /*!< Status. */
} ApiFwsWriteExtDataCfmType;

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
* FUNCTION:      SendApiFwsInitReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FWS_INIT_REQ = 0x4F80
****************************************************************************/
void SendApiFwsInitReq ( RosTaskIdType Src,
                         rsbool ResetWhenDone);              /*!< Set to TRUE if the FWS
                                                                task should reset the device
                                                                when a complete FW has been
                                                                written successfully. Set to
                                                                FALSE if the application
                                                                will reboot the device
                                                                (Needed if e.g. the
                                                                application must close data
                                                                connection before reset, or
                                                                notify someone before the
                                                                reset.). */

/****************************************************************************
* FUNCTION:      SendApiFwsTerminateReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FWS_TERMINATE_REQ = 0x4F82
****************************************************************************/
void SendApiFwsTerminateReq ( RosTaskIdType Src,
                              rsbool Boot);                  /*!< Set to TRUE if the FWS
                                                                task should reboot the
                                                                system to execute/commit the
                                                                new FW. */

/****************************************************************************
* FUNCTION:      SendApiFwsWriteReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FWS_WRITE_REQ = 0x4F86
****************************************************************************/
void SendApiFwsWriteReq ( RosTaskIdType Src,
                          rsuint32 Offset,                   /*!< The offset of this
                                                                data block in the .fws file. */
                          rsuint32 Length,                   /*!< The length of data in
                                                                bytes */
                          rsuint8* DataPtr);                 /*!< Pointer to the data to
                                                                write. The data must be
                                                                available to
                                                                API_FWS_WRITE_CFM is
                                                                received. */

/****************************************************************************
* FUNCTION:      SendApiFwsWriteExtDataReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_FWS_WRITE_EXT_DATA_REQ = 0x4F88
****************************************************************************/
void SendApiFwsWriteExtDataReq ( RosTaskIdType Src,
                                 rsuint32 Offset,            /*!< The offset of this
                                                                data block in the .fws file. */
                                 rsuint8 Length,             /*!< The length of data in
                                                                bytes */
                                 rsuint8 Data[1]);           /*!< The data to write. */

/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APIFWS_H */


