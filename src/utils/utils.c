/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:53:00 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/24 11:34:12 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int	get_dongle_id(int id, int number_of_coder, int type)
{
	if (type == RIGHT)
		return (id);
	if (type == LEFT)
	{
		if (id == 0)
			return (number_of_coder - 1);
		else
			return (id - 1);
	}
	return (-1);
}

int	ft_is_digit(int c)
{
	return (c >= 48 && c <= 57);
}

int	ft_memcopy(void *src, void *dst, unsigned long size)
{
	unsigned long	i;

	i = 0;
	while (i < size)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (true);
}

bool	copy_request(t_request *request[2], t_scheduler *scheduler)
{
	t_request	*r1;
	t_request	*r2;

	r1 = request_pop(scheduler->queue);
	if (!r1)
		return (false);
	r2 = malloc(sizeof(t_request));
	if (!r2)
		return (false);
	*r2 = *r1;
	r2->next = NULL;
	request[0] = r1;
	request[1] = r2;
	return (true);
}
