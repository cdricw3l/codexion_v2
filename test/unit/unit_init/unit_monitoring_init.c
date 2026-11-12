/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_monitoring_init.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 08:42:27 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/11 21:00:37 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_init.h"

void check_monitoring(t_sim *sim, t_monitoring *monitoring, t_coder *coders)
{
    size_t i;
    size_t nb;

    i = 0;
    nb = sim->params[number_of_coders];
    assert(monitoring->simulation_state == &sim->simulation_state);
    assert(monitoring->simulation_state_mu == sim->simulation_state_mu);
    assert(!pthread_mutex_lock(monitoring->simulation_state_mu));
    *monitoring->simulation_state = ON;
    assert(!pthread_mutex_unlock(monitoring->simulation_state_mu));
    assert(sim->simulation_state == ON);
    sim->simulation_state = OFF;
    assert(*monitoring->simulation_state == OFF);
    while (i < nb)
    {
        assert(&monitoring->coders[i] == &coders[i]);
        i++;
    }
}

void unit_monitoring_init(void)
{
    START_TEST;
    t_sim *sim;
    t_coder *coders;
    t_dongles *dongles;
    t_monitoring *monitoring;
    int params[8];
    
    unit_get_param(params);
    sim = sim_init(params);
    if (!sim)
        return ;
    dongles = dongle_init(params, sim);
    assert(dongles); 
    coders = coders_init(params, sim, dongles);
    assert(!monitoring_init(params, NULL, coders));
    assert(!monitoring_init(params, sim, NULL));
    monitoring = monitoring_init(params, sim, coders);
    assert(monitoring);
    check_monitoring(sim, monitoring, coders);
    free(coders);
    free(dongles);
    free(monitoring);
    sim_clean(&sim);
    END_TEST;
}
