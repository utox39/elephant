#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

#define ID_SIZE 5
#define NUMBER_OF_ARGS 3

void check_args(int argc);

void check_file_exists(const FILE *todo);

void generate_random_ID(char random_id[]);

unsigned int generate_random_number(void);

void check_args(int argc) {
    if (argc < NUMBER_OF_ARGS) {
        print_error(TOO_FEW_ARGS_ERROR);
        //TODO: create help_function
        exit(EXIT_FAILURE);
    } else if (argc > NUMBER_OF_ARGS) {
        print_error(TOO_MANY_ARGS_ERROR);
        //TODO: create help_function
        exit(EXIT_FAILURE);
    }
}

// TODO: add file name as formal argument
void check_file_exists(const FILE *todo) {
    if (todo == NULL) {
        print_error(TODO_TXT_FILE_NOT_FOUND_ERROR);
        exit(EXIT_FAILURE);
    }
}

unsigned int generate_random_number(void) {
    unsigned int random_data;
    int urandom = open("/dev/urandom", O_RDONLY);
    if (urandom == -1) {
        perror("Error opening /dev/urandom\n");
        exit(EXIT_FAILURE);
    }

    if (read(urandom, &random_data, sizeof(random_data)) != sizeof(random_data)) {
        perror("Error reading /dev/urandom\n");
        close(urandom);
        exit(EXIT_FAILURE);
    }

    close(urandom);
    return random_data % 100;
}

void generate_random_ID(char random_id[]) {
    const char char_set[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const int charset_size = sizeof(char_set) - 1;

    for (int i = 0; i < ID_SIZE - 1; i++) {
        random_id[i] = char_set[generate_random_number() % charset_size];
    }

    random_id[ID_SIZE - 1] = '\0';
}
