// =============================================================================
/*!
 * @file       tests/test_helper.h
 *
 * This file contains the definition of helper classes used for testing.
 *
 * @version    1.3.0
 *
 * @copyright  Copyright &copy; &nbsp; 2014 Bithium S.A.
 *
 * For licensing information, please see the file 'LICENSE' in the root folder.
 */
// =============================================================================
#ifndef HF_TEST_HELPER_H
#define HF_TEST_HELPER_H

#include <string.h>
#include <sstream>
#include <algorithm>
#include <iostream>

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "hanfun/common.h"
#include "hanfun/attributes.h"
#include "hanfun/protocol.h"

#include "hanfun/interface.h"
#include "hanfun/profiles.h"
#include "hanfun/devices.h"

#include "hanfun/core/device_information.h"
#include "hanfun/core/device_management.h"
#include "hanfun/core/attribute_reporting.h"

#include "hanfun/units.h"

using namespace HF;
using namespace HF::Protocol;

// =============================================================================
// Helper Test Functions
// =============================================================================

#define STRING_FROM(_T)                                                    \
   SimpleString StringFrom (const _T &data)                                \
   {                                                                       \
      Common::SerializableHelper <_T &> wrapper (const_cast <_T &>(data)); \
      return StringFrom (wrapper);                                         \
   }

SimpleString StringFrom (const std::vector <uint8_t> &array);

SimpleString StringFrom (const HF::Common::Serializable &data);

SimpleString StringFrom (const HF::Common::Interface &itf);

template<typename _type>
void check_index (_type expected, _type actual, uint32_t index, const char *header,
                  const char *fileName,
                  int lineNumber)
{
   if (actual != expected)
   {
      std::ostringstream error;
      error << header << " at index " << index << std::endl
            << "\t\t expected : "
            << expected << std::endl
            << "\t\t but was  : "
            << actual;

      FAIL_TEST_LOCATION (error.str ().c_str (), fileName, lineNumber);
   }
}

#define CHECK_ATTRIBUTE_UID(_index, _expected, _actual) \
   check_index <uint8_t>(_expected, _actual, _index, "Attribute UID : ", __FILE__, __LINE__)

// =============================================================================
// Helper Test Classes
// =============================================================================

namespace HF
{
   namespace Testing
   {
      struct Payload
      {
         Common::ByteArray data;

         Payload(uint16_t _size = 0):
            data (_size & Protocol::MAX_PAYLOAD)
         {
            std::random_device rd;
            std::mt19937 mt (rd ());
            std::uniform_int_distribution <uint8_t> dist;

            auto gen = std::bind (dist, mt);

            std::generate_n (data.begin (), data.size (), gen);
         }

         virtual ~Payload()
         {}

         uint16_t size () const
         {
            return data.size ();
         }

         uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const
         {
            array.extend (data.size ());

            auto start = array.begin () + offset;

            array.insert (start, data.begin (), data.end ());

            return data.size ();
         }

         uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0)
         {
            assert (array.available (offset, data.size ()));

            auto begin = array.begin () + offset;
            auto end   = begin + data.size ();

            std::copy (begin, end, data.begin ());

            return data.size ();
         }
      };

      //! Test Interface.
      template<class Base>
      struct InterfaceHelper:public Base
      {
         Protocol::Address addr;
         Protocol::Message sendMsg;

         InterfaceHelper()
         {}

         virtual ~InterfaceHelper()
         {}

         void send (const Protocol::Address &addr, Protocol::Message &message)
         {
            mock ("Interface").actualCall ("send");

            this->addr    = addr;
            this->sendMsg = message;
         }

         void notify (const HF::Attributes::IAttribute &old_value,
                      const HF::Attributes::IAttribute &new_value) const
         {
            UNUSED (old_value);
            UNUSED (new_value);

            mock ("Interface").actualCall ("notify");
         }
      };

      template<class Base>
      struct InterfaceParentHelper:public InterfaceHelper <Base>
      {
         Interface::Role role () const
         {
            return Interface::SERVER_ROLE;
         }
      };

      struct TestInterface:public InterfaceHelper <Interfaces::AbstractInterface>
      {
         static const uint16_t UID = 0x5A5A;

         typedef enum
         {
            ATTR1 = 0x01,
            ATTR2 = 0x02,
            ATTR3 = 0x03,
         } Attributes;

