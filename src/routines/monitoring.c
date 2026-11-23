/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 15:01:51 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/23 09:33:13 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	*monitoring_routine(void *data)
{
	int				i;
	t_monitoring	*monitor;
	int64_t		last_compil;

	monitor = (t_monitoring *)data;
	while (1)
	{
		i = 0;
		while (get_sim_state(monitor->sim_state, monitor->state_mu) && i < monitor->params[number_of_coders])
		{
			last_compil = get_timestamp(monitor->coders[i].timestamp,
					monitor->coders[i].timestamp_mu);
			if ((get_now() - last_compil) >= (int64_t)(monitor->params[time_to_burnout] * 1000000))
			{
				if (last_compil != -1)
				{
					display_action(&monitor->coders[i], BURNED);
					set_sim_state(monitor->sim_state, monitor->state_mu, OFF);
				}
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
