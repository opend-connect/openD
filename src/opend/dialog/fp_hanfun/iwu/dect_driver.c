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
/*========================== Include files ==================================*/

#include <include/uleDectAPI.h>

#include <Phoenix/Api/Api.h>
#include <Phoenix/Api/Types/ApiTypes.h>

#include <dect_driver.h>
#include <Phoenix/Api/FpMm/ApiFpMm.h>
#include <Phoenix/Api/FpMm/ApiFpMmMps.h>
#include <Phoenix/Api/FpUle/ApiFpUleMps.h>
#include <Phoenix/Api/HAL/ApiHAL.h>
#include <Phoenix/Api/HAL/ApiHalMps.h>
#include <Phoenix/Api/RsList.h>
#include <Phoenix/Api/RosPrimitiv.h>
#include <Phoenix/FpProductTest/ApiFpProdTestMps.h>

#ifdef WIN_BUILD
#include <winsock2.h>
#endif

#include <fp_host_version.h>


rsuint8 DECT_BRIDGE_MODE = 0;
rsuint8 DECT_UPGRADE = 0;
#ifdef LEGACY_CODE_TBR
rsuint8 DECT_DECTMODE_US = 0;
rsuint8 DECT_DECTMODE_EU = 0;
rsuint8 DECT_NVSDEFAULT = 0;
rsuint8 DECT_DECTMODE_JP = 0;
#endif // LEGACY_CODE_TBR
rsuint8 Isconnected = 0;
rsuint8 DECTMASK = 0x1F;
rsuint8 isEU=1;
rsuint8 isUS=1;
rsuint8 isJP=1;
#ifdef WIN_BUILD
int sock, length, fromlen, n;
struct sockaddr_in server;
struct sockaddr_in from;
#endif
char buf[1024];
unsigned short RCVBUFF[64];
extern char VERSION[50];
rsuint8 nxt_realease_reason;
rsuint16 datapoll_cur_id=0;
DataPacket_t dataPckt;

#define API_TASK 0x01

char ULE_mail_switch(unsigned short Length, unsigned char *MailPtr);
int fwsApiFpMmHandsetPresentInd(const ApiFpMmHandsetPresentIndType* m);
int fwsApiFpUleDataInd(rsuint8 portid,const MmiUlePdu_common_t* m);


#define TX_BUFF_SIZE 5

rsuint8 j,k;

typedef struct
{
  rsuint8   len[TX_BUFF_SIZE];
  rsuint8 	data[TX_BUFF_SIZE][30];
  rsuint8	pending[TX_BUFF_SIZE];
  rsuint8   currentid;
  rsuint8   TxBusy;
} TxBuffstr;

TxBuffstr txbuff[64];


void TxBuff_SendData(rsuint8 portid, rsuint8 len, rsuint8 *Data){

	for(k=0;k<TX_BUFF_SIZE;k++){
		if((txbuff[portid].pending[k]>0)&&(txbuff[portid].len[k]==0)&&(len==0)) break; // Ignore if 0 length message is already scheduled.
		if((k<(TX_BUFF_SIZE-1))&&(len==0)) continue; // Add 0 length message at the end (send last)
		if(txbuff[portid].pending[k]>0) continue;
		printf("Add buffered data in position %d \n", k);
		txbuff[portid].pending[k]=1;
		txbuff[portid].len[k]= len;
		for(j=0;j<len;j++){
			txbuff[portid].data[k][j]= Data[j];
		}
		if (txbuff[portid].TxBusy){
			//Stack busy
		}else{
		   txbuff[portid].currentid = k;
		   txbuff[portid].TxBusy = 1;
		   SendApiFpUleDataReq(API_TASK, portid,0x80,  txbuff[portid].len[k], &txbuff[portid].data[k][0]);
		}
		break;
	}
}

void TxBuff_LastTxStatus(rsuint8 portid, rsuint8 ok){

	txbuff[portid].TxBusy=0;
	txbuff[portid].pending[txbuff[portid].currentid]= ok;

}

void TxBuff_Send(){
	rsuint8 portid;
	for ( portid=0;portid<64;portid++){
		if (txbuff[portid].TxBusy) continue;

		for(k=0;k<TX_BUFF_SIZE;k++){
			if(txbuff[portid].pending[k]==0) continue;
			txbuff[portid].currentid = k;
			txbuff[portid].TxBusy = 1;
			printf("Get buffered data in position %d \n", k);
			SendApiFpUleDataReq(API_TASK, portid, 0x80,  txbuff[portid].len[k], &txbuff[portid].data[k][0]);
			break;
		}
	}
}


/****************************************************************************
 *  FUNCTION: ApiFpDlcUleDataInd
 *
 *  INPUTS  : ApiFpUleDataInd *p_mail
 *  RETURNS : void
 *
 *  DESCRIPTION: responds to incoming data (API_FP_ULE_DATA_IND)
 ****************************************************************************/
