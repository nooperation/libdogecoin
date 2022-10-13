#ifndef __LIBDOGECOIN_GETOPTIONS_H__
#define __LIBDOGECOIN_GETOPTIONS_H__

#include <stdbool.h>
#include <stddef.h>

typedef struct program_option {
    char shortcut;
    const char* name;
    bool requires_argument;
} program_option;

char get_argument(char* argv[], int argc, int* current_argv_index, const program_option* options, size_t num_options, char** option_argument);

#endif
