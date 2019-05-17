/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_fp_hanfun_app.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
 * @author     STACKFORCE
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 */


#include "application.h"

/* Module class declaration. */
class Fp_hanfun_app
{
public:
   virtual ~Fp_hanfun_app() {}
   virtual void Save( void ) = 0;
};


/* Module class implementaion. */
class MockFp_hanfun_app : public Fp_hanfun_app
{
public:
  MOCK_METHOD0(Save, void( void ));
};

void setMockFp_hanfun_appReference(Fp_hanfun_app *ref);
