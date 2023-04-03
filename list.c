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

void writeTeamNamesInFile(TeamList *teamList, char *fileName) {
    FILE *file = fopen(fileName, "wt");
    if(file != NULL) {
        while(teamList != NULL) {
            fprintf(file, "%s\n", teamList->team->name);
            teamList = teamList->next;
        }
        fclose(file);
    }
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

void writeRoundTitleInFile(int roundNumber, char *fileName) {
    FILE *file = fopen(fileName, "at");
    if(file != NULL) {
        fprintf(file, "\n--- ROUND NO:%d\n", roundNumber);
        fclose(file);
    }
}

void writeWinnersTitleInFile(int roundNumber, char *fileName) {
    FILE *file = fopen(fileName, "at");
    if(file != NULL) {
        fprintf(file, "\nWINNERS OF ROUND NO:%d\n", roundNumber);
        fclose(file);
    }
}

void writeMatchInFile(Match *match, char *fileName) {
    FILE *file = fopen(fileName, "at");
    if(file != NULL) {
        fprintf(file, "%-33s-%33s\n", match->firstTeam->name, match->secondTeam->name);
        fclose(file);
    }
}

float findTeamScore(Team *team) {
    int points = 0, numberOfPlayers = 0;
    PlayerList *currentPlayerList = team->players;
    while(currentPlayerList != NULL) {
        numberOfPlayers++;
        points += currentPlayerList->player->points;
        currentPlayerList = currentPlayerList->next;
    }
    float mean = (float) points / numberOfPlayers;
    return mean;
}

void writeWinnerInFile(Team *team, char *fileName) {
    FILE *file = fopen(fileName, "at");
    if(file != NULL) {
        fprintf(file, "%-35s-  %.2f\n", team->name, findTeamScore(team));
        fclose(file);
    }
}




