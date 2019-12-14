#ifndef __GAMEMASTER_H__
#define __GAMEMASTER_H__

#include "../struct/user.h"

extern UserNode *root;

// Move these to server
UserNode *loadUserInfo();

#endif