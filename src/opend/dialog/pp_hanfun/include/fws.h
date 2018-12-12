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

/****************************************************************************
* Includes
****************************************************************************/
#ifndef FWS_H
#define FWS_H


#define FWS_TIMER			UART_LOG_TIMER
#define FWS_BUF_SIZE		510

typedef struct
{
  rsuint8					Enabled;
  rsuint8 					TaskDisable;
  rsuint8					Ready;
  rsuint8					DataAvail;
  rsuint32					Offst;
  rsuint8					XferTimeouts;
  rsuint8					NextMsgAction;
  rsuint16					len;
  rsuint8 					DataBuf[FWS_BUF_SIZE];
} MmiFWS_t;



void FwsApiFwsStatusInd(const ApiFwsStatusIndType *m);
void FwsApiFwsWriteExtDataCfm(const ApiFwsWriteExtDataCfmType *m);
void FwsApiPpUleDataInd(const ApiPpUleDataIndType* m);
void FwsApiPpUleDataInd_MdtFws(const MmiUleData_MmiDataTypeFws* d);
void FwsTimeout();
void FwsStart(void);
void FwsAbort(const char* reason);
void FwsFillDataPacket(MmiUlePdu_common_t* Datapacket);


#endif // FWS_H
