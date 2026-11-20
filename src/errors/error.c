/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 08:19:39 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/20 00:31:20 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"
#define BASE_16 "0123456789ABCDEF"

void	ft_putnbr_error(int fd, int nb, int base)
{
	long	n;
	char	c;

	n = nb;
	if (nb < 0)
	{
		write(fd, "-", 1);
		n = n * -1;
	}
	if (nb >= base)
		ft_putnbr_error(fd, nb / base, base);
	c = BASE_16[nb % base];
	write(fd, &c, 1);
}

int	parsing_error_msg(int code, char *arg)
{
	char	*msg;

	if (code == NB_ARG)
	{
		msg = HRED"Bad number of arguments"CRESET"\n";
		write(STDERR_FILENO, msg, strlen(msg));
	}
	if (code == BAD_ARG)
	{
		msg = HRED" is a bad argument"CRESET"\n";
		write(STDERR_FILENO, HRED, strlen(HRED));
		write(STDERR_FILENO, "'", 1);
		write(STDERR_FILENO, arg, strlen(arg));
		write(STDERR_FILENO, "'", 1);
		write(STDERR_FILENO, msg, strlen(msg));
		write(STDERR_FILENO, CRESET, strlen(CRESET));
	}
	return (false);
}

void	*err_msg(char *err)
{
	if (err)
		write(STDERR_FILENO, err, strlen(err));
	return (NULL);
}
