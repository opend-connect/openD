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

#ifndef REPSTYPES_H
#define REPSTYPES_H

/****************************************************************************
*                               Include files
****************************************************************************/


/****************************************************************************
*                              Macro definitions
****************************************************************************/

#define EAP_USB_SERIAL_SIZE 50U

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

// Reps error codes
typedef enum
{
  REPS_ERROR_SUCCESS = 0,
  // returned from write operations if no space free. Returned from
  // read operations if no data available
  REPS_ERROR_NO_DATA,
  // the program id is already in use
  REPS_ERROR_PID_TAKEN,
  REPS_ERROR_SERVER_NOT_FOUND,
  REPS_ERROR_OUT_OF_MEMORY,
  // the connection to the server was lost
  REPS_ERROR_BROKEN_CONNECTION,
  // one of the resources needed for communication was impossible to
  // create/open, or it already existed in an context where it should
  // not exist
  REPS_ERROR_RESOURCE_CONFLICT,
  // the shared memory name was too long
  REPS_ERROR_NAME_TOO_LONG,
  // the server did not respond to the client request event within the
  // timeout
  REPS_ERROR_SERVER_TIMEOUT,
  // returned by the client if a wrong version number is reported in
  // the shared memory header.
  REPS_ERROR_VERSION_CONFLICT,
  // returned by the client if the server refuses a connection.
  REPS_ERROR_CONNECTION_REFUSED,
  // returned by the client if the PID is out of range
  REPS_ERROR_UNSUPPORTED_PID,
  // returned if the client failed to start the REPS program
  REPS_ERROR_FAILED_TO_START_SERVER,
  // returned if the client failed to stop the REPS program
  REPS_ERROR_FAILED_TO_STOP_SERVER,
  // returned if the server failed to set and open the TL requested by the client
  REPS_ERROR_FAILED_TO_SET_TL,
  // returned if the server failed to set and open the TL requested by the client because the TL specified is busy
  REPS_ERROR_FAILED_TO_SET_TL_BUSY,
  // returned if the tl type selected by the client is invalid
  REPS_ERROR_INVALID_TL,
  // returned if the client failed to get the current TL configuration form the server
  REPS_ERROR_FAILED_TO_GET_TL,
  // returned if the client failed to get the server version
  REPS_ERROR_FAILED_TO_GET_VERSION,
  // unspecified error
  REPS_ERROR_UNSPECIFIED
} RepsErrorEnum;
typedef uint32 RepsErrorType;

typedef struct
{
  uint8 IP[16];       // Specifies the IP e.g."127.0.0.1"
  uint32 Port;        // Specifies the TCP/IP port to use.
  uint32 Protocol;    // Specifies the protocol used on top of TCP/IP.
                      // 0: Raw EAP data format
                      // 1: TI GSM data format
  uint32 Id;          // TI GSM Trace ID
  uint32 Options;     // Option bit field.
                      // bit 0: Ignore EAP checksum (1).
                      // bit 1-31: Reserved. Must be set to 0.
  uint32 SocketType;  // Specifes if the socket is a client or server socket. If server socket, the IP is not used
                      // 0: Client socket
                      // 1: Server socket
} RepsSocketCfgType;

typedef enum
{
  TLTYPE_DISABLED,
  TLTYPE_UART,
  TLTYPE_UNIUSB,
  TLTYPE_FLEXUSB,
  TLTYPE_LOOP,
  TLTYPE_REPS_CLIENT,
  TLTYPE_SOCKET,
  TLTYPE_USBHID,
  TLTYPE_MAX
} RepsTlIdEnum;
typedef uint32 RepsTlIdType;

typedef struct
{
  uint32 Port;
  uint32 BaudRate;
  union
  {
    struct
    {
      uint32 Parity      : 2; // 0-2 = none,odd,even
      uint32 StopBits    : 2; // 1,2 = 1, 2
      uint32 Cts         : 1; // 0,1 = CTS output flow control off or on
      uint32 Rts         : 2; // 0=low-level driver, 1=high-level driver, 2=manual (RTS high), 3=manual (RTS low).
      uint32 Reserved    : 25;
    } Bits;
    uint32 Val;
  } PortCfg;
  uint32 PacketBasedFlowControl; // 0,1 = Packet based flow control off,on
  uint32 RetransmitTimeout; // Retransmit time out in ms. Used with Packet based flow control only
  uint32 RetransmitCount; // Max number of retransmissions performed. Used with Packet based flow control only
  uint32 SingleWire; // 0,1 = Single Wire UART interface off,on
  uint32 WindowBasedFlowControl; // 0,1 = Window based flow control off,on
} RepsUartCfgType;

typedef struct
{
  uint32 Magic; // 0xCAFEBABE.
  uint16 Vid;
  uint16 Pid;
  char Serial[EAP_USB_SERIAL_SIZE];
} RepsUsbCfgType;

typedef union
{
  uint32 Magic; // if 0xCAFEBABE => UsbCfg.
  struct
  {
    RepsUartCfgType UartCfg; // TLTYPE_UART
    uint32 ClientPid;        // TLTYPE_REPS_CLIENT
    RepsSocketCfgType SocketCfg;   // TLTYPE_SOCKET
  };
  RepsUsbCfgType UsbConfig;  // TLTYPE_USBHID
} RepsTlParametersType;

typedef struct
{
  uint32 Major;
  uint32 Minor;
  uint32 Build;
  uint32 CheckedBuild;
} RepsVersionInfoType;

/****************************************************************************
*                           Global variables/const
****************************************************************************/


/****************************************************************************
*                             Function prototypes
****************************************************************************/

#endif // REPSTYPES_H
