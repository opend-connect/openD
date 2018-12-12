// =============================================================================
/*!
 * @file       inc/hanfun/protocol.h
 *
 * This file contains the definitions for the HAN-FUN protocol messages.
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
#ifndef HF_PROTOCOL_H
#define HF_PROTOCOL_H

#include "hanfun/common.h"

// =============================================================================
// API
// =============================================================================

namespace HF
{
   // Forward declaration.
   namespace Transport
   {
      struct Link;
   }

   /*!
    * HAN-FUN %Protocol implementation.
    */
   namespace Protocol
   {
      /*!
       * @addtogroup protocol Protocol
       *
       * This module contains the classes that define and implement the %Protocol API.
       * @{
       */
      //! HAN-FUN Broadcast - device address.
      constexpr uint16_t BROADCAST_ADDR = 0x7FFF;

      //! HAN-FUN Broadcast - unit address.
      constexpr uint8_t BROADCAST_UNIT = 0xFF;

      //! HAN-FUN Network - Maximum application payload length.
      constexpr uint16_t MAX_PAYLOAD = 0x01FF;

      // =============================================================================
      // Classes
      // =============================================================================

      /*!
       * Network Message.
       */
      struct Message
      {
         /*!
          * Message types.
          */
         typedef enum _Type
         {
            COMMAND_REQ                   = 0x01, //!< Command request
            COMMAND_RESP_REQ              = 0x02, //!< Command request with response required.
            COMMAND_RES                   = 0x03, //!< Command response.

            GET_ATTR_REQ                  = 0x04, //!< Get attributes request.
            GET_ATTR_RES                  = 0x05, //!< Get attributes response.

            SET_ATTR_REQ                  = 0x06, //!< Set attributes request.
            SET_ATTR_RESP_REQ             = 0x07, //!< Set attributes request with response required.
            SET_ATTR_RES                  = 0x08, //!< Set attributes response.

            GET_ATTR_PACK_REQ             = 0x09, //!< Get pack attributes request.
            GET_ATTR_PACK_RES             = 0x0A, //!< Get pack attributes response.

            SET_ATTR_PACK_REQ             = 0x0B, //!< Set pack attributes request.
            SET_ATTR_PACK_RESP_REQ        = 0x0C, //!< Set pack attributes request with response required.
            SET_ATTR_PACK_RES             = 0x0D, //!< Set pack attributes response.

            ATOMIC_SET_ATTR_PACK_REQ      = 0x0E, //!< Atomic set pack attributes request.
            ATOMIC_SET_ATTR_PACK_RESP_REQ = 0x0F, //!< Atomic set pack attributes request with response required.
            ATOMIC_SET_ATTR_PACK_RES      = 0x10, //!< Atomic set pack attributes response.
         } Type;

         /*!
          * Interface Address.
          */
         struct Interface:public Common::Interface
         {
            //! Minimum pack/unpack required data size.
            static const uint16_t min_size = Common::Interface::min_size // Interface UID.
                                             + sizeof(uint8_t);          // Interface Member.

            uint8_t member;            //!< Interface destination member.

            /*!
             * Constructor.
             *
             * @param [in] uid      interface %UID.
             * @param [in] role     interface role.
             * @param [in] member   interface member.
             */
            Interface(uint16_t uid = 0, uint8_t role = 0, uint8_t member = 0):Common::Interface(uid, role), member (member)
            {}

            //! @copydoc HF::Common::Serializable::size
            uint16_t size () const;

            //! @copydoc HF::Common::Serializable::pack
            uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

            //! @copydoc HF::Common::Serializable::unpack
            uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0);
         };

         // =============================================================================
         // API
         // =============================================================================

         uint8_t   reference;          //!< Application reference.
         Type      type;               //!< Message type. @see Message::Type

         Interface itf;                //!< Interface Address.

         /*!
          * Message payload.
          */
         Common::ByteArray payload;

         //! The payload length value read when unpacking the message.
         uint16_t length;

         /*!
          * Constructor
          *
          * @param [in] size     message payload size.
          * @param [in] _type    message type.
          */
         Message(uint16_t size = 0, Type _type = COMMAND_REQ):
            reference (0), type (_type), payload (Common::ByteArray (size)), length (0)
         {
            assert (size <= MAX_PAYLOAD);
         }

         /*!
          * Create a new message that is a response to the given message in @c parent.
          *
          * @note If @c parent is already a response then the new message has the same type.
          *
          * @param [in] parent   reference to the message to create a response for.
          * @param [in] size     size of the payload buffer.
          */
         Message(const Message &parent, uint16_t size);

         //! Minimum pack/unpack required data size.
         static constexpr uint16_t min_size = sizeof(uint8_t)       // Application Reference.
                                              + sizeof(uint8_t)     // Message Type.
                                              + Interface::min_size // Interface UID + Member.
                                              + sizeof(uint16_t);   // Payload Length Value.

         //! @copydoc HF::Common::Serializable::size
         uint16_t size () const;

         //! @copydoc HF::Common::Serializable::pack
         uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

         /*!
          * @copydoc HF::Common::Serializable::unpack
          *
          * @warning This __DOES NOT__ copy the payload portion from the given @c array into
          * the @c payload field in this object.
          */
         uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0);
      };

      /*!
       * Network Address.
       */
      struct Address
      {
         uint16_t mod    : 1;    //!< Address modifier.
         uint16_t device : 15;   //!< Device Address.

         uint8_t  unit;          //!< Source Unit.

         /*!
          * HAN-FUN Network Destination Address Types.
          */
         typedef enum _Type
         {
            DEVICE = 0,   //!< Destination address is for single device.
            GROUP  = 1,   //!< Destination address is for a group of devices.
         } Type;

         /*!
          * Create a new message address.
          *
          * @param [in] _dev    device address. Default @c HF_BROADCAST_ADDR.
          * @param [in] _unit   unit address. Default @c HF_BROADCAST_UNIT.
          * @param [in] _mod    address modifier. Default @c DEVICE_ADDR.
          */
         Address(uint16_t _dev = BROADCAST_ADDR, uint8_t _unit = BROADCAST_UNIT,
                 Type _mod = DEVICE)
            :mod (_mod), device (_dev), unit (_unit)
         {}

         //! Minimum pack/unpack required data size.
         static constexpr uint16_t min_size = sizeof(uint16_t)    // Device Address + Flag.
                                              + sizeof(uint8_t);  // Unit Address.

         //! @copydoc HF::Common::Serializable::size
         uint16_t size () const;

         //! @copydoc HF::Common::Serializable::pack
         uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

         //! @copydoc HF::Common::Serializable::unpack
         uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0);

         /*!
          * Checks if this address if for the Protocol::BROADCAST_ADDR and
          * Protocol::BROADCAST_UNIT.
          *
          * @retval true   if it is the network's broadcast address,
          * @retval false  otherwise.
          */
         bool is_broadcast ()
         {
            return device == BROADCAST_ADDR && unit == BROADCAST_UNIT;
         }

         /*!
          * Checks if the given device @c address is equal to the device address
          * present in this Protocol::Address object.
          *
          * @param [in] address  network address to match.
          *
          * @retval true   if it is the network's address are equal,
          * @retval false  otherwise.
          */
         bool is_local (uint16_t address)
         {
            return this->device == address;
         }
      };

      /*!
       * HAN-FUN Protocol Packet.
       */
      struct Packet
      {
         Address source;           //!< Source Address.
         Address destination;      //!< Destination Address.

         /*!
          * Packet message payload;
          */
         Message message;

         //! Link where this packet originated from.
         Transport::Link *link;

         Packet():link (nullptr) {}

         /*!
          * Constructor.
          *
          * @param [in] message  message this packet holds.
          */
         Packet(Message &message):message (message), link (nullptr) {}

         /*!
          * Constructor.
          *
          * @param [in] dst_addr    destination device address.
          * @param [in] message     message to be sent.
          * @param [in] unit        destination unit for this packet.
          */
         Packet(Address &dst_addr, Message &message, uint8_t unit = BROADCAST_UNIT):
            destination (dst_addr), message (message), link (nullptr)
         {
            source.mod    = Address::DEVICE;
            source.device = BROADCAST_ADDR;
            source.unit   = unit;
         }

         /*!
          * Constructor.
          *
          * @param [in] src_addr    source device address for packet.
          * @param [in] dst_addr    destination device address for packet.
          * @param [in] message     message payload.
          */
         Packet(Address &src_addr, Address &dst_addr, Message &message):
            source (src_addr), destination (dst_addr), message (message), link (nullptr)
         {}

         //! Minimum pack/unpack required header data size.
         static constexpr uint16_t header_min_size = Address::min_size   // Source Address.
                                                     + Address::min_size // Destination Address.
                                                     + sizeof(uint16_t); // Transport Layer header.

         //! Minimum pack/unpack required data size.
         static constexpr uint16_t min_size = header_min_size        // Network header size.
                                              + Message::min_size;   // Message size.

         //! @copydoc HF::Common::Serializable::size
         uint16_t size () const;

         //! @copydoc HF::Common::Serializable::pack
         uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

         //! @copydoc HF::Common::Serializable::unpack
         uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0);
      };

      /*!
       * Parent class for the response messages.
       */
      struct Response
      {
         // =============================================================================
         // API
         // =============================================================================

         //! Minimum number of bytes required by this message.
         constexpr static uint16_t min_size = sizeof(uint8_t);

         Common::Result            code;

         Response(Common::Result code = Common::Result::OK):code (code) {}

         //! @copydoc HF::Common::Serializable::size
         uint16_t size () const;

         //! @copydoc HF::Common::Serializable::pack
         uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

         //! @copydoc HF::Common::Serializable::unpack
         uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0);
      };

      /*! @} */

      // =============================================================================
      // Filter classes
      // =============================================================================

      /*!
       * This namespace contains the different packet filters.
       *
       * Filters are used in processing the incoming packets from the network in order
       * to provide the required functionality of the HAN-FUN protocol.
       */
      namespace Filters
      {
         /*!
          * @addtogroup tsp_filters Filters
          * @ingroup protocol
          *
          * This module contains the filters used in the %Protocol API implementation.
          * @{
          */

         /*!
          * This class provides support for generating a response when a response is
          * required from an incoming message received, but no response was generated.
          */
         class ResponseRequired
         {
            protected:

            //! Filter database entry.
            struct Entry
            {
               uint16_t           address; //!< Source device address.
               Message::Type      type;    //!< Response type.
               Message::Interface itf;     //!< Interface the message relates to.

               Entry(uint16_t _address, Message::Type _type, Message::Interface _itf):
                  address (_address), type (_type), itf (_itf)
               {}

               Entry(const Packet &packet):address (packet.destination.device),
                  type (packet.message.type), itf (packet.message.itf)
               {}
            };

            //! Filter database.
            std::list <Entry> db;

            public:

            /*!
             * Checks if the given @c packet, is a retransmission according to
             * the filters database data.
             *
             * The given @c packet and @c payload are used to update the filters database.
             *
             * @param [in] packet     reference to the incoming packet.
             *
             * @retval  true     the packet is a retransmission.
             * @retval  false    the packet is a not retransmission.
             */
            bool operator ()(const HF::Protocol::Packet &packet);

            /*!
             * Number of entries in the filter's database.
             *
             * @return  the number of entries in the filter's database.
             */
            uint16_t size () const
            {
               return db.size ();
            }
         };

         /*! @} */

      }  // namespace Filters

      /*!
       * @addtogroup protocol
       * @{
       */
      // =============================================================================
      // Operators
      // =============================================================================

      inline bool operator ==(Address const &lhs, Address const &rhs)
      {
         return (lhs.device == rhs.device) && (lhs.unit == rhs.unit) && (lhs.mod == rhs.mod);
      }

      inline bool operator !=(Address const &lhs, Address const &rhs)
      {
         return !(lhs == rhs);
      }

      inline bool operator <(Address const &lhs, Address const &rhs)
      {
         return (lhs.device < rhs.device) ||
                (lhs.device == rhs.device &&
                 (lhs.mod < rhs.mod || (lhs.mod == rhs.mod && lhs.unit < rhs.unit)));
      }

      // =============================================================================
      // Helper Functions
      // =============================================================================

      /*!
       * Check if message type is a request.
       *
       * If @c response is @c false then return true for all requests, otherwise
       * only for those that require a response.
       *
       * @param [in] type        message type to check if it is a request.
       * @param [in] response    false check for all request types, otherwise
       *                         only those that require a response.
       *
       * @retval true   if the message is a request.
       * @retval false  otherwise.
       */
      bool request (Message::Type type, bool response = false);

      /*!
       * Check if message is a response.
       *
       * @param [in] type  message type to check if it is a response.
       *
       * @retval true   if the message is a response.
       * @retval false  otherwise.
       */
      bool response (Message::Type type);

      /*!
       * Check if the given message types are the request and response for
       * each other, for example, the Message::Type::COMMAND_RES matches both
       * the Message::Type::COMMAND_REQ and Message::Type::COMMAND_RESP_REQ.
       *
       * @param [in] lhs   message type to match.
       * @param [in] rhs   message type to match.
       *
       * @retval true   if the message types match.
       * @retval false  otherwise.
       */
      bool matches (Message::Type lhs, Message::Type rhs);

      /*! @} */

   }  // namespace Protocol

}  // namespace HF

