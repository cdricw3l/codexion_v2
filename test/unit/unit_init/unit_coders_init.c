/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_coders_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 14:47:25 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/07 16:31:59 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_init.h"

void check_coder(int params[8], t_coder *coders, t_sim *sim, t_dongles *dongles)
{
    size_t i;

    i = 0;
    assert(coders->can_compile);
    assert(coders->can_compile_cond);
    assert(coders->can_compile_mu);
    assert(coders->dongle_left);
    assert(coders->dongle_right);
    assert(coders->queue);
    assert(coders->params[number_of_coders] == params[number_of_coders]);
    assert(coders->params[time_to_burnout] == params[time_to_burnout]);
    assert(coders->params[time_to_compile] == params[time_to_compile]);
    assert(coders->params[time_to_debug] == params[time_to_debug]);
    assert(coders->params[time_to_refactor] == params[time_to_refactor]);
    assert(coders->params[number_of_compiles_required] == params[number_of_compiles_required]);
    assert(coders->params[dongle_cooldown] == params[dongle_cooldown]);
    assert(coders->params[scheduler] == params[scheduler]);
    while (i < params[number_of_coders])
    {
        assert(coders[i].coder_id == i);
        assert(coders[i].can_compile == &sim->can_compile[i]);
        assert(coders[i].can_compile_cond == &sim->can_compile_cond[i]);
        assert(coders[i].can_compile_mu == &sim->can_compile_mu[i]);
        assert(coders[i].dongle_left == &dongles[get_dongle(i, params[number_of_coders], LEFT)]);
        assert(coders[i].dongle_right == &dongles[get_dongle(i, params[number_of_coders], RIGHT)]);
        assert(coders[i].queue == sim->queue);
        i++;
    }
    
}

void unit_coder_init(void)
{
    START_TEST;
    t_sim *sim;
    t_coder *coders;
    t_dongles *dongles;
    int params[8];  

    params[number_of_coders] = NB_CODER;
    params[time_to_burnout] = 500;
    params[time_to_compile] = 200;
    params[time_to_debug] = 100;
    params[time_to_refactor] = 100;
    params[number_of_compiles_required] = 10;
    params[dongle_cooldown] = 10;
    params[scheduler] = FIFO;


    params[number_of_coders] = NB_CODER;
    sim = sim_init(params);
    if (!sim)
        return ;
    assert(dongle_init(1, NULL) == NULL);
    dongles = dongle_init(NB_CODER, sim);
    assert(dongles);
    coders = coders_init(params, sim, dongles);
    assert(coders);
    check_coder(params, coders, sim, dongles);
    free(dongles);
    free(coders);

    clean_sim(&sim);
    END_TEST;
}