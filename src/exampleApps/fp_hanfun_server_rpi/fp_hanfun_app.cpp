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
 * @brief      UDP client side app implementation.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 */

#include <string>
#include <forward_list>
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <fstream>
#include "application.h"
#include "fp_hanfun_app.h"
#include "opend_hanfun_api_fp.h"
#include "udp_server.h"
#include <../../json/single_include/nlohmann/json.hpp>

extern "C"
{
#include "opend_api.h"
}

/* JSON HAN-FUN device file. */
#ifndef HF_APP_CONFIG_FILE
   #define HF_APP_CONFIG_FILE   "./hanfun.json"
#endif

using json = nlohmann::json;

/* json library object. */
json j;

/* Map object. */
std::map <std::string, Command *> Command::registry;

/**
 * @brief   Device management confirm callback.
 *
 * @details Executes the service specific device management confirmation.
 *
 * @param   hDevMgmtConfirm Pointer to the device management confirm structure.
 */
void devMgmtConfirmCallback(openD_hanfunApi_devMgmtCfm_t *hDevMgmtConfirm);

/**
 * @brief   Profile indication callback.
 *
 * @details Executes the service specific profile indication.
 *
 * @param   hProfileInd Pointer to the profile indication structure.
 */
void profileIndCallback(openD_hanfunApi_profileInd_t *hProfileInd);

/**
 * @brief   Profile confirm callback.
 *
 * @details Executes the service specific profile confirmation.
 *
 * @param   hProfileConfirm Pointer to the profile confirm structure.
 */
void profileConfirmCallback(openD_hanfunApi_profileCfm_t *hProfileConfirm);

/**
 * @brief   Bind management confirm callback.
 *
 * @details Executes the service specific bind management confirmation.
 *
 * @param   hBindMgmtConfirm Pointer to the bind management confirm structure.
 */
void bindMgmtConfirmCallback(openD_hanfunApi_bindMgmtCfm_t *hBindMgmtConfirm);

/**
 * @brief   Device management indication callback.
 *
 * @details Executes the service specific device management indication.
 *
 * @param   hDevMgmtIndication Pointer to the device management indication structure.
 */
void devMgmtIndicationCallback(openD_hanfunApi_devMgmtInd_t *hDevMgmtIndication);


