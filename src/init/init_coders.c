/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 14:37:23 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/09 10:53:31 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static t_dongles	*get_dongle(int coder_id,
	int nb_of_coder, int type, t_dongles *dongle)
{
	return (&dongle[get_dongle_id(coder_id, nb_of_coder, type)]);
}

t_coder	*coders_init(int p[8], t_sim *sim, t_dongles *dgl)
{
	int	i;
	t_coder	*coders;

	coders = malloc(sizeof(t_coder) * p[number_of_coders]);
	if (!coders)
		return (err_msg("Error initialisation dongle\n"));
	i = 0;
	while (i < p[number_of_coders])
	{
		coders[i].coder_id = i;
		coders[i].can_compile = &sim->can_compile[i];
		coders[i].can_compile_mu = &sim->can_compile_mu[i];
		coders[i].can_compile_cond = &sim->can_compile_cond[i];
		coders[i].queue = sim->queue;
		coders[i].dongle_left = get_dongle(i, p[number_of_coders], LEFT, dgl);
		coders[i].dongle_right = get_dongle(i, p[number_of_coders], RIGHT, dgl);
		coders[i].simulation_state = &sim->simulation_state;
		coders[i].simulation_state_mu = sim->simulation_state_mu;
		coders[i].timestamp = &sim->timestamp[i];
		coders[i].timestamp_mu = &sim->timestamp_mu[i];
		coders[i].display_mu = sim->display_mu;
		ft_memcopy(p, &coders[i].params, sizeof(int) * 8);
		i++;
	}
	return (coders);
}
