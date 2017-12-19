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
 * @file       opend_hanfun_pDimmableLight.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN pDimmableLight.
 *
 * @addtogroup OPEND_HANFUN_PROFILE
 * @{
 *
 * @defgroup   OPEND_HANFUN_PDIMMABLELIGHT openD HAN-FUN pDimmableLight
 *             This module specifies the HAN-FUN dimmable light profile.
 * @{
 */

#ifndef __OPEND_HANFUN_PDIMMABLELIGHT_H__
#define __OPEND_HANFUN_PDIMMABLELIGHT_H__

#include "../interfaces/opend_hanfun_iLevelControl.h"
#include "../interfaces/opend_hanfun_iOnOff.h"

/**
 * openD Hanfun pDimmableLight interfaces.
 */
typedef enum openD_hanfun_pDimmableLight_interface {
  /**
   * Interface iOnOff.
   */
  OPEND_HANFUN_PDIMMABLELIGHT_IONOFF,
  /**
   * Interface iLevelControl.
   */
  OPEND_HANFUN_PDIMMABLELIGHT_ILEVELCONTROL,
} openD_hanfun_pDimmableLight_interface_t;

/**
 * openD Hanfun pDimmableLight profile request structure.
 */
typedef struct openD_hanfun_pDimmableLightReq {
  /**
   * Interface.
   */
  openD_hanfun_pDimmableLight_interface_t interface;

  /**
   * Interface structures.
   */
  union {
    openD_hanfun_iOnOffServerReq_t onOff;
    openD_hanfun_iLevelControlServerReq_t levelControl;
  };
} openD_hanfun_pDimmableLightReq_t;

/**
 * openD Hanfun pDimmableLight profile confirm structure.
 */
typedef struct openD_hanfun_pDimmableLightCfm {
  /**
   * Interface.
   */
  openD_hanfun_pDimmableLight_interface_t interface;

  /**
   * Interface structures.
   */
  union {
    openD_hanfun_iOnOffServerCfm_t onOff;
    openD_hanfun_iLevelControlServerCfm_t levelControl;
  };
} openD_hanfun_pDimmableLightCfm_t;

/**
 * openD Hanfun pDimmableLight profile indication structure.
 */
typedef struct openD_hanfun_pDimmableLightInd {
  /**
   * Interface.
   */
  openD_hanfun_pDimmableLight_interface_t interface;

  /**
   * Interface structures.
   */
  union {
    openD_hanfun_iOnOffServerInd_t onOff;
    openD_hanfun_iLevelControlServerInd_t levelControl;
  };
} openD_hanfun_pDimmableLightInd_t;


/*! @} defgroup OPEND_HANFUN_PDIMMABLELIGHT */

/*! @} addtogroup OPEND_HANFUN_PROFILE */

#endif /* __OPEND_HANFUN_PDIMMABLELIGHT_H__ */
#ifdef __cplusplus
}
#endif
