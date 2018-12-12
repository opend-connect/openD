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
* Definition of the ApiPpUle interface.
*/


#ifndef APIPPULE_H
#define APIPPULE_H

/****************************************************************************
*                               Include files
****************************************************************************/
/*! The following API header files must be included. */
#include <Api/ApiCfg.h> /* API configuration */
/*! The following API header files must be included. */
#include <Phoenix/Api/Types/ApiTypes.h> /* API types */
/*! The following API header files must be included. */
#include <Phoenix/Api/PpUle/ApiPpUleTypes.h> /* ULE API types */

/****************************************************************************
*                               Macros/Defines
****************************************************************************/

/*! Defines PP SlotSize used in FP allocation IE */
#define API_PP_ULP_B_FIELD_FULL_SLOT         0x01


/*! Define bits pr. frame
     - We always use the uplink value for A-Field */
#define API_PP_ULP_B_FIELD_FULL_SLOT_BITS      280


/*! Define bits pr. frame
     - We always use the uplink value for A-Field */
#define API_PP_ULP_NO_OF_BPF_TYPES               4


/*! Define bits pr. frame
    - We always use the uplink value for A-Field */
#ifndef API_PP_ULE_APP_TASK
  #define API_PP_ULE_APP_TASK MMI_TASK  // temp
#endif 


/*! Define bits pr. frame
    - We always use the uplink value for A-Field */
#ifndef APIPPULE_TASK
  #define APIPPULE_TASK APIPPULP_TASK
#endif


/*! Misc type definitions */


#define API_ULE_MTU_SIZE_MIN                 API_ULE_MTU_SIZE_32
#define  API_ULE_MTU_SIZE_DEFAULT     API_ULE_MTU_SIZE_500
#define  API_ULE_MTU_SIZE_6LOWPAN    API_ULE_MTU_SIZE_1280
#define  API_ULE_MTU_SIZE_MAX              API_ULE_MTU_SIZE_1280

typedef  rsuint8 * ApiUleNvsDataPtr_t;

extern const rsuint16  BITS_PR_FRAME[API_PP_ULP_NO_OF_BPF_TYPES];



/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

#if (RTX_CORE_VERSION >= 0x0224)
  #include <Standard/Common/RsPushPack1.h>
#else
  #pragma pack(push,1)
#endif

/* Global mail primitives:
  API_PP_ULE_INIT_REQ=0x5A00,
  API_PP_ULE_INIT_CFM=0x5A01,
  API_PP_ULE_PVC_CONFIG_REQ=0x5A27,
  API_PP_ULE_PVC_CONFIG_CFM=0x5A28,
  API_PP_ULE_PVC_CONFIG_REJ=0x5A29,
  API_PP_ULE_PVC_CONFIG_IND=0x5A2E,
  API_PP_ULE_PVC_PENDING_IND=0x5A2A,
  API_PP_ULE_PVC_PENDING_RES=0x5A2B,
  API_PP_ULE_PVC_IWU_DATA_REQ=0x5A2C,
  API_PP_ULE_PVC_IWU_DATA_IND=0x5A2D,
  API_PP_ULE_SETUP_AGAIN_IND=0x5A2F,
  API_PP_ULE_START_LOCATE_IND=0x5A30,
  API_PP_ULE_HIGH_PAGING_MODE_IND=0x5A31,
  API_PP_ULE_LCE_PAGING_MODE_IND=0x5A32,
  API_PP_ULE_START_VOICE_CALL_IND=0x5A33,
  API_PP_ULE_INFO_REQ=0x5A08,
  API_PP_ULE_INFO_CFM=0x5A09,
  API_PP_ULE_SUBS_STATUS_REQ=0x5A1E,
  API_PP_ULE_SUBS_STATUS_CFM=0x5A1F,
  API_PP_ULE_SUBS_DELETE_REQ=0x5A20,
  API_PP_ULE_SUBS_DELETE_CFM=0x5A21,
  API_PP_ULE_DB_PAGE_ENABLE_REQ=0x5A22,
  API_PP_ULE_LOCATE_REQ=0x5A07,
  API_PP_ULE_LOCATE_REJ=0x5A34,
  API_PP_ULE_DB_PAGE_ENABLE_CFM=0x5A23,
  API_PP_ULE_SUSPEND_REQ=0x5A0B,
  API_PP_ULE_RESUME_ERROR_IND=0x5A26,
  API_PP_ULE_HIBERNATE_READ_REQ=0x5A0E,
  API_PP_ULE_HIBERNATE_READ_CFM=0x5A0F,
  API_PP_ULE_HIBERNATE_WRITE_REQ=0x5A10,
  API_PP_ULE_HIBERNATE_WRITE_CFM=0x5A11,
  API_PP_ULE_READY_IND=0x5A15,
  API_PP_ULE_DTR_IND=0x5A16,
  API_PP_ULE_DATA_IND=0x5A17,
  API_PP_ULE_DATA_REQ=0x5A18,
  API_PP_ULE_DATA_CFM=0x5A25,
  API_PP_ULE_DB_PAGE_IND= 0x5A24,
  API_PP_ULE_HAL_SET_PORT_REQ=0x5A1A,
  API_PP_ULE_HAL_GET_PORT_REQ=0x5A1B,
  API_PP_ULE_HAL_GET_PORT_CFM=0x5A1C,
  API_PP_ULE_HAL_PORT_IND=0x5A1D,
The global mail primitives MUST be defined in Global.h! */




/*! ULE mode */
typedef enum RSENUMTAG(ApiPpUleMode_t)
{
  API_PP_ULE_MODE_UNDEF                 = ULP_MODE_UNDEF,                 /*!< undefined */
  API_PP_ULE_MODE_UNLOCKED              = ULP_MODE_UNSYNCHRONIZED,        /*!< Unlocked */
  API_PP_ULE_MODE_UNLOCKED_SYNCHRONIZED = ULP_MODE_UNLOCKED_SYNCHRONIZED, /*!< Unlocked
                                                                             with
                                                                             synchronization */
  API_PP_ULE_MODE_OFF                   = ULP_MODE_OFF,                   /*!< ULE mode
                                                                             OFF */
} RSENUM8(ApiPpUleMode_t);

