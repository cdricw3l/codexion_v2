/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 05:52:28 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/24 11:34:15 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int64_t	get_last_use(t_dongles *dongle)
{
	int64_t	last_used;

	pthread_mutex_lock(&dongle->last_use_mu);
	last_used = dongle->last_use;
	pthread_mutex_unlock(&dongle->last_use_mu);
	return (last_used);
}

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
