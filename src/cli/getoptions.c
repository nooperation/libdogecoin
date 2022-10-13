#include <dogecoin/getoptions.h>
#include <stddef.h>

char get_argument(char* argv[], int argc, int* current_argv_index, const program_option* options, size_t num_options, char** option_argument)
{
    if (argv == NULL || current_argv_index == NULL) {
        return 0;
    }

    // First argument is the path to the current running executable. useless to us
    if (*current_argv_index == 0) {
        (*current_argv_index)++;
    }

    if (*current_argv_index >= argc) {
        return 0;
    }

    const char* current_option = argv[*current_argv_index];
    if (current_option == NULL) {
        return 0;
    }

    // Argument must start with a single hyphen
    if (current_option[0] != '-') {
        return 0;
    }
    current_option++;

    // Argument may contain a second hyphen, indicating a long option
    if (current_option == '-') {
        current_option++;
    }

    // Argument must contain at least a single character
    if (current_option == '\0') {
        return 0;
    }

    for (size_t i = 0; i < num_options; i++) {
        if ((current_option[0] == options[i].shortcut && current_option[1] == '\0') || strcmp(current_option, options[i].name) == 0) {
            if (!options[i].requires_argument) {
                return options[i].shortcut;
            }

            if (*current_argv_index + 1 >= argc) {
                return 0;
            }

            if (option_argument == NULL) {
                return 0;
            }

            *option_argument = argv[*current_argv_index + 1];
            (*current_argv_index)++;
            return options[i].shortcut;
        }
    }
}
