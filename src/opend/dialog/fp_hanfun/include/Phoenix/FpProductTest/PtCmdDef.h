/*
 * Copyright (c) by RTX A/S, Denmark
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of RTX A/S nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */
/*! \file
* RTX Product Test command primitives (opcodes) and parameter structs are
* defined in this file. */

#ifndef PTCMDDEF_H 
#define PTCMDDEF_H 

/****************************************************************************
*                     Enumerations/Type definitions/Structs                  
****************************************************************************/

/** \page prod_test_commands Production Test Command Overview
*
* All the Product Test commands supported are listed on this page.
* Each command is assigned an user friendly name and an opcode.
* The name is used to identify the commands in the test apps on the PC and the
* opcode is used to identify the commands in the target implementation (DUT).
* The \ref rtx_prod_test_dll "RtxProdTest.dll" translates between the string
* representation of the test commands in the test apps and the binary
* representation used in the target implementation.
* 
* A bat file is generated for each test command to make it easy to send test
* commands to the DUT. The name of these bat files are the
* "test command name".bat. E.g. SetTestMode.bat.
* The batfiles use \ref pt_mail "PtMail.exe" to send the test command to the DUT.
* 
* The command string specified for each command shows how to execute this command
* from the test app through the RtxProdTest.dll (e.g PtMail.exe). See \ref PtTestCmd
* for more info about the test command and response sting format.
* The response string specifies the expected output returned from the RtxProdTest.dll
* when a response to a test command is received from the device under test.
*
* \section Project Project Test Commands
*
* - <b>Name:</b> \ref PT_CMD_IO_TEST "IoTest"<br>
*   <b>Opcode:</b> \ref PT_CMD_IO_TEST<br>
*   <b>Description:</b> This command is used to test the external IO connections of the CVM480 module<br>
*   <b>Command:</b> <i>"IoTest"</i><br>
*   <b>Response:</b> <i>"Result:<rsuint8 Result>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GET_ADC2 "GetAdc2"<br>
*   <b>Opcode:</b> \ref PT_CMD_GET_ADC2<br>
*   <b>Description:</b> This command is used to read the current value of ADC2.<br>
*   <b>Command:</b> <i>"GetAdc2"</i><br>
*   <b>Response:</b> <i>"AdcValue:<rsuint16 AdcValue>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_SERIAL_BACKDRIVE_PROTECTION "SetSerialBackdriveProtection"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_SERIAL_BACKDRIVE_PROTECTION<br>
*   <b>Description:</b> This command is used to set serial backdrive protection value of SPI and UART.<br>
*   <b>Command:</b> <i>"SetSerialBackdriveProtection <rsuint8 ProtectMask>"</i><br>
*   <b>Response:</b> <i>""</i>
*
*
* \section Common Common Test Commands
*
* - <b>Name:</b> \ref PT_CMD_GET_SW_VERSION "GetVersion"<br>
*   <b>Opcode:</b> \ref PT_CMD_GET_SW_VERSION<br>
*   <b>Description:</b> This command is used to read the SW version number.<br>
*   <b>Command:</b> <i>"GetVersion"</i><br>
*   <b>Response:</b> <i>"Version:<rsuint16 Version> SubVersion:<rsuint16 SubVersion> Build:<rsuint16 Build>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SW_RESET "Reset"<br>
*   <b>Opcode:</b> \ref PT_CMD_SW_RESET<br>
*   <b>Description:</b> Used to request the DUT to reset. The DUT waits for the EE write cache to become empty before it resets.<br>
*   <b>Command:</b> <i>"Reset"</i><br>
*   <b>Response:</b> <i>""</i>
*
* - <b>Name:</b> \ref PT_CMD_GET_SW_LINK_DATE "GetLinkDate"<br>
*   <b>Opcode:</b> \ref PT_CMD_GET_SW_LINK_DATE<br>
*   <b>Description:</b> This command is used to request the SW link date and time.<br>
*   <b>Command:</b> <i>"GetLinkDate"</i><br>
*   <b>Response:</b> <i>"Year:<rsuint8 Year> Month:<rsuint8 Month> Day:<rsuint8 Day> Hour:<rsuint8 Hour> Minute:<rsuint8 Minute>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GET_EE_CACHE_STATE "GetEeCacheState"<br>
*   <b>Opcode:</b> \ref PT_CMD_GET_EE_CACHE_STATE<br>
*   <b>Description:</b> This command is used to get the current state of the write cache in the EEPROM driver.<br>
*   <b>Command:</b> <i>"GetEeCacheState"</i><br>
*   <b>Response:</b> <i>"CacheEmpty:<rsbool CacheEmpty>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GET_PROD_DATA "GetProdData"<br>
*   <b>Opcode:</b> \ref PT_CMD_GET_PROD_DATA<br>
*   <b>Description:</b> This command is used to read some data form the part of the EEPROM reserved for the production.<br>
*   <b>Command:</b> <i>"GetProdData <rsuint8 Length> <rsuint8 DataOffset>"</i><br>
*   <b>Response:</b> <i>"Data:<rsuint8 Data[]>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_PROD_DATA "SetProdData"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_PROD_DATA<br>
*   <b>Description:</b> This command is used to write some data to the part of the EEPROM reserved for the production.<br>
*   <b>Command:</b> <i>"SetProdData <rsuint8 Length> <rsuint8 DataOffset> <rsuint8 Data[]>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_NVS "SetNvs"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_NVS<br>
*   <b>Description:</b> This command is used to write data to the NVS (EEPROM).<br>
*   <b>Command:</b> <i>"SetNvs <rsuint32 Address> <rsuint8 Length> <rsuint8 Data[]>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GET_NVS "GetNvs"<br>
*   <b>Opcode:</b> \ref PT_CMD_GET_NVS<br>
*   <b>Description:</b> This command is used to read data from the NVS.<br>
*   <b>Command:</b> <i>"GetNvs <rsuint32 Address> <rsuint8 Length>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status> Address:<rsuint32 Address> Length:<rsuint8 Length> Data:<rsuint8 Data[]>"</i>
*
* - <b>Name:</b> \ref PT_CMD_NVS_DEFAULT "NvsDefault"<br>
*   <b>Opcode:</b> \ref PT_CMD_NVS_DEFAULT<br>
*   <b>Description:</b> This command is used to do a default programming of the NVS / EEPROM in the DUT. Two cfm messages are sent back to the PC as response to this command. The first with Status == RSS_PENDING is sent when the default programming is started and the second with Status=RSS_SUCCESS is sent when the default programming has finished.<br>
*   <b>Command:</b> <i>"NvsDefault <rsbool FactoryDefault>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_AUTO_TEST "SetAutoTest"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_AUTO_TEST<br>
*   <b>Description:</b> This command is used to set the AutoTest parameter in the EEPROM/NVS of the DUT.<br>
*   <b>Command:</b> <i>"SetAutoTest <rsuint8 AutoTest>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GET_AUTO_TEST "GetAutoTest"<br>
*   <b>Opcode:</b> \ref PT_CMD_GET_AUTO_TEST<br>
*   <b>Description:</b> This command is used to read the AutoTest parameter stored in the EEPROM/NVS of the DUT.<br>
*   <b>Command:</b> <i>"GetAutoTest"</i><br>
*   <b>Response:</b> <i>"AutoTest:<rsuint8 AutoTest>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_INITIAL_TEST_MODE "SetInitialTestMode"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_INITIAL_TEST_MODE<br>
*   <b>Description:</b> Set InitialTestMode in NVS. It can be used to automatically set the DUT in testmode at next power up.<br>
*   <b>Command:</b> <i>"SetInitialTestMode <rsbool Value>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_IMAGE_CFG "SetImageCfg"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_IMAGE_CFG<br>
*   <b>Description:</b> This command is used to select active image. MSB selects if COLA application should be enabled<br>
*   <b>Command:</b> <i>"SetImageCfg <rsuint8 ImageCfg>"</i><br>
*   <b>Response:</b> <i>""</i>
*
* - <b>Name:</b> \ref PT_CMD_IS_TARGET_CONNECTED "IsTargetConnected"<br>
*   <b>Opcode:</b> \ref PT_CMD_IS_TARGET_CONNECTED<br>
*   <b>Description:</b> This command checks if the communication with the target is ok<br>
*   <b>Command:</b> <i>"IsTargetConnected"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
*
* \section RF RF Test Commands
*
* - <b>Name:</b> \ref PT_CMD_GET_RSSI "GetRssi"<br>
*   <b>Opcode:</b> \ref PT_CMD_GET_RSSI<br>
*   <b>Description:</b> This command is used to get the current uncompensated RSSI level on the Rx slot of the connection. If more than one connection, the RSSI of the first connection is returned.<br>
*   <b>Command:</b> <i>"GetRssi"</i><br>
*   <b>Response:</b> <i>"Rssi:<rsuint8 Rssi>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GET_RSSI_CONT_RX "GetRssiContRx"<br>
*   <b>Opcode:</b> \ref PT_CMD_GET_RSSI_CONT_RX<br>
*   <b>Description:</b> This command is used to get the current uncompensated RSSI level in continuous RX mode.<br>
*   <b>Command:</b> <i>"GetRssiContRx"</i><br>
*   <b>Response:</b> <i>"Rssi:<rsuint8 Rssi>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GET_RSSI_ADV_BURST_RX "GetRssiAdvBurstRx"<br>
*   <b>Opcode:</b> \ref PT_CMD_GET_RSSI_ADV_BURST_RX<br>
*   <b>Description:</b> This command is used to get the current uncompensated RSSI level with SetAdvBurstMode.<br>
*   <b>Command:</b> <i>"GetRssiAdvBurstRx [rsuint8 CrcSlots]"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status> Rssi:<rsuint8 Rssi> VcoCal:<rsuint16 VcoCal> CrcErrors:<rsuint16 CrcErrors>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_DIVERSITY_MODE "SetDiversityMode"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_DIVERSITY_MODE<br>
*   <b>Description:</b> This command is used to set the DiversityMode temporarily in the RAM (EEPROM in RAM).<br>
*   <b>Command:</b> <i>"SetDiversityMode <PtDiversityModeType DiversityMode>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_ID "SetId"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_ID<br>
*   <b>Description:</b> This command is used to set the RFPI of a base or IPEI of a handset.<br>
*   <b>Command:</b> <i>"SetId <rsuint8 Id[5]>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GET_ID "GetId"<br>
*   <b>Opcode:</b> \ref PT_CMD_GET_ID<br>
*   <b>Description:</b> This command is used to get the RFPI of a base or IPEI of a handset.<br>
*   <b>Command:</b> <i>"GetId"</i><br>
*   <b>Response:</b> <i>"Id[5]:<rsuint8 Id[5]>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_CONTINUOUS_TX "SetContTx"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_CONTINUOUS_TX<br>
*   <b>Description:</b> This command is used to set the DUT in continuous TX mode on the channel specified.<br>
*   <b>Command:</b> <i>"SetContTx <rsuint8 Channel> [rsuint8 Antenna] [rsuint8 Radio]"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_CONTINUOUS_RX "SetContRx"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_CONTINUOUS_RX<br>
*   <b>Description:</b> This command is used to set the DUT in continuous RX mode on the channel specified.<br>
*   <b>Command:</b> <i>"SetContRx <rsuint8 Channel> [rsuint8 Antenna] [rsuint8 Radio]"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_BURST_MODE "SetBurstMode"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_BURST_MODE<br>
*   <b>Description:</b> This command is used to set the DUT in burst TX mode on the channel and antenna specified.<br>
*   <b>Command:</b> <i>"SetBurstMode <rsuint8 Channel> <rsuint8 Antenna>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_ADV_BURST_MODE "SetAdvBurstMode"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_ADV_BURST_MODE<br>
*   <b>Description:</b> This command is used to set the DUT in burst TX mode on the channel and antenna specified.<br>
*   <b>Command:</b> <i>"SetAdvBurstMode <rsuint8 Freq> <PtBurstModeAntType Antenna> [PtBurstModeType Mode] [PtBurstSlotLengthType SlotLength] [PtBurstDataType Data] [PtBurstActiveSlotsType ActiveSlots] [rsuint8 Radio]"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_RF_CLOCK_STATE "SetRfClock"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_RF_CLOCK_STATE<br>
*   <b>Description:</b> This command is used to enable or disable the RF clock inntest mode. Test mode is exited if RfClockEnabled = FALSE<br>
*   <b>Command:</b> <i>"SetRfClock <rsbool RfClockEnabled>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_FIXED_FREQUENCY "SetFixedFrequency"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_FIXED_FREQUENCY<br>
*   <b>Description:</b> This command is used to set the DUT in TX mode on fixed frequency. Used in 2G4 and 5G8.<br>
*   <b>Command:</b> <i>"SetFixedFrequency <rsuint8 Channel>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_DECT_MODE "SetDectMode"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_DECT_MODE<br>
*   <b>Description:</b> This command is used to set the DECT mode of the device.<br>
*   <b>Command:</b> <i>"SetDectMode <PtDectModeType DectMode>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GET_DECT_MODE "GetDectMode"<br>
*   <b>Opcode:</b> \ref PT_CMD_GET_DECT_MODE<br>
*   <b>Description:</b> This command is used to get the current DECT mode of the device.<br>
*   <b>Command:</b> <i>"GetDectMode"</i><br>
*   <b>Response:</b> <i>"DectMode:<PtDectModeType DectMode>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_MODULATION "SetModulation"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_MODULATION<br>
*   <b>Description:</b> This command is used to set the TX modulation.<br>
*   <b>Command:</b> <i>"SetModulation [rsuint8 Modulation]"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GET_MODULATION "GetModulation"<br>
*   <b>Opcode:</b> \ref PT_CMD_GET_MODULATION<br>
*   <b>Description:</b> This command is used to read the TX modulation stored in the NVS.<br>
*   <b>Command:</b> <i>"GetModulation"</i><br>
*   <b>Response:</b> <i>"Modulation:<rsuint8 Modulation>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_RSSI_LIMIT_FP "SetRssiLimitFp"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_RSSI_LIMIT_FP<br>
*   <b>Description:</b> This command is used to set the RSSI limit in the NVS.<br>
*   <b>Command:</b> <i>"SetRssiLimitFp <rsuint8 MaxRssiLevel>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_CLOCK_FREQUENCY "SetFreq"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_CLOCK_FREQUENCY<br>
*   <b>Description:</b> This command is used to set the clock frequency in the NVS and adjust the clock in the SC144xx<br>
*   <b>Command:</b> <i>"SetFreq <rsuint16 Frequency>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GET_CLOCK_FREQUENCY "GetFreq"<br>
*   <b>Opcode:</b> \ref PT_CMD_GET_CLOCK_FREQUENCY<br>
*   <b>Description:</b> This command is used to get the current clock frequency used.<br>
*   <b>Command:</b> <i>"GetFreq"</i><br>
*   <b>Response:</b> <i>"Frequency:<rsuint16 Frequency>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GET_NVS_CLOCK_FREQUENCY "GetFreqNvs"<br>
*   <b>Opcode:</b> \ref PT_CMD_GET_NVS_CLOCK_FREQUENCY<br>
*   <b>Description:</b> This command is used to get clock frequency setting stored in the NVS.<br>
*   <b>Command:</b> <i>"GetFreqNvs"</i><br>
*   <b>Response:</b> <i>"Frequency:<rsuint16 Frequency>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_FP_ENROLL_BIT "SetEnroll"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_FP_ENROLL_BIT<br>
*   <b>Description:</b> This command is used to set the enroll bit in the FP.<br>
*   <b>Command:</b> <i>"SetEnroll <rsbool Enroll>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_ENROLMENT_DATA "SetEnrolmentData"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_ENROLMENT_DATA<br>
*   <b>Description:</b> This command is used to set enrolment data on base and handset. This makes it possible to register a handset on a base via the test interface without any communication over the air interface.<br>
*   <b>Command:</b> <i>"SetEnrolmentData <rsuint8 HandsetNo> <rsuint8 Rfpi[5]> <rsuint8 Ipei[5]> <rsuint8 Uak[16]>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_RF_POWER_LEVEL_PORT "SetRfPowerLevelPort"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_RF_POWER_LEVEL_PORT<br>
*   <b>Description:</b> This command is used to set power level port setting.<br>
*   <b>Command:</b> <i>"SetRfPowerLevelPort <rsuint8 PortSetting>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_RF_POWER_LEVEL_ALGORITHM "SetRfPowerLevelAlgorithm"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_RF_POWER_LEVEL_ALGORITHM<br>
*   <b>Description:</b> This command is used to enable and disable the power control algorithm.<br>
*   <b>Command:</b> <i>"SetRfPowerLevelAlgorithm <rsbool Enabled>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GET_RF_POWER_LEVEL_ALGORITHM "GetRfPowerLevelAlgorithm"<br>
*   <b>Opcode:</b> \ref PT_CMD_GET_RF_POWER_LEVEL_ALGORITHM<br>
*   <b>Description:</b> This command is used to check whether the power control algorithm is enabled.<br>
*   <b>Command:</b> <i>"GetRfPowerLevelAlgorithm"</i><br>
*   <b>Response:</b> <i>"Enabled:<rsbool Enabled>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_DUMMY_BEARER "SetDummyBearer"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_DUMMY_BEARER<br>
*   <b>Description:</b> Sets the slot and frequency for the dummy bearer<br>
*   <b>Command:</b> <i>"SetDummyBearer <rsuint8 Slot> <rsuint8 Freq>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_4x1_POWER_LEVEL "Set4x1PowerLevelParms"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_4x1_POWER_LEVEL<br>
*   <b>Description:</b> Set the NVS parameters for 4x1 (481, 441, ..., LMX4181) RF transmit power level. For some projects this will require RF reinitialization to take effect (e.g. SetTestMode or SetBurstMode).<br>
*   <b>Command:</b> <i>"Set4x1PowerLevelParms <rsuint8 Index> <rsuint16 PA_CTRL1_REG> <rsuint16 TEST_MODE2_REG> <rsuint16 BBADC_CTRL_REG>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_RSSI_LIMIT_FP_LOWER_THRESHOLD "SetRssiLimitFp_LowerThreshold"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_RSSI_LIMIT_FP_LOWER_THRESHOLD<br>
*   <b>Description:</b> This command is used to set the RSSI limit (Lower Threshold) in the NVS.<br>
*   <b>Command:</b> <i>"SetRssiLimitFp_LowerThreshold <rsuint8 MaxRssiLevel_LowerThreshold>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_AC "SetAc"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_AC<br>
*   <b>Description:</b> This command is used to set the access code in the FP.<br>
*   <b>Command:</b> <i>"SetAc <rsuint8 Ac[4]>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GET_AC "GetAc"<br>
*   <b>Opcode:</b> \ref PT_CMD_GET_AC<br>
*   <b>Description:</b> This command is used to get the current access code stored in the FP.<br>
*   <b>Command:</b> <i>"GetAc"</i><br>
*   <b>Response:</b> <i>"Ac[4]:<rsuint8 Ac[4]>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GET_RF_PATCH_LEN "GetRfPatchLength"<br>
*   <b>Opcode:</b> \ref PT_CMD_GET_RF_PATCH_LEN<br>
*   <b>Description:</b> Get the number of activated RF patches.<br>
*   <b>Command:</b> <i>"GetRfPatchLength"</i><br>
*   <b>Response:</b> <i>"PatchLength:<rsuint8 PatchLength>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_RF_PATCH_LEN "SetRfPatchLength"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_RF_PATCH_LEN<br>
*   <b>Description:</b> Set the number of activated RF patches.<br>
*   <b>Command:</b> <i>"SetRfPatchLength <rsuint8 PatchLength>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GET_RF_PATCH "GetRfPatch"<br>
*   <b>Opcode:</b> \ref PT_CMD_GET_RF_PATCH<br>
*   <b>Description:</b> Get an RF patch from NVS. The patch may not be active<br>
*   <b>Command:</b> <i>"GetRfPatch <rsuint8 PatchNumber>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status> ParameterNumber:<rsuint8 ParameterNumber> PatchRegNo:<rsuint8 PatchRegNo> PatchRegVal:<rsuint16 PatchRegVal>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_RF_PATCH "SetRfPatch"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_RF_PATCH<br>
*   <b>Description:</b> Write an RF patch into NVS. Note that for the RF patch to be active, the RF patch length must also be set.<br>
*   <b>Command:</b> <i>"SetRfPatch <rsuint8 PatchNumber> <rsuint8 ParameterNumber> <rsuint8 PatchRegNo> <rsuint16 PatchRegVal>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GET_JDECT_STATE "GetJDectState"<br>
*   <b>Opcode:</b> \ref PT_CMD_GET_JDECT_STATE<br>
*   <b>Description:</b> Get JDect number of active channels<br>
*   <b>Command:</b> <i>"GetJDectState"</i><br>
*   <b>Response:</b> <i>"JDectActiveChannels:<rsuint8 JDectActiveChannels> JDect5chSupport:<rsbool JDect5chSupport>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_JDECT_STATE "SetJDectState"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_JDECT_STATE<br>
*   <b>Description:</b> Set JDect number of active channels. 5 channel mode can always be selected and will not perform PHS scanning. Will return RSS_NO_CAPABILITY if the FP is not configured for Japan DECT mode (use SetDectMode).<br>
*   <b>Command:</b> <i>"SetJDectState <rsuint8 JDectActiveChannels>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
*
* \section BB BB Test Commands
*
* - <b>Name:</b> \ref PT_CMD_SET_BAND_GAP "SetBandGap"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_BAND_GAP<br>
*   <b>Description:</b> This command is used to set/adjust the band gap in the SC144xx and store it in the EEPROM.<br>
*   <b>Command:</b> <i>"SetBandGap <rsuint8 BandGap>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GET_BAND_GAP "GetBandGap"<br>
*   <b>Opcode:</b> \ref PT_CMD_GET_BAND_GAP<br>
*   <b>Description:</b> This command is used to read the band gap setting from the EEPROM.<br>
*   <b>Command:</b> <i>"GetBandGap"</i><br>
*   <b>Response:</b> <i>"BandGap:<rsuint8 BandGap>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_AUDIO_LOOP_BACK "SetAudioLb"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_AUDIO_LOOP_BACK<br>
*   <b>Description:</b> This command is used to request the DUT to enable/disable audio loop back (earpiece on a handset typically).<br>
*   <b>Command:</b> <i>"SetAudioLb <rsbool LoopBack>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_AUDIO_LOOP_BACK_HEADSET "SetAudioLbHeadset"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_AUDIO_LOOP_BACK_HEADSET<br>
*   <b>Description:</b> This command is used to request the DUT to enable/disable audio loop back on the headset.<br>
*   <b>Command:</b> <i>"SetAudioLbHeadset <rsbool LoopBack>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_LED "SetLed"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_LED<br>
*   <b>Description:</b> This command is used to switch a LED on/off.<br>
*   <b>Command:</b> <i>"SetLed <PtLedCmdType Command> <rsuint8 LedId>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
*
* \section GAP GAP Test Commands
*
* - <b>Name:</b> \ref PT_CMD_GAP_LOC_OFF "GapLocOff"<br>
*   <b>Opcode:</b> \ref PT_CMD_GAP_LOC_OFF<br>
*   <b>Description:</b> This command is used to disable location update.<br>
*   <b>Command:</b> <i>"GapLocOff"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GAP_LOC_ON "GapLocOn"<br>
*   <b>Opcode:</b> \ref PT_CMD_GAP_LOC_ON<br>
*   <b>Description:</b> This command is used to enable location update.<br>
*   <b>Command:</b> <i>"GapLocOn"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GAP_AUTH_OFF "GapAuthOff"<br>
*   <b>Opcode:</b> \ref PT_CMD_GAP_AUTH_OFF<br>
*   <b>Description:</b> This command is used to disable authentication.<br>
*   <b>Command:</b> <i>"GapAuthOff"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GAP_AUTH_ON "GapAuthOn"<br>
*   <b>Opcode:</b> \ref PT_CMD_GAP_AUTH_ON<br>
*   <b>Description:</b> This command is used to enable authentication.<br>
*   <b>Command:</b> <i>"GapAuthOn"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GAP_RELEASE "GapRelease"<br>
*   <b>Opcode:</b> \ref PT_CMD_GAP_RELEASE<br>
*   <b>Description:</b> This command is used to release the current connection to the GAP tester.<br>
*   <b>Command:</b> <i>"GapRelease"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GAP_TERM_ACCESS_RIGHTS "GapTerm"<br>
*   <b>Opcode:</b> \ref PT_CMD_GAP_TERM_ACCESS_RIGHTS<br>
*   <b>Description:</b> This command is used to terminate a registeration.<br>
*   <b>Command:</b> <i>"GapTerm"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GAP_REVOKE_ACCESS_RIGHTS "GapRevoke"<br>
*   <b>Opcode:</b> \ref PT_CMD_GAP_REVOKE_ACCESS_RIGHTS<br>
*   <b>Description:</b> This command is used to revoke a registeration.<br>
*   <b>Command:</b> <i>"GapRevoke"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GAP_TERM_ACCESS_RIGHTS_ALL "GapTermAll"<br>
*   <b>Opcode:</b> \ref PT_CMD_GAP_TERM_ACCESS_RIGHTS_ALL<br>
*   <b>Description:</b> This command is used to terminate all registerations.<br>
*   <b>Command:</b> <i>"GapTermAll"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GAP_REVOKE_ACCESS_RIGHTS_ALL "GapRevokeAll"<br>
*   <b>Opcode:</b> \ref PT_CMD_GAP_REVOKE_ACCESS_RIGHTS_ALL<br>
*   <b>Description:</b> This command is used to revoke all registerations.<br>
*   <b>Command:</b> <i>"GapRevokeAll"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GAP_START_AUTH "GapStartAuth"<br>
*   <b>Opcode:</b> \ref PT_CMD_GAP_START_AUTH<br>
*   <b>Description:</b> This command is used to start authentication when testing TBR22.<br>
*   <b>Command:</b> <i>"GapStartAuth"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
*
* \section CAT-iq CAT-iq Test Commands
*
* - <b>Name:</b> \ref PT_CMD_SET_PP_CAPABILITY "SetPpCapability"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_PP_CAPABILITY<br>
*   <b>Description:</b> This command is used to set all bits except the Codec list in the PpCapability var stored in the NVS for the PP device selected.<br>
*   <b>Command:</b> <i>"SetPpCapability <rsuint8 HandsetNo> <rsbool KnownEmc> <rsbool WB> <rsbool EWB> <rsbool HeadsetManagement> <rsbool EarlyEncryption> <rsuint8 EchoParameter> [rsuint32 PMID]"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GET_PP_CAPABILITY "GetPpCapability"<br>
*   <b>Opcode:</b> \ref PT_CMD_GET_PP_CAPABILITY<br>
*   <b>Description:</b> This command is used to get all bits except the Codec list of the PpCapability var stored in the NVS for the PP device selected.<br>
*   <b>Command:</b> <i>"GetPpCapability <rsuint8 HandsetNo>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status> KnownEmc:<rsbool KnownEmc> WB:<rsbool WB> EWB:<rsbool EWB> HeadsetManagement:<rsbool HeadsetManagement> EarlyEncryption:<rsbool EarlyEncryption> EchoParameter:<rsuint8 EchoParameter> PMID:<rsuint32 PMID>"</i>
*
* - <b>Name:</b> \ref PT_CMD_SET_PP_CAPABILITY_CODEC_LIST "SetPpCapabilityCodecList"<br>
*   <b>Opcode:</b> \ref PT_CMD_SET_PP_CAPABILITY_CODEC_LIST<br>
*   <b>Description:</b> This command is used to set the codec list in the PpCapability var stored in the NVS for the PP device selected.<br>
*   <b>Command:</b> <i>"SetPpCapabilityCodecList <rsuint8 HandsetNo> <rsuint8 CodecListLength> <PtSwCodecType CodecList[]>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_CMD_GET_PP_CAPABILITY_CODEC_LIST "GetPpCapabilityCodecList"<br>
*   <b>Opcode:</b> \ref PT_CMD_GET_PP_CAPABILITY_CODEC_LIST<br>
*   <b>Description:</b> This command is used to get the codec list of the PpCapability var stored in the NVS for the PP device selected.<br>
*   <b>Command:</b> <i>"GetPpCapabilityCodecList <rsuint8 HandsetNo>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status> CodecListLength:<rsuint8 CodecListLength> CodecList:<PtSwCodecType CodecList[]>"</i>
*
*
* \section OTP OTP Test Commands
*
* - <b>Name:</b> \ref PT_GET_OTP_INFO "GetOtpInfo"<br>
*   <b>Opcode:</b> \ref PT_GET_OTP_INFO<br>
*   <b>Description:</b> Get OTP information (flash serial number, size of OTP area, lock status).<br>
*   <b>Command:</b> <i>"GetOtpInfo"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status> Locked:<rsbool Locked> OtpSize:<rsuint16 OtpSize> Length:<rsuint8 Length> Data:<rsuint8 Data[]>"</i>
*
* - <b>Name:</b> \ref PT_SET_OTP_COMMIT "SetOtpCommit"<br>
*   <b>Opcode:</b> \ref PT_SET_OTP_COMMIT<br>
*   <b>Description:</b> Commit HW adjustment parameters from NVS to OTP. This is typically Rfpi/Ipei, BmcModulationDeviation, BmcDefaultFrequency and Bandgap.<br>
*   <b>Command:</b> <i>"SetOtpCommit <rsuint8 Password>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_SET_OTP_LOCK "SetOtpLock"<br>
*   <b>Opcode:</b> \ref PT_SET_OTP_LOCK<br>
*   <b>Description:</b> Lock the OTP area in the flash.<br>
*   <b>Command:</b> <i>"SetOtpLock <rsuint8 Password>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
* - <b>Name:</b> \ref PT_GET_OTP_DATA "GetOtpData"<br>
*   <b>Opcode:</b> \ref PT_GET_OTP_DATA<br>
*   <b>Description:</b> Read data from flash OTP area.<br>
*   <b>Command:</b> <i>"GetOtpData <rsuint32 Address> <rsuint8 Length>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status> Address:<rsuint32 Address> Length:<rsuint8 Length> Data:<rsuint8 Data[]>"</i>
*
* - <b>Name:</b> \ref PT_SET_OTP_DATA "SetOtpData"<br>
*   <b>Opcode:</b> \ref PT_SET_OTP_DATA<br>
*   <b>Description:</b> Write data to the flash OTP area.<br>
*   <b>Command:</b> <i>"SetOtpData <rsuint32 Address> <rsuint8 Length> <rsuint8 Data[]>"</i><br>
*   <b>Response:</b> <i>"Status:<RsStatusType Status>"</i>
*
*
*
*/
/// This enum defines the DECT types possible.
typedef enum RSENUMTAG(PtDectModeType)
{
  EU_DECT = 0x00, //!< Set to Europe DECT mode.
  US_DECT = 0x01, //!< Set to USA DECT mode.
  SA_DECT = 0x02, //!< Set to South America DECT mode.
  TAIWAN_DECT = 0x03, //!< Set to Taiwan DECT mode.
  MALAYSIA_DECT = 0x04, //!< Set to Malaysia DECT mode.
  CHINA_DECT = 0x05, //!< Set to China DECT mode.
  THAILAND_DECT = 0x06, //!< Set to Thailand DECT mode.
  BRAZIL_DECT = 0x07, //!< Set to Brazil DECT mode.
  US_DECT_EXT_FREQ = 0x08, //!< Set to US DECT mode with extended freq band.
  KOREAN_DECT = 0x09, //!< Set to Korean DECT mode.
  JAPAN_DECT = 0x0A, //!< Set to Japan DECT mode with 2 channels. In PP this is used for both 2 and 5 channel mode
  JAPAN_DECT_5CH = 0x0B, //!< Set FP to Japan DECT mode with PHS scanning enabled to allow use of 5 channels.
  CHILE_DECT = 0x0C, //!< Set to Chile DECT mode.
  US_DECT_2 = 0x0D, //!< Set to USA DECT mode, but with alternate settings for frequency offset and used carriers.
  SA_DECT_2 = 0x0E, //!< Set to SA DECT mode, but offset by one carrier.
  BRAZIL_DECT_2 = 0x0F, //!< Set to BRAZIL DECT mode, but with alternate settings for frequency offset and used carriers.
  THAILAND_DECT_2 = 0x10, //!< Set to THAILAND DECT mode, but with alternate settings for frequency offset and used carriers.
  US_DECT_INVERTED = 0x11, //!< Set to inverted US DECT mode (channel 0 is at 1921 MHz).
  UNKNOWN_DECT_MODE = 0xFF  
} RSENUM8(PtDectModeType);

