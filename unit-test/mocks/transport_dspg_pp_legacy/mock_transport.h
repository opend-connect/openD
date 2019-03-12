/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_transport.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
 * @author     STACKFORCE
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 */

#include <gmock/gmock.h>

extern "C"{
#include "transport.h"
}

/* Module class declaration. */
class Transport
{
public:
   virtual ~Transport() {}
   virtual void legacy_state_machine() = 0;
   virtual void opend_iwu_answer_call() = 0;
   virtual void opend_iwu_audio_init() = 0;
   virtual void opend_iwu_call_init(iwu_call_setup_cllb call_setup_cllb, iwu_call_terminated_cllb call_terminated_cllb) = 0;
   virtual void opend_iwu_call_request(char setupCallAndHandsetId) = 0;
   virtual void opend_iwu_deregister_request() = 0;
   virtual void opend_iwu_get_registration_state() = 0;
   virtual void opend_iwu_init() = 0;
   virtual void opend_iwu_register_request() = 0;
   virtual int8_t opend_iwu_set_registration_pin(uint8_t data[4]) = 0;
   virtual void opend_iwu_release_call() = 0;
   virtual void opend_iwu_sub_init(iwu_registration_cllb registration_cllb, iwu_deregistration_cllb deregistration_cllb, iwu_get_registration_state registration_state_cllb) = 0;
};


/* Module class implementaion. */
class MockTransport : public Transport
{
public:
   MOCK_METHOD0(legacy_state_machine ,  void());
   MOCK_METHOD0(opend_iwu_answer_call ,  void());
   MOCK_METHOD0(opend_iwu_audio_init ,  void());
   MOCK_METHOD2(opend_iwu_call_init ,  void(iwu_call_setup_cllb call_setup_cllb, iwu_call_terminated_cllb call_terminated_cllb));
   MOCK_METHOD1(opend_iwu_call_request ,  void(char setupCallAndHandsetId));
   MOCK_METHOD0(opend_iwu_deregister_request ,  void());
   MOCK_METHOD0(opend_iwu_get_registration_state ,  void());
   MOCK_METHOD0(opend_iwu_init ,  void());
   MOCK_METHOD0(opend_iwu_register_request ,  void());
   MOCK_METHOD1(opend_iwu_set_registration_pin,  int8_t(uint8_t data[4]));
   MOCK_METHOD0(opend_iwu_release_call ,  void());
   MOCK_METHOD3(opend_iwu_sub_init ,  void(iwu_registration_cllb registration_cllb, iwu_deregistration_cllb deregistration_cllb, iwu_get_registration_state registration_state_cllb));
};

void setMockTransportReference(Transport *transportParam);
