#include "../include/test.h"

int main(void)
{
    START_TEST;

    printf("voici %d\n", NULL);
    // struct timespec start;
    // struct timespec end;
    // struct timespec diff;

    // clock_gettime(CLOCK_MONOTONIC, &start);
    // usleep(200000);
    // clock_gettime(CLOCK_MONOTONIC, &end);
    // diff = time_diff(start, end);
    // printf("time: %ld\n", (second_to_nano(diff.tv_sec) + diff.tv_nsec) / 1000000);
    // usleep(200000);
    // clock_gettime(CLOCK_MONOTONIC, &end);
    // diff = time_diff(start, end);
    // printf("time: %ld\n", (second_to_nano(diff.tv_sec) + diff.tv_nsec) / 1000000);

    END_TEST;

    
    return (0);
}