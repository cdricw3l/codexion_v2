/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_monitoring.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 08:38:56 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/22 04:47:03 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/codexion.h"

t_monitoring	*monitoring_init(t_sim *sim, t_coder *coders, int params[8])
{
	t_monitoring	*monitoring;

	if (!sim || !coders)
		return (NULL);
	monitoring = malloc(sizeof(t_monitoring));
	if (!monitoring)
		return (NULL);
	monitoring->timestamp = sim->timestamp;
	monitoring->timestamp_mu = sim->timestamp_mu;
	monitoring->simulation_state = &sim->simulation_state;
	monitoring->state_mu = sim->state_mu;
	monitoring->coders = coders;
	ft_memcopy(params, monitoring->params, sizeof(int) * 8);
	return (monitoring);
}
