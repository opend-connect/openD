/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_AppCall.h
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
#include "cmbs_api.h"
#include "appcall.h"
}

/* Module class declaration. */
class AppCall
{
public:
   virtual ~AppCall() {}
   virtual u16 appcall_EstablishCall ( PST_APPCALL_PROPERTIES pst_Properties, int n_Properties ) = 0;
   virtual PST_CALL_OBJ _appcall_CallObjGetById( u16 u16_CallId ) = 0;
   virtual int appcall_ReleaseCall( PST_APPCALL_PROPERTIES pst_Properties, int n_Properties, u16 u16_CallId, char * psz_CLI ) = 0;
};


/* Module class implementaion. */
class MockAppCall : public AppCall
{
public:
    MOCK_METHOD2( appcall_EstablishCall, u16( PST_APPCALL_PROPERTIES pst_Properties, int n_Properties) );
    MOCK_METHOD1( _appcall_CallObjGetById, PST_CALL_OBJ( u16 u16_CallId ) );
    MOCK_METHOD4( appcall_ReleaseCall, int( PST_APPCALL_PROPERTIES pst_Properties, int n_Properties, u16 u16_CallId, char * psz_CLI ) );
};

void setMockAppCallReference(AppCall *ref);
