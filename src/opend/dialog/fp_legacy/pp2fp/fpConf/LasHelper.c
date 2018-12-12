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
/****************************************************************************
*                               Include files
****************************************************************************/

#include <Core/RtxCore.h>
#include <Ros/RosCfg.h>
#include <Cola/Cola.h>
#include <Phoenix/Api/Api.h>
#include "CfState.h"
#include "ApiHelper.h"
#include "CallCtrl.h"
#include "LineCtrl.h"
#include "LasHelper.h"

#ifdef PP_MMI_HOST_UTIL
 #include "HostUtil.h"
#endif


/****************************************************************************
*                              Macro definitions
****************************************************************************/

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/****************************************************************************
*                            Global variables/const
****************************************************************************/

/****************************************************************************
*                            Local variables/const
****************************************************************************/

/****************************************************************************
*                          Local Function prototypes
****************************************************************************/

/****************************************************************************
*                                Implementation
***************************************************************************/
/****************************************************************************
* FUNCTION:      PackFldIdentifiers
* DESCRIPTION:
****************************************************************************/
static void PackFldIdentifiers(ApiLasReqFldIdentifiersType **Identifier, rsuint8 NoOfIdentifiers, ApiIeType *IdentifierPtr)
{
  if(*Identifier == NULL)
  {
    rsuint8 i;

    *Identifier = (ApiLasReqFldIdentifiersType *)RcHeapAllocEx(RSOFFSETOF(ApiLasReqFldIdentifiersType, FieldIdentifiers) + sizeof(ApiIeType) * NoOfIdentifiers, RHF_NULL_ON_FULL);

    (*Identifier)->Length = sizeof(ApiIeType) * NoOfIdentifiers;
    for(i=0; i<NoOfIdentifiers; i++)
    {
      (*Identifier)->FieldIdentifiers[i] = IdentifierPtr[i];
    }
  }
}
/****************************************************************************
* FUNCTION:      RequestLasEntry
* DESCRIPTION:
****************************************************************************/
void RequestLasEntry(rsuint16 StartIndex, rsuint16 SessionId, rsuint8 NumberOfEntries, rsuint8 NoOfIdentifiers, ApiIeType *IdentifierPtr, ApiLasListIdType ListId)
{
  //Build read las entry mail
  ApiInfoElementType *ieBlockPtr = NULL;
  rsuint16 ieBlockLength = 0;
  ApiLasReqFldIdentifiersType *FldIdentifier = NULL;
  PackFldIdentifiers(&FldIdentifier, NoOfIdentifiers, IdentifierPtr);
  ApiBuildInfoElement(&ieBlockPtr,
                      &ieBlockLength,
                      API_IE_LAS_REQUESTED_FIELD_IDENTIFIERS,
                      RSOFFSETOF(ApiLasReqFldIdentifiersType, FieldIdentifiers) + FldIdentifier->Length,
                      (rsuint8 *)FldIdentifier);

  SendApiLasReadEntriesReq(COLA_TASK,  SessionId, StartIndex, NumberOfEntries, API_LAS_READDIRECTION_FORWARD, API_LAS_READSTATUS_UNCHANGED, ieBlockLength, (rsuint8 *)ieBlockPtr);
  ApiFreeInfoElement(&ieBlockPtr);
  RcHeapFreeEx((void*)FldIdentifier, RHF_NULL_ON_FULL);
}

/***************************************************************************
*  FUNCTION: EditLasEntry
*  INPUTS  :
*  OUTPUTS :
*  -------------------------------------------------------------------------
*  DESCRIPTION:
*****************************************************************************/
static void EditLasEntry(rsuint8 NoOfIdentifiers, ApiIeType *IdentifierPtr, ApiLasListIdType ListId)
{
  //Build read las entry mail
  ApiInfoElementType *ieBlockPtr = NULL;
  rsuint16 ieBlockLength = 0;
  ApiLasReqFldIdentifiersType *FldIdentifier = NULL;
  PackFldIdentifiers(&FldIdentifier, NoOfIdentifiers, IdentifierPtr);
  ApiBuildInfoElement(&ieBlockPtr,
                      &ieBlockLength,
                      API_IE_LAS_REQUESTED_FIELD_IDENTIFIERS,
                      RSOFFSETOF(ApiLasReqFldIdentifiersType, FieldIdentifiers) + FldIdentifier->Length,
                      (rsuint8 *)FldIdentifier);

  SendApiLasEditEntryReq(COLA_TASK,  pCfSysCtrl->LasSessionData[ListId].SessionId, pCfSysCtrl->LasSessionData[ListId].EntryIdentifier, ieBlockLength, (rsuint8 *)ieBlockPtr);

  ApiFreeInfoElement(&ieBlockPtr);

  RcHeapFreeEx((void *)FldIdentifier, RHF_NULL_ON_FULL);
}


