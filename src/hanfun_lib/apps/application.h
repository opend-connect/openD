// =============================================================================
/*!
 * @file       apps/application.h
 *
 * This file contains the definitions for the HAN-FUN example applications.
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

#ifndef HF_APP_H
#define HF_APP_H

#include "hanfun.h"

#include "hanfun/debug.h"

// =============================================================================
// API
// =============================================================================

namespace HF
{
   /*!
    * @addtogroup examples Examples
    *
    * This module contains the classes for the provided example applications.
    * @{
    */

   /*!
    * This namespace contains the declaration of the functions that implement the
    * HAN-FUN example applications.
    */
   namespace Application
   {
      /*!
       * Initialize the application.
       *
       * @param [in] transport   reference to the transport layer to use.
       */
      void Initialize (HF::Transport::Layer &transport);

      /*!
       * Handle the command.
       *
       * @param [in] command  string containing the command issued by the user.
       *
       * @retval  true  quit command requested,
       * @retval  false otherwise.
       */
      bool Handle (std::string command);

      /*!
       * Save application configuration.
       */
      void Save ();

      /*!
       * Callback indicating that the application configuration has been
       * saved.
       */
      void Saved ();

      /*!
       * Restore application configuration.
       */
      void Restore ();

      /*!
       * Callback indicating that the application configuration has been
       * restored.
       */
      void Restored ();

#if HF_APP_EXT_REG
      /*!
       * Enable/Disable registration mode.
       *
       * @param mode    true - enable registration;
       *                false - disable registration;
       *
       * @retval  true if the operation was successful;
       * @retval  false otherwise.
       */
      bool Registration (bool mode);

      /*!
       * De-register the device with the given HAN-FUN Address.
       *
       * @param address    HAN-FUN address of the device to de-register.
       */
      void Deregister (uint16_t address);
#endif

   }  // namespace Application

   /*! @} */

}  // namespace HF

#endif /* HF_APP_H */
