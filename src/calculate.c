#include "../headers/calculate.h"

int findMaxPowOf2(int number) {
    int power = 0;
    while(pow(2, power) <= number) {
        power++;
    }
    power--;
    return power;
}

void findTeamToEliminate(TeamList **teamList, TeamList **teamToEliminate) {
    float lowestScore = FLOAT_MAX;
    TeamList *currentTeamList = *teamList;
    while(currentTeamList != NULL) {
        float mean = findTeamScore(currentTeamList->team);
        if(lowestScore > mean) {
            lowestScore = mean;
            *teamToEliminate = currentTeamList;
        }
        currentTeamList = currentTeamList->next;
    }
}

float findTeamScore(Team *team) {
    if(team != NULL) {
        int points = 0, numberOfPlayers = 0;
        PlayerList *currentPlayerList = team->players;
        while(currentPlayerList != NULL) {
            numberOfPlayers++;
            points += currentPlayerList->player->points;
            currentPlayerList = currentPlayerList->next;
        }
        float mean = (float) points / numberOfPlayers;
        return mean;
    } else {
        return -1;
    }
}
