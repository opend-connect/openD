/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       ut_dspg_openD_hanfunApi_fp_init.cpp
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
#include "opend_hanfun_api.h"


/** Resource under test */
#include "test_hf_transport.cpp"
#include "opend_hanfun_fp.cpp"
#include "opend_hanfun.cpp"


/** Mocks */
#include "mock_testlib.h"
#include "mock_appmsgparser.h"

#include "dspg_fp_hanfun_api_stubs.h"


/** Namespaces */
using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::InvokeWithoutArgs;


/*!
 * Class definition
 */
class ut_dspg_openD_hanfunApi_fp_init: public testing::Test
{
    public:

        MockTestlib ObjMockTestLib;
        MockAppMsgParser ObjAppMsgParser;

        void SetUp()
        {
            setMockTestlibReference(&ObjMockTestLib);
            setMockAppMsgParserReference(&ObjAppMsgParser);
        }
        void TearDown()
        {
        }
};

/*
 * Unit tests
 * */
/*!
 * \brief Tests the function opend_hanfunapi_fp_init.
 *
 * \details Verifies if the function works as expected when applying a valid
 *          pointer as parameter.
 */
TEST_F( ut_dspg_openD_hanfunApi_fp_init, ut_dspg_openD_hanfunApi_fp_init_valid_Pointer )
{
    openD_status_t result;
    openD_hanfunApiPrimitives_t primitives;
    HF::ULE::Transport* transport = HF::ULE::Transport::instance();

    primitives.openD_hanfunApiProfileCfm = profileConfirmCallback;
	primitives.openD_hanfunApi_mgmtCfm = devMgmtConfirmCallback;
	primitives.openD_hanfunApiProfileInd = profileIndCallback;
    primitives.openD_hanfunApi_bindCfm = bindMgmtConfirmCallback;

    result = openD_hanfunApi_init( &primitives );

    EXPECT_EQ( OPEND_STATUS_OK, result );

    transport->initialize ();

    // Setup mock
    EXPECT_CALL( ObjMockTestLib, app_HanRegularStart( TRUE) )
    .Times( 1 );

    result = openD_hanfunApi_fp_init( transport );

    EXPECT_EQ( OPEND_STATUS_OK, result );
}



/*!
 * \brief Tests the function opend_hanfunapi_fp_init.
 *
 * \details Verifies if the function works as expected when applying a null
 *          pointer as parameter.
 */
TEST_F( ut_dspg_openD_hanfunApi_fp_init, ut_dspg_openD_hanfunApi_fp_init_null_pointer )
{
    EXPECT_EQ( OPEND_STATUS_ARGUMENT_INVALID, openD_hanfunApi_fp_init( NULL ));
}
