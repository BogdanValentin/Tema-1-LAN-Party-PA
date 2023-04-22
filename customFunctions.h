#include "stive.h"
#include "queue.h"
#include "calculate.h"
#include "error_handling.h"

void createWinnerLosersStacks(Queue *matchQueue, StackNode **winnersStack, StackNode **losersStack);
void storeLast8Finalists(TeamList **last8Finalists, QueueNode *q);
void fillQueueWithMatches(Queue **matchQueue, TeamList *teamList);
void addOnePointToEveryPlayerFromStack(StackNode *winnersStack);
void refillQueueWithMatches(Queue *matchQueue, StackNode **winnersStack, int *numberOfTeams);
