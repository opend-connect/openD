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
 * @file       stateManager.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      State manager module.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * \{
 */

#ifndef __STATEMANAGER_H__
#define __STATEMANAGER_H__

#include <stdint.h>
#include <stdbool.h>

/* Function prototype of state functions. */
typedef bool (*stateManager_stateFct_t)( void *param );

/* State type. */
typedef uint8_t stateManager_state_t;

/**
 * State manager context.
 *
 * Internal structure DO NOT ACCESS directly, call API functions for accessing.
 */
typedef struct {
  const stateManager_stateFct_t *states;
  stateManager_state_t statesNum;
  stateManager_state_t state;
} stateManager_ctxt_t;


/**
 * @brief   State manager initialization.
 *
 * @details Initializes the state manager module.
 *
 * @param   ctxt Pointer of a state manager module context (@ref stateManager_ctxt_t).
 * @param   states Pointer of an array of state functions (@ref stateManager_stateFct_t).
 * @param   statesNum Number of states (@ref stateManager_state_t).
 */
void stateManager_init( stateManager_ctxt_t * const ctxt,
                        const stateManager_stateFct_t states[],
                        const stateManager_state_t statesNum );

/**
 * @brief   Sets a state.
 *
 * @details Sets the state of the state machine of the context to the current one.
 *
 * @param   ctxt Pointer of a state manager module context (@ref stateManager_ctxt_t).
 * @param   states State to change to (@ref stateManager_state_t).
 */
void stateManager_setState( stateManager_ctxt_t * const ctxt,
                            const stateManager_state_t state);

/**
 * @brief   Gets a current state.
 *
 * @details Gets the current state of the state machine of the context.
 *
 * @param   ctxt Pointer of a state manager module context (@ref stateManager_ctxt_t).
 */
stateManager_state_t stateManager_getState( stateManager_ctxt_t * const ctxt );

/**
 * @brief   Calls the current state function.
 *
 * @details Calls the current state of the state machine of the context.
 *
 * @param   ctxt Pointer of a state manager module context (@ref msManager_ctxt_t).
 * @param   param Pointer of a parameter.
 */
bool stateManager_execState( stateManager_ctxt_t * const ctxt, void *param );


#endif /* __STATEMANAGER_H__ */
#ifdef __cplusplus
}
#endif
