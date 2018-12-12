// =============================================================================
/*!
 * @file       inc/hanfun/interfaces/simple_humidity.h
 *
 * This file contains the definitions for the Simple Humidity interface.
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
#ifndef HF_ITF_SIMPLE_HUMIDITY_H
#define HF_ITF_SIMPLE_HUMIDITY_H

#include "hanfun/common.h"

#include "hanfun/interface.h"

namespace HF
{
   namespace Interfaces
   {
      namespace SimpleHumidity
      {
         class Server;
      }

      /*!
       * @ingroup simple_humidity_itf
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
      HF::Attributes::IAttribute *create_attribute (SimpleHumidity::Server *server, uint8_t uid);

      /*!
       * This namespace contains the implementation of the Simple Humidity interface
       */
      namespace SimpleHumidity
      {
         /*!
          * @addtogroup simple_humidity_itf  Simple Humidity Interface
          * @ingroup interfaces
          *
          * This module contains the classes that define and implement the Simple Humidity
          * interface API.
          * @{
          */

         //! Attributes
         typedef enum _Attributes
         {
            VALUE_ATTR     = 0x01, //!< Measured humidity attribute UID.
            TOLERANCE_ATTR = 0x02, //!< Tolerance attribute UID.
            __LAST_ATTR__  = TOLERANCE_ATTR,
         } Attributes;

         /*!
          * Helper class to handle the Measured Humidity attribute for the
          * Simple Humidity interface.
          */
         struct Humidity:public HF::Attributes::Attribute <uint16_t>
         {
            static constexpr uint8_t ID        = VALUE_ATTR;
            static constexpr bool    WRITABBLE = false;

            Humidity(uint16_t value = 0, HF::Interface *owner = nullptr):
               Attribute <uint16_t>(Interface::SIMPLE_HUMIDITY, ID, owner, value, WRITABBLE)
            {}
         };

         /*!
          * Helper class to handle the Tolerance attribute for the Simple Humidity interface.
          */
         struct Tolerance:public HF::Attributes::Attribute <uint16_t>
         {
            static constexpr uint8_t ID        = TOLERANCE_ATTR;
            static constexpr bool    WRITABBLE = false;

            Tolerance(uint16_t value = 0, HF::Interface *owner = nullptr):
               Attribute <uint16_t>(Interface::SIMPLE_HUMIDITY, ID, owner, value, WRITABBLE)
            {}
         };

         /*!
          * @copybrief HF::Interfaces::create_attribute (HF::Interfaces::SimpleHumidity::Server *,uint8_t)
          *
          * @see HF::Interfaces::create_attribute (HF::Interfaces::SimpleHumidity::Server *,uint8_t)
          *
          * @param [in] uid   attribute %UID to create the attribute object for.
          *
          * @retval  pointer to an attribute object
          * @retval  <tt>nullptr</tt> if the attribute UID does not exist.
          */
         inline HF::Attributes::IAttribute *create_attribute (uint8_t uid)
         {
            return Interfaces::create_attribute (static_cast <SimpleHumidity::Server *>(nullptr), uid);
         }

         /*!
          * Simple Humidity %Interface : Parent.
          *
          * This is the parent class for the Simple Humidity interface implementation.
          */
         struct Base:public Interfaces::Base <Interface::SIMPLE_HUMIDITY>
         {
            protected:

            Base()
            {}
         };

         /*!
          * Simple Humidity %Interface : %Server side interface.
          *
          * This class provides the API for server side of the Simple Humidity interface.
          */
         class Server:public InterfaceRole <SimpleHumidity::Base, Interface::SERVER_ROLE>
         {
            protected:

            //! Current measured humidity.
            uint16_t _value;

            const uint16_t _tolerance;

            public:

            //! Constructor
            Server(uint16_t tolerance = 0):_value (0), _tolerance (tolerance)
            {}

            virtual ~Server() {}

            // ======================================================================
            // API
            // ======================================================================

            /*!
             * Getter for the current measured humidity.
             *
             * @return  the current measured humidity.
             */
            uint16_t humidity ();

            /*!
             * Setter for the current measured humidity.
             *
             * @param [in] __value  the new humidity value to use.
             */
            void humidity (uint16_t __value);

            /*!
             * Getter for the tolerance attribute.
             *
             * @return  the tolerance value.
             */
            uint16_t tolerance ();

            // =============================================================================
            // Attributes API
            // =============================================================================

            HF::Attributes::IAttribute *attribute (uint8_t uid)
            {
               return Interfaces::create_attribute (this, uid);
            }

            HF::Attributes::UIDS attributes (uint8_t pack_id = HF::Attributes::Pack::MANDATORY) const;

            friend HF::Attributes::IAttribute *Interfaces::create_attribute (
               SimpleHumidity::Server *, uint8_t);
         };

         /*!
          * %Level Control %Interface : %Client side implementation.
          *
          * This class provides the client side of the %Level Control interface.
          */
         class Client:public InterfaceRole <SimpleHumidity::Base, Interface::CLIENT_ROLE>
         {
            public:

            // ======================================================================
            // Commands
            // ======================================================================
            //! @name Commands
            //! @{

            /*!
             * Send a @c GET_ATTR_PACK_REQ to the given address to get the values
             * for all the attributes in the server.
             *
             * @param [in] addr        network address to send the message to.
             */
            void read_all (Protocol::Address &addr);

            /*!
             * Send a @c GET_ATTR_REQ to the given address to get the current humidity.
             *
             * @tparam [in] _Attribute  attribute UID to read from the server.
             * @param  [in] addr        network address to send the message to.
             */
            template<Attributes _Attribute>
            void read (Protocol::Address &addr)
            {
               Protocol::Message message;

               message.itf.role   = SERVER_ROLE;
               message.itf.id     = SimpleHumidity::Client::uid ();
               message.itf.member = _Attribute;
               message.type       = Protocol::Message::GET_ATTR_REQ;

               send (addr, message);
            }

            //! @}
            // ======================================================================

            // ======================================================================
            // Events
            // ======================================================================
            //! @name Events
            //! @{

            virtual void read_resp (const Protocol::Address &addr,
                                    const HF::Attributes::Attribute <uint16_t> &attr)
            {
               UNUSED (addr);
               UNUSED (attr);
            }

            //! @}
            // ======================================================================

            protected:

            Common::Result handle_attribute (Protocol::Packet &packet, Common::ByteArray &payload,
                                             uint16_t offset);

         };

         /*! @} */
      }
   }
}

#endif /* HF_ITF_SIMPLE_HUMIDITY_H */
