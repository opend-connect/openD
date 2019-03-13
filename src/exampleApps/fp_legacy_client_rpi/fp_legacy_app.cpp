/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       fp_legacy_app.cpp
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger
 * @brief      fp legacy app implementation.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 */

#include <cstring>
#include <forward_list>
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <iterator>
#include <stdbool.h>
#include "fp_legacy_app.h"
#include <../../json/single_include/nlohmann/json.hpp>

using json = nlohmann::json;

/* json library object. */
json j;

/* Map object for commands. */
std::map <std::string, Command *> Command::registry;

struct Command_Registration:public Command
{
  Command_Registration ():Command ("w", "w:Open the registration window.") {}
  void run (std::vector <std::string> &args);
}command_Registration;

struct Command_Delete:public Command
{
  Command_Delete ():Command ("e", "e:Deletes all registered hansets.") {}
  void run (std::vector <std::string> &args);
}command_Delete;

struct Command_DeleteSingle:public Command
{
  Command_DeleteSingle ():Command ("d", "d <h>:Deletes a registered hansets with handset id <h>.") {}
  void run (std::vector <std::string> &args);
}command_DeleteSingle;

struct Command_SetupCall:public Command
{
  Command_SetupCall ():Command ("r", "r <h>:Setup a call with handset id <h>.") {}
  void run (std::vector <std::string> &args);
}command_SetupCall;

struct Command_ReleaseCall:public Command
{
  Command_ReleaseCall ():Command ("t", "t <c>:Release a call with call id <c>.") {}
  void run (std::vector <std::string> &args);
}command_ReleaseCall;

struct Command_Mute:public Command
{
  Command_Mute ():Command ("z", "z:Mute.") {}
  void run (std::vector <std::string> &args);
}command_Mute;

struct Command_Unmute:public Command
{
  Command_Unmute ():Command ("u", "u:Unmute.") {}
  void run (std::vector <std::string> &args);
}command_Unmute;

struct Command_VolumeUp:public Command
{
  Command_VolumeUp ():Command ("i", "i:Volume up.") {}
  void run (std::vector <std::string> &args);
}command_VolumeUp;

struct Command_VolumeDown:public Command
{
  Command_VolumeDown ():Command ("o", "o:Volume down.") {}
  void run (std::vector <std::string> &args);
}command_VolumeDown;

struct Command_SetPin:public Command
{
  Command_SetPin ():Command ("p", "p <pin code>:Set pin code (4 digits), for example 1234") {}
  void run (std::vector <std::string> &args);
}command_SetPin;

void Command_Registration::run (std::vector <std::string> &args)
{
  j["version"] = "1.0.0";
  j["module"] = "legacy";
  j["primitive"] = "request";
  j["service"] = "openRegistrationWindow";
  j["status"] = "OK";
  j["param1"] = "w";
  j["param2"] = "0";
  j["param3"] = "0";
  size_t len = strlen((j.dump()).c_str())+1;
  udp_send((j.dump()).c_str(), len);

  std::cout.clear (); std::cout << "Registration window open until timeout!" <<
  std::endl; std::cout.clear (); std::cerr.clear ();
}

void Command_Delete::run (std::vector <std::string> &args)
{
  j["version"] = "1.0.0";
  j["module"] = "legacy";
  j["primitive"] = "request";
  j["service"] = "subscriptionDelete";
  j["status"] = "OK";
  j["param1"] = "e";
  j["param2"] = "0";
  j["param3"] = "0";
  size_t len = strlen((j.dump()).c_str())+1;
  udp_send((j.dump()).c_str(), len);

  std::cout.clear (); std::cout << "Deletes all registered handsets!" <<
  std::endl; std::cout.clear (); std::cerr.clear ();
}

void Command_DeleteSingle::run (std::vector <std::string> &args)
{
  if (args.size () != 1 )
  {
    std::cout.clear (); std::cout << "Wrong usage - use command h or ? for help menu" <<
    std::endl;std::cout.clear (); std::cerr.clear ();
    return;
  }

  j["version"] = "1.0.0";
  j["module"] = "legacy";
  j["primitive"] = "request";
  j["service"] = "OPEND_SUBAPI_SUBSCRIPTION_DELETE";
  j["status"] = "OK";
  j["param1"] = "d";
  j["param2"] = args[0].c_str();
  j["param3"] = "0";
  size_t len = strlen((j.dump()).c_str())+1;
  udp_send((j.dump()).c_str(), len);

  std::cout.clear (); std::cout << "Delete handset " << args[0].c_str() <<
  std::endl; std::cout.clear (); std::cerr.clear ();
}

