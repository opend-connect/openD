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
 * @file       opend_hanfun_dataTypes.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Patrick Weber
 * @brief      openD HAN-FUN data types.
 *
 * @defgroup   OPEND_HANFUN_DATATYPES openD Hanfun data types
 *             This header file declares the openD HAN-FUN specific data types.
 * @{
 */

#ifndef __OPEND_HANFUN_DATATYPES_H__
#define __OPEND_HANFUN_DATATYPES_H__

#include <stdint.h>

/*
 * openD Hanfun broadcast - device address.
 */
#define OPEND_HANFUN_ADDRESS_BROADCAST_DEVICE = 0x7FFF;
/*
 * openD Hanfun broadcast - unit address.
 */
#define OPEND_HANFUN_ADDRESS_BROADCAST_UNIT = 0xFF;


typedef enum openD_hanfun_address_modType
{
  /*
   * Destination address is for single device.
   */
  OPEND_HANFUN_ADDRESS_MODTYPE_DEVICE = 0,
  /*
   * Destination address is for a group of devices.
   */
  OPEND_HANFUN_ADDRESS_MODTYPE_GROUP  = 1,
} openD_hanfun_address_modType_t;

/**
 * openD Hanfun address structure.
 */
typedef struct openD_hanfun_address {
  /**
    * Address modifier.
    */
  uint16_t mod: 1;
  /**
    * Device Address.
    */
  uint16_t device: 15;
  /**
    * Unit.
    */
  uint8_t unit;
} openD_hanfun_address_t;


/*! @} defgroup OPEND_HANFUN_DATATYPES */

#endif /* __OPEND_HANFUN_DATATYPES_H__ */
#ifdef __cplusplus
}
#endif