/*! Port direction mode for the ULE/ULP wakeup port. If using the port as
   output,  API_PP_ULE_SLEEPMODE_WAKEON_TIMER should be selected. */
typedef enum RSENUMTAG(ApiPpUlePortDirMode_t)
{
  API_PP_ULE_PORT_DIR_MODE_UNDEF       = ULP_PORT_DIR_MODE_UNDEF,       /*!< undefined */
  API_PP_ULE_PORT_DIR_MODE_IN_PULLUP   = ULP_PORT_DIR_MODE_IN_PULLUP,   /*!< Input
                                                                           pull-up */
  API_PP_ULE_PORT_DIR_MODE_IN_PULLDOWN = ULP_PORT_DIR_MODE_IN_PULLDOWN, /*!< Input
                                                                           pull-down */
  API_PP_ULE_PORT_DIR_MODE_OUT_H       = ULP_PORT_DIR_MODE_OUT_H,       /*!< Output,
                                                                           high */
  API_PP_ULE_PORT_DIR_MODE_OUT_L       = ULP_PORT_DIR_MODE_OUT_L,       /*!< Output ,
                                                                           low */
} RSENUM8(ApiPpUlePortDirMode_t);

/*! Trigger mode for the ULE/ULP wakeup port. */
typedef enum RSENUMTAG(ApiPpUlePortTrigMode_t)
{
  PI_PP_ULE_PORT_MODE_UNDEF                  = ULP_PORT_MODE_UNDEF,                
                                                            /*!<  */
  API_PP_ULE_PORT_TRIG_MODE_RISING_EDGE      = ULP_PORT_TRIG_MODE_RISING_EDGE,     
                                                            /*!<  */
  API_PP_ULE_PORT_TRIG_MODE_FALLING_EDGE     = ULP_PORT_TRIG_MODE_FALLING_EDGE,    
                                                            /*!<  */
  API_PP_ULE_PORT_TRIG_MODE_ACTIV_HIGH_LEVEL = ULP_PORT_TRIG_MODE_ACTIV_HIGH_LEVEL,
                                                            /*!<  */
  API_PP_ULE_PORT_TRIG_MODE_ACTIV_LOW_LEVEL  = ULP_PORT_TRIG_MODE_ACTIV_LOW_LEVEL, 
                                                            /*!<  */
} RSENUM8(ApiPpUlePortTrigMode_t);

/*! ULE sleep mode */
typedef enum RSENUMTAG(ApiPpUleSleepMode_t)
{
  API_PP_ULE_SLEEPMODE_UNDEF                 = ULP_SLEEPMODE_UNDEF,                
                                                            /*!< undefined */
  API_PP_ULE_SLEEPMODE_WAKEON_PORT_AND_TIMER = ULP_SLEEPMODE_WAKEON_PORT_AND_TIMER,
                                                            /*!< Wake on port and timer */
  API_PP_ULE_SLEEPMODE_WAKEON_PORT           = ULP_SLEEPMODE_WAKEON_PORT,          
                                                            /*!< Wake on port */
  API_PP_ULE_SLEEPMODE_WAKEON_TIMER          = ULP_SLEEPMODE_WAKEON_TIMER          
                                                            /*!< Wake on timer */
} RSENUM8(ApiPpUleSleepMode_t);

/*! ULE wakeup event type */
typedef enum RSENUMTAG(ApiPpUleWakeupEventType_t)
{
  API_PP_ULE_WAKEUP_EVENT_UNDEF   = 0, /*!< undefined */
  API_PP_ULE_WAKEUP_EVENT_NON_ULP = 1, /*!< non-ULE wakeup event ie. cold-start */
  API_PP_ULE_WAKEUP_EVENT_PORT    = 2, /*!< port-event */
  API_PP_ULE_WAKEUP_EVENT_TIMER   = 3  /*!< Timer-event */
} RSENUM8(ApiPpUleWakeupEventType_t);

/*! ULE suspend mode */
typedef enum RSENUMTAG(ApiPpUleSuspendMode_t)
{
  API_PP_ULE_SUSPEND_MODE_SLEEP     = ULP_MNG_SUSPEND_MODE_SLEEP,     /*!< Sleep mode */
  API_PP_ULE_SUSPEND_MODE_HIBERNATE = ULP_MNG_SUSPEND_MODE_HIBERNATE, /*!< Hibernate
                                                                         mode */
} RSENUM8(ApiPpUleSuspendMode_t);

/*! ULE time unit */
typedef enum RSENUMTAG(ApiPpUleTimeUnit_t)
{
  API_PP_ULE_TIME_UNIT_S   = 0, /*!< seconds */
  API_PP_ULE_TIME_UNIT_MS  = 3, /*!< milli-seconds */
  API_PP_ULE_TIME_UNIT_RAW = 7, /*!< raw , debug only */
} RSENUM8(ApiPpUleTimeUnit_t);

/*! ULE data link control */
typedef enum RSENUMTAG(ApiUleDlcCtrl_t)
{
  API_ULE_DLC_CTRL_UNACKNOWLEDGED        = 0, /*!< to send a packet with no
                                                 acknowledgement */
  API_ULE_DLC_CTRL_ACKNOWLEDGED          = 1, /*!< send a packet with acknowledgement */
  API_ULE_DLC_CTRL_ACKNOWLEDGED_FAST_ACK = 2, /*!< send a packet with acknowledgement.
                                                 The device will receive an extra frame
                                                 after transmission to receive
                                                 acknowledgment. */
} RSENUM8(ApiUleDlcCtrl_t);

