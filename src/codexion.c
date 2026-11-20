/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 14:28:27 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/20 01:06:04 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"


void coder_activation(t_coder *coders)
{
	int i;
	int nb;
	int even_odd;

	i = 0;
	nb = coders[0].params[number_of_coders];
	even_odd = 0;
	while (even_odd < 2)
	{
		i = 0;
		while (i < coders->params[number_of_coders])
		{
			if (i % 2 == even_odd)
			{
				set_can_compile(&coders[i], true);
				#if DEBBUG_MODE == true
						printf("Coder %ld is ON %ld\n", coders->coder_id);
				#endif
			}
			i++;
		}
		even_odd++;
	}
}

bool start_simulation(t_data *d)
{
	t_sim *sim;
	t_coder *coder;
	t_scheduler *scheduler;
	t_monitoring *monitoring;
	
	sim = d->sim;
	coder = d->coder;
	scheduler = d->scheduler;
	monitoring = d->monitoring;
	set_sim_state(&sim->simulation_state, sim->simulation_state_mu, ON);
	if (!launch_coders(sim, coder))
		return (false);
	if (!launch_scheduler(sim, scheduler))
		return (false);
	coder_activation(coder);
	if (!launch_monitor(sim, monitoring))
		return (false);
	joint_thread(sim);
	return (true);
}

int	main(int argc, char **argv)
{
	t_data 			d;
	int				params[8];

	if (!parse_arguments(&argv[1], params))
	{
		err_msg("Error parsing arguments\n");
		return (1);
	}
	#if DEBBUG_MODE == true
		printf("Mode debug activé : affichage des parametres.\n");
		display_params(params, argc - 1);
	#endif
	if(!initialisation(&d, params))
    {
        printf(BRED"Erreur d'initialisation"CRESET"\n");
        return(1) ;
    }
	start_simulation(&d);
	// joint_coders(d.sim);
	// set_sim_state(&d.sim->simulation_state, d.sim->simulation_state_mu, OFF);
	// pthread_join(monitor_thread, NULL);
	// pthread_join(scheduler_thread, NULL);
	
	return (clear_data(&d,0));
}
