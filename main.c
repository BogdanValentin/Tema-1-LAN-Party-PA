// TODO valgrind intrebat de free-urile alea
// TODO error handling for all malocs

#include "list.h"
#include "tasks.h"

#define NUMBEROFTASKS 5

int main(int argc, char *argv[])
//  ./lanParty c.in d.in r.out
{
    TeamList *teamList = NULL;
    int numberOfTeams = 0;

    FILE *fileTasks = fopen(argv[1], "rt");
    if(fileTasks != NULL) {
        int tasks[5];

        // TODO REFACTOR FUNCTIE
        for(int i = 0; i < NUMBEROFTASKS; i++) {
            fscanf(fileTasks, "%d", &tasks[i]);
        }

        fclose(fileTasks);

        if(tasks[0] == 1) {    
            numberOfTeams = task1(&teamList, argv[2], argv[3]);
        }
        if(tasks[1] == 1) {
            task2(&teamList, &numberOfTeams, argv[3]);
        }
        if(tasks[2] == 1) {
            //task3();
        }
        if(tasks[3] == 1) {
            //task4();
        }
        if(tasks[4] == 1) {
            //task5();
        }
    }
    deleteTeamList(&teamList);
    return 0;
}