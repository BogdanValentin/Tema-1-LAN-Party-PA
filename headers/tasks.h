#pragma once

#include <math.h>

#include "list.h"
#include "calculate.h"
#include "read.h"
#include "write.h"
#include "customFunctions.h"
#include "queue.h"
#include "stive.h"
#include "tree.h"
#include "error_handling.h"

#define NUMBER_OF_FINALISTS 8

// Responsible for handling task 1.
void task1(TeamList **teamList, int *numberOfTeams, char *fileNameInput, char *fileNameOutput);

// Responsible for handling task 2.
void task2(TeamList **teamList, int *numberOfTeams, char *fileNameOutput);

// Responsible for handling task 3.
void task3(TeamList **teamList, TeamList **last8Finalists, char *fileNameOutput);

// Responsible for handling task 4.
void task4(TeamList *last8Finalists, TeamList **last8FinalistsDescending, char *fileNameOutput);

// Responsible for handling task 5.
void task5(TeamList *last8finalistsDescending, char *fileNameOutput);