/*! NVS client id */
typedef enum RSENUMTAG(ApiPpUleNvsClient_t)
{
  API_PP_ULE_NVS_CLIENT_APP = 0, /*!< Application-layer NVS client */
                                 /*!<  */
                                 /*!<  */
} RSENUM8(ApiPpUleNvsClientId_t);

/*! ULE-API error codes */
typedef enum RSENUMTAG(ApiPpUleError_t)
{
  API_PP_ULE_ERR_NO_ERROR           , /*!<  */
  API_PP_ULE_ERR_BUSY               , /*!<  */
  API_PP_ULE_ERR_BUFFER_OVERRUN     , /*!<  */
  API_PP_ULE_ERR_GLOBAL_ERROR       , /*!<  */
  API_PP_ULE_ERR_INTERFACE_MISMATCH , /*!<  */
  API_PP_ULE_ERR_UNSUPPORTED        , /*!<  */
  API_PP_ULE_ERR_RANGE_ERROR        , /*!<  */
  API_PP_ULE_ERR_NO_RESOURCES       , /*!<  */
  API_PP_ULE_ERR_DLC_NOT_READY      , /*!<  */
  API_PP_ULE_ERR_OVERSIZE_PACKET    , /*!<  */
  API_PP_ULE_ERR_UNKNOWN            , /*!<  */
  API_PP_ULE_ERR_MODE               , /*!<  */
  API_PP_ULE_ERR_UNLOCKED           , /*!<  */
  API_PP_ULE_ERR_CONNECTION         , /*!<  */
  API_PP_ULE_ERR_SIZE               , /*!<  */
  API_PP_ULE_ERR_COMMON_ERROR_COUNT , /*!<  */
  API_PP_ULE_ERR_TIMEOUT            , /*!<  */
  API_PP_ULE_ERR_NO_INSTANCE        , /*!<  */
  API_PP_ULE_ERR_NOT_LOCATED        , /*!<  */
  API_PP_ULE_ERR_NO_ACTIVE_SCALL    , /*!<  */
  API_PP_ULE_ERR_PVC_USER_REJ       , /*!<  */
  API_PP_ULE_ERR_PVC_SUSPENDED      , /*!<  */
  API_PP_ULE_ERR_FP_PVC_REQ         , /*!<  */
  API_PP_ULE_ERR_FP_PVC_SUSPENDED   , /*!<  */
  API_PP_ULE_ERR_FP_PVC_NONE_REJ    , /*!<  */
  API_PP_ULE_ERR_FP_PVC_SUSPEND_REJ , /*!<  */
  API_PP_ULE_ERR_FP_PVC_RESUME_REJ  , /*!<  */
  API_PP_ULE_ERR_PVC_MTU_PT_REJ     , /*!<  */
  API_PP_ULE_ERR_PVC_MTU_FT_REJ     , /*!<  */
  API_PP_ULE_ERR_PVC_WIN_REJ        , /*!<  */
  API_PP_ULE_ERR_PVC_LT_REJ         , /*!<  */
  API_PP_ULE_ERR_PVC_PID_REJ        , /*!<  */
  API_PP_ULE_ERR_FP_CCM             , /*!<  */
  API_PP_ULE_ERR_FP_PVC_IDENTITY_REJ , /*!<  */
} RSENUM8(ApiPpUleError_t);

/*! GPIO identifiers */
typedef enum RSENUMTAG(ApiPpUleGpioId_t)
{
  API_PP_ULE_GPIO_KEYB_SW1 = 1,    /*!< SW1 */
  API_PP_ULE_GPIO_KEYB_SW2 = 2,    /*!< SW2 */
  API_PP_ULE_GPIO_KEYB_3   = 4,    /*!< reserved */
  API_PP_ULE_GPIO_KEYB_4   = 8,    /*!< reserved */
  API_PP_ULE_GPIO_KEYB_5   = 16,   /*!< reserved */
  API_PP_ULE_GPIO_KEYB_6   = 32,   /*!< reserved */
  API_PP_ULE_GPIO_KEYB_7   = 64,   /*!< reserved */
  API_PP_ULE_GPIO_KEYB_8   = 0x80, /*!< reserved */
  API_PP_ULE_GPIO_ADC1     = 0x81, /*!< ADC1 */
  API_PP_ULE_GPIO_LED3     = 0x82, /*!< LED3 */
  API_PP_ULE_GPIO_LED4     = 0x83, /*!< LED4 */
  API_PP_ULE_GPIO_KEYB_INT = 0x84, /*!< Pseudo port for configuring keyboard interrupt */
  API_PP_ULE_GPIO_SWRESET  = 0x85, /*!< Pseudo port for doing a SW-RESET */
} RSENUM8(ApiPpUleGpioId_t);

/*! ULE dummy bearer paging mode */
typedef enum RSENUMTAG(ApiPpUleDbPageMode_t)
{
  API_ULE_DLC_DB_PAGE_MODE_0 = 0, /*!< Disable page mode */
  API_ULE_DLC_DB_PAGE_MODE_1 = 1, /*!< Enable paging, 10 ms scanning */
  API_ULE_DLC_DB_PAGE_MODE_2 = 2, /*!< Enable paging, 160 ms scanning */
  API_ULE_DLC_DB_PAGE_MODE_3 = 3, /*!< Enable paging, 640 ms scanning */
} RSENUM8(ApiPpUleDbPageMode_t);

/*! ULE protocol identifier */
typedef enum RSENUMTAG(ApiPpUleProtocolId_t)
{
  API_ULE_PROTOCOL_UNDEFINED   = 0,    /*!< Undefined protocol */
  API_ULE_PROTOCOL_FUN_1       = 1,    /*!< HAN/FUN protocol Ver. 1 */
  API_ULE_PROTOCOL_6LOWPAN     = 6,    /*!< 6LOWPAN */
  API_ULE_PROTOCOL_PROPRIETARY = 0x80, /*!< Proprietary protocol */
} RSENUM8(ApiPpUleProtocolId_t);

