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

#ifndef RTX_EAI_H
#define RTX_EAI_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <RtxEai/RtxEaiCfg.h>
#include <RtxEai/RtxEap.h>
#include <DevDrv/Classes/SerCom/DrvClassSerCom.h>

/****************************************************************************
*                              Macro definitions
****************************************************************************/
#define RTX_EAI_LOG_INPUT_MAIL     0x01
#define RTX_EAI_LOG_OUTPUT_MAIL    0x02
#define RTX_EAI_LOG_TIMERS         0x04
#define RTX_EAI_LOG_HEAP           0x08
#define RTX_EAI_LOG_TASK_FUNCTIONS 0x10
#define RTX_EAI_LOG_PRINTF         0x20

// The following defines bit values that can be used to set the GraphConfig
// parameter to RtxEaiAddGraphEx():
#define RTX_EAI_AG_CONFIG_AUTO_SCALE BIT0
#define RTX_EAI_AG_CONFIG_X_PC_TIME  BIT1
#define RTX_EAI_AG_CONFIG_X_LINE0    BIT2

// The following defines bit values that can be used to set the Options
// parameter to RtxEaiAddGraphEx():
#define RTX_EAI_AG_OPTION_SIGNED BIT0

// The following defines bit values that can be used to set the Options
// parameter to RtxEaiAddLineToGraphEx():
#define RTX_EAI_ALTG_OPTION_FORCE_SIGNED   BIT0
#define RTX_EAI_ALTG_OPTION_FORCE_UNSIGNED BIT1
#define RTX_EAI_ALTG_OPTION_PLOT_DOTS      BIT2
#define RTX_EAI_ALTG_OPTION_PLOT_STAIRS    BIT3
#define RTX_EAI_ALTG_OPTION_PLOT_BINARY    BIT4


#ifndef RTX_EAI_MAIL2TX_SUPPORT
  #define RTX_EAI_MAIL2TX_SUPPORT 0
#endif

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/
typedef enum RtxEaiPowerStateType
{
  RTX_EAI_POWER_STATE_IDLE = 0x00,
  RTX_EAI_POWER_STATE_ACTIVE = 0x01
} RtxEaiPowerStateType;

typedef enum RtxEaiDriverOptionsType
{
  RTX_EAI_DRIVER_CFG_DEFAULT,  // Std. EAP framing. Used for e.g. UART and SPI
  RTX_EAI_DRIVER_CFG_USE_HDLC, // Std. EAP framing + HDLC. Used for e.g. UART and SPI
  RTX_EAI_DRIVER_CFG_NO_CRC    // Std. EAP framing, but no CRC. Used for e.g USB
} RtxEaiDriverOptionsType;

typedef struct RtxEaiDriverCfgType
{
  RtxEaiDriverOptionsType Option;
  const DrvClassSerCom_CmdDataType* (*GetDriverinterface)(void);
  void (*DriverReadyFct)(rsuint8 Instance);
} RtxEaiDriverCfgType;

#if (RTX_EAI_MAIL2TX_SUPPORT == 1)
typedef struct RtxEaiMail2TxType
{
  RosPrimitiveType Primitive; // RTX_EAI_MAIL2TX
  rsuint8 Instance;
  rsuint8 ProgramId;
  rsuint8 TaskId;
  RosMailType Mail;
} RtxEaiMail2TxType;
#endif

/****************************************************************************
*                           Global variables/const
****************************************************************************/
#ifdef RTX_EAI_LOG_TRACE_SUPPORT
  extern RTX_EAI_DATA_LOC rsuint8 RtxEaiLogOptions[RTX_EAI_NO_OF_TASKS];
  #ifdef RTX_EAI_NO_OF_LOG_PRIMITIVES
  extern RTX_EAI_DATA_LOC rsuint16 RtxEaiLogPrimitives[RTX_EAI_NO_OF_LOG_PRIMITIVES+1];
  #endif
  #ifdef RTX_EAI_NO_OF_EXCLUDE_PRIMITIVES
  extern RTX_EAI_DATA_LOC rsuint16 RtxEaiExcludePrimitives[RTX_EAI_NO_OF_EXCLUDE_PRIMITIVES+1];
  #endif
  extern RTX_EAI_DATA_LOC rsbool RtxEaiTraceStarted;
  extern RTX_EAI_DATA_LOC rsuint8 RtxEaiTraceProgramId;
  extern RTX_EAI_DATA_LOC rsuint8 RtxEaiTraceTaskId;
#endif


/****************************************************************************
*                             Function prototypes
****************************************************************************/


/****************************************************************************
*  FUNCTION: RtxEaiInit
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to initialise the RtxEai module.
****************************************************************************/
#ifdef RTX_EAI_SUPPORT
void RtxEaiInit(void);
#else
#undef RtxEaiInit
#define RtxEaiInit()
#endif

/****************************************************************************
*  FUNCTION: RtxEaiTerminate
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to terminate the RtxEai module.
****************************************************************************/
#ifdef RTX_EAI_SUPPORT
void RtxEaiTerminate(void);
#else
#undef RtxEaiTerminate
#define RtxEaiTerminate()
#endif

/****************************************************************************
*  FUNCTION: RtxEaiKick
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function can be used to kick the RTX EAI interface. This
*               can e.g. be used to kick the HW driver to deliver received
*               data to the RTX EAI module.
****************************************************************************/
#ifdef RTX_EAI_SUPPORT
void RtxEaiKick(void);
#else
#undef RtxEaiKick
#define RtxEaiKick()
#endif

/****************************************************************************
*  FUNCTION: RtxEaicommandHandler
*
*  INPUTS  : ProgramId: the ID of the mail originator
*            MailPtr
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function can be used by the application to forward a EAP
*               message to the RtxEai module.
****************************************************************************/
#ifdef RTX_EAI_SUPPORT
void RtxEaiCommandHandler(rsuint8 ProgramId, const rsuint8* MailPtr);
#else
#undef RtxEaiCommandHandler
#define RtxEaiCommandHandler(ProgramId, MailPtr)
#endif

/****************************************************************************
*  FUNCTION: RtxEaiSetInstance
*
*  INPUTS  : TaskId
*            Instance
*  OUTPUTS : none
*  RETURNS : none
*
*  DESCRIPTION: This function is used to set the RTX EAI driver instance used
*               for the task specified.
****************************************************************************/
void RtxEaiSetInstance(rsuint8 TaskId, rsuint8 Instance);

/****************************************************************************
*  FUNCTION: RtxEaiGetInstance
*
*  INPUTS  : TaskId
*  OUTPUTS : none
*  RETURNS : Instance
*
*  DESCRIPTION: This function is used to get the RTX EAI driver instance used
*               for the task specified.
****************************************************************************/
rsuint8 RtxEaiGetInstance(rsuint8 TaskId);


// "RtxEai Buffer API"
/****************************************************************************
*  FUNCTION: RtxEaiGetBuffer
*
*  INPUTS  : ProgramId specifies the destination application on the host.
*                      (Part of EAP payload header.)
*            TaskId specifies the destination task / thread in the host
*                   application. (Part of EAP payload header.)
*            Size specifies the requested buffer size.
*  OUTPUTS : none.
*  RETURNS : pointer to the buffer allocated (points to message part of EAP
*            packet). NULL is returned if the TX buffer is full.
*
*  DESCRIPTION: This function is used to allocate an TX buffer. The RtxEai is
*               responsible for the EAP framing. This function can be used to
*               send any EAP packet from any task in the system.
*               This function is e.g. used in the Bluetooth systems to send
*               debug information generated by the RTX Bluetooth Core to the
*               host.
****************************************************************************/
#ifdef RTX_EAI_SUPPORT
rsuint8 *RtxEaiGetBuffer(rsuint8 ProgramId, rsuint8 TaskId, rsuint16 Size);
#else
#undef RtxEaiGetBuffer
#define RtxEaiGetBuffer(ProgramId, TaskId, Size) NULL
#endif

