/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_request_pop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 07:06:22 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/18 00:25:35 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_request.h"

t_coder *init_coder(int nb, t_request_queue *queue);
void *push_request_routine(void *data);


void *pop_request_routine(void *data)
{
    t_request_queue *queue;
    t_request *request;

    queue = (t_request_queue *)data;
    while (request_get_queue_size(queue))
    {
        request = request_pop(queue);
        printf("Scheduler pop the request:\n");
        request_display_node(request);
        assert(request);
        free(request);
        usleep(50000);
    }
    return (NULL);
}

void thread_request_pop(void)
{
    START_TEST;
    t_request_queue *queue;
    t_coder *coders;
    pthread_t thread_coder[NB_THREAD];
    pthread_t thread_scheduler;
    size_t i;

    queue = request_queue_init();
    assert(queue);
    coders = init_coder(NB_THREAD, queue);
    assert(coders);
    i = 0;
    while (i < NB_THREAD)
    {
        if (pthread_create(&thread_coder[i], NULL, push_request_routine, &coders[i]))
        {
            printf("Error thread_creation");
            return ;
        }
        i++;
    }
    if (pthread_create(&thread_scheduler, NULL, pop_request_routine, queue))
    {
        printf("Error thread_creation");
        return ;
    }
    i = 0;
    while (i < NB_THREAD)
    {
        pthread_join(thread_coder[i], NULL);
        free(coders[i].can_compile);
        free(coders[i].can_compile_cond);
        free(coders[i].can_compile_mu);
        //printf("Thread %ld is finish\n", coders[i].coder_id);
        i++;
    }
    pthread_join(thread_scheduler, NULL);
    assert(queue->queue_size == 0);
    free(coders);
    request_destroy_queue(&queue);
    END_TEST;
}

static void simple_request_pop(void)
{
	START_TEST;

    t_request_queue *queue;
    t_request *request;
    t_coder *coder;


    queue = request_queue_init();
    assert(queue);
    assert(queue->queue);

    coder = init_coder(1, queue);
    assert(coder);

  
    assert(request_push(coder));
    assert(request_push(coder));
    assert(request_push(coder));
    assert(request_push(coder));

    assert(queue->queue_size == 4);
    request = request_pop(coder->queue);
    assert(request->request_id == 0);
    assert(queue->queue_size == 3);
    
    request = request_pop(coder->queue);
    assert(request->request_id == 1);
    assert(queue->queue_size == 2);
    
    request = request_pop(coder->queue);
    assert(queue->queue_size == 1);
    assert(request->request_id == 2);

    request = request_pop(coder->queue);
    assert(request->request_id == 3);
    assert(queue->queue_size == 0);
    
    request = request_pop(coder->queue);
    assert(!request);
    assert(queue->queue_size == 0);
    assert(*queue->queue == NULL);

    request = request_pop(NULL);
    assert(!request);
    assert(queue->queue_size == 0);

    assert(request_destroy_queue(&queue));
	assert(!queue);
    
	END_TEST;	
}


void unit_request_pop(void)
{
    simple_request_pop();
    thread_request_pop();
}