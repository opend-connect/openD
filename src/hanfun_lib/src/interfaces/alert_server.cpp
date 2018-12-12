// =============================================================================
/*!
 * @file       src/interfaces/alert_server.cpp
 *
 * This file contains the implementation of the Alert interface : Server role.
 *
 * @version    1.3.0
 *
 * @copyright  Copyright &copy; &nbsp; 2014 ULE Alliance
 *
 * For licensing information, please see the file 'LICENSE' in the root folder.
 *
 * Initial development by Bithium S.A. [http://www.bithium.com]
 */
// =============================================================================

#include "hanfun/interfaces/alert.h"

// =============================================================================
// Defines
// =============================================================================

//! Number of bits present in the alert state.
#define STATE_SIZE_BITS   (sizeof(uint32_t) * 8)

// =============================================================================
// API
// =============================================================================

using namespace HF;
using namespace HF::Interfaces;
using namespace HF::Interfaces::Alert;

// =============================================================================
// Alert Interface : Server Role
// =============================================================================

//! Constructor
Server::Server()
{
   _state   = 0x0;
   _enabled = UINT32_MAX;
}

//! Destructor
Server::~Server()
{}

// =============================================================================
// Server::state
// =============================================================================
/*!
 *
 */
// =============================================================================
uint32_t Server::state ()
{
   return this->_state;
}

// =============================================================================
// Server::state
// =============================================================================
/*!
 *
 */
// =============================================================================
void Server::set_state (uint32_t value)
{
   this->_state = value;
}

// =============================================================================
// Server::state
// =============================================================================
/*!
 *
 */
// =============================================================================
bool Server::state (uint8_t index, bool state)
{
   if (index >= STATE_SIZE_BITS)
   {
      return false;
   }

   bool res = enabled (index);

   if (res)
   {
      uint32_t mask = 1U << index;

      uint32_t old  = this->_state;

      if (state)
      {
         this->_state |= mask;
      }
      else
      {
         this->_state &= ~mask;
      }

      State old_value (old, this);
      State new_value (this->_state, this);

      this->notify (old_value, new_value);
   }

   return res;
}

// =============================================================================
// Server::state
// =============================================================================
/*!
 *
 */
// =============================================================================
bool Server::state (uint8_t index)
{
   if (index >= STATE_SIZE_BITS)
   {
      return false;
   }

   return (this->_state & (1U << index)) != 0;
}

// =============================================================================
// Server::clear
// =============================================================================
/*!
 *
 */
// =============================================================================
void Server::clear ()
{
   uint32_t old = this->_state;

   this->_state = 0;

   State old_value (old, this);
   State new_value (this->_state, this);

   notify (old_value, new_value);
}

// =============================================================================
// Server::enable
// =============================================================================
/*!
 *
 */
// =============================================================================
void Server::enable (uint8_t index)
{
   if (index > STATE_SIZE_BITS)
   {
      return;
   }

   uint32_t old = this->_enabled;

   this->_enabled |= (1U << index);

   Enable old_value (old, this);
   Enable new_value (this->_enabled, this);

   notify (old_value, new_value);
}

// =============================================================================
// Server::enableAll
// =============================================================================
/*!
 *
 */
// =============================================================================
void Server::enableAll ()
{
   uint32_t old = this->_enabled;

   this->_enabled = UINT32_MAX;

   Enable old_value (old, this);
   Enable new_value (this->_enabled, this);

   notify (old_value, new_value);
}

// =============================================================================
// Server::enabled
// =============================================================================
/*!
 *
 */
// =============================================================================
uint32_t Server::enabled ()
{
   return this->_enabled;
}

// =============================================================================
// Server::enabled
// =============================================================================
/*!
 *
 */
// =============================================================================
void Server::set_enabled (uint32_t value)
{
   this->_enabled = value;
}

// =============================================================================
// Server::enabled
// =============================================================================
/*!
 *
 */
// =============================================================================
bool Server::enabled (uint8_t index)
{
   if (index > STATE_SIZE_BITS)
   {
      return false;
   }

   return (this->_enabled & (1U << index)) != 0;
}

// =============================================================================
// Server::disable
// =============================================================================
/*!
 *
 */
// =============================================================================
void Server::disable (uint8_t index)
{
   if (index > STATE_SIZE_BITS)
   {
      return;
   }

   uint32_t old = this->_enabled;

   this->_enabled &= (~(1U << index));

   Enable old_value (old, this);
   Enable new_value (this->_enabled, this);

   notify (old_value, new_value);
}

// =============================================================================
// Server::disableAll
// =============================================================================
/*!
 *
 */
// =============================================================================
void Server::disableAll ()
{
   uint32_t old = this->_enabled;

   this->_enabled = 0;

   Enable old_value (old, this);
   Enable new_value (this->_enabled, this);

   notify (old_value, new_value);
}

// =============================================================================
// Server::disabled
// =============================================================================
/*!
 *
 */
// =============================================================================
bool Server::disabled (uint8_t index)
{
   if (index > STATE_SIZE_BITS)
   {
      return true;
   }

   return (this->_enabled & (1U << index)) == 0;
}

// =============================================================================
// Server::status_cmd
// =============================================================================
/*!
 *
 */
// =============================================================================
Alert::Message *Server::create_status (uint16_t profile_uid)
{
   return new Message (profile_uid, this->_state);
}

// =============================================================================
// Server::status
// =============================================================================
/*!
 *
 */
// =============================================================================
void Server::status (Protocol::Address &addr, uint16_t profile_uid)
{
   Message alert_msg (profile_uid, this->_state);

   Protocol::Message message (alert_msg.size ());

   message.itf.role   = CLIENT_ROLE;
   message.itf.id     = Server::uid ();
   message.itf.member = STATUS_CMD;

   alert_msg.pack (message.payload);

   send (addr, message);
}
