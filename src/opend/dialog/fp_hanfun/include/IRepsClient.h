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

#ifndef IREPSCLIENT_H
#define IREPSCLIENT_H

/****************************************************************************
*                               Include files
****************************************************************************/

#ifdef INCLUDE_RTX_MODULES
  #include <Modules\Interfaces\RepsClient\RepsTypes.h>
#else
  #ifndef RTXDEF_H
  typedef unsigned char uint8;
  typedef signed char int8;
  typedef unsigned short uint16;
  typedef short int16;
  typedef unsigned long uint32;
  typedef long int32;

  typedef unsigned int umin8;
  typedef unsigned int umin16;
  typedef unsigned int umin32;
  #endif
  #ifndef RS_STANDARD_H
  typedef unsigned char rsuint8;
  typedef unsigned short rsuint16;
  typedef unsigned long rsuint32;
  #endif
  #ifndef ROS_TASKID_NONE
  typedef unsigned char RosTaskIdType;
  #define ROS_TASKID_NONE ((RosTaskIdType)-1)
  #endif

  #include "RepsTypes.h"
#endif

/****************************************************************************
*                              Macro definitions
****************************************************************************/
#ifdef STATIC_LOAD_DLL
   #define FUNC(rettype,name) __declspec(dllimport) rettype CALLBACK name
#else
  #ifdef REPSCLIENT_EXPORTS
    #define FUNC(rettype,name) __declspec(dllexport) rettype CALLBACK name
  #else
    #ifdef REPSCLIENT_VARS
      #define FUNC(rettype,name) rettype (CALLBACK* name)
    #else
      #define FUNC(rettype,name) extern rettype (CALLBACK* name)
    #endif
  #endif
#endif

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/


typedef uint8 RepsProgramIdType;


typedef struct RepsClientType
{
  // This manual-reset event is signaled by the server when data is
  // available for read in the uplink buffer. The application must
  // read the buffer until it is empty /after/ resetting the event
  // to unblock correctly on this event. Due to the way concurrency
  // is handled, the event may be in the signaled state even if no
  // data is ready in the buffer. The server signals the event every
  // time a buffer (may comprise several packets returned by
  // RepsGetPacketFromServer) is filled, but the application may
  // have read the data before waiting for the event. This event
  // will also be signaled at server shutdown. In that case calls to
  // the data transport functions will return
  // REPS_ERROR_BROKEN_CONNECTION.
  HANDLE UlDataInEvent;

  // This manual-reset event is signaled by the server when data can
  // be written to the downlink buffer. The application must have
  // received "buffer full" in a RepsSendPacketToServer call /after/
  // clearing this event in order to unblock correctly on this event
  // the next time. Due to the way concurrency is handled, the event
  // may be signaled even if no space is free. The server signals
  // the event every time space is freed, but the application's
  // write routine may have used that space before waiting for this
  // event. This event will also be signaled at server shutdown. In
  // that case calls to the data transport functions will return
  // REPS_ERROR_BROKEN_CONNECTION.
  HANDLE DlFreeSpaceEvent;

  // This pointer is reserved for internal use, it may not be accessed
  // by the application.
  void * Private;
} RepsClientType;


typedef enum
{
  REPS_SF_NONE                   = 0x00000000,
  REPS_SF_READ_INIFILE           = 0x00000001,
  REPS_SF_STEALTH_MODE           = 0x00000002,
  REPS_SF_NO_MESSAGES_LOG        = 0x00000004,
  REPS_SF_LOG_BIN_DATA           = 0x00000008,
  REPS_SF_LOG_TXT_DATA           = 0x00000010,
  REPS_SF_LOG_TXT_DATA_TO_SCREEN = 0x00000020
} RepsStartFlagsEnum;
typedef uint32 RepsStartFlagsType;

#ifndef RTXDEF_H
#pragma pack(push, 1)
#else
#include <Modules\Defines\Align1.h>
#endif

typedef struct
{
  RepsProgramIdType ProgramId;
  uint8 TaskId;
  union
  {
    uint8 Data[65536];
    uint16 Message;
  } Message;
} RepsEapMessageType;

