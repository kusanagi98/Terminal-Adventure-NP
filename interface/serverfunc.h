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

#include "../helper/mysocket.h"
#include "../struct/user.h"
#define BUFFER_LEN 1024

int handleRequest(int connfd, UserNode **root);

/* handle function */
int login(int connfd, UserNode *root);
int addUser(int connfd, UserNode **root);
int sendPlayerInfo(int connfd, UserNode *root);
int updatePlayerInfo(int connfd, UserNode **root);
int sendHighScore(int connfd, UserNode *root);

#endif