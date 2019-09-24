/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_opend.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
 * @author     STACKFORCE
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 */


extern "C"{
  #include "opend_api.h"
}

/* Module class declaration. */
class Opend
{
public:
   virtual ~Opend() {}
   virtual openD_status_t openD_init( void* ) = 0;
  //  virtual openD_status_t openD_api_getStatus( void ) = 0;
   virtual void openD_setStatusBusy( void ) = 0;
   virtual void openD_setStatusIdle( void ) = 0;
};


/* Module class implementaion. */
class MockOpend : public Opend
{
public:
  MOCK_METHOD1(openD_init, openD_status_t( void* ));
  // MOCK_METHOD0(openD_getStatus, openD_status_t( void ));
  MOCK_METHOD0(openD_setStatusBusy, void( void ));
  MOCK_METHOD0(openD_setStatusIdle, void( void ));
};

void setMockOpendReference(Opend *ref);