void ApiFpUleDataInd(ApiFpUleDataIndType *p_mail) {
	datapoll_cur_id=p_mail->TerminalId;
  if (p_mail->Length ==0){
	  ULE_PI_MSG("Dect Driver ULE_Receive_Data dummy 0 length packet ID: %d \n",p_mail->TerminalId);
	  ULE_PI_MSG("0len: Setting release reason to %d for ID: %d \n",nxt_realease_reason,p_mail->TerminalId);
      SendApiFpUleDatapoll(API_TASK,p_mail->TerminalId,nxt_realease_reason,NULL);
      nxt_realease_reason=(nxt_realease_reason==0)?0x10:0;
      return;
   }else{
	   ULE_PI_MSG("Setting release reason to %d for ID: %d \n",0, p_mail->TerminalId);
	   SendApiFpUleDatapoll(API_TASK,p_mail->TerminalId,0,NULL);
	   nxt_realease_reason=0x10;
   }

#ifdef HANFUN
   return;
#endif

#if defined(CONFIG_CATIQ_V11_SUPPORT) || defined(CONFIG_CATIQ_V12_SUPPORT)
   ULE_PI_MSG("Dect Driver ULE_Receive_Data TerminalId  %d Length %d \n",p_mail->TerminalId, p_mail->Length);
#else
   ULE_PI_MSG("Dect Driver ULE_Receive_Data PpNumber  %d Length %d \n",p_mail->PpNumber, p_mail->Length);
#endif

   if ( p_mail->Length  > DATA_TRANSMIT_MAX_SIZE) {
      ULE_ERR_MSG("Dect Driver received more data then permitted! ID: %d %d %d \n",p_mail->TerminalId, DATA_TRANSMIT_MAX_SIZE , p_mail->Length);
      return;
   }


   if((p_mail->Data[15]==0xBE)&&(p_mail->Data[16]==0xEF)){ // Decode RF statistics
#ifdef DATA_LINK_TEST
      if(RCVBUFF[p_mail->TerminalId]!= (p_mail->Data[6]*255 + p_mail->Data[7])){
         ULE_ERR_MSG("Dect Driver skipped packets %d %d %d \n",p_mail->TerminalId,RCVBUFF[p_mail->TerminalId],  (p_mail->Data[6]*255 + p_mail->Data[7]));
         RCVBUFF[p_mail->TerminalId]=p_mail->Data[6]*255 + p_mail->Data[7]+1;
      }else{
         RCVBUFF[p_mail->TerminalId]++;
      }

      if(p_mail->Data[17]!= 0){
         ULE_ERR_MSG("Dect Driver PP error code %d %d  \n",p_mail->TerminalId,p_mail->Data[17]);
      }

      rsuint16 n;

      for (n=23;n<DATA_LINK_TEST_PACKET_SIZE;n++){
         if ((p_mail->Data[n]!=((n  - 3 )& 0xFF))&&
               (p_mail->Data[n]!=((n + p_mail->TerminalId - 3 )& 0xFF))){
            ULE_ERR_MSG("Dect Driver receive error %d %d %d \n",p_mail->TerminalId, ((n  - 3 )& 0xFF), p_mail->Data[n]);
         }
      }
#endif
      ULE_PI_MSG("Dect Driver ULE_Receive_Data ID: %d Length: %d  SensorType: 0x%X DataType: 0x%X Counter: %d  Data: 0x%X 0x%X 0x%X TxPass: %d TxFail: %d Sync: %d msec TxLatency: %d msec Rssi: 0x%X \n",
          p_mail->TerminalId, p_mail->Length,
         p_mail->Data[1],p_mail->Data[0],p_mail->Data[2],
         p_mail->Data[3],p_mail->Data[4],p_mail->Data[5],
         p_mail->Data[6]*255 + p_mail->Data[7],
         p_mail->Data[8]*255 + p_mail->Data[9],
         p_mail->Data[10]*255 +p_mail->Data[11],
         p_mail->Data[12]*255 +p_mail->Data[13],
         p_mail->Data[14]);
   }else{
      ULE_PI_MSG("Dect Driver ULE_Receive_Data  %d Length %d  first 10 bytes:  %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
          p_mail->TerminalId, p_mail->Length,
         p_mail->Data[0],p_mail->Data[1],p_mail->Data[2],p_mail->Data[3],p_mail->Data[4],
         p_mail->Data[5],p_mail->Data[6],p_mail->Data[7],p_mail->Data[8],p_mail->Data[9],
         p_mail->Data[10],p_mail->Data[11],p_mail->Data[12],p_mail->Data[13],p_mail->Data[14]);
   }

   dataPckt.Payload.Hdr.Length = p_mail->Length;
   memcpy(&(dataPckt.Payload.Hdr.Type), &(p_mail->Data[0]), (p_mail->Length));
#if defined(CONFIG_CATIQ_V11_SUPPORT) || defined(CONFIG_CATIQ_V12_SUPPORT)
   if(fwsApiFpUleDataInd(p_mail->TerminalId,&(dataPckt.Payload))){
      return;
   }else{
   ULE_Receive_Data(p_mail->TerminalId, &dataPckt);
   }
#else
   if(fwsApiFpUleDataInd(p_mail->PpNumber,&(dataPckt.Payload.Hdr.Length))){
      return;
   }else{
   ULE_Receive_Data(p_mail->PpNumber, &dataPckt);
   }
#endif
}

/****************************************************************************
 *  FUNCTION: ApiFpUleDataCfm
 *
 *  INPUTS  : ApiFpUleDataRejCfm *p_mail
 *  RETURNS : void
 *
 *  DESCRIPTION: responds to data confirm (API_FP_ULE_DATA_CFM)
 ****************************************************************************/
#if defined(CONFIG_CATIQ_V11_SUPPORT) || defined(CONFIG_CATIQ_V12_SUPPORT)
void ApiFpUleDataRejCfm(ApiFpUleDataCfmType *p_mail) {

   if(p_mail->Status){
   ULE_PI_MSG("Dect Driver:  API_FP_ULE_DATA_CFM received: %d Status: %d \n",p_mail->TerminalId,p_mail->Status);
   ULE_Data_reject(p_mail->TerminalId, p_mail->Status);
   }
}
#else
void ApiFpUleDataRejCfm(ApiFpUleDataRejectIndType *p_mail) {

   if(p_mail->Status){
   ULE_PI_MSG("Dect Driver:  API_FP_ULE_DATA_REJECT_IND received: %d Status: %d \n",p_mail->PpNumber,p_mail->Status);
   ULE_Data_reject(p_mail->PpNumber, p_mail->Status);
   }
}
#endif
void ApiFpUleGetRegistrationCountCfm(ApiFpUleGetRegistrationCountCfmType *p_mail) {

   ULE_PI_MSG("Dect Driver: ApiFpUleGetRegistrationCountCfm Received parameters:\n Status: %d\n NoDevices: %d\n MaxNoHs: %d\n MaxNoDevices: %d\n Length: %d \n Data: %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d \n",
         p_mail->Status,
         p_mail->NoDevices,
         p_mail->MaxNoHs,
         p_mail->MaxNoDevices,
         p_mail->Length,
         (rsuint8)p_mail->DeviceIdBitArr[0],
         (rsuint8)p_mail->DeviceIdBitArr[1],
         (rsuint8)p_mail->DeviceIdBitArr[2],
         (rsuint8)p_mail->DeviceIdBitArr[3],
         (rsuint8)p_mail->DeviceIdBitArr[4],
         (rsuint8)p_mail->DeviceIdBitArr[5],
         (rsuint8)p_mail->DeviceIdBitArr[6],
         (rsuint8)p_mail->DeviceIdBitArr[7],
         (rsuint8)p_mail->DeviceIdBitArr[8],
         (rsuint8)p_mail->DeviceIdBitArr[9],
         (rsuint8)p_mail->DeviceIdBitArr[10],
         (rsuint8)p_mail->DeviceIdBitArr[11],
         (rsuint8)p_mail->DeviceIdBitArr[12],
         (rsuint8)p_mail->DeviceIdBitArr[13],
         (rsuint8)p_mail->DeviceIdBitArr[14],
         (rsuint8)p_mail->DeviceIdBitArr[15],
         (rsuint8)p_mail->DeviceIdBitArr[16],
         (rsuint8)p_mail->DeviceIdBitArr[17],
         (rsuint8)p_mail->DeviceIdBitArr[18],
         (rsuint8)p_mail->DeviceIdBitArr[19],
         (rsuint8)p_mail->DeviceIdBitArr[20],
         (rsuint8)p_mail->DeviceIdBitArr[21],
         (rsuint8)p_mail->DeviceIdBitArr[22],
         (rsuint8)p_mail->DeviceIdBitArr[23]);

   ULE_Get_Registration_Count_Cfm(p_mail->Status, p_mail->MaxNoHs, p_mail->Length, p_mail->DeviceIdBitArr);

}

void ApiFpMmSetRegistrationModeCfmULE(ApiFpMmSetRegistrationModeCfmType *p_mail) {

   ULE_PI_MSG("Dect Driver: ApiFpMmSetRegistrationModeCfm Received parameters Status: %d\n",
         p_mail->Status);

   ULE_SetRegMode_Cfm(p_mail->Status);

}

