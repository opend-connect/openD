/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_hanfun_fp.cpp
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger
 * @brief
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 */

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <pthread.h>

#include "opend_dataTypes.h"
#include "opend_hanfun_api_fp.h"
#include "opend_hanfun.h"

#include "hanfun.h"
#include "application.h"
#include "hf_transport.h"

extern "C"
{
  #include "apphan.h"
  #include "appmsgparser.h"
  #include "appsrv.h"
}

/*!
 * Copy macro of HANFUN address.
 */
#define ADDR_CPY( DEST, SRC ) \
  DEST.mod = SRC.mod; \
  DEST.device = SRC.device; \
  DEST.unit = SRC.unit; \

#define MAX_HANFUN_ENTRIES        0xFFFF

/*!
 * Semaphore read module table functionality.
 */
pthread_mutex_t sem_hanfun_readTable;

/*!
 * Static and global SimpleLight profile object.
 */
static SimpleLight * g_simple_light = nullptr;

/*!
 * Static and global SimpleOnOffSwitchable profile object.
 */
static SimpleSwitch * g_simple_switch = nullptr;

/*!
 * HAN-FUN devices vector.
 */
std::vector<openD_hanfunDevice_t> _hanfunDevices;
/*!
 * HAN-FUN device units vector.
 */
std::vector<openD_hanfunDevice_unit_t> hanfunDevice_units;

/**
 * HANFUN address of the node device.
 */
uint16_t hanfunAddress;

/**
 * Application address of the node device.
 */
uint16_t appAddress[255];

/**
 * @brief   Handle device information.
 *
 * @details Handle the received device information.
 *
 * @param   payload Payload of the received data.
 * @param   offset Offset of the received message.
 */
static void handle_device_infomation (HF::Common::ByteArray &payload, uint16_t offset);

/**
 * @brief   Switch SimpleOnOffSwitch service.
 *
 * @details Switch and execute the service of the SimpleOnOffSwitch service.
 *
 * @param   hProfileRequest Pointer of the HAN-FUN API request structure (@ref openD_hanfunApi_profileReq_t).
 * @param   device Address of the device to execute the service.
 *
 * @retval  Status of the operation.
 */
static openD_status_t simpleOnOffSwitchService( openD_hanfunApi_profileReq_t *hProfileRequest, HF::Protocol::Address device );

void SimpleLight::on (HF::Protocol::Address &source)
{
  openD_hanfunApi_profileInd_t hProfileInd;

  hProfileInd.profile = OPEND_HANFUNAPI_SIMPLE_LIGHT;
  hProfileInd.simpleLight.service = OPEND_HANFUN_IONOFF_SERVER_ON_ADDR;
  ADDR_CPY( hProfileInd.simpleLight.param.onAddr.addr, source )
  hProfileInd.status = OPEND_STATUS_OK;
  g_simple_light->HF::Units::Unit<HF::Profiles::SimpleLight>::on( source );

  openD_hanfun_profileInd(&hProfileInd);
}

void SimpleLight::off (HF::Protocol::Address &source)
{
  openD_hanfunApi_profileInd_t hProfileInd;

  hProfileInd.profile = OPEND_HANFUNAPI_SIMPLE_LIGHT;
  hProfileInd.simpleLight.service = OPEND_HANFUN_IONOFF_SERVER_OFF_ADDR;
  ADDR_CPY( hProfileInd.simpleLight.param.onAddr.addr, source )
  hProfileInd.status = OPEND_STATUS_OK;
  g_simple_light->HF::Units::Unit<HF::Profiles::SimpleLight>::off( source );

  openD_hanfun_profileInd(&hProfileInd);
}

void SimpleLight::toggle (HF::Protocol::Address &source)
{
  openD_hanfunApi_profileInd_t hProfileInd;

  hProfileInd.profile = OPEND_HANFUNAPI_SIMPLE_LIGHT;
  hProfileInd.simpleLight.service = OPEND_HANFUN_IONOFF_SERVER_TOGGLE_ADDR;
  ADDR_CPY( hProfileInd.simpleLight.param.onAddr.addr, source )
  hProfileInd.status = OPEND_STATUS_OK;
  g_simple_light->HF::Units::Unit<HF::Profiles::SimpleLight>::toggle( source );

  openD_hanfun_profileInd(&hProfileInd);
}

uint16_t openD_hanfunApi_fp_devMgmt_get( openD_hanfunDevice_t **hanfunDevices )
{
  uint16_t size = 0;

  _hanfunDevices.clear();
  hanfunDevice_units.clear();

  FP * fp = FP::instance();
  size = fp->unit0()->device_management()->save( hanfunDevices );

  return size;
}

