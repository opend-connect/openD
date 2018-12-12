// =============================================================================
/*!
 * @file       inc/hanfun/interfaces/simple_power_meter.h
 *
 * This file contains the definitions for the Simple Power Meter interface.
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
#ifndef HF_ITF_SIMPLE_POWER_METER_H
#define HF_ITF_SIMPLE_POWER_METER_H

#include "hanfun/common.h"

#include "hanfun/protocol.h"
#include "hanfun/interface.h"

// =============================================================================
// Configuration
// =============================================================================

#if HF_ITF_SPM_REPORT_CMD

   #if !HF_ITF_SPM_REPORT_INTERVAL_ATTR
      #define HF_ITF_SPM_REPORT_INTERVAL_ATTR   1
   #endif

#endif

#if HF_ITF_SPM_RESET_CMD

   #if !HF_ITF_SPM_ENERGY_ATTR
      #undef HF_ITF_SPM_ENERGY_ATTR
      #define HF_ITF_SPM_ENERGY_ATTR            1
   #endif

   #if !HF_ITF_SPM_ENERGY_AT_RESET_ATTR
      #undef HF_ITF_SPM_ENERGY_AT_RESET_ATTR
      #define HF_ITF_SPM_ENERGY_AT_RESET_ATTR   1
   #endif

   #if !HF_ITF_SPM_TIME_AT_RESET_ATTR
      #undef HF_ITF_SPM_TIME_AT_RESET_ATTR
      #define HF_ITF_SPM_TIME_AT_RESET_ATTR     1
   #endif

#endif

// =============================================================================
// Define
// =============================================================================

//! Helper macro used to support attribute reporting.
#define ATTR_SETTER(__type, __arg, __uid)                                              \
   {                                                                                   \
      __type old = __arg;                                                              \
                                                                                       \
      __arg = value;                                                                   \
                                                                                       \
      HF::Attributes::Attribute <__type> *old_attr =                                   \
         static_cast <HF::Attributes::Attribute <__type> *>(create_attribute (__uid)); \
      old_attr->set (old);                                                             \
                                                                                       \
      HF::Attributes::Attribute <__type> *new_attr =                                   \
         static_cast <HF::Attributes::Attribute <__type> *>(attribute (__uid));        \
                                                                                       \
      notify (*old_attr, *new_attr);                                                   \
                                                                                       \
      delete old_attr;                                                                 \
      delete new_attr;                                                                 \
   }

// =============================================================================
// API
// =============================================================================

namespace HF
{
   namespace Interfaces
   {
      // Forward declaration
      namespace SimplePowerMeter
      {
         class Server;
      }

      /*!
       * @ingroup spm_itf
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
      HF::Attributes::IAttribute *create_attribute (HF::Interfaces::SimplePowerMeter::Server *server,
                                                    uint8_t uid);

      /*!
       * This namespace contains the implementation of the Simple Power Meter interface.
       */
      namespace SimplePowerMeter
      {
         /*!
          * @addtogroup spm_itf  Simple Power Meter Interface
          * @ingroup interfaces
          *
          * This module contains the classes that define and implement the Simple Power Meter
          * interface API.
          * @{
          */
         //! Commands IDs.
         typedef enum _CMD
         {
            REPORT_CMD            = 0x01,          //!< Report command ID.
            MEASUREMENT_RESET_CMD = 0x01           //!< Measurement Reset command ID.
         } CMD;

         /*!
          * Attributes IDs.
          */
         typedef enum _Attributes
         {
            ENERGY_ATTR             = 0x01,          //!< Energy Attribute ID.
            ENERGY_AT_RESET_ATTR    = 0x02,          //!< Energy at Last Reset Attribute ID.
            TIME_AT_RESET_ATTR      = 0x03,          //!< Time at Last Reset Attribute ID.
            POWER_ATTR              = 0x04,          //!< Instantaneous Power Attribute ID.
            AVG_POWER_ATTR          = 0x05,          //!< Average Power Attribute ID.
            AVG_POWER_INTERVAL_ATTR = 0x06,          //!< Average Power Interval Attribute ID.
            VOLTAGE_ATTR            = 0x07,          //!< Voltage Attribute ID.
            CURRENT_ATTR            = 0x08,          //!< Current Attribute ID.
            FREQUENCY_ATTR          = 0x09,          //!< Frequency Attribute ID.
            POWER_FACTOR_ATTR       = 0x0A,          //!< Power Factor Attribute ID.
            REPORT_INTERVAL_ATTR    = 0x0B,          //!< Report Interval Attribute ID.
            __LAST_ATTR__           = REPORT_INTERVAL_ATTR,
         } Attributes;

         /*!
          * This represents a measurement for a given attribute.
          */
         struct Measurement
         {
            //! Minimum pack/unpack required data size.
            static constexpr uint16_t min_size = sizeof(uint8_t)      // Precision size.
                                                 + sizeof(uint32_t);  // Value size.

            uint8_t  unit;  //!< %Measurement precision/type.
            uint32_t value; //!< %Measurement value.

            //! @copydoc HF::Common::Serializable::size
            uint16_t size () const
            {
               return min_size;
            }

            //! @copydoc HF::Common::Serializable::pack
            uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const
            {
               SERIALIZABLE_CHECK (array, offset, min_size);

               offset += array.write (offset, static_cast <uint8_t>(unit));
               array.write (offset, value);

               return min_size;
            }

            //! @copydoc HF::Common::Serializable::unpack
            uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0)
            {
               SERIALIZABLE_CHECK (array, offset, min_size);

               uint8_t temp;
               offset += array.read (offset, temp);

               unit    = static_cast <Common::Precision>(temp);

               offset += array.read (offset, value);

               return min_size;
            }

            /*!
             * @copydoc HF::Attributes::IAttribute::compare
             *
             * @todo Take unit into consideration.
             */
            int compare (const Measurement &other) const
            {
               int res = value - other.value;
               return res;
            }

            /*!
             * @copydoc HF::Attributes::IAttribute::changed
             *
             * @todo Take unit into consideration.
             */
            float changed (const Measurement &other) const
            {
               return (((float) (value - other.value)) / other.value);
            }
         };

         /*!
          * Simple Meter report.
          *
          * @todo This needs a way to dynamically add only the attributes
          *       that are needed to the report.
          */
         struct Report
         {
            Measurement energy;                       //!< Energy measurement.

            Measurement last_energy;                  //!< Energy measurement at last reset.
            Measurement last_time;                    //!< Device time measurement at last reset.

            Measurement power;                        //!< Instantaneous Power measurement.
            Measurement avg_power;                    //!< Average Power measurement.

            uint16_t    avg_power_interval;           //!< Average Power Interval.

            uint8_t     power_factor;                 //!< Power Factor.

            Measurement voltage;                      //!< Voltage measurement.
            Measurement current;                      //!< Current measurement.
            Measurement frequency;                    //!< Frequency measurement.

            /*!
             * This array contains an indication of with attributes should be packed or
             * were unpacked.
             */
            std::array <bool, __LAST_ATTR__ + 1> enabled;

            Report();

            //! Minimum pack/unpack required data size.
            static constexpr uint16_t min_size = sizeof(uint8_t);  // Number of attributes.

            //! @copydoc HF::Common::Serializable::size
            uint16_t size () const;

            //! @copydoc HF::Common::Serializable::pack
            uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

            //! @copydoc HF::Common::Serializable::unpack
            uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0);
         };

         /*!
          * @copybrief HF::Interfaces::create_attribute (HF::Interfaces::SimplePowerMeter::Server *,uint8_t)
          *
          * @see HF::Interfaces::create_attribute (HF::Interfaces::SimplePowerMeter::Server *,uint8_t)
          *
          * @param [in] uid   attribute %UID to create the attribute object for.
          *
          * @retval  pointer to an attribute object
          * @retval  <tt>nullptr</tt> if the attribute UID does not exist.
          */
         HF::Attributes::IAttribute *create_attribute (uint8_t uid);

         /*!
          * Simple Power Meter Interface : Parent.
          *
          * This is the parent class for the Simple Power Meter interface implementation.
          */
         struct Base:public Interfaces::Base <Interface::SIMPLE_POWER_METER>
         {
            protected:

            Base() {}

            using Interfaces::Base <Interface::SIMPLE_POWER_METER>::payload_size;

            uint16_t payload_size (Protocol::Message::Interface &itf) const
            {
               UNUSED (itf);
               return payload_size_helper <Report>();
            }
         };

         /*!
          * Simple Power Meter Interface : Server side implementation.
          *
          * This class provides the server side of the Simple Power Meter interface.
          */
         class Server:public InterfaceRole <SimplePowerMeter::Base, Interface::SERVER_ROLE>
         {
            protected:

            /* Attributes */
#if HF_ITF_SPM_ENERGY_ATTR
            Measurement _energy;           //!< Energy measurement attribute.
#endif

#if HF_ITF_SPM_ENERGY_AT_RESET_ATTR
            Measurement _last_energy;      //!< Energy measurement at last reset attribute.
#endif

#if HF_ITF_SPM_TIME_AT_RESET_ATTR
            Measurement _last_time;        //!< Device time measurement at last reset attribute.
#endif

#if HF_ITF_SPM_POWER_ATTR
            Measurement _power;            //!< Instantaneous Power measurement attribute.
#endif

#if HF_ITF_SPM_AVG_POWER_ATTR
            Measurement _avg_power;        //!< Average Power measurement attribute.
#endif

#if HF_ITF_SPM_AVG_POWER_INTERVAL_ATTR
            uint16_t _avg_power_interval;  //!< Average Power Interval attribute.
#endif

#if HF_ITF_SPM_POWER_FACTOR_ATTR
            uint8_t _power_factor;         //!< Power Factor attribute.
#endif

#if HF_ITF_SPM_VOLTAGE_ATTR
            Measurement _voltage;          //!< Voltage measurement attribute.
#endif

#if HF_ITF_SPM_CURRENT_ATTR
            Measurement _current;          //!< Current measurement attribute.
#endif

#if HF_ITF_SPM_FREQUENCY_ATTR
            Measurement _frequency;        //!< Frequency measurement attribute.
#endif

#if HF_ITF_SPM_REPORT_CMD
            uint16_t _report_interval;     //!< Report Interval attribute.

            uint32_t _last_periodic;       //! Time in seconds of the last report message sent.
#endif

            public:

            //! Constructor
            Server();

            // =============================================================================
            // API
            // =============================================================================

            void periodic (uint32_t time);

            // ======================================================================
            // Getters & Setters
            // ======================================================================
            //! @name Getters & Setters
            //! @{

#if HF_ITF_SPM_ENERGY_ATTR
            /*!
             * Retrieve the energy measurement value for the meter.
             *
             * @return  the current measurement for the energy attribute.
             */
            Measurement energy ()
            {
               return _energy;
            }

            /*!
             * Set the energy measurement value for the meter.
             *
             * @param value   the measurement to set as current.
             */
            void energy (Measurement &value)
            {
               ATTR_SETTER (Measurement, _energy, ENERGY_ATTR);
            }
#endif

#if HF_ITF_SPM_ENERGY_AT_RESET_ATTR
            /*!
             * Retrieve the energy measurement value at the last reset.
             *
             * @return     the energy measurement value at the last reset.
             */
            Measurement last_energy ()
            {
               return _last_energy;
            }

            /*!
             * Set the energy measurement value at the last reset.
             *
             * @param value     the energy measurement value.
             */
            void last_energy (Measurement &value)
            {
               ATTR_SETTER (Measurement, _last_energy, ENERGY_AT_RESET_ATTR);
            }
#endif

#if HF_ITF_SPM_TIME_AT_RESET_ATTR
            /*!
             * Retrieve the device time value at the last reset.
             *
             * @return      the device time value at the last reset.
             */
            Measurement last_time ()
            {
               return _last_time;
            }

            /*!
             * Set the device time value at the last reset.
             *
             * @param value     the device time value.
             */
            void last_time (Measurement &value)
            {
               ATTR_SETTER (Measurement, _last_time, TIME_AT_RESET_ATTR);
            }
#endif

#if HF_ITF_SPM_POWER_ATTR
            /*!
             * Retrieve the instantaneous power measurement value for the meter.
             *
             * @return  the current value for the instantaneous power attribute.
             */
            Measurement power ()
            {
               return _power;
            }

            /*!
             * Set the instantaneous power measurement value for the meter.
             *
             * @param value   the measurement value to set the instantaneous power attribute to.
             */
            void power (Measurement &value)
            {
               ATTR_SETTER (Measurement, _power, POWER_ATTR);
            }
#endif

#if HF_ITF_SPM_AVG_POWER_ATTR
            /*!
             * Retrieve the average power measurement value for the meter.
             *
             * @return  the current measurement for the average power attribute.
             */
            Measurement avg_power ()
            {
               return _avg_power;
            }

            /*!
             * Set the average power measurement value for the meter.
             *
             * @param value   the measurement value to set the average power attribute to.
             */
            void avg_power (Measurement &value)
            {
               ATTR_SETTER (Measurement, _avg_power, AVG_POWER_ATTR);
            }
#endif

#if HF_ITF_SPM_AVG_POWER_INTERVAL_ATTR
            /*!
             * Retrieve the average power interval value for the meter.
             *
             * @return  the current value for the average power interval attribute.
             */
            uint16_t avg_power_interval ()
            {
               return _avg_power_interval;
            }

            /*!
             * Set the average power interval measurement value for the meter.
             *
             * @param value   the measurement value to set the average power interval attribute to.
             */
            void avg_power_interval (uint16_t value)
            {
               ATTR_SETTER (uint16_t, _avg_power_interval, AVG_POWER_INTERVAL_ATTR);
            }
#endif

#if HF_ITF_SPM_POWER_FACTOR_ATTR
            /*!
             * Retrieve the power factor value for the meter.
             *
             * @return  the value for the power factor attribute.
             */
            uint8_t power_factor ()
            {
               return _power_factor;
            }

            /*!
             * Set the power factor measurement value for the meter.
             *
             * @param value   the measurement value to set the power factor attribute to.
             */
            void power_factor (uint8_t value)
            {
               ATTR_SETTER (uint8_t, _power_factor, POWER_FACTOR_ATTR);
            }
#endif

#if HF_ITF_SPM_VOLTAGE_ATTR
            /*!
             * Retrieve the voltage measurement value for the meter.
             *
             * @return  the current measurement for the voltage attribute.
             */
            Measurement voltage ()
            {
               return _voltage;
            }

            /*!
             * Set the voltage measurement value for the meter.
             *
             * @param value   the measurement value to set the voltage attribute to.
             */
            void voltage (Measurement &value)
            {
               ATTR_SETTER (Measurement, _voltage, VOLTAGE_ATTR);
            }
#endif

#if HF_ITF_SPM_CURRENT_ATTR
            /*!
             * Retrieve the current measurement value for the meter.
             *
             * @return  the measurement for the current attribute.
             */
            Measurement current ()
            {
               return _current;
            }

            /*!
             * Set the current measurement value for the meter.
             *
             * @param value   the measurement value to set the current attribute to.
             */
            void current (Measurement &value)
            {
               ATTR_SETTER (Measurement, _current, CURRENT_ATTR);
            }
#endif

#if HF_ITF_SPM_FREQUENCY_ATTR
            /*!
             * Retrieve the frequency measurement value for the meter.
             *
             * @return  the measurement for the frequency attribute.
             */
            Measurement frequency ()
            {
               return _frequency;
            }

            /*!
             * Set the frequency energy measurement value for the meter.
             *
             * @param value   the measurement value to set the frequency attribute to.
             */
            void frequency (Measurement &value)
            {
               ATTR_SETTER (Measurement, _frequency, FREQUENCY_ATTR);
            }
#endif

#if HF_ITF_SPM_REPORT_CMD
            /*!
             * Retrieve the report interval value for the meter.
             *
             * @return  the value for the report interval attribute.
             */
            uint16_t report_interval ()
            {
               return _report_interval;
            }

            /*!
             * Set the report interval value for the meter.
             *
             * @param value   the value to set the report interval attribute to.
             */
            void report_interval (uint16_t value)
            {
               ATTR_SETTER (uint16_t, _report_interval, REPORT_INTERVAL_ATTR);
            }
#endif

            //! @}

            // =============================================================================
            // Attribute API
            // =============================================================================

            HF::Attributes::IAttribute *attribute (uint8_t uid);

            HF::Attributes::UIDS attributes (uint8_t pack_id = HF::Attributes::Pack::MANDATORY) const;

            friend HF::Attributes::IAttribute *Interfaces::create_attribute (SimplePowerMeter::Server *, uint8_t);

            protected:

            /*!
             * Create a report message.
             *
             * @return  message to send or @c nullptr if the message cannot be created.
             */
            virtual Report *report ();
         };

         /*!
          * Simple Power Meter Interface : Client side implementation.
          *
          * This class provides the client side of the Simple Power Meter interface.
          */
         struct Client:public InterfaceRole <SimplePowerMeter::Base, Interface::CLIENT_ROLE>
         {
            // ======================================================================
            // Events
            // ======================================================================
            //! @name Events
            //! @{

            /*!
             * Receive a report message from a server.
             *
             * @param [in] source   device address that sent the report.
             * @param [in] report   the report received from the server.
             */
            virtual void report (Protocol::Address &source, Report &report)
            {
               UNUSED (source);
               UNUSED (report);
            }

            //! @}
            // =============================================================================

            protected:

            Common::Result handle_command (Protocol::Packet &packet, Common::ByteArray &payload,
                                           uint16_t offset);
         };

         /*! @} */

      }  // namespace SimplePowerMeter

   }  // namespace Interfaces

}   // namespace HF

/*!
 * @addtogroup spm_itf
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
std::ostream &operator <<(std::ostream &stream, const HF::Interfaces::SimplePowerMeter::CMD command);

/*!
 * Convert the given @c attribute into a string and write it to the given @c stream.
 *
 * @param [in] stream      out stream to write the string to.
 * @param [in] attribute   attribute value to convert to a string.
 *
 * @return   <tt>stream</tt>
 */
std::ostream &operator <<(std::ostream &stream, const HF::Interfaces::SimplePowerMeter::Attributes attribute);

/*! @} */

#endif /* HF_ITF_SIMPLE_POWER_METER */
