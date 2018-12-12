/*
 * Copyright (C) 2018 by Dialog Semiconductor. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of Dialog Semiconductor nor the names of its Affiliates
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
#ifndef DRVCLASSSERCOM_H
#define DRVCLASSSERCOM_H

/****************************************************************************
*                               Include files
****************************************************************************/
#include <DevDrv/RtxDevDrv.h>

/****************************************************************************
*                              Macro definitions
****************************************************************************/

// Define the version of the interface added by the class. This number MUST be
// incremented whenever the class interface changes.
#define DRV_CLASS_SERCOM_ADDITIONAL_IF_VERSION  0x01

// Compose a common version number from both interface version numbers
#define DRV_CLASS_SERCOM_IF_VERSION ((DRV_BASECLASS_IF_VERSION << 8) + DRV_CLASS_SERCOM_ADDITIONAL_IF_VERSION)

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

typedef enum
{
   DRV_CLASS_SERCOM_UART_SC1448X,
   DRV_CLASS_SERCOM_UART_SC1445X,
   DRV_CLASS_SERCOM_USB_SC1445X,
   DRV_CLASS_SERCOM_SPI_SC144XX,
   DRV_CLASS_SERCOM_USB_HID,
   DRV_CLASS_SERCOM_UART_SC14470,
   DRV_CLASS_SERCOM_UART_SC1442X,
   DRV_CLASS_SERCOM_RAMBUS,
   DRV_CLASS_SERCOM_WINSHM,
   DRV_CLASS_SERCOM_WINSOCKET,
   DRV_CLASS_SERCOM_UART_EFM32G,
   DRV_CLASS_SERCOM_LEUART_EFM32G
}  DrvClassSerCom_IdType;

// Cdi.IoCtrl Cmd values.
typedef enum
{
   DRV_CLASS_SERCOM_IOCTRL_CONNECTED, // Get connection status. Returns rsbool in CmdData.
}  DrvClassSerCom_IoCtrlType;

// ***************************
// Device Driver Error Codes
// ***************************
typedef enum DrvClassSerCom_ErrorType
{
  DRV_CLASS_SERCOM_ERR_UNSPECIFIED = DRV_ERR_COMMON_ERROR_COUNT,
  DRV_CLASS_SERCOM_ERR_INVALID_BAUDRATE,
  DRV_CLASS_SERCOM_ERR_NO_DATA,
  DRV_CLASS_SERCOM_ERR_TX_BUFFER_FULL
} DrvClassSerCom_ErrorType;

typedef enum
{
  DRV_CLASS_SERCOM_EV_READY,
  DRV_CLASS_SERCOM_EV_RX_DATA_READY,
  DRV_CLASS_SERCOM_EV_TX_DONE
} DrvClassSerCom_EventType;

typedef union
{
  struct
  {
    rsuint16 DataLength;
  } RxDataReadyEventParameter;
  struct
  {
    const void *DataPtr;
    rsuint16 DataLength;
    RS_PADDING(2)
  } TxDoneEventParameter;
} DrvClassSerCom_EventParamType;

// Event call back function ptr type:
typedef void (*DrvClassSerCom_CallBackFuncPtrType)(DrvClassSerCom_EventType Event, DrvClassSerCom_EventParamType* ParamPtr, rsuint16 context);

// ***************************
// Device Driver Commands
// ***************************

/****************************************************************************
*  FUNCTION: Init()
*
*  INPUTS  : Instance
*  OUTPUTS : none
*  RETURNS : Status
*
*  DESCRIPTION: The init function is used to initialize the driver and the HW
*  used by the driver. Driver specific init parameters are read from const data
*  declared in the driver configuration C file in the project specific config
*  folder. E.g.: Config\UartSc14428\UartSc14428.c. The configuration parameters
*  for a UART driver will be BAUD rate, single wire/duplex, no data bits etc.
****************************************************************************/


/****************************************************************************
*  FUNCTION: Read()
*
*  INPUTS  : Instance
*            DataPtr    Specifies the address of the buffer where to data that
*                       should be copied by the driver.
*            DataLength Specifies the total number of bytes that can be copied
*                       to the buffer when Read() is called.
*  OUTPUTS : DataLength Specifies the actual number of bytes copied to the buffer
*                       when Read() returns.
*  RETURNS : Status
*
*  DESCRIPTION: This function is used to read data from the RX data buffer in
*  the driver. The requested number of bytes is copied from the RX data buffer
*  in the driver to the buffer specified by the Read() function.
*
*  The copying of the RX data from the driver to the app is done in the context
*  of the Read() function (the driver) in order to make sure that the app does
*  not have to know anything about the implementation of the RX data buffering
*  in the driver. The drawback of this is that it may be necessary to copy the
*  data from the RX buffer in the driver to a temporary holding buffer in the app.
****************************************************************************/
typedef DrvErrorType (*DrvClassSerCom_CmdReadPtrType)(DrvInstanceHandleType Instance, void *DataPtr, rsuint16 *DataLengthPtr);

