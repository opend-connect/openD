// =============================================================================
/*!
 * @file       src/interfaces/on_off.cpp
 *
 * This file contains the implementation of the common functionality for the
 * On-Off interface.
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

#include "hanfun/interfaces/on_off.h"

// =============================================================================
// API
// =============================================================================

using namespace HF;
using namespace HF::Interfaces;
using namespace HF::Interfaces::OnOff;

// =============================================================================
// create_attribute
// =============================================================================
/*!
 *
 */
// =============================================================================
HF::Attributes::IAttribute *OnOff::create_attribute (uint8_t uid)
{
   return Interfaces::create_attribute ((OnOff::Server *) nullptr, uid);
}
