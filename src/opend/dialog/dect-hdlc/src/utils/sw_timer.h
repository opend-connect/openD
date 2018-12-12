#ifdef __cplusplus
extern "C" {
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
 * @file       sw_timer.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @author     Heiko Berger
 * @brief      Software timer API.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   SW_TIMER_API Software timer API
 *             This module specifies the software timer API.
 * \{
 */

#ifndef __SW_TIMER_H__
#define __SW_TIMER_H__

#include <stdint.h>

/**
 * @brief   Software timer timeout callback primitive.
 */
typedef void ( *sw_timeoutCallback )( void );

/*!
 * @brief   Starts a software timer.
 *
 * @param   timeout Timeout in ms.
 * @param   timeoutCallback Callback function called at timeout.
 */
void sw_timer_start( uint16_t timeout, sw_timeoutCallback timeoutCallback );

/*!
 * @brief   Ticks the software timer and checks for timeouts.
 *
 * @details In case a timeout occurs this function calls the registered callback
 *          function of the timer.
 *
 * @param   elapsedTime Elapsed time in ms.
 */
void sw_timer_tick( uint16_t elapsedTime );

/*! @} defgroup LOW_LEVEL_TIMER_API */

#endif  // __SW_TIMER_H__

#ifdef __cplusplus
}
#endif
