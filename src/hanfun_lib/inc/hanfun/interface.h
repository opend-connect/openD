// =============================================================================
/*!
 * @file       inc/hanfun/interface.h
 *
 * This file contains the definitions common to all interfaces.
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
#ifndef HF_INTERFACE_H
#define HF_INTERFACE_H

#include "hanfun/common.h"
#include "hanfun/attributes.h"

#include "hanfun/protocol.h"

namespace HF
{
   /*!
    * @defgroup interfaces Interfaces
    *
    * This module contains the classes that define and implement the %Interfaces API.
    */

   /*!
    * @addtogroup common_itf Common
    * @ingroup interfaces
    *
    * This module contains the common classes for the %Interfaces API implementation.
    * @{
    */

   /*!
    * Common interface for all Interfaces.
    */
   struct Interface
   {
      /*!
       * Interface roles.
       */
      typedef enum _Role
      {
         CLIENT_ROLE = 0,   //!< Client Role.
         SERVER_ROLE = 1,   //!< Server Role.
      } Role;

      /*!
       * Interfaces Unique Identifiers (UID).
       */
      typedef enum _UID
      {
         /* Core Services */
         DEVICE_MANAGEMENT   = 0x0001,   //!< %Device Management interface %UID.
         BIND_MANAGEMENT     = 0x0002,   //!< Bind Management interface %UID.
         GROUP_MANGEMENT     = 0x0003,   //!< Group Management interface %UID. __Not implemented__
         IDENTIFY            = 0x0004,   //!< Identify interface %UID. __Not implemented__
         DEVICE_INFORMATION  = 0x0005,   //!< %Device information Interface UID. __Not implemented__
         ATTRIBUTE_REPORTING = 0x0006,   //!< %Attribute Reporting interface UID. __Not implemented__
         TAMPER_ALERT        = 0x0101,   //!< Tamper %Alert interface UID. __Not implemented__
         TIME                = 0x0102,   //!< %Time interface UID. __Not implemented__
         POWER               = 0x0110,   //!< Power interface UID. __Not implemented__
         KEEP_ALIVE          = 0x0115,   //!< Keep Alive interface UID. __Not implemented__

         /* Functional Interfaces. */
         ALERT              = 0x0100,    //!< Alert Interface UID
         ON_OFF             = 0x0200,    //!< ON-OFF Interface UID
         LEVEL_CONTROL      = 0x0201,    //!< Level Control Interface UID
         SIMPLE_POWER_METER = 0x0300,    //!< Simple Power Meter Interface UID
         SIMPLE_TEMPERATURE = 0x0301,    //!< Simple Temperature Interface UID
         SIMPLE_HUMIDITY    = 0x0302,    //!< Simple Humidity Interface UID

         /* Reserved */
         RESERVED = 0x7F00,              //!< Proprietary interfaces.
         MAX_UID  = 0x7FFE,              //!< Max interface UID value.
         ANY_UID  = 0x7FFF,              //!< Any interface UID value.
      } UID;

      struct Any:public Common::Interface
      {
         Any() : Common::Interface(ANY_UID)
         {}
      };

      //! Maximum value for command IDs in interfaces.
      static constexpr uint8_t MAX_CMD_ID = 0xFF;

      virtual ~Interface() {}

      // =============================================================================
      // API
      // =============================================================================

      /*!
       * This method returns the interface UID.
       *
       * Subclasses MUST override this method to provide a valid value
       * for the interface being implemented.
       *
       * This method returns a @c uint16_t and not a Interface::UID,
       * to provide support for proprietary interfaces.
       *
       * @return  the UID for the interface.
       */
      virtual uint16_t uid () const = 0;

      /*!
       * Return the Interface::Role this interface implements.
       *
       * @return  the Interface::Role implemented by the interface.
       */
      virtual Interface::Role role () const = 0;

      /*!
       * Handle incoming messages from the network.
       *
       * @param [in]    packet   the packet receive from the network.
       *
       * @param [in]    payload  the byte array containing the data received from the
       *                         network.
       *
       * @param [in]    offset   the offset the payload start at in the byte array.
       *
       * @return        the result of the message processing.
       */
      virtual Common::Result handle (Protocol::Packet &packet, Common::ByteArray &payload,
                                     uint16_t offset) = 0;

      /*!
       * Handle periodic processing.
       *
       * @param [in] time    current system clock value in seconds.
       */
      virtual void periodic (uint32_t time) = 0;

      /*!
       * Return a pointer to the interface attribute with the given @c uid.
       *
       * @param [in] uid   identifier of the attribute in the interface.
       *
       * @return     a pointer to the attribute if it exists,
       *             @c nullptr otherwise.
       */
      virtual HF::Attributes::IAttribute *attribute (uint8_t uid) = 0;

      /*!
       * Return a vector containing the attribute UIDs, for the given pack ID.
       *
       * @param [in] pack_id  the Attribute pack ID to get the attributes UIDs for.
       *
       * @return  vector containing the attributes UIDs.
       */
      virtual HF::Attributes::UIDS attributes (
         uint8_t pack_id = HF::Attributes::Pack::MANDATORY) const = 0;
   };

   /*! @} */

   /*!
    * This is the top-level namespace for the implemented %Interfaces.
    */
   namespace Interfaces
   {
      /*!
       * @addtogroup common_itf
       * @{
       */

      /*!
       * Top-level parent class for all implemented interfaces.
       *
       * This class provides the implementation of the common functionality present in
       * all interfaces implementations.
       */
      struct AbstractInterface:virtual public Interface
      {
         virtual ~AbstractInterface() {}

         Common::Result handle (Protocol::Packet &packet, Common::ByteArray &payload,
                                uint16_t offset);

         void periodic (uint32_t time)
         {
            UNUSED (time);
         }

         HF::Attributes::IAttribute *attribute (uint8_t uid)
         {
            UNUSED (uid);
            return nullptr;
         }

         virtual HF::Attributes::UIDS attributes (
            uint8_t pack_id = HF::Attributes::Pack::MANDATORY) const
         {
            UNUSED (pack_id);
            return HF::Attributes::UIDS ();
         }

         bool operator ==(AbstractInterface &other)
         {
            return uid () == other.uid ();
         }

         bool operator !=(AbstractInterface &other)
         {
            return !(*this == other);
         }

         protected:

         /*!
          * Send message @c msg to the network address given by @c addr.
          *
          * @param [in] addr        HF network address.
          * @param [in] message     pointer to the message to be sent to the network.
          */
         virtual void send (const Protocol::Address &addr, Protocol::Message &message) = 0;

         /*!
          * Notify that an attribute value as changed.
          *
          * @param [in] old_value   attribute's old value.
          * @param [in] new_value   attribute's new value.
          */
         virtual void notify (const HF::Attributes::IAttribute &old_value,
                              const HF::Attributes::IAttribute &new_value) const
         {
            UNUSED (old_value);
            UNUSED (new_value);
         }

         /*!
          * Check if message has correct attributes to be processed by the interface.
          *
          * The attributes checked are :
          * - Interface UID;
          * - Interface Role;
          *
          * @see HF::Interface::handle
          *
          * @param [in] message  incoming message.
          * @param [in] payload  message payload.
          * @param [in] offset   offset in payload array to start reading.
          *
          * @retval Common::Result::OK       if message is for this interface;
          * @retval Common::Result::FAIL_ARG otherwise.
          */
         Common::Result check (Protocol::Message &message, Common::ByteArray &payload,
                               uint16_t offset);

         /*!
          * Check if @c payload data size if sufficient for processing the @c message.
          *
          * @see HF::Interface::handle
          *
          * @param [in] message  incoming message.
          * @param [in] payload  message payload.
          * @param [in] offset   offset in payload array to start reading.
          *
          * @retval Common::Result::OK       if message is for this interface;
          * @retval Common::Result::FAIL_ARG otherwise.
          */
         Common::Result check_payload_size (Protocol::Message &message, Common::ByteArray &payload,
                                            uint16_t offset);

         /*!
          * Return the minimal payload size that should be present for the given
          * message.
          *
          * @param [in] message message that was received.
          *
          * @return  the minimum size in bytes that the packet payload should hold.
          */
         virtual uint16_t payload_size (Protocol::Message &message) const;

         /*!
          * Return the minimal payload size that a message should hold when
          * addressed at the given interface.
          *
          * @param [in] itf   the interface being address.
          *
          * @return  the minimum number of bytes for the message for the interface.
          */
         virtual uint16_t payload_size (Protocol::Message::Interface &itf) const
         {
            UNUSED (itf);
            return 0;
         }

         /*!
          * Helper function template to retrieve minimum size required for
          * serializing/deserializing the class given.
          *
          * @tparam _Message  message class to get the minimum size to of.
          *
          * @return  the minimum size required to serializing/deserializing given class.
          */
         template<typename _Message>
         uint16_t payload_size_helper () const
         {
            _Message message;
            return message.size ();
         }

         /*!
          * @copydoc HF::Interface::handle
          *
          * Handle command request/response messages, i.e. :
          *  - Protocol::Message:Type::COMMAND_REQ;
          *  - Protocol::Message:Type::COMMAND_RESP_REQ;
          *  - Protocol::Message:Type::COMMAND_RES;
          */
         virtual Common::Result handle_command (Protocol::Packet &packet,
                                                Common::ByteArray &payload, uint16_t offset);

         /*!
          * @copydoc HF::Interface::handle
          *
          * Handle attributes request/response messages, i.e. :
          *  - Protocol::Message:Type::GET_ATTR_REQ;
          *  - Protocol::Message:Type::SET_ATTR_REQ;
          *  - Protocol::Message:Type::SET_ATTR_RESP_REQ;
          *  - Protocol::Message:Type::GET_ATTR_PACK_REQ;
          *  - Protocol::Message:Type::SET_ATTR_PACK_REQ;
          *  - Protocol::Message:Type::SET_ATTR_PACK_RESP_REQ;
          */
         virtual Common::Result handle_attribute (Protocol::Packet &packet,
                                                  Common::ByteArray &payload, uint16_t offset);

         /*!
          * Check if the given UID matches the interface UID.
          *
          * @param [in] uid   the UID value to check against the interface UID.
          *
          * @retval  true     the UIDs match,
          * @retval  false    otherwise.
          */
         virtual bool check_uid (uint16_t uid) const = 0;
      };


      /*!
       * Helper class template for parent class implementation of the interfaces.
       *
       * @tparam _uid   interface UID to be used by the interface.
       */
      template<Interface::UID _uid>
      struct Base:public AbstractInterface
      {
         //! @copydoc HF::Interface::uid
         uint16_t uid () const
         {
            return _uid;
         }

         protected:

         /*!
          * Check if the given @c uid value matches the interface's @c %UID value.
          *
          * @param [in] uid   %UID value to check against.
          *
          * @retval  true     if the values match.
          * @retval  false    otherwise.
          */
         bool check_uid (uint16_t uid) const
         {
            return Base::uid () == uid;
         }
      };

      /*!
       * Helper class template for implementing a given interface role.
       *
       * @tparam Itf    parent interface class.
       * @tparam _role  interface role implemented.
       */
      template<typename Itf, Interface::Role _role>
      struct InterfaceRole:public Itf
      {
         //! @copydoc Interface::role
         Interface::Role role () const
         {
            return _role;
         }
      };

      /*!
       * Helper template class to allow interfaces implementation to be
       * added as fields to other classes.
       *
       * @tparam  _Interface  base parent interface class.
       * @tparam  _Proxy      class providing the required methods for proper interface
       *                      usage.
       */
      template<typename _Interface, typename _Proxy>
      struct Proxy:public _Interface
      {
         static_assert (std::is_base_of <Interfaces::AbstractInterface, _Interface>::value,
                        "Interface MUST be of type HF::Interfaces::AbstractInterface !");

         typedef _Interface base;

         Proxy(_Proxy &_proxy):proxy (_proxy)
         {}

         //! @copydoc HF::Interfaces::AbstractInterface::send
         void send (const Protocol::Address &addr, Protocol::Message &message)
         {
            proxy.send (addr, message);
         }

         //! @copydoc HF::Interfaces::AbstractInterface::notify
         void notify (const HF::Attributes::IAttribute &old_value,
                      const HF::Attributes::IAttribute &new_value) const
         {
            proxy.notify (old_value, new_value);
         }

         protected:

         //! Referent to the class providing the required functionality.
         _Proxy &proxy;
      };

      /*! @} */

   }  // namespace Interfaces

   /*! @} */

}  // namespace HF

/*!
 * @addtogroup common_itf
 * @{
 */

// =============================================================================
// Stream Helpers
// =============================================================================

/*!
 * Convert the given @c role into a string and write it to the given @c stream.
 *
 * @param [in] stream   out stream to write the string to.
 * @param [in] role     role value to convert to a string.
 *
 * @return   <tt>stream</tt>
 */
std::ostream &operator <<(std::ostream &stream, const HF::Interface::Role role);

/*!
 * Convert the given @c uid into a string and write it to the given @c stream.
 *
 * @param [in] stream   out stream to write the string to.
 * @param [in] uid      uid value to convert to a string.
 *
 * @return   <tt>stream</tt>
 */
std::ostream &operator <<(std::ostream &stream, const HF::Interface::UID uid);

/*! @} */

#endif /* HF_INTERFACE_H */
