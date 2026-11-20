/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_sim_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 21:08:14 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/19 19:02:27 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_init.h"

void check_sim(t_sim *sim,int params[8])
{
    size_t i;

    i = 0;
    assert(sim);
    assert(sim->params[number_of_coders] == params[number_of_coders]);
    assert(sim->params[time_to_burnout] == params[time_to_burnout]);
    assert(sim->params[time_to_compile] == params[time_to_compile]);
    assert(sim->params[time_to_debug] == params[time_to_debug]);
    assert(sim->params[time_to_refactor] == params[time_to_refactor]);
    assert(sim->params[number_of_compiles_required] == params[number_of_compiles_required]);
    assert(sim->params[dongle_cooldown] == params[dongle_cooldown]);
    assert(sim->params[scheduler] == params[scheduler]);
    assert(sim->can_compile);
    assert(sim->can_compile_cond);
    assert(sim->display_mu);
    assert(sim->can_compile_mu);
    assert(sim->request_queue_mu);
    assert(sim->timestamp_mu);
    assert(sim->dongle_mu);
    assert(sim->timestamp);
    assert(sim->thread);
    assert(sim->queue);
    assert(sim->simulation_state == OFF);
    while (i < NB_CODER)
    {
        assert(sim->can_compile[i] == false);
        assert(sim->timestamp[i] == 0);
        assert(!pthread_cond_signal(&sim->can_compile_cond[i]));
        assert(!pthread_mutex_lock(&sim->can_compile_mu[i]));
        assert(!pthread_mutex_unlock(&sim->can_compile_mu[i]));
        assert(!pthread_mutex_lock(&sim->timestamp_mu[i]));
        assert(!pthread_mutex_unlock(&sim->timestamp_mu[i]));
        assert(!pthread_mutex_lock(&sim->dongle_mu[i]));
        assert(!pthread_mutex_unlock(&sim->dongle_mu[i]));
        assert(!pthread_mutex_lock(&sim->timestamp_mu[i]));
        assert(!pthread_mutex_unlock(&sim->timestamp_mu[i]));
        i++;
    }
    assert(!pthread_mutex_lock(sim->request_queue_mu));
    assert(!pthread_mutex_unlock(sim->request_queue_mu));
    assert(!pthread_mutex_lock(sim->display_mu));
    assert(!pthread_mutex_unlock(sim->display_mu));
    assert(!pthread_mutex_lock(sim->simulation_state_mu));
    assert(!pthread_mutex_unlock(sim->simulation_state_mu));
    
}

void unit_sim_init(void)
{
    START_TEST;
    t_data  data;
    int params[8];
    

    unit_get_param(params);
    if(!initialisation(&data, params))
        printf(BRED"Erreur d'initialisation"CRESET"\n");
    else
        check_sim(data.sim, params);
    clear_data(&data, 0);
    END_TEST;
}