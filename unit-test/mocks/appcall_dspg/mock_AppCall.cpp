/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       mock_AppCall.cpp
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
#include "cmbs_api.h"
#include "appcall.h"
}

#include "mock_AppCall.h"

/* Module pointer. */
AppCall *g_AppCall;

extern "C"{

  /* Implement the function to satisfy the linker. */
  void keyb_ReleaseNotify(u16 u16_CallId){
      assert(g_AppCall!=NULL);
  }

  u16 appcall_EstablishCall(PST_APPCALL_PROPERTIES pst_Properties, int n_Properties){
      assert(g_AppCall!=NULL);
      g_AppCall->appcall_EstablishCall(pst_Properties, n_Properties);
  }

  PST_CALL_OBJ _appcall_CallObjGetById( u16 u16_CallId){
      assert(g_AppCall!=NULL);
      g_AppCall->_appcall_CallObjGetById(u16_CallId);
  }

  int appcall_ReleaseCall( PST_APPCALL_PROPERTIES pst_Properties, int n_Properties, u16 u16_CallId, char * psz_CLI){
      assert(g_AppCall!=NULL);
      g_AppCall->appcall_ReleaseCall(pst_Properties, n_Properties, u16_CallId, psz_CLI);
  }

} /* extern */

void setMockAppCallReference(AppCall *ref) {
   g_AppCall = ref;
}
