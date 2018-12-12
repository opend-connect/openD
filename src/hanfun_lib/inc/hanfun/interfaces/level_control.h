// =============================================================================
/*!
 * @file       inc/hanfun/interfaces/level_control.h
 *
 * This file contains the definitions for the Level Control interface.
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

#ifndef HF_ITF_LEVEL_CONTROL_H
#define HF_ITF_LEVEL_CONTROL_H

#include "hanfun/protocol.h"
#include "hanfun/interface.h"

namespace HF
{
   namespace Interfaces
   {
      namespace LevelControl
      {
         class Server;
      }

      /*!
       * @ingroup level_ctl_itf
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
      HF::Attributes::IAttribute *create_attribute (HF::Interfaces::LevelControl::Server *server,
                                                    uint8_t uid);

      /*!
       * This namespace contains the implementation of the Level Control interface
       */
      namespace LevelControl
      {
         /*!
          * @addtogroup level_ctl_itf  Level Control Interface
          * @ingroup interfaces
          *
          * This module contains the classes that define and implement the %Level Control
          * interface API.
          * @{
          */

         //! Command IDs.
         typedef enum _CMD
         {
            SET_LEVEL_CMD = 0x01,      //!< Set Level Command ID.
            __LAST_CMD__  = SET_LEVEL_CMD
         } CMD;

         //! Attributes
         typedef enum _Attributes
         {
            LEVEL_ATTR    = 0x01,      //!< State attribute UID.
            __LAST_ATTR__ = LEVEL_ATTR,
         } Attributes;

         struct Message
         {
            //! Level value to set at the server side.
            uint8_t level;

            Message(uint8_t level = 0):level (level) {}

            //! Minimum pack/unpack required data size.
            static constexpr uint16_t min_size = sizeof(uint8_t);

            //! \see HF::Serializable::size.
            uint16_t size () const
            {
               return min_size;
            }

            //! \see HF::Serializable::pack.
            uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const
            {
               SERIALIZABLE_CHECK (array, offset, min_size);

               array.write (offset, level);

               return min_size;
            }

            //! \see HF::Serializable::unpack.
            uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0)
            {
               SERIALIZABLE_CHECK (array, offset, min_size);

               array.read (offset, level);

               return min_size;
            }
         };

         /*!
          * Helper class to handle the %Level attribute for the Level Control interface.
          */
         struct Level:public HF::Attributes::Attribute <uint8_t>
         {
            static constexpr uint8_t ID        = LEVEL_ATTR;
            static constexpr bool    WRITABBLE = true;

            Level(uint8_t level = 0, HF::Interface *owner = nullptr):
               Attribute <uint8_t>(Interface::LEVEL_CONTROL, ID, owner, level, WRITABBLE)
            {}
         };

         /*!
          * @copybrief HF::Interfaces::create_attribute (HF::Interfaces::LevelControl::Server *,uint8_t)
          *
          * @see HF::Interfaces::create_attribute (HF::Interfaces::LevelControl::Server *,uint8_t)
          *
          * @param [in] uid   attribute %UID to create the attribute object for.
          *
          * @retval  pointer to an attribute object
          * @retval  <tt>nullptr</tt> if the attribute UID does not exist.
          */
         HF::Attributes::IAttribute *create_attribute (uint8_t uid);

         /*!
          * Level Control Interface : Parent.
          *
          * This is the parent class for the Level Control interface implementation.
          */
         struct Base:public Interfaces::Base <Interface::LEVEL_CONTROL>
         {
            protected:

            Base() {}

            using Interfaces::Base <Interface::LEVEL_CONTROL>::payload_size;

            uint16_t payload_size (Protocol::Message::Interface &itf) const
            {
               UNUSED (itf);
               return payload_size_helper <Level>();
            }

            /*!
             * Make sure level percentage values is in range [0,100].
             *
             * @param [in] value    reference to the value to check and fix.
             */
            void check_and_fix (float &value)
            {
               if (value < 0)
               {
                  value = 0;
               }
               else if (value > 100)
               {
                  value = 100;
               }
            }
         };

         /*!
          * %Level Control %Interface : %Server side implementation.
          *
          * This class provides the server side of the %Level Control interface.
          *
          * @remarks
          *
          * The @c _level attribute represents the level value in percentage in
          * the [0,255] range, i.e., the <tt>0 == 0%</tt> and the <tt>255 == 100%</tt>.
          *
          * Use the overloaded level functions with float attributes to send the values
          * in the [0,100] range and have them converted into the proper range.
          */
         class Server:public InterfaceRole <LevelControl::Base, Interface::SERVER_ROLE>
         {
            protected:

            //! Current level value.
            uint8_t _level;

            public:

            //! Constructor
            Server():_level (0) {}

            // ======================================================================
            // API
            // ======================================================================

            /*!
             * Getter for the current level.
             *
             * @return  the current level.
             */
            uint8_t level ();

            /*!
             * Setter for the server level.
             *
             * @param [in] new_level  the new level value to use.
             */
            void level (uint8_t new_level);

            /*!
             * Setter for the server level (unsigned float).
             *
             * @remark This method converts the given @c new_level percentage value in the
             * range of [0,100] to the range used by the interface [0-255].
             *
             * @param [in] new_level  the new level value to use.
             */
            void level (float new_level);

            // =============================================================================
            // Events
            // =============================================================================
            //! @name Events
            //! @{

            /*!
             * Callback for a @c SET_ATTR_REQ or @c SET_LEVEL_CMD message,
             * when the level value is changed.
             *
             * @remark When this method is called the attribute has already been updated to
             * the new value.
             *
             * @param [in] source       device address the change was received from.
             * @param [in] old_level    the old level value to used.
             * @param [in] new_level    the new level value to use.
             */
            virtual void level_change (Protocol::Address &source, uint8_t old_level, uint8_t new_level);

            //! @}
            // =============================================================================

            // =============================================================================
            // Attributes API
            // =============================================================================

            HF::Attributes::IAttribute *attribute (uint8_t uid)
            {
               return Interfaces::create_attribute (this, uid);
            }

            HF::Attributes::UIDS attributes (uint8_t pack_id = HF::Attributes::Pack::MANDATORY) const
            {
               UNUSED (pack_id);
               /* *INDENT-OFF* */
               return HF::Attributes::UIDS ({ LevelControl::LEVEL_ATTR });
               /* *INDENT-ON* */
            }

            friend HF::Attributes::IAttribute *Interfaces::create_attribute (LevelControl::Server *, uint8_t);

            protected:

            Common::Result handle_attribute (Protocol::Packet &packet, Common::ByteArray &payload,
                                             uint16_t offset);

            Common::Result handle_command (Protocol::Packet &packet, Common::ByteArray &payload,
                                           uint16_t offset);
         };

         /*!
          * %Level Control %Interface : %Client side implementation.
          *
          * This class provides the client side of the %Level Control interface.
          */
         class Client:public InterfaceRole <LevelControl::Base, Interface::CLIENT_ROLE>
         {
            public:

            // ======================================================================
            // Commands
            // ======================================================================
            //! @name Commands
            //! @{

            /*!
             * Send a @c SET_LEVEL_CMD to the given address to set the level
             * at @c new_level.
             *
             * @param [in] addr        network address to send the message to.
             * @param [in] new_level   level value to send in the message.
             */
            void level (Protocol::Address &addr, uint8_t new_level);

            /*!
             * Send a @c SET_LEVEL_CMD to broadcast network address to set the level
             * at @c new_level.
             *
             * @param [in] new_level    level value to send in the message.
             */
            void level (uint8_t new_level)
            {
               Protocol::Address addr;
               level (addr, new_level);
            }

            /*!
             * @copydoc Client::level(Protocol::Address &,uint8_t)
             *
             * @remark This method converts the given @c new_level percentage value in the
             * range of [0,100] to the range used by the interface [0-255].
             */
            void level (Protocol::Address &addr, float new_level);

            /*!
             * @copydoc Client::level(uint8_t)
             */
            void level (float new_level)
            {
               Protocol::Address addr;
               level (addr, new_level);
            }

            //! @}
            // =============================================================================
         };

         /*! @} */

      }  // namespace LevelControl

   }  // namespace Interfaces

}   // namespace HF

/*!
 * @addtogroup level_ctl_itf
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
std::ostream &operator <<(std::ostream &stream, const HF::Interfaces::LevelControl::CMD command);

/*!
 * Convert the given @c attribute into a string and write it to the given @c stream.
 *
 * @param [in] stream      out stream to write the string to.
 * @param [in] attribute   attribute value to convert to a string.
 *
 * @return   <tt>stream</tt>
 */
std::ostream &operator <<(std::ostream &stream, const HF::Interfaces::LevelControl::Attributes attribute);

/*! @} */

#endif /* LEVEL_CONTROL_H_ */
