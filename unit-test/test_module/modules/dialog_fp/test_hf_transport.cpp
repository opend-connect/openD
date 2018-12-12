// =============================================================================
/*!
 * \file       /hanfun_tsp/src/transport.cpp
 *
 * This file contains the implementation of the transport
 *
 * \author     Filipe Alves <filipe.alves@bithium.com>
 *
 * \version    x.x.x
 *
 * \copyright  Copyright &copy; &nbsp; 2014 Bithium S.A.
 */
// =============================================================================

#include <iostream>
#include <sstream>  // std::ostringstream
#include <cstdint>

#include <hanfun.h>
#define HF_LOG_LEVEL HF_LOG_LEVEL_TRACE
#include <inc/hanfun/debug.h>
#include <application.h>


#include "hf_transport.h"

extern "C"
{
// #include <uleDectAPI.h>
#include <Phoenix/Api/Api.h>
#include <Phoenix/Api/FpUle/ApiFpUle.h>
#include <dect_driver.h>
#include <include/uleAppAPI.h>
}

// =============================================================================
// Defines
// =============================================================================

extern "C" void TxBuff_SendData(rsuint8 portid, rsuint8 len, rsuint8 *Data);

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


}

uint8_t changeConcentratorDectMode(uint8_t DectMode)
{

}


void resetConcentratorDectModule()
{

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

}

// =============================================================================
// HF::ULE::Transport::connected
// =============================================================================
/*!
 *
 */
// =============================================================================
void HF::ULE::Transport::connected (uint8_t dev_id, uint8_t _ipui[5])
{

}

// =============================================================================
// HF::ULE::Transport::receive
// =============================================================================
/*!
 *
 */
// =============================================================================
void HF::ULE::Transport::receive (const uint8_t dev_id, const uint8_t data[], size_t size)
{

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
   return nullptr;
}

// =============================================================================
// HF::ULE::Link
// =============================================================================
void HF::ULE::Link::send (HF::Common::ByteArray &array)
{

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

   return ULE_Success;
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

}

// =============================================================================
// Event Handing
// =============================================================================
char IsSensor;

extern "C" void mail_switch(unsigned short Length, unsigned char *MailPtr)
{


}

void initUleApp(int argc, char **argv)
{

}
