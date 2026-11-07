/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_init_sim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 21:08:14 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/07 08:50:55 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../unit.h"

#define NB_CODER 8

static void check_sim(t_sim *sim)
{
    size_t i;

    i = 0;
    assert(sim);
    assert(sim->can_compile);
    assert(sim->can_compile_cond);
    assert(sim->can_compile_mu);
    assert(sim->display_mu);
    assert(sim->request_queue_mu);
    assert(sim->timestamp);
    assert(sim->timestamp_mu);
    while (i < NB_CODER)
    {
        assert(sim->can_compile[i] == false);
        assert(sim->timestamp[i] == 0);
        
        assert(!pthread_mutex_lock(&sim->can_compile_mu[i]));
        assert(!pthread_mutex_unlock(&sim->can_compile_mu[i]));
        assert(!pthread_cond_signal(&sim->can_compile_cond[i]));
        assert(!pthread_mutex_lock(&sim->timestamp_mu[i]));
        assert(!pthread_mutex_unlock(&sim->timestamp_mu[i]));

        i++;
    }
    assert(!pthread_mutex_lock(sim->request_queue_mu));
    assert(!pthread_mutex_unlock(sim->request_queue_mu));
    assert(!pthread_mutex_lock(sim->display_mu));
    assert(!pthread_mutex_unlock(sim->display_mu));
    
}

void unit_init_sim(void)
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