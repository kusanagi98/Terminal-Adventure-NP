#include "serverfunc.h"
#include "../helper/helper.h"

int handleRequest(int connfd, UserNode **root)
{
    char buffer[BUFFER_LEN];
    int n;

    /* command */

    bzero(buffer, BUFFER_LEN);
    /* read function */
    if ((n = read(connfd, buffer, BUFFER_LEN)) == -1)
        return 0;
    buffer[n] = '\0';
    printf("mode: %s\n\n", buffer);
    if ((n = write(connfd, "OK", strlen("OK"))) == -1)
    {
        if (write(connfd, "die", strlen("die")) == -1)
            return 0;
    }

    if (strcmp(buffer, "login") == 0)
    {
        return login(connfd, *root);
    }
    else if (strcmp(buffer, "register") == 0)
    {
        addUser(connfd, root);
    }
    else if (strcmp(buffer, "Fetch user data") == 0)
    {
        return sendPlayerInfo(connfd, *root);
    }
    else if (strcmp(buffer, "Update user data") == 0)
    {
        return updatePlayerInfo(connfd, root);
    }
    else if(strcmp(buffer, "Fetch high score") == 0)
    {
        return sendHighScore(connfd, *root);
    }
    else
    {
        return 0;
    }

    return 0;
}

int login(int connfd, UserNode *root)
{
    char buffer[BUFFER_LEN];
    int n;
    UserNode *user;

    /* read info from client
        format: username:password */
    bzero(buffer, BUFFER_LEN);
    if ((n = read(connfd, buffer, BUFFER_LEN)) == -1)
    {
        if (write(connfd, "die", strlen("die")) == -1)
            return 0;

        return 0;
    }
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
                return 0;

            return 0;
        }
    }
    else if (strcmp(user->user.password, password) == 0)
    {
        if(user->loggedin == 0) {
            user->loggedin = 1;
            if ((n = write(connfd, "Logged in", strlen("Logged in"))) == -1)
            {
                if (write(connfd, "die", strlen("die")) == -1)
                {
                    return 0;
                }

                return 0;
            }
        }
        else if(user->loggedin == 1){
           if ((n = write(connfd, "Cant login", strlen("Cant login"))) == -1)
            {
                if (write(connfd, "die", strlen("die")) == -1)
                {
                    return 0;
                }

                return 0;
            } 
        }

        return 1;
    }
    else
    {
        if (write(connfd, "Password not match", strlen("Password not match")) == -1)
        {
            return 0;
        }
    }

    return 1;
}

int sendPlayerInfo(int connfd, UserNode *root)
{
    int n, data;
    char buffer[BUFFER_LEN];

    if ((n = read(connfd, buffer, BUFFER_LEN)) == -1)
    {
        if (write(connfd, "die", strlen("die")) == -1)
            return 0;
        return 0;
    }
    buffer[n] = '\0';
    UserNode *user = findUser(root, buffer);

    /* send user's level*/
    data = htonl(user->user.level);
    if ((n = write(connfd, &data, sizeof(data))) == -1)
    {
        if (write(connfd, "die", strlen("die")) == -1)
            return 0;

        return 0;
    }
    /* send user's hp*/
    data = htonl(user->user.curHP);
    if ((n = write(connfd, &data, sizeof(data))) == -1)
    {
        if (write(connfd, "die", strlen("die")) == -1)
            return 0;

        return 0;
    }
    /* send user's mp*/
    data = htonl(user->user.curMP);
    if ((n = write(connfd, &data, sizeof(data))) == -1)
    {
        if (write(connfd, "die", strlen("die")) == -1)
            return 0;

        return 0;
    }
    /* send user's exp*/
    data = htonl(user->user.curExp);
    if ((n = write(connfd, &data, sizeof(data))) == -1)
    {
        if (write(connfd, "die", strlen("die")) == -1)
            return 0;
        return 0;
    }
    /* send user's stage*/
    data = htonl(user->user.stage);
    if ((n = write(connfd, &data, sizeof(data))) == -1)
    {
        if (write(connfd, "die", strlen("die")) == -1)
            return 0;
        return 0;
    }

    return 1;
}

int sendHighScore(int connfd, UserNode *root)
{
    // TODO
    int n;
    char *buffer;
    char temp[BUFFER_LEN];

    root = sortUserlist(root);

    while(root != NULL)
    {
        buffer = userHighScoreFormat(root->user.username, root->user.stage);
        printf("%s\n", buffer);
        if ((n = write(connfd, buffer, BUFFER_LEN)) == -1)
        {
            if (write(connfd, "die", strlen("die")) == -1)
                return 0;
            return 0;
        }

        if ((n = read(connfd, temp, BUFFER_LEN)) == -1)
        {
            if (write(connfd, "die", strlen("die")) == -1)
                return 0;
            return 0;
        }
        root = root->next;
    }

    if ((n = write(connfd, "END", strlen("END"))) == -1)
    {
        if (write(connfd, "die", strlen("END")) == -1)
            return 0;
        return 0;
    }

    if ((n = read(connfd, temp, BUFFER_LEN)) == -1)
    {
        if (write(connfd, "die", strlen("die")) == -1)
            return 0;
        return 0;
    }

    printf("%s return 1\n", temp);

    return 1;
}

int updatePlayerInfo(int connfd, UserNode **root)
{
    int n;
    char buffer[BUFFER_LEN];

    if ((n = read(connfd, buffer, BUFFER_LEN)) == -1)
    {
        if (write(connfd, "die", strlen("die")) == -1)
            return 0;
        return 0;
    }
    buffer[n] = '\0';

    char *username = strtok(buffer, ":");
    int level = atoi(strtok(NULL, ":"));
    int curExp = atoi(strtok(NULL, ":"));
    int curHP = atoi(strtok(NULL, ":"));
    int curMP = atoi(strtok(NULL, ":"));
    int stage = atoi(strtok(NULL, ":"));

    UserNode *user = findUser(*root, username);
    user->user.level = level;
    user->user.curExp = curExp;
    user->user.curHP = curHP;
    user->user.curMP = curMP;
    user->user.stage = stage;

    writeUserData(*root);

    return 1;
}

int addUser(int connfd, UserNode **root)
{
    char buffer[BUFFER_LEN];
    int n;
    UserNode *user;

    /* read info from client
        format: username:password */
    bzero(buffer, BUFFER_LEN);
    if ((n = read(connfd, buffer, BUFFER_LEN)) == -1)
    {
        if (write(connfd, "die", strlen("die")) == -1)
            return 0;

        return 0;
    }
    buffer[n] = '\0';

    /* split information */
    char *username = strtok(buffer, ":");
    printf("username: %s\n", username);
    char *password = strtok(NULL, ":");
    printf("password: %s\n", password);
    user = findUser(*root, username);

    if(user == NULL)
    {
        UserInfo userInfo = initUserInfo(username, password);
        /* init user info */
        *root = insertNode(*root, makeNewNode(userInfo));
        writeUserData(*root);
        if ((n = write(connfd, "Register success", strlen("Register success"))) == -1)
        {
            if (write(connfd, "die", strlen("die")) == -1)
                return 0;
            return 0;
        }
    }
    else {
        if ((n = write(connfd, "User existed", strlen("User existed"))) == -1)
        {
            if (write(connfd, "die", strlen("die")) == -1)
                return 0;
            return 0;
        }
    }

    return 1;
}
