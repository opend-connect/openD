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
 * @file       msManager.c
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
 */
#include <stddef.h>

#include "stateManager.h"
#include "messageManager.h"

#include "msManager.h"

void msManager_init( msManager_ctxt_t * const ctxt,
                     const msManager_stateFct_t states[],
                     const msManager_state_t statesNum ) {

  stateManager_init( (stateManager_ctxt_t*) ctxt,
                     (stateManager_stateFct_t*) states,
                     (stateManager_state_t) statesNum );
  return;
}

void msManager_changeState( msManager_ctxt_t * const ctxt,
                            const msManager_state_t state ) {

  messageManager_t message;

  /* Set the leave primitive and execute the state. */
  message.primitive = MESSAGE_PRIMITIVE_LEAVE;
  message.param = NULL;
  stateManager_execState( (stateManager_ctxt_t*) ctxt, (void*) &message );

  /* Set current state. */
  stateManager_setState( (stateManager_ctxt_t*) ctxt, (stateManager_state_t) state );

  /* Set the initialization primitive and execute the state. */
  message.primitive = MESSAGE_PRIMITIVE_INIT;
  message.param = NULL;
  stateManager_execState( (stateManager_ctxt_t*) ctxt, (void*) &message );

  return;
}

bool msManager_handleService( msManager_ctxt_t * const ctxt,
                              msManager_message_t * const message ) {

  return stateManager_execState( (stateManager_ctxt_t*) ctxt, (void*) message );

}

#ifdef __cplusplus
}
#endif
