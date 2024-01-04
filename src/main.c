#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"
#include "errors.h"
#include "helper.h"

#define BUFFER_SIZE 1024
#define ADD_EXPECTED_ARGS_NUMBER 3
#define RM_EXPECTED_ARGS_NUMBER 3
#define LIST_EXPECTED_ARGS_NUMBER 2

void handler(int argc, const char **arg);

int find_todo(FILE *todo, const char *todo_id);

void write_todo(const char *content);

void delete_todo(const char *todo_id);

void print_todo_list(void);


char *todo_path = NULL;


int main(int argc, const char **argv) {
    // Get user home directory via environment variable
    const char *home = getenv("HOME");

    unsigned long todo_path_len = strlen(home) + strlen("/.todo.txt");

    // task file path
    todo_path = (char *) malloc(todo_path_len * sizeof(char));
    if (todo_path == NULL) {
        fprintf(stderr, "Allocation for todo_path failed.\n");
        exit(EXIT_FAILURE);
    }
    strncpy(todo_path, home, strlen(home));
    strncat(todo_path, "/.todo.txt", todo_path_len);

    // Handle command line arguments
    handler(argc, argv);

    free(todo_path);

    return 0;
}

void handler(int argc, const char **arg) {
    // Handle command line arguments
    if (!strcmp(arg[1], "add")) {
        check_args(ADD_EXPECTED_ARGS_NUMBER, argc);
        write_todo(arg[2]);
    } else if (!strcmp(arg[1], "rm")) {
        check_args(RM_EXPECTED_ARGS_NUMBER, argc);
        delete_todo(arg[2]);
    } else if (!strcmp(arg[1], "list")) {
        check_args(LIST_EXPECTED_ARGS_NUMBER, argc);
        print_todo_list();
    } else if (!strcmp(arg[1], "help")) {
        help();
    } else {
        print_error(UNKNOWN_COMMAND_ERROR);
        exit(EXIT_FAILURE);
    }
}

void write_todo(const char *content) {
    FILE *todo = NULL;
    todo = fopen(todo_path, "a");
    check_file_exists(todo, todo_path);
    if (content) {
        char random_id[ID_SIZE];
        // Generate a random for the new task
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
    int todo_line;
    int line_count = 0;
    unsigned long tmp_filepath_len = strlen("/.temp.tmp") + strlen(home);

    // tmp file path
    tmp_filepath = (char *) malloc(tmp_filepath_len * sizeof(char));
    strncpy(tmp_filepath, home, strlen(home));
    strncat(tmp_filepath, "/.temp.tmp", tmp_filepath_len);
    if (tmp_filepath == NULL) {
        printf("elephant: ~/.temp.tmp not created\n");
        exit(EXIT_FAILURE);
    }

    todo = fopen(todo_path, "r");
    check_file_exists(todo, todo_path);

    // Find the line number of the task to be deleted
    todo_line = find_todo(todo, todo_id);
    fclose(todo);

    if (todo_line == 0) {
        print_error(TODO_ID_NOT_FOUND_ERROR);
        exit(EXIT_FAILURE);
    }

    // Create a temporary file where tasks are rewritten without the one to be deleted
    tmp_file = fopen(tmp_filepath, "w");
    check_file_exists(tmp_file, tmp_filepath);

    todo = fopen(todo_path, "r");
    check_file_exists(todo, todo_path);

    while ((fgets(buffer, BUFFER_SIZE, todo)) != NULL) {
        line_count++;

        // If line count matches the task line to delete, it replaces that line with an empty string
        if (line_count == todo_line) {
            fputs("", tmp_file);
        } else {
            fputs(buffer, tmp_file);
        }
    }

    fclose(todo);
    fclose(tmp_file);

    // Delete original file
    remove(todo_path);

    // Rename temporary file as original file
    rename(tmp_filepath, todo_path);

    printf("%s successfully deleted\n", todo_id);

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

void print_todo_list(void) {
    FILE *todo = NULL;
    char buffer[BUFFER_SIZE];

    todo = fopen(todo_path, "r");
    check_file_exists(todo, todo_path);

    // Print the task list
    printf("TODO:\n");
    printf("ID  |Task Description\n");
    printf("----------------------\n");
    while (fgets(buffer, sizeof(buffer), todo)) {
        printf("%s", buffer);
    }

    fclose(todo);
}
