/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 20:21:33 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/08 10:53:14 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static t_sim	*get_sim(int params[8])
{
	t_sim	*sim;

	sim = malloc(sizeof(t_sim));
	if (!sim)
		return (err_msg(BRED"Error malloc init simulation\n"CRESET));
	memset(sim, 0, sizeof(t_sim));
	ft_memcopy(params, sim->params, sizeof(int) * 8);
	sim->thread = threads_init(params[number_of_coders]);
	if (!sim->thread)
		return (sim_clean(&sim));
	sim->can_compile_cond = init_dynamique_cond(params[number_of_coders]);
	if (!sim->can_compile_cond)
		return (sim_clean(&sim));
	sim->can_compile_mu = init_dynamique_mutex(params[number_of_coders]);
	if (!sim->can_compile_mu)
		return (sim_clean(&sim));
	sim->timestamp_mu = init_dynamique_mutex(params[number_of_coders]);
	if (!sim->timestamp_mu)
		return (sim_clean(&sim));
	sim->dongle_mu = init_dynamique_mutex(params[number_of_coders]);
	if (!sim->dongle_mu)
		return (sim_clean(&sim));
	return (sim);
}

t_sim	*sim_init(int params[8])
{
	t_sim	*sim;

	sim = get_sim(params);
	if (!sim)
		return (NULL);
	sim->can_compile = can_compile_init(params[number_of_coders]);
	if (!sim->can_compile)
		return (sim_clean(&sim));
	sim->timestamp = timestamp_init(params[number_of_coders]);
	if (!sim->timestamp)
		return (sim_clean(&sim));
	sim->display_mu = init_dynamique_mutex(1);
	if (!sim->display_mu)
		return (sim_clean(&sim));
	sim->request_queue_mu = init_dynamique_mutex(1);
	if (!sim->request_queue_mu)
		return (sim_clean(&sim));
	sim->simulation_state_mu = init_dynamique_mutex(1);
	if (!sim->simulation_state_mu)
		return (sim_clean(&sim));
	sim->queue = request_queue_init();
	if (!sim->queue)
		return (sim_clean(&sim));
	sim->simulation_state = OFF;
	return (sim);
}