void Command_SetupCall::run (std::vector <std::string> &args)
{
  if (args.size () < 1)
  {
    std::cout.clear (); std::cout << "Wrong usage - use command h or ? for help menu" <<
    std::endl;std::cout.clear (); std::cerr.clear ();
    return;
  }

  j["version"] = "1.0.0";
  j["module"] = "legacy";
  j["primitive"] = "request";
  j["service"] = "setupCall";
  j["status"] = "OK";
  j["param1"] = "r";
  j["param2"] = args[0].c_str();
  j["param3"] = "0";
  size_t len = strlen((j.dump()).c_str())+1;
  udp_send((j.dump()).c_str(), len);
}

void Command_ReleaseCall::run (std::vector <std::string> &args)
{
  if (args.size () < 1)
  {
    std::cout.clear (); std::cout << "Wrong usage - use command h or ? for help menu" <<
    std::endl;std::cout.clear (); std::cerr.clear ();
    return;
  }

  j["version"] = "1.0.0";
  j["module"] = "legacy";
  j["primitive"] = "request";
  j["service"] = "releaseCall";
  j["status"] = "OK";
  j["param1"] = "t";
  j["param2"] = args[0].c_str();
  j["param3"] = "0";
  size_t len = strlen((j.dump()).c_str())+1;
  udp_send((j.dump()).c_str(), len);
}

void Command_Mute::run (std::vector <std::string> &args)
{
  j["version"] = "1.0.0";
  j["module"] = "legacy";
  j["primitive"] = "request";
  j["service"] = "mute";
  j["status"] = "OK";
  j["param1"] = "z";
  j["param2"] = "0";
  j["param3"] = "0";
  size_t len = strlen((j.dump()).c_str())+1;
  udp_send((j.dump()).c_str(), len);
}

void Command_Unmute::run (std::vector <std::string> &args)
{
  j["version"] = "1.0.0";
  j["module"] = "legacy";
  j["primitive"] = "request";
  j["service"] = "unmute";
  j["status"] = "OK";
  j["param1"] = "u";
  j["param2"] = "0";
  j["param3"] = "0";
  size_t len = strlen((j.dump()).c_str())+1;
  udp_send((j.dump()).c_str(), len);
}

void Command_VolumeUp::run (std::vector <std::string> &args)
{
  j["version"] = "1.0.0";
  j["module"] = "legacy";
  j["primitive"] = "request";
  j["service"] = "volumeUp";
  j["status"] = "OK";
  j["param1"] = "i";
  j["param2"] = "0";
  j["param3"] = "0";
  size_t len = strlen((j.dump()).c_str())+1;
  udp_send((j.dump()).c_str(), len);
}

void Command_VolumeDown::run (std::vector <std::string> &args)
{
  j["version"] = "1.0.0";
  j["module"] = "legacy";
  j["primitive"] = "request";
  j["service"] = "volumeDown";
  j["status"] = "OK";
  j["param1"] = "o";
  j["param2"] = "0";
  j["param3"] = "0";
  size_t len = strlen((j.dump()).c_str())+1;
  udp_send((j.dump()).c_str(), len);
}

void Command_SetPin::run (std::vector <std::string> &args)
{
  if (args.size () != 1 )
  {
    std::cout.clear (); std::cout << "Wrong usage - use command h or ? for help menu" <<
    std::endl;std::cout.clear (); std::cerr.clear ();
    return;
  }

  j["version"] = "1.0.0";
  j["module"] = "legacy";
  j["primitive"] = "request";
  j["service"] = "OPEND_SUBAPI_SET_AC";
  j["status"] = "OK";
  j["param1"] = "p";
  j["param2"] = args[0].c_str();
  j["param3"] = "0";
  size_t len = strlen((j.dump()).c_str())+1;
  udp_send((j.dump()).c_str(), len);
}

/* HF::Application::Initialize */
void HF::Application::Initialize (receiveUdpData rxUdpData)
{
  rxThread_init();

  udp_init(rxUdpData);

  Command::add(&command_SetPin);
  Command::add(&command_Registration);
  Command::add(&command_Delete);
  Command::add(&command_DeleteSingle);
  Command::add(&command_SetupCall);
  Command::add(&command_ReleaseCall);
  Command::add(&command_Mute);
  Command::add(&command_Unmute);
  Command::add(&command_VolumeUp);
  Command::add(&command_VolumeDown);
}

