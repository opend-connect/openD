/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       ut_dialog_openD_hanfunApi_fp_devMgmtRequest.cpp
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
 * @author     Daniel Jaeckle (STACKFORCE)
 * @author     Mario Behringer (STACKFORCE)
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 */

/** Include files */
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdio.h>
#include <string.h>



#include "application.h"
#include "hf_transport.h"



/** Resource under test */
#include "test_hf_transport.cpp"
#include "opend_hanfun_fp.cpp"
#include "opend_hanfun.cpp"


/** Stubs */
#include "dialog_fp_hanfun_api_stubs.h"


/** Namespaces */
using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::InvokeWithoutArgs;


/*!
 * Class definition
 */
class ut_dialog_openD_hanfunApi_fp_devMgmtRequest: public testing::Test
{
    public:

        void SetUp()
        {
        }
        void TearDown()
        {
        }
};

/*
 * Unit tests
 * */
/*!
 * \brief Tests the function openD_hanfunApi_fp_devMgmtRequest.
 *
 * \details
 */
TEST_F( ut_dialog_openD_hanfunApi_fp_devMgmtRequest, ut_dialog_openD_hanfunApi_fp_devMgmtRequest_invalid_Pointer )
{
    openD_status_t result;
    openD_hanfunApiPrimitives_t primitives;
    openD_hanfunApi_devMgmtReq_t hMgmtRequest;
    HF::ULE::Transport* transport = HF::ULE::Transport::instance();

    primitives.openD_hanfunApiProfileCfm = profileConfirmCallback;
	primitives.openD_hanfunApi_mgmtCfm = devMgmtConfirmCallback;
	primitives.openD_hanfunApiProfileInd = profileIndCallback;
    primitives.openD_hanfunApi_bindCfm = bindMgmtConfirmCallback;

    result = openD_hanfunApi_init( &primitives );

    EXPECT_EQ( OPEND_STATUS_OK, result );

    transport->initialize ();

    result = openD_hanfunApi_fp_init( transport );

    EXPECT_EQ( result, OPEND_STATUS_OK );

    // Call function under test
    result = openD_hanfunApi_fp_devMgmtRequest( NULL );

    EXPECT_EQ( OPEND_STATUS_ARGUMENT_INVALID, result );
}
