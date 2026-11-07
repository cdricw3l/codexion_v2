/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_sim_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 21:08:14 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/07 16:06:35 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_init.h"

static void check_sim(t_sim *sim)
{
    size_t i;

    i = 0;
    assert(sim);
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
        i++;
    }
    assert(!pthread_mutex_lock(sim->request_queue_mu));
    assert(!pthread_mutex_unlock(sim->request_queue_mu));
    assert(!pthread_mutex_lock(sim->display_mu));
    assert(!pthread_mutex_unlock(sim->display_mu));
    
}

void unit_sim_init(void)
{
    START_TEST;
    t_sim *sim;
    int params[8];  

    params[number_of_coders] = NB_CODER;
    sim = sim_init(params);
    if (!sim)
        return ;
    check_sim(sim);
    printf(BGRN"INITIALISATION OK"CRESET"\n");
    clean_sim(&sim);
    END_TEST;
}