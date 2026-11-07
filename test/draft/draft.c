#include "../include/test.h"

int main(void)
{
    START_TEST;
    

    pthread_t *thread;
    thread = malloc(sizeof(pthread_t) * 10);
    assert(thread);
    assert(&thread[0]);
    return (0);
}