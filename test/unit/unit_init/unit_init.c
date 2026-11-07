/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 21:07:31 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/07 14:48:56 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_init.h"

int unit_init(void)
{
	START_BLOCK;

	unit_sim_init();
	unit_dongle_init();
	unit_coder_init();
	return (TRUE);
}