#include <sys/types.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "skill.h"
#include "monster.h"
#include "level.h"
#include "stage.h"
#include "game.h"
extern SkillInfo skills[];
extern LevelInfo levels[];
extern MonsterInfo monsters[];
extern StageInfo stages[];
int userCurHP, userCurMP, userCurLevel, userCurExp, userCurStage, monsterCurHP, monsterCurMP, curDmg;
int userStageHP, userStageMP; //Hold user's hp and mp at the start of the stage for reload
SkillInfo monsterSkill;
extern UserNode *root;
void campaign()
{
    int i, j, k, x;
    char ch1, ch2, ch3, ch4, temp;
    char nattack[] = "Normal Attack";
    printf("%s\n", root->user.username);
    printf("Game start\n");
    printf("--------------------------------\n");
    // Hold user info to local variables
    userCurLevel = root->user.level;
    userCurHP = root->user.curHP;
    userCurMP = root->user.curMP;
    userCurExp = root->user.curExp;
    userCurStage = root->user.stage;
    // Go through all the stages from the saved one
    for (i = userCurStage; i < MAX_STAGE; i++)
    {
        ch3 = '0';
        ch4 = '0';
        userStageHP = userCurHP;
        userStageMP = userCurMP;
        printf("Stage %d\n", i);
        printf("--------------------------------\n");
        // Go through all the monsters
        for (j = 0; j < stages[i].number; j++)
        {
            printf("A wild" MAG " %s " RESET "appears\n", stages[i].monsters[j].name);
            printf("--------------------------------\n");
            monsterCurHP = stages[i].monsters[j].hp;
            monsterCurMP = stages[i].monsters[j].mp;
            while (1)
            {
                printf(YEL "%s" RESET "\t" MAG "%s\n" RESET, root->user.username, stages[i].monsters[j].name);
                printf(YEL "HP" RESET ":%d\t" MAG "HP" RESET ":%d\n", userCurHP, monsterCurHP);
                printf(YEL "MP" RESET ":%d\t" MAG "MP" RESET ":%d\n", userCurMP, monsterCurMP);
                printf("--------------------------------\n");
                // User command
                do
                {
                    printf("1. %s\n", nattack);
                    printf("2. Skills\n");
                    printf("Your choice:\n");
                    ch1 = getchar();
                    scanf("%c", &temp); //Consume a \n character. Press enter an extra time if no input
                    if (ch1 == '1')
                    {
                        printf("--------------------------------\n");
                        // Normal Attack
                        curDmg = damageCalculationPlayer(skills[SKILL_COUNT - 1], levels[userCurLevel - 1], stages[i].monsters[j]);
                        monsterCurHP -= curDmg;
                        printUserLog(root->user.username, nattack, curDmg, T_NORMAL);
                    }
                    else if (ch1 == '2')
                    {
                        // Skills
                        for (k = 0; k < levels[userCurLevel - 1].count; k++)
                        {
                            printf("%d. %s\n", k + 1, levels[userCurLevel - 1].skills[k].name);
                        }
                        printf("Your choice:\n");
                        ch2 = getchar();
                        scanf("%c", &temp); //Consume a \n character. Press enter an extra time if no input
                        x = ch2 - '0';
                        if (x < 1 || x > levels[userCurLevel - 1].count)
                        {
                            // Repeat the loop
                            ch1 = '3';
                            //continue;
                        }
                        else
                        {
                            printf("--------------------------------\n");
                            if (userCurMP >= levels[userCurLevel - 1].skills[x - 1].mpcost)
                            {
                                // Healing
                                if (levels[userCurLevel - 1].skills[x - 1].type == T_HEAL)
                                {
                                    curDmg = levels[userCurLevel - 1].skills[x - 1].dmg * levels[userCurLevel - 1].def;
                                    userCurHP += curDmg;
                                    if (userCurHP > levels[userCurLevel - 1].hp)
                                    {
                                        curDmg -= userCurHP - levels[userCurLevel - 1].hp;
                                        userCurHP = levels[userCurLevel - 1].hp;
                                    }
                                    printUserLog(root->user.username, levels[userCurLevel - 1].skills[x - 1].name, curDmg, levels[userCurLevel - 1].skills[x - 1].type);
                                }
                                else
                                {
                                    curDmg = damageCalculationPlayer(levels[userCurLevel - 1].skills[x - 1], levels[userCurLevel - 1], stages[i].monsters[j]);
                                    monsterCurHP -= curDmg;
                                    userCurMP -= levels[userCurLevel - 1].skills[x - 1].mpcost;
                                    printUserLog(root->user.username, levels[userCurLevel - 1].skills[x - 1].name, curDmg, levels[userCurLevel - 1].skills[x - 1].type);
                                }
                            }
                            else
                            {
                                printf("Not enough MP\n");
                                ch1 = '3';
                            }
                        }
                    }
                    else
                    {
                        //continue;
                    }
                } while (ch1 != '1' && ch1 != '2');
                // Monster turn
                if (monsterCurHP > 0)
                {
                    monsterSkill = monsterAI(stages[i].monsters[j], monsterCurHP);
                    // Healing
                    if (monsterSkill.type == T_HEAL)
                    {
                        curDmg = monsterSkill.dmg * stages[i].monsters[j].def;
                        monsterCurHP += curDmg;
                        if (monsterCurHP > stages[i].monsters[j].hp)
                        {
                            curDmg -= monsterCurHP - stages[i].monsters[j].hp;
                            monsterCurHP = stages[i].monsters[j].hp;
                        }
                        printMonsterLog(stages[i].monsters[j].name, monsterSkill.name, curDmg, monsterSkill.type);
                    }
                    else
                    {
                        curDmg = damageCalculationMonster(monsterSkill, levels[userCurLevel - 1], stages[i].monsters[j]);
                        userCurHP -= curDmg;
                        printMonsterLog(stages[i].monsters[j].name, monsterSkill.name, curDmg, monsterSkill.type);
                        if (userCurHP <= 0)
                        {
                            //Reload from the start of the stage or stop
                            printf("--------------------------------\n");
                            printf(YEL "%s" RESET " lost\n", root->user.username);
                            printf("--------------------------------\n");
                            ch3 = gameoverChoice();
                            break;
                        }
                    }
                }
                else
                {
                    break;
                }
            }
            // Loss
            if (ch3 == '1' || ch3 == '2')
            {
                break;
            }
            // Win
            printf("--------------------------------\n");
            printf(YEL "%s" RESET " defeated %s\n", root->user.username, stages[i].monsters[j].name);
            if (userCurLevel < MAX_LEVEL)
            {
                printf(YEL "%s" RESET " gained %d EXP\n", root->user.username, stages[i].monsters[j].exp);
                userCurExp += stages[i].monsters[j].exp;
                if (userCurExp >= levels[userCurLevel - 1].maxexp)
                {
                    userCurLevel += 1;
                    userCurHP = levels[userCurLevel - 1].hp;
                    userCurMP = levels[userCurLevel - 1].mp;
                    userCurExp = 0;
                    printf(YEL "%s" RESET " grew to Level %d \n", root->user.username, userCurLevel);
                }
            }
            printf("--------------------------------\n");
        }
        if (ch3 == '1')
        {
            i--;
            userCurHP = userStageHP;
            userCurMP = userStageMP;
        }
        // Stop playing
        else if (ch3 == '2')
        {
            break;
        }
        else
        {
            printf("--------------------------------\n");
            printf(YEL "%s" RESET " beat stage %d\n", root->user.username, i);
            printf("--------------------------------\n");
            userCurStage += 1;
            //Save (move to server)
            root->user.level = userCurLevel;
            root->user.curExp = userCurExp;
            root->user.curHP = userCurHP;
            root->user.curMP = userCurMP;
            root->user.stage = userCurStage;
            storeUserInfo(root);
            ////Menu for continue or stop playing
            ch4 = stageoverChoice();
            if (ch4 == '2')
            {
                break;
            }
        }
    }
    // Stop playing
    if (ch3 == '2' || ch4 == '2')
    {
        return;
    }
    printf("Congrats you beat the game\n");
}
int damageCalculationPlayer(SkillInfo skill, LevelInfo player, MonsterInfo monster)
{
    if ((skill.type == T_FIRE && monster.type == T_GRASS) || (skill.type == T_WATER && monster.type == T_FIRE) || (skill.type == T_GRASS && monster.type == T_WATER))
    {
        return player.atk * skill.dmg / monster.def * 2;
    }
    else if ((skill.type == T_FIRE && monster.type == T_WATER) || (skill.type == T_FIRE && monster.type == T_GRASS) || (skill.type == T_WATER && monster.type == T_WATER) || (skill.type == T_WATER && monster.type == T_GRASS) || (skill.type == T_GRASS && monster.type == T_GRASS) || (skill.type == T_GRASS && monster.type == T_FIRE))
    {
        return player.atk * skill.dmg / monster.def / 2;
    }
    else
    {
        return player.atk * skill.dmg / monster.def;
    }
}
int damageCalculationMonster(SkillInfo skill, LevelInfo player, MonsterInfo monster)
{
    return monster.atk * skill.dmg / player.def;
}
SkillInfo monsterAI(MonsterInfo monster, int curHP)
{
    double MaxHP = monster.hp;
    if (curHP >= 60 * MaxHP / 100)
    {
        return monster.skills[0];
    }
    else if (curHP >= 40 * MaxHP / 100)
    {
        return monster.skills[1];
    }
    else if (curHP >= 20 * MaxHP / 100)
    {
        return monster.skills[2];
    }
    else
    {
        return monster.skills[3];
    }
}
char gameoverChoice()
{
    char ch, temp;
    do
    {
        printf("1. Reload from the beginning of the stage\n");
        printf("2. Stop\n");
        printf("Your choice:\n");
        ch = getchar();
        scanf("%c", &temp); //Consume a \n character. Press enter an extra time if no input
        if (ch == '1' || ch == '2')
        {
            return ch;
        }
    } while (ch != '1' && ch != '2');
    return '0';
}
char stageoverChoice()
{
    char ch, temp;
    do
    {
        printf("1. Continue\n");
        printf("2. Stop\n");
        printf("Your choice:\n");
        ch = getchar();
        scanf("%c", &temp); //Consume a \n character. Press enter an extra time if no input
        if (ch == '1' || ch == '2')
        {
            return ch;
        }
    } while (ch != '1' && ch != '2');
    return '0';
}
// UTILITY FUNCTIONS
void printUserLog(char user[], char skill[], int dmg, Type type)
{
    switch (type)
    {
    case T_HEAL:
        printf(YEL "%s" RESET " uses " WHT "%s" RESET "\n", user, skill);
        printf(YEL "%s" RESET " heals for %d hp\n", user, dmg);
        break;
    case T_WATER:
        printf(YEL "%s" RESET " uses " BLU "%s" RESET "\n", user, skill);
        printf(YEL "%s" RESET " deals %d\n", user, dmg);
        break;
    case T_FIRE:
        printf(YEL "%s" RESET " uses " RED "%s" RESET "\n", user, skill);
        printf(YEL "%s" RESET " deals %d\n", user, dmg);
        break;
    case T_GRASS:
        printf(YEL "%s" RESET " uses " GRN "%s" RESET "\n", user, skill);
        printf(YEL "%s" RESET " deals %d\n", user, dmg);
        break;
    default:
        printf(YEL "%s" RESET " uses " CYN "%s" RESET "\n", user, skill);
        printf(YEL "%s" RESET " deals %d\n", user, dmg);
        break;
    }
}
void printMonsterLog(char user[], char skill[], int dmg, Type type)
{
    switch (type)
    {
    case T_HEAL:
        printf(MAG "%s" RESET " uses " WHT "%s" RESET "\n", user, skill);
        printf(MAG "%s" RESET " heals for %d hp\n", user, dmg);
        break;
    default:
        printf(MAG "%s" RESET " uses " CYN "%s" RESET "\n", user, skill);
        printf(MAG "%s" RESET " deals %d\n", user, dmg);
        break;
    }
}
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
void storeUserInfo(UserNode *head)
{
    UserNode *cur = NULL;
    FILE *f;
    if (head == NULL)
        return;
    cur = head;
    f = fopen("userinfo.txt", "w");
    while (cur != NULL)
    {
        fprintf(f, "%s %s %d %d %d %d %d\n", cur->user.username, cur->user.password, cur->user.level, cur->user.curExp, cur->user.curHP, cur->user.curMP, cur->user.stage);
        cur = cur->next;
    }
    fclose(f);
}
UserNode *makeNewNode(UserInfo data)
{
    UserNode *new = (UserNode *)malloc(sizeof(UserNode));
    new->user = data;
    new->next = NULL;
    return new;
}
UserNode *insertNode(UserNode *root, UserNode *new)
{
    UserNode *cur = NULL;
    if (root == NULL)
        return new;
    cur = root;
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = new;
    return root;
}
void freeList(UserNode *root)
{
    UserNode *tmp = NULL;
    while (root != NULL)
    {
        tmp = root;
        root = root->next;
        free(tmp);
    }
}