/*!
 * @addtogroup protocol
 * @{
 */

// =============================================================================
// Stream Helpers
// =============================================================================

/*!
 * Convert the given message @c type into a string and write it to the given @c stream.
 *
 * @param [in] stream   out stream to write the string to.
 * @param [in] type     message type value to convert to a string.
 *
 * @return   <tt>stream</tt>
 */
std::ostream &operator <<(std::ostream &stream, const HF::Protocol::Message::Type type);

/*!
 * Convert the given @c message into a string and write it to the given @c stream.
 *
 * @param [in] stream    out stream to write the string to.
 * @param [in] message   message value to convert to a string.
 *
 * @return   <tt>stream</tt>
 */
std::ostream &operator <<(std::ostream &stream, const HF::Protocol::Message &message);

/*!
 * Convert the given @c address into a string and write it to the given @c stream.
 *
 * @param [in] stream   out stream to write the string to.
 * @param [in] address  HAN-FUN address to convert to a string.
 *
 * @return   <tt>stream</tt>
 */
std::ostream &operator <<(std::ostream &stream, const HF::Protocol::Address &address);

/*!
 * Convert the given @c packet into a string and write it to the given @c stream.
 *
 * @param [in] stream   out stream to write the string to.
 * @param [in] packet   HAN-FUN packet to convert to a string.
 *
 * @return   <tt>stream</tt>
 */
std::ostream &operator <<(std::ostream &stream, const HF::Protocol::Packet &packet);

/*! @} */

#endif /* HF_PROTOCOL_H */
