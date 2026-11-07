/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_clean_pthread.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 15:36:39 by cdric.b           #+#    #+#             */
/*   Updated: 2026/11/06 21:15:02 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void *clean_dynamique_mutex(pthread_mutex_t **mutex, int nb)
{
    int i;
    pthread_mutex_t *mu;

    i = 0;
    mu = *mutex;
    while (i < nb)
    {
        if(pthread_mutex_destroy(&mu[i]))
            write(STDERR_FILENO,"Error destruction mutext\n", strlen("Error destruction mutext\n"));
        i++;
    }
    free(*mutex);
    *mutex = NULL;
    return (NULL);
}

void *clean_dynamique_cond(pthread_cond_t **cond, int nb)
{
    int i;
    int err;
    pthread_cond_t *co;

    i = 0;
    co = *cond;
    while (i < nb)
    {
        if(pthread_cond_destroy(&co[i]))
            write(STDERR_FILENO,"Error destruction cond Nb: ", strlen("Error destruction cond Nb: "));
        i++;
    }
    free(*cond);
    *cond = NULL;
    return (NULL);
}

void *clean_sim(t_sim **s)
{
    t_sim *sim;

    sim = *s;
    if (sim->can_compile)
        free(sim->can_compile);
    if (sim->can_compile_cond)
        free(sim->can_compile_cond);
    if (sim->can_compile_mu)
        free(sim->can_compile_mu);
    if (sim->display_mu)
        free(sim->display_mu);
    if (sim->request_queue_mu)
        free(sim->request_queue_mu);
    if (sim->timestamp)
        free(sim->timestamp);
    if (sim->timestamp_mu)
        free(sim->timestamp_mu);
    free(*s);
    return(NULL);
}