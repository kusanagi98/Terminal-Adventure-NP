#include <stdlib.h>
#include <string.h>
#include "user.h"


UserNode *findUser(UserNode *root, char *username)
{
    UserNode *tmp = root;
    while(tmp != NULL) {
        if (strcmp(tmp->user.username, username) == 0)
            return tmp;
        tmp = tmp->next;
    }

    return NULL;
}

UserNode *makeNewNode(UserInfo data)
{
    UserNode *new = (UserNode *)malloc(sizeof(UserNode));
    new->user = data;
    new->loggedin = 0;
    new->next = NULL;
    return new;
}

UserNode *insertNode(UserNode *root, UserNode *new)
{
    UserNode *cur = NULL;
    if (root == NULL)
        return new;
    cur = root;
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = new;
    return root;
}

void freeList(UserNode *root)
{
    UserNode *tmp = NULL;
    while (root != NULL)
    {
        tmp = root;
        root = root->next;
        free(tmp);
    }
}

void printList(UserNode *root)
{
    while(root != NULL) {
        printf("%s %s %d\n", root->user.username, root->user.password, root->user.stage);
        root = root->next;
    }
}

UserNode *sortUserlist(UserNode *root)
{
    UserNode *curr = root, *temp;
    UserNode *swapper = (UserNode*)malloc(sizeof(UserNode));
    while(curr != NULL)
    {
        temp = curr;
        while(temp != NULL)
        {
            if(temp->user.stage > curr->user.stage) {
                printf("swapping: %s - %s\n", curr->user.username, temp->user.username);
                swapper->user = curr->user;
                curr->user = temp->user;
                temp->user = swapper->user;
            }
            temp = temp->next;
        }

        curr = curr->next;
    }

    return root;
}

UserInfo initUserInfo(char *username, char *password)
{
    UserInfo userInfo;

    strcpy(userInfo.username, username);
    strcpy(userInfo.password, password);
    userInfo.curExp = 0;
    userInfo.curHP = 100;
    userInfo.curMP = 50;
    userInfo.stage = 1;
    userInfo.level = 1;

    return userInfo;
}

void writeUserData(UserNode *root)
{
    UserNode *curr = root;
    FILE *f = fopen("userinfo.txt", "w+");
    if (f == NULL)
        return;

    while (curr != NULL)
    {
        fprintf(f, "%s %s %d %d %d %d %d\n",
                curr->user.username,
                curr->user.password,
                curr->user.level,
                curr->user.curExp,
                curr->user.curHP,
                curr->user.curMP,
                curr->user.stage);
        curr = curr->next;
    }

    fclose(f);
}