/***************************************************************************
*  FUNCTION: ClearLasSessionData
*  INPUTS  :
*  OUTPUTS :
*  -------------------------------------------------------------------------
*  DESCRIPTION: reads the attached handsets of a specific line
*****************************************************************************/
void ClearLasSessionData(ApiLasListIdType Index)
{
  if (Index < NUMBER_OF_LISTS_IN_LAS)
  {
    pCfSysCtrl->LasSessionData[Index].SessionId         = 0;
    pCfSysCtrl->LasSessionData[Index].EntryIdentifier   = 0;
    pCfSysCtrl->LasSessionData[Index].NoOfEntries       = 0;
    pCfSysCtrl->LasSessionData[Index].CurrentEntry      = 0;
  }
  pCfSysCtrl->LasState[Index] = LAS_STATE_NO_ACTIVE;
}


/***************************************************************************
*  FUNCTION: GetLasSessionDataIndex
*  INPUTS  :
*  OUTPUTS :
*  -------------------------------------------------------------------------
*  DESCRIPTION:
*****************************************************************************/
static ApiLasListIdType GetLasSessionDataIndex(rsuint16 Id)
{
  rsuint8 i;
  for (i = 0; i<NUMBER_OF_LISTS_IN_LAS; i++)
  {
    if(pCfSysCtrl->LasSessionData[i].SessionId == Id)
    {
      return i;
    }
  }
  return NUMBER_OF_LISTS_IN_LAS;
}

/***************************************************************************
*  FUNCTION: ReadLine
*  INPUTS  :
*  OUTPUTS :
*  -------------------------------------------------------------------------
*  DESCRIPTION: reads the attached handsets of a specific line
*****************************************************************************/
static void ReadLine(void)
{
  ApiIeType ApiIePtr[1]={API_IE_LAS_ATTACHED_HANDSETS};
  RequestLasEntry(pCfSysCtrl->LasSessionData[API_LAS_LINE_SETTINGS].CurrentEntry,
                  pCfSysCtrl->LasSessionData[API_LAS_LINE_SETTINGS].SessionId,
                  1,
                  1,
                  (ApiIeType *)ApiIePtr,
                  API_LAS_LINE_SETTINGS);
}

/***************************************************************************
*  FUNCTION: EditLine
*  INPUTS  :
*  OUTPUTS :
*  -------------------------------------------------------------------------
*  DESCRIPTION: reads the attached handsets of a specific line
*****************************************************************************/
static void EditLine(void)
{
  ApiIeType ApiIePtr[1]={API_IE_LAS_ATTACHED_HANDSETS};
  EditLasEntry(1, (ApiIeType *)ApiIePtr, API_LAS_LINE_SETTINGS);
}

/***************************************************************************
*  FUNCTION: SaveLine
*  INPUTS  :
*  OUTPUTS :
*  -------------------------------------------------------------------------
*  DESCRIPTION: reads the attached handsets of a specific line
*****************************************************************************/
static void SaveLine(void)
{
  ApiInfoElementType *IePtr = NULL;
  rsuint16 IeLength = 0;
  ApiLasAttachedHandsetsType Hs;
  Hs.Editable=TRUE;
  Hs.NumberOfAttachedHandsets = 3;
  Hs.Length = 1;
  Hs.Bitmap[0] = pCfSysCtrl->New_Hs;
  ApiBuildInfoElement(&IePtr, &IeLength, API_IE_LAS_ATTACHED_HANDSETS, sizeof(ApiLasAttachedHandsetsType), (rsuint8*)&Hs);
  SendApiLasSaveEntryReq(COLA_TASK,  pCfSysCtrl->LasSessionData[API_LAS_LINE_SETTINGS].SessionId, pCfSysCtrl->LasSessionData[API_LAS_LINE_SETTINGS].EntryIdentifier,  IeLength, (rsuint8*)IePtr);

  ApiFreeInfoElement(&IePtr);
}

