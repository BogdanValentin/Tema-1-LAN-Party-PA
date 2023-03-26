#include "tasks.h"

int task1(TeamList **teamList, char *fileNameInput, char *fileNameOutput) {
    FILE *fileDate = fopen(fileNameInput, "rt");
    int numberOfTeams;
    if(fileDate != NULL) {
        readNumberOfTeams(fileDate, &numberOfTeams);

        // citire date fiecare echipa
        for(int i = 0; i < numberOfTeams; i++) {
            // TODO refactor for-ul
            int numberOfPlayersInTeam;
            readNumberOfPlayersInTeam(fileDate, &numberOfPlayersInTeam);

            fgetc(fileDate); // citire spatiu intre numar playeri si nume echipa

            Team *newTeam = NULL;
            readTeamName(fileDate, &newTeam);

            PlayerList *playerList = NULL;
            readPlayers(fileDate, &playerList, numberOfPlayersInTeam);
            
            fgetc(fileDate); // citire randul liber intre echipe

            addPlayerListToTeam(&newTeam, playerList);

            addTeamToTeamList(teamList, newTeam);
        }
        fclose(fileDate);
    }
    writeTeamNamesInFile(*teamList, fileNameOutput);
    return numberOfTeams;
}

void task2(TeamList **teamList, int *numberOfTeams, char *fileNameOutput) {
    int wantedNumberOfTeams = pow(2, findMaxPowOf2(*numberOfTeams));
    
    while(*numberOfTeams > wantedNumberOfTeams) {
        TeamList *teamToEliminate = NULL;
        findTeamToEliminate(teamList, &teamToEliminate);
        eliminateTeam(teamList, teamToEliminate);
        (*numberOfTeams)--;
    }
    writeTeamNamesInFile(*teamList, fileNameOutput);
}