void devMgmtConfirmCallback(openD_hanfunApi_devMgmtCfm_t *hDevMgmtConfirm)
{
  openD_status_t confirmAndIndStatusByte = hDevMgmtConfirm->status;
  FP * fp = FP::instance();

  if(confirmAndIndStatusByte != OPEND_STATUS_OK)
  {
    return;
  }

  switch(hDevMgmtConfirm->service)
  {
	  case OPEND_HANFUNAPI_DEVICE_MANAGEMENT_ENTRIES_REGISTRATION:
	    confirmAndIndStatusByte = hDevMgmtConfirm->status;
      std::cout.clear (); std::cout << std::setfill (' ');
      std::cout.clear (); std::cout << "HAN-FUN" << "  Currently registered Devices (" <<
      (int) hDevMgmtConfirm->param.entriesRegistration.size
      << "):" << std::endl; std::cout.clear (); std::cerr.clear ();
      if((int) hDevMgmtConfirm->param.entriesRegistration.size == 0)
      {
        j["version"] = "1.0.0";
        j["module"] = "hanfun";
        j["primitive"] = "confirmation";
        j["service"] = "deviceManagementEntriesRegistration";
        j["status"] = "INV";
        j["param1"] = "0";
        j["param2"] = "0";
        j["param3"] = "0";
        size_t len = strlen((j.dump()).c_str())+1;
        udp_send((j.dump()).c_str(), len);
      }
      for(int i=0; i < (int) hDevMgmtConfirm->param.entriesRegistration.size; i++)
      {
        std::stringstream stream_uid;
        std::string uid;

        std::cout.clear (); std::cout <<
        (fp->link (hDevMgmtConfirm->param.entriesRegistration.registrationElement[i].address) != nullptr ? "+ " : "- ");
        std::cout.clear (); std::cout << std::right << std::setw (5) <<
        hDevMgmtConfirm->param.entriesRegistration.registrationElement[i].address << " | ";
        std::cout.clear (); std::cout << "dect uid: " << hDevMgmtConfirm->param.entriesRegistration.registrationElement[i].uid[0] <<
        hDevMgmtConfirm->param.entriesRegistration.registrationElement[i].uid[1] << hDevMgmtConfirm->param.entriesRegistration.registrationElement[i].uid[2] <<
        hDevMgmtConfirm->param.entriesRegistration.registrationElement[i].uid[3] << hDevMgmtConfirm->param.entriesRegistration.registrationElement[i].uid[4] <<
        std::endl; std::cout.clear (); std::cerr.clear ();

        std::string size = std::to_string(hDevMgmtConfirm->param.entriesRegistration.size);
        std::string address = std::to_string(hDevMgmtConfirm->param.entriesRegistration.registrationElement[i].address);
        stream_uid << std::hex << std::setw(2) << std::setfill('0') << hDevMgmtConfirm->param.entriesRegistration.registrationElement[i].uid[0];
        stream_uid << std::hex << std::setw(2) << std::setfill('0') << hDevMgmtConfirm->param.entriesRegistration.registrationElement[i].uid[1];
        stream_uid << std::hex << std::setw(2) << std::setfill('0') << hDevMgmtConfirm->param.entriesRegistration.registrationElement[i].uid[2];
        stream_uid << std::hex << std::setw(2) << std::setfill('0') << hDevMgmtConfirm->param.entriesRegistration.registrationElement[i].uid[3];
        stream_uid << std::hex << std::setw(2) << std::setfill('0') << hDevMgmtConfirm->param.entriesRegistration.registrationElement[i].uid[4];
        stream_uid >> uid;

        j["version"] = "1.0.0";
        j["module"] = "hanfun";
        j["primitive"] = "confirmation";
        j["service"] = "deviceManagementEntriesRegistration";
        j["status"] = "OK";
        j["param1"] = size;
        j["param2"] = address;
        j["param3"] = uid;
        size_t len = strlen((j.dump()).c_str())+1;
        udp_send((j.dump()).c_str(), len);
      }
	    break;
    case OPEND_HANFUNAPI_DEVICE_MANAGEMENT_ENTRIES_LINK:
      for(int i=0; i < (int) hDevMgmtConfirm->param.entriesRegistration.size; i++)
      {
        std::cout.clear (); std::cout << std::setw (5) << hDevMgmtConfirm->param.entriesRegistration.registrationElement[i].address
        << " | "; std::cout.clear (); std::cout << "dect uid: " << hDevMgmtConfirm->param.entriesRegistration.registrationElement[i].uid[0] <<
        hDevMgmtConfirm->param.entriesRegistration.registrationElement[i].uid[1] << hDevMgmtConfirm->param.entriesRegistration.registrationElement[i].uid[2] <<
        hDevMgmtConfirm->param.entriesRegistration.registrationElement[i].uid[3] << hDevMgmtConfirm->param.entriesRegistration.registrationElement[i].uid[4] <<
        std::endl; std::cout.clear (); std::cerr.clear ();
      }
      break;
    case OPEND_HANFUNAPI_DEVICE_MANAGEMENT_CHANGE_CONCENTRATOR_DECT_MODE:
      std::cout.clear (); std::cout << "Successful change of Dect mode." << std::endl; std::cout.clear (); std::cerr.clear ();
	    std::cout.clear (); std::cout << "Resetting the Dect Module" << std::endl; std::cout.clear (); std::cerr.clear ();
      break;
	  default:
      confirmAndIndStatusByte = OPEND_STATUS_ARGUMENT_INVALID;
	    break;
  }
}

