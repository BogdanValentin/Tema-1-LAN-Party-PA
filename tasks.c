#include "tasks.h"
#include "queue.h"
#include "stive.h"

int  task1(TeamList **teamList, char *fileNameInput, char *fileNameOutput) {
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

TeamList *task3(TeamList **teamList, char *fileNameOutput) {
    TeamList *last8Finalists = NULL;
    int roundNumber = 0;    // contor runda
    int numberOfTeams;      // contor numar echipe pentru a ne opri cand ajungem la echipa castigatoare
    
    // creare coada cu echipe
    Queue *matchQueue = NULL;
    fillQueueWithMatches(&matchQueue, *teamList);

    do {
        // afisare numarul rundei
        writeRoundTitleInFile(++roundNumber, fileNameOutput);

        // afisare meciuri intre echipe
        writeRoundMatchesInFile(matchQueue, fileNameOutput);

        // creare stive
        StackNode *losersStack = NULL;
        StackNode *winnersStack = NULL;
        createWinnerLosersStacks(matchQueue, &winnersStack, &losersStack);
        
        // adaugare un punct fiecarui player 
        addOnePointToEveryPlayerFromStack(winnersStack);

        // stergere stiva pierzatori
        deleteStack(&losersStack);

        // afisare titlu castigatori
        writeWinnersTitleInFile(roundNumber, fileNameOutput);

        // afisare castigatori
        writeWinnersInFile(winnersStack, fileNameOutput);

        // refacere coada meciuri din stiva de castigatori
        refillQueueWithMatches(matchQueue, &winnersStack, &numberOfTeams);

        // stocare ultimele 8 echipe
        if(numberOfTeams == 8) {
            storeLast8Finalists(&last8Finalists, matchQueue->front);
        }
        
    } while(numberOfTeams > 1); // pana cand avem un castigator

    return last8Finalists;
}
