/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_monitoring_init.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 08:42:27 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/22 04:52:40 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_init.h"

void check_monitoring(t_sim *sim, t_monitoring *monitoring, t_coder *coders)
{
    size_t i;
    size_t nb;

    i = 0;
    nb = sim->params[number_of_coders];

    assert(monitoring->sim_state == &sim->sim_state);
    assert(monitoring->state_mu == sim->state_mu);
    
    set_sim_state(monitoring->sim_state, monitoring->state_mu, ON);
    assert(get_sim_state(monitoring->sim_state, monitoring->state_mu) == ON);
    set_sim_state(monitoring->sim_state, monitoring->state_mu, OFF);
    assert(get_sim_state(monitoring->sim_state, monitoring->state_mu) == OFF);
    set_sim_state(&sim->sim_state, sim->state_mu, ON);
    assert(get_sim_state(monitoring->sim_state, monitoring->state_mu) == ON);
    set_sim_state(monitoring->sim_state, monitoring->state_mu, OFF);
    assert(get_sim_state(&sim->sim_state, sim->state_mu) == OFF);

    while (i < nb)
    {
        assert(&monitoring->coders[i] == &coders[i]);
        assert(get_sim_state(coders->sim_state, coders->state_mu) == OFF);
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
