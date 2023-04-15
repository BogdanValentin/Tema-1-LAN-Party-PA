#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player {
    char *firstName;
    char *secondName;
    int points;
} Player;

typedef struct PlayerList {
    Player *player;
    struct PlayerList *next;
} PlayerList;

typedef struct Team {
    char *name;
    PlayerList *players;
} Team;

typedef struct TeamList {
    Team *team;
    struct TeamList *next;
} TeamList;

typedef struct Match {
    Team *firstTeam, *secondTeam;
} Match;

void addPlayerToPlayerList(PlayerList **playerList, Player *player);
void addPlayerListToTeam(Team **team, PlayerList *playerList);
void addTeamToTeamList(TeamList **teamList, Team *team);
void writeTeamNamesInFile(TeamList *teamList, char *fileName);
void deletePlayerList(PlayerList **playerList);
void deleteTeamList(TeamList **teamList);
void eliminateTeam(TeamList **teamList, TeamList *teamToEliminate);
void addTeamCopyToTeamList(TeamList **teamList, Team *team);

