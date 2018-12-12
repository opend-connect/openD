/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       fp_hanfun_app.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger
 * @brief      UDP client side app api.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   UDP client app api
 *             This file specifies the udp client app side.
 * @{
 */


#include "hanfun.h"
#include "hanfun/debug.h"
#include <iostream>
#include <string>
#include <map>
#include <iterator>

using namespace std;


class Command
{
  protected:

  const std::string keyCommand;
  const std::string usageCommand;

  public:

  static std::map <std::string, Command *> registry;

  Command(const char *key, const char *__usage):
    keyCommand (key), usageCommand (__usage)
  {}

  virtual ~Command(){};

  const std::string &key () const
  {
    return keyCommand;
  }

  const std::string usage (bool format = false) const
  {
    return usageCommand;
  }

  /**
   * @brief   Run specific command.
   *
   * @details Run the specific command with arguments.
   *
   * @param   args Arguments for the command.
   */
  virtual void run (std::vector <std::string> &args) = 0;

  /**
   * @brief   Add command object.
   *
   * @details Add the command pointer object to the registry.
   *
   * @param   command Command that should be added.
   */
  static void add (Command *command);

  /**
   * @brief   Ruc command with args.
   *
   * @details Execute the hanfun command with arguments.
   *
   * @param   cmd Reference to the command.
   * @param   args Arguments for the command.
   */
  static void run (std::string &cmd, std::vector <std::string> &args);

  /**
   * @brief   Help display.
   *
   * @details Display the help menu for the user.
   *
   * @param   stream Output stream of the help menu.
   */
  static std::ostream &help (std::ostream &stream);
};

/*! @} */
