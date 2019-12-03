#ifndef __GAME_H__
#define __GAME_H__
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

//GAME MECHANICS FUNCTIONS
int damageCalculationPlayer(SkillInfo skill, LevelInfo player, MonsterInfo monster);
int damageCalculationMonster(SkillInfo skill, LevelInfo player, MonsterInfo monster);
SkillInfo monsterAI(MonsterInfo monster, int curHP);
void campaign();
char gameoverChoice();
char stageoverChoice();
//UTILITY FUNCTIONS
void printUserLog(char user[], char skill[], int dmg, Type type);
void printMonsterLog(char monster[], char skill[], int dmg, Type type);

#endif

