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
#include "client.h"
// TODO: Separate files and add makefile
SkillInfo skills[SKILL_COUNT] = {
    {S_EMBER, "Ember", 20, 5, T_FIRE},
    {S_VINEWHIP, "Vine Whip", 20, 5, T_GRASS},
    {S_WATERGUN, "Water Gun", 20, 5, T_WATER},
    {S_HEADBUTT, "Headbutt", 30, 7, T_NORMAL},
    {S_SLASH, "Slash", 35, 8, T_NORMAL},
    {S_FLAMEWHEEL, "Flame Wheel", 30, 10, T_FIRE},
    {S_MAGICALLEAF, "Magical Leaf", 30, 10, T_GRASS},
    {S_WATERPULSE, "Water Pulse", 30, 10, T_WATER},
    {S_FLAMETHROWER, "FlameThrower", 35, 15, T_FIRE},
    {S_LEAFBLADE, "Leaf Blade", 35, 15, T_GRASS},
    {S_SURF, "Surf", 35, 15, T_WATER},
    {S_MEGAPUNCH, "Mega Punch", 40, 15, T_NORMAL},
    {S_FIREBLAST, "Fire Blast", 40, 20, T_FIRE},
    {S_SOLARBEAM, "Solar Beam", 40, 20, T_GRASS},
    {S_HYDROPUMP, "Hydro Pump", 40, 20, T_WATER},
    {S_MEGAKICK, "Mega Kick", 45, 20, T_NORMAL},
    {S_BLASTBURN, "Blast Burn", 45, 25, T_FIRE},
    {S_FRENZYPLANT, "Frenzy Plant", 45, 25, T_GRASS},
    {S_HYDROCANNON, "Hydro Cannon", 45, 25, T_WATER},
    {S_HYPERBEAM, "Hyper Beam", 45, 25, T_NORMAL},
    {ES_TACKLE, "Tackle", 10, 0, T_NORMAL},
    {ES_ACID, "Acid", 15, 0, T_NORMAL},
    {ES_SLUDGEBOMB, "Sludge Bomb", 20, 0, T_NORMAL},
    {ES_GUNKSHOT, "Gunk Shot", 25, 0, T_NORMAL},
    {ES_SCRATCH, "Scratch", 10, 0, T_NORMAL},
    {ES_THRUST, "Thrust", 15, 0, T_NORMAL},
    {ES_POTION, "Potion", 5, 0, T_HEAL},
    {ES_GOBLINPUNCH, "Goblin Punch", 25, 0, T_NORMAL},
    {S_NORMALATTACK, "Normal Attack", 10, 0, T_NORMAL}};