/***************************************************************************
*  FUNCTION: HostLasEndSession
*  INPUTS  :
*  OUTPUTS :
*  -------------------------------------------------------------------------
*  DESCRIPTION:
*****************************************************************************/
static void HostLasStartSession(ApiLasListIdType ListId)
{
  if(pCfSysCtrl->LasSessionData[ListId].SessionId == 0)
  {
    SendApiLasStartSessionReq(COLA_TASK,  ListId, 0, NULL);
  }
  else
  {
    //The session for this list is already started, thus do nothing
  }
}

/***************************************************************************
*  FUNCTION: HostLasEndSession
*  INPUTS  :
*  OUTPUTS :
*  -------------------------------------------------------------------------
*  DESCRIPTION:
*****************************************************************************/
static void HostLasEndSession(ApiLasListIdType ListId)
{
  if(pCfSysCtrl->LasSessionData[ListId].SessionId != 0)
  {
    SendApiLasEndSessionReq(COLA_TASK,  pCfSysCtrl->LasSessionData[ListId].SessionId);
    ClearLasSessionData(ListId);
  }
  else
  {
    //The session for this list is already closed, thus do nothing
  }
}


/***************************************************************************
*  FUNCTION: HostLasCreateLine
*  INPUTS  :
*  OUTPUTS :
*  -------------------------------------------------------------------------
*  DESCRIPTION:
*****************************************************************************/
static void HostLasCreateLine(void)
{
  ApiInfoElementType *IePtr = NULL;
  rsuint16 IeLength = 0;
  rsuint8 i;
  ApiLasNameType *NamePtr = NULL;
  ApiLasLineIdType Id;
  ApiLasAttachedHandsetsType Hs;
//  ApiLasPermanentClirType Clir;
  rsuint8 LineNo = (pCfSysCtrl->LasState[API_LAS_LINE_SETTINGS]-LINE_STATE_CREATE_ALL_LINES); //First line we save is line 0, however the saved id starts from 1
  rsuint8 name[10] = {'L','i','n','e',' ','N','o','.',' ',' '};
  name[9] = 0x30 + LineNo;

  //Save Line Number
  Id.LineIdSubtype = API_SUB_LINE_ID_EXT_LINE_ID;
  Id.Length = 1;
  Id.LineId[0] = LineNo+1; //LAS lineId starts from 1
  ApiBuildInfoElement(&IePtr, &IeLength, API_IE_LAS_LINE_ID, sizeof(ApiLasLineIdType), (rsuint8*)&Id);

  //Save Line Name
  NamePtr = (ApiLasNameType *)RcHeapAllocEx((sizeof(ApiLasNameType)+10-1), RHF_NULL_ON_FULL);
  NamePtr->Length = 10;
  memcpy(NamePtr->Name, (void*)name, 10);
  ApiBuildInfoElement(&IePtr, &IeLength, API_IE_LAS_LINE_NAME, sizeof(ApiLasNameType)+10-1, (rsuint8*)NamePtr);

  //Save attached HS, defalut all registrated HS
  Hs.Length = 1;
  for (i = 1; i < NO_HANDSETS; i++)
  {
    if (CallState[i].State != HS_NOT_REGISTERED)
    {
      Hs.Bitmap[0] |= 0x01<<(i-1);
    }
  }
  ApiBuildInfoElement(&IePtr, &IeLength, API_IE_LAS_ATTACHED_HANDSETS, sizeof(ApiLasAttachedHandsetsType), (rsuint8*)&Hs);
  pCfSysCtrl->LasLineSettings[LineNo].AttachedHeadsets= Hs.Bitmap[0]; //Attached Hs saved local

//   //Save CLIR information, default false
//   Clir.ClirMode = FALSE;
//   Clir.ClirCode1 = 0;
//   Clir.ClirCode2 = 0;
//   ApiBuildInfoElement(&IePtr, &IeLength, API_IE_LAS_PERMANENT_CLIR, sizeof(ApiLasPermanentClirType), (rsuint8*)&Clir);
//   HostLasLineSettings[LineNo].PermanentClir = Clir.ClirMode; //CLIR saved local

  //Send infomation to LAS
  SendApiLasSaveEntryReq(COLA_TASK,  pCfSysCtrl->LasSessionData[API_LAS_LINE_SETTINGS].SessionId, 0,  IeLength, (rsuint8*)IePtr);
  ApiFreeInfoElement(&IePtr);
}

