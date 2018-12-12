// =============================================================================
/*!
 * @file       src/interfaces/level_control.cpp
 *
 * This file contains the implementation of the common functionality for the
 * Level Control interface.
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

#include "hanfun/interfaces/level_control.h"

// =============================================================================
// API
// =============================================================================

using namespace HF;
using namespace HF::Interfaces;
using namespace HF::Interfaces::LevelControl;

// =============================================================================
// LevelControl::create_attribute
// =============================================================================
/*!
 *
 */
// =============================================================================
HF::Attributes::IAttribute *LevelControl::create_attribute (uint8_t uid)
{
   return Interfaces::create_attribute ((LevelControl::Server *) nullptr, uid);
}