/// This enum defines the possible values for diversity mode.
typedef enum RSENUMTAG(PtDiversityModeType)
{
  PT_DIVERSITY_MODE_ENABLED = 0x00, //!< Enable diversity mode
  PT_DIVERSITY_MODE_ANTENNA_1 = 0x01, //!< Disable diversity mode. Only use antenna 1
  PT_DIVERSITY_MODE_ANTENNA_2 = 0x02  //!< Disable diversity mode. Only use antenna 2
} RSENUM8(PtDiversityModeType);

/// This enum defines the possible values for multi RF band search mode.
typedef enum RSENUMTAG(PtMultiBandModeType)
{
  PT_MULTI_BAND_MODE_DISABLED = 0x00, //!< Multi band search mode disabled. Frequency band is defined by SetDectMode.
  PT_MULTI_BAND_MODE_ENROLLMENT = 0x01, //!< Search in all frequency bands, but only during enrollment. Search is started in the band defined by SetDectMode.
  PT_MULTI_BAND_MODE_ALWAYS = 0x02, //!< Search in all frequency bands, every time search is performed. Search is started in the band defined by SetDectMode.
  PT_MULTI_BAND_MODE_INVALID = 0xFF  //!< Invalid multi band mode
} RSENUM8(PtMultiBandModeType);

