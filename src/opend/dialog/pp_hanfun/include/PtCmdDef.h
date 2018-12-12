///*
// * Copyright (c) by RTX A/S, Denmark
// * All rights reserved.
// *
// * Redistribution and use in source and binary forms, with or without
// * modification, are permitted provided that the following conditions
// * are met:
// * 1. Redistributions of source code must retain the above copyright
// *    notice, this list of conditions and the following disclaimer.
// * 2. Redistributions in binary form must reproduce the above copyright
// *    notice, this list of conditions and the following disclaimer in the
// *    documentation and/or other materials provided with the distribution.
// * 3. Neither the name of RTX A/S nor the names of its contributors
// *    may be used to endorse or promote products derived from this software
// *    without specific prior written permission.
// *
// * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
// * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
// * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// * SUCH DAMAGE.
// *
// */
//
///*! \file
//* RTX Product Test command primitives (opcodes) and parameter structs are
//* defined in this file. */
//
//#ifndef PTCMDDEF_H
//#define PTCMDDEF_H
//
///****************************************************************************
//*                     Enumerations/Type definitions/Structs
//****************************************************************************/
//
///** \page prod_test_commands Production Test Command Overview
//*
//* All the Product Test commands supported are listed on this page.
//* Each command is assigned an user friendly name and an opcode.
//* The name is used to identify the commands in the test apps on the PC and the
//* opcode is used to identify the commands in the target implementation (DUT).
//* The \ref rtx_prod_test_dll "RtxProdTest.dll" translates between the string
//* representation of the test commands in the test apps and the binary
//* representation used in the target implementation.
//*
//* A bat file is generated for each test command to make it easy to send test
//* commands to the DUT. The name of these bat files are the
//* "test command name".bat. E.g. SetTestMode.bat.
//* The batfiles use \ref pt_mail "PtMail.exe" to send the test command to the DUT.
//*
//* The command string specified for each command shows how to execute this command
//* from the test app through the RtxProdTest.dll (e.g PtMail.exe). See \ref PtTestCmd
//* for more info about the test command and response sting format.
//* The response string specifies the expected output returned from the RtxProdTest.dll
//* when a response to a test command is received from the device under test.
//*
//* \section Common Common Test Commands
//*
//* - <b>Name:</b> \ref PT_CMD_SET_TEST_MODE "SetTestMode"<br>
//*   <b>Opcode:</b> \ref PT_CMD_SET_TEST_MODE<br>
//*   <b>Description:</b> This command is used to request the DUT to enter or exit DECT test mode. The DUT will do a warm start after this command has been handled.<br>
//*   <b>Command:</b> <i>"SetTestMode <rsbool TestMode>"</i><br>
//*   <b>Response:</b> <i>""</i>
//*
//* - <b>Name:</b> \ref PT_CMD_GET_SW_VERSION "GetVersion"<br>
//*   <b>Opcode:</b> \ref PT_CMD_GET_SW_VERSION<br>
//*   <b>Description:</b> This command is used to read the SW version number.<br>
//*   <b>Command:</b> <i>"GetVersion"</i><br>
//*   <b>Response:</b> <i>"Version:<rsuint16 Version> SubVersion:<rsuint16 SubVersion>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_SW_RESET "Reset"<br>
//*   <b>Opcode:</b> \ref PT_CMD_SW_RESET<br>
//*   <b>Description:</b> Used to request the DUT to reset. The DUT waits for the EE write cache to become empty before it resets.<br>
//*   <b>Command:</b> <i>"Reset"</i><br>
//*   <b>Response:</b> <i>""</i>
//*
//* - <b>Name:</b> \ref PT_CMD_GET_SW_LINK_DATE "GetLinkDate"<br>
//*   <b>Opcode:</b> \ref PT_CMD_GET_SW_LINK_DATE<br>
//*   <b>Description:</b> This command is used to request the SW link date and time.<br>
//*   <b>Command:</b> <i>"GetLinkDate"</i><br>
//*   <b>Response:</b> <i>"Year:<rsuint8 Year> Month:<rsuint8 Month> Day:<rsuint8 Day> Hour:<rsuint8 Hour> Minute:<rsuint8 Minute>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_GET_EE_CACHE_STATE "GetEeCacheState"<br>
//*   <b>Opcode:</b> \ref PT_CMD_GET_EE_CACHE_STATE<br>
//*   <b>Description:</b> This command is used to get the current state of the write cache in the EEPROM driver.<br>
//*   <b>Command:</b> <i>"GetEeCacheState"</i><br>
//*   <b>Response:</b> <i>"CacheEmpty:<rsbool CacheEmpty>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_GET_PROD_DATA "GetProdData"<br>
//*   <b>Opcode:</b> \ref PT_CMD_GET_PROD_DATA<br>
//*   <b>Description:</b> This command is used to read some data form the part of the EEPROM reserved for the production.<br>
//*   <b>Command:</b> <i>"GetProdData <rsuint8 Length> <rsuint8 DataOffset>"</i><br>
//*   <b>Response:</b> <i>"Data:<rsuint8 Data[]>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_SET_PROD_DATA "SetProdData"<br>
//*   <b>Opcode:</b> \ref PT_CMD_SET_PROD_DATA<br>
//*   <b>Description:</b> This command is used to write some data to the part of the EEPROM reserved for the production.<br>
//*   <b>Command:</b> <i>"SetProdData <rsuint8 Length> <rsuint8 DataOffset> <rsuint8 Data[]>"</i><br>
//*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_AM "AmCmd"<br>
//*   <b>Opcode:</b> \ref PT_CMD_AM<br>
//*   <b>Description:</b> This command is used to send a test command to the Audio manager in the DUT.<br>
//*   <b>Command:</b> <i>"AmCmd <rsuint8 CommandId> <rsuint8 ParameterLength> <rsuint8 Parameter[]>"</i><br>
//*   <b>Response:</b> <i>"Data:<rsuint8 Data[]>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_SET_NVS "SetNvs"<br>
//*   <b>Opcode:</b> \ref PT_CMD_SET_NVS<br>
//*   <b>Description:</b> This command is used to write data to the NVS (EEPROM).<br>
//*   <b>Command:</b> <i>"SetNvs <rsuint32 Address> <rsuint8 Length> <rsuint8 Data[]>"</i><br>
//*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_GET_NVS "GetNvs"<br>
//*   <b>Opcode:</b> \ref PT_CMD_GET_NVS<br>
//*   <b>Description:</b> This command is used to read data from the NVS.<br>
//*   <b>Command:</b> <i>"GetNvs <rsuint32 Address> <rsuint8 Length>"</i><br>
//*   <b>Response:</b> <i>"Status:<RsStatusType Status> Address:<rsuint32 Address> Length:<rsuint8 Length> Data:<rsuint8 Data[]>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_NVS_DEFAULT "NvsDefault"<br>
//*   <b>Opcode:</b> \ref PT_CMD_NVS_DEFAULT<br>
//*   <b>Description:</b> This command is used to do a default programming of the NVS / EEPROM in the DUT. Two cfm messages are sent back to the PC as response to this command. The first with Status == RSS_PENDING is sent when the default programming is started and the second with Status=RSS_SUCCESS is sent when the default programming has finished.<br>
//*   <b>Command:</b> <i>"NvsDefault <rsbool FactoryDefault>"</i><br>
//*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
//*
//*
//* \section RF RF Test Commands
//*
//* - <b>Name:</b> \ref PT_CMD_GET_RSSI "GetRssi"<br>
//*   <b>Opcode:</b> \ref PT_CMD_GET_RSSI<br>
//*   <b>Description:</b> This command is used to get the current uncompensated RSSI level on the Rx slot of the connection. If more than one connection, the RSSI of the first connection is returned.<br>
//*   <b>Command:</b> <i>"GetRssi"</i><br>
//*   <b>Response:</b> <i>"Rssi:<rsuint8 Rssi>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_GET_RSSI_CONT_RX "GetRssiContRx"<br>
//*   <b>Opcode:</b> \ref PT_CMD_GET_RSSI_CONT_RX<br>
//*   <b>Description:</b> This command is used to get the current uncompensated RSSI level in continuous RX mode.<br>
//*   <b>Command:</b> <i>"GetRssiContRx"</i><br>
//*   <b>Response:</b> <i>"Rssi:<rsuint8 Rssi>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_SET_DIVERSITY_MODE "SetDiversityMode"<br>
//*   <b>Opcode:</b> \ref PT_CMD_SET_DIVERSITY_MODE<br>
//*   <b>Description:</b> This command is used to set the DiversityMode temporarily in the RAM (EEPROM in RAM).<br>
//*   <b>Command:</b> <i>"SetDiversityMode <PtDiversityModeType DiversityMode>"</i><br>
//*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_SET_ID "SetId"<br>
//*   <b>Opcode:</b> \ref PT_CMD_SET_ID<br>
//*   <b>Description:</b> This command is used to set the RFPI of a base or IPEI of a handset.<br>
//*   <b>Command:</b> <i>"SetId <rsuint8 Id[5]>"</i><br>
//*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_GET_ID "GetId"<br>
//*   <b>Opcode:</b> \ref PT_CMD_GET_ID<br>
//*   <b>Description:</b> This command is used to get the RFPI of a base or IPEI of a handset.<br>
//*   <b>Command:</b> <i>"GetId"</i><br>
//*   <b>Response:</b> <i>"Id[5]:<rsuint8 Id[5]>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_SET_CONTINUOUS_TX "SetContTx"<br>
//*   <b>Opcode:</b> \ref PT_CMD_SET_CONTINUOUS_TX<br>
//*   <b>Description:</b> This command is used to set the DUT in continuous TX mode on the channel specified.<br>
//*   <b>Command:</b> <i>"SetContTx <rsuint8 Channel> [rsuint8 Antenna] [rsuint8 Radio]"</i><br>
//*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_SET_CONTINUOUS_RX "SetContRx"<br>
//*   <b>Opcode:</b> \ref PT_CMD_SET_CONTINUOUS_RX<br>
//*   <b>Description:</b> This command is used to set the DUT in continuous RX mode on the channel specified.<br>
//*   <b>Command:</b> <i>"SetContRx <rsuint8 Channel> [rsuint8 Antenna] [rsuint8 Radio]"</i><br>
//*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_SET_BURST_MODE "SetBurstMode"<br>
//*   <b>Opcode:</b> \ref PT_CMD_SET_BURST_MODE<br>
//*   <b>Description:</b> This command is used to set the DUT in burst TX mode on the channel and antenna specified.<br>
//*   <b>Command:</b> <i>"SetBurstMode <rsuint8 Channel> <rsuint8 Antenna>"</i><br>
//*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_SET_RF_CLOCK_STATE "SetRfClock"<br>
//*   <b>Opcode:</b> \ref PT_CMD_SET_RF_CLOCK_STATE<br>
//*   <b>Description:</b> This command is used to enable or disable the RF clock inntest mode. Test mode is exited if RfClockEnabled = FALSE<br>
//*   <b>Command:</b> <i>"SetRfClock <rsbool RfClockEnabled>"</i><br>
//*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_SET_DECT_MODE "SetDectMode"<br>
//*   <b>Opcode:</b> \ref PT_CMD_SET_DECT_MODE<br>
//*   <b>Description:</b> This command is used to set the DECT mode of the device.<br>
//*   <b>Command:</b> <i>"SetDectMode <PtDectModeType DectMode>"</i><br>
//*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_GET_DECT_MODE "GetDectMode"<br>
//*   <b>Opcode:</b> \ref PT_CMD_GET_DECT_MODE<br>
//*   <b>Description:</b> This command is used to get the current DECT mode of the device.<br>
//*   <b>Command:</b> <i>"GetDectMode"</i><br>
//*   <b>Response:</b> <i>"DectMode:<PtDectModeType DectMode>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_SET_MODULATION "SetModulation"<br>
//*   <b>Opcode:</b> \ref PT_CMD_SET_MODULATION<br>
//*   <b>Description:</b> This command is used to set the TX modulation.<br>
//*   <b>Command:</b> <i>"SetModulation [rsuint8 Modulation]"</i><br>
//*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_GET_MODULATION "GetModulation"<br>
//*   <b>Opcode:</b> \ref PT_CMD_GET_MODULATION<br>
//*   <b>Description:</b> This command is used to read the TX modulation stored in the EEPROM.<br>
//*   <b>Command:</b> <i>"GetModulation"</i><br>
//*   <b>Response:</b> <i>"Modulation:<rsuint8 Modulation>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_GET_LOCK_STATE "GetLockState"<br>
//*   <b>Opcode:</b> \ref PT_CMD_GET_LOCK_STATE<br>
//*   <b>Description:</b> This command is used to get the lock state.<br>
//*   <b>Command:</b> <i>"GetLockState"</i><br>
//*   <b>Response:</b> <i>"Locked:<rsbool Locked>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_SET_RSSI_LIMIT_PP "SetRssiLimitPp"<br>
//*   <b>Opcode:</b> \ref PT_CMD_SET_RSSI_LIMIT_PP<br>
//*   <b>Description:</b> This command is used to set the RSSI limit in the NVS.<br>
//*   <b>Command:</b> <i>"SetRssiLimitPp <rsuint8 MaxRssiLevelFullSlot> <rsuint8 MaxRssiLevelDoubleSlot>"</i><br>
//*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_SET_CLOCK_FREQUENCY "SetFreq"<br>
//*   <b>Opcode:</b> \ref PT_CMD_SET_CLOCK_FREQUENCY<br>
//*   <b>Description:</b> This command is used to set the clock frequency in the EEPROM and adjust the clock in the SC144xx<br>
//*   <b>Command:</b> <i>"SetFreq <rsuint16 Frequency>"</i><br>
//*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_GET_CLOCK_FREQUENCY "GetFreq"<br>
//*   <b>Opcode:</b> \ref PT_CMD_GET_CLOCK_FREQUENCY<br>
//*   <b>Description:</b> This command is used to get the current clock frequency used.<br>
//*   <b>Command:</b> <i>"GetFreq"</i><br>
//*   <b>Response:</b> <i>"Frequency:<rsuint16 Frequency>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_GET_NVS_CLOCK_FREQUENCY "GetFreqNvs"<br>
//*   <b>Opcode:</b> \ref PT_CMD_GET_NVS_CLOCK_FREQUENCY<br>
//*   <b>Description:</b> This command is used to get clock frequency setting stored in the NVS.<br>
//*   <b>Command:</b> <i>"GetFreqNvs"</i><br>
//*   <b>Response:</b> <i>"Frequency:<rsuint16 Frequency>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_SET_ENROLMENT_DATA "SetEnrolmentData"<br>
//*   <b>Opcode:</b> \ref PT_CMD_SET_ENROLMENT_DATA<br>
//*   <b>Description:</b> This command is used to set enrolment data on base and handset. This makes it possible to register a handset on a base via the test interface without any communication over the air interface.<br>
//*   <b>Command:</b> <i>"SetEnrolmentData <rsuint8 HandsetNo> <rsuint8 Rfpi[5]> <rsuint8 Ipei[5]> <rsuint8 Uak[16]>"</i><br>
//*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_SET_RF_POWER_LEVEL_PORT "SetRfPowerLevelPort"<br>
//*   <b>Opcode:</b> \ref PT_CMD_SET_RF_POWER_LEVEL_PORT<br>
//*   <b>Description:</b> This command is used to set power level port setting.<br>
//*   <b>Command:</b> <i>"SetRfPowerLevelPort <rsuint8 PortSetting>"</i><br>
//*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_SET_RF_POWER_LEVEL_ALGORITHM "SetRfPowerLevelAlgorithm"<br>
//*   <b>Opcode:</b> \ref PT_CMD_SET_RF_POWER_LEVEL_ALGORITHM<br>
//*   <b>Description:</b> This command is used to enable and disable the power control algorithm.<br>
//*   <b>Command:</b> <i>"SetRfPowerLevelAlgorithm <rsbool Enabled>"</i><br>
//*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_GET_RF_POWER_LEVEL_ALGORITHM "GetRfPowerLevelAlgorithm"<br>
//*   <b>Opcode:</b> \ref PT_CMD_GET_RF_POWER_LEVEL_ALGORITHM<br>
//*   <b>Description:</b> This command is used to check whether the power control algorithm is enabled.<br>
//*   <b>Command:</b> <i>"GetRfPowerLevelAlgorithm"</i><br>
//*   <b>Response:</b> <i>"Enabled:<rsbool Enabled>"</i>
//*
//*
//* \section BB BB Test Commands
//*
//* - <b>Name:</b> \ref PT_CMD_SET_BAND_GAP "SetBandGap"<br>
//*   <b>Opcode:</b> \ref PT_CMD_SET_BAND_GAP<br>
//*   <b>Description:</b> This command is used to set/adjust the band gap in the SC144xx and store it in the EEPROM.<br>
//*   <b>Command:</b> <i>"SetBandGap <rsuint8 BandGap>"</i><br>
//*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_GET_BAND_GAP "GetBandGap"<br>
//*   <b>Opcode:</b> \ref PT_CMD_GET_BAND_GAP<br>
//*   <b>Description:</b> This command is used to read the band gap setting from the EEPROM.<br>
//*   <b>Command:</b> <i>"GetBandGap"</i><br>
//*   <b>Response:</b> <i>"BandGap:<rsuint8 BandGap>"</i>
//*
//*
//* \section Battery Battery Test Commands
//*
//* - <b>Name:</b> \ref PT_CMD_CALIBRATE_SOC "CalibrateSoc"<br>
//*   <b>Opcode:</b> \ref PT_CMD_CALIBRATE_SOC<br>
//*   <b>Description:</b> This command is used to request the DUT to start the calibration of the SOC conversion factor through internal or external current source. Please note that it may take up to 2 secs for the SOC calibration to complete.<br>
//*   <b>Command:</b> <i>"CalibrateSoc <rsuint8 Current>"</i><br>
//*   <b>Response:</b> <i>"SocFactor:<rsuint16 SocFactor>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_GET_BATTERY_VOLTAGE "GetBatt"<br>
//*   <b>Opcode:</b> \ref PT_CMD_GET_BATTERY_VOLTAGE<br>
//*   <b>Description:</b> This command is used to request the DUT to start the calibration of the SOC conversion factor through internal or external current source.<br>
//*   <b>Command:</b> <i>"GetBatt"</i><br>
//*   <b>Response:</b> <i>"BatteryVoltage:<rsuint16 BatteryVoltage>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_SET_NO_BATTERY "SetNoBatt"<br>
//*   <b>Opcode:</b> \ref PT_CMD_SET_NO_BATTERY<br>
//*   <b>Description:</b> This command is used to write battery NO voltage parameter in Eeprom and RAM.<br>
//*   <b>Command:</b> <i>"SetNoBatt <rsuint16 Level>"</i><br>
//*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_SET_LOW_BATTERY "SetLowBatt"<br>
//*   <b>Opcode:</b> \ref PT_CMD_SET_LOW_BATTERY<br>
//*   <b>Description:</b> This command is used to write the low battery voltage parameter in Eeprom and RAM.<br>
//*   <b>Command:</b> <i>"SetLowBatt <rsuint16 Level>"</i><br>
//*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_SET_HIGH_BATTERY "SetHighBatt"<br>
//*   <b>Opcode:</b> \ref PT_CMD_SET_HIGH_BATTERY<br>
//*   <b>Description:</b> This command is used to write the high battery voltage parameter in Eeprom and RAM.<br>
//*   <b>Command:</b> <i>"SetHighBatt <rsuint16 Level>"</i><br>
//*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_GET_BATTERY_CURRENT "GetBattCurrent"<br>
//*   <b>Opcode:</b> \ref PT_CMD_GET_BATTERY_CURRENT<br>
//*   <b>Description:</b> This command is used to get the current consumption.<br>
//*   <b>Command:</b> <i>"GetBattCurrent"</i><br>
//*   <b>Response:</b> <i>"Current:<rsuint16 Current>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_GET_CRADLE "GetCradle"<br>
//*   <b>Opcode:</b> \ref PT_CMD_GET_CRADLE<br>
//*   <b>Description:</b> This command is used to get the current cradle state.<br>
//*   <b>Command:</b> <i>"GetCradle"</i><br>
//*   <b>Response:</b> <i>"CradleState:<rsbool CradleState>"</i>
//*
//* - <b>Name:</b> \ref PT_CMD_SET_CHARGE_PORT "SetCharge"<br>
//*   <b>Opcode:</b> \ref PT_CMD_SET_CHARGE_PORT<br>
//*   <b>Description:</b> This command is used to set the charge port ON or OFF.<br>
//*   <b>Command:</b> <i>"SetCharge <rsbool Charge>"</i><br>
//*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
//*
//*
//* \section CAT-iq CAT-iq Test Commands
//*
//*
//*
//*/
///// This enum defines the DECT types possible.
//typedef enum RSENUMTAG(PtDectModeType)
//{
//  EU_DECT = 0x00, //!< Set to EU DECT mode.
//  US_DECT = 0x01, //!< Set to US DECT mode.
//  SA_DECT = 0x02, //!< Set to SA DECT mode.
//  TAIWAN_DECT = 0x03, //!< Set to Taiwan DECT mode.
//  MALAYSIA_DECT = 0x04, //!< Set to Malaysia DECT mode.
//  CHINA_DECT = 0x05, //!< Set to China DECT mode.
//  THAILAND_DECT = 0x06, //!< Set to Thailand DECT mode.
//  BRAZIL_DECT = 0x07, //!< Set to Brazil DECT mode.
//  US_DECT_EXT_FREQ = 0x08, //!< Set to US DECT mode with extended freq band.
//  KOREAN_DECT = 0x09, //!< Set to Korean DECT mode.
//  JAPAN_DECT = 0x0A, //!< Set to Korean DECT mode.
//  UNKNOWN_DECT_MODE = 0xFF
//} RSENUM8(PtDectModeType);
//
///// This enum defines the possible values for diversity mode.
//typedef enum RSENUMTAG(PtDiversityModeType)
//{
//  PT_DIVERSITY_MODE_ENABLED = 0x00, //!< Enable diversity mode
//  PT_DIVERSITY_MODE_ANTENNA_1 = 0x01, //!< Disable diversity mode. Only use antenna 1
//  PT_DIVERSITY_MODE_ANTENNA_2 = 0x02  //!< Disable diversity mode. Only use antenna 2
//} RSENUM8(PtDiversityModeType);
//
///// This enum defines the audio tone test commands supported.
//typedef enum RSENUMTAG(PtAmToneTestCmdType)
//{
//  PT_AM_TONE_STOP = 0x00, //!< Stop the tone generation.
//  PT_AM_TONE_500HZ = 0x01, //!< Play 500 Hz tone.
//  PT_AM_TONE_1000HZ = 0x02, //!< Play 1000 Hz tone.
//  PT_AM_TONE_3000HZ = 0x03, //!< Play 3000 Hz tone.
//  PT_AM_TONE_6000HZ = 0x04, //!< Play 6000 Hz tone.
//  PT_AM_TONE_INVALID = 0xFF
//} RSENUM8(PtAmToneTestCmdType);
//
///// This enum defines the LED test commands supported.
//typedef enum RSENUMTAG(PtLedCmdType)
//{
//  PT_LED_OFF = 0x00, //!< Switch off a LED.
//  PT_LED_ON = 0x01, //!< Switch on a LED.
//  PT_LED_INVALID = 0xFF
//} RSENUM8(PtLedCmdType);
//
///// This enum defines the back light commands supported.
//typedef enum RSENUMTAG(PtBacklightCmdType)
//{
//  PT_BACKLIGHT_OFF = 0x00, //!< Switch off the backlight.
//  PT_BACKLIGHT_ON = 0x01, //!< Switch on the backlight.
//  PT_BACKLIGHT_INVALID = 0xFF
//} RSENUM8(PtBacklightCmdType);
//
///// This enum is used to identify the device for which the backlight command is used
//typedef enum RSENUMTAG(PtBacklightIdType)
//{
//  PT_BACKLIGHT_ALL = 0x00, //!< All backlights (default).
//  PT_BACKLIGHT_DISPLAY = 0x01, //!< The backlight for the display.
//  PT_BACKLIGHT_KEYPAD = 0x02, //!< The backlight for the keypad.
//  PT_BACKLIGHT_EXT_KEYPAD = 0x03, //!< The backlight for an external keypad.
//  PT_BACKLIGHT_GROUP_INVALID = 0xFF
//} RSENUM8(PtBacklightIdType);
//
///// This enum defines the display test commands supported.
//typedef enum RSENUMTAG(PtDisplayTestCmdType)
//{
//  PT_DISPLAY_CLEAR = 0x00, //!< Clear the display.
//  PT_DISPLAY_INVALID = 0xFF
//} RSENUM8(PtDisplayTestCmdType);
//
///// This enum defines the codec types.
//typedef enum RSENUMTAG(PtSwCodecType)
//{
//  PT_SW_CT_NONE = 0x00,
//  PT_SW_CT_USER_SPECIFIC_32 = 0x01, //!< Information transfer rate 32 kbit/s
//  PT_SW_CT_G726 = 0x02, //!< ADPCM
//  PT_SW_CT_G722 = 0x03, //!< WB
//  PT_SW_CT_G711A = 0x04, //!< A-law
//  PT_SW_CT_G711U = 0x05, //!< u-law
//  PT_SW_CT_G7291 = 0x06, //!< G.729.1
//  PT_SW_CT_MP4_32 = 0x07, //!< MPEG-4 ER AAC-LD, information transfer rate 32 kbit/s
//  PT_SW_CT_MP4_64 = 0x08, //!< MPEG-4 ER AAC-LD, information transfer rate 64 kbit/s
//  PT_SW_CT_USER_SPECIFIC_64 = 0x09  //!< Information transfer rate 64 kbit/s
//} RSENUM8(PtSwCodecType);
//
///// Enables the Common test commands.
//#ifndef PT_COMMON_TEST
//  #define PT_COMMON_TEST 1
//#endif
//
///** \name Common Test Command Opcodes
//* The following Common test commands are defined.*/
////@{
//
///*! This command is used to request the DUT to enter or exit DECT test mode. The DUT will do a warm start after this command has been handled. <br>
//Parameters: \ref PtSetTestModeReqType <br>
//Returns: none <br>
//Bat file: SetTestMode.bat */
//#define PT_CMD_SET_TEST_MODE 0x0001
//
///// \ref PT_CMD_SET_TEST_MODE REQ parameter type.
//typedef struct
//{
//  rsbool TestMode; //!< Mode = 0(FALSE): Normal mode; Mode > 0 (TRUE): Test mode enabled. On PP's the mode is also used to set the test carrier used. [0x01-0x09] uses dummy RFPI [00 00 00 10 00; 00 00 00 90 00]. 0x0F uses the LockToFp[5] parameter in the EEPROM.
//} PtSetTestModeReqType;
//
///*! This command is used to read the SW version number. <br>
//Parameters: none <br>
//Returns: \ref PtGetVersionCfmType <br>
//Bat file: GetVersion.bat */
#define PT_CMD_GET_SW_VERSION 0x0016
//
///// \ref PT_CMD_GET_SW_VERSION CFM parameter type.
//typedef struct
//{
//  rsuint16 Version; //!< The version number (BCD coded). E.g. 0x1234 = v1234 (version 12.34).
//  rsuint16 SubVersion; //!< Sub version / branch number (BCD coded).
//} PtGetVersionCfmType;
//
///*! Used to request the DUT to reset. The DUT waits for the EE write cache to become empty before it resets. <br>
//Parameters: none <br>
//Returns: none <br>
//Bat file: Reset.bat */
#define PT_CMD_SW_RESET 0x0028
//
///*! This command is used to request the SW link date and time. <br>
//Parameters: none <br>
//Returns: \ref PtGetLinkDateCfmType <br>
//Bat file: GetLinkDate.bat */
//#define PT_CMD_GET_SW_LINK_DATE 0x0029
//
///// \ref PT_CMD_GET_SW_LINK_DATE CFM parameter type.
//typedef struct
//{
//  rsuint8 Year; //!< BCD coded: [0;99] (2000-2099).
//  rsuint8 Month; //!< BCD coded [1;12] (jan-dec).
//  rsuint8 Day; //!< BCD coded: day of month [1;31]
//  rsuint8 Hour; //!< BCD coded: [0:23]
//  rsuint8 Minute; //!< BCD coded: [0:59]
//} PtGetLinkDateCfmType;
//
///*! This command is used to get the current state of the write cache in the EEPROM driver. <br>
//Parameters: none <br>
//Returns: \ref PtGetEeCacheStateCfmType <br>
//Bat file: GetEeCacheState.bat */
//#define PT_CMD_GET_EE_CACHE_STATE 0x004C
//
///// \ref PT_CMD_GET_EE_CACHE_STATE CFM parameter type.
//typedef struct
//{
//  rsbool CacheEmpty; //!< TRUE(1): The cache is empty; FALSE(0): the cache is not empty.
//} PtGetEeCacheStateCfmType;
//
///*! This command is used to read some data form the part of the EEPROM reserved for the production. <br>
//Parameters: \ref PtGetProdDataReqType <br>
//Returns: \ref PtGetProdDataCfmType <br>
//Bat file: GetProdData.bat */
//#define PT_CMD_GET_PROD_DATA 0x009C
//
///// \ref PT_CMD_GET_PROD_DATA REQ parameter type.
//typedef struct
//{
//  rsuint8 Length; //!< The number of bytes to read from the production data in the EEPROM.
//  rsuint8 DataOffset; //!< The offset of the first byte to read from the production data in the EEPROM.
//} PtGetProdDataReqType;
//
///// \ref PT_CMD_GET_PROD_DATA CFM parameter type.
//typedef struct
//{
//  rsuint8 Data[1]; //!< The data read from the production data in the EEPROM.
//} PtGetProdDataCfmType;
//
///*! This command is used to write some data to the part of the EEPROM reserved for the production. <br>
//Parameters: \ref PtSetProdDataReqType <br>
//Returns: \ref PtSetProdDataCfmType <br>
//Bat file: SetProdData.bat */
//#define PT_CMD_SET_PROD_DATA 0x009D
//
///// \ref PT_CMD_SET_PROD_DATA REQ parameter type.
//typedef struct
//{
//  rsuint8 Length; //!< The number of bytes to write to the production data in the EEPROM.
//  rsuint8 DataOffset; //!< The offset of the first byte to read from the production data in the EEPROM.
//  rsuint8 Data[1]; //!< The data to be written to the production data in the EEPROM.
//} PtSetProdDataReqType;
//
///// \ref PT_CMD_SET_PROD_DATA CFM parameter type.
//typedef struct
//{
//  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
//} PtSetProdDataCfmType;
//
///*! This command is used to send a test command to the Audio manager in the DUT. <br>
//Parameters: \ref PtAmCmdReqType <br>
//Returns: \ref PtAmCmdCfmType <br>
//Bat file: AmCmd.bat */
//#define PT_CMD_AM 0x00CF
//
///// \ref PT_CMD_AM REQ parameter type.
//typedef struct
//{
//  rsuint8 CommandId; //!< The audio manger test sub command id. Id's are defined in audio manager src.
//  rsuint8 ParameterLength; //!< The number of bytes in Parameter[].
//  rsuint8 Parameter[1]; //!< Optional command specific parameters. The number of bytes depends on the actual command.
//} PtAmCmdReqType;
//
///// \ref PT_CMD_AM CFM parameter type.
//typedef struct
//{
//  rsuint8 Data[1]; //!< Optional data returned by the DUT.
//} PtAmCmdCfmType;
//
///*! This command is used to write data to the NVS (EEPROM). <br>
//Parameters: \ref PtSetNvsReqType <br>
//Returns: \ref PtSetNvsCfmType <br>
//Bat file: SetNvs.bat */
//#define PT_CMD_SET_NVS 0x0100
//
///// \ref PT_CMD_SET_NVS REQ parameter type.
//typedef struct
//{
//  rsuint32 Address; //!< The address of the first byte to write to in the NVS.
//  rsuint8 Length; //!< The number of bytes to write to the NVS.
//  rsuint8 Data[1]; //!< The data that should be written to the NVS.
//} PtSetNvsReqType;
//
///// \ref PT_CMD_SET_NVS CFM parameter type.
//typedef struct
//{
//  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
//} PtSetNvsCfmType;
//
///*! This command is used to read data from the NVS. <br>
//Parameters: \ref PtGetNvsReqType <br>
//Returns: \ref PtGetNvsCfmType <br>
//Bat file: GetNvs.bat */
//#define PT_CMD_GET_NVS 0x0101
//
///// \ref PT_CMD_GET_NVS REQ parameter type.
//typedef struct
//{
//  rsuint32 Address; //!< The address of the first byte to read.
//  rsuint8 Length; //!< The number of bytes to read from the NVS.
//} PtGetNvsReqType;
//
///// \ref PT_CMD_GET_NVS CFM parameter type.
//typedef struct
//{
//  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
//  rsuint32 Address; //!< The address of the first byte read from the NVS.
//  rsuint8 Length; //!< The number of bytes read from the NVS.
//  rsuint8 Data[1]; //!< The data read from the NVS.
//} PtGetNvsCfmType;
//
///*! This command is used to do a default programming of the NVS / EEPROM in the DUT. Two cfm messages are sent back to the PC as response to this command. The first with Status == RSS_PENDING is sent when the default programming is started and the second with Status=RSS_SUCCESS is sent when the default programming has finished. <br>
//Parameters: \ref PtNvsDefaultReqType <br>
//Returns: \ref PtNvsDefaultCfmType <br>
//Bat file: NvsDefault.bat */
#define PT_CMD_NVS_DEFAULT 0x0102
//
///// \ref PT_CMD_NVS_DEFAULT REQ parameter type.
//typedef struct
//{
//  rsbool FactoryDefault; //!< TRUE(1) defaults the adjustment parameters (factory settings); FALSE(0): preserves the adjustment parameters.
//} PtNvsDefaultReqType;
//
///// \ref PT_CMD_NVS_DEFAULT CFM parameter type.
//typedef struct
//{
//  RsStatusType Status; //!< Returns RSS_PENDING(0x11) followed by RSS_SUCCESS(0x00) if the command succeeded or RSS_'error'(>0) if the command failed.
//} PtNvsDefaultCfmType;
//
//
////@} end of Common
//
///// Enables the DECT RF test commands.
//#ifndef PT_DECT_RF_TEST
//  #define PT_DECT_RF_TEST 1
//#endif
//
///** \name RF Test Command Opcodes
//* The following RF test commands are defined.*/
////@{
//
///*! This command is used to get the current uncompensated RSSI level on the Rx slot of the connection. If more than one connection, the RSSI of the first connection is returned. <br>
//Parameters: none <br>
//Returns: \ref PtGetRssiCfmType <br>
//Bat file: GetRssi.bat */
#define PT_CMD_GET_RSSI 0x000A
//
///// \ref PT_CMD_GET_RSSI CFM parameter type.
//typedef struct
//{
//  rsuint8 Rssi; //!< Uncompensated RSSI level. 0xFF is returned if no connection has been established.
//} PtGetRssiCfmType;
//
///*! This command is used to get the current uncompensated RSSI level in continuous RX mode. <br>
//Parameters: none <br>
//Returns: \ref PtGetRssiContRxCfmType <br>
//Bat file: GetRssiContRx.bat */
//#define PT_CMD_GET_RSSI_CONT_RX 0x000F
//
///// \ref PT_CMD_GET_RSSI_CONT_RX CFM parameter type.
//typedef struct
//{
//  rsuint8 Rssi; //!< Uncompensated RSSI level.
//} PtGetRssiContRxCfmType;
//
///*! This command is used to set the DiversityMode temporarily in the RAM (EEPROM in RAM). <br>
//Parameters: \ref PtSetDiversityModeReqType <br>
//Returns: \ref PtSetDiversityModeCfmType <br>
//Bat file: SetDiversityMode.bat */
//#define PT_CMD_SET_DIVERSITY_MODE 0x0013
//
///// \ref PT_CMD_SET_DIVERSITY_MODE REQ parameter type.
//typedef struct
//{
//  PtDiversityModeType DiversityMode; //!< The Diversity mode.
//} PtSetDiversityModeReqType;
//
///// \ref PT_CMD_SET_DIVERSITY_MODE CFM parameter type.
//typedef struct
//{
//  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
//} PtSetDiversityModeCfmType;
//
///*! This command is used to set the RFPI of a base or IPEI of a handset. <br>
//Parameters: \ref PtSetIdReqType <br>
//Returns: \ref PtSetIdCfmType <br>
//Bat file: SetId.bat */
//#define PT_CMD_SET_ID 0x001B
//
///// \ref PT_CMD_SET_ID REQ parameter type.
//typedef struct
//{
//  rsuint8 Id[5]; //!< The RFPI/IPEI.
//} PtSetIdReqType;
//
///// \ref PT_CMD_SET_ID CFM parameter type.
//typedef struct
//{
//  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
//} PtSetIdCfmType;
//
///*! This command is used to get the RFPI of a base or IPEI of a handset. <br>
//Parameters: none <br>
//Returns: \ref PtGetIdCfmType <br>
//Bat file: GetId.bat */
//#define PT_CMD_GET_ID 0x001C
//
///// \ref PT_CMD_GET_ID CFM parameter type.
//typedef struct
//{
//  rsuint8 Id[5]; //!< The RFPI/IPEI.
//} PtGetIdCfmType;
//
///*! This command is used to set the DUT in continuous TX mode on the channel specified. <br>
//Parameters: \ref PtSetContTxReqType <br>
//Returns: \ref PtSetContTxCfmType <br>
//Bat file: SetContTx.bat */
//#define PT_CMD_SET_CONTINUOUS_TX 0x002B
//
///// \ref PT_CMD_SET_CONTINUOUS_TX REQ parameter type.
//typedef struct
//{
//  rsuint8 Channel; //!< The channel to transmit on.
//  rsuint8 Antenna; //!< The antenna to transmit on. 0 for default value usually from NVS DiversityMode. 1 for antenna 1, etc.
//  rsuint8 Radio; //!< The radio to transmit on. Ignored on blind slot projects. 0/1 on zero-blind slot projects
//} PtSetContTxReqType;
//
///// \ref PT_CMD_SET_CONTINUOUS_TX CFM parameter type.
//typedef struct
//{
//  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
//} PtSetContTxCfmType;
//
///*! This command is used to set the DUT in continuous RX mode on the channel specified. <br>
//Parameters: \ref PtSetContRxReqType <br>
//Returns: \ref PtSetContRxCfmType <br>
//Bat file: SetContRx.bat */
//#define PT_CMD_SET_CONTINUOUS_RX 0x002E
//
///// \ref PT_CMD_SET_CONTINUOUS_RX REQ parameter type.
//typedef struct
//{
//  rsuint8 Channel; //!< The channel to receive on.
//  rsuint8 Antenna; //!< The antenna to receive on. 0 for default value usually from NVS DiversityMode. 1 for antenna 1, etc.
//  rsuint8 Radio; //!< The radio to receive on. Ignored on blind slot projects. 0/1 on zero-blind slot projects
//} PtSetContRxReqType;
//
///// \ref PT_CMD_SET_CONTINUOUS_RX CFM parameter type.
//typedef struct
//{
//  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
//} PtSetContRxCfmType;
//
///*! This command is used to set the DUT in burst TX mode on the channel and antenna specified. <br>
//Parameters: \ref PtSetBurstModeReqType <br>
//Returns: \ref PtSetBurstModeCfmType <br>
//Bat file: SetBurstMode.bat */
//#define PT_CMD_SET_BURST_MODE 0x002F
//
///// \ref PT_CMD_SET_BURST_MODE REQ parameter type.
//typedef struct
//{
//  rsuint8 Channel; //!< The channel to transmit on.
//  rsuint8 Antenna; //!< The antenna to transmit on.
//} PtSetBurstModeReqType;
//
///// \ref PT_CMD_SET_BURST_MODE CFM parameter type.
//typedef struct
//{
//  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
//} PtSetBurstModeCfmType;
//
///*! This command is used to enable or disable the RF clock inntest mode. Test mode is exited if RfClockEnabled = FALSE <br>
//Parameters: \ref PtSetRfClockReqType <br>
//Returns: \ref PtSetRfClockCfmType <br>
//Bat file: SetRfClock.bat */
//#define PT_CMD_SET_RF_CLOCK_STATE 0x0040
//
///// \ref PT_CMD_SET_RF_CLOCK_STATE REQ parameter type.
//typedef struct
//{
//  rsbool RfClockEnabled; //!< TRUE (1): the RF clock is enabled; FALSE (0): the RF clock is disabled.
//} PtSetRfClockReqType;
//
///// \ref PT_CMD_SET_RF_CLOCK_STATE CFM parameter type.
//typedef struct
//{
//  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
//} PtSetRfClockCfmType;
//
///*! This command is used to set the DECT mode of the device. <br>
//Parameters: \ref PtSetDectModeReqType <br>
//Returns: \ref PtSetDectModeCfmType <br>
//Bat file: SetDectMode.bat */
#define PT_CMD_SET_DECT_MODE 0x0200
//
///// \ref PT_CMD_SET_DECT_MODE REQ parameter type.
//typedef struct
//{
//  PtDectModeType DectMode; //!< The dect mode.
//} PtSetDectModeReqType;
//
///// \ref PT_CMD_SET_DECT_MODE CFM parameter type.
//typedef struct
//{
//  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
//} PtSetDectModeCfmType;
//
///*! This command is used to get the current DECT mode of the device. <br>
//Parameters: none <br>
//Returns: \ref PtGetDectModeCfmType <br>
//Bat file: GetDectMode.bat */
#define PT_CMD_GET_DECT_MODE 0x007C
//
///// \ref PT_CMD_GET_DECT_MODE CFM parameter type.
//typedef struct
//{
//  PtDectModeType DectMode; //!< The current dect mode.
//} PtGetDectModeCfmType;
//
///*! This command is used to set the TX modulation. <br>
//Parameters: \ref PtSetModulationReqType <br>
//Returns: \ref PtSetModulationCfmType <br>
//Bat file: SetModulation.bat */
//#define PT_CMD_SET_MODULATION 0x0012
//
///// \ref PT_CMD_SET_MODULATION REQ parameter type.
//typedef struct
//{
//  rsuint8 Modulation; //!< The modulation.
//} PtSetModulationReqType;
//
///// \ref PT_CMD_SET_MODULATION CFM parameter type.
//typedef struct
//{
//  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
//} PtSetModulationCfmType;
//
///*! This command is used to read the TX modulation stored in the EEPROM. <br>
//Parameters: none <br>
//Returns: \ref PtGetModulationCfmType <br>
//Bat file: GetModulation.bat */
//#define PT_CMD_GET_MODULATION 0x0201
//
///// \ref PT_CMD_GET_MODULATION CFM parameter type.
//typedef struct
//{
//  rsuint8 Modulation; //!< The modulation.
//} PtGetModulationCfmType;
//
///*! This command is used to get the lock state. <br>
//Parameters: none <br>
//Returns: \ref PtGetLockStateCfmType <br>
//Bat file: GetLockState.bat */
//#define PT_CMD_GET_LOCK_STATE 0x0094
//
///// \ref PT_CMD_GET_LOCK_STATE CFM parameter type.
//typedef struct
//{
//  rsbool Locked; //!< TRUE(1): the PP is locked to a FP; FALSE(0) the PP is not locked to a FP.
//} PtGetLockStateCfmType;
//
///*! This command is used to set the RSSI limit in the NVS. <br>
//Parameters: \ref PtSetRssiLimitPpReqType <br>
//Returns: \ref PtSetRssiLimitPpCfmType <br>
//Bat file: SetRssiLimitPp.bat */
//#define PT_CMD_SET_RSSI_LIMIT_PP 0x0203
//
///// \ref PT_CMD_SET_RSSI_LIMIT_PP REQ parameter type.
//typedef struct
//{
//  rsuint8 MaxRssiLevelFullSlot; //!< The max RSSI for full slot connections.
//  rsuint8 MaxRssiLevelDoubleSlot; //!< The max RSSI for double slot connections.
//} PtSetRssiLimitPpReqType;
//
///// \ref PT_CMD_SET_RSSI_LIMIT_PP CFM parameter type.
//typedef struct
//{
//  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
//} PtSetRssiLimitPpCfmType;
//
///*! This command is used to set the clock frequency in the EEPROM and adjust the clock in the SC144xx <br>
//Parameters: \ref PtSetFreqReqType <br>
//Returns: \ref PtSetFreqCfmType <br>
//Bat file: SetFreq.bat */
//#define PT_CMD_SET_CLOCK_FREQUENCY 0x0204
//
///// \ref PT_CMD_SET_CLOCK_FREQUENCY REQ parameter type.
//typedef struct
//{
//  rsuint16 Frequency; //!< The new clock frequency setting. 16 bits are used for SC14480 and 8 bits only for the other Sitel chips in which case the MSB should be set to 0 or omitted.
//} PtSetFreqReqType;
//
///// \ref PT_CMD_SET_CLOCK_FREQUENCY CFM parameter type.
//typedef struct
//{
//  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
//} PtSetFreqCfmType;
//
///*! This command is used to get the current clock frequency used. <br>
//Parameters: none <br>
//Returns: \ref PtGetFreqCfmType <br>
//Bat file: GetFreq.bat */
//#define PT_CMD_GET_CLOCK_FREQUENCY 0x0205
//
///// \ref PT_CMD_GET_CLOCK_FREQUENCY CFM parameter type.
//typedef struct
//{
//  rsuint16 Frequency; //!< The current clock frequency used. Please note that some devices return one byte only. Two bytes are used on SC14480 only.
//} PtGetFreqCfmType;
//
///*! This command is used to get clock frequency setting stored in the NVS. <br>
//Parameters: none <br>
//Returns: \ref PtGetFreqNvsCfmType <br>
//Bat file: GetFreqNvs.bat */
//#define PT_CMD_GET_NVS_CLOCK_FREQUENCY 0x0206
//
///// \ref PT_CMD_GET_NVS_CLOCK_FREQUENCY CFM parameter type.
//typedef struct
//{
//  rsuint16 Frequency; //!< The clock frequency setting read from the NVS. Please note that some devices return one byte only. Two bytes are used on SC14480 only.
//} PtGetFreqNvsCfmType;
//
///*! This command is used to set enrolment data on base and handset. This makes it possible to register a handset on a base via the test interface without any communication over the air interface. <br>
//Parameters: \ref PtSetEnrolmentDataReqType <br>
//Returns: \ref PtSetEnrolmentDataCfmType <br>
//Bat file: SetEnrolmentData.bat */
//#define PT_CMD_SET_ENROLMENT_DATA 0x0207
//
///// \ref PT_CMD_SET_ENROLMENT_DATA REQ parameter type.
//typedef struct
//{
//  rsuint8 HandsetNo; //!< The handset number [1; max number of handsets that can be registered on the base].
//  rsuint8 Rfpi[5]; //!< The RFPI of the base.
//  rsuint8 Ipei[5]; //!< The IPEI of the handset.
//  rsuint8 Uak[16]; //!< The UAK (random number) generated. Must be the same on both the base and the handset.
//} PtSetEnrolmentDataReqType;
//
///// \ref PT_CMD_SET_ENROLMENT_DATA CFM parameter type.
//typedef struct
//{
//  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
//} PtSetEnrolmentDataCfmType;
//
///*! This command is used to set power level port setting. <br>
//Parameters: \ref PtSetRfPowerLevelPortReqType <br>
//Returns: \ref PtSetRfPowerLevelPortCfmType <br>
//Bat file: SetRfPowerLevelPort.bat */
//#define PT_CMD_SET_RF_POWER_LEVEL_PORT 0x0209
//
///// \ref PT_CMD_SET_RF_POWER_LEVEL_PORT REQ parameter type.
//typedef struct
//{
//  rsuint8 PortSetting; //!< The power level port setting (project specific).
//} PtSetRfPowerLevelPortReqType;
//
///// \ref PT_CMD_SET_RF_POWER_LEVEL_PORT CFM parameter type.
//typedef struct
//{
//  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
//} PtSetRfPowerLevelPortCfmType;
//
///*! This command is used to enable and disable the power control algorithm. <br>
//Parameters: \ref PtSetRfPowerLevelAlgorithmReqType <br>
//Returns: \ref PtSetRfPowerLevelAlgorithmCfmType <br>
//Bat file: SetRfPowerLevelAlgorithm.bat */
//#define PT_CMD_SET_RF_POWER_LEVEL_ALGORITHM 0x020C
//
///// \ref PT_CMD_SET_RF_POWER_LEVEL_ALGORITHM REQ parameter type.
//typedef struct
//{
//  rsbool Enabled; //!< TRUE(1): The power control algorithm is enabled; FALSE(0): disabled.
//} PtSetRfPowerLevelAlgorithmReqType;
//
///// \ref PT_CMD_SET_RF_POWER_LEVEL_ALGORITHM CFM parameter type.
//typedef struct
//{
//  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
//} PtSetRfPowerLevelAlgorithmCfmType;
//
///*! This command is used to check whether the power control algorithm is enabled. <br>
//Parameters: none <br>
//Returns: \ref PtGetRfPowerLevelAlgorithmCfmType <br>
//Bat file: GetRfPowerLevelAlgorithm.bat */
//#define PT_CMD_GET_RF_POWER_LEVEL_ALGORITHM 0x020D
//
///// \ref PT_CMD_GET_RF_POWER_LEVEL_ALGORITHM CFM parameter type.
//typedef struct
//{
//  rsbool Enabled; //!< TRUE(1): The power control algorithm is enabled; FALSE(0): disabled.
//} PtGetRfPowerLevelAlgorithmCfmType;
//
//
////@} end of RF
//
///// Enables the BB test commands.
//#ifndef PT_BB_TEST
//  #define PT_BB_TEST 1
//#endif
//
///** \name BB Test Command Opcodes
//* The following BB test commands are defined.*/
////@{
//
///*! This command is used to set/adjust the band gap in the SC144xx and store it in the EEPROM. <br>
//Parameters: \ref PtSetBandGapReqType <br>
//Returns: \ref PtSetBandGapCfmType <br>
//Bat file: SetBandGap.bat */
//#define PT_CMD_SET_BAND_GAP 0x003F
//
///// \ref PT_CMD_SET_BAND_GAP REQ parameter type.
//typedef struct
//{
//  rsuint8 BandGap; //!< The new band gap value.
//} PtSetBandGapReqType;
//
///// \ref PT_CMD_SET_BAND_GAP CFM parameter type.
//typedef struct
//{
//  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
//} PtSetBandGapCfmType;
//
///*! This command is used to read the band gap setting from the EEPROM. <br>
//Parameters: none <br>
//Returns: \ref PtGetBandGapCfmType <br>
//Bat file: GetBandGap.bat */
//#define PT_CMD_GET_BAND_GAP 0x0300
//
///// \ref PT_CMD_GET_BAND_GAP CFM parameter type.
//typedef struct
//{
//  rsuint8 BandGap; //!< The current band gap value.
//} PtGetBandGapCfmType;
//
//
////@} end of BB
//
///// Enables the Battery test commands.
//#ifndef PT_BATTERY_TEST
//  #define PT_BATTERY_TEST 1
//#endif
//
///** \name Battery Test Command Opcodes
//* The following Battery test commands are defined.*/
////@{
//
///*! This command is used to request the DUT to start the calibration of the SOC conversion factor through internal or external current source. Please note that it may take up to 2 secs for the SOC calibration to complete. <br>
//Parameters: \ref PtCalibrateSocReqType <br>
//Returns: \ref PtCalibrateSocCfmType <br>
//Bat file: CalibrateSoc.bat */
//#define PT_CMD_CALIBRATE_SOC 0x0480
//
///// \ref PT_CMD_CALIBRATE_SOC REQ parameter type.
//typedef struct
//{
//  rsuint8 Current; //!< External charge current in mA. The SC14480 uses the internal current source for calibration (less accurate) if 0 is used.
//} PtCalibrateSocReqType;
//
///// \ref PT_CMD_CALIBRATE_SOC CFM parameter type.
//typedef struct
//{
//  rsuint16 SocFactor; //!< The SOC factor calculated (0xFFFF if illegal result calculated).
//} PtCalibrateSocCfmType;
//
///*! This command is used to request the DUT to start the calibration of the SOC conversion factor through internal or external current source. <br>
//Parameters: none <br>
//Returns: \ref PtGetBattCfmType <br>
//Bat file: GetBatt.bat */
//#define PT_CMD_GET_BATTERY_VOLTAGE 0x0481
//
///// \ref PT_CMD_GET_BATTERY_VOLTAGE CFM parameter type.
//typedef struct
//{
//  rsuint16 BatteryVoltage; //!< A/D converter level for the battery vaoltage.
//} PtGetBattCfmType;
//
///*! This command is used to write battery NO voltage parameter in Eeprom and RAM. <br>
//Parameters: \ref PtSetNoBattReqType <br>
//Returns: \ref PtSetNoBattCfmType <br>
//Bat file: SetNoBatt.bat */
//#define PT_CMD_SET_NO_BATTERY 0x0482
//
///// \ref PT_CMD_SET_NO_BATTERY REQ parameter type.
//typedef struct
//{
//  rsuint16 Level; //!< The no battery voltage level.
//} PtSetNoBattReqType;
//
///// \ref PT_CMD_SET_NO_BATTERY CFM parameter type.
//typedef struct
//{
//  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
//} PtSetNoBattCfmType;
//
///*! This command is used to write the low battery voltage parameter in Eeprom and RAM. <br>
//Parameters: \ref PtSetLowBattReqType <br>
//Returns: \ref PtSetLowBattCfmType <br>
//Bat file: SetLowBatt.bat */
//#define PT_CMD_SET_LOW_BATTERY 0x0483
//
///// \ref PT_CMD_SET_LOW_BATTERY REQ parameter type.
//typedef struct
//{
//  rsuint16 Level; //!< The low battery voltage level.
//} PtSetLowBattReqType;
//
///// \ref PT_CMD_SET_LOW_BATTERY CFM parameter type.
//typedef struct
//{
//  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
//} PtSetLowBattCfmType;
//
///*! This command is used to write the high battery voltage parameter in Eeprom and RAM. <br>
//Parameters: \ref PtSetHighBattReqType <br>
//Returns: \ref PtSetHighBattCfmType <br>
//Bat file: SetHighBatt.bat */
//#define PT_CMD_SET_HIGH_BATTERY 0x0484
//
///// \ref PT_CMD_SET_HIGH_BATTERY REQ parameter type.
//typedef struct
//{
//  rsuint16 Level; //!< The high battery voltage level.
//} PtSetHighBattReqType;
//
///// \ref PT_CMD_SET_HIGH_BATTERY CFM parameter type.
//typedef struct
//{
//  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
//} PtSetHighBattCfmType;
//
///*! This command is used to get the current consumption. <br>
//Parameters: none <br>
//Returns: \ref PtGetBattCurrentCfmType <br>
//Bat file: GetBattCurrent.bat */
//#define PT_CMD_GET_BATTERY_CURRENT 0x0487
//
///// \ref PT_CMD_GET_BATTERY_CURRENT CFM parameter type.
//typedef struct
//{
//  rsuint16 Current; //!< The current consumption in 0.1 mA. 0xFFFF is returned if the current can not be measured.
//} PtGetBattCurrentCfmType;
//
///*! This command is used to get the current cradle state. <br>
//Parameters: none <br>
//Returns: \ref PtGetCradleCfmType <br>
//Bat file: GetCradle.bat */
//#define PT_CMD_GET_CRADLE 0x0489
//
///// \ref PT_CMD_GET_CRADLE CFM parameter type.
//typedef struct
//{
//  rsbool CradleState; //!< The current cradle state: TRUE(1) in cradle; FALSE(0) not in cradle.
//} PtGetCradleCfmType;
//
///*! This command is used to set the charge port ON or OFF. <br>
//Parameters: \ref PtSetChargeReqType <br>
//Returns: \ref PtSetChargeCfmType <br>
//Bat file: SetCharge.bat */
//#define PT_CMD_SET_CHARGE_PORT 0x048A
//
///// \ref PT_CMD_SET_CHARGE_PORT REQ parameter type.
//typedef struct
//{
//  rsbool Charge; //!< TRUE(1): charge on; FALSE(0): charge off.
//} PtSetChargeReqType;
//
///// \ref PT_CMD_SET_CHARGE_PORT CFM parameter type.
//typedef struct
//{
//  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
//} PtSetChargeCfmType;
//
///* This message is used to send a HW test command to the target. The function
//   RTX_EAI_HW_TEST_HANDLER() is called when this request is received. */
//typedef struct
//{
//  RosPrimitiveType Primitive;
//  rsuint8 ProgramId;     /* The program id that should be used in when a
//                            RTX_EAP_HW_TEST_CFM is sent back to the host. */
//  rsuint8 TaskId;        /* The task id that should be used in when a
//                            RTX_EAP_HW_TEST_CFM is sent back to the host. */
//  rsuint16 Opcode; /* Op-code identifying the HW test command. */
//  rsuint16 Length; /* The total length in bytes of the parameters. */
//  rsuint16 Parameters[1]; /* Optional parameters. */
//} RtxEapHwTestReqType;
//
///* This message is used to send a response to a HW test command to the host. */
//typedef struct
//{
//  RosPrimitiveType Primitive;
//  rsuint16 Opcode; /* Op-code identifying the response. */
//  rsuint16 Length; /* The total length in bytes of the parameters. */
//  rsuint8 Parameters[1]; /* Optional parameters. */
//} RtxEapHwTestCfmType;
//
////@} end of Battery
//
///// Enables the CAT-iq test commands.
//#ifndef PT_CATIQ_TEST
//  #define PT_CATIQ_TEST 1
//#endif
//
///** \name CAT-iq Test Command Opcodes
//* The following CAT-iq test commands are defined.*/
////@{
//
//
////@} end of CAT-iq
//
//
//
//#endif // PTCMDDEF_H

