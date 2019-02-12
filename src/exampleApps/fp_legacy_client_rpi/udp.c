/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       udp.c
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger
 * @brief      UDP client side implementation.
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "udp.h"
#include <pthread.h>
#include <stdbool.h>

/* The used udp port from udp client and server side. */
#define PORT     8999
/* Max udp buffer size. */
#define MAXLINE  1024

/* Socket file descriptor. */
int sockfd;
/* Socket address of the udp server. */
struct sockaddr_in servaddr;
/* Socket address length. */
int len;
/* RX thread variable. */
pthread_t Rx232Id;
/* Stop the RX task. */
volatile bool StopRxTask;
/* Function pointer for udp received data callback. */
receiveUdpData rxData_cllb;

/**
 * @brief   RX thread.
 *
 * @details Handle the RX thread for serial bus communication.
 */
void *rxThread(void);

void udp_init(receiveUdpData rxUdpData)
{
  rxData_cllb = rxUdpData;

  /* Creating socket file descriptor. */
  if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
    perror("socket creation failed");
  }

  memset(&servaddr, 0, sizeof(servaddr));

  /* Filling server information. */
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = INADDR_ANY;
}

void udp_send(const char *data, size_t len)
{
  sendto(sockfd, (const char *)data, len,
         MSG_NOSIGNAL, (const struct sockaddr *) &servaddr,
         sizeof(servaddr));
}

int rxThread_init()
{
  /* Stop the thread. */
  StopRxTask = true;

  int i;
  if( (i= pthread_create( &Rx232Id, NULL, (void *)&rxThread, NULL) ))
  {
    printf("Rx232Id Thread creation failed\n");
  }
  pthread_detach(Rx232Id);

  /* Initialize thread. */
  StopRxTask = false;

  return 0;
}

void udpSendHello()
{
  const char *buffer = "{\"module\":\"legacy\",\"param1\":\"0\",\"param2\":\"0\",\"param3\":\"0\",\"primitive\":\"request\",\"service\":\"sendHello\",\"status\":\"OK\",\"version\":\"1.0.0\"}";
  /* Send with Ansi \0. */
  udp_send(buffer, strlen(buffer)+1);
}

void *rxThread(void)
{
  char buffer[MAXLINE];
  int  n;

  while(StopRxTask == true) usleep (10000);
  while(StopRxTask == false)
  {
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                MSG_WAITALL, ( struct sockaddr *) &servaddr,
                &len);
    if(n > 0)
    {
      if(!rxData_cllb) break;
      rxData_cllb(buffer);
    }
  }
  /* To indicate that the task has stopped. */
  StopRxTask = false;
  pthread_exit(0);
}