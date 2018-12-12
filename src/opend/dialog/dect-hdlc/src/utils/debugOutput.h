#ifdef __cplusplus
extern "C" {
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
 * @file       debugOutput.h
 * @copyright  STACKFORCE GmbH, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      Debug output helper.
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 */
#ifndef __DEBUG_OUTPUT_H__
#define __DEBUG_OUTPUT_H__

#include <stdio.h>


#pragma GCC diagnostic ignored "-Wformat"
#define DEBUG_OK( msg, ... ) \
  do { if ( DEBUG_OUTPUT_ENABLE ) printf( "# OK - %5s (%d) - " msg "\r\n", __FILE__, __LINE__, ##__VA_ARGS__ ); } while (0)

#pragma GCC diagnostic ignored "-Wformat"
#define DEBUG_ERROR( msg, ... ) \
  do { if ( DEBUG_OUTPUT_ENABLE ) printf( "# ERROR - %5s (%d) - " msg "\r\n", __FILE__, __LINE__, ##__VA_ARGS__ ); } while (0)

#pragma GCC diagnostic ignored "-Wformat"
#define DEBUG_INFO( msg, ... ) \
  do { if ( DEBUG_OUTPUT_ENABLE ) printf( "# INFO - %5s (%d) - " msg "\r\n", __FILE__, __LINE__, ##__VA_ARGS__ ); } while (0)

#pragma GCC diagnostic ignored "-Wformat"
#define DEBUG_WARNING( msg, ... ) \
  do { if ( DEBUG_OUTPUT_ENABLE ) printf( "# WARNING - %5s (%d) - " msg "\r\n", __FILE__, __LINE__, ##__VA_ARGS__ ); } while (0)

#pragma GCC diagnostic ignored "-Wformat"
#define DEBUG_RAW( msg, ... ) \
  do { if ( DEBUG_OUTPUT_ENABLE ) printf( msg , ##__VA_ARGS__ ); } while (0)

#endif /* __DEBUG_OUTPUT_H__ */

#ifdef __cplusplus
}
#endif
