#include "clientfunc.h"
#include "game.h"

extern UserInfo user;

void login(int connfd)
{
    char buffer[BUFFER_LEN];
    char username[STRING_LEN];
    char password[STRING_LEN];
    int n;

    /* input username & password */
    printf("Username: ");
    scanf("%s%*c", username);
    printf("Password: ");
    scanf("%s%*c", password);

    /* inform mode to server */
    if (write(connfd, "login", strlen("login")) == -1)
        die("write error", 0);
    bzero(buffer, BUFFER_LEN);
    if (write(connfd, buffer, strlen(buffer)) == -1)
        die("write error", 0);

    /* send format: username:password */
    bzero(buffer, BUFFER_LEN);
    strcpy(buffer, username);
    strcat(buffer, ":");
    strcat(buffer, password);
    if (write(connfd, buffer, strlen(buffer)) == -1)
        die("write error", 0);

    /* read reply from server */
    bzero(buffer, BUFFER_LEN);
    if ((n = read(connfd, buffer, BUFFER_LEN)) == -1)
        die(buffer, 0);
    buffer[n] = '\0';
    // buffer[n] = '\0';
    // printf("%s\n", buffer);
    if ((strcmp(buffer, "Password not match") == 0) || (strcmp(buffer, "User not found") == 0) || (strcmp(buffer, "die") == 0))
    {
        die(buffer, 0);
    }

    printf("%s\n", buffer);
    // else
    // {

    //     printf("logged in\nfetching data....\n");
    //     fetchPlayerData(connfd);
    // }
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
        else
        {
            exit(0);
        }
    }
}