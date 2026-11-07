/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_dongle_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 13:18:34 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/07 14:49:09 by cebouhad         ###   ########.fr       */
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

    params[number_of_coders] = NB_CODER;
    sim = sim_init(params);
    if (!sim)
        return ;
    assert(dongle_init(1, NULL) == NULL);
    dongles = dongle_init(NB_CODER, sim);
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
    clean_sim(&sim);
    END_TEST;
}