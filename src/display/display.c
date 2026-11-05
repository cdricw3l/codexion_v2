/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 05:55:52 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/05 12:47:21 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void display_params(int params[8], int nb)
{
    printf(HBLU"[Number of philosopher]:"HYEL" %d\n", nb);
    printf(HBLU"[Time to burnout]:"HYEL" %d ms\n", params[time_to_burnout]);
    printf(HBLU"[Time to compile]:"HYEL" %d ms\n", params[time_to_compile]);
    printf(HBLU"[Time to debug]:"HYEL" %d ms\n", params[time_to_debug]);
    printf(HBLU"[Time to refactor]:"HYEL" %d ms\n", params[time_to_refactor]);
    printf(HBLU"[Number of compiles required]:"HYEL" %d\n", params[number_of_compiles_required]);
    printf(HBLU"[Dongle cooldown]:"HYEL" %d ms\n", params[dongle_cooldown]);
    printf(HBLU"[scheduler]: "HYEL);
    if (params[scheduler] == FIFO)
        printf("fifo"CRESET"\n");
    else if (params[scheduler] == EDF)
        printf("edf"CRESET"\n");
    printf("\n");
}