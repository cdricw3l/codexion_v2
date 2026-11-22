/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 12:49:24 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/22 04:47:03 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/codexion.h"

static void	*clean_dynamique_mutex(pthread_mutex_t **m, int nb)
{
	pthread_mutex_t	*mu;

	mu = *m;
	while (--nb >= 0)
	{
		if (pthread_mutex_destroy(&mu[nb]))
			err_msg("Error destruction mutext\n");
	}
	free(*m);
	return (NULL);
}

static void	*clean_dynamique_cond(t_sim **s)
{
	int				nb;
	pthread_cond_t	*co;

	nb = (*s)->params[number_of_coders];
	co = (*s)->can_compile_cond;
	while (--nb >= 0)
	{
		if (pthread_cond_destroy(&co[nb]))
			err_msg("Error destruction cond\n");
	}
	free(co);
	return (NULL);
}

static void	destroy_mutex(t_sim *sim)
{
	int	nb_coder;

	nb_coder = sim->params[number_of_coders];
	if (sim->dongle_mu)
		clean_dynamique_mutex(&sim->dongle_mu, nb_coder);
	if (sim->timestamp_mu)
		clean_dynamique_mutex(&sim->timestamp_mu, nb_coder);
	if (sim->can_compile_mu)
		clean_dynamique_mutex(&sim->can_compile_mu, nb_coder);
	if (sim->display_mu)
		clean_dynamique_mutex(&sim->display_mu, 1);
	if (sim->request_queue_mu)
		clean_dynamique_mutex(&sim->request_queue_mu, 1);
	if (sim->state_mu)
		clean_dynamique_mutex(&sim->state_mu, 1);
}

void	*clean_sim(t_sim **sim)
{
	if (!*sim)
		return (NULL);
	destroy_mutex(*sim);
	if ((*sim)->thread)
		free((*sim)->thread);
	if ((*sim)->can_compile)
		free((*sim)->can_compile);
	if ((*sim)->can_compile_cond)
		clean_dynamique_cond(sim);
	if ((*sim)->timestamp)
		free((*sim)->timestamp);
	if ((*sim)->queue)
		request_destroy_queue(&(*sim)->queue);
	free(*sim);
	return (NULL);
}