uint16_t DeviceManagement::Server::save ( openD_hanfunDevice_t **hanfunDevice )
{
   LOG (INFO) << "Saving registration entries..." << NL;

  unsigned i = 0;

  /* *INDENT-OFF* */
  for_each( entries ().begin (), entries ().end (),
            [&i](HF::Core::DeviceManagement::Device &device)
  {

    openD_hanfunDevice_t hanfunDevice;

    /* Address */
    hanfunDevice.address = device.address;
    /* EMC */
    hanfunDevice.emc = device.emc;
    /* Units */
    for( unsigned j = 0; j < device.units.size(); j++ )
    {
      openD_hanfunDevice_unit_t openD_hanfunDevice_unit;
      hanfunDevice_units.push_back( openD_hanfunDevice_unit );

      /* Save the first reference to the current HANFUN device. */
      if( 0U == j) {
        hanfunDevice.units = &hanfunDevice_units.back();
      }

      hanfunDevice.units[j].id = device.units[j].id;
      hanfunDevice.units[j].profile = device.units[j].profile;
    }
    hanfunDevice.units_length = device.units.size();

    /* IPUI */
    const HF::UID::DECT *dect = static_cast <const HF::UID::DECT *>(device.uid.raw ());
    for( uint8_t j = 0; j < HF::UID::DECT::length (); j++ )
    {
      hanfunDevice.ipui[j] = (int) (*dect)[j];
    }

    _hanfunDevices.push_back( hanfunDevice );
    i++;
  });
  /* *INDENT-ON* */

  *hanfunDevice = &_hanfunDevices[0];

  return _hanfunDevices.size();
}

void openD_hanfunApi_fp_devMgmt_set( openD_hanfunDevice_t *hanfunDevice, uint16_t size )
{
  FP * fp = FP::instance();
  fp->unit0()->device_management()->restore( hanfunDevice, size );

  return;
}

void DeviceManagement::Server::restore( openD_hanfunDevice_t *hanfunDevice, uint16_t size )
{
  LOG (INFO) << "Restoring registration entries..." << NL;

  HF::ULE::Transport * transport = HF::ULE::Transport::instance();

  bool isDeviceAvailable = true;
  uint16_t entryIndex = 0U;
  ST_IE_HAN_EXTENDED_DEVICE_ENTRIES st_HANExtendedDeviceEntry;
  ST_HAN_EXTENDED_DEVICE_INFO st_HANExtendedDeviceInfo;
  st_HANExtendedDeviceEntry.u16_NumOfEntries = 0U;
  st_HANExtendedDeviceEntry.pst_DeviceEntries = &st_HANExtendedDeviceInfo;

  set_deviceEntryList( &st_HANExtendedDeviceEntry );

  while( isDeviceAvailable && (entryIndex < MAX_HANFUN_ENTRIES) ) {
    SEM_INIT_READTABLE;

    app_DsrHanDeviceReadTable( 1U, entryIndex++, FALSE );

    SEM_WAIT_READTABLE;

    if( st_HANExtendedDeviceEntry.u16_NumOfEntries < 1U ) {
      /* No device entry available anymore. */
      isDeviceAvailable = false;

    } else {
      /* Device entry available. */
      bool isInDeviceList = false;

      if( st_HANExtendedDeviceEntry.pst_DeviceEntries && hanfunDevice ) {
        for( uint16_t i = 0; i < size; i++ )
        {
          if( 0U == memcmp( st_HANExtendedDeviceEntry.pst_DeviceEntries->u8_IPUI, hanfunDevice[i].ipui, 5U) )
          {
            HF::Core::DeviceManagement::Device device;

            isInDeviceList = true;

            device.address = hanfunDevice[i].address;
            device.emc = hanfunDevice[i].emc;

            HF::UID::DECT *dect = new HF::UID::DECT;
            (*dect)[0] = hanfunDevice[i].ipui[0];
            (*dect)[1] = hanfunDevice[i].ipui[1];
            (*dect)[2] = hanfunDevice[i].ipui[2];
            (*dect)[3] = hanfunDevice[i].ipui[3];
            (*dect)[4] = hanfunDevice[i].ipui[4];
            device.uid = dect;

            for (unsigned j = 0; j <  hanfunDevice[i].units_length; j++)
            {
              device.units.push_back(0);
              device.units[j].id = hanfunDevice[i].units[j].id;
              device.units[j].profile = hanfunDevice[i].units[j].profile;
            }


            /* Add the device to the device management. */
            HF::Core::DeviceManagement::Server <Entries>::entries().insert(device);

            /* Connect the device at the transport instance. */
            HF::ULE::Transport * transport = HF::ULE::Transport::instance();
            transport->connected(st_HANExtendedDeviceEntry.pst_DeviceEntries->u16_DeviceId, hanfunDevice[i].ipui);

            break;
          }
        }
      }

      /* Device is not available in device list. */
      if( !isInDeviceList ) {
        /* Deregister device from module. */
        app_DsrHanDeleteDevice( st_HANExtendedDeviceEntry.pst_DeviceEntries->u16_DeviceId, false );
      }

    }
  }

  return;
}

