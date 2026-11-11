/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_monitoring.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 08:38:56 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/08 14:18:29 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

t_monitoring	*monitoring_init(int params[8], t_sim *sim)
{
	t_monitoring	*monitoring;

	if (!sim)
		return (NULL);
	monitoring = malloc(sizeof(t_monitoring));
	if (!monitoring)
		return (NULL);
	monitoring->simulation_state = &sim->simulation_state;
	monitoring->simulation_state_mu = sim->simulation_state_mu;
	monitoring->timestamp = sim->timestamp;
	monitoring->timestamp_mu = sim->timestamp_mu;
	ft_memcopy(params, monitoring->params, sizeof(int) * 8);
	return (monitoring);
}
