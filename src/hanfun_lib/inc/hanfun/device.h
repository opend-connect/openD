// =============================================================================
/*!
 * @file       inc/hanfun/device.h
 *
 * This file contains the declaration of the API for a HAN-FUN device.
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

#ifndef HF_DEVICE_H
#define HF_DEVICE_H

#include "hanfun/common.h"
#include "hanfun/transport.h"

namespace HF
{
   // Forward declaration of the core namespace.
   namespace Core
   {
      namespace DeviceInformation
      {
         struct Server;

      }  // namespace DeviceInformation

      namespace AttributeReporting
      {
         struct IServer;

      }  // namespace DeviceInformation

   }  // namespace Devices


   // Forward declaration of the units namespace.
   namespace Units
   {
      // Forward declaration of the Unit's interface.
      struct IUnit;

   }  // namespace Units

   // Forward declaration of the protocol namespace.
   namespace Protocol
   {
      // Forward declaration of the protocol packet structure.
      struct Packet;

   }  // namespace Protocol

   /*!
    * @addtogroup dev_common
    * @{
    */

   /*!
    * This class represents the interface common to all HAN-FUN devices.
    */
   struct IDevice:public Transport::Endpoint
   {
      /*!
       * %Unit list type.
       */
      struct IUnits:public Common::SimpleList <Units::IUnit *>
      {
         IUnits::size_type size () const
         {
            return distance (begin (), end ());
         }
      };

      /*!
       * HAN-FUN device Unit 0 common API.
       */
      struct IUnit0
      {
         /*!
          * Return a pointer to unit 0 device information service.
          *
          * @return  pointer to unit 0 device information service.
          */
         virtual Core::DeviceInformation::Server *device_info () const = 0;

         /*!
          * Return a pointer to unit 0 device information service.
          *
          * @return  pointer to unit 0 device information service.
          */
         virtual Core::DeviceInformation::Server *device_info () = 0;

         /*!
          * Return a pointer to unit 0 attribute reporting service.
          *
          * @return  pointer to unit 0 attribute reporting service.
          */
         virtual Core::AttributeReporting::IServer *attribute_reporting () const = 0;

         /*!
          * Return a pointer to unit 0 attribute reporting service.
          *
          * @return  pointer to unit 0 attribute reporting service.
          */
         virtual Core::AttributeReporting::IServer *attribute_reporting () = 0;
      };

      /*!
       * Return the device address on the HAN-FUN network, when the device is registered,
       * or @c HF_BROADCAST_ADDR otherwise.
       *
       * @return  the device address on the HAN-FUN network,
       *          @c HF_BROADCAST_ADDR otherwise.
       */
      virtual uint16_t address () const = 0;

      /*!
       * Return the list of units registered in this device.
       *
       * @return     list containing the device's registered units.
       */
      virtual const IUnits &units () const = 0;

      /*!
       * Return pointer to the unit with the given id.
       *
       * @param [in] id    unit identifier.
       *
       * @return  pointer to the unit with the given id,
       *          nullptr otherwise.
       */
      virtual Units::IUnit *unit (uint8_t id) const = 0;

      /*!
       * Return pointer to the unit 0 for this device.
       *
       * @return  pointer to the unit 0 for this device.
       */
      virtual IUnit0 *unit0 () const = 0;

      /*!
       * Add unit to devices unit lists.
       *
       * @param unit    pointer to the unit to add to the list.
       */
      virtual void add (Units::IUnit *unit) = 0;

      /*!
       * Remove unit from device's unit list.
       *
       * @param unit    pointer to the unit to remove from the list.
       */
      virtual void remove (Units::IUnit *unit) = 0;

      /*!
       * Send given @c packet into the HAN-FUN network.
       *
       * @param packet  reference to the packet to send to the network.
       */
      virtual void send (Protocol::Packet &packet) = 0;

      //! @copydoc HF::Interface::periodic
      virtual void periodic (uint32_t time) = 0;
   };

   /*! @} */

}  // namespace HF

#endif /* DEVICE_H_ */
