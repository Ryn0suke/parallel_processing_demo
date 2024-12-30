#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include <stdio.h>
#include <stdlib.h>

char **allocate_2d_array(int rows, int cols);

void free_2d_array(char** array, int rows);

void set_a(char** array, int rows, int cols);

int count_a_num(char** array, int rows, int cols, int start, int end);

#endif
