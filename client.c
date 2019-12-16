#include <sys/types.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "struct/skill.h"
#include "struct/monster.h"
#include "struct/level.h"
#include "struct/stage.h"
#include "struct/user.h"
#include "game/game.h"
#include "helper/mysocket.h"
#include "interface/clientfunc.h"

#define BUFFER_LEN 1024
//int userCurHP, userCurMP, userCurLevel, userCurExp, userCurStage, monsterCurHP, monsterCurMP, curDmg;
//SkillInfo monsterSkill;
char ch;   //options
char temp; //temp for consuming \n
int loginStatus = 0;
//UserInfo tmp;          //temp for storing info from input file
UserInfo user; //store UserInfo
struct sockaddr_in servaddr;
int sockfd;

int main(int argc, char const *argv[])
{
    int port;

    /* config client */
    if (argc < 3)
        die("Must provide a port number.\nUsage: ./client <Server Address> <PORT Number>\n", 1);

    if (argc < 2)
        die("Must provide a server address.\nUsage: ./client <Server Address> <PORT Number>\n", 1);

    port = getPort(argv[2]);

    if (port == -1)
        die("Invalid port number.\n", 1);

    /* socket create and varification */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
        die("socket creation failed", 0);
    else
        printf("Socket successfully created..\n");

    /* reset server for config */
    bzero(&servaddr, sizeof(servaddr));
    servaddr = configAddress(argv[1], port);

    /* connect the client socket to server socket */
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
        die("connection failed", 0);
    else
        printf("connected to the server %s:%d\n", inet_ntoa(servaddr.sin_addr), servaddr.sin_port);

    // TODO: Move user linked list to server
    // root = loadUserInfo();
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
        printf("\n|---------------------------------------|");
        printf("\n|" RED "\tTERMINAL ADVENTURE DEMO\t\t" RESET "|");
        printf("\n|---------------------------------------|");
        // printf("\n1. Play");
        // TODO: Create profile and login
        printf("\n|---------------------------------------|");
        printf("\n|\t1. Sign in                      |");
        printf("\n|\t2. Register                     |");
        printf("\n|\t3. High score                   |");
        printf("\n|\t4. Sign out                     |");
        printf("\n|---------------------------------------|");
        printf("\nYour choice(1, other to quit):");
        ch = getchar();

        scanf("%c", &temp); //Consume a \n character. Press enter an extra time if no input
        if (ch == '1')
        {
            login(sockfd);
            playMenu(sockfd);
        }
        else if(ch == '2')
        {
            registerFunc(sockfd);
        }
        else if(ch=='3') {
          fetchHighScore(sockfd);
        }
        else if(ch=='4') {
            logout(sockfd);
        }
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
            // freeList(root);
            break;
        }
    }
}
