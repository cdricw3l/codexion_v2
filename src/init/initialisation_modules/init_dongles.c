/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dongles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 13:05:07 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/19 23:26:50 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/codexion.h"

void	*dongle_init_err(t_dongles *dongles, size_t idx)
{
	size_t	i;

	i = 0;
	while (i < idx)
	{
		pthread_mutex_destroy(&dongles[i].is_used_mu);
		i++;
	}
	free(dongles);
	return (err_msg("Erreur initialisation dongles\n"));
}

t_dongles	*dongle_init(t_sim *sim, int params[8])
{
	int			i;
	t_dongles	*dongles;

	if (!sim || !sim->dongle_mu)
		return (NULL);
	dongles = malloc(sizeof(t_dongles) * params[number_of_coders]);
	if (!dongles)
		return (err_msg("Error initialisation dongle\n"));
	i = 0;
	while (i < params[number_of_coders])
	{
		dongles[i].id = i;
		dongles[i].is_used = OFF;
		if (pthread_mutex_init(&(dongles[i].is_used_mu), NULL))
			return (dongle_init_err(dongles, i));
		dongles[i].dongle = &sim->dongle_mu[i];
		dongles[i].last_use = 0;
		i++;
	}
	return (dongles);
}
