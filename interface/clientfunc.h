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

#ifndef __CLIENTFUNC_H__
#define __CLIENTFUNC_H__

#define BUFFER_LEN 1024 /**< Maximum of buffer lenght */

/**
 * @brief Fill login form and send to server
 * 
 * @param int connection file desciptor
 * */
void login(int connfd);

/**
 * @brief Fill register form and send to server
 * 
 * @param int connection file desciptor
 * */
void registerFunc(int connfd);

/**
 * @brief Get player data from server
 * 
 * @param int connection file desciptor
 * */
void fetchPlayerData(int connfd);

/**
 * @brief Play menu
 * 
 * @param int connection file desciptor
 * */
void playMenu(int connfd);

/**
 * @brief Request for update user current status
 * 
 * @param int connection file desciptor
 * */
void updateUserInfo(int connfd, UserInfo user);

/**
 * @brief Get highscore list from server
 * 
 * @param int connection file descriptor
 * */
void fetchHighScore(int connfd);


/**
 * @brief Inform logout to server
 * 
 * @param int connection file descriptor
 * */
void logout(int connfd);

#endif