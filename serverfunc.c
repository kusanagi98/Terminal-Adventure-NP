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

    /* read info from client
        format: username:password */
    bzero(buffer, BUFFER_LEN);
    if ((n = read(connfd, buffer, BUFFER_LEN)) == -1)
        if (write(connfd, "die", strlen("die")) == -1)
            return;
    buffer[n] = '\0';

    /* split information */
    char *username = strtok(buffer, ":");
    printf("username: %s\n", username);
    char *password = strtok(NULL, ":");
    printf("password: %s\n", password);
    user = findUser(root, username);

    if (user == NULL)
    {
        if ((n = write(connfd, "User not found", strlen("User not found"))) == -1)
        {
            if (write(connfd, "die", strlen("die")) == -1)
                return;
        }
    }
    else if (strcmp(user->user.password, password) == 0)
    {
        if ((n = write(connfd, "Logged in", strlen("Logged in"))) == -1)
            if (write(connfd, "die", strlen("die")) == -1)
                return;
    }
    else
    {
        if (write(connfd, "Password not match", strlen("Password not match")) == -1)
            return;
    }

    // sendPlayerInfo(connfd, user);
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
