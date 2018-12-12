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

#include <stdio.h>
#include <stdint.h>

#include <Core/RtxCore.h>


#define DBG_MSG_FROM_STACK 	1
#define DBG_MSG_TO_STACK 	0
#define DBG_MSG_NO_LEN		(int32_t)(-1)

static uint8_t primitive_debug_enabled = 0;


void print_stack_messages(const RosMailType* p_mail, uint8_t incoming, int32_t inlen)
{
	uint16_t i, data_len, buff_len;
	char *data_buf;

	if (!primitive_debug_enabled)
		return;

#ifndef __linux__ // HDLC on RSX
	if (inlen == DBG_MSG_NO_LEN) {
		data_len = (uint16_t)(*((uint8_t *)p_mail - 1) * 256 + *((uint8_t *)p_mail - 2));
		data_len -= 2; // remove primitive
	}
	else {
		data_len = (uint16_t)inlen;
	}
#else
	// check HdlcUart.c -> RxThread -> DataReceiverContainer
	// super ugly but didn't want to break Task convention
	data_len =  (uint16_t) (*((uint8_t *)p_mail-4));
	// data_len is 3+PRIM+DATA,
	if (data_len >= 5) data_len -= 5; // it can't be less than 5 (3+PRIM)
	else data_len -= 2; // this is the case of custom RosAllocate packet, remove only PRIM
#endif

	if (data_len) {
		data_buf = malloc(data_len*sizeof(char)*4);
		buff_len=0;
		for (i=0; i<data_len;i++) {
			buff_len += snprintf(data_buf+buff_len, 4, "%02X ", p_mail->Data.Data[i]);
		}
		data_buf[buff_len-1] = '\0';
	} else {
		data_buf = "";
	}

	if (incoming == DBG_MSG_FROM_STACK)
		printf("\tHOST: |R|<<<| P: (0x%0X) D: [%s]\n", p_mail->Primitive, data_buf);
	else
		printf("\tHOST: |T|>>>| P: (0x%0X) D: [%s]\n", p_mail->Primitive, data_buf);

	if (data_buf && data_len) {
		free(data_buf);
		data_buf = NULL;
	}
}


void enable_stack_msg_debug()
{
	printf("\tHOST <=> DEVICE Message Debugging: Enabled\n");
	primitive_debug_enabled = 1;
}
void print_incoming_msg(const RosMailType* p_mail)
{
	print_stack_messages(p_mail, DBG_MSG_FROM_STACK, DBG_MSG_NO_LEN);
}

void print_outgoing_msg(const RosMailType* p_mail)
{
	print_stack_messages(p_mail, DBG_MSG_TO_STACK, DBG_MSG_NO_LEN);
}


void print_incoming_msg_len(const RosMailType* p_mail, const uint32_t len)
{
	print_stack_messages(p_mail, DBG_MSG_FROM_STACK, (int32_t)len);
}
