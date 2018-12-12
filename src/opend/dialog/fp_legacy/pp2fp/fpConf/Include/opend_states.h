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
 * @file       opend_states.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD states.
 *
 * @defgroup   OPEND_STATES openD states
 *             This file specifies the internal states.
 * \{
 */

#ifndef __OPEND_STATES_H__
#define __OPEND_STATES_H__

#include "msManager.h"

#include <stdbool.h>

typedef enum {
  OPEND_STATE_INIT,
  OPEND_STATE_STANDBY,
  OPEND_STATE_CALL
} opendStates_t;

/* openD function prototypes of application states. */
bool opend_state_init( void *param );
bool opend_state_standby( void *param );
bool opend_state_call( void *param );

msManager_ctxt_t opendStateCtxt;

/*! @} defgroup OPEND_STATES */

#endif /* __OPEND_STATES_H__ */
#ifdef __cplusplus
}
#endif
