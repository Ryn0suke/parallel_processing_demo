#include "utils.h"

char **allocate_2d_array(int rows, int cols) {
    char **array = malloc(rows * sizeof(char*));

    if(!array) {
        perror("Faild to allocate memory for rows");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < rows; i++) {
        array[i] = malloc(cols * sizeof(char));
        if(!array[i]) {
            perror("Failed to allocate memory for columns");
            exit(EXIT_FAILURE);
        }
    }

    return array;
}

void free_2d_array(char** array, int rows) {
    for(int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}

void set_a(char** array, int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            array[i][j] = 'a';
        }
    }
}

int count_a_num(char **array, int rows, int cols, int start, int end) {
    int count = 0;

    for (int i = start; i < end; i++) {
        for (int j = 0; j < cols; j++) {
            if (array[i][j] == 'a') {
                count++;
            }
        }
    }

    return count;
}