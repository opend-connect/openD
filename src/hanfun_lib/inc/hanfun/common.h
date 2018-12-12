// =============================================================================
/*!
 * @file       inc/hanfun/common.h
 *
 * This file contains the common defines for the HAN-FUN library.
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

#ifndef HF_COMMON_H
#define HF_COMMON_H

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cmath>

#include <algorithm>
#include <array>
#include <forward_list>
#include <functional>
#include <iterator>
#include <limits>
#include <list>
#include <memory>
#include <set>
#include <string>
#include <type_traits>
#include <vector>

#include "hanfun/dlg_assert.h"

#include "hanfun/gcc.h"
#include "hanfun/version.h"
#include "hanfun/config.h"

/*!
 * @addtogroup common  Common
 * This module contains common helper classes, functions and definitions.
 */

// =============================================================================
// Defines
// =============================================================================

/*!
 * @ingroup common
 *
 * Helper macro to remove warning about unused function/method argument.
 */
#define UNUSED(x)   (void) x

/*!
 * @ingroup common
 *
 * Helper macro to check if the given @c __array has enough size so @c __size bytes
 * can be written/read from the given @c __offset.
 *
 * @warning This macro issues a <tt>return 0;</tt> when there aren't enough resources, i.e.
 * the @c __array size is not sufficient for reading/writing to.
 *
 * @param [in] __array     reference to the ByteArray containing the data.
 * @param [in] __offset    offset index to check available data from.
 * @param [in] __size      number of bytes required.
 */
#define SERIALIZABLE_CHECK(__array, __offset, __size) \
   {                                                  \
      assert (__array.available (__offset, __size));  \
                                                      \
      if (!__array.available (__offset, __size))      \
      {                                               \
         return 0;                                    \
      }                                               \
   }

// =============================================================================
// API
// =============================================================================

/*!
 * Top-level namespace for the HAN-FUN library.
 */
namespace HF
{
   /*!
    * @addtogroup common Common
    * @{
    */

   constexpr uint8_t CORE_VERSION       = 1; //!< %Core %Service & %Interfaces major version supported.
   constexpr uint8_t PROFILES_VERSION   = 1; //!< %Profiles major version supported.
   constexpr uint8_t INTERFACES_VERSION = 1; //!< %Interfaces major version supported.

   /*! @} */

   /*!
    * This namespace contains helper classes to be used though out the HAN-FUN
    * implementation.
    */
   namespace Common
   {
      /*!
       * @addtogroup common
       * @{
       */
      // =============================================================================
      // Helper Classes.
      // =============================================================================

      /*!
       * These constants represent precisions that a measurement can be in.
       */
      typedef enum _Precision
      {
         BASE  = 0x00, //!< Base unit.
         MILI  = 0x10, //!< Mili
         MICRO = 0x11, //!< Micro
         NANO  = 0x12, //!< Nano
         PICO  = 0x13, //!< Pico
         KILO  = 0x20, //!< Kilo
         MEGA  = 0x21, //!< Mega
         GIGA  = 0x22, //!< Giga
         TERA  = 0x23, //!< Tera
      } Precision;

      /*!
       * This represents the type of time that is associated with a
       * time measurement.
       */
      typedef enum _Time
      {
         UPTIME = 0x00, //!< Uptime.
         UTC    = 0x01, //!< UTC time.
      } Time;

      /*!
       * This class represents a byte array.
       *
       * The method in this class are used to serialize the messages to be sent over the
       * network, converting between the host's endianness and the big-endian network format.
       */
      struct ByteArray:public std::vector <uint8_t>
      {
         /*!
          * Create a byte array with the given initial size.
          *
          * @param [in] size the initial size of the byte array.
          */
         ByteArray(uint16_t size = 0);

         /*!
          * Create a byte array with the given initial data.
          *
          * @param [in] data    data to initialize the byte array with.
          * @param [in] size    size in bytes of the data.
          */
         ByteArray(const uint8_t data[], const uint16_t size);

         /*!
          * Create byte array from the values in the given list.
          *
          * @param [in] raw  values to add to the byte array.
          */
         ByteArray(std::initializer_list <uint8_t> raw):vector (raw)
         {}

         //! Destructor
         virtual ~ByteArray() {}

         /*!
          * Write a byte into the array at the given @c offset.
          *
          * @param [in] offset  offset to write the byte to.
          * @param [in] data    byte value to write to the array.
          *
          * @return  number of bytes written (1).
          */
         uint16_t write (uint16_t offset, uint8_t data);

