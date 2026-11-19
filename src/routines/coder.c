/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 12:48:06 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/18 23:52:30 by cebouhad         ###   ########.fr       */
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
	//printf("Coder %ld: before right lock\n", coder->coder_id);
	pthread_mutex_lock(coder->dongle_right->dongle);

	//printf("Coder %ld: before left lock\n", coder->coder_id);
	pthread_mutex_lock(coder->dongle_left->dongle);

	//printf("Coder %ld: both dongles acquired\n", coder->coder_id);
	display_action(coder, COMPILE);
	action(coder, COMPILE);
	pthread_mutex_unlock(coder->dongle_right->dongle);
	pthread_mutex_unlock(coder->dongle_left->dongle);
	*coder->can_compile = FALSE;
	pthread_mutex_unlock(coder->can_compile_mu);
	display_action(coder, DEBUG);
	action(coder, DEBUG);
	display_action(coder, REFACTO);
	action(coder, REFACTO);
}

static int	create_and_push_request(t_coder *coder)
{
	return (request_push(coder));
}

void	*coder_routine(void *data)
{
	int			i;
	t_coder		*coder;

	coder = (t_coder *)data;
	i = 0;
	while (i < coder->params[number_of_compiles_required]
		&& get_sim_state(coder->simulation_state, coder->simulation_state_mu))
	{
		if (!create_and_push_request(coder))
		{
			set_sim_state(coder->simulation_state,
				coder->simulation_state_mu, OFF);
			return (NULL);
		}
		pthread_mutex_lock(coder->can_compile_mu);
		while (get_sim_state(coder->simulation_state, coder->simulation_state_mu) && *coder->can_compile == FALSE)
		{	
			pthread_cond_wait(coder->can_compile_cond, coder->can_compile_mu);
		}
		*coder->can_compile = FALSE;

		/* if a coder burn, the scheduler send signal to all the coder. We dont want to display action, We want to stop the simulation */
		if (get_sim_state(coder->simulation_state, coder->simulation_state_mu))
		{
			//printf("Coder %ld: entering action\n", coder->coder_id);
			coder_action(coder);
		}
		else
		{
			pthread_mutex_unlock(coder->can_compile_mu);
			return (NULL);
		}
		i++;
	}
	return (NULL);
}