         Interface::Role _role;
         uint16_t        _uid;
         uint16_t        attr1;
         uint16_t        attr2;
         uint16_t        attr3;

         TestInterface():_role (Interface::SERVER_ROLE), _uid (UID) {}

         TestInterface(Role role, uint16_t _uid):
            _role (role), _uid (_uid), attr1 (0x5A51), attr2 (0x5A52), attr3 (0x5A53)
         {}

         uint16_t uid () const
         {
            return _uid;
         }

         Interface::Role role () const
         {
            return _role;
         }

         HF::Attributes::IAttribute *attribute (uint8_t uid)
         {
            return create_attribute (this, uid);
         }

         //! @see AbstractInterface::attributes
         HF::Attributes::UIDS attributes (uint8_t pack_id = HF::Attributes::Pack::MANDATORY) const
         {
            HF::Attributes::UIDS result;

            if (pack_id == HF::Attributes::Pack::ALL)
            {
               result.push_back (ATTR1);
               result.push_back (ATTR2);
            }

            result.push_back (ATTR3);

            return result;
         }

         static HF::Attributes::IAttribute *create_attribute (uint8_t uid)
         {
            return create_attribute (nullptr, uid);
         }

         static HF::Attributes::IAttribute *create_attribute (TestInterface *itf, uint8_t uid)
         {
            uint16_t itf_uid = (itf != nullptr ? itf->uid () : TestInterface::UID);

            switch (uid)
            {
               case ATTR1:
               {
                  if (itf == nullptr)
                  {
                     return new HF::Attributes::Attribute <uint16_t>(itf_uid, uid);
                  }
                  else
                  {
                     return new HF::Attributes::Attribute <uint16_t &>(itf_uid, uid, itf, itf->attr1);
                  }

                  break;
               }

               case ATTR2:
               {
                  if (itf == nullptr)
                  {
                     return new HF::Attributes::Attribute <uint16_t>(itf_uid, uid);
                  }
                  else
                  {
                     return new HF::Attributes::Attribute <uint16_t &>(itf_uid, uid, itf, itf->attr2);
                  }

                  break;
               }
               case ATTR3:
               {
                  if (itf == nullptr)
                  {
                     return new HF::Attributes::Attribute <uint16_t>(itf_uid, uid, itf, 0, true);
                  }
                  else
                  {
                     return new HF::Attributes::Attribute <uint16_t &>(itf_uid, uid, itf, itf->attr3, true);
                  }

                  break;
               }

               default:
                  return nullptr;
            }
         }

         protected:

         Common::Result handle_command (Protocol::Packet &packet, Common::ByteArray &payload, uint16_t offset)
         {
            UNUSED (packet);
            UNUSED (payload);
            UNUSED (offset);

            mock ("Interface").actualCall ("handle_command").onObject (this);

            return Common::Result::OK;
         }

         bool check_uid (uint16_t uid) const
         {
            return this->_uid == uid;
         }
      };

      HF::Attributes::Factory FactoryGetter (HF::Common::Interface itf);

      //! Test Interface.
      template<class Base>
      struct ProfileHelper:public InterfaceHelper <Base>
      {
         HF::Attributes::List attributes (Common::Interface itf, uint8_t pack_id,
                                          const HF::Attributes::UIDS &uids) const
         {
            UNUSED (itf);
            UNUSED (pack_id);
            UNUSED (uids);
            return HF::Attributes::List ();
         }
      };

      struct Profile:public Profiles::IProfile, public TestInterface
      {
         uint16_t _uid;

         uint16_t uid () const
         {
            return _uid;
         }

         using TestInterface::attributes;

         HF::Attributes::List attributes (Common::Interface itf, uint8_t pack_id,
                                          const HF::Attributes::UIDS &uids) const
         {
            UNUSED (itf);
            return HF::Attributes::get (*this, pack_id, uids);
         }
      };

      struct Unit:public HF::Units::Unit <Profile>
      {
         Unit(uint16_t id, IDevice &device):
            HF::Units::Unit <Profile>(id, device)
         {}
      };

      struct Link:public HF::Transport::AbstractLink
      {
         HF::UID::UID_T       *_uid;
         HF::Transport::Layer *tsp;

         Common::ByteArray    data;

         Link(HF::UID::UID_T *uid = new HF::UID::NONE (), HF::Transport::Layer *tsp = nullptr):
            _uid (uid), tsp (tsp)
         {}

         virtual ~Link()
         {
            delete _uid;
         }

