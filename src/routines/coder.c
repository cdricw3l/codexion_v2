/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 12:48:06 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/12 23:03:32 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"



static void	coder_action(t_coder *coder)
{
	assert(!pthread_mutex_lock(coder->dongle_right->dongle));
	assert(!pthread_mutex_lock(coder->dongle_left->dongle));
	display_action(coder, COMPILE);
	action(coder, COMPILE);
	assert(!pthread_mutex_unlock(coder->dongle_right->dongle));
	assert(!pthread_mutex_unlock(coder->dongle_left->dongle));
	*coder->can_compile = FALSE;
	pthread_mutex_unlock(coder->can_compile_mu);
	display_action(coder, DEBUG);
	action(coder, DEBUG);
	display_action(coder, REFACTO);
	action(coder, REFACTO);
}

static int	create_and_push_request(t_coder *coder)
{
	t_request	*request;

	request = request_new_node(coder);
	if (!request)
		return (FALSE);
	return (TRUE);
}

void	*coder_routine(void *data)
{
	int			i;
	t_coder		*coder;

	coder = (t_coder *)data;
	i = 0;
	
	while (i < coder->params[number_of_compiles_required]
		&& get_sim_state(coder->simulation_state,coder->simulation_state_mu))
	{
		if (!create_and_push_request(coder))
		{
			set_sim_state(coder->simulation_state,
				coder->simulation_state_mu, OFF);
			return (NULL);
		}
		pthread_mutex_lock(coder->can_compile_mu);
		while (*coder->can_compile == FALSE)
		{
			printf("coder %ld is waiting\n", coder->coder_id);
			pthread_cond_wait(coder->can_compile_cond, coder->can_compile_mu);
		}
		coder_action(coder);
		i++;
	}
	return (NULL);
}

int launch_coders(t_sim *sim, t_coder *coders,  void *(*routine)(void *), clock_t start)
{
	int i;

	i = 0;
	while (i < sim->params[number_of_coders])
	{
		if (i % 2 == 0)
		{
			coders[i].simulation_start = start;
			set_timestamp(&coders[i]);
			if (pthread_create(&sim->thread[i], NULL, routine, &coders[i]))
			{
				err_msg("Error lauch thread coder\n");
				return (FALSE);
			}
		}
		i++;

	}
	i = 0;
	while (i < sim->params[number_of_coders])
	{
		
		if (i % 2 != 0)
		{
			coders[i].simulation_start = start;
			set_timestamp(&coders[i]);
			if (pthread_create(&sim->thread[i], NULL, routine, &coders[i]))
			{
				err_msg("Error lauch thread coder\n");
				return (FALSE);
			}
		}
		i++;

	}
	
	return (TRUE);
}
int joint_coders(t_sim *sim)
{
	int i;

	i = 0;
	while (i < sim->params[number_of_coders])
	{
		if (pthread_join(sim->thread[i], NULL))
		{
			err_msg("Error join thread coder\n");
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
void action(t_coder *coder, int action)
{
	if (action == COMPILE)
	{
		usleep(coder->params[time_to_compile] * 1000);
        set_timestamp(coder);
	}
    if (action == DEBUG)
        usleep(coder->params[time_to_debug] * 1000);
    if (action == REFACTO)
        usleep(coder->params[time_to_refactor] * 1000);
}