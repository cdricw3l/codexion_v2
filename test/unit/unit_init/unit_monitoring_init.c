/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_monitoring_init.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 08:42:27 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/19 20:44:50 by cebouhad         ###   ########.fr       */
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
    
    set_sim_state(monitoring->simulation_state, monitoring->simulation_state_mu, ON);
    assert(get_sim_state(monitoring->simulation_state, monitoring->simulation_state_mu) == ON);
    set_sim_state(monitoring->simulation_state, monitoring->simulation_state_mu, OFF);
    assert(get_sim_state(monitoring->simulation_state, monitoring->simulation_state_mu) == OFF);
    set_sim_state(&sim->simulation_state, sim->simulation_state_mu, ON);
    assert(get_sim_state(monitoring->simulation_state, monitoring->simulation_state_mu) == ON);
    set_sim_state(monitoring->simulation_state, monitoring->simulation_state_mu, OFF);
    assert(get_sim_state(&sim->simulation_state, sim->simulation_state_mu) == OFF);

    while (i < nb)
    {
        assert(&monitoring->coders[i] == &coders[i]);
        assert(get_sim_state(coders->simulation_state, coders->simulation_state_mu) == OFF);
        i++;
    }
}

void unit_monitoring_init(void)
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
    
    assert(data.sim);
    assert(data.dongles);
    assert(data.coder);
    assert(data.scheduler);
    assert(data.monitoring);
    check_monitoring(data.sim, data.monitoring, data.coder);
    clear_data(&data, 0);
    END_TEST;
}
