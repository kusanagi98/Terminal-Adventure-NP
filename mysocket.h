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

/*
    @param port in string

    return port number if valid port or -1 if invalid
*/
int getPort(const char *port_argument);

/*
    @param message
    @param type

    exit program when error encounter or get exit message
*/
void die(char *msg, int type);

struct sockaddr_in configAddress(const char *ip, int port);