/* DeviceManagement::Entries::save. */
HF::Common::Result DeviceManagement::Entries::save (const HF::Core::DeviceManagement::Device &device)
{
  /* Save the entry for the register request. */
  auto res = HF::Core::DeviceManagement::Entries::save (device);
  HF::Application::Save();
  return res;
}

void DeviceManagement::Entries::insert (const Device &device)
{
   HF::Core::DeviceManagement::Entries::save (device);
}


void  DeviceManagement::Server::registered (HF::Core::DeviceManagement::DevicePtr &device)
{
  openD_hanfunApi_devMgmtInd_t hDevMgmtIndication;

  if( device == nullptr ) {
    return;
  }

  hDevMgmtIndication.param.getAddress.address = device->address;
  hDevMgmtIndication.service = OPEND_HANFUNAPI_DEVICE_MANAGEMENT_REGISTER_DEVICE;
  openD_hanfun_devMgmtInd( &hDevMgmtIndication );
}


/* DeviceManagement::Entries::destroy. */
HF::Common::Result DeviceManagement::Entries::destroy (const HF::Core::DeviceManagement::Device &device)
{
  /* Destroy the entry for the deregister request. */
  auto res = HF::Core::DeviceManagement::Entries::destroy (device);
  HF::Application::Save();
  return res;
}

/* DeviceManagement::Server::available. */
bool DeviceManagement::Server::available (uint16_t address)
{
  if (address == 0 || address == HF::Protocol::BROADCAST_ADDR)
  {
    return false;
  }

  /* Check if the address is available. */
  auto it = std::find_if(entries().begin(), entries().end(),
                         [address](const HF::Core::DeviceManagement::Device &dev)
                         {
                           return address == dev.address;
                         });

  return it == entries ().end ();
}

/* DeviceManagement::Server::next_address. */
uint16_t DeviceManagement::Server::next_address ()
{
  /* Next address for a device. */
  uint16_t result = _next_address;

  _next_address = HF::Protocol::BROADCAST_ADDR;

  if (result == HF::Protocol::BROADCAST_ADDR)
  {
    result = HF::Core::DeviceManagement::Server <Entries>::next_address ();
  }

  return result;
}

/* DeviceManagement::Server::deregister */
bool DeviceManagement::Server::deregister (uint16_t address)
{
  if (address == 0 || address == HF::Protocol::BROADCAST_ADDR)
  {
    return false;
  }

  auto _entry = entry (address);

  if (_entry != nullptr)
  {
    /* Deregister a node device. */
    HF::Core::DeviceManagement::Server <Entries>::deregister (_entry);
    return true;
  }

  return false;
}

/* BindManagement::Entries::save */
HF::Common::Result BindManagement::Entries::save (const Entry &entry)
{
  auto res = HF::Core::BindManagement::Entries::save (entry);
  return res;
}

/* BindManagement::Entries::insert */
void BindManagement::Entries::insert (Entry &entry)
{
  /* Save the bind management entry. */
  HF::Core::BindManagement::Entries::save (entry);
}

/* BindManagement::Entries::destroy */
HF::Common::Result BindManagement::Entries::destroy (const Entry &entry)
{
  /* Destroy the bind mangement entry. */
  auto res = HF::Core::BindManagement::Entries::destroy (entry);
  return res;
}

