#include <stdlib.h>
#include <string.h>
#include "user.h"


UserNode *findUser(UserNode *root, char *username)
{
    UserNode *tmp = root;
    while(tmp) {
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
    while(root) {
        printf("%s %s\n", root->user.username, root->user.password);
        root = root->next;
    }
}