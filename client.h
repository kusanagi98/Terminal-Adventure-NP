#ifndef __CLIENT_H__
#define __CLIENT_H__
#include "monster.h"
#include "skill.h"
#include "level.h"
#define BUF_SIZE 100
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

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
    struct UserInfoNode *next;
} UserNode;


//GAME MECHANICS FUNCTIONS
int damageCalculationPlayer(SkillInfo skill, LevelInfo player, MonsterInfo monster);
int damageCalculationMonster(SkillInfo skill, LevelInfo player, MonsterInfo monster);
SkillInfo monsterAI(MonsterInfo monster, int curHP);
//UTILITY FUNCTIONS
UserNode *loadUserInfo();



UserNode *makeNewNode(UserInfo data); //Create a new node for the account linked list

UserNode *insertNode(UserNode *root, UserNode *new); //Append the new node to the account linked list

void freeList(UserNode *root);

#endif