void devMgmtIndicationCallback(openD_hanfunApi_devMgmtInd_t *hDevMgmtIndication)
{
  if(!hDevMgmtIndication)
  {
    return;
  }

  switch(hDevMgmtIndication->service)
  {
    case OPEND_HANFUNAPI_DEVICE_MANAGEMENT_REGISTER_DISABLE:
      std::cout.clear (); std::cout << "[INFO ] " << "Registration mode disabled." <<
      std::endl; std::cout.clear (); std::cerr.clear ();
      j["version"] = "1.0.0";
      j["module"] = "hanfun";
      j["primitive"] = "indication";
      j["service"] = "deviceManagementRegisterDisable";
      j["status"] = "OK";
      j["param1"] = "0";
      j["param2"] = "0";
      j["param3"] = "0";
      udp_send((j.dump()).c_str(), strlen((j.dump()).c_str())+1);
      break;

    case OPEND_HANFUNAPI_DEVICE_MANAGEMENT_REGISTER_DEVICE:
      {
        std::string address = std::to_string(hDevMgmtIndication->param.getAddress.address);
        std::cout.clear (); std::cout << "[INFO ] " << "Device with ID " << address << " registered" <<
        std::endl; std::cout.clear (); std::cerr.clear ();
        j["version"] = "1.0.0";
        j["module"] = "hanfun";
        j["primitive"] = "indication";
        j["service"] = "deviceManagementRegisterDevice";
        j["status"] = "OK";
        j["param1"] = address;
        j["param2"] = "0";
        j["param3"] = "0";
        udp_send((j.dump()).c_str(), strlen((j.dump()).c_str())+1);
      }
      break;

    case OPEND_HANFUNAPI_DEVICE_MANAGEMENT_GET_DEVICE_CORE_INFORMATION:
      openD_hanfunApi_devMgmtReq_t hMgmtRequest;
      hMgmtRequest.service = OPEND_HANFUNAPI_DEVICE_MANAGEMENT_GET_DEVICE_CORE_INFORMATION;
      openD_hanfunApi_fp_devMgmtRequest( &hMgmtRequest, hDevMgmtIndication->param.getAddress.address, 0 );
      break;

    case OPEND_HANFUNAPI_DEVICE_MANAGEMENT_TIMEOUT:
      printf("DECT module communication timeout!\n");
      break;

    default:
      break;
  }

  return;
}

void profileIndCallback( openD_hanfunApi_profileInd_t *hProfileInd )
{
  openD_status_t confirmAndIndStatusByte = hProfileInd->status;
  size_t len;

  if(confirmAndIndStatusByte != OPEND_STATUS_OK)
  {
    return;
  }

  switch(hProfileInd->profile)
  {
    case OPEND_HANFUNAPI_SIMPLE_LIGHT:
      switch(hProfileInd->simpleLight.service)
      {
        case OPEND_HANFUN_IONOFF_SERVER_TOGGLE_ADDR:
          printf("Toggle LED indication from PP received.\n");
          j["version"] = "1.0.0";
          j["module"] = "hanfun";
          j["primitive"] = "indication";
          j["service"] = "IOnOffClientToggle";
          j["status"] = "OK";
          j["param1"] = std::to_string(hProfileInd->simpleLight.param.toggleAddr.addr.device);
          j["param2"] = "0";
          j["param3"] = "0";
          len = strlen((j.dump()).c_str())+1;
          udp_send((j.dump()).c_str(), len);
		      break;
        case OPEND_HANFUN_IONOFF_SERVER_ON_ADDR:
          /* INDICATION IMPLEMENT HERE */
          break;
		    case OPEND_HANFUN_IONOFF_SERVER_OFF_ADDR:
          /* INDICATION IMPLEMENT HERE */
		      break;
		    default:
          confirmAndIndStatusByte = OPEND_STATUS_SERVICE_UNKNOWN;
		      break;
	    }
	    break;
	  default:
      confirmAndIndStatusByte = OPEND_STATUS_ARGUMENT_INVALID;
	    break;
  }
}

void profileConfirmCallback(openD_hanfunApi_profileCfm_t *hProfileConfirm)
{
  openD_status_t confirmAndIndStatusByte = hProfileConfirm->status;

  if(confirmAndIndStatusByte != OPEND_STATUS_OK)
  {
    return;
  }

  switch(hProfileConfirm->profile)
  {
    case OPEND_HANFUNAPI_SIMPLE_ONOFF_SWITCH:
      switch(hProfileConfirm->simpleOnOffSwitch.service)
	    {
		    case OPEND_HANFUN_IONOFF_CLIENT_TOGGLE:
          /* CONFIRMATION IMPLEMENT HERE */
		      break;
		    default:
          confirmAndIndStatusByte = OPEND_STATUS_SERVICE_UNKNOWN;
		      break;
	    }
	    break;
	case OPEND_HANFUNAPI_MOTION_DETECTOR:
      switch(hProfileConfirm->motionDetector.service)
	    {
		    case OPEND_HANFUN_iDETECTOR_ALERT:
          /* CONFIRMATION IMPLEMENT HERE */
		      break;
		    default:
          confirmAndIndStatusByte = OPEND_STATUS_SERVICE_UNKNOWN;
		      break;
	    }
	  break;
	default:
    confirmAndIndStatusByte = OPEND_STATUS_ARGUMENT_INVALID;
	  break;
  }
}

