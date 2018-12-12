/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       transport.cpp
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber, Heiko Berger
 * @brief
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * \{
 */
#include <stdlib.h>
#include <stdio.h>

#include <stdbool.h>
#include "mcu.h"
#include "opend_sw_timer.h"
#include "lptim.h"
#include "opend_ll_serial.h"
#include "ule.h"

/* Set the Maximum value of the counter */
#define Period               (uint32_t) 65535

/* Set the Timeout value */
#define Timeout              (uint32_t) (18500 - 1)

keepAliveClb sendKeepAlive;

byteReceivedClb handleReceivedByte;

bool initIwu(keepAliveClb keepAlive, byteReceivedClb byteReceived)
{
  if(keepAlive == NULL || byteReceived == NULL)
  {
    return false;
  }

  sendKeepAlive = keepAlive;
  handleReceivedByte = byteReceived;

  openD_ll_serial_init( 0, 115200, handleReceivedByte );

  return true;
}

/*!
 * @brief   Software timer callback notify.
 *
 * @details Send a TX frame with UART for each software timeout.
 */
static void _sw_timer_timeoutNotify()
{
  sendKeepAlive();
}

/*!
 * @brief   Hardware timer callback notify.
 *
 * @details Get the elapsed time.
 *
 * @param   elapsedTime Elapsed time.
 */
static void _hw_timer_timeNotify( uint16_t elapsedTime )
{
  static uint16_t currentTime;
	currentTime += elapsedTime;

	if(currentTime == 65000)
	{
		currentTime = 5000;
	}

	if(currentTime % 10000 == 0)
	{
		openD_sw_timer_start(5000, &_sw_timer_timeoutNotify);
	}

  openD_sw_timer_tick(elapsedTime);
}

void keepAliveTimerStart()
{
  lp_timer_init( &_hw_timer_timeNotify );
  lp_timer_start(Period, Timeout);
}

void successConInd()
{
}

void failureConInd()
{
}

void exitApp()
{
  return;
}
