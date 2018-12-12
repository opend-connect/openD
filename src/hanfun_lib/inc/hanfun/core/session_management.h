// =============================================================================
/*!
 * @file       inc/hanfun/core/session_management.h
 *
 * This file contains the definitions for the session management functionality.
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
#ifndef HF_SESSION_MANAGEMENT_H
#define HF_SESSION_MANAGEMENT_H

#include "hanfun/common.h"
#include "hanfun/protocol.h"

namespace HF
{
   namespace Core
   {
      /*!
       * This namespace contains the classes that implement the Session Management functionality.
       */
      namespace SessionManagement
      {
         /*!
          * @addtogroup sessions Session Management
          * @ingroup core
          *
          * This module contains the classes that implement the Session Management functionality.
          * @{
          */

         /*!
          * Available commands for session management.
          */
         typedef enum _CMD
         {
            START,   //!< Start a new session for a device.
            GET,     //!< Retrieve information.
            END,     //!< End the session for device.
         } CMD;

         // =============================================================================
         // Messages API
         // =============================================================================

         /*!
          * Start Read Session Command Message.
          */
         struct StartResponse:public Protocol::Response
         {
            uint16_t count; //!< Number of device entries.

            /*!
             * Constructor.
             *
             * @param [in] count number of entries available.
             */
            StartResponse(uint16_t count = 0):
               count (count)
            {}

            //! Minimum pack/unpack required data size.
            static constexpr uint16_t min_size = Protocol::Response::min_size + sizeof(uint16_t);

            uint16_t size () const
            {
               return min_size;
            }

            uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const
            {
               SERIALIZABLE_CHECK (array, offset, min_size);

               offset += Protocol::Response::pack (array, offset);
               array.write (offset, count);

               return min_size;
            }

            uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0)
            {
               SERIALIZABLE_CHECK (array, offset, min_size);

               offset += Protocol::Response::unpack (array, offset);
               array.read (offset, count);

               return min_size;
            }
         };

         /*!
          * Get Entries Command Message.
          */
         struct GetEntriesMessage
         {
            uint16_t offset; //!< Start index for the first entry to be provided.
            uint8_t  count;  //!< Number of entries to be sent in the response.


            GetEntriesMessage(uint16_t offset = 0, uint8_t count = 0):
               offset (offset), count (count)
            {}

            //! Minimum pack/unpack required data size.
            constexpr static uint16_t min_size = sizeof(offset) + sizeof(count);

            //! @copydoc HF::Common::Serializable::size
            uint16_t size () const
            {
               return min_size;
            }

            //! @copydoc HF::Common::Serializable::pack
            uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const
            {
               SERIALIZABLE_CHECK (array, offset, min_size);

               offset += array.write (offset, this->offset);
               array.write (offset, this->count);

               return min_size;
            }

            //! @copydoc HF::Common::Serializable::unpack
            uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0)
            {
               SERIALIZABLE_CHECK (array, offset, min_size);

               offset += array.read (offset, this->offset);
               array.read (offset, this->count);

               return min_size;
            }
         };

         template<typename _Entry>
         struct GetEntriesResponse:public Protocol::Response
         {
            std::vector <_Entry> entries;

            //! Minimum pack/unpack required data size.
            static constexpr uint16_t min_size = Protocol::Response::min_size
                                                 + sizeof(uint8_t);  // Number of entries.

            uint16_t size () const
            {
               uint16_t result = min_size;

               /* *INDENT-OFF* */
               std::for_each (entries.begin (), entries.end (), [&result](const _Entry &entry)
               {
                  result += entry.size ();
               });
               /* *INDENT-ON* */

               return result;
            }

            uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const
            {
               SERIALIZABLE_CHECK (array, offset, size ());

               uint16_t start = offset;

               offset += Protocol::Response::pack (array, offset);

               uint8_t count = entries.size ();
               offset += array.write (offset, count);

               /* *INDENT-OFF* */
               std::for_each(entries.begin(), entries.end(),
                             [&offset, &array](const _Entry &entry)
               {
                  offset += entry.pack (array, offset);
               });
               /* *INDENT-ON* */

               return offset - start;
            }

            uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0)
            {
               SERIALIZABLE_CHECK (array, offset, min_size);

               uint16_t start = offset;

               offset += Protocol::Response::unpack (array, offset);

               uint8_t count = 0;
               offset += array.read (offset, count);

               entries.clear ();

               _Entry entry;

               for (uint8_t i = 0; i < count; i++)
               {
                  offset += entry.unpack (array, offset);
                  entries.push_back (entry);
               }

               return offset - start;
            }
         };

         template<>
         struct GetEntriesResponse <void> :public Protocol::Response
         {
            uint8_t count;

            GetEntriesResponse():count (0)
            {}

            //! Minimum pack/unpack required data size.
            static constexpr uint16_t min_size = Protocol::Response::min_size
                                                 + sizeof(uint8_t);  // Number of entries.

            uint16_t size () const
            {
               return min_size;
            }

            uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const
            {
               SERIALIZABLE_CHECK (array, offset, min_size);

               offset += Protocol::Response::pack (array, offset);

               uint8_t count = 0;
               array.write (offset, count);

               return min_size;
            }

            uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0)
            {
               SERIALIZABLE_CHECK (array, offset, min_size);

               offset += Protocol::Response::unpack (array, offset);

               uint8_t count = 0;
               array.read (offset, count);

               return min_size;
            }
         };

         typedef GetEntriesResponse <void> GetEntriesEmptyResponse;

         // =============================================================================
         // Server API
         // =============================================================================

         /*!
          * Session Management API : Server side.
          */
         struct IServer
         {
            /*!
             * Start a session for the device with the given @c address.
             *
             * Only one session is associated with any given device at any time.
             *
             * @param [in] address  device address to start the session for.
             */
            virtual void start_session (uint16_t address) = 0;

            /*!
             * Terminate the session associated with the device with the
             * given @c address.
             *
             * @param [in] address  device address to end the session for.
             */
            virtual void end_session (uint16_t address) = 0;

            /*!
             * Check if a session for the device with the given @c address exists.
             *
             * @param [in] address  device address to check is a session exists.
             *
             * @retval  true     if a session exists,
             * @retval  false    otherwise.
             */
            virtual bool exists (uint16_t address) const = 0;

            /*!
             * Check if the session for the device with the given @c address is
             * valid, i.e., the underling entries have not been modified since the
             * start of the session.
             *
             * @param [in] address  device address to check is the session is valid.
             *
             * @retval  true     if the session exists and is valid,
             * @retval  false    otherwise.
             */
            virtual bool is_valid (uint16_t address) const = 0;
         };

         /*!
          * Parent class for session management functionality - Server side.
          */
         class AbstractServer:public IServer
         {
            protected:

            /*!
             * Session database entry.
             *
             * A session entry is valid if no modifications where made to the
             * underling entries database, since the start of the session.
             */
            struct Session
            {
               uint16_t address;    //!< Device address for session.
               bool     valid;      //!< Indicate if the session is still valid.

               /*!
                * Constructor.
                *
                * @param [in] _address    device address this session belongs to.
                * @param [in] _valid      @c true if the session is valid, @c false otherwise.
                */
               Session(uint16_t _address = HF::Protocol::BROADCAST_ADDR, bool _valid = false):
                  address (_address), valid (_valid)
               {}
            };

            typedef std::vector <Session> Container;
            typedef Container::iterator iterator;
            typedef Container::const_iterator const_iterator;

            //! Session's database.
            Container sessions;

            // =============================================================================
            // API
            // =============================================================================

            public:

            //! Constructor.
            AbstractServer():sessions (Container ())
            {}

            virtual ~AbstractServer()
            {}

            void start_session (uint16_t address)
            {
               auto it = find (address);

               if (it == sessions.end ())  // Session does not exist.
               {
                  sessions.push_back (Session (address, true));
               }
               else  // Session already exists. Update state.
               {
                  it->valid = true;
               }
            }

            void end_session (uint16_t address)
            {
               auto it = find (address);

               if (it != sessions.end ())
               {
                  sessions.erase (it);
               }
            }

            bool exists (uint16_t address) const
            {
               return find (address) != sessions.end ();
            }

            bool is_valid (uint16_t address) const
            {
               auto it = find (address);

               if (it != sessions.end ())
               {
                  return it->valid;
               }

               return false;
            }

            /*!
             * Invalidate all sessions.
             */
            void invalidate ()
            {
               /* *INDENT-OFF* */
               std::for_each (sessions.begin (), sessions.end (), [](Session &session)
               {
                  session.valid = false;
               });
               /* *INDENT-ON* */
            }

            protected:

            /*!
             * @copydoc HF::Interfaces::AbstractInterface::handle_command.
             *
             * @param [in] cmd      the session operation to process.
             * @param [in] packet   the packet receive from the network.
             *
             * @param [in] payload  the byte array containing the data received from the
             *                      network.
             *
             * @param [in] offset   the offset the payload start at in the byte array.
             *
             * @return the result of the message processing.
             */
            Common::Result handle_command (CMD cmd, Protocol::Packet &packet,
                                           Common::ByteArray &payload, uint16_t offset = 0);

            /*!
             * Find the session associated with the given device @c address.
             *
             * @param [in] address  device address to search a session for.
             *
             * @return  an iterator to the session found or Container::end() otherwise.
             */
            iterator find (uint16_t address)
            {
               /* *INDENT-OFF* */
               return std::find_if (sessions.begin (), sessions.end (),
                                    [address](const Session &session)
               {
                  return address == session.address;
               });
               /* *INDENT-ON* */
            }

            /*!
             * Find the session associated with the given device @c address.
             *
             * @param [in] address  device address to search a session for.
             *
             * @return  a constant iterator to the session found or Container::end() otherwise.
             */
            const_iterator find (uint16_t address) const
            {
               /* *INDENT-OFF* */
               return std::find_if (sessions.cbegin (), sessions.cend (),
                                    [address](const Session &session)
               {
                  return address == session.address;
               });
               /* *INDENT-ON* */
            }

            /*!
             * Get the minimum number of bytes necessary to pack/unpack a message of the
             * given command.
             *
             * @param [in] cmd   the command to get the number of bytes for.
             *
             * @return  number of bytes required.
             */
            uint16_t payload_size (CMD cmd) const;

            /*!
             * Check if the given @c offset is valid and adjust the @c count value if
             * necessary.
             *
             * @param [in]    offset   offset to start reading the entries from.
             * @param [inout] count    number of entries to read.
             * @param [in]    size     number of entries present in the underling container.
             *
             * @retval HF::Common::Result::OK         if entries can be read.
             * @retval HF::Common::Result::FAIL_ARG   if the offset value is invalid.
             */
            Common::Result check_offset (uint16_t offset, uint8_t &count, uint16_t size) const;

            //! @copydoc HF::Interfaces::AbstractInterface::send
            virtual void send (const Protocol::Address &addr, Protocol::Message &message) = 0;

            /*!
             * Get the number of entries present in the container.
             *
             * @return  number of entries in the wrapped service.
             */
            virtual uint16_t entries_size () const = 0;

            /*!
             * Create a GetEntriesResponse message message with, @c count entries starting
             * from the given @c offset and serialize the created message into the
             * given byte array in @c payload.
             *
             * @remark  if <tt>offset + count > [number of entries]</tt>, the message will
             *          truncated to the available entries starting from the given @c offset.
             *
             * @param [in]  offset   the offset to start reading the entries.
             * @param [in]  count    number of entries to read.
             * @param [out] payload  byte array to serialize the entries to.
             *
             * @retval  Common::Result::OK         message created successfully;
             * @retval  Common::Result::FAIL_ARG   if @c offset is bigger than the
             *                                     number of entries.
             */
            virtual Common::Result entries (uint16_t offset, uint8_t count, Common::ByteArray &payload) = 0;

            /*!
             * Check if a session for the given device @c address exists and if it is valid.
             *
             * In case a session does not exist or is invalid, place an GetEntriesEmptyResponse
             * into the byte array given by @c payload to be sent to the remote device.
             *
             * @param [in] address     device address to check the session for.
             * @param [out] payload    the byte array to place the response in case of error.
             *
             * @retval Common::Result::FAIL_READ_SESSION    if the session does not exist;
             * @retval Common::Result::FAIL_FAIL_MODIFIED   if the session is not valid;
             * @retval Common::Result::OK                   a session exists an is valid.
             */
            Common::Result check_session (uint16_t address, Common::ByteArray &payload) const;
         };

         /*!
          * Wrapper over persistent storage APIs to invalidate sessions on
          * save and destroy.
          */
         template<typename Parent>
         class Entries:public Parent
         {
            AbstractServer &manager;

            public:

            typedef typename Parent::value_type value_type;

            /*!
             * Constructor.
             *
             * @param [in] _manager    session manager the entries are associated to.
             */
            Entries(AbstractServer &_manager):Parent (),
               manager (_manager)
            {}

            /*!
             * Constructor.
             *
             * @param [in] other       entries container to wrap.
             * @param [in] _manager    session manager the entries are associated to.
             */
            Entries(const Entries &other, AbstractServer &_manager):
               Parent (other), manager (_manager)
            {}

            virtual ~Entries()
            {}

            //! @copydoc HF::Common::IEntries::save
            Common::Result save (const value_type &entry)
            {
               auto res = Parent::save (entry);
               manager.invalidate ();
               return res;
            }

            //! @copydoc HF::Common::IEntries::destroy
            Common::Result destroy (const value_type &entry)
            {
               auto res = Parent::destroy (entry);
               manager.invalidate ();
               return res;
            }
         };

         /*!
          * Helper template to inject session management functionality into
          * services requiring it - Server side.
          */
         template<typename _Entries>
         struct Server:public AbstractServer
         {
            typedef Entries <_Entries> Container;

            /*!
             * Return the container for the service entries.
             *
             * @return  reference to the object containing the wrapped service entries.
             */
            Container &entries () const
            {
               return const_cast <Container &>(_entries);
            }

            protected:

            Server():AbstractServer (), _entries (*this)
            {}

            virtual ~Server()
            {}

            /*!
             * Copy-Constructor.
             *
             * Make sure that the entries are copied mantain this object as the session manager.
             *
             * @param [in] other    reference to the object to copy from.
             */
            Server(const Server &other):
               AbstractServer (other), _entries (other._entries, *this)
            {}

            // =============================================================================
            // API
            // =============================================================================

            uint16_t entries_size () const
            {
               return static_cast <uint16_t>(_entries.size ());
            }

            typedef typename _Entries::value_type value_type;

            Common::Result entries (uint16_t offset, uint8_t count, Common::ByteArray &payload)
            {
               GetEntriesResponse <value_type> response;

               response.code = check_offset (offset, count, entries_size ());

               if (response.code == Common::Result::OK)
               {
                  auto start = _entries.begin ();
                  std::advance (start, offset);

                  auto end = start;
                  std::advance (end, count);
                  std::copy (start, end, std::back_inserter (response.entries));
               }

               payload = Common::ByteArray (response.size ());

               response.pack (payload);

               return response.code;
            }

            private:

            //! Wrap container for the entries of the wrapped container.
            Container _entries;
         };

         // =============================================================================
         // Client API
         // =============================================================================

         /*!
          * Parent class for session management functionality - Client side.
          */
         class AbstractClient
         {
            // ======================================================================
            // Commands
            // ======================================================================
            //! @name Commands
            //! @{

            /*!
             * Send a message to start a session on the server.
             */
            virtual void start_session () const = 0;

            /*!
             * Send a message to end the current session on the server.
             */
            virtual void end_session () const = 0;

            /*!
             * Send a message to get @c count entries starting at @c offset.
             *
             * @param [in] offset   the index to start the entries from.
             * @param [in] count    the number of entries to retrieve.
             */
            virtual void get_entries (uint16_t offset, uint8_t count = 0) const = 0;

            //! @}
            // ======================================================================
            // ======================================================================
            // Events
            // ======================================================================
            //! @name Events
            //! @{

            /*!
             * This is event is called when a response to a start session message is
             * received.
             *
             * @param [in] response the received response.
             */
            virtual void session_started (StartResponse &response)
            {
               UNUSED (response);
            }

            /*!
             * This is event is called when a response to a end session message is
             * received.
             *
             * @param [in] response the received response.
             */
            virtual void session_ended (Protocol::Response &response)
            {
               UNUSED (response);
            }

            //! @}
            // ======================================================================

            protected:

            /*!
             * @copydoc HF::Interfaces::AbstractInterface::handle_command.
             *
             * @param [in] cmd      the session operation to process.
             * @param [in] packet   the packet receive from the network.
             * @param [in] payload  the byte array containing the data received from the
             *                      network.
             * @param [in] offset   the offset the payload start at in the byte array.
             *
             * @return  the result of the message processing.
             */
            Common::Result handle_command (CMD cmd, Protocol::Packet &packet,
                                           Common::ByteArray &payload, uint16_t offset = 0);

            /*!
             * Get the minimum number of bytes necessary to pack/unpack a message of the
             * given command.
             *
             * @param [in] cmd   the command to get the number of bytes for.
             *
             * @return  number of bytes required.
             */
            uint16_t payload_size (CMD cmd) const;

            /*!
             * Helper method to send a message to read, @c count entries starting at
             * @c offset from the server.
             *
             * @param [in] offset   index to start reading the entries from.
             * @param [in] count    number of entries to read.
             */
            template<uint8_t _role, uint16_t _uid, uint8_t _member>
            void get_entries (uint16_t offset, uint8_t count = 0) const
            {
               SessionManagement::GetEntriesMessage msg (offset, count);

               Protocol::Address addr (0, 0);
               Protocol::Message message;

               message.itf.role   = _role;
               message.itf.id     = _uid;
               message.itf.member = _member;

               message.payload    = Common::ByteArray (msg.size ());

               msg.pack (message.payload);

               const_cast <AbstractClient *>(this)->send (addr, message);
            }

            /*!
             * Helper method to create a session management request.
             *
             * @tparam  _role    role to use in the created message.
             * @tparam  _uid     interface UID to use in the message.
             * @tparam  _member  interface member ID to use.
             *
             */
            template<uint8_t _role, uint16_t _uid, uint8_t _member>
            void request () const
            {
               Protocol::Address addr (0, 0);
               Protocol::Message message;

               message.itf.role   = _role;
               message.itf.id     = _uid;
               message.itf.member = _member;

               const_cast <AbstractClient *>(this)->send (addr, message);
            }

            //! @copydoc HF::Interfaces::AbstractInterface::send
            virtual void send (const Protocol::Address &addr, Protocol::Message &message) = 0;
         };

         /*!
          * Helper template to inject session management functionality into
          * services requiring it - Client side.
          */
         template<typename _Entry>
         struct Client:public AbstractClient
         {
            // ======================================================================
            // Events
            // ======================================================================
            //! @name Events
            //! @{

            /*!
             * This event is called when a response to a get entries is received.
             *
             * @param [in] response the response received.
             */
            virtual void entries (const GetEntriesResponse <_Entry> &response)
            {
               UNUSED (response);
            }

            //! @}
            // ======================================================================

            protected:

            Common::Result handle_command (CMD cmd, Protocol::Packet &packet,
                                           Common::ByteArray &payload, uint16_t offset = 0)
            {
               if (cmd == GET)
               {
                  GetEntriesResponse <_Entry> response;
                  response.unpack (payload, offset);
                  entries (response);
                  return Common::Result::OK;
               }
               else
               {
                  return AbstractClient::handle_command (cmd, packet, payload, offset);
               }
            }
         };

      }  // namespace SessionManagement

      /*! @} */

   }  // namespace Core

}  // namespace HF

#endif /* HF_SESSION_MANAGEMENT_H */