void bindMgmtConfirmCallback(openD_hanfunApi_bindMgmtCfm_t *hBindMgmtConfirm)
{
  openD_status_t confirmAndIndStatusByte = hBindMgmtConfirm->status;

  if(confirmAndIndStatusByte != OPEND_STATUS_OK)
  {
    return;
  }

  switch(hBindMgmtConfirm->service)
  {
	  case OPEND_HANFUNAPI_BIND_MANAGEMENT_ENTRIES:
      std::cout.clear ();std::cout << "HAN-FUN current Binds (" << hBindMgmtConfirm->param.entriesElement.entriesSize << "):"
      << std::endl; std::cout.clear (); std::cerr.clear ();
      std::cout.clear ();std::cout << "\t" << std::left << std::setfill(' ')
                                   << std::setw(16) << "Source"
                                   << std::setw(18) << "| Destination"
                                   << "| Interface" << std::endl
                                   << "\t" << std::setfill('-')
                                   << std::setw(15) << "-"
                                   << std::setw(18) << " | "
                                   << std::setw(12) << " | " << std::endl
                                   << std::setfill(' ');

      for(int i = 0; i < hBindMgmtConfirm->param.entriesElement.entriesSize; i++)
      {
        std::cout.clear (); std::cout << "\t" << "M:" << std::hex << hBindMgmtConfirm->param.entriesElement.src[i].mod <<
        " D:" << std::hex << hBindMgmtConfirm->param.entriesElement.src[i].device << " U:" << std::hex <<
        hBindMgmtConfirm->param.entriesElement.src[i].unit <<" | " << "M:" << std::hex <<
        hBindMgmtConfirm->param.entriesElement.dst[i].mod << " D:" << std::setfill('0') << std::setw(4) <<
        std::hex << hBindMgmtConfirm->param.entriesElement.dst[i].device << " U:" << std::hex <<
        hBindMgmtConfirm->param.entriesElement.dst[i].unit << " | " << "R:" << std::hex <<
        hBindMgmtConfirm->param.entriesElement.itf[i].role << " UID:" << std::hex <<
        hBindMgmtConfirm->param.entriesElement.itf[i].id << std::endl;std::cout.clear (); std::cerr.clear ();
      }
	    break;
    case OPEND_HANFUNAPI_BIND_MANAGEMENT_ADD:
      switch (hBindMgmtConfirm->param.entriesElement.error)
      {
        case 0:
        {
          std::cout.clear (); std::cout << "[INFO ] "
          << "Bind created !" << std::endl; std::cout.clear (); std::cerr.clear ();
          break;
        }
        case 1:
        {
          std::cerr.clear (); std::cerr << "[WARN ] " << "Bind already exist !"
          << std::endl; std::cout.clear (); std::cerr.clear ();
          break;
        }
        case 2:
        case 3:
        {
          std::cerr.clear (); std::cerr << "[ERROR] " << "Bind not possible: " <<
          std::endl; std::cout.clear (); std::cerr.clear ();
          if ((hBindMgmtConfirm->param.entriesElement.error & 0x01) != 0)
          {
            std::cerr.clear (); std::cerr << "[ERROR] " << "  - Second device does not exist !" <<
            std::endl; std::cout.clear (); std::cerr.clear ();
          }
          else
          {
            std::cerr.clear (); std::cerr << "[ERROR] " << "  - Fist device does not exist !" <<
            std::endl;std::cout.clear (); std::cerr.clear ();
          }
          break;
        }
        default:
          std::cerr.clear (); std::cerr << "[ERROR] " << "No match for bind !" <<
          std::endl; std::cout.clear (); std::cerr.clear ();
          break;
      }
      break;
    case OPEND_HANFUNAPI_BIND_MANAGEMENT_REMOVE:
      if (hBindMgmtConfirm->param.entriesElement.error == 1)
      {
        std::cout.clear ();std::cout << "[INFO ] " << "Bind: " <<
        hBindMgmtConfirm->param.entriesElement.devicesToBind.address1 << " - " <<
        hBindMgmtConfirm->param.entriesElement.devicesToBind.address2 << " removed !" <<
        std::endl; std::cout.clear (); std::cerr.clear ();
      }
      else
      {
        std::cout.clear (); std::cout << "[INFO ] " << "Bind: does not exist !"
        << std::endl; std::cout.clear (); std::cerr.clear ();
      }
      break;
	  default:
      confirmAndIndStatusByte = OPEND_STATUS_ARGUMENT_INVALID;
	    break;
  }
}


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
  openD_hanfunApi_devMgmtReq_t hMgmtRequest;
  hMgmtRequest.service = OPEND_HANFUNAPI_DEVICE_MANAGEMENT_ENTRIES_REGISTRATION;

  openD_hanfunApi_fp_devMgmtRequest(&hMgmtRequest);
}

