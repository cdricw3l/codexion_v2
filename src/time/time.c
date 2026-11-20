/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 08:07:31 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/20 01:14:41 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

/*
	second_to_nano = sec * 1000000000
	ms_to_nano = ms * 1000000
	nano_to_ms = ms / 1000000
*/

struct timespec	time_diff(struct timespec start, struct timespec end)
{
	struct timespec	temp;

	if ((end.tv_nsec - start.tv_nsec) < 0)
	{
		temp.tv_sec = end.tv_sec - start.tv_sec - 1;
		temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
	}
	else
	{
		temp.tv_sec = end.tv_sec - start.tv_sec;
		temp.tv_nsec = end.tv_nsec - start.tv_nsec;
	}
	return (temp);
}

uint64_t	time_calculation(struct timespec time)
{
	uint64_t	n_to_sec;

	n_to_sec = time.tv_sec * 1000000000;
	return ((n_to_sec + time.tv_nsec) / 1000000);
}

/**
 * set the timestamp of the last compilation in nano second
 */
void	set_timestamp(t_coder *coder)
{
	struct timespec	now;

	clock_gettime(CLOCK_MONOTONIC, &now);
	pthread_mutex_lock(coder->timestamp_mu);
	*(coder->timestamp) = (now.tv_nsec + (now.tv_sec * 1000000000));
	pthread_mutex_unlock(coder->timestamp_mu);
}

/**
 * get the timestamp of the last compilation in nano second
 */
uint64_t	get_timestamp(uint64_t *timestamp, pthread_mutex_t *timestamp_mu)
{
	uint64_t	time;

	pthread_mutex_lock(timestamp_mu);
	time = *timestamp;
	pthread_mutex_unlock(timestamp_mu);
	return (time);
}

uint64_t	get_now(void)
{
	struct timespec	n;
	uint64_t		now;

	clock_gettime(CLOCK_MONOTONIC, &n);
	now = n.tv_nsec + (n.tv_sec * 1000000000);
	return (now);
}
