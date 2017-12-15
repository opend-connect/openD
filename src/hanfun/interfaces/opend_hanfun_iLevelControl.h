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
 * @brief      openD HAN-FUN iLevelControl.
 *
 * @addtogroup OPEND_HANFUN_INTERFACE
 * @{
 *
 * @defgroup   OPEND_HANFUN_ILEVELCONTROL openD HAN-FUN iLevelControl
 *             This module specifies the HAN-FUN LevelControl interface.
 * @{
 */

#ifndef __OPEND_HANFUN_ILEVELCONTROL_H__
#define __OPEND_HANFUN_ILEVELCONTROL_H__

#include <stdint.h>
#include <float.h>

#include "../opend_hanfun_dataTypes.h"

/**
 * openD Hanfun iLevelControl client services.
 */
typedef enum openD_hanfun_iLevelControlClient_service {
  /**
   * Send a SET_LEVEL message to broadcast network address to set the level
   * at @c levelInt.
   */
  OPEND_HANFUN_ILEVELCONTROL_CLIENT_SET_LEVEL_INT,
  /**
   * Send a SET_LEVEL message to the device at the given address
   * @c addr to set the level @c new_level at @ref openD_hanfun_iLevelControl_levelIntAddr_t.
   */
  OPEND_HANFUN_ILEVELCONTROL_CLIENT_SET_LEVEL_INT_ADDR,
  /**
   * Send a SET_LEVEL message to broadcast network address to set the level
   * at @c levelFloat.
   */
  OPEND_HANFUN_ILEVELCONTROL_CLIENT_SET_LEVEL_FLOAT,
  /**
   * Send a SET_LEVEL message to the device at the given address
   * @c addr to set the level @c new_level at @ref openD_hanfun_iLevelControl_levelFloatAddr_t.
   */
  OPEND_HANFUN_ILEVELCONTROL_CLIENT_SET_LEVEL_FLOAT_ADDR,
  /**
   * Send a INCREASE_LEVEL message to broadcast network address to increase
   * the level by @c levelInt.
   */
  OPEND_HANFUN_ILEVELCONTROL_CLIENT_INCREASE_LEVEL_INT,
  /**
   * Send a INCREASE_LEVEL message to the device at the given address
   * @c addr to increment the level by @c new_level at @ref openD_hanfun_iLevelControl_levelIntAddr_t.
   */
  OPEND_HANFUN_ILEVELCONTROL_CLIENT_INCREASE_LEVEL_INT_ADDR,
  /**
   * Send a INCREASE_LEVEL message to broadcast network address to increase
   * the level by @c levelFloat.
   */
  OPEND_HANFUN_ILEVELCONTROL_CLIENT_INCREASE_LEVEL_FLOAT,
  /**
   * Send a INCREASE_LEVEL message to the device at the given address
   * @c addr to increment the level by @c new_level at @ref openD_hanfun_iLevelControl_levelFloatAddr_t.
   */
  OPEND_HANFUN_ILEVELCONTROL_CLIENT_INCREASE_LEVEL_FLOAT_ADDR,
  /**
   * Send a INCREASE_LEVEL message to broadcast network address to decrease
   * the level by @c levelInt.
   */
  OPEND_HANFUN_ILEVELCONTROL_CLIENT_DECREASE_LEVEL_INT,
  /**
   * Send a INCREASE_LEVEL message to the device at the given address
   * @c addr to decrement the level by @c new_level at @ref openD_hanfun_iLevelControl_levelIntAddr_t.
   */
  OPEND_HANFUN_ILEVELCONTROL_CLIENT_DECREASE_LEVEL_INT_ADDR,
  /**
   * Send a INCREASE_LEVEL message to broadcast network address to decrease
   * the level by @c levelFloat.
   */
  OPEND_HANFUN_ILEVELCONTROL_CLIENT_DECREASE_LEVEL_FLOAT,
  /**
   * Send a INCREASE_LEVEL message to the device at the given address
   * @c addr to decrement the level by @c new_level at @ref openD_hanfun_iLevelControl_levelFloatAddr_t.
   */
  OPEND_HANFUN_ILEVELCONTROL_CLIENT_DECREASE_LEVEL_FLOAT_ADDR,
} openD_hanfun_iLevelControlClient_service_t;

/**
 * openD Hanfun iLevelControl server services.
 */
typedef enum openD_hanfun_iLevelControlServer_service {
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

} openD_hanfun_iLevelControlServer_service_t;

/**
 * openD Hanfun iLevelControl client request parameter structure of the @c SET_LEVEL_INT, @c INCREASE_LEVEL_INT and @c DECREASE_LEVEL_INT service.
 */
typedef struct openD_hanfun_iLevelControlClientReq_levelInt {
  /**
   * Value to send in the message.
   */
  uint8_t value;
} openD_hanfun_iLevelControlClientReq_levelInt_t;

/**
 * openD Hanfun iLevelControl client request parameter structure of the @c SET_LEVEL_INT_ADDR, @c INCREASE_LEVEL_INT_ADDR and @c DECREASE_LEVEL_INT_ADDR service.
 */
typedef struct openD_hanfun_iLevelControlClientReq_levelIntAddr {
  /**
   * Hanfun network address to send the message to.
   */
  openD_hanfun_address_t addr;
  /**
   * Value to send in the message.
   */
  uint8_t value;
} openD_hanfun_iLevelControlClientReq_levelIntAddr_t;

/**
 * openD Hanfun iLevelControl client request parameter structure of the @c SET_LEVEL_FLOAT, @c INCREASE_LEVEL_FLOAT and @c DECREASE_LEVEL_FLOAT service.
 */
typedef struct openD_hanfun_iLevelControlClientReq_levelFloat {
  /**
   * Value to send in the message.
   */
  uint8_t value;
} openD_hanfun_iLevelControlClientReq_levelFloat_t;

/**
 * openD Hanfun iLevelControl client request parameter structure of the @c SET_LEVEL_FLOAT_ADDR, @c INCREASE_LEVEL_FLOAT_ADDR and @c DECREASE_LEVEL_FLOAT_ADDR service.
 */
typedef struct openD_hanfun_iLevelControlClientReq_levelFloatAddr {
  /**
   * Hanfun network address to send the message to.
   */
  openD_hanfun_address_t addr;
  /**
   * Value to send in the message.
   */
  uint8_t value;
} openD_hanfun_iLevelControlClientReq_levelFloatAddr_t;

/**
 * openD Hanfun iLevelControl server confirm parameter structure of the @c GET_LEVEL service.
 */
typedef struct openD_hanfun_iLevelControlServerCfm_getLevel {
  /**
   * Current level.
   */
  uint8_t value;
} openD_hanfun_iLevelControlServerCfm_getLevel_t;

/**
 * openD Hanfun iLevelControl server request parameter structure of the @c SET_LEVEL_INT, @c INCREASE_LEVEL_INT and @c DECREASE_LEVEL_INT service.
 */
typedef struct openD_hanfun_iLevelControlServerReq_levelInt {
  /**
   * Value to send in the message.
   */
  uint8_t value;
} openD_hanfun_iLevelControlServerReq_levelInt_t;

/**
 * openD Hanfun iLevelControl server request parameter structure of the @c SET_LEVEL_FLOAT, @c INCREASE_LEVEL_FLOAT and @c DECREASE_LEVEL_FLOAT service.
 */
typedef struct openD_hanfun_iLevelControlServerReq_levelFloat {
  /**
   * Value to send in the message.
   */
  uint8_t value;
} openD_hanfun_iLevelControlServerReq_levelFloat_t;

/**
 * openD Hanfun iLevelControl server indication parameter structure of the @c LEVEL_CHANGE service.
 */
typedef struct openD_hanfun_iLevelControlServerInd_levelChange {
  /**
   * Hanfun device source address the change was received from.
   */
  openD_hanfun_address_t source;
  /**
   * Old level value to used.
   */
  uint8_t old_level;
  /**
   * New level value to use.
   */
  uint8_t new_level;
} openD_hanfun_iLevelControlServerInd_levelChange_t;


/**
 * openD Hanfun iLevelControl client request structure.
 */
typedef struct openD_hanfun_iLevelControlClientReq {
  /**
   * Hanfun iLevelControl client service.
   */
  openD_hanfun_iLevelControlClient_service_t service;

    /**
     * Hanfun iLevelControl parameters.
     */
  union {
    openD_hanfun_iLevelControlClientReq_levelInt_t setLevelInt;
    openD_hanfun_iLevelControlClientReq_levelIntAddr_t setLevelIntAddr;
    openD_hanfun_iLevelControlClientReq_levelFloat_t setLevelFloat;
    openD_hanfun_iLevelControlClientReq_levelFloatAddr_t setLevelFloatAddr;
    openD_hanfun_iLevelControlClientReq_levelInt_t increaseLevelInt;
    openD_hanfun_iLevelControlClientReq_levelIntAddr_t increaseLevelIntAddr;
    openD_hanfun_iLevelControlClientReq_levelFloat_t increaseLevelFloat;
    openD_hanfun_iLevelControlClientReq_levelFloatAddr_t increaseLevelFloatAddr;
    openD_hanfun_iLevelControlClientReq_levelInt_t decreaseLevelInt;
    openD_hanfun_iLevelControlClientReq_levelIntAddr_t decreaseLevelIntAddr;
    openD_hanfun_iLevelControlClientReq_levelFloat_t decreaseLevelFloat;
    openD_hanfun_iLevelControlClientReq_levelFloatAddr_t decreaseLevelFloatAddr;
  } param;
} openD_hanfun_iLevelControlClientReq_t;

/**
 * openD Hanfun iLevelControl server request structure.
 */
typedef struct openD_hanfun_iLevelControlServerReq {
  /**
   * Hanfun iLevelControl server service.
   */
  openD_hanfun_iLevelControlServer_service_t service;

    /**
     * Hanfun iLevelControl parameters.
     */
  union {
    openD_hanfun_iLevelControlServerReq_levelInt_t setLevelInt;
    openD_hanfun_iLevelControlServerReq_levelFloat_t setLevelFloat;
    openD_hanfun_iLevelControlServerReq_levelInt_t increaseLevelInt;
    openD_hanfun_iLevelControlServerReq_levelFloat_t increaseLevelFloat;
    openD_hanfun_iLevelControlServerReq_levelInt_t decreaseLevelInt;
    openD_hanfun_iLevelControlServerReq_levelFloat_t decreaseLevelFloat;
  } param;
} openD_hanfun_iLevelControlServerReq_t;

/**
 * openD Hanfun iLevelControl server confirm structure.
 */
typedef struct openD_hanfun_iLevelControlServerCfm {
  /**
   * Hanfun iLevelControl server service.
   */
  openD_hanfun_iLevelControlServer_service_t service;

    /**
     * Hanfun iLevelControl parameters.
     */
  union {
    openD_hanfun_iLevelControlServerCfm_getLevel_t getLevel;
  } param;
} openD_hanfun_iLevelControlServerCfm_t;

/**
 * openD Hanfun iLevelControl server indication structure.
 */
typedef struct openD_hanfun_iLevelControlServerInd {
  /**
   * Hanfun iLevelControl serverservice.
   */
  openD_hanfun_iLevelControlServer_service_t service;

  /**
   * Hanfun iLevelControl parameters.
   */
  union {
    openD_hanfun_iLevelControlServerInd_levelChange_t levelChange;
  } param;
} openD_hanfun_iLevelControlServerInd_t;


/*! @} defgroup OPEND_HANFUN_ILEVELCONTROL */

/*! @} addtogroup OPEND_HANFUN_INTERFACE */

#endif /* __OPEND_HANFUN_ILEVELCONTROL_H__ */
#ifdef __cplusplus
}
#endif
