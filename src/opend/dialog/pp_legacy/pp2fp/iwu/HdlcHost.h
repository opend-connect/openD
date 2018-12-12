/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       HdlcHost.h
 * @copyright  STACKFORCE GmbH, Germany, www.stackforce.de
 * @author     Mario Behringer <mario.behringer@stackforce.de>
 * @brief      Abstraction of the dialog specific CMVDECT HDLC protocol.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 */

#ifndef __HDLC_HOST_H__
#define __HDLC_HOST_H__

int hdlc_hostInit( void );
void hdlc_hostSend(unsigned char iTaskId, unsigned char *bInputDataPtr,
                   unsigned short iLength);

#endif // __HDLC_HOST_H__