void Command_Register::run (std::vector <std::string> &args)
{
  openD_hanfunApi_devMgmtReq_t hMgmtRequest;
  openD_status_t opend_status = OPEND_STATUS_FAIL;

  uint16_t address = strtol (args[1].c_str (), NULL, 10);

  if (args.size () > 0 && args[0] == "0") //!< Disable Registration
  {
    hMgmtRequest.service = OPEND_HANFUNAPI_DEVICE_MANAGEMENT_REGISTER_DISABLE;
    if (openD_hanfunApi_fp_devMgmtRequest(&hMgmtRequest) == OPEND_STATUS_OK)
    {
      std::cout.clear (); std::cout << "[INFO ] " << "Disable the Registration mode: SUCCESS" <<
      std::endl; std::cout.clear (); std::cerr.clear ();
      j["version"] = "1.0.0";
      j["module"] = "hanfun";
      j["primitive"] = "confirmation";
      j["service"] = "deviceManagementRegisterDisable";
      j["status"] = "OK";
      j["param1"] = "0";
      j["param2"] = "0";
      j["param3"] = "0";
      size_t len = strlen((j.dump()).c_str())+1;
      udp_send((j.dump()).c_str(), len);
    }
    else
    {
      std::cerr.clear (); std::cerr << "[WARN ] " << "Disable the Registration mode: FAIL" <<
      std::endl; std::cout.clear (); std::cerr.clear ();
      j["version"] = "1.0.0";
      j["module"] = "hanfun";
      j["primitive"] = "confirmation";
      j["service"] = "deviceManagementRegisterDisable";
      j["status"] = "ERR";
      j["param1"] = "0";
      j["param2"] = "0";
      j["param3"] = "0";
      size_t len = strlen((j.dump()).c_str())+1;
      udp_send((j.dump()).c_str(), len);
    }
  }
  else if(args.size () > 1 && args[0] == "1") //!< Enable Registration
  {
    hMgmtRequest.service = OPEND_HANFUNAPI_DEVICE_MANAGEMENT_REGISTER_ENABLE;
    opend_status = openD_hanfunApi_fp_devMgmtRequest(&hMgmtRequest, address);
    {
      if (opend_status == OPEND_STATUS_OK)
      {
        std::cout.clear (); std::cout << "[INFO ] " << "Enable the Registration mode: SUCCESS" <<
        std::endl; std::cout.clear (); std::cerr.clear ();
        std::cout.clear (); std::cout << "[INFO ] " << "Next Registration will have the address : " <<
        (int) address << std::endl; std::cout.clear (); std::cerr.clear ();

        j["version"] = "1.0.0";
        j["module"] = "hanfun";
        j["primitive"] = "confirmation";
        j["service"] = "deviceManagementRegisterEnable";
        j["status"] = "OK";
        j["param1"] = std::to_string(address);
        j["param2"] = "0";
        j["param3"] = "0";
        size_t len = strlen((j.dump()).c_str())+1;
        udp_send((j.dump()).c_str(), len);
      }
      if (opend_status == OPEND_STATUS_FAIL)
      {
        std::cerr.clear (); std::cerr << "[WARN ] " << "[HANFUN] Enable the Registration mode: FAIL" <<
        std::endl; std::cout.clear (); std::cerr.clear ();

        j["version"] = "1.0.0";
        j["module"] = "hanfun";
        j["primitive"] = "confirmation";
        j["service"] = "deviceManagementRegisterEnable";
        j["status"] = "ERR";
        j["param1"] = "0";
        j["param2"] = "0";
        j["param3"] = "0";
        size_t len = strlen((j.dump()).c_str())+1;
        udp_send((j.dump()).c_str(), len);
      }
      if (opend_status == OPEND_STATUS_ARGUMENT_INVALID)
      {
        std::cerr.clear (); std::cerr << "[ERROR] " << "Registration not possible: address " << (int) address
        << "  not available." << std::endl; std::cout.clear (); std::cerr.clear ();

        j["version"] = "1.0.0";
        j["module"] = "hanfun";
        j["primitive"] = "confirmation";
        j["service"] = "deviceManagementRegisterEnable";
        j["status"] = "INV";
        j["param1"] = "0";
        j["param2"] = "0";
        j["param3"] = "0";
        size_t len = strlen((j.dump()).c_str())+1;
        udp_send((j.dump()).c_str(), len);
      }
    }
  }
  else
  {
    std::cout.clear ();std::cout << "Wrong usage - use command h or ? for help menu" <<
    std::endl;std::cout.clear (); std::cerr.clear ();
  }
}

