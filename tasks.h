#pragma once

#include <math.h>

#include "list.h"
#include "calculate.h"
#include "read.h"

int task1(TeamList **teamList, char *fileNameInput, char *fileNameOutput);
void task2(TeamList **teamList, int *numberOfTeams, char *fileNameOutput);
TeamList *task3(TeamList **teamList, char *fileNameOutput);