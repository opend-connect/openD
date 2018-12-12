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

#ifndef __EXTDBHOOKS_H__
#define __EXTDBHOOKS_H__

typedef struct ExtDBHooksType{
int (*hookExtDBInit)(void *data);
int (*hookExtDBReset)(ApiLasListIdType ListId);
int (*hookExtDBFields)(ApiLasListIdType ListId, rsuint16 *IeLength, ApiInfoElementType **IePtr);
int (*hookExtDBCount)(ApiLasListIdType ListId);
int (*hookExtDBRead)(ApiLasListIdType ListId, int index, int flds_Length, ApiIeType *flds, rsuint16 *IeLength, ApiInfoElementType **IePtr);
int (*hookExtDBWrite)(ApiLasListIdType ListId, int index, rsuint16 IeLength, rsuint8 *IePtr);
int (*hookExtDBDel)(ApiLasListIdType ListId, int index);
int (*hookExtDBSearch)(ApiLasListIdType ListId, int index, int slength, ApiIeType *sie, int length, ApiIeType *flds, rsuint16 *IeLength, ApiInfoElementType **IePtr);
}ExtDBHooksType;

extern ExtDBHooksType extDBHooks;


int hExtDBInit(void *data);

int hExtDBReset(ApiLasListIdType ListId);
int hExtDBFields(ApiLasListIdType ListId, rsuint16 *IeLength, ApiInfoElementType **IePtr);
int hExtDBCount(ApiLasListIdType ListId);
int hExtDBRead(ApiLasListIdType ListId, int index, int flds_Length, ApiIeType *flds, rsuint16 *IeLength, ApiInfoElementType **IePtr);
int hExtDBWrite(ApiLasListIdType ListId, int index, rsuint16 IeLength, rsuint8 *IePtr);
int hExtDBDel(ApiLasListIdType ListId, int index);
int hExtDBSearch(ApiLasListIdType ListId, int index, int slength, ApiIeType *sie, int length, ApiIeType *flds, rsuint16 *IeLength, ApiInfoElementType **IePtr);

#endif	//__EXTDBHOOKS_H__