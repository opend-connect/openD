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
 * @file       opend_hanfun_iOnOff.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN API iOnOff.
 *
 * @addtogroup OPEND_HANFUN_INTERFACE
 * @{
 *
 * @defgroup   OPEND_HANFUN_API_IONOFF openD HAN-FUN API iOnOff
 *             This module specifies the HAN-FUN OnOff interface.
 * @{
 */

#ifndef __OPEND_HANFUN_API_IONOFF_H__
#define __OPEND_HANFUN_API_IONOFF_H__

#include <stdbool.h>

#include "../opend_hanfun_dataTypes.h"

/**
 * openD HanfunApi iOnOff services.
 */
typedef enum openD_hanfunApi_iOnOff_service {
  /**
   * Send a ON message to the device at the given address @c openD_hanfunApi_address_t.
   */
  OPEND_HANFUN_IONOFF_SERVER_ON_ADDR,
  /**
   * Send a OFF message to the device at the given address @c openD_hanfunApi_address_t.
   */
  OPEND_HANFUN_IONOFF_SERVER_OFF_ADDR,
  /**
   * Send a TOGGLE message to the device at the given address @c openD_hanfunApi_address_t.
   */
  OPEND_HANFUN_IONOFF_SERVER_TOGGLE_ADDR,
  /**
   * Set the state attribute to given value.
   */
  OPEND_HANFUN_IONOFF_SERVER_SET_STATE,
  /**
   * Get the current state of the interface.
   */
  OPEND_HANFUN_IONOFF_SERVER_GET_STATE,

  /**
   * Send a ON message to the device at the given address @c openD_hanfunApi_address_t.
   */
  OPEND_HANFUN_IONOFF_CLIENT_ON_ADDR,
  /**
   * Send a ON message to the broadcast address.
   */
  OPEND_HANFUN_IONOFF_CLIENT_ON,
  /**
   * Send a OFF message to the device at the given address @c openD_hanfunApi_address_t.
   */
  OPEND_HANFUN_IONOFF_CLIENT_OFF_ADDR,
  /**
   * Send a OFF message to the broadcast address.
   */
  OPEND_HANFUN_IONOFF_CLIENT_OFF,
  /**
   * Send a TOGGLE message to the device at the given address @c openD_hanfunApi_address_t.
   */
  OPEND_HANFUN_IONOFF_CLIENT_TOGGLE_ADDR,
  /**
   * Send a TOGGLE message to the broadcast address.
   */
  OPEND_HANFUN_IONOFF_CLIENT_TOGGLE,

} openD_hanfunApi_iOnOff_service_t;

/**
 * openD HanfunApi iOnOff structure.
 */
typedef struct openD_hanfunApi_iOnOff {
  /**
   * HanfunApi iOnOff service.
   */
  openD_hanfunApi_iOnOff_service_t service;

  /**
   * HanfunApi iOnOff parameters.
   */
  union {
    openD_hanfunApi_address_t addr;
    bool state;
  } param;
} openD_hanfunApi_iOnOff_t;


/*! @} defgroup OPEND_HANFUN_API_IONOFF */

/*! @} addtogroup OPEND_HANFUN_INTERFACE */

#endif /* __OPEND_HANFUN_API_IONOFF_H__ */
#ifdef __cplusplus
}
#endif
