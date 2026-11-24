/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 05:55:52 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/24 11:22:41 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	display_params(int params[8])
{
	printf(HBLU"[Number of philosopher]:"HYEL" %d\n", params[number_of_coders]);
	printf(HBLU"[Time to burnout]:"HYEL" %d ms\n", params[time_to_burnout]);
	printf(HBLU"[Time to compile]:"HYEL" %d ms\n", params[time_to_compile]);
	printf(HBLU"[Time to debug]:"HYEL" %d ms\n", params[time_to_debug]);
	printf(HBLU"[Time to refactor]:"HYEL" %d ms\n", params[time_to_refactor]);
	printf(HBLU"[Number of compiles required]:"HYEL" %d\n",
		params[number_of_compiles_required]);
	printf(HBLU"[Dongle cooldown]:"HYEL" %d ms\n", params[dongle_cooldown]);
	printf(HBLU"[scheduler]: "HYEL);
	if (params[arbitration] == FIFO)
		printf("fifo"CRESET"\n");
	else if (params[arbitration] == EDF)
		printf("edf"CRESET"\n");
	printf("\n");
}

void	display_action(t_coder *coder, int action)
{
	int64_t	now;
	int64_t	time;

	now = get_now();
	time = (now - *(coder->simulation_start)) / 1000000;
	if (!get_sim_state(coder->sim_state, coder->state_mu))
		return ;
	pthread_mutex_lock(coder->display_mu);
	if (action == COMPILE)
	{
		printf("%ld %ld has taken dongle\n", time, coder->coder_id + 1);
		printf("%ld %ld has taken dongle\n", time, coder->coder_id + 1);
		printf("%ld %ld is compiling\n", time, coder->coder_id + 1);
	}
	if (action == DEBUG)
		printf("%ld %ld is debugging\n", time, coder->coder_id + 1);
	if (action == REFACTO)
		printf("%ld %ld is refactoring\n", time, coder->coder_id + 1);
	pthread_mutex_unlock(coder->display_mu);
}

void	display_timestamp(pthread_mutex_t *mu_display, int64_t *start)
{
	pthread_mutex_lock(mu_display);
	printf("Timestamp -> %ld\n", (get_now() - *start) / 1000000);
	pthread_mutex_unlock(mu_display);
}
