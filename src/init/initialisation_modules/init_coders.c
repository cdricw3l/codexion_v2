/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 14:37:23 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/24 11:18:30 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/codexion.h"

static t_dongles	*get_dongle(int coder_id,
	int params[8], int type, t_dongles *dongle)
{
	int	dongle_id[2];

	get_dongle_arr(coder_id, params, dongle_id);
	return (&dongle[dongle_id[type]]);
}

t_coder	*coders_init(t_sim *sim, t_dongles *dgl, int p[8])
{
	int		i;
	t_coder	*coders;

	coders = malloc(sizeof(t_coder) * p[number_of_coders]);
	if (!coders)
		return (err_msg("Error initialisation dongle\n"));
	i = 0;
	while (i < p[number_of_coders])
	{
		coders[i].coder_id = i;
		coders[i].simulation_start = &sim->simulation_start;
		coders[i].can_compile = &sim->can_compile[i];
		coders[i].can_compile_mu = &sim->can_compile_mu[i];
		coders[i].can_compile_cond = &sim->can_compile_cond[i];
		coders[i].queue = sim->queue;
		coders[i].dongle_left = get_dongle(i, p, LEFT, dgl);
		coders[i].dongle_right = get_dongle(i, p, RIGHT, dgl);
		coders[i].sim_state = &sim->sim_state;
		coders[i].state_mu = sim->state_mu;
		coders[i].timestamp = &sim->timestamp[i];
		coders[i].timestamp_mu = &sim->timestamp_mu[i];
		coders[i].display_mu = sim->display_mu;
		ft_memcopy(p, &coders[i++].params, sizeof(int) * 8);
	}
	return (coders);
}