static void handle_device_infomation (HF::Common::ByteArray &payload, uint16_t offset)
{
  HF::Protocol::GetAttributePack::Response response (HF::Core::DeviceInformation::create_attribute);

  response.unpack (payload, offset);

  using namespace HF::Core::DeviceInformation;
  using namespace HF::Attributes;
  using namespace HF::Debug;

  uint8_t log_width = 20;

  std::cout.clear (); std::cout << "[INFO ] " << "====== Device Information : Attributes ======"
  << std::endl << std::right << std::setw (log_width) << std::setfill (' ');

  std::for_each (response.attributes.begin (), response.attributes.end (),
                 [log_width](const HF::Attributes::IAttribute *attr)
  {
    std::cout.clear ();std::cout << std::right << std::setw (log_width) << std::setfill (' ');

      switch (attr->uid ())
      {
        case CORE_VERSION_ATTR:
        {
          auto *version = adapt <uint8_t>(attr);
          std::cout.clear (); std::cout << "Core (" << Hex <uint8_t>(attr->uid ())
          << ") | 0x" << Hex <uint8_t>(version->get ());
          break;
        }
        case PROFILE_VERSION_ATTR:
        {
          auto *version = adapt <uint8_t>(attr);
          std::cout.clear (); std::cout << "Profile (" << Hex <uint8_t>(attr->uid ())
          << ") | 0x" << Hex <uint8_t>(version->get ());
          break;
        }
        case INTERFACE_VERSION_ATTR:
        {
          auto *version = adapt <uint8_t>(attr);
          std::cout.clear (); std::cout << "Interface (" << Hex <uint8_t>(attr->uid ())
          << ") | 0x" << std::right << Hex <uint8_t>(version->get ());
          break;
        }
        case EXTRA_CAP_ATTR:
        {
          auto *extra_cap = adapt <uint8_t>(attr);
          std::cout.clear (); std::cout << "Extra Cap. (" << Hex <uint8_t>(attr->uid ())
          << ") | 0x" << Hex <uint8_t>(extra_cap->get ());
          break;
        }
        case MIN_SLEEP_TIME_ATTR:
        {
          auto *min_sleep = adapt <uint32_t>(attr);
          std::cout.clear (); std::cout << "Min. Sleep (" << Hex <uint8_t>(attr->uid ())
          << ") | 0x" << Hex <uint32_t>(min_sleep->get ());
          break;
        }
        case ACTUAL_RESP_TIME_ATTR:
        {
          auto *actual_time = adapt <uint32_t>(attr);
          std::cout.clear (); std::cout << "Actual Resp. Time (" << Hex <uint8_t>(attr->uid ())
          << ") | 0x" << Hex <uint32_t>(actual_time->get ());
          break;
        }
        case APP_VERSION_ATTR:
        {
          auto *version = adapt <std::string>(attr);
          std::cout.clear (); std::cout << "APP Version (" << Hex <uint8_t>(attr->uid ())
          << ") | " << version->get ();
          break;
        }
        case HW_VERSION_ATTR:
        {
          auto *version = adapt <std::string>(attr);
          std::cout.clear (); std::cout << "HW Version (" << Hex <uint8_t>(attr->uid ())
          << ") | " << version->get ();
          break;
        }
        case EMC_ATTR:
        {
          auto *emc = adapt <uint16_t>(attr);
          std::cout.clear (); std::cout << "EMC (" << Hex <uint8_t>(attr->uid ()) << ") | 0x"
          << Hex <uint16_t>(emc->get ());
          break;
        }
        case DECT_ID_ATTR:
        {
          auto *dect = adapt < std::vector < uint8_t >> (attr);
          std::cout.clear ();std::cout << "DECT (" << Hex <uint8_t>(attr->uid ()) << ") | ";
          auto value = dect->get ();
          std::for_each(value.begin (), value.end (), [](uint8_t byte)
          {
             std::cout.clear (); std::cout << byte;
          });
          break;
        }
        case MANUFACTURE_NAME_ATTR:
        {
          auto *name = adapt <std::string>(attr);
          std::cout.clear ();std::cout << "Manuf. Name (" << Hex <uint8_t>(attr->uid ())
          << ") | " << name->get ();
          break;
        }
        case LOCATION_ATTR:
        {
          auto *location = adapt <std::string>(attr);
          std::cout.clear ();std::cout << "Location (" << Hex <uint8_t>(attr->uid ())
          << ") | " << location->get ();
          break;
        }
        case ENABLED_ATTR:
        {
          auto *enabled = adapt <uint8_t>(attr);
          std::cout.clear ();std::cout << "Enable (" << Hex <uint8_t>(attr->uid ())
          << ") | 0x" << Hex <uint8_t>(enabled->get ());
          break;
        }
        case FRIENDLY_NAME_ATTR:
        {
          auto *names_attr = adapt <FriendlyName>(attr);
          std::cout.clear (); std::cout << "Friendly Name (" << Hex <uint8_t>(attr->uid ()) << ") |";
          auto const &names = names_attr->get ();
          std::for_each (names.units.begin (), names.units.end (),
                         [](const FriendlyName::Unit &unit)
          {
             std::cout.clear (); std::cout << " (" << (int) unit.id << ") " << unit.name;
          });
          break;
        }
        case UID_ATTR:
        {
          auto *uid = adapt <HF::UID::UID>(attr);
          std::cout.clear (); std::cout << "UID (" << Hex <uint8_t>(attr->uid ())
          << ") | " << uid->get ();
          break;
        }
        case SERIAL_NUMBER_ATTR:
        {
          auto *serial = adapt <std::string>(attr);
          std::cout.clear (); std::cout << "Serial Number (" << Hex <uint8_t>(attr->uid ())
          << ") | " << serial->get ();
          break;
        }
        default:
        {
          std::cout.clear ();std::cout << "Unknown | UID - " << attr->uid () << std::endl;
          break;
        }
     }

     std::cout.clear (); std::cout << std::endl;
   });

   std::cout.clear (); std::cout << "[INFO ] " << "====== Device Information : Attributes ======"
   << std::endl; std::cout.clear (); std::cerr.clear ();
}

/* Commands::Unit::handle */
HF::Common::Result Commands::Unit::handle (HF::Protocol::Packet &packet,
                                           HF::Common::ByteArray &payload, uint16_t offset)
{
  if (packet.message.type == HF::Protocol::Message::GET_ATTR_PACK_RES &&
      packet.message.itf.id == HF::Interface::DEVICE_INFORMATION)
  {
    /* Handle the received device information after the request. */
    handle_device_infomation (payload, offset);
    return HF::Common::Result::OK;
  }

  return HF::Common::Result::FAIL_ARG;
}

