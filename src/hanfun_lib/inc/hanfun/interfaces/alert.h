// =============================================================================
/*!
 * @file       inc/hanfun/interfaces/alert.h
 *
 * This file contains the definitions for the Alert interface.
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
#ifndef HF_ITF_ALERT_H
#define HF_ITF_ALERT_H

#include "hanfun/common.h"

#include "hanfun/protocol.h"
#include "hanfun/interface.h"

// =============================================================================
// API
// =============================================================================

namespace HF
{
   namespace Interfaces
   {
      // Forward declaration.
      namespace Alert
      {
         class Server;

      }  // namespace Alert

      /*!
       * @ingroup alert_itf
       *
       * Create an attribute object that can hold the attribute with the given @c uid.
       *
       * If @c server is not equal to @c nullptr then initialize it with the current
       * value.
       *
       * @param [in] server   pointer to the object to read the current value from.
       * @param [in] uid      attribute's UID to create the attribute object for.
       *
       * @retval  pointer to an attribute object
       * @retval  <tt>nullptr</tt> if the attribute UID does not exist.
       */
      HF::Attributes::IAttribute *create_attribute (HF::Interfaces::Alert::Server *server,
                                                    uint8_t uid);

      /*!
       * This namespace contains the implementation of the %Alert interface.
       */
      namespace Alert
      {
         /*!
          * @addtogroup alert_itf  Alert Interface
          * @ingroup interfaces
          *
          * This module contains the classes that define and implement the %Alert interface API.
          * @{
          */
         //! Command IDs.
         typedef enum _CMD
         {
            STATUS_CMD   = 0x01,         //!< Alert Status Command ID.
            __LAST_CMD__ = STATUS_CMD
         } CMD;

         //! Attributes
         typedef enum _Attributes
         {
            STATE_ATTR    = 0x01, //!< %State attribute %UID.
            ENABLE_ATTR   = 0x02, //!< %Enable attribute %UID.
            __LAST_ATTR__ = ENABLE_ATTR,
         } Attributes;

         /*!
          * Payload for the %Status command.
          */
         struct Message
         {
            //! Minimum pack/unpack required data size.
            static constexpr uint16_t min_size = sizeof(uint16_t)    // Profile UID.
                                                 + sizeof(uint32_t); // State.

            uint16_t type;        //!< Unit Type that generated the message.
            uint32_t state;       //!< Current state of the server.

            /*!
             * Constructor.
             *
             * @param [in] type     unit that generated this message.
             * @param [in] state    state to sent to the client.
             */
            Message(uint16_t type = 0, uint32_t state = 0);

            //! @copydoc HF::Common::Serializable::size
            uint16_t size () const;

            //! @copydoc HF::Common::Serializable::pack
            uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

            //! @copydoc HF::Common::Serializable::unpack
            uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0);
         };

         /*!
          * Helper class to handle the %State attribute for the %Alert interface.
          */
         struct State:public HF::Attributes::Attribute <uint32_t>
         {
            static constexpr uint8_t ID        = STATE_ATTR; //!< Attribute %UID.
            static constexpr bool    WRITABBLE = false;      //!< Attribute Read/Write

            State(uint32_t data = 0, const HF::Interface *owner = nullptr):
               Attribute <uint32_t>(Interface::ALERT, ID, owner, data, WRITABBLE)
            {}
         };

         /*!
          * Helper class to handle the Enabled attribute for the %Alert interface.
          */
         struct Enable:public HF::Attributes::Attribute <uint32_t>
         {
            static constexpr uint8_t ID        = ENABLE_ATTR; //!< Attribute %UID.
            static constexpr bool    WRITABBLE = true;        //!< Attribute Read/Write

            Enable(uint32_t data = 0, const HF::Interface *owner = nullptr):
               Attribute <uint32_t>(Interface::ALERT, ID, owner, data, WRITABBLE)
            {}
         };

         /*!
          * @copybrief HF::Interfaces::create_attribute (HF::Interfaces::Alert::Server *,uint8_t)
          *
          * @see HF::Interfaces::create_attribute (HF::Interfaces::Alert::Server *,uint8_t)
          *
          * @param [in] uid   attribute %UID to create the attribute object for.
          *
          * @retval  pointer to an attribute object
          * @retval  <tt>nullptr</tt> if the attribute UID does not exist.
          */
         HF::Attributes::IAttribute *create_attribute (uint8_t uid);

         /*!
          * %Alert %Interface : Parent.
          *
          * This is the parent class for the %Alert interface implementation.
          */
         struct Base:public Interfaces::Base <Interface::ALERT>
         {
            protected:

            using Interfaces::Base <Interface::ALERT>::payload_size;

            uint16_t payload_size (Protocol::Message::Interface &itf) const
            {
               UNUSED (itf);
               return payload_size_helper <Message>();
            }
         };

         /*!
          * %Alert %Interface : %Server side implementation.
          *
          * This class provides the server side of the %Alert interface.
          */
         class Server:public InterfaceRole <Alert::Base, Interface::SERVER_ROLE>
         {
            protected:

            uint32_t _state;     //!< Alert's state
            uint32_t _enabled;   //!< Alert's enable state

            public:

            //! Constructor.
            Server();

            //! Destructor
            virtual ~Server();

            // ======================================================================
            // State API
            // ======================================================================

            /*!
             * Return the current state for all the alerts as a bitmask.
             *
             * @return  the bitmask of the alert states.
             */
            uint32_t state ();

            /*!
             * Set the state bitmask to the given @c value.
             *
             * @param [in] value    bitmask value to set the alert states.
             */
            void set_state (uint32_t value);

            /*!
             * Set the alert given by @c index to @c value.
             *
             * The alert entry @b MUST be enabled in order for the state to be set.
             *
             * @param [in] index   index of the alert to set : <tt>[0,31]</tt>.
             * @param [in] value   state to set the index to.
             *
             * @return  @c true if the alert state was set or @c false otherwise.
             */
            bool state (uint8_t index, bool value);

            /*!
             * Get the state of the alert given by @c index.
             *
             * @note This will return @c false if @c index is greater than 31.
             *
             * @param [in] index   index of the alert to get the state from : [0,31].
             *
             * @return  true if the alert is active, false otherwise.
             */
            bool state (uint8_t index);

            /*!
             * Clear all the alerts.
             */
            void clear ();

            // ======================================================================
            // Enable API
            // ======================================================================

            /*!
             * Enable alert at @c index.
             *
             * @param [in] index   index to enable the alert : [0,31].
             */
            void enable (uint8_t index);

            /*!
             * Enable all alerts.
             */
            void enableAll ();

            /*!
             * Check if alert at @c index is enabled.
             *
             * @param [in] index   index of the alert to get the enabled state : [0,31].
             *
             * @retval  <tt>true</tt> if the alert at @c index is enabled,
             * @retval  <tt>false</tt> otherwise.
             */
            bool enabled (uint8_t index);

            /*!
             * Return the bitmask of the enable state of the alerts.
             *
             * @return  the bitmask of the enable state of the alerts.
             */
            uint32_t enabled ();

            /*!
             * Set the bitmask of the enable state of the alerts.
             *
             * @param [in] value the bitmask of the enable state of the alerts to set.
             */
            void set_enabled (uint32_t value);

            /*!
             * Disable the alert at @c index.
             *
             * @param [in] index   index of the alert to disable : [0,31].
             */
            void disable (uint8_t index);

            /*!
             * Check if alert at @c index is disabled.
             *
             * @param [in] index   index of the alert to get the enable state : [0,31].
             *
             * @retval  <tt>true</tt> if the alert at @c index is disabled
             * @retval  <tt>false</tt> otherwise
             */
            bool disabled (uint8_t index);

            /*!
             * Disable all alerts.
             */
            void disableAll ();

            // =============================================================================
            // Attributes API
            // =============================================================================

            HF::Attributes::IAttribute *attribute (uint8_t uid)
            {
               return Interfaces::create_attribute (this, uid);
            }

            friend HF::Attributes::IAttribute *Interfaces::create_attribute (Alert::Server *, uint8_t);

            // ======================================================================
            // Commands
            // ======================================================================
            //! @name Commands
            //! @{

            /*!
             * Send a HAN-FUN message containing a @c Alert::STATUS_CMD, to the given
             * network address.
             *
             * @param [in] addr       the network address to send the message to.
             * @param [in] unit_type  the unit type ( @see hf_profile_uid_t ) sending the message.
             */
            void status (Protocol::Address &addr, uint16_t unit_type);

            /*!
             * Send a HAN-FUN message containing a @c Alert::STATUS_CMD, to the broadcast
             * network address.
             *
             * @param [in] unit_type  the unit type ( @see HF::Profile::UID ) sending the message.
             */
            void status (uint16_t unit_type)
            {
               Protocol::Address addr;
               status (addr, unit_type);
            }

            //! @}
            // ======================================================================

            HF::Attributes::UIDS attributes (uint8_t pack_id =
                                                HF::Attributes::Pack::MANDATORY) const
            {
               UNUSED (pack_id);
               /* *INDENT-OFF* */
               return HF::Attributes::UIDS ({ Alert::STATE_ATTR, Alert::ENABLE_ATTR });
               /* *INDENT-ON* */
            }

            protected:

            /*!
             * Create a HAN-FUN message containing a @c Alert::STATUS_CMD, to be sent to the
             * network.
             *
             * @param unit_type     unit type (i.e. profile) source for the alert status message.
             *
             * @return              a pointer to a @c Alert::Message, or @c nullptr if the message can't
             *                      be allocated.
             */
            Alert::Message *create_status (uint16_t unit_type);

         };

         /*!
          * %Alert %Interface : %Client side implementation.
          *
          * This class provides the client side of the %Alert interface.
          */
         struct Client:public InterfaceRole <Alert::Base, Interface::CLIENT_ROLE>
         {
            // ======================================================================
            // Events
            // ======================================================================
            //! @name Events
            //! @{

            /*!
             * Callback function called when a status update message is received
             * from an %Alert server.
             *
             * @param [in] source   device address the message was received from.
             * @param [in] message  message received
             */
            virtual void status (Protocol::Address &source, Message &message)
            {
               UNUSED (source);
               UNUSED (message);
            }

            //! @}
            // ======================================================================

            protected:

            Common::Result handle_command (Protocol::Packet &packet, Common::ByteArray &payload,
                                           uint16_t offset);
         };

         /*! @} */

      }  // namespace Alert

   }  // namespace Interfaces

}  // namespace HF

/*!
 * @addtogroup alert_itf
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
std::ostream &operator <<(std::ostream &stream, const HF::Interfaces::Alert::CMD command);

/*!
 * Convert the given @c attribute into a string and write it to the given @c stream.
 *
 * @param [in] stream      out stream to write the string to.
 * @param [in] attribute   attribute value to convert to a string.
 *
 * @return   <tt>stream</tt>
 */
std::ostream &operator <<(std::ostream &stream, const HF::Interfaces::Alert::Attributes attribute);

/*! @} */

#endif /* HF_ITF_ALERT_H */
