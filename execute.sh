#!/bin/bash

gcc -o multi_thread -pthread multi_thread.c utils.c
gcc -o multi_process multi_process.c utils.c

process_csv="./result/multi_process.csv"
thread_csv="./result/multi_thread.csv"

echo "Processes,Time" > $process_csv
echo "Threads,Time" > $thread_csv

for type in multi_process multi_thread
do
    for i in {1..10}
    do
        result=$("./$type" $i)

        if [ "$type" = "multi_process" ]; then
            echo "$result" >> $process_csv
        elif [ "$type" = "multi_thread" ]; then
            echo "$result" >> $thread_csv
        fi
    done
done
