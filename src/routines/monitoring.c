/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 15:01:51 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/22 04:53:41 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	*monitoring_routine(void *data)
{
	int				i;
	t_monitoring	*monitor;
	uint64_t		last_compil;

	monitor = (t_monitoring *)data;
	while (1)
	{
		i = 0;
		while (i < monitor->params[number_of_coders])
		{
			last_compil = get_timestamp(monitor->coders[i].timestamp,
					monitor->coders[i].timestamp_mu);
			if ((get_now() - last_compil)
				>= monitor->params[time_to_burnout] * 1000000ULL)
			{
				set_sim_state(monitor->sim_state, monitor->state_mu, OFF);
				display_action(&monitor->coders[i], BURNED);
				return (NULL);
			}
			i++;
		}
		if (get_sim_state(monitor->sim_state, monitor->state_mu))
			return (NULL);
	}
	return (NULL);
}
