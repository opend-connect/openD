// =============================================================================
/*!
 * @file       src/profiles.cpp
 *
 * This file contains the implementation of the functionality related with HAN-FUN
 * Profiles.
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

#include "hanfun/common.h"

#include "hanfun/interface.h"

#include "hanfun/profiles.h"

// =============================================================================
// Defines
// =============================================================================

/*!
 * Profile table entry.
 */
struct Profile
{
   uint16_t uid;     //!< Profile UID.
   uint16_t index;   //!< Start index on @c profiles_interfaces table, for the profile.
   uint8_t  count;   //!< Number of interface entries in @c profiles_interfaces table.
};

// =============================================================================
// Global Variables
// =============================================================================

/*!
 * Interface UID + Interface Role for profile.
 */
static const HF::Common::Interface profiles_interfaces[] =
{
   // 00 - HF::Profiles::SIMPLE_ONOFF_SWITCHABLE
   {HF::Interface::ON_OFF,             HF::Interface::SERVER_ROLE},

   // 01 - HF::Profiles::SIMPLE_ONOFF_SWITCH
   {HF::Interface::ON_OFF,             HF::Interface::CLIENT_ROLE},

   // 02 - HF::Profiles::SIMPLE_LEVEL_CONTROLLABLE
   {HF::Interface::LEVEL_CONTROL,      HF::Interface::SERVER_ROLE},

   // 03 - HF::Profiles::SIMPLE_LEVEL_CONTROL
   {HF::Interface::LEVEL_CONTROL,      HF::Interface::CLIENT_ROLE},

   // 04 - HF::Profiles::SIMPLE_LEVEL_CONTROLLABLE_SWITCHABLE
   {HF::Interface::ON_OFF,             HF::Interface::SERVER_ROLE},
   {HF::Interface::LEVEL_CONTROL,      HF::Interface::SERVER_ROLE},

   // 06 - HF::Profiles::SIMPLE_LEVEL_CONTROL_SWITCH,
   {HF::Interface::ON_OFF,             HF::Interface::CLIENT_ROLE},
   {HF::Interface::LEVEL_CONTROL,      HF::Interface::CLIENT_ROLE},

   // 08 - HF::Profiles::AC_OUTLET,
   {HF::Interface::ON_OFF,             HF::Interface::SERVER_ROLE},

   // 09 - HF::Profiles::AC_OUTLET_WITH_POWER_METERING,
   {HF::Interface::ON_OFF,             HF::Interface::SERVER_ROLE},
   {HF::Interface::SIMPLE_POWER_METER, HF::Interface::SERVER_ROLE},

   // 11 - HF::Profiles::SIMPLE_LIGHT,
   {HF::Interface::ON_OFF,             HF::Interface::SERVER_ROLE},

   // 12 - HF::Profiles::DIMMABLE_LIGHT,
   {HF::Interface::ON_OFF,             HF::Interface::SERVER_ROLE},
   {HF::Interface::LEVEL_CONTROL,      HF::Interface::SERVER_ROLE},

   // 14 - HF::Profiles::DIMMER_SWITCH,
   {HF::Interface::ON_OFF,             HF::Interface::CLIENT_ROLE},
   {HF::Interface::LEVEL_CONTROL,      HF::Interface::CLIENT_ROLE},

   // 16 - HF::Profiles::SIMPLE_DOOR_LOCK,
   {HF::Interface::ON_OFF,             HF::Interface::SERVER_ROLE},

   // 17 - HF::Profiles::DOOR_BELL,
   {HF::Interface::ALERT,              HF::Interface::SERVER_ROLE},

   // 18 - HF::Profiles::SIMPLE_POWER_METER,
   {HF::Interface::SIMPLE_POWER_METER, HF::Interface::SERVER_ROLE},

   // 19 - HF::Profiles::SIMPLE_DETECTOR,
   {HF::Interface::ALERT,              HF::Interface::SERVER_ROLE},

   // 20 - HF::Profiles::DOOR_OPEN_CLOSE_DETECTOR,
   {HF::Interface::ALERT,              HF::Interface::SERVER_ROLE},

   // 21 - HF::Profiles::WINDOW_OPEN_CLOSE_DETECTOR,
   {HF::Interface::ALERT,              HF::Interface::SERVER_ROLE},

   // 22 - HF::Profiles::MOTION_DETECTOR,
   {HF::Interface::ALERT,              HF::Interface::SERVER_ROLE},

   // 23 - HF::Profiles::SMOKE_DETECTOR,
   {HF::Interface::ALERT,              HF::Interface::SERVER_ROLE},

   // 24 - HF::Profiles::GAS_DETECTOR,
   {HF::Interface::ALERT,              HF::Interface::SERVER_ROLE},

   // 25 - HF::Profiles::FLOOD_DETECTOR,
   {HF::Interface::ALERT,              HF::Interface::SERVER_ROLE},

   // 26 - HF::Profiles::GLASS_BREAK_DETECTOR,
   {HF::Interface::ALERT,              HF::Interface::SERVER_ROLE},

   // 27 - HF::Profiles::VIBRATION_DETECTOR,
   {HF::Interface::ALERT,              HF::Interface::SERVER_ROLE},

   // 28 - HF::Profiles::SIREN,
   {HF::Interface::ON_OFF,             HF::Interface::SERVER_ROLE},

   // 29 - HF::Profiles::ALERTABLE,
   {HF::Interface::ALERT,              HF::Interface::CLIENT_ROLE},

   // 30 - HF::Profiles::SIMPLE_PENDANT,
   {HF::Interface::ALERT,              HF::Interface::SERVER_ROLE},

   // 31 - HF::Profiles::SIMPLE_TEMPERATURE_SENSOR,
   {HF::Interface::SIMPLE_TEMPERATURE, HF::Interface::SERVER_ROLE},

   // 32 - HF::Profiles::SIMPLE_HUMIDITY_SENSOR,
   {HF::Interface::SIMPLE_HUMIDITY,    HF::Interface::SERVER_ROLE},
};

