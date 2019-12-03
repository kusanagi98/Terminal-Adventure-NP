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

#ifndef __CLIENTFUNC_H__
#define __CLIENTFUNC_H__

#define BUFFER_LEN 1024

void login(int connfd);
void fetchPlayerData(int connfd);
void playMenu();

#endif