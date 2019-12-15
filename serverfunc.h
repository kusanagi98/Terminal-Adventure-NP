#ifndef __SERVERFUNC_H__
#define __SERVERFUNC_H__
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <ctype.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>

#include "mysocket.h"
#include "user.h"
#define BUFFER_LEN 1024

void handleRequest(int connfd, UserNode *root);

void login(int connfd, UserNode *root);
void sendPlayerInfo(int connfd, UserNode *user);

#endif