/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 14:37:23 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/07 18:08:28 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

t_coder *coders_init(int params[8], t_sim *sim, t_dongles *dongle)
{
    t_coder *coders;
    size_t  i;
    
    coders = malloc(sizeof(t_coder) * params[number_of_coders]);
    if (!coders)
        return (err_msg("Error initialisation dongle\n"));
    i = 0;
    while (i < params[number_of_coders])
    {
        coders[i].coder_id = i;
        coders[i].can_compile = &sim->can_compile[i];
        coders[i].can_compile_mu = &sim->can_compile_mu[i];
        coders[i].can_compile_cond = &sim->can_compile_cond[i];
        coders[i].queue = sim->queue;
        coders[i].dongle_left = &dongle[get_dongle(i, params[number_of_coders], LEFT)];
        coders[i].dongle_right = &dongle[get_dongle(i, params[number_of_coders], RIGHT)];
        coders[i].simulation_state = &sim->simulation_state;
        coders[i].simulation_state_mu = sim->simulation_state_mu;
        coders[i].timestamp = &sim->timestamp[i];
        coders[i].timestamp_mu = &sim->timestamp_mu[i];
        ft_memcopy(params, coders[i].params, sizeof(int) * 8);
        i++;
    }
    return (coders);
}