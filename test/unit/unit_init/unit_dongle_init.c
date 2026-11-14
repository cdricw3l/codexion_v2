/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_dongle_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 13:18:34 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/11 20:56:16 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_init.h"

void unit_dongle_init(void)
{
    START_TEST;
    t_sim *sim;
    size_t  i;
    t_dongles *dongles;
    int params[8];  

    unit_get_param(params);
    sim = sim_init(params);
    if (!sim)
        return ;
    assert(dongle_init(params, NULL) == NULL);
    dongles = dongle_init(params, sim);
    assert(dongles);
    i = 0;
    while (i < NB_CODER)
    {
        assert(dongles[i].id == i);
        assert(dongles[i].last_use == 0);
        assert(dongles[i].dongle == &sim->dongle_mu[i]);
        assert(!pthread_mutex_lock(dongles[i].dongle));
        assert(!pthread_mutex_unlock(dongles[i].dongle));
        i++;
    }
    free(dongles);
    sim_clean(&sim);
    END_TEST;
}