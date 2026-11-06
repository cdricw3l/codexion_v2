/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_request_push.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 15:20:53 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/06 05:48:16 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_request.h"

#define NB_THREAD 2

int check_queue_unique_request(t_request *root)
{

    t_request *next;

    while (root)
    {
        next = root->next;
        while (next)
        {
            if (root->request_id == next->request_id)
                return (false);
            next = next->next;
        }
        root = root->next;
    }
    return (TRUE);
}


t_coder *init_coder(int nb, t_request_queue *queue)
{
    t_coder *coders;
    int i;

    coders = malloc(sizeof(t_coder) * nb);
    assert(coders);
    i = 0;
    while (i < nb)
    {
        coders[i].can_compile = false;
        pthread_cond_init(&coders[i].can_compile_cond, NULL);
        pthread_mutex_init(&coders[i].can_compile_mu, NULL);
        coders[i].coder_id = i;
        coders[i].queue = queue;
        i++;
    }
    return (coders);
}


void *push_request_routine(void *data)
{
    t_coder *coder;
    t_request *request;
    size_t i;

    coder = (t_coder *)data;
    i = 0;
    assert(coder->queue);
    assert(coder->queue->queue);
    // assert(!pthread_mutex_lock(&coder->queue->queue_mutex));
    // assert(!pthread_mutex_unlock(&coder->queue->queue_mutex));
    while (i < 10)
    {
        request = request_new_node(coder);
        assert(request_push(coder->queue, request));
        i++;
        usleep(200000);
    }
    return (NULL);
}
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
        printf("Thread %ld is launched\n", coders[i].coder_id);
        i++;
    }
    i = 0;
    while (i < NB_THREAD)
    {
        pthread_join(thread[i], NULL);
        printf("Thread %ld is finish\n", coders[i].coder_id);
        i++;
    }
    free(coders);
    assert(queue->queue_size == 20);
    assert(check_queue_unique_request(*queue->queue));
    request_display(queue);
    request_clear_queue(queue);
    request_destroy_queue(&queue);
    END_TEST;
}

static void simple_request_push(void)
{
	START_TEST;

    t_request r1;
    t_request_queue *queue;
    t_request r2;
    t_request r3;


    queue = request_queue_init();
    assert(queue);
    assert(queue->queue);

    r1.coder_id = 0;
    r1.next = NULL;
    assert(request_push(queue, &r1));
    assert(queue->queue_size == 1);
    assert(request_get_last_node(*queue->queue) == &r1);

    r2.coder_id = 1;
    r2.next = NULL;
    assert(request_push(queue, &r2));
    assert(queue->queue_size == 2);
    assert(request_get_last_node(*queue->queue) == &r2);

    r3.coder_id = 2;
    r3.next = NULL;
    assert(request_push(queue, &r3));
    assert(queue->queue_size == 3);
    assert(request_get_last_node(*queue->queue) == &r3);

    assert(!request_push(queue, NULL));
    assert(queue->queue_size == 3);
    assert(!request_push(NULL, NULL));
    assert(queue->queue_size == 3);

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