/***************************************************************************
*  FUNCTION: HostLasGetAllLineSetting
*  INPUTS  :
*  OUTPUTS :
*  -------------------------------------------------------------------------
*  DESCRIPTION:
*****************************************************************************/
static void HostLasGetAllLineSetting(void)
{
  if (pCfSysCtrl->LasSessionData[API_LAS_LINE_SETTINGS].NoOfEntries > 0)
  {
    ApiIeType ApiIePtr[3]={API_IE_LAS_LINE_ID, API_IE_LAS_ATTACHED_HANDSETS, API_IE_LAS_PERMANENT_CLIR};
    RequestLasEntry(pCfSysCtrl->LasSessionData[API_LAS_LINE_SETTINGS].CurrentEntry,
                    pCfSysCtrl->LasSessionData[API_LAS_LINE_SETTINGS].SessionId,
                    1,
                    3,
                    (ApiIeType *)ApiIePtr,
                    API_LAS_LINE_SETTINGS);
  }
  else
  {
    HostLasEndSession(API_LAS_LINE_SETTINGS);
  }
}

/***************************************************************************
*  FUNCTION: HostLasGetLineSettings
*  INPUTS  :
*  OUTPUTS :
*  -------------------------------------------------------------------------
*  DESCRIPTION:
*****************************************************************************/
void HostLasGetLineSettings(void)
{
  if (pCfSysCtrl->LasSessionData[API_LAS_LINE_SETTINGS].SessionId == 0)
  {
    //Start session
    pCfSysCtrl->LasState[API_LAS_LINE_SETTINGS] = LINE_STATE_GET_LINE_ALL_SETTINGS;
    HostLasStartSession(API_LAS_LINE_SETTINGS);
  }
  else
  {
    pCfSysCtrl->LasSessionData[API_LAS_LINE_SETTINGS].CurrentEntry  = 1;
    pCfSysCtrl->LasState[API_LAS_LINE_SETTINGS] = LINE_STATE_GET_LINE_ALL_SETTINGS;
    HostLasGetAllLineSetting();
  }
}

/***************************************************************************
*  FUNCTION: HostLasInitialzeLineSettings
*  INPUTS  :
*  OUTPUTS :
*  -------------------------------------------------------------------------
*  DESCRIPTION:
*****************************************************************************/
void HostLasInitialzeLineSettings(void)
{
  if (pCfSysCtrl->LasSessionData[API_LAS_LINE_SETTINGS].SessionId == 0)
  {
    //Start session
    pCfSysCtrl->LasState[API_LAS_LINE_SETTINGS] = LINE_STATE_INIT_ALL_LINES;
    HostLasStartSession(API_LAS_LINE_SETTINGS);
  }
  else
  {
    if (pCfSysCtrl->LasSessionData[API_LAS_LINE_SETTINGS].NoOfEntries < LS_NO_LINES)
    {
      if (pCfSysCtrl->LasSessionData[API_LAS_LINE_SETTINGS].NoOfEntries == 0)
      {
        pCfSysCtrl->LasState[API_LAS_LINE_SETTINGS] = LINE_STATE_CREATE_ALL_LINES;
        HostLasCreateLine();
      }
      else
      {
        pCfSysCtrl->LasState[API_LAS_LINE_SETTINGS] = LINE_STATE_DELETE_ALL_LINES;
        pCfSysCtrl->LasSessionData[API_LAS_LINE_SETTINGS].CurrentEntry = 1;
        ReadLine();
      }
    }
    else
    {
      HostLasGetLineSettings();
    }
  }
}

