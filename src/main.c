#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"
#include "errors.h"

#define BUFFER_SIZE 1024

void handler(int argc, const char **arg);

int find_todo(FILE *todo, const char *todo_id);

void write_todo(const char *content);

void delete_todo(const char *todo_id);


char *todo_path = NULL;


int main(int argc, const char **argv) {
    const char *home = getenv("HOME");

    unsigned long todo_path_len = strlen(home) + strlen("/.todo.txt");

    todo_path = (char *) malloc(todo_path_len * sizeof(char));
    strncpy(todo_path, home, strlen(home));
    strncat(todo_path, "/.todo.txt", todo_path_len);

    handler(argc, argv);

    free(todo_path);

    return 0;
}

void handler(int argc, const char **arg) {
    check_args(argc);

    if (!strcmp(arg[1], "add")) {
        write_todo(arg[2]);
    } else if (!strcmp(arg[1], "rm")) {
        delete_todo(arg[2]);
    } else {
        print_error(UNKNOWN_COMMAND_ERROR);
        exit(EXIT_FAILURE);
    }
}

void write_todo(const char *content) {
    FILE *todo = NULL;
    todo = fopen(todo_path, "a");
    check_file_exists(todo);
    if (content) {
        char random_id[ID_SIZE];
        generate_random_ID(random_id);
        fprintf(todo, "%s: %s\n", random_id, content);
    }

    fclose(todo);
}

void delete_todo(const char *todo_id) {
    FILE *todo = NULL;
    FILE *tmp_file = NULL;
    char buffer[BUFFER_SIZE];

    const char *home = getenv("HOME");

    if (home == NULL) {
        fprintf(stderr, "Unable to get the home folder path\n");
        exit(EXIT_FAILURE);
    }

    char *tmp_filepath = NULL;
    int todo_line = 0;
    int line_count = 0;
    unsigned long tmp_filepath_len = strlen("/.temp.tmp") + strlen(home);

    tmp_filepath = (char *) malloc(tmp_filepath_len * sizeof(char));

    strncpy(tmp_filepath, home, strlen(home));
    strncat(tmp_filepath, "/.temp.tmp", tmp_filepath_len);

    if (tmp_filepath == NULL) {
        printf("elephant: ~/.temp.tmp not created\n");
        exit(EXIT_FAILURE);
    }

    todo = fopen(todo_path, "r");
    check_file_exists(todo);

    todo_line = find_todo(todo, todo_id);
    fclose(todo);
    if (todo_line == 0) {
        print_error(TODO_ID_NOT_FOUND_ERROR);
        exit(EXIT_FAILURE);
    }

    tmp_file = fopen(tmp_filepath, "w");
    if (tmp_file == NULL) {
        printf("elephant: %s not found\n", tmp_filepath);
        exit(EXIT_FAILURE);
    }

    todo = fopen(todo_path, "r");
    check_file_exists(todo);

    while ((fgets(buffer, BUFFER_SIZE, todo)) != NULL) {
        line_count++;

        if (line_count == todo_line) {
            fputs("", tmp_file);
        } else {
            fputs(buffer, tmp_file);
        }
    }

    fclose(todo);
    fclose(tmp_file);

    /* Delete original file */
    remove(todo_path);

    /* Rename temporary file as original file */
    rename(tmp_filepath, todo_path);

    printf("%s successfully deleted", todo_id);

    free(tmp_filepath);
}

int find_todo(FILE *todo, const char *todo_id) {
    int line_num = 0;
    char line[1024];

    while (fgets(line, sizeof(line), todo)) {
        line_num++;
        const char *position_in_line = strstr(line, todo_id);

        if (position_in_line != NULL) {
            return line_num;
        }
    }

    return 0;

}
