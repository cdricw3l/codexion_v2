/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integration_scheduler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 10:32:20 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/22 04:52:40 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "integration.h"

static void get_dongle(size_t id, int params[8], int dongle[2])
{
    dongle[LEFT] = get_dongle_id(id, params[number_of_coders], LEFT);
    dongle[RIGHT] = get_dongle_id(id, params[number_of_coders], RIGHT);
    if (id == 2)
        assert(dongle[LEFT] == 1 && dongle[RIGHT] == 2);
}

int fifo(t_heap_node *n1, t_heap_node *n2)
{
    t_request *request_1;
    t_request *request_2;

    request_1 = (t_request *)n1->content;
    request_2 = (t_request *)n2->content;
    if (request_1->request_id > request_2->request_id)
        return (true);
    return (false);
}

void *scheduler_routine(void *data)
{

    t_scheduler *scheduler;
    t_request   *request;
    t_heap_node *node1;
    t_heap_node *node2;
    int dongle[2] = {-1, -1};
    int nb;
    
    scheduler = (t_scheduler *)data;
    nb = 0;
    while (get_sim_state(scheduler->sim_state, scheduler->state_mu) == ON)
    {
        request = request_pop(scheduler->queue);
        if (request)
        {
            node1 = heap_new_node(request);
            node2 = heap_new_node(request);
            get_dongle(request->coder_id, scheduler->params, dongle);
            assert(heap_push(scheduler->heaps[dongle[LEFT]], node1, fifo)); 
            assert(heap_push(scheduler->heaps[dongle[RIGHT]], node2, fifo)); 
            usleep(100000);
            nb++;
        }
    }
    return (NULL);
}
