#pragma once

#include <math.h>

#include "list.h"

#define FLOAT_MAX 3.402823466e+38F

/*  Returnes the max power of 2 that is less than or equal to a given number.*/
int findMaxPowOf2(int number);

/*  Finds the team with the lowest mean score in a team list and sets a pointer
    to point to that team.*/
void findTeamToEliminate(TeamList **teamList, TeamList **teamToEliminate);

/*  Calculates the mean score of a given team.*/
float findTeamScore(Team *team);
