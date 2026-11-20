/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 10:44:15 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/19 20:48:41 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/codexion.h"

pthread_t	*threads_init(int nb)
{
	pthread_t	*thrd_coder;

	thrd_coder = malloc(sizeof(pthread_t) * nb);
	if (!thrd_coder)
		return (NULL);
	return (thrd_coder);
}

pthread_mutex_t	*init_dynamique_mutex(int nb)
{
	int				i;
	int				j;
	pthread_mutex_t	*mu;

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

pthread_cond_t	*init_dynamique_cond(int nb)
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

bool	*can_compile_init(int nb)
{
	bool	*can_compile;

	can_compile = malloc(sizeof(bool) * nb);
	if (!can_compile)
		return (NULL);
	memset(can_compile, false, sizeof(bool) * nb);
	return (can_compile);
}

time_t	*timestamp_init(int nb)
{
	time_t	*timestamp;

	timestamp = malloc(sizeof(uint64_t) * nb);
	if (!timestamp)
		return (NULL);
	memset(timestamp, 0, sizeof(uint64_t) * nb);
	return (timestamp);
}
