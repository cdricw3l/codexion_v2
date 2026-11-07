/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_init_sim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 21:08:14 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/06 21:15:29 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../unit.h"

void unit_init_sim(void)
{
    START_TEST;
    t_sim *sim;
    int params[8];  

    params[number_of_coders] = 8;
    sim = sim_init(params);
    printf(BGRN"INITIALISATION OK"CRESET"\n");
    clean_sim(&sim);
    END_TEST;
}