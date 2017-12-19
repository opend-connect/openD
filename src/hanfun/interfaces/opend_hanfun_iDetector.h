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
 * @file       opend_hanfun_iDetector.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN iDetector.
 *
 * @addtogroup OPEND_HANFUN_INTERFACE
 * @{
 *
 * @defgroup   OPEND_HANFUN_IDETECTOR openD HAN-FUN iDetector
 *             This module specifies the HAN-FUN detector interface.
 * @{
 */

#ifndef __OPEND_HANFUN_IDETECTOR_H__
#define __OPEND_HANFUN_IDETECTOR_H__

#include <stdbool.h>

#include "../opend_hanfun_dataTypes.h"

/**
 * openD Hanfun iDetector server services.
 */
typedef enum openD_hanfun_iDetector_service {
  /**
   * Send an alert message to the remote device given by the address @c openD_hanfun_address_t.
   */
  OPEND_HANFUN_iDETECTOR_ALERT_ADDR,
  /**
   * Send an alert message to the broadcast address.
   */
  OPEND_HANFUN_iDETECTOR_ALERT,

} openD_hanfun_iDetector_service_t;

/**
 * openD Hanfun iDetector request parameter structure of the @c ALERT_ADDR service.
 */
typedef struct openD_hanfun_iDetectorReq_alertAddr {
  /**
   * Hanfun device address to send the message to.
   */
  openD_hanfun_address_t addr;
  /**
   * Alert state.
   */
  bool state;
} openD_hanfun_iDetectorReq_alertAddr_t;

/**
 * openD Hanfun iDetector request parameter structure of the @c ALERT service.
 */
typedef struct openD_hanfun_iDetectorReq_alert {
  /**
   * Alert state.
   */
  bool state;
} openD_hanfun_iDetectorReq_alert_t;

/**
 * openD Hanfun iDetector request structure.
 */
typedef struct openD_hanfun_iDetectorReq {
  /**
   * Hanfun iDetector server service.
   */
  openD_hanfun_iDetector_service_t service;

  /**
   * Hanfun iDetector parameters.
   */
  union {
    openD_hanfun_iDetectorReq_alertAddr_t alertAddr;
    openD_hanfun_iDetectorReq_alert_t alert;
  } param;
} openD_hanfun_iDetectorReq_t;


/*! @} defgroup OPEND_HANFUN_IDETECTOR */

/*! @} addtogroup OPEND_HANFUN_PROFILE */

#endif /* __OPEND_HANFUN_IDETECTOR_H__ */
#ifdef __cplusplus
}
#endif
