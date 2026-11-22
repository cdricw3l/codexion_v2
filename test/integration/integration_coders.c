/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integration_coders.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 09:52:15 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/22 04:47:03 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "integration.h"

void display_heap(t_heap *heap)
{
    size_t i;

    i = 0;
    while (i < heap->heap_size)
    {
        request_display_node((t_request *)(heap->queue[i]->content));
        i++;
    }
    
}

void *coder_routine(void *data)
{
    t_coder *coder;
    t_request *request;

    coder = (t_coder *)data;
    request = request_push(coder);
    assert(request_push(coder->queue, request));
    return (NULL);
}

void start_coder_thread(t_sim *sim, t_coder *coder, t_scheduler *scheduler)
{
    START_BLOCK;
    size_t i;
    uint64_t start;

    i = 0;
    set_sim_state(&sim->simulation_state,sim->state_mu, ON);
    start = get_now();
    while (i < sim->params[number_of_coders])
    {
        if (i % 2 == 0)
        {
            coder->simulation_start = start;
            if (pthread_create(&sim->thread[i], NULL, coder_routine, &coder[i]))
                return ;
            
        }
            
        usleep(100000);
        i++;
    }
    i = 0;
    while (i < sim->params[number_of_coders])
    {
        if (i % 2 != 0)
        {
            coder->simulation_start = start;
            if (pthread_create(&sim->thread[i], NULL, coder_routine, &coder[i]))
                return ;
        }
            
        usleep(100000);
        i++;
    }
    
    pthread_create(&scheduler->scheduler_thread, NULL, scheduler_routine, scheduler);
    i = 0;
    while (i < sim->params[number_of_coders])
    {
        pthread_join(sim->thread[i], NULL);
        i++;
    }
    usleep(100000);
    printf("The number of request is %d\n", request_get_queue_size(scheduler->queue));

    while (request_get_queue_size(scheduler->queue))
        usleep(50000);
    set_sim_state(&sim->simulation_state,sim->state_mu, OFF);

    pthread_join(scheduler->scheduler_thread, NULL);

    i = 0;
    while (i < sim->params[number_of_coders])
    {
        printf(BGRN"Queue %ld:"CRESET"\n", i);
        display_heap(scheduler->heaps[i]);
        i++;
    }
    
    
}