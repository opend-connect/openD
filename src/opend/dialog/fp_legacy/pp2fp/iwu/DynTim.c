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

/****************************************************************************
*                               Include files                                 
****************************************************************************/
#include <Core/RtxCore.h>
#include <Ros/RosCfg.h>

#include "LinkList.h"
#include "DynTim.h"

extern void ColaTask(const RosMailType* MailPtr);

/****************************************************************************
*                              Macro definitions                              
****************************************************************************/
#define FILE_NAME "DynMmiTim"
#define DYNMMI_TIMER_RESOLUTION 10


/****************************************************************************
*                     Enumerations/Type definitions/Structs                   
****************************************************************************/

typedef struct DynMmiTimerListType
{
  struct DynMmiTimerListType *Next;
  RosTaskIdType OsTaskId;
  RosTimerIdType TimerId;
  RsTimerTickType TimerValue;
  DynMmiTimerStatusType TimerStatus;
} DynMmiTimerListType;

/****************************************************************************
*                            Global variables/const                           
****************************************************************************/
static MmiLinkedListType DynMmiTimerList;

/****************************************************************************
*                            Local variables/const                            
****************************************************************************/
static rsuint32 TimerCnt;   /* Time counter */
RsTimerTickType BtSiTimerValue; /* Used for calculation the time remaining till the next timeout */

/****************************************************************************
*                          Local Function prototypes                          
****************************************************************************/
extern void MainTask(const RosMailType* MailPtr);

/****************************************************************************
*                                Implementation                               
****************************************************************************/

static void SendDynMmiTimeoutInd (RosTaskIdType TaskId, RosTimerIdType TimerId )
{
  DynMmiTimeoutIndType* pMail = (DynMmiTimeoutIndType*)RosMailAllocate(TaskId, TaskId, sizeof(DynMmiTimeoutIndType));
  pMail->Primitive = TIMEOUT;//DYNMMI_TIMEOUT_IND;
  pMail->TimerId = TimerId;
  //RosMailDeliver((RosMailType*)pMail);

  ColaTask((RosMailType*)pMail);
}

/****************************************************************************/
static DynMmiTimerListType* DynMmiTimFindTimerInList(RosTaskIdType TaskId, RosTimerIdType TimerId, DynMmiTimerListType **prev)
{
  DynMmiTimerListType *p = (DynMmiTimerListType *)DynMmiTimerList.Front;
  *prev = p;
  while(p != NULL)
  {
    if ( (p->TimerId == TimerId) && (p->OsTaskId == TaskId) )
    {
      break;
    }
    *prev = p;
    p = p->Next;
  }
  return(p);
}

/****************************************************************************/
static DynMmiTimerListType* DynMmiTimFindTimeOutInList(RsTimerTickType TimerValue, DynMmiTimerListType **prev)
{
  DynMmiTimerListType *p = (DynMmiTimerListType *)DynMmiTimerList.Front;
  *prev = p;
  while(p != NULL)
  {
    if (((p->TimerValue-TimerCnt)  > (TimerValue-TimerCnt)) || (p->TimerStatus != DYNMMI_TIMER_RUNNING) )
    {
      break;
    }
    *prev = p;
    p = p->Next;
  }
  return(p);
}

/****************************************************************************/
DynMmiTimerStatusType DynMmiTimerStatus (RosTaskIdType TaskId, RosTimerIdType TimerId)
{
  DynMmiTimerStatusType Res = DYNMMI_TIMER_INVALID;
  DynMmiTimerListType *p, *prev;
  p = DynMmiTimFindTimerInList(TaskId, TimerId, &prev);
  if (p != NULL)
  {
    Res = p->TimerStatus;
    if (Res == DYNMMI_TIMER_EXPIRED)
    {
      p->TimerStatus = DYNMMI_TIMER_STOPPED;
    }
  }
  return (Res);
}

/****************************************************************************/
RsTimerTickType DynMmiRemainingTime (RosTimerIdType TimerId)
{
  RsTimerTickType Time = 0;
  DynMmiTimerListType *p, *prev;
  p = DynMmiTimFindTimerInList(API_TASK, TimerId, &prev);
  if (p != NULL)
  {
    if (p->TimerStatus == DYNMMI_TIMER_RUNNING)
    {
      Time = p->TimerValue - TimerCnt;
    }
  }
  return (Time);
}


/****************************************************************************/
rsbool DynMmiCreateTimer (RosTimerIdType TimerId)
{
  rsbool Res = FALSE;
  DynMmiTimerListType *prev;
  // Check if the TimerId already exists:
  if (NULL == DynMmiTimFindTimerInList(API_TASK, TimerId, &prev))
  {
    // Create the new element:
    DynMmiTimerListType *p = MmiLinkedListAdd(&DynMmiTimerList, sizeof(DynMmiTimerListType));
    if (p != NULL)
    {
      p->OsTaskId = API_TASK;
      p->TimerId = TimerId;
      p->TimerStatus = DYNMMI_TIMER_STOPPED;
      Res = TRUE;
    }
  }
  return (Res);
}


/****************************************************************************/
void DynMmiDestroyTimer (RosTimerIdType TimerId)
{
  DynMmiTimerListType *p, *prev;

  p = DynMmiTimFindTimerInList(API_TASK, TimerId, &prev);
  if (p != NULL)
  {
    if (p->TimerStatus == DYNMMI_TIMER_RUNNING)
    {
      DynMmiStopTimer (TimerId);
    }
    MmiLinkedListDelete(&DynMmiTimerList, p);
  }
}

