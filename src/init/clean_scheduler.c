/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_scheduler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 05:48:12 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/18 01:05:23 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	*scheduler_clean(t_scheduler **s)
{
	int			i;
	t_scheduler	*scheduler;

	scheduler = *s;
	i = 0;
	while (i < scheduler->params[number_of_coders])
		free(&scheduler->heaps[i++]);
	free(scheduler->heaps);
	free(*s);
	*s = NULL;
	return (NULL);
}
