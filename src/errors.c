#include <stdio.h>

#include "errors.h"

void print_error(int errno) {
    switch (errno) {
        case TOO_MANY_ARGS_ERROR:
            printf("elephant: too many arguments.\n");
            break;
        case TOO_FEW_ARGS_ERROR:
            printf("elephant: too few arguments.\n");
            break;
        case UNKNOWN_COMMAND_ERROR:
            printf("elephant: unknown command.\n");
            break;
        case TODO_TXT_FILE_NOT_FOUND_ERROR:
            printf("elephant: todo.txt file not found.\n");
            break;
        case TODO_ID_NOT_FOUND_ERROR:
            printf("elephant: todo_id not found.\n");
            break;
        default:
            break;
    }
}
