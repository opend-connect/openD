// =============================================================================
/*!
 * @file       apps/node.h
 *
 * This file contains the definition of the Node class that represents the
 * HAN-FUN Node on the application.
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
#ifndef HF_APP_BASE_H
#define HF_APP_BASE_H

#include "hanfun.h"

/*!
 * @addtogroup examples
 * @{
 */

// =============================================================================
// API
// =============================================================================

/*!
 * This class represents a node in the HAN-FUN network.
 */
struct Node:public HF::Devices::Node::Abstract <HF::Devices::Node::DefaultUnit0>
{
   void receive (HF::Protocol::Packet &packet, HF::Common::ByteArray &payload, uint16_t offset);
};

/*!
 * Unit implementing a Simple Light.
 */
struct SimpleLight:public HF::Units::Unit <HF::Profiles::SimpleLight>
{
   /*!
    * Constructor.
    *
    * @param [in] index    unit id.
    * @param [in] device   reference to the device that holds this unit.
    */
   SimpleLight(uint8_t index, HF::IDevice &device):
      HF::Units::Unit <HF::Profiles::SimpleLight>(index, device)
   {}

   void on (HF::Protocol::Address &source);

   void off (HF::Protocol::Address &source);

   void toggle (HF::Protocol::Address &source);
};

/*!
 * Unit implementing a Simple Switch.
 */
struct SimpleSwitch:public HF::Units::Unit <HF::Profiles::SimpleOnOffSwitch>
{
   /*!
    * Constructor.
    *
    * @param [in] index    unit id.
    * @param [in] device   reference to the device that holds this unit.
    */
   SimpleSwitch(uint8_t index, HF::IDevice &device):
      HF::Units::Unit <HF::Profiles::SimpleOnOffSwitch>(index, device)
   {}
};

/*! @} */

#endif /* HF_APP_BASE_H */
