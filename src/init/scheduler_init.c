#include "../../include/codexion.h"

t_scheduler *scheduler_init(int params[8], t_request_queue *queue)
{   
    t_scheduler *scheduler;
    size_t      i;
    size_t      j;

    if (!queue)
        return (NULL);
    scheduler = malloc(sizeof(t_scheduler));
    if (!scheduler)
        return (err_msg("Error initilisation scheduler\n"));
    scheduler->heaps = malloc(sizeof(t_heap *) * params[number_of_coders]);
    if (!scheduler->heaps)
    {
        free(scheduler);
        return (err_msg("Error initilisation heaps scheduler\n"));
    }
    i = 0;
    while (i < params[number_of_coders])
    {
        scheduler->heaps[i] = heap_init();
        if (!scheduler->heaps[i])
        {
            j = 0;
            while (j < i)
                free(scheduler->heaps[j++]);
            free(scheduler);
            return (err_msg("Error initilisation heap scheduler\n"));
        }
        i++;
    }
    scheduler->queue = queue;
    ft_memcopy(params, scheduler->params, sizeof(int) * 8);
    return (scheduler);
}
