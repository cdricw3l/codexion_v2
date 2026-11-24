/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_scheduler_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 04:28:18 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/24 13:22:18 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_init.h"

void check_scheduler(int nb, t_scheduler *scheduler)
{
    int i;
    int nb_request;
    t_request *request;

    i = 0;
    assert(scheduler->queue);
    while (i < nb)
    {
        assert(scheduler->heaps[i++]);
        i++;
    }
    nb_request = 0;
    while (scheduler->queue->queue_size)
    {
        request = request_pop(scheduler->queue);
        assert(request);
        nb_request++;
        assert(request->request_id == (size_t)nb_request);
        free(request);
    }
    assert(nb_request == scheduler->params[number_of_coders] * scheduler->params[number_of_compiles_required]);
}

void *scheduler_coder_routine(void *ptr)
{
    t_coder *coder;
    int i;
    
    coder = (t_coder *)ptr;
    i = 0;
    while (i < coder->params[number_of_compiles_required])
    {
        assert(request_push(coder));
        i++;
    }
    return (NULL);
}

void unit_scheduler_init(void)
{
    START_TEST;
    t_data data;
   
    int i;
    int params[8];

    unit_get_param(params);
    if(!initialisation(&data, params))
    {
        printf(BRED"Erreur d'initialisation"CRESET"\n");
        return ;
    }
    
    
    assert(data.sim);
    assert(data.dongles);
    assert(data.coder);
    assert(data.scheduler);
    assert(data.scheduler->queue == data.sim->queue);
    assert(data.sim->queue == data.scheduler->queue);
    assert(data.sim->queue == data.coder->queue);
    assert(data.scheduler->sim_state == &data.sim->sim_state);
    assert(data.scheduler->state_mu == data.sim->state_mu);

    i = 0;
    while (i < data.sim->params[number_of_coders])
    {
        assert(data.coder[i].params[number_of_compiles_required] == params[number_of_compiles_required]);
        pthread_create(&data.sim->thread[i], NULL, scheduler_coder_routine, &data.coder[i]);
        usleep(50000);
        i++;
    }
    i = 0;
    while (i < data.sim->params[number_of_coders])
    {
        pthread_join(data.sim->thread[i], NULL);
        i++;
    }
    assert((int)data.sim->queue->queue_size == data.sim->params[number_of_coders] * data.sim->params[number_of_compiles_required]);
    check_scheduler(params[number_of_coders], data.scheduler);
    clear_data(&data, 0);
    END_TEST;
}