/*! ULE protocol version */
typedef enum RSENUMTAG(ApiPpUleProtocolVer_t)
{
  API_ULE_PROTOCOL_VERSION_0  = 0,    /*!< ULE protocol version 0 */
  API_ULE_PROTOCOL_VERSION_1  = 1,    /*!< ULE protocol version 1 */
  API_ULE_PROTOCOL_VERSION_7F = 0x7F, /*!< ULE protocol, version  0x7f  (max) */
} RSENUM8(ApiPpUleProtocolVer_t);

/*! ULE PVC configuration parameter for DLC window size */
typedef enum RSENUMTAG(ApiPpUleWindowSize_t)
{
  API_ULE_WINDOW_SIZE_MIN     = 8,  /*!< DLC minimum window size */
  API_ULE_WINDOW_SIZE_DEFAULT = 16, /*!< DLC default window size */
  API_ULE_WINDOW_SIZE_MAX     = 32, /*!< DLC maximum window size */
} RSENUM8(ApiPpUleWindowSize_t);

/*! ULE PVC configuration parameter for MTU size */
typedef enum RSENUMTAG(ApiPpUleMtuSize_t)
{
  API_ULE_MTU_SIZE_32   = 32,   /*!< MTU minimum size */
  API_ULE_MTU_SIZE_64   = 64,   /*!<  */
  API_ULE_MTU_SIZE_128  = 128,  /*!<  */
  API_ULE_MTU_SIZE_256  = 256,  /*!<  */
  API_ULE_MTU_SIZE_500  = 500,  /*!< Default ULE MTU size */
  API_ULE_MTU_SIZE_1280 = 1280, /*!< Minimum IPV6 MTU size */
} RSENUM16(ApiPpUleMtuSize_t);

/*! ULE PVC configuration parameter for MTU lifetime (determines number of
   retransmissions) */
typedef enum RSENUMTAG(ApiPpUleMtuLifetime_t)
{
  API_ULE_MTU_LIFETIME_MIN     = 1,    /*!< MTU minimum lifetime in frames */
  API_ULE_MTU_LIFETIME_3       = 3,    /*!<  */
  API_ULE_MTU_LIFETIME_DEFAULT = 7,    /*!< default */
  API_ULE_MTU_LIFETIME_15      = 15,   /*!<  */
  API_ULE_MTU_LIFETIME_MAX     = 1008, /*!< MTU  maximum lifetime in frames */
} RSENUM16(ApiPpUleMtuLifetime_t);

/*! ULE PVC configuration initiator */
typedef enum RSENUMTAG(ApiPpUlePvcInitiator_t)
{
  API_ULE_PP_INITIATOR =0, /*!< PP is supposed  to initiate service change */
  API_ULE_FP_INITIATOR =1, /*!< FP is supposed  to initiate service change */
} RSENUM8(ApiPpUlePvcInitiator_t);

/*! ULE PVC configuration initiator */
typedef enum RSENUMTAG(ApiPpUlePageCh_t)
{
  API_ULE_PP_BROADCAST_CH =1, /*!< This is a broadcast channel */
  API_ULE_FP_PAGING_CH    =2, /*!< This is a paging channel */
} RSENUM8(ApiPpUlePageCh_t);

/*! ULE resume activity */
typedef enum RSENUMTAG(ApiPpUleActivityStatus_t)
{
  API_PP_ULE_START_UNDEF               =0, /*!< Startup not defined or error */
  API_PP_ULE_START_DB_ERROR            =1, /*!< Error in Dummy bearer data */
  API_PP_ULE_START_APP_ONLY            =2, /*!< Only start Application */
  API_PP_ULE_START_PAGED               =3, /*!< Early page detected */
  API_PP_ULE_START_PAGE_ERR            =4, /*!< Could not determine if paged */
  API_PP_ULE_START_KEEP_ALIVE          =5, /*!< Keep alive cycle */
  API_PP_ULE_START_KEEP_ALIVE_PAGED    =6, /*!< Keep alive cycle and paged */
  API_PP_ULE_START_KEEP_ALIVE_PAGE_ERR =7, /*!< Keep alive cycle, don?t know if paged */
} RSENUM8(ApiPpUleActivityStatus_t);

/*! ULE paging channel parameters, Id and periodicity.                     
                                                    ( Id is calculated from
   frame start and bit offset  parameters  ) */
typedef struct ApiPpUlePage_t
{
  ApiPpUlePageCh_t  Descriptor;         /*!< Selects broadcast or paging */
  rsuint16  Id;                         /*!< Paging id */
  rsuint16  Period;                     /*!< Periodicity in frames */
} ApiPpUlePage_t;

/*! ULE activity counters, used to control what activity to run during a
   ULE resume cycle.                                                          
               (If  ResumeCount mod ?ActivityCounter?  == 0 then the activity
   is scheduled for activation. ) */
typedef struct ApiPpUleActivityCounters_t
{
  rsuint16  CheckPage;                  /*!< Early check for paging */
  rsuint16  StartApp;                   /*!< Only start application */
  rsuint16  KeepAlive;                  /*!< Start keep alive cycle */
} ApiPpUleActivityCounters_t;



/*! Mail without parameters. */
typedef struct ApippuleEmptySignalType
{
  RosPrimitiveType Primitive; /*!< Mail primitive. */
} ApippuleEmptySignalType;

/*! Initializes the ULE-API. It must be sent as the very first mail from
   the application to the ULE-API. ULE-API confirms the request by replying
   with a API_ULE_INIT_CFM. */
