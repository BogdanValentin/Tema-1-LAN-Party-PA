#pragma once

#include "list.h"

/*  Reads the number of teams in "numberOfTeams"
    from the file pointed to by the FILE pointer "file".*/
void readNumberOfTeams(FILE *file, int *numberOfTeams);

/*  Reads the number of players in a team in "numberOfPlayersInTeam"
    from the file pointed to by the FILE pointer "file".*/
void readNumberOfPlayersInTeam(FILE *file, int *numberOfPlayersInTeam);

/*  Reads the name of a team in the "newTeam" struct
    from the file pointed to by the FILE pointer "file".*/
void readTeamName(FILE *file, Team **newTeam);

/*  Reads the name of a player in the "newPlayer" struct
    from the file pointed to by the FILE pointer "file".*/
void readNamesOfPlayer(FILE *file, Player **newPlayer);

/*  Reads the points of a player in the "newPlayer" struct
    from the file pointed to by the FILE pointer "file".*/
void readPointsOfPlayer(FILE *file, Player **newPlayer);

/*  Reads the players in the "playerList" list
    from the file pointed to by the FILE pointer "file".*/
void readPlayers(FILE *file, PlayerList **playerList, int numberOfPlayersInTeam);