/*!
 * Profile to interface mapping.
 */
static const Profile profiles[] =
{
   // Profile UID,                                      Index,  Count.
   {HF::Profiles::SIMPLE_ONOFF_SWITCHABLE,              0x0000, 1},      // 0
   {HF::Profiles::SIMPLE_ONOFF_SWITCH,                  0x0001, 1},      // 1
   {HF::Profiles::SIMPLE_LEVEL_CONTROLLABLE,            0x0002, 1},      // 2
   {HF::Profiles::SIMPLE_LEVEL_CONTROL,                 0x0003, 1},      // 3
   {HF::Profiles::SIMPLE_LEVEL_CONTROLLABLE_SWITCHABLE, 0x0004, 2},      // 4
   {HF::Profiles::SIMPLE_LEVEL_CONTROL_SWITCH,          0x0006, 2},      // 6
   {HF::Profiles::AC_OUTLET,                            0x0008, 1},      // 8
   {HF::Profiles::AC_OUTLET_WITH_POWER_METERING,        0x0009, 2},      // 9
   {HF::Profiles::SIMPLE_LIGHT,                         0x000B, 1},      // 11
   {HF::Profiles::DIMMABLE_LIGHT,                       0x000C, 2},      // 12
   {HF::Profiles::DIMMER_SWITCH,                        0x000E, 2},      // 14
   {HF::Profiles::SIMPLE_DOOR_LOCK,                     0x0010, 1},      // 16
   {HF::Profiles::DOOR_BELL,                            0x0011, 1},      // 17
   {HF::Profiles::SIMPLE_POWER_METER,                   0x0012, 1},      // 18
   {HF::Profiles::SIMPLE_DETECTOR,                      0x0013, 1},      // 19
   {HF::Profiles::DOOR_OPEN_CLOSE_DETECTOR,             0x0014, 1},      // 20
   {HF::Profiles::WINDOW_OPEN_CLOSE_DETECTOR,           0x0015, 1},      // 21
   {HF::Profiles::MOTION_DETECTOR,                      0x0016, 1},      // 22
   {HF::Profiles::SMOKE_DETECTOR,                       0x0017, 1},      // 23
   {HF::Profiles::GAS_DETECTOR,                         0x0018, 1},      // 24
   {HF::Profiles::FLOOD_DETECTOR,                       0x0019, 1},      // 25
   {HF::Profiles::GLASS_BREAK_DETECTOR,                 0x001A, 1},      // 26
   {HF::Profiles::VIBRATION_DETECTOR,                   0x001B, 1},      // 27
   {HF::Profiles::SIREN,                                0x001C, 1},      // 28
   {HF::Profiles::ALERTABLE,                            0x001D, 1},      // 29
   {HF::Profiles::SIMPLE_PENDANT,                       0x001E, 1},      // 30
   {HF::Profiles::SIMPLE_TEMPERATURE_SENSOR,            0x001F, 1},      // 31
   {HF::Profiles::SIMPLE_HUMIDITY_SENSOR,               0x0020, 1},      // 32
   {HF::Profiles::USER_INTERFACE,                       0xFFFF, 0},      //
   {HF::Profiles::GENERIC_APPLICATION,                  0xFFFF, 0},      //
};

// =============================================================================
// API
// =============================================================================

// =============================================================================
// HF::Profiles::interfaces
// =============================================================================
/*!
 *
 */
// =============================================================================
HF::Common::Interface const *HF::Profiles::interfaces (uint16_t profile, uint16_t &count)
{
   for (uint32_t index = 0; index < (sizeof(profiles) / sizeof(*profiles)); ++index)
   {
      if (profiles[index].uid == profile)
      {
         count = profiles[index].count;

         if (count == 0)
         {
            return nullptr;
         }
         else
         {
            return &(profiles_interfaces[profiles[index].index]);
         }
      }
   }

   return nullptr;
}
