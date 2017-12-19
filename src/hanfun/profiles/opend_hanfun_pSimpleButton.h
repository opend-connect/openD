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
 * @file       opend_hanfun_pSimpleButton.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN pSimpleButton.
 *
 * @addtogroup OPEND_HANFUN_PROFILE
 * @{
 *
 * @defgroup   OPEND_HANFUN_PSIMPLEBUTTON openD HAN-FUN pSimpleButton
 *             This module specifies the HAN-FUN simple button profile.
 * @{
 */

#ifndef __OPEND_HANFUN_PSIMPLEBUTTON_H__
#define __OPEND_HANFUN_PSIMPLEBUTTON_H__

#include "../interfaces/opend_hanfun_iSimpleButton.h"

/**
 * openD Hanfun pSimpleButton profile request structure.
 */
typedef openD_hanfun_iSimpleButtonServerReq_t openD_hanfun_pSimpleButtonReq_t;

/**
 * openD Hanfun pSimpleButton profile confirm structure.
 */
typedef openD_hanfun_iSimpleButtonServerCfm_t openD_hanfun_pSimpleButtonCfm_t;


/*! @} defgroup OPEND_HANFUN_PSIMPLEBUTTON */

/*! @} addtogroup OPEND_HANFUN_PROFILE */

#endif /* __OPEND_HANFUN_PSIMPLEBUTTON_H__ */
#ifdef __cplusplus
}
#endif