void Command_Deregister::run (std::vector <std::string> &args)
{
  openD_hanfunApi_devMgmtReq_t hMgmtRequest;
  hMgmtRequest.service = OPEND_HANFUNAPI_DEVICE_MANAGEMENT_DEREGISTER;
  bool res = false;
  uint16_t address = strtol (args[0].c_str (), NULL, 10);

  if (args.size () < 1)
  {
    std::cout.clear ();std::cout << "Wrong usage - use command h or ? for help menu" <<
    std::endl;std::cout.clear (); std::cerr.clear ();
    return;
  }

  if(openD_hanfunApi_fp_devMgmtRequest(&hMgmtRequest, address) == OPEND_STATUS_OK)
  {
    res = true;
  }

  j["version"] = "1.0.0";
  j["module"] = "hanfun";
  j["primitive"] = "confirmation";
  j["service"] = "deviceManagementDeregister";
  if(res == true)
  {
    j["status"] = "OK";
  }
  else
  {
    j["status"] = "ERR";
  }
  j["param1"] = std::to_string(address);
  j["param2"] = "0";
  j["param3"] = "0";
  size_t len = strlen((j.dump()).c_str())+1;
  udp_send((j.dump()).c_str(), len);

  std::cout.clear (); std::cout << "[INFO ] " << "Device " << (int) address << " de-registration: "
  << (res ? "SUCCESS" : "FAIL") << " !" << std::endl; std::cout.clear (); std::cerr.clear ();
}

void Command_On::run (std::vector <std::string> &args)
{
  openD_hanfunApi_profileReq_t hProfileRequest;
  hProfileRequest.profile = OPEND_HANFUNAPI_SIMPLE_ONOFF_SWITCH;
  hProfileRequest.simpleOnOffSwitch.service = OPEND_HANFUN_IONOFF_CLIENT_ON;

  if (args.size () < 2)
  {
    std::cout.clear (); std::cout << "Wrong usage - use command h or ? for help menu"
    << std::endl; std::cout.clear (); std::cerr.clear ();
    return;
  }

  uint16_t arg1 = strtol (args[0].c_str (), NULL, 10);
  uint16_t arg2 = strtol (args[1].c_str (), NULL, 10);

  if( OPEND_STATUS_OK != openD_hanfunApi_fp_profileRequest(&hProfileRequest, arg1, arg2) )
  {
    std::cerr.clear (); std::cerr << "[WARN ] " << "[HANFUN] Simple on/off switch request: FAIL" <<
    std::endl; std::cout.clear (); std::cerr.clear ();

    j["version"] = "1.0.0";
    j["module"] = "hanfun";
    j["primitive"] = "confirmation";
    j["service"] = "IOnOffClientOn";
    j["status"] = "ERR";
    j["param1"] = "0";
    j["param2"] = "0";
    j["param3"] = "0";
    size_t len = strlen((j.dump()).c_str())+1;
    udp_send((j.dump()).c_str(), len);
  }
}

void Command_Off::run (std::vector <std::string> &args)
{
  openD_hanfunApi_profileReq_t hProfileRequest;
  hProfileRequest.profile = OPEND_HANFUNAPI_SIMPLE_ONOFF_SWITCH;
  hProfileRequest.simpleOnOffSwitch.service = OPEND_HANFUN_IONOFF_CLIENT_OFF;

  if (args.size () < 2)
  {
    std::cout.clear ();std::cout << "Wrong usage - use command h or ? for help menu"
    << std::endl; std::cout.clear (); std::cerr.clear ();
    return;
  }

  uint16_t arg1 = strtol (args[0].c_str (), NULL, 10);
  uint16_t arg2 = strtol (args[1].c_str (), NULL, 10);

  if( OPEND_STATUS_OK != openD_hanfunApi_fp_profileRequest(&hProfileRequest, arg1, arg2) )
  {
    std::cerr.clear (); std::cerr << "[WARN ] " << "[HANFUN] Simple on/off switch request: FAIL" <<
    std::endl; std::cout.clear (); std::cerr.clear ();

    j["version"] = "1.0.0";
    j["module"] = "hanfun";
    j["primitive"] = "confirmation";
    j["service"] = "IOnOffClientOff";
    j["status"] = "ERR";
    j["param1"] = "0";
    j["param2"] = "0";
    j["param3"] = "0";
    size_t len = strlen((j.dump()).c_str())+1;
    udp_send((j.dump()).c_str(), len);
  }
}

