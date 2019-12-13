/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       devicelist.cpp
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger
 * @brief      HANFUN Device List Implementation
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose
 * between one of them if you use this work. For further details, please refer
 * to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 */

//#include "fp_hanfun_alarm.h"
#include "application.h"
#include "opend_hanfun_api_fp.h"
#include <../../json/single_include/nlohmann/json.hpp>

#include "hanfun.h"
#include "hanfun/debug.h"
#include <map>
#include <iterator>

#include <algorithm>
#include <cstdint>
#include <forward_list>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

/* JSON HAN-FUN device file. */
#ifndef HF_APP_CONFIG_FILE
#define HF_APP_CONFIG_FILE "./hanfun.json"
#endif

using json = nlohmann::json;

static std::string json_uid(uint16_t uid)
{
   std::ostringstream convert;

   convert << "0x" << std::setfill('0') << std::setw(sizeof(uint16_t) * 2)
           << std::hex << uid;

   return convert.str();
}

static uint16_t json_uid(std::string uid)
{
   return strtol(uid.substr(2).c_str(), NULL, 16);
}

void HF::Application::Save()
{
   std::cout << "Application configuration save !" << std::endl;

   json j;
   openD_hanfunDevice_t* hanfunDevices = NULL;
   uint16_t hanfunDevices_size;

   std::ofstream ofs(HF_APP_CONFIG_FILE);

   /* Get the available devices. */
   hanfunDevices_size = openD_hanfunApi_fp_devMgmt_get(&hanfunDevices);

   json root;

   for (unsigned i = 0; i < hanfunDevices_size; i++)
   {
      /* Address */
      root[i]["address"] = hanfunDevices[i].address;
      /* EMC */
      root[i]["emc"] = json_uid(hanfunDevices[i].emc);
      /* Units */
      for (unsigned k = 0; k < hanfunDevices[i].units_length; k++)
      {
         json& units = root[i]["units"][k];
         units["id"] = hanfunDevices[i].units[k].id;
         units["profile"] = json_uid(hanfunDevices[i].units[k].profile);
      }

      /* IPUI */
      root[i]["uid"] = { { "type", "dect" } };
      for (unsigned k = 0U; k < 5U; ++k)
      {
         root[i]["uid"]["value"][k] = hanfunDevices[i].ipui[k];
      }
   }

   if (ofs.is_open())
   {
      j["core"]["device_management"] = root;
      ofs << std::setw(4) << j << std::endl;
      ofs.close();
   }

   std::cout.clear (); std::cout << "Application configuration saved !" << std::endl; std::cout.clear (); std::cerr.clear ();
}

void HF::Application::Restore()
{
   json j;
   std::vector<openD_hanfunDevice_t> hanfunDevices;
   std::vector<openD_hanfunDevice_unit_t> hanfunDevice_units;

   std::ifstream ifs(HF_APP_CONFIG_FILE);

   /* Check if file exists. */
   if (ifs.good())
   {
      try
      {
         /* Stream to JSON object. */
         ifs >> j;

         json root = j["core"]["device_management"];

         /* JSON object to device list. */
         for (unsigned i = 0; i < root.size(); i++)
         {
            openD_hanfunDevice_t hanfunDevice;

            /* Address */
            hanfunDevice.address = (uint16_t)root[i].at("address").get<std::uint16_t>();
            /* EMC */
            hanfunDevice.emc = json_uid(root[i].at("emc").get<std::string>());
            /* Units */
            for (unsigned j = 0U; j < root[i]["units"].size(); j++)
            {
               openD_hanfunDevice_unit_t openD_hanfunDevice_unit;
               hanfunDevice_units.push_back(openD_hanfunDevice_unit);

               /* Save the first reference to the current HANFUN device. */
               if (0U == j)
               {
                  hanfunDevice.units = &hanfunDevice_units[0];
               }

               /* Convert units from JSON. */
               hanfunDevice_units[j].id = (uint8_t)root[i]["units"][j].at("id").get<std::uint8_t>();
               hanfunDevice_units[j].profile = json_uid(root[i]["units"][j].at("profile").get<std::string>());
            }

            hanfunDevice.units_length = root[i]["units"].size();

            /* IPUI */
            for (unsigned j = 0U; j < 5U; ++j)
            {
               hanfunDevice.ipui[j] = (uint8_t)root[i]["uid"]["value"][j];
            }

            hanfunDevices.push_back(hanfunDevice);
         }
      }
      catch (json::exception& e)
      {
         LOG(WARN) << "Reading configuration file error!" << e.what() << NL;
      }
   }
   else
   {
      LOG(INFO) << "No HAN-FUN device file exists." << NL;
   }

   /* Restore device list. */
   openD_hanfunApi_fp_devMgmt_set(&hanfunDevices[0], hanfunDevices.size());

   ifs.close();

   std::cout.clear (); std::cout << "Application configuration restored !" << std::endl; std::cout.clear (); std::cerr.clear ();
}
