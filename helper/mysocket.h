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

/**
 * @brief Get port number from argument
 * 
 * @param String port number
 * 
 * @return -1 on invalid
 * @return port number on valid
 * */
int getPort(const char *port_argument);

/**
 * @brief Exit program when error encounter or get exit message
 * 
 * @param String message
 * @param int type
 * */
void die(char *msg, int type);

/**
 * @brief Config an address with ip and port
 * 
 * @param String ip address
 * @param int port number
 * 
 * @return sockaddr_in
 * */
struct sockaddr_in configAddress(const char *ip, int port);