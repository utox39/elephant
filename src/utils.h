#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

#ifndef UTILS_H
#define UTILS_H

#define ID_SIZE 5

void check_args(int expected_args_num, int actual_args_num);

void check_file_exists(const FILE *file_ptr, const char *filename);

void generate_random_ID(char random_id[]);

unsigned int generate_random_number(void);

void check_args(int expected_args_num, int actual_args_num) {
    if (actual_args_num < expected_args_num) {
        print_error(TOO_FEW_ARGS_ERROR);
        printf("usage: elephant [COMMAND] [VALUE]\n");
        exit(EXIT_FAILURE);
    } else if (actual_args_num > expected_args_num) {
        print_error(TOO_MANY_ARGS_ERROR);
        printf("usage: elephant [COMMAND] [VALUE]\n");
        exit(EXIT_FAILURE);
    }

}

void check_file_exists(const FILE *file_ptr, const char *filename) {
    if (file_ptr == NULL) {
        printf("elephant: %s not found.\n", filename);
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

#endif
