/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:53:00 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/06 21:12:04 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

size_t ft_strlen(char *str)
{
	size_t len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

void *init_dyn_arr(int nb, int size)
{
	int *arr;

	arr = malloc(size * nb);
	if(!arr)
		return (NULL);
	memset(arr, 0, size * nb);
	return (arr);
}

int	max(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}

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

int	get_dongle(int id, int number_of_coder, int type)
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
