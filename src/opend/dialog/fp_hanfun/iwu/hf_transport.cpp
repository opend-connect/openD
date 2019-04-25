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

#include <iostream>
#include <sstream>  // std::ostringstream
#include <cstdint>

#include <hanfun.h>
#define HF_LOG_LEVEL HF_LOG_LEVEL_TRACE
#include <inc/hanfun/debug.h>
#include <application.h>


#include "hf_transport.h"

#include "apps/base.h"

#include "opend_hanfun.h"

extern "C"
{
#include <uleDectAPI.h>
#include <Phoenix/Api/Api.h>
#include <Phoenix/Api/FpUle/ApiFpUle.h>
#include <dect_driver.h>
#include <include/uleAppAPI.h>
}

#include "opend_hanfun_api.h"

bool restoreRunning = false;

// =============================================================================
// Defines
// =============================================================================

extern "C" void TxBuff_SendData(rsuint8 portid, rsuint8 len, rsuint8 *Data);

static void ule_disable_registration_timeout_clb( void );

#define GET_ID(X) (X->TerminalId & 0xFF)

// =============================================================================
// Helper Functions
// =============================================================================

static int8_t com_port_global = NO_COMPORT_USE;
static std::string global_port_name;

void setBaseComport(int8_t comport)
{
	com_port_global = comport;
}

void setBaseHdlcPortStr(std::string portname)
{
	global_port_name = portname;
}


std::string rfpiToHex( uint8_t data[5] )
{
	std::ostringstream oss;

	oss << std::hex << std::setfill('0');

	for(uint8_t i=0; i < 5; i++) {
		oss << ':' << std::setw(2) << std::uppercase << std::hex << (uint8_t)data[i];
	}

	return oss.str().substr(1);	// cut leading ':'
}

std::string getBaseRfpiString()
{

	uint8_t baseRFPI[5] = {0};

	ULE_GetRFPI(baseRFPI);

	//std::string s = "hf://" + rfpiToHex(baseRFPI);
	//return s;
	return rfpiToHex(baseRFPI);

}

uint8_t changeConcentratorDectMode(uint8_t DectMode)
{
  /*
   * Wrapper to uleResourceManager ULE_DectMode()
   * Available DectMode Options: 0: EU, 1: US:, 2:JP_5CH
   * After execution of ULE_DectMode() the system should wait and exit
   */
  return (uint8_t) ULE_DectMode(DectMode);
}


void resetConcentratorDectModule()
{
	/* Wrapper to uleResourceManager ULE_Fp_Reset() */
	ULE_Fp_Reset();
}


extern "C" void request_device_core_info( uint8_t dev_legacy_id )
{
   openD_hanfunApi_devMgmtInd_t hMgmtInd;
   hMgmtInd.service = OPEND_HANFUNAPI_DEVICE_MANAGEMENT_GET_DEVICE_CORE_INFORMATION;
   hMgmtInd.param.getAddress.address = (uint16_t) dev_legacy_id;
   openD_hanfun_devMgmtInd( &hMgmtInd );
}

// =============================================================================
// API
// =============================================================================

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
// HF::ULE::Transport::initialize
// =============================================================================
/*!
 *
 */
// =============================================================================
void HF::ULE::Transport::initialize ()
{
   int8_t comport;
   std::string website_location("../ULE_ReferenceDesign/legacy_apps/ApplicationData/website");
   std::string target_ip(TARGET_IPADDR);

   if ( com_port_global != NO_COMPORT_USE && com_port_global != ULE_INIT_CONNECT_ON_LINUX_HOST) {
	   comport = com_port_global;
   }

   if ( com_port_global == ULE_INIT_CONNECT_ON_LINUX_HOST ) {
	   if ( global_port_name.length() > 0 )
	   ULE_Configure_Hdlc_Port(global_port_name.c_str());
   }


   if (ULE_Init(ACCESSCODE, 200, 0, (char*)website_location.c_str(), 8020, (char *)target_ip.c_str(), TRUE, FALSE, FALSE, comport) != ULE_Success)
   {
      LOG(ERROR) << "ULE FAILED to INIT. Exiting.." << NL;
      exit(-1);
   }
}

