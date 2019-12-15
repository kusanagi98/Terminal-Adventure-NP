#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "skill.h"
#define MAX_MONSTER 10

typedef struct MonsterInformation
{
    char name[STRING_LEN];
    int hp;
    int mp;
    int atk;
    int def;
    int exp;
    Type type;
    SkillInfo skills[4];
} MonsterInfo;

void loadMonsterInfo();

#endif