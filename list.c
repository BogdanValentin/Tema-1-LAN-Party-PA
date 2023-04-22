#include "list.h"

void addPlayerToPlayerList(PlayerList **playerList, Player *player) {
    if (*playerList == NULL) {
        *playerList = malloc(sizeof(PlayerList));
        if(*playerList == NULL) {
            mallocError();
        }
        (*playerList)->player = player;
        (*playerList)->next = NULL;
    } else {
        PlayerList *playerListCopy = *playerList;
        while (playerListCopy->next != NULL) {
            playerListCopy = playerListCopy->next;
        }
        playerListCopy->next = malloc(sizeof(PlayerList));
        if(playerListCopy->next == NULL) {
            mallocError();
        }
        playerListCopy->next->player = player;
        playerListCopy->next->next = NULL;
    }
}

void addPlayerListToTeam(Team **team, PlayerList *playerList) {
    (*team)->players = playerList;
}

void addTeamToEndOfTeamList(TeamList **teamList, Team *team) {
    TeamList *newNode = malloc(sizeof(TeamList));
    if(newNode == NULL) {
        mallocError();
    }
    newNode->team = team;
    newNode->next = *teamList;
    *teamList = newNode;
}

void addTeamToBeginningOfTeamList(TeamList **teamList, Team *team) {
    TeamList *newNode = malloc(sizeof(TeamList));
    if(newNode == NULL) {
        mallocError();
    }
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

void addTeamCopyToTeamList(TeamList **teamList, Team *team) {
    Team *newTeam = malloc(sizeof(Team));
    if(newTeam == NULL) {
        mallocError();
    }

    newTeam->name = malloc(strlen(team->name) + 1);
    if(newTeam->name == NULL) {
        mallocError();
    }
    strcpy(newTeam->name, team->name);

    newTeam->players = NULL;

    PlayerList *currentPlayer = team->players;
    while (currentPlayer != NULL) {
        Player *newPlayer = malloc(sizeof(Player));
        if(newPlayer == NULL) {
            mallocError();
        }
        newPlayer->firstName = malloc(strlen(currentPlayer->player->firstName) + 1);
        if(newPlayer->firstName == NULL) {
            mallocError();
        }
        strcpy(newPlayer->firstName, currentPlayer->player->firstName);

        newPlayer->secondName = malloc(strlen(currentPlayer->player->secondName) + 1);
        if(newPlayer->secondName == NULL) {
            mallocError();
        }
        strcpy(newPlayer->secondName, currentPlayer->player->secondName);

        newPlayer->points = currentPlayer->player->points;

        PlayerList *newPlayersList = malloc(sizeof(PlayerList));
        if(newPlayersList == NULL) {
            mallocError();
        }
        newPlayersList->player = newPlayer;
        newPlayersList->next = newTeam->players;
        newTeam->players = newPlayersList;

        currentPlayer = currentPlayer->next;
    }

    addTeamToEndOfTeamList(teamList, newTeam);
}

void freePlayerList(PlayerList **playerList) {
    if(*playerList != NULL) {
        PlayerList *next = (*playerList)->next;
        free((*playerList)->player->firstName);
        free((*playerList)->player->secondName);
        free((*playerList)->player);
        free(*playerList);
        *playerList = NULL;
        freePlayerList(&next);
    }
}

void freeTeamList(TeamList **teamList) {
    if(*teamList != NULL) {
        TeamList *next = (*teamList)->next;
        free((*teamList)->team->name);
        freePlayerList(&(*teamList)->team->players);
        free(*teamList);
        *teamList = NULL;
        freeTeamList(&next);
    }
}

void freeTeam(Team **team) {
    free((*team)->name);
    freePlayerList(&(*team)->players);
    free(*team);
}

void deleteTeam(TeamList **teamList, TeamList *teamToEliminate) {
    if (*teamList == NULL || teamToEliminate == NULL) {
        return;
    }
    // First node
    if (teamToEliminate == *teamList) {
        *teamList = (*teamList)->next;
    } else { // Rest of the nodes
        TeamList *current = *teamList;
        while(current->next != NULL) {
            if(current->next == teamToEliminate) {
                current->next = current->next->next;
                break;
            }
            current = current->next;
        }
    }
    freeTeam(&teamToEliminate->team);
    free(teamToEliminate);
}