LevelInfo levels[MAX_LEVEL];
MonsterInfo monsters[2];
StageInfo stages[2];
FILE *f;
int i, j, skill_num, type_num, k;
int x;
int userCurHP, userCurMP, userCurLevel, userCurExp, userCurStage, monsterCurHP, monsterCurMP, curDmg;
SkillInfo monsterSkill;
char ch, ch1, ch2;     //options
char temp;             //temp for consuming \n
UserInfo tmp;          //temp for storing info from input file
UserNode *root = NULL; //linked list root
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
UserNode *makeNewNode(UserInfo data)
{
    UserNode *new = (UserNode *)malloc(sizeof(UserNode));
    new->user = data;
    new->next = NULL;
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
int main()
{
    // TODO: Move user linked list to server
    f = fopen("userinfo.txt", "r");
    if (f == NULL)
    {
        printf("Error: Can\'t read input file!\n");
        return -1;
    }
    while (fscanf(f, "%s", tmp.username) != EOF)
    {
        ch = fgetc(f);
        fscanf(f, "%s", tmp.password);
        ch = fgetc(f);
        fscanf(f, "%d", &tmp.level);
        ch = fgetc(f);
        fscanf(f, "%d", &tmp.curExp);
        ch = fgetc(f);
        fscanf(f, "%d", &tmp.curHP);
        ch = fgetc(f);
        fscanf(f, "%d", &tmp.curMP);
        ch = fgetc(f);
        fscanf(f, "%d", &tmp.stage);
        root = insertNode(root, makeNewNode(tmp));
    }
    fclose(f);
    f = fopen("levelinfo.txt", "r");
    if (f == NULL)
    {
        printf("Error: Can\'t read input file!\n");
        return -1;
    }
    for (i = 0; i < MAX_LEVEL; i++)
    {
        fscanf(f, "%d", &levels[i].level);
        ch = fgetc(f);
        fscanf(f, "%d", &levels[i].hp);
        ch = fgetc(f);
        fscanf(f, "%d", &levels[i].mp);
        ch = fgetc(f);
        fscanf(f, "%d", &levels[i].atk);
        ch = fgetc(f);
        fscanf(f, "%d", &levels[i].def);
        ch = fgetc(f);
        fscanf(f, "%d", &levels[i].maxexp);
        ch = fgetc(f);
        fscanf(f, "%d", &levels[i].count);
        for (j = 0; j < levels[i].count; j++)
        {
            ch = fgetc(f);
            fscanf(f, "%d", &skill_num);
            levels[i].skills[j] = skills[skill_num];
        }
    }
    fclose(f);
    //printf("%d\n", levels[2].level);
    f = fopen("monsterinfo.txt", "r");
    if (f == NULL)
    {
        printf("Error: Can\'t read input file!\n");
        return -1;
    }
    for (i = 0; i < 2; i++)
    {
        fscanf(f, "%s", monsters[i].name);
        ch = fgetc(f);
        fscanf(f, "%d", &monsters[i].hp);
        ch = fgetc(f);
        fscanf(f, "%d", &monsters[i].mp);
        ch = fgetc(f);
        fscanf(f, "%d", &monsters[i].atk);
        ch = fgetc(f);
        fscanf(f, "%d", &monsters[i].def);
        ch = fgetc(f);
        fscanf(f, "%d", &monsters[i].exp);
        ch = fgetc(f);
        fscanf(f, "%d", &type_num);
        monsters[i].type = type_num;
        for (j = 0; j < 4; j++)
        {
            ch = fgetc(f);
            fscanf(f, "%d", &skill_num);
            monsters[i].skills[j] = skills[skill_num];
        }
    }
    fclose(f);
    printf("%d\n", monsters[1].type);
    if (monsters[1].type == T_NORMAL)
        printf("true\n");
    stages[0].number = 5;
    for (i = 0; i < stages[0].number; i++)
    {
        stages[0].monsters[i] = monsters[0];
    }
    stages[1].number = 5;
    for (i = 0; i < stages[1].number; i++)
    {
        stages[1].monsters[i] = monsters[1];
    }
    while (1)
    {
        printf("\nTERMINAL ADVENTURE DEMO");
        printf("\n--------------------------------");
        printf("\n1. Play");
        // TODO: Create profile and login
        // printf("\n2. Sign in");
        // printf("\n3. Search");
        // printf("\n4. Sign out");
        printf("\nYour choice(1, other to quit):");
        ch = getchar();
        scanf("%c", &temp); //Consume a \n character. Press enter an extra time if no input
        if (ch == '1')
        {
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
            for (i = userCurStage; i < 2; i++)
            {
                printf("Stage %d\n", i);
                printf("--------------------------------\n");
                // Go through all the monsters
                for (j = 0; j < stages[i].number; j++)
                {
                    printf("A wild %s appears\n", stages[i].monsters[j].name);
                    printf("--------------------------------\n");
                    monsterCurHP = stages[i].monsters[j].hp;
                    monsterCurMP = stages[i].monsters[j].mp;
                    while (1)
                    {
                        printf("%s\t%s\n", root->user.username, stages[i].monsters[j].name);
                        printf("HP:%d\tHP:%d\n", userCurHP, monsterCurHP);
                        printf("MP:%d\tMP:%d\n", userCurMP, monsterCurMP);
                        printf("--------------------------------\n");
                        // User command
                        do
                        {
                            printf("1. Normal Attack\n");
                            printf("2. Skills\n");
                            printf("Your choice:\n");
                            ch1 = getchar();
                            scanf("%c", &temp); //Consume a \n character. Press enter an extra time if no input
                            if (ch1 == '1')
                            {
                                // Normal Attack
                                curDmg = damageCalculationPlayer(skills[SKILL_COUNT - 1], levels[userCurLevel - 1], stages[i].monsters[j]);
                                monsterCurHP -= curDmg;
                                printf("%s uses Normal Attack\n", root->user.username);
                                printf("%s deals %d\n", root->user.username, curDmg);
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
                                            printf("%s uses %s\n", root->user.username, levels[userCurLevel - 1].skills[x - 1].name);
                                            printf("%s heals for %d hp\n", root->user.username, curDmg);
                                        }
                                        else
                                        {
                                            curDmg = damageCalculationPlayer(levels[userCurLevel - 1].skills[x - 1], levels[userCurLevel - 1], stages[i].monsters[j]);
                                            monsterCurHP -= curDmg;
                                            userCurMP -= levels[userCurLevel - 1].skills[x - 1].mpcost;
                                            printf("%s uses %s\n", root->user.username, levels[userCurLevel - 1].skills[x - 1].name);
                                            printf("%s deals %d damage\n", root->user.username, curDmg);
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
                                printf("%s uses %s\n", stages[i].monsters[j].name, monsterSkill.name);
                                printf("%s heals for %d hp\n", stages[i].monsters[j].name, curDmg);
                            }
                            else
                            {
                                curDmg = damageCalculationMonster(monsterSkill, levels[userCurLevel - 1], stages[i].monsters[j]);
                                userCurHP -= curDmg;
                                printf("%s uses %s\n", stages[i].monsters[j].name, monsterSkill.name);
                                printf("%s deals %d damage\n", stages[i].monsters[j].name, curDmg);
                                if (userCurHP <= 0)
                                {
                                    // TODO: Allow player to reload the savefile or reload from the start of the stage
                                    exit(1);
                                }
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                    printf("--------------------------------\n");
                    printf("%s defeated %s\n", root->user.username, stages[i].monsters[j].name);
                    if (userCurLevel < MAX_LEVEL)
                    {
                        printf("%s gained %d EXP\n", root->user.username, stages[i].monsters[j].exp);
                        userCurExp += stages[i].monsters[j].exp;
                        if (userCurExp >= levels[userCurLevel - 1].maxexp)
                        {
                            userCurLevel += 1;
                            userCurHP = levels[userCurLevel - 1].hp;
                            userCurMP = levels[userCurLevel - 1].mp;
                            userCurExp = 0;
                            printf("%s grew to Level %d \n", root->user.username, userCurLevel);
                        }
                    }
                    printf("--------------------------------\n");
                }
                // TODO: Add menu for save, continue or stop playing
                printf("--------------------------------\n");
                printf("%s beat stage %d\n", root->user.username, i);
                printf("--------------------------------\n");
                userCurStage += 1;
            }
            printf("Congrats you beat the game\n");
            //signinUser(root, argv[1]);
            //scanf("%c",&temp);
        }
        // else if(ch=='2') {
        //   signinUser(root, argv[1]);
        //   scanf("%c",&temp);
        // }
        // else if(ch=='3') {
        //   searchUser(root);
        //   scanf("%c",&temp);
        // }
        // else if(ch=='4') {
        //   signoutUser(root);
        //   scanf("%c",&temp);
        // }
        else
        {
            freeList(root);
            break;
        }
    }
}