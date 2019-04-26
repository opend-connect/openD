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

#include "HanFunTask.h"

#include "hanfun.h"
#include "ule.h"

#include "dlg_transport.h"
#include "log.h"

#include "opend_hanfun.h"

#include "opend_ll_serial.h"
#include "hdlc.h"

#define DEF_PORT "/dev/ttyUSB0"

using namespace std;

string transport_port_name;

/*!
 * HANFUN statemachine of the transport iwu.
 */
extern "C" void hanfun_state_machine(const RosMailType* p_mail)
{
  UlePdu * pdu;
  HF::ULE::Transport * g_transport = HF::ULE::Transport::instance();

  switch (p_mail->Primitive)
  {
    case API_PP_ULE_INIT_CFM:
      openD_hanfunApi_devMgmtCfm_t hDevMgmtConfirm;
      hDevMgmtConfirm.service = OPEND_HANFUNAPI_DEVICE_MANAGEMENT_DEVICE_READY;
      hDevMgmtConfirm.status = OPEND_STATUS_OK;
      openD_hanfun_devMgmtCfm(&hDevMgmtConfirm);
      break;

  	case API_PP_ULE_DATA_IND:
    {
	  if (MmiCtrl.FWS.Enabled)
	  	break; /* Skip if we are in FWS update mode. */

        /* Print the received message. */
		    pdu = (UlePdu *)p_mail->Data.Data;
		    MmiCtrl.delaysleep=DELAYSLEEP_CHECK;

        /* Create payload and handle the received message in the HANFUN library. */
        HF::Common::ByteArray payload(pdu->data, pdu->size);
        g_transport->HF::Devices::Node::Transport::receive(new HF::ULE::Link(g_transport), payload);
		break;
    }
    case API_PP_ULE_READY_IND:
    {
    /* DECT Stack is ready to accept packet. */
          MmiCtrl.isRegistered = 1;
          openD_hanfunApi_devMgmtInd_t hMgmtInd;
          hMgmtInd.service=OPEND_HANFUNAPI_DEVICE_MANAGEMENT_REGISTER_DEVICE;
          openD_hanfun_devMgmtInd(&hMgmtInd);
          ColaMail(HANFUN_CONNECT);
		break;
    }
    case API_PP_ULE_DTR_IND:
    {
      if ( ((ApiPpUleDtrIndType *) p_mail)->Status == API_PP_ULE_ERR_NO_ERROR )
      {
        g_transport->delivered();
      }
      else
      {
        g_transport->delivered(false);
      }
      break;
      }
    case API_PP_ULE_DB_PAGE_IND:
       g_transport->check();
       break;
    case TIMEOUT:
    {
      switch (p_mail->Timeout.Parameter)
      {
        case DUMMY_MESSAGE_TIMER:
       	  g_transport->check();
          break;
      }
      break;
	  }
  }
}

// =============================================================================
// HF::ULE::Transport::instance
// =============================================================================
/*!
 *
 */
// =============================================================================
HF::ULE::Transport * HF::ULE::Transport::instance ()
{
   static HF::ULE::Transport transport;

   return &transport;
}

// =============================================================================
// HF::ULE::Transport
// =============================================================================

void hdlc_parsedPacket( uint8_t *data, uint16_t length ) {

  ColaTask( (RosMailType*) &data[2] );

	return;
}

void _allocateMemory( uint8_t **data, uint16_t length ) {

  *data = (uint8_t *) malloc( length );
}

void _freeMemory( uint8_t *data ) {
  free( data );
}

// =============================================================================
// HF::ULE::Transport::initialize
// =============================================================================
/*!
 *
 */
// =============================================================================

void HF::ULE::Transport::initialize()
{
    MmiCtrl.isRegistered = 0;

  /* HDLC initialization. */
	hdlc_init( hdlc_parsedPacket, _allocateMemory, _freeMemory, openD_ll_serial_send);

	this->_transport_init = true;

	/* Soft reset after hdlc is up */
	mmi_SoftResetModule();
	mmi_SetModuleDectModeEU();

	mmiRosTimerEmu_Init();
}

// =============================================================================
// HF::ULE::Transport::configure
// =============================================================================
/*!
 *
 */
// =============================================================================

void HF::ULE::Transport::configure(char *portname)
{

}

// =============================================================================
// HF::ULE::Transport::destroy
// =============================================================================
/*!
 *
 */
// =============================================================================
void HF::ULE::Transport::destroy()
{

}

// =============================================================================
// HF::ULE::Transport::receive
// =============================================================================
/*!
 *
 */
// =============================================================================
void HF::ULE::Transport::receive (const rsuint8 *data, size_t size)
{
  HF::Common::ByteArray payload(data, size);
  HF::Devices::Node::Transport::receive(link, payload);
}

// =============================================================================
// HF::ULE::Transport::connected
// =============================================================================
/*!
 *
 */
// =============================================================================
void HF::ULE::Transport::connected()
{
   add(new HF::ULE::Link(this));
}

// =============================================================================
// HF::ULE::Transport::check
// =============================================================================
/*!
 *
 */
// =============================================================================

void HF::ULE::Transport::check()
{
   if (tx_queue.empty() || (tx_queue.size() == 1 && is_tx_pending()))
   {
      HF::Common::ByteArray temp;
      tx_queue.push( temp);

      if (tx_queue.size() == 1)
      {
         send();
      }
   }
}
// =============================================================================
// HF::ULE::Transport::deliver
// =============================================================================
/*!
 *
 */
// =============================================================================
void HF::ULE::Transport::deliver(HF::Common::ByteArray &payload)
{
   tx_queue.push (payload);
   if(MmiCtrl.delaysleep==DELAYSLEEP_CHECK) Disable_Sleep();
   /*
    * If the stack is not ready or we are in the middle of transmitting a
    * packet or the queue is not empty, then return.
    */
   if (!is_stack_ready() || is_tx_pending() || tx_queue.size() > 1)
   {
      if (!is_stack_ready())
      {

      }

      if (is_tx_pending())
      {

      }

      if (tx_queue.size() > 1)
      {
         send(); // try to send
      }

      return;
   }

   send ();
}

// =============================================================================
// HF::ULE::Transport::delivered
// =============================================================================
/*!
 *
 */
// =============================================================================
void HF::ULE::Transport::delivered(bool result)
{
   if(result)
   {
      if (!tx_queue.empty())  // Send next message.
      {
         tx_queue.pop ();
         send ();
      }else{
    	  MmiCtrl.delaysleep=DELAYSLEEP_REENABLE;
      }
   }
}

// =============================================================================
// HF::ULE::Transport::send
// =============================================================================
/*!
 *
 */
// =============================================================================
void HF::ULE::Transport::send()
{
   if (!tx_queue.empty())
   {
      MmiCtrl.PendTDR = 1;
      if(MmiCtrl.delaysleep==DELAYSLEEP_CHECK) {Disable_Sleep();MmiCtrl.delaysleep=DELAYSLEEP_REENABLE;}
      SendApiPpUleDataReq(COLA_TASK, API_ULE_DLC_CTRL_ACKNOWLEDGED, tx_queue.front().size(), tx_queue.front().data());
   }
}
// HF::ULE::Link
// =============================================================================

// =============================================================================
// HF::ULE::Link::send
// =============================================================================
/*!
 *
 */
// =============================================================================
void HF::ULE::Link::send (HF::Common::ByteArray &payload)
{
  _layer->deliver(payload);
}

void successConInd()
{

}

void failureConInd()
{

}

void exitApp()
{
  HF::ULE::Transport * g_transport = HF::ULE::Transport::instance();
  g_transport->destroy();
}