// =============================================================================
// HF::ULE::Transport::destroy
// =============================================================================
/*!
 *
 */
// =============================================================================
void HF::ULE::Transport::destroy ()
{
   ULE_Exit();
}

// =============================================================================
// HF::ULE::Transport::connected
// =============================================================================
/*!
 *
 */
// =============================================================================
void HF::ULE::Transport::connected (uint16_t dev_id, uint8_t _ipui[5])
{
   Link * link = this->find_by_id(dev_id);

   if (link == nullptr)
   {
      HF::UID::DECT ipui;
      ipui[0] = _ipui[0];
      ipui[1] = _ipui[1];
      ipui[2] = _ipui[2];
      ipui[3] = _ipui[3];
      ipui[4] = _ipui[4];
      link = new Link(dev_id, ipui, this);
      add(link);
   }
}

// =============================================================================
// HF::ULE::Transport::receive
// =============================================================================
/*!
 *
 */
// =============================================================================
void HF::ULE::Transport::receive (const uint16_t dev_id, const uint8_t data[], size_t size)
{
   HF::Common::ByteArray payload(data, size);

   auto link = this->find_by_id(dev_id);

   // Link was found send to endpoints.
   if (link != nullptr)
   {
      HF::Devices::Concentrator::Transport::receive(link, payload);
   }
   else
   {
      LOG(ERROR) << "Could not find link for device : " << dev_id << NL;
   }
}

// =============================================================================
// HF::ULE::Transport::find_by_id
// =============================================================================
/*!
 *
 */
// =============================================================================
HF::ULE::Link * HF::ULE::Transport::find_by_id (uint16_t dev)
{
   auto it = std::find_if(links.begin(), links.end(), [dev](const HF::Transport::Link * link)
   {
      return ((HF::ULE::Link *)link)->id() == dev;
   });

   // Link was found send to endpoints.
   if (it != links.end())
   {
      return static_cast<HF::ULE::Link *>(*it);
   }

   return nullptr;
}

// =============================================================================
// HF::ULE::Transport::find_by_address
// =============================================================================
/*!
 *
 */
// =============================================================================
HF::ULE::Link * HF::ULE::Transport::find_by_address (uint16_t address)
{
   auto it = std::find_if(links.begin(), links.end(), [address](const HF::Transport::Link * link)
   {
      return link->address() == address;
   });

   // Link was found.
   if (it != links.end())
   {
      return static_cast<HF::ULE::Link *>(*it);
   }

   return nullptr;
}

// =============================================================================
// HF::ULE::Link
// =============================================================================
void HF::ULE::Link::send (HF::Common::ByteArray &array)
{
   LOG(DEBUG) << __PRETTY_FUNCTION__ << " : " << array << NL;

  // TxBuff_SendData(dev_id,array.size(), (rsuint8*) array.data());
   std::for_each (array.begin (), array.end (), [](uint8_t byte)
   {
      printf(" %X ",byte);
   });
   rsuint8 DlcCtrl = 0x80 ; /*Bit7, Dummy Bearer Paging*/
   SendApiFpUleDataReq(API_TASK, dev_id, DlcCtrl, array.size(), (rsuint8*) array.data());
}

// =============================================================================
// HF::ULE::Registration
// =============================================================================
/*!
 *
 */
// =============================================================================
bool HF::Application::Registration (bool mode)
{
   UleErr_e res;

   if (mode)
   {
      res = ULE_Enable_Registration(60, ule_disable_registration_timeout_clb);
   }
   else
   {
      res = ULE_Disable_Registration();
   }

   return res == ULE_Success;
}

static void ule_disable_registration_timeout_clb( void ) {
   openD_hanfunApi_devMgmtInd_t hDevMgmtIndication;

   hDevMgmtIndication.service = OPEND_HANFUNAPI_DEVICE_MANAGEMENT_REGISTER_DISABLE;
   openD_hanfun_devMgmtInd( &hDevMgmtIndication );

   return;
}

