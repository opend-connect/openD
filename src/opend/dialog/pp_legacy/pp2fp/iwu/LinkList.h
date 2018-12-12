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

#ifndef MMILINKLIST_H
#define MMILINKLIST_H

/****************************************************************************
*                               Include files                                 
****************************************************************************/


/****************************************************************************
*                              Macro definitions                             
****************************************************************************/


/****************************************************************************
*                     Enumerations/Type definitions/Structs                  
****************************************************************************/

typedef struct MmiListElementType
{
  struct MmiListElementType* Next;
  // Element data here.
} MmiListElementType;

typedef struct
{
  MmiListElementType* Front;
  MmiListElementType* End;
  rsuint8                 Length;
} MmiLinkedListType;

/****************************************************************************
*                           Global variables/const                           
****************************************************************************/


/****************************************************************************
*                             Function prototypes                            
****************************************************************************/

/****************************************************************************
* DESCRIPTION: Adds a element of the size specified to the the linked list, 
* and returns a pointer to the newly added element. The calling task can then 
* fill in the element contents.
****************************************************************************/
void* MmiLinkedListAdd(MmiLinkedListType* ListRoot, rsuint16 Size);

/****************************************************************************
* DESCRIPTION: Deletes the element identified from the linked list. The 
* ListRoot may be updated. The returned value is a pointer to the element 
* following the element just deleted (if any). This can be used to traverse 
* the list and delete multiple elements, without starting from the root when 
* a element has been deleted.
****************************************************************************/
void* MmiLinkedListDelete(MmiLinkedListType* ListRoot, void* Element);

#endif