void Command_Toggle::run (std::vector <std::string> &args)
{
  openD_hanfunApi_profileReq_t hProfileRequest;
  hProfileRequest.profile = OPEND_HANFUNAPI_SIMPLE_ONOFF_SWITCH;
  hProfileRequest.simpleOnOffSwitch.service = OPEND_HANFUN_IONOFF_CLIENT_TOGGLE;

  if (args.size () < 2)
  {
    std::cout.clear ();std::cout << "Wrong usage - use command h or ? for help menu"
    << std::endl;std::cout.clear (); std::cerr.clear ();
    return;
  }

  uint16_t arg1 = strtol (args[0].c_str (), NULL, 10);
  uint16_t arg2 = strtol (args[1].c_str (), NULL, 10);

  if( OPEND_STATUS_OK != openD_hanfunApi_fp_profileRequest(&hProfileRequest, arg1, arg2) )
  {
    std::cerr.clear (); std::cerr << "[WARN ] " << "[HANFUN] Simple on/off switch request: FAIL" <<
    std::endl; std::cout.clear (); std::cerr.clear ();

    j["version"] = "1.0.0";
    j["module"] = "hanfun";
    j["primitive"] = "confirmation";
    j["service"] = "IOnOffClientToggle";
    j["status"] = "ERR";
    j["param1"] = "0";
    j["param2"] = "0";
    j["param3"] = "0";
    size_t len = strlen((j.dump()).c_str())+1;
    udp_send((j.dump()).c_str(), len);
  }
}

static std::string json_uid( uint16_t uid )
{
  std::ostringstream convert;

  convert << "0x" << std::setfill ('0') << std::setw (sizeof(uint16_t) * 2) << std::hex << uid;

  return convert.str ();
}

static uint16_t json_uid( std::string uid )
{
   return strtol( uid.substr (2).c_str (), NULL, 16 );
}

void HF::Application::Save ()
{
  std::cout.clear (); std::cout << "Application configuration save !" << std::endl; std::cout.clear (); std::cerr.clear ();

  json j;
  openD_hanfunDevice_t *hanfunDevices = NULL;
  uint16_t hanfunDevices_size;

  std::ofstream ofs (HF_APP_CONFIG_FILE);

  /* Get the available devices. */
  hanfunDevices_size = openD_hanfunApi_fp_devMgmt_get( &hanfunDevices );

  json root;

  for( unsigned i = 0; i < hanfunDevices_size; i++ )
  {
    /* Address */
    root[i]["address"] = hanfunDevices[i].address;
    /* EMC */
    root[i]["emc"] = json_uid( hanfunDevices[i].emc );
    /* Units */
    for (unsigned k = 0; k < hanfunDevices[i].units_length; k++)
    {
      json &units = root[i]["units"][k];
      units["id"] = hanfunDevices[i].units[k].id;
      units["profile"] = json_uid( hanfunDevices[i].units[k].profile );
    }
    /* IPUI */
    root[i]["uid"] = { {"type", "dect"} };
    for (unsigned k = 0U; k < 5U; ++k)
    {
      root[i]["uid"]["value"][k] = hanfunDevices[i].ipui[k];
    }
  }

  if (ofs.is_open ())
  {
    j["core"]["device_management"] = root;
    ofs << std::setw(4) << j << std::endl;
    ofs.close ();
  }

  Saved ();
}