/****************************************************************************
*  FUNCTION: Write()
*
*  INPUTS  : Instance
*            DataPtr
*            DataLength
*  OUTPUTS : none
*  RETURNS : none
*
*  DESCRIPTION: The Write() function is used to request the driver to send a
*  block of data.
*
*  The implementation of the Write() function is driver dependent. Some drivers
*  may buffer all the data internally and some may just store the DataPtr and
*  the DataLength and then read from the app buffer as data is being transmitted.
*
*  The copying of the TX data from the app to the HW (or internal TX buffer in
*  the driver) is done in the context of the Write() function (the driver) in
*  order to make sure that the app does not have to know anything about the
*  implementation of the HW/TX data buffering in the driver. The drawback of
*  this is that it may be necessary to copy the data from the app buffer to a
*  temporary TX data holding buffer in the driver.
*
*  The Write() function returns:
*   1. DRV_ERR_NONE if the data is copied to the HW or a TX data holding buffer
*      immediately, and the app can free/reuse the buffer (DataPtr) immediately
*      after the Write function has returned.
*   2. DRV_ERR_BUSY if the TX data is not copied to the HW or a TX data holding
*      buffer immediately. The driver stores the DataPtr and the DataLength and
*      copies the data to the HW as the HW is ready to receive more data. The
*      app may not free/reuse the buffer (DataPtr) before a DRV_SERCOM_EV_TX_DONE
*      event has been sent to the app via the call back function registered in
*      the driver.
*   3. DRV_SERCOM_ERR_TX_BUFFER_FULL if the driver is not able to send the data r
*      equested. The app must wait for DRV_SERCOM_EV_TX_DONE and then call Write()
*      again in order to get the data sent or through the data away (treat this
*      as buffer overrun).
*   4. <ERROR code> if the driver is not able to send any data due to e.g. HW
*      problems, the driver has not been initialised etc.
*
*  The app must be able to handle all cases mentioned above.
*  I.e. depending on the driver it may be possible to copy the data directly to a
*  buffer in the context of the Write() function or copy the data form the app
*  buffer in the context of the driver (ISR).
****************************************************************************/
typedef DrvErrorType (*DrvClassSerCom_CmdWritePtrType)(DrvInstanceHandleType Instance, const void *DataPtr, rsuint16 DataLength);

/****************************************************************************
*  FUNCTION: Terminate()
*
*  INPUTS  : Instance
*  OUTPUTS : none
*  RETURNS : Error code
*
*  DESCRIPTION: This function is used to close the driver and flush the data in
*  the internal buffers. Re-init of the driver can be done by calling Terminate()
*  followed by Init().
****************************************************************************/
typedef DrvErrorType (*DrvClassSerCom_CmdTerminatePtrType)(DrvInstanceHandleType Instance);

/****************************************************************************
*  FUNCTION: Terminate()
*
*  INPUTS  : Instance
*  OUTPUTS : None
*  RETURNS : Number of bytes buffered in the RX buffer in the driver.
*
*  DESCRIPTION: This function is used to request the used size of the RX buffer.
****************************************************************************/
typedef rsuint16 (*DrvClassSerCom_CmdGetRxBufferSizePtrType)(DrvInstanceHandleType Instance);


// ***************************
// Device Driver Command Table
// ***************************
typedef struct DrvClassSerCom_CmdDataType
{
  // Mandatory interface
  DrvCdiType                                Cdi;
  // SerCom class specific commands
  DrvClassSerCom_CmdWritePtrType            Write;
  DrvClassSerCom_CmdReadPtrType             Read;
  DrvClassSerCom_CmdTerminatePtrType        Terminate;
  DrvClassSerCom_CmdGetRxBufferSizePtrType  GetRxBufferSize;

} DrvClassSerCom_CmdDataType;




/****************************************************************************
*                           Global variables/const
****************************************************************************/


/****************************************************************************
*                             Function prototypes
****************************************************************************/



#endif

