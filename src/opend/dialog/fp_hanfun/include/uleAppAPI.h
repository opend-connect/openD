/*
 * Copyright (C) 2018 by Dialog Semiconductor. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of Dialog Semiconductor nor the names of its Affiliates
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
#ifndef __ULEAPPAPI_H__
#define __ULEAPPAPI_H__

#include <include/uleAppEnum.h>
//#include <microhttpd.h>
/******************************************************************************
 *                     ULE API FOR USER APPLICATION                           *
 ******************************************************************************/

/* Helper functions */
unsigned sys_sleep (unsigned seconds);

int sys_usleep(unsigned useconds);

// This is the user interface to ULE functionality. User is  allowed to call only these functions.

// Called always at the beginning of each app to initialize ULE. Subsequent calls to other ULE function will fail if Init fails.
UleErr_e ULE_Init(rsuint32 AccessCodeDefault, rsuint32 SensorTimeoutDefault, rsuint32 TxTimeoutDefault,
		char *WebSiteLocation, rsuint32 HTTPport, char *BoardIPaddr, rsuint8 DbgPI, rsuint8 DbgAPI, rsuint8 DbgMUTEX,rsint8 Comport);
// Used at the end of app to free memory reserved from ULE variables.
UleErr_e ULE_Exit();
// Used to set the Access Code of CVM
UleErr_e ULE_Set_Access_Code(rsuint8 Ac_1, rsuint8 Ac_2, rsuint8 Ac_3, rsuint8 Ac_4);
// Used to read the Access Code of CVM
UleErr_e ULE_Get_Access_Code(rsuint8 *Ac_1Ptr, rsuint8 *Ac_2Ptr, rsuint8 *Ac_3Ptr, rsuint8 *Ac_4Ptr);
UleErr_e ULE_Get_Access_Code_Force(rsuint8 *Ac_1Ptr, rsuint8 *Ac_2Ptr, rsuint8 *Ac_3Ptr, rsuint8 *Ac_4Ptr);
// Used to get the list of ULE sensors currently registered
UleErr_e ULE_Get_Registration_Count(rsuint8 *Registered,rsuint8 *MaxSupported);
// Used to put CVM in registration mode
UleErr_e ULE_Enable_Registration(rsuint32 registration_timeout);
// Used to release CVM from  registration mode
UleErr_e ULE_Disable_Registration();
// Used to read current registration mode
rsbool ULE_Get_Registration_Mode();
// Used to Deregister all ULE Devices
UleErr_e ULE_DeRegister_all();
// Used to Deregister a single ULE device
UleErr_e ULE_DeRegister(rsuint8 portId);
// Used to set the timeout value after which the sensor will be considered OFFLINE. Set 0 to disable.
UleErr_e ULE_Set_PP_timeout(rsuint8 portId, rsuint32 timeout_val);
// Used to read the timeout value after which the sensor will be considered OFFLINE.
UleErr_e ULE_Get_PP_timeout(rsuint8 portId, rsuint32 *timeoutPtr, rsuint32 *timeoutPtr1);
// Get the time in seconds the ULE system is up
rsuint32 ULE_Get_Sys_Time();
// Used to set the timeout value after which the Tx Buff send will get Aborted. Set 0 to disable.
UleErr_e ULE_Set_TxData_timeout(rsuint8 portId, rsuint32 timeout_val);
// Used to read the timeout value after which the Tx Buff send will get Aborted.
UleErr_e ULE_Get_TxData_timeout(rsuint8 portId, rsuint32 *timeoutPtr);
// Used to read the state of TX Buffer
UleErr_e ULE_Get_PP_transmit_status(rsuint8 portId, rsuint8 *statusPtr);
// Used to read the state of ULE sensor (online/offline/registered)
UleErr_e ULE_Get_PP_status(rsuint8 portId, rsuint8 *statusPtr);
// Used to read the type of ULE sensor (switch/button/relay/etc)
UleErr_e ULE_Get_PP_type(rsuint8 portId, rsuint8 *statusPtr);
// Used to read the Rssi value of the given PP
UleErr_e ULE_Get_PP_RSSI_Val(rsuint8 portId, rsuint8 *rssiVal);
// Used to store the Rssi value of the given PP
UleErr_e ULE_Set_PP_RSSI_Val(rsuint8 portId, rsuint8 rssiVal);
// User function to Get PP user attribute value
UleErr_e ULE_Get_PP_Attribute(rsuint8 portId, rsuint8 num, rsuint32 *valPtr);
// User function to Set PP user attribute value
UleErr_e ULE_Set_PP_Attribute(rsuint8 portId, rsuint8 num, rsuint32 valPtr);
// Used to read data from sensor receive buffer after PckID (being the last value being read). If PckID=0 all packets will be read.
UleErr_e ULE_Read_Data(rsuint8 portId, rsuint32 PctID, DataPackets_t **pcklst);
// Used to read the latest data received for a single event
UleErr_e ULE_Read_Latest_Event_Data(rsuint8 portId, rsuint8 Event, DataPacket_t *dataPacketPtr);
// Used to send data to the sensor
UleErr_e ULE_Send_Data(rsuint8 portId, rsuint8 EarlyBit, DataPacket_t *dataPacketPtr);
UleErr_e ULE_Send_Data_Raw(rsuint8 portId,  rsuint8 EarlyBit, rsuint16 Len, rsuint8 *Data);
// Used to abort the Tx send which is still pending
UleErr_e ULE_TxAbort(rsuint8 portId);
// Used to register a user function to handle certain event for given sensor type
UleErr_e ULE_RegisterEventCallback(rsuint8 sensor_type, rsuint8 data_type, void(*CallBack)(rsuint8 portid,
									DataPacket_t *dataPacketPtr));
