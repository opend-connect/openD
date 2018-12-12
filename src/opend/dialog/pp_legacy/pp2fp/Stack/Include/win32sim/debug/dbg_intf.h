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

#ifndef __DBG_INTF_H__
#define __DBG_INTF_H__

#if defined(RTX_CORE_H) && !defined(RTXDEF_H)
  #define uint8 rsuint8
  #define uint16 rsuint16
  #define uint32 rsuint32
  #define boolean rsbool
  #define int32 rsint32
#endif


// The standard printf prototype must be known to the compiler before tampering with
// it with the preprocessor.
#include <stdio.h>


// To configure the following compiler defines are used:
// WIN32_SIM:                        Used in the source code to distinguish between code only used in target and code only used on PC.
// WIN32_BMC_SIM:                    Used to include code related to the BMC simulation.
// WIN32_DISP_SIM:                   Used to include code related to the display simulation.
// WIN32_GDISP_SIM:                  Used to include code related to the graphical display simulation.
// WIN32_GDISP_SYNC_SENDMAIL:
// WIN32_GDISP_DIRECT:               Drawing to dll (WIN32_GDISP_SIM defined) is done directly. Not using shadow RAM.
// GENERIC_KEYBOARD_SUPPORT          Simulating keyboard behaviour
// WIN32_LED_SIM                     Used to simulate LED behaviour
// WIN32_CM:                         (Not used anymore - see below. Used to include the interface to the Communication Manager.
// WIN32_CM_INCLUDE                  Replaces WIN32_CM. Used this way to default exclude WIN32_CM as this is probably not used anymore
// WIN32_DPRS_LOAD_MONITOR           Used to include the DPRS load monitor
// WIN32_CS_INTERPRETATION           Used to combine Cs messages to DLC and NWK messages.

// To include various production tests in RSX
// WIN32_CTU_TEST
// WIN32_ATS_COMMON_TEST
// WIN32_ATS_A_TEST
// WIN32_ATS_I_TEST
// WIN32_INFINEON_TEST
// WIN32_NSC_VOICE:        Used for RSSI and CRC trace for national based voice products

// To generate special versions of the RSX program
// WIN32_TRACE_ON_SPI:     Used in the CVM project, generate a version that make trace over the SPI bus.
// WIN32_TRACE_ON_UART:    Used in the CVM project, generate a version that make trace over the UART bus.
// LOGBINMAILFORMAT:       Save in binary format.

// To make a program with limited functionality the following defines are used:
// WIN32_NO_MAILTRACE:     Used to exclude mailtrace.
// WIN32_NO_EEPROM_EDITOR: Used to exclude the eeprom editor.
// WIN32_NO_RSSI_TRACE:    Used to exclude the BMC status trace.
// WIN32_NO_A_FIELD_TRACE: Used to exclude the A-FIELD trace.
// WIN32_NO_RMEM:          Used to exclude the memory editor.
// WIN32_NO_LOAD_MONITOR:  Used to exclude the DPRS load monitor.
// WIN32_NO_PROD_TEST:     Used to exclude the production test.
// WIN32_NO_GLOBAL_PRINT_WINDOW: Used to exclude the global print window in the RSX program.
// WIN32_EXCLUDE_TASKS:    Used to exclude mailtrace for tasks that are not initialized.
// WIN32_NO_MAIL_CONVERSION: Used to exclude mail conversion.
// WIN32_NO_MAIL_OPTIONS:  Used to exclude the mail options menus

// WIN32_CUSTOMER_MMI_PRESENTATION Used for customer releases which shall present the MMI. A special dll is needed for dispsim then.

// Remove interrupts
#define interrupt

#ifdef DBG_INTF_REDEFINE_PRINTF
// Redefine the tty functions
#define printf Printf
#define clrscr Clrscr
#define textcolor TextColor
#define gotoxy Gotoxy
#endif

