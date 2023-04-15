#pragma once

#include <math.h>

#include "list.h"
#include "calculate.h"
#include "read.h"
#include "write.h"
#include "customFunctions.h"

int task1(TeamList **teamList, char *fileNameInput, char *fileNameOutput);
void task2(TeamList **teamList, int *numberOfTeams, char *fileNameOutput);
TeamList *task3(TeamList **teamList, char *fileNameOutput);
TeamList *task4(TeamList *last8Finalists, char *fileNameOutput);
void task5(TeamList *last8finalistsDescending, char *fileNameOutput);