/****************************************************************************
*  FUNCTION: RtxEaiGetBufferI
*
*  INPUTS  : Instance specifies the RTX EAI instance to use.
*            ProgramId specifies the destination application on the host.
*                      (Part of EAP payload header.)
*            TaskId specifies the destination task / thread in the host
*                   application. (Part of EAP payload header.)
*            Size specifies the requested buffer size.
*  OUTPUTS : none.
*  RETURNS : pointer to the buffer allocated (points to message part of EAP
*            packet). NULL is returned if the TX buffer is full.
*
*  DESCRIPTION: This function is used to allocate an TX buffer. The RtxEai is
*               responsible for the EAP framing. This function can be used to
*               send any EAP packet from any task in the system.
*               This function is e.g. used in the Bluetooth systems to send
*               debug information generated by the RTX Bluetooth Core to the
*               host.
****************************************************************************/
#ifdef RTX_EAI_SUPPORT
rsuint8 *RtxEaiGetBufferI(rsuint8 Instance, rsuint8 ProgramId, rsuint8 TaskId, rsuint16 Size);
#else
#undef RtxEaiGetBufferI
#define RtxEaiGetBufferI(Instance, ProgramId, TaskId, Size) NULL
#endif

/****************************************************************************
*  FUNCTION: RtxEaiDeliverBuffer()
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to send a buffer allocated by the
*               RtxEaiGetBuffer() function.
****************************************************************************/
#ifdef RTX_EAI_SUPPORT
void RtxEaiDeliverBuffer(rsuint8 *p);
#else
#undef RtxEaiDeliverBuffer
#define RtxEaiDeliverBuffer()
#endif

/****************************************************************************
*  FUNCTION: RtxEaiInternalDeliverBuffer()
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to send a buffer allocated by the
*               RtxEaiGetBuffer() function. Use this send function when the
*               mail primitive is assigned using
*               RTX_EAP_ASSIGN_UINT16. Primirily intended for EAI internal
*               use.
****************************************************************************/
#ifdef RTX_EAI_SUPPORT
#if RS_ENDIAN_TYPE == RS_BIG_ENDIAN
void RtxEaiInternalDeliverBuffer(rsuint8 *p);
#else
#define RtxEaiInternalDeliverBuffer RtxEaiDeliverBuffer
#endif
#endif

/****************************************************************************
*  FUNCTION: RtxEaiAllocTraceBuffer
*
*  INPUTS  : ProgramId specifies the destination application on the host.
*                      (Part of EAP payload header.)
*            TaskId specifies the destination task / thread in the host
*                   application. (Part of EAP payload header.)
*            Size specifies the requested buffer size.
*  OUTPUTS : none.
*  RETURNS : pointer to the buffer allocated (points to message part of EAP
*            packet). NULL is returned if the TX buffer is full.
*
*  DESCRIPTION: This function is used to allocate an space for a packet in the
*               TX trace buffer. The RtxEai is responsible for the EAP framing.
****************************************************************************/
#ifdef RTX_EAI_SUPPORT
rsuint8* RtxEaiAllocTraceBuffer(rsuint8 ProgramId, rsuint8 TaskId, rsuint16 Size);
#else
#undef RtxEaiAllocTraceBuffer
#define RtxEaiAllocTraceBuffer(ProgramId, TaskId, Size) NULL
#endif

/****************************************************************************
*  FUNCTION: RtxEaiDeliverTraceBuffer()
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to send a buffer allocated by the
*               RtxEaiAlocTraceBuffer() function.
****************************************************************************/
#ifdef RTX_EAI_SUPPORT
void RtxEaiDeliverTraceBuffer(rsuint8 *p);
#else
#undef RtxEaiDeliverTraceBuffer
#define RtxEaiDeliverTraceBuffer()
#endif

/****************************************************************************
*  FUNCTION: RtxEaiGetTxSpaceI
*
*  INPUTS  : Instance specifies the RTX EAI instance to use.
*  OUTPUTS : none.
*  RETURNS : Available TX buffer space.
*
*  DESCRIPTION: This function is used to query the available TX buffer space.
****************************************************************************/
#ifdef RTX_EAI_SUPPORT
rsuint32 RtxEaiGetTxSpaceI(rsuint8 Instance);
#else
#undef RtxEaiGetTxSpaceI
#define RtxEaiGetTxSpaceI(Instance) 0
#endif

/****************************************************************************
*  FUNCTION: RtxEaiTxBufferEmptyI
*
*  INPUTS  : Instance specifies the RTX EAI instance to use.
*  OUTPUTS : none.
*  RETURNS : true if tx buffer is empty, false if messages ar still pending.
*
*  DESCRIPTION: This function is used to query the state of the TX buffer.
****************************************************************************/
#ifdef RTX_EAI_SUPPORT
rsbool RtxEaiTxBufferEmptyI(rsuint8 Instance);
#else
#undef RtxEaiTxBufferEmptyI
#define RtxEaiTxBufferEmptyI(Instance) TRUE
#endif

// "RtxEai Message API"
/****************************************************************************
*  FUNCTION: RtxEaiSendMessage()
*
*  INPUTS  : ProgramId specifies the destination application on the host.
*                      (Part of EAP payload header.)
*            TaskId specifies the destination task / thread in the host
*                   application. (Part of EAP payload header.)
*            Primitive holds the message id.
*  OUTPUTS : none.
*  RETURNS : void.
*
*  DESCRIPTION: This function is used to send a messages (primitive only).
*               The RtxEai module is responsible for the EAP framing.
*               This function can be used to send a message from any task in
*               the system. The messages will be sent on the RTX EAI instance
*               used for task 0.
****************************************************************************/
#ifdef RTX_EAI_SUPPORT
void RtxEaiSendMessage(rsuint8 ProgramId, rsuint8 TaskId, rsuint16 Primitive);
#else
#undef RtxEaiSendMessage
#define RtxEaiSendMessage(ProgramId, TaskId, Primitive)
#endif

/****************************************************************************
*  FUNCTION: RtxEaiSendMessageI()
*
*  INPUTS  : Instance specifies the RTX EAI instance to use.
*            ProgramId specifies the destination application on the host.
*                      (Part of EAP payload header.)
*            TaskId specifies the destination task / thread in the host
*                   application. (Part of EAP payload header.)
*            Primitive holds the message id.
*  OUTPUTS : none.
*  RETURNS : void.
*
*  DESCRIPTION: This function is used to send a messages (primitive only).
*               The RtxEai module is responsible for the EAP framing.
*               This function can be used to send a message from any task in
*               the system. The messages will be sent on the RTX EAI instance
*               specified by the Instance parameter.
****************************************************************************/
#ifdef RTX_EAI_SUPPORT
void RtxEaiSendMessageI(rsuint8 Instance, rsuint8 ProgramId, rsuint8 TaskId, rsuint16 Primitive);
#else
#undef RtxEaiSendMessageI
#define RtxEaiSendMessageI(Instance, ProgramId, TaskId, Primitive)
#endif

