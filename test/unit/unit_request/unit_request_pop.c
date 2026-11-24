/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_request_pop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 07:06:22 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/24 14:41:51 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_request.h"

#define D 0

t_coder *init_coder(int nb, t_request_queue *queue);
void *push_request_routine(void *data);

static void simple_request_pop(void)
{
	START_TEST;

    t_data data;
    int params[8];
    t_request *request;
    

    unit_get_param(params);
    params[number_of_coders] = 2;
    if(!initialisation(&data, params))
    {
        printf(BRED"Erreur d'initialisation"CRESET"\n");
        return ;
    }

    t_coder *coder = &data.coder[0];
    assert(coder);

    assert(request_push(coder));
    assert(request_push(coder));
    assert(request_push(coder));
    assert(request_push(coder));

    assert(coder->queue->queue_size == 4);

    request = request_pop(coder->queue);
    assert(request->request_id == 1);
    free(request);
    assert(coder->queue->queue_size == 3);
    request = request_pop(coder->queue);
    assert(request->request_id == 2);
    free(request);
    assert(coder->queue->queue_size == 2);
    request = request_pop(coder->queue);
    assert(request->request_id == 3);
    free(request);
    assert(coder->queue->queue_size == 1);
    request = request_pop(coder->queue);
    assert(request->request_id == 4);
    free(request);
    assert(coder->queue->queue_size == 0);
    
    request = request_pop(coder->queue);
    assert(!request);
    assert(coder->queue->queue_size == 0);
    assert(*coder->queue->queue == NULL);

    request = request_pop(NULL);
    assert(!request);
    assert(coder->queue->queue_size == 0);
    assert(*coder->queue->queue == NULL);
    
    request_clear_queue(data.sim->queue);
    clear_data(&data, 0);
	END_TEST;	
}



void *pop_request_routine(void *data)
{

    t_scheduler *scheduler;
    t_request   *request;

    scheduler = (t_scheduler *)data;
    while (request_get_queue_size(scheduler->queue))
    {
        request = request_pop(scheduler->queue);
        #if D == 1
            printf("Scheduler pop the request:\n");
            request_display_node(request);
        #endif
        assert(request);
        free(request);
        usleep(50000);
    }
    return (NULL);
}

void thread_request_pop(void)
{
    START_TEST;
    int         i;
    t_data      data;
    int         params[8];
    
    unit_get_param(params);
    
    if(!initialisation(&data, params))
    {
        printf(BRED"Erreur d'initialisation"CRESET"\n");
        return ;
    }
    assert(params[number_of_coders] == NB_CODER);
    assert(data.coder);
    assert(data.coder->queue);
    i = 1;
    while (i < NB_CODER + 1)
    {
        if (pthread_create(&data.sim->thread[i], NULL, push_request_routine, &data.coder[i - 1]))
        {
            printf("Error thread_creation");
            return ;
        }
        i++;
    }
    i = 1;
    if (pthread_create(&data.sim->thread[0], NULL, pop_request_routine, data.scheduler))
    {
        printf("Error thread_creation");
        return ;
    }
    while (i < NB_CODER + 1)
    {
        pthread_join(data.sim->thread[i], NULL);
        i++;
    }
    
    
    pthread_join(data.sim->thread[0], NULL);
    assert(data.scheduler->queue->queue_size == 0);
    assert(--(data.scheduler->queue->request_counter) == 20);
    clear_data(&data, 0);
    END_TEST;
}



void unit_request_pop(void)
{
    simple_request_pop();
    thread_request_pop();
}