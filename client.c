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
int i, j, skill_num, count, type_num;
int userCurHP, userCurMP, userCurLevel, userCurExp, userCurStage, monsterCurHP, monsterCurMP, curDmg;
SkillInfo monsterSkill;
char ch, ch1;          //options
char temp;             //temp for consuming \n
UserInfo tmp;          //temp for storing info from input file
UserNode *root = NULL; //linked list root
int damageCalculationPlayer(SkillInfo skill, LevelInfo player, MonsterInfo monster)
{
    return player.atk * skill.dmg / monster.def;
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
        fscanf(f, "%d", &count);
        for (j = 0; j < count; j++)
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
            userCurLevel = root->user.level;
            userCurHP = root->user.curHP;
            userCurMP = root->user.curMP;
            userCurExp = root->user.curExp;
            userCurStage = root->user.stage;
            for (i = userCurStage; i < 2; i++)
            {
                printf("Stage %d\n", i);
                for (j = 0; j < stages[i].number; j++)
                {
                    printf("A wild %s appears\n", stages[i].monsters[j].name);
                    monsterCurHP = stages[i].monsters[j].hp;
                    monsterCurMP = stages[i].monsters[j].mp;
                    while (1)
                    {
                        printf("%s\t%s\n", root->user.username, stages[i].monsters[j].name);
                        printf("HP:%d\tHP:%d\n", userCurHP, monsterCurHP);
                        printf("MP:%d\tMP:%d\n", userCurMP, monsterCurMP);
                        do
                        {
                            printf("1. Normal Attack\n");
                            printf("2. Skills\n");
                            printf("Your choice:\n");
                            ch1 = getchar();
                            //scanf("%c", &temp); //Consume a \n character. Press enter an extra time if no input
                            if (ch1 == '1')
                            {
                                curDmg = damageCalculationPlayer(skills[SKILL_COUNT - 1], levels[root->user.level - 1], stages[i].monsters[j]);
                                monsterCurHP -= curDmg;
                                printf("%s uses Normal Attack\n", root->user.username);
                                printf("%s deals %d\n", root->user.username, curDmg);
                            }
                            else if (ch1 == '2')
                            {
                            }
                            else
                            {
                                //continue;
                            }
                        } while (ch1 != '1');
                        if (monsterCurHP > 0)
                        {
                            monsterSkill = monsterAI(stages[i].monsters[j], monsterCurHP);
                            curDmg = damageCalculationMonster(monsterSkill, levels[root->user.level - 1], stages[i].monsters[j]);
                            userCurHP -= curDmg;
                            printf("%s uses %s\n", stages[i].monsters[j].name, monsterSkill.name);
                            printf("%s deals %d\n", stages[i].monsters[j].name, curDmg);
                            if (userCurHP <= 0)
                            {
                                exit(1);
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                    printf("%s defeated %s\n", root->user.username, stages[i].monsters[j].name);
                    if (userCurLevel < MAX_LEVEL)
                    {
                        printf("%s gained %d EXP\n", root->user.username, stages[i].monsters[j].exp);
                        userCurExp += stages[i].monsters[j].exp;
                        if (userCurExp >= levels[root->user.level - 1].maxexp)
                        {
                            userCurLevel += 1;
                            userCurHP = levels[root->user.level - 1].hp;
                            userCurMP = levels[root->user.level - 1].mp;
                            userCurExp = 0;
                        }
                    }
                }
                printf("%s beat stage %d\n", root->user.username, i);
                userCurStage += 1;
            }
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