void ApiFpUleAbortCfm(ApiFpUleAbortDataCfmType *p_mail) {
#if defined(CONFIG_CATIQ_V11_SUPPORT) || defined(CONFIG_CATIQ_V12_SUPPORT)
   ULE_PI_MSG("Dect Driver: ApiFpUleAbortCfm Received parameters:\n Device: %d\n  Status: %d\n",
         p_mail->TerminalId,
         p_mail->Status);
#else
   ULE_PI_MSG("Dect Driver: ApiFpUleAbortCfm Received parameters:\n Device: %d\n  Status: %d\n",
         p_mail->PpNumber,
         p_mail->Status);

#endif
   ULE_TxAbort_Cfm(p_mail->Status);

}

void ApiFpHALReadCfm(ApiHalReadCfmType *MailPtr){

   rsuint8 RfLMX4x68DataEU_DECT[] = {0x0C,0xB0,0x00,0x68,0x03,0x88};
   rsuint8 RfLMX4x68DataUS_DECT[] = {0x1a,0x80,0x00,0x56,0x03,0x98};
   rsuint8 i;
   // printf("MailPtr->Address = %d %d %d %d %d \n", MailPtr->Address,isEU,isUS,isJP,DECTMASK);
   // printf("Read Address = %d Length = %d Data = %d %d %d %d %d  %d %d %d %d %d \n", MailPtr->Address,MailPtr->Length,
   //      MailPtr->Data[0],MailPtr->Data[1],MailPtr->Data[2],MailPtr->Data[3],MailPtr->Data[4],
   //      MailPtr->Data[5],MailPtr->Data[6],MailPtr->Data[7],MailPtr->Data[8],MailPtr->Data[9]);
   //return;

   if((MailPtr->Address==0x3d)&&(MailPtr->Status==RSS_SUCCESS)){
      DECTMASK = DECTMASK & 30;
      for (i=0;i<6;i++){
      if (MailPtr->Data[i]!=RfLMX4x68DataEU_DECT[i]){
         isEU=0;
      }
      }
   }
   if((MailPtr->Address==0x43)&&(MailPtr->Status==RSS_SUCCESS)){
      DECTMASK = DECTMASK & 30;
      for (i=0;i<6;i++){
      if (MailPtr->Data[i]!=RfLMX4x68DataUS_DECT[i]){
         isUS=0;
         isJP=0;
      }
      }
   }
   if((MailPtr->Address==0x2A)&&(MailPtr->Status==RSS_SUCCESS)){
      DECTMASK = DECTMASK & 29;
      if (MailPtr->Data[0]!=0){
         isEU=0;
      }
      if (MailPtr->Data[0]!=0xee){
         isUS=0;
      }
      if (MailPtr->Data[0]!=0xfd){
         isJP=0;
      }
   }
   if((MailPtr->Address==0x112)&&(MailPtr->Status==RSS_SUCCESS)){
      DECTMASK = DECTMASK & 27;
      if (MailPtr->Data[0]!=3){
               isEU=0;isUS=0;isJP=0;
      }
      if (MailPtr->Data[1]!=0xFF){
         isEU=0;
      }
      if (MailPtr->Data[1]!=0xe0){
         isUS=0;
      }
      if (MailPtr->Data[1]!=0xe0){
         isJP=0;
      }
   }
   if((MailPtr->Address==0x2c)&&(MailPtr->Status==RSS_SUCCESS)){
      DECTMASK = DECTMASK & 23;
      if (MailPtr->Data[0]!=0){
         isEU=0;
      }
      if (MailPtr->Data[0]!=1){
         isUS=0;
      }
       if (MailPtr->Data[0]!=1){
         isJP=0;
      }
   }
   if((MailPtr->Address==0xab)&&(MailPtr->Status==RSS_SUCCESS)){
      DECTMASK = DECTMASK & 15;
      if (MailPtr->Data[0]!=0x80){
         isEU=0;
      }
      if (MailPtr->Data[0]!=0x80){
         isUS=0;
      }
      if (MailPtr->Data[0]!=0x80){
         isJP=0;
      }
   }
   if (DECTMASK==0){
   ULE_PI_DectMode(1,3);
      if (isEU){
         ULE_PI_MSG("Dect Region is set to EUROPE \n");
         ULE_PI_DectMode(MailPtr->Status,0);
      }
      else if (isUS){
         ULE_PI_MSG("Dect Region is set to  US \n");
         ULE_PI_DectMode(MailPtr->Status,1);
      }
      else if (isJP){
         ULE_PI_MSG("Dect Region is set to JPN 5-CH \n");
         ULE_PI_DectMode(MailPtr->Status,2);
      }
      else{
         ULE_PI_MSG("Dect Region is set to CUSTOM \n");
         ULE_PI_DectMode(MailPtr->Status,3);
      }
   }
}


void ApiFpUleIPUICfm(ApiFpUleGetDeviceIpuiCfmType *p_mail) {
#if defined(CONFIG_CATIQ_V11_SUPPORT) || defined(CONFIG_CATIQ_V12_SUPPORT)
   ULE_PI_MSG("Dect Driver: ApiFpUleGetDeviceIpuiCfmType Received parameters:\n Device: %d\n IPUI: %d %d %d %d %d\n Status: %d\n",
         p_mail->TerminalId,(int)p_mail->IPUI[0],(int)p_mail->IPUI[1],(int)p_mail->IPUI[2],(int)p_mail->IPUI[3],(int)p_mail->IPUI[4],(int)p_mail->Status);
   ULE_GetIPUI_Cfm(p_mail->Status, p_mail->TerminalId, p_mail->IPUI);
#else
   ULE_PI_MSG("Dect Driver: ApiFpUleGetDeviceIpuiCfmType Received parameters:\n Device: %d\n IPUI: %d %d %d %d %d\n Status: %d\n",
         p_mail->DeviceId,(int)p_mail->IPUI[0],(int)p_mail->IPUI[1],(int)p_mail->IPUI[2],(int)p_mail->IPUI[3],(int)p_mail->IPUI[4],(int)p_mail->Status);
   ULE_GetIPUI_Cfm(p_mail->Status, p_mail->DeviceId, p_mail->IPUI);
#endif

}

void ApiFpUleInitCfm(ApiFpUleInitCfmType *MailPtr) {
   if ((!MailPtr->Status)||(MailPtr->Status==RSS_DUPLICATE)) {
      PRINT_MESSAGE("Dect Driver: API_FP_ULE_INIT_CFM received. Status: success \n");
      ULE_Set_SysInit(ULE_Init_Success);
   } else {
      PRINT_MESSAGE("->Dect Driver: API_FP_ULE_INIT_CFM received. Status: error --> %d\n ",MailPtr->Status);
      ULE_Set_SysInit(ULE_Init_Fail);
   }
}