typedef struct ApiPpUleInitReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_INIT_REQ=0x5A00 */
  ApiPpUleMode_t Mode;                  /*!< Specifies off, unlocked or unlocked
                                           synchronous mode. */
  ApiPpUleSleepMode_t SleepMode;        /*!< wakeup  mode ie. wake on timer /port or
                                           both. */
  ApiPpUleSuspendMode_t SuspendMode;    /*!< suspend mode ie. sleep or hibernate.
                                           
                                           In hibernate mode the device is completely
                                           powered off and the lowest possible power
                                           consumption is achieved. */
  ApiPpUleActivityCounters_t ActivityCounters; /*!< Used to control resume actions */
} ApiPpUleInitReqType;

/*! Confirms that the ULE-API has been initialized and provides information
   about startup type and activity status.  These messages also contain
   performance and debug information, that normally can be ignored. */
typedef struct ApiPpUleInitCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_INIT_CFM=0x5A01 */
  rsbool IsUlpWakeup;                   /*!< Indicates whether startup was a ULE wake-up
                                           or cold boot. */
  ApiPpUleWakeupEventType_t WakeupEvent; /*!< Wakeup event type */
  ApiPpUleActivityStatus_t ActivityStatus; /*!< Activity status */
  rsuint8 BpaStatus;                    /*!< Performance data for BPA  (For debug usage) */
  rsuint16 ResumeCounter;               /*!< Activity counter */
  rsuint16 DbgDataLength;               /*!< Length of debug data   (default =0) */
  rsuint8* DbgDataPtr;                  /*!< Pointer to debug data  (default= NULL) */
} ApiPpUleInitCfmType;

/*! Used to setup the ULE protocol data, shall only be sent after the ULE
   API is initialized.
    During the ULE protocol configuration other mails may be received or
   transmitted as part of the PVC configuration, see MSC for description. */
typedef struct ApiPpUlePvcConfigReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_PVC_CONFIG_REQ=0x5A27 */
  ApiPpUleProtocolId_t ProtocolId;      /*!< 0 undefined protocol 
                                           1 ULE FUN #1 protocol
                                           >127 Proprietary ULE protocol */
  ApiPpUleProtocolVer_t ProtocolVer;    /*!< 7 bit Protocol version number, default  0 */
  rsuint16 Emc;                         /*!< EMC code if an  proprietary protocol is
                                           used */
  ApiPpUleMtuSize_t MtuPtSize;          /*!< MTU size in PT->FT direction */
  ApiPpUleMtuSize_t MtuFtSize;          /*!< MTU size in FT->PT direction */
  ApiPpUleMtuLifetime_t MtuLifetime;    /*!< MAC layer maximum  lifetime */
  ApiPpUleWindowSize_t WindowSize;      /*!< DLC layer window size */
  ApiPpUlePvcInitiator_t Initiator;     /*!< Initiator  PT=0,   FT otherwise  (default
                                           PT) */
} ApiPpUlePvcConfigReqType;

/*! Received  if and when the PVC configuration succeeded */
typedef struct ApiPpUlePvcConfigCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_PVC_CONFIG_CFM=0x5A28 */
  ApiPpUleProtocolVer_t ProtocolVer;    /*!< Peer Protocol version */
  ApiPpUleMtuSize_t MtuPtSize;          /*!< MTU size in PT->FT direction */
  ApiPpUleMtuSize_t MtuFtSize;          /*!< MTU size in FT->PT direction */
  ApiPpUleMtuLifetime_t MtuLifetime;    /*!< MAC layer maximum  lifetime */
  ApiPpUleWindowSize_t WindowSize;      /*!< DLC layer window size */
  ApiPpUlePage_t Page_1;                /*!< Paging channel 1 */
  ApiPpUlePage_t Page_2;                /*!< Paging Channel 2 */
} ApiPpUlePvcConfigCfmType;

/*! Received if the PVC configuration failed. */
typedef struct ApiPpUlePvcConfigRejType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_PVC_CONFIG_REJ=0x5A29 */
  ApiPpUleError_t Reason;               /*!< Indicates why the PVC configuration failed */
  rsuint16 Value;                       /*!< If  possible, value of rejected parameter */
} ApiPpUlePvcConfigRejType;

/*! Received if PVC needs a new configuration or a reconfiguration. */
typedef struct ApiPpUlePvcConfigIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_PVC_CONFIG_IND=0x5A2E */
  ApiPpUleError_t Reason;               /*!< Indicates why the PVC configuration is
                                           needed */
} ApiPpUlePvcConfigIndType;

/*! Received during PVC configuration, indicates that proprietary protocol
   configuration can be started. */
typedef struct ApiPpUlePvcPendingIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_PVC_PENDING_IND=0x5A2A */
  ApiPpUleProtocolId_t ProtocolId;      /*!< ID of the ULE selected protocol */
} ApiPpUlePvcPendingIndType;

/*! Send when the proprietary configuration is done. */
typedef struct ApiPpUlePvcPendingResType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_PVC_PENDING_RES=0x5A2B */
  ApiPpUleError_t Status;               /*!< If no errors then PVC configuration is
                                           continued, otherwise the configuration is
                                           terminated and the API_PP_ULE_PVC_CONFIG_REJ
                                           primitive is send to the API. */
} ApiPpUlePvcPendingResType;

/*! Transmitted during the proprietary protocol configuration */
typedef struct ApiPpUlePvcIwuDataReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_PVC_IWU_DATA_REQ=0x5A2C */
  rsuint16 InfoElementLength;           /*!< Data length */
  rsuint8 InfoElement[1];               /*!< Data */
} ApiPpUlePvcIwuDataReqType;

/*! Received during the proprietary protocol configuration */
typedef struct ApiPpUlePvcIwuDataIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_PVC_IWU_DATA_IND=0x5A2D */
  rsuint16 InfoElementLength;           /*!< Data length */
  rsuint8 InfoElement[1];               /*!< Data */
} ApiPpUlePvcIwuDataIndType;

