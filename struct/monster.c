#include <stdio.h>
#include <stdlib.h>
#include "monster.h"
#include "skill.h"

extern SkillInfo skills[];

MonsterInfo monsters[MAX_MONSTER];

void loadMonsterInfo()
{
    FILE *f;
    int i, j, skill_num, type_num;
    f = fopen("monsterinfo.txt", "r");
    if (f == NULL)
    {
        printf("Error: Can\'t read input file!\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < MAX_MONSTER; i++)
    {
        fscanf(f, "%s", monsters[i].name);
        fgetc(f);
        fscanf(f, "%d", &monsters[i].hp);
        fgetc(f);
        fscanf(f, "%d", &monsters[i].mp);
        fgetc(f);
        fscanf(f, "%d", &monsters[i].atk);
        fgetc(f);
        fscanf(f, "%d", &monsters[i].def);
        fgetc(f);
        fscanf(f, "%d", &monsters[i].exp);
        fgetc(f);
        fscanf(f, "%d", &type_num);
        monsters[i].type = type_num;
        for (j = 0; j < 4; j++)
        {
            fgetc(f);
            fscanf(f, "%d", &skill_num);
            monsters[i].skills[j] = skills[skill_num];
        }
    }
    fclose(f);
}