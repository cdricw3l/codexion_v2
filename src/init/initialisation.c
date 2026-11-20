/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 18:23:26 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/19 22:59:47 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialisation.h"

int	clear_data(t_data *d, int code)
{
	if (!d)
		return (ERR);
	if (d->sim)
		clean_sim(&d->sim);
	if (d->dongles)
		free(d->dongles);
	if (d->coder)
		free(d->coder);
	if (d->scheduler)
		clean_scheduler(&d->scheduler);
	if (d->monitoring)
		free(d->monitoring);
	return (code);
}

int	initialisation(t_data *d, int params[8])
{
	memset(d, 0, sizeof(t_data));
	d->sim = sim_init(params);
	if (!d->sim)
		return (ERR);
	d->dongles = dongle_init(d->sim, params);
	if (!d->dongles)
		return (clear_data(d, ERR));
	d->coder = coders_init(d->sim, d->dongles, params);
	if (!d->coder)
		return (clear_data(d, ERR));
	d->scheduler = scheduler_init(d->sim, params);
	if (!d->scheduler)
		return (clear_data(d, ERR));
	d->monitoring = monitoring_init(d->sim, d->coder, params);
	if (!d->monitoring)
		return (clear_data(d, ERR));
	return (OK);
}
