/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:53:00 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/11 06:07:22 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int get_sim_state(int *state, pthread_mutex_t *state_mutex)
{
    int status;

    pthread_mutex_lock(state_mutex);
    status = *state;
    pthread_mutex_unlock(state_mutex);
    return (status);
}

void set_sim_state(int *state, pthread_mutex_t *state_mutex, int new_state)
{
    pthread_mutex_lock(state_mutex);
    *state = new_state;
    pthread_mutex_unlock(state_mutex);
}