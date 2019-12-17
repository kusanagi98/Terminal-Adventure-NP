#include "clientfunc.h"
#include "../game/game.h"
#include <string.h>
#include <stdlib.h>

extern UserInfo user;
extern int loginStatus;
extern struct sockaddr_in servaddr;

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
    if ((n = read(connfd, buffer, BUFFER_LEN) == -1))
        die("read error", 0);

    /* send format: username:password */
    bzero(buffer, BUFFER_LEN);
    strcpy(buffer, username);
    strcat(buffer, ":");
    strcat(buffer, password);
    if (write(connfd, buffer, strlen(buffer)) == -1)
        die("write error", 0);

    /* re ad reply from server */
    bzero(buffer, BUFFER_LEN);
    if ((n = read(connfd, buffer, BUFFER_LEN)) == -1)
        die(buffer, 0);
    buffer[n] = '\0';
    // buffer[n] = '\0';
    // printf("%s\n", buffer);
    if (strcmp(buffer, "Password not match") == 0)
    {
        die(buffer, 0);
    }
    else if (strcmp(buffer, "User not found") == 0)
    {
        die(buffer, 0);
    }
    else if (strcmp(buffer, "Cant login") == 0)
    {
        die(buffer, 0);
    }
    else if (strcmp(buffer, "die") == 0)
    {
        die(buffer, 0);
    }

    printf("%s\n", buffer);
    loginStatus = 1;
    strcpy(user.username, username);
}

void registerFunc(int connfd)
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
    if (write(connfd, "register", strlen("register")) == -1)
        die("write error", 0);
    if ((n = read(connfd, buffer, BUFFER_LEN) == -1))
        die("read error", 0);

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
    if (strcmp(buffer, "User existed") == 0)
    {
        die(buffer, 0);
    }
    else if (strcmp(buffer, "die") == 0)
    {
        die(buffer, 0);
    }

    printf("%s\n", buffer);
    strcpy(user.username, username);
}

void fetchPlayerData(int connfd)
{
    int recv = 0, n;
    char buffer[BUFFER_LEN];

    if (write(connfd, "Fetch user data", strlen("Fetch user data")) == -1)
        die("write error", 0);

    if ((n = read(connfd, buffer, BUFFER_LEN) == -1))
        die("read error", 0);

    if (write(connfd, user.username, strlen(user.username)) == -1)
        die("write error", 0);

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

void fetchHighScore(int connfd)
{
    char buffer[BUFFER_LEN];
    int n;
    int counter = 1;

    if (write(connfd, "Fetch high score", strlen("Fetch high score")) == -1)
        die("write error", 0);

    if ((n = read(connfd, buffer, BUFFER_LEN) == -1))
        die("read error", 0);

    printf("\n----------------------------------------\n");
    printf(RED "HIGH SCORE\n" RESET);
    while (1)
    {
        bzero(buffer, BUFFER_LEN);
        if ((n = read(connfd, buffer, BUFFER_LEN) == -1))
            die("read error", 0);

        if (strcmp(buffer, "END") == 0)
            break;
        if (counter == 1)
            printf(RED "%d. %s\n" RESET, counter, buffer);
        else if (counter == 2 || counter == 3)
            printf(YEL "%d. %s\n" RESET, counter, buffer);
        else
            printf("%d. %s\n", counter, buffer);

        if (write(connfd, "OK", strlen("OK")) == -1)
            die("write error", 0);

        counter++;
    }
    printf("----------------------------------------\n");

    if (write(connfd, "OK", strlen("OK")) == -1)
        die("write error", 0);
}

void updateUserInfo(int connfd, UserInfo user)
{
    char buffer[BUFFER_LEN];
    char temp[20];
    if (write(connfd, "Update user data", strlen("Update user data")) == -1)
        die("write error", 0);

    if (read(connfd, buffer, BUFFER_LEN) == -1)
        die("write error", 0);

    bzero(buffer, BUFFER_LEN);

    strcpy(buffer, user.username);
    strcat(buffer, ":");

    sprintf(temp, "%d", user.level);
    strcat(buffer, temp);
    strcat(buffer, ":");
    bzero(temp, 20);

    sprintf(temp, "%d", user.curExp);
    strcat(buffer, temp);
    strcat(buffer, ":");
    bzero(temp, 20);

    sprintf(temp, "%d", user.curHP);
    strcat(buffer, temp);
    strcat(buffer, ":");
    bzero(temp, 20);

    sprintf(temp, "%d", user.curMP);
    strcat(buffer, temp);
    strcat(buffer, ":");
    bzero(temp, 20);

    sprintf(temp, "%d", user.stage);
    strcat(buffer, temp);
    bzero(temp, 20);

    // printf("%s\n", buffer);
    if (write(connfd, buffer, BUFFER_LEN) == -1)
        die("write error", 0);
}

void playMenu(int connfd)
{
    int choice;

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

        scanf("%d%*c", &choice);
        if (choice == 1)
        {
            fetchPlayerData(connfd);
            campaign();
        }
        else if (choice == 2)
        {
            break;
        }
        else
        {
            printf("Invalid choice. Please try again\n");
            continue;
        }
    }
}

void logout(int connfd)
{
    char buffer[BUFFER_LEN];
    if(loginStatus == 0)
    {
        printf("Cannot logout now. Please login first\n");
        return;
    }

    if (write(connfd, "Logout", strlen("Logout")) == -1)
        die("write error", 0);

    if (read(connfd, buffer, BUFFER_LEN) == -1)
        die("write error", 0);

    bzero(buffer, BUFFER_LEN);

    /* inform username */
    if (write(connfd, user.username, strlen(user.username)) == -1)
        die("write error", 0);

    if (read(connfd, buffer, BUFFER_LEN) == -1)
        die("write error", 0);

    printf("%s\n", buffer);
    if(strcmp(buffer, "Logged out") == 0)
    {
        loginStatus = 0;
    }
}