         void send (Common::ByteArray &array)
         {
            this->data = array;
            mock ("Link").actualCall ("send");
         }

         const HF::UID::UID uid () const
         {
            return HF::UID::UID(_uid);
         }

         HF::Transport::Layer const *transport () const
         {
            return tsp;
         }
      };

      template<class Parent>
      struct AbstractDevice:public Parent
      {
         uint16_t                         _address;

         std::vector <Protocol::Packet *> packets;

         Link                             link;

         AbstractDevice():
            _address (Protocol::BROADCAST_ADDR)
         {
            link.address(42);
         }

         virtual ~AbstractDevice()
         {
            /* *INDENT-OFF* */
            std::for_each (packets.begin (), packets.end (), [](Protocol::Packet *packet)
            {
               delete packet;
            });
            /* *INDENT-ON* */

            packets.clear ();
         }

         void connected (HF::Transport::Link *link)
         {
            UNUSED (link);
            mock ("AbstractDevice").actualCall ("connected");
         }

         void disconnected (HF::Transport::Link *link)
         {
            UNUSED (link);
            mock ("AbstractDevice").actualCall ("disconnected");
         }

         void send (Protocol::Packet &packet)
         {
            mock ("AbstractDevice").actualCall ("send");

            if (packet.link == nullptr)
            {
               packet.link = &link;
            }

            Parent::send (packet);

            Protocol::Packet *temp = new Protocol::Packet (packet);

            packets.push_back (temp);
         }

         void receive (Protocol::Packet &packet, Common::ByteArray &payload, uint16_t offset)
         {
            mock ("AbstractDevice").actualCall ("receive");
            Parent::receive (packet, payload, offset);
         }
      };

#define SET_SERVICE(_X, _Y) \
   {                        \
      if (_X != nullptr)    \
      {                     \
         delete _X;         \
      }                     \
                            \
      _X = _Y;              \
   }

      class DeviceUnit0:public HF::Devices::Node::IUnit0
      {
         HF::Core::DeviceInformation::Server *dev_info;
         HF::Core::DeviceManagement::Client  *dev_mgt;
         HF::Core::AttributeReporting::Server *attr_reporting;

         public:

         DeviceUnit0(HF::IDevice &device):
            HF::Devices::Node::IUnit0 (device), dev_info (nullptr), dev_mgt (nullptr),
            attr_reporting (nullptr)
         {}

         virtual ~DeviceUnit0()
         {
            delete dev_info;
            delete dev_mgt;
            delete attr_reporting;
         }

         void device_info (HF::Core::DeviceInformation::Server *_dev_info)
         {
            SET_SERVICE (dev_info, _dev_info);
         }

         HF::Core::DeviceInformation::Server *device_info ()
         {
            if (dev_info == nullptr)
            {
               device_info (new HF::Core::DeviceInformation::Server (*this));
            }

            return dev_info;
         }

         HF::Core::DeviceInformation::Server *device_info () const
         {
            return dev_info;
         }

         void device_management (HF::Core::DeviceManagement::Client *_dev_mgt)
         {
            SET_SERVICE (dev_mgt, _dev_mgt);
         }

         HF::Core::DeviceManagement::Client *device_management ()
         {
            if (dev_mgt == nullptr)
            {
               device_management (new HF::Core::DeviceManagement::Client (*this));
            }

            return dev_mgt;
         }

         HF::Core::DeviceManagement::Client *device_management () const
         {
            return dev_mgt;
         }

         void attribute_reporting (HF::Core::AttributeReporting::Server *_attr_reporting)
         {
            SET_SERVICE (attr_reporting, _attr_reporting);
         }

         HF::Core::AttributeReporting::Server *attribute_reporting ()
         {
            if (attr_reporting == nullptr)
            {
               attribute_reporting (new HF::Core::AttributeReporting::Server (*this));
            }

            return attr_reporting;
         }

         HF::Core::AttributeReporting::Server *attribute_reporting () const
         {
            return attr_reporting;
         }

         Common::Result handle (HF::Protocol::Packet &packet, Common::ByteArray &payload, uint16_t offset)
         {
            UNUSED (packet);
            UNUSED (payload);
            UNUSED (offset);
            return Common::Result::FAIL_UNKNOWN;
         }

