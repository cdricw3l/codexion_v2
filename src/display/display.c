/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 05:55:52 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/22 04:08:50 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	display_params(int params[8], int nb)
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
	uint64_t	now;
	uint64_t	time;

	now = get_now();
	time = (now - coder->simulation_start) / 1000000;
	if (!get_sim_state(coder->simulation_state, coder->simulation_state_mu))
		return ;
	pthread_mutex_lock(coder->display_mu);
	if (action == COMPILE)
	{
		printf("%ld %ld has taken dongle\n", time, coder->coder_id);
		printf("%ld %ld has taken dongle\n", time, coder->coder_id);
		printf("%ld %ld is compiling\n", time, coder->coder_id);
	}
	if (action == DEBUG)
		printf("%ld %ld is debugging\n", time, coder->coder_id);
	if (action == REFACTO)
		printf("%ld %ld is refactoring\n", time, coder->coder_id);
	if (action == BURNED)
		printf("%ld %ld burned out\n", time, coder->coder_id);
	if (action == END)
		printf("%ld %ld end of the simulation\n", time, coder->coder_id);
	pthread_mutex_unlock(coder->display_mu);
}
