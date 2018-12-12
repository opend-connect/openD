// =============================================================================
/*!
 * @file       inc/hanfun/interfaces/on_off.h
 *
 * This file contains the definitions for the OnOff interface.
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

#ifndef HF_ITF_ON_OFF_H
#define HF_ITF_ON_OFF_H

#include "hanfun/protocol.h"
#include "hanfun/interface.h"

namespace HF
{
   namespace Interfaces
   {
      // Forward declaration.
      namespace OnOff
      {
         class Server;
      }

      /*!
       * @ingroup on_off_itf
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
      HF::Attributes::IAttribute *create_attribute (OnOff::Server *server, uint8_t uid);

      /*!
       * This namespace contains the implementation of the On-Off interface.
       */
      namespace OnOff
      {
         /*!
          * @addtogroup on_off_itf  On-Off Interface
          * @ingroup interfaces
          *
          * This module contains the classes that define and implement the On-Off interface API.
          * @{
          */
         //! Command IDs.
         typedef enum _CMD
         {
            ON_CMD       = 0x01, //!< On Command ID.
            OFF_CMD      = 0x02, //!< Off Command ID.
            TOGGLE_CMD   = 0x03, //!< Toggle Command ID.
            __LAST_CMD__ = TOGGLE_CMD,
         } CMD;

         //! Attributes
         typedef enum _Attributes
         {
            STATE_ATTR    = 0x01, //!< State attribute UID.
            __LAST_ATTR__ = STATE_ATTR,
         } Attributes;

         /*!
          * Helper class to handle the %State attribute for the On-Off interface.
          */
         struct State:public HF::Attributes::Attribute <bool>
         {
            static constexpr uint8_t ID        = STATE_ATTR;  //!< Attribute UID.
            static constexpr bool    WRITABBLE = false;       //!< Attribute Read/Write

            State(bool state = false, HF::Interface *owner = nullptr):
               Attribute <bool>(Interface::ON_OFF, ID, owner, state, WRITABBLE)
            {}
         };

         /*!
          * @copybrief HF::Interfaces::create_attribute (HF::Interfaces::OnOff::Server *,uint8_t)
          *
          * @see HF::Interfaces::create_attribute (HF::Interfaces::OnOff::Server *,uint8_t)
          *
          * @param [in] uid   attribute %UID to create the attribute object for.
          *
          * @retval  pointer to an attribute object
          * @retval  <tt>nullptr</tt> if the attribute UID does not exist.
          */
         HF::Attributes::IAttribute *create_attribute (uint8_t uid);

         /*!
          * On-Off Interface : Parent.
          *
          * This is the parent class for the On-Off interface implementation.
          */
         struct Base:public Interfaces::Base <Interface::ON_OFF>
         {};

         /*!
          * On-Off %Interface : %Server side implementation.
          *
          * This class provides the server side of the On-Off interface.
          */
         class Server:public InterfaceRole <OnOff::Base, Interface::SERVER_ROLE>
         {
            protected:

            /*!
             * Current server state.
             *
             *  * @c true : the interface is ON.
             *  * @c false: the interface is OFF.
             */
            bool _state;

            public:

            //! Constructor
            Server():_state (false) {}

            //! Destructor
            virtual ~Server() {}

            // ======================================================================
            // Events
            // ======================================================================
            //! @name Events
            //! @{

            /*!
             * Callback that is called when a @c ON_CMD message is received.
             *
             * @param [in] source   device address that sent the command.
             */
            virtual void on (Protocol::Address &source);

            /*!
             * Callback that is called when a @c OFF_CMD message is received.
             *
             * @param [in] source   device address that sent the command.
             */
            virtual void off (Protocol::Address &source);

            /*!
             * Callback that is called when a @c TOGGLE_CMD message is received.
             *
             * @param [in] source   device address that sent the command.
             */
            virtual void toggle (Protocol::Address &source);

            //! @}

            // =============================================================================
            // Get/Set API.
            // =============================================================================

            /*!
             * Setter : set the state attribute to given value.
             *
             * @param state   @c true the interface is on, @c false the interface is off.
             */
            void state (bool state);

            /*!
             * Getter : get the current state of the interface :
             *    * @c true the interface is ON.
             *    * @c false the interface is OFF.
             *
             * @retval  <tt>true</tt> if the interface is ON.
             * @retval  <tt>false</tt> if the interface is OFF.
             */
            bool state ();

            // =============================================================================
            // Attribute API.
            // =============================================================================

            HF::Attributes::IAttribute *attribute (uint8_t uid)
            {
               return Interfaces::create_attribute (this, uid);
            }

            HF::Attributes::UIDS attributes (uint8_t pack_id = HF::Attributes::Pack::MANDATORY) const
            {
               UNUSED (pack_id);
               /* *INDENT-OFF* */
               return HF::Attributes::UIDS ({ OnOff::STATE_ATTR });
               /* *INDENT-ON* */
            }

            friend HF::Attributes::IAttribute *Interfaces::create_attribute (OnOff::Server *, uint8_t);

            protected:

            Common::Result handle_command (Protocol::Packet &packet, Common::ByteArray &payload,
                                           uint16_t offset);
         };

         /*!
          * On-Off %Interface : %Client side implementation.
          *
          * This class provides the client side of the On-Off interface.
          */
         struct Client:public InterfaceRole <OnOff::Base, Interface::CLIENT_ROLE>
         {
            // ======================================================================
            // Commands
            // ======================================================================
            //! @name Commands
            //! @{

            /*!
             * Send a @c OnOff::ON_CMD message to the device at the given address.
             *
             * @param addr    the address of the device to send the message to.
             */
            void on (Protocol::Address &addr);

            /*!
             * Send a @c OnOff::ON_CMD message to the broadcast address.
             */
            void on ()
            {
               Protocol::Address addr;
               on (addr);
            }

            /*!
             * Send a @c OnOff::OFF_CMD message to the device at the given address.
             *
             * @param addr    the address of the device to send the message to.
             */
            void off (Protocol::Address &addr);

            /*!
             * Send a @c OnOff::OFF_CMD message to the broadcast address.
             */
            void off ()
            {
               Protocol::Address addr;
               off (addr);
            }

            /*!
             * Send a @c OnOff::TOGGLE_CMD message to the device at the given address.
             *
             * @param addr    the address of the device to send the message to.
             */
            void toggle (Protocol::Address &addr);

            /*!
             * Send a @c OnOff::TOGGLE_CMD message to the broadcast address.
             */
            void toggle ()
            {
               Protocol::Address addr;
               toggle (addr);
            }

            //! @}
            // =============================================================================
         };

         /*! @} */

      }  // namespace OnOff

   }  // namespace Interfaces

}   // namespace HF

/*!
 * @addtogroup on_off_itf
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
std::ostream &operator <<(std::ostream &stream, const HF::Interfaces::OnOff::CMD command);

/*!
 * Convert the given @c attribute into a string and write it to the given @c stream.
 *
 * @param [in] stream      out stream to write the string to.
 * @param [in] attribute   attribute value to convert to a string.
 *
 * @return   <tt>stream</tt>
 */
std::ostream &operator <<(std::ostream &stream, const HF::Interfaces::OnOff::Attributes attribute);

/*! @} */

#endif /* HF_ITF_ON_OFF_H */