         /*!
          * Write a word in the big endian format into the
          * array at the given @c offset.
          *
          * @param [in] offset  offset to write the word to.
          * @param [in] data    word value to write to the array.
          *
          * @return  number of bytes written (2).
          */
         uint16_t write (uint16_t offset, uint16_t data);

         /*!
          * Write a double-word in big endian format into the
          * array at the given @c offset.
          *
          * @param [in] offset  offset to write the double-word to.
          * @param [in] data    double-word value to write to the array.
          *
          * @return  number of bytes written (4).
          */
         uint16_t write (uint16_t offset, uint32_t data);

         //! @copydoc ByteArray::write (uint16_t, uint8_t)
         uint16_t write (uint16_t offset, bool data)
         {
            return write (offset, static_cast <uint8_t>(data));
         }

         //! @copydoc ByteArray::write (uint16_t, uint8_t)
         template<typename T>
         uint16_t write (uint16_t offset, T data)
         {
            typedef typename std::make_unsigned <T>::type Type;
            return write (offset, static_cast <Type>(data));
         }

         /*!
          * Read the byte at @c offset into @c data.
          *
          * @param [in]  offset  offset to read the byte from.
          * @param [out] data    reference to save the read value to.
          *
          * @return  number of bytes read (1).
          */
         uint16_t read (uint16_t offset, uint8_t &data) const;

         /*!
          * Read the word in big-endian format at @c offset into @c data.
          *
          * @param [in]  offset  offset to read the word from.
          * @param [out] data    reference to save the read value to.
          *
          * @return  number of bytes read (2).
          */
         uint16_t read (uint16_t offset, uint16_t &data) const;

         /*!
          * Read the double-word in big-endian format at @c offset into @c data.
          *
          * @param [in]  offset  offset to read the double-word from.
          * @param [out] data    reference to save the read value to.
          *
          * @return  number of bytes read (4).
          */
         uint16_t read (uint16_t offset, uint32_t &data) const;

         //! @copydoc  ByteArray::read (uint16_t, uint8_t)
         uint16_t read (uint16_t offset, bool &data) const
         {
            uint8_t  temp;
            uint16_t result = read (offset, temp);

            data = (temp & 0x01) != 0;

            return result;
         }

         //! @copydoc  ByteArray::read (uint16_t, uint8_t)
         template<typename T>
         uint16_t read (uint16_t offset, T &data) const
         {
            typedef typename std::make_unsigned <T>::type Type;
            Type temp;
            uint16_t result = read (offset, temp);

            data = static_cast <T>(temp);

            return result;
         }

         /*!
          * Check if the array as at least @c expected bytes
          * available from the given @c offset.
          *
          * @param [in] offset     the offset from where to start counting.
          * @param [in] expected   the number of byte required.
          *
          * @retval  true if enough data is available,
          * @retval  false otherwise.
          */
         bool available (uint16_t offset, uint16_t expected) const
         {
            return expected <= available (offset);
         }

         /*!
          * Return the number of data bytes available from the given @c offset.
          *
          * @param [in] offset   the offset from where to start counting.
          *
          * @return  number of data bytes available from the given @c offset.
          */
         uint16_t available (uint16_t offset) const
         {
            return (size () >= offset ? size () - offset : 0);
         }

         bool operator ==(const ByteArray &other)
         {
            return (this->size () == other.size () &&
                    std::equal (this->begin (), this->end (), other.begin ()));
         }

         bool operator !=(const ByteArray &other)
         {
            return !(*this == other);
         }

         /*!
          * Extend the byte array by the given size.
          *
          * This is the same as calling : array.reserve(array.size() + _size)
          *
          * @param [in] _size number of bytes to extent the array by.
          */
         void extend (uint16_t _size)
         {
            vector <uint8_t>::reserve (size () + _size);
         }

         /*!
          * Ensure that the byte array can hold the number of bytes given
          * in @c _size, from the given @c offset.
          *
          * @param [in] _offset  offset index to check from.
          * @param [in] _size    number of bytes to ensure that exist.
          */
         void ensure (uint16_t _offset, uint16_t _size)
         {
            if (!available (_offset, _size))
            {
               _size = _size - available (_offset) + std::max <int16_t>((int16_t) (_offset - size ()), 0);
               vector <uint8_t>::reserve (size () + _size);
               std::fill_n (back_inserter (*this), _size, 0);
            }
         }
      };

      template<typename T>
      struct SimpleList:public std::forward_list<T>
      {};