/* FP::receive */
void FP::receive (HF::Protocol::Packet &packet, HF::Common::ByteArray &payload, uint16_t offset)
{
  std::cout.clear (); std::cout << "[DEBUG] " << ">>>>>>>>>>>>> Message Received <<<<<<<<<<<<<"
  << std::endl; std::cout.clear (); std::cerr.clear ();

  std::cout.clear (); std::cout << "[TRACE] " << "Payload : " << payload
  << std::endl; std::cout.clear (); std::cerr.clear ();

  std::cout.clear ();std::cout << "[DEBUG] " << std::endl << packet
  << std::endl; std::cout.clear (); std::cerr.clear ();

  HF::Devices::Concentrator::Abstract <Unit0>::receive (packet, payload, offset);
}

/* FP::has_bind */
bool FP::has_bind (uint16_t dev_addr_1, uint16_t dev_addr_2)
{
  HF::Protocol::Address source (dev_addr_1, 1);
  HF::Common::Interface itf (HF::Interface::ON_OFF, HF::Interface::SERVER_ROLE);
  HF::Protocol::Address destination (dev_addr_2, 1);

  return _unit0.bind_management ()->entries ().find (source, itf, destination) != nullptr;
}

FP * FP::instance()
{
  static FP fp;

  return &fp;
}

/* FP::bind */
uint8_t FP::bind (uint16_t dev_addr_1, uint16_t dev_addr_2)
{
  if (this->has_bind (dev_addr_1, dev_addr_2))
  {
    return 1;
  }

  HF::Protocol::Address source (dev_addr_1, 1);
  HF::Common::Interface itf (HF::Interface::ON_OFF, HF::Interface::SERVER_ROLE);
  HF::Protocol::Address destination (dev_addr_2, 1);

  auto res = _unit0.bind_management ()->add (source, destination, itf);

  if (res == HF::Common::OK)
  {
    return 0;
  }

  if (_unit0.device_management ()->entry (dev_addr_1) == nullptr)
  {
    return 2;
  }

  if (_unit0.device_management ()->entry (dev_addr_2) == nullptr)
  {
    return 3;
  }

  return 4;
}

/* FP::unbind */
bool FP::unbind (uint16_t dev_addr_1, uint16_t dev_addr_2)
{
  HF::Protocol::Address source (dev_addr_1, 1);
  HF::Common::Interface itf (HF::Interface::ON_OFF, HF::Interface::SERVER_ROLE);
  HF::Protocol::Address destination (dev_addr_2, 1);

  return _unit0.bind_management ()->remove (source, destination, itf) == HF::Common::Result::OK;
}

openD_status_t openD_hanfunApi_fp_init( HF::Transport::Layer *transport )
{
  if( !transport )
  {
    return OPEND_STATUS_ARGUMENT_INVALID;
  }

  FP * fp = FP::instance();

  transport->add(fp);

  app_HanRegularStart(TRUE);

  return OPEND_STATUS_OK;
}

openD_status_t opend_hanfunApi_createProfile(openD_hanfunApi_profile_t opend_profile, uint8_t id)
{
  FP * fp = FP::instance();

  switch(opend_profile){
    case OPEND_HANFUNAPI_SIMPLE_LIGHT:
      g_simple_light = new SimpleLight(id, *fp);
      break;
    case OPEND_HANFUNAPI_SIMPLE_ONOFF_SWITCH:
      g_simple_switch = new SimpleSwitch(id, *fp);
      break;
    default:
      return OPEND_STATUS_ARGUMENT_INVALID;
      break;
  }

  return OPEND_STATUS_OK;
}

uint16_t *getAddress()
{
  return appAddress;
}

