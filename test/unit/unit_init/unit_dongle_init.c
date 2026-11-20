/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_dongle_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 13:18:34 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/19 19:17:03 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_init.h"

void check_sim(t_sim *sim,int params[8]);

void unit_dongle_init(void)
{
    START_TEST;
    t_data  data;
    size_t  i;
    int params[8];  

    unit_get_param(params);
    if(!initialisation(&data, params))
    {
        printf(BRED"Erreur d'initialisation"CRESET"\n");
        return ;
    }
    else
        check_sim(data.sim, params);
    i = 0;
    while (i < NB_CODER)
    {
        assert(data.dongles[i].id == i);
        assert(data.dongles[i].last_use == 0);
        assert(data.dongles[i].dongle == &data.sim->dongle_mu[i]);
        assert(!pthread_mutex_lock(data.dongles[i].dongle));
        assert(!pthread_mutex_unlock(data.dongles[i].dongle));
        i++;
    }
    clear_data(&data, 0);
    END_TEST;
}