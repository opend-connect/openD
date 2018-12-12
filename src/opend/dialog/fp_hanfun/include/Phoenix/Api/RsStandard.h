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
* Standards definitions.
*/


#ifndef APIRSSTANDARD_H   
#define APIRSSTANDARD_H   

#define PACKED_STRUCT __attribute__((packed))

/****************************************************************************
*                              Macro definitions                              
****************************************************************************/

#define RS_LITTLE_ENDIAN   1 /*!< Intel-like CPU's. */
#define RS_BIG_ENDIAN      2 /*!< Motorola-like CPU's */
#ifndef RS_ENDIAN_TYPE
  #define RS_ENDIAN_TYPE RS_LITTLE_ENDIAN // Default
#endif
#define RSMAX(a, b) (((a) > (b)) ? (a) : (b)) /*!< Computes the maximum of \a a and \a b. */
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
/****************************************************************************
*                     Enumerations/Type definitions/Structs                  
****************************************************************************/
#if !defined(VP_API_TYPES_H) && !defined(STD_DEF_H__)
typedef signed char       int8;
typedef unsigned char     uint8;
typedef unsigned short    uint16;
typedef signed short      int16;
typedef unsigned long     uint32;
typedef signed long       int32;
typedef unsigned char     boolean;
#endif
//typedef unsigned char     boolean;
typedef char rschar;                  // Plain char for strings
typedef unsigned char rsuint8;        // 8-bit unsigned quantity
typedef signed char rsint8;           // 8-bit signed quantity
typedef unsigned short rsuint16;      // 16-bit unsigned quantity
typedef signed short rsint16;         // 16-bit signed quantity
typedef unsigned long rsuint32;       // 32-bit unsigned quantity
typedef signed long rsint32;          // 32-bit signed quantity
typedef unsigned char rsbitfield;     // For use as bitfields
typedef unsigned char rsbool;         // boolean quantity

#if !defined(STD_DEF_H__)
#define RSENUM8(EnumName)   Enum_##EnumName; typedef rsuint8  EnumName
#define RSENUM16(EnumName)  Enum_##EnumName; typedef rsuint16 EnumName
#define RSENUM32(EnumName)  Enum_##EnumName; typedef rsuint32 EnumName
#endif
#define RSENUM8S(EnumName)  Enum_##EnumName; typedef rsint8   EnumName
#define RSENUMTAG(EnumName) Enum_##EnumName

#define PrimitiveType RosPrimitiveType

typedef unsigned char RosTaskIdType;

typedef enum RSENUMTAG(RsStatusType)
{
  RSS_SUCCESS               = 0x00, /*!< The request completed successfully. */
  RSS_NOT_SUPPORTED         = 0x01, /*!< The request is not supported. */
  RSS_BAD_ARGUMENTS         = 0x02, /*!< One or more arguments are not correct. */
  RSS_BAD_ADDRESS           = 0x03, /*!< The address is incorrect. */
  RSS_BAD_FUNCTION          = 0x04, /*!< Incorrect function. */
  RSS_BAD_HANDLE            = 0x05, /*!< The handle is invalid. */
  RSS_BAD_DATA              = 0x06, /*!< The data is invalid. */
  RSS_BAD_LENGTH            = 0x07, /*!< The program issued a command but the command length is incorrect. */
  RSS_NO_MEMORY             = 0x08, /*!< Not enough storage is available to process this command. */
  RSS_NO_DEVICE             = 0x09, /*!< No such device */
  RSS_NO_DATA               = 0x0A, /*!< No data is available. */
  RSS_RETRY                 = 0x0B, /*!< The operation could not be completed. A retry should be performed. */
  RSS_NOT_READY             = 0x0C, /*!< The device is not ready. */
  RSS_IO                    = 0x0D, /*!< I/O error */
  RSS_CRC                   = 0x0E, /*!< Data error (cyclic redundancy check). */
  RSS_CANCELLED             = 0x0F, /*!< The operation was cancelled. */
  RSS_RESET                 = 0x10, /*!< The I/O bus was reset. */
  RSS_PENDING               = 0x11, /*!< The operation is in progress. */
  RSS_BUSY                  = 0x12, /*!< Device or resource busy */
  RSS_TIMEOUT               = 0x13, /*!< This operation returned because the timeout period expired. */
  RSS_OVERFLOW              = 0x14, /*!< Value too large for defined data type */
  RSS_NOT_FOUND             = 0x15, /*!< Element not found. */
  RSS_STALLED               = 0x16, /*!< Endpoint stalled. */
  RSS_DENIED                = 0x17, /*!< Access denied or authentication failed. */
  RSS_REJECTED              = 0x18, /*!< Rejected (e.g. by user). */
  RSS_AMBIGUOUS             = 0x19, /*!< Ambiguous e.g. name or number. */
  RSS_NO_RESOURCE           = 0x1A, /*!< Not enough resources are available to process this command. */
  RSS_NOT_CONNECTED         = 0x1B, /*!< No connection to destination. */
  RSS_OFFLINE               = 0x1C, /*!< Destination is offline. */
  RSS_REMOTE_ERROR          = 0x1D, /*!< Failed at remote destination. */
  RSS_NO_CAPABILITY         = 0x1E, /*!< A required capability is missing. */
  RSS_FILE_ACCESS           = 0x1F, /*!< File access error. */
  RSS_DUPLICATE             = 0x20, /*!< Duplicate entry e.g. same entry already exists when trying to create. */
  RSS_LOGGED_OUT            = 0x21, /*!< Operation not possible while logged out. */
  RSS_ABNORMAL_TERMINATION  = 0x22, /*!< Operation terminated abnormally. */
  RSS_FAILED                = 0x23, /*!< Operation failed. */
  RSS_UNKNOWN               = 0x24, /*!< Unknown error. */
  RSS_BLOCKED               = 0x25, /*!< Destination is blocked. */
  RSS_NOT_AUTHORIZED        = 0x26, /*!< You are not authorized to perform this operation. */
  RSS_PROXY_CONNECT         = 0x27, /*!< Could not connect to proxy. */
  RSS_INVALID_PASSWORD      = 0x28, /*!< Invalid password. */
  RSS_FORBIDDEN             = 0x29, /*!< Forbidden. */
  RSS_MISSING_PARAMETER     = 0x2A, /*!< One or more mandatory paramters are missing. */
  RSS_SPARE_2B              = 0x2B, /*!< Spare. */
  RSS_SPARE_2C              = 0x2C, /*!< Spare. */
  RSS_SPARE_2D              = 0x2D, /*!< Spare. */
  RSS_SPARE_2E              = 0x2E, /*!< Spare. */
  RSS_SPARE_2F              = 0x2F, /*!< Spare. */
  RSS_UNAVAILABLE           = 0x30, /*!< Service unavailable. */
  RSS_NETWORK               = 0x31, /*!< Network error. */
  RSS_NO_CREDITS            = 0x32, /*!< No credits. */
  RSS_LOW_CREDITS           = 0x33, /*!< Low credits. */
  RSS_MAX = 0xFF
} RSENUM8(RsStatusType);

#endif

const char* RsStatusStr(RsStatusType Status);
