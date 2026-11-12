/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_monitoring.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 20:25:01 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/12 00:16:13 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_monitoring.h"


void *unit_coder_monitor_routine(void *data)
{
    t_coder *coder;
    size_t  i;

    coder = (t_coder *)data;
    i = 0;

    while (coder->params[number_of_coders] > i)
    {
        pthread_mutex_lock(coder->dongle_left->dongle);
        pthread_mutex_lock(coder->dongle_right->dongle);
        display_action(coder, COMPILE);
        action(coder, COMPILE);
        display_action(coder, DEBUG);
        action(coder, DEBUG);
        display_action(coder, REFACTO);
        action(coder, REFACTO);
    }
    return (NULL);
}

static void unit_monitoring_thread(t_sim *sim, t_coder *coder, t_monitoring *monitor)
{
    START_TEST;
    set_sim_state(&sim->simulation_state, sim->simulation_state_mu, ON);
    assert(!launch_coders(sim, coder, unit_coder_monitor_routine, PAIR));
    assert(launch_coders(sim, coder, unit_coder_monitor_routine, IMPAIRE));
    assert(joint_coders(sim));
    END_TEST;
}


int unit_monitoring(void)
{
    START_BLOCK;
    t_sim *sim;
    t_dongles *dongle;
    t_coder *coders;
    t_scheduler *scheduler;
    t_monitoring *monitor;

    int param[8];
    unit_get_param(param);

    sim = sim_init(param);
    assert(sim);
    dongle = dongle_init(param, sim);
    assert(dongle);
    coders = coders_init(param, sim, dongle);
    assert(coders);
    scheduler = scheduler_init(param, sim);
    assert(scheduler);
    monitor = monitoring_init(param, sim, coders);
    assert(monitor);
    unit_monitoring_thread(sim, coders, monitor);
    return (TRUE);

}