// define the colors, also defined in conio.h
#define DEBUG_BLACK            0
#define DEBUG_BLUE             1
#define DEBUG_GREEN            2
#define DEBUG_CYAN             3
#define DEBUG_RED              4
#define DEBUG_MAGENTA          5
#define DEBUG_BROWN            6
#define DEBUG_LIGHTGRAY        7
#define DEBUG_DARKGRAY         8
#define DEBUG_LIGHTBLUE        9
#define DEBUG_LIGHTGREEN	    10
#define DEBUG_LIGHTCYAN       11
#define DEBUG_LIGHTRED        12
#define DEBUG_LIGHTMAGENTA	  13
#define DEBUG_YELLOW          14
#define DEBUG_WHITE           15
// Additional colors only defined in the debug environment
#define DEBUG_DARKGREEN       16
#define DEBUG_DARKPINK        17
#define DEBUG_PINK            18
#define DEBUG_DARKBLUE        19

// Define run-time errors used by function "debug_RunTimeError"
#define RTE_EEPROM_SIZE_OVERFLOW    0


typedef enum
{
   MAILTRACE_TYPE_INPUT_MAIL,
   MAILTRACE_TYPE_OUTPUT_MAIL,
   MAILTRACE_TYPE_EMU_INPUT_MAIL,
   MAILTRACE_TYPE_EMU_OUTPUT_MAIL,
   MAILTRACE_TYPE_UART_INPUT_MAIL,
   MAILTRACE_TYPE_UART_OUTPUT_MAIL,
   MAILTRACE_TYPE_UART_ERROR_BYTES
} MailtraceType;

typedef enum
{
   MAILFORMAT_USE_DEFAULT_MAIL_FORMAT,
   MAILFORMAT_USE_MAILCRACKER,
   MAILFORMAT_USE_BOTH,
} MailFormatType;

typedef enum
{
   AFIELDTRACE_TYPE_FP_RX,
   AFIELDTRACE_TYPE_FP_TX,
   AFIELDTRACE_TYPE_PP_RX,
   AFIELDTRACE_TYPE_PP_TX
} AFieldTraceType;



// Function prototype for the mailcracker function
typedef void (* MailFormatPtr)(uint32 iSendingTaskId, uint32 iRecievingTaskId, uint32 iMailLength, uint8 *bMailPtr, char *szText, uint32 *iColor);

// Function prototype for the kernel main loop and the timer interrupt.
typedef void (* KernelPtr)(void);

// Function prototype for RSX program.
typedef void (* TaskWindowPtr)(uint8 *bMailPtr);

// Function for rmem call back functions
typedef void (* RmemFormatPtr)(uint32 iLength, uint8 *bDataPtr, char *szText);