/* Command::add */
void Command::add (Command *command)
{
  registry.insert (std::pair <std::string, Command *>(command->key (), command));
}

/* Command::run */
void Command::run (std::string &key, std::vector <std::string> &args)
{
  auto it = registry.find (key);

  if (it == registry.end ())
  {
    std::cerr.clear (); std::cerr << "[ERROR] " << "Command '" << key << "' not exist !" << std::endl; std::cout.clear (); std::cerr.clear ();
    Command::help (std::cout);
  }
  else
  {
    it->second->run (args);
  }
}

/* Command::help */
std::ostream &Command::help (std::ostream &streamOut)
{
  struct entry
  {
    std::string cmd;
    std::string help;
  };

  if (Command::registry.size() == 0)
  {
    streamOut << "";
    return streamOut;
  }

  static std::string cache;
  std::stringstream stream;

  uint16_t size = 0;
  std::vector <entry> entries;


  std::for_each (Command::registry.begin (), Command::registry.end (),
                 [&entries, &size](std::pair <std::string, Command *> e)
  {

    const std::string &raw = e.second->usage (); /* usageCommand in raw */

    char *temp = new char[raw.size () + 1];

    strncpy (temp, raw.c_str (), raw.size ()); /* Copy raw in temp */

    temp[raw.size ()] = 0;

    std::vector <char *> lines;
    char *saveptr = NULL;
    for (char *p = strtok_r (temp, "\n", &saveptr); p != NULL; p = strtok_r (NULL, "\n", &saveptr))
    {
      lines.push_back (p); /* Copy temp in lines */
    }

    std::for_each (lines.begin (), lines.end (), [&entries, &size](char *line)
    {
      entry e;
      char *saveptr = NULL;

      char *p = strtok_r (line, ":", &saveptr);
      e.cmd = std::string (p); /* Copy string before : in e.cmd */

      p = strtok_r (NULL, ":", &saveptr);
      e.help = std::string (p); /* Copy string after : in e.cmd */

      entries.push_back (e); /* Copy cmd and help in eintries */

      if (size < e.cmd.size ())
      {
        size = e.cmd.size ();
      }
    });

    delete[] temp;
  });

  size++;

  stream << std::endl;

  stream << "************************************************" << std::endl;
  stream << "  STACKFORCE openD LEGACY Demo Application 1.0  " << std::endl;
  stream << "************************************************" << std::endl << std::endl;

  stream << std::setfill (' ');

  std::for_each (entries.begin (), entries.end (), [&stream, size](entry &e)
  {
    stream << std::left << std::setw (size) << e.cmd << "    : " << e.help << std::endl;
  });

  stream << std::left << std::setw (size) << "h or ?" << "    : " << "Help menu." << std::endl << std::endl;
  stream << "Select an Option (Q or q to close the demo app): " << std::endl;

  cache = stream.str();

  streamOut << cache;

  return streamOut;
}

/* HF::Application::Handle */
bool HF::Application::Handle (std::string command)
{
  std::cout.clear (); std::cout << "[INFO] " << __PRETTY_FUNCTION__ << std::endl; std::cout.clear (); std::cerr.clear ();

  if (command.empty () || (command.size () == 1 && command[0] == '\n'))
  {
    Command::help (std::cout);
    return false;
  }

  std::istringstream buf (command);
  std::istream_iterator <std::string> beg (buf), end;

  std::vector <std::string> tokens (beg, end);

  std::string cmd = *tokens.begin ();

  std::vector <std::string> args (tokens.begin () + 1, tokens.end ());

  if (cmd == "q" || cmd == "Q")
  {
    return true;
  }
  else if (cmd == "h" || cmd == "?")
  {
    /* json library object. */
    json j;
    j["version"] = "1.0.0";
    j["module"] = "legacy";
    j["primitive"] = "request";
    j["service"] = "printHelp";
    j["status"] = "OK";
    j["param1"] = "a";
    j["param2"] = "0";
    j["param3"] = "0";
    size_t len = strlen((j.dump()).c_str())+1;
    udp_send((j.dump()).c_str(), len);

    std::cout.clear (); std::cout << "";
    Command::help (std::cout);
  }
  else
  {
    Command::run (cmd, args);
  }

  std::cout.clear (); std::cout << "> " << std::flush;

  return false;
}



