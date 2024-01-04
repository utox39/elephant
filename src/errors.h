#include <stdio.h>

#ifndef ERRORS_H
#define ERRORS_H

#define TOO_MANY_ARGS_ERROR 300
#define TOO_FEW_ARGS_ERROR 301
#define UNKNOWN_COMMAND_ERROR 302
#define TODO_ID_NOT_FOUND_ERROR 303

void print_error(int errno);

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
        case TODO_ID_NOT_FOUND_ERROR:
            printf("elephant: todo_id not found.\n");
            break;
        default:
            break;
    }
}

#endif
