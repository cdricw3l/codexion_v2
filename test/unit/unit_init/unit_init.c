/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 21:07:31 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/19 21:39:57 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_init.h"

int unit_initialisation(void)
{
	START_BLOCK;
	unit_sim_init();
	unit_dongle_init();
	unit_coder_init();
	unit_scheduler_init();
	unit_monitoring_init();
	return (TRUE);
}