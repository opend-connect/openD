// =============================================================================
/*!
 * @file       inc/hanfun/gcc.h
 *
 * This file contains workarounds for the implementation on C++11 in older versions
 * of GCC.
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

#ifndef HF_GCC_H
#define HF_GCC_H

#if __cplusplus < 201103
const class nullptr_t
{
   public:

   /* Return 0 for any class pointer */
   template<typename T>
   operator T *() const
   {
      return 0;
   }

   /* Return 0 for any member pointer */
   template<typename T, typename U>
   operator T U::*() const
   {
      return 0;
   }

   /* Safe boolean conversion */
   operator void *() const
   {
      return 0;
   }

   template<typename T>
   bool operator ==(const T &other) const
   {
      return *this == other;
   }

   template<typename T>
   bool operator !=(const T &other) const
   {
      return *this != other;
   }

   private:

   /* Not allowed to get the address */
   void operator &() const;

}
nullptr = {};

   #define __attribute_deprecated__   __attribute__ ((deprecated))

#endif

#endif /* HF_GCC_H */