/// This enum defines the possible values for burst mode Antenna.
typedef enum RSENUMTAG(PtBurstModeAntType)
{
  ABURST_ANT1 = 0x01, //!< Antenna 1
  ABURST_ANT2 = 0x02, //!< Antenna 2
  ABURST_NO_ANT = 0x10  //!< No antenna active
} RSENUM8(PtBurstModeAntType);

/// This enum defines the possible values for burst mode type.
typedef enum RSENUMTAG(PtBurstModeType)
{
  ABURST_TX = 0x00, //!< Only TX burst slots
  ABURST_RX = 0x01, //!< Only RX burst slots
  ABURST_TX_RX = 0x02  //!< Both TX and RX burst slots
} RSENUM8(PtBurstModeType);

/// This enum defines the possible values for active burst mode slots.
typedef enum RSENUMTAG(PtBurstActiveSlotsType)
{
  ABURST_SINGLE = 0x00, //!< Burst on a single RX and/or TX slot
  ABURST_HALF = 0x01, //!< Burst on all slots in the TX and/or RX half
  ABURST_ALL = 0x02  //!< Burst on all slots, e.g. TX burst also in RX half.
} RSENUM8(PtBurstActiveSlotsType);

/// This enum defines the possible values for burst mode A and B field content.
typedef enum RSENUMTAG(PtBurstDataType)
{
  ABURST_RANDOM = 0x00, //!< Static pseudo random data
  ABURST_FIG31 = 0x01, //!< Figure 31
  ABURST_0F = 0x02, //!< Fill with 0F/00/FF/0F
  ABURST_UNMODULATED = 0x03, //!< Unmodulated
  ABURST_PROTECTED = 0x04  //!< Used with ABURST_RX only, to receive protected B field. GetRssiAdvBurstRx can be used to get number of CRC errors.
} RSENUM8(PtBurstDataType);