// Used to get the IPUI value of portable sensor (unique value)
UleErr_e ULE_GetIPUI(rsuint8 portId,rsuint8 IPUIval[]);
// Used to get the RFPI value of fixed part (unique value)
UleErr_e ULE_GetRFPI(rsuint8 RFPIval[]);
// Used to set the callback function for the user JSON command. To bypass the whole JSON interface refer to ULE_Init function.
UleErr_e ULE_RegisterWebReqCallback(cJSON* (*CallBack)(char *UserJSONstring));
// FWS related functionality
void FWSInit(rsuint8 portid);
void FWSInitALL(const char *fileToUse);
UleErr_e ULE_Get_PP_FWS_Status_Info(rsuint8 portId, rsuint8 *ppState, rsuint8 *fwsStatus, rsuint8 *fwsProgress);
rsuint8 getAvailableFwsFileNames(char *fileNames[]);
rsuint8 getAvailableFwsFilesNumber();
rsuint8 deleteFwsFile(const char *fileName);
void setFwsFilenameToUse(rsuint8 portId, const char *fileName);

char * ULE_Get_SW_Version();
UleErr_e ULE_Get_PP_SW_Version_Info(rsuint8 portId, rsuint8 swVersion[]);
void Reset_Smartplug_MinMax_Values(rsuint8 portid);

UleErr_e ULE_UpdateCVMFW();
UleErr_e ULE_DectMode(rsuint8 DectMode);
UleErr_e ULE_Get_DectMode(rsuint8 *DectMode);
UleErr_e ULE_Set_Time_Server(char *addr);
UleErr_e ULE_Set_SIP_Server(char *addr);
UleErr_e ULE_update_sip_account (unsigned char id, unsigned char  en, char* username,char* userid,char* userpass);
// Functions used to handle the linked list of received packets.
DataPackets_t *ULE_create_datpck(DataPacket_t *pckPtr);
DataPackets_t *ULE_add_datpck(DataPackets_t *pckListPtr, DataPacket_t *pckPtr);
void ULE_delete_dat_pck(DataPackets_t *pckPtr);
void ULE_Configure_Hdlc_Port(const char* portname);
#endif //__ULEAPPAPI_H__
