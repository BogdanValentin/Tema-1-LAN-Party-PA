#include "../headers/customFunctions.h"

void createWinnerLosersStacks(Queue *matchQueue, StackNode **winnersStack, StackNode **losersStack) {
	while(isQueueEmpty(matchQueue) == 0) {
            Match *currentMatch = deQueue(matchQueue);

            float mean1 = findTeamScore(currentMatch->firstTeam);
            
            float mean2 = findTeamScore(currentMatch->secondTeam);
            
            if(mean1 > mean2) {
                push(winnersStack, currentMatch->firstTeam);
                push(losersStack, currentMatch->secondTeam);
            } else {
                push(losersStack, currentMatch->firstTeam);
                push(winnersStack, currentMatch->secondTeam);
            }
            free(currentMatch);
    }
}

void storeLast8Finalists(TeamList **last8Finalists, QueueNode *q) {
	addTeamCopyToTeamList(last8Finalists, q->val->firstTeam);
	addTeamCopyToTeamList(last8Finalists, q->val->secondTeam);
	if(q->next != NULL) {
		storeLast8Finalists(last8Finalists, q->next);
	}
}

void fillQueueWithMatches(Queue **matchQueue, TeamList *teamList) {
	*matchQueue = createQueue();
    while(teamList != NULL && teamList->next != NULL) {
        Match *newMatch = malloc(sizeof(Match));
        if(newMatch == NULL) {
            mallocError();
        }

        newMatch->firstTeam = teamList->team;
        newMatch->secondTeam = teamList->next->team;

        enQueue(*matchQueue, newMatch);

        teamList = teamList->next->next;
    }
}

void addOnePointToEveryPlayerFromStack(StackNode *winnersStack) {
    while(winnersStack != NULL) {
        PlayerList *currentPos = winnersStack->val->players;
        while(currentPos != NULL) {
            currentPos->player->points++;
            currentPos = currentPos->next;
        }
        winnersStack = winnersStack->next;
    }
}

void refillQueueWithMatches(Queue *matchQueue, StackNode **winnersStack, int *numberOfTeams) {
    *numberOfTeams = 0;
    while(isStackEmpty(*winnersStack) == 0) {
        (*numberOfTeams)++;
        Match *newMatch = malloc(sizeof(Match));
        if(newMatch == NULL) {
            mallocError();
        }
        Team *aux1 = pop(winnersStack);
        newMatch->firstTeam = aux1;
        if(isStackEmpty(*winnersStack) == 0) {
            (*numberOfTeams)++;
            Team *aux2 = pop(winnersStack);
            newMatch->secondTeam = aux2;
        }
        enQueue(matchQueue, newMatch);
    }
}
