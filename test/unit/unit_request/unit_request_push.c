/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_request_push.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 15:20:53 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/18 00:27:47 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_request.h"

t_coder *init_coder(int nb, t_request_queue *queue);
int check_queue_unique_request(t_request *root);
void *push_request_routine(void *data);

static void thread_request_push(void)
{
    START_TEST;
    size_t          i;
    pthread_t       thread[NB_THREAD];
    t_coder         *coders;
    t_request_queue *queue;

    queue = request_queue_init();
    assert(queue);
    assert(queue->queue);
    i = 0;
    coders = init_coder(NB_THREAD, queue);
    assert(coders);
    while (i < NB_THREAD)
    {
        if (pthread_create(&thread[i], NULL, push_request_routine, &coders[i]))
        {
            printf("Error thread_creation");
            return ;
        }
        //printf("Thread %ld is launched\n", coders[i].coder_id);
        i++;
    }
    i = 0;
    while (i < NB_THREAD)
    {
        pthread_join(thread[i], NULL);
        free(coders[i].can_compile);
        free(coders[i].can_compile_cond);
        free(coders[i].can_compile_mu);
                //printf("Thread %ld is finish\n", coders[i].coder_id);
        i++;
    }
    
    free(coders);
    assert(queue->queue_size == 20);
    assert(check_queue_unique_request(*queue->queue));
    //request_display(queue);
    request_clear_queue(queue);
    request_destroy_queue(&queue);
    END_TEST;
}

static void simple_request_push(void)
{
	START_TEST;

    t_request_queue *queue;
    t_coder *coder;


    queue = request_queue_init();
    assert(queue);
    assert(queue->queue);
    coder = init_coder(1, queue);
   
    assert(request_push(coder));
    assert(queue->queue_size == 1);
    assert(request_get_last_node(*queue->queue)->request_id == 0);

    assert(request_push(coder));
    assert(queue->queue_size == 2);
    assert(request_get_last_node(*queue->queue)->request_id == 1);

    assert(request_push(coder));
    assert(queue->queue_size == 1);
    assert(request_get_last_node(*queue->queue)->request_id == 2);

    assert(request_push(coder));
    assert(queue->queue_size == 1);
    assert(request_get_last_node(*queue->queue)->request_id == 3);

    t_request_queue *ptr = NULL;
    assert(!request_destroy_queue(&ptr));
    
    assert(request_destroy_queue(&queue));
	assert(!queue);
    
	END_TEST;	
}

void unit_request_push(void)
{
    simple_request_push();
    thread_request_push();
    
}