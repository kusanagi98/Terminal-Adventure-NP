#ifndef __STAGE_H__
#define __STAGE_H__

#include "monster.h"
#define MAX_STAGE 7

typedef struct StageInformation
{
    int number;
    MonsterInfo monsters[10];
} StageInfo;

void loadStageInfo();

#endif