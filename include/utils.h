#ifndef UTILS_H
#define UTILS_H

#define fatal_error(err) fatal_error_func(err, __FILE__, __LINE__)

enum ERROR_TYPE_E {
    ERR_OUT_OF_BOUNDS,
    ERR_ILLEGAL_VALUE,
    ERR_DIVIDE_BY_ZERO,
};
/* Type of fatal error encountered during runtime */
typedef enum ERROR_TYPE_E ERROR_TYPE;

/**
 * @brief  Prints error message to terminal and exits program
 *
 * @param err Type of error encountered
 * @param fileName Name of the src file in which error occurred
 * @param line Line in file where error occurred
 *
 * @note Should be accessed mainly through fatal_error(err) macro
 */
void fatal_error_func(
    const ERROR_TYPE err, const char *fileName, const unsigned int line
);


#endif