/// This enum defines the possible slot types
typedef enum RSENUMTAG(PtBurstSlotLengthType)
{
  ABURST_SLOT_FULL = 0x00, //!< Full slot (40 byte B field)
  ABURST_SLOT_LONG = 0x01, //!< Long slot (80 byte B field)
  ABURST_SLOT_LONG_672 = 0x02, //!< Long slot (80 byte B field and 32 bit extra CRC)
  ABURST_SLOT_DOUBLE = 0x03, //!< Double slot (100 byte B field)
  ABURST_SLOT_HALF = 0x04, //!< Half slot (20 byte B field)
  ABURST_SLOT_DUMMY = 0x05  //!< Dummy slot (0 byte B field)
} RSENUM8(PtBurstSlotLengthType);

/// This enum defines the audio tone test commands supported.
typedef enum RSENUMTAG(PtAmToneTestCmdType)
{
  PT_AM_TONE_STOP = 0x00, //!< Stop the tone generation.
  PT_AM_TONE_500HZ = 0x01, //!< Play 500 Hz tone.
  PT_AM_TONE_1000HZ = 0x02, //!< Play 1000 Hz tone.
  PT_AM_TONE_3000HZ = 0x03, //!< Play 3000 Hz tone.
  PT_AM_TONE_6000HZ = 0x04, //!< Play 6000 Hz tone.
  PT_AM_TONE_350HZ = 0x05, //!< Play 350 Hz tone.
  PT_AM_TONE_700HZ = 0x06, //!< Play 700 Hz tone.
  PT_AM_TONE_INVALID = 0xFF  
} RSENUM8(PtAmToneTestCmdType);

/// This enum defines the LED test commands supported.
typedef enum RSENUMTAG(PtLedCmdType)
{
  PT_LED_OFF = 0x00, //!< Switch off a LED.
  PT_LED_ON = 0x01, //!< Switch on a LED.
  PT_LED_INVALID = 0xFF  
} RSENUM8(PtLedCmdType);

/// This enum defines the back light commands supported.
typedef enum RSENUMTAG(PtBacklightCmdType)
{
  PT_BACKLIGHT_OFF = 0x00, //!< Switch off the backlight.
  PT_BACKLIGHT_ON = 0x01, //!< Switch on the backlight.
  PT_BACKLIGHT_INVALID = 0xFF  
} RSENUM8(PtBacklightCmdType);

/// This enum is used to identify the device for which the backlight command is used
typedef enum RSENUMTAG(PtBacklightIdType)
{
  PT_BACKLIGHT_ALL = 0x00, //!< All backlights (default).
  PT_BACKLIGHT_DISPLAY = 0x01, //!< The backlight for the display.
  PT_BACKLIGHT_KEYPAD = 0x02, //!< The backlight for the keypad.
  PT_BACKLIGHT_EXT_KEYPAD = 0x03, //!< The backlight for an external keypad.
  PT_BACKLIGHT_GROUP_INVALID = 0xFF  
} RSENUM8(PtBacklightIdType);

/// This enum defines the display test commands supported.
typedef enum RSENUMTAG(PtDisplayTestCmdType)
{
  PT_DISPLAY_CLEAR = 0x00, //!< Clear the display.
  PT_DISPLAY_INVALID = 0xFF  
} RSENUM8(PtDisplayTestCmdType);

/// This enum defines different logical audio devices
typedef enum RSENUMTAG(PtFEDevice)
{
  PT_AU_FE_EARPIECE_LSR = 0x00, //!< Earpieces LSR device
  PT_AU_FE_EARPIECE_MIC = 0x01, //!< Earpieces MIC device
  PT_AU_FE_HANDSFREE_LSR = 0x02, //!< Handsfree LSR device
  PT_AU_FE_HANDSFREE_MIC = 0x03, //!< Handsfree MIC device
  PT_AU_FE_HEADSET_LSR = 0x04, //!< Headset LSR Device
  PT_AU_FE_HEADSET_MIC = 0x05  //!< Headset MIC Device
} RSENUM8(PtFEDevice);

/// This enum defines different FE modes
typedef enum RSENUMTAG(PtFEMode)
{
  PT_AU_FE_OFF = 0x00, //!< Off.
  PT_AU_FE_SE_P = 0x01, //!< Single ended +.
  PT_AU_FE_SE_N = 0x02, //!< Single ended -.
  PT_AU_FE_DIFF = 0x03, //!< Differential
  PT_AU_FE_CLASSD_OR_MIC_HS = 0x04  //!< CLASSD differential output or MIC HS.
} RSENUM8(PtFEMode);

/// This enum defines the codec types.
typedef enum RSENUMTAG(PtSwCodecType)
{
  PT_SW_CT_NONE = 0x00, 
  PT_SW_CT_USER_SPECIFIC_32 = 0x01, //!< Information transfer rate 32 kbit/s
  PT_SW_CT_G726 = 0x02, //!< ADPCM
  PT_SW_CT_G722 = 0x03, //!< WB
  PT_SW_CT_G711A = 0x04, //!< A-law
  PT_SW_CT_G711U = 0x05, //!< u-law
  PT_SW_CT_G7291 = 0x06, //!< G.729.1
  PT_SW_CT_MP4_32 = 0x07, //!< MPEG-4 ER AAC-LD, information transfer rate 32 kbit/s
  PT_SW_CT_MP4_64 = 0x08, //!< MPEG-4 ER AAC-LD, information transfer rate 64 kbit/s
  PT_SW_CT_USER_SPECIFIC_64 = 0x09  //!< Information transfer rate 64 kbit/s
} RSENUM8(PtSwCodecType);

/// 
#ifndef PT_DLL_TL_TYPE
  #define PT_DLL_TL_TYPE PT_TL_TYPE_SOCKET
#endif

/// The default REPS name used by the RtxProdTest.dll.
#ifndef PT_DLL_REPS_NAME
#  define PT_DLL_REPS_NAME "RtxEaiPortServer"
#endif

/// The default TL type used by the RtxProdTest.dll.
#ifndef PT_DLL_TL_TYPE
  #define PT_DLL_TL_TYPE PT_TL_TYPE_UART_HDLC
#endif

/// The default BAUD rate used by the RtxProdTest.dll.
#ifndef PT_DLL_UART_BAUDRATE
  #define PT_DLL_UART_BAUDRATE 115200
#endif

/// The default REPS name used by the RtxProdTest.dll.
#ifndef PT_DLL_REPS_NAME
#  define PT_DLL_REPS_NAME "RtxEaiPortServer"
#endif

/** \name Project Test Command Opcodes
* The following Project test commands are defined.*/ 
//@{

/*! This command is used to test the external IO connections of the CVM480 module <br>
Parameters: none <br>
Returns: \ref PtIoTestCfmType <br>
Bat file: IoTest.bat */
#define PT_CMD_IO_TEST 0x00D0

/// \ref PT_CMD_IO_TEST CFM parameter type.
typedef struct
{
  rsuint8 Result; //!< Returns 0 if the IO test passed or the number of the test step that failed if the IO test did not pass.
} PtIoTestCfmType;

/*! This command is used to read the current value of ADC2. <br>
Parameters: none <br>
Returns: \ref PtGetAdc2CfmType <br>
Bat file: GetAdc2.bat */
#define PT_CMD_GET_ADC2 0x00D1

/// \ref PT_CMD_GET_ADC2 CFM parameter type.
typedef struct
{
  rsuint16 AdcValue; //!< The ADC value.
} PtGetAdc2CfmType;

/*! This command is used to set serial backdrive protection value of SPI and UART. <br>
Parameters: \ref PtSetSerialBackdriveProtectionReqType <br>
Returns: none <br>
Bat file: SetSerialBackdriveProtection.bat */
#define PT_CMD_SET_SERIAL_BACKDRIVE_PROTECTION 0x00D2

/// \ref PT_CMD_SET_SERIAL_BACKDRIVE_PROTECTION REQ parameter type.
typedef struct
{
  rsuint8 ProtectMask; //!< Enable the Serial Backdrive protection. BIT0=SPI, BIT1=UART
} PtSetSerialBackdriveProtectionReqType;


//@} end of Project

/// Enables the Common test commands.
#ifndef PT_COMMON_TEST
  #define PT_COMMON_TEST 1
#endif

/** \name Common Test Command Opcodes
* The following Common test commands are defined.*/ 
//@{

/*! This command is used to read the SW version number. <br>
Parameters: none <br>
Returns: \ref PtGetVersionCfmType <br>
Bat file: GetVersion.bat */
#define PT_CMD_GET_SW_VERSION 0x0016

/// \ref PT_CMD_GET_SW_VERSION CFM parameter type.
typedef struct
{
  rsuint16 Version; //!< The version number (BCD coded). E.g. 0x1234 = v1234 (version 12.34).
  rsuint16 SubVersion; //!< Sub version / branch number (BCD coded).
  rsuint16 Build; //!< Build number.
} PtGetVersionCfmType;

/*! Used to request the DUT to reset. The DUT waits for the EE write cache to become empty before it resets. <br>
Parameters: none <br>
Returns: none <br>
Bat file: Reset.bat */
#define PT_CMD_SW_RESET 0x0028

/*! This command is used to request the SW link date and time. <br>
Parameters: none <br>
Returns: \ref PtGetLinkDateCfmType <br>
Bat file: GetLinkDate.bat */
#define PT_CMD_GET_SW_LINK_DATE 0x0029

/// \ref PT_CMD_GET_SW_LINK_DATE CFM parameter type.
typedef struct
{
  rsuint8 Year; //!< BCD coded: [0;99] (2000-2099).
  rsuint8 Month; //!< BCD coded [1;12] (jan-dec).
  rsuint8 Day; //!< BCD coded: day of month [1;31]
  rsuint8 Hour; //!< BCD coded: [0:23]
  rsuint8 Minute; //!< BCD coded: [0:59]
} PtGetLinkDateCfmType;

/*! This command is used to get the current state of the write cache in the EEPROM driver. <br>
Parameters: none <br>
Returns: \ref PtGetEeCacheStateCfmType <br>
Bat file: GetEeCacheState.bat */
#define PT_CMD_GET_EE_CACHE_STATE 0x004C

/// \ref PT_CMD_GET_EE_CACHE_STATE CFM parameter type.
typedef struct
{
  rsbool CacheEmpty; //!< TRUE(1): The cache is empty; FALSE(0): the cache is not empty.
} PtGetEeCacheStateCfmType;

/*! This command is used to read some data form the part of the EEPROM reserved for the production. <br>
Parameters: \ref PtGetProdDataReqType <br>
Returns: \ref PtGetProdDataCfmType <br>
Bat file: GetProdData.bat */
#define PT_CMD_GET_PROD_DATA 0x009C

/// \ref PT_CMD_GET_PROD_DATA REQ parameter type.
typedef struct
{
  rsuint8 Length; //!< The number of bytes to read from the production data in the EEPROM.
  rsuint8 DataOffset; //!< The offset of the first byte to read from the production data in the EEPROM.
} PtGetProdDataReqType;

/// \ref PT_CMD_GET_PROD_DATA CFM parameter type.
typedef struct
{
  rsuint8 Data[1]; //!< The data read from the production data in the EEPROM.
} PtGetProdDataCfmType;

