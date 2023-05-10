#pragma once

#include "stive.h"
#include "queue.h"
#include "calculate.h"
#include "error_handling.h"

/*  Processes a queue of matches, separating the teams into winners and losers
    stacks based on their team scores. This function also frees the memory of
    the dequeued match.*/
void createWinnerLosersStacks(Queue *matchQueue, StackNode **winnersStack, StackNode **losersStack);

/*  Recursively traverses the input queue and adds the teams from each match
    to a TeamList, creating a copy of each team in the process.*/
void storeLast8Finalists(TeamList **last8Finalists, QueueNode *q);

/*  Fills a given queue with matches created from a provided team list.
    It creates matches by pairing adjacent teams in the team list.*/
void fillQueueWithMatches(Queue **matchQueue, TeamList *teamList);

/*  Adds one point to every player in each team in a given stack of winners.*/
void addOnePointToEveryPlayerFromStack(StackNode *winnersStack);

/*  Refills a given match queue with matches created from a stack of winning
    teams. It creates matches by pairing adjacent teams popped from the
    winners stack.*/
void refillQueueWithMatches(Queue *matchQueue, StackNode **winnersStack, int *numberOfTeams);
