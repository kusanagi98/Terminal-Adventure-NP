#include "helper.h"

/**
 * @brief Format highscore message
 * 
 * @param String username
 * @param int user current stage
 * 
 * @return String with Format: "username : stage"
 * */
char *userHighScoreFormat(char *username, int stage)
{
    char *result;
    char temp[MAX_STAGE_IN_STRING];
    result = (char*)calloc(strlen(username) + 4 + MAX_STAGE_IN_STRING, sizeof(char));

    strcpy(result, username);
    strcat(result, " : ");
    sprintf(temp, "%d", stage);
    strcat(result, temp);

    return result;
}