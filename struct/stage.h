#ifndef __STAGE_H__
#define __STAGE_H__

#include "monster.h"
#define MAX_STAGE 7 /**< Maximum number of stage */

/**
 * @brief StageInformation structure
 * 
 * Structure to store stage's information
 * */
typedef struct StageInformation
{
    int number; /**< Stage number */
    MonsterInfo monsters[10]; /**< Stage's monsters */
} StageInfo;

/**
 * @brief Load Stage Info from file
 * */
void loadStageInfo();

#endif