/***************************************************************************
*  FUNCTION: HandleLasStartSessionCfm
*  INPUTS  :
*  OUTPUTS :
*  -------------------------------------------------------------------------
*  DESCRIPTION: Handle Las Start Session Confirmation
*****************************************************************************/
static void HandleLasStartSessionCfm(ApiLasStartSessionCfmType *MailPtr)
{
  pCfSysCtrl->LasSessionData[MailPtr->ListIdentifier].SessionId     = MailPtr->SessionIdentifier;
  pCfSysCtrl->LasSessionData[MailPtr->ListIdentifier].NoOfEntries   = MailPtr->NoOfEntries;
  pCfSysCtrl->LasSessionData[MailPtr->ListIdentifier].CurrentEntry  = 0;

  switch (MailPtr->ListIdentifier)
  {
    case API_LAS_LINE_SETTINGS:
      switch (pCfSysCtrl->LasState[API_LAS_LINE_SETTINGS])
      {
        case LINE_STATE_INIT_ALL_LINES:
          if (pCfSysCtrl->LasSessionData[API_LAS_LINE_SETTINGS].NoOfEntries < LS_NO_LINES)
          {
            if (pCfSysCtrl->LasSessionData[API_LAS_LINE_SETTINGS].NoOfEntries == 0)
            {
              pCfSysCtrl->LasState[API_LAS_LINE_SETTINGS] = LINE_STATE_CREATE_ALL_LINES;
              HostLasCreateLine();
            }
            else
            {
              pCfSysCtrl->LasState[API_LAS_LINE_SETTINGS] = LINE_STATE_DELETE_ALL_LINES;
              pCfSysCtrl->LasSessionData[API_LAS_LINE_SETTINGS].CurrentEntry = 1;
              ReadLine();
            }
          }
          else
          {
            pCfSysCtrl->LasState[API_LAS_LINE_SETTINGS] = LINE_STATE_GET_LINE_ALL_SETTINGS;
            pCfSysCtrl->LasSessionData[API_LAS_LINE_SETTINGS].CurrentEntry = 1;
            HostLasGetAllLineSetting();
          }
          break;

        case LINE_STATE_GET_LINE_ALL_SETTINGS:
          pCfSysCtrl->LasSessionData[API_LAS_LINE_SETTINGS].CurrentEntry = 1;
          HostLasGetAllLineSetting();
          break;

        case LINE_STATE_ATTACH_NEW_HS_READ:
          pCfSysCtrl->LasSessionData[API_LAS_LINE_SETTINGS].CurrentEntry = 1;
          ReadLine();
          break;
      }
      break;
  }
}

/***************************************************************************
*  FUNCTION: HandleLasDataPacketInd
*  INPUTS  :
*  OUTPUTS :
*  -------------------------------------------------------------------------
*  DESCRIPTION:
*****************************************************************************/
static void HandleLasDataPacketInd(ApiLasDataPacketIndType* MailPtr)
{
  pCfSysCtrl->LasSessionData[GetLasSessionDataIndex(MailPtr->SessionIdentifier)].EntryIdentifier = MailPtr->EntryIdentifier;
  switch (GetLasSessionDataIndex(MailPtr->SessionIdentifier))
  {
    case API_LAS_LINE_SETTINGS:
      switch (pCfSysCtrl->LasState[API_LAS_LINE_SETTINGS])
      {
        case LINE_STATE_GET_LINE_ALL_SETTINGS:
        {
          rsuint8 LineId;
          //Save Line Id
          ApiInfoElementType* pIe = ApiGetInfoElement((ApiInfoElementType *)MailPtr->InfoElement,
                                                      MailPtr->InfoElementLength,
                                                      API_IE_LAS_LINE_ID);
          if (pIe != NULL)
          {
            LineId = (((ApiLasLineIdType*)&(pIe->IeData[0]))->LineId[0]) - 1; //minus one since LAS line ID starts form 1
            if (LineId > LS_NO_LINES)
            {
              if(MailPtr->Last == TRUE)
              {
                HostLasEndSession(API_LAS_LINE_SETTINGS);
              }
              return;
            }
          }
          else
          {
            HostLasEndSession(API_LAS_LINE_SETTINGS);
            return;
          }

          //Save Attaced Hs
          pIe = ApiGetInfoElement((ApiInfoElementType *)MailPtr->InfoElement,
                                                        MailPtr->InfoElementLength,
                                                        API_IE_LAS_ATTACHED_HANDSETS);
          if (pIe != NULL)
          {
            pCfSysCtrl->LasLineSettings[LineId].AttachedHeadsets = ((ApiLasAttachedHandsetsType*)(&(pIe->IeData[0])))->Bitmap[0];
          }

          //Save CLIR
          pIe = ApiGetInfoElement((ApiInfoElementType *)MailPtr->InfoElement,
                                                        MailPtr->InfoElementLength,
                                                        API_IE_LAS_PERMANENT_CLIR);
          if (pIe != NULL)
          {
            pCfSysCtrl->LasLineSettings[LineId].PermanentClir = ((ApiLasPermanentClirType*)(&(pIe->IeData[0])))->ClirMode;
          }

          //Get next line or if all lines is received return
          if(pCfSysCtrl->LasSessionData[API_LAS_LINE_SETTINGS].CurrentEntry < pCfSysCtrl->LasSessionData[API_LAS_LINE_SETTINGS].NoOfEntries)
          {
            pCfSysCtrl->LasSessionData[API_LAS_LINE_SETTINGS].CurrentEntry++;
            HostLasGetAllLineSetting();
          }
          else
          {
            HostLasEndSession(API_LAS_LINE_SETTINGS);
//            for (rsuint8 i = 0; i<LS_NO_LINES; i++)
//            {
//              printf("Attached Hs to Line nr %x: %x \n", i+1, HostLasLineSettings[i].AttachedHeadsets);
//            }
          }
        }
        break;

      case LINE_STATE_ATTACH_NEW_HS_READ:
      {
        pCfSysCtrl->LasState[API_LAS_LINE_SETTINGS] = LINE_STATE_ATTACH_NEW_HS_EDIT;
        EditLine();
      }
      break;

      case LINE_STATE_ATTACH_NEW_HS_EDIT:
      {
        rsuint8 hs;
        ApiInfoElementType* pIe = ApiGetInfoElement((ApiInfoElementType *)MailPtr->InfoElement,
                                                      MailPtr->InfoElementLength,
                                                      API_IE_LAS_ATTACHED_HANDSETS);
        if (pIe != NULL)
        {
          hs = ((ApiLasAttachedHandsetsType*)(&(pIe->IeData[0])))->Bitmap[0];
          if (pCfSysCtrl->ClearAttachedHs)
          {
            hs &= ~(0x01<<(pCfSysCtrl->Hs_No-1));   //Clear the Hs from current line, Minus 1 since Hs_No always is from 1 to 6
          }
          else
          {
            hs |= 0x01<<(pCfSysCtrl->Hs_No-1);      //attach the Hs from current line, Minus 1 since Hs_No always is from 1 to 6
          }
          pCfSysCtrl->New_Hs = hs;              //The New_Hs, is saved in the save line state (LINE_STATE_ATTACH_NEW_HS_SAVE)
        }
        else
        {
          HostLasEndSession(API_LAS_LINE_SETTINGS);
          break;
        }
        pCfSysCtrl->LasState[API_LAS_LINE_SETTINGS] = LINE_STATE_ATTACH_NEW_HS_SAVE;
        SaveLine();
      }
      break;
    }
    break;
  }
}

