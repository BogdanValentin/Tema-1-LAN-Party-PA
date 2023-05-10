#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error_handling.h"

/*  Struct used to store a player's info.*/
typedef struct Player {
    char *firstName;
    char *secondName;
    int points;
} Player;

/*  Struct used to store a list of players' info.*/
typedef struct PlayerList {
    Player *player;
    struct PlayerList *next;
} PlayerList;

/*  Struct used to store a team's info.*/
typedef struct Team {
    char *name;
    PlayerList *players;
} Team;

/*  Struct used to store a list of teams info.*/
typedef struct TeamList {
    Team *team;
    struct TeamList *next;
} TeamList;

/*  Struct used to store the 2 teams comprising a match.*/
typedef struct Match {
    Team *firstTeam, *secondTeam;
} Match;

/*  Adds a player to the end of a player list.*/
void addPlayerToPlayerList(PlayerList **playerList, Player *player);

/*  Adds a player list to a team.*/
void addPlayerListToTeam(Team **team, PlayerList *playerList);

/*  Adds a team to the end of a team list.*/
void addTeamToEndOfTeamList(TeamList **teamList, Team *team);

/*  Adds a team to the beginning of a team list.*/
void addTeamToBeginningOfTeamList(TeamList **teamList, Team *team);

/*  Performs a deep copy of a team and adds it to a team list.*/
void addTeamCopyToTeamList(TeamList **teamList, Team *team);

/*  Frees the allocated memory of a player list including every player's info.*/
void freePlayerList(PlayerList **playerList);

/*  Frees the allocated memory of a team list including every team's info.*/
void freeTeamList(TeamList **teamList);

/*  Frees the memory allocated for a team.*/
void freeTeam(Team **team);

/*  Deletes a team from a team list.*/
void deleteTeam(TeamList **teamList, TeamList *teamToEliminate);
