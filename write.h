#pragma once

#include "queue.h"
#include "stive.h"
#include "calculate.h"

/*  Writes the winner's team name and score to the specified file.*/
void writeWinnerInFile(Team *team, char *fileName);

/*  Writes the round title to the specified file.*/
void writeRoundTitleInFile(int roundNumber, char *fileName);

/*  Writes the winners' title for a specific round to the specified file.*/
void writeWinnersTitleInFile(int roundNumber, char *fileName);

/*  Writes a match with team names to the specified file.*/
void writeMatchInFile(Match *match, char *fileName);

/*  Writes a list of team names to the specified file.*/
void writeTeamNamesInFile(TeamList *teamList, char *fileName);

/*  Writes all matches in a queue to the specified file.*/
void writeRoundMatchesInFile(Queue *queue, char *fileNameOutput);

/*  Writes the winner's team name and points to the specified file.*/
void writeWinnerAndPoints(StackNode *stackCopy, FILE *file);

/*  Writes the winners' information from a stack to the specified file.*/
void writeWinnersInFile(StackNode *winnersstack, char *fileNameOutput);
