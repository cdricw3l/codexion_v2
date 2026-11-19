/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 15:01:51 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/19 00:27:18 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	*monitoring_routine(void *data)
{
	t_monitoring	*monitor;
	uint64_t			last_compil;
	int				i;

	monitor = (t_monitoring *)data;
	while (get_sim_state(monitor->simulation_state,
			monitor->simulation_state_mu) == ON)
	{
		i = 0;
		while (i < monitor->params[number_of_coders])
		{
			last_compil = get_timestamp(monitor->coders[i].timestamp,
					monitor->coders[i].timestamp_mu);
			if ((get_now() - last_compil) / 1000000
				> monitor->params[time_to_burnout])
			{
				display_action(&monitor->coders[i], BURNED);
				set_sim_state(monitor->simulation_state,
					monitor->simulation_state_mu, OFF);
				return (NULL);
			}
			usleep(10000);
			i++;
		}
	}
	return (NULL);
}
