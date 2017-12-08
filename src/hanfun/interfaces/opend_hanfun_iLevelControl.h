#ifdef __cplusplus
extern "C"
{
#endif
/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       opend_hanfun_iLevelControl.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN API iLevelControl.
 *
 * @addtogroup OPEND_HANFUN_INTERFACE
 * @{
 *
 * @defgroup   OPEND_HANFUN_API_ILEVELCONTROL openD HAN-FUN API iLevelControl
 *             This module specifies the HAN-FUN LevelControl interface.
 * @{
 */

#ifndef __OPEND_HANFUN_API_ILEVELCONTROL_H__
#define __OPEND_HANFUN_API_ILEVELCONTROL_H__

#include <stdint.h>
#include <float.h>

#include "../opend_hanfun_dataTypes.h"

/**
 * openD HanfunApi iLevelControl services.
 */
typedef enum openD_hanfunApi_iLevelControl_service {
  /**
   * Get the current level.
   */
  OPEND_HANFUN_ILEVELCONTROL_SERVER_GET_LEVEL,
  /**
   * Get the server level @c levelInt.
   */
  OPEND_HANFUN_ILEVELCONTROL_SERVER_SET_LEVEL_INT,
  /**
   * Set the server level @c levelFloat.
   */
  OPEND_HANFUN_ILEVELCONTROL_SERVER_SET_LEVEL_FLOAT,
  /**
   * Increase the current level @c levelInt.
   */
  OPEND_HANFUN_ILEVELCONTROL_SERVER_INCREASE_LEVEL_INT,
  /**
   * Increase the current level @c levelFloat.
   */
  OPEND_HANFUN_ILEVELCONTROL_SERVER_INCREASE_LEVEL_FLOAT,
  /**
   * Decrease the current level @c levelInt.
   */
  OPEND_HANFUN_ILEVELCONTROL_SERVER_DECREASE_LEVEL_INT,
  /**
   * Decrease the current level @c levelFloat.
   */
  OPEND_HANFUN_ILEVELCONTROL_SERVER_DECREASE_LEVEL_FLOAT,
  /**
   * Message when the level value is changed.
   */
  OPEND_HANFUN_ILEVELCONTROL_SERVER_LEVEL_CHANGE,

  /**
   * Send a SET_LEVEL message to broadcast network address to set the level
   * at @c levelInt.
   */
  OPEND_HANFUN_ILEVELCONTROL_CLIENT_SET_LEVEL_INT,
  /**
   * Send a SET_LEVEL message to the device at the given address
   * @c addr to set the level @c new_level at @ref openD_hanfunApi_iLevelControl_levelIntAddr_t.
   */
  OPEND_HANFUN_ILEVELCONTROL_CLIENT_SET_LEVEL_INT_ADDR,
  /**
   * Send a SET_LEVEL message to broadcast network address to set the level
   * at @c levelFloat.
   */
  OPEND_HANFUN_ILEVELCONTROL_CLIENT_SET_LEVEL_FLOAT,
  /**
   * Send a SET_LEVEL message to the device at the given address
   * @c addr to set the level @c new_level at @ref openD_hanfunApi_iLevelControl_levelFloatAddr_t.
   */
  OPEND_HANFUN_ILEVELCONTROL_CLIENT_SET_LEVEL_FLOAT_ADDR,
  /**
   * Send a INCREASE_LEVEL message to broadcast network address to increase
   * the level by @c levelInt.
   */
  OPEND_HANFUN_ILEVELCONTROL_CLIENT_INCREASE_LEVEL_INT,
  /**
   * Send a INCREASE_LEVEL message to the device at the given address
   * @c addr to increment the level by @c new_level at @ref openD_hanfunApi_iLevelControl_levelIntAddr_t.
   */
  OPEND_HANFUN_ILEVELCONTROL_CLIENT_INCREASE_LEVEL_INT_ADDR,
  /**
   * Send a INCREASE_LEVEL message to broadcast network address to increase
   * the level by @c levelFloat.
   */
  OPEND_HANFUN_ILEVELCONTROL_CLIENT_INCREASE_LEVEL_FLOAT,
  /**
   * Send a INCREASE_LEVEL message to the device at the given address
   * @c addr to increment the level by @c new_level at @ref openD_hanfunApi_iLevelControl_levelFloatAddr_t.
   */
  OPEND_HANFUN_ILEVELCONTROL_CLIENT_INCREASE_LEVEL_FLOAT_ADDR,
  /**
   * Send a INCREASE_LEVEL message to broadcast network address to decrease
   * the level by @c levelInt.
   */
  OPEND_HANFUN_ILEVELCONTROL_CLIENT_DECREASE_LEVEL_INT,
  /**
   * Send a INCREASE_LEVEL message to the device at the given address
   * @c addr to decrement the level by @c new_level at @ref openD_hanfunApi_iLevelControl_levelIntAddr_t.
   */
  OPEND_HANFUN_ILEVELCONTROL_CLIENT_DECREASE_LEVEL_INT_ADDR,
  /**
   * Send a INCREASE_LEVEL message to broadcast network address to decrease
   * the level by @c levelFloat.
   */
  OPEND_HANFUN_ILEVELCONTROL_CLIENT_DECREASE_LEVEL_FLOAT,
  /**
   * Send a INCREASE_LEVEL message to the device at the given address
   * @c addr to decrement the level by @c new_level at @ref openD_hanfunApi_iLevelControl_levelFloatAddr_t.
   */
  OPEND_HANFUN_ILEVELCONTROL_CLIENT_DECREASE_LEVEL_FLOAT_ADDR,
} openD_hanfunApi_iLevelControl_service_t;

/**
 * openD Hanfun iLevelControl levelChange structure.
 */
typedef struct openD_hanfunApi_iLevelControl_levelChange {
  /**
    * Hanfun device source address the change was received from.
    */
  openD_hanfunApi_address_t source;
  /**
    * Old level value to used.
    */
  uint8_t old_level;
  /**
    * New level value to use.
    */
  uint8_t new_level;
} openD_hanfunApi_iLevelControl_levelChange_t;

/**
 * openD Hanfun iLevelControl levelIntAddr structure.
 */
typedef struct openD_hanfunApi_iLevelControl_levelIntAddr {
  /**
    * Hanfun network address to send the message to.
    */
  openD_hanfunApi_address_t addr;
  /**
    * New level value to send in the message.
    */
  uint8_t new_level;
} openD_hanfunApi_iLevelControl_levelIntAddr_t;

/**
 * openD Hanfun iLevelControl levelIntAddr structure.
 */
typedef struct openD_hanfunApi_iLevelControl_levelFloatAddr {
  /**
    * Hanfun network address to send the message to.
    */
  openD_hanfunApi_address_t addr;
  /**
    * New level value to send in the message.
    */
  float new_level;
} openD_hanfunApi_iLevelControl_levelFloatAddr_t;

/**
 * openD HanfunApi iLevelControl structure.
 */
typedef struct openD_hanfunApi_iLevelControl {
  /**
   * HanfunApi iLevelControl service.
   */
  openD_hanfunApi_iLevelControl_service_t service;

    /**
     * HanfunApi iLevelControl parameters.
     */
  union {
    /**
     * HanfunApi integer level parameter.
     */
    uint8_t levelInt;
    /**
     * HanfunApi float level parameter.
     */
    float levelFloat;
    /**
     * HanfunApi levelChange structure parameter.
     */
    openD_hanfunApi_iLevelControl_levelChange_t levelChange;
    /**
     * HanfunApi levelIntAddr structure parameter.
     */
    openD_hanfunApi_iLevelControl_levelIntAddr_t levelIntAddr;
    /**
     * HanfunApi levelFloatAddr structure parameter.
     */
    openD_hanfunApi_iLevelControl_levelFloatAddr_t levelFloatAddr;
  } param;
} openD_hanfunApi_iLevelControl_t;


/*! @} defgroup OPEND_HANFUN_API_ILEVELCONTROL */

/*! @} addtogroup OPEND_HANFUN_INTERFACE */

#endif /* __OPEND_HANFUN_ILEVELCONTROL_H__ */
#ifdef __cplusplus
}
#endif
