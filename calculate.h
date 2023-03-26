#pragma once

#include <math.h>

#include "list.h"

#define FLOAT_MAX 3.402823466e+38F

int findMaxPowOf2(int number);
void findTeamToEliminate(TeamList **teamList, TeamList **teamToEliminate);
