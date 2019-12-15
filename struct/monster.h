#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "skill.h"
#define MAX_MONSTER 10 /**< Maximum number of Monster */

/**
 * @brief MonsterInformation structure
 * 
 * Structure to store monster's information
 * */
typedef struct MonsterInformation
{
    char name[STRING_LEN]; /**< Monster name */
    int hp; /**< Monster hp */
    int mp; /**< Monster mp */ 
    int atk; /**< Monster attack */
    int def; /**< Monster defend */
    int exp; /**< EXP ammount earned on Monster defeat */
    Type type; /**< Monster Type */
    SkillInfo skills[4]; /**< Monster skill */
} MonsterInfo;

/**
 * @brief Load Monster Info from file
 * */
void loadMonsterInfo();

#endif