/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_monitoring.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 08:38:56 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/11 20:51:09 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

t_monitoring	*monitoring_init(int params[8], t_sim *sim, t_coder *coders)
{
	t_monitoring	*monitoring;

	if (!sim || !coders)
		return (NULL);
	monitoring = malloc(sizeof(t_monitoring));
	if (!monitoring)
		return (NULL);
	monitoring->simulation_state = &sim->simulation_state;
	monitoring->simulation_state_mu = sim->simulation_state_mu;
	monitoring->coders = coders;
	ft_memcopy(params, monitoring->params, sizeof(int) * 8);
	return (monitoring);
}
