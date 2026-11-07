/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 20:21:33 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/07 08:49:33 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static bool *can_compile_init(int nb)
{
    bool *can_compile;

    can_compile = malloc(sizeof(bool) * nb);
    if (!can_compile)
        return (NULL);
    memset(can_compile, false, sizeof(bool) * nb);
    return (can_compile);
}

static time_t *timestamp_init(int nb)
{
    time_t *timestamp;

    timestamp = malloc(sizeof(time_t) * nb);
    if (!timestamp)
        return (NULL);
    memset(timestamp, 0, sizeof(time_t) * nb);
    return (timestamp);
}

t_sim *sim_init(int params[8])
{
    t_sim *sim;

    sim = malloc(sizeof(t_sim));
    memset(sim, 0, sizeof(t_sim));
    if (!sim)
        return (err_msg(BRED"Error malloc init simulation\n"CRESET));
    sim->can_compile_cond = init_dynamique_cond(params[number_of_coders]);
    if (!sim->can_compile_cond)
        return (clean_sim(&sim));
    sim->can_compile_mu = init_dynamique_mutex(params[number_of_coders]);
    if (!sim->can_compile_mu)
        return (clean_sim(&sim));
    sim->can_compile = can_compile_init(params[number_of_coders]);
    if (!sim->can_compile)
        return (clean_sim(&sim));
    sim->timestamp_mu = init_dynamique_mutex(params[number_of_coders]);
    if (!sim->timestamp_mu)
        return (clean_sim(&sim));
    sim->timestamp = timestamp_init(params[number_of_coders]);
    if (!sim->timestamp)
        return (clean_sim(&sim));
    sim->display_mu = init_dynamique_mutex(1);
    if (!sim->display_mu)
        return (clean_sim(&sim));
    sim->request_queue_mu = init_dynamique_mutex(1);
    if (!sim->request_queue_mu)
        return (clean_sim(&sim));
    return (sim);
}
