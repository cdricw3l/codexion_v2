/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_thread.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 12:17:47 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/19 20:53:35 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

/*
	sim->thread[0] = scheduler thread;
	sim->thread[1] = monitoring thread;
	sim->thread[2 -> n_coder] = monitoring thread;
*/





int launch_monitor(t_sim *sim, t_monitoring *monitor)
{
	if (pthread_create(&sim->thread[1], NULL, monitoring_routine, monitor))
	{
		err_msg("Error lauch thread monitor\n");
		return (false);
	}
	return (true);
}

int launch_scheduler(t_sim *sim, t_scheduler *scheduler)
{
	if (pthread_create(&sim->thread[0], NULL, scheduler_routine, scheduler))
	{
		err_msg("Error lauch thread scheduler\n");
		return (false);
	}
	return (true);
}

int	launch_coders(t_sim *sim, t_coder *coders)
{
	int			i;
	uint64_t	start;

	i = 2;
	start = get_now();
	while (i < sim->params[number_of_coders] + 2)
	{
		coders[i - 2].simulation_start = start;
		set_timestamp(&coders[i - 2]);
		if (pthread_create(&sim->thread[i], NULL, coder_routine, &coders[i - 2]))
		{
			err_msg("Error lauch thread coder\n");
			return (false);
		}
		i++;
	}
	#if DEBBUG_MODE == true
		printf("All coder are launched\n");
	#endif
	return (true);
}
