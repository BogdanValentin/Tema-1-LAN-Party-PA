#include "../headers/read.h"

void readNumberOfTeams(FILE *file, int *numberOfTeams) {
    fscanf(file, "%d", numberOfTeams);
}

void readNumberOfPlayersInTeam(FILE *file, int *numberOfPlayersInTeam) {
    fscanf(file, "%d", numberOfPlayersInTeam);
}

void readTeamName(FILE *file, Team **newTeam) {
    char teamName[BUFFER_SIZE];

    if (fgets(teamName, sizeof(teamName), file) != NULL) {
        int len = strlen(teamName);
        while (len > 0 && (teamName[len - 1] == '\r' || teamName[len - 1] == '\n' || teamName[len - 1] == ' ')) {
            teamName[len - 1] = '\0';
            len--;
        }
        
        *newTeam = malloc(sizeof(Team));
        if (*newTeam == NULL) {
            mallocError();
        }
        (*newTeam)->name = malloc((strlen(teamName) + 1) * sizeof(char));
        if ((*newTeam)->name == NULL) {
            mallocError();
        }
        strcpy((*newTeam)->name, teamName);
    } else {
        printf("Eroare la citirea numelui echipei\n");
    }
}

void readNamesOfPlayer(FILE *file, Player **newPlayer) {
    char firstName[BUFFER_SIZE];
    fscanf(file, "%s", firstName);
    (*newPlayer)->firstName = malloc((strlen(firstName) + 1) * sizeof(char));
    if ((*newPlayer)->firstName == NULL) {
		mallocError();
	}
    strcpy((*newPlayer)->firstName, firstName);

    char secondName[BUFFER_SIZE];
    fscanf(file, "%s", secondName);
    (*newPlayer)->secondName = malloc((strlen(secondName) + 1) * sizeof(char));
    if ((*newPlayer)->secondName == NULL) {
		mallocError();
	}
    strcpy((*newPlayer)->secondName, secondName);
}

void readPointsOfPlayer(FILE *file, Player **newPlayer) {
    int points;
    fscanf(file, "%d", &points);
    (*newPlayer)->points = points;
}

void readPlayers(FILE *file, PlayerList **playerList, int numberOfPlayersInTeam) {
    for(int i = 0; i < numberOfPlayersInTeam; i++) {
        Player *newPlayer = malloc(sizeof(Player));
        if (newPlayer == NULL) {
		    mallocError();
	    }
        readNamesOfPlayer(file, &newPlayer);
        readPointsOfPlayer(file, &newPlayer);
        addPlayerToPlayerList(playerList, newPlayer);
    }
}
