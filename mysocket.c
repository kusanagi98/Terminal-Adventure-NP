#include "mysocket.h"

int getPort(const char *port_argument)
{
    int port_num = atoi(port_argument);

    if (port_num > 0 && port_num < 65535)
        return port_num;
    else
        return -1;
}

void die(char *msg, int type)
{
    if (type == 1)
    {
        perror(msg);
    }
    else if (type == 0)
    {
        printf("%s\n", msg);
    }
    exit(1);
}

struct sockaddr_in configAddress(const char *ip, int port)
{
    struct sockaddr_in addr;
    /* empty server to config */
    bzero(&addr, sizeof(addr));
    /* this is an Internet address */
    addr.sin_family = AF_INET;
    /* let the system figure out our IP address */
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    /* this is the port we will listen on */
    addr.sin_port = port;

    return addr;
}