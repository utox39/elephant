#ifndef UTILS_H
#define UTILS_H

#define ID_SIZE 5

void check_args(int expected_args_num, int actual_args_num);

void check_file_exists(const FILE *file_ptr, const char *filename);

void generate_random_ID(char random_id[]);

#endif
