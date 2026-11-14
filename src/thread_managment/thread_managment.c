/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_managment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 12:17:47 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/14 12:21:57 by cebouhad         ###   ########.fr       */
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
	return (TRUE);
}

int	launch_coders(t_sim *sim, t_coder *coders,
		void *(*routine)(void *), clock_t start)
{
	int	i;
	int	even_odd;

	even_odd = 0;
	while (even_odd < 2)
	{
		i = 0;
		while (i < sim->params[number_of_coders])
		{
			if (i % 2 == even_odd)
			{
				coders[i].simulation_start = start;
				set_timestamp(&coders[i]);
				if (pthread_create(&sim->thread[i], NULL, routine, &coders[i]))
				{
					err_msg("Error lauch thread coder\n");
					return (FALSE);
				}
			}
			i++;
		}
		even_odd++;
	}
	return (TRUE);
}
