// =============================================================================
/*!
 * @file       inc/hanfun/debug.h
 *
 * This file contains the prototypes of the debug functionality in HAN-FUN.
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

#ifndef HF_DEBUG_H
#define HF_DEBUG_H

#include <iostream>
#include <iomanip>

/*!
 * @addtogroup debug Debug
 *
 * This module contains the helper functions to aid in debugging HAN-FUN applications.
 * @{
 */
// =============================================================================
// Defines
// =============================================================================

//! Helper define for new-line and stream clear.
#define NL                   std::endl;std::cout.clear ();std::cerr.clear ()

#define HF_LOG_LEVEL_NONE    0   //!<  No debug messages will be displayed.
#define HF_LOG_LEVEL_ERROR   1   //!<  Only error messages will be displayed.
#define HF_LOG_LEVEL_WARN    2   //!<  Display warning and error messages.
#define HF_LOG_LEVEL_INFO    3   //!<  Display information, warning and error messages.
#define HF_LOG_LEVEL_DEBUG   4   //!<  Display debug, information, warning and error messages.
#define HF_LOG_LEVEL_TRACE   5   //!<  Display all messages.

// Set default log level to HF_LOG_LEVEL_INFO.
#ifndef HF_LOG_LEVEL
   #define HF_LOG_LEVEL      HF_LOG_LEVEL_INFO
#endif

#if HF_LOG_LEVEL >= HF_LOG_LEVEL_ERROR
   #define ERROR             std::cerr.clear ();std::cerr << "[ERROR] "
#else
   #define ERROR             std::cerr.setstate (std::ios_base::badbit);std::cerr
#endif

#if HF_LOG_LEVEL >= HF_LOG_LEVEL_WARN
   #define WARN              std::cerr.clear ();std::cerr << "[WARN ] "
#else
   #define WARN              std::cerr.setstate (std::ios_base::badbit);std::cerr
#endif

#if HF_LOG_LEVEL >= HF_LOG_LEVEL_INFO
   #define INFO              std::cout.clear ();std::cout << "[INFO ] "
#else
   #define INFO              std::cout.setstate (std::ios_base::badbit);std::cout
#endif

#if HF_LOG_LEVEL >= HF_LOG_LEVEL_DEBUG
   #define DEBUG             std::cout.clear ();std::cout << "[DEBUG] "
#else
   #define DEBUG             std::cout.setstate (std::ios_base::badbit);std::cout
#endif

#if HF_LOG_LEVEL >= HF_LOG_LEVEL_TRACE
   #define TRACE             std::cout.clear ();std::cout << "[TRACE] "
#else
   #define TRACE             std::cout.setstate (std::ios_base::badbit);std::cout
#endif

#define APP                  std::cout.clear ();std::cout

//! Log messages with the level given by @c X
#define LOG(X)   X

namespace HF
{
   /*!
    * Top-level namespace for debug helper functions.
    */
   namespace Debug
   {
      template<typename T>
      struct Hex
      {
         static_assert (std::is_unsigned <T>::value, "Type MUST be an unsigned integer");

         static constexpr size_t size = 2 * sizeof(T);

         T                       value;

         Hex(T _value):value (_value)
         {}
      };

      template<typename T>
      inline std::ostream &operator <<(std::ostream &stream, Hex <T> hex)
      {
         std::ios_base::fmtflags ff = stream.flags ();
         char f                     = stream.fill (' ');

         stream << std::uppercase << std::right << std::hex << std::setfill ('0')
                << std::setw (hex.size) << (int) hex.value;

         stream << std::setfill (f) << std::setiosflags (ff);
         return stream;
      }

   }  // namespace Debug

}  // namespace HF

/*! @} */

#endif /* HF_DEBUG_H */
