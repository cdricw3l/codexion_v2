/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 12:54:28 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/02 17:23:40 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

size_t	ft_strlen(char *str)
{
	size_t len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
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
	if (!dst)
		return (ERR);
	if (!src && size)
		return (ERR);
	while (i < size)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (OK);
}