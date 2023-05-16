#include "../headers/tasks.h"

void task1(TeamList **teamList, int *numberOfTeams, char *fileNameInput, char *fileNameOutput) {
    FILE *fileDate = fopen(fileNameInput, "rt");
    if(fileDate != NULL) {
        readNumberOfTeams(fileDate, numberOfTeams);

        // citire date fiecare echipa
        for(int i = 0; i < *numberOfTeams; i++) {
            int numberOfPlayersInTeam;
            readNumberOfPlayersInTeam(fileDate, &numberOfPlayersInTeam);

            fgetc(fileDate); // citire spatiu intre numar playeri si nume echipa

            Team *newTeam = NULL;
            readTeamName(fileDate, &newTeam);

            PlayerList *playerList = NULL;
            readPlayers(fileDate, &playerList, numberOfPlayersInTeam);
            
            fgetc(fileDate); // citire randul liber intre echipe

            addPlayerListToTeam(&newTeam, playerList);

            addTeamToEndOfTeamList(teamList, newTeam);
        }
        fclose(fileDate);
    } else {
        fileError(fileNameInput);
    }
    writeTeamNamesInFile(*teamList, fileNameOutput);
}

void task2(TeamList **teamList, int *numberOfTeams, char *fileNameOutput) {
    int wantedNumberOfTeams = pow(2, findMaxPowOf2(*numberOfTeams));
    
    while(*numberOfTeams > wantedNumberOfTeams) {
        TeamList *teamToEliminate = NULL;
        findTeamToEliminate(teamList, &teamToEliminate);
        deleteTeam(teamList, teamToEliminate);
        (*numberOfTeams)--;
    }
    writeTeamNamesInFile(*teamList, fileNameOutput);
}

void task3(TeamList **teamList, TeamList **last8Finalists, char *fileNameOutput) {
    int roundNumber = 0;    // contor runda
    int numberOfTeams;      // contor numar echipe pentru a ne opri cand ajungem la echipa castigatoare
    
    // creare coada cu echipe
    Queue *matchQueue = NULL;
    fillQueueWithMatches(&matchQueue, *teamList);
   
    StackNode *winnersStack = NULL;

    do {
        writeRoundTitleInFile(++roundNumber, fileNameOutput);

        writeRoundMatchesInFile(matchQueue, fileNameOutput);

        StackNode *losersStack = NULL;
        createWinnerLosersStacks(matchQueue, &winnersStack, &losersStack);
        
        addOnePointToEveryPlayerFromStack(winnersStack);

        deleteStack(&losersStack);

        writeWinnersTitleInFile(roundNumber, fileNameOutput);

        writeWinnersInFile(winnersStack, fileNameOutput);

        refillQueueWithMatches(matchQueue, &winnersStack, &numberOfTeams);

        if(numberOfTeams == NUMBER_OF_FINALISTS) {
            storeLast8Finalists(last8Finalists, matchQueue->front);
        }
        
    } while(numberOfTeams > 1);

    deleteQueue(matchQueue);
    deleteStack(&winnersStack);
}

void task4(TeamList *last8Finalists, TeamList **last8FinalistsDescending, char *fileNameOutput) {
    BSTNode *root = NULL;
    createBSTTree(&root, last8Finalists);

    FILE *file = fopen(fileNameOutput, "at");
    if(file) {
        fprintf(file, "\nTOP 8 TEAMS:\n");
        fclose(file);
    }

    BST_DRS(last8FinalistsDescending, root, fileNameOutput);
    deleteBSTTree(root);
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
    deleteAVLTree(root);
}
