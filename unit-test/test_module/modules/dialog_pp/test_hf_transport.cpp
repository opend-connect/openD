// =============================================================================
/*!
 * \file			/HANFUN_APP/src/hanfun/transport.cpp
 *
 * This file contains the implementation of the Simple Power Meter interface.
 *
 * \author		Filipe Alves <filipe.alves@bithium.com>
 *
 * \version		x.x.x
 *
 * \copyright	Copyright &copy; &nbsp; 2014 Bithium S.A.
 */
// =============================================================================

#include <string>

#include "HanFunTask.h"

#include "hanfun.h"
#include "ule.h"

#include "dlg_transport.h"
#include "opend_hanfun.h"

#define DEF_PORT "/dev/ttyUSB0"

using namespace std;

string transport_port_name;

/*!
 * Print a string.
 */
void printString(const char* fmt, ...);

void printString(const char* fmt, ...)
{
  va_list argptr;
  va_start(argptr, fmt);
  vprintf(fmt, argptr);
  va_end(argptr);
}

/*!
 * HANFUN statemachine of the transport iwu.
 */
extern "C" void hanfun_state_machine(const RosMailType* p_mail)
{

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

// =============================================================================
// HF::ULE::Transport::initialize
// =============================================================================
/*!
 *
 */
// =============================================================================

void HF::ULE::Transport::initialize()
{
  this->_transport_init = true;
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

}

void successConInd()
{
  printf("SUCCESS");
}

void failureConInd()
{
  printf("FAIL");
}

void exitApp()
{
  HF::ULE::Transport * g_transport = HF::ULE::Transport::instance();
  g_transport->destroy();
}