openD_status_t openD_hanfunApi_fp_devMgmtRequest( openD_hanfunApi_devMgmtReq_t *hMgmtRequest, uint16_t address, uint8_t dectMode )
{
  openD_status_t ret = OPEND_STATUS_FAIL;
  FP * fp = FP::instance();
  HF::Protocol::Address device (address, 0);
  openD_hanfunApi_devMgmtCfm_t hDevMgmtConfirm;
  HF::Core::SessionManagement::Entries<DeviceManagement::Entries> &devices = fp->unit0 ()->device_management ()->entries ();
  uint16_t i = 0;
  HF::Protocol::Message *msg = nullptr;
  std::forward_list <HF::Transport::Link *> &links = fp->links();

  if(hMgmtRequest == NULL)
  {
    return OPEND_STATUS_ARGUMENT_INVALID;
  }

  switch(hMgmtRequest->service){
    case OPEND_HANFUNAPI_DEVICE_MANAGEMENT_REGISTER_ENABLE:
      hDevMgmtConfirm.service = OPEND_HANFUNAPI_DEVICE_MANAGEMENT_REGISTER_ENABLE;
      if(fp->unit0 ()->device_management ()->available (address) && address != 0 &&
         address < HF::Protocol::BROADCAST_ADDR)
      {
        fp->unit0 ()->device_management ()->next_address (address);
        hanfunAddress = address;
        app_SrvSubscriptionOpenExt( 120, CMBS_HS_REG_ENABLE_ULE );
        ret = OPEND_STATUS_OK;
      }
      else
      {
        hDevMgmtConfirm.status = OPEND_STATUS_ARGUMENT_INVALID;
        openD_hanfun_devMgmtCfm( &hDevMgmtConfirm );
        ret =  OPEND_STATUS_ARGUMENT_INVALID;
      }
      break;
    case OPEND_HANFUNAPI_DEVICE_MANAGEMENT_REGISTER_DISABLE:
      hDevMgmtConfirm.service = OPEND_HANFUNAPI_DEVICE_MANAGEMENT_REGISTER_DISABLE;
      app_SrvSubscriptionClose();
      ret = OPEND_STATUS_OK;
      break;
    case OPEND_HANFUNAPI_DEVICE_MANAGEMENT_DEREGISTER:
      hDevMgmtConfirm.service = OPEND_HANFUNAPI_DEVICE_MANAGEMENT_DEREGISTER;
      /* External de-registration. */
      HF::Application::Deregister(address);
      /* HANFUN deregistration. */
      if(fp->unit0 ()->device_management ()->deregister (address) == true)
      {
        hDevMgmtConfirm.status = OPEND_STATUS_OK;
        openD_hanfun_devMgmtCfm( &hDevMgmtConfirm );
        ret = OPEND_STATUS_OK;
      }
      else
      {
        hDevMgmtConfirm.status = OPEND_STATUS_FAIL;
        openD_hanfun_devMgmtCfm( &hDevMgmtConfirm );
        ret = OPEND_STATUS_FAIL;
      }
      break;
    case OPEND_HANFUNAPI_DEVICE_MANAGEMENT_ENTRIES_REGISTRATION:
      {
      hDevMgmtConfirm.service = OPEND_HANFUNAPI_DEVICE_MANAGEMENT_ENTRIES_REGISTRATION;
      hDevMgmtConfirm.param.entriesRegistration.size = (int) devices.size ();
      hDevMgmtConfirm.status = OPEND_STATUS_OK;
      std::vector<hanfunApiDevMgmt_registrationElement_t> registrationElements;

      for(const HF::Core::DeviceManagement::Device &device : devices)
      {
        HF::UID::DECT *dect;
        if(device.uid.raw ()->type () == HF::UID::DECT_UID)
        {
          dect = (HF::UID::DECT *) device.uid.raw ();
          registrationElements.push_back( {device.address, {(*dect)[0], (*dect)[1], (*dect)[2], (*dect)[3], (*dect)[4] } } );
        } else {
          registrationElements.push_back( {device.address, {0, 0, 0, 0, 0} } );
        }
      }
      hDevMgmtConfirm.param.entriesRegistration.registrationElement = &*registrationElements.begin();
      openD_hanfun_devMgmtCfm( &hDevMgmtConfirm );
      ret = OPEND_STATUS_OK;
      }
      break;
    case OPEND_HANFUNAPI_DEVICE_MANAGEMENT_GET_DEVICE_INFORMATION_MANDATORY:
      hDevMgmtConfirm.service = OPEND_HANFUNAPI_DEVICE_MANAGEMENT_GET_DEVICE_INFORMATION_MANDATORY;
      msg = HF::Core::DeviceInformation::mandatory ();
      if (msg != nullptr)
      {
        fp->commands.send (device, *msg, nullptr);
        delete msg;
        hDevMgmtConfirm.status = OPEND_STATUS_OK;
        openD_hanfun_devMgmtCfm( &hDevMgmtConfirm );
      }
      else
      {
        hDevMgmtConfirm.status = OPEND_STATUS_FAIL;
        openD_hanfun_devMgmtCfm( &hDevMgmtConfirm );
      }
      ret = OPEND_STATUS_OK;
      break;
    case OPEND_HANFUNAPI_DEVICE_MANAGEMENT_GET_DEVICE_INFORMATION_ALL:
      hDevMgmtConfirm.service = OPEND_HANFUNAPI_DEVICE_MANAGEMENT_GET_DEVICE_INFORMATION_ALL;
      msg = HF::Core::DeviceInformation::all ();
      if (msg != nullptr)
      {
        fp->commands.send (device, *msg, nullptr);
        delete msg;
        hDevMgmtConfirm.status = OPEND_STATUS_OK;
        openD_hanfun_devMgmtCfm( &hDevMgmtConfirm );
      }
      else
      {
        hDevMgmtConfirm.status = OPEND_STATUS_FAIL;
        openD_hanfun_devMgmtCfm( &hDevMgmtConfirm );
      }
      ret = OPEND_STATUS_OK;
      break;
    case OPEND_HANFUNAPI_DEVICE_MANAGEMENT_CHANGE_CONCENTRATOR_DECT_MODE:
      hDevMgmtConfirm.service = OPEND_HANFUNAPI_DEVICE_MANAGEMENT_CHANGE_CONCENTRATOR_DECT_MODE;
      hDevMgmtConfirm.status = OPEND_STATUS_OK;

      openD_hanfun_devMgmtCfm( &hDevMgmtConfirm );
      ret = OPEND_STATUS_OK;
      break;
    case OPEND_HANFUNAPI_DEVICE_MANAGEMENT_ENTRIES_LINK:
      {
      hDevMgmtConfirm.service = OPEND_HANFUNAPI_DEVICE_MANAGEMENT_ENTRIES_LINK;
      hDevMgmtConfirm.status = OPEND_STATUS_OK;
      std::vector<hanfunApiDevMgmt_registrationElement_t> registrationElements;

      for(const HF::Transport::Link *link : links)
      {
        HF::UID::DECT *dect;
        if(link->uid().raw ()->type () == HF::UID::DECT_UID)
        {
          dect = (HF::UID::DECT *) link->uid().raw ();
          registrationElements.push_back( {link->address(), {(*dect)[0], (*dect)[1], (*dect)[2], (*dect)[3], (*dect)[4] } } );
        } else {
          registrationElements.push_back( {link->address(), {0, 0, 0, 0, 0} } );
        }
        i++;
      }
      hDevMgmtConfirm.param.entriesRegistration.size = i;
      hDevMgmtConfirm.param.entriesRegistration.registrationElement = &*registrationElements.begin();
      openD_hanfun_devMgmtCfm( &hDevMgmtConfirm );
      ret = OPEND_STATUS_OK;
      }
      break;
    default:
      hDevMgmtConfirm.status = OPEND_STATUS_ARGUMENT_INVALID;
      openD_hanfun_devMgmtCfm( &hDevMgmtConfirm );
      ret = OPEND_STATUS_ARGUMENT_INVALID;
      break;
  }

  return ret;
}

