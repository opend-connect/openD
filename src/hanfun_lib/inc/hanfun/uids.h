// =============================================================================
/*!
 * @file       inc/hanfun/uids.h
 *
 * This file contains the declaration of the classes that implement the HAN-FUN
 * UIDs.
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
#ifndef HF_UIDS_H
#define HF_UIDS_H

#include "hanfun/common.h"

namespace HF
{
   // =============================================================================
   // UID implementation
   // =============================================================================

   /*!
    * This is the top-level namespace for HAN-FUN UIDs.
    */
   namespace UID
   {
      /*!
       * @addtogroup uid_t UIDs
       * @ingroup devices
       *
       * This module contains the classes implementing the available %UID for HAN-FUN devices.
       * @{
       */

      //! Types of UIDs available.
      typedef enum _Type
      {
         NONE_UID = 0x00,   //!< Empty UID.
         DECT_UID = 0x01,   //!< RFPI or IPUI.
         MAC_UID  = 0x02,   //!< Media Access Control (IEEE-MAC-48)
         URI_UID  = 0x03,   //!< Uniform Resource Identifier.
      } Type;

      /*!
       * API for all UIDs.
       *
       * Parent UID class.
       */
      struct UID_T:public Common::Serializable, public Common::Cloneable <UID_T>
      {
         /*!
          * Type of the UID. @see HF::UID::Type.
          *
          * @return  type of the UID.
          */
         virtual uint8_t type () const = 0;

         bool operator ==(const UID_T &other) const
         {
            return (this->compare (other) == 0);
         }

         bool operator !=(const UID_T &other) const
         {
            return !(*this == other);
         }

         /*!
          * Compare the current UID with the given UID.
          *
          * This function returns a value less that 0 if the current UID object
          * order is lower that the given UID, 0 if the UIDs represent the same
          * entity and a value greater that 0 if current UID object is above the given
          * UID.
          *
          * @param [in] other  a pointer to a UID object to compare to.
          *
          * @retval     <0 the current UID is lower that the given UID.
          * @retval     0  the current UID is the same as given UID.
          * @retval     >0 the current UID is greater that the given UID.
          */
         virtual int compare (const UID_T &other) const
         {
            return (this->type () - other.type ());
         }

         //! Minimum pack/unpack required data size.
         static constexpr uint16_t min_size = sizeof(uint8_t)     // UID Type.
                                              + sizeof(uint8_t);  // Size of the UID.

         //! @copydoc HF::Common::Serializable::size
         uint16_t size () const
         {
            return min_size;
         }

         //! @copydoc HF::Common::Serializable::pack
         uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const
         {
            SERIALIZABLE_CHECK (array, offset, min_size);

            array.write (offset, this->type ());

            return sizeof(uint8_t);
         }

         //! @copydoc HF::Common::Serializable::unpack
         uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0)
         {
            SERIALIZABLE_CHECK (array, offset, min_size);

            uint8_t type;
            array.read (offset, type);

            assert ((type & (~0x80)) == this->type ());

            return sizeof(uint8_t);
         }
      };

      /*!
       * Helper template parent class for all UID's implementation.
       *
       * @tparam _type type value for the UID.
       */
      template<uint8_t _type>
      struct Abstract:public UID_T
      {
         uint8_t type () const
         {
            return _type;
         }
      };

      /*!
       * This class represents an empty UID.
       */
      struct NONE:public Abstract <NONE_UID>
      {
         uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const
         {
            SERIALIZABLE_CHECK (array, offset, min_size);

            offset += UID_T::pack (array, offset);

            array.write (offset, (uint8_t) 0);

            return min_size;
         }

         uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0)
         {
            SERIALIZABLE_CHECK (array, offset, min_size);

            uint16_t res = UID_T::unpack (array, offset);

            if (res == 0)
            {
               return 0;
            }

            offset += res;

            uint8_t size;
            array.read (offset, size);

            assert (size == 0);

            return min_size;
         }

         NONE *clone () const
         {
            return new NONE (*this);
         }
      };

      /*!
       * Helper template parent class for all UIDs based on fixed number of bytes.
       *
       * @tparam  _Class   child class being created.
       * @tparam  _size    number of bytes in the UID.
       * @tparam  _type    UID type value.
       */
      template<typename _Class, uint8_t _size, uint8_t _type>
      class ByteArray:public Abstract <_type>
      {
         protected:

         uint8_t value[_size];

         public:

         ByteArray():Abstract <_type>() {}

         /*!
          * Constructor.
          *
          * @param [in] _value   initial value for UID.
          */
         ByteArray(uint8_t _value[_size]):Abstract <_type>()
         {
            memcpy (value, _value, _size * sizeof(uint8_t));
         }

         /*!
          * Constructor.
          *
          * @param [in] _value   initial fill value for UID.
          */
         ByteArray(uint8_t _value):Abstract <_type>()
         {
            memset (value, _value, _size * sizeof(uint8_t));
         }

         //! Minimum pack/unpack required data size.
         static constexpr uint16_t min_size = UID_T::min_size + _size;

         uint16_t size () const
         {
            return min_size;
         }

         uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const
         {
            SERIALIZABLE_CHECK (array, offset, min_size);

            offset += Abstract <_type>::pack (array, offset);

            offset += array.write (offset, (uint8_t) sizeof(value));

            for (uint8_t i = 0; i < sizeof(value); i++)
            {
               offset += array.write (offset, value[i]);
            }

            return min_size;
         }

         uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0)
         {
            SERIALIZABLE_CHECK (array, offset, min_size);

            offset += Abstract <_type>::unpack (array, offset);

            uint8_t size;
            offset += array.read (offset, size);

            assert (size == sizeof(value));

            if (size != sizeof(value))
            {
               return 0;
            }

            for (uint8_t i = 0; i < size; i++)
            {
               offset += array.read (offset, value[i]);
            }

            return min_size;
         }

         // ===================================================================
         // API
         // ===================================================================

         int compare (const UID_T &other) const
         {
            int res = Abstract <_type>::compare (other);
            return (res ==
                    0 ? memcmp (value, ((_Class *) &other)->value, sizeof(value)) : res);
         }

         // =============================================================================
         // Array style API.
         // =============================================================================

         /*!
          * Get byte at the given @c index.
          *
          * @param [in] index index to get the byte from.
          *
          * @return  the byte at the given index.
          */
         uint8_t const &operator [](uint16_t index) const
         {
            return value[index];
         }

         /*!
          * Get byte at the given @c index.
          *
          * @param [in] index index to get the byte from.
          *
          * @return  the byte at the given index.
          */
         uint8_t &operator [](uint16_t index)
         {
            return value[index];
         }

         /*!
          * Get byte at the given @c index, asserting that the index is
          * within the correct range.
          *
          * @warning the assert is only in effect if NDEBUG is not defined.
          *
          * @param [in] index index to get the byte from.
          *
          * @return  the byte at the given index.
          */
         uint8_t const &at (uint16_t index) const
         {
            assert (index < _size);
            return value[index];
         }

         /*!
          * Get byte at the given @c index, asserting that the index is
          * within the correct range.
          *
          * @warning the assert is only in effect if NDEBUG is not defined.
          *
          * @param [in] index index to get the byte from.
          *
          * @return  the byte at the given index.
          */
         uint8_t &at (uint16_t index)
         {
            assert (index < _size);
            return value[index];
         }

         // =============================================================================
         // Helper API
         // =============================================================================

         /*!
          * Fill the underlining byte array with the given value.
          *
          * @param byte    the value to be used to fill the byte array.
          */
         void fill (uint8_t byte)
         {
            memset (value, byte, sizeof(value));
         }

         /*!
          * Fill the underlining byte array with 0.
          */
         void clear ()
         {
            memset (value, 0, sizeof(value));
         }

         /*!
          * Return the number of bytes in the underlining byte array.
          *
          * @return  number of bytes in the underlining byte array.
          */
         static uint16_t length ()
         {
            return _size;
         }
      };

      /*!
       * DECT UID class.
       */
      struct DECT:public ByteArray <DECT, 5, DECT_UID>
      {
         //! Number of bytes in a RFPI UID.
         constexpr static uint8_t SIZE = 5;

         DECT():ByteArray <DECT, 5, DECT_UID>(0xFF)
         {}

         /*!
          * Constructor.
          *
          * @param [in] _value   initial value for UID.
          */
         DECT(uint8_t _value[5]):ByteArray <DECT, 5, DECT_UID>(_value)
         {}

         // ===================================================================
         // Cloneable
         // ===================================================================

         DECT *clone () const
         {
            return new DECT (*this);
         }
      };

      /*!
       * IEEE MAC-48b UID class.
       */
      struct MAC:public ByteArray <MAC, 6, MAC_UID>
      {
         //! Number of bytes in a MAC UID.
         constexpr static uint8_t SIZE = 6;

         MAC():ByteArray <MAC, 6, MAC_UID>()
         {}

         MAC(uint8_t _value[6]):ByteArray <MAC, 6, MAC_UID>(_value)
         {}

         // ===================================================================
         // Cloneable
         // ===================================================================

         MAC *clone () const
         {
            return new MAC (*this);
         }
      };

      /*!
       * URI UID class.
       */
      struct URI:public Abstract <URI_UID>
      {
         std::string value;

         URI()
         {}

         URI(const std::string &value):
            value (value)
         {}

         uint16_t size () const
         {
            return Abstract <URI_UID>::size () + value.size ();
         }

         uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const
         {
            SERIALIZABLE_CHECK (array, offset, size ());

            uint16_t start = offset;

            offset += Abstract <URI_UID>::pack (array, offset);

            assert (value.size () <= 0xFF);
            offset += array.write (offset, (uint8_t) value.size ());

            for (uint8_t i = 0; i < value.size (); i++)
            {
               offset += array.write (offset, (uint8_t) value[i]);
            }

            return offset - start;
         }

         uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0)
         {
            SERIALIZABLE_CHECK (array, offset, min_size);

            uint16_t start = offset;

            offset += Abstract <URI_UID>::unpack (array, offset);

            uint8_t size;
            offset += array.read (offset, size);

            SERIALIZABLE_CHECK (array, offset, size);

            value = std::string (size, 0);

            for (uint8_t i = 0; i < size; i++)
            {
               uint8_t c;
               offset  += array.read (offset, c);
               value[i] = c;
            }

            return offset - start;
         }

         // ===================================================================
         // Cloneable
         // ===================================================================

         URI *clone () const
         {
            return new URI (*this);
         }

         // ===================================================================
         // API
         // ===================================================================

         int compare (const UID_T &other) const
         {
            int res = Abstract <URI_UID>::compare (other);
            return (res == 0 ? value.compare (((URI *) &other)->value) : res);
         }

         /*!
          * Return the string value associated with this URI.
          *
          * @return  the string associated with this URI.
          */
         std::string str () const
         {
            return value;
         }
      };

      /*!
       * Wrapper around UID_T pointer's.
       *
       * This class can either wrap an existing pointer (i.e. a pointer to an object it doesn't own)
       * or wrap a pointer to an object that was created based on an existing object. In this
       * case the clone object is owned by this class instance.
       *
       * The destructor of this class will @c delete the object it owns.
       */
      class UID:public HF::Common::Serializable
      {
         //!< Underling UID_T pointer.
         UID_T *_raw;

         //! Indicate if the wrapped pointer should be deleted when this object is deleted.
         bool owner;

         public:

         UID():_raw (new NONE ()), owner (true)
         {}

         /*!
          * Constructor.
          *
          * @param [in] _uid    pointer to the UID being wrapped.
          * @param [in] _owner  take ownership of the pointer being wrapped.
          */
         UID(UID_T *_uid, bool _owner = false):
            _raw (_uid), owner (_owner)
         {
            assert (_uid != nullptr);
         }

         /*!
          * Move constructor.
          *
          * @param [in] other    UID to move from.
          */
         UID(UID &&other):_raw (other._raw), owner (other.owner)
         {
            other.owner = false;
         }

         /*!
          * Copy constructor.
          *
          * The underling UID_T is cloned and this object takes ownership of it.
          *
          * @param [in] other    UID to copy from.
          */
         UID(const UID &other):_raw (other._raw->clone ()), owner (true)
         {}

         virtual ~UID()
         {
            if (owner)
            {
               delete _raw;
            }
         }

         // =============================================================================
         // API
         // =============================================================================

         //! @copydoc HF::UID::UID_T::type
         uint8_t type () const
         {
            return _raw->type ();
         }

         bool operator ==(const UID &other) const
         {
            return (this->_raw->compare (*(other._raw)) == 0);
         }

         bool operator !=(const UID &other) const
         {
            return !(*this == other);
         }

         uint16_t size () const
         {
            return _raw->size ();
         }

         uint16_t pack (Common::ByteArray &array, uint16_t offset) const
         {
            return _raw->pack (array, offset);
         }

         uint16_t unpack (const Common::ByteArray &array, uint16_t offset);

         // =============================================================================
         // Utils
         // =============================================================================

         /*!
          * Copy assignment operator.
          *
          * @param [in] other    UID to copy from.
          *
          * @return  a reference to this object.
          */
         UID &operator =(const UID &other)
         {
            // Ship if same object.
            if (this == &other)
            {
               return *this;
            }

            // Delete current wrapped object if owner.
            if (this->owner)
            {
               delete this->_raw;
            }

            // Clone wrapped UID_T and take ownership of the clone.
            this->_raw  = other._raw->clone ();
            this->owner = true;

            return *this;
         }

         /*!
          * Move assignment operator.
          *
          * @param [in] other    UID to move from.
          *
          * @return  a reference to this object.
          */
         UID &operator =(UID &&other)
         {
            std::swap (this->_raw, other._raw);
            std::swap (this->owner, other.owner);

            return *this;
         }

         /*!
          * Use the given pointer @c as the pointer of the underlining UID to wrap around
          * of.
          *
          * @warning the class takes ownership of the pointer and will delete the
          * associated object when it is destructed.
          *
          * @param _uid    pointer to the UID_T object instance to manage.
          *
          * @return  reference to self.
          */
         UID &operator =(UID_T *_uid)
         {
            if (owner)
            {
               delete this->_raw;
            }

            _raw  = _uid;
            owner = true;

            return *this;
         }

         //! @copydoc HF::UID::UID_T::compare
         int compare (const UID &other) const
         {
            return _raw->compare (*(other._raw));
         }

         //! @copydoc HF::UID::UID_T::compare
         int compare (const UID_T &other) const
         {
            return _raw->compare (other);
         }

         /*!
          * Get the underling wrapped UID_T pointer.
          *
          * @return the underling wrapped UID_T pointer.
          */
         UID_T const *raw () const
         {
            return _raw;
         }

         //! @copydoc HF::Attributes::IAttribute::changed
         float changed (const UID &other) const
         {
            UNUSED (other);
            return 0.0;
         }
      };

      /*! @} */

   }  // namespace UID

}  // namespace HF

// =============================================================================
// Helper Functions
// =============================================================================

/*!
 * @addtogroup uid_t
 * @{
 */

inline bool operator ==(const HF::UID::UID &lhs, const HF::UID::UID_T &rhs)
{
   return (lhs.compare (rhs) == 0);
}

inline bool operator ==(const HF::UID::UID_T &lhs, const HF::UID::UID &rhs)
{
   return (rhs.compare (lhs) == 0);
}

inline bool operator !=(const HF::UID::UID &lhs, const HF::UID::UID_T &rhs)
{
   return !(lhs == rhs);
}

inline bool operator !=(const HF::UID::UID_T &lhs, const HF::UID::UID &rhs)
{
   return !(lhs == rhs);
}

/*!
 * Convert the given @c uid into a string and write it to the given @c stream.
 *
 * @param [in] stream   out stream to write the string to.
 * @param [in] uid      device %UID to convert to a string.
 *
 * @return   <tt>stream</tt>
 */
std::ostream &operator <<(std::ostream &stream, const HF::UID::UID &uid);

/*! @} */

#endif /* HF_UIDS_H */
