#pragma once

#include "list.h"

#define BUFFER_SIZE 100

/*  Reads the number of teams from a file.*/
void readNumberOfTeams(FILE *file, int *numberOfTeams);

/*  Reads the number of players in a team from a file.*/
void readNumberOfPlayersInTeam(FILE *file, int *numberOfPlayersInTeam);

/*  Reads the name of a team from a file.*/
void readTeamName(FILE *file, Team **newTeam);

/*  Reads the name of a player from a file.*/
void readNamesOfPlayer(FILE *file, Player **newPlayer);

/*  Reads the points of a player from a file.*/
void readPointsOfPlayer(FILE *file, Player **newPlayer);

/*  Reads the players from a file.*/
void readPlayers(FILE *file, PlayerList **playerList, int numberOfPlayersInTeam);
