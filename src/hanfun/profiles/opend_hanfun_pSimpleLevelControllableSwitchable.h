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
 * @file       opend_hanfun_pSimpleLevelControllableSwitchable.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN pSimpleLevelControllableSwitchable.
 *
 * @addtogroup OPEND_HANFUN_PROFILE
 * @{
 *
 * @defgroup   OPEND_HANFUN_PSIMPLELEVELCONTROLLABLESWITCHABLE openD HAN-FUN pSimpleLevelControllableSwitchable
 *             This module specifies the HAN-FUN SimpleLevelControllableSwitchable profile.
 * @{
 */

#ifndef __OPEND_HANFUN_PSIMPLELEVELCONTROLLABLESWITCHABLE_H__
#define __OPEND_HANFUN_PSIMPLELEVELCONTROLLABLESWITCHABLE_H__

#include "../interfaces/opend_hanfun_iLevelControl.h"
#include "../interfaces/opend_hanfun_iOnOff.h"

/**
 * openD Hanfun pSimpleLevelControllableSwitchable interfaces.
 */
typedef enum openD_hanfun_pSimpleLevelControllableSwitchable_interface {
  /**
   * Interface iOnOff.
   */
  OPEND_HANFUN_PSIMPLELEVELCONTROLLABLESWITCHABLE_IONOFF,
  /**
   * Interface iLevelControl.
   */
  OPEND_HANFUN_PSIMPLELEVELCONTROLLABLESWITCHABLE_ILEVELCONTROL,
} openD_hanfun_pSimpleLevelControllableSwitchable_interface_t;

/**
 * openD Hanfun pSimpleLevelControllableSwitchable profile request structure.
 */
typedef struct openD_hanfun_pSimpleLevelControllableSwitchableReq {
  /**
   * Interface.
   */
  openD_hanfun_pSimpleLevelControllableSwitchable_interface_t interface;

  /**
   * Interface structures.
   */
  union {
    openD_hanfun_iOnOffServerReq_t onOff;
    openD_hanfun_iLevelControlServerReq_t levelControl;
  };
} openD_hanfun_pSimpleLevelControllableSwitchableReq_t;

/**
 * openD Hanfun pSimpleLevelControllableSwitchable profile confirm structure.
 */
typedef struct openD_hanfun_pSimpleLevelControllableSwitchableCfm {
  /**
   * Interface.
   */
  openD_hanfun_pSimpleLevelControllableSwitchable_interface_t interface;

  /**
   * Interface structures.
   */
  union {
    openD_hanfun_iOnOffServerCfm_t onOff;
    openD_hanfun_iLevelControlServerCfm_t levelControl;
  };
} openD_hanfun_pSimpleLevelControllableSwitchableCfm_t;

/**
 * openD Hanfun pSimpleLevelControllableSwitchable profile indication structure.
 */
typedef struct openD_hanfun_pSimpleLevelControllableSwitchableInd {
  /**
   * Interface.
   */
  openD_hanfun_pSimpleLevelControllableSwitchable_interface_t interface;

  /**
   * Interface structures.
   */
  union {
    openD_hanfun_iOnOffServerInd_t onOff;
    openD_hanfun_iLevelControlServerInd_t levelControl;
  };
} openD_hanfun_pSimpleLevelControllableSwitchableInd_t;


/*! @} defgroup OPEND_HANFUN_PSIMPLELEVELCONTROLLABLESWITCHABLE */

/*! @} addtogroup OPEND_HANFUN_PROFILE */

#endif /* __OPEND_HANFUN_PSIMPLELEVELCONTROLLABLESWITCHABLE_H__ */
#ifdef __cplusplus
}
#endif
