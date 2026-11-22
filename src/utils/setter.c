/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 05:53:24 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/20 06:26:41 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	set_sim_state(int *state, pthread_mutex_t *state_mutex, int new_state)
{
	pthread_mutex_lock(state_mutex);
	*state = new_state;
	pthread_mutex_unlock(state_mutex);
}

void	set_dongle_state(t_dongles *dongle, int state)
{
	pthread_mutex_lock(&dongle->is_used_mu);
	dongle->is_used = state;
	pthread_mutex_unlock(&dongle->is_used_mu);
}

void	set_can_compile(t_coder *coder, bool value)
{
	pthread_mutex_lock(coder->can_compile_mu);
	*coder->can_compile = value;
	pthread_cond_signal(coder->can_compile_cond);
	pthread_mutex_unlock(coder->can_compile_mu);
}