/*! This command is used to write some data to the part of the EEPROM reserved for the production. <br>
Parameters: \ref PtSetProdDataReqType <br>
Returns: \ref PtSetProdDataCfmType <br>
Bat file: SetProdData.bat */
#define PT_CMD_SET_PROD_DATA 0x009D

/// \ref PT_CMD_SET_PROD_DATA REQ parameter type.
typedef struct
{
  rsuint8 Length; //!< The number of bytes to write to the production data in the EEPROM.
  rsuint8 DataOffset; //!< The offset of the first byte to read from the production data in the EEPROM.
  rsuint8 Data[1]; //!< The data to be written to the production data in the EEPROM.
} PtSetProdDataReqType;

/// \ref PT_CMD_SET_PROD_DATA CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetProdDataCfmType;

/*! This command is used to write data to the NVS (EEPROM). <br>
Parameters: \ref PtSetNvsReqType <br>
Returns: \ref PtSetNvsCfmType <br>
Bat file: SetNvs.bat */
#define PT_CMD_SET_NVS 0x0100

/// \ref PT_CMD_SET_NVS REQ parameter type.
typedef struct
{
  rsuint32 Address; //!< The address of the first byte to write to in the NVS.
  rsuint8 Length; //!< The number of bytes to write to the NVS.
  rsuint8 Data[1]; //!< The data that should be written to the NVS.
} PtSetNvsReqType;

/// \ref PT_CMD_SET_NVS CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetNvsCfmType;

/*! This command is used to read data from the NVS. <br>
Parameters: \ref PtGetNvsReqType <br>
Returns: \ref PtGetNvsCfmType <br>
Bat file: GetNvs.bat */
#define PT_CMD_GET_NVS 0x0101

/// \ref PT_CMD_GET_NVS REQ parameter type.
typedef struct
{
  rsuint32 Address; //!< The address of the first byte to read.
  rsuint8 Length; //!< The number of bytes to read from the NVS.
} PtGetNvsReqType;

/// \ref PT_CMD_GET_NVS CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
  rsuint32 Address; //!< The address of the first byte read from the NVS.
  rsuint8 Length; //!< The number of bytes read from the NVS.
  rsuint8 Data[1]; //!< The data read from the NVS.
} PtGetNvsCfmType;

/*! This command is used to do a default programming of the NVS / EEPROM in the DUT. Two cfm messages are sent back to the PC as response to this command. The first with Status == RSS_PENDING is sent when the default programming is started and the second with Status=RSS_SUCCESS is sent when the default programming has finished. <br>
Parameters: \ref PtNvsDefaultReqType <br>
Returns: \ref PtNvsDefaultCfmType <br>
Bat file: NvsDefault.bat */
#define PT_CMD_NVS_DEFAULT 0x0102

/// \ref PT_CMD_NVS_DEFAULT REQ parameter type.
typedef struct
{
  rsbool FactoryDefault; //!< TRUE(1) defaults the adjustment parameters (factory settings); FALSE(0): preserves the adjustment parameters.
} PtNvsDefaultReqType;

/// \ref PT_CMD_NVS_DEFAULT CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_PENDING(0x11) followed by RSS_SUCCESS(0x00) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtNvsDefaultCfmType;

/*! This command is used to set the AutoTest parameter in the EEPROM/NVS of the DUT. <br>
Parameters: \ref PtSetAutoTestReqType <br>
Returns: \ref PtSetAutoTestCfmType <br>
Bat file: SetAutoTest.bat */
#define PT_CMD_SET_AUTO_TEST 0x0107

/// \ref PT_CMD_SET_AUTO_TEST REQ parameter type.
typedef struct
{
  rsuint8 AutoTest; //!< The new value for the AutoTest parameter.
} PtSetAutoTestReqType;

/// \ref PT_CMD_SET_AUTO_TEST CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetAutoTestCfmType;

/*! This command is used to read the AutoTest parameter stored in the EEPROM/NVS of the DUT. <br>
Parameters: none <br>
Returns: \ref PtGetAutoTestCfmType <br>
Bat file: GetAutoTest.bat */
#define PT_CMD_GET_AUTO_TEST 0x0108

/// \ref PT_CMD_GET_AUTO_TEST CFM parameter type.
typedef struct
{
  rsuint8 AutoTest; //!< The value of the AutoTest parameter.
} PtGetAutoTestCfmType;

/*! Set InitialTestMode in NVS. It can be used to automatically set the DUT in testmode at next power up. <br>
Parameters: \ref PtSetInitialTestModeReqType <br>
Returns: \ref PtSetInitialTestModeCfmType <br>
Bat file: SetInitialTestMode.bat */
#define PT_CMD_SET_INITIAL_TEST_MODE 0x0109

/// \ref PT_CMD_SET_INITIAL_TEST_MODE REQ parameter type.
typedef struct
{
  rsbool Value; //!< Value = 0(FALSE): Normal mode; Mode > 0 (TRUE): Test mode enabled. On PP's the mode is also used to set the test carrier used. [0x01-0x09] uses dummy RFPI [00 00 00 10 00; 00 00 00 90 00]. 0x0F uses the LockToFp[5] parameter in the EEPROM. Value = 0xfd: Enable CLK100 output but stay in normal mode. Value = 0xfe: Enable CLK100 output ad go to testmode. Value = 0xfc: One shot testmode. NVS will be set to 0 after the boot.
} PtSetInitialTestModeReqType;

/// \ref PT_CMD_SET_INITIAL_TEST_MODE CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetInitialTestModeCfmType;

/*! This command is used to select active image. MSB selects if COLA application should be enabled <br>
Parameters: \ref PtSetImageCfgReqType <br>
Returns: none <br>
Bat file: SetImageCfg.bat */
#define PT_CMD_SET_IMAGE_CFG 0x010B

/// \ref PT_CMD_SET_IMAGE_CFG REQ parameter type.
typedef struct
{
  rsuint8 ImageCfg; //!< example: Mode = 00 selects image 0.  Mode = 80 selects image 0 + COLAapp
} PtSetImageCfgReqType;

/*! This command checks if the communication with the target is ok <br>
Parameters: none <br>
Returns: \ref PtIsTargetConnectedCfmType <br>
Bat file: IsTargetConnected.bat */
#define PT_CMD_IS_TARGET_CONNECTED 0x010C

/// \ref PT_CMD_IS_TARGET_CONNECTED CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtIsTargetConnectedCfmType;


//@} end of Common

/// Enables the DECT RF test commands.
#ifndef PT_DECT_RF_TEST
  #define PT_DECT_RF_TEST 1
#endif

/** \name RF Test Command Opcodes
* The following RF test commands are defined.*/ 
//@{

/*! This command is used to get the current uncompensated RSSI level on the Rx slot of the connection. If more than one connection, the RSSI of the first connection is returned. <br>
Parameters: none <br>
Returns: \ref PtGetRssiCfmType <br>
Bat file: GetRssi.bat */
#define PT_CMD_GET_RSSI 0x000A

/// \ref PT_CMD_GET_RSSI CFM parameter type.
typedef struct
{
  rsuint8 Rssi; //!< Uncompensated RSSI level. 0xFF is returned if no connection has been established.
} PtGetRssiCfmType;

/*! This command is used to get the current uncompensated RSSI level in continuous RX mode. <br>
Parameters: none <br>
Returns: \ref PtGetRssiContRxCfmType <br>
Bat file: GetRssiContRx.bat */
#define PT_CMD_GET_RSSI_CONT_RX 0x000F

/// \ref PT_CMD_GET_RSSI_CONT_RX CFM parameter type.
typedef struct
{
  rsuint8 Rssi; //!< Uncompensated RSSI level.
} PtGetRssiContRxCfmType;

/*! This command is used to get the current uncompensated RSSI level with SetAdvBurstMode. <br>
Parameters: \ref PtGetRssiAdvBurstRxReqType <br>
Returns: \ref PtGetRssiAdvBurstRxCfmType <br>
Bat file: GetRssiAdvBurstRx.bat */
#define PT_CMD_GET_RSSI_ADV_BURST_RX 0x021f

/// \ref PT_CMD_GET_RSSI_ADV_BURST_RX REQ parameter type.
typedef struct
{
  rsuint8 CrcSlots; //!< Number of slots to test CRC in (use with ABURST_PROTECTED). If 0 only Rssi is returned.
} PtGetRssiAdvBurstRxReqType;

/// \ref PT_CMD_GET_RSSI_ADV_BURST_RX CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
  rsuint8 Rssi; //!< Uncompensated RSSI level.
  rsuint16 VcoCal; //!< Returns the VCO calibration result
  rsuint16 CrcErrors; //!< Number of CRC errors. Valid with ABURST_PROTECTED
} PtGetRssiAdvBurstRxCfmType;

/*! This command is used to set the DiversityMode temporarily in the RAM (EEPROM in RAM). <br>
Parameters: \ref PtSetDiversityModeReqType <br>
Returns: \ref PtSetDiversityModeCfmType <br>
Bat file: SetDiversityMode.bat */
#define PT_CMD_SET_DIVERSITY_MODE 0x0013

/// \ref PT_CMD_SET_DIVERSITY_MODE REQ parameter type.
typedef struct
{
  PtDiversityModeType DiversityMode; //!< The Diversity mode.
} PtSetDiversityModeReqType;

/// \ref PT_CMD_SET_DIVERSITY_MODE CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetDiversityModeCfmType;

/*! This command is used to set the RFPI of a base or IPEI of a handset. <br>
Parameters: \ref PtSetIdReqType <br>
Returns: \ref PtSetIdCfmType <br>
Bat file: SetId.bat */
#define PT_CMD_SET_ID 0x001B

/// \ref PT_CMD_SET_ID REQ parameter type.
typedef struct
{
  rsuint8 Id[5]; //!< The RFPI/IPEI.
} PtSetIdReqType;

/// \ref PT_CMD_SET_ID CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetIdCfmType;

/*! This command is used to get the RFPI of a base or IPEI of a handset. <br>
Parameters: none <br>
Returns: \ref PtGetIdCfmType <br>
Bat file: GetId.bat */
#define PT_CMD_GET_ID 0x001C

/// \ref PT_CMD_GET_ID CFM parameter type.
typedef struct
{
  rsuint8 Id[5]; //!< The RFPI/IPEI.
} PtGetIdCfmType;

/*! This command is used to set the DUT in continuous TX mode on the channel specified. <br>
Parameters: \ref PtSetContTxReqType <br>
Returns: \ref PtSetContTxCfmType <br>
Bat file: SetContTx.bat */
#define PT_CMD_SET_CONTINUOUS_TX 0x002B

/// \ref PT_CMD_SET_CONTINUOUS_TX REQ parameter type.
typedef struct
{
  rsuint8 Channel; //!< The channel to transmit on.
  rsuint8 Antenna; //!< The antenna to transmit on. 0 for default value usually from NVS DiversityMode (set with SetDiversityMode). 1 for antenna 1, etc. For PP the argument is currently not used, NVS setting is always used.
  rsuint8 Radio; //!< The radio to transmit on. Ignored on blind slot projects. 0/1 on zero-blind slot projects
} PtSetContTxReqType;

/// \ref PT_CMD_SET_CONTINUOUS_TX CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetContTxCfmType;

/*! This command is used to set the DUT in continuous RX mode on the channel specified. <br>
Parameters: \ref PtSetContRxReqType <br>
Returns: \ref PtSetContRxCfmType <br>
Bat file: SetContRx.bat */
#define PT_CMD_SET_CONTINUOUS_RX 0x002E

/// \ref PT_CMD_SET_CONTINUOUS_RX REQ parameter type.
typedef struct
{
  rsuint8 Channel; //!< The channel to receive on.
  rsuint8 Antenna; //!< The antenna to receive on. 0 for default value usually from NVS DiversityMode. 1 for antenna 1, etc. For PP this argument is currently ignored.
  rsuint8 Radio; //!< The radio to receive on. Ignored on blind slot projects. 0/1 on zero-blind slot projects
} PtSetContRxReqType;