/****************************************************************************/
void DynMmiStartTimer (RosTimerIdType TimerId,RsTimerTickType Time)
{
  DynMmiTimerListType *p, *prev;
  
  /* Check for max possible timer value */
  Time = Time / DYNMMI_TIMER_RESOLUTION;
  if (Time == 0)
  {
    Time++; //One is added, in order to timeout, when TimerCnt is incremented
  }

//MBA  if (Time > RTX_OS_MAX_TIMER_VALUE)
//  {
//    Time = (OsTimerValueType)~RTX_OS_MAX_TIMER_VALUE;
//  }

  /* Activate timer */
  p = DynMmiTimFindTimerInList(API_TASK, TimerId, &prev);
  if (p != NULL)
  {
    Time = Time + TimerCnt;
    p->TimerValue = Time;
    p->TimerStatus = DYNMMI_TIMER_RUNNING;

    //Only move the timer if there is more than one timer:
    if (DynMmiTimerList.Front != DynMmiTimerList.End)  
    {
      /* Remove the timer from the non active list.*/
      if ((MmiListElementType*)p == DynMmiTimerList.Front)
      { // it the first timer in the list
        DynMmiTimerList.Front = (MmiListElementType*)p->Next;
      }
      else if ((MmiListElementType*)p == DynMmiTimerList.End)
      { // it is the last timer in the list
        prev->Next = NULL;
        DynMmiTimerList.End = (MmiListElementType*)prev;
      }
      else
      {
        prev->Next = p->Next;
      }

      /* Insert the timer in the active list */
      p->Next = DynMmiTimFindTimeOutInList(Time,&prev);
      if (prev == p->Next)
      {
        // The timer shall be inserted as the first in the list.
        DynMmiTimerList.Front = (MmiListElementType*)p;
      }
      else
      {
        prev->Next = p;
        if (p->Next == NULL)
        {
          //The timer shall be inserted as the last in the list.
          DynMmiTimerList.End = (MmiListElementType*)p;
        }
      }
    }
    BtSiTimerValue = ((DynMmiTimerListType*)DynMmiTimerList.Front)->TimerValue - TimerCnt;
  }
}

/****************************************************************************/
static DynMmiTimerListType *StopTimer (RosTaskIdType TaskId, RosTimerIdType TimerId, DynMmiTimerStatusType Status)
{
  DynMmiTimerListType *prev;
  DynMmiTimerListType *p = DynMmiTimFindTimerInList(TaskId, TimerId,&prev);
  if (p != NULL)
  {
    p->TimerStatus = Status;
    if (p->Next != NULL)   /* Do nothing if the timer already is the last in the list. */
    {
      /* Remove the timer from the active part of the list */
      if ((DynMmiTimerListType*) DynMmiTimerList.Front == p)
      {
        DynMmiTimerList.Front = (MmiListElementType*)p->Next;
      }
      else
      {
        prev->Next = p->Next;
      }
      /* Insert the stopped timer in the end of the list */
      ((DynMmiTimerListType *)DynMmiTimerList.End)->Next = p;
      DynMmiTimerList.End = (MmiListElementType*)p;
      p->Next = NULL;
    }
    /* Set the timer for the next timeout */
    if ( (DynMmiTimerList.Front != NULL) && (((DynMmiTimerListType*)DynMmiTimerList.Front)->TimerStatus == DYNMMI_TIMER_RUNNING) )
    {
      BtSiTimerValue = ((DynMmiTimerListType*)DynMmiTimerList.Front)->TimerValue - TimerCnt;
    }
    else
    {
      BtSiTimerValue = 0;
    }
  }
  return(p);
}

/****************************************************************************/
void DynMmiStopTimer (RosTimerIdType TimerId)
{
  StopTimer(API_TASK,TimerId,DYNMMI_TIMER_STOPPED);
}

/****************************************************************************/
void DynMmiExpireTimer (RosTaskIdType TaskId, RosTimerIdType TimerId)
{
  StopTimer(TaskId,TimerId,DYNMMI_TIMER_EXPIRED);
}

/****************************************************************************/
void DynMmiTimerTick (void)
{
  if (BtSiTimerValue != 0)
  {
    TimerCnt++;
    BtSiTimerValue--;
    if (BtSiTimerValue == 0)
    {
      DynMmiRunTimerSystem();
    }
  }
}

/****************************************************************************/
void DynMmiRunTimerSystem (void)
{
  if (BtSiTimerValue == 0)
  {
    RosTimerIdType TId;
    RosTaskIdType TaskId;
    DynMmiTimerListType *p = (DynMmiTimerListType *)DynMmiTimerList.Front;
    while( (p != NULL) && (p->TimerStatus == DYNMMI_TIMER_RUNNING) && (p->TimerValue == TimerCnt) )
    {
      TId = p->TimerId;
      TaskId = p->OsTaskId;
      /* Timer pointer must be set to the next, before it is moved to the non active part of the list. */
      p = p->Next;
      /* Move the timer to the non active part of the list. */
      DynMmiExpireTimer(TaskId, TId);
      SendDynMmiTimeoutInd (TaskId, TId);
    }
  }
}
      
/****************************************************************************/
void DynMmiTerminateTimerSystem(void)
{
  DynMmiTimerListType *p = (DynMmiTimerListType *)DynMmiTimerList.Front;
  while(p != NULL)
  {
    p = MmiLinkedListDelete(&DynMmiTimerList, p);
  } 
}


