/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_msManager.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
 * @author     STACKFORCE
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 */

/* Module class declaration. */
class MsManager
{
public:
   virtual ~MsManager() {}
   virtual void msManager_changeState( msManager_ctxt_t * const ctxt, const msManager_state_t state ) = 0;
   virtual bool msManager_handleService( msManager_ctxt_t * const ctxt, msManager_message_t * const message ) = 0;
   virtual void msManager_init( msManager_ctxt_t * const ctxt, const msManager_stateFct_t states[], const msManager_state_t statesNum ) = 0;
};


/* Module class implementaion. */
class MockMsManager : public MsManager
{
public:
   MOCK_METHOD2(msManager_changeState ,  void( msManager_ctxt_t * const ctxt, const msManager_state_t state ));
   MOCK_METHOD2(msManager_handleService ,  bool( msManager_ctxt_t * const ctxt, msManager_message_t * const message ));
   MOCK_METHOD3(msManager_init ,  void( msManager_ctxt_t * const ctxt, const msManager_stateFct_t states[], const msManager_state_t statesNum ));
};

void setMockMsManagerReference(MsManager *ref);
