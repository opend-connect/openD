// =============================================================================
/*!
 * @file       inc/hanfun/core/attribute_reporting.h
 *
 * This file contains the definitions for the core Attribute Reporting Service
 * in HAN-FUN.
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
#ifndef HF_CORE_ATTRIBUTE_REPORTING_H
#define HF_CORE_ATTRIBUTE_REPORTING_H

#include "hanfun/common.h"
#include "hanfun/core.h"

#include "hanfun/attributes.h"

namespace HF
{
   namespace Core
   {
      // Forward declaration.
      namespace AttributeReporting
      {
         struct IServer;
      }  // namespace AttributeReporting

      /*!
       * @ingroup attr_reporting
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
      HF::Attributes::IAttribute *create_attribute (HF::Core::AttributeReporting::IServer *server,
                                                    uint8_t uid);

      /*!
       * This namespace contains the classes that implement the Attribute Reporting service.
       */
      namespace AttributeReporting
      {
         /*!
          * @addtogroup attr_reporting  Attribute Reporting
          * @ingroup core
          *
          * This module contains the classes that implement the Attribute Reporting service.
          *
          * @addtogroup attr_reporting_common Common
          * @ingroup attr_reporting
          *
          * This module contains the common definitions for the Attribute Reporting service
          * implementation.
          * @{
          */
         //! Commands.
         typedef enum _CMD
         {
            PERIODIC_REPORT_CMD    = 0x01, //!< Periodic Report.
            EVENT_REPORT_CMD       = 0x02, //!< Event Report.
            CREATE_PERIODIC_CMD    = 0x01, //!< Create Periodic Report.
            CREATE_EVENT_CMD       = 0x02, //!< Create Event Report.
            ADD_PERIODIC_ENTRY_CMD = 0x03, //!< Add periodic report entry.
            ADD_EVENT_ENTRY_CMD    = 0x04, //!< Add event report entry.
            DELETE_REPORT_CMD      = 0x05, //!< Delete report.
            GET_PERIODIC_ENTRIES   = 0x06, //!< Get periodic entries.
            GET_EVENT_ENTRIES      = 0x07, //!< Get event entries.
            __LAST_CMD__           = GET_EVENT_ENTRIES
         } CMD;

         //! Attributes.
         typedef enum _Attributes
         {
            REPORT_COUNT_ATTR          = 0x01, //!< Number of report entries attribute.
            PERIODIC_REPORT_COUNT_ATTR = 0x02, //!< Number of periodic report entries attribute.
            EVENT_REPORT_COUNT_ATTR    = 0x03, //!< Number of event report entries attribute.
            __LAST_ATTR__              = EVENT_REPORT_COUNT_ATTR
         } Attributes;

         //! Types of reports send from the server to the client.
         typedef enum _Type
         {
            PERIODIC = 0x00, //!< Periodic Report.
            EVENT    = 0x01, //!< Event Report.
         } Type;

         /*!
          * Report Identifier.
          */
         struct Reference
         {
            uint8_t type : 1; //!< Report type : PERIODIC or EVENT
            uint8_t id   : 7; //!< Report ID.

            /*!
             * Constructor.
             *
             * @param [in] _type report type, @c PERIODIC or @c EVENT.
             * @param [in] _id   report id.
             */
            Reference(uint8_t _type = 0, uint8_t _id = 0):
               type (_type), id (_id)
            {}

            //! Minimum pack/unpack required data size.
            static constexpr uint16_t min_size = sizeof(uint8_t);

            //! @copydoc HF::Common::Serializable::size
            uint16_t size () const;

            //! @copydoc HF::Common::Serializable::pack
            uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

            //! @copydoc HF::Common::Serializable::unpack
            uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0);
         };

         /*!
          * Parent class for all report rule entries.
          */
         struct Entry
         {
            uint8_t           unit;    //!< Unit ID this entry to.
            Common::Interface itf;     //!< Interface UID.

            uint8_t           pack_id; //!< Attribute's Pack ID.

            //! Minimum pack/unpack required data size.
            static constexpr uint16_t min_size = sizeof(uint8_t)               // Unit ID.
                                                 + Common::Interface::min_size // Interface
                                                 + sizeof(uint8_t);            // Attribute Pack ID.

            //! @copydoc HF::Common::Serializable::size
            uint16_t size () const;

            //! @copydoc HF::Common::Serializable::pack
            uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

            //! @copydoc HF::Common::Serializable::unpack
            uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0);

            protected:

            Entry() {}
         };

         /*!
          * Parent class for all report rules.
          */
         struct Rule
         {
            //! Report reference this rule generates.
            Reference report;

            //! Device/unit that will receive the report.
            Protocol::Address destination;

            //! Minimum pack/unpack required data size.
            static constexpr uint16_t min_size = Reference::min_size             // Report ID.
                                                 + Protocol::Address ::min_size; // Destination Address.

            //! @copydoc HF::Common::Serializable::size
            uint16_t size () const;

            //! @copydoc HF::Common::Serializable::pack
            uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

            //! @copydoc HF::Common::Serializable::unpack
            uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0);

            protected:

            Rule() {}

            /*!
             * Constructor.
             *
             * @param [in] type Report reference type of this rule.
             */
            Rule(Type type):report (type) {}
         };

         /*! @} */

         /*!
          * This namespace contains the classes to handle the attribute reporting
          * periodic functionality.
          */
         namespace Periodic
         {
            /*!
             * @addtogroup attr_report_periodic Periodic
             * @ingroup attr_reporting
             *
             * This module contains the class that implement the support for the periodic
             * rules in the Attribute Reporting service.
             * @{
             */

            /*!
             * This class represents an entry in a periodic rule.
             */
            struct Entry:public AttributeReporting::Entry
            {
               HF::Attributes::UIDS uids;

               uint16_t size () const;

               uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

               uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0);
            };

            /*!
             * This class represents a periodic rule for attribute reporting.
             */
            struct Rule:public AttributeReporting::Rule
            {
               typedef Common::SimpleList <Entry> Container;

               typedef Container::iterator iterator;

               typedef Container::const_iterator const_iterator;

               //! Attribute indicating the time interval rule needs to be activated.
               uint32_t interval;

               //! Attribute indicating the last time rule was activated.
               uint32_t last_time;

               /*!
                * Constructor.
                *
                * @param [in] _interval   periodic rule interval value.
                */
               Rule(uint32_t _interval = 0):AttributeReporting::Rule(PERIODIC), interval (_interval),
                  last_time (0)
               {}

               //! Minimum pack/unpack required data size.
               static constexpr uint16_t min_size = AttributeReporting::Rule::min_size   // Parent Min. Size.
                                                    + sizeof(uint32_t)                   // Interval Value.
                                                    + sizeof(uint8_t);                   // Nr. Entries.

               uint16_t size () const;

               uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

               uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0);

               /*!
                * Add the given @c entry to rule.
                *
                * @param [in] entry    reference to the entry to add to this rule.
                */
               void add (const Entry &entry)
               {
                  entries.push_front (entry);
               }

               /*!
                * Remove all entries in this rule.
                */
               void clear ()
               {
                  entries.clear ();
               }

               /*!
                * Number of entries present in this rule.
                *
                * @return  number of entries present in this rule.
                */
               uint16_t entries_count ()
               {
                  return std::distance (entries.begin (), entries.end ());
               }


               /*!
                * Get an iterator to the start of the entries in this rule.
                *
                * @return  iterator to the start of the entries present in this rule.
                */
               iterator begin ()
               {
                  return entries.begin ();
               }

               /*!
                * Get an iterator to the end of the entries in this rule.
                *
                * @return  iterator to the end of the entries present in this rule.
                */
               iterator end ()
               {
                  return entries.end ();
               }

               /*!
                * Get a constant iterator to the start of the entries in this rule.
                *
                * @return  iterator to the start of the entries present in this rule.
                */
               const_iterator cbegin () const
               {
                  return entries.cbegin ();
               }

               /*!
                * Get constant iterator to the end of the entries in this rule.
                *
                * @return  iterator to the end of the entries present in this rule.
                */
               const_iterator cend () const
               {
                  return entries.cend ();
               }

               protected:

               //! Container for the entries of the periodic rule.
               Container entries;
            };

            /*! @} */

         }  // namespace Periodic

         /*!
          * Namespace for Attribute Reporting based on events.
          */
         namespace Event
         {
            /*!
             * @addtogroup attr_report_event Event
             * @ingroup attr_reporting
             *
             * This module contains the class that implement the support for the event
             * rules in the Attribute Reporting service.
             * @{
             */

            /*!
             * Types of events.
             */
            typedef enum _Type
            {
               COV = 0x00, //!< Change of value event.
               HT  = 0x01, //!< High Threshold reached event.
               LT  = 0x02, //!< Low Threshold reached event.
               EQ  = 0x03, //!< Equal value event.
            } Type;

            /*!
             * Entry field for a given attribute.
             */
            struct Field
            {
               //! Field type.
               Type type;

               //! Attribute UID.
               uint8_t attr_uid;

               //! Field value.
               Common::ByteArray value;

               /*!
                * Constructor.
                *
                * @param [in] _type       field type.
                * @param [in] _attr_uid   field attribute uid.
                */
               Field(Type _type = COV, uint8_t _attr_uid = 0):
                  type (_type), attr_uid (_attr_uid)
               {}

               //! Minimum pack/unpack required data size.
               static constexpr uint16_t min_size = sizeof(uint8_t)    // Field type.
                                                    + sizeof(uint8_t); // Size of value holder or COV value.

               /*!
                * @copydoc HF::Common::Serializable::size
                *
                * @param [in] with_uid    if @c true include @c attr_uid size
                *                         in the size calculation.
                */
               uint16_t size (bool with_uid) const;

               /*!
                * @copydoc HF::Common::Serializable::pack
                *
                * @param [in] with_uid    include @c attr_uid in the serialization.
                */
               uint16_t pack (Common::ByteArray &array, uint16_t offset, bool with_uid) const;

               /*!
                * @copydoc HF::Common::Serializable::unpack
                *
                * @warning If @c with_uid == @c true, then if the value read from the
                *          array does not match the attribute's UID, no more data will be read.
                *
                * @param [in] with_uid    include uid() size in the calculation.
                */
               uint16_t unpack (const Common::ByteArray &array, uint16_t offset, bool with_uid);
            };

            /*!
             * Report event entry.
             */
            struct Entry:public AttributeReporting::Entry
            {
               //! Vector containing the fields for this entry.
               std::vector <Field> fields;

               uint16_t size () const;

               uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

               uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0);
            };

            /*!
             * Report event rule.
             */
            struct Rule:public AttributeReporting::Rule
            {
               typedef Common::SimpleList <Entry> Container;

               typedef Container::iterator iterator;

               typedef Container::const_iterator const_iterator;

               Rule():AttributeReporting::Rule(EVENT)
               {}

               //! Minimum pack/unpack required data size.
               static constexpr uint16_t min_size = AttributeReporting::Rule::min_size    // Parent Min. Size.
                                                    + sizeof(uint8_t);                    // Nr. Entries.

               uint16_t size () const;

               uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

               uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0);

               /*!
                * Add the given @c entry to rule.
                *
                * @param [in] entry    reference to the entry to add to this rule.
                */
               void add (const Entry &entry)
               {
                  entries.push_front (entry);
               }

               /*!
                * Remove all entries in this rule.
                */
               void clear ()
               {
                  entries.clear ();
               }

               /*!
                * Number of entries present in this rule.
                *
                * @return  number of entries present in this rule.
                */
               uint16_t entries_count ()
               {
                  return std::distance (entries.begin (), entries.end ());
               }

               /*!
                * Get a iterator to the start of the entries in this rule.
                *
                * @return  iterator to the start of the entries present in this rule.
                */
               iterator begin ()
               {
                  return entries.begin ();
               }

               /*!
                * Get a iterator to the end of the entries in this rule.
                *
                * @return  iterator to the end of the entries present in this rule.
                */
               iterator end ()
               {
                  return entries.end ();
               }

               /*!
                * Get a constant iterator to the start of the entries in this rule.
                *
                * @return  iterator to the start of the entries present in this rule.
                */
               const_iterator cbegin () const
               {
                  return entries.cbegin ();
               }

               /*!
                * Get constant iterator to the end of the entries in this rule.
                *
                * @return  iterator to the end of the entries present in this rule.
                */
               const_iterator cend () const
               {
                  return entries.cend ();
               }

               protected:

               //! Container for the entries of this rule.
               Container entries;
            };

            /*! @} */

         }  // namespace Event

         /*!
          * This namespace contains the classes that implement the
          * attribute reporting notifications.
          */
         namespace Report
         {
            /*!
             * @addtogroup attr_reporting_report   Reports
             * @ingroup attr_reporting
             *
             * This module contains the classes that implement the messages used in
             * the %Attribute Reporting service implementation.
             * @{
             */
            // =============================================================================
            // Notification API
            // =============================================================================

            typedef std::shared_ptr <HF::Attributes::IAttribute> Attribute;

            /*!
             * Parent call for all reports.
             */
            struct Abstract:public AttributeReporting::Reference
            {
               /*!
                * Constructor.
                *
                * @param [in] type report type, @c PERIODIC or @c EVENT.
                * @param [in] id   report id.
                */
               Abstract(uint8_t type = 0, uint8_t id = 0):
                  AttributeReporting::Reference (type, id)
               {}
            };

            /*!
             * Parent class for all notification entries.
             */
            struct Entry
            {
               static constexpr uint16_t min_size = sizeof(uint8_t)                // Unit index size.
                                                    + Common::Interface::min_size  // Interface UID size.
                                                    + sizeof(uint8_t);             // Number of attributes/fields.

               uint8_t           unit; //!< Unit id that originated this notification.
               Common::Interface itf;  //!< Interface UID this notification relates to.

               Entry():unit (0), itf (0, 0) {}

               /*!
                * Constructor.
                *
                * @param [in] _unit    unit id for this notification.
                * @param [in] _itf     interface %UID for this notification.
                */
               Entry(uint8_t _unit, Common::Interface _itf):
                  unit (_unit), itf (_itf)
               {}

               virtual ~Entry() {}

               //! @copydoc HF::Common::Serializable::size
               uint16_t size () const;

               //! @copydoc HF::Common::Serializable::pack
               uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

               /*!
                * @copydoc HF::Common::Serializable::unpack
                *
                * @param [in] get_factory    pointer to a function that returns the attribute factory
                *                            for the interface given by @c itf.
                */
               uint16_t unpack (HF::Attributes::FactoryGetter get_factory,
                                const Common::ByteArray &array, uint16_t offset = 0);

               protected:

               /*!
                * Unpack an incoming attribute.
                *
                * @copydoc HF::Common::Serializable::unpack
                *
                * @param [in] factory  function pointer to used to create attributes for the
                *                      interface given in @c itf.
                */
               virtual uint16_t unpack (HF::Attributes::Factory factory,
                                        const Common::ByteArray &array, uint16_t offset = 0)
               {
                  UNUSED (factory);
                  UNUSED (array);
                  UNUSED (offset);

                  return 0;
               }

               /*!
                * Get the number of entries is this rule entry.
                *
                * @return  number of entries is this rule entry.
                */
               virtual uint8_t count () const
               {
                  return 0;
               }
            };

            // =============================================================================
            // Messages
            // =============================================================================

            /*!
             * This message is used to create a reporting rule.
             */
            struct CreateMessage
            {
               //! Device address to create the report rule for.
               Protocol::Address destination;

               //! Minimum pack/unpack required data size.
               static constexpr uint16_t min_size = Protocol::Address::min_size; // Destination.

               //! @copydoc HF::Common::Serializable::size
               uint16_t size () const;

               //! @copydoc HF::Common::Serializable::pack
               uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

               //! @copydoc HF::Common::Serializable::unpack
               uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0);
            };

            /*!
             * This message is used to delete a reporting rule.
             */
            struct DeleteMessage
            {
               //! Identification of the rule to delete.
               Reference report;

               //! Minimum pack/unpack required data size.
               static constexpr uint16_t min_size = Reference::min_size; // Report ID.

               //! @copydoc HF::Common::Serializable::size
               uint16_t size () const;

               //! @copydoc HF::Common::Serializable::pack
               uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

               //! @copydoc HF::Common::Serializable::unpack
               uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0);
            };

            /*!
             * Parent class for the messages to create reporting
             * rule entries.
             */
            struct AddEntryMessage
            {
               //! Identification of the rule to add the entries to.
               Reference report;

               virtual ~AddEntryMessage() {}

               //! Minimum pack/unpack required data size.
               static constexpr uint16_t min_size = Reference::min_size // Destination.
                                                    + sizeof(uint8_t);  // Nr. Entries.

               //! @copydoc HF::Common::Serializable::size
               uint16_t size () const;

               //! @copydoc HF::Common::Serializable::pack
               uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

               //! @copydoc HF::Common::Serializable::unpack
               uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0);

               protected:

               AddEntryMessage() {}

               /*!
                * @copydoc HF::Common::Serializable::unpack
                *
                * Unpack an underling entry for the add entry command.
                */
               virtual uint16_t unpack_entry (const Common::ByteArray &array, uint16_t offset = 0)
               {
                  UNUSED (array);
                  UNUSED (offset);

                  return 0;
               }

               /*!
                * Get number of entries in this message.
                *
                * @return number of entries in this message.
                */
               virtual uint8_t count () const
               {
                  return 0;
               }

               /*!
                * Get the minimum number of bytes required for unpacking an entry.
                *
                * @return minimum number of bytes required for unpacking an entry.
                */
               virtual uint16_t entry_size () const
               {
                  return 0;
               }
            };

            // =============================================================================
            // Periodic Report Support
            // =============================================================================

            /*!
             * Periodic report notification.
             */
            struct Periodic:public Abstract
            {
               /*!
                * Periodic notification entry.
                */
               struct Entry:public Report::Entry
               {
                  std::vector <Report::Attribute> attributes;

                  Entry() {}

                  /*!
                   * Constructor.
                   *
                   * @param [in] unit    unit id for this notification.
                   * @param [in] itf     interface %UID for this notification.
                   */
                  Entry(uint8_t unit, Common::Interface itf):Report::Entry(unit, itf)
                  {}

                  uint16_t size () const;

                  uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

                  /*!
                   * Add attribute to this periodic report entry.
                   *
                   * @param [in] attr  reference to a pointer of the attribute to add.
                   */
                  void add (HF::Attributes::IAttribute * &attr);

                  using Report::Entry::unpack;

                  protected:

                  uint16_t unpack (HF::Attributes::Factory factory,
                                   const Common::ByteArray &array, uint16_t offset = 0);

                  uint8_t count () const
                  {
                     return attributes.size ();
                  }
               };

               //! Entries associated with this notification.
               Common::SimpleList <Entry> entries;

               /*!
                * Constructor.
                *
                * @param [in] id    report reference ID.
                */
               Periodic(uint8_t id = 0):Abstract (PERIODIC, id)
               {}

               uint16_t size () const;

               uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

               //! @copydoc Report::Entry::unpack
               uint16_t unpack (HF::Attributes::FactoryGetter get_factory,
                                const Common::ByteArray &array, uint16_t offset = 0);

               /*!
                * Add entry into this periodic report.
                *
                * @param [in] entry    entry to add into this periodic report.
                */
               void add (Entry &entry);

               // =============================================================================
               // Message API
               // =============================================================================

               /*!
                * Create a Periodic rule message.
                */
               struct CreateMessage:public Report::CreateMessage
               {
                  //! Time interval to send the periodic report.
                  uint32_t interval;

                  uint16_t size () const;

                  uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

                  uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0);
               };

               /*!
                * Add entries into a periodic rule message.
                */
               struct AddEntryMessage:public Report::AddEntryMessage
               {
                  typedef Common::SimpleList <AttributeReporting::Periodic::Entry> Container;

                  typedef Container::iterator iterator;

                  typedef Container::const_iterator const_iterator;

                  AddEntryMessage()
                  {
                     report.type = PERIODIC;
                  }

                  uint16_t size () const;

                  uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

                  /*!
                   * Add a periodic entry into this message.
                   *
                   * @param [in] entry    entry to add to this message.
                   */
                  void add (const AttributeReporting::Periodic::Entry &entry)
                  {
                     entries.push_front (entry);
                  }

                  /*!
                   * Get a iterator to the start of the entries in this rule.
                   *
                   * @return  iterator to the start of the entries present in this rule.
                   */
                  iterator begin ()
                  {
                     return entries.begin ();
                  }

                  /*!
                   * Get a iterator to the end of the entries in this message.
                   *
                   * @return  iterator to the end of the entries present in this message.
                   */
                  iterator end ()
                  {
                     return entries.end ();
                  }

                  /*!
                   * Get a constant iterator to the start of the entries in this message.
                   *
                   * @return  constant iterator to the start of the entries present in this message.
                   */
                  const_iterator cbegin () const
                  {
                     return entries.cbegin ();
                  }

                  /*!
                   * Get constant iterator to the end of the entries in this message.
                   *
                   * @return  constant iterator to the end of the entries present in this message.
                   */
                  const_iterator cend () const
                  {
                     return entries.cend ();
                  }

                  protected:

                  //! Entries container.
                  Container entries;

                  uint16_t unpack_entry (const Common::ByteArray &array, uint16_t offset = 0);

                  uint8_t count () const
                  {
                     return std::distance (entries.begin (), entries.end ());
                  }

                  uint16_t entry_size () const
                  {
                     return AttributeReporting::Periodic::Entry::min_size;
                  }
               };
            };

            // =============================================================================
            // Event Report Support
            // =============================================================================

            /*!
             * Event type notification.
             */
            struct Event:public Abstract
            {
               /*!
                * Field for the entries in event notification.
                */
               struct Field
               {
                  static constexpr uint16_t min_size = sizeof(uint8_t)     // Event Type size.
                                                       + sizeof(uint8_t);  // Attribute UID.

                  //! Event type.
                  AttributeReporting::Event::Type type;

                  //! Attribute value.
                  Attribute attribute;

                  //! @copydoc HF::Common::Serializable::size
                  uint16_t size () const;

                  //! @copydoc HF::Common::Serializable::pack
                  uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

                  //! @copydoc Report::Entry::unpack(HF::Attributes::Factory, const Common::ByteArray &, uint16_t)
                  uint16_t unpack (HF::Attributes::Factory factory, const Common::ByteArray &array,
                                   uint16_t offset = 0);

                  /*!
                   * Set the field's attribute to the given attribute in @c attr.
                   *
                   * @param [in] attr  pointer to the attribute to set this field to.
                   */
                  void set_attribute (HF::Attributes::IAttribute *attr)
                  {
                     Attribute temp (attr);
                     attribute = std::move (temp);
                  }
               };

               /*!
                * Event notification entry.
                */
               struct Entry:public Report::Entry
               {
                  //! Vector containing the fields for the event entry.
                  std::vector <Field> fields;

                  Entry() {}

                  /*!
                   * Constructor.
                   *
                   * @param [in] unit    unit id for this notification.
                   * @param [in] itf     interface %UID for this notification.
                   */
                  Entry(uint8_t unit, Common::Interface itf):Report::Entry(unit, itf)
                  {}

                  uint16_t size () const;

                  uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

                  /*!
                   * Add the given field into this entry.
                   *
                   * @param [in] field    field to add to the entry.
                   */
                  void add (Field &field)
                  {
                     fields.push_back (std::move (field));
                  }

                  using Report::Entry::unpack;

                  protected:

                  uint16_t unpack (HF::Attributes::Factory factory,
                                   const Common::ByteArray &array, uint16_t offset = 0);

                  uint8_t count () const
                  {
                     return fields.size ();
                  }
               };

               //! Entries for the event notification.
               Common::SimpleList <Entry> entries;

               /*!
                * Constructor.
                *
                * @param [in] id    report reference ID.
                */
               Event(uint8_t id = 0):Abstract (EVENT, id)
               {}

               //! @copydoc HF::Common::Serializable::size
               uint16_t size () const;

               //! @copydoc HF::Common::Serializable::pack
               uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

               //! @copydoc Report::Entry::unpack
               uint16_t unpack (HF::Attributes::FactoryGetter get_factory,
                                const Common::ByteArray &array, uint16_t offset = 0);

               /*!
                * Add event entry into this event report.
                */
               void add (Entry &entry)
               {
                  entries.push_front (std::move (entry));
               }

               // =============================================================================
               // Message API
               // =============================================================================

               /*!
                * Create a Event rule message.
                */
               struct CreateMessage:public Report::CreateMessage
               {};

               /*!
                * Add entries into a event rule message.
                */
               struct AddEntryMessage:public Report::AddEntryMessage
               {
                  typedef Common::SimpleList <AttributeReporting::Event::Entry> Container;

                  typedef Container::iterator iterator;

                  typedef Container::const_iterator const_iterator;

                  AddEntryMessage()
                  {
                     report.type = EVENT;
                  }

                  uint16_t size () const;

                  uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

                  /*!
                   * Add a event entry into this message.
                   *
                   * @param [in] entry    entry to add to this message.
                   */
                  void add (const AttributeReporting::Event::Entry &entry)
                  {
                     entries.push_front (entry);
                  }

                  /*!
                   * Get a iterator to the start of the entries in this rule.
                   *
                   * @return  iterator to the start of the entries present in this rule.
                   */
                  iterator begin ()
                  {
                     return entries.begin ();
                  }

                  /*!
                   * Get a iterator to the end of the entries in this message.
                   *
                   * @return  iterator to the end of the entries present in this message.
                   */
                  iterator end ()
                  {
                     return entries.end ();
                  }

                  /*!
                   * Get a constant iterator to the start of the entries in this message.
                   *
                   * @return  constant iterator to the start of the entries present in this message.
                   */
                  const_iterator cbegin () const
                  {
                     return entries.cbegin ();
                  }

                  /*!
                   * Get constant iterator to the end of the entries in this message.
                   *
                   * @return  constant iterator to the end of the entries present in this message.
                   */
                  const_iterator cend () const
                  {
                     return entries.cend ();
                  }

                  protected:

                  //! Container that holds the entries present in the message.
                  Container entries;

                  uint16_t unpack_entry (const Common::ByteArray &array, uint16_t offset = 0);

                  uint8_t count () const
                  {
                     return std::distance (entries.begin (), entries.end ());
                  }

                  uint16_t entry_size () const
                  {
                     return AttributeReporting::Event::Entry::min_size;
                  }
               };

               /*!
                * This function checks if any fields in the given event rule entry
                * match the change for the attribute given by @c old_value to @c new_value.
                *
                * @param [in] entry       event rule entry.
                * @param [in] old_value   attribute's old value.
                * @param [in] new_value   attribute's new value.
                *
                * @return  an report event entry to be sent or @c nullptr if no fields match.
                */
               static Report::Event::Entry *process (
                  const AttributeReporting::Event::Entry &entry,
                  const HF::Attributes::IAttribute &old_value,
                  const HF::Attributes::IAttribute &new_value);
            };

            /*! @} */

         }  // namespace Report

         /*!
          * @addtogroup attr_reporting_common
          * @{
          */
         // =============================================================================
         // Message API
         // =============================================================================

         struct Response:public HF::Protocol::Response
         {
            Reference report;

            uint16_t size () const;

            uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

            uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0);
         };

         // =============================================================================
         // API
         // =============================================================================

         //! Start value for report identifiers.
         static constexpr uint8_t START_ADDR = 0x01;

         //! Maximum value for report identifiers.
         static constexpr uint8_t MAX_ADDR = 0x7E;

         //! Value indicating all reports.
         static constexpr uint8_t ALL_ADDR = 0x7F;

         typedef std::vector <Periodic::Entry>::iterator periodic_iterator;
         typedef std::vector <Event::Entry>::iterator event_iterator;

         /*!
          * Create a new attribute reporting event rule for the device with the
          * given address.
          *
          * @param [in] destination   device address the rule should be created for.
          *
          * @return  pointer to a message indicating the result of the operation to be
          *          sent to the requesting device.
          */
         Protocol::Message *create (Protocol::Address &destination);

         /*!
          * Create a new attribute reporting periodic rule for the device with the
          * given address and the given @c interval.
          *
          * @param [in] destination   device address the rule should be created for.
          * @param [in] interval      time interval in seconds for the periodic rule.
          *
          * @return  pointer to a message indicating the result of the operation to be
          *          sent to the requesting device.
          */
         Protocol::Message *create (Protocol::Address &destination, uint32_t interval);

         /*!
          * Remove the rule with the given @c type and the given @c report_id.
          *
          * @param [in] type        report type (HF::Core::AttributeReporting::Type)
          * @param [in] report_id   report ID.
          *
          * @return  pointer to a message indicating the result of the operation to be
          *          sent to the requesting device.
          */
         Protocol::Message *destroy (Type type, uint8_t report_id);

         /*!
          * Remove the rule for the given @c report reference.
          *
          * @param [in] report   report reference to remove the rule for.
          *
          * @return  pointer to a message indicating the result of the operation to be
          *          sent to the requesting device.
          */
         Protocol::Message *destroy (Reference report);

         /*!
          * Add the periodic entries from @c start to @c end into the rule with
          * the given @c report reference.
          *
          * @param [in] report     report reference
          * @param [in] begin      iterator to the start of the periodic entries to add.
          * @param [in] end        iterator to the end of the periodic entries to add.
          *
          * @return  pointer to a message indicating the result of the operation to be
          *          sent to the requesting device.
          */
         Protocol::Message *add (Reference report, periodic_iterator begin, periodic_iterator end);

         /*!
          * Add the event entries from @c start to @c end into the rule with
          * the given @c report reference.
          *
          * @param [in] report     report reference
          * @param [in] begin      iterator to the start of the event entries to add.
          * @param [in] end        iterator to the end of the event entries to add.
          *
          * @return  pointer to a message indicating the result of the operation to be
          *          sent to the requesting device.
          */
         Protocol::Message *add (Reference report, event_iterator begin, event_iterator end);

         /*!
          * @copybrief HF::Core::create_attribute (HF::Core::AttributeReporting::Server *,uint8_t)
          *
          * @see HF::Core::create_attribute (HF::Core::AttributeReporting::Server *,uint8_t)
          *
          * @param [in] uid   attribute %UID to create the attribute object for.
          *
          * @retval  pointer to an attribute object
          * @retval  <tt>nullptr</tt> if the attribute UID does not exist.
          */
         HF::Attributes::IAttribute *create_attribute (uint8_t uid);

         /*!
          * @}
          * @addtogroup attr_reporting
          * @{
          */

         /*!
          * Attribute Reporting - Client Role.
          */
         struct Client:public HF::Interfaces::Base <HF::Interface::ATTRIBUTE_REPORTING>
         {
            // =============================================================================
            // Interface API
            // =============================================================================

            Interface::Role role () const
            {
               return HF::Interface::CLIENT_ROLE;
            }

            // =============================================================================
            // API
            // =============================================================================

            // ======================================================================
            // Events
            // ======================================================================
            //! @name Events
            //! @{

            /*!
             * Event indicating a @c PERIODIC_REPORT_CMD or a @c EVENT_REPORT_CMD.
             *
             * @param [in] type     type of report.
             * @param [in] address  device address that originated the event.
             * @param [in] payload  data in the report.
             * @param [in] offset   offset from which to start reading the data of the
             *                      the report in the @c payload.
             */
            virtual void report (Type type, const Protocol::Address &address,
                                 const Common::ByteArray &payload, uint16_t offset)
            {
               UNUSED (type);
               UNUSED (address);
               UNUSED (payload);
               UNUSED (offset);
            }

            /*!
             * Event indicating the result of a @c CREATE_PERIODIC_CMD or
             * @c CREATE_EVENT_CMD.
             *
             * @param [in] address     device address that originated the event.
             * @param [in] response    result of the operation.
             */
            virtual void created (const Protocol::Address &address, const Response &response)
            {
               UNUSED (address);
               UNUSED (response);
            }

            /*!
             * Event indicating the result of a @c ADD_PERIODIC_ENTRY_CMD or
             * @c ADD_EVENT_ENTRY_CMD.
             *
             * @param [in] address     device address that originated the event.
             * @param [in] response    result of the operation.
             */
            virtual void added (const Protocol::Address &address, const Response &response)
            {
               UNUSED (address);
               UNUSED (response);
            }

            /*!
             * Event indicating the result of a @c DELETE_REPORT_CMD.
             *
             * @param [in] address     device address that originated the event.
             * @param [in] response    result of the operation.
             */
            virtual void deleted (const Protocol::Address &address, const Response &response)
            {
               UNUSED (address);
               UNUSED (response);
            }

            //! @}
            // ======================================================================

            protected:

            uint16_t payload_size (Protocol::Message &message) const;

            uint16_t payload_size (Protocol::Message::Interface &itf) const;

            Common::Result handle_command (Protocol::Packet &packet, Common::ByteArray &payload,
                                           uint16_t offset);

         };

         /*!
          * Helper class for using the Attribute Reporting service.
          */
         struct AbstractClient:public Client
         {
            // =============================================================================
            // API
            // =============================================================================

            // ======================================================================
            // Commands
            // ======================================================================
            //! \name Commands
            //! @{

            /*!
             * Create a new attribute reporting event rule on the device with the
             * given @c destination address, for the device/unit that contains this interface.
             *
             * @param [in] destination   device address the rule should be sent to.
             */
            void create (Protocol::Address &destination);

            /*!
             * Create a new attribute reporting periodic rule on the device with the
             * given @c destination address and the given @c interval, for the device/unit
             * that contains this interface.
             *
             * @param [in] destination   device address the rule should be sent to.
             * @param [in] interval      time interval in seconds for the periodic rule.
             */
            void create (Protocol::Address &destination, uint32_t interval);

            /*!
             * Remove the rule with the given @c type and the given @c report_id,
             * on the device with the given @c destination address.
             *
             * @param [in] destination    device address the rule should be sent to.
             * @param [in] type           report type (HF::Core::AttributeReporting::Type)
             * @param [in] report_id      report ID.
             */
            void destroy (Protocol::Address &destination, Type type, uint8_t report_id);

            /*!
             * Remove the rule for the given @c report reference, on the device with the
             * given @c destination address.
             *
             * @param [in] destination    device address the rule should be sent to.
             * @param [in] report         report reference to remove the rule for.
             */
            void destroy (Protocol::Address &destination, Reference report);

            /*!
             * Add the periodic entries from @c start to @c end into the rule with
             * the given @c report reference, on the device with the given @c destination address.
             *
             * @param [in] destination    device address the rule should be sent to.
             * @param [in] report         report reference
             * @param [in] begin          iterator to the start of the periodic entries to add.
             * @param [in] end            iterator to the end of the periodic entries to add.
             */
            void add (Protocol::Address &destination, Reference report,
                      periodic_iterator begin, periodic_iterator end);

            /*!
             * Add the event entries from @c start to @c end into the rule with
             * the given @c report reference, on the device with the given @c destination
             * address.
             *
             * @param [in] destination    device address the rule should be sent to.
             * @param [in] report         report reference
             * @param [in] begin          iterator to the start of the event entries to add.
             * @param [in] end            iterator to the end of the event entries to add.
             */
            void add (Protocol::Address &destination, Reference report,
                      event_iterator begin, event_iterator end);

            //! @}
            // ======================================================================

            protected:

            /*!
             * Get the unit that contains this interface.
             *
             * @return  reference to unit that contains this interface.
             */
            virtual HF::Units::IUnit &unit () const = 0;
         };

         /*!
          * %Attribute Reporting - %Server %Role.
          *
          * This class provides the minimal implementation for the %Attribute reporting
          * server role functionality.
          *
          * All requests will get a HF::Common::Result::FAIL_RESOURCES response.
          */
         struct IServer:public AbstractService
         {
            /*!
             * Constructor.
             *
             * @param [in] unit  reference to the unit containing this service.
             */
            IServer(Unit0 &unit):
               AbstractService (unit)
            {}

            virtual ~IServer() {}

            // =============================================================================
            // API
            // =============================================================================

            uint16_t uid () const
            {
               return HF::Interface::ATTRIBUTE_REPORTING;
            }

            Interface::Role role () const
            {
               return HF::Interface::SERVER_ROLE;
            }

            /*!
             * Process an attribute change from @c old_value to @c new_value for the given
             * @c unit.
             *
             * This method checks if the change in the given attribute matches the conditions
             * present in any of the attribute reporting rules.
             *
             * @param [in] unit        unit ID where the attribute is present.
             * @param [in] old_value   old value for the attribute.
             * @param [in] new_value   new value for the attribute.
             */
            virtual void notify (uint8_t unit, const HF::Attributes::IAttribute &old_value,
                                 const HF::Attributes::IAttribute &new_value)
            {
               UNUSED (unit);
               UNUSED (old_value);
               UNUSED (new_value);
            }

            /*!
             * Get the number of rules for the given @c type.
             *
             * @param [in] type  attribute reporting type to get the number of rules for.
             *
             * @return  number of rules for the given @c type.
             */
            virtual uint16_t count (Type type) const
            {
               UNUSED (type);
               return 0;
            }

            // =============================================================================
            // Interface Attribute API.
            // =============================================================================

            HF::Attributes::IAttribute *attribute (uint8_t uid)
            {
               return Core::create_attribute (this, uid);
            }

            HF::Attributes::UIDS attributes (uint8_t pack_id =
                                                HF::Attributes::Pack::MANDATORY) const
            {
               UNUSED (pack_id);
               return HF::Attributes::UIDS {REPORT_COUNT_ATTR, PERIODIC_REPORT_COUNT_ATTR,
                                            EVENT_REPORT_COUNT_ATTR};
            }

            protected:

            using AbstractService::notify;

            Common::Result handle_command (Protocol::Packet &packet, Common::ByteArray &payload,
                                           uint16_t offset);

            /*!
             * Send the response to a command with the given @c result.
             *
             * @param [in] packet   incoming packet to generate the response for.
             * @param [in] report   report identification.
             * @param [in] result   operation result.
             */
            void response (Protocol::Packet &packet, Reference &report, Common::Result result);

            /*!
             * Check if the given command is authorized for the device with
             * the given address.
             *
             * @param [in] member interface member to check.
             * @param [in] source device address of the incoming command.
             *
             * @retval  true  the command if authorized.
             * @retval  false otherwise.
             */
            virtual bool authorized (uint8_t member, Protocol::Address &source)
            {
               UNUSED (member);
               UNUSED (source);

               return true;
            }

            bool check_uid (uint16_t uid) const
            {
               return IServer::uid () == uid;
            }
         };

         /*!
          * %Attribute Reporting - %Server %Role.
          */
         struct Server:public IServer
         {
            Common::SimpleList <Periodic::Rule> periodic_rules;    //!< Periodic rules.
            Common::SimpleList <Event::Rule>    event_rules;       //!< Event rules.

            /*!
             * Constructor.
             *
             * @param [in] unit  reference to the unit containing this service.
             */
            Server(Unit0 &unit):
               IServer (unit), last_time (0)
            {}

            virtual ~Server() {}

            // =============================================================================
            // API
            // =============================================================================

            /*!
             * Handle a create periodic rule command.
             *
             * @param [in] message  create periodic rule message.
             *
             * @retval HF::Common::Result::FAIL_RESOURCES   if the rule could not be created.
             * @retval HF::Common::Result::OK               if the rule was created.
             */
            virtual Common::Result handle (const Report::Periodic::CreateMessage &message);

            /*!
             * Handle an add periodic entries message.
             *
             * @param message    add periodic entries message with the entries to add.
             *
             * @retval Common::Result::FAIL_ARG    if the rule cannot be found.
             * @retval Common::Result::OK          if the entries where added.
             */
            virtual Common::Result handle (const Report::Periodic::AddEntryMessage &message);

            /*!
             * Handle a create event rule command.
             *
             * @param [in] message  create event rule message.
             *
             * @retval HF::Common::Result::FAIL_RESOURCES   if the rule could not be created.
             * @retval HF::Common::Result::OK               if the rule was created.
             */
            virtual Common::Result handle (const Report::Event::CreateMessage &message);

            /*!
             * Handle an add event entries message.
             *
             * @param message    add event entries message with the entries to add.
             *
             * @retval Common::Result::FAIL_ARG    if the rule cannot be found.
             * @retval Common::Result::OK          if the entries where added.
             */
            virtual Common::Result handle (const Report::Event::AddEntryMessage &message);

            /*!
             * Handle a delete rule request.
             *
             * @param [in] message  delete rule request message.
             *
             * @retval Common::Result::FAIL_ARG    if the rule cannot be found.
             * @retval Common::Result::OK          if the rule was deleted.
             */
            virtual Common::Result handle (const Report::DeleteMessage &message);

            using HF::Interfaces::AbstractInterface::handle;

            void periodic (uint32_t time);

            void notify (uint8_t unit, const HF::Attributes::IAttribute &old_value,
                         const HF::Attributes::IAttribute &new_value);

            uint16_t count (Type type) const;

            protected:

            //! Last time the periodic function was called.
            uint32_t last_time;

            using AbstractService::notify;

            uint16_t payload_size (Protocol::Message::Interface &itf) const;

            Common::Result handle_command (Protocol::Packet &packet, Common::ByteArray &payload,
                                           uint16_t offset);
         };

         /*! @} */

      }  // namespace AttributeReporting

   }  // namespace Core

}  // namespace HF

/*!
 * @addtogroup attr_reporting
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
std::ostream &operator <<(std::ostream &stream, const HF::Core::AttributeReporting::CMD command);

/*!
 * Convert the given @c attribute into a string and write it to the given @c stream.
 *
 * @param [in] stream      out stream to write the string to.
 * @param [in] attribute   attribute value to convert to a string.
 *
 * @return   <tt>stream</tt>
 */
std::ostream &operator <<(std::ostream &stream, const HF::Core::AttributeReporting::Attributes attribute);

/*! @} */

#endif /* HF_CORE_ATTRIBUTE_REPORTING_H */
