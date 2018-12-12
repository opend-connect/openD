/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_transport.cpp
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
 * @author     STACKFORCE
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 */

#include "mock_transport.h"

/* Module pointer. */
Transport *g_transport;

extern "C"{

void legacy_state_machine() {
   assert(g_transport != NULL);
   g_transport->legacy_state_machine();
} /* legacy_state_machine */

void opend_iwu_answer_call() {
   assert(g_transport != NULL);
   g_transport->opend_iwu_answer_call();
} /* opend_iwu_answer_call */

void opend_iwu_audio_init() {
   assert(g_transport != NULL);
   g_transport->opend_iwu_audio_init();
} /* opend_iwu_audio_init */

void opend_iwu_call_init(iwu_call_setup_cllb call_setup_cllb, iwu_call_terminated_cllb call_terminated_cllb) {
   assert(g_transport != NULL);
   g_transport->opend_iwu_call_init( call_setup_cllb, call_terminated_cllb);
} /* opend_iwu_call_init */

void opend_iwu_call_request(char setupCallHandsetId) {
   assert(g_transport != NULL);
   g_transport->opend_iwu_call_request(setupCallHandsetId);
} /* opend_iwu_call_request */

void opend_iwu_deregister_request() {
   assert(g_transport != NULL);
   g_transport->opend_iwu_deregister_request();
} /* opend_iwu_deregister_request */

void opend_iwu_get_registration_state() {
   assert(g_transport != NULL);
   g_transport->opend_iwu_get_registration_state();
} /* opend_iwu_get_registration_state */

void opend_iwu_init() {
   assert(g_transport != NULL);
   g_transport->opend_iwu_init();
} /* opend_iwu_init */

void opend_iwu_register_request() {
   assert(g_transport != NULL);
   g_transport->opend_iwu_register_request();
} /* opend_iwu_register_request */

void opend_iwu_release_call() {
   assert(g_transport != NULL);
   g_transport->opend_iwu_release_call();
} /* opend_iwu_release_call */

void opend_iwu_sub_init(iwu_registration_cllb registration_cllb, iwu_deregistration_cllb deregistration_cllb, iwu_get_registration_state registration_state_cllb) {
   assert(g_transport != NULL);
   g_transport->opend_iwu_sub_init( registration_cllb, deregistration_cllb, registration_state_cllb);
} /* opend_iwu_sub_init */

} /* extern */

void setMockTransportReference(Transport *transportParam) {
   g_transport = transportParam;
}
