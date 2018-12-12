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
 * @file       stateManager.c
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
 */

#include "stateManager.h"

void stateManager_init( stateManager_ctxt_t * const ctxt,
                        const stateManager_stateFct_t states[],
                        const stateManager_state_t statesNum ) {

  if( !ctxt ){
    return;
  }

  ctxt->states = states;
  ctxt->statesNum = statesNum;

  return;
}

void stateManager_setState( stateManager_ctxt_t * const ctxt,
                            const stateManager_state_t state ) {

  if( !ctxt ){
   return;
  }

  if( ctxt->state < ctxt->statesNum ) {
    ctxt->state = state;
  }

  return;
}

stateManager_state_t stateManager_getState( stateManager_ctxt_t * const ctxt ) {
  return ctxt->state;
}

bool stateManager_execState( stateManager_ctxt_t * const ctxt, void *param ) {

  bool ret = false;

  if( !ctxt ){
    return false;
  }

  stateManager_stateFct_t stateFct;

  if( ctxt->state < ctxt->statesNum ) {
    stateFct = ctxt->states[ctxt->state];
    if( stateFct ) {
      ret = stateFct( param );
    }
  }

  return ret;
}


#ifdef __cplusplus
}
#endif