/// \ref PT_CMD_SET_CONTINUOUS_RX CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetContRxCfmType;

/*! This command is used to set the DUT in burst TX mode on the channel and antenna specified. <br>
Parameters: \ref PtSetBurstModeReqType <br>
Returns: \ref PtSetBurstModeCfmType <br>
Bat file: SetBurstMode.bat */
#define PT_CMD_SET_BURST_MODE 0x002F

/// \ref PT_CMD_SET_BURST_MODE REQ parameter type.
typedef struct
{
  rsuint8 Channel; //!< The channel to transmit on.
  rsuint8 Antenna; //!< The antenna to transmit on.
} PtSetBurstModeReqType;

/// \ref PT_CMD_SET_BURST_MODE CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetBurstModeCfmType;

/*! This command is used to set the DUT in burst TX mode on the channel and antenna specified. <br>
Parameters: \ref PtSetAdvBurstModeReqType <br>
Returns: \ref PtSetAdvBurstModeCfmType <br>
Bat file: SetAdvBurstMode.bat */
#define PT_CMD_SET_ADV_BURST_MODE 0x0030

/// \ref PT_CMD_SET_ADV_BURST_MODE REQ parameter type.
typedef struct
{
  rsuint8 Freq; //!< The frequency to transmit on.
  PtBurstModeAntType Antenna; //!< The antenna to transmit on.
  PtBurstModeType Mode; //!< Burst mode type
  PtBurstSlotLengthType SlotLength; //!< Length of the burst slot
  PtBurstDataType Data; //!< A and B field content
  PtBurstActiveSlotsType ActiveSlots; //!< Select which slots to burst on
  rsuint8 Radio; //!< Select radio
} PtSetAdvBurstModeReqType;

/// \ref PT_CMD_SET_ADV_BURST_MODE CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetAdvBurstModeCfmType;

/*! This command is used to enable or disable the RF clock inntest mode. Test mode is exited if RfClockEnabled = FALSE <br>
Parameters: \ref PtSetRfClockReqType <br>
Returns: \ref PtSetRfClockCfmType <br>
Bat file: SetRfClock.bat */
#define PT_CMD_SET_RF_CLOCK_STATE 0x0040

/// \ref PT_CMD_SET_RF_CLOCK_STATE REQ parameter type.
typedef struct
{
  rsbool RfClockEnabled; //!< TRUE (1): the RF clock is enabled; FALSE (0): the RF clock is disabled.
} PtSetRfClockReqType;

/// \ref PT_CMD_SET_RF_CLOCK_STATE CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetRfClockCfmType;

/*! This command is used to set the DUT in TX mode on fixed frequency. Used in 2G4 and 5G8. <br>
Parameters: \ref PtSetFixedFrequencyReqType <br>
Returns: \ref PtSetFixedFrequencyCfmType <br>
Bat file: SetFixedFrequency.bat */
#define PT_CMD_SET_FIXED_FREQUENCY 0x0045

/// \ref PT_CMD_SET_FIXED_FREQUENCY REQ parameter type.
typedef struct
{
  rsuint8 Channel; //!< The fixed channel to transmit on.
} PtSetFixedFrequencyReqType;

/// \ref PT_CMD_SET_FIXED_FREQUENCY CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetFixedFrequencyCfmType;

/*! This command is used to set the DECT mode of the device. <br>
Parameters: \ref PtSetDectModeReqType <br>
Returns: \ref PtSetDectModeCfmType <br>
Bat file: SetDectMode.bat */
#define PT_CMD_SET_DECT_MODE 0x0200

/// \ref PT_CMD_SET_DECT_MODE REQ parameter type.
typedef struct
{
  PtDectModeType DectMode; //!< The dect mode.
} PtSetDectModeReqType;

/// \ref PT_CMD_SET_DECT_MODE CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetDectModeCfmType;

/*! This command is used to get the current DECT mode of the device. <br>
Parameters: none <br>
Returns: \ref PtGetDectModeCfmType <br>
Bat file: GetDectMode.bat */
#define PT_CMD_GET_DECT_MODE 0x007C

/// \ref PT_CMD_GET_DECT_MODE CFM parameter type.
typedef struct
{
  PtDectModeType DectMode; //!< The current dect mode.
} PtGetDectModeCfmType;

/*! This command is used to set the TX modulation. <br>
Parameters: \ref PtSetModulationReqType <br>
Returns: \ref PtSetModulationCfmType <br>
Bat file: SetModulation.bat */
#define PT_CMD_SET_MODULATION 0x0012

/// \ref PT_CMD_SET_MODULATION REQ parameter type.
typedef struct
{
  rsuint8 Modulation; //!< The modulation.
} PtSetModulationReqType;

/// \ref PT_CMD_SET_MODULATION CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetModulationCfmType;

/*! This command is used to read the TX modulation stored in the NVS. <br>
Parameters: none <br>
Returns: \ref PtGetModulationCfmType <br>
Bat file: GetModulation.bat */
#define PT_CMD_GET_MODULATION 0x0201

/// \ref PT_CMD_GET_MODULATION CFM parameter type.
typedef struct
{
  rsuint8 Modulation; //!< The modulation.
} PtGetModulationCfmType;

/*! This command is used to set the RSSI limit in the NVS. <br>
Parameters: \ref PtSetRssiLimitFpReqType <br>
Returns: \ref PtSetRssiLimitFpCfmType <br>
Bat file: SetRssiLimitFp.bat */
#define PT_CMD_SET_RSSI_LIMIT_FP 0x0202

/// \ref PT_CMD_SET_RSSI_LIMIT_FP REQ parameter type.
typedef struct
{
  rsuint8 MaxRssiLevel; //!< The max RSSI.
} PtSetRssiLimitFpReqType;

/// \ref PT_CMD_SET_RSSI_LIMIT_FP CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetRssiLimitFpCfmType;

/*! This command is used to set the clock frequency in the NVS and adjust the clock in the SC144xx <br>
Parameters: \ref PtSetFreqReqType <br>
Returns: \ref PtSetFreqCfmType <br>
Bat file: SetFreq.bat */
#define PT_CMD_SET_CLOCK_FREQUENCY 0x0204

/// \ref PT_CMD_SET_CLOCK_FREQUENCY REQ parameter type.
typedef struct
{
  rsuint16 Frequency; //!< The new clock frequency setting. 16 bits are used for SC14480, SC1444x and newer generation Dialog chips. 8 bits are used only for older Dialog chips.
} PtSetFreqReqType;

/// \ref PT_CMD_SET_CLOCK_FREQUENCY CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetFreqCfmType;

/*! This command is used to get the current clock frequency used. <br>
Parameters: none <br>
Returns: \ref PtGetFreqCfmType <br>
Bat file: GetFreq.bat */
#define PT_CMD_GET_CLOCK_FREQUENCY 0x0205

/// \ref PT_CMD_GET_CLOCK_FREQUENCY CFM parameter type.
typedef struct
{
  rsuint16 Frequency; //!< The current clock frequency used. Please note that some devices return one byte only. Two bytes are used on SC14480, SC1444x and newer generation Dialog chips.
} PtGetFreqCfmType;

/*! This command is used to get clock frequency setting stored in the NVS. <br>
Parameters: none <br>
Returns: \ref PtGetFreqNvsCfmType <br>
Bat file: GetFreqNvs.bat */
#define PT_CMD_GET_NVS_CLOCK_FREQUENCY 0x0206

/// \ref PT_CMD_GET_NVS_CLOCK_FREQUENCY CFM parameter type.
typedef struct
{
  rsuint16 Frequency; //!< The clock frequency setting read from the NVS. Please note that some devices return one byte only. Two bytes are used on SC14480, SC1444x and newer generation Dialog chips.
} PtGetFreqNvsCfmType;

/*! This command is used to set the enroll bit in the FP. <br>
Parameters: \ref PtSetEnrollReqType <br>
Returns: \ref PtSetEnrollCfmType <br>
Bat file: SetEnroll.bat */
#define PT_CMD_SET_FP_ENROLL_BIT 0x009F

/// \ref PT_CMD_SET_FP_ENROLL_BIT REQ parameter type.
typedef struct
{
  rsbool Enroll; //!< TRUE(1): set the enroll bit (Open FP for subscription); FALSE(0): clear the enroll bit.
} PtSetEnrollReqType;

/// \ref PT_CMD_SET_FP_ENROLL_BIT CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetEnrollCfmType;

/*! This command is used to set enrolment data on base and handset. This makes it possible to register a handset on a base via the test interface without any communication over the air interface. <br>
Parameters: \ref PtSetEnrolmentDataReqType <br>
Returns: \ref PtSetEnrolmentDataCfmType <br>
Bat file: SetEnrolmentData.bat */
#define PT_CMD_SET_ENROLMENT_DATA 0x0207

/// \ref PT_CMD_SET_ENROLMENT_DATA REQ parameter type.
typedef struct
{
  rsuint8 HandsetNo; //!< The handset number [1; max number of handsets that can be registered on the base].
  rsuint8 Rfpi[5]; //!< The RFPI of the base.
  rsuint8 Ipei[5]; //!< The IPEI of the handset.
  rsuint8 Uak[16]; //!< The UAK (random number) generated. Must be the same on both the base and the handset.
} PtSetEnrolmentDataReqType;

/// \ref PT_CMD_SET_ENROLMENT_DATA CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetEnrolmentDataCfmType;

/*! This command is used to set power level port setting. <br>
Parameters: \ref PtSetRfPowerLevelPortReqType <br>
Returns: \ref PtSetRfPowerLevelPortCfmType <br>
Bat file: SetRfPowerLevelPort.bat */
#define PT_CMD_SET_RF_POWER_LEVEL_PORT 0x0209

/// \ref PT_CMD_SET_RF_POWER_LEVEL_PORT REQ parameter type.
typedef struct
{
  rsuint8 PortSetting; //!< The power level port setting (project specific).
} PtSetRfPowerLevelPortReqType;

/// \ref PT_CMD_SET_RF_POWER_LEVEL_PORT CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetRfPowerLevelPortCfmType;

/*! This command is used to enable and disable the power control algorithm. <br>
Parameters: \ref PtSetRfPowerLevelAlgorithmReqType <br>
Returns: \ref PtSetRfPowerLevelAlgorithmCfmType <br>
Bat file: SetRfPowerLevelAlgorithm.bat */
#define PT_CMD_SET_RF_POWER_LEVEL_ALGORITHM 0x020C

/// \ref PT_CMD_SET_RF_POWER_LEVEL_ALGORITHM REQ parameter type.
typedef struct
{
  rsbool Enabled; //!< TRUE(1): The power control algorithm is enabled; FALSE(0): disabled.
} PtSetRfPowerLevelAlgorithmReqType;

/// \ref PT_CMD_SET_RF_POWER_LEVEL_ALGORITHM CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetRfPowerLevelAlgorithmCfmType;

/*! This command is used to check whether the power control algorithm is enabled. <br>
Parameters: none <br>
Returns: \ref PtGetRfPowerLevelAlgorithmCfmType <br>
Bat file: GetRfPowerLevelAlgorithm.bat */
#define PT_CMD_GET_RF_POWER_LEVEL_ALGORITHM 0x020D

/// \ref PT_CMD_GET_RF_POWER_LEVEL_ALGORITHM CFM parameter type.
typedef struct
{
  rsbool Enabled; //!< TRUE(1): The power control algorithm is enabled; FALSE(0): disabled.
} PtGetRfPowerLevelAlgorithmCfmType;

/*! Sets the slot and frequency for the dummy bearer <br>
Parameters: \ref PtSetDummyBearerReqType <br>
Returns: \ref PtSetDummyBearerCfmType <br>
Bat file: SetDummyBearer.bat */
#define PT_CMD_SET_DUMMY_BEARER 0x020E

