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

void task3(TeamList **teamList, char *fileNameOutput) {
    int flag = 0;
    int roundNumber = 0;
    int numberOfMatches;
    Queue *matchQueue;
    
    do {
        
        // creare coada
        if(flag == 0) {
            matchQueue = createQueue();
            TeamList *teamListCopy = *teamList;
            while(teamListCopy != NULL && teamListCopy->next != NULL) {
                Match *newMatch = malloc(sizeof(Match));

                newMatch->firstTeam = teamListCopy->team;
                newMatch->secondTeam = teamListCopy->next->team;

                enQueue(matchQueue, newMatch);

                teamListCopy = teamListCopy->next->next;
            }
            flag = 1;
        }
        
        // print queue
        writeRoundTitleInFile(++roundNumber, fileNameOutput);

        // TODO afisare coada
        QueueNode *current = matchQueue->front;
        while(current != NULL) {
            writeMatchInFile(current->val, fileNameOutput);
            current = current->next;
        }

        // creare stive
        StackNode *losersStack = NULL;
        StackNode *winnersStack = NULL;
        while(isQueueEmpty(matchQueue) == 0) {
            Match *currentMatch = deQueue(matchQueue);

            // calcul puncte prima echipa
            float mean1 = findTeamScore(currentMatch->firstTeam);
            
            // calcul puncte a doua echipa
            float mean2 = findTeamScore(currentMatch->secondTeam);
            
            if(mean1 > mean2) {
                push(&winnersStack, currentMatch->firstTeam);

                push(&losersStack, currentMatch->secondTeam);
            } else {
                push(&losersStack, currentMatch->firstTeam);

                push(&winnersStack, currentMatch->secondTeam);
            }
        }

        // adaugare un punct fiecarui player 
        StackNode *winnersStackCopy = winnersStack;
        while(winnersStackCopy != NULL) {
            PlayerList *currentPos = winnersStackCopy->val->players;
            while(currentPos != NULL) {
                currentPos->player->points++;
                currentPos = currentPos->next;
            }
            winnersStackCopy = winnersStackCopy->next;
        }

        deleteStack(&losersStack);

        

        writeWinnersTitleInFile(roundNumber, fileNameOutput);

        // TODO afisare stiva
        StackNode *stackCopy = winnersStack;
        FILE *file = fopen(fileNameOutput, "at");
        if(file != NULL) {
            functiebelea(stackCopy, file);
            fclose(file);
        }


        numberOfMatches = 0;
        while(isStackEmpty(winnersStack) == 0) {
            numberOfMatches++;
            Match *newMatch = malloc(sizeof(Match));
            Team *aux1 = pop(&winnersStack);
            newMatch->firstTeam = aux1;
            if(isStackEmpty(winnersStack) == 0) {
                numberOfMatches++;
                Team *aux2 = pop(&winnersStack);
                newMatch->secondTeam = aux2;
            }
            enQueue(matchQueue, newMatch);
        }
        
    } while(numberOfMatches > 1);
}