openD_status_t openD_hanfunApi_fp_bindMgmtRequest( openD_hanfunApi_bindMgmtReq_t *hBindRequest, uint16_t address1, uint16_t address2 )
{
  FP * fp = FP::instance();
  HF::Common::_Result res;
  HF::Protocol::Address source;
  HF::Protocol::Address dest (0, 1);
  HF::Common::Interface itf(HF::Interface::ANY_UID);
  HF::Core::BindManagement::Entries entries;
  openD_hanfunApi_bindMgmtCfm_t hBindMgmtConfirm;
  uint8_t entriesSize = 0;

  if(hBindRequest == NULL)
  {
    return OPEND_STATUS_ARGUMENT_INVALID;
  }

  switch(hBindRequest->service){
    case OPEND_HANFUNAPI_BIND_MANAGEMENT_ADD_GLOBAL_BIND:
      hBindMgmtConfirm.service = OPEND_HANFUNAPI_BIND_MANAGEMENT_ADD_GLOBAL_BIND;
      res = fp->unit0 ()->bind_management ()->add (source, dest, itf);
      if(res == HF::Common::OK)
      {
        hBindMgmtConfirm.status = OPEND_STATUS_OK;
        openD_hanfun_bindMgmtCfm(&hBindMgmtConfirm);
        return OPEND_STATUS_OK;
      }
      else
      {
        hBindMgmtConfirm.status = OPEND_STATUS_FAIL;
        openD_hanfun_bindMgmtCfm(&hBindMgmtConfirm);
        return OPEND_STATUS_FAIL;
      }
      break;
    case OPEND_HANFUNAPI_BIND_MANAGEMENT_REMOVE_GLOBAL_BIND:
      hBindMgmtConfirm.service = OPEND_HANFUNAPI_BIND_MANAGEMENT_REMOVE_GLOBAL_BIND;
      res = fp->unit0 ()->bind_management ()->remove (source, dest, itf);
      if(res == HF::Common::OK)
      {
        hBindMgmtConfirm.status = OPEND_STATUS_OK;
        openD_hanfun_bindMgmtCfm(&hBindMgmtConfirm);
        return OPEND_STATUS_OK;
      }
      else
      {
        hBindMgmtConfirm.status = OPEND_STATUS_FAIL;
        openD_hanfun_bindMgmtCfm(&hBindMgmtConfirm);
        return OPEND_STATUS_FAIL;
      }
      break;
    case OPEND_HANFUNAPI_BIND_MANAGEMENT_ADD:
      hBindMgmtConfirm.service = OPEND_HANFUNAPI_BIND_MANAGEMENT_ADD;
      hBindMgmtConfirm.status = OPEND_STATUS_OK;
      hBindMgmtConfirm.param.entriesElement.error = fp->bind (address1, address2);
      hBindMgmtConfirm.param.entriesElement.devicesToBind.address1 = address1;
      hBindMgmtConfirm.param.entriesElement.devicesToBind.address2 = address2;
      openD_hanfun_bindMgmtCfm(&hBindMgmtConfirm);
      return OPEND_STATUS_OK;
      break;
    case OPEND_HANFUNAPI_BIND_MANAGEMENT_REMOVE:
      hBindMgmtConfirm.service = OPEND_HANFUNAPI_BIND_MANAGEMENT_REMOVE;
      hBindMgmtConfirm.status = OPEND_STATUS_OK;
      if (fp->unbind (address1, address2))
      {
        hBindMgmtConfirm.param.entriesElement.error = 1;
      }
      else
      {
        hBindMgmtConfirm.param.entriesElement.error = 0;
      }
      hBindMgmtConfirm.param.entriesElement.devicesToBind.address1 = address1;
      hBindMgmtConfirm.param.entriesElement.devicesToBind.address2 = address2;
      openD_hanfun_bindMgmtCfm(&hBindMgmtConfirm);
      return OPEND_STATUS_OK;
      break;
    case OPEND_HANFUNAPI_BIND_MANAGEMENT_ENTRIES:
      entries = fp->unit0 ()->bind_management ()->entries ();
      hBindMgmtConfirm.service = OPEND_HANFUNAPI_BIND_MANAGEMENT_ENTRIES;
      hBindMgmtConfirm.status = OPEND_STATUS_OK;
      for(const HF::Core::BindManagement::Entry &entry : entries)
      {
        hBindMgmtConfirm.param.entriesElement.src[entriesSize].mod = entry.source.mod;
        hBindMgmtConfirm.param.entriesElement.src[entriesSize].device = entry.source.device;
        hBindMgmtConfirm.param.entriesElement.src[entriesSize].unit = entry.source.unit;
        hBindMgmtConfirm.param.entriesElement.dst[entriesSize].mod = entry.destination.mod;
        hBindMgmtConfirm.param.entriesElement.dst[entriesSize].device = entry.destination.device;
        hBindMgmtConfirm.param.entriesElement.dst[entriesSize].unit = entry.destination.unit;
        hBindMgmtConfirm.param.entriesElement.itf[entriesSize].role = entry.itf.role;
        hBindMgmtConfirm.param.entriesElement.itf[entriesSize].id = entry.itf.id;
        entriesSize++;
      }
      hBindMgmtConfirm.param.entriesElement.entriesSize = entriesSize;
      openD_hanfun_bindMgmtCfm(&hBindMgmtConfirm);
      return OPEND_STATUS_OK;
      break;
    default:
      hBindMgmtConfirm.status = OPEND_STATUS_ARGUMENT_INVALID;
      openD_hanfun_bindMgmtCfm(&hBindMgmtConfirm);
      return OPEND_STATUS_ARGUMENT_INVALID;
      break;
  }
}