/*!  */
typedef struct ApiPpUleSetupAgainIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_SETUP_AGAIN_IND=0x5A2F */
  rsuint16 Delay;                       /*!< Delay in ms */
} ApiPpUleSetupAgainIndType;

/*!  */
typedef struct ApiPpUleStartLocateIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_START_LOCATE_IND=0x5A30 */
} ApiPpUleStartLocateIndType;

/*!  */
typedef struct ApiPpUleHighPagingModeIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_HIGH_PAGING_MODE_IND=0x5A31 */
  rsuint16 Delay;                       /*!< Delay in ms */
} ApiPpUleHighPagingModeIndType;

/*!  */
typedef struct ApiPpUleLcePagingModeIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_LCE_PAGING_MODE_IND=0x5A32 */
  ApiPpUleDbPageMode_t PagingMode;      /*!< Paging mode */
  rsuint16 Delay;                       /*!< Delay in ms */
} ApiPpUleLcePagingModeIndType;

/*! Received during the proprietary protocol configuration */
typedef struct ApiPpUleStartVoiceCallIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_START_VOICE_CALL_IND=0x5A33 */
} ApiPpUleStartVoiceCallIndType;

/*!  */
typedef struct ApiPpUleInfoReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_INFO_REQ=0x5A08 */
} ApiPpUleInfoReqType;

/*!  */
typedef struct ApiPpUleInfoCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_INFO_CFM=0x5A09 */
  ApiPpUleMode_t Mode;
  rsuint32 UlpTimer;
} ApiPpUleInfoCfmType;

/*!  */
typedef struct ApiPpUleSubsStatusReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_SUBS_STATUS_REQ=0x5A1E */
} ApiPpUleSubsStatusReqType;

/*!  */
typedef struct ApiPpUleSubsStatusCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_SUBS_STATUS_CFM=0x5A1F */
  RsStatusType Status;                  /*!< RSS_SUCCESS: Subscription
                                           exists.
RSS_NO_DATA: No subscription. */
} ApiPpUleSubsStatusCfmType;

/*!  */
typedef struct ApiPpUleSubsDeleteReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_SUBS_DELETE_REQ=0x5A20 */
} ApiPpUleSubsDeleteReqType;

/*!  */
typedef struct ApiPpUleSubsDeleteCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_SUBS_DELETE_CFM=0x5A21 */
} ApiPpUleSubsDeleteCfmType;

/*! Enable paging on dummy bearer */
typedef struct ApiPpUleDbPageEnableReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_DB_PAGE_ENABLE_REQ=0x5A22 */
  ApiPpUleDbPageMode_t Mode;            /*!< Enable page mode and set scanning interval */
} ApiPpUleDbPageEnableReqType;

/*! Requests a new location-registration. */
typedef struct ApiPpUleLocateReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_LOCATE_REQ=0x5A07 */
} ApiPpUleLocateReqType;

/*! Locate registration was rejected,  failed or PP unlocked */
typedef struct ApiPpUleLocateRejType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_LOCATE_REJ=0x5A34 */
} ApiPpUleLocateRejType;

/*!  */
typedef struct ApiPpUleDbPageEnableCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_DB_PAGE_ENABLE_CFM=0x5A23 */
  RsStatusType Status;                  /*!< RSS_SUCCESS:  Paging is enabled */
} ApiPpUleDbPageEnableCfmType;

/*! Used by the application when it is ready to enter sleep mode, at this
   time all non volatile data will be lost if suspend mode is hibernation. If
   a data transmit is pending the application layer should wait on the
   following API_PP_ULE_DTR_IND before suspending */
typedef struct ApiPpUleSuspendReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_SUSPEND_REQ=0x5A0B */
  rsuint32 time;                        /*!< suspend time i.e sleep time,in seconds or
                                           milli-seconds. */
  ApiPpUleTimeUnit_t time_unit;         /*!< Time unit */
  ApiPpUlePortDirMode_t PortDirMode;    /*!< ULP port direction mode. */
  ApiPpUlePortTrigMode_t PortTrigMode;  /*!< ULP port trigger mode.
                                            */
} ApiPpUleSuspendReqType;

/*! Indicates that the device for some reason is unable to restore lock
   after being resumed.
    A typical response is to issue a new Lock request or if the device not is
   enrolled a new registration request. */
typedef struct ApiPpUleResumeErrorIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_RESUME_ERROR_IND=0x5A26 */
} ApiPpUleResumeErrorIndType;

/*! NVS-data read request. ULE-API confirms the request by replying with a
   API_ULE_HIBERNATE_READ_CFM containing the NVS-data ? if any. */
typedef struct ApiPpUleHibernateReadReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_HIBERNATE_READ_REQ=0x5A0E */
  ApiPpUleNvsClientId_t nvs_client_id;  /*!< API_PP_ULE_NVS_CLIENT_APP */
} ApiPpUleHibernateReadReqType;

/*! NVS data read confirm. */
typedef struct ApiPpUleHibernateReadCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_HIBERNATE_READ_CFM=0x5A0F */
  ApiPpUleNvsClientId_t nvs_client_id;  /*!< API_PP_ULE_NVS_CLIENT_APP */
  rsuint8 Length;                       /*!< Length of data */
  rsuint8 Data[1];
} ApiPpUleHibernateReadCfmType;

/*! NVS-data write request. ULE-API confirms the request by replying with a
   API_ULE_HIBERNATE_WRITE_CFM.  Notice that this mail should be sent before
   issuing a suspend request (API_PP_SUSPEND_REQ). */
typedef struct ApiPpUleHibernateWriteReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_HIBERNATE_WRITE_REQ=0x5A10 */
  ApiPpUleNvsClientId_t nvs_client_id;  /*!< API_PP_ULE_NVS_CLIENT_APP */
  rsuint8 Length;                       /*!< Length of data */
  rsuint8 Data[1];
} ApiPpUleHibernateWriteReqType;