/****************************************************************************
*  FUNCTION: RtxEaiSendMail()
*
*  INPUTS  : ProgramId specifies the destination application on the host.
*                      (Part of EAP payload header.)
*            TaskId specifies the destination task / thread in the host
*                   application. (Part of EAP payload header.)
*            MailPtr holds pointer to the mail.
*            MailSize holds the length of the mail.
*  OUTPUTS : none.
*  RETURNS : void.
*
*  DESCRIPTION: This function is used to send a mail from the target to a host
*               application.
*               The RtxEai module is responsible for the EAP framing but the
*               calling task is responsible for the mail formatting.
*               This function can be used to send a mail from any task in
*               the system.
****************************************************************************/
#ifdef RTX_EAI_SUPPORT
void RtxEaiSendMail(rsuint8 ProgramId, rsuint8 TaskId, rsuint8 *MailPtr, rsuint16 MailSize);
#else
#undef RtxEaiSendMail
#define RtxEaiSendMail(ProgramId, TaskId, MailPtr, MailSize)
#endif

/****************************************************************************
*  FUNCTION: RtxEaiSendMailI()
*
*  INPUTS  : Instance specifies the RTX EAI instance to use.
*            ProgramId specifies the destination application on the host.
*                      (Part of EAP payload header.)
*            TaskId specifies the destination task / thread in the host
*                   application. (Part of EAP payload header.)
*            MailPtr holds pointer to the mail.
*            MailSize holds the length of the mail.
*  OUTPUTS : none.
*  RETURNS : void.
*
*  DESCRIPTION: This function is used to send a mail from the target to a host
*               application.
*               The RtxEai module is responsible for the EAP framing but the
*               calling task is responsible for the mail formatting.
*               This function can be used to send a mail from any task in
*               the systemm, and the mail will be sent on the RTX EAI instance
*               specified by the Instance parameter.
****************************************************************************/
#ifdef RTX_EAI_SUPPORT
void RtxEaiSendMailI(rsuint8 Instance, rsuint8 ProgramId, rsuint8 TaskId, rsuint8 *MailPtr, rsuint16 MailSize);
#else
#undef RtxEaiSendMailI
#define RtxEaiSendMailI(Instance, ProgramId, TaskId, MailPtr, MailSize)
#endif

/****************************************************************************
*  FUNCTION: RtxEaiSendMailToEapSendMail()
*
*  INPUTS  : MailPtr holds pointer to the mail.
*            MailSize holds the length of the mail.
*  OUTPUTS : none.
*  RETURNS : void.
*
*  DESCRIPTION: This function is used to send a mail from the target to the
*               "EAP Send Mail" program running on a PC. This function sends
*               the mail using ProgramId = 1 and TaskId = 0.
*               The RtxEai module is responsible for the EAP framing but the
*               calling task is responsible for the mail formatting.
*               This function can be used to send a mail from any task in
*               the system. It should eg. be used in tasks that need to send
*               back a mail to the "EAP Send Mail" when it has received a mail
*               from the "EAP Send Mail" program.
****************************************************************************/
#ifdef RTX_EAI_SUPPORT
void RtxEaiSendMailToEapSendMail(rsuint8 *MailPtr, rsuint16 MailSize);
#else
#undef RtxEaiSendMailToEapSendMail
#define RtxEaiSendMailToEapSendMail(MailPtr, MailSize)
#endif

/****************************************************************************
*  FUNCTION: RtxEaiSendSwBuildInfoCfm()
*
*  INPUTS  : ProgramId
*            TaskId
*            ProgramerId
*            VersionHexFormat
*            VersionStrFormat
*            LinkData
*            ReleaseLabel
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to send a RTX_EAP_SW_BUILD_INFO_CFM
*               message to the Host.
****************************************************************************/
void RtxEaiSendSwBuildInfoCfm(rsuint8 ProgramId,
                              rsuint8 TaskId,
                              const rsuint8 *ProgramerId,
                              const rsuint16 VersionHexFormat,
                              const rsuint8 *VersionStrFormat,
                              const rsuint8 *LinkDate,
                              const rsuint8 *ReleaseLabel);

/****************************************************************************
*  FUNCTION: RtxEaiSendProjectTestEvent
*
*  INPUTS  : ProgramId specifies the destination application on the host.
*                      (Part of EAP payload header.)
*            TaskId specifies the destination task / thread in the host
*                   application. (Part of EAP payload header.)
*            Opcode holds the message id.
*            ParamtersLength the length of the parameters
*            pParameters pointer to struct holding the paramters.
*  OUTPUTS : none.
*  RETURNS : void.
*
*  DESCRIPTION: This function is used to send a RTX_EAP_PROJECT_TEST_CFM
*               message to an application on the host.
****************************************************************************/
#ifdef RTX_EAI_PROJECT_TEST_HANDLER
void RtxEaiSendProjectTestEvent(rsuint8 ProgramId,
                                rsuint8 TaskId,
                                rsuint16 Opcode,
                                rsuint16 ParametersLength,
                                rsuint8* pParameters);
#endif

/****************************************************************************
*  FUNCTION: RtxEaiSendRfTestEvent
*
*  INPUTS  : ProgramId specifies the destination application on the host.
*                      (Part of EAP payload header.)
*            TaskId specifies the destination task / thread in the host
*                   application. (Part of EAP payload header.)
*            Opcode holds the message id.
*            ParamtersLength the length of the parameters
*            pParameters pointer to struct holding the paramters.
*  OUTPUTS : none.
*  RETURNS : void.
*
*  DESCRIPTION: This function is used to send a RTX_EAP_RF_TEST_CFM message
*               to an application on the host.
****************************************************************************/
#ifdef RTX_EAI_RF_TEST_HANDLER
void RtxEaiSendRfTestEvent(rsuint8 ProgramId,
                           rsuint8 TaskId,
                           rsuint16 Opcode,
                           rsuint16 ParametersLength,
                           rsuint8* pParameters);
#endif

/****************************************************************************
*  FUNCTION: RtxEaiSendHwTestEvent
*
*  INPUTS  : ProgramId specifies the destination application on the host.
*                      (Part of EAP payload header.)
*            TaskId specifies the destination task / thread in the host
*                   application. (Part of EAP payload header.)
*            Opcode holds the message id.
*            ParamtersLength the length of the parameters
*            pParameters pointer to struct holding the paramters.
*  OUTPUTS : none.
*  RETURNS : void.
*
*  DESCRIPTION: This function is used to send a RTX_EAP_HW_TEST_CFM message
*               to an application on the host.
****************************************************************************/
#ifdef RTX_EAI_HW_TEST_HANDLER
void RtxEaiSendHwTestEvent(rsuint8 ProgramId,
                           rsuint8 TaskId,
                           rsuint16 Opcode,
                           rsuint16 ParametersLength,
                           rsuint8* pParameters);
#endif

/****************************************************************************
*  FUNCTION: RtxEaiSendSwTestEvent
*
*  INPUTS  : ProgramId specifies the destination application on the host.
*                      (Part of EAP payload header.)
*            TaskId specifies the destination task / thread in the host
*                   application. (Part of EAP payload header.)
*            Opcode holds the message id.
*            ParamtersLength the length of the parameters
*            pParameters pointer to struct holding the paramters.
*  OUTPUTS : none.
*  RETURNS : void.
*
*  DESCRIPTION: This function is used to send a RTX_EAP_SW_TEST_CFM message
*               to an application on the host.
****************************************************************************/
#ifdef RTX_EAI_SW_TEST_HANDLER
void RtxEaiSendSwTestEvent(rsuint8 ProgramId,
                           rsuint8 TaskId,
                           rsuint16 Opcode,
                           rsuint16 ParametersLength,
                           rsuint8* pParameters);
#endif

// "RtxEai Trace API"

