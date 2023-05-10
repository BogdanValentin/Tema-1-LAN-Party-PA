#include "../headers/read.h"

void readNumberOfTeams(FILE *file, int *numberOfTeams) {
    fscanf(file, "%d", numberOfTeams);
}

void readNumberOfPlayersInTeam(FILE *file, int *numberOfPlayersInTeam) {
    fscanf(file, "%d", numberOfPlayersInTeam);
}

void readTeamName(FILE *file, Team **newTeam) {
    char teamName[100];
    
    /*  Probabil de unde folosesc WSL newline-ul este \r\n (ca pe WIN)
        in loc de \n (ca pe LINUX). Asa ca sunt nevoit sa citesc pana la \r
        si dupa sa mai citesc 2 caractere (\r\n). Merg multe combinatii pentru
        a scapa de aceste 2 caractere (am vazut ca fscanf mai si ignora unele
        dintre ele) dar nu vreau sa mai pierd timp depanand asta. Cert e ca merge
        asa pe LINUX.*/

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
    char firstName[100];
    fscanf(file, "%s", firstName);
    (*newPlayer)->firstName = malloc((strlen(firstName) + 1) * sizeof(char));
    if ((*newPlayer)->firstName == NULL) {
		mallocError();
	}
    strcpy((*newPlayer)->firstName, firstName);

    char secondName[100];
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