/*! NVS data write confirm. */
typedef struct ApiPpUleHibernateWriteCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_HIBERNATE_WRITE_CFM=0x5A11 */
  ApiPpUleNvsClientId_t nvs_client_id;  /*!< API_PP_ULE_NVS_CLIENT_APP */
} ApiPpUleHibernateWriteCfmType;

/*! Indicates that the ULE-API/protocol is ready for the first data
   transmission. After wake-Up the application layer should wait on this mail
   before transmitting any data. */
typedef struct ApiPpUleReadyIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_READY_IND=0x5A15 */
} ApiPpUleReadyIndType;

/*! Indicates that the ULE-API/protocol is ready for data transmit.  This
   mail is a confirmation, on a pending API_PP_ULE_DATA_REQ. 
    The Release reason can contain request to delay or to start some
   procedure, see description of DTR handling TBD
    The application layer shall wait on this mail after data is transmitted,
   and before suspend is called. */
typedef struct ApiPpUleDtrIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_DTR_IND=0x5A16 */
  ApiPpUleError_t
 Status;              /*!< Result of pending data transmission.
                                           API_PP_ULE_ERR_NO_ERROR:  Data was Acknowledged.
                                           All other means Data was not Acknowledged. */
} ApiPpUleDtrIndType;

/*! This mail indicates that data has been received from the PP.
    
    Notice that in ?unlocked mode? it?s necessary first to send an
   API_PP_ULE_DATA_REQ. In future versions of the SDK this might be changed. */
typedef struct ApiPpUleDataIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_DATA_IND=0x5A17 */
  rsbool ReadyToTransmit;               /*!< Indicates whether the ULE-API is ready for
                                           data transmit or not */
  rsuint16 Length;                      /*!< Length of data */
  rsuint8 Data[1];
} ApiPpUleDataIndType;

/*! This mail is used by the API for sending data to the PP. */
typedef struct ApiPpUleDataReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_DATA_REQ=0x5A18 */
  ApiUleDlcCtrl_t DlcCtrl;              /*!< Data link control. Specifies whether data
                                           transmission should be acknowledged or not. */
  rsuint16 Length;                      /*!< Length of data */
  rsuint8 Data[1];
} ApiPpUleDataReqType;

/*! This mail is used by the API for sending data confirmation to the PP. */
typedef struct ApiPpUleDataCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_DATA_CFM=0x5A25 */
  ApiPpUleError_t Result;               /*!< RSS_SUCCESS if data is accepted for
                                           transmission otherwise an error code that
                                           indicates why data couldn?t be transmitted. */
} ApiPpUleDataCfmType;

/*! This mail is used by the API for sending Dummy Bearer page indication 
   to the PP. */
typedef struct ApiPpUleDbPageIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_DB_PAGE_IND= 0x5A24 */
  rsuint8 PageId;                       /*!< BitOffset  that triggered this paging
                                           message 
                                           See A.2.1 in ETSI- TS 102-939-1 */
} ApiPpUleDbPageIndType;

/*! Set a  GPIO port. */
typedef struct ApiPpUleHalSetPortReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_HAL_SET_PORT_REQ=0x5A1A */
  ApiPpUleGpioId_t gpio_id;             /*!< GPIO identifier */
  rsuint16 value;                       /*!< port value */
} ApiPpUleHalSetPortReqType;

/*! Request current status for aGPIO port */
typedef struct ApiPpUleHalGetPortReqType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_HAL_GET_PORT_REQ=0x5A1B */
  ApiPpUleGpioId_t gpio_id;             /*!< GPIO identifier */
} ApiPpUleHalGetPortReqType;

/*! Confirmation about the specified GPIO port */
typedef struct ApiPpUleHalGetPortCfmType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_HAL_GET_PORT_CFM=0x5A1C */
  ApiPpUleGpioId_t gpio_id;             /*!< GPIO identifier */
  rsuint16 value;                       /*!< Port value */
} ApiPpUleHalGetPortCfmType;

/*! Indication from a GPIO port */
typedef struct ApiPpUleHalPortIndType
{
  RosPrimitiveType Primitive;            /*!< API_PP_ULE_HAL_PORT_IND=0x5A1D */
  ApiPpUleGpioId_t gpio_id;             /*!< GPIO identifier */
  rsuint16 value;                       /*!< Port value */
} ApiPpUleHalPortIndType;

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
* FUNCTION:      SendApiPpUleInitReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_INIT_REQ=0x5A00
****************************************************************************/
void SendApiPpUleInitReq ( RosTaskIdType Src,
                           ApiPpUleMode_t Mode,              /*!< Specifies off,
                                                                unlocked or unlocked
                                                                synchronous mode. */
                           ApiPpUleSleepMode_t SleepMode,    /*!< wakeup  mode ie. wake
                                                                on timer /port or both. */
                           ApiPpUleSuspendMode_t SuspendMode,
                                                             /*!< suspend mode ie. sleep
                                                                or hibernate.
                                                                
                                                                In hibernate mode the
                                                                device is completely powered
                                                                off and the lowest possible
                                                                power consumption is
                                                                achieved. */
                           ApiPpUleActivityCounters_t ActivityCounters);
                                                             /*!< Used to control resume
                                                                actions */

