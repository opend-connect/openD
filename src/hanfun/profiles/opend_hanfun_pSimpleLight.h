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
 * @file       opend_hanfun_pSimpleLight.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN pSimpleLight.
 *
 * @addtogroup OPEND_HANFUN_PROFILE
 * @{
 *
 * @defgroup   OPEND_HANFUN_PSIMPLELIGHT openD HAN-FUN pSimpleLight
 *             This module specifies the HAN-FUN simple light profile.
 * @{
 */

#ifndef __OPEND_HANFUN_PSIMPLELIGHT_H__
#define __OPEND_HANFUN_PSIMPLELIGHT_H__

#include "../interfaces/opend_hanfun_iOnOff.h"

/**
 * openD Hanfun pSimpleLight profile request structure.
 */
typedef openD_hanfun_iOnOffServerReq_t openD_hanfun_pSimpleLightReq_t;

/**
 * openD Hanfun pSimpleLight profile confirm structure.
 */
typedef openD_hanfun_iOnOffServerCfm_t openD_hanfun_pSimpleLightCfm_t;

/**
 * openD Hanfun pSimpleLight profile indication structure.
 */
typedef openD_hanfun_iOnOffServerInd_t openD_hanfun_pSimpleLightInd_t;


/*! @} defgroup OPEND_HANFUN_PSIMPLELIGHT */

/*! @} addtogroup OPEND_HANFUN_PROFILE */

#endif /* __OPEND_HANFUN_PSIMPLELIGHT_H__ */
#ifdef __cplusplus
}
#endif
