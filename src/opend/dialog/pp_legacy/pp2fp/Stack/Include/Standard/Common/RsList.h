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
* Standard double-linked list, fully inlined implementation.<br>
* For a queue-type list, entries are usually inserted at the tail and removed from the head.
*
* <hr>
*
* The following code shows typical list usage for storing imaginary call control information.
*
* \code
* // Define a struct with the fields needed.
* typedef struct
* {
*   // link must be first field in struct.
*   RsListEntryType Link;
*   // other fields follow...
*   rsuint8 CallRef;
*   rsuint8 Src;
*   rsuint8 Dst;
*   // etc...
* } CcDataType;
*
* // Our list.
* RsListEntryType CcList;
*
* // Startup: Initalize to empty list.
* void TestTaskInit(RosTaskIdType TaskId)
* {
*   RsListInitializeHead(&CcList);
* }
*
* // Here we allocate an entry from the heap, initialize it, and add it to our list.
* CcDataType* AllocateCc(rsuint8 CallRef)
* {
*   CcDataType* pe = (CcDataType*)RcHeapAlloc(sizeof(CcDataType));
*   // Initialize link.
*   RsListInitializeHead(&pe->Link);
*   // Initialize other fields.
*   pe->CallRef = CallRef;
*   pe->Src = 0;
*   pe->Dst = 0;
*   // Add to our list.
*   RsListInsertTail(&CcList, &pe->Link);
*   return pe;
* }
*
* // Cleanup: Detach the entry from the list and free the heap memory.
* void FreeCc(CcDataType* pe)
* {
*   // Remove from our list.
*   RsListRemoveEntry(&pe->Link);
*   // Free memory.
*   RcHeapFree(pe);
* }
*
* // Search the list for a specific entry and return the pointer to it.
* CcDataType* FindCc(rsuint8 CallRef)
* {
*   // Start.
*   CcDataType* pe = (CcDataType*)CcList.Flink;
*   while (pe != (CcDataType*)&CcList)
*   {
*     if (pe->CallRef == CallRef)
*     {
*       // Found it.
*       return pe;
*     }
*     // Next.
*     pe = (CcDataType*)pe->Link.Flink;
*   }
*   // Not found.
*   return NULL;
* }
* \endcode
* <br>
*/


#ifndef RS_LIST_H
#define RS_LIST_H

/****************************************************************************
*                               Include files
****************************************************************************/

/****************************************************************************
*                              Macro definitions
****************************************************************************/

#ifndef RS_C_INLINE

#define RsListInitializeHead(ListHead) ((ListHead)->Flink = (ListHead)->Blink = (ListHead))
/*!< Initialize a list header (to empty). */

#define RsListIsEmpty(ListHead) ((ListHead)->Flink == (ListHead))
/*!< Test if a list is empty. */

#define RsListRemoveEntry(Entry) {\
    RsListEntryType* _EX_Blink = (Entry)->Blink;\
    RsListEntryType* _EX_Flink = (Entry)->Flink;\
    _EX_Blink->Flink = _EX_Flink;\
    _EX_Flink->Blink = _EX_Blink;\
    }
/*!< Remove/detach an entry from anywhere in the list. */

#define RsListRemoveHead(ListHead) (ListHead)->Flink;{RsListRemoveEntry((ListHead)->Flink)}
/*!< Remove (and return) an entry from the head end of the list. */

#define RsListRemoveTail(ListHead) (ListHead)->Blink;{RsListRemoveEntry((ListHead)->Blink)}
/*!< Remove (and return) an entry from the tail end of the list. */

#define RsListInsertTail(ListHead,Entry) {\
    RsListEntryType* _EX_ListHead = (ListHead);\
    RsListEntryType* _EX_Blink = _EX_ListHead->Blink;\
    (Entry)->Flink = _EX_ListHead;\
    (Entry)->Blink = _EX_Blink;\
    _EX_Blink->Flink = (Entry);\
    _EX_ListHead->Blink = (Entry);\
    }
/*!< Insert an entry at the tail end of the list. */

#define RsListInsertHead(ListHead,Entry) {\
    RsListEntryType* _EX_ListHead = (ListHead);\
    RsListEntryType* _EX_Flink = _EX_ListHead->Flink;\
    (Entry)->Flink = _EX_Flink;\
    (Entry)->Blink = _EX_ListHead;\
    _EX_Flink->Blink = (Entry);\
    _EX_ListHead->Flink = (Entry);\
    }
/*!< Insert an entry at the head end of the list. */

#endif

/****************************************************************************
*                     Enumerations/Type definitions/Structs
****************************************************************************/

/// Double-linked list header.
typedef struct RsListEntryType
{
  struct RsListEntryType* Flink; /*!< Forward or head. */
  struct RsListEntryType* Blink; /*!< Backwards or tail. */
} RsListEntryType;

/****************************************************************************
*                           Global variables/const
****************************************************************************/

/****************************************************************************
*                             Function prototypes
****************************************************************************/

#ifdef RS_C_INLINE
RS_C_INLINE void RsListInitializeHead(RsListEntryType* ListHead)
{
  ListHead->Flink = ListHead->Blink = ListHead;
}

RS_C_INLINE rsbool RsListIsEmpty(RsListEntryType* ListHead)
{
  return (rsbool)(ListHead->Flink == ListHead);
}

RS_C_INLINE void RsListRemoveEntry(RsListEntryType* Entry)
{
  RsListEntryType* _EX_Blink = Entry->Blink;
  RsListEntryType* _EX_Flink = Entry->Flink;
  _EX_Blink->Flink = _EX_Flink;
  _EX_Flink->Blink = _EX_Blink;
}

RS_C_INLINE RsListEntryType* RsListRemoveHead(RsListEntryType* ListHead)
{
  RsListEntryType* h = ListHead->Flink;
  RsListRemoveEntry(h);
  return h;
}

RS_C_INLINE RsListEntryType* RsListRemoveTail(RsListEntryType* ListHead)
{
  RsListEntryType* b = ListHead->Blink;
  RsListRemoveEntry(b);
  return b;
}

RS_C_INLINE void RsListInsertTail(RsListEntryType* ListHead, RsListEntryType* Entry)
{
  RsListEntryType* _EX_ListHead = ListHead;
  RsListEntryType* _EX_Blink = _EX_ListHead->Blink;
  Entry->Flink = _EX_ListHead;
  Entry->Blink = _EX_Blink;
  _EX_Blink->Flink = Entry;
  _EX_ListHead->Blink = Entry;
}

RS_C_INLINE void RsListInsertHead(RsListEntryType* ListHead, RsListEntryType* Entry)
{
  RsListEntryType* _EX_ListHead = ListHead;
  RsListEntryType* _EX_Flink = _EX_ListHead->Flink;
  Entry->Flink = _EX_Flink;
  Entry->Blink = _EX_ListHead;
  _EX_Flink->Blink = Entry;
  _EX_ListHead->Flink = Entry;
}
#endif

#endif

// End of file.