// =============================================================================
// HF::ULE::Deregister
// =============================================================================
/*!
 * \warning Can only de-register devices from ULE that are currently connected.
 */
// =============================================================================
void HF::Application::Deregister (uint16_t address)
{
   auto link = HF::ULE::Transport::instance()->find_by_address(address);

   if (link != nullptr)
   {
      if (ULE_DeRegister(link->id()) != ULE_Success)
      {
         LOG(ERROR) << "Could not de-register device : " << address << NL;
      }
   }
   else
   {
      LOG (WARN) << "Could not find link for address : " << address << NL;
   }
}

// =============================================================================
// Event Handing
// =============================================================================
char IsSensor;

extern "C" void mail_switch(unsigned short Length, unsigned char *MailPtr)
{
   HF::ULE::Transport * transport = HF::ULE::Transport::instance();

   ApifpuleEmptySignalType *p_mail = (ApifpuleEmptySignalType *) MailPtr;

   switch (p_mail->Primitive)
   {
      case API_FP_ULE_INIT_CFM:
      {
         LOG (TRACE) << ">>> API_FP_ULE_INIT_CFM <<<" << NL;
         break;
      }
      case API_FP_ULE_PVC_CONFIG_RES:
      {
         LOG (TRACE) << ">>> API_FP_ULE_PVC_CONFIG_RES <<<" << NL;
         break;
      }
      case API_FP_ULE_PVC_CONFIG_CFM:
      {
         LOG (TRACE) << ">>> API_FP_ULE_PVC_CONFIG_CFM <<<" << NL;

         ApiFpUlePvcConfigCfmType * p_cfm = (ApiFpUlePvcConfigCfmType *) p_mail;

         LOG (TRACE) << "Getting IPUI for device " << std::hex
                     << GET_ID(p_cfm) << std::dec << NL;
		 printf("SendApiFpUleGetDeviceIpuiReq %d \n", p_cfm->TerminalId);
         SendApiFpUleGetDeviceIpuiReq(API_TASK, p_cfm->TerminalId);

         break;
      }
      case API_FP_ULE_PVC_CONFIG_REJ:
      {
         LOG (TRACE) << ">>> API_FP_ULE_PVC_CONFIG_REJ <<<" << NL;
         break;
      }
      case API_FP_ULE_PVC_CONFIG_IND:
      {
    	  IsSensor=0;
         LOG (TRACE) << ">>> API_FP_ULE_PVC_CONFIG_IND <<<" << NL;
         break;
      }
      case API_FP_ULE_PVC_PENDING_IND:
      {
         LOG (TRACE) << ">>> API_FP_ULE_PVC_PENDING_IND <<<" << NL;
         ApiFpUlePage_t Page[2] = { { 0, 0, 0 } };
         if(IsSensor==1){
        	 LOG (TRACE) << ">>> IS_SENSOR!!! <<<" << NL;
        	 SendApiFpUlePvcPendingRes(API_TASK, ((ApiFpUlePvcConfigIndType *) MailPtr)->TerminalId, API_FP_ULE_ERR_NO_ERROR, 1, Page);
         }

         IsSensor=1;

#if 0
         ApiFpUlePage_t Page[2] = { { 0, 0, 0 },
                                    { 0, 0, 0 } };

         SendApiFpUlePvcPendingRes(API_TASK, ((ApiFpUlePvcConfigIndType *) MailPtr)->TerminalId, API_FP_ULE_ERR_NO_ERROR, 1, Page);
#endif
         break;
      }
      case API_FP_ULE_PVC_IWU_DATA_IND:
      {
         LOG (TRACE) << ">>> API_FP_ULE_PVC_IWU_DATA_IND <<<" << NL;
         IsSensor=0;
#if 1
         // ApiFpUlePvcIwuDataIndType *pIwu= (ApiFpUlePvcIwuDataIndType*) MailPtr;
         ApiFpUlePage_t Page[2] = { { API_ULE_PAGING_CH, 10 + ((ApiFpUlePvcIwuDataIndType*) MailPtr)->TerminalId, 2 },
                                    { 0, 0, 0 } };

         // SendApiFpUlePvcIwuDataReq(API_TASK, pIwu->TerminalId, pIwu->InfoElementLength, (rsuint8*)pIwu->InfoElement);
         SendApiFpUlePvcPendingRes(API_TASK, ((ApiFpUlePvcConfigIndType *) MailPtr)->TerminalId, API_FP_ULE_ERR_NO_ERROR, 1, Page);
#endif
         break;
      }
      case API_FP_ULE_GET_REGISTRATION_COUNT_CFM:
      {
         LOG (TRACE) << ">>> API_FP_ULE_GET_REGISTRATION_COUNT_CFM <<<" << NL;
         break;
      }
      case API_FP_ULE_DELETE_REGISTRATION_CFM:
      {
         LOG (TRACE) << ">>> API_FP_ULE_DELETE_REGISTRATION_CFM <<<" << NL;
         break;
      }
      case API_FP_ULE_GET_DEVICE_IPUI_CFM:
      {
         LOG (TRACE) << ">>> API_FP_ULE_GET_DEVICE_IPUI_CFM <<<" << NL;

         ApiFpUleGetDeviceIpuiCfmType * p_ipui = (ApiFpUleGetDeviceIpuiCfmType *) p_mail;

         LOG (TRACE) << ">>> ID :" << std::hex << GET_ID(p_ipui) << std::dec << " <<<" << NL;

         if( !restoreRunning ) {
            auto link = transport->find_by_id(GET_ID(p_ipui));

            if (link == nullptr)
            {
               transport->connected (GET_ID(p_ipui), p_ipui->IPUI);
            }
            // already registered
         }
         break;
      }
      case API_FP_ULE_DATA_IND:
      {
         LOG (TRACE) << ">>> API_FP_ULE_DATA_IND <<<" << NL;

         ApiFpUleDataIndType * p_data = (ApiFpUleDataIndType *) p_mail;
         if (p_data->Length==0) break;

         transport->receive(GET_ID(p_data), p_data->Data, p_data->Length);

         break;
      }
      case API_FP_ULE_DTR_IND:
      {
         LOG (TRACE) << ">>> API_FP_ULE_DTR_IND <<<" << NL;
         break;
      }
      case API_FP_ULE_ABORT_DATA_CFM:
      {
         LOG (TRACE) << ">>> API_FP_ULE_ABORT_DATA_CFM <<<" << NL;
         break;
      }
      case API_FP_ULE_DATA_CFM:
      {
         LOG (TRACE) << ">>> API_FP_ULE_DATA_CFM <<<" << NL;
         break;
      }
      case API_FP_ULE_FEATURES_CFM:
      {
         LOG (TRACE) << ">>> API_FP_ULE_FEATURES_CFM <<<" << NL;
         break;
      }
      case RTX_EAP_TRACE_INPUT_MAIL_IND:
    	  // trace mails, ignore them
    	  break;
      default:

         LOG (TRACE) << ">>> " << __PRETTY_FUNCTION__ << " : "
                     << std::hex << p_mail->Primitive << std::dec << " <<<" << NL;

         break;
   }
}

void initUleApp(int argc, char **argv)
{
  int8_t comport = ULE_INIT_CONNECT_ON_LINUX_HOST;

  setBaseComport(comport);
  if ( comport == ULE_INIT_CONNECT_ON_LINUX_HOST && argc >=2) {
     std::string port_ipnut (argv[1]);
     setBaseHdlcPortStr(port_ipnut);
  }

  std::string baseRFPIstr = getBaseRfpiString();
  LOG(DEBUG) << "BASE RFPI: " << baseRFPIstr << NL;

  HF::UID::URI uid(baseRFPIstr);

  /* HAN-FUN Transport Layer over ULE Stack. */
  HF::ULE::Transport * transport = HF::ULE::Transport::instance();
  transport->uid(&uid);
}
