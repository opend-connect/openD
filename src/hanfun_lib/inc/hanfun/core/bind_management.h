// =============================================================================
/*!
 * @file       inc/hanfun/core/bind_management.h
 *
 * This file contains the definitions for the core Bind Management Interface
 * of the HAN-FUN protocol.
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
#ifndef HF_BIND_MANAGEMENT_H
#define HF_BIND_MANAGEMENT_H

#include "hanfun/common.h"
#include "hanfun/protocol.h"

#include "hanfun/core.h"

#include "hanfun/interface.h"

#include "hanfun/core/session_management.h"

// =============================================================================
// API
// =============================================================================

namespace HF
{
   // Forward declaration.

   namespace Devices
   {
      namespace Concentrator
      {
         struct IUnit0;

      }  // namespace Concentrator

   }  // namespace Devices

   // =============================================================================
   // API
   // =============================================================================

   namespace Core
   {
      // Forward declaration.
      namespace BindManagement
      {
         struct IServer;
      }  // namespace BindManagement

      /*!
       * @ingroup bind_mgt
       *
       * Create an attribute object that can hold the attribute with the given @c uid.
       *
       * If @c server is not equal to @c nullptr then initialize it with the current
       * value.
       *
       * @param [in] server   pointer to the object to read the current value from.
       * @param [in] uid      attribute's UID to create the attribute object for.
       *
       * @return  pointer to an attribute object or @c nullptr if the attribute UID does not
       *          exist.
       */
      HF::Attributes::IAttribute *create_attribute (HF::Core::BindManagement::IServer *server,
                                                    uint8_t uid);

      /*!
       * This namespace contains the classes that implement the Bind Management service.
       */
      namespace BindManagement
      {
         /*!
          * @addtogroup bind_mgt Bind Management
          * @ingroup core
          *
          * This module contains the classes that implement the Bind Management service.
          * @{
          */

         //! Commands.
         typedef enum _CMD
         {
            ADD_BIND_CMD      = 0x01, //!< Add bind entry command.
            REMOVE_BIND_CMD   = 0x02, //!< Remove bind entry command.
            START_SESSION_CMD = 0x03, //!< Start Session Read Registration Info.
            END_SESSION_CMD   = 0x04, //!< End Session Read Registration Info.
            GET_ENTRIES_CMD   = 0x05, //!< Get Entries Command.
            __LAST_CMD__      = GET_ENTRIES_CMD
         } CMD;

         //! Attributes.
         typedef enum _Attributes
         {
            NUMBER_OF_ENTRIES_ATTR = 0x01, //!< Number of entries attribute.
            __LAST_ATTR__          = NUMBER_OF_ENTRIES_ATTR
         } Attributes;

         /*!
          * This represents a bind entry data structure.
          */
         struct Entry
         {
            Protocol::Address source;           //!< Source Address.

            Protocol::Address destination;      //!< Destination Address.

            Common::Interface itf;              //!< Destination Interface.

            Entry()
            {}

            /*!
             * Constructor.
             *
             * @param [in] _source  device source for the bind entry.
             * @param [in] _itf     interface UID + role for the bind entry.
             */
            Entry(Protocol::Address _source, Common::Interface _itf):
               source (_source), itf (_itf)
            {}

            /*!
             * Constructor.
             *
             * @param [in] _source        device source for the bind entry.
             * @param [in] _itf           interface UID + role for the bind entry.
             * @param [in] _destination   destination device for he bing entry.
             */
            Entry(Protocol::Address _source, Common::Interface _itf,
                  Protocol::Address _destination):
               source (_source), destination (_destination), itf (_itf)
            {}

            //! Minimum pack/unpack required data size.
            static constexpr uint16_t min_size = Protocol::Address::min_size     // Source Address
                                                 + Protocol::Address::min_size   // Destination Address
                                                 + Common::Interface::min_size;  // Interface UID.

            //! @copydoc HF::Common::Serializable::size
            uint16_t size () const;

            //! @copydoc HF::Common::Serializable::pack
            uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

            //! @copydoc HF::Common::Serializable::unpack
            uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0);
         };

         typedef HF::Common::Pointer <const Entry> EntryPtr;

         /*!
          * Add/Remove Bind message.
          */
         struct Message:public Entry
         {};

         // =============================================================================
         // API
         // =============================================================================

         /*!
          * Bind Management persistent storage API.
          */
         struct IEntries:public Common::IEntries <Entry>
         {
            // =============================================================================
            // API
            // =============================================================================

            using Common::IEntries <Entry>::destroy;

            /*!
             * Destroy the entries in the persistent storage, that refer to the
             * the given address.
             *
             * This method destroys the entries that refer to the address both in
             * the source and in the destination address.
             *
             * @param [in] address   HF address to remove entries for.
             * @param [in] type      HF address type.
             *
             * @retval  Common::Result::OK and a copy of the destroyed entry if the entry was destroyed.
             * @retval  Common::Result::FAIL_ARG and @c nullptr otherwise.
             */
            virtual Common::Result destroy (uint16_t address, Protocol::Address::Type type =
                                               Protocol::Address::DEVICE) = 0;

            // =============================================================================
            // Query API
            // =============================================================================

            /*!
             * Return the Bind entry for the given parameters.
             *
             * @param [in] source         source address of the device.
             * @param [in] destination    destination address of the device.
             * @param [in] itf            interface to bind.
             *
             * @retval a pointer to bind entry for the given parameters,
             * @retval nullptr if bind entry does not exist.
             */
            virtual EntryPtr find (const Protocol::Address &source, const Common::Interface &itf,
                                   const Protocol::Address &destination) const = 0;

            /*!
             * Check if entries for the device with given @c source address and for the given
             * interface @c ifc exist.
             *
             * @param [in] source   device address to search for.
             * @param [in] itf      interface id to search for.
             *
             * @retval  true if entries exist,
             * @retval  false otherwise.
             */
            virtual bool any_of (Protocol::Address const &source,
                                 Common::Interface const &itf) const = 0;

            /*!
             * Call the given function for all the entries with given @c source address and
             * for the given interface @c ifc.
             *
             * @param [in] source   device address to search for.
             * @param [in] itf      interface id to search for.
             * @param [in] func     function to call for all the entries.
             */
            virtual void for_each (Protocol::Address const &source, Common::Interface const &itf,
                                   std::function <void(const Entry &)> func) const = 0;
         };

         /*!
          * @copybrief HF::Core::create_attribute (HF::Core::BindManagement::Server *,uint8_t)
          *
          * @see HF::Core::create_attribute (HF::Core::BindManagement::Server *,uint8_t)
          *
          * @param [in] uid   attribute %UID to create the attribute object for.
          *
          * @retval  pointer to an attribute object
          * @retval  <tt>nullptr</tt> if the attribute UID does not exist.
          */
         HF::Attributes::IAttribute *create_attribute (uint8_t uid);

         /*!
          * Parent class for the Bind Management interface implementation.
          */
         class Abstract:public Service <HF::Interface::BIND_MANAGEMENT>
         {
            protected:

            /*!
             * Constructor.
             *
             * @param [in] unit  reference to the unit containing this service.
             */
            Abstract(HF::Core::Unit0 &unit):
               Service (unit)
            {}
         };

         /*!
          * Bind Management interface : Client side.
          */
         class Client:public ServiceRole <Abstract, HF::Interface::CLIENT_ROLE>,
            protected SessionManagement::Client <Entry>
         {
            typedef ServiceRole <Abstract, HF::Interface::CLIENT_ROLE> Service;

            public:

            typedef SessionManagement::Client <Entry> SessionMgr;

            /*!
             * Constructor.
             *
             * @param [in] unit  reference to the unit containing this service.
             */
            Client(HF::Core::Unit0 &unit):
               ServiceRole (unit)
            {}

            virtual ~Client() {}

            /*!
             * Reference to the session management API.
             *
             * @return  reference to the object implementing the session management API for
             *          this device management client.
             */
            SessionMgr &session ()
            {
               return *this;
            }

            // ======================================================================
            // Commands
            // ======================================================================
            //! @name Commands
            //! @{

            /*!
             * Send a ADD_BIND command.
             *
             * @param [in] source         the HAN-FUN source device.
             * @param [in] destination    the HAN-FUN destination device.
             * @param [in] itf            the interface to bind between source and destination.
             */
            void add (const Protocol::Address &source, const Protocol::Address &destination,
                      const Common::Interface &itf);

            /*!
             * Send a REMOVE_BIND command.
             *
             * @param [in] source         the HAN-FUN source device.
             * @param [in] destination    the HAN-FUN destination device.
             * @param [in] itf            the interface to unbind between source and destination.
             */
            void remove (const Protocol::Address &source, const Protocol::Address &destination,
                         const Common::Interface &itf);

            // ======================================================================
            // Session Management
            // ======================================================================

            /*!
             * Start read entries session.
             */
            void start_session () const
            {
               SessionMgr::request <SERVER_ROLE, Interface::DEVICE_MANAGEMENT,
                                    START_SESSION_CMD>();
            }

            /*!
             * Read entries.
             *
             * @param [in] offset   start read at offset.
             * @param [in] count    number of entries to read.
             */
            void get_entries (uint16_t offset, uint8_t count = 0) const
            {
               SessionMgr::get_entries <SERVER_ROLE, Interface::DEVICE_MANAGEMENT,
                                        GET_ENTRIES_CMD>(offset, count);
            }

            /*!
             * End read entries session.
             */
            void end_session () const
            {
               SessionMgr::request <SERVER_ROLE, Interface::DEVICE_MANAGEMENT,
                                    END_SESSION_CMD>();
            }

            //! @}
            // ======================================================================

            // ======================================================================
            // Events
            // ======================================================================
            //! @name Events
            //! @{

            /*!
             * This method is called when the response to a command is received.
             *
             * @param [in] cmd      the command that response refers to.
             * @param [in] response the result of the command.
             */
            virtual void response (const CMD cmd, const Protocol::Response &response);

            //! @}
            // ======================================================================

            using Service::send;

            void send (const Protocol::Address &addr, Protocol::Message &message)
            {
               Service::send (addr, message);
            }

            protected:

            using ServiceRole::payload_size;

            uint16_t payload_size (Protocol::Message::Interface &itf) const;

            Common::Result handle_command (Protocol::Packet &packet, Common::ByteArray &payload,
                                           uint16_t offset);
         };

         /*!
          * Bind Management interface : Server side API.
          */
         struct IServer:public ServiceRole <Abstract, HF::Interface::SERVER_ROLE>
         {
            virtual ~IServer() {}

            // =============================================================================
            // API
            // =============================================================================

            /*!
             * Return a reference to the unit that this service belongs to.
             *
             * This is the same reference as AbstractService::unit, but static casted
             * to allow access to the the other interfaces.
             *
             * @return  a reference to the unit that holds this interface.
             */
            HF::Devices::Concentrator::IUnit0 &unit0 () const;

            // ======================================================================
            // Commands
            // ======================================================================
            //! @name Commands
            //! @{

            /*!
             * Create a new bind entry in the database.
             *
             * @param [in] source         the HAN-FUN source device.
             * @param [in] destination    the HAN-FUN destination device.
             * @param [in] itf            the interface to bind between source and destination.
             *
             * @return  Common::Result::OK if the bind was created or Result::FAIL_* otherwise.
             */
            virtual Common::Result add (const Protocol::Address &source,
                                        const Protocol::Address &destination,
                                        const Common::Interface &itf) = 0;

            /*!
             * Remove a bind entry from the database.
             *
             * @param [in] source         the HAN-FUN source device.
             * @param [in] destination    the HAN-FUN destination device.
             * @param [in] itf            the interface to bind between source and destination.
             *
             * @return  Common::Result::OK if the bind was removed or Result::FAIL_* otherwise.
             */
            virtual Common::Result remove (const Protocol::Address &source,
                                           const Protocol::Address &destination,
                                           const Common::Interface &itf) = 0;

            //! @}
            // ======================================================================

            /*!
             * Reference to the persistent storage implementation.
             *
             * @return  reference to the object responsible by the persistent storage of the
             *          bind entries.
             */
            virtual IEntries &entries () const = 0;

            /*!
             * Reference to the session management API.
             *
             * @return  reference to the object implementing the session management API for
             *          this bind management server.
             */
            virtual SessionManagement::IServer &sessions () = 0;

            protected:

            /*!
             * Constructor.
             *
             * @param [in] unit  reference to the unit containing this service.
             */
            IServer(Unit0 &unit):
               ServiceRole <Abstract, HF::Interface::SERVER_ROLE>(unit)
            {}
         };

         /*!
          * Parent class for bind management - server role.
          */
         struct AbstractServer:public IServer
         {
            virtual ~AbstractServer() {}

            // =============================================================================
            // API.
            // =============================================================================

            Common::Result add (const Protocol::Address &source,
                                const Protocol::Address &destination,
                                const Common::Interface &itf);

            Common::Result remove (const Protocol::Address &source,
                                   const Protocol::Address &destination,
                                   const Common::Interface &itf);

            // =============================================================================
            // Interface Attribute API.
            // =============================================================================

            HF::Attributes::IAttribute *attribute (uint8_t uid)
            {
               return Core::create_attribute (this, uid);
            }

            HF::Attributes::UIDS attributes (uint8_t pack_id = HF::Attributes::Pack::MANDATORY) const
            {
               UNUSED (pack_id);
               return HF::Attributes::UIDS {NUMBER_OF_ENTRIES_ATTR};
            }

            protected:

            /*!
             * Constructor.
             *
             * @param [in] unit  reference to the unit containing this service.
             */
            AbstractServer(Unit0 &unit):IServer (unit)
            {}

            Common::Result handle_command (Protocol::Packet &packet, Common::ByteArray &payload,
                                           uint16_t offset);
         };

         /*!
          * Default implementation of the bind entries container.
          */
         struct Entries:public IEntries
         {
            typedef std::set <Entry> Container;
            typedef Container::iterator iterator;
            typedef Container::const_iterator const_iterator;
            typedef Container::value_type value_type;

            uint16_t size () const;

            Common::Result save (const Entry &entry);

            /*!
             * @copydoc HF::Common::IEntries::destroy
             *
             * @warning the reference passed into this method SHOULD NOT be considered
             *          valid if it was obtained by calling the find method.
             */
            Common::Result destroy (const Entry &entry);

            Common::Result destroy (uint16_t address,
                                    Protocol::Address::Type type = Protocol::Address::DEVICE);

            // =============================================================================
            // Query API
            // =============================================================================

            EntryPtr find (const Protocol::Address &source, const Common::Interface &itf,
                           const Protocol::Address &destination) const;

            bool any_of (Protocol::Address const &source, Common::Interface const &itf) const;

            void for_each (Protocol::Address const &source, Common::Interface const &itf,
                           std::function <void(const Entry &)> func) const;

            iterator begin ()
            {
               return db.begin ();
            }

            iterator end ()
            {
               return db.end ();
            }

            const_iterator begin () const
            {
               return db.begin ();
            }

            iterator end () const
            {
               return db.end ();
            }

            /*!
             * Return a pair of iterators for the entries that match the given search
             * criteria.
             *
             * @param [in] source   device address to search for.
             * @param [in] itf      interface id to search for.
             *
             * @return  iterators to the entries found.
             */
            std::pair <iterator, iterator> find (Protocol::Address const &source,
                                                 Common::Interface const &itf) const;

            /*!
             * Destroy the entries in the persistent storage, for which the given
             * predicate function returns @c true.
             *
             * @param [in] func  predicate to call for each entry to check if it
             *                   should be deleted.
             *
             * @retval  Common::Result::OK if at least one entry was destroyed.
             * @retval  Common::Result::FAIL_ARG, otherwise.
             */
            template<typename Func>
            Common::Result destroy (Func func)
            {
               Common::Result result = Common::Result::FAIL_ARG;

               for (iterator itr = db.begin (); itr != db.end ();)
               {
                  if (func (*itr))
                  {
                     auto old = itr++;
                     destroy (*old);
                     result = Common::Result::OK;
                  }
                  else
                  {
                     ++itr;
                  }
               }

               return result;
            }

            protected:

            //! Container for the bind entries.
            Container db;
         };

         /*!
          * Helper class used to implement custom functionality to the bind management
          * server side.
          */
         template<typename _Entries = BindManagement::Entries>
         struct Server:public AbstractServer, public SessionManagement::Server <_Entries>
         {
            typedef typename SessionManagement::Server <_Entries> SessionMgr;
            typedef typename SessionMgr::Container Container;

            /*!
             * Constructor.
             *
             * @param [in] unit  reference to the unit containing this service.
             */
            Server(Unit0 &unit):AbstractServer (unit)
            {}

            virtual ~Server()
            {}

            Container &entries () const
            {
               return SessionMgr::entries ();
            }

            SessionMgr &sessions ()
            {
               return *this;
            }

            using AbstractServer::send;

            void send (const Protocol::Address &addr, Protocol::Message &message)
            {
               AbstractServer::send (addr, message);
            }

            protected:

            _Entries _entries; //!< Bind entries database.

            uint16_t payload_size (Protocol::Message::Interface &itf) const
            {
               switch (itf.member)
               {
                  case START_SESSION_CMD:
                     return SessionMgr::payload_size (SessionManagement::START);

                  case GET_ENTRIES_CMD:
                     return SessionMgr::payload_size (SessionManagement::GET);

                  case END_SESSION_CMD:
                     return SessionMgr::payload_size (SessionManagement::END);

                  default:
                     return AbstractService::payload_size (itf);
               }
            }

            Common::Result handle_command (Protocol::Packet &packet, Common::ByteArray &payload,
                                           uint16_t offset)
            {
               switch (packet.message.itf.member)
               {
                  case START_SESSION_CMD:
                     return SessionMgr::handle_command (SessionManagement::START, packet,
                                                        payload, offset);

                  case GET_ENTRIES_CMD:
                     return SessionMgr::handle_command (SessionManagement::GET, packet,
                                                        payload, offset);

                  case END_SESSION_CMD:
                     return SessionMgr::handle_command (SessionManagement::END, packet,
                                                        payload, offset);

                  default:
                     return AbstractServer::handle_command (packet, payload, offset);
               }
            }

            using SessionMgr::entries;
         };

         typedef Server <> DefaultServer;

         // =============================================================================
         // Operators
         // =============================================================================

         inline bool operator ==(const Entry &lhs, const Entry &rhs)
         {
            return lhs.source == rhs.source && lhs.destination == rhs.destination &&
                   lhs.itf == rhs.itf;
         }

         inline bool operator !=(const Entry &lhs, const Entry &rhs)
         {
            return !(lhs == rhs);
         }

         inline bool operator <(const Entry &lhs, const Entry &rhs)
         {
            return lhs.source < rhs.source || (lhs.source == rhs.source
                                               && (lhs.itf < rhs.itf ||
                                                   (lhs.itf == rhs.itf && lhs.destination < rhs.destination)));
         }

      }  // namespace BindManagement

      /*! @} */

   }  // namespace Core

}  // namespace HF

/*!
 * @addtogroup bind_mgt
 * @{
 */

// =============================================================================
// Stream Helpers
// =============================================================================

/*!
 * Convert the given @c command into a string and write it to the given @c stream.
 *
 * @param [in] stream   out stream to write the string to.
 * @param [in] command  role value to convert to a string.
 *
 * @return   <tt>stream</tt>
 */
std::ostream &operator <<(std::ostream &stream, const HF::Core::BindManagement::CMD command);

/*!
 * Convert the given @c attribute into a string and write it to the given @c stream.
 *
 * @param [in] stream      out stream to write the string to.
 * @param [in] attribute   attribute value to convert to a string.
 *
 * @return   <tt>stream</tt>
 */
std::ostream &operator <<(std::ostream &stream, const HF::Core::BindManagement::Attributes attribute);

/*! @} */

#endif /* HF_BIND_MANAGEMENT_H */