/***************************************************************************
*  FUNCTION: HandleLasSaveEntryCfm
*  INPUTS  :
*  OUTPUTS :
*  -------------------------------------------------------------------------
*  DESCRIPTION:
*****************************************************************************/
static void HandleLasSaveEntryCfm(ApiLasSaveEntryCfmType* MailPtr)
{
  switch (GetLasSessionDataIndex(MailPtr->SessionIdentifier))
  {
    case API_LAS_SUPPORTED_LISTS:
    case API_LAS_OUTGOING_CALLS:
    case API_LAS_INCOMING_ACCEPTED_CALLS:
    case API_LAS_MISSED_CALLS:
    case API_LAS_ALL_CALLS:
    case API_LAS_CONTACTS:
    case API_LAS_INTERNAL_NAMES:
    case API_LAS_DECT_SYSTEM_SETTINGS:
      break;

    case API_LAS_LINE_SETTINGS:
      switch(pCfSysCtrl->LasState[API_LAS_LINE_SETTINGS])
      {
        case LINE_STATE_CREATE_ALL_LINES:
        case LINE_STATE_CREATE_LINE1:
        case LINE_STATE_CREATE_LINE2:
        break;

        case LINE_STATE_ATTACH_NEW_HS_SAVE:
        if (pCfSysCtrl->LasSessionData[API_LAS_LINE_SETTINGS].CurrentEntry < pCfSysCtrl->LasSessionData[API_LAS_LINE_SETTINGS].NoOfEntries)
        {
          pCfSysCtrl->LasSessionData[API_LAS_LINE_SETTINGS].CurrentEntry++;
          pCfSysCtrl->LasState[API_LAS_LINE_SETTINGS] = LINE_STATE_ATTACH_NEW_HS_READ;
          ReadLine();
        }
        else
        {
          HostLasGetLineSettings();
        }
        break;

        case LINE_STATE_CREATE_LINE3:
        {
          HostLasEndSession(API_LAS_LINE_SETTINGS);
        }
        break;
      }
      break;
  }
}


