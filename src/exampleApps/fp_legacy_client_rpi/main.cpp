/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       main.cpp
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger
 * @brief      Client side demo application.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 */

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <iomanip>
#include "fp_legacy_app.h"
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "udp.h"
#include <../../json/single_include/nlohmann/json.hpp>

using json = nlohmann::json;

/**
 * @brief   Handle confirmation and indication.
 *
 * @details Handle received confirmation and indication data from the udp server.
 *
 * @param   buffer Pointer to the received data.
 */
void handleConfirmationAndIndication(char *buffer);

void handleConfirmationAndIndication(char *buffer)
{
  printf("Received udp data from server: %s\n", buffer);

  json j = json::parse(buffer);

  string version = j.at("version").get<std::string>();
  string module = j.at("module").get<std::string>();
  string primitive = j.at("primitive").get<std::string>();
  string service = j.at("service").get<std::string>();
  string status = j.at("status").get<std::string>();
  string param1 = j.at("param1").get<std::string>();
  string param2 = j.at("param2").get<std::string>();
  string param3 = j.at("param3").get<std::string>();

  if(service.compare("openRegistrationWindow") == 0)
  {
    if(status.compare("OK") == 0)
    {
      std::cout.clear (); std::cout << "[INFO ] " << "Handset with ID: " << param1 << " successfully registered" <<
      std::endl; std::cout.clear (); std::cerr.clear ();
    }
  }
  if(service.compare("setupCall") == 0)
  {
    if(status.compare("OK") == 0)
    {
      std::cout.clear (); std::cout << "[INFO ] " << "Call with ID: " << param1 << " successfully setup" <<
      std::endl; std::cout.clear (); std::cerr.clear ();
    }
  }
  if(service.compare("releaseCall") == 0)
  {
    if(status.compare("OK") == 0)
    {
      std::cout.clear (); std::cout << "Call successfully released" <<
      std::endl; std::cout.clear (); std::cerr.clear ();
    }
  }
  if(service.compare("setAudio") == 0)
  {
    if(status.compare("OK") == 0)
    {
      std::cout.clear (); std::cout << "Set audio successfull" <<
      std::endl; std::cout.clear (); std::cerr.clear ();
    }
    if(status.compare("ERR") == 0)
    {
      std::cout.clear (); std::cout << "Set audio failed" <<
      std::endl; std::cout.clear (); std::cerr.clear ();
    }
  }
  if(service.compare("muteUnmute") == 0)
  {
    if(status.compare("OK") == 0)
    {
      std::cout.clear (); std::cout << "Mute/Unmute successfull" <<
      std::endl; std::cout.clear (); std::cerr.clear ();
    }
    if(status.compare("ERR") == 0)
    {
      std::cout.clear (); std::cout << "Mute/Unmute failed" <<
      std::endl; std::cout.clear (); std::cerr.clear ();
    }
  }
}

// =============================================================================
// Main
// =============================================================================

int main (void)
{
  char buffer[1024];
  bool udpSendInit = true;

  HF::Application::Initialize(&handleConfirmationAndIndication);

  std::string input = "?";
  while( !HF::Application::Handle(input) )
  {
    std::cin.getline(buffer, sizeof(buffer));
    input = std::string(buffer);
    if(udpSendInit)
    {
      udpSendHello();
      udpSendInit = false;
    }
  }
  /* json library object. */
  json j;
  j["version"] = "1.0.0";
  j["module"] = "legacy";
  j["primitive"] = "request";
  j["service"] = "closeApp";
  j["status"] = "OK";
  j["param1"] = "q";
  j["param2"] = "0";
  j["param3"] = "0";
  size_t len = strlen((j.dump()).c_str())+1;
  udp_send((j.dump()).c_str(), len);

  exit(0);
}