/****************************************************************************
*  FUNCTION: RtxEaiLogEnabled
*
*  INPUTS  : Sender the task that has sent the mail
*            Receiver the receiver of the mail
*            Primitive the primitive of the mail
*  OUTPUTS : none
*  RETURNS : TRUE if the mail will be logged, FALSE if not.
*
*  DESCRIPTION: This function is usded to determine if a mail will be logged or not.
*               This is useful to determine if a mail (which' sole purpose is to
*               be logged), should be sent at all.
****************************************************************************/
rsbool RtxEaiLogEnabled(rsuint8 Sender, rsuint8 Receiver, rsuint16 Primitive);

/****************************************************************************
*  FUNCTION: RtxEaiLogMail
*
*  INPUTS  : Sender the task that has sent the mail
*            Receiver the receiver of the mail
*            Primitive the primitive of the mail
*            MailLength length of the mail incl. the Primitive
*            MailPtr pointer to the mail
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to send an RTX_EAP_TRACE_xxx_MAIL_IND
*               message to the host. The mail trace message is only sent to
*               the host if it is included in the mail trace options down
*               loaded by the host.
****************************************************************************/
#ifdef RTX_EAI_LOG_TRACE_SUPPORT
void RtxEaiLogMail(rsuint8 Sender, rsuint8 Receiver, rsuint16 Primitive, rsuint16 MailLength, const RosMailType *MailPtr);
#else
#undef RtxEaiLogMail
#define RtxEaiLogMail(Sender, Receiver, Primitive, MailLength, MailPtr)
#endif

/****************************************************************************
*  FUNCTION: RtxEaiLogMail
*
*  INPUTS  : Sender the task that has sent the mail
*            Receiver the receiver of the mail
*            Primitive the primitive of the mail
*            MailLength length of the mail incl. the Primitive
*            MailPtr pointer to the mail
*            Time The time the task used to process the mail.
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to send an RTX_EAP_TRACE_xxx_MAIL_IND
*               message to the host. The mail trace message is only sent to
*               the host if it is included in the mail trace options down
*               loaded by the host.
****************************************************************************/
#ifdef RTX_EAI_LOG_TRACE_SUPPORT
void RtxEaiLogMail2(rsuint8 Sender, rsuint8 Receiver, rsuint16 Primitive, rsuint16 MailLength, const RosMailType *MailPtr, RsPerformanceTimeType Time);
#else
#undef RtxEaiLogMail2
#define RtxEaiLogMail2(Sender, Receiver, Primitive, MailLength, MailPtr)
#endif

/****************************************************************************
*  FUNCTION: RtxEaiLogComment
*
*  INPUTS  : TaskId
*            format, ...
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to log a comment / text in the trace
*               stream / window. The text is only logged if this function is
*               enabled for the spceified task.
****************************************************************************/
#ifdef RTX_EAI_LOG_COMMENT_SUPPORT
void RtxEaiLogComment(rsuint8 TaskId, const char* format, ...);
#else
  #ifndef PCCOMPILE
    #define RtxEaiLogComment(TaskId,format,...)
  #endif
#endif

/****************************************************************************
*  FUNCTION: RtxEaiVaLogComment
*
*  INPUTS  : TaskId,
*            format,
*            argptr
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to log a comment / text in the trace
*               stream / window. The text is only logged if this function is
*               enabled for the spceified task.
****************************************************************************/
#ifdef RTX_EAI_LOG_COMMENT_SUPPORT
void RtxEaiVaLogComment(rsuint8 TaskId, const char* format, va_list argptr);
#else
#undef RtxEaiVaLogComment
#define RtxEaiVaLogComment(TaskId, format, argptr)
#endif

/****************************************************************************
*  FUNCTION: RtxEaiLogPdu
*
*  INPUTS  : TaskId
*            ProtocolId
*            PduLength
*            PduPtr
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to log a PDU. The PDU is only logged if
*               this function is enabled for the spceified task.
****************************************************************************/
#ifdef RTX_EAI_LOG_PDU_SUPPORT
void RtxEaiLogPdu(rsuint8 TaskId, rsuint8 ProtocolId, rsuint8 Direction, rsuint16 PduLength, rsuint8 *PduPtr);
#else
#undef RtxEaiLogPdu
#define RtxEaiLogPdu(TaskId, ProtocolId, Direction, PduLength, PduPtr)
#endif

/****************************************************************************
*  FUNCTION: RtxEaiLogFunction
*
*  INPUTS  : TaskId
*            FunctionId
*            ParameterLength
*            ParameterPtr
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to log a function call. The function
*               call is only logged if this function is enabled for the
*               spceified task.
****************************************************************************/
#ifdef RTX_EAI_LOG_FUNCTION_SUPPORT
void RtxEaiLogFunction(rsuint8 TaskId, rsuint16 FunctionId, rsuint16 ParametersLength, rsuint8 *ParametersPtr);
#else
#undef RtxEaiLogFunction
#define RtxEaiLogFunction(TaskId, FunctionId, ParametersLength, ParametersPtr)
#endif

/****************************************************************************
*  FUNCTION:
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION:
****************************************************************************/
#ifdef RTX_EAI_LOG_RAW_DATA_SUPPORT
void RtxEaiLogRawData(rsuint8 TaskId, rsuint16 DataLength, rsuint8 *DataPtr);
#else
#undef RtxEaiLogRawData
#define RtxEaiLogRawData(TaskId, DataLength, DataPtr)
#endif

/****************************************************************************
*  FUNCTION:
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION:
****************************************************************************/
#ifdef RTX_EAI_LOG_RUNTIMER_ERROR_SUPPORT
void RtxEaiLogRuntimeError(rsuint8 TaskId, rsuint32 LineNumber, char *FileName);
#else
#undef RtxEaiLogRuntimeError
#define RtxEaiLogRuntimeError(TaskId, LineNumber, FileName)
#endif

/****************************************************************************
*  FUNCTION:
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION:
****************************************************************************/
#ifdef RTX_EAI_LOG_ASSERT_SUPPORT
void RtxEaiLogAssert(rsuint8 TaskId, rsuint32 LineNumber, char *FileName);
#else
#undef RtxEaiLogAssert
#define RtxEaiLogAssert(TaskId, LineNumber, FileName)
#endif

/****************************************************************************
*  FUNCTION:
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION:
****************************************************************************/
#ifdef RTX_EAI_LOG_TIMER_SUPPORT
void RtxEaiLogTimerStart(rsuint8 TaskId, rsuint8 TimerId, rsuint16 Time);
void RtxEaiLogTimerStartEx(rsuint8 TaskId, rsuint16 TimerId, rsuint32 Time);
#else
#undef RtxEaiLogTimerStart
#define RtxEaiLogTimerStart(TaskId, TimerId, Time)
#undef RtxEaiLogTimerStartEx
#define RtxEaiLogTimerStartEx(TaskId, TimerId, Time)
#endif

/****************************************************************************
*  FUNCTION:
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION:
****************************************************************************/
#ifdef RTX_EAI_LOG_TIMER_SUPPORT
void RtxEaiLogTimerStop(rsuint8 TaskId, rsuint8 TimerId);
void RtxEaiLogTimerStopEx(rsuint8 TaskId, rsuint16 TimerId);
#else
#undef RtxEaiLogTimerStop
#define RtxEaiLogTimerStop(TaskId, TimerId)
#undef RtxEaiLogTimerStopEx
#define RtxEaiLogTimerStopEx(TaskId, TimerId)
#endif

/****************************************************************************
*  FUNCTION:
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION:
****************************************************************************/
#ifdef RTX_EAI_LOG_RT_TIMER_SUPPORT
void RtxEaiLogRtTimerCreate(rsuint8 TaskId, rsuint32 TimerId);
#else
#undef RtxEaiLogRtTimerCreate
#undef  RtxEaiLogRtTimerCreate
#define RtxEaiLogRtTimerCreate(TaskId, TimerId)
#endif

