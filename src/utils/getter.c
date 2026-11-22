/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 05:52:28 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/20 06:24:09 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int	get_dongle_state(t_dongles *dongle)
{
	int	state;

	pthread_mutex_lock(&dongle->is_used_mu);
	state = dongle->is_used;
	pthread_mutex_unlock(&dongle->is_used_mu);
	return (state);
}

bool	get_can_compile(t_coder *coder)
{
	bool	value;

	pthread_mutex_lock(coder->can_compile_mu);
	value = *coder->can_compile;
	pthread_mutex_unlock(coder->can_compile_mu);
	return (value);
}

int	get_sim_state(int *state, pthread_mutex_t *state_mutex)
{
	int	status;

	pthread_mutex_lock(state_mutex);
	status = *state;
	pthread_mutex_unlock(state_mutex);
	return (status);
}

void	get_dongle_arr(size_t id, int params[8], int dongle[2])
{
	dongle[LEFT] = get_dongle_id(id, params[number_of_coders], LEFT);
	dongle[RIGHT] = get_dongle_id(id, params[number_of_coders], RIGHT);
	if (id == 2)
		assert(dongle[LEFT] == 1 && dongle[RIGHT] == 2);
}

int	get_dongle_id(int id, int number_of_coder, int type)
{
	if (type == RIGHT)
		return (id);
	if (type == LEFT)
	{
		if (id == 0)
			return (number_of_coder - 1);
		else
			return (id - 1);
	}
	return (-1);
}
