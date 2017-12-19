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
 * @file       opend_hanfun_pSimpleAirPressureSensor.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN pSimpleAirPressureSensor.
 *
 * @addtogroup OPEND_HANFUN_PROFILE
 * @{
 *
 * @defgroup   OPEND_HANFUN_PSIMPLEAIRPRESSURESENSOR openD HAN-FUN pSimpleAirPressureSensor
 *             This module specifies the HAN-FUN simple air pressure sensor profile.
 * @{
 */

#ifndef __OPEND_HANFUN_PSIMPLEAIRPRESSURESENSOR_H__
#define __OPEND_HANFUN_PSIMPLEAIRPRESSURESENSOR_H__

#include "../interfaces/opend_hanfun_iSimpleAirPressure.h"

/**
 * openD Hanfun pSimpleAirPressureSensor profile request structure.
 */
typedef openD_hanfun_iSimpleAirPressureServerReq_t openD_hanfun_pSimpleAirPressureSensorReq_t;

/**
 * openD Hanfun pSimpleAirPressureSensor profile confirm structure.
 */
typedef openD_hanfun_iSimpleAirPressureServerCfm_t openD_hanfun_pSimpleAirPressureSensorCfm_t;


/*! @} defgroup OPEND_HANFUN_PSIMPLEAIRPRESSURESENSOR */

/*! @} addtogroup OPEND_HANFUN_PROFILE */

#endif /* __OPEND_HANFUN_PSIMPLEAIRPRESSURESENSOR_H__ */
#ifdef __cplusplus
}
#endif
