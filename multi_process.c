#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>
#include <sys/wait.h>
#include "utils.h"

#define ROW_NUM 1000000
#define COL_NUM 10

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <integer>\n", argv[0]);
        return 1;
    }

    const int PROCESS_NUM = atoi(argv[1]);

    char** str = allocate_2d_array(ROW_NUM, COL_NUM);

    set_a(str, ROW_NUM, COL_NUM);

    pid_t pid[PROCESS_NUM];
    struct timeval t0, t1;

    gettimeofday(&t0, NULL);

    for (int i = 0; i < PROCESS_NUM; i++) {
        pid[i] = fork();
        if (pid[i] == -1) {
            err(EXIT_FAILURE, "can not create");
        } else if (pid[i] == 0) {
            // 子プロセス
            int range = ROW_NUM / PROCESS_NUM;
            int start = i * range;
            int end = (i == PROCESS_NUM - 1) ? ROW_NUM : (i + 1) * range;
            int count = count_a_num(str, ROW_NUM, COL_NUM, start, end);

            //printf("プロセス%dのcountの数：%d\n", i, count);

            exit(EXIT_SUCCESS);
        }
    }

    for (int i = 0; i < PROCESS_NUM; i++) {
        int status;
        waitpid(pid[i], &status, 0);
    }

    gettimeofday(&t1, NULL);
    timersub(&t1, &t0, &t1);

    //printf("処理時間: %ld.%06ld 秒\n", (long)t1.tv_sec, (long)t1.tv_usec);
    printf("%d,%ld.%06ld\n", PROCESS_NUM, (long)t1.tv_sec, (long)t1.tv_usec);

    free_2d_array(str, ROW_NUM);

    return 0;
}
