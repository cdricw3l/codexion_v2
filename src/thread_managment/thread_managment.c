/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_managment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 12:17:47 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/19 03:23:46 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int	joint_coders(t_sim *sim)
{
	int	i;

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
	printf("All coder are joined\n");
	return (TRUE);
}

int	launch_coders(t_sim *sim, t_coder *coders,
		void *(*routine)(void *), uint64_t start)
{
	int	i;
	
	i = 0;
	while (i < sim->params[number_of_coders])
	{
		coders[i].simulation_start = start;
		set_timestamp(&coders[i]);
		if (pthread_create(&sim->thread[i], NULL, routine, &coders[i]))
		{
			err_msg("Error lauch thread coder\n");
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
