/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 12:49:24 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/08 09:34:35 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	*clean_dynamique_mutex(pthread_mutex_t **mutex, int nb)
{
	int				i;
	pthread_mutex_t	*mu;

	i = 0;
	mu = *mutex;
	while (i < nb)
	{
		if (pthread_mutex_destroy(&mu[i]))
			err_msg("Error destruction mutext\n");
		i++;
	}
	free(*mutex);
	*mutex = NULL;
	return (NULL);
}

void	*clean_dynamique_cond(pthread_cond_t **cond, int nb)
{
	int				i;
	pthread_cond_t	*co;

	i = 0;
	co = *cond;
	while (i < nb)
	{
		if (pthread_cond_destroy(&co[i]))
			err_msg("Error destruction cond\n");
		i++;
	}
	free(*cond);
	*cond = NULL;
	return (NULL);
}

void	*sim_clean(t_sim **sim)
{
	if ((*sim)->thread)
		free((*sim)->thread);
	if ((*sim)->can_compile)
		free((*sim)->can_compile);
	if ((*sim)->can_compile_cond)
		free((*sim)->can_compile_cond);
	if ((*sim)->can_compile_mu)
		free((*sim)->can_compile_mu);
	if ((*sim)->display_mu)
		free((*sim)->display_mu);
	if ((*sim)->request_queue_mu)
		free((*sim)->request_queue_mu);
	if ((*sim)->timestamp)
		free((*sim)->timestamp);
	if ((*sim)->timestamp_mu)
		free((*sim)->timestamp_mu);
	if ((*sim)->simulation_state_mu)
		free((*sim)->simulation_state_mu);
	if ((*sim)->dongle_mu)
		free((*sim)->dongle_mu);
	if ((*sim)->queue)
		request_destroy_queue(&(*sim)->queue);
	free(*sim);
	return (NULL);
}
