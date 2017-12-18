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
 * @file       opend_hanfun_pDimmableColourBulb.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN pDimmableColourBulb.
 *
 * @addtogroup OPEND_HANFUN_PROFILE
 * @{
 *
 * @defgroup   OPEND_HANFUN_PDIMMABLECOLOURBULB openD HAN-FUN pDimmableColourBulb
 *             This module specifies the HAN-FUN dimmable colour bulb profile.
 * @{
 */

#ifndef __OPEND_HANFUN_PDIMMABLECOLOURBULB_H__
#define __OPEND_HANFUN_PDIMMABLECOLOURBULB_H__

#include "../interfaces/opend_hanfun_iOnOff.h"
#include "../interfaces/opend_hanfun_iColourControl.h"
#include "../interfaces/opend_hanfun_iLevelControl.h"

/**
 * openD Hanfun pDimmableColourBulb interfaces.
 */
typedef enum openD_hanfun_pDimmableColourBulb_interface {
  /**
   * Interface iOnOff.
   */
  OPEND_HANFUN_PDIMMABLECOLOURBULB_IONOFF,
  /**
   * Interface iColourControl.
   */
  OPEND_HANFUN_PDIMMABLECOLOURBULB_ICOLOURCONTROL,
  /**
   * Interface iLevelControl.
   */
  OPEND_HANFUN_PDIMMABLECOLOURBULB_ILEVELCONTROL,
} openD_hanfun_pDimmableColourBulb_interface_t;

/**
 * openD Hanfun pDimmableColourBulb profile request structure.
 */
typedef struct openD_hanfun_pDimmableColourBulbReq {
  /**
   * Interface.
   */
  openD_hanfun_pDimmableColourBulb_interface_t interface;

  /**
   * Interface structures.
   */
  union {
    openD_hanfun_iOnOffServerReq_t onOff;
    openD_hanfun_iColourControlServerReq_t colourControl;
    openD_hanfun_iLevelControlServerReq_t levelControl;
  };
} openD_hanfun_pDimmableColourBulbReq_t;

/**
 * openD Hanfun pDimmableColourBulb profile confirm structure.
 */
typedef struct openD_hanfun_pDimmableColourBulbCfm {
  /**
   * Interface.
   */
  openD_hanfun_pDimmableColourBulb_interface_t interface;

  /**
   * Interface structures.
   */
  union {
    openD_hanfun_iOnOffServerCfm_t onOff;
    openD_hanfun_iColourControlServerCfm_t colourControl;
    openD_hanfun_iLevelControlServerCfm_t ;
  };
} openD_hanfun_pDimmableColourBulbCfm_t;

/**
 * openD Hanfun pDimmableColourBulb profile indication structure.
 */
typedef struct openD_hanfun_pDimmableColourBulbInd {
  /**
   * Interface.
   */
  openD_hanfun_pDimmableColourBulb_interface_t interface;

  /**
   * Interface structures.
   */
  union {
    openD_hanfun_iOnOffServerInd_t onOff;
    openD_hanfun_iColourControlServerInd_t colourControl;
    openD_hanfun_iLevelControlServerInd_t levelControl;
  };
} openD_hanfun_pDimmableColourBulbInd_t;


/*! @} defgroup OPEND_HANFUN_PDIMMABLECOLOURBULB */

/*! @} addtogroup OPEND_HANFUN_PROFILE */

#endif /* __OPEND_HANFUN_PDIMMABLECOLOURBULB_H__ */
#ifdef __cplusplus
}
#endif
