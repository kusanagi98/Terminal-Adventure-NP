#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "skill.h"
#define MAX_LEVEL 20

/**
 * @brief LevelInformation Structure
 * 
 * Structure to store Player Level's Information 
 * */
typedef struct LevelInformation
{
    int level; /**< Level */
    int hp; /**< HP */
    int mp; /**< MP */
    int atk; /**< Attack */
    int def; /**< Defend */
    int maxexp; /**< Max Exp */
    int count; /**< Skill count */
    SkillInfo skills[20];
} LevelInfo;

/**
 * @brief Load LevelInfo from file
 * */
void loadLevelInfo();

#endif