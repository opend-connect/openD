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
 * @file       lptim.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber, Heiko Berger
 * @brief      low power timer API.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   NUCLEOL053_LOW_POWER_TIMER_API nucleol053 low power timer API
 *             This module specifies the low power timer API.
 * \{
 */

#ifndef __LPTIM_H__
#define __LPTIM_H__

#include <stdint.h>

/**
 * @brief   Timer callback primitive.
 *
 * @param   elapsedTime Elapsed time of low power timer.
 */
typedef void ( *lp_timer_callback )( uint16_t elapsedTime  );

/**
 * @brief   Low power timer API initialization.
 *
 * @details Initialize the low power timer.
 *
 * @param   ll_timer_callback Callback to notify the elapsed time.
 *
 * @retval  Status of the operation.
 */
int8_t lp_timer_init( lp_timer_callback ll_timer_callback );

/**
 * @brief   low power timer API start.
 *
 * @details Start the low power timer.
 *
 * @param   period  Period of the low power timer.
 * @param   timeout Timeout of the low power timer.
 *
 * @retval  Status of the operation.
 */
int8_t lp_timer_start( uint32_t period, uint32_t timeout );

/*! @} defgroup NUCLEOL053_LOW_POWER_TIMER_API */

#endif // __LPTIM_H__

#ifdef __cplusplus
}
#endif
