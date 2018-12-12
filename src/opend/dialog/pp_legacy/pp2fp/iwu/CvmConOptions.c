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
/***************************************************************************
*                               Include files
****************************************************************************/
#include <Core/RtxCore.h>
#include <ProjCfg.h>
#include <PortDef.h>
#include <Ros/RosCfg.h>

#include <RtxEai/RtxEai.h>
#include "HostUtil.h"
#include "DynTim.h"
//#include "KeyboardCfg.h"
#include <Phoenix/Api/Api.h>
#if RC_HEAP_IMPLEMENTATION == RHI_USER
#include "malloc.h"
#include "stdlib.h"
#endif

/****************************************************************************
*                              Macro definitions
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/
typedef enum CvmConOptionsStates
{
  CVMCON_STATE_INIT,            // 0x00
  CVMCON_STATE_IDLE,            // 0x01
  CVMCON_STATE_TOGGLE_STACK,    // 0x02
  CVMCON_STATE_TOGGLE_COLA,     // 0x03
  CVMCON_STATE_TOGGLE_DECTMODE, // 0x04
} CvmConOptionsStates;
CvmConOptionsStates CvmConOptionsState = CVMCON_STATE_INIT;

/****************************************************************************
*                            Global variables/const
****************************************************************************/
rsuint8 ImgCfgStatus[3] = { RSS_NOT_FOUND, RSS_NOT_FOUND, RSS_NOT_FOUND};
rsbool CvmConOptionsHelpState = FALSE;
rsuint8 DectModeRequested = 0xFF;

/****************************************************************************
*                            Function declarations
****************************************************************************/
//extern void rsx_InitTask(rsuint32 iTaskId, char *szTaskName, rsuint32 iKeyPrimitive, TaskWindowPtr FunkPtr);
extern void rsx_SendMail(rsuint32 iTaskId, rsuint32 iLength, rsuint8 *bDataPtr);
extern void rsx_SendMailP1(rsuint32 iTaskId, rsuint16 Primitive, rsuint8 bParm1);
extern void rsx_SendMailP2(rsuint32 iTaskId, rsuint16 Primitive, rsuint8 bParm1, rsuint8 bParm2);