/***************************************************************************
*  FUNCTION: HostLasAttachHsToAllLines
*  INPUTS  : HandsetId, detach or attach handset from Line
*  OUTPUTS :
*  -------------------------------------------------------------------------
*  DESCRIPTION:
*   Attach or detach a specific handset to all the lines
*****************************************************************************/
void HostLasAttachHsToAllLines(rsuint8 Hs, rsbool ClearHs)
{
  //The handset number shall be in the range of 1 to 6
  if (Hs > 0 && Hs < NO_HANDSETS)
  {
    pCfSysCtrl->Hs_No = Hs;
    pCfSysCtrl->ClearAttachedHs = ClearHs;
    if (pCfSysCtrl->LasSessionData[API_LAS_LINE_SETTINGS].SessionId == 0)
    {
      //Start session
      pCfSysCtrl->LasState[API_LAS_LINE_SETTINGS] = LINE_STATE_ATTACH_NEW_HS_READ;
      HostLasStartSession(API_LAS_LINE_SETTINGS);
    }
    else
    {
      pCfSysCtrl->LasSessionData[API_LAS_LINE_SETTINGS].CurrentEntry  = 1;
      pCfSysCtrl->LasState[API_LAS_LINE_SETTINGS] = LINE_STATE_ATTACH_NEW_HS_READ;
      ReadLine();
    }
  }
}

/***************************************************************************
*  FUNCTION: HostLasTask
*  INPUTS  :
*  OUTPUTS :
*  -------------------------------------------------------------------------
*  DESCRIPTION:
*****************************************************************************/
void HostLasTask(RosMailType *MailPtr)
{
  switch(MailPtr->Primitive)
  {
    case API_LAS_START_SESSION_CFM:                  HandleLasStartSessionCfm((ApiLasStartSessionCfmType *)MailPtr); break;
    //case API_LAS_END_SESSION_CFM:                    HandleLasEndSessionCfm((ApiLasEndSessionCfmType*)MailPtr); break ;
    //case API_LAS_QUERY_SUPPORTED_ENTRY_FIELDS_CFM:   HandleLasQuerySupportedEntryFieldsCfm((ApiLasQuerySupportedEntryFieldsCfmType*)MailPtr); break;
    //case API_LAS_READ_ENTRIES_CFM:                   HandeLasReadEntriesCfm((ApiLasReadEntriesCfmType*)MailPtr); break;
    //case API_LAS_EDIT_ENTRY_CFM:                     HandleLasEditEntryCfm((ApiLasEditEntryCfmType*)MailPtr); break;
    case API_LAS_SAVE_ENTRY_CFM:                     HandleLasSaveEntryCfm((ApiLasSaveEntryCfmType*)MailPtr); break;
    //case API_LAS_DELETE_ENTRY_CFM:                   HandleLasDeleteEntryCfm((ApiLasDeleteEntryCfmType*)MailPtr); break;
    //case API_LAS_DELETE_LIST_CFM:                    HandleLasDeleteListCfm((ApiLasDeleteListCfmType*)MailPtr); break;
    //case API_LAS_SEARCH_ENTRIES_CFM:                 HandleLasSearchEntriesCfm((ApiLasSearchEntriesCfmType*)MailPtr); break;
    //case API_LAS_NEGATIVE_ACKNOWLEDGE_IND:           HandleLasNegativeAckInd((ApiLasNegativeAcknowledgeIndType*)MailPtr); break;
    case API_LAS_DATA_PACKET_IND:                    HandleLasDataPacketInd((ApiLasDataPacketIndType*)MailPtr); break;
    //case API_LAS_DB_CLEAR_CFM:                       HostLasEndSession(API_LAS_SUPPORTED_LISTS); break;
    //These are primitives for las which should be send:
    //case API_LAS_START_SESSION_REQ:
    //case API_LAS_END_SESSION_REQ:
    //case API_LAS_QUERY_SUPPORTED_ENTRY_FIELDS_REQ:
    //case API_LAS_READ_ENTRIES_REQ:
    //case API_LAS_EDIT_ENTRY_REQ:
    //case API_LAS_SAVE_ENTRY_REQ:
    //case API_LAS_DELETE_ENTRY_REQ:
    //case API_LAS_DELETE_LIST_REQ:
    //case API_LAS_SEARCH_ENTRIES_REQ:
    //case API_LAS_DATA_PACKET_REQ:

  }
}

// End of file.

