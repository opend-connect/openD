// =============================================================================
/*!
 * @file       inc/hanfun/core/device_management.h
 *
 * This file contains the definitions for the core Device Management Interface
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
#ifndef HF_DEVICE_MANGEMENT_H
#define HF_DEVICE_MANGEMENT_H

#include "hanfun/common.h"
#include "hanfun/uids.h"

#include "hanfun/protocol.h"

#include "hanfun/core.h"
#include "hanfun/device.h"
#include "hanfun/units.h"

#include "hanfun/core/session_management.h"

namespace HF
{
   // Forward declarations

   namespace Devices
   {
      namespace Concentrator
      {
         struct IUnit0;

      }  // namespace Concentrator

   }  // namespace Devices

   namespace Core
   {
      // Forward declaration.
      namespace DeviceManagement
      {
         struct IServer;
      }  // namespace DeviceManagement

      /*!
       * @ingroup dev_mgt
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
      HF::Attributes::IAttribute *create_attribute (HF::Core::DeviceManagement::IServer *server,
                                                    uint8_t uid);

      /*!
       * This namespace contains the classes that implement the Device Management service.
       */
      namespace DeviceManagement
      {
         /*!
          * @addtogroup dev_mgt  Device Management
          * @ingroup core
          *
          * This module contains the classes that implement the %Device Management service.
          * @{
          */
         //! Commands.
         typedef enum _CMD
         {
            REGISTER_CMD      = 0x01, //!< Register device command.
            DEREGISTER_CMD    = 0x02, //!< De-register device command.
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

         constexpr static uint16_t START_ADDR = 0x0001;  //!< First HAN-FUN Address.
         constexpr static uint16_t END_ADDR   = 0x7FFE;  //!< Last HAN-FUN Address.

         // =============================================================================

         /*!
          * Unit Entry
          */
         struct Unit
         {
            uint8_t  id;        //!< Unit Id.
            uint16_t profile;   //!< Unit UID. @see IProfile::UID.

            //! Optional interfaces.
            std::vector <Common::Interface> interfaces;

            /*!
             * Constructor.
             *
             * @param [in] id       unit id.
             * @param [in] profile  unit UID / Profile UID.
             */
            Unit(uint8_t id = 0, uint16_t profile = 0):
               id (id), profile (profile)
            {}

            /*!
             * Constructor.
             *
             * @param [in] unit  reference to a HF::Units::IUnit.
             */
            Unit(const HF::Units::IUnit &unit):
               id (unit.id ()), profile (unit.uid ()), interfaces (unit.interfaces ())
            {}

            //! Minimum pack/unpack required data size.
            static constexpr uint16_t min_size = sizeof(uint8_t)     // Unit entry size.
                                                 + sizeof(uint8_t)   // Unit ID.
                                                 + sizeof(uint16_t); // Unit's profile UID.

            //! @copydoc HF::Common::Serializable::size
            uint16_t size () const;

            //! @copydoc HF::Common::Serializable::pack
            uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

            //! @copydoc HF::Common::Serializable::unpack
            uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0);

            /*!
             * This method checks if the remote device unit implements the given interface.
             *
             * The known interfaces for the profile associated with this unit and the
             * declared optional interfaces are searched, to check if the requested interface
             * is available.
             *
             * @param [in] itf_uid    the interface UID to check if the profile implements.
             * @param [in] role       the interface role to match.
             *
             * @retval  true     if this unit implements the requested interface,
             * @retval  false    otherwise.
             */
            bool has_interface (uint16_t itf_uid, HF::Interface::Role role) const;
         };

         /*!
          * Device Entry.
          */
         struct Device
         {
            uint16_t           address;   //!< Device Address.
            std::vector <Unit> units;     //!< Unit list of the interface.

            uint16_t           emc;       //!< Device EMC if applicable, 0 otherwise.

            HF::UID::UID       uid;       //!< Device UID.

            Device():address (Protocol::BROADCAST_ADDR), emc (0)
            {}

            virtual ~Device()
            {}

            // =============================================================================
            // Serializable API
            // =============================================================================

            //! Minimum pack/unpack required data size.
            static constexpr uint16_t min_size = sizeof(uint16_t)   // Device Address.
                                                 + sizeof(uint8_t); // Number of units.

            //! @copydoc HF::Common::Serializable::size
            uint16_t size () const;

            //! @copydoc HF::Common::Serializable::pack
            uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

            //! @copydoc HF::Common::Serializable::unpack
            uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0);

            // =============================================================================
            // Operators
            // =============================================================================

            //! Equals operator.
            bool operator ==(Device &other)
            {
               if (this->address != other.address || this->uid != other.uid)
               {
                  return false;
               }
               else
               {
                  return true;
               }
            }

            //! Not equals operator.
            bool operator !=(Device &other)
            {
               return !(*this == other);
            }
         };

         typedef Common::Pointer <const Device> DevicePtr;

         // =============================================================================
         // Register Command Messages
         // =============================================================================

         /*!
          * Register command message.
          */
         struct RegisterMessage
         {
            uint16_t           emc;   //! Device EMC if applicable, 0 otherwise.
            std::vector <Unit> units; //! Device units listing.

            HF::UID::UID       uid;   //! Device UID.

            /*!
             * Constructor.
             *
             * @param [in] emc   device EMC (Electronic Manufacture Code)
             * @param [in] _uid  device UID. @see HF::UID::UID_T
             */
            RegisterMessage(uint16_t emc = 0x0000, HF::UID::UID _uid = HF::UID::UID ()):
               emc (emc), uid (_uid)
            {}

            virtual ~RegisterMessage();

            //! Minimum pack/unpack required data size.
            static constexpr uint16_t min_size = UID::UID_T::min_size // UID.
                                                 + sizeof(uint8_t);   // Number of units.

            //! @copydoc HF::Common::Serializable::size
            uint16_t size () const;

            //! @copydoc HF::Common::Serializable::pack
            uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

            //! @copydoc HF::Common::Serializable::unpack
            uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0);
         };

         /*!
          * Register command response.
          */
         struct RegisterResponse:public Protocol::Response
         {
            uint16_t address; //!< Address for the device to use.
            uint16_t emc;     //!< HAN-FUN Concentrator EMC if applicable.

            RegisterResponse(uint16_t address = Protocol::BROADCAST_ADDR, uint16_t emc = 0):
               address (address & Protocol::BROADCAST_ADDR), emc (emc)
            {}

            uint16_t size () const;

            uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

            uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0);
         };

         // =============================================================================
         // De-register Command Messages.
         // =============================================================================

         /*!
          * De-register command message.
          */
         struct DeregisterMessage
         {
            uint16_t address; //!< Address of the device to de-register.

            /*!
             * Constructor.
             *
             * @param [in] address  device address to de-register.
             */
            DeregisterMessage(uint16_t address = 0):
               address (address)
            {}

            //! Minimum pack/unpack required data size.
            static constexpr uint16_t min_size = sizeof(uint16_t);   // Device Address.

            //! @copydoc HF::Common::Serializable::size
            uint16_t size () const;

            //! @copydoc HF::Common::Serializable::pack
            uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

            //! @copydoc HF::Common::Serializable::unpack
            uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0);
         };

         /*!
          * Device Management - Persistent Storage API.
          */
         struct IEntries:public Common::IEntries <Device>
         {
            /*!
             * Return the Device entry for the given address.
             *
             * @param [in] address    the device address.
             *
             * @retval  a pointer to the Device entry associated with the given address,
             * @retval  nullptr if the entry does not exist.
             */
            virtual DevicePtr find (uint16_t address) const = 0;

            /*!
             * Return the Device entry for the given UID.
             *
             * @param [in] uid   the device UID.
             *
             * @retval  a pointer the Device entry associated with the given UID,
             * @retval  nullptr if the entry does not exist.
             */
            virtual DevicePtr find (const HF::UID::UID &uid) const = 0;

            /*!
             * Return next available address for registering a device.
             *
             * @return  the address to use in the next registration.
             */
            virtual uint16_t next_address () const = 0;
         };

         /*!
          * @copybrief HF::Core::create_attribute (HF::Core::DeviceManagement::Server *,uint8_t)
          *
          * @see HF::Core::create_attribute (HF::Core::DeviceManagement::Server *,uint8_t)
          *
          * @param [in] uid   attribute %UID to create the attribute object for.
          *
          * @retval  pointer to an attribute object
          * @retval  <tt>nullptr</tt> if the attribute UID does not exist.
          */
         HF::Attributes::IAttribute *create_attribute (uint8_t uid);

         /*!
          * Parent class for the Device Management interface implementation.
          */
         class Abstract:public Service <HF::Interface::DEVICE_MANAGEMENT>
         {
            protected:

            /*!
             * Constructor.
             *
             * @param [in] unit  reference to the unit containing this service.
             */
            Abstract(Unit0 &unit):
               Service (unit)
            {}
         };

         /*!
          * Device Management interface : Client side.
          */
         class Client:public ServiceRole <Abstract, HF::Interface::CLIENT_ROLE>,
            protected SessionManagement::Client <Device>
         {
            typedef ServiceRole <Abstract, HF::Interface::CLIENT_ROLE> Service;

            protected:

            uint16_t _address; //! Device HAN-FUN Address.

            public:

            typedef SessionManagement::Client <Device> SessionMgr;

            /*!
             * Constructor.
             *
             * @param [in] unit  reference to the unit containing this service.
             */
            Client(Unit0 &unit):
               ServiceRole (unit), _address (Protocol::BROADCAST_ADDR)
            {}

            virtual ~Client() {}

            /*!
             * Return the address given by the HF Concentrator to the Device.
             *
             * @return  the device HAN-FUN address.
             */
            virtual uint16_t address () const
            {
               return _address;
            }

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
             * Send a register message.
             */
            void register_device ();

            /*!
             * Send a de-register message for the given @c address.
             *
             * @param [in] address    the address of the device to de-register.
             */
            void deregister (uint16_t address);

            /*!
             * Send a de-register message for current address.
             */
            void deregister ()
            {
               deregister (_address);
            }

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
             * This method is called when a response to a registration message
             * is received.
             *
             * @param [in] response  the register response that was received.
             */
            virtual void registered (RegisterResponse &response);

            /*!
             * This method is called when a response to a de-registration message
             * is received.
             *
             * @param [in] response    the response received.
             */
            virtual void deregistered (Protocol::Response &response);

            //! @}
            // ======================================================================

            using Service::send;

            //! @copydoc SessionManagement::AbstractClient::send
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
          * Device Management interface : Server side API.
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

            /*!
             * Return the Device entry for the given address.
             *
             * @param [in] address    the device address.
             *
             * @retval  a pointer the Device entry associated with the given address,
             * @retval  nullptr if the entry does not exist.
             */
            DevicePtr entry (uint16_t address) const;

            /*!
             * Return the Device entry for the given UID.
             *
             * @param [in] uid   the device UID.
             *
             * @retval  a pointer the Device entry associated with the given UID,
             * @retval  nullptr if the entry does not exist.
             */
            DevicePtr entry (const HF::UID::UID &uid) const
            {
               return entries ().find (uid);
            }

            /*!
             * Get a reference to the current object implementing the persistence API,
             * for the device information.
             *
             * @return  reference to the current object for the persistence API.
             */
            virtual IEntries &entries () const = 0;

            /*!
             * Reference to the session management API.
             *
             * @return  reference to the object implementing the session management API for
             *          this device management server.
             */
            virtual SessionManagement::IServer &sessions () = 0;

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

            /*!
             * Return next available address for registering a device.
             *
             * @return  the address to use in the next registration.
             */
            virtual uint16_t next_address ()
            {
               return entries ().next_address ();
            }

            // ======================================================================
            // Events
            // ======================================================================
            //! @name Events
            //! @{

            /*!
             * Indicate that a device has been registered.
             *
             * @param [in] device  pointer to the device entry corresponding to the registered
             *                     device.
             */
            virtual void registered (DevicePtr &device)
            {
               UNUSED (device);
            }

            /*!
             * Indicate that a device has been de-registered.
             *
             * @param [in] device  pointer to the device entry corresponding to the de-registered
             *                     device.
             */
            virtual void deregistered (DevicePtr &device)
            {
               UNUSED (device);
            }

            //! @}
            // ======================================================================

            protected:

            /*!
             * Constructor.
             *
             * @param [in] unit  reference to the unit containing this service.
             */
            IServer(Unit0 &unit):ServiceRole (unit)
            {}
         };

         /*!
          * Device Management interface : Server side default implementation.
          */
         struct AbstractServer:public IServer
         {
            virtual ~AbstractServer() {}

            // =============================================================================
            // API
            // =============================================================================

            protected:

            /*!
             * Constructor.
             *
             * @param [in] unit  reference to the unit containing this service.
             */
            AbstractServer(Unit0 &unit):IServer (unit)
            {}

            // ======================================================================
            // Events
            // ======================================================================
            //! @name Events
            //! @{

            /*!
             * This method is called when a registration message is received.
             */
            virtual Common::Result register_device (Protocol::Packet &packet,
                                                    Common::ByteArray &payload, uint16_t offset);

            /*!
             * This method is called when a de-registration message is received.
             */
            virtual Common::Result deregister_device (Protocol::Packet &packet,
                                                      Common::ByteArray &payload, uint16_t offset);

            //! @}
            // ======================================================================

            // ======================================================================
            // Commands
            // ======================================================================
            //! @name Commands
            //! @{

            /*!
             * This method serves to indicate if a given @c member of the interface
             * can be used by the @c source device affecting the @c destination
             * device configuration on the system.
             *
             * @param [in] member       interface member UID.
             * @param [in] source       device entry for the requesting device.
             * @param [in] destination  device entry for the affected device.
             *
             * @retval  true     the operation is allowed,
             * @retval  false    otherwise.
             */
            virtual bool authorized (uint8_t member, DevicePtr &source, DevicePtr &destination);

            /*!
             * De-register the device that corresponds to the given Device entry.
             *
             * @warning this method by-passes the authorization scheme.
             *
             * @param [in] device   pointer to the device entry to de-register.
             *
             * @return the result of the destroy method.
             */
            virtual Common::Result deregister (DevicePtr &device);

            //! @}
            // ======================================================================

            using ServiceRole <Abstract, HF::Interface::SERVER_ROLE>::payload_size;

            uint16_t payload_size (Protocol::Message::Interface &itf) const;

            Common::Result handle_command (Protocol::Packet &packet, Common::ByteArray &payload,
                                           uint16_t offset);
         };

         /*!
          * Default implementation of the persistence API.
          */
         struct Entries:public IEntries
         {
            typedef std::vector <Device> Container;
            typedef Container::iterator iterator;
            typedef Container::const_iterator const_iterator;
            typedef Container::value_type value_type;

            uint16_t size () const
            {
               return db.size ();
            }

            Common::Result save (const Device &entry);

            /*!
             * @copydoc HF::Common::IEntries::destroy
             *
             * @warning the reference passed into this method SHOULD NOT be considered
             *          valid if it was obtained by calling the find method.
             *
             */
            Common::Result destroy (const Device &entry);

            DevicePtr find (uint16_t address) const;

            DevicePtr find (const HF::UID::UID &uid) const;

            uint16_t next_address () const;

            /*!
             * Get an iterator to the start of the entries in this container.
             *
             * @return  iterator to the start of the entries present in this container.
             */
            iterator begin ()
            {
               return db.begin ();
            }

            /*!
             * Get an iterator to the end of the entries in this container.
             *
             * @return  iterator to the end of the entries present in this container.
             */
            iterator end ()
            {
               return db.end ();
            }

            /*!
             * Get a constant iterator to the start of the entries in this container.
             *
             * @return  constant iterator to the start of the entries present in this container.
             */
            const_iterator begin () const
            {
               return db.cbegin ();
            }

            /*!
             * Get a constant iterator to the start of the entries in this container.
             *
             * @return  constant iterator to the start of the entries present in this container.
             */
            const_iterator end () const
            {
               return db.cend ();
            }

            protected:

            //! Actual container for the entries.
            Container db;
         };

         /*!
          * Helper class used to implement custom functionality to the device management
          * server side.
          */
         template<typename _Entries = DeviceManagement::Entries>
         struct Server:public AbstractServer, public SessionManagement::Server <_Entries>
         {
            typedef typename SessionManagement::Server <_Entries> SessionMgr;
            typedef typename SessionMgr::Container Container;

            /*!
             * Constructor.
             *
             * @param [in] unit  reference to the unit containing this service.
             */
            Server(Unit0 &unit):
               AbstractServer (unit), SessionManagement::Server <_Entries>()
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
                     return SessionMgr::handle_command (SessionManagement::START, packet, payload,
                                                        offset);

                  case GET_ENTRIES_CMD:
                     return SessionMgr::handle_command (SessionManagement::GET, packet, payload,
                                                        offset);

                  case END_SESSION_CMD:
                     return SessionMgr::handle_command (SessionManagement::END, packet, payload,
                                                        offset);

                  default:
                     return AbstractServer::handle_command (packet, payload, offset);
               }
            }

            using SessionMgr::entries;
         };

         // =========================================================================
         // Default API Implementations
         // =========================================================================

         typedef Server <> DefaultServer;

         // =============================================================================
         // Operators
         // =============================================================================

         inline bool operator ==(const Unit &lhs, const Unit &rhs)
         {
            if (lhs.id != rhs.id)
            {
               return false;
            }

            if (lhs.profile != rhs.profile)
            {
               return false;
            }

            if (lhs.interfaces.size () != rhs.interfaces.size ())
            {
               return false;
            }

            for (uint8_t i = 0; i < lhs.interfaces.size (); i++)
            {
               if (lhs.interfaces[i] != rhs.interfaces[i])
               {
                  return false;
               }
            }

            return true;
         }

         inline bool operator !=(const Unit &lhs, const Unit &rhs)
         {
            return !(lhs == rhs);
         }

         inline bool operator ==(const Device &lhs, const Device &rhs)
         {
            if (lhs.address != rhs.address)
            {
               return false;
            }

            if (lhs.units.size () != rhs.units.size ())
            {
               return false;
            }

            for (uint8_t i = 0; i < lhs.units.size (); i++)
            {
               if (lhs.units[i] != rhs.units[i])
               {
                  return false;
               }
            }

            return true;
         }

         inline bool operator !=(const Device &lhs, const Device &rhs)
         {
            return !(lhs == rhs);
         }

         /*! @} */

      } // namespace DeviceManagement

   } // namespace Core

} // namespace HF

/*!
 * @addtogroup dev_mgt
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
std::ostream &operator <<(std::ostream &stream, const HF::Core::DeviceManagement::CMD command);

/*!
 * Convert the given @c attribute into a string and write it to the given @c stream.
 *
 * @param [in] stream      out stream to write the string to.
 * @param [in] attribute   attribute value to convert to a string.
 *
 * @return   <tt>stream</tt>
 */
std::ostream &operator <<(std::ostream &stream, const HF::Core::DeviceManagement::Attributes attribute);

/*! @} */

#endif /* HF_DEVICE_MANGEMENT_H */
