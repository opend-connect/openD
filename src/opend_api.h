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
 * @file       opend_api.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD API.
 *
 * @defgroup   OPEND_API openD API
 *             This module specifies the unified API of openD connect.
 * \{
 */

#ifndef __OPEND_API_H__
#define __OPEND_API_H__

#include "opend_dataTypes.h"

/**
 * @brief   openD API initialization.
 *
 * @details DETAILED DESCRIPTION HERE.
 *
 * @retval  openD_status_t Status of the operation (@ref openD_status_t).
 */
openD_status_t openD_init( void );

/*! @} defgroup OPEND_API */

#endif /* __OPEND_API_H__ */
#ifdef __cplusplus
}
#endif