static openD_status_t simpleOnOffSwitchService( openD_hanfunApi_profileReq_t *hProfileRequest, HF::Protocol::Address device )
{
  openD_hanfunApi_profileCfm_t hProfileConfirm;

  if( nullptr == g_simple_switch ) {
    return OPEND_STATUS_FAIL;
  }

  switch(hProfileRequest->simpleOnOffSwitch.service){
    case OPEND_HANFUN_IONOFF_CLIENT_ON:
      g_simple_switch->on(device);
      break;
    case OPEND_HANFUN_IONOFF_CLIENT_OFF:
      g_simple_switch->off(device);
      break;
    case OPEND_HANFUN_IONOFF_CLIENT_TOGGLE:
      g_simple_switch->toggle(device);
      break;
    default:
      return OPEND_STATUS_SERVICE_UNKNOWN;
      break;
  }

  hProfileConfirm.profile = OPEND_HANFUNAPI_SIMPLE_ONOFF_SWITCH;
  hProfileConfirm.status = OPEND_STATUS_OK;
  openD_hanfun_profileCfm(&hProfileConfirm);
  return OPEND_STATUS_OK;
}

openD_status_t openD_hanfunApi_fp_profileRequest( openD_hanfunApi_profileReq_t *hProfileRequest, uint16_t address, uint16_t unit )
{
  HF::Protocol::Address device(address, unit);
  openD_hanfunApi_profileCfm_t hProfileConfirm;

  if(hProfileRequest == NULL)
  {
    return OPEND_STATUS_ARGUMENT_INVALID;
  }

  /* Check if device is registered. */
  FP * fp = FP::instance();
  auto _entry = fp->unit0 ()->device_management ()->entry ( address );
  if(_entry == nullptr)
  {
    return OPEND_STATUS_ARGUMENT_INVALID;
  }

  switch(hProfileRequest->profile){
    case OPEND_HANFUNAPI_SIMPLE_ONOFF_SWITCH:
      return simpleOnOffSwitchService(hProfileRequest, device);
      break;
    default:
      hProfileConfirm.status = OPEND_STATUS_ARGUMENT_INVALID;
      openD_hanfun_profileCfm(&hProfileConfirm);
      return OPEND_STATUS_ARGUMENT_INVALID;
      break;
  }
}
