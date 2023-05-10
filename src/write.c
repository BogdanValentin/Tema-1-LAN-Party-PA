#include "../headers/write.h"

void writeWinnerInFile(Team *team, char *fileName) {
    FILE *file = fopen(fileName, "at");
    if(file != NULL) {
        fprintf(file, "%-35s-  %.2f\n", team->name, findTeamScore(team));
        fclose(file);
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

void writeRoundMatchesInFile(Queue *queue, char *fileNameOutput) {
	QueueNode *current = queue->front;
	while(current != NULL) {
		writeMatchInFile(current->val, fileNameOutput);
		current = current->next;
	}
}

void writeWinnerAndPoints(StackNode *stackCopy, FILE *file) {
    fprintf(file, "%-34s-  %.2f\n", stackCopy->val->name, findTeamScore(stackCopy->val));
    if(stackCopy->next != NULL) {
        writeWinnerAndPoints(stackCopy->next, file);
    }
}

void writeWinnersInFile(StackNode *winnersstack, char *fileNameOutput) {
    FILE *file = fopen(fileNameOutput, "at");
    if(file != NULL) {
        writeWinnerAndPoints(winnersstack, file);
        fclose(file);
    }
}
