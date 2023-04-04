#include "queue.h"
#include "stive.h"
#include "calculate.h"

void writeWinnerInFile(Team *team, char *fileName);
void writeRoundTitleInFile(int roundNumber, char *fileName);
void writeWinnersTitleInFile(int roundNumber, char *fileName);
void writeMatchInFile(Match *match, char *fileName);
void writeTeamNamesInFile(TeamList *teamList, char *fileName);
void writeRoundMatchesInFile(Queue *queue, char *fileNameOutput);
void writeWinnerAndPoints(StackNode *stackCopy, FILE *file);
void writeWinnersInFile(StackNode *winnersstack, char *fileNameOutput);