      // =============================================================================
      // Common Interfaces
      // =============================================================================

      /*!
       * This represents the common interface for message serialization.
       */
      struct Serializable
      {
         //! Destructor
         virtual ~Serializable() {}

         /*!
          * Number bytes needed to serialize the message.
          *
          * @return  number of bytes the message requires to be serialized.
          */
         virtual uint16_t size () const = 0;

         /*!
          * Write the object on to a ByteArray so it can be sent over the network.
          *
          * The buffer passed in __MUST__ have enough size to hold the serialized object, e.g.,
          *
          * @code
          * Serializable obj;
          * ByteArray payload(obj.size());
          * obj.pack(payload);
          * @endcode
          *
          * @param [inout] array   ByteArray reference to write the object to.
          * @param [in]    offset  offset to start writing to.
          *
          * @return  the number of bytes written.
          */
         virtual uint16_t pack (ByteArray &array, uint16_t offset = 0) const = 0;

         /*!
          * Read a message from a ByteArray.
          *
          * @param [in] array   ByteArray reference to read the message from.
          * @param [in] offset  offset to start reading from.
          *
          * @return  the number of bytes read.
          */
         virtual uint16_t unpack (const ByteArray &array, uint16_t offset = 0) = 0;
      };

      /*!
       * Wrapper for classes that implement the Serializable concept.
       *
       * @tparam T   data type to warp.
       *
       * @warning T should be POD (Plain Old Data)
       */
      template<typename T, typename = void>
      struct SerializableHelper:public Serializable
      {
         //! Data type instance wrapped.
         T data;

         SerializableHelper()
         {
            memset (&data, 0, sizeof(T));
         }

         SerializableHelper(T data):data (data)
         {}

         uint16_t size () const
         {
            return data.size ();
         }

         uint16_t pack (ByteArray &array, uint16_t offset = 0) const
         {
            SERIALIZABLE_CHECK (array, offset, size ());
            return data.pack (array, offset);
         }

         uint16_t unpack (const ByteArray &array, uint16_t offset = 0)
         {
            SERIALIZABLE_CHECK (array, offset, size ());
            return data.unpack (array, offset);
         }

         //! @copydoc HF::Attributes::IAttribute::compare
         int compare (const SerializableHelper <T> &other) const
         {
            return data.compare (other.data);
         }

         //! @copydoc HF::Attributes::IAttribute::changed
         float changed (const SerializableHelper <T> &other) const
         {
            return data.changed (other.data);
         }
      };

      /*!
       * Wrapper to pointers for classes that implement the Serializable concept.
       *
       * @tparam T   pointer for the data type to warp.
       */
      template<typename T>
      struct SerializableHelper <T, typename std::enable_if <std::is_pointer <T>::value>::type> :
         public Serializable
      {
         //! Pointer to the wrapped instance.
         T data;

         SerializableHelper()
         {
            data = nullptr;
         }

         SerializableHelper(T data):data (data)
         {}

         uint16_t size () const
         {
            return data->size ();
         }

         uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const
         {
            SERIALIZABLE_CHECK (array, offset, size ());
            return data->pack (array, offset);
         }

         uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0)
         {
            SERIALIZABLE_CHECK (array, offset, size ());
            return data->unpack (array, offset);
         }

         //! @copydoc HF::Attributes::IAttribute::compare
         int compare (const SerializableHelper <T> &other) const
         {
            return data->compare (other.data);
         }

         //! @copydoc HF::Attributes::IAttribute::changed
         float changed (const SerializableHelper <T> &other) const
         {
            return data->changed (other.data);
         }
      };

      /*!
       * Wrapper for base integer types implementing the  Serializable API.
       *
       * @tparam T   integral data type to warp.
       */
      template<typename T>
      struct SerializableHelper <T, typename std::enable_if <std::is_integral <typename std::remove_reference <T>::type>::value>::type> :
         public Common::Serializable
      {
         //! Data type instance wrapped.
         T data;

         SerializableHelper()
         {
            data = 0;
         }

         SerializableHelper(T data):data (data) {}

         //! Minimum pack/unpack required data size.
         static constexpr uint16_t min_size = sizeof(T);

         uint16_t size () const
         {
            return min_size;
         }

         uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const
         {
            SERIALIZABLE_CHECK (array, offset, min_size);

            array.write (offset, data);

            return min_size;
         }

         uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0)
         {
            SERIALIZABLE_CHECK (array, offset, min_size);

            array.read (offset, data);

            return min_size;
         }

