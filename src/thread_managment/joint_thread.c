/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joint_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 01:01:42 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/22 04:00:51 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static int	joint_coders(t_sim *sim)
{
	int	i;

	i = CODERS_THREAD_START;
	while (i < sim->params[number_of_coders] + 2)
	{
		if (pthread_join(sim->thread[i], NULL))
		{
			err_msg("Error join thread coder\n");
			return (false);
		}
		i++;
	}
	printf("All coder are joined\n");
	return (true);
}

void	joint_thread(t_sim *sim)
{
	joint_coders(sim);
	set_sim_state(&sim->simulation_state, sim->simulation_state_mu, OFF);
	pthread_join(sim->thread[SCHEDULER_THREAD], NULL);
	pthread_join(sim->thread[MONITOR_THREAD], NULL);
}