void HF::Application::Restore ()
{
  json j;
  std::vector<openD_hanfunDevice_t> hanfunDevices;
  std::vector<openD_hanfunDevice_unit_t> hanfunDevice_units;

  std::ifstream ifs (HF_APP_CONFIG_FILE);

  /* Check if file exists. */
  if( ifs.good() )
  {
    try
    {
      /* Stream to JSON object. */
      ifs >> j;

      json root = j["core"]["device_management"];

      /* JSON object to device list. */
      for( unsigned i = 0; i < root.size (); i++ )
      {
        openD_hanfunDevice_t hanfunDevice;

        /* Address */
        hanfunDevice.address = (uint16_t) root[i].at("address").get<std::uint16_t>();
        /* EMC */
        hanfunDevice.emc = json_uid (root[i].at("emc").get<std::string>());
        /* Units */
        for (unsigned j = 0U; j <  root[i]["units"].size(); j++)
        {
          openD_hanfunDevice_unit_t openD_hanfunDevice_unit;
          hanfunDevice_units.push_back( openD_hanfunDevice_unit );

          /* Save the first reference to the current HANFUN device. */
          if( 0U == j) {
            hanfunDevice.units = &hanfunDevice_units[0];
          }

          /* Convert units from JSON. */
          hanfunDevice_units[j].id = (uint8_t) root[i]["units"][j].at("id").get<std::uint8_t>();
          hanfunDevice_units[j].profile = json_uid (root[i]["units"][j].at("profile").get<std::string>());
        }
        hanfunDevice.units_length = root[i]["units"].size();

        /* IPUI */
        for (unsigned j = 0U; j < 5U; ++j)
        {
            hanfunDevice.ipui[j] = (uint8_t) root[i]["uid"]["value"][j];
        }

        hanfunDevices.push_back( hanfunDevice );
      }

    }
    catch (json::exception& e)
    {
      LOG(WARN) << "Reading configuration file error!" << e.what() << NL;
    }
  } else {
    LOG(INFO) << "No HAN-FUN device file exists." << NL;
  }

  /* Restore device list. */
  openD_hanfunApi_fp_devMgmt_set( &hanfunDevices[0], hanfunDevices.size() );

  ifs.close ();

  Restored ();
}

/* HF::Application::Initialize */
int HF::Application::Initialize (HF::Transport::Layer &transport, int argc, char **argv)
{
  openD_status_t ret;
  char *serialPort = NULL;

	/* Variable for the openD primitives. */
	openD_hanfunApiPrimitives openD_hanfunApiPrimitives;

  /* Set the confirmation and indication callbacks. */
  openD_hanfunApiPrimitives.openD_hanfunApiProfileCfm = profileConfirmCallback;
  openD_hanfunApiPrimitives.openD_hanfunApiProfileInd = profileIndCallback;
  openD_hanfunApiPrimitives.openD_hanfunApi_mgmtCfm = devMgmtConfirmCallback;
  openD_hanfunApiPrimitives.openD_hanfunApi_mgmtInd = devMgmtIndicationCallback;
  openD_hanfunApiPrimitives.openD_hanfunApi_bindCfm = bindMgmtConfirmCallback;

  /* Initialize the openD HANFUN API primitives. */
	if(openD_hanfunApi_init(&openD_hanfunApiPrimitives) == OPEND_STATUS_OK)
	{
	  std::cout.clear (); std::cout << "\nInitialization of primitives: SUCCESS" << std::endl; std::cout.clear (); std::cerr.clear ();
	}

  if( argc >= 2 ) {
    serialPort = argv[1];
  }

  ret = openD_init( serialPort );
  if( ret != OPEND_STATUS_OK )
  {
    std::cout.clear (); std::cout << "\nInitialization of openD: FAILED" << std::endl; std::cout.clear (); std::cerr.clear ();

    if( ret == OPEND_STATUS_SERIAL_INIT_FAIL )
    {
      if( serialPort ) {
        std::cout.clear (); std::cout << "\nFailed to initialize serial port: " << serialPort << std::endl; std::cout.clear (); std::cerr.clear ();
      } else {
        std::cout.clear (); std::cout << "\nFailed to initialize serial port! " << std::endl; std::cout.clear (); std::cerr.clear ();
      }
    }
    return -1;
  }

  transport.initialize ();

  openD_hanfunApi_fp_init(&transport);

  /* Create simple light profile. */
  opend_hanfunApi_createProfile( OPEND_HANFUNAPI_SIMPLE_LIGHT, 1 );
  /* Create simple switch profile. */
  opend_hanfunApi_createProfile( OPEND_HANFUNAPI_SIMPLE_ONOFF_SWITCH, 2 );

  Command::add(&command_ListRegs);
  Command::add(&command_Register);
  Command::add(&command_Deregister);
  Command::add(&command_Off);
  Command::add(&command_On);
  Command::add(&command_Toggle);

  Restore();

  return 0;
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
  std::cout.clear (); std::cout << "[TRACE] " << __PRETTY_FUNCTION__ << std::endl; std::cout.clear (); std::cerr.clear ();

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