         //! @copydoc HF::Attributes::IAttribute::compare
         int compare (const SerializableHelper <T> &other) const
         {
            return data - other.data;
         }

         //! @copydoc HF::Attributes::IAttribute::changed
         float changed (const SerializableHelper <T> &other) const
         {
            return (((float) (data - other.data)) / other.data);
         }
      };

      /*!
       * Wrapper for Common::ByteArray implementing the  Serializable API.
       */
      template<>
      struct SerializableHelper <Common::ByteArray> :
         public Common::Serializable
      {
         Common::ByteArray data;

         SerializableHelper()
         {}

         SerializableHelper(Common::ByteArray _data):data (_data) {}

         //! Minimum pack/unpack required data size.
         static constexpr uint16_t min_size = sizeof(uint8_t);

         uint16_t size () const
         {
            return min_size + data.size ();
         }

         uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const
         {
            SERIALIZABLE_CHECK (array, offset, size ());

            uint16_t start = offset;

            offset += array.write (offset, (uint8_t) data.size ());

            auto it = array.begin ();
            std::advance (it, offset);

            std::copy (data.begin (), data.end (), it);

            offset += data.size ();

            return offset - start;
         }

         uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0)
         {
            SERIALIZABLE_CHECK (array, offset, min_size);

            uint16_t start = offset;

            uint8_t  _size = 0;
            offset += array.read (offset, _size);

            SERIALIZABLE_CHECK (array, offset, _size);

            auto it = array.begin ();
            std::advance (it, offset);

            std::copy_n (it, _size, data.begin ());

            offset += _size;

            return offset - start;
         }

         //! @copydoc HF::Attributes::IAttribute::compare
         int compare (const SerializableHelper <Common::ByteArray> &other) const
         {
            int res = data.size () - other.size ();

            if (res == 0)
            {
               return memcmp (data.data (), other.data.data (), data.size ());
            }

            return res;
         }

         //! @copydoc HF::Attributes::IAttribute::changed
         float changed (const SerializableHelper <Common::ByteArray> &other) const
         {
            UNUSED (other);
            return 0.0;
         }
      };

      /*!
       * Wrapper for std::string implementing the Serializable API.
       */
      template<>
      struct SerializableHelper <std::string> :
         public Common::Serializable
      {
         std::string data;

         SerializableHelper()
         {}

         SerializableHelper(std::string _data):data (_data) {}

         //! Minimum pack/unpack required data size.
         static constexpr uint16_t min_size = sizeof(uint8_t);

         static uint16_t size (const std::string &data)
         {
            return min_size + data.size ();
         }

         uint16_t size () const
         {
            return size (data);
         }

         uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const
         {
            SERIALIZABLE_CHECK (array, offset, size ());

            uint16_t start = offset;

            offset += array.write (offset, (uint8_t) data.size ());

            auto it = array.begin ();
            std::advance (it, offset);

            std::copy (data.begin (), data.end (), it);

            offset += data.size ();

            return offset - start;
         }

         uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0)
         {
            SERIALIZABLE_CHECK (array, offset, min_size);

            uint16_t start = offset;

            uint8_t  _size = 0;
            offset += array.read (offset, _size);

            SERIALIZABLE_CHECK (array, offset, _size);

            auto it = array.begin ();
            std::advance (it, offset);

            data.resize (_size);

            std::copy_n (it, _size, data.begin ());

            offset += _size;

            return offset - start;
         }

         //! @copydoc HF::Attributes::IAttribute::compare
         int compare (const SerializableHelper <std::string> &other) const
         {
            return strcmp (data.data (), other.data.data ());
         }

         //! @copydoc HF::Attributes::IAttribute::changed
         float changed (const SerializableHelper <std::string> &other) const
         {
            UNUSED (other);
            return 0.0;
         }
      };

      /*!
       * Wrapper for std::vector implementing the Serializable API.
       *
       * @remark This class will unpack the same number of bytes as the
       * size of the @c data vector.
       */
      template<>
      struct SerializableHelper < std::vector < uint8_t >>:
         public Common::Serializable
      {
         std::vector <uint8_t> data;

         SerializableHelper()
         {}

         SerializableHelper(std::vector <uint8_t> _data):data (_data) {}

         uint16_t size () const
         {
            return data.size ();
         }

         uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const
         {
            SERIALIZABLE_CHECK (array, offset, size ());

            uint16_t start = offset;

            auto it        = array.begin ();
            std::advance (it, offset);

            std::copy (data.begin (), data.end (), it);

            offset += data.size ();

            return offset - start;
         }

         uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0)
         {
            SERIALIZABLE_CHECK (array, offset, size ());

            uint16_t start = offset;

            auto it        = array.begin ();
            std::advance (it, offset);

            std::copy_n (it, data.size (), data.begin ());

            offset += data.size ();

            return offset - start;
         }

         //! @copydoc HF::Attributes::IAttribute::compare
         int compare (const SerializableHelper < std::vector < uint8_t >> &other) const
         {
            return memcmp (data.data (), other.data.data (), data.size ());
         }

         //! @copydoc HF::Attributes::IAttribute::changed
         float changed (const SerializableHelper < std::vector < uint8_t >> &other) const
         {
            UNUSED (other);
            return 0.0;
         }
      };

      /*!
       * This class represents the interface that cloneable objects need
       * to implement.
       */
      template<typename T>
      struct Cloneable
      {
         /*!
          * Create a clone object of the object where this method is being called.
          *
          * @return  a new object that is a clone of this object.
          */
         virtual T *clone () const = 0;
      };

      /*!
       * Commands result codes.
       */
      typedef enum _Result
      {
         OK                = 0x00, //!< Request OK
         FAIL_AUTH         = 0x01, //!< Fail - Not Authorized
         FAIL_ARG          = 0x02, //!< Fail - Invalid Argument
         FAIL_SUPPORT      = 0x03, //!< Fail - Not Supported
         FAIL_RO_ATTR      = 0x04, //!< Fail - Read only attribute.
         FAIL_READ_SESSION = 0x20, //!< Fail - Read Session not established
         FAIL_MODIFIED     = 0x21, //!< Fail - Entries table modified
         FAIL_RESOURCES    = 0xFE, //!< Fail - Not enough resources
         FAIL_UNKNOWN      = 0xFF, //!< Fail - Unknown reason
      } Result;

      /*!
       * Interface UID.
       */
      struct Interface
      {
         uint16_t role : 1;  //!< Interface role : Server or Client.
         uint16_t id   : 15; //!< Identifier of the interface. @see Interface::UID.

         /*!
          * Constructor
          *
          * @param [in] id    interface UID.
          * @param [in] role  interface role.
          */
         Interface(uint16_t id = 0, uint8_t role = 0):
            role (role), id (id)
         {}

         //! Minimum pack/unpack required data size.
         static constexpr uint16_t min_size = sizeof(uint16_t);   // Interface UID.

         //! @copydoc HF::Common::Serializable::size
         uint16_t size () const;

         //! @copydoc HF::Common::Serializable::pack
         uint16_t pack (Common::ByteArray &array, uint16_t offset = 0) const;

         //! @copydoc HF::Common::Serializable::unpack
         uint16_t unpack (const Common::ByteArray &array, uint16_t offset = 0);
      };

      // =============================================================================
      // Operators
      // =============================================================================

      inline bool operator ==(const Interface &lhs, const Interface &rhs)
      {
         return (lhs.role == rhs.role) && (lhs.id == rhs.id);
      }

      inline bool operator !=(const Interface &lhs, const Interface &rhs)
      {
         return !(lhs == rhs);
      }

      inline bool operator <(Interface const &lhs, Interface const &rhs)
      {
         return (lhs.role < rhs.role) || (lhs.role == rhs.role && lhs.id < rhs.id);
      }

      // =============================================================================
      // Helper Classes
      // =============================================================================

      /*!
       * Simple raw pointer wrapper.
       */
      template<typename T>
      class Pointer
      {
         T *pointer;

         bool owner;

         public:

         /*!
          * Constructor
          *
          * @param [in] _pointer    pointer to wrap.
          * @param [in] _owner      boolean indicating if the underling pointer should
          *                         be deleted when this object is deleted.
          */
         Pointer(T *_pointer = nullptr, bool _owner = false):
            pointer (_pointer), owner (_owner)
         {}

         /*!
          * Constructor.
          *
          * @param [in] _pointer    pointer to wrap.
          */
         Pointer(T &_pointer):
            pointer (&_pointer), owner (false)
         {}

         /*!
          * Move constructor.
          *
          * @param [in] other original object.
          */
         Pointer(Pointer <T> &&other):pointer (nullptr), owner (false)
         {
            std::swap (this->pointer, other.pointer);
            std::swap (this->owner, other.owner);
         }

         /*!
          * Copy constructor.
          *
          * @param [in] other original object.
          */
         Pointer(Pointer <T> &other):pointer (other.pointer), owner (other.owner)
         {
            other.owner = false;
         }

         ~Pointer()
         {
            if (owner)
            {
               delete pointer;
            }
         }

         T &operator *() const
         {
            return *pointer;
         }

         T *operator ->() const
         {
            return pointer;
         }

         bool operator ==(const Pointer <T> &other) const
         {
            return pointer == other.pointer;
         }

         bool operator !=(const Pointer <T> &other) const
         {
            return !(*this == other);
         }

         bool operator ==(const T *other) const
         {
            return pointer == other;
         }

         bool operator !=(const T *other) const
         {
            return pointer != other;
         }

         bool operator ==(const T &other) const
         {
            return pointer == &other;
         }

         bool operator !=(const T &other) const
         {
            return pointer != &other;
         }

         /*!
          * Assignment move operator.
          *
          * @param [in] other object to move from.
          *
          * @return  reference to this object.
          */
         Pointer <T> &operator =(Pointer <T> &&other)
         {
            if (this->owner)
            {
               delete this->pointer;
            }

            this->pointer = other.pointer;
            this->owner   = other.owner;

            other.owner   = false;

            return *this;
         }
      };

      /*!
       * Basic API for persistent storage implementations.
       */
      template<typename T>
      struct IEntries
      {
         // =============================================================================
         // API
         // =============================================================================

         /*!
          * Return the number of entries in the container.
          *
          * @return  the number of entries in the container.
          */
         virtual uint16_t size () const = 0;

         /*!
          * Store the given bind @c entry to persistent storage.
          *
          * @param [in] entry the bind entry to store.
          *
          * @retval  Common::Result::OK if the bind entry was saved,
          * @retval  Common::Result::FAIL_UNKNOWN otherwise.
          */
         virtual Result save (const T &entry) = 0;

         /*!
          * Destroy the given @c entry in the persistent storage.
          *
          * @param [in] entry   reference to the bind entry to erase.
          *
          * @retval  Common::Result::OK, if the entry was destroyed.
          * @retval  Common::Result::FAIL_ARG otherwise.
          */
         virtual Result destroy (const T &entry) = 0;
      };

      /*!
       * Convert a percentage value into the [0,std::numeric_limits<T>::max()] range.
       *
       * @param [in] value    the percentage value to convert.
       * @tparam T   integer type to convert to.
       *
       * @return  the value equivalent to the percentage in the
       *          [0,std::numeric_limits<T>::max()] range.
       */
      template<typename T, typename P = float>
      T from_percent (P value)
      {
         return static_cast <T>(round ((static_cast <float>(value) * std::numeric_limits <T>::max ()) / 100.0));
      }

      /*!
       * Convert a value in the [0,std::numeric_limits<T>::max()] range into a
       * percentage.
       *
       * @param [in] value    the value to convert to the percentage.
       * @tparam T   integer type to convert from.
       *
       * @return  the percentage value.
       */
      template<typename T, typename P = float>
      P to_percent (T value)
      {
         return static_cast <P>(round ((static_cast <float>(value) * 100.0) / std::numeric_limits <T>::max ()));
      }

      /*! @} */
   }  // namespace Common

}  // namespace HF

/*!
 * @addtogroup common
 * @{
 */

// =============================================================================
// Stream Helpers
// =============================================================================

/*!
 * Convert the given @c byte into a string and write it to the given @c stream.
 *
 * @param [in] stream   out stream to write the string to.
 * @param [in] byte     byte value to convert to a string.
 *
 * @return   <tt>stream</tt>
 */
std::ostream &operator <<(std::ostream &stream, const uint8_t byte);

/*!
 * Convert the given @c packet into a string and write it to the given @c stream if
 * <tt>stream == std::cout || stream == std::cerr</tt>. Otherwise send bytes to stream.
 *
 * @param [in] stream   out stream to write the string/bytes to.
 * @param [in] array    byte array to convert to a string/sent to the stream.
 *
 * @return   <tt>stream</tt>
 */
std::ostream &operator <<(std::ostream &stream, const HF::Common::ByteArray &array);

/*!
 * Convert the given @c interface into a string and write it to the given @c stream.
 *
 * @param [in] stream      out stream to write the string to.
 * @param [in] interface   interface value to convert to a string.
 *
 * @return   <tt>stream</tt>
 */
std::ostream &operator <<(std::ostream &stream, const HF::Common::Interface interface);

/*! @} */

#endif /* HF_COMMON_H */
