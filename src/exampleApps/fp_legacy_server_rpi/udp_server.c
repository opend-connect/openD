/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file       udp_server.c
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, www.stackforce.de
 * @author     Heiko Berger
 * @brief
 * @details
 *
 * This work is dual-licensed under Apache 2.0 and GPL 2.0. You can choose between one of them if you use this work.
 * For further details, please refer to the project home: https://github.com/opend-connect/openD
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-only
 *
 */

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "udp_server.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/* The used udp port from udp client and server side. */
#define PORT     8999
/* Max udp buffer size. */
#define MAXLINE  1024

/* Socket file descriptor. */
int sockfd;
/* Socket address of the udp server/client. */
static struct sockaddr_in servaddr, cliaddr;
/* Number of received bytes. */
int  n;
/* Socket address length. */
int len;

void udp_init()
{
  char buffer[MAXLINE];

  /* Creating socket file descriptor. */
  if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
      perror("socket creation failed");
  }

  memset(&servaddr, 0, sizeof(servaddr));
  memset(&cliaddr, 0, sizeof(cliaddr));

  /* Filling server information. */
  servaddr.sin_family    = AF_INET; // IPv4
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(PORT);

  /* Bind the socket with the server address. */
  if ( bind(sockfd, (const struct sockaddr *)&servaddr,
          sizeof(servaddr)) < 0 )
  {
      perror("bind failed");
  }
}

void udp_receive(char *buffer)
{
  recvfrom(sockfd, (char *)buffer, 1024,
           MSG_WAITALL, ( struct sockaddr *) &cliaddr,
           &len);
}

void udp_send(const char *data, size_t len)
{
  sendto(sockfd, (const char *)data, len,
         MSG_NOSIGNAL, (const struct sockaddr *) &cliaddr,
         sizeof(cliaddr));
}
