/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 12:48:06 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/22 00:24:23 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static void	action(t_coder *coder, int action)
{
	if (action == COMPILE)
	{
		set_timestamp(coder);
		usleep(coder->params[time_to_compile] * 1000);
	}
	if (action == DEBUG)
		usleep(coder->params[time_to_debug] * 1000);
	if (action == REFACTO)
		usleep(coder->params[time_to_refactor] * 1000);
}



static void	coder_action(t_coder *coder)
{
	pthread_mutex_lock(coder->dongle_right->dongle);
	coder->dongle_right->is_used = true;
	pthread_mutex_lock(coder->dongle_left->dongle);
	coder->dongle_left->is_used = true;
	
	
	display_action(coder, COMPILE);
	action(coder, COMPILE);
	
	coder->dongle_right->is_used = false;
	pthread_mutex_unlock(coder->dongle_right->dongle);
	coder->dongle_left->is_used = false;
	pthread_mutex_unlock(coder->dongle_left->dongle);
	
	display_action(coder, DEBUG);
	action(coder, DEBUG);
	display_action(coder, REFACTO);
	action(coder, REFACTO);
}

static void wait(t_coder *coder)
{
	pthread_mutex_lock(coder->can_compile_mu);
	while (*coder->can_compile == false)
		pthread_cond_wait(coder->can_compile_cond, coder->can_compile_mu);
	pthread_mutex_unlock(coder->can_compile_mu);
}

void	*coder_routine(void *data)
{
	int			i;
	int 		nb_of_compile;
	t_coder		*coder;

	coder = (t_coder *)data;
	
	i = 0;
	nb_of_compile = 0;
	wait(coder);
	while (i < coder->params[number_of_compiles_required]
		&& get_sim_state(coder->simulation_state, coder->simulation_state_mu))
	{
		if (!request_push(coder))
		{
			set_sim_state(coder->simulation_state,
				coder->simulation_state_mu, OFF);
			return (NULL);
		}
		pthread_mutex_lock(coder->can_compile_mu);
		while (get_sim_state(coder->simulation_state, coder->simulation_state_mu) && *coder->can_compile == false)
			pthread_cond_wait(coder->can_compile_cond, coder->can_compile_mu);
		/* if a coder burn, the scheduler send signal to all the coder. We dont want to display action, We want to stop the simulation */
		if (get_sim_state(coder->simulation_state, coder->simulation_state_mu))
		{
			//printf("Coder %ld: entering action\n", coder->coder_id);
			coder_action(coder);
			*coder->can_compile = false;
			pthread_mutex_unlock(coder->can_compile_mu);
		}
		else
		{
			pthread_mutex_unlock(coder->can_compile_mu);
			return (NULL);
		}
		i++;
		nb_of_compile++;
	}
	assert(nb_of_compile == coder->params[number_of_compiles_required]);
	return (NULL);
}