/****************************************************************************
* FUNCTION:      SendApiPpUlePvcConfigReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_PVC_CONFIG_REQ=0x5A27
****************************************************************************/
void SendApiPpUlePvcConfigReq ( RosTaskIdType Src,
                                ApiPpUleProtocolId_t ProtocolId,
                                                             /*!< 0 undefined protocol 
                                                                1 ULE FUN #1 protocol
                                                                >127 Proprietary ULE
                                                                protocol */
                                ApiPpUleProtocolVer_t ProtocolVer,
                                                             /*!< 7 bit Protocol version
                                                                number, default  0 */
                                rsuint16 Emc,                /*!< EMC code if an 
                                                                proprietary protocol is used */
                                ApiPpUleMtuSize_t MtuPtSize,  /*!< MTU size in PT->FT
                                                                 direction */
                                ApiPpUleMtuSize_t MtuFtSize,  /*!< MTU size in FT->PT
                                                                 direction */
                                ApiPpUleMtuLifetime_t MtuLifetime,
                                                             /*!< MAC layer maximum 
                                                                lifetime */
                                ApiPpUleWindowSize_t WindowSize,
                                                             /*!< DLC layer window size */
                                ApiPpUlePvcInitiator_t Initiator);
                                                             /*!< Initiator  PT=0,   FT
                                                                otherwise  (default PT) */

/****************************************************************************
* FUNCTION:      SendApiPpUlePvcPendingRes
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_PVC_PENDING_RES=0x5A2B
****************************************************************************/
void SendApiPpUlePvcPendingRes ( RosTaskIdType Src,
                                 ApiPpUleError_t Status);    /*!< If no errors then PVC
                                                                configuration is continued,
                                                                otherwise the configuration
                                                                is terminated and the
                                                                API_PP_ULE_PVC_CONFIG_REJ
                                                                primitive is send to the
                                                                API. */

/****************************************************************************
* FUNCTION:      SendApiPpUlePvcIwuDataReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_PVC_IWU_DATA_REQ=0x5A2C
****************************************************************************/
void SendApiPpUlePvcIwuDataReq ( RosTaskIdType Src,
                                 rsuint16 InfoElementLength,  /*!< Data length */
                                 rsuint8 InfoElement[1]);    /*!< Data */

/****************************************************************************
* FUNCTION:      SendApiPpUleInfoReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_INFO_REQ=0x5A08
****************************************************************************/
void SendApiPpUleInfoReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpUleSubsStatusReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_SUBS_STATUS_REQ=0x5A1E
****************************************************************************/
void SendApiPpUleSubsStatusReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpUleSubsDeleteReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_SUBS_DELETE_REQ=0x5A20
****************************************************************************/
void SendApiPpUleSubsDeleteReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpUleDbPageEnableReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_DB_PAGE_ENABLE_REQ=0x5A22
****************************************************************************/
void SendApiPpUleDbPageEnableReq ( RosTaskIdType Src,
                                   ApiPpUleDbPageMode_t Mode);
                                                             /*!< Enable page mode and
                                                                set scanning interval */

/****************************************************************************
* FUNCTION:      SendApiPpUleLocateReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_LOCATE_REQ=0x5A07
****************************************************************************/
void SendApiPpUleLocateReq ( RosTaskIdType Src );


/****************************************************************************
* FUNCTION:      SendApiPpUleSuspendReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_SUSPEND_REQ=0x5A0B
****************************************************************************/
void SendApiPpUleSuspendReq ( RosTaskIdType Src,
                              rsuint32 time,                 /*!< suspend time i.e sleep
                                                                time,in seconds or
                                                                milli-seconds. */
                              ApiPpUleTimeUnit_t time_unit,  /*!< Time unit */
                              ApiPpUlePortDirMode_t PortDirMode,
                                                             /*!< ULP port direction
                                                                mode. */
                              ApiPpUlePortTrigMode_t PortTrigMode);
                                                             /*!< ULP port trigger mode.
                                                                 */

/****************************************************************************
* FUNCTION:      SendApiPpUleHibernateReadReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_HIBERNATE_READ_REQ=0x5A0E
****************************************************************************/
void SendApiPpUleHibernateReadReq ( RosTaskIdType Src,
                                    ApiPpUleNvsClientId_t nvs_client_id);
                                                             /*!<
                                                                API_PP_ULE_NVS_CLIENT_APP */

/****************************************************************************
* FUNCTION:      SendApiPpUleHibernateWriteReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_HIBERNATE_WRITE_REQ=0x5A10
****************************************************************************/
void SendApiPpUleHibernateWriteReq ( RosTaskIdType Src,
                                     ApiPpUleNvsClientId_t nvs_client_id,
                                                             /*!<
                                                                API_PP_ULE_NVS_CLIENT_APP */
                                     rsuint8 Length,         /*!< Length of data */
                                     rsuint8 Data[1]);       /*!<  */

/****************************************************************************
* FUNCTION:      SendApiPpUleDataReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_DATA_REQ=0x5A18
****************************************************************************/
void SendApiPpUleDataReq ( RosTaskIdType Src,
                           ApiUleDlcCtrl_t DlcCtrl,          /*!< Data link control.
                                                                Specifies whether data
                                                                transmission should be
                                                                acknowledged or not. */
                           rsuint16 Length,                  /*!< Length of data */
                           rsuint8 Data[1]);                 /*!<  */

/****************************************************************************
* FUNCTION:      SendApiPpUleHalSetPortReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_HAL_SET_PORT_REQ=0x5A1A
****************************************************************************/
void SendApiPpUleHalSetPortReq ( RosTaskIdType Src,
                                 ApiPpUleGpioId_t gpio_id,   /*!< GPIO identifier */
                                 rsuint16 value);            /*!< port value */

/****************************************************************************
* FUNCTION:      SendApiPpUleHalGetPortReq
* DESCRIPTION:   MPS function for sending mails with primitive:
*                API_PP_ULE_HAL_GET_PORT_REQ=0x5A1B
****************************************************************************/
void SendApiPpUleHalGetPortReq ( RosTaskIdType Src,
                                 ApiPpUleGpioId_t gpio_id);  /*!< GPIO identifier */

/** \endcond */
#ifdef __cplusplus
}
#endif
#endif /*APIPPULE_H */


