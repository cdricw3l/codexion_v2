#include "../include/test.h"

void *routine_scheduler_test(void *data)
{
    t_scheduler *scheduler;
    size_t i;

    scheduler = (t_scheduler *)data;
    i = 0;
    while (i < 10)
    {
        if (!request_pop(scheduler->queue))
            printf("No request to pop\n");
        i++;
    }
    return (NULL);
}

int main(void)
{
    START_TEST;
    
    t_scheduler scheduler;
    t_request_queue *queue;

    queue = request_queue_init();
    assert(queue || queue->queue);
    assert(scheduler_init(&scheduler, queue));
    if (pthread_create(&scheduler.scheduler_thread, NULL, routine_scheduler_test, &scheduler))    
    {
        printf("Error creation thread\n");
        return (1);
    }
    pthread_join(scheduler.scheduler_thread, NULL);
    return (0);
}