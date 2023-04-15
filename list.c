#include "list.h"

void addPlayerToPlayerList(PlayerList **playerList, Player *player) {
    if (*playerList == NULL) {
        *playerList = malloc(sizeof(PlayerList));
        (*playerList)->player = player;
        (*playerList)->next = NULL;
    } else {
        PlayerList *playerListCopy = *playerList;
        while (playerListCopy->next != NULL) {
            playerListCopy = playerListCopy->next;
        }
        playerListCopy->next = malloc(sizeof(PlayerList));
        playerListCopy->next->player = player;
        playerListCopy->next->next = NULL;
    }
}

void addPlayerListToTeam(Team **team, PlayerList *playerList) {
    (*team)->players = playerList;
}

void addTeamToTeamList(TeamList **teamList, Team *team) {
    TeamList *newNode = malloc(sizeof(TeamList));
    newNode->team = team;
    newNode->next = *teamList;
    *teamList = newNode;
}

void addTeamToBeginningTeamList(TeamList **teamList, Team *team) {
    TeamList *newNode = malloc(sizeof(TeamList));
    newNode->team = team;
    newNode->next = NULL;
    if (*teamList == NULL) {
        *teamList = newNode;
    } else {
        TeamList *teamListCopy = *teamList;
        while (teamListCopy->next != NULL) {
            teamListCopy = teamListCopy->next;
        }
        teamListCopy->next = newNode;
    }
}

void addTeamCopyToTeamList(TeamList **teamList, Team *team) { // deep copy
    Team *newTeam = malloc(sizeof(Team));

    newTeam->name = malloc(strlen(team->name) + 1);
    strcpy(newTeam->name, team->name);

    newTeam->players = NULL;

    PlayerList *currentPlayer = team->players;
    while (currentPlayer != NULL) {
        Player *newPlayer = malloc(sizeof(Player));
        newPlayer->firstName = malloc(strlen(currentPlayer->player->firstName) + 1);
        strcpy(newPlayer->firstName, currentPlayer->player->firstName);

        newPlayer->secondName = malloc(strlen(currentPlayer->player->secondName) + 1);
        strcpy(newPlayer->secondName, currentPlayer->player->secondName);

        newPlayer->points = currentPlayer->player->points;

        PlayerList *newPlayersList = malloc(sizeof(PlayerList));
        newPlayersList->player = newPlayer;
        newPlayersList->next = newTeam->players;
        newTeam->players = newPlayersList;

        currentPlayer = currentPlayer->next;
    }

    addTeamToTeamList(teamList, newTeam);
}

void deletePlayerList(PlayerList **playerList) {
    if(*playerList != NULL) {
        PlayerList *next = (*playerList)->next;
        free((*playerList)->player->firstName);
        free((*playerList)->player->secondName);
        free(*playerList);
        *playerList = NULL;
        deletePlayerList(&next);
    }
}

void deleteTeamList(TeamList **teamList) {
    if(*teamList != NULL) {
        TeamList *next = (*teamList)->next;
        free((*teamList)->team->name);
        deletePlayerList(&(*teamList)->team->players);
        free(*teamList);
        *teamList = NULL;
        deleteTeamList(&next);
    }
}

void eliminateTeam(TeamList **teamList, TeamList *teamToEliminate) {
    if (*teamList == NULL || teamToEliminate == NULL) {
        return;
    }
    // First node
    if (teamToEliminate == *teamList) {
        *teamList = (*teamList)->next;
        free(teamToEliminate);
    } else { // Rest of the nodes
        TeamList *current = *teamList;
        while(current->next != NULL) {
            if(current->next == teamToEliminate) {
                current->next = current->next->next;
                break;
            }
            current = current->next;
        }
        free(teamToEliminate);
    }
}
