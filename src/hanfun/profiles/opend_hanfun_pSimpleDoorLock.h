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
 * @file       opend_hanfun_pSimpleDoorLock.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN pSimpleDoorLock.
 *
 * @addtogroup OPEND_HANFUN_PROFILE
 * @{
 *
 * @defgroup   OPEND_HANFUN_PSIMPLEDOORLOCK openD HAN-FUN pSimpleDoorLock
 *             This module specifies the HAN-FUN simple door lock profile.
 * @{
 */

#ifndef __OPEND_HANFUN_PSIMPLEDOORLOCK_H__
#define __OPEND_HANFUN_PSIMPLEDOORLOCK_H__

#include "../interfaces/opend_hanfun_iOnOff.h"

/**
 * openD Hanfun pSimpleDoorLock profile request structure.
 */
typedef openD_hanfun_iOnOffServerReq_t openD_hanfun_pSimpleDoorLockReq_t;

/**
 * openD Hanfun pSimpleDoorLock profile confirm structure.
 */
typedef openD_hanfun_iOnOffServerCfm_t openD_hanfun_pSimpleDoorLockCfm_t;

/**
 * openD Hanfun pSimpleDoorLock profile indication structure.
 */
typedef openD_hanfun_iOnOffServerInd_t openD_hanfun_pSimpleDoorLockInd_t;


/*! @} defgroup OPEND_HANFUN_PSIMPLEDOORLOCK */

/*! @} addtogroup OPEND_HANFUN_PROFILE */

#endif /* __OPEND_HANFUN_PSIMPLEDOORLOCK_H__ */
#ifdef __cplusplus
}
#endif
