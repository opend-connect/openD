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
 * @file       opend_hanfun_pSimpleLevelControllable.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN pSimpleLevelControllable.
 *
 * @addtogroup OPEND_HANFUN_PROFILE
 * @{
 *
 * @defgroup   OPEND_HANFUN_PSIMPLELEVELCONTROLLABLE openD HAN-FUN pSimpleLevelControllable
 *             This module specifies the HAN-FUN simple level controllable profile.
 * @{
 */

#ifndef __OPEND_HANFUN_PSIMPLELEVELCONTROLLABLE_H__
#define __OPEND_HANFUN_PSIMPLELEVELCONTROLLABLE_H__

#include "../interfaces/opend_hanfun_iLevelControl.h"

/**
 * openD Hanfun simpleLevelControllable profile request structure.
 */
typedef openD_hanfun_iLevelControlServerReq_t openD_hanfun_pSimpleLevelControllableReq_t;

/**
 * openD Hanfun simpleLevelControllable profile confirm structure.
 */
typedef openD_hanfun_iLevelControlServerCfm_t openD_hanfun_pSimpleLevelControllableCfm_t;

/**
 * openD Hanfun simpleLevelControllable profile indication structure.
 */
typedef openD_hanfun_iLevelControlServerInd_t openD_hanfun_pSimpleLevelControllableInd_t;


/*! @} defgroup OPEND_HANFUN_PSIMPLELEVELCONTROLLABLE */

/*! @} addtogroup OPEND_HANFUN_PROFILE */

#endif /* __OPEND_HANFUN_PSIMPLELEVELCONTROLLABLE_H__ */
#ifdef __cplusplus
}
#endif
