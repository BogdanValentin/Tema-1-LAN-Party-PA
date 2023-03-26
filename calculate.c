#include "calculate.h"

int findMaxPowOf2(int number) {
    int power = 0;
    while(pow(2, power) < number) {
        power++;
    }
    power--;
    return power;
}

void findTeamToEliminate(TeamList **teamList, TeamList **teamToEliminate) {
    // TODO refactor code
    float lowestScore = FLOAT_MAX;
    TeamList *currentTeamList = *teamList, *prevTeam = *teamList;
    int flag = 0;
    while(currentTeamList != NULL) {
        if(flag > 1) {
            prevTeam = prevTeam->next;
        }
        flag++;
        int numberOfPointsPerTeam = 0, numberOfPlayersInTeam = 0;
        PlayerList *currentPlayerList = currentTeamList->team->players;
        while(currentPlayerList != NULL) {
            numberOfPlayersInTeam++;
            numberOfPointsPerTeam += currentPlayerList->player->points;
            currentPlayerList = currentPlayerList->next;
        }
        float mean = (float) numberOfPointsPerTeam / numberOfPlayersInTeam;
        if(lowestScore > mean) {
            lowestScore = mean;
            *teamToEliminate = prevTeam;
        }
        currentTeamList = currentTeamList->next;
    }
}