/****************************************************************************
* Name   : HandleCvmConOptions
* Input  :
* Output :
*---------------------------------------------------------------------------
* Usage  : 
****************************************************************************/
void HandleCvmConOptions(const RosMailType* MailPtr)
{
  switch (MailPtr->Primitive)
  {
    case INITTASK:
      {
        #define PT_CMD_GET_DECT_MODE 0x007C  
        SendApiProdTestReq(API_TASK,  (rsuint16)PT_CMD_GET_DECT_MODE, 0, NULL);
      }
      break;
    
    case API_FP_RESET_IND:
    case API_PP_RESET_IND:
      Printf("RX: API_XP_RESET_IND\n");
      if(CvmConOptionsState == CVMCON_STATE_TOGGLE_STACK)
      {
        typedef struct
        {
          rsbool FactoryDefault; 
        } PtNvsDefaultReqType;
        #define PT_CMD_NVS_DEFAULT 0x0102
        PtNvsDefaultReqType *PtNvsDefaultReqPtr = (PtNvsDefaultReqType*)RcHeapAllocEx(sizeof(PtNvsDefaultReqType), RHF_NULL_ON_FULL);
        PtNvsDefaultReqPtr->FactoryDefault = 1; //forced default
        SendApiProdTestReq(API_TASK,  (rsuint16)PT_CMD_NVS_DEFAULT, (rsuint16)sizeof(PtNvsDefaultReqType), (rsuint8*)PtNvsDefaultReqPtr);
        RcHeapFreeEx(PtNvsDefaultReqPtr, RHF_NULL_ON_FULL);
        Printf("Defauling the eeprom...\n");
        Printf("Please switch to the appropriate CvmCon matching the \n");
        Printf("primitive and eeprom layout of the selected image.\n\n");
      }
      CvmConOptionsState = CVMCON_STATE_IDLE;
      break;

    case KEY_MESSAGE:
      switch(MailPtr->P1.P1)
      {
        // case 0xF1: //PC 'F1' funtion key
        // if(CvmConOptionsHelpState==TRUE)
        // {
        //   Printf("EXTENDED CVMCON PRODTEST OPTIONS:\n");
        //   Printf("  'F7'=Get StackInfo (Id, LinkDate, SwVerion, DectMode)\n");
        //   Printf("           OTPInfo (Id, Modulation, Freq, Bandgap)\n");
        //   Printf("  'F8'=Get ImageCfg (Status on FP/PP Stack and COLA)\n");
        //   Printf("  'F9'=Toggle between DectModes\n");
        //   Printf(" 'F11'=Toggle between FP/PP StackImage (and default eeprom)\n");
        //   Printf(" 'F12'=Toggle between COLA Enabled/Disabled\n");
        //   Printf("---------------------------------------------------------------\n");
        //   CvmConOptionsHelpState=FALSE;
        //   return;
        // }
        // break;


        //case 0xF6: //PC 'F6' funtion key
        case 0x73: //PC 's' funtion key
          Printf("\nAPI_PROD_TEST_REQ (NvsDefault)\n");
          {
            #define PT_CMD_NVS_DEFAULT 0x0102
            typedef struct
            {
              rsbool FactoryDefault;
            } PtNvsDefaultReqType;
            PtNvsDefaultReqType *PtParametersPtr = (PtNvsDefaultReqType*)RcHeapAllocEx(sizeof(PtNvsDefaultReqType), RHF_NULL_ON_FULL);
            PtParametersPtr->FactoryDefault = 1; //Forced Default
            SendApiProdTestReq(API_TASK,  (rsuint16)PT_CMD_NVS_DEFAULT, (rsuint16)sizeof(PtNvsDefaultReqType), (rsuint8*)PtParametersPtr);
            RcHeapFreeEx(PtParametersPtr, RHF_NULL_ON_FULL);
          }
          return;

        // case 0xF7: //PC 'F7' funtion key
        case 0x64: //PC 'd' funtion key
          Printf("\nAPI_PROD_TEST_REQ (StackInfo)\n");
          {
            #define PT_CMD_GET_ID   0x001C  
            #define PT_CMD_GET_SW_LINK_DATE 0x0029  
            #define PT_CMD_GET_SW_VERSION 0x0016
            #define PT_CMD_GET_DECT_MODE 0x007C  
            SendApiProdTestReq(API_TASK,  (rsuint16)PT_CMD_GET_ID   , 0, NULL);
            SendApiProdTestReq(API_TASK,  (rsuint16)PT_CMD_GET_SW_LINK_DATE, 0, NULL);
            SendApiProdTestReq(API_TASK,  (rsuint16)PT_CMD_GET_SW_VERSION, 0, NULL);
            SendApiProdTestReq(API_TASK,  (rsuint16)PT_CMD_GET_DECT_MODE, 0, NULL);
          }
          {
            #define PT_GET_OTP_DATA   0x0703 
            typedef struct
            {
              rsuint32 Address; //!< The address of the first byte to read.
              rsuint8 Length; //!< The number of bytes to read.
            } PtGetOtpDataReqType;  

            PtGetOtpDataReqType *PtParametersPtr = (PtGetOtpDataReqType*)RcHeapAllocEx(sizeof(PtGetOtpDataReqType), RHF_NULL_ON_FULL);
            PtParametersPtr->Address = 0x00000000;
            PtParametersPtr->Length = 10;

            SendApiProdTestReq(API_TASK,  (rsuint16)PT_GET_OTP_DATA, (rsuint16)sizeof(PtGetOtpDataReqType), (rsuint8*)PtParametersPtr);
            RcHeapFreeEx(PtParametersPtr, RHF_NULL_ON_FULL);
          }
          return;

        // case 0xF8: //PC 'F8' funtion key
        case 0x66: //PC 'f' funtion key
          Printf("\nAPI_PROD_TEST_REQ (ImageInfo)\n");
          CvmConOptionsState = CVMCON_STATE_IDLE;
          SendApiImageInfoReq ( API_TASK, 0);
          SendApiImageInfoReq ( API_TASK, 1);
          SendApiImageInfoReq ( API_TASK, 2);
          return;

        //case 0xF9: //PC 'F9' funtion key
        case 0x67: //PC 'g' funtion key
//          Printf("\nAPI_PROD_TEST_REQ (Switch Dectmode)\n");
          if(CvmConOptionsState == CVMCON_STATE_IDLE)
          {
            #define PT_CMD_GET_DECT_MODE 0x007C  
            SendApiProdTestReq(API_TASK,  (rsuint16)PT_CMD_GET_DECT_MODE, 0, NULL);
            CvmConOptionsState = CVMCON_STATE_TOGGLE_DECTMODE;
            DectModeRequested = 0xFF; //no mode
          }
          break;

        // case 0xFB: //PC 'F11' funtion key
        case 0x68: //PC 'h' funtion key
          Printf("\nAPI_PROD_TEST_REQ (Toggle Stack)\n");
          CvmConOptionsState = CVMCON_STATE_TOGGLE_STACK;
          SendApiImageInfoReq ( API_TASK, 0);
          SendApiImageInfoReq ( API_TASK, 1);
          SendApiImageInfoReq ( API_TASK, 2);
          return;

        // case 0xFC: //PC 'F12' funtion key
        case 0x6A: //PC 'j' funtion key
          Printf("\nAPI_PROD_TEST_REQ (Toggle Cola)\n");
          CvmConOptionsState = CVMCON_STATE_TOGGLE_COLA;
          SendApiImageInfoReq ( API_TASK, 0);
          SendApiImageInfoReq ( API_TASK, 1);
          SendApiImageInfoReq ( API_TASK, 2);
          return;
      }
      break;

    case API_PROD_TEST_CFM:
      switch(((ApiProdTestCfmType*)MailPtr)->Opcode)
      {
        case PT_CMD_GET_ID:
           {
            typedef struct
            {
              rsuint8 Id[5]; //!< The RFPI/IPEI.
            } PtGetIdCfmType;

            ApiProdTestCfmType *k = (ApiProdTestCfmType*)MailPtr;
            PtGetIdCfmType *p = (PtGetIdCfmType*)k->Parameters;
  //          Printf("RX: API_PROD_TEST_CFM (PT_CMD_GET_ID)\n");
            Printf("   IdNumber(RFPI/IPEI) = %02x %02x %02x %02x %02x\n", p->Id[0], p->Id[1], p->Id[2], p->Id[3], p->Id[4], p->Id[5]);
          }
          break;

         case PT_CMD_GET_SW_LINK_DATE:
         {
            typedef struct
            {
              rsuint8 Year; //!< BCD coded: [0;99] (2000-2099).
              rsuint8 Month; //!< BCD coded [1;12] (jan-dec).
              rsuint8 Day; //!< BCD coded: day of month [1;31]
              rsuint8 Hour; //!< BCD coded: [0:23]
              rsuint8 Minute; //!< BCD coded: [0:59]
            } PtGetLinkDateCfmType;

            ApiProdTestCfmType *k = (ApiProdTestCfmType*)MailPtr;
            PtGetLinkDateCfmType *p = (PtGetLinkDateCfmType*)k->Parameters;
  //          Printf("RX: API_PROD_TEST_CFM (PT_CMD_GET_SW_LINK_DATE)\n");
            Printf("   LinkDate = %02x.%02x.%02x %02x:%02x\n", p->Year, p->Month, p->Day, p->Hour, p->Minute);
         }
         break;

        case PT_CMD_GET_SW_VERSION:
        {
            typedef struct
            {
              rsuint16 Version; //!< The version number (BCD coded). E.g. 0x1234 = v1234 (version 12.34).
              rsuint16 SubVersion; //!< Sub version / branch number (BCD coded).
            } PtGetVersionCfmType;

            ApiProdTestCfmType *k = (ApiProdTestCfmType*)MailPtr;
            PtGetVersionCfmType *p = (PtGetVersionCfmType*)k->Parameters;
            Printf("   Version = %04x\n", p->Version);
          }
          break;

        case PT_CMD_GET_DECT_MODE:
          {
            typedef enum RSENUMTAG(PtDectModeType)
            {
              EU_DECT = 0x00, 
              US_DECT = 0x01, 
              SA_DECT = 0x02, 
              TAIWAN_DECT = 0x03, 
              MALAYSIA_DECT = 0x04, 
              CHINA_DECT = 0x05, 
              THAILAND_DECT = 0x06, 
              BRAZIL_DECT = 0x07, 
              US_DECT_EXT_FREQ = 0x08, 
              KOREAN_DECT = 0x09, 
              JAPAN_DECT = 0x0A, 
              JAPAN_DECT_5CH = 0x0B, 
              UNKNOWN_DECT_MODE = 0xFF  
            } RSENUM8(PtDectModeType);

            #define PT_CMD_GET_DECT_MODE 0x007C  
            #define PT_CMD_SET_DECT_MODE 0x0200
            typedef struct
            {
              PtDectModeType DectMode; 
            } PtGetDectModeCfmType;

            typedef struct
            {
              PtDectModeType DectMode; //!< The dect mode.
            } PtSetDectModeReqType;

            ApiProdTestCfmType *k = (ApiProdTestCfmType*)MailPtr;
            PtGetDectModeCfmType *p = (PtGetDectModeCfmType*)k->Parameters;

            // check if change unsuccessfull (Pp does not have JAPAN_DECT_5CH)
            if(DectModeRequested != 0xFF) 
            {
              if(DectModeRequested != p->DectMode)
              {
                //dect mode change unsuccessfull switch back to US_DECT
                PtSetDectModeReqType *PtSetDectModeReqPtr = (PtSetDectModeReqType*)RcHeapAllocEx(sizeof(PtSetDectModeReqType), RHF_NULL_ON_FULL);
                DectModeRequested = PtSetDectModeReqPtr->DectMode = US_DECT;
                SendApiProdTestReq(API_TASK,  (rsuint16)PT_CMD_SET_DECT_MODE, (rsuint16)sizeof(PtSetDectModeReqType), (rsuint8*)PtSetDectModeReqPtr);
                RcHeapFreeEx(PtSetDectModeReqPtr, RHF_NULL_ON_FULL);
                CvmConOptionsState = CVMCON_STATE_IDLE;
                SendApiProdTestReq(API_TASK,  (rsuint16)PT_CMD_GET_DECT_MODE, 0, NULL);
                return;
              }
            }

            switch(CvmConOptionsState)
            {
              case CVMCON_STATE_TOGGLE_DECTMODE:
                Printf("\nAPI_PROD_TEST_REQ (toggle Dectmode)\n");
                Printf("Please restart target for changes to take effect.\n");
                {
                  PtSetDectModeReqType *PtSetDectModeReqPtr = (PtSetDectModeReqType*)RcHeapAllocEx(sizeof(PtSetDectModeReqType), RHF_NULL_ON_FULL);
                  switch(p->DectMode)
                  {
                    case US_DECT:
                      DectModeRequested = PtSetDectModeReqPtr->DectMode = EU_DECT;
                      break;

                    case EU_DECT:
                      DectModeRequested = PtSetDectModeReqPtr->DectMode = JAPAN_DECT;
                      break;

                    case JAPAN_DECT:
                      DectModeRequested = PtSetDectModeReqPtr->DectMode = JAPAN_DECT_5CH;
                      break;

                    //case JAPAN_DECT:
                    default:
                      DectModeRequested = PtSetDectModeReqPtr->DectMode = US_DECT;
                      break;
                  }
                  SendApiProdTestReq(API_TASK,  (rsuint16)PT_CMD_SET_DECT_MODE, (rsuint16)sizeof(PtSetDectModeReqType), (rsuint8*)PtSetDectModeReqPtr);
                  RcHeapFreeEx(PtSetDectModeReqPtr, RHF_NULL_ON_FULL);
                  CvmConOptionsState = CVMCON_STATE_IDLE;
                  SendApiProdTestReq(API_TASK,  (rsuint16)PT_CMD_GET_DECT_MODE, 0, NULL);
                }
                break;

              case CVMCON_STATE_INIT:
                Printf("CvmCon ready.\n");
                CvmConOptionsState = CVMCON_STATE_IDLE;
                //no break;

              default:
                switch(p->DectMode)
                {
                  case EU_DECT: Printf("   DectMode = EU_DECT\n"); break;
                  case US_DECT: Printf("   DectMode = US_DECT\n"); break;
                  case SA_DECT: Printf("   DectMode = SA_DECT\n"); break;
                  case TAIWAN_DECT: Printf("   DectMode = TAIWAN_DECT\n"); break;
                  case MALAYSIA_DECT: Printf("   DectMode = MALAYSIA_DECT\n"); break;
                  case CHINA_DECT: Printf("   DectMode = CHINA_DECT\n"); break;
                  case THAILAND_DECT: Printf("   DectMode = THAILAND_DECT\n"); break;
                  case BRAZIL_DECT: Printf("   DectMode = BRAZIL_DECT\n"); break;
                  case US_DECT_EXT_FREQ: Printf("   DectMode = US_DECT_EXT_FREQ\n"); break;
                  case KOREAN_DECT: Printf("   DectMode = KOREAN_DECT\n"); break;
                  case JAPAN_DECT: Printf("   DectMode = JAPAN_DECT\n"); break;
                  case JAPAN_DECT_5CH: Printf("   DectMode = JAPAN_DECT_5CH\n"); break;
                  default: Printf("   DectMode = UNKNOWN\n"); break;
                }
                break;
            }
          }
          break;

        case PT_GET_OTP_DATA: 
          {
            typedef struct
            {
              rsuint8 IdNumber[5]; // E.g. RFPI or IPEI.
              rsuint8 BmcModulationDeviation;
              rsuint16 BmcDefaultFrequency;
              rsuint8 Bandgap;
              ApiGuidType Guid;
            } OtpLayoutType;          

            typedef struct
            {
              RsStatusType Status; //!< Returns RSS_SUCCESS(0) if the command succeeded or RSS_'error'(>0) if the command failed.
              rsuint32 Address; //!< The address of the first byte read.
              rsuint8 Length; //!< The number of bytes read.
              rsuint8 Data[1]; //!< The data read.
            } PtGetOtpDataCfmType;

            ApiProdTestCfmType *k = (ApiProdTestCfmType*)MailPtr;
            PtGetOtpDataCfmType *p = (PtGetOtpDataCfmType*)k->Parameters;
            OtpLayoutType *j = (OtpLayoutType*)p->Data;
            Printf("API_PROD_TEST_REQ (OtpInfo)\n");
            Printf("   IdNumber(RFPI/IPEI) = %02x %02x %02x %02x %02x\n", j->IdNumber[0],j->IdNumber[1],j->IdNumber[2],j->IdNumber[3],j->IdNumber[4]);
            Printf("   BmcModulationDeviation = 0x%02x\n", j->BmcModulationDeviation);
            Printf("   BmcDefaultFrequency = 0x%04x\n", j->BmcDefaultFrequency);
            Printf("   Bandgap = 0x%02x\n", j->Bandgap);
          }
      }
      break;

   case API_IMAGE_INFO_CFM:
     switch(((ApiImageInfoCfmType*)MailPtr)->ImageIndex)
     {  
       case 0: //CVMFP
         Printf("   ImageStatus: 0:FP_CVM = ");
         switch(((ApiImageInfoCfmType*)MailPtr)->Status)
         {
           case RSS_SUCCESS:   Printf("RSS_SUCCESS: Image is running.\n"); break;
           case RSS_NO_DATA:   Printf("RSS_NO_DATA: No image header found at this index.\n"); break;
           case RSS_OFFLINE:   Printf("RSS_OFFLINE: Image Disabled.\n"); break;
           case RSS_BLOCKED:   Printf("RSS_BLOCKED: System mismatch.\n"); break;
           case RSS_NOT_FOUND: Printf("RSS_NOT_FOUND: End of list\n"); break;
           default:            Printf("NO INFO AVAILABLE\n"); break; 
         }
         ImgCfgStatus[0] = ((ApiImageInfoCfmType*)MailPtr)->Status;
         break;

       case 1: //CVMPP
         Printf("                1:PP_CVM = ");
         switch(((ApiImageInfoCfmType*)MailPtr)->Status)
         {
           case RSS_SUCCESS:   Printf("RSS_SUCCESS: Image is running.\n"); break;
           case RSS_NO_DATA:   Printf("RSS_NO_DATA: No image header found at this index.\n"); break;
           case RSS_OFFLINE:   Printf("RSS_OFFLINE: Image Disabled.\n"); break;
           case RSS_BLOCKED:   Printf("RSS_BLOCKED: System mismatch.\n"); break;
           case RSS_NOT_FOUND: Printf("RSS_NOT_FOUND: End of list\n"); break;
           default:            Printf("NO INFO AVAILABLE\n"); break; 
         }
         ImgCfgStatus[1] = ((ApiImageInfoCfmType*)MailPtr)->Status;
         break;

       case 2: //COLA
         Printf("                2:COLA   = ");
         switch(((ApiImageInfoCfmType*)MailPtr)->Status)
         {
           case RSS_SUCCESS:   Printf("RSS_SUCCESS: Image is running.\n"); break;
           case RSS_NO_DATA:   Printf("RSS_NO_DATA: No image header found at this index.\n"); break;
           case RSS_OFFLINE:   Printf("RSS_OFFLINE: Image Disabled.\n"); break;
           case RSS_BLOCKED:   Printf("RSS_BLOCKED: System mismatch.\n"); break;
           case RSS_NOT_FOUND: Printf("RSS_NOT_FOUND: End of list\n"); break;
           default:            Printf("NO INFO AVAILABLE\n"); break; 
         }
         ImgCfgStatus[2] = ((ApiImageInfoCfmType*)MailPtr)->Status;

         //check if imageCfg changes requested
         switch(CvmConOptionsState)
         {
           case CVMCON_STATE_TOGGLE_STACK:
             if(ImgCfgStatus[0] == RSS_SUCCESS) //check FP selected
             {
               if(ImgCfgStatus[1] == RSS_OFFLINE) //check if valid PP present
               {
                 if(ImgCfgStatus[2] == RSS_SUCCESS) //check if COLA active
                 {
                   Printf("\nSwitching to ImageCfg=0x81 (PP+COLA)\n"); //select PP with COLA
                   SendApiImageActivateReq(API_TASK, 1, 1);
                 }
                 else
                 {
                   Printf("\nSwitching to ImageCfg=0x01 (PP)\n"); //select PP without COLA
                   SendApiImageActivateReq(API_TASK, 1, 0);
                 }
               }
               else
               {
                 Printf("\nSwitching request ignored. No Valid PP image available\n");
               }
             }
             else //PP selected
             {
               if(ImgCfgStatus[1] == RSS_SUCCESS) //check PP selected
               {
                 if(ImgCfgStatus[0] == RSS_OFFLINE) //check if valid FP present
                 {
                   if(ImgCfgStatus[2] == RSS_SUCCESS) //check if COLA active
                   {
                     Printf("\nSwitching to ImageCfg=0x80 (FP+COLA)\n"); //select FP with COLA
                     SendApiImageActivateReq(API_TASK, 0, 1);
                     ImgCfgStatus[2] = RSS_SUCCESS;
                   }
                   else
                   {
                     Printf("\nSwitching to ImageCfg=0x00 (FP)\n"); //select FP without COLA
                     SendApiImageActivateReq(API_TASK, 0, 0);
                     ImgCfgStatus[2] = RSS_UNKNOWN;
                   }
                 }  
                 else
                 {
                   Printf("\nSwitching request ignored. No Valid FP image available\n");
                 }
               }
             }
             break;
 
           case CVMCON_STATE_TOGGLE_COLA:
             if(ImgCfgStatus[2] == RSS_SUCCESS) //check if COLA active
             {
               Printf("\nSwitching ImageCfg to deactivate COLA\n"); //select PP without COLA
               SendApiImageActivateReq(API_TASK, 0xFF, 0);
             }
             else
             {
               if(ImgCfgStatus[2] == RSS_OFFLINE) //check if inactive COLA image present
               {
                 Printf("\nSwitching ImageCfg to activate COLA\n"); //select PP with COLA
                 SendApiImageActivateReq(API_TASK, 0xFF, 1);
               }
               else
               {
                 Printf("\nSwitching request ignored (No Valid COLA image available)\n");
               }
             }
             break;

           case CVMCON_STATE_IDLE:
           default:
             break;
         }
         break;
    }
  }
}

