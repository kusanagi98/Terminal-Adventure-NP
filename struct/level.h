#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "skill.h"
#define MAX_LEVEL 20

typedef struct LevelInformation
{
    int level;
    int hp;
    int mp;
    int atk;
    int def;
    int maxexp;
    int count;
    SkillInfo skills[20];
} LevelInfo;

void loadLevelInfo();

#endif