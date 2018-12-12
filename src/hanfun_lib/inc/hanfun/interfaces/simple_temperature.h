// =============================================================================
/*!
 * @file       inc/hanfun/interfaces/simple_temperature.h
 *
 * This file contains the definitions for the Simple Temperature interface.
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
#ifndef HF_ITF_SIMPLE_TEMPERATURE_H
#define HF_ITF_SIMPLE_TEMPERATURE_H

#include "hanfun/common.h"

#include "hanfun/interface.h"

namespace HF
{
   namespace Interfaces
   {
      namespace SimpleTemperature
      {
         class Server;
      }

      /*!
       * @ingroup simple_temp_itf
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
      HF::Attributes::IAttribute *create_attribute (SimpleTemperature::Server *server, uint8_t uid);

      /*!
       * This namespace contains the implementation of the Simple Temperature interface
       */
      namespace SimpleTemperature
      {
         /*!
          * @addtogroup simple_temp_itf  Simple Temperature Interface
          * @ingroup interfaces
          *
          * This module contains the classes that define and implement the Simple Temperature
          * interface API.
          * @{
          */

         //! Attributes
         typedef enum _Attributes
         {
            VALUE_ATTR     = 0x01, //!< Measured temperature attribute UID.
            MINIMUM_ATTR   = 0x02, //!< Minimum measured temperature attribute UID.
            MAXIMUM_ATTR   = 0x03, //!< Maximum measured temperature attribute UID.
            TOLERANCE_ATTR = 0x04, //!< Tolerance attribute UID.
            __LAST_ATTR__  = TOLERANCE_ATTR,
         } Attributes;

         /*!
          * Helper class to handle the Measured Temperature attribute for the
          * Simple Temperature interface.
          */
         struct Temperature:public HF::Attributes::Attribute <int16_t>
         {
            static constexpr uint8_t ID        = VALUE_ATTR;
            static constexpr bool    WRITABBLE = false;

            Temperature(int16_t value = 0, HF::Interface *owner = nullptr):
               Attribute <int16_t>(Interface::SIMPLE_TEMPERATURE, ID, owner, value, WRITABBLE)
            {}
         };

         /*!
          * Helper class to handle the Minimum Measured Temperature attribute for the
          * Simple Temperature interface.
          */
         struct MininumTemperature:public HF::Attributes::Attribute <int16_t>
         {
            static constexpr uint8_t ID        = MINIMUM_ATTR;
            static constexpr bool    WRITABBLE = false;

            MininumTemperature(int16_t value = 0, HF::Interface *owner = nullptr):
               Attribute <int16_t>(Interface::SIMPLE_TEMPERATURE, ID, owner, value, WRITABBLE)
            {}
         };

         /*!
          * Helper class to handle the Maximum Measured Temperature attribute for the
          * Simple Temperature interface.
          */
         struct MaximumTemperature:public HF::Attributes::Attribute <int16_t>
         {
            static constexpr uint8_t ID        = MAXIMUM_ATTR;
            static constexpr bool    WRITABBLE = false;

            MaximumTemperature(int16_t value = 0, HF::Interface *owner = nullptr):
               Attribute <int16_t>(Interface::SIMPLE_TEMPERATURE, ID, owner, value, WRITABBLE)
            {}
         };

         /*!
          * Helper class to handle the Tolerance attribute for the Simple Temperature interface.
          */
         struct Tolerance:public HF::Attributes::Attribute <uint16_t>
         {
            static constexpr uint8_t ID        = TOLERANCE_ATTR;
            static constexpr bool    WRITABBLE = false;

            Tolerance(uint16_t value = 0, HF::Interface *owner = nullptr):
               Attribute <uint16_t>(Interface::SIMPLE_TEMPERATURE, ID, owner, value, WRITABBLE)
            {}
         };

         /*!
          * @copybrief HF::Interfaces::create_attribute (HF::Interfaces::SimpleTemperature::Server *,uint8_t)
          *
          * @see HF::Interfaces::create_attribute (HF::Interfaces::SimpleTemperature::Server *,uint8_t)
          *
          * @param [in] uid   attribute %UID to create the attribute object for.
          *
          * @retval  pointer to an attribute object
          * @retval  <tt>nullptr</tt> if the attribute UID does not exist.
          */
         inline HF::Attributes::IAttribute *create_attribute (uint8_t uid)
         {
            return Interfaces::create_attribute (static_cast <SimpleTemperature::Server *>(nullptr), uid);
         }

         /*!
          * Simple Temperature %Interface : Parent.
          *
          * This is the parent class for the Simple Temperature interface implementation.
          */
         struct Base:public Interfaces::Base <Interface::SIMPLE_TEMPERATURE>
         {
            protected:

            Base()
            {}
         };

         /*!
          * Simple Temperature %Interface : %Server side interface.
          *
          * This class provides the API for server side of the Simple Temperature interface.
          */
         class Server:public InterfaceRole <SimpleTemperature::Base, Interface::SERVER_ROLE>
         {
            protected:

            //! Current measured temperature.
            int16_t _value;

            const int16_t  _minimum;   //!< Minimum measurable temperature.
            const int16_t  _maximum;   //!< Maximum measurable temperature.
            const uint16_t _tolerance; //!< Tolerance.

            public:

            /*!
             * Constructor
             *
             * @param [in] minimum     Minimum measurable temperature.
             * @param [in] maximum     Maximum measurable temperature.
             * @param [in] tolerance   Tolerance.
             */
            Server(int16_t minimum = std::numeric_limits <int16_t>::min (),
                   int16_t maximum = std::numeric_limits <int16_t>::max (),
                   int16_t tolerance = 0):
               _value (0), _minimum (minimum), _maximum (maximum),
               _tolerance (tolerance)
            {}

            virtual ~Server() {}

            // ======================================================================
            // API
            // ======================================================================

            /*!
             * Getter for the current measured temperature.
             *
             * @return  the current measured temperature.
             */
            int16_t temperature ();

            /*!
             * Setter for the current measured temperature.
             *
             * @param [in] __value  the new temperature value to use.
             */
            void temperature (int16_t __value);

            /*!
             * Getter for the minimum measurable temperature.
             *
             * @return  the minimum measurable temperature.
             */
            int16_t minimum_temperature ();

            /*!
             * Getter for the maximum measurable temperature.
             *
             * @return  the maximum measurable temperature.
             */
            int16_t maximum_temperature ();

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
               SimpleTemperature::Server *, uint8_t);
         };

         /*!
          * %Level Control %Interface : %Client side implementation.
          *
          * This class provides the client side of the %Level Control interface.
          */
         class Client:public InterfaceRole <SimpleTemperature::Base, Interface::CLIENT_ROLE>
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
             * Send a @c GET_ATTR_REQ to the given address to get the current temperature.
             *
             * @tparam [in] _Attribute  attribute UID to read from the server.
             * @param  [in] addr        network address to send the message to.
             */
            template<Attributes _Attribute>
            void read (Protocol::Address &addr)
            {
               Protocol::Message message;

               message.itf.role   = SERVER_ROLE;
               message.itf.id     = SimpleTemperature::Client::uid ();
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
                                    const HF::Attributes::Attribute <int16_t> &attr)
            {
               UNUSED (addr);
               UNUSED (attr);
            }

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

#endif /* HF_ITF_SIMPLE_TEMPERATURE_H */
