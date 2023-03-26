#pragma once

#include "list.h"

void readNumberOfTeams(FILE *file, int *numberOfTeams);
void readNumberOfPlayersInTeam(FILE *file, int *numberOfPlayersInTeam);
void readTeamName(FILE *file, Team **newTeam);
void readNamesOfPlayer(FILE *file, Player **newPlayer);
void readPointsOfPlayer(FILE *file, Player **newPlayer);
void readPlayers(FILE *file, PlayerList **playerList, int numberOfPlayersInTeam);