/// \ref PT_CMD_SET_DUMMY_BEARER REQ parameter type.
typedef struct
{
  rsuint8 Slot; //!< Slot
  rsuint8 Freq; //!< Frequency
} PtSetDummyBearerReqType;

/// \ref PT_CMD_SET_DUMMY_BEARER CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetDummyBearerCfmType;

/*! Set the NVS parameters for 4x1 (481, 441, ..., LMX4181) RF transmit power level. For some projects this will require RF reinitialization to take effect (e.g. SetTestMode or SetBurstMode). <br>
Parameters: \ref PtSet4x1PowerLevelParmsReqType <br>
Returns: \ref PtSet4x1PowerLevelParmsCfmType <br>
Bat file: Set4x1PowerLevelParms.bat */
#define PT_CMD_SET_4x1_POWER_LEVEL 0x020F

/// \ref PT_CMD_SET_4x1_POWER_LEVEL REQ parameter type.
typedef struct
{
  rsuint8 Index; //!< NVS Index
  rsuint16 PA_CTRL1_REG; //!< PA_CTRL1_REG
  rsuint16 TEST_MODE2_REG; //!< TEST_MODE2_REG
  rsuint16 BBADC_CTRL_REG; //!< BBADC_CTRL_REG. On LMX4181 this register is named TEST_CTRL3_REG
} PtSet4x1PowerLevelParmsReqType;

/// \ref PT_CMD_SET_4x1_POWER_LEVEL CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSet4x1PowerLevelParmsCfmType;

/*! This command is used to set the RSSI limit (Lower Threshold) in the NVS. <br>
Parameters: \ref PtSetRssiLimitFp_LowerThresholdReqType <br>
Returns: \ref PtSetRssiLimitFp_LowerThresholdCfmType <br>
Bat file: SetRssiLimitFp_LowerThreshold.bat */
#define PT_CMD_SET_RSSI_LIMIT_FP_LOWER_THRESHOLD 0x0211

/// \ref PT_CMD_SET_RSSI_LIMIT_FP_LOWER_THRESHOLD REQ parameter type.
typedef struct
{
  rsuint8 MaxRssiLevel_LowerThreshold; //!< The lower threshold RSSI limit.
} PtSetRssiLimitFp_LowerThresholdReqType;

/// \ref PT_CMD_SET_RSSI_LIMIT_FP_LOWER_THRESHOLD CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetRssiLimitFp_LowerThresholdCfmType;

/*! This command is used to set the access code in the FP. <br>
Parameters: \ref PtSetAcReqType <br>
Returns: \ref PtSetAcCfmType <br>
Bat file: SetAc.bat */
#define PT_CMD_SET_AC 0x0212

/// \ref PT_CMD_SET_AC REQ parameter type.
typedef struct
{
  rsuint8 Ac[4]; //!< The access code.
} PtSetAcReqType;

/// \ref PT_CMD_SET_AC CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetAcCfmType;

/*! This command is used to get the current access code stored in the FP. <br>
Parameters: none <br>
Returns: \ref PtGetAcCfmType <br>
Bat file: GetAc.bat */
#define PT_CMD_GET_AC 0x0213

/// \ref PT_CMD_GET_AC CFM parameter type.
typedef struct
{
  rsuint8 Ac[4]; //!< The access code.
} PtGetAcCfmType;

/*! Get the number of activated RF patches. <br>
Parameters: none <br>
Returns: \ref PtGetRfPatchLengthCfmType <br>
Bat file: GetRfPatchLength.bat */
#define PT_CMD_GET_RF_PATCH_LEN 0x0214

/// \ref PT_CMD_GET_RF_PATCH_LEN CFM parameter type.
typedef struct
{
  rsuint8 PatchLength; //!< Number of activated RF pathces
} PtGetRfPatchLengthCfmType;

/*! Set the number of activated RF patches. <br>
Parameters: \ref PtSetRfPatchLengthReqType <br>
Returns: \ref PtSetRfPatchLengthCfmType <br>
Bat file: SetRfPatchLength.bat */
#define PT_CMD_SET_RF_PATCH_LEN 0x0215

/// \ref PT_CMD_SET_RF_PATCH_LEN REQ parameter type.
typedef struct
{
  rsuint8 PatchLength; //!< Number of activated RF pathces
} PtSetRfPatchLengthReqType;

/// \ref PT_CMD_SET_RF_PATCH_LEN CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetRfPatchLengthCfmType;

/*! Get an RF patch from NVS. The patch may not be active <br>
Parameters: \ref PtGetRfPatchReqType <br>
Returns: \ref PtGetRfPatchCfmType <br>
Bat file: GetRfPatch.bat */
#define PT_CMD_GET_RF_PATCH 0x0216

/// \ref PT_CMD_GET_RF_PATCH REQ parameter type.
typedef struct
{
  rsuint8 PatchNumber; //!< Patch index. Index of the NVS location storing the RF patch
} PtGetRfPatchReqType;

/// \ref PT_CMD_GET_RF_PATCH CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
  rsuint8 ParameterNumber; //!< RF parameter index. Index into the RF parameter definition table (corresponding to nn in DEFAULT_RF_PARAMETER_nn) of the RF parameter to patch.
  rsuint8 PatchRegNo; //!< The RF register to patch. Usually the same register as in the original RF parameter definition table
  rsuint16 PatchRegVal; //!< New value for the RF register
} PtGetRfPatchCfmType;

/*! Write an RF patch into NVS. Note that for the RF patch to be active, the RF patch length must also be set. <br>
Parameters: \ref PtSetRfPatchReqType <br>
Returns: \ref PtSetRfPatchCfmType <br>
Bat file: SetRfPatch.bat */
#define PT_CMD_SET_RF_PATCH 0x0217

/// \ref PT_CMD_SET_RF_PATCH REQ parameter type.
typedef struct
{
  rsuint8 PatchNumber; //!< Patch index. Index of the NVS location storing the RF patch
  rsuint8 ParameterNumber; //!< RF parameter index. Index into the RF parameter definition table (corresponding to nn in DEFAULT_RF_PARAMETER_nn) of the RF parameter to patch.
  rsuint8 PatchRegNo; //!< The RF register to patch. Usually the same register as in the original RF parameter definition table
  rsuint16 PatchRegVal; //!< New value for the RF register
} PtSetRfPatchReqType;

/// \ref PT_CMD_SET_RF_PATCH CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetRfPatchCfmType;

/*! Get JDect number of active channels <br>
Parameters: none <br>
Returns: \ref PtGetJDectStateCfmType <br>
Bat file: GetJDectState.bat */
#define PT_CMD_GET_JDECT_STATE 0x0222

/// \ref PT_CMD_GET_JDECT_STATE CFM parameter type.
typedef struct
{
  rsuint8 JDectActiveChannels; //!< Number of active channels for JDect. 0 means JDect not active, otherwise 2 or 5 will be returned
  rsbool JDect5chSupport; //!< TRUE if the product supports 5 ch Japan DECT.
} PtGetJDectStateCfmType;

/*! Set JDect number of active channels. 5 channel mode can always be selected and will not perform PHS scanning. Will return RSS_NO_CAPABILITY if the FP is not configured for Japan DECT mode (use SetDectMode). <br>
Parameters: \ref PtSetJDectStateReqType <br>
Returns: \ref PtSetJDectStateCfmType <br>
Bat file: SetJDectState.bat */
#define PT_CMD_SET_JDECT_STATE 0x0223

/// \ref PT_CMD_SET_JDECT_STATE REQ parameter type.
typedef struct
{
  rsuint8 JDectActiveChannels; //!< Active channels: 2 or 5
} PtSetJDectStateReqType;

/// \ref PT_CMD_SET_JDECT_STATE CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetJDectStateCfmType;


//@} end of RF

/// Enables the BB test commands.
#ifndef PT_BB_TEST
  #define PT_BB_TEST 1
#endif

/** \name BB Test Command Opcodes
* The following BB test commands are defined.*/ 
//@{

/*! This command is used to set/adjust the band gap in the SC144xx and store it in the EEPROM. <br>
Parameters: \ref PtSetBandGapReqType <br>
Returns: \ref PtSetBandGapCfmType <br>
Bat file: SetBandGap.bat */
#define PT_CMD_SET_BAND_GAP 0x003F

/// \ref PT_CMD_SET_BAND_GAP REQ parameter type.
typedef struct
{
  rsuint8 BandGap; //!< The new band gap value.
} PtSetBandGapReqType;

/// \ref PT_CMD_SET_BAND_GAP CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetBandGapCfmType;

/*! This command is used to read the band gap setting from the EEPROM. <br>
Parameters: none <br>
Returns: \ref PtGetBandGapCfmType <br>
Bat file: GetBandGap.bat */
#define PT_CMD_GET_BAND_GAP 0x0300

/// \ref PT_CMD_GET_BAND_GAP CFM parameter type.
typedef struct
{
  rsuint8 BandGap; //!< The current band gap value.
} PtGetBandGapCfmType;

/*! This command is used to request the DUT to enable/disable audio loop back (earpiece on a handset typically). <br>
Parameters: \ref PtSetAudioLbReqType <br>
Returns: \ref PtSetAudioLbCfmType <br>
Bat file: SetAudioLb.bat */
#define PT_CMD_SET_AUDIO_LOOP_BACK 0x0062

/// \ref PT_CMD_SET_AUDIO_LOOP_BACK REQ parameter type.
typedef struct
{
  rsbool LoopBack; //!< TRUE: start audio loop back; FALSE: stop audio loop back
} PtSetAudioLbReqType;

/// \ref PT_CMD_SET_AUDIO_LOOP_BACK CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetAudioLbCfmType;

/*! This command is used to request the DUT to enable/disable audio loop back on the headset. <br>
Parameters: \ref PtSetAudioLbHeadsetReqType <br>
Returns: \ref PtSetAudioLbHeadsetCfmType <br>
Bat file: SetAudioLbHeadset.bat */
#define PT_CMD_SET_AUDIO_LOOP_BACK_HEADSET 0x0063

/// \ref PT_CMD_SET_AUDIO_LOOP_BACK_HEADSET REQ parameter type.
typedef struct
{
  rsbool LoopBack; //!< TRUE: start audio loop back; FALSE: stop audio loop back
} PtSetAudioLbHeadsetReqType;

/// \ref PT_CMD_SET_AUDIO_LOOP_BACK_HEADSET CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetAudioLbHeadsetCfmType;

/*! This command is used to switch a LED on/off. <br>
Parameters: \ref PtSetLedReqType <br>
Returns: \ref PtSetLedCfmType <br>
Bat file: SetLed.bat */
#define PT_CMD_SET_LED 0x0302

/// \ref PT_CMD_SET_LED REQ parameter type.
typedef struct
{
  PtLedCmdType Command; //!< The LED command.
  rsuint8 LedId; //!< The id of the LED (project specific).
} PtSetLedReqType;

/// \ref PT_CMD_SET_LED CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetLedCfmType;


//@} end of BB

/// Enables the GAP test commands.
#ifndef PT_GAP_TEST
  #define PT_GAP_TEST 1
#endif

/** \name GAP Test Command Opcodes
* The following GAP test commands are defined.*/ 
//@{

/*! This command is used to disable location update. <br>
Parameters: none <br>
Returns: \ref PtGapLocOffCfmType <br>
Bat file: GapLocOff.bat */
#define PT_CMD_GAP_LOC_OFF 0x0500

/// \ref PT_CMD_GAP_LOC_OFF CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtGapLocOffCfmType;

/*! This command is used to enable location update. <br>
Parameters: none <br>
Returns: \ref PtGapLocOnCfmType <br>
Bat file: GapLocOn.bat */
#define PT_CMD_GAP_LOC_ON 0x0501

/// \ref PT_CMD_GAP_LOC_ON CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtGapLocOnCfmType;

