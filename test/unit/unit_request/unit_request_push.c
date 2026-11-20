/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_request_push.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 15:20:53 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/20 01:49:57 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_request.h"

t_coder *init_coder(int nb, t_request_queue *queue);
int check_queue_unique_request(t_request *root);
void *push_request_routine(void *data);

static void simple_request_push(void)
{
	START_TEST;
    t_data data;
    int params[8];

    unit_get_param(params);
    params[number_of_coders] = 1;
    if(!initialisation(&data, params))
    {
        printf(BRED"Erreur d'initialisation"CRESET"\n");
        return ;
    }

    t_coder *coder = &data.coder[0];

    assert(coder->queue);
    assert(coder->queue->queue);
   
    assert(request_push(coder));
    assert(coder->queue->queue_size == 1);
    assert(request_get_last_node(*coder->queue->queue)->request_id == 1);

    assert(request_push(coder));
    assert(coder->queue->queue_size == 2);
    assert(request_get_last_node(*coder->queue->queue)->request_id == 2);

    assert(request_push(coder));
    assert(coder->queue->queue_size == 3);
    assert(request_get_last_node(*coder->queue->queue)->request_id == 3);

    assert(request_push(coder));
    assert(coder->queue->queue_size == 4);
    assert(request_get_last_node(*coder->queue->queue)->request_id == 4);

    clear_data(&data, 0);
    
	END_TEST;	
}

static void thread_request_push(void)
{
    START_TEST;
    t_data data;
   
    size_t i;
    int params[8];

    unit_get_param(params);
    if(!initialisation(&data, params))
    {
        printf(BRED"Erreur d'initialisation"CRESET"\n");
        return ;
    }
    assert(data.coder);
    assert(data.coder->queue);
    assert(data.coder->queue->queue);
    i = 0;
    while (i < NB_CODER)
    {
        if (pthread_create(&data.sim->thread[i], NULL, push_request_routine, &data.coder[i]))
        {
            printf("Error thread_creation");
            return ;
        }
        //printf("Thread %ld is launched\n", coders[i].coder_id);
        i++;
    }
    i = 0;
    while (i < NB_CODER)
    {
        pthread_join(data.sim->thread[i], NULL);
        //printf("Thread %ld is finish\n", coders[i].coder_id);
        i++;
    }
    assert(data.coder->queue->queue_size == 20);
    assert(check_queue_unique_request(*data.coder->queue->queue));
    clear_data(&data, 0);
    END_TEST;
}



void unit_request_push(void)
{
    simple_request_push();
    thread_request_push();
    
}