void ApiFpUleDtrInd(ApiFpUleDtrIndType *p_mail) {

   ULE_PI_MSG(" \r\n Dect Driver:  DTR received.\n");

#ifdef CONFIG_CATIQ_V11_SUPPORT
   ULE_RTS_Rcv(p_mail->TerminalId);
#else
   ULE_RTS_Rcv(p_mail->PpNumber);
#endif
}


void HandleResetIndULE(void *MailPtr) {

   ULE_PI_MSG("Dect Driver: Reset \n");

   // if ENABLE_AUTO_RSX_TRACING is defined
   ULE_Enable_AutoRsxTracing();

   SendApiFpGetFwVersionReq(API_TASK);
   SendApiProdTestReq(API_TASK, 0x007C, 0, NULL); // Dect Mode
#if !defined(IPBS_452_BUILD) && !defined(HANFUN)
   HandleResetInd(MailPtr);
#endif
   SendApiFpFeaturesReq(API_TASK, API_FP_EXTENDED_TERMINAL_ID_SUPPORT);
   printf("Sending API_FP_MM_START_PROTOCOL_REQ  !!! \n");
   SendApiFpMmStartProtocolReq(API_TASK);

}


 void ApiFpGetFwVersionCfmULE(ApiFpGetFwVersionCfmType *MailPtr) {

   memset(VERSION,0,sizeof(VERSION));
#if defined(IPBS_452_BUILD)
	strcpy(VERSION, SC14450_VERSION);
#elif defined(WIN_BUILD)
	strcpy(VERSION,"WIN_BUILD");
#else
	strcpy(VERSION,"LINUX_BUILD");
#endif
#if defined(CONFIG_CVM480_DECT_SUPPORT)
   strcat(VERSION,":CVM:0");
#elif defined(IPBS_452_BUILD)
   strcat(VERSION,":LMX:");
#else
   strcat(VERSION,":CVMDECT_FP_HOST:");
#endif
   if (MailPtr->VersionHex !=0){
      char VER[10];
      sprintf(VER,"%x",(int)MailPtr->VersionHex);
      strcat(VERSION,VER);
   }
   else if ((MailPtr->LinkDate[0]==18)&&
      (MailPtr->LinkDate[1]==3)&&
      (MailPtr->LinkDate[2]==19)&&
      (MailPtr->LinkDate[3]==23)&&
      (MailPtr->LinkDate[4]==25)){
      strcat(VERSION,"711");
   }
   else if ((MailPtr->LinkDate[0]==18)&&
         (MailPtr->LinkDate[1]==6)&&
         (MailPtr->LinkDate[2]==40)&&
         (MailPtr->LinkDate[3]==8)&&
         (MailPtr->LinkDate[4]==55)){
         strcat(VERSION,"900");
   }
   else if ((MailPtr->LinkDate[0]==18)&&
            (MailPtr->LinkDate[1]==7)&&
            (MailPtr->LinkDate[2]==24)&&
            (MailPtr->LinkDate[3]==23)&&
            (MailPtr->LinkDate[4]==64)){
            strcat(VERSION,"901");
   }
   else{
      strcat(VERSION,"000");
   }
#ifdef CONFIG_SOUND
   strcat(VERSION,":VOIP_EN");
#else
   strcat(VERSION,":VOIP_DIS");
#endif

#ifdef IPBS_452_BUILD
	ULE_PI_MSG(" ##### %s SC14452_VERSION_DATE: %s SC14452_VERSION_STATUS: %s\n ", VERSION, SC14450_VERSION_DATE, SC14450_VERSION_STATUS);
	ULE_PI_MSG("##### Firmware version: %s CVMDECT Status: %d VersionHex: %x  LinkDate: %x:%x:%x:%x:%x \n ", SC14450_VERSION,
#else
   ULE_PI_MSG("\n#####################################################################################\n");
   ULE_PI_MSG("###  APPLICATION: %s\n", VERSION);
   ULE_PI_MSG("###  VERSION NUMBER: %s BUILD DATE: %s STATUS: N/A \n", BUILD_VERSION, BUILD_DATE);
   ULE_PI_MSG("###  Firmware version: FPCVM441 Status: %d VersionHex: %lx LinkDate: %x:%x:%x:%x:%x \n",
#endif
         MailPtr->Status,
         MailPtr->VersionHex,MailPtr->LinkDate[0],MailPtr->LinkDate[1],MailPtr->LinkDate[2],MailPtr->LinkDate[3],MailPtr->LinkDate[4]);
   ULE_PI_MSG("#####################################################################################\n");
}

 void ApiFpMmGetIdCfmULE(ApiFpMmGetIdCfmType *MailPtr) {
   ULE_PI_MSG("Dect Driver: ApiFpMmGetIdCfm. Received parameters: Status: %d Id: %X %X %X %X %X\n ",
               MailPtr->Status,
               MailPtr->Id[0],MailPtr->Id[1],MailPtr->Id[2],MailPtr->Id[3],MailPtr->Id[4]);

   ULE_GetRFPI_Cfm(MailPtr->Status, MailPtr->Id);
}
/****************************************************************************
 *  FUNCTION: ApiFpMmGetModelCfm
 *
 *  INPUTS  : mailpointer
 *  OUTPUTS : none
 *  RETURNS : none
 *
 *  DESCRIPTION: Handle API_FP_GET_MODEL_CFM
 ****************************************************************************/
 void ApiFpMmGetModelCfmULE(ApiFpMmGetModelCfmType *MailPtr) {
   ULE_PI_MSG("Dect Driver: ApiFpMmGetModelCfm. Received parameters: Status: %d ModelId: %d \n ",
         MailPtr->Status,(int)MailPtr->ModelId.MANIC);
}
/****************************************************************************
 *  FUNCTION: ApiFpMmSetAccessCodeCfm
 *
 *  INPUTS  : mailpointer
 *  OUTPUTS : none
 *  RETURNS : none
 *
 *  DESCRIPTION: Handle API_FP_MM_SET_ACCESS_CODE_CFM
 ****************************************************************************/
 void ApiFpMmSetAccessCodeCfmULE(ApiFpMmSetAccessCodeCfmType *MailPtr) {

   ULE_Set_Ac_Code_Write(MailPtr->Status);

}
/****************************************************************************
 *  FUNCTION: ApiFpMmGetAccessCodeCfm
 *
 *  INPUTS  : mailpointer
 *  OUTPUTS : none
 *  RETURNS : none
 *
 *  DESCRIPTION: Handle API_FP_MM_GET_ACCESS_CODE_CFM
 ****************************************************************************/
 void ApiFpMmGetAccessCodeCfmULE(ApiFpMmGetAccessCodeCfmType *MailPtr) {

   ULE_PI_MSG("Dect Driver:  API_FP_MM_GET_ACCESS_CODE_CFM, Current FP AC=0x%X 0x%X 0x%X 0x%X \n", MailPtr->Ac[0], MailPtr->Ac[1], MailPtr->Ac[2], MailPtr->Ac[3]);

   ULE_Get_Ac_Code_Write(MailPtr->Status, MailPtr->Ac[0], MailPtr->Ac[1], MailPtr->Ac[2], MailPtr->Ac[3]);
}
/****************************************************************************
 *  FUNCTION: ApiFpGetRegisterCfm
 *
 *  INPUTS  : mailpointer
 *  OUTPUTS : none
 *  RETURNS : none
 *
 *  DESCRIPTION: Handle API_FP_GET_REGISTER_CFM
 ****************************************************************************/
#if !defined(CONFIG_CATIQ_V11_SUPPORT) && !defined(CONFIG_CATIQ_V12_SUPPORT) //TBD: Change this part to support new HAL Api
 void ApiFpGetRegisterCfmULE(ApiFpGetRegisterCfmType *MailPtr) {

   ULE_PI_MSG("Dect Driver:  API_FP_MM_GET_REGISTRATION_CFM");

}
#endif
/******************************************************************************
 *                                 Registration                                  *
 ******************************************************************************/
/****************************************************************************
 *  FUNCTION: ApiFpMmGetRegistrationCountCfm
 *
 *  INPUTS  : mailpointer
 *  OUTPUTS : none
 *  RETURNS : none
 *
 *  DESCRIPTION: Handle API_FP_GET_REGISTRATION_COUNT_CFM
 *               Set correct callstate of handsets
 ****************************************************************************/

 void ApiFpMmGetRegistrationCountCfmULE(ApiFpMmGetRegistrationCountCfmType *MailPtr) {

#if defined(CONFIG_CATIQ_V11_SUPPORT) || defined(CONFIG_CATIQ_V12_SUPPORT)
      ULE_PI_MSG("Dect Driver:  Received parameters:\n Status: %d\n MaxNoHandsets: %d\n TerminalIdCount: %d\n",
            MailPtr->Status,
            MailPtr->MaxNoHandsets,
            MailPtr->TerminalIdCount);
#else
      ULE_PI_MSG("Dect Driver:  Received parameters:\n Status: %d\n MaxNoHandsets: %d\n HandsetIdLength: %d\n",
            MailPtr->Status,
            MailPtr->MaxNoHandsets,
            MailPtr->HandsetIdLength);
#endif


   //ULE_Get_Registration_Count_Cfm (MailPtr);

}
/****************************************************************************
 *  FUNCTION: ApiFpMmDeleteRegistrationCfm
 *
 *  INPUTS  : mailpointer
 *  OUTPUTS : none
 *  RETURNS : none
 *
 *  DESCRIPTION: Handle API_FP_MM_DELETE_REGISTRATION_CFM
 *
 ****************************************************************************/
 void ApiFpMmDeleteRegistrationCfmULE(ApiFpMmDeleteRegistrationCfmType *MailPtr) {

#if defined(CONFIG_CATIQ_V11_SUPPORT) || defined(CONFIG_CATIQ_V12_SUPPORT)

      if (!MailPtr->Status) {
         ULE_PI_MSG("Dect Driver:  API_FP_DELETE_REGISTRATION_CFM. Succesfully deleted device %d\n",
               MailPtr->TerminalId);
      } else {
         ULE_PI_MSG("Dect Driver:  API_FP_DELETE_REGISTRATION_CFM. Failed to delete device %d. Error status: %d\n",
               MailPtr->TerminalId,
               MailPtr->Status);
      }
      ULE_Deregister_Cfm(MailPtr->Status, MailPtr->TerminalId);
#else
      if (!MailPtr->Status) {
         ULE_PI_MSG("Dect Driver:  API_FP_DELETE_REGISTRATION_CFM. Succesfully deleted device %d\n",
               MailPtr->HandsetId);
      } else {
         ULE_PI_MSG("Dect Driver:  API_FP_DELETE_REGISTRATION_CFM. Failed to delete device %d. Error status: %d\n",
               MailPtr->HandsetId,
               MailPtr->Status);
      }
      ULE_Deregister_Cfm(MailPtr->Status, MailPtr->HandsetId);
#endif

}

/****************************************************************************
 *  FUNCTION: ApiFpMmRegistrationCompleteInd
 *
 *  INPUTS  : mailpointer
 *  OUTPUTS : none
 *  RETURNS : none
 *
 *  DESCRIPTION: Handle API_FP_REGISTRATION_COMPLETE_IND
 ****************************************************************************/
 void ApiFpMmRegistrationCompleteIndULE(ApiFpMmRegistrationCompleteIndType *MailPtr) {
#if defined(CONFIG_CATIQ_V11_SUPPORT) || defined(CONFIG_CATIQ_V12_SUPPORT)
   ULE_PI_MSG("Dect Driver:  Registration complete: TerminalId %d \n...", MailPtr->TerminalId);
   ULE_PP_add(MailPtr->TerminalId);
#else
   ULE_PI_MSG("Dect Driver:  Registration complete: PpNumber %d \n...", MailPtr->HandsetId);
   ULE_PP_add(MailPtr->HandsetId);
#endif

}
/****************************************************************************
 *  FUNCTION: ApiFpMmHandsetPresentInd
 *
 *  INPUTS  : mailpointer
 *  OUTPUTS : none
 *  RETURNS : none
 *
 *  DESCRIPTION: Handle API_FP_HANDSET_PRESENT_IND
 *               Set correct callstate of handset
 ****************************************************************************/
 void ApiFpMmHandsetPresentIndULE(ApiFpMmHandsetPresentIndType *MailPtr) {


#if defined(CONFIG_CATIQ_V11_SUPPORT) || defined(CONFIG_CATIQ_V12_SUPPORT)
   ULE_PI_MSG("Dect Driver12345:  Handset present indication: TerminalId %i\n...",MailPtr->TerminalId);

   if (fwsApiFpMmHandsetPresentInd(MailPtr)) return;
   ULE_PP_add(((ApiFpMmHandsetPresentIndType *) MailPtr)->TerminalId);

#else
   uint8 TerminalId = MailPtr->HandsetId;
   ULE_PI_MSG("Dect Driver:  Handset present indication: PpNumber %i\n...",MailPtr->HandsetId);
   if (fwsApiFpMmHandsetPresentInd(MailPtr)) return;
   ULE_PP_add(((ApiFpMmHandsetPresentIndType *) MailPtr)->HandsetId);
#endif
}


/****************************************************************************
 *  FUNCTION: ApiFpUleServiceInd
 *
 *  INPUTS  : mailpointer
 *  OUTPUTS : none
 *  RETURNS : none
 *
 *  DESCRIPTION: Handle API_FP_MM_GET_HANDSET_IPUI_CFM
 ****************************************************************************/
#if !defined(CONFIG_CATIQ_V11_SUPPORT) && !defined(CONFIG_CATIQ_V12_SUPPORT)
 void ApiFpUleServiceInd(ApiFpUleServiceIndType* MailPtr) {

   // Note: connection parameters are hard coded in the app_pp function...
   ApiFpUleServiceResType m_data;
   ApiFpUleServiceResType *m = &m_data; // container

   ULE_PI_MSG("Dect Driver:  API_FP_ULE_SERVICE_RES - PpNumber: %d\n",MailPtr->PpNumber);

   m->Status = RSS_SUCCESS;

   if ((MailPtr->Bandwidth == 0) && (MailPtr->DownlinkRedundant == 0) && (MailPtr->ContentionLatency == 0)
         && (MailPtr->MaxDutyCycle == 0)) {

      m->UlpFrameLenDown = 0;
      m->DownlinkFrame = 0;
      m->DownlinkRedundant = 0;
      m->UlpFrameLenUp = 0;
      m->UplinkStartFrame = 0;
      m->UplinkEndFrame = 0;
      m->Slotsize = 1;
   } else {

      // sync device
      //m->UlpFrameLenDown   = lpitem->Config.UlpFrameLenDown ;
      m->UlpFrameLenDown = MailPtr->MaxDutyCycle;
      m->DownlinkFrame = (unsigned short) (MailPtr->PpNumber * 2);
      m->DownlinkRedundant = 1;
      m->UlpFrameLenUp = 8;
      m->UplinkStartFrame = 128;
      m->UplinkEndFrame = 255;
      m->Slotsize = 1;

   }

   ULE_PI_MSG("<-API_FP_ULE_SERVICE_RES - PpNumber: %d\n SyncMode: %X\n UlpFrameLenDown: %X\n DownlinkFrame: %X\n DownlinkRedundant: %X\n UlpFrameLenUp: %X\n UplinkStartFrame: %X\n UplinkEndFrame: %X\n Slotsize: %X\n",
         MailPtr->PpNumber,
         m->Status,
         m->UlpFrameLenDown,
         m->DownlinkFrame,
         m->DownlinkRedundant,
         m->UlpFrameLenUp,
         m->UplinkStartFrame,
         m->UplinkEndFrame,
         m->Slotsize);

   SendApiFpUleServiceRes(API_TASK, MailPtr->PpNumber, m->Status, m->UlpFrameLenDown, m->DownlinkFrame,
         m->DownlinkRedundant, m->UlpFrameLenUp, m->UplinkStartFrame, m->UplinkEndFrame, m->Slotsize);

}
#endif


 /****************************************************************************
  *  FUNCTION: HandleApiProdTestCfm
  *
  *  INPUTS  : mailpointer
  *  OUTPUTS : none
  *  RETURNS : none
  *
  *  DESCRIPTION: Handle API_PROD_TEST_CFM
  ****************************************************************************/
void HandleApiProdTestCfm(ApiProdTestCfmType* MailPtr) {

   switch (MailPtr->Opcode) {

        case 0x007C: // PT_CMD_GET_DECT_MODE
        {
         rsuint8 dectMode = (rsuint8) MailPtr->Parameters[0];

         if (dectMode == 0x00){
            ULE_PI_MSG("Dect Region is set to EUROPE \n");
            ULE_PI_DectMode(RSS_SUCCESS,0);
         }
         else if (dectMode == 0x01){
            ULE_PI_MSG("Dect Region is set to  US \n");
            ULE_PI_DectMode(RSS_SUCCESS,1);
         }
         else if (dectMode == 0x0B){
            ULE_PI_MSG("Dect Region is set to JPN 5-CH \n");
            ULE_PI_DectMode(RSS_SUCCESS,2);
         }
         else{
            ULE_PI_MSG("Dect Region is set to CUSTOM \n");
            ULE_PI_DectMode(RSS_SUCCESS,3);
         }


         break;
        }
        default:
           break;

   }


}


/******************************************************************************
 *                NOTE: following functions not used for ULE                  *
 ******************************************************************************/
#if 0

static void ApiFpCcSetupInd(ApiFpCcSetupIndType *MailPtr)
{
   ApiFpCcAudioIdType AudioId;
   ApiInfoElementType *IeBlockPtr = NULL;
   rsuint16 IeBlockLength = 0;
   ApiSystemCallIdType mSystemCallId[2];
   rsuint16 i,reject_call=0,multikeypadLength = 0;
   ApiIa5CharType *pMultikeypad = NULL;
   ApiSystemCallIdType SystemCallIdTmp;

   printf("\n ApiFpCcSetupInd: TerminalId %d BasicService %d CallClass %d Instance %d Value %d \n",MailPtr->TerminalId,MailPtr->BasicService,MailPtr->CallClass,MailPtr->CallReference.Instance,MailPtr->CallReference.Value);

    if (MailPtr->InfoElementLength > 0)
     {
       ApiInfoElementType *pIe = NULL;

       pIe = ApiGetInfoElement((ApiInfoElementType*)MailPtr->InfoElement,
                                MailPtr->InfoElementLength,
                                API_IE_SYSTEM_CALL_ID);
       if (pIe != NULL)
       {
         /*SystemCallId. */SystemCallIdTmp.ApiSubId         = ((ApiSystemCallIdType*)(pIe->IeData))->ApiSubId;
         /*SystemCallId.*/ SystemCallIdTmp.ApiSystemCallId  = ((ApiSystemCallIdType*)(pIe->IeData))->ApiSystemCallId;
         printf("\n ApiFpCcSetupInd ApiSubId %d ApiSystemCallId %d \n",SystemCallIdTmp.ApiSubId ,SystemCallIdTmp.ApiSystemCallId);

       }
     }




   AudioId.IntExtAudio=API_IEA_INT;
   AudioId.SourceTerminalId=MailPtr->TerminalId;
   AudioId.AudioEndPointId=0;
   //SetupindRcv_callref = MailPtr->CallReference;
   SendApiFpCcSetupRes(API_TASK, MailPtr->CallReference, RSS_SUCCESS, AudioId);

   mSystemCallId[0].ApiSubId         = SystemCallIdTmp.ApiSubId;//SystemCallId.ApiSubId;
   mSystemCallId[0].ApiSystemCallId  = SystemCallIdTmp.ApiSystemCallId;//SystemCallId.ApiSystemCallId;

   ApiCallStatusListType CallStatusListValue;
   CallStatusListValue.ApiCallStatus[0].CallStatusSubId = API_SUB_CALL_STATUS;
   CallStatusListValue.ApiCallStatus[0].CallStatusValue.Value = API_CSS_CALL_SETUP_ACK;
   ApiBuildInfoElement(&IeBlockPtr, &IeBlockLength, API_IE_SYSTEM_CALL_ID, sizeof(ApiSystemCallIdType), (rsuint8*)&mSystemCallId[0]);
   ApiBuildInfoElement(&IeBlockPtr, &IeBlockLength, API_IE_CALL_STATUS, sizeof(ApiCallStatusListType), (rsuint8*)&CallStatusListValue);
   SendApiFpCcSetupAckReq(API_TASK, MailPtr->CallReference, API_CC_SIGNAL_DIAL_TONE_ON, API_IN_BAND_AVAILABLE, IeBlockLength, (rsuint8*)IeBlockPtr);
   ApiFreeInfoElement(&IeBlockPtr);IeBlockLength=0;IeBlockPtr = NULL;



}
#endif
/****************************************************************************
 *  FUNCTION: mail_switch
 *
 *  INPUTS  : mailpointer
 *  OUTPUTS : none
 *  RETURNS : none
 *
 *  DESCRIPTION: Handle incoming messages
 ****************************************************************************/
void mail_switch(unsigned short Length, unsigned char *MailPtr);

static char IsSensor=0;


char ULE_mail_switch(unsigned short Length, unsigned char *MailPtr) {

	//int i;
	//printf("\n ULE_mail_switch: Len: %02d Data: ", Length);
	//for(i=0;i<Length; i++){
	//	printf ("%x ", MailPtr[i]);
	//}
	//printf("\n Prim: 0x%04X \n ", *(PrimitiveType*) MailPtr);

   mail_switch( Length, MailPtr);

   switch (*(PrimitiveType*) MailPtr) {

   /*******************************
    *         Management           *
    *******************************/



   //case API_FP_INIT_PCM_CFM:
   //   printf("\n API_FP_INIT_PCM_CFM status: %d \n",((ApiFpInitPcmCfmType*)MailPtr)->Status);
   //   break;

   //case API_FP_CC_SETUP_IND:
   //     ApiFpCcSetupInd((ApiFpCcSetupIndType*)MailPtr);
   //     break;


   case API_FP_RESET_IND:
      HandleResetIndULE(MailPtr);
      break;

   case API_FP_GET_FW_VERSION_CFM:
      ApiFpGetFwVersionCfmULE((ApiFpGetFwVersionCfmType*) MailPtr);
      break;

   case API_FP_MM_GET_ID_CFM:
      ApiFpMmGetIdCfmULE((ApiFpMmGetIdCfmType*) MailPtr);
      break;

   case API_FP_MM_GET_MODEL_CFM:
      ApiFpMmGetModelCfmULE((ApiFpMmGetModelCfmType*) MailPtr);
      break;

   case API_FP_MM_SET_ACCESS_CODE_CFM:
      ApiFpMmSetAccessCodeCfmULE((ApiFpMmSetAccessCodeCfmType*) MailPtr);
      break;

   case API_FP_MM_GET_ACCESS_CODE_CFM:
      ApiFpMmGetAccessCodeCfmULE((ApiFpMmGetAccessCodeCfmType*) MailPtr);
      break;

#if !defined(CONFIG_CATIQ_V11_SUPPORT) && !defined(CONFIG_CATIQ_V12_SUPPORT) //TBD: Change this part to support new HAL Api
   case API_FP_GET_REGISTER_CFM:
      ApiFpGetRegisterCfmULE((ApiFpGetRegisterCfmType*) MailPtr);
      break;
#endif
      /*******************************
       *        Registration          *
       *******************************/
   case API_FP_MM_GET_REGISTRATION_COUNT_CFM:
      ApiFpMmGetRegistrationCountCfmULE((ApiFpMmGetRegistrationCountCfmType*) MailPtr);
      break;
   case 0x4193:
   case API_FP_MM_DELETE_REGISTRATION_CFM:
      ApiFpMmDeleteRegistrationCfmULE((ApiFpMmDeleteRegistrationCfmType*) MailPtr);
      break;
   case API_FP_MM_SET_REGISTRATION_MODE_CFM:
      ApiFpMmSetRegistrationModeCfmULE((ApiFpMmSetRegistrationModeCfmType*) MailPtr);
      break;
   case API_FP_MM_REGISTRATION_COMPLETE_IND:
      ApiFpMmRegistrationCompleteIndULE((ApiFpMmRegistrationCompleteIndType*) MailPtr);
      break;
	case API_FP_MM_REGISTRATION_FAILED_IND:
		{
		ApiFpMmRegistrationFailedIndType *ptr = (ApiFpMmRegistrationFailedIndType* ) MailPtr;
		PRINT_MESSAGE("Registration Failed: Reason: 0x%02X IPUI: %02X %02X %02X %02X %02X \n", ptr->Reason, ptr->IPUI[0], ptr->IPUI[1], ptr->IPUI[2], ptr->IPUI[3], ptr->IPUI[4]);
		}
		break;
   case API_FP_MM_HANDSET_PRESENT_IND:
	   ULE_PI_MSG("Dect Driver12345:  Handset present indication: TerminalId \n...");
#ifndef HANFUN
      ApiFpMmHandsetPresentIndULE((ApiFpMmHandsetPresentIndType*) MailPtr);
#endif
      break;

   case API_FP_MM_GET_HANDSET_IPUI_CFM:
      //ApiFpMmGetHandsetIpuiCfm((ApiFpMmGetHandsetIpuiCfmType*) MailPtr);
      break;
   case API_FP_MM_HANDSET_DEREGISTERED_IND:
      ULE_PI_MSG("Device successfully deregistered \n");
      break;
      /************************************
       *    ULE NOTIFICATIONS             *
       *************************************/
#if !defined(CONFIG_CATIQ_V11_SUPPORT) && !defined(CONFIG_CATIQ_V12_SUPPORT)
   case API_FP_ULE_SERVICE_IND:
      ApiFpUleServiceInd((ApiFpUleServiceIndType*) MailPtr);
      break;
#endif
   case API_FP_ULE_INIT_CFM:
      ApiFpUleInitCfm((ApiFpUleInitCfmType*) MailPtr);
      break;
   case API_FP_ULE_DATA_IND:
      ApiFpUleDataInd((ApiFpUleDataIndType *) MailPtr);
      break;
   case API_FP_ULE_DTR_IND:
	   TxBuff_LastTxStatus(((ApiFpUleDtrIndType *)MailPtr)->TerminalId,((ApiFpUleDtrIndType *)MailPtr)->Status);
#ifndef HANFUN
      ApiFpUleDtrInd((ApiFpUleDtrIndType *) MailPtr);
#endif
       //printf("\n  SendApiFpUleGetDeviceIpuiReq(API_TASK, 977777798); \n");
       // SendApiFpUleGetDeviceIpuiReq(API_TASK, 7);
      //TxBuff_Send();
      break;
#if defined(CONFIG_CATIQ_V11_SUPPORT) || defined(CONFIG_CATIQ_V12_SUPPORT)
   case API_FP_ULE_DATA_CFM:
      ApiFpUleDataRejCfm((ApiFpUleDataCfmType *) MailPtr);
#else
   case 0x418B:
      ApiFpUleDataRejCfm((ApiFpUleDataRejectIndType *) MailPtr);
#endif
      break;
   case API_FP_ULE_GET_REGISTRATION_COUNT_CFM:
      ApiFpUleGetRegistrationCountCfm((ApiFpUleGetRegistrationCountCfmType*) MailPtr);
      break;
   case API_FP_ULE_ABORT_DATA_CFM:
      ApiFpUleAbortCfm((ApiFpUleAbortDataCfmType*) MailPtr);
      break;
   case API_FP_ULE_GET_DEVICE_IPUI_CFM:
      ApiFpUleIPUICfm((ApiFpUleGetDeviceIpuiCfmType*) MailPtr);
      break;
   case API_HAL_READ_CFM:
      ApiFpHALReadCfm((ApiHalReadCfmType*) MailPtr);
      break;
   //case API_474A_DUMMY: //*! This mail is sent from the SUOTA client to the MMI to provide status info (ApiSclStatusIndType)
   //   break;
    case API_PROD_TEST_CFM:
       HandleApiProdTestCfm((ApiProdTestCfmType*) MailPtr);
       break;

    case API_FP_ULE_PVC_CONFIG_CFM:
    	printf("SendApiFpUleDatapoll %d \n",((ApiFpUlePvcConfigCfmType*) MailPtr)->TerminalId);
    	// SendApiFpUleDataPollReq (API_TASK,((ApiFpUlePvcConfigCfmType*) MailPtr)->TerminalId,0x10);
    	nxt_realease_reason=0x10;
        SendApiFpUleDatapoll(API_TASK,((ApiFpUlePvcConfigCfmType*) MailPtr)->TerminalId,0x10,NULL);
       break;
    case API_FP_ULE_PVC_CONFIG_REJ:

       break;
    case API_FP_ULE_PVC_CONFIG_IND:
      {
        ApiFpUleProtocol_t Protocol= { API_ULE_PROTOCOL_FUN_1, API_ULE_PROTOCOL_VERSION_0, 0};
       IsSensor=0;

       SendApiFpUlePvcConfigRes (API_TASK, ((ApiFpUlePvcConfigIndType *)MailPtr)->TerminalId, API_ULE_PP_INITIATOR,
                                                API_ULE_MTU_SIZE_MAX, API_ULE_MTU_SIZE_MAX,
                                                API_ULE_MTU_LIFETIME_DEFAULT, API_ULE_WINDOW_SIZE_DEFAULT,
                                                1, &Protocol);
      }
      break;

#ifndef HANFUN
    case API_FP_ULE_PVC_PENDING_IND:
      {
          ApiFpUlePage_t Page[2] = { { 0, 0, 0 } };
          if(IsSensor==1){
        	  printf(">>> IS_SENSOR!!! <<< \n");
         	 SendApiFpUlePvcPendingRes(API_TASK, ((ApiFpUlePvcConfigIndType *) MailPtr)->TerminalId, API_FP_ULE_ERR_NO_ERROR, 1, Page);
          }

          IsSensor=1;
      //  ApiFpUlePage_t Page[2]= {{API_ULE_PAGING_CH, 17, 2},{0,0,0}};
      // SendApiFpUlePvcPendingRes ( API_TASK, ((ApiFpUlePvcConfigIndType *)MailPtr)->TerminalId,
      //                             API_FP_ULE_ERR_NO_ERROR , 0, NULL);

      }
      break;

    case API_FP_ULE_PVC_IWU_DATA_IND:
      {
          IsSensor=0;
       // ApiFpUlePvcIwuDataIndType *pIwu= (ApiFpUlePvcIwuDataIndType*) MailPtr;
        ApiFpUlePage_t Page[2]= {{API_ULE_PAGING_CH, 10 + ((ApiFpUlePvcIwuDataIndType*) MailPtr)->TerminalId, 2},{0,0,0}};

        // SendApiFpUlePvcIwuDataReq(API_TASK, pIwu->TerminalId, pIwu->InfoElementLength, (rsuint8*)pIwu->InfoElement);
        SendApiFpUlePvcPendingRes (API_TASK, ((ApiFpUlePvcConfigIndType *)MailPtr)->TerminalId,
                                   API_FP_ULE_ERR_NO_ERROR , 1, Page);
      }
      break;
#endif

#ifdef DECT_FUNCTIONS
         /******************************************************************************************/
         // FWU.
         //API_FP_FWU_ENABLE_REQ = 0x4F00,

       case API_FP_FWU_ENABLE_CFM:
         HandleApiFpFwuEnableCfm((const ApiFpFwuEnableCfmType*)MailPtr);
         break;

       case API_FP_FWU_DEVICE_NOTIFY_IND:
         HandleApiFpFwuDeviceNotifyInd((const ApiFpFwuDeviceNotifyIndType*)MailPtr);
         // fwu->MlNotifyInd((const ApiFpFwuDeviceNotifyIndType*)mail);
         break;

         //API_FP_FWU_UPDATE_REQ = 0x4F03,

       case API_FP_FWU_UPDATE_CFM:
         HandleApiFpFwuUpdateCfm((const ApiFpFwuUpdateCfmType*)MailPtr);
         // fwu->MlUpdateCfm((const ApiFpFwuUpdateCfmType*)mail);
         break;

       case API_FP_FWU_UPDATE_IND:
         HandleApiFpFwuUpdateInd((const ApiFpFwuUpdateIndType*)MailPtr);
         // fwu->MlUpdateInd((const ApiFpFwuUpdateIndType*)mail);
         break;

         //API_FP_FWU_UPDATE_RES = 0x4F06,

       case API_FP_FWU_GET_BLOCK_IND:
         HandleApiFpFwuGetBlockInd((const ApiFpFwuGetBlockIndType*)MailPtr);
         break;

         //API_FP_FWU_GET_BLOCK_RES = 0x4F08,

       case API_FP_FWU_GET_CRC_IND:
         HandleApiFpFwuGetCrcInd((const ApiFpFwuGetCrcIndType*)MailPtr);
         break;

         //API_FP_FWU_GET_CRC_RES = 0x4F0A,

       case API_FP_FWU_COMPLETE_IND:
         HandleApiFpFwuCompleteInd((const ApiFpFwuCompleteIndType*)MailPtr);
         break;

       case API_FP_FWU_STATUS_IND:
         HandleApiFpFwuStatusInd((const ApiFpFwuStatusIndType*)MailPtr);
         break;

       case API_FP_FWU_MULTI_CRC_IND:
         HandleApiFpFwuMultiCrcInd((const ApiFpFwuMultiCrcIndType*)MailPtr);
         break;
#else
#if !defined(CONFIG_CATIQ_V11_SUPPORT) && !defined(CONFIG_CATIQ_V12_SUPPORT)
       case API_FP_INIT_PCM_CFM:
       case API_FP_FWU_DEVICE_NOTIFY_IND:
       case API_FP_FWU_UPDATE_IND:
       case API_FP_FWU_STATUS_IND:
          break;
#endif
#endif
       case 0x4F02: // API_FP_FWU_DEVICE_NOTIFY_IND, shows up in v1112,1114
          break;
//       case 0x4015:
//          printf("%x %x : %d : %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x \n  ",MailPtr[3],MailPtr[4],MailPtr[5],
//                MailPtr[6],MailPtr[7],MailPtr[8],MailPtr[9],MailPtr[10],MailPtr[11],MailPtr[12],MailPtr[13],
//                MailPtr[14],MailPtr[15],MailPtr[16],MailPtr[17],MailPtr[18],MailPtr[19],MailPtr[20],MailPtr[21]);
       break;
   default:
   //   ULE_DefaultDectHandler(MailPtr);
      break;

   }
   return 0;
}
