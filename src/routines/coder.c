/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 12:48:06 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/11 23:39:14 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static void	coder_action(t_coder *coder)
{
	display_action(coder, TAKE);
	set_timestamp(coder);
	usleep(coder->params[time_to_compile]);
	display_action(coder, DEBUG);
	usleep(coder->params[time_to_debug]);
	display_action(coder, REFACTO);
	usleep(coder->params[time_to_debug]);
}

static int	create_and_push_request(t_coder *coder)
{
	t_request	*request;

	request = request_new_node(coder);
	if (!request)
		return (FALSE);
	if (request_push(coder->queue, request))
		return (TRUE);
	free(request);
	return (FALSE);
}

void	*coder_routine(void *data)
{
	size_t		i;
	t_coder		*coder;

	coder = (t_coder *)data;
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
			pthread_cond_wait(coder->can_compile_cond, coder->can_compile_mu);
		
	}
	return (NULL);
}

int launch_coders(t_sim *sim, t_coder *coders,  void *(*routine)(void *), int mode)
{
	size_t i;

	i = 0;
	while (i < sim->params[number_of_coders])
	{
		if (i % 2 == mode)
		{
			if (pthread_create(&sim->thread[i], NULL, routine, &coders[i]))
			{
				err_msg("Error lauch thread coder\n");
				return (FALSE);
			}
			i++;
		}
	}
	return (TRUE);
}
int joint_coders(t_sim *sim)
{
	size_t i;

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
		usleep(coder->params[time_to_compile] * 1000);
    if (action == DEBUG)
        usleep(coder->params[time_to_debug] * 1000);
    if (action == REFACTO)
        usleep(coder->params[time_to_refactor] * 1000);
}