#include <stdio.h>
#include <stdlib.h>
#include "level.h"
#include "skill.h"

extern SkillInfo skills[];

LevelInfo levels[MAX_LEVEL];

void loadLevelInfo()
{
    FILE *f;
    int i, j, skill_num;
    f = fopen("levelinfo.txt", "r");
    if (f == NULL)
    {
        printf("Error: Can\'t read input file!\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < MAX_LEVEL; i++)
    {
        fscanf(f, "%d", &levels[i].level);
        fgetc(f);
        fscanf(f, "%d", &levels[i].hp);
        fgetc(f);
        fscanf(f, "%d", &levels[i].mp);
        fgetc(f);
        fscanf(f, "%d", &levels[i].atk);
        fgetc(f);
        fscanf(f, "%d", &levels[i].def);
        fgetc(f);
        fscanf(f, "%d", &levels[i].maxexp);
        fgetc(f);
        fscanf(f, "%d", &levels[i].count);
        for (j = 0; j < levels[i].count; j++)
        {
            fgetc(f);
            fscanf(f, "%d", &skill_num);
            levels[i].skills[j] = skills[skill_num];
        }
    }
    fclose(f);
}