/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       at_commands.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger
 * @brief      openD at commands api.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   SERIAL protocol
 *             This file specifies the serial protocol.
 * @{
 */


/*!
 * States for the legacy RX message handler .
 */
typedef enum{
  STARTUP,
  OK,
  IREG,
  CSTS,
  DREG,
  ISUB,
  ALRT,
  CEND,
} rx_states_t;

/*!
 * States for the legacy TX message handler .
 */
typedef enum{
  INIT,
  REGISTRATION_SEARCH_BASE,
  REGISTRATION_SEARCH_BASE_PIN,
  CALL_SETUP,
  TERMINATE_CALL,
  DEREGISTRATION,
  GET_REGISTRATION_STATE,
  ANSWER_CALL,
  AUDIO_SMOD,
  AUDIO_FDHF,
  AUDIO_SKEY,
  AUDIO_INIT,
} tx_states;

/**
 * @brief   Notify state machine.
 *
 * @details AT commands notify iwu state machine callback.
 *
 * @param   state Received RX state.
 * @param   data Pointer that hold the received data.
 */
typedef void (*notify_state_machine)(rx_states_t state, void *data);

/**
 * @brief   Initialize at commands.
 *
 * @details Initialization of the serial protocol at commands.
 *
 * @param   state_machine Callback function pointer to notify the state machine.
 */
void at_commands_init(notify_state_machine state_machine);

/**
 * @brief   Parse at command.
 *
 * @details Handle the parse at commands.
 *
 * @param   atCommand Pointer that holds the data.
 * @param   size Size of the data.
 */
void at_commands_parse(uint8_t atCommand[], uint16_t size);

/**
 * @brief   Create at command.
 *
 * @details This function creates DSPG specific at commands.
 *
 * @param   at_Command AT command.
 * @param   data Pointer to AT command arguments.
 * @param   buffer Pointer to write the command into.
 * @param   buffer Buffer length.
 */
uint8_t at_commands_create(tx_states at_Command, void* data, uint8_t *buffer, uint8_t bufferLen);
