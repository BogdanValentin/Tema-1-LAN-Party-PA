#include "error_handling.h"

void mallocError() {
    printf("Error: malloc failed");
    exit(1);
}

void fileError(char *fileName) {
    printf("Error: file \"%s\" could not be opened", fileName);
    exit(1);
}