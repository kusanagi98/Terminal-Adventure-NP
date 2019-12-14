#ifndef __USER_H__
#define __USER_H__

#include <stdio.h>

#define STRING_LEN 20

typedef struct UserInformation
{
    char username[STRING_LEN];
    char password[STRING_LEN];
    int level;
    int curExp;
    int curHP;
    int curMP;
    int stage;
} UserInfo;

typedef struct UserInfoNode
{
    UserInfo user;
    int loggedin;
    struct UserInfoNode *next;
} UserNode;

void storeUserInfo(UserNode *head);

UserNode *makeNewNode(UserInfo data); //Create a new node for the account linked list

UserNode *insertNode(UserNode *root, UserNode *new); //Append the new node to the account linked list

void freeList(UserNode *root);

void printList(UserNode *root);

UserNode *findUser(UserNode *root, char *username);

UserNode *sortUserlist(UserNode *root);

UserInfo initUserInfo(char *username, char *password);

void writeUserData(UserNode *root);

#endif