/****************************************************************************
*  FUNCTION:
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION:
****************************************************************************/
#ifdef RTX_EAI_LOG_RT_TIMER_SUPPORT
void RtxEaiLogRtTimerDestroy(rsuint8 TaskId, rsuint32 TimerId);
#else
#undef  RtxEaiLogRtTimerDestroy
#define RtxEaiLogRtTimerDestroy(TaskId, TimerId)
#endif

/****************************************************************************
*  FUNCTION:
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION:
****************************************************************************/
#ifdef RTX_EAI_LOG_RT_TIMER_SUPPORT
void RtxEaiLogRtTimerStart(rsuint8 TaskId, rsuint32 TimerId, rsuint32 Time);
#else
#undef  RtxEaiLogRtTimerStart
#define RtxEaiLogRtTimerStart(TaskId, TimerId, Time)
#endif

/****************************************************************************
*  FUNCTION:
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION:
****************************************************************************/
#ifdef RTX_EAI_LOG_RT_TIMER_SUPPORT
void RtxEaiLogRtTimerStop(rsuint8 TaskId, rsuint32 TimerId);
#else
#undef  RtxEaiLogRtTimerStop
#define RtxEaiLogRtTimerStop(TaskId, TimerId)
#endif

/****************************************************************************
*  FUNCTION:
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION:
****************************************************************************/
#ifdef RTX_EAI_LOG_HEAP_SUPPORT
void RtxEaiLogHeapAlloc(rsuint8 TaskId, rsuint32 Address, rsuint16 Size);
#else
#undef  RtxEaiLogHeapAlloc
#define RtxEaiLogHeapAlloc(TaskId, Address, Size)
#endif

/****************************************************************************
*  FUNCTION:
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION:
****************************************************************************/
#ifdef RTX_EAI_LOG_HEAP_SUPPORT
void RtxEaiLogHeapFree(rsuint8 TaskId, rsuint32 Address);
#else
#undef  RtxEaiLogHeapFree
#define RtxEaiLogHeapFree(TaskId, Address)
#endif

/****************************************************************************
*  FUNCTION:
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION:
****************************************************************************/
#ifdef RTX_EAI_LOG_WATCH_SUPPORT
void RtxEaiLogAddWatch(rsuint8 TaskId, rsuint32 Address, rsuint16 Size, char *Name);
#else
#undef  RtxEaiLogAddWatch
#define RtxEaiLogAddWatch(TaskId, Address, Size, Name)
#endif

/****************************************************************************
*  FUNCTION:
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION:
****************************************************************************/
#ifdef RTX_EAI_LOG_PRINTF_SUPPORT
void RtxEaiPrintf(rsuint8 TaskId, const char* format, ...);
#else
  #ifndef PCCOMPILE
    #define RtxEaiPrintf(TaskId,format,...)
  #endif
#endif

/****************************************************************************
*  FUNCTION:
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION:
****************************************************************************/
#ifdef RTX_EAI_LOG_PRINTF_SUPPORT
void RtxEaiVaPrintf(rsuint8 TaskId, const char* format, va_list argptr);
#else
#undef  RtxEaiVaPrintf
#define RtxEaiVaPrintf(TaskId, format, argptr)
#endif

/****************************************************************************
*  FUNCTION:
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION:
****************************************************************************/
#ifdef RTX_EAI_LOG_CLEAR_SCREEN_SUPPORT
void RtxEaiClearScreen(rsuint8 TaskId);
#else
#undef  RtxEaiClearScreen
#define RtxEaiClearScreen(TaskId)
#endif

/****************************************************************************
*  FUNCTION:
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION:
****************************************************************************/
#ifdef RTX_EAI_LOG_SCREEN_GOTOXY_SUPPORT
void RtxEaiScreenGotoxy(rsuint8 TaskId, rsuint8 X,rsuint8 Y);
#else
#undef  RtxEaiScreenGotoxy
#define RtxEaiScreenGotoxy(TaskId, X,Y)
#endif

/****************************************************************************
*  FUNCTION:
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION:
****************************************************************************/
#ifdef RTX_EAI_LOG_GRAPH_UPDATE_SUPPORT
void RtxEaiLogGraphUpdate(rsuint8 GraphId, rsuint8 NumberOfLines, rsuint8 DataElementSize, void *pLineData);
#else
#undef  RtxEaiLogGraphUpdate
#define RtxEaiLogGraphUpdate(GraphId, NumberOfLines, DataElementSize, pLineData)
#endif

/****************************************************************************
*  FUNCTION:
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION:
****************************************************************************/
#ifdef RTX_EAI_LOG_GRAPH_DATA_SUPPORT
void RtxEaiLogGraphData(rsuint8 GraphId, rsuint8 LineId, rsuint8 DataElementSize, rsuint16 SampleCount, void *pLineData);
#else
#undef  RtxEaiLogGraphData
#define RtxEaiLogGraphData(GraphId, LineId, DataElementSize, SampleCount, pLineData)
#endif

/****************************************************************************
*  FUNCTION:
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION:
****************************************************************************/
#ifdef RTX_EAI_LOG_GRAPH_DATA_SUPPORT
void RtxEaiLogGraphDataEx(rsuint8 GraphId, rsuint8 LineId, rsuint8 Append, rsuint8 DataElementSize, rsuint16 SampleCount, rsuint8 NumberOfLines, void *pLineData);
#else
#undef  RtxEaiLogGraphDataEx
#define RtxEaiLogGraphDataEx(GraphId, LineId, Append, DataElementSize, SampleCount, NumberOfLines, pLineData)
#endif

/****************************************************************************
*  FUNCTION:
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION:
****************************************************************************/
#ifdef RTX_EAI_ADD_GRAPH_SUPPORT
void RtxEaiAddGraph(rsuint8 GraphId, rsuint8 GraphConfig, rsuint8 Options, char *pName);
#else
#undef  RtxEaiAddGraph
#define RtxEaiAddGraph(GraphId, GraphConfig, Options, pName)
#endif

/****************************************************************************
*  FUNCTION:
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION:
****************************************************************************/
#ifdef RTX_EAI_ADD_LINE_TO_GRAPH_SUPPORT
void RtxEaiAddLineToGraph(rsuint8 GraphId, rsuint8 LineId, rsuint32 MaxY, rsuint16 YScale, char *pName);
#else
#undef  RtxEaiAddLineToGraph
#define RtxEaiAddLineToGraph(GraphId, LineId, MaxY, YScale, pName)
#endif

/****************************************************************************
*  FUNCTION:
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION:
****************************************************************************/
#ifdef RTX_EAI_ADD_LINE_TO_GRAPH_SUPPORT
void RtxEaiAddLineToGraphEx(rsuint8 GraphId, rsuint8 LineId, rsuint32 MaxY, rsuint16 YScale, rsuint8 Options, char *pName);
#else
#undef  RtxEaiAddLineToGraphEx
#define RtxEaiAddLineToGraphEx(GraphId, LineId, MaxY, YScale, Options, pName)
#endif

/****************************************************************************
*  FUNCTION:
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION:
****************************************************************************/
#ifdef RTX_EAI_REMOVE_GRAPH_SUPPORT
void RtxEaiRemoveGraph(rsuint8 GraphId);
#else
#undef  RtxEaiRemoveGraph
#define RtxEaiRemoveGraph(GraphId)
#endif

//
// RtxEai application callbacks
//

