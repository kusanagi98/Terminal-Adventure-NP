#ifndef __GAMEMASTER_H__
#define __GAMEMASTER_H__

#include "../struct/user.h"

extern UserNode *root;

/**
 * @brief Load UserInfo from file
 *
 * @return A list of UserNode
 * */
UserNode *loadUserInfo();

#endif