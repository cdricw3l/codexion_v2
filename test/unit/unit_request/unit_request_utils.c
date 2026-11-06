/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_request_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 05:27:38 by cebouhad          #+#    #+#             */
/*   Updated: 2026/11/06 07:05:34 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unit_request.h"

t_coder *get_coder(size_t id, t_request_queue *queue)
{
    t_coder *coder;

    coder = malloc(sizeof(t_coder));
    assert(coder);
    coder->can_compile = false;
    pthread_cond_init(&coder->can_compile_cond,NULL);
    pthread_mutex_init(&coder->can_compile_mu, NULL);
    coder->coder_id = id;
    coder->queue = queue;
    return (coder);
}

t_coder *init_coder(int nb, t_request_queue *queue)
{
    t_coder *coders;
    int i;

    coders = malloc(sizeof(t_coder) * nb);
    assert(coders);
    i = 0;
    while (i < nb)
    {
        coders[i].can_compile = false;
        pthread_cond_init(&coders[i].can_compile_cond, NULL);
        pthread_mutex_init(&coders[i].can_compile_mu, NULL);
        coders[i].coder_id = i;
        coders[i].queue = queue;
        i++;
    }
    return (coders);
}