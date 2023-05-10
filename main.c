#include "list.h"
#include "tasks.h"
#include "error_handling.h"

#define NUMBEROFTASKS 5

int main(int argc, char *argv[])
{
    TeamList *teamList = NULL;
    TeamList *last8Finalists = NULL;
    TeamList *last8FinalistsDescending = NULL;
    int numberOfTeams = 0;

    FILE *fileTasks = fopen(argv[1], "rt");
    if(fileTasks == NULL) {
        fileError(argv[1]);
    } else {
        int tasks[5];

        for(int i = 0; i < NUMBEROFTASKS; i++) {
            fscanf(fileTasks, "%d", &tasks[i]);
        }

        fclose(fileTasks);

        if(tasks[0] == 1) {
            task1(&teamList, &numberOfTeams, argv[2], argv[3]);
        }
        if(tasks[1] == 1) {
            task2(&teamList, &numberOfTeams, argv[3]);
        }
        if(tasks[2] == 1) {
            task3(&teamList, &last8Finalists, argv[3]);
            freeTeamList(&teamList);
        }
        if(tasks[3] == 1) {
            task4(last8Finalists, &last8FinalistsDescending, argv[3]);
        }
        if(tasks[4] == 1) {
            task5(last8FinalistsDescending, argv[3]);
            freeTeamList(&last8FinalistsDescending);
        }
    }
    return 0;
}