/****************************************************************************
*  FUNCTION: RTX_EAP_SW_BUILD_INFO_REQ_RECEIVED
*
*  INPUTS  : ProgramId and TaskId specifies the destination address of the
*            RTX_EAP_SW_BUILD_INFO_CFM.
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: Called by the RtxEai when RTX_EAP_SW_BUILD_INFO_REQ is received.
*               RtxEaiSendSwBuildInfoCfm() should be called from this function.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
void RTX_EAP_SW_BUILD_INFO_REQ_RECEIVED(rsuint8 ProgramId, rsuint8 TaskId);

/****************************************************************************
*  FUNCTION: RTX_EAI_TRACE_STARTED
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: Called by the RtxEai when the mail trace is started by the host.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
#ifdef RTX_EAI_TRACE_STARTED
void RTX_EAI_TRACE_STARTED(void);
#endif

/****************************************************************************
*  FUNCTION: RTX_EAI_TRACE_STOPPED
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: Called by the RtxEai when the mail trace is stopped by the host.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
#ifdef RTX_EAI_TRACE_STOPPED
void RTX_EAI_TRACE_STOPPED(void);
#endif

/****************************************************************************
*  FUNCTION: RTX_EAI_SEND_MAIL
*
*  INPUTS  : Destination
*            MAilPtr
*            MailLength
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: Called by the RtxEai to send a mail received from the host to a task.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
#ifdef RTX_EAI_SEND_MAIL
void RTX_EAI_SEND_MAIL(rsuint8 Destination, rsuint16 MailLength, rsuint8 *MailPtr);
#endif
#ifdef RTX_EAI_SEND_MAIL_ALT_CH1
void RTX_EAI_SEND_MAIL_ALT_CH1(rsuint8 Destination, rsuint16 MailLength, rsuint8 *MailPtr);
#endif
#ifdef RTX_EAI_SEND_MAIL_ALT_CH2
void RTX_EAI_SEND_MAIL_ALT_CH2(rsuint8 Destination, rsuint16 MailLength, rsuint8 *MailPtr);
#endif
#ifdef RTX_EAI_SEND_MAIL_ALT_CH3
void RTX_EAI_SEND_MAIL_ALT_CH3(rsuint8 Destination, rsuint16 MailLength, rsuint8 *MailPtr);
#endif

/****************************************************************************
*  FUNCTION: RTX_EAI_KEY_PRESS_HANDLER
*
*  INPUTS  : Destination
*            KeyCode
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: Called by the RtxEai to send a key press received from the
*               host to a task.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
#ifdef RTX_EAI_KEY_PRESS_HANDLER
void RTX_EAI_KEY_PRESS_HANDLER(rsuint8 Destination, rsuint32 KeyCode);
#endif
#ifdef RTX_EAI_KEY_PRESS_HANDLER_ALT_CH1
void RTX_EAI_KEY_PRESS_HANDLER_ALT_CH1(rsuint8 Destination, rsuint32 KeyCode);
#endif
#ifdef RTX_EAI_KEY_PRESS_HANDLER_ALT_CH2
void RTX_EAI_KEY_PRESS_HANDLER_ALT_CH2(rsuint8 Destination, rsuint32 KeyCode);
#endif
#ifdef RTX_EAI_KEY_PRESS_HANDLER_ALT_CH3
void RTX_EAI_KEY_PRESS_HANDLER_ALT_CH3(rsuint8 Destination, rsuint32 KeyCode);
#endif

/****************************************************************************
*  FUNCTION: RTX_EAI_TRACE_SET_ALT_LOG_CHx
*
*  INPUTS  : ProgramId indicates the ProgramId used by the RTX Monitor to
*                      identify this log channel.
*            NumberOfTasks indicates the number of elements in the LogOption[]
*            LogOptionPtr is a pointer to LogOption[]
*            NumberOfLogPrimitives the number of elements in LogPrimitives[]
*            LogPrimitivesPtr is a pointer to LogPrimitives[]
*            NumberOfExcludePrimitives number of elements in ExcludePrimitives[]
*            ExcludePrimitivesPtr is a pointer to ExcludePrimitives[]
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used by the RtxEai to store the downloaded
*               options of an alternative log channel.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
#ifdef RTX_EAI_TRACE_SET_ALT_LOG_CH1
void RTX_EAI_TRACE_SET_ALT_LOG_CH1(rsuint8 ProgramId,
                                   rsuint8 NumberOfTasks,
                                   rsuint8 *LogOptionPtr,
                                   rsuint8 NumberOfLogPrimitives,
                                   rsuint16 *LogPrimitivesPtr,
                                   rsuint8 NumberOfExcludePrimitives,
                                   rsuint16 *ExcludePrimitivesPtr);
#endif
#ifdef RTX_EAI_TRACE_SET_ALT_LOG_CH2
void RTX_EAI_TRACE_SET_ALT_LOG_CH2(rsuint8 ProgramId,
                                   rsuint8 NumberOfTasks,
                                   rsuint8 *LogOptionPtr,
                                   rsuint8 NumberOfLogPrimitives,
                                   rsuint16 *LogPrimitivesPtr,
                                   rsuint8 NumberOfExcludePrimitives,
                                   rsuint16 *ExcludePrimitivesPtr);
#endif
#ifdef RTX_EAI_TRACE_SET_ALT_LOG_CH3
void RTX_EAI_TRACE_SET_ALT_LOG_CH3(rsuint8 ProgramId,
                                   rsuint8 NumberOfTasks,
                                   rsuint8 *LogOptionPtr,
                                   rsuint8 NumberOfLogPrimitives,
                                   rsuint16 *LogPrimitivesPtr,
                                   rsuint8 NumberOfExcludePrimitives,
                                   rsuint16 *ExcludePrimitivesPtr);
#endif


/****************************************************************************
*  FUNCTION: RTX_EAI_NVS_READ
*
*  INPUTS  : DataPtr pointer to memory block where to the data read is copied.
*            Address holds the Offset in the NVS form which data is read.
*            NumberOfBytes to read.
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to read from the NVS.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
void RTX_EAI_NVS_READ(rsuint8 *DataPtr, rsuint32 Address, rsuint16 NumberOfBytes);

/****************************************************************************
*  FUNCTION: RTX_EAI_NVS_READ_NB
*
*  INPUTS  : ProgramId Identifies the originatior (on the host) of the req.
*            TaskId Identifies the originatior (on the host) of the req.
*            Address holds the Offset in the NVS form which data is read.
*            NumberOfBytes to read.
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to read from the NVS without waiting for
*               the read function to complete in RtxEai.c. Used when the
*               RTX_EAI_NVS_READ_REQ message is recived. It is the application
*               that sends the RTX_EAP_NVS_READ_CFM message back to the host/PC
*               when the requested data has been read from the NVS.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
void RTX_EAI_NVS_READ_NB(rsuint8 ProgramId,
                         rsuint8 TaskId,
                         rsuint32 Address,
                         rsuint16 NumberOfBytes);

/****************************************************************************
*  FUNCTION: RTX_EAI_NVS_WRITE
*
*  INPUTS  : Address
*            DataPtr
*            NumberOfBytes
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to write some data to the NVS.
*               Some PC / HOST applications like e.g. the ServiceTool expects
*               an RTX_EAP_NVS_WRITE_CFM message when the NVS in the target
*               has been updated. RtxEai.c sends this messages when this
*               function has been called.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
void RTX_EAI_NVS_WRITE(rsuint32 Address, rsuint8 *DataPtr, rsuint16 NumberOfBytes);

/****************************************************************************
*  FUNCTION: RTX_EAI_NVS_WRITE_NB
*
*  INPUTS  : ProgramId Identifies the originatior (on the host) of the req.
*            TaskId Identifies the originatior (on the host) of the req.
*            Address
*            DataPtr
*            NumberOfBytes
*
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to write some data to the NVS when it is
*               not possible to wait / block until the NVS has been updated.
*               It is used when a RTX_EAP_NVS_WRITE_REQ is received.
*               Some PC / HOST applications like e.g. the ServiceTool expects
*               an RTX_EAP_NVS_WRITE_CFM message when the NVS in the target
*               has been updated. RtxEai.c does not send this messages when this
*               function is used because.
*               A RTX_EAP_NVS_WRITE_CFM should be sent to the Host application
*               identified by the ProgramId and TaskId paramters.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
void RTX_EAI_NVS_WRITE_NB(rsuint8 ProgramId,
                          rsuint8 TaskId,
                          rsuint32 Address,
                          rsuint8 *DataPtr,
                          rsuint16 NumberOfBytes);

/****************************************************************************
*  FUNCTION: RTX_EAI_NVS_SET_DEFAULT
*
*  INPUTS  : Option Project specific option
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to request a default programming of
*               the NVS.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
void RTX_EAI_NVS_SET_DEFAULT(rsuint32	Option);

/****************************************************************************
*  FUNCTION: RTX_EAI_NVS_GET_CACHE_STATE
*
*  INPUTS  : void
*  OUTPUTS : none
*  RETURNS : TRUE if the cache is empty and FALSE otherwise.
*
*  DESCRIPTION: This function is used to query whether the NVS cache is empty.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
rsuint8 RTX_EAI_NVS_GET_CACHE_STATE(void);

/****************************************************************************
*  FUNCTION: RTX_EAI_NVS_SET_DOMAIN
*
*  INPUTS  : The new domain
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to change the active NVS domain
****************************************************************************/
void RTX_EAI_NVS_SET_DOMAIN(rsuint8	NewDomain);

