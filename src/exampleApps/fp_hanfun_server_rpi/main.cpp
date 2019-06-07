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
 * @brief      Server side demo application.
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
#include <hanfun.h>

#define HF_LOG_LEVEL HF_LOG_LEVEL_TRACE

#include <hanfun/debug.h>
#include "application.h"
#include "hf_transport.h"
#include "udp_server.h"
#include <../../json/single_include/nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;


void HF::Application::Saved ()
{
  std::cout.clear (); std::cout << "Application configuration saved !" << std::endl; std::cout.clear (); std::cerr.clear ();
}

void HF::Application::Restored ()
{
  std::cout.clear (); std::cout << "Application configuration restored !" << std::endl; std::cout.clear (); std::cerr.clear ();
}


// =================================================================
// Main
// =================================================================

int main (int argc, char **argv)
{
  json j;
  std::string input;

  udp_init();

  /* HAN-FUN Transport Layer over ULE Stack. */
  HF::ULE::Transport * transport = HF::ULE::Transport::instance();

  HF::Application::Initialize(*transport, argc, argv);

  while( !HF::Application::Handle(input) )
  {
    char buffer[1024];

    udp_receive(buffer);
    printf("%s\n", buffer);

    try
    {
      j = json::parse(buffer);

      string version = j.at("version").get<std::string>();
      string module = j.at("module").get<std::string>();
      string primitive = j.at("primitive").get<std::string>();
      string service = j.at("service").get<std::string>();
      string status = j.at("status").get<std::string>();
      string param1 = j.at("param1").get<std::string>();
      string param2 = j.at("param2").get<std::string>();
      string param3 = j.at("param3").get<std::string>();

      input = param1 + " " + param2 + " " + param3;
    }
    catch (json::exception& e)
    {
      std::cout.clear (); std::cout << "Received UDP data error!" << e.what() <<std::endl; std::cout.clear (); std::cerr.clear ();
    }
  }

  transport->destroy();

  exit(0);
}
