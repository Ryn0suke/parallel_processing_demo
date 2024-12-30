#include <stdio.h>
#include <sys/time.h>
#include "utils.h"

#define ROW_NUM 1000000
#define COL_NUM 10

int main() {
    char** str = allocate_2d_array(ROW_NUM, COL_NUM);

    set_a(str, ROW_NUM, COL_NUM);

    struct timeval t0, t1;
    gettimeofday(&t0, NULL);

    int count = count_a_num(str, ROW_NUM, COL_NUM, 0, ROW_NUM);

    gettimeofday(&t1, NULL);

    timersub(&t1, &t0, &t1);

    printf("aの数は%d個です\n", count);
    printf("処理時間: %d.%06d\n", t1.tv_sec,t1.tv_usec);

    free_2d_array(str, ROW_NUM);

    return 0;
}