/****************************************************************************
*  FUNCTION: RTX_EAI_NVS_SET_DOMAIN
*
*  INPUTS  : The domain which to get the size of
*  OUTPUTS : none
*  RETURNS : The size of the domain in bytes
*
*  DESCRIPTION: This function is used to get the size of a given domain
****************************************************************************/
rsuint32 RTX_EAI_NVS_GET_DOMAIN_SIZE(rsuint8	Domain);
/****************************************************************************
*  FUNCTION: RTX_EAI_DSP_READ
*
*  INPUTS  : DataPtr pointer to memory block where to the data read is copied.
*            Address holds the Offset in the DSP RAM form which data is read.
*            NumberOfBytes to read.
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to read from the DSP RAM.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
void RTX_EAI_DSP_READ(rsuint8 *DataPtr, rsuint32 Address, rsuint16 NumberOfBytes);

/****************************************************************************
*  FUNCTION: RTX_EAI_DSP_WRITE
*
*  INPUTS  : Address
*            DataPtr
*            NumberOfBytes
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to write data to the DSP RAM.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
void RTX_EAI_DSP_WRITE(rsuint32 Address, rsuint8 *DataPtr, rsuint16 NumberOfBytes);

/****************************************************************************
*  FUNCTION: RTX_EAI_DSP_MEMSET
*
*  INPUTS  : Address
*            NewValue
*            NumberOfBytes
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to initialise some of the DSP RAM.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
void RTX_EAI_DSP_MEMSET(rsuint32 Address, rsuint8 NewValue, rsuint16 NumberOfBytes);

/****************************************************************************
*  FUNCTION: RTX_EAI_FPGA_READ
*
*  INPUTS  : DataPtr pointer to memory block where to the data read is copied.
*            Address holds the Offset in the FPGA RAM form which data is read.
*            NumberOfBytes to read.
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to read from the FPGA RAM.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
void RTX_EAI_FPGA_READ(rsuint8 *DataPtr, rsuint32 Address, rsuint16 NumberOfBytes);

/****************************************************************************
*  FUNCTION: RTX_EAI_FPGA_WRITE
*
*  INPUTS  : Address
*            DataPtr
*            NumberOfBytes
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to write data to the FPGA RAM.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
void RTX_EAI_FPGA_WRITE(rsuint32 Address, rsuint8 *DataPtr, rsuint16 NumberOfBytes);

/****************************************************************************
*  FUNCTION: RTX_EAI_FPGA_MEMSET
*
*  INPUTS  : Address
*            NewValue
*            NumberOfBytes
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to initialise some of the FPGA RAM.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
void RTX_EAI_FPGA_MEMSET(rsuint32 Address, rsuint8 NewValue, rsuint16 NumberOfBytes);

/****************************************************************************
*  FUNCTION: RTX_EAI_SEQUENCER_READ
*
*  INPUTS  : DataPtr pointer to memory block where to the data read is copied.
*            Address holds the Offset in the SEQUENCER RAM form which data is read.
*            NumberOfBytes to read.
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to read from the SEQUENCER RAM.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
void RTX_EAI_SEQUENCER_READ(rsuint8 *DataPtr, rsuint32 Address, rsuint16 NumberOfBytes);

/****************************************************************************
*  FUNCTION: RTX_EAI_SEQUENCER_WRITE
*
*  INPUTS  : Address
*            DataPtr
*            NumberOfBytes
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to write data to the SEQUENCER RAM.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
void RTX_EAI_SEQUENCER_WRITE(rsuint32 Address, rsuint8 *DataPtr, rsuint16 NumberOfBytes);

/****************************************************************************
*  FUNCTION: RTX_EAI_SEQUENCER_MEMSET
*
*  INPUTS  : Address
*            NewValue
*            NumberOfBytes
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to initialise some of the SEQUENCER RAM.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
void RTX_EAI_SEQUENCER_MEMSET(rsuint32 Address, rsuint8 NewValue, rsuint16 NumberOfBytes);

/****************************************************************************
*  FUNCTION: RTX_EAI_PROJECT_TEST_HANDLER
*
*  INPUTS  : ProgramId
*            TaskId
*            Opcode
*            Parameters
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to handle project specific test commands.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
void RTX_EAI_PROJECT_TEST_HANDLER(rsuint8 ProgramId,
                                  rsuint8 TaskId,
                                  rsuint16 Opcode,
                                  rsuint16 ParametersLength,
                                  rsuint8 *Parameters);

/****************************************************************************
*  FUNCTION: RTX_EAI_RF_TEST_HANDLER
*
*  INPUTS  : ProgramId
*            TaskId
*            Opcode
*            Parameters
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to handle RF test commands.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
void RTX_EAI_RF_TEST_HANDLER(rsuint8 ProgramId,
                             rsuint8 TaskId,
                             rsuint16 Opcode,
                             rsuint16 ParametersLength,
                             rsuint8 *Parameters);

/****************************************************************************
*  FUNCTION: RTX_EAI_HW_TEST_HANDLER
*
*  INPUTS  : ProgramId
*            TaskId
*            Opcode
*            Parameters
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to handle HW test commands.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
void RTX_EAI_HW_TEST_HANDLER(rsuint8 ProgramId,
                             rsuint8 TaskId,
                             rsuint16 Opcode,
                             rsuint16 ParametersLength,
                             rsuint8 *Parameters);

/****************************************************************************
*  FUNCTION: RTX_EAI_SW_TEST_HANDLER
*
*  INPUTS  : ProgramId
*            TaskId
*            Opcode
*            Parameters
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to handle SW test commands.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
void RTX_EAI_SW_TEST_HANDLER(rsuint8 ProgramId,
                             rsuint8 TaskId,
                             rsuint16 Opcode,
                             rsuint16 ParametersLength,
                             rsuint8 *Parameters);

/****************************************************************************
*  FUNCTION: RTX_EAI_PROJECT_COMMAND_HANDLER
*
*  INPUTS  : ProgramId, MailPtr
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to handle project specific commands.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
#ifdef RTX_EAI_PROJECT_COMMAND_HANDLER_OWN_DEFINE
  // in some old projects the RTX_EAI_PROJECT_COMMAND_HANDLER is redefined to a normal task and hereby the ProgramId cannot be transferred. FM
#else
void RTX_EAI_PROJECT_COMMAND_HANDLER(rsuint8 ProgramId, const rsuint8* MailPtr);
#endif


// Driver Interface.

/****************************************************************************
*  FUNCTION: RTX_EAI_DRIVER_INIT
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to initialise the RtxEai driver.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
void RTX_EAI_DRIVER_INIT(void);

/****************************************************************************
*  FUNCTION: RTX_EAI_DRIVER_TERMINATE
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to shutdown the RtxEai driver.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
void RTX_EAI_DRIVER_TERMINATE(void);

/****************************************************************************
*  FUNCTION: RTX_EAI_DRIVER_KICK
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: This function is used to by the RtxEai module to trigger the
*               driver to e.g. read data from RX buffer.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
void RTX_EAI_DRIVER_KICK(void);

/****************************************************************************
*  FUNCTION: RTX_EAI_DRIVER_GET_TX_BUFFER
*
*  INPUTS  : Size specifies the requested buffer size excluding the EAP
*            framing overhead.
*  OUTPUTS : none
*  RETURNS : pointer to payload buffer or NULL if no buffer is available.
*
*  DESCRIPTION: Called by the RtxEai to get a buffer for TX from the HW driver.
*               (use #define in RtxEaiCfg.h to rename the callback)
*               The HW driver is responsible for the formatting of the EAP
*               framing including the Header field and the checksum field if
*               used on that interface.
****************************************************************************/
rsuint8* RTX_EAI_DRIVER_TX_GET_BUFFER(rsuint8 Instance, rsuint16 Size);

