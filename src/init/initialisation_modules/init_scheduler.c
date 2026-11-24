/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scheduler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 09:22:08 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/24 02:34:44 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/codexion.h"

static void	*scheduler_error(t_scheduler **scheduler)
{
	free(*scheduler);
	*scheduler = NULL;
	return (err_msg("Error initilisation scheduler\n"));
}

static void	*scheduler_heap_error(t_scheduler **scheduler, size_t end)
{
	size_t	i;

	i = 0;
	while (i < end)
		free((*scheduler)->heaps[i++]);
	err_msg("Error initilisation heap scheduler\n");
	return (scheduler_error(scheduler));
}

static void	*get_arbitration_function(int arbitration)
{
	if (arbitration == FIFO)
		return (fifo);
	return (edf);
}

t_scheduler	*scheduler_init(t_sim *sim, int params[8])
{
	int			i;
	t_scheduler	*scheduler;

	if (!sim)
		return (NULL);
	scheduler = malloc(sizeof(t_scheduler));
	if (!scheduler)
		return (err_msg("Error initilisation scheduler\n"));
	scheduler->heaps = malloc(sizeof(t_heap *) * params[number_of_coders]);
	if (!scheduler->heaps)
		return (scheduler_error(&scheduler));
	i = 0;
	while (i < params[number_of_coders])
	{
		scheduler->heaps[i] = heap_init();
		if (!scheduler->heaps[i])
			return (scheduler_heap_error(&scheduler, i));
		i++;
	}
	scheduler->simulation_start = &sim->simulation_start;
	scheduler->queue = sim->queue;
	scheduler->sim_state = &sim->sim_state;
	scheduler->state_mu = sim->state_mu;
	scheduler->display_mu = sim->display_mu;
	scheduler->f = get_arbitration_function(params[arbitration]);
	ft_memcopy(params, scheduler->params, sizeof(int) * 8);
	return (scheduler);
}
