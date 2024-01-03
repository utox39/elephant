#include <stdio.h>

void help();

void help() {
    printf("usage: elephant [COMMAND] [VALUE]\n\n"
           "Task Manager Program: an elephant never forgets\n\n"
           "commands:\n"
           "  add \"Task description\"\t"
           "Add a new task with the provided description to the to-do list.\n\n"
           "  rm TASK_ID\t\t\t"
           "Remove the task with the specified ID from the to-do list.\n\n"
           "  list\t\t\t\t"
           "Display the current tasks in the to-do list.\n\n"
           "  help\t\t\t\t"
           "Display this help message.\n\n"
           "examples:\n"
           "  elephant add \"Buy groceries\"\n"
           "  elephant rm TASK_ID\n"
           "  elephant list\n"
    );
}
