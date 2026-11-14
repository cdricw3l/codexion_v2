/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 14:28:27 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/14 15:15:57 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

#define DISPLAY_PARAM TRUE

int	main(int argc, char **argv)
{
	int				params[8];
	t_sim			*sim;
	t_dongles		*dongles;
	t_coder			*coders;
	t_scheduler		*scheduler;
	t_monitoring	*monitoring;
	clock_t			start;
	pthread_t		monitor_thread;
	pthread_t		scheduler_thread;

	if (!parse_arguments(&argv[1], params))
	{
		err_msg("Error parsinfg arguments\n");
		return (1);
	}
	if (DISPLAY_PARAM)
		display_params(params, argc - 1);
	sim = sim_init(params);
	if (!sim)
		return (1);
	dongles = dongle_init(params, sim);
	if (!dongles)
	{
		sim_clean(&sim);
		return (1);
	}
	coders = coders_init(params, sim, dongles);
	if (!coders)
	{
		sim_clean(&sim);
		free(dongles);
		return (1);
	}
	scheduler = scheduler_init(params, sim);
	if (!scheduler)
	{
		sim_clean(&sim);
		free(dongles);
		free(coders);
		return (1);
	}
	monitoring = monitoring_init(params, sim, coders);
	if (!monitoring)
	{
		sim_clean(&sim);
		free(dongles);
		free(coders);
		scheduler_clean(&scheduler);
		return (1);
	}
	start = get_now();
	set_sim_state(&sim->simulation_state, sim->simulation_state_mu, ON);
	assert(launch_coders(sim, coders, coder_routine, start));
	assert(!pthread_create(&scheduler_thread, NULL, scheduler_routine, scheduler));
	assert(!pthread_create(&monitor_thread, NULL, monitoring_routine, monitoring));
	joint_coders(sim);
	set_sim_state(&sim->simulation_state, sim->simulation_state_mu, OFF);
	pthread_join(scheduler_thread, NULL);
	pthread_join(monitor_thread, NULL);
	sim_clean(&sim);
	free(dongles);
	free(coders);
	free(monitoring);
	scheduler_clean(&scheduler);
	return (0);
}
