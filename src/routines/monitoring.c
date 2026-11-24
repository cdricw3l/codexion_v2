/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 15:01:51 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/24 10:31:17 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	*monitoring_routine(void *data)
{
	int				i;
	t_monitoring	*monitor;
	int64_t			last_compil;
	int64_t			now;

	monitor = (t_monitoring *)data;
	while (1)
	{
		i = 0;
		while (i < monitor->params[number_of_coders])
		{
			last_compil = get_compilation_timestamp(monitor->coders[i].timestamp,
					monitor->coders[i].timestamp_mu);
			now = get_now();
			if ((now - last_compil) > (int64_t)(monitor->params[time_to_burnout] * 1000000))
			{
				if (last_compil != -1)
				{
					pthread_mutex_lock(monitor->coders[i].display_mu);
					printf("%ld %ld burned out\n", (now - *(monitor->coders[i].simulation_start)) / 1000000, monitor->coders[i].coder_id + 1);
					pthread_mutex_unlock(monitor->coders[i].display_mu);
					set_sim_state(monitor->sim_state, monitor->state_mu, OFF);
				}
				return (NULL);
			}
			usleep(500);
			i++;
		}
	}
	return (NULL);
}
