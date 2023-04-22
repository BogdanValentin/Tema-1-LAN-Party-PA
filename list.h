#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error_handling.h"

/*  Struct used to store a player's info */
typedef struct Player {
    char *firstName;
    char *secondName;
    int points;
} Player;

/*  Struct used to store a list of players' info */
typedef struct PlayerList {
    Player *player;
    struct PlayerList *next;
} PlayerList;

/*  Struct used to store a team's info */
typedef struct Team {
    char *name;
    PlayerList *players;
} Team;

/*  Struct used to store a list of teams info */
typedef struct TeamList {
    Team *team;
    struct TeamList *next;
} TeamList;

/*  Struct used to store the 2 teams comprising a match */
typedef struct Match {
    Team *firstTeam, *secondTeam;
} Match;

/*  Adds the "player" Player to the "playerList" list. */
void addPlayerToPlayerList(PlayerList **playerList, Player *player);

/*  Adds the "playerList" list to the "team" Team. */
void addPlayerListToTeam(Team **team, PlayerList *playerList);

/*  Frees the memory allocated for the "playerList" list
    including every player's info. */
void freePlayerList(PlayerList **playerList);

/*  Adds the "team" Team to the end of "teamList" list. */
void addTeamToEndOfTeamList(TeamList **teamList, Team *team);

/*  Adds the "team" Team to the beginning of the "teamList" list. */
void addTeamToBeginningOfTeamList(TeamList **teamList, Team *team);

/*  Performs a deep copy of the "team" Team and adds it to the
    "teamList" list */
void addTeamCopyToTeamList(TeamList **teamList, Team *team);

/*  Frees the memory allocated for the "teamList" list
    including every team's info. */
void freeTeamList(TeamList **teamList);

/*  Frees the memory allocated for the "team" Team */
void freeTeam(Team **team);

/*  Deletes the team pointed to by "teamToEliminate" from
    the "teamList" list and frees it's memory */
void deleteTeam(TeamList **teamList, TeamList *teamToEliminate);
