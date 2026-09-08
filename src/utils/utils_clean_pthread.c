/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_clean_pthread.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 15:36:39 by cdric.b           #+#    #+#             */
/*   Updated: 2026/09/03 13:32:04 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int clean_dynamique_mutex(pthread_mutex_t **mutex, int nb)
{
    int i;
    pthread_mutex_t *mu;
    int err;

    i = 0;
    err = TRUE;
    mu = *mutex;
    while (i < nb)
    {
        if(pthread_mutex_destroy(&mu[i]))
        {
            write(STDERR_FILENO,"Error destruction mutext Nb: ", strlen("Error destruction mutext Nb: "));
            ft_putnbr_error(STDERR_FILENO,i, 10);
            write(STDERR_FILENO, "\n", 1);
            err = FALSE;
        }
        i++;
    }
    free(*mutex);
    *mutex = NULL;
    return (err);
}

int clean_dynamique_cond(pthread_cond_t **cond, int nb)
{
    int i;
    int err;
    pthread_cond_t *co;

    i = 0;
    err = TRUE;
    co = *cond;
    while (i < nb)
    {
        if(pthread_cond_destroy(&co[i]))
        {
            write(STDERR_FILENO,"Error destruction cond Nb: ", strlen("Error destruction mutext Nb: "));
            ft_putnbr_error(STDERR_FILENO,i, 10);
            write(STDERR_FILENO, "\n", 1);
            err = FALSE;
        }
        i++;
    }
    free(*cond);
    *cond = NULL;
    return (err);
}