//#include <stdio.h>
#include <stdlib.h>
#include "../include/utils.h"

NO_RETURN_FUNC
void fatal_error_func(
    const ERROR_TYPE err, const char *fileName, const unsigned int line
) {


    exit(EXIT_FAILURE);
}
