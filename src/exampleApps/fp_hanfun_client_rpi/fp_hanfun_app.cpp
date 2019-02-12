/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       fp_hanfun_app.cpp
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger
 * @brief      Implementation of the fixed part HAN FUN client
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
#include "fp_hanfun_app.h"
#include <../../json/single_include/nlohmann/json.hpp>

using json = nlohmann::json;

/* json library object. */
json j;

/* Map object for commands. */
std::map <std::string, Command *> Command::registry;

struct Command_ListRegs:public Command
{
  Command_ListRegs ():Command ("lr", "lr:List registered devices.") {}
  void run (std::vector <std::string> &args);
}command_ListRegs;

struct Command_Register:public Command
{
  Command_Register ():Command ("r", "r 1 <x>:Register the device x.\nr 0:Exit registration mode.") {}
  void run (std::vector <std::string> &args);
}command_Register;

struct Command_Deregister:public Command
{
  Command_Deregister ():Command ("d", "d <x>:De-register the device x.") {}
  void run (std::vector <std::string> &args);
}command_Deregister;

struct Command_On:public Command
{
  Command_On ():Command ("on", "on <x> 1:Send an ON command to device x.") {}
  void run (std::vector <std::string> &args);
}command_On;

struct Command_Off:public Command
{
  Command_Off ():Command ("off", "off <x> 1:Send an OFF command to device x.") {}
  void run (std::vector <std::string> &args);
}command_Off;

struct Command_Toggle:public Command
{
  Command_Toggle ():Command ("tog", "tog <x> 1:Send a TOGGLE command to device x.") {}
  void run (std::vector <std::string> &args);
}command_Toggle;

void Command_ListRegs::run (std::vector <std::string> &args)
{
  j["version"] = "1.0.0";
  j["module"] = "hanfun";
  j["primitive"] = "request";
  j["service"] = "deviceManagementEntriesRegistration";
  j["status"] = "OK";
  j["param1"] = "lr";
  j["param2"] = "0";
  j["param3"] = "0";
  size_t len = strlen((j.dump()).c_str())+1;
  udp_send((j.dump()).c_str(), len);
}

void Command_Register::run (std::vector <std::string> &args)
{
  if ( (args.size () > 0 && args[0] == "0") || (args.size () > 1 && args[0] == "1") )
  {
    j["version"] = "1.0.0";
    j["module"] = "hanfun";
    j["primitive"] = "request";
    if(strcmp(args[0].c_str(), "1") == 0)
    {
      j["service"] = "deviceManagementRegisterDisable";
    }
    else
    {
      j["service"] = "deviceManagementRegisterEnable";
    }
    j["status"] = "OK";
    j["param1"] = "r";
    j["param2"] = args[0].c_str();
    if ( args.size () > 1 )
      j["param3"] = args[1].c_str();
  }
  else
  {
    std::cout.clear ();std::cout << "Wrong usage - use command h or ? for help menu" <<
    std::endl;std::cout.clear (); std::cerr.clear ();
  }

  size_t len = strlen((j.dump()).c_str())+1;
  udp_send((j.dump()).c_str(), len);
}

void Command_Deregister::run (std::vector <std::string> &args)
{
  if (args.size () < 1)
  {
    std::cout.clear (); std::cout << "Wrong usage - use command h or ? for help menu" <<
    std::endl;std::cout.clear (); std::cerr.clear ();
    return;
  }

  j["version"] = "1.0.0";
  j["module"] = "hanfun";
  j["primitive"] = "request";
  j["service"] = "deviceManagementDeregister";
  j["status"] = "OK";
  j["param1"] = "d";
  j["param2"] = args[0].c_str();
  if ( args.size () > 1 )
    j["param3"] = args[1].c_str();
  size_t len = strlen((j.dump()).c_str())+1;
  udp_send((j.dump()).c_str(), len);
}

void Command_On::run (std::vector <std::string> &args)
{
  if (args.size () < 2)
  {
    std::cout.clear (); std::cout << "Wrong usage - use command h or ? for help menu"
    << std::endl; std::cout.clear (); std::cerr.clear ();
    return;
  }

  j["version"] = "1.0.0";
  j["module"] = "hanfun";
  j["primitive"] = "request";
  j["service"] = "IOnOffClientOn";
  j["status"] = "OK";
  j["param1"] = "on";
  j["param2"] = args[0].c_str();
  j["param3"] = args[1].c_str();
  size_t len = strlen((j.dump()).c_str())+1;
  udp_send((j.dump()).c_str(), len);
}

void Command_Off::run (std::vector <std::string> &args)
{
  if (args.size () < 2)
  {
    std::cout.clear (); std::cout << "Wrong usage - use command h or ? for help menu"
    << std::endl; std::cout.clear (); std::cerr.clear ();
    return;
  }

  j["version"] = "1.0.0";
  j["module"] = "hanfun";
  j["primitive"] = "request";
  j["service"] = "IOnOffClientOff";
  j["status"] = "OK";
  j["param1"] = "off";
  j["param2"] = args[0].c_str();
  j["param3"] = args[1].c_str();
  size_t len = strlen((j.dump()).c_str())+1;
  udp_send((j.dump()).c_str(), len);
}

void Command_Toggle::run (std::vector <std::string> &args)
{
  if (args.size () < 2)
  {
    std::cout.clear (); std::cout << "Wrong usage - use command h or ? for help menu"
    << std::endl; std::cout.clear (); std::cerr.clear ();
    return;
  }

  j["version"] = "1.0.0";
  j["module"] = "hanfun";
  j["primitive"] = "request";
  j["service"] = "IOnOffClientToggle";
  j["status"] = "OK";
  j["param1"] = "tog";
  j["param2"] = args[0].c_str();
  j["param3"] = args[1].c_str();
  size_t len = strlen((j.dump()).c_str())+1;
  udp_send((j.dump()).c_str(), len);
}

/* HF::Application::Initialize */
void HF::Application::Initialize (receiveUdpData rxUdpData)
{
  rxThread_init();

  udp_init(rxUdpData);

  Command::add(&command_ListRegs);
  Command::add(&command_Register);
  Command::add(&command_Deregister);
  Command::add(&command_Off);
  Command::add(&command_On);
  Command::add(&command_Toggle);
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
  stream << "  STACKFORCE openD HANFUN Demo Application 1.0  " << std::endl;
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
