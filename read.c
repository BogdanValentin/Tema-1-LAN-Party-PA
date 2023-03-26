#include "read.h"

void readNumberOfTeams(FILE *file, int *numberOfTeams) {
    fscanf(file, "%d", numberOfTeams);
}

void readNumberOfPlayersInTeam(FILE *file, int *numberOfPlayersInTeam) {
    fscanf(file, "%d", numberOfPlayersInTeam);
}

void readTeamName(FILE *file, Team **newTeam) {
    char teamName[100];
    /*
        Long rant: 
        Probabil de unde folosesc WSL newline-ul este \r\n (ca pe WIN)
        in loc de \n (ca pe LINUX). Asa ca sunt nevoit sa citesc pana la \r
        si dupa sa mai citesc 2 caractere (\r\n). Merg multe combinatii pentru
        a scapa de aceste 2 caractere (am vazut ca fscanf mai si ingnora unele
        dintre ele) dar vreau sa mai pierd timp depanand asta. Cert e ca merge
        asa pe LINUX.
    */
    fscanf(file, "%99[^\r]", teamName);
    fgetc(file);
    fgetc(file); 
    *newTeam = malloc(sizeof(Team));
    (*newTeam)->name = malloc((strlen(teamName) + 1) * sizeof(char));
    strcpy((*newTeam)->name, teamName);
}

void readNamesOfPlayer(FILE *file, Player **newPlayer) {
    // citire primul nume player
    char firstName[100];
    fscanf(file, "%s", firstName);
    (*newPlayer)->firstName = malloc((strlen(firstName) + 1) * sizeof(char));
    strcpy((*newPlayer)->firstName, firstName);

    // citire al doilea nume player
    char secondName[100];
    fscanf(file, "%s", secondName);
    (*newPlayer)->secondName = malloc((strlen(secondName) + 1) * sizeof(char));
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
        readNamesOfPlayer(file, &newPlayer);
        readPointsOfPlayer(file, &newPlayer);
        addPlayerToPlayerList(playerList, newPlayer);
    }
}
