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
 * @file       msManager.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      Message state manager module.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * \{
 */

#ifndef __MSMANAGER_H__
#define __MSMANAGER_H__

#include <stdint.h>

#include "stateManager.h"
#include "messageManager.h"

/**
 * Message state manager context.
 *
 * Internal structure DO NOT ACCESS directly, call API functions for accessing.
 */
typedef stateManager_ctxt_t msManager_ctxt_t;

/**
 * Type of states.
 */
typedef stateManager_state_t msManager_state_t;

/**
 * State function type.
 */
typedef stateManager_stateFct_t msManager_stateFct_t;

/**
 * Type of messages.
 */
typedef messageManager_t msManager_message_t;

/**
 * @brief   Message state manager initialization.
 *
 * @details Initializes the message state manager module.
 *
 * @param   ctxt Pointer of a message state manager module context (@ref msManager_ctxt_t).
 * @param   states Pointer of an array of state functions (@ref msManager_stateFct_t).
 * @param   statesNum Number of states (@ref msManager_state_t).
 */
void msManager_init( msManager_ctxt_t * const ctxt,
                     const msManager_stateFct_t states[],
                     const msManager_state_t statesNum );

/**
 * @brief   Changes the state of the state machine.
 *
 * @details Changes the state of the state machine of the context to the current one
 *          and calls the state function.
 *          The generic message @ref MESSAGE_PRIMITIVE_LEAVE is called in the old state
 *          function. In the new state function the message @ref MESSAGE_PRIMITIVE_INIT
 *          is also called.
 *
 * @param   ctxt Pointer of a message state manager module context (@ref msManager_ctxt_t).
 * @param   states State to change to (@ref msManager_state_t).
 */
void msManager_changeState( msManager_ctxt_t * const ctxt,
                            const msManager_state_t state );

/**
 * @brief   Handles messages in the current state.
 *
 * @details Handles messages in the current state of the state machine of the current context.
 *
 * @param   ctxt Pointer of a message state manager module context (@ref msManager_ctxt_t).
 * @param   message Pointer of a message (@ref msManager_message_t).
 */
bool msManager_handleService( msManager_ctxt_t * const ctxt,
                              msManager_message_t * const message );

#endif /* __MSMANAGER_H__ */
#ifdef __cplusplus
}
#endif
