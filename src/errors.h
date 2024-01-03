#include <stdio.h>

#define TOO_MANY_ARGS_ERROR 300
#define TOO_FEW_ARGS_ERROR 301
#define UNKNOWN_COMMAND_ERROR 302
#define TODO_TXT_FILE_NOT_FOUND_ERROR 303
#define TODO_ID_NOT_FOUND_ERROR 304

void print_error(int errno);