/****************************************************************************
*  FUNCTION: RTX_EAI_DRIVER_DELIVER_TX_BUFFER
*
*  INPUTS  : BufferPtr
*            Size
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: Called by RtxEai once a buffer returned from
*               RTX_EAI_DRIVER_GET_TX_BUFFER() is filled and ready for TX.
*               The HW driver must calculate the the checksum if it is used.
*               (use #define in RtxEaiCfg.h to rename the callback)
****************************************************************************/
void RTX_EAI_DRIVER_TX_DELIVER_BUFFER(rsuint8 *p);

/****************************************************************************
*  FUNCTION: RtxEaiDriverRxBufferReady
*
*  INPUTS  : Instance driver instance
*            BufferPtr pointer to payload part of EAP message received
*            Size indicates the sice of the payload buffer
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: Called by driver once a complete EAP packet has been received.
*               This function MUST be called from "OS kernel loop" context as
*               the EAP messages received are processed in the context of this
*               function. I.e. do not call this function from interrupt context.
*               The HW driver must check the checksum if it is used.
*               The driver must keep the data until RTX_EAI_DRIVER_RX_BUFFER_READ()
*               is called from the EapiIf implementation.
****************************************************************************/
#ifdef RTX_EAI_SUPPORT
void RtxEaiDriverRxBufferReady(rsuint8 Instance, rsuint8* BufferPtr, rsuint16 Size);
#else
#undef  RtxEaiDriverRxBufferReady
#define RtxEaiDriverRxBufferReady(Instance, BufferPtr, Size)
#endif

/****************************************************************************
*  FUNCTION: RTX_EAI_DRIVER_RX_BUFFER_READ
*
*  INPUTS  : BufferPtr
*            Size
*  OUTPUTS : none
*  RETURNS : void
*
*  DESCRIPTION: Called by RtxEai when an RX buffer has been read.
*               (use #define in RtxEaiCfg.h to rename the callback).
*               The driver should not call RtxEaiDriverRxBufferReady from
*               this context.
****************************************************************************/
void RTX_EAI_DRIVER_RX_BUFFER_READ(void);

#ifdef RTX_EAP_TRACE_TIME

/****************************************************************************
*  FUNCTION: RTX_EAI_SET_TRACE_TIME_COUNTER
*
*  INPUTS  : Time: 10 ms since midnight UTC
*            RtcSource: Source of the time info
*  OUTPUTS : none
*  RETURNS : none
*
*  DESCRIPTION: Called when new time info is received. The function must
*  determine whether to update its own time depending on RtcSource.
****************************************************************************/
void RTX_EAI_SET_TRACE_TIME_COUNTER(rsuint32 Time, RtxEapRtcSourceType RtcSource);

/****************************************************************************
*  FUNCTION: RTX_EAI_GET_TRACE_TIME_COUNTER
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : Time in 10 ms since midnight UTC
*
*  DESCRIPTION: Called to get time info for mail trace.
****************************************************************************/
rsuint32 RTX_EAI_GET_TRACE_TIME_COUNTER(void);

/****************************************************************************
*  FUNCTION: RTX_EAI_GET_RTC_SOURCE
*
*  INPUTS  : none
*  OUTPUTS : none
*  RETURNS : RTX Source
*
*  DESCRIPTION: Returns source of the real time clock used for the mail
*  trace time info.
****************************************************************************/
RtxEapRtcSourceType RTX_EAI_GET_RTC_SOURCE(void);

/****************************************************************************
*  FUNCTION: SendEapTargetTimeInfo
*
*  INPUTS  : See RtxEapTargetTimeInfoIndType for description
*  OUTPUTS : none
*  RETURNS : none
*
*  DESCRIPTION: Send RTX_EAP_TARGET_TIME_INFO_IND mail. Calls
*  RTX_EAI_GET_TRACE_TIME_COUNTER to get trace time.
****************************************************************************/
void SendEapTargetTimeInfo(RtxEapRtcSourceType NewRtcSource, RtxEapRtcSourceType OldRtcSource,
                           rsuint32 NewUtcTime, rsuint32 OldUtcTime, rsuint32 OldTraceTime);

#endif // RTX_EAP_TRACE_TIME

/****************************************************************************
*  FUNCTION: RTX_EAI_SET_POWER_STATE
*
*  INPUTS  : The new power state of the RtxEai module.
*  OUTPUTS : none
*  RETURNS : none
*
*  DESCRIPTION: Sets the current power state of RtxEai module.
****************************************************************************/
void RTX_EAI_SET_POWER_STATE(RtxEaiPowerStateType PowerState);


/****************************************************************************
*  FUNCTION: RtxEaiProjectEndianHandler
*
*  INPUTS  : Mail
*            FromTargetEndian: TRUE if the mail is in target endian before swap
*  OUTPUTS : none
*  RETURNS : none
*
*  DESCRIPTION: This function is called for in- and outgoing messages on
*  big endian targets, to enable conversion to little endian format. The
*  function must be implemented in the project.
****************************************************************************/
#if RS_ENDIAN_TYPE == RS_BIG_ENDIAN
void RtxEaiProjectEndianHandler(rsuint8* MailPtr, rsbool FromTargetEndian);
#endif

void RTX_EAI_AUDIO_IND_HANDLER(rsuint8 AudioHandle, rsuint8 NumberOfBytes, rsuint8 *AudioData);

#if RTX_EAI_PROXY_SUPPORT == 1
/****************************************************************************
*  FUNCTION: RtxEaiProxyGetPid
*
*  INPUTS  : TaskId
*  OUTPUTS : ProgramId
*  RETURNS : none
*
*  DESCRIPTION: This function can be used to obtain the program ID used when
*               mails from the task with TaskId is sent to remote entity via
*               the RtxEaiProxyTask.
****************************************************************************/
rsuint8 RtxEaiProxyGetPid(rsuint8 TaskId);
#endif


#ifdef __cplusplus
}
#endif

#endif