         HF::Attributes::List attributes (Common::Interface itf, uint8_t pack_id,
                                          const HF::Attributes::UIDS &uids) const
         {
            UNUSED (itf);
            UNUSED (pack_id);
            UNUSED (uids);
            return HF::Attributes::List ();
         }
      };

      class ConcentratorUnit0:public HF::Devices::Concentrator::IUnit0
      {
         HF::Core::DeviceInformation::Server *dev_info;
         HF::Core::DeviceManagement::IServer *dev_mgt;
         HF::Core::AttributeReporting::Server *attr_reporting;
         HF::Core::BindManagement::IServer   *bind_mgt;

         public:

         ConcentratorUnit0(HF::IDevice &device):
            HF::Devices::Concentrator::IUnit0 (device), dev_info (nullptr), dev_mgt (nullptr),
            attr_reporting (nullptr), bind_mgt (nullptr)
         {}

         virtual ~ConcentratorUnit0()
         {
            delete dev_info;
            delete dev_mgt;
            delete attr_reporting;
            delete bind_mgt;
         }

         // =============================================================================
         // API
         // =============================================================================

         void device_info (HF::Core::DeviceInformation::Server *_dev_info)
         {
            SET_SERVICE (dev_info, _dev_info);
         }

         HF::Core::DeviceInformation::Server *device_info () const
         {
            return dev_info;
         }

         HF::Core::DeviceInformation::Server *device_info ()
         {
            if (dev_info == nullptr)
            {
               device_info (new HF::Core::DeviceInformation::Server (*this));
            }

            return dev_info;
         }

         void device_management (HF::Core::DeviceManagement::IServer *_dev_mgt)
         {
            SET_SERVICE (dev_mgt, _dev_mgt);
         }

         HF::Core::DeviceManagement::IServer *device_management ()
         {
            if (dev_mgt == nullptr)
            {
               device_management (new HF::Core::DeviceManagement::DefaultServer (*this));
            }

            return dev_mgt;
         }

         HF::Core::DeviceManagement::IServer *device_management () const
         {
            return dev_mgt;
         }

         void attribute_reporting (HF::Core::AttributeReporting::Server *_attr_reporting)
         {
            SET_SERVICE (attr_reporting, _attr_reporting);
         }

         HF::Core::AttributeReporting::Server *attribute_reporting () const
         {
            return attr_reporting;
         }

         HF::Core::AttributeReporting::Server *attribute_reporting ()
         {
            if (attr_reporting == nullptr)
            {
               attribute_reporting (new HF::Core::AttributeReporting::Server (*this));
            }

            return attr_reporting;
         }

         void bind_management (HF::Core::BindManagement::IServer *_bind_mgt)
         {
            SET_SERVICE (bind_mgt, _bind_mgt);
         }

         HF::Core::BindManagement::IServer *bind_management ()
         {
            if (bind_mgt == nullptr)
            {
               bind_management (new HF::Core::BindManagement::DefaultServer (*this));
            }

            return bind_mgt;
         }

         HF::Core::BindManagement::IServer *bind_management () const
         {
            return bind_mgt;
         }

         Common::Result handle (HF::Protocol::Packet &packet, Common::ByteArray &payload, uint16_t offset)
         {
            switch (packet.message.itf.id)
            {
               case HF::Interface::DEVICE_INFORMATION:
               {
                  return device_info ()->handle (packet, payload, offset);
               }
               case HF::Interface::ATTRIBUTE_REPORTING:
               {
                  return attribute_reporting ()->handle (packet, payload, offset);
               }
               case HF::Interface::DEVICE_MANAGEMENT:
               {
                  return device_management ()->handle (packet, payload, offset);
               }
               case HF::Interface::BIND_MANAGEMENT:
               {
                  return bind_management ()->handle (packet, payload, offset);
               }
               default:
                  return Common::Result::FAIL_UNKNOWN;
            }
         }

         HF::Attributes::List attributes (Common::Interface itf, uint8_t pack_id,
                                          const HF::Attributes::UIDS &uids) const
         {
            UNUSED (itf);
            UNUSED (pack_id);
            UNUSED (uids);
            return HF::Attributes::List ();
         }
      };

      struct Device:public AbstractDevice < HF::Devices::Node::Abstract < DeviceUnit0 >>
      {};

      struct Concentrator:public AbstractDevice < HF::Devices::Concentrator::Abstract < ConcentratorUnit0 >>
      {};

   } // namespace Testing

} // namespace HF

#endif /* HF_TEST_HELPER_H */