/*! This command is used to disable authentication. <br>
Parameters: none <br>
Returns: \ref PtGapAuthOffCfmType <br>
Bat file: GapAuthOff.bat */
#define PT_CMD_GAP_AUTH_OFF 0x0502

/// \ref PT_CMD_GAP_AUTH_OFF CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtGapAuthOffCfmType;

/*! This command is used to enable authentication. <br>
Parameters: none <br>
Returns: \ref PtGapAuthOnCfmType <br>
Bat file: GapAuthOn.bat */
#define PT_CMD_GAP_AUTH_ON 0x0503

/// \ref PT_CMD_GAP_AUTH_ON CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtGapAuthOnCfmType;

/*! This command is used to release the current connection to the GAP tester. <br>
Parameters: none <br>
Returns: \ref PtGapReleaseCfmType <br>
Bat file: GapRelease.bat */
#define PT_CMD_GAP_RELEASE 0x0504

/// \ref PT_CMD_GAP_RELEASE CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtGapReleaseCfmType;

/*! This command is used to terminate a registeration. <br>
Parameters: none <br>
Returns: \ref PtGapTermCfmType <br>
Bat file: GapTerm.bat */
#define PT_CMD_GAP_TERM_ACCESS_RIGHTS 0x0505

/// \ref PT_CMD_GAP_TERM_ACCESS_RIGHTS CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtGapTermCfmType;

/*! This command is used to revoke a registeration. <br>
Parameters: none <br>
Returns: \ref PtGapRevokeCfmType <br>
Bat file: GapRevoke.bat */
#define PT_CMD_GAP_REVOKE_ACCESS_RIGHTS 0x0506

/// \ref PT_CMD_GAP_REVOKE_ACCESS_RIGHTS CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtGapRevokeCfmType;

/*! This command is used to terminate all registerations. <br>
Parameters: none <br>
Returns: \ref PtGapTermAllCfmType <br>
Bat file: GapTermAll.bat */
#define PT_CMD_GAP_TERM_ACCESS_RIGHTS_ALL 0x0507

/// \ref PT_CMD_GAP_TERM_ACCESS_RIGHTS_ALL CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtGapTermAllCfmType;

/*! This command is used to revoke all registerations. <br>
Parameters: none <br>
Returns: \ref PtGapRevokeAllCfmType <br>
Bat file: GapRevokeAll.bat */
#define PT_CMD_GAP_REVOKE_ACCESS_RIGHTS_ALL 0x0508

/// \ref PT_CMD_GAP_REVOKE_ACCESS_RIGHTS_ALL CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtGapRevokeAllCfmType;

/*! This command is used to start authentication when testing TBR22. <br>
Parameters: none <br>
Returns: \ref PtGapStartAuthCfmType <br>
Bat file: GapStartAuth.bat */
#define PT_CMD_GAP_START_AUTH 0x0509

/// \ref PT_CMD_GAP_START_AUTH CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtGapStartAuthCfmType;


//@} end of GAP

/// Enables the CAT-iq test commands.
#ifndef PT_CATIQ_TEST
  #define PT_CATIQ_TEST 1
#endif

/** \name CAT-iq Test Command Opcodes
* The following CAT-iq test commands are defined.*/ 
//@{

/*! This command is used to set all bits except the Codec list in the PpCapability var stored in the NVS for the PP device selected. <br>
Parameters: \ref PtSetPpCapabilityReqType <br>
Returns: \ref PtSetPpCapabilityCfmType <br>
Bat file: SetPpCapability.bat */
#define PT_CMD_SET_PP_CAPABILITY 0x0580

/// \ref PT_CMD_SET_PP_CAPABILITY REQ parameter type.
typedef struct
{
  rsuint8 HandsetNo; //!< The handset number [1; max number of handsets that can be registered on the base].
  rsbool KnownEmc; //!< Set to TRUE if IWU's are allowed.
  rsbool WB; //!< Set to TRUE if the PP supports NG-DECT PART 1: Wide band voice (TS 102 527-1).
  rsbool EWB; //!< Set to TRUE if the PP Supports  NG-DECT PART 3:  Extended Wideband speech services, this implies all PP mandatory features except Common parallel calls (ETSI TS 102 527-3).
  rsbool HeadsetManagement; //!< Set to TRUE if the PP Supports NG-DECT PART 3: Headset management feature NG1.N.21. (ETSI TS 102 527-3)
  rsbool EarlyEncryption; //!< Set to TRUE if the PP supports Re-keying and early encryption.
  rsuint8 EchoParameter; //!< Pp Echo suppression parameter (3 bits in spec, but only 2 used).
  rsuint32 PMID; //!< Handset PMID. This parameter is optional because it is not used on all projects.
} PtSetPpCapabilityReqType;

/// \ref PT_CMD_SET_PP_CAPABILITY CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetPpCapabilityCfmType;

/*! This command is used to get all bits except the Codec list of the PpCapability var stored in the NVS for the PP device selected. <br>
Parameters: \ref PtGetPpCapabilityReqType <br>
Returns: \ref PtGetPpCapabilityCfmType <br>
Bat file: GetPpCapability.bat */
#define PT_CMD_GET_PP_CAPABILITY 0x0581

/// \ref PT_CMD_GET_PP_CAPABILITY REQ parameter type.
typedef struct
{
  rsuint8 HandsetNo; //!< The handset number [1; max number of handsets that can be registered on the base].
} PtGetPpCapabilityReqType;

/// \ref PT_CMD_GET_PP_CAPABILITY CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
  rsbool KnownEmc; //!< Set to TRUE if IWU's are allowed.
  rsbool WB; //!< Set to TRUE if the PP supports NG-DECT PART 1: Wide band voice (TS 102 527-1).
  rsbool EWB; //!< Set to TRUE if the PP Supports  NG-DECT PART 3:  Extended Wideband speech services, this implies all PP mandatory features except Common parallel calls (ETSI TS 102 527-3).
  rsbool HeadsetManagement; //!< Set to TRUE if the PP Supports NG-DECT PART 3: Headset management feature NG1.N.21. (ETSI TS 102 527-3)
  rsbool EarlyEncryption; //!< Set to TRUE if the PP supports Re-keying and early encryption.
  rsuint8 EchoParameter; //!< Pp Echo suppression parameter (3 bits in spec, but only 2 used).
  rsuint32 PMID; //!< Handset PMID.
} PtGetPpCapabilityCfmType;

/*! This command is used to set the codec list in the PpCapability var stored in the NVS for the PP device selected. <br>
Parameters: \ref PtSetPpCapabilityCodecListReqType <br>
Returns: \ref PtSetPpCapabilityCodecListCfmType <br>
Bat file: SetPpCapabilityCodecList.bat */
#define PT_CMD_SET_PP_CAPABILITY_CODEC_LIST 0x0582

/// \ref PT_CMD_SET_PP_CAPABILITY_CODEC_LIST REQ parameter type.
typedef struct
{
  rsuint8 HandsetNo; //!< The handset number [1; max number of handsets that can be registered on the base].
  rsuint8 CodecListLength; //!< The number of elements in the CodecList[]. The actual size of the codec list can be found in the EEPROM documentation for the project.
  PtSwCodecType CodecList[1]; //!< The codec list - array of PtSwCodecType.
} PtSetPpCapabilityCodecListReqType;

/// \ref PT_CMD_SET_PP_CAPABILITY_CODEC_LIST CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetPpCapabilityCodecListCfmType;

/*! This command is used to get the codec list of the PpCapability var stored in the NVS for the PP device selected. <br>
Parameters: \ref PtGetPpCapabilityCodecListReqType <br>
Returns: \ref PtGetPpCapabilityCodecListCfmType <br>
Bat file: GetPpCapabilityCodecList.bat */
#define PT_CMD_GET_PP_CAPABILITY_CODEC_LIST 0x0583

/// \ref PT_CMD_GET_PP_CAPABILITY_CODEC_LIST REQ parameter type.
typedef struct
{
  rsuint8 HandsetNo; //!< The handset number [1; max number of handsets that can be registered on the base].
} PtGetPpCapabilityCodecListReqType;

/// \ref PT_CMD_GET_PP_CAPABILITY_CODEC_LIST CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
  rsuint8 CodecListLength; //!< The number of elements in the CodecList[]
  PtSwCodecType CodecList[1]; //!< The codec list - array of PtSwCodecType.
} PtGetPpCapabilityCodecListCfmType;


//@} end of CAT-iq

/// Test commands for flash OTP area.
#ifndef PT_OTP_TEST
  #define PT_OTP_TEST 1
#endif

/** \name OTP Test Command Opcodes
* The following OTP test commands are defined.*/ 
//@{

/*! Get OTP information (flash serial number, size of OTP area, lock status). <br>
Parameters: none <br>
Returns: \ref PtGetOtpInfoCfmType <br>
Bat file: GetOtpInfo.bat */
#define PT_GET_OTP_INFO 0x0700

/// \ref PT_GET_OTP_INFO CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
  rsbool Locked; //!< The lock status of the OTP area (0=writeable, 1=locked down).
  rsuint16 OtpSize; //!< The size of the OTP area in the flash (excluding serial number).
  rsuint8 Length; //!< The size of the flash serial number.
  rsuint8 Data[1]; //!< The flash serial number.
} PtGetOtpInfoCfmType;

/*! Commit HW adjustment parameters from NVS to OTP. This is typically Rfpi/Ipei, BmcModulationDeviation, BmcDefaultFrequency and Bandgap. <br>
Parameters: \ref PtSetOtpCommitReqType <br>
Returns: \ref PtSetOtpCommitCfmType <br>
Bat file: SetOtpCommit.bat */
#define PT_SET_OTP_COMMIT 0x0701

/// \ref PT_SET_OTP_COMMIT REQ parameter type.
typedef struct
{
  rsuint8 Password; //!< Must be 0xAA.
} PtSetOtpCommitReqType;

/// \ref PT_SET_OTP_COMMIT CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetOtpCommitCfmType;

/*! Lock the OTP area in the flash. <br>
Parameters: \ref PtSetOtpLockReqType <br>
Returns: \ref PtSetOtpLockCfmType <br>
Bat file: SetOtpLock.bat */
#define PT_SET_OTP_LOCK 0x0702

/// \ref PT_SET_OTP_LOCK REQ parameter type.
typedef struct
{
  rsuint8 Password; //!< Must be 0xBB.
} PtSetOtpLockReqType;

/// \ref PT_SET_OTP_LOCK CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetOtpLockCfmType;

/*! Read data from flash OTP area. <br>
Parameters: \ref PtGetOtpDataReqType <br>
Returns: \ref PtGetOtpDataCfmType <br>
Bat file: GetOtpData.bat */
#define PT_GET_OTP_DATA 0x0703

/// \ref PT_GET_OTP_DATA REQ parameter type.
typedef struct
{
  rsuint32 Address; //!< The address of the first byte to read.
  rsuint8 Length; //!< The number of bytes to read.
} PtGetOtpDataReqType;

/// \ref PT_GET_OTP_DATA CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
  rsuint32 Address; //!< The address of the first byte read.
  rsuint8 Length; //!< The number of bytes read.
  rsuint8 Data[1]; //!< The data read.
} PtGetOtpDataCfmType;

/*! Write data to the flash OTP area. <br>
Parameters: \ref PtSetOtpDataReqType <br>
Returns: \ref PtSetOtpDataCfmType <br>
Bat file: SetOtpData.bat */
#define PT_SET_OTP_DATA 0x0704

/// \ref PT_SET_OTP_DATA REQ parameter type.
typedef struct
{
  rsuint32 Address; //!< The address of the first byte to write.
  rsuint8 Length; //!< The number of bytes to write.
  rsuint8 Data[1]; //!< The data that should be written.
} PtSetOtpDataReqType;

/// \ref PT_SET_OTP_DATA CFM parameter type.
typedef struct
{
  RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
} PtSetOtpDataCfmType;


//@} end of OTP



#endif // PTCMDDEF_H

