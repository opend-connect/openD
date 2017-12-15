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
 * @file       opend_hanfun_pSimplePowerMeter.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN pSimplePowerMeter.
 *
 * @addtogroup OPEND_HANFUN_PROFILE
 * @{
 *
 * @defgroup   OPEND_HANFUN_PSIMPLEPOWERMETER openD HAN-FUN pSimplePowerMeter
 *             This module specifies the HAN-FUN simple power meter profile.
 * @{
 */

#ifndef __OPEND_HANFUN_PSIMPLEPOWERMETER_H__
#define __OPEND_HANFUN_PSIMPLEPOWERMETER_H__

#include "../interfaces/opend_hanfun_iSimplePowerMeter.h"

/**
 * openD Hanfun pSimplePowerMeter profile request structure.
 */
typedef openD_hanfun_iSimplePowerMeterServerReq_t openD_hanfun_pSimplePowerMeterReq_t;

/**
 * openD Hanfun pSimplePowerMeter profile confirm structure.
 */
typedef openD_hanfun_iSimplePowerMeterServerCfm_t openD_hanfun_pSimplePowerMeterCfm_t;


/*! @} defgroup OPEND_HANFUN_PSIMPLEPOWERMETER */

/*! @} addtogroup OPEND_HANFUN_PROFILE */

#endif /* __OPEND_HANFUN_PSIMPLEPOWERMETER_H__ */
#ifdef __cplusplus
}
#endif
