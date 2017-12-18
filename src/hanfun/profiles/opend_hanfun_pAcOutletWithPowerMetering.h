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
 * @file       opend_hanfun_pAcOutletWithPowerMetering.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN pAcOutletWithPowerMetering.
 *
 * @addtogroup OPEND_HANFUN_PROFILE
 * @{
 *
 * @defgroup   OPEND_HANFUN_PACOUTLETWITHPOWERMETERING openD HAN-FUN pAcOutletWithPowerMetering
 *             This module specifies the HAN-FUN AC outlet with power metering profile.
 * @{
 */

#ifndef __OPEND_HANFUN_PACOUTLETWITHPOWERMETERING_H__
#define __OPEND_HANFUN_PACOUTLETWITHPOWERMETERING_H__

#include "../interfaces/opend_hanfun_iOnOff.h"
#include "../interfaces/opend_hanfun_iSimplePowerMeter.h"

/**
 * openD Hanfun pAcOutletWithPowerMetering interfaces.
 */
typedef enum openD_hanfun_pAcOutletWithPowerMetering_interface {
  /**
   * Interface iOnOff.
   */
  OPEND_HANFUN_PACOUTLETWITHPOWERMETERING_IONOFF,
  /**
   * Interface iLevelControl.
   */
  OPEND_HANFUN_PACOUTLETWITHPOWERMETERING_ILEVELCONTROL,
} openD_hanfun_pAcOutletWithPowerMetering_interface_t;

/**
 * openD Hanfun pAcOutletWithPowerMetering profile request structure.
 */
typedef struct openD_hanfun_pAcOutletWithPowerMeteringReq {
  /**
   * Interface.
   */
  openD_hanfun_pAcOutletWithPowerMetering_interface_t interface;

  /**
   * Interface structures.
   */
  union {
    openD_hanfun_iOnOffServerReq_t onOff;
    openD_hanfun_iSimplePowerMeterServerReq_t simplePowerMeter;
  };
} openD_hanfun_pAcOutletWithPowerMeteringReq_t;

/**
 * openD Hanfun pAcOutletWithPowerMetering profile confirm structure.
 */
typedef struct openD_hanfun_pAcOutletWithPowerMeteringCfm {
  /**
   * Interface.
   */
  openD_hanfun_pAcOutletWithPowerMetering_interface_t interface;

  /**
   * Interface structures.
   */
  union {
    openD_hanfun_iOnOffServerCfm_t onOff;
    openD_hanfun_iSimplePowerMeterServerCfm_t simplePowerMeter;
  };
} openD_hanfun_pAcOutletWithPowerMeteringCfm_t;

/**
 * openD Hanfun pAcOutletWithPowerMetering profile indication structure.
 */
typedef struct openD_hanfun_pAcOutletWithPowerMeteringInd {
  /**
   * Interface.
   */
  openD_hanfun_pAcOutletWithPowerMetering_interface_t interface;

  /**
   * Interface structures.
   */
  union {
    openD_hanfun_iOnOffServerInd_t onOff;
  };
} openD_hanfun_pAcOutletWithPowerMeteringInd_t;


/*! @} defgroup OPEND_HANFUN_PACOUTLETWITHPOWERMETERING */

/*! @} addtogroup OPEND_HANFUN_PROFILE */

#endif /* __OPEND_HANFUN_PACOUTLETWITHPOWERMETERING_H__ */
#ifdef __cplusplus
}
#endif
