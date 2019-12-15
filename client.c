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

//int userCurHP, userCurMP, userCurLevel, userCurExp, userCurStage, monsterCurHP, monsterCurMP, curDmg;
//SkillInfo monsterSkill;
char ch;   //options
char temp; //temp for consuming \n
//UserInfo tmp;          //temp for storing info from input file
UserNode *root = NULL; //linked list root

int main()
{
    // TODO: Move user linked list to server
    root = loadUserInfo();
    loadLevelInfo();
    loadMonsterInfo();
    loadStageInfo();
    // printf("%d\n", monsters[1].type);
    // if (monsters[1].type == T_NORMAL)
    //     printf("true\n");
    // stages[0].number = 5;
    // for (i = 0; i < stages[0].number; i++)
    // {
    //     stages[0].monsters[i] = monsters[0];
    // }
    // stages[1].number = 5;
    // for (i = 0; i < stages[1].number; i++)
    // {
    //     stages[1].monsters[i] = monsters[1];
    // }
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
            campaign();
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
