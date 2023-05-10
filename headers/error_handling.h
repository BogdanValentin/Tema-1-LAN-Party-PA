#pragma once

#include <stdlib.h>
#include <stdio.h>

/*  Handles memory allocation failure by printing an error message and
    terminating the program. */
void mallocError();

/*  Handles file opening failure by printing an error message and
    terminating the program. */
void fileError(char *fileName);
