#include "clientfunc.h"
#include "game.h"

extern UserInfo user;

void login(int connfd)
{
    char buffer[BUFFER_LEN];
    int n;

    if (write(connfd, "login", strlen("login")) == -1)
        die("write error", 0);

    bzero(buffer, BUFFER_LEN);

    if ((n = read(connfd, buffer, BUFFER_LEN)) == -1)
        die("read error", 0);
    buffer[n] = '\0';
    printf("%s\n", buffer);

    printf("Username: ");
    scanf("%s%*c", buffer);
    if (write(connfd, buffer, strlen(buffer)) == -1)
        die("write error", 0);

    bzero(buffer, BUFFER_LEN);
    if ((n = read(connfd, buffer, BUFFER_LEN)) == -1)
        die("read error", 0);
    buffer[n] = '\0';
    if (strcmp(buffer, "User not found") == 0)
    {
        die(buffer, 1);
    }

    bzero(buffer, BUFFER_LEN);
    printf("Password: ");
    scanf("%s%*c", buffer);
    if (write(connfd, buffer, strlen(buffer)) == -1)
        die("write error", 0);

    bzero(buffer, BUFFER_LEN);
    if ((n = read(connfd, buffer, BUFFER_LEN)) == -1)
        die(buffer, 0);
    buffer[n] = '\0';
    printf("%s\n", buffer);
    if (strcmp(buffer, "password not match") == 0)
    {
        die(buffer, 1);
    }
    else
    {

        printf("logged in\nfetching data....\n");
        fetchPlayerData(connfd);
    }
}

void fetchPlayerData(int connfd)
{
    int recv = 0, n;
    /* get level */
    if ((n = read(connfd, &recv, sizeof(recv))) == -1)
        die("read error", 0);
    user.level = ntohl(recv);
    /* get hp */
    if ((n = read(connfd, &recv, sizeof(recv))) == -1)
        die("read error", 0);
    user.curHP = ntohl(recv);
    /* get mp */
    if ((n = read(connfd, &recv, sizeof(recv))) == -1)
        die("read error", 0);
    user.curMP = ntohl(recv);
    /* get exp */
    if ((n = read(connfd, &recv, sizeof(recv))) == -1)
        die("read error", 0);
    user.curExp = ntohl(recv);
    /* get stage */
    if ((n = read(connfd, &recv, sizeof(recv))) == -1)
        die("read error", 0);
    user.stage = ntohl(recv);
}

void playMenu()
{
    char choice;

    while (1)
    {
        printf("\n|---------------------------------------|");
        printf("\n|" RED "\tPLAY\t\t                " RESET "|");
        printf("\n|---------------------------------------|");
        printf("\n|---------------------------------------|");
        printf("\n|\t1. Campain                      |");
        printf("\n|\t2. Back                         |");
        printf("\n|---------------------------------------|");
        printf("\nYour choice(1, other to quit):");

        scanf("%c%*c", &choice);
        if (choice == '1')
        {
            campaign();
        }
        if (choice == '2')
        {
            break;
        }
        else {
            exit(0);
        }
    }
}