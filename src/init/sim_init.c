/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 20:21:33 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/06 20:25:42 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

t_sim *sim_init(int params[8])
{
    t_sim *sim;

    sim = malloc(sizeof(sim));
    if (!sim)
    {
        return (err_msg(BRED"Error malloc init simulation\n"CRESET));
    }

}