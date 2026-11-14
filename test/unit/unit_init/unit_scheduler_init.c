/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_scheduler_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 04:28:18 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/14 12:45:15 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_init.h"

void check_scheduler(int nb, t_scheduler *scheduler)
{
    size_t i;
    size_t nb_request;
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
        free(request);
        nb_request++;
    }
    assert(nb_request == scheduler->params[number_of_coders] * scheduler->params[number_of_compiles_required]);
}

void *scheduler_coder_routine(void *ptr)
{
    t_coder *coder;
    t_request *request;
    size_t i;
    
    coder = (t_coder *)ptr;
    i = 0;
    while (i < coder->params[number_of_compiles_required])
    {
        request = request_push(coder);
        assert(request);
        i++;
    }
    return (NULL);
}

void unit_scheduler_init(void)
{
    START_TEST;
    t_sim   *sim;
    t_coder *coders;
    t_dongles *dongles;
    t_scheduler *scheduler;
    size_t i;
    int params[8];

    unit_get_param(params);
    
    
    sim = sim_init(params);
    assert(sim);
    dongles = dongle_init(params, sim);
    assert(dongles);
    coders = coders_init(params, sim, dongles);
    assert(coders);
    scheduler = scheduler_init(params, sim);
    assert(scheduler);
    assert(scheduler->queue == sim->queue);
    assert(sim->queue == scheduler->queue);
    assert(sim->queue == coders->queue);
    assert(scheduler->simulation_state == &sim->simulation_state);
    assert(scheduler->simulation_state_mu == sim->simulation_state_mu);

    i = 0;
    while (i < sim->params[number_of_coders])
    {
        assert(coders[i].params[number_of_compiles_required] == 20);
        pthread_create(&sim->thread[i], NULL, scheduler_coder_routine, &coders[i]);
        usleep(50000);
        i++;
    }
    i = 0;
    while (i < sim->params[number_of_coders])
    {
        pthread_join(sim->thread[i], NULL);
        i++;
    }
    assert(sim->queue->queue_size == sim->params[number_of_coders] * sim->params[number_of_compiles_required]);
    check_scheduler(params[number_of_coders], scheduler);

    free(dongles);
    free(coders);
    scheduler_clean(&scheduler);
    sim_clean(&sim);

    END_TEST;
}