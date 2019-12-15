#ifndef __SERVERFUNC_H__
#define __SERVERFUNC_H__
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <ctype.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>

#include "../helper/mysocket.h"
#include "../struct/user.h"

#define BUFFER_LEN 1024 /**< Maximum of buffer lenght */

/**
 * @brief Redirect client request to right function
 * 
 * @param(int) connection file desciptor
 * @param(UserNode *) user list 
 * 
 * @return redirected function
 * */
int handleRequest(int connfd, UserNode **root);

/**
 * @brief User login handle
 * 
 * @param int connection file description
 * @param UserNode user list root
 * 
 * @return 1 on success
 * @return 0 on error
 * */
int login(int connfd, UserNode *root);

/**
 * @brief Add new user when client register
 * 
 * @param int connection file descriptor
 * @param UserNode pointer to user list
 * 
 * @return 1 on success
 * @return 0 on error
 * */
int addUser(int connfd, UserNode **root);

/**
 * @brief Send player info to client
 * 
 * @param int connection file description
 * @param UserNode user list root
 * 
 * @return 1 on success
 * @return 0 on error
 * */
int sendPlayerInfo(int connfd, UserNode *root);

/**
 * @brief Update user stat
 * 
 * @param int connection file descriptor
 * @param UserNode* pointer to user list
 * 
 * @return 1 on success
 * @return 0 on error
 * */
int updatePlayerInfo(int connfd, UserNode **root);


/**
 * @brief Send users high score to client
 * 
 * @param int connection file description
 * @param UserNode user list root
 * 
 * @return 1 on success
 * @return 0 on error
 * */
int sendHighScore(int connfd, UserNode *root);

#endif