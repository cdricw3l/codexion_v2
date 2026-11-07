/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 20:21:33 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/07 18:10:45 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static pthread_t	*threads_init(int nb)
{
	pthread_t	*thrd_coder;

	thrd_coder = malloc(sizeof(pthread_t) * nb);
	if (!thrd_coder)
		return (NULL);
	return (thrd_coder);
}


static pthread_mutex_t	*init_dynamique_mutex(int nb)
{
	pthread_mutex_t	*mu;
	int				i;
	int				j;

	mu = malloc(sizeof(pthread_mutex_t) * nb);
	if (!mu)
		return (NULL);
	i = 0;
	while (i < nb)
	{
		if (pthread_mutex_init(&mu[i], NULL))
		{
			j = 0;
			while (j < i)
				pthread_mutex_destroy(&mu[j++]);
			free(mu);
			return (NULL);
		}
		i++;
	}
	return (mu);
}

static pthread_cond_t	*init_dynamique_cond(int nb)
{
	pthread_cond_t	*cond;
	int				i;
	int				j;

	cond = malloc(sizeof(pthread_cond_t) * nb);
	if (!cond)
		return (NULL);
	i = 0;
	while (i < nb)
	{
		if (pthread_cond_init(&cond[i], NULL))
		{
			j = 0;
			while (j < i)
				pthread_cond_destroy(&cond[j++]);
			free(cond);
			return (NULL);
		}
		i++;
	}
	return (cond);
}


static bool *can_compile_init(int nb)
{
    bool *can_compile;

    can_compile = malloc(sizeof(bool) * nb);
    if (!can_compile)
        return (NULL);
    memset(can_compile, false, sizeof(bool) * nb);
    return (can_compile);
}

static time_t *timestamp_init(int nb)
{
    time_t *timestamp;

    timestamp = malloc(sizeof(time_t) * nb);
    if (!timestamp)
        return (NULL);
    memset(timestamp, 0, sizeof(time_t) * nb);
    return (timestamp);
}

t_sim *sim_init(int params[8])
{
    t_sim *sim;

    sim = malloc(sizeof(t_sim));
    memset(sim, 0, sizeof(t_sim));
    if (!sim)
        return (err_msg(BRED"Error malloc init simulation\n"CRESET));
	sim->thread = threads_init(params[number_of_coders]);
	if (!sim->thread)
		return (clean_sim(&sim));
    sim->can_compile_cond = init_dynamique_cond(params[number_of_coders]);
    if (!sim->can_compile_cond)
        return (clean_sim(&sim));
    sim->can_compile_mu = init_dynamique_mutex(params[number_of_coders]);
    if (!sim->can_compile_mu)
        return (clean_sim(&sim));
	sim->can_compile = can_compile_init(params[number_of_coders]);
    if (!sim->can_compile)
        return (clean_sim(&sim));
    sim->timestamp_mu = init_dynamique_mutex(params[number_of_coders]);
    if (!sim->timestamp_mu)
        return (clean_sim(&sim));
	sim->timestamp = timestamp_init(params[number_of_coders]);
    if (!sim->timestamp)
        return (clean_sim(&sim));
    sim->dongle_mu = init_dynamique_mutex(params[number_of_coders]);
    if (!sim->dongle_mu)
        return (clean_sim(&sim));
    sim->display_mu = init_dynamique_mutex(1);
    if (!sim->display_mu)
        return (clean_sim(&sim));
    sim->request_queue_mu = init_dynamique_mutex(1);
    if (!sim->request_queue_mu)
        return (clean_sim(&sim));
    sim->simulation_state_mu = init_dynamique_mutex(1);
    if (!sim->simulation_state_mu)
        return (clean_sim(&sim));
	sim->queue = request_queue_init();
	if (!sim->queue)
		return (clean_sim(&sim));
	sim->simulation_state = OFF;
    return (sim);
}
