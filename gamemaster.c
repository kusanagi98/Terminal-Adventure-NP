
#include <stdio.h>
#include <stdlib.h>
#include "user.h"

UserNode *loadUserInfo()
{
    FILE *f;
    UserInfo tmp;
    UserNode *list = NULL;
    f = fopen("userinfo.txt", "r");
    if (f == NULL)
    {
        printf("Error: Can\'t read input file!\n");
        exit(EXIT_FAILURE);
    }
    while (fscanf(f, "%s", tmp.username) != EOF)
    {
        fgetc(f);
        fscanf(f, "%s", tmp.password);
        fgetc(f);
        fscanf(f, "%d", &tmp.level);
        fgetc(f);
        fscanf(f, "%d", &tmp.curExp);
        fgetc(f);
        fscanf(f, "%d", &tmp.curHP);
        fgetc(f);
        fscanf(f, "%d", &tmp.curMP);
        fgetc(f);
        fscanf(f, "%d", &tmp.stage);
        list = insertNode(list, makeNewNode(tmp));
    }
    fclose(f);
    return list;
}