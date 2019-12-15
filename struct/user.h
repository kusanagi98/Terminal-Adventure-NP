/**
 * @file user.h
 * @brief File containing User structure and usage
 * */

#ifndef __USER_H__
#define __USER_H__

#include <stdio.h>

#define STRING_LEN 20 /**< Maximum number of character */

/**
 * @brief UserInformation structure
 * 
 * Structure to store user's information
 * */
typedef struct UserInformation
{
    char username[STRING_LEN]; /**< Username */
    char password[STRING_LEN]; /**< Password */
    int level; /**< Level */
    int curExp; /**< Current EXP */
    int curHP; /**< Current HP */
    int curMP; /**< Current MP */
    int stage; /**< Current stage */
} UserInfo;

/**
 * @brief UserInfoNode structure
 * 
 * Structure to store user's information as linked list
 * */
typedef struct UserInfoNode
{
    UserInfo user; /**< UserInfo */
    int loggedin; /**< Login status */
    struct UserInfoNode *next; /**< Next user */
} UserNode;


/**
 * @brief Create new UserNode with UserInfo
 * 
 * 
 * @param UserInfo Data for UserNode
 * 
 * @return A node created with provided data 
 * */
UserNode *makeNewNode(UserInfo data);

/**
 * @brief Insert a node to UserNode list
 * 
 * @param UserNode Root of an UserNode list
 * @param UserNode Node to insert
 * 
 * @return Root of an UserNode list with inserted node
 * */
UserNode *insertNode(UserNode *root, UserNode *new);

/**
 * @brief Free an UserNode list
 * 
 * @param UserNode Root of an UserNode list
 * */
void freeList(UserNode *root);

/**
 * @brief Print an UserNode list
 * 
 * @param UserNode Root of an UserNode list
 * */
void printList(UserNode *root);

/**
 * @brief Find an User from UserNode list
 * 
 * @param UserNode Root of an UserNode list
 * @param String Username to find
 * 
 * @return An UserNode on found
 * @return NULL on not found
 * */
UserNode *findUser(UserNode *root, char *username);

/**
 * @brief Sort a node to UserNode list
 * 
 * @param UserNode Root of an UserNode list
 * 
 * @return Root of an UserNode list with sorted node
 * */
UserNode *sortUserlist(UserNode *root);

/**
 * @brief Initial an UserInformation from username and password
 * 
 * @param String username
 * @param String password
 * 
 * @return new UserInfo
 * */
UserInfo initUserInfo(char *username, char *password);

/**
 * @brief Write an UserNode list to file
 * 
 * @param UserNode Root of an UserNode list
 * */
void writeUserData(UserNode *root);

#endif