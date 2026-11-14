/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:53:00 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/14 14:02:41 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

size_t	get_str_arr_len(char **str_arr)
{
	size_t	size;

	if (!str_arr)
		return (0);
	size = 0;
	while (*str_arr)
	{
		str_arr++;
		size++;
	}
	return (size);
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
	return (TRUE);
}

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

void	get_dongle_arr(size_t id, int params[8], int dongle[2])
{
	dongle[LEFT] = get_dongle_id(id, params[number_of_coders], LEFT);
	dongle[RIGHT] = get_dongle_id(id, params[number_of_coders], RIGHT);
	if (id == 2)
		assert(dongle[LEFT] == 1 && dongle[RIGHT] == 2);
}
