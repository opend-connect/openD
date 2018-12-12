// =============================================================================
/*!
 * @file       inc/hanfun/devices.h
 *
 * This file contains the definitions for the devices in a HAN-FUN network.
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
#ifndef HF_DEVICES_H
#define HF_DEVICES_H

#include "hanfun/common.h"
#include "hanfun/protocol.h"

#include "hanfun/device.h"

#include "hanfun/core.h"
#include "hanfun/core/device_information.h"
#include "hanfun/core/device_management.h"
#include "hanfun/core/bind_management.h"
#include "hanfun/core/attribute_reporting.h"

#include "hanfun/transport.h"

namespace HF
{
   /*!
    * This is the top-level namespace for the HAN-FUN devices implementation.
    */
   namespace Devices
   {
      /*! @defgroup devices Devices
       *
       * This module contains the classes that define and implement the %Devices API.
       *
       * @addtogroup dev_common Common
       * @ingroup devices
       *
       * This module contains the common classes for the implementation of the %Devices API.
       * @{
       */

      /*!
       * This class provides the basic implementation for the Device's interface.
       */
      struct AbstractDevice:public IDevice
      {
         // =============================================================================
         // IDevice API
         // =============================================================================

         const IUnits &units () const
         {
            return _units;
         }

         void add (Units::IUnit *unit)
         {
            _units.push_front (unit);
         }

         void remove (Units::IUnit *unit)
         {
            _units.remove (unit);
         }

         Units::IUnit *unit (uint8_t id) const;

         void send (Protocol::Packet &packet);

         void receive (Protocol::Packet &packet, Common::ByteArray &payload, uint16_t offset);

         void periodic (uint32_t time);

         protected:

         //! Last reference number used to send a packet.
         uint8_t next_reference;

         //! List containing pointers to the units present in the device.
         IUnits _units;

         //! Support for generating missing responses for messages.
         Protocol::Filters::ResponseRequired response_filter;

         AbstractDevice():
            next_reference (0)
         {}

         // =============================================================================

         /*!
          * Return the link that can be used to send a packet to the device with the given
          * address.
          *
          * @param [in] addr    the address of the device to send the packet to.
          *
          * @return             a pointer to the link that can be used to send the packet,
          *                     @c nullptr otherwise;
          */
         virtual Transport::Link *link (uint16_t addr) const = 0;

         /*!
          * Check if the given packet is for this device.
          *
          * @param [in] packet   reference to the incoming packet.
          *
          * @return
          */
         virtual bool is_local (Protocol::Packet &packet)
         {
            return packet.destination.device == address ();
         }

         /*!
          * Check if the device has a valid, i.e. not HF::Protocol::BROADCAST_ADDR.
          *
          * @return  if the device address is different from HF::Protocol::BROADCAST_ADDR.
          */
         bool is_registered ()
         {
            return this->address () != Protocol::BROADCAST_ADDR;
         }
      };

      /*! @} */

      /*!
       * This is the namespace for the implementation of the HAN-FUN %Node devices.
       */
      namespace Node
      {
         /*!
          * @addtogroup node  Node device API.
          * @ingroup devices
          *
          * This module contains the classes that define and implement the %Device API on the
          * node side.
          * @{
          */

         /*!
          * Interface of Unit 0 for Node devices.
          */
         struct IUnit0:public HF::Core::Unit0, public HF::IDevice::IUnit0
         {
            /*!
             * Constructor
             *
             * @param device  reference to the device this unit 0 belongs to.
             */
            IUnit0(HF::IDevice &device):
               HF::Core::Unit0 (device)
            {}

            /*!
             * Get the pointer to the node's Device Management service.
             *
             * @return pointer to the node's Device Management service.
             */
            virtual HF::Core::DeviceManagement::Client *device_management () = 0;

            /*!
             * Get the pointer to the node's Device Management service.
             *
             * @return pointer to the node's Device Management service.
             */
            virtual HF::Core::DeviceManagement::Client *device_management () const = 0;
         };

         /*!
          * Template to create Unit 0 for HAN-FUN node devices.
          */
         template<typename... ITF>
         struct Unit0:public HF::Unit0 <IUnit0, ITF...>
         {
            static_assert (std::is_base_of <HF::Core::DeviceManagement::Client,
                                            typename HF::Unit0 <IUnit0, ITF...>::DeviceMgt>::value,
                           "DeviceMgt must be of type HF::Core::DeviceManagement::Client");

            typedef typename HF::Unit0 <IUnit0, ITF...> _Parent;

            typedef typename _Parent::DeviceInfo DeviceInfo;
            typedef typename _Parent::DeviceMgt DeviceMgt;
            typedef typename _Parent::AttrReporting AttrReporting;

            /*!
             * Constructor
             *
             * @param device  reference to the device this unit 0 belongs to.
             */
            Unit0(IDevice &device):
               HF::Unit0 <IUnit0, ITF...>(device)
            {}

            /*!
             * Get the pointer to the node's Device Information service.
             *
             * @return pointer to the node's Device Information service.
             */
            DeviceInfo *device_info () const
            {
               return _Parent::device_info ();
            }

            /*!
             * Get the pointer to the node's Device Information service.
             *
             * @return pointer to the node's Device Information service.
             */
            DeviceInfo *device_info ()
            {
               return _Parent::device_info ();
            }

            /*!
             * Get the pointer to the node's Attribute Reporting service.
             *
             * @return pointer to the node's Attribute Reporting service.
             */
            AttrReporting *attribute_reporting () const
            {
               return _Parent::attribute_reporting ();
            }

            /*!
             * Get the pointer to the node's Attribute Reporting service.
             *
             * @return pointer to the node's Attribute Reporting service.
             */
            AttrReporting *attribute_reporting ()
            {
               return _Parent::attribute_reporting ();
            }

            /*!
             * Get the pointer to the node's Device Management service.
             *
             * @return pointer to the node's Device Management service.
             */
            DeviceMgt *device_management ()
            {
               return &std::get <_Parent::DEV_MGT>(_Parent::interfaces);
            }

            /*!
             * Get the pointer to the node's Device Management service.
             *
             * @return pointer to the node's Device Management service.
             */
            DeviceMgt *device_management () const
            {
               return const_cast <DeviceMgt *>(&std::get <_Parent::DEV_MGT>(_Parent::interfaces));
            }
         };

         /*!
          * Unit0 using default classes to provide the core services for node devices.
          */
         struct DefaultUnit0:public Unit0 <HF::Core::DeviceInformation::Server,
                                           HF::Core::DeviceManagement::Client,
                                           HF::Core::AttributeReporting::Server>
         {
            DefaultUnit0(IDevice &device):
               Unit0 <Core::DeviceInformation::Server, Core::DeviceManagement::Client,
                      Core::AttributeReporting::Server>(device)
            {}
         };

         /*!
          * Template for declaring HAN-FUN node devices.
          */
         template<typename CoreServices = DefaultUnit0>
         class Abstract:public AbstractDevice
         {
            public:

            // =============================================================================
            // Transport::Endpoint API
            // =============================================================================

            void connected (HF::Transport::Link *link)
            {
               _link = link;
            }

            void disconnected (HF::Transport::Link *link)
            {
               if (_link == link)
               {
                  _link = nullptr;
               }
            }

            void receive (Protocol::Packet &packet, Common::ByteArray &payload, uint16_t offset)
            {
               AbstractDevice::receive (packet, payload, offset);
            }

            // =============================================================================
            // IDevice API.
            // =============================================================================

            uint16_t address () const
            {
               return unit0 ()->device_management ()->address ();
            }

            CoreServices *unit0 () const
            {
               return const_cast <CoreServices *>(&_unit0);
            }

            protected:

            //! Link to the be used when sending packets to the network.
            HF::Transport::Link *_link;

            //! Unit 0 implementation this device will use.
            CoreServices _unit0;

            Abstract():_link (nullptr), _unit0 (*this)
            {}

            // =============================================================================

            HF::Transport::Link *link (uint16_t addr) const
            {
               UNUSED (addr);
               return _link;
            }

            /*!
             * Check if an incoming packet is for the node.
             *
             * @param [in] packet reference to the incoming packet.
             *
             * @retval  true  if the packet if for the node;
             * @retval  false otherwise.
             */
            bool is_local (Protocol::Packet &packet)
            {
               return AbstractDevice::is_local (packet) ||
                      // If we are unregistered only allow packets to unit 0.
                      (address () == Protocol::BROADCAST_ADDR && packet.destination.unit == 0);
            }
         };

         typedef Abstract <> Node;

         /*!
          * Parent class for transport layer implementations on a HAN-FUN Node.
          */
         class Transport:public HF::Transport::AbstractLayer
         {
            protected:

            //! Pointer to the link used to send packets to the network.
            HF::Transport::Link *link;

            public:

            Transport():
               link (nullptr)
            {}

            void destroy ()
            {
               remove ((HF::Transport::Link *) nullptr);
            }

            void add (HF::Transport::Endpoint *ep)
            {
               HF::Transport::AbstractLayer::add (ep);

               if (link != nullptr)
               {
                  ep->connected (link);
               }
            }

            /*!
             * Add the given link to the list of known links and call the connected method
             * for all registered end-points.
             *
             * @param [in] _link  pointer to the link to add.
             */
            void add (HF::Transport::Link *_link)
            {
               assert (_link != nullptr);

               this->link = _link;
               HF::Transport::AbstractLayer::connected (_link);
            }

            /*!
             * Call the @c disconnected method for all registered end-points with the
             * given @c _link and remove it from list of known links.
             *
             * If @c _link is @c nullptr, then remove all known links.
             *
             * @param [in] _link  pointer to the link to remove.
             */
            void remove (HF::Transport::Link *_link = nullptr)
            {
               if ((_link == nullptr && this->link != nullptr) || (_link == this->link))
               {
                  HF::Transport::AbstractLayer::disconnected (this->link);
                  delete this->link;
                  this->link = nullptr;
               }
            }

            using HF::Transport::AbstractLayer::remove;

            /*!
             * Find the link used to send messages to the HAN-FUN device with
             * the given @c address.
             *
             * @note in the nodes there is only one link as all messages are sent to the base.
             *
             * @param [in] address  the HAN-FUN address to find the link for.
             *
             * @return  a pointer to the link for the given address or
             *          @c nullptr if no link exists for the given address.
             */
            HF::Transport::Link *find (uint16_t address)
            {
               UNUSED (address);
               return link;
            }
         };

         /*! @} */

      } // namespace Node

      /*!
       * This is the namespace for the implementation of HAN-FUN %Concentrator devices.
       */
      namespace Concentrator
      {
         /*!
          * @addtogroup concentrator  Concentrator device API.
          * @ingroup devices
          *
          * This module contains the classes that define and implement the %Device API on the
          * concentrator side.
          * @{
          */

         /*!
          * Unit 0 interface API for HAN-FUN Concentrators.
          */
         struct IUnit0:public HF::Core::Unit0, public HF::IDevice::IUnit0
         {
            /*!
             * Constructor
             *
             * @param device  reference to the device this unit 0 belongs to.
             */
            IUnit0(HF::IDevice &device):
               HF::Core::Unit0 (device)
            {}

            /*!
             * Return a pointer to unit 0 device management service.
             *
             * @return  pointer to unit 0 device management service.
             */
            virtual HF::Core::DeviceManagement::IServer *device_management () = 0;

            /*!
             * Return a pointer to unit 0 device management service.
             *
             * @return  pointer to unit 0 device management service.
             */
            virtual HF::Core::DeviceManagement::IServer *device_management () const = 0;

            /*!
             * Return a pointer to unit 0 bind management service.
             *
             * @return  pointer to unit 0 bind management service.
             */
            virtual HF::Core::BindManagement::IServer *bind_management () = 0;

            /*!
             * Return a pointer to unit 0 bind management service.
             *
             * @return  pointer to unit 0 bind management service.
             */
            virtual HF::Core::BindManagement::IServer *bind_management () const = 0;
         };

         /*!
          * Template to create Unit0 for HAN-FUN concentrator devices.
          */
         template<typename... ITF>
         struct Unit0:public HF::Unit0 <IUnit0, ITF...>
         {
            static_assert (std::is_base_of <HF::Core::DeviceManagement::IServer,
                                            typename HF::Unit0 <IUnit0, ITF...>::DeviceMgt>::value,
                           "DeviceMgt must be of type HF::Core::DeviceManagement::IServer");

            typedef typename HF::Unit0 <IUnit0, ITF...> _Parent;

            typedef typename _Parent::DeviceInfo DeviceInfo;
            typedef typename _Parent::DeviceMgt DeviceMgt;
            typedef typename _Parent::AttrReporting AttrReporting;

            typedef typename std::tuple_element <3, decltype (_Parent::interfaces)>::type BindMgt;

            static_assert (std::is_base_of <HF::Core::BindManagement::IServer, BindMgt>::value,
                           "BindMgt must be of type HF::Core::BindManagement::IServer");

            /*!
             * Constructor
             *
             * @param device  reference to the device this unit 0 belongs to.
             */
            Unit0(HF::IDevice &device):
               HF::Unit0 <IUnit0, ITF...>(device)
            {}

            BindMgt *bind_management () const
            {
               return const_cast <BindMgt *>(&std::get <3>(_Parent::interfaces));
            }

            BindMgt *bind_management ()
            {
               return &std::get <3>(_Parent::interfaces);
            }

            DeviceInfo *device_info () const
            {
               return _Parent::device_info ();
            }

            DeviceInfo *device_info ()
            {
               return _Parent::device_info ();
            }

            AttrReporting *attribute_reporting () const
            {
               return _Parent::attribute_reporting ();
            }

            AttrReporting *attribute_reporting ()
            {
               return _Parent::attribute_reporting ();
            }
         };

         /*!
          * Unit0 using default classes to provide the core services.
          */
         struct DefaultUnit0:public Unit0 <Core::DeviceInformation::Server,
                                           Core::DeviceManagement::DefaultServer,
                                           Core::AttributeReporting::Server,
                                           Core::BindManagement::DefaultServer>
         {
            /*!
             * Constructor
             *
             * @param device  reference to the device this unit 0 belongs to.
             */
            DefaultUnit0(IDevice &device):
               Unit0 (device)
            {}
         };

         /*!
          * This is the parent class for the HAN-FUN Concentrator devices
          * implementation.
          */
         class AbstractBase:public AbstractDevice
         {
            public:

            // =============================================================================
            // IDevice API.
            // =============================================================================

            uint16_t address () const
            {
               return 0;
            }

            // =============================================================================
            // Transport::Endpoint API
            // =============================================================================

            void connected (HF::Transport::Link *link);

            void disconnected (HF::Transport::Link *link);

            void receive (Protocol::Packet &packet, Common::ByteArray &payload, uint16_t offset);

            virtual ~AbstractBase() {}

            protected:

            //! List of links present in this concentrator.
            Common::SimpleList <Transport::Link *> _links;

            // =============================================================================

            HF::Transport::Link *link (uint16_t addr) const;

            /*!
             * Route the given packet to the corresponding device.
             *
             * @param [in] packet  reference for the packet to route.
             * @param [in] payload reference to the ByteArray containing the packet payload.
             * @param [in] offset  offset from where the packet data starts.
             */
            virtual void route_packet (Protocol::Packet &packet, Common::ByteArray &payload,
                                       uint16_t offset);

            /*!
             * Get the unit 0 used by this concentrator device.
             *
             * @return pointer to the unit 0 used by this concentrator device.
             */
            virtual Concentrator::IUnit0 *unit0 () const = 0;
         };

         /*!
          * Template for HAN-FUN concentrator devices.
          */
         template<typename CoreServices = DefaultUnit0>
         class Abstract:public AbstractBase
         {
            public:

            CoreServices *unit0 () const
            {
               return const_cast <CoreServices *>(&_unit0);
            }

            protected:

            CoreServices _unit0;

            Abstract():AbstractBase (), _unit0 (*this)
            {}
         };

         typedef Abstract <> Concentrator;

         /*!
          * Parent class for transport layer implementations on a HAN-FUN
          * %Concentrator device.
          */
         class Transport:public HF::Transport::AbstractLayer
         {
            protected:

            //! List of links present in the transport layer.
            Common::SimpleList <HF::Transport::Link *> links;

            public:

            virtual ~Transport()
            {
               destroy ();
            }

            void destroy ();

            void add (HF::Transport::Endpoint *ep)
            {
               HF::Transport::AbstractLayer::add (ep);
               /* *INDENT-OFF* */
               std::for_each(links.begin(), links.end(), [ep](HF::Transport::Link *link)
               {
                  ep->connected (link);
               });
               /* *INDENT-ON* */
            }

            /*!
             * Add the given link to the list of known links and call the connected method
             * for all registered end-points.
             *
             * @param [in] link  pointer to the link to add.
             */
            void add (HF::Transport::Link *link)
            {
               assert (link != nullptr);

               links.push_front (link);
               HF::Transport::AbstractLayer::connected (link);
            }

            /*!
             * Call the @c disconnected method for all registered end-points with the
             * given @c link and remove it from list of known links.
             *
             * If @c link is @c nullptr, then remove all known links.
             *
             * @param [in] link  pointer to the link to remove.
             */
            void remove (HF::Transport::Link *link = nullptr);

            using HF::Transport::AbstractLayer::remove;

            /*!
             * Find the link used to send messages to the HAN-FUN device with
             * the given @c address.
             *
             * @param [in] address  the HAN-FUN address to find the link for.
             *
             * @return  a pointer to the link for the given address or
             *          @c nullptr if no link exists for the given address.
             */
            HF::Transport::Link *find (uint16_t address);
         };

         /*! @} */

      } // namespace Concentrator

   }  // namespace Devices

}  // namespace HF

#endif /* HF_DEVICES_H */
