#ifndef __GAME_H__
#define __GAME_H__
#include "../struct/monster.h"
#include "../struct/skill.h"
#include "../struct/level.h"
#define BUF_SIZE 100 /**< Maximum buffer size */
#define RED   "\x1B[31m" /**< Print in Red color */
#define GRN   "\x1B[32m" /**< Print in Greed color */
#define YEL   "\x1B[33m" /**< Print in Yellow color */
#define BLU   "\x1B[34m" /**< Print in Blue color */
#define MAG   "\x1B[35m" /**< Print in Mag color */
#define CYN   "\x1B[36m" /**< Print in Cyn color */ 
#define WHT   "\x1B[37m" /**< Print in White color */
#define RESET "\x1B[0m" /**< Print Reset */

/**
 * @brief Player's damage calculation
 * 
 * @param SkillInfo Player skill
 * @param LevelInfo Player's level info
 * @param MonsterInfo Monster information
 * */
int damageCalculationPlayer(SkillInfo skill, LevelInfo player, MonsterInfo monster);

/**
 * @brief Monster's damage calculation
 * 
 * @param SkillInfo Monster skill
 * @param LevelInfo Player's level info
 * @param MonsterInfo Monster information
 * */
int damageCalculationMonster(SkillInfo skill, LevelInfo player, MonsterInfo monster);

/**
 * @brief Monster's behavior
 * 
 * @param MonsterInfo Monster information
 * @param int Monster current HP
 * 
 * @return Monster Skill
 * */
SkillInfo monsterAI(MonsterInfo monster, int curHP);

/**
 * @brief PVE mode
 * */
void campaign();

/**
 * @brief Game over menu
 * 
 * @return Player choice
 * */
char gameoverChoice();

/**
 * @brief Game over menu
 * 
 * @return Player choice
 * */
char stageoverChoice();

/**
 * @brief Print User log
 * 
 * @param String Username
 * @param String Skill name
 * @param int Damage
 * @param Type Skill type
 * */
void printUserLog(char user[], char skill[], int dmg, Type type);

/**
 * @brief Print Monster log
 * 
 * @param String Monster name
 * @param String Skill name
 * @param int Damage
 * @param Type Skill type
 * */
void printMonsterLog(char monster[], char skill[], int dmg, Type type);

#endif

