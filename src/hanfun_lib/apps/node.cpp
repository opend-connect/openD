// =============================================================================
/*!
 * @file       apps/node.cpp
 *
 * This file contains the implementation of the Node class that represents the
 * HAN-FUN Node on the example application.
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
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

#include "node.h"

#include "common.h"

// #define HF_LOG_LEVEL HF_LOG_LEVEL_TRACE
#include "application.h"

// =============================================================================
// Node
// =============================================================================

/*!
 * @addtogroup examples
 * @{
 */

// =============================================================================
// Node::receive
// =============================================================================
/*!
 *
 */
// =============================================================================
void Node::receive (HF::Protocol::Packet &packet, HF::Common::ByteArray &payload, uint16_t offset)
{
   LOG (DEBUG) << ">>>>>>>>>>>>> Message Received <<<<<<<<<<<<<" << NL;

   LOG (TRACE) << "Payload : " << payload << NL;

   LOG (DEBUG) << packet << NL;

   HF::Devices::Node::Abstract <HF::Devices::Node::DefaultUnit0>::receive (packet, payload, offset);
}

// =============================================================================
// Simple Light
// =============================================================================

void SimpleLight::on (HF::Protocol::Address &source)
{
   HF::Units::Unit <HF::Profiles::SimpleLight>::on (source);
   LOG (INFO) << ">>>>>>>>>>>>> SimpleLight : ON <<<<<<<<<<<<<" << NL;
}

void SimpleLight::off (HF::Protocol::Address &source)
{
   HF::Units::Unit <HF::Profiles::SimpleLight>::off (source);
   LOG (INFO) << ">>>>>>>>>>>>> SimpleLight : OFF <<<<<<<<<<<<<" << NL;
}

void SimpleLight::toggle (HF::Protocol::Address &source)
{
   HF::Units::Unit <HF::Profiles::SimpleLight>::toggle (source);
   LOG (INFO) << ">>>>>>>>>>>>> SimpleLight : TOGGLE <<<<<<<<<<<<<" << NL;
}

/*! @} */
