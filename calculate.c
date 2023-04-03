#include "calculate.h"

int findMaxPowOf2(int number) {
    int power = 0;
    while(pow(2, power) <= number) {
        power++;
    }
    
    power--;
    return power;
}

void findTeamToEliminate(TeamList **teamList, TeamList **teamToEliminate) {
    // TODO refactor code
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
