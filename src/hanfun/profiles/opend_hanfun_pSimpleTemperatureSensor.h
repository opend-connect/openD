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
 * @file       opend_hanfun_pSimpleTemperatureSensor.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN pSimpleTemperatureSensor.
 *
 * @addtogroup OPEND_HANFUN_PROFILE
 * @{
 *
 * @defgroup   OPEND_HANFUN_PSIMPLETEMPERATURESENSOR openD HAN-FUN pSimpleTemperatureSensor
 *             This module specifies the HAN-FUN simple temperature sensor profile.
 * @{
 */

#ifndef __OPEND_HANFUN_PSIMPLETEMPERATURESENSOR_H__
#define __OPEND_HANFUN_PSIMPLETEMPERATURESENSOR_H__

#include "../interfaces/opend_hanfun_iSimpleTemperature.h"

/**
 * openD Hanfun pSimpleTemperatureSensor profile request structure.
 */
typedef openD_hanfun_iSimpleTemperatureServerReq_t openD_hanfun_pSimpleTemperatureSensorReq_t;

/**
 * openD Hanfun pSimpleTemperatureSensor profile confirm structure.
 */
typedef openD_hanfun_iSimpleTemperatureServerCfm_t openD_hanfun_pSimpleTemperatureSensorCfm_t;


/*! @} defgroup OPEND_HANFUN_PSIMPLETEMPERATURESENSOR */

/*! @} addtogroup OPEND_HANFUN_PROFILE */

#endif /* __OPEND_HANFUN_PSIMPLETEMPERATURESENSOR_H__ */
#ifdef __cplusplus
}
#endif