#ifndef RTXDEF_H
#pragma pack(pop)
#else
#include <Modules\Defines\AlignDef.h>
#endif

/****************************************************************************
*                           Global variables/const
****************************************************************************/


/****************************************************************************
*                             Function prototypes
****************************************************************************/

#ifdef __cplusplus
extern "C" {
  #endif

  ULONG CALLBACK RepsClientLoadDll(const char * DllName);
  VOID CALLBACK RepsClientUnloadDll(VOID);

  /****************************************************************************
   *  FUNCTION: RepsConnectLocal
   *
   *  INPUTS:
   *
   *       ServerShmName: Name of shared memory segment created by the
   *       server.
   *
   *       ProgramId: The program ID to associate with the
   *       connection. Supported values are 0-255, other values are
   *       reserved for future extensions.
   *
   *  OUTPUTS:
   *
   *        ErrorDest: If the function fails, an error code is
   *        written to to this address
   *
   *  RETURNS: Pointer to a structure for maintaining connection
   *  state. NULL if the function fails
   *
   *  DESCRIPTION: Creates a connection to the server. The returned
   *  strucuture can be used in subsequent calls to the send/receive
   *  functions. After a successful connection the server will forward
   *  all EAP packets matching the specified program id to this client.
   ****************************************************************************/
   FUNC(RepsClientType*, RepsConnectLocal)(RepsErrorType* ErrorDest, const char* ServerShmName, RepsProgramIdType ProgramId);

  /****************************************************************************
   *  FUNCTION: RepsConnectLocalAutoPid
   *
   *  INPUTS:
   *
   *       ServerShmName: Name of shared memory segment created by
   *       the server.
   *
   *  OUTPUTS:
   *
   *       ErrorDest: If the function fails, an error code is
   *       written to to this address.
   *
   *       ProgramId: If successful, the automatically allocated progam
   *       id is written to this address
   *
   *  RETURNS: Pointer to a structure for maintaining connection
   *  state. NULL if the function fails
   *
   *  DESCRIPTION: Creates a connection to the server. The returned
   *  strucuture can be used in subsequent calls to the send/receive
   *  functions. After a successful connection the server will forward
   *  all EAP packets matching the allocated program id to this
   *  client. This function automatically allocates an unused program
   *  ID to the client.
   ****************************************************************************/
  FUNC(RepsClientType*, RepsConnectLocalAutoPid)(RepsErrorType* ErrorDest, const char* ServerShmName, RepsProgramIdType* ProgramId);

  /****************************************************************************
   *  FUNCTION: RepsDisconnect
   *
   *  INPUTS:
   *
   *       Ci: pointer to the connection state data.
   *
   *  OUTPUTS: None
   *
   *  RETURNS: void
   *
   *  DESCRIPTION: Disconnects a connection to the server. Ci is
   *  invalid after this call. Please note that this function hits a
   *  two second timeout if the server has been terminated before the
   *  client disconnected the connection to the server.
   ****************************************************************************/
  FUNC(void, RepsDisconnect)(RepsClientType* Ci);

  /****************************************************************************
   *  FUNCTION: RepsSendPacketToServer
   *
   *  INPUTS:
   *
   *       Ci: the connection to use
   *       packet: the address of the data to be sent
   *       Size: the size of the packet to be sent
   *
   *  OUTPUTS: None
   *
   *  RETURNS: REPS_ERROR_SUCCESS if successful, otherwise a reps
   *  error code. If the buffer is full, the function returns
   *  REPS_ERROR_NO_DATA.
   *
   *  DESCRIPTION: This function tries to send a packet on the
   *  connection identified by Ci. If the function returns an error
   *  code other than REPS_ERROR_NO_DATA or REPS_ERROR_SUCCESS, the
   *  connection should be disconnected. REPS_ERROR_NO_DATA is returned if
   *  the TX buffer is full, and the packet is not sent in this case.
   ****************************************************************************/
  FUNC(RepsErrorType, RepsSendPacketToServer)(RepsClientType* Ci, const RepsEapMessageType* packet, uint32 Size);

  /****************************************************************************
   *  FUNCTION: RepsSendPendingPacketsToServer
   *
   *  INPUTS:
   *
   *       Ci: pointer to the connection state data.
   *
   *  OUTPUTS: None
   *
   *  RETURNS: REPS_ERROR_SUCCESS if successful, otherwise a reps
   *  error code.
   *
   *  DESCRIPTION: This function delivers pending packetes on the connection
   *  identified by Ci. If the function returns an error code other than
   *  REPS_ERROR_NO_DATA or REPS_ERROR_SUCCESS, the connection should be
   *  disconnected. REPS_ERROR_NO_DATA is returned if no data was pending in the
   *  TX buffer.
   ****************************************************************************/
  FUNC(RepsErrorType, RepsSendPendingPacketsToServer)(RepsClientType* Ci);

  /****************************************************************************
   *  FUNCTION: RepsGetPacketFromServer
   *
   *  INPUTS:
   *
   *        Ci: The connection to use.
   *
   *  OUTPUTS:
   *
   *        Dest: The packet is written to this address.
   *        Size: The actual size of the packet is written to this address.
   *
   *  RETURNS: REPS_ERROR_SUCCESS if successful, otherwise an error code.
   *
   *  DESCRIPTION: This function tries to get a packet on the
   *  connection identified by Ci. If the function returns an error
   *  code other than REPS_ERROR_NO_DATA or REPS_ERROR_SUCCESS, the
   *  connection should be disconnected.
   ****************************************************************************/
  FUNC(RepsErrorType, RepsGetPacketFromServer)(RepsClientType* Ci, RepsEapMessageType* Dest, uint32* Size);

  /****************************************************************************
   *  FUNCTION: RepsStartServer
   *
   *  INPUTS:
   *
   *        ExeName: The name of the REPS aplication exe file including the
   *        full path to the exe file.
   *
   *        ServerShmName: The name of the Server shared memory segment
   *        holding the buffers used to store the data exchanged between
   *        the server and the clients.
   *
   *        Flags: The flags are used by the client to set some options
   *        in the server. See the description of the RepsStartFlagsEnum
   *        for a description of the individual flags.
   *
   *  OUTPUTS: None.
   *
   *  RETURNS: REPS_ERROR_SUCCESS if successful, otherwise an error code.
   *
   *  DESCRIPTION: This function can be used by a client to starts the REPS
   *               application.
   ****************************************************************************/
  FUNC(RepsErrorType, RepsStartServer)(const char* ExeName, const char* ServerShmName, RepsStartFlagsType Flags);

  /****************************************************************************
   *  FUNCTION: RepsStopServer
   *
   *  INPUTS: Ci: The connection to use.
   *
   *  OUTPUTS: None.
   *
   *  RETURNS: REPS_ERROR_SUCCESS if successful, otherwise an error code.
   *
   *  DESCRIPTION: This function sends a terminate request to the REPS application
   *  connected to the client using the connection specified by the Ci parameter.
   ****************************************************************************/
  FUNC(RepsErrorType, RepsStopServer)(RepsClientType* Ci);

  /****************************************************************************
   *  FUNCTION: RepsSetTransportLayer
   *
   *  INPUTS:
   *
   *        Ci: The connection to use.
   *
   *        TlType: Specifies the transport layer to use.
   *
   *        TlParameters: Specifies TL specific parameters.
   *
   *  OUTPUTS: None.
   *
   *  RETURNS: REPS_ERROR_SUCCESS if successful, otherwise an error code.
   *
   *  DESCRIPTION: This function can be used by the client to set the Transport
   *  Layer used by the Server.
   ****************************************************************************/
  FUNC(RepsErrorType, RepsSetTransportLayer)(RepsClientType* Ci, RepsTlIdType TlType, const RepsTlParametersType* TlParameters);

  /****************************************************************************
   *  FUNCTION: RepsGetTransportLayer
   *
   *  INPUTS:
   *
   *        Ci: The connection to use.
   *
   *  OUTPUTS:
   *
   *        TlType: The TL type used by the server is written to this address.
   *        TlParamters: The TL parameters are written to this address.
   *
   *  RETURNS: REPS_ERROR_SUCCESS if successful, otherwise an error code.
   *
   *  DESCRIPTION: This function can be used by the client to get the Transport
   *  Layer used by the Server.
   ****************************************************************************/
  FUNC(RepsErrorType, RepsGetTransportLayer)(RepsClientType* Ci, RepsTlIdType* TlType, RepsTlParametersType* TlParameters);

  /****************************************************************************
   *  FUNCTION: RepsGetErrorString
   *
   *  INPUTS: RepsError: REPS error code.
   *
   *  OUTPUTS: None.
   *
   *  RETURNS: Pointer to string representation of REPS error.
   *
   *  DESCRIPTION: This function can be used by the client to translate REPS
   *  error codes to strings.
   ****************************************************************************/
  FUNC(const char*, RepsGetErrorString)(RepsErrorType RepsError);

  /****************************************************************************
   *  FUNCTION: RepsGetClientDllVersion
   *
   *  INPUTS: none
   *
   *  OUTPUTS:
   *
   *        VersionInfo: The version information is written to this address.
   *
   *  RETURNS: REPS_ERROR_SUCCESS if successful, otherwise an error code.
   *
   *  DESCRIPTION: The client uses this function to get the version number of
   *  the RepsClient.dll.
   ****************************************************************************/
  FUNC(RepsErrorType, RepsGetClientDllVersion)(RepsVersionInfoType* VersionInfo);

  /****************************************************************************
   *  FUNCTION: RepsGetServerVersion
   *
   *  INPUTS:
   *
   *        Ci: The connection to use.
   *
   *  OUTPUTS:
   *
   *        VersionInfo: The version information is written to this address.
   *
   *  RETURNS: REPS_ERROR_SUCCESS if successful, otherwise an error code.
   *
   *  DESCRIPTION: The client uses this function to get the version number of
   *  the server it is con-nected to.
   ****************************************************************************/
  FUNC(RepsErrorType, RepsGetServerVersion)(RepsClientType* Ci, RepsVersionInfoType* VersionInfo);

  /****************************************************************************
   *  FUNCTION: RepsGetConnectionCount
   *
   *  INPUTS:
   *
   *        Ci: The connection to use.
   *
   *  OUTPUTS:
   *
   *        ConnectionCount: The number of connections are written to this address.
   *
   *  RETURNS: REPS_ERROR_SUCCESS if successful, otherwise an error code.
   *
   *  DESCRIPTION: The client uses this function to query the server it is
   *  connected to about the total number of connections established to the server.
   ****************************************************************************/
  FUNC(RepsErrorType, RepsGetConnectionCount)(RepsClientType* Ci, uint32 *ConnectionCount);


  /****************************************************************************
   *  FUNCTION: RepsSendPacketToServerAndWait
   *
   *  INPUTS:
   *
   *        Ci: The connection to use.
   *        Timeout: Specifies the timeout interval, in milliseconds.
   *        TxPacketPtr: Pointer to the message that the client wants to send to
   *                     the target.
   *        TxPacketSize: The total size of the TX packet.
   *        RxPrimitive: The message id of the message that the client wants to
   *                     wait for when the packet has been sent to the target.
   *        RxPacketPtr: Pointer to buffer where to this function copies the
   *                      message to when it is received from the target.
   *        RxPacketSize:	Holds the total size of the RX buffer when this
   *                      function is called.
   *
   *  OUTPUTS:
   *
   *        RxPacketSize:	Holds the actual size of the received message when the
   *                      function returns.
   *
   *  RETURNS: REPS_ERROR_SUCCESS if successful, otherwise an error code.
   *
   *  DESCRIPTION: The client can uses this function to send a message
   *  (can either be an EAP message or an RTX OS mail) to the target and wait
   *  for a response message from the target. All messages received from the
   *  REPS while this function is waiting for the requested message is discarded.
   *  This function waits until the requested message is received or until the
   *  timeout interval indicated by the Timeout parameter has elapsed.
   ****************************************************************************/
  FUNC(RepsErrorType, RepsSendPacketToServerAndWait)(RepsClientType* Ci,
                                                     uint32 Timeout,
                                                     const RepsEapMessageType* TxPacketPtr,
                                                     uint32 TxPacketSize,
                                                     uint16 RxPrimitive,
                                                     RepsEapMessageType* RxPacketPtr,
                                                     uint32* RxPacketSize);

  /****************************************************************************
   *  FUNCTION: RepsTestTargetConnection
   *
   *  INPUTS:
   *
   *        Ci: The connection to use.
   *        Timeout: Specifies the timeout interval, in milliseconds.
   *
   *  OUTPUTS:
   *
   *  RETURNS: REPS_ERROR_SUCCESS if successful, otherwise an error code.
   *
   *  DESCRIPTION: The client can use this function to test the connection to
   *  the target. This function sends an RTX_EAP_TEST_CONNECTION_PING_PONG_IND
   *  to the target and waits for an RTX_EAP_TEST_CONNECTION_PING_PONG_IND
   *  message from the target.
   ****************************************************************************/
  FUNC(RepsErrorType, RepsTestTargetConnection)(RepsClientType* Ci, uint32 Timeout);

  /****************************************************************************
   *  FUNCTION: RepsGetEapVersion
   *
   *  INPUTS:
   *
   *        Ci: The connection to use.
   *        Timeout: Specifies the timeout interval, in milliseconds.
   *
   *  OUTPUTS:
   *
   *        Version: Holds the EAP version received from the target.
   *
   *  RETURNS: REPS_ERROR_SUCCESS if successful, otherwise an error code.
   *
   *  DESCRIPTION: The client can use this function to get the version of the
   *  RTX EAP supported by the target.
   ****************************************************************************/
  FUNC(RepsErrorType, RepsGetEapVersion)(RepsClientType* Ci, uint32 Timeout, uint32 *Version);

  /****************************************************************************
   *  FUNCTION: RepsGetSwBuildInfo
   *
   *  INPUTS:
   *
   *        Ci: The connection to use.
   *        Timeout: Specifies the timeout interval, in milliseconds.
   *        ProgramerId[8]: Pointer to eight byte buffer whereto the release
   *                        creator identification string is copied to.
   *        VersionHexFormat: The version number as 16 bit integer is retuned to
   *                          this buffer. E.g. 0x0107 for version 1.07.
   *        VersionStrFormat[4]: Pointer to a four byte buffer whereto the version
   *                             information in string format is copied to. E.g. "0107".
   *        LinkDate[5]: Pointer to five byte buffer whereto the link data
   *                     information is copied to.
   *        ReleaseLabelLength:	Specifies the length of the ReleaseLabel buffer. when this function is called and the actual length of the release label string when this function returns.
   *        ReleaseLabel: Pointer to buffer whereto the release label is copied to.
   *
   *  OUTPUTS:
   *
   *        ReleaseLabelLength:	Holds the actual length of the release label string.
   *
   *  RETURNS: REPS_ERROR_SUCCESS if successful, otherwise an error code.
   *
   *  DESCRIPTION: The client can use this function to get SW version
   *  information from the target.
   ****************************************************************************/
  FUNC(RepsErrorType, RepsGetSwBuildInfo)(RepsClientType* Ci,
                                          uint32 Timeout,
                                          uint8 ProgramerId[8],
                                          uint16* VersionHexFormat,
                                          uint8 VersionStrFormat[4],
                                          uint8 LinkDate[5],
                                          uint8* ReleaseLabelLength,
                                          uint8* ReleaseLabel);

  /****************************************************************************
   *  FUNCTION: RepsMemoryRead
   *
   *  INPUTS:
   *
   *        Ci: The connection to use.
   *        Timeout: Specifies the timeout interval, in milliseconds.
   *        MemoryId: Identifies the memory that the client wants to read from.
   *        Address: The address that the client wants to start reading from.
   *        NumberOfBytes: The number of bytes that the client wants to read.
   *
   *  OUTPUTS:
   *
   *        Buffer: Pointer to buffer where to the data read from target is written.
   *
   *  RETURNS: REPS_ERROR_SUCCESS if successful, otherwise an error code.
   *
   *  DESCRIPTION: This function is used to read from target memory using the
   *  RTX_EAP_MEMORY_READ_REQ message. This function can be used to read from
   *  RAM, NVS and other memory types used in the target implementation.
   ****************************************************************************/
  FUNC(RepsErrorType, RepsMemoryRead)(RepsClientType* Ci,
                                      uint32 Timeout,
                                      uint16 MemoryId,
                                      uint32 Address,
                                      uint16 NumberOfBytes,
                                      uint8* Buffer);

  /****************************************************************************
   *  FUNCTION: RepsMemoryWrite
   *
   *  INPUTS:
   *
   *        Ci: The connection to use.
   *        Timeout: Specifies the timeout interval, in milliseconds.
   *        MemoryId: Identifies the memory that the client wants to write to.
   *        Address: The address that the client wants to start writing to.
   *        NumberOfBytes: The number of bytes that the client wants to write.
   *        Data: Pointer to the data that the client wants to write to the target memory.
   *
   *  OUTPUTS:
   *
   *  RETURNS: REPS_ERROR_SUCCESS if successful, otherwise an error code.
   *
   *  DESCRIPTION: This function is used to write to target memory using the
   *  RTX_EAP_MEMORY_WRITE_REQ message. This function can be used to write to
   *  RAM, NVS and other memory types used in the target implementation.
   ****************************************************************************/
  FUNC(RepsErrorType, RepsMemoryWrite)(RepsClientType* Ci,
                                       uint32 Timeout,
                                       uint16 MemoryId,
                                       uint32 Address,
                                       uint16 NumberOfBytes,
                                       uint8* Data);

  /****************************************************************************
   *  FUNCTION: RepsMemorySet
   *
   *  INPUTS:
   *
   *        Ci: The connection to use.
   *        Timeout: Specifies the timeout interval, in milliseconds.
   *        MemoryId: Identifies the memory that the client wants to write to.
   *        Address: The address that the client wants to start writing to.
   *        NumberOfBytes: The number of bytes that the client wants to write.
   *        Value: The value that the client wants to write to the target memory.
   *
   *  OUTPUTS:
   *
   *  RETURNS: REPS_ERROR_SUCCESS if successful, otherwise an error code.
   *
   *  DESCRIPTION: This function is used to write (memset) a specific value to
   *  a memory block in the target memory using the RTX_EAP_MEMORY_MEMSET_REQ
   *  message. This function can be used to write to RAM, NVS and other memory
   *  types used in the target implementation.
   ****************************************************************************/
  FUNC(RepsErrorType, RepsMemorySet)(RepsClientType* Ci,
                                     uint32 Timeout,
                                     uint16 MemoryId,
                                     uint32 Address,
                                     uint32 NumberOfBytes,
                                     uint8  Value);

  /****************************************************************************
   *  FUNCTION: RepsMemorySetDefault
   *
   *  INPUTS:
   *
   *        Ci: The connection to use.
   *        Timeout: Specifies the timeout interval, in milliseconds.
   *        MemoryId: Identifies the memory that the client wants to write to.
   *        Option: Target/memory specific option.
   *
   *  OUTPUTS:
   *
   *  RETURNS: REPS_ERROR_SUCCESS if successful, otherwise an error code.
   *
   *  DESCRIPTION: This function is used to command the target, using the
   *  RTX_EAP_MEMORY_SET_DEFAULT_REQ message, to perform an initialization of
   *  some memory. This function can e.g. be used to request the target to do a
   *  default programming of the NVS in the target.
   ****************************************************************************/
  FUNC(RepsErrorType, RepsMemorySetDefault)(RepsClientType* Ci,
                                            uint32 Timeout,
                                            uint16 MemoryId,
                                            uint32 Option);


  /****************************************************************************
   *  FUNCTION: RepsRamRead
   *
   *  INPUTS:
   *
   *        Ci: The connection to use.
   *        Timeout: Specifies the timeout interval, in milliseconds.
   *        Address: The address that the client wants to start reading from.
   *        NumberOfBytes: The number of bytes that the client wants to read.
   *
   *  OUTPUTS:
   *
   *        Buffer: Pointer to buffer where to the data read from target is written.
   *
   *  RETURNS: REPS_ERROR_SUCCESS if successful, otherwise an error code.
   *
   *  DESCRIPTION: This function is used to read from target RAM using the
   *  RTX_EAP_RAM_READ_REQ message. This function can be used to read from RAM only.
   ****************************************************************************/
  FUNC(RepsErrorType, RepsRamRead)(RepsClientType* Ci,
                                   uint32 Timeout,
                                   uint32 Address,
                                   uint8  NumberOfBytes,
                                   uint8* Buffer);

  /****************************************************************************
   *  FUNCTION: RepsRamWrite
   *
   *  INPUTS:
   *
   *        Ci: The connection to use.
   *        Address: The address that the client wants to start writing to.
   *        NumberOfBytes: The number of bytes that the client wants to write.
   *        Data: Pointer to the data that the client wants to write to the RAM.
   *
   *  OUTPUTS:
   *
   *  RETURNS: REPS_ERROR_SUCCESS if successful, otherwise an error code.
   *
   *  DESCRIPTION: This function is used to write to the target RAM using the
   *  RTX_EAP_RAM_WRITE_REQ message. This function can be used to modify the
   *  RAM only. Please note that the target does not send a response to a
   *  RTX_EAP_RAM_WRITE_REQ message. The client can use the RepsRamRead()
   *  function to verify that the target memory has been updated correctly if
   *  necessary.
   ****************************************************************************/
  FUNC(RepsErrorType, RepsRamWrite)(RepsClientType* Ci,
                                    uint32 Address,
                                    uint8  NumberOfBytes,
                                    uint8* Data);

  /****************************************************************************
   *  FUNCTION: RepsRamSet
   *
   *  INPUTS:
   *
   *        Ci: The connection to use.
   *        Address: The address that the client wants to start writing to.
   *        NumberOfBytes: The number of bytes that the client wants to write.
   *        Value: The value that the client wants to write to the RAM.
   *
   *  OUTPUTS:
   *
   *  RETURNS: REPS_ERROR_SUCCESS if successful, otherwise an error code.
   *
   *  DESCRIPTION: This function is used to write (memset) a specific value to
   *  a memory block in the target RAM using the RTX_EAP_RAM_MEMSET_REQ message.
   *  This function can be used to write to RAM only.
   ****************************************************************************/
  FUNC(RepsErrorType, RepsRamSet)(RepsClientType* Ci,
                                  uint32 Timeout,
                                  uint32 Address,
                                  uint32 NumberOfBytes,
                                  uint8  Value);

  /****************************************************************************
   *  FUNCTION: RepsNvsRead
   *
   *  INPUTS:
   *
   *        Ci: The connection to use.
   *        Timeout: Specifies the timeout interval, in milliseconds.
   *        Address: The address that the client wants to start reading from.
   *        NumberOfBytes: The number of bytes that the client wants to read.
   *
   *  OUTPUTS:
   *
   *        Buffer: Pointer to buffer where to the data read from target is written.
   *
   *  RETURNS: REPS_ERROR_SUCCESS if successful, otherwise an error code.
   *
   *  DESCRIPTION: This function is used to read from target NVS using the
   *  RTX_EAP_NVS_READ_REQ message. This function can be used to read from
   *  NVS only.
   ****************************************************************************/
  FUNC(RepsErrorType, RepsNvsRead)(RepsClientType* Ci,
                                   uint32 Timeout,
                                   uint16 Address,
                                   uint8  NumberOfBytes,
                                   uint8* Buffer);

  /****************************************************************************
   *  FUNCTION: RepsNvsWrite
   *
   *  INPUTS:
   *
   *        Ci: The connection to use.
   *        Timeout: Specifies the timeout interval, in milliseconds.
   *        Address: The address that the client wants to start writing to.
   *        NumberOfBytes: The number of bytes that the client wants to write.
   *        Data: Pointer to the data that the client wants to write to the NVS.
   *
   *  OUTPUTS:
   *
   *  RETURNS: REPS_ERROR_SUCCESS if successful, otherwise an error code.
   *
   *  DESCRIPTION: This function is used to write to target NVS using the
   *  RTX_EAP_NVS_WRITE_REQ message. This function can be used to write to
   *  NVS only.
   ****************************************************************************/
  FUNC(RepsErrorType, RepsNvsWrite)(RepsClientType* Ci,
                                    uint32 Timeout,
                                    uint16 Address,
                                    uint8  NumberOfBytes,
                                    uint8* Data);

  /****************************************************************************
   *  FUNCTION: RepsNvsSetDefault
   *
   *  INPUTS:
   *
   *        Ci: The connection to use.
   *        Timeout: Specifies the timeout interval, in milliseconds.
   *
   *  OUTPUTS:
   *
   *  RETURNS: REPS_ERROR_SUCCESS if successful, otherwise an error code.
   *
   *  DESCRIPTION: This function is used to command the target, using the
   *  RTX_EAP_NVS_SET_DEFAULT_REQ, to perform a default programming of the
   *  target NVS.
   ****************************************************************************/
  FUNC(RepsErrorType, RepsNvsSetDefault)(RepsClientType* Ci,
                                         uint32 Timeout);

  /****************************************************************************
   *  FUNCTION: RepsStrSendPacket
   *
   *  INPUTS:
   *
   *        Ci: The connection to use.
   *        TxStr: Pointer to the message string that the client wants to send
   *               to the target.
   *
   *  OUTPUTS:
   *
   *  RETURNS: REPS_ERROR_SUCCESS if successful, otherwise an error code.
   *
   *  DESCRIPTION: The client can uses this function to send a message specified
   *  by an ascii string as "<uint8:TaskId> <uint16:Primitive> <uint8:Data[]>".
   *  E.g. "00 f066 01 00 5d 00 02 00 3f 00".
   ****************************************************************************/
  FUNC(RepsErrorType, RepsStrSendPacket)(RepsClientType* Ci, char *TxStr);

  /****************************************************************************
   *  FUNCTION: RepsStrSendPacketQuery
   *
   *  INPUTS:
   *
   *        Ci: The connection to use.
   *        Timeout: Specifies the timeout interval, in milliseconds.
   *        TxStr: Pointer to the message string that the client wants to send
   *               to the target.
   *        RxPrimitive: The message id of the message that the client wants to
   *                     wait for when the packet has been sent to the target.
   *        RxStr: Pointer to buffer where to this function writes string the
   *               representation of the packet received from the target.
   *        RxStrSize: Specifies the size of the RxStr buffer.
   *
   *  OUTPUTS:
   *
   *  RETURNS: REPS_ERROR_SUCCESS if successful, otherwise an error code.
   *
   *  DESCRIPTION: The client can uses this function to send a message specified
   *  by an ascii string as "<uint8:TaskId> <uint16:Primitive> <uint8:Data[]>".
   *  E.g. "00 f066 01 00 5d 00 02 00 3f 00".
   *  When the packet has been sent this function waits for a response message
   *  from the target. All messages received from the REPS while this function
   *  is waiting for the requested message are discarded.
   *  This function waits until the requested message is received or until the
   *  timeout interval indicated by the Timeout parameter has elapsed.
   ****************************************************************************/
  FUNC(RepsErrorType, RepsStrSendPacketQuery)(RepsClientType* Ci,
                                              uint32 Timeout,
                                              char* TxStr,
                                              uint16 RxPrimitive,
                                              char* RxStr,
                                              uint32 RxStrSize);

  #ifdef __cplusplus
}
#endif

#endif // IREPSCLIENT_H
