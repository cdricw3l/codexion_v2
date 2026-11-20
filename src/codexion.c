/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 14:28:27 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/19 21:14:05 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

#define DISPLAY_PARAM FALSE

int	main(int argc, char **argv)
{
	t_data 			d;
	int				params[8];
	
	pthread_t		monitor_thread;
	pthread_t		scheduler_thread;

	if (!parse_arguments(&argv[1], params))
	{
		err_msg("Error parsinfg arguments\n");
		return (1);
	}
	#if DISPLAY_PARAM == TRUE
		printf("Mode debug activé : affichage des journaux.\n");
		display_params(params, argc - 1);
	#endif
	if(!initialisation(&d, params))
    {
        printf(BRED"Erreur d'initialisation"CRESET"\n");
        return(1) ;
    }
	// set_sim_state(&d.sim->simulation_state, d.sim->simulation_state_mu, ON);
	// assert(launch_coders(d.sim, d.coder, coder_routine));
	// assert(!pthread_create(&scheduler_thread, NULL, scheduler_routine, scheduler));
	// size_t z;

	// z = 0;
	// while (z < params[number_of_coders])
	// {
	// 	if (z % 2 == 0)
	// 	{
	// 		pthread_mutex_lock(coders[z].can_compile_mu);
	// 		*coders[z].can_compile = TRUE;
	// 		pthread_cond_signal(coders[z].can_compile_cond);
	// 		pthread_mutex_unlock(coders[z].can_compile_mu);
	// 	}
		

	// 	z++;
	// }
	// z = 0;
	// while (z < params[number_of_coders])
	// {
	// 	if (z % 2 != 0)
	// 	{
	// 		pthread_mutex_lock(d.coder[z].can_compile_mu);
	// 		*d.coder[z].can_compile = TRUE;
	// 		pthread_cond_signal(d.coders[z].can_compile_cond);
	// 		pthread_mutex_unlock(coders[z].can_compile_mu);
	// 	}
		

	// 	z++;
	// }
	// assert(!pthread_create(&monitor_thread, NULL, monitoring_routine, d.monitoring));
	// joint_coders(d.sim);
	// set_sim_state(&d.sim->simulation_state, d.sim->simulation_state_mu, OFF);
	// pthread_join(monitor_thread, NULL);
	// pthread_join(scheduler_thread, NULL);
	return (clear_data(&d,0));
}
