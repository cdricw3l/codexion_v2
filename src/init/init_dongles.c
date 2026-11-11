/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dongles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 13:05:07 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/08 14:17:48 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

t_dongles	*dongle_init(int nb, t_sim *sim)
{
	int			i;
	t_dongles	*dongles;

	if (!sim || !sim->dongle_mu)
		return (NULL);
	dongles = malloc(sizeof(t_dongles) * nb);
	if (!dongles)
		return (err_msg("Error initialisation dongle\n"));
	i = 0;
	while (i < nb)
	{
		dongles[i].id = i;
		dongles[i].dongle = &sim->dongle_mu[i];
		dongles[i].last_use = 0;
		i++;
	}
	return (dongles);
}
