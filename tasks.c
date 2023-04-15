#include "tasks.h"
#include "queue.h"
#include "stive.h"
#include "tree.h"

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

TeamList *task3(TeamList **teamList, char *fileNameOutput) {
    TeamList *last8Finalists = NULL;
    int roundNumber = 0;    // contor runda
    int numberOfTeams;      // contor numar echipe pentru a ne opri cand ajungem la echipa castigatoare
    
    // creare coada cu echipe
    Queue *matchQueue = NULL;
    fillQueueWithMatches(&matchQueue, *teamList);
   
    StackNode *winnersStack = NULL;

    do {
        // afisare numarul rundei
        writeRoundTitleInFile(++roundNumber, fileNameOutput);

        // afisare meciuri intre echipe
        writeRoundMatchesInFile(matchQueue, fileNameOutput);

        // creare stive
        StackNode *losersStack = NULL;
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

    deleteQueue(matchQueue);
    deleteStack(&winnersStack);

    return last8Finalists;
}

TeamList *task4(TeamList *last8Finalists, char *fileNameOutput) {
    BSTNode *root = NULL;
    while(last8Finalists != NULL) {
        root = BST_insert(root, last8Finalists->team);
        last8Finalists = last8Finalists->next;
    }

    // titlu
    FILE *file = fopen(fileNameOutput, "at");
    if(file) {
        fprintf(file, "\nTOP 8 TEAMS:\n");
        fclose(file);
    }
    TeamList *last8FinalistsDescending = NULL;
    BST_DRS(&last8FinalistsDescending, root, fileNameOutput);
    return last8FinalistsDescending;
}

void task5(TeamList *last8finalistsDescending, char *fileNameOutput) {
    AVLNode *root = NULL;
    while(last8finalistsDescending != NULL) {
        root = AVL_insert(root, last8finalistsDescending->team);
        last8finalistsDescending = last8finalistsDescending->next;
    }
    
    FILE *file = fopen(fileNameOutput, "at");
    if(file) {
        fprintf(file, "\nTHE LEVEL 2 TEAMS ARE:\n");
        fclose(file);
    }
    int level = -1;
    AVL_DRS(root, fileNameOutput, level);
        // problema la egalitate


        // todo vazut inaltimea de unde se numara
}
