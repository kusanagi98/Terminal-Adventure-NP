#include <stdio.h>
#include <stdlib.h>
#include "stage.h"
#include "monster.h"

extern MonsterInfo monsters[];

StageInfo stages[MAX_STAGE];

void loadStageInfo()
{
    FILE *f;
    int i, j, monster_num;
    f = fopen("stageinfo.txt", "r");
    if (f == NULL)
    {
        printf("Error: Can\'t read input file!\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < MAX_STAGE; i++)
    {
        fscanf(f, "%d", &stages[i].number);
        for (j = 0; j < stages[i].number; j++)
        {
            fgetc(f);
            fscanf(f, "%d", &monster_num);
            stages[i].monsters[j] = monsters[monster_num];
        }
    }
    fclose(f);
}