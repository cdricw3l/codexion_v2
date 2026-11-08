/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_clean.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 05:48:12 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/08 05:55:20 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void *scheduler_clean(t_scheduler **s)
{
    t_scheduler *scheduler;
    size_t i;

    scheduler = *s;
    i = 0;
    while (i < scheduler->params[number_of_coders])
        free(scheduler->heaps[i++]);
    free(scheduler->heaps);
    free(*s);
    *s = NULL;
    return(NULL);
}