#ifdef __cplusplus
   extern "C"
   {
#endif
   // Functions called from tasks
#ifdef NATALIE_V11
#ifdef __GNUC__
#define Printf(szString, ...) printf(szString, ##__VA_ARGS__)
#else
#define Printf(szString, ...) printf(szString, __VA_ARGS__)
#endif
#else
   extern int  Printf(const char *szString, ...);
#endif
   extern void PrintfInt(char *szString, ...);
   extern void PrintfClient(uint8 Task, char *szString, ...);
   extern void TextColor(uint32 newcolor);
   extern void Gotoxy(uint32 x, uint32 y);
   extern void Clrscr(void);

   extern void LogComment(char *format, ...);
   extern void LogCommentIncTime(uint32 TargetTraceTime, char *format, ...);

   // Interface functions called from the kernel.
   extern uint32 debug_GetTargetTraceTime(void);
   extern boolean debug_LogMailTrace(uint32 bSendingTaskId, uint32 bRecievingTaskId, uint32 iPacketLength, uint8 *PacketPointer, MailtraceType TraceType);
   extern boolean debug_LogMailTraceIncTime(uint32 iSendingTaskId, uint32 iRecievingTaskId, uint32 iPacketLength, uint8 *PacketPointer, MailtraceType TraceType, uint32 TraceTime);
   extern boolean debug_LogMailTraceProcTime(uint32 iSendingTaskId, uint32 iRecievingTaskId, uint32 iPacketLength, uint8 *PacketPointer, MailtraceType TraceType, uint32 TraceTime, uint16 ProcTime);

   extern void debug_LogStopTimer(uint32 bTimerId, uint32 bTaskId);
   extern void debug_LogStopTimerIncTime(uint32 bTimerId, uint32 bTaskId, uint32 TargetTraceTime);

   extern void debug_LogStartTimer(uint32 bTimerId, uint32 bTaskId, uint32 Time);
   extern void debug_LogStartTimerIncTime(uint32 bTimerId, uint32 bTaskId, uint32 Time, uint32 TargetTraceTime);

   extern void debug_Sleep(uint32 iTime);
   extern void debug_LogText(char *format, ...);    // Used to log mails from the ddu kernel. Also reset the log text color to black after the string is printed
   extern void debug_LogTextColor(int Color);       // Changes the log text color in the mail trace window
   extern void debug_SendPacket(uint32 iProgramId, uint32 iTaskId, uint32 iLength, uint8 *bDataPtr);

   // Interface function called from the mac interrupt
   extern void debug_LogAfields(uint8 bSlot, uint8 bCarrier, uint8 bFrameNumber, uint8 *bMultiFrameNumber, uint8 *bAfieldData, uint8 *bBfieldData, AFieldTraceType TraceType, uint8 bRssi, uint8 bCrc);
   extern void debug_LogRssi(uint8 bRssi, uint8 bCrc, uint8 bPhase, uint8 bCrcB9B4, uint8 bFrequency);

   // Interface function called from the run-time error function
   extern void debug_RunTimeError(uint32 iTaskId, uint32 iErrorCode, char *szString);

   // Init functions called from task.c
   extern void debug_SetPrintInputFormat(char *szPrintFormat);
   extern void debug_SetPrintOutputFormat(char *szPrintFormat);
   extern void debug_SetPrintFormatTaskLen(uint8 MaxTaskLen);

   // Functions to get primitive, task and timer names. These functions
   // can f.x. be called from the mail interpretation functions.
   extern char *debug_GetPrimitiveName(uint32 iTaskValue, uint32 iPrimitiveValue);
   extern char *debug_GetTaskName(uint32 iTaskValue);
   extern char *debug_GetTimerName(uint32 iTimerValue);

   // Functions to get primitive, task and timer count.
   extern uint16 debug_GetTaskCount(void);
   extern uint16 debug_GetTimerCount(void);
   extern uint16 debug_GetPrimitiveCount(void);
   extern void debug_GetReleaseLabel(char* dest);

   extern void debug_SetPrimitiveFormat(uint32 iPrimitiveFormat);
   extern uint32 debug_ReadPrimitiveFile(char *szFileName, char **EnumStrings);
   extern void debug_InitializeEepromEditor(uint32 iSize, char *szHeaderText);
   extern void debug_SetRmemFile(char *szHeaderText);
   extern void debug_LoadTreeFile(char *szHeaderText);
   extern void debug_SetEepromText(uint32 iAddress, uint32 iLength, char *szText);
   extern void debug_SetEepromText_1(uint32 iAddress, uint32 iLength, char *szText);
   extern void debug_SetEepromText_2(uint32 iAddress, uint32 iLength, char *szText);
   extern void debug_StartDisplaySimulation(char *szText);
   extern void debug_InitTask(uint32 iTaskId, char *szTaskName, uint32 iOwnWindow, uint32 iKeyPrimitive, MailFormatPtr FunkPtr, char *EnumStrings[], uint32 iNumberOfPrimitives);
   extern void debug_InitTimer(uint32 iTimerId, char *szTaskName);
   extern void debug_InitUartTrace(MailFormatPtr FunkPtr, char *EnumStrings[], uint32 iNumberOfPrimitives);
   extern void debug_SetMailFormatType(MailFormatType Format);
   extern void debug_SetHeaderText(char *szHeaderText);
   extern void debug_SetKernelSpeed(uint32 iKernelSpeed);   // iKernelSpeed is in percent of real time
   extern void debug_SetGlobalPrimitiveFile(char *EnumStrings[], uint32 iNumberOfPrimitives);
   extern int32 debug_ProgramId;
#ifdef REPSCLIENT_DLL
   extern char pszRtxEaiServerName[];
#endif
   extern void debug_SetKernelMainLoop(KernelPtr FunkPtr);
   extern void debug_SetTimerInterrupt(KernelPtr FunkPtr, uint32 Time);
   extern void debug_InitializeKeyboardSimulation(uint32 iTaskId, uint32 KeypressPrim, uint32 KeyreleasePrim);
#ifdef WIN32_GDISP_SIM
   //For now the following functionality is only supported for graphical displays.
   extern void debug_InitializeMMIDll(char *dllName);
#endif

#ifdef WIN32_PRJ_CLASS_REG
   extern void debug_RegisterUserClass(WNDPROC lpfnWndProc, LPCSTR  lpszClassName);
   extern void debug_CreateMdiChild(LPCSTR  lpszClassName, LPCSTR  lpszWindowTitle);
   extern void UserReceiveHandler(uint8 TaskId, int Length, uint8 *Mail);
#endif


   // Functions to interpretate DECT and ISDN frames
   extern void debug_InterpretateDlcMessage(uint8 DataArr[], char szString[], uint8 DownlinkFlag);
   extern void debug_InterpretateSFormatMessage(uint8 DataArr[], uint32 iLength, char szString[]);
   extern void debug_InterpretateIsdnMessage(uint8 DataArr[], uint32 w16Length, char szString[]);

   // Initialize variables
   extern void debug_DbgInitUINT8(char *szTitle, uint8 *pVar);
   extern void debug_DbgInitUINT16(char *szTitle, uint16 *pVar);
   extern void debug_DbgInitUINT32(char *szTitle, uint32 *pVar);
   extern void debug_DbgInitBOOLEAN(char *szTitle, boolean *pVar);

   // Initialize arrays
   extern void debug_DbgInitUINT8_Array(char *szTitle, uint8 *pVar, uint32 iSize);
   extern void debug_DbgInitUINT16_Array(char *szTitle, uint16 *pVar, uint32 iSize);
   extern void debug_DbgInitUINT32_Array(char *szTitle, uint32 *pVar, uint32 iSize);
   extern void debug_DbgInitBOOLEAN_Array(char *szTitle, boolean *pVar, uint32 iSize);

   // Interface to rmem interpretation functions
   extern void debug_InitRmemCallBackFunction(RmemFormatPtr FunkPtr, uint32 iIndex, char *szTitle);

   // Interface to DPRS load monitor
   extern void debug_LogDPRSLoad(uint8 LoadMsb, uint8 LoadLsb, uint8 TargetUplink, uint8 MinUplink, uint8 ActualUplink, uint8 TargetDownlink, uint8 MinDownlink, uint8 ActualDownlink,
                       uint8 debug_TxBytesMsb, uint8 debug_TxBytesLsb, uint8 debug_PduRetrans_NACKMsb, uint8 debug_PduRetrans_NACKLsb,
                       uint8 debug_PduRetrans_NoSDUMsb, uint8 debug_PduRetrans_NoSDULsb, uint8 debug_PduRetrans_WindowFullMsb, uint8 debug_PduRetrans_WindowFullLsb,
                       uint8 debug_FillBytesMsb, uint8 debug_FillBytesLsb, uint8 debug_NoOfGF_FramesMsb, uint8 debug_NoOfGF_FramesLsb,
                       uint8 debug_IdleFramesMsb, uint8 debug_IdleFramesLsb, uint8 debug_PduFramesMsb, uint8 debug_PduFramesLsb,
                       uint8 debug_PduRetrans_SduBufferFullMsb, uint8 debug_PduRetrans_SduBufferFullLsb,
                       uint8 debug_Var1Msb, uint8 debug_Var1Lsb, uint8 debug_Var2Msb, uint8 debug_Var2Lsb, uint8 debug_Var3Msb, uint8 debug_Var3Lsb);

   // Display simulation
   extern void dispsim_Printf(char *format, ...);
   extern void dispsim_Gotoxy(uint32 xpos, uint32 ypos);
   extern uint32 dispsim_Kbhit(void);
   extern uint32 dispsim_Getch(void);
#ifdef WIN32_GDISP_SIM
   //Graphical display simulation
   extern void dispsim_Updategraphicdisplay(uint8 *dataarray);
   extern void dispsim_UpdategraphicdisplayArea(uint8 *dataarray,
                                                uint16 X,
                                                uint16 Y,
                                                uint16 Width,
                                                uint16 Height);

   extern void dispsim_Updategraphiclight(uint8 *lightarray);

   #ifdef WIN32_GDISP_DIRECT
   extern void dispsim_FillRect(uint32 col, int16 x1, int16 y1, int16 x2, int16 y2 );
   extern void dispsim_HLine(uint32 col, int16 xmin, int16 xmax, int16 y );
   extern void dispsim_VLine(uint32 col, int16 x, int16 ymin, int16 ymax );
   extern void dispsim_PlotXY(uint32 col, int16 x, int16 y );
   #endif

#endif

   // RSX initialization
   extern void rsx_InitTask(uint32 iTaskId, char *szTaskName, uint32 iKeyPrimitive, TaskWindowPtr FunkPtr);
   extern void rsx_StartTimer(uint32 Time, uint16 Task, uint16 Primitive, uint16 TimerId);
   extern void rsx_StopTimer(uint16 TimerId);
   extern void debug_InitNonBinTraceInterface(uint32 iTransmitTaskId, uint32 iReceiveTaskId);

   // Download program initialization
   extern void debug_DownloadInit(char *szStartUpDir, char *szProgramName);
   extern void debug_DownloadInfineonInit(char *szStartUpDir, char *szProgramName);

   // Control the UART. Set delay after each Tx byte on the UART. Usefull
   // if the interrupt load in target is high and the UART interrupt is running
   // with a low priority.
   extern void debug_SetRs232TxDelay(uint32 iTime);

   // Set file names for mailtrace.
   extern void debug_SetMailLogFile(char *szFileName);
   extern void debug_SetMailLogFileNameOnly(char *szFileName);
   extern void debug_SetRssiLogFileNameOnly(char *szFileName);
   extern void debug_SetAtraceLogFileNameOnly(char *szFileName);
   extern void debug_SetRmemLogFile(char *szFileName);


   // Halt the system.
   extern void debug_HaltSystem(void);
   extern void debug_CheckSystemHalt(void);
   extern void debug_Checks(uint32 iValue, uint32 iMinValue, uint32 iMaxValue, char *iFile, uint32 iLine);
   extern void debug_EnterCriticalSection(void);
   extern void debug_LeaveCriticalSection(void);
   extern void debug_SuspendTask(uint32 iTime);

   // window position save/restore
   extern void debug_SaveWindowPositions(void);
   extern void debug_RestoreWindowPositions(void);

   extern int BusMode; // 0: RS232  1:I2C 2:TCP server 3: TCP client
   extern int32 RsPort;
   extern char szIpAddress[];

#ifdef __cplusplus
   }
#endif

 #if defined(RTX_CORE_H) && !defined(RTXDEF_H)
  #undef uint8
  #undef uint16
  #undef uint32
  #undef int32
  #undef boolean
 #endif

#endif
