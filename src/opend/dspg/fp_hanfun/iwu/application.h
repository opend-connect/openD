/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       application.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger
 * @brief      iwu application api.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   HANFUN IWU
 *             This file specifies the IWU api for the application.
 * @{
 */

#ifndef HF_APP_H
#define HF_APP_H

#include "hanfun.h"
#include "hanfun/debug.h"


namespace HF
{
   /* Namespace for hanfun demo application. */
   namespace Application
   {
      /*!
       * @brief   Initialize app.
       *
       * @details Initialize the client side demo application.
       *
       * @param transport Reference to the transport layer to use.
       * @param argc Holds the number of parameters.
       * @param argv Pointer of the pointer parameters.
       */
      int Initialize (HF::Transport::Layer &transport, int argc, char **argv);

      /**
       * @brief   Handle command.
       *
       * @details Handle the terminal user input.
       *
       * @param   command Command to run.
       *
       * @retval  True if quit command is requested.
       */
      bool Handle (std::string command);

      /**
       * @brief   Save.
       *
       * @details Save application configuration.
       */
      void Save ();

      /**
       * @brief   Saved.
       *
       * @details Callback indicating that the application configuration has been saved.
       */
      void Saved ();

      /**
       * @brief   Restore.
       *
       * @details Restore application configuration.
       */
      void Restore ();

      /**
       * @brief   Restored.
       *
       * @details Callback indicating that the application configuration has been restored.
       */
      void Restored ();

#if HF_APP_EXT_REG
      /**
       * Enable/Disable registration mode.
       *
       * @param mode True - enable registration, False - disable registration.
       *
       * @retval True if the operation was successful;
       */
      bool Registration (bool mode);

      /**
       * @brief   Deregister.
       *
       * @details Deregister the device with the given HAN-FUN Address.
       *
       * @param address HAN-FUN address of the device to deregister.
       */
      void Deregister (uint16_t address);
#endif

   }
}

#endif /* HF_APP_H */
