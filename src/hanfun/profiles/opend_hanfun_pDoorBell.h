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
 * @file       opend_hanfun_pDoorBell.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN pDoorBell.
 *
 * @addtogroup OPEND_HANFUN_PROFILE
 * @{
 *
 * @defgroup   OPEND_HANFUN_PDOORBELL openD HAN-FUN pDoorBell
 *             This module specifies the HAN-FUN DoorBell profile.
 * @{
 */

#ifndef __OPEND_HANFUN_PDOORBELL_H__
#define __OPEND_HANFUN_PDOORBELL_H__

#include "../interfaces/opend_hanfun_iAlert.h"

/**
 * openD Hanfun pDoorBell profile request structure.
 */
typedef openD_hanfun_iAlertServerReq_t openD_hanfun_pAlertableReq_t;

/**
 * openD Hanfun pDoorBell profile confirm structure.
 */
typedef openD_hanfun_iAlertServerCfm_t openD_hanfun_pAlertableCfm_t;


/*! @} defgroup OPEND_HANFUN_PDOORBELL */

/*! @} addtogroup OPEND_HANFUN_PROFILE */

#endif /* __OPEND_HANFUN_PDOORBELL_H__ */
#ifdef __cplusplus
}
#endif
