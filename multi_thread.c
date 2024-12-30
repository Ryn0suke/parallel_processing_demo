#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "utils.h"

#define ROW_NUM 1000000
#define COL_NUM 10

typedef struct {
    char** str;
    int start;
    int end;
    int index;
} ThreadArgs;

void* thread(void* args) {
    ThreadArgs* targs = (ThreadArgs*)args;
    char** str = targs->str;
    int start = targs->start;
    int end = targs->end;
    int index = targs->index;

    int count = count_a_num(str, ROW_NUM, COL_NUM, start, end);

    //printf("スレッド%dのcountの数：%d\n", index, count);

    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <integer>\n", argv[0]);
        return 1;
    }

    const int THREAD_NUM = atoi(argv[1]);

    char** str = allocate_2d_array(ROW_NUM, COL_NUM);
    set_a(str, ROW_NUM, COL_NUM);

    struct timeval t0, t1;
    pthread_t threads[THREAD_NUM];
    ThreadArgs args[THREAD_NUM];

    gettimeofday(&t0, NULL);

    for (int i = 0; i < THREAD_NUM; i++) {
        int range = ROW_NUM / THREAD_NUM;
        int start = i * range;
        int end = (i == THREAD_NUM - 1) ? ROW_NUM : (i + 1) * range;

        args[i].str = str;
        args[i].start = start;
        args[i].end = end;
        args[i].index = i;

        if (pthread_create(&threads[i], NULL, thread, &args[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    for (int i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            return 1;
        }
    }

    gettimeofday(&t1, NULL);
    timersub(&t1, &t0, &t1);

    //printf("処理時間: %ld.%06ld 秒\n", (long)t1.tv_sec, (long)t1.tv_usec);
    printf("%d,%ld.%06ld\n", THREAD_NUM, (long)t1.tv_sec, (long)t1.tv_usec);

    free_2d_array(str, ROW_NUM);

    return 0;
}
