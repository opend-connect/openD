/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       transport.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger
 * @brief      openD interworking unit api.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 * @defgroup   TRANSPORT iwu
 *             This file specifies the interworking unit api.
 * @{
 */

/*!
 * Address of the success byte for +IREG and +ISUB confirmation.
 */
#define REGISTRATION_CFM_SUCCESSBYTE_ADDRESS 20

/*!
 * IWU registration finished confirmation callback.
 */
typedef void (*iwu_registration_cllb) (void *param);

/*!
 * IWU call setup succesfull confirmation callback.
 */
typedef void (*iwu_call_setup_cllb) (void);

/*!
 * IWU call terminated succesfull confirmation callback.
 */
typedef void (*iwu_call_terminated_cllb) (void);

/*!
 * IWU deregistration finished confirmation callback.
 */
typedef void (*iwu_deregistration_cllb) (void *param);

/*!
 * IWU get registration state confirmation callback.
 */
typedef void (*iwu_get_registration_state) (void *param);

/**
 * @brief   openD iwu sub initialization.
 *
 * @details Save the device management configuration in an entry.
 *
 * @param   registration_cllb Registration callback.
 * @param   deregistration_cllb Deregistration callback.
 * @param   registration_state_cllb Get registration state callback.
 */
void opend_iwu_sub_init(iwu_registration_cllb registration_cllb, iwu_deregistration_cllb deregistration_cllb, iwu_get_registration_state registration_state_cllb);

/**
 * @brief   openD iwu call initialization.
 *
 * @details Initialize the iwu for the call module.
 *
 * @param   call_setup_cllb Call setup callback.
 * @param   call_terminated_cllb Call terminated callback.
 */
void opend_iwu_call_init(iwu_call_setup_cllb call_setup_cllb, iwu_call_terminated_cllb call_terminated_cllb);

/**
 * @brief   Legacy state machine.
 *
 * @details Execute the next task of the iwu legacy state machine.
 */
void legacy_state_machine();

/**
 * @brief   openD iwu call request.
 *
 * @details The device sends a call setup request.
 *
 * @param   Handset ID.
 */
void opend_iwu_call_request(char setupCallHandsetId);

/**
 * @brief   openD iwu release call.
 *
 * @details The device sends a call release request.
 */
void opend_iwu_release_call();

/**
 * @brief   openD iwu answer call.
 *
 * @details The device sends a call answer.
 */
void opend_iwu_answer_call();

/**
 * @brief   openD iwu initialization.
 *
 * @details Initialize the interworking unit.
 */
void opend_iwu_init();

/**
 * @brief   openD send registration request.
 *
 * @details The device sends a registration request.
 */
void opend_iwu_register_request();

/**
 * @brief   openD send deregistration request.
 *
 * @details The device sends a deregistration request.
 */
void opend_iwu_deregister_request();

/**
 * @brief   opend iwu get registration state.
 *
 * @details Get registration state.
 */
void opend_iwu_get_registration_state();

/**
 * @brief   opend iwu audio init.
 *
 * @details Audio initialization.
 */
void opend_iwu_audio_init();
