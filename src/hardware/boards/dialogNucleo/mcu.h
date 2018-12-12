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
 * @file       mcu.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber, Heiko Berger
 * @brief      nucleol053 mcu settings.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   NUCLEOL053_MCU_API nucleol053 mcu api
 *             This module specifies mcu API of the nucleo.
 * \{
 */

#ifndef __MCU_H__
#define __MCU_H__

#if !defined  (HSE_VALUE)
  #define HSE_VALUE    ((uint32_t)8000000) /*!< Value of the External oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined  (MSI_VALUE)
  #define MSI_VALUE    ((uint32_t)2000000) /*!< Value of the Internal oscillator in Hz*/
#endif /* MSI_VALUE */

#if !defined  (HSI_VALUE)
  #define HSI_VALUE    ((uint32_t)16000000) /*!< Value of the Internal oscillator in Hz*/
#endif /* HSI_VALUE */

#define VECT_TAB_OFFSET  0x00 /*!< Vector Table base offset field.
                                   This value must be a multiple of 0x200. */


/*!
 * MCU initialization.
 */
void mcu_init( void );

/*!
 * Hard Fault exception.
 */
void HardFault_Handler(void);

/*!
 * Memory Manage exception.
 */
void MemManage_Handler(void);

/*!
 * Bus Fault exception.
 */
void BusFault_Handler(void);

/*!
 * Usage Fault exception.
 */
void UsageFault_Handler(void);

/*!
 * SVCall exception.
 */
void SVC_Handler(void);

/*!
 * Debug Monitor exception.
 */
void DebugMon_Handler(void);

/*!
 * PendSVC exception.
 */
void PendSV_Handler(void);

/*!
 * SysTick Handler.
 */
void SysTick_Handler(void);

/*!
 * System Clock Configuration.
 */
void SystemClock_Config(void);

/*! @} defgroup NUCLEOL053_MCU_API */

#endif // __MCU_H__

#ifdef __cplusplus
}
#endif
