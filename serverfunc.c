#include "serverfunc.h"

void handleRequest(int connfd, UserNode *root)
{
    char buffer[BUFFER_LEN];
    int n;

    bzero(buffer, BUFFER_LEN);
    /* read function */
    if ((n = read(connfd, buffer, BUFFER_LEN)) == -1)
        die("read error", 1);
    buffer[n] = '\0';
    printf("mode: %s\n", buffer);
    if (strcmp(buffer, "login") == 0)
    {
        login(connfd, root);
    }
    else if (strcmp(buffer, "register") == 0)
    {
        // do register
        printf("register");
    }
}

void login(int connfd, UserNode *root)
{
    char buffer[BUFFER_LEN];
    int n;
    UserNode *user;

    if (write(connfd, "confirmed", strlen("confirmed")) == -1)
        return;

    bzero(buffer, BUFFER_LEN);
    if ((n = read(connfd, buffer, BUFFER_LEN)) == -1)
        if (write(connfd, "die", strlen("die")) == -1)
            return;
    buffer[n] = '\0';
    user = findUser(root, buffer);

    if (user == NULL)
    {
        if ((n = write(connfd, "User not found", strlen("User not found"))) == -1)
            if (write(connfd, "die", strlen("die")) == -1)
                return;
    }
    else
    {
        if ((n = write(connfd, "password", strlen("password"))) == -1)
            if (write(connfd, "die", strlen("die")) == -1)
                return;
    }

    if ((n = read(connfd, buffer, BUFFER_LEN)) == -1)
        if (write(connfd, "die", strlen("die")) == -1)
            return;
    buffer[n] = '\0';

    if (strcmp(user->user.password, buffer) == 0)
    {
        if ((n = write(connfd, "logged in", strlen("logged in"))) == -1)
            if (write(connfd, "die", strlen("die")) == -1)
                return;
    }
    else if (write(connfd, "password not match", strlen("password not match")) == -1)
        return;

    sendPlayerInfo(connfd, user);
}

void sendPlayerInfo(int connfd, UserNode *user)
{
    int n, data;
    /* send user's level*/
    data = htonl(user->user.level);
    if ((n = write(connfd, &data, sizeof(data))) == -1)
    {
        if (write(connfd, "die", strlen("die")) == -1)
            return;
    }
    /* send user's hp*/
    data = htonl(user->user.curHP);
    if ((n = write(connfd, &data, sizeof(data))) == -1)
    {
        if (write(connfd, "die", strlen("die")) == -1)
            return;
    }
    /* send user's mp*/
    data = htonl(user->user.curMP);
    if ((n = write(connfd, &data, sizeof(data))) == -1)
    {
        if (write(connfd, "die", strlen("die")) == -1)
            return;
    }
    /* send user's exp*/
    data = htonl(user->user.curExp);
    if ((n = write(connfd, &data, sizeof(data))) == -1)
    {
        if (write(connfd, "die", strlen("die")) == -1)
            return;
    }
    /* send user's stage*/
    data = htonl(user->user.stage);
    if ((n = write(connfd, &data, sizeof(data))) == -1)
    {
        if (write(connfd, "die", strlen("die")